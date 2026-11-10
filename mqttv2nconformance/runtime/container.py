from failures import Failure
"""G4 appendix I type 0x04, independent from ITSK-00150 message-set 0x02/0x03."""
from dataclasses import dataclass
import struct

MAX_PAYLOAD = 1024 * 1024


@dataclass(frozen=True)
class Container:
    version: int
    fid: int
    standard_type: int
    flags: int
    metadata: bytes
    message_id: int
    psid: int
    payload: bytes


def prefix(byte_order):
    if byte_order not in ('big', 'little'):
        raise Failure('CONTAINER_FORMAT','컨테이너 byte_order는 big 또는 little이어야 합니다.')
    return '>' if byte_order == 'big' else '<'


def encode(c, byte_order='big'):
    order = prefix(byte_order)
    for name, limit in [('version',255), ('fid',65535), ('standard_type',255),
                        ('flags',255), ('message_id',255), ('psid',0xffffffff)]:
        v = getattr(c, name)
        if type(v) is not int or not 0 <= v <= limit:
            raise Failure('CONTAINER_FORMAT',name + ': 컨테이너 정수 범위 오류')
    if len(c.metadata) > 255 or not 1 <= len(c.payload) <= MAX_PAYLOAD:
        raise Failure('CONTAINER_FORMAT','메타데이터 또는 UPER payload 길이가 범위를 벗어났습니다.')
    return (struct.pack(order+'BBHBBB',4,c.version,c.fid,c.standard_type,len(c.metadata),c.flags)
            + c.metadata + struct.pack(order+'BII',c.message_id,c.psid,len(c.payload)) + c.payload)


def decode(wire, byte_order='big'):
    order = prefix(byte_order)
    if len(wire) < 16 or len(wire) > MAX_PAYLOAD + 271:
        raise Failure('CONTAINER_FORMAT','V2N 컨테이너가 잘렸거나 허용 크기를 초과했습니다.')
    kind, version, fid, standard, sem_len, flags = struct.unpack_from(order+'BBHBBB',wire)
    if kind != 4:
        raise Failure('CONTAINER_FORMAT',f'container_type 불일치: 기대 0x04 / 실제 0x{kind:02X}')
    end = 7 + sem_len
    if len(wire) < end + 9:
        raise Failure('CONTAINER_FORMAT','SEM 또는 메시지 헤더가 잘렸습니다.')
    message_id, psid, length = struct.unpack_from(order+'BII',wire,end)
    if not 1 <= length <= MAX_PAYLOAD or end + 9 + length != len(wire):
        raise Failure('CONTAINER_FORMAT','message_length와 실제 payload 길이가 다릅니다.')
    return Container(version,fid,standard,flags,bytes(wire[7:end]),message_id,psid,bytes(wire[end+9:]))


def validate(wire, message, config):
    c = decode(wire, config['byte_order'])
    expected = dict(version=config['container_version'],standard_type=config['standard_type'],
                    fid=message['fid'],psid=message['psid'])
    for name,value in expected.items():
        actual=getattr(c,name)
        if actual != value:
            raise Failure('CONTAINER_FIELD_MISMATCH',f'{name} 불일치: 기대 {value} / 실제 {actual}',criterion=f'{name}={value}',observed=dict(field=name,expected=value,actual=actual),checks=['시험 메시지 종류와 FID·PSID·컨테이너 설정 대조'])
    # message_id is a container identifier, not an ASN.1 MessageFrame type.
    return c
