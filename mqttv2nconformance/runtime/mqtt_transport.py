"""libmosquitto transport with CONNACK, SUBACK and publication acknowledgement."""
from __future__ import annotations
import ctypes as C
from pathlib import Path
import os
import queue
import threading
import time
import uuid

_LIB = None
_DLL_DIRECTORIES = []


class MosquittoMessage(C.Structure):
    _fields_ = [('mid', C.c_int), ('topic', C.c_char_p), ('payload', C.c_void_p),
                ('payloadlen', C.c_int), ('qos', C.c_int), ('retain', C.c_bool)]


def library():
    global _LIB
    if _LIB is not None:
        return _LIB
    folder = Path(__file__).resolve().parents[1] / 'runtime/broker/mosquitto'
    if not (folder / 'mosquitto.dll').is_file():
        raise FileNotFoundError('동봉 MQTT 런타임이 없습니다. ZIP 전체를 다시 풀어 주세요.')
    if hasattr(os, 'add_dll_directory'):
        _DLL_DIRECTORIES.append(os.add_dll_directory(str(folder)))
    lib = C.CDLL(str(folder / 'mosquitto.dll'))
    for name, result, arguments in (
        ('mosquitto_lib_init', C.c_int, []),
        ('mosquitto_new', C.c_void_p, [C.c_char_p, C.c_bool, C.c_void_p]),
        ('mosquitto_destroy', None, [C.c_void_p]),
        ('mosquitto_username_pw_set', C.c_int, [C.c_void_p, C.c_char_p, C.c_char_p]),
        ('mosquitto_connect', C.c_int, [C.c_void_p, C.c_char_p, C.c_int, C.c_int]),
        ('mosquitto_reconnect', C.c_int, [C.c_void_p]),
        ('mosquitto_disconnect', C.c_int, [C.c_void_p]),
        ('mosquitto_loop_start', C.c_int, [C.c_void_p]),
        ('mosquitto_loop_stop', C.c_int, [C.c_void_p, C.c_bool]),
        ('mosquitto_subscribe', C.c_int, [C.c_void_p, C.POINTER(C.c_int), C.c_char_p, C.c_int]),
        ('mosquitto_publish', C.c_int, [C.c_void_p, C.POINTER(C.c_int), C.c_char_p, C.c_int, C.c_void_p, C.c_int, C.c_bool]),
        ('mosquitto_tls_set', C.c_int, [C.c_void_p, C.c_char_p, C.c_char_p, C.c_char_p, C.c_char_p, C.c_void_p]),
        ('mosquitto_strerror', C.c_char_p, [C.c_int]),
    ):
        function = getattr(lib, name)
        function.restype, function.argtypes = result, arguments
    lib.mosquitto_lib_init()
    _LIB = lib
    return lib


class MqttClient:
    def __init__(self, host, port, *, username=None, password=None, client_id=None, ca_file=None):
        self.lib = library()
        self.host, self.port = host, int(port)
        self.client = self.lib.mosquitto_new((client_id or ('prj22-easy-' + uuid.uuid4().hex[:16])).encode(), True, None)
        if not self.client:
            raise MemoryError('MQTT client allocation failed')
        self.connected = threading.Event()
        self.messages = queue.Queue()
        self.condition = threading.Condition()
        self.subacks, self.pubacks, self.subscriptions = {}, set(), {}
        self.connection_error = None
        self.started = False
        self.callbacks = []
        self._callback('connect', [C.c_void_p, C.c_void_p, C.c_int], self._connected)
        self._callback('disconnect', [C.c_void_p, C.c_void_p, C.c_int], self._disconnected)
        self._callback('subscribe', [C.c_void_p, C.c_void_p, C.c_int, C.c_int, C.POINTER(C.c_int)], self._subscribed)
        self._callback('publish', [C.c_void_p, C.c_void_p, C.c_int], self._published)
        self._callback('message', [C.c_void_p, C.c_void_p, C.POINTER(MosquittoMessage)], self._message)
        if username is not None:
            self._check(self.lib.mosquitto_username_pw_set(self.client, str(username).encode(), str(password or '').encode()))
        if ca_file:
            self._check(self.lib.mosquitto_tls_set(self.client, str(ca_file).encode(), None, None, None, None))

    def _callback(self, name, arguments, handler):
        callback_type = C.CFUNCTYPE(None, *arguments)
        callback = callback_type(handler)
        setter = getattr(self.lib, 'mosquitto_' + name + '_callback_set')
        setter.argtypes, setter.restype = [C.c_void_p, callback_type], None
        setter(self.client, callback)
        self.callbacks.append(callback)

    def _check(self, rc):
        if rc:
            raise ConnectionError('MQTT: ' + self.lib.mosquitto_strerror(rc).decode('utf8', errors='replace'))

    def _connected(self, client, userdata, rc):
        self.connection_error = rc if rc else None
        self.connected.set()

    def _disconnected(self, client, userdata, rc):
        self.connected.clear()

    def _subscribed(self, client, userdata, mid, count, granted):
        with self.condition:
            self.subacks[mid] = [granted[i] for i in range(count)]
            self.condition.notify_all()

    def _published(self, client, userdata, mid):
        with self.condition:
            self.pubacks.add(mid)
            self.condition.notify_all()

    def _message(self, client, userdata, pointer):
        message = pointer.contents
        self.messages.put(dict(topic=message.topic.decode('utf8'), payload=C.string_at(message.payload, message.payloadlen),
            qos=message.qos, retain=bool(message.retain), received=time.monotonic()))

    def connect(self, timeout=15):
        self._check(self.lib.mosquitto_connect(self.client, self.host.encode(), self.port, 30))
        self._check(self.lib.mosquitto_loop_start(self.client))
        self.started = True
        if not self.connected.wait(timeout):
            raise TimeoutError('MQTT CONNACK를 확인하지 못했습니다.')
        if self.connection_error:
            raise ConnectionError(f'MQTT CONNACK가 연결을 거부했습니다 (code {self.connection_error}).')

    def subscribe(self, topics, timeout=15):
        for topic, qos in topics.items():
            mid = C.c_int()
            with self.condition:
                self._check(self.lib.mosquitto_subscribe(self.client, C.byref(mid), topic.encode(), int(qos)))
                if not self.condition.wait_for(lambda: mid.value in self.subacks, timeout):
                    raise TimeoutError('MQTT SUBACK를 확인하지 못했습니다: ' + topic)
                grants = self.subacks.pop(mid.value)
            if not grants or any(q not in (0, 1, 2) for q in grants):
                raise ConnectionError('MQTT 구독이 거부됐습니다: ' + topic)
            if grants[0] != int(qos):
                raise ConnectionError(f'MQTT 요청 QoS {qos}와 SUBACK QoS {grants[0]}가 다릅니다: {topic}')
            self.subscriptions[topic] = int(qos)

    def publish(self, topic, payload, *, qos=0, retain=False, key=None, timeout=15):
        payload = payload.encode('utf8') if isinstance(payload, str) else bytes(payload)
        mid = C.c_int()
        buffer = C.create_string_buffer(payload)
        with self.condition:
            self._check(self.lib.mosquitto_publish(self.client, C.byref(mid), topic.encode(), len(payload), buffer, int(qos), bool(retain)))
            if not self.condition.wait_for(lambda: mid.value in self.pubacks, timeout):
                raise TimeoutError('MQTT 발행 완료를 확인하지 못했습니다: ' + topic)
            self.pubacks.remove(mid.value)
        return dict(topic=topic, qos=int(qos), packetId=mid.value, completed=True,
                    completion={0: 'socket-send', 1: 'PUBACK', 2: 'PUBCOMP'}[int(qos)])

    def receive(self, timeout=.1):
        try:
            return self.messages.get(timeout=timeout)
        except queue.Empty:
            return None

    def close(self):
        if self.client:
            self.lib.mosquitto_disconnect(self.client)
            if self.started:
                self.lib.mosquitto_loop_stop(self.client, True)
            self.lib.mosquitto_destroy(self.client)
            self.client = None
