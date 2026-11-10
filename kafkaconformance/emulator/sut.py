"""Independent development SUT; never imports the tester or its validator.

Control files arrange test data only; they are not Kafka protocol requirements.
"""
import argparse,base64,hashlib,json,os,time
from pathlib import Path
from confluent_kafka import Consumer,Producer,TopicPartition

def same(a,b):
    if type(a)!=type(b):return False
    if isinstance(a,dict):return a.keys()==b.keys() and all(same(v,b[k]) for k,v in a.items())
    if isinstance(a,list):return len(a)==len(b) and all(same(x,y) for x,y in zip(a,b))
    return a==b
def main():
    p=argparse.ArgumentParser();p.add_argument('--config',required=True);p.add_argument('--work',required=True);p.add_argument('--role',choices=['producer','consumer'],required=True);p.add_argument('--fault',choices=['none','no-commit','invalid-json','bad-field','wrong-topic'],default='none');a=p.parse_args()
    c=json.loads(Path(a.config).read_text(encoding='utf8'));work=Path(a.work);work.mkdir(parents=True,exist_ok=True)
    log=(work/'peer-records.jsonl').open('x',encoding='utf8',buffering=1)
    base={'bootstrap.servers':c['bootstrap_servers']}
    if c.get('security_file'):base.update(json.loads(Path(c['security_file']).read_text(encoding='utf8')))
    def emit(event,**kw):log.write(json.dumps(dict(event=event,time=time.time(),**kw),ensure_ascii=False)+'\n')
    seen=set();deadline=time.monotonic()+1800
    while time.monotonic()<deadline:
        try:stage=json.loads((work/'kafka-run.json').read_text(encoding='utf8'))
        except (OSError,ValueError):time.sleep(.05);continue
        if stage.get('phase')=='finished':break
        key=(stage['runId'],stage['testName'])
        if key in seen:time.sleep(.05);continue
        seen.add(key);s=stage['stream'];topic=c['topic_'+s]
        path=(Path(__file__).resolve().parents[1]/'fixtures/map.json' if c['facility_fixture']=='기본 제공 자료' else Path(c['facility_fixture'])) if s=='facility' else Path(__file__).resolve().parents[1]/'fixtures'/(s+'.json')
        expected=json.loads(path.read_text(encoding='utf8'));ready=work/'peer-ready.json'
        def prepared():
            temp=ready.with_suffix('.tmp');temp.write_text(json.dumps(dict(runId=key[0],testName=key[1])),encoding='utf8');os.replace(temp,ready)
        if a.role=='producer':
            producer=Producer({**base,'acks':'all','enable.idempotence':True,'message.timeout.ms':10000})
            prepared();due=time.monotonic()
            for n in range(stage['count']):
                while time.monotonic()<due:time.sleep(min(.05,max(0,due-time.monotonic())))
                value=json.loads(json.dumps(expected))
                if a.fault=='bad-field':
                    if s=='open':value['objectData']['objectID']=True
                    elif s=='platform':value['KAFKA_FCLTY_STATUS']['KAFKA_PORT']=65536
                    elif s=='i2x':value['i2xStrgHum']=101
                    elif s=='map':value['messageId']=19
                raw=json.dumps(value,ensure_ascii=False,separators=(',',':')).encode('utf8')
                if s=='open' and c.get('open_encoding')=='base64-json':raw=base64.b64encode(raw)
                if a.fault=='invalid-json':raw=b'{invalid'
                sent=[];actual_topic=topic+'.unagreed' if a.fault=='wrong-topic' else topic
                producer.produce(actual_topic,value=raw,partition=0,on_delivery=lambda e,m:sent.append((e,m)))
                producer.flush(15)
                if not sent or sent[0][0]:raise RuntimeError('독립 상대 발행 오류')
                m=sent[0][1];emit('published',runId=key[0],testName=key[1],round=n+1,topic=actual_topic,partition=m.partition(),offset=m.offset(),sha256=hashlib.sha256(raw).hexdigest(),valueBase64=base64.b64encode(raw).decode())
                due=time.monotonic()+(stage['period'] if stage['mode']=='period' else .02)
        else:
            consumer=Consumer({**base,'group.id':c['group_id'],'enable.auto.commit':False,'enable.auto.offset.store':False,'auto.offset.reset':c.get('auto_offset_reset','latest'),'heartbeat.interval.ms':3000,'session.timeout.ms':10000,'max.poll.interval.ms':1800000})
            assigned=[];pending=[]
            def on_assign(client,parts):
                for part in parts:part.offset=int(stage['baseline'][str(part.partition)])
                client.assign(parts);assigned.extend(parts)
            consumer.subscribe([topic],on_assign=on_assign)
            end=time.monotonic()+30
            while not assigned and time.monotonic()<end:
                early=consumer.poll(.1)
                if early is not None:pending.append(early)
            if not assigned:raise RuntimeError('대상 Consumer partition 할당 실패')
            prepared()
            try:
                for n in range(stage['count']):
                    end=time.monotonic()+c['timeout_seconds']+(stage['period'] if stage['mode']=='period' else 0);m=None
                    while time.monotonic()<end:
                        m=pending.pop(0) if pending else consumer.poll(.1)
                        if m is not None:break
                    if m is None:raise TimeoutError('독립 상대 자료 미수신')
                    if m.error():raise RuntimeError(str(m.error().code()))
                    raw=m.value();decoded=base64.b64decode(raw,validate=True) if s=='open' and c.get('open_encoding')=='base64-json' else raw
                    value=json.loads(decoded.decode('utf8'));valid=same(expected,value)
                    emit('received',runId=key[0],testName=key[1],round=n+1,topic=topic,partition=m.partition(),offset=m.offset(),sha256=hashlib.sha256(raw).hexdigest(),valueBase64=base64.b64encode(raw).decode(),processed=valid)
                    if not valid:raise ValueError('합의 준비자료와 독립 상대 수신 자료가 다릅니다.')
                    if a.fault!='no-commit':
                        consumer.commit(message=m,asynchronous=False);stored=consumer.committed([TopicPartition(topic,m.partition())],timeout=10)[0].offset
                        if stored!=m.offset()+1:raise ValueError('독립 상대 commit 재조회 불일치')
                        emit('committed',runId=key[0],testName=key[1],round=n+1,offset=stored)
            finally:consumer.close()
    emit('finished');log.close()
if __name__=='__main__':main()
