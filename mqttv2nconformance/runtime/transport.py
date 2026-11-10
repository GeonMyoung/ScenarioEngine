"""Scoped adaptation of the imported prj22 transport; original kept unchanged."""
import ctypes as C
import queue
import time
from datetime import datetime, timezone
from mqtt_transport import MqttClient


class Stopped(Exception):
    pass


class Transport(MqttClient):
    def __init__(self,host,port,*,stop=lambda:False,observe=lambda *a:None,keepalive=30,will=None,**kwargs):
        self.stop_requested=stop;self.observe=observe;self.keepalive=int(keepalive)
        self.fault=None;self.closing=False;self.client=None
        try:
            super().__init__(host,port,**kwargs)
            self.messages=queue.Queue(maxsize=128);self.unsubacks=set()
            for name,result,args in [
                ('mosquitto_connect_async',C.c_int,[C.c_void_p,C.c_char_p,C.c_int,C.c_int]),
                ('mosquitto_unsubscribe',C.c_int,[C.c_void_p,C.POINTER(C.c_int),C.c_char_p]),
                ('mosquitto_will_set',C.c_int,[C.c_void_p,C.c_char_p,C.c_int,C.c_void_p,C.c_int,C.c_bool])]:
                f=getattr(self.lib,name);f.restype,f.argtypes=result,args
            self._callback('unsubscribe',[C.c_void_p,C.c_void_p,C.c_int],self._unsubscribed)
            if will:
                payload=bytes.fromhex(will['payload_hex']);buf=C.create_string_buffer(payload)
                self._check(self.lib.mosquitto_will_set(self.client,will['topic'].encode(),len(payload),buf,int(will.get('qos',1)),bool(will.get('retain',False))))
        except Exception:
            if self.client:self.close()
            raise

    def check(self):
        if self.stop_requested():raise Stopped('사용자가 시험을 중지했습니다.')
        if self.fault:raise ConnectionError(self.fault)

    def _wait(self,predicate,timeout,description):
        deadline=time.monotonic()+timeout
        with self.condition:
            while not predicate():
                self.check()
                remaining=deadline-time.monotonic()
                if remaining<=0:raise TimeoutError(description)
                self.condition.wait(min(.05,remaining))
        self.check()

    def _connected(self,client,userdata,rc):
        super()._connected(client,userdata,rc)
        with self.condition:self.condition.notify_all()

    def _disconnected(self,client,userdata,rc):
        super()._disconnected(client,userdata,rc)
        if not self.closing:self.fault=f'MQTT 연결이 종료되었습니다 (code {rc}).'
        with self.condition:self.condition.notify_all()

    def _message(self,client,userdata,pointer):
        try:
            m=pointer.contents
            if m.payloadlen<0 or m.payloadlen>1024*1024+271:raise ValueError('수신 MQTT payload 크기 초과')
            event=dict(topic=m.topic.decode('utf-8'),payload=C.string_at(m.payload,m.payloadlen),
                       qos=int(m.qos),retain=bool(m.retain),received=time.monotonic(),
                       received_utc=datetime.now(timezone.utc).isoformat(timespec='milliseconds'),packet_id=int(m.mid))
            self.messages.put_nowait(event)
        except Exception as e:self.fault='MQTT 수신 실패: '+str(e)

    def _unsubscribed(self,client,userdata,mid):
        with self.condition:self.unsubacks.add(mid);self.condition.notify_all()

    def connect(self,timeout=15):
        self.check();self.observe('send','CONNECT',dict(host=self.host,port=self.port,keepalive=self.keepalive))
        self._check(self.lib.mosquitto_connect_async(self.client,self.host.encode(),self.port,self.keepalive))
        self._check(self.lib.mosquitto_loop_start(self.client));self.started=True
        self._wait(self.connected.is_set,timeout,'MQTT CONNACK 대기 제한시간을 초과했습니다.')
        if self.connection_error:raise ConnectionError(f'MQTT 연결 거부 (code {self.connection_error})')
        self.observe('receive','CONNACK',dict(code=0))

    def subscribe(self,topics,timeout=15):
        for topic,qos in topics.items():
            self.check();mid=C.c_int()
            with self.condition:
                self.observe('send','SUBSCRIBE',dict(topic=topic,qos=qos))
                self._check(self.lib.mosquitto_subscribe(self.client,C.byref(mid),topic.encode(),int(qos)))
                self._wait(lambda:mid.value in self.subacks,timeout,'MQTT SUBACK 대기시간 초과')
                grants=self.subacks.pop(mid.value)
            self.observe('receive','SUBACK',dict(packet_id=mid.value,granted_qos=grants))
            if grants!=[int(qos)]:raise ConnectionError('요청 QoS와 SUBACK 허용값이 다릅니다.')
            self.subscriptions[topic]=int(qos)

    def unsubscribe(self,topic,timeout=15):
        self.check();mid=C.c_int()
        with self.condition:
            self.observe('send','UNSUBSCRIBE',dict(topic=topic))
            self._check(self.lib.mosquitto_unsubscribe(self.client,C.byref(mid),topic.encode()))
            self._wait(lambda:mid.value in self.unsubacks,timeout,'MQTT UNSUBACK 대기시간 초과')
            self.unsubacks.remove(mid.value)
        self.subscriptions.pop(topic,None);self.observe('receive','UNSUBACK',dict(packet_id=mid.value))

    def publish(self,topic,payload,*,qos=0,retain=False,timeout=15):
        self.check();payload=bytes(payload);mid=C.c_int();buf=C.create_string_buffer(payload)
        with self.condition:
            self._check(self.lib.mosquitto_publish(self.client,C.byref(mid),topic.encode(),len(payload),buf,int(qos),bool(retain)))
            self._wait(lambda:mid.value in self.pubacks,timeout,'MQTT 발행 완료 대기시간 초과')
            self.pubacks.remove(mid.value)
        kind={0:'socket-send',1:'PUBACK',2:'PUBCOMP'}[int(qos)]
        self.observe('receive' if qos else 'local',kind,dict(topic=topic,packet_id=mid.value,qos=qos))
        return dict(topic=topic,packet_id=mid.value,qos=qos,completion=kind)

    def record_message(self,event):
        self.observe('receive','PUBLISH',dict(topic=event['topic'],payload_hex=event['payload'].hex(),
                     qos=event['qos'],retain=event['retain'],packet_id=event['packet_id'],received_monotonic=event['received']))

    def receive(self,timeout=.1,observe=True):
        self.check()
        event=super().receive(min(timeout,.1))
        if event and observe:self.record_message(event)
        return event

    def close(self):
        if self.client:
            self.closing=True
            if self.started:self.observe('send','DISCONNECT',{})
            super().close()
            # The network thread is stopped. Preserve in-flight/excess raw evidence.
            if hasattr(self,'messages'):
                while True:
                    try:self.record_message(self.messages.get_nowait())
                    except queue.Empty:break

