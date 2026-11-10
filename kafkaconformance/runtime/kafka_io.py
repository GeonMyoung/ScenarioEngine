"""librdkafka observation adapter; follows prj22 explicit commit/readback boundary."""
import json
from pathlib import Path
from confluent_kafka import Consumer, Producer, TopicPartition

def common(c):
    conf={'bootstrap.servers':c['bootstrap_servers'], 'socket.timeout.ms':10000, 'socket.connection.setup.timeout.ms':10000}
    if c.get('security_file'):
        security=json.loads(Path(c['security_file']).read_text(encoding='utf-8-sig'))
        allowed={'security.protocol','sasl.mechanism','sasl.username','sasl.password','ssl.ca.location','ssl.certificate.location','ssl.key.location','ssl.key.password'}
        if set(security)-allowed: raise ValueError('인증 설정에 허용되지 않은 키가 있습니다.')
        conf.update(security)
    return conf

def consumer(c, group=None):
    return Consumer({**common(c),'group.id':group or c['group_id'], 'enable.auto.commit':False,
                     'enable.auto.offset.store':False,'auto.offset.reset':c.get('auto_offset_reset','latest'),
                     'heartbeat.interval.ms':3000,'session.timeout.ms':10000,'max.poll.interval.ms':1800000})

def producer(c):
    return Producer({**common(c),'acks':'all','enable.idempotence':True,'message.timeout.ms':int(c['timeout_seconds']*1000)})

def metadata(client, topic, timeout):
    # No auto-creation: use list-all metadata and require the agreed topic exists.
    m=client.list_topics(timeout=timeout)
    if topic not in m.topics or m.topics[topic].error: raise ValueError('합의 토픽이 브로커에 없습니다: '+topic)
    return sorted(m.topics[topic].partitions)

def offsets(client, topic, partitions, timeout):
    rows=client.committed([TopicPartition(topic,p) for p in partitions],timeout=timeout)
    if any(x.error for x in rows): raise RuntimeError('브로커 저장 offset 조회 실패')
    return {x.partition:x.offset for x in rows}

def commit_checked(client, msg, timeout):
    target=TopicPartition(msg.topic(),msg.partition(),msg.offset()+1)
    rows=client.commit(offsets=[target], asynchronous=False)
    if any(x.error for x in rows): raise RuntimeError('offset commit 실패')
    stored=offsets(client,msg.topic(),[msg.partition()],timeout)[msg.partition()]
    if stored != target.offset: raise RuntimeError('commit 후 브로커 저장 offset 불일치')
    return stored
