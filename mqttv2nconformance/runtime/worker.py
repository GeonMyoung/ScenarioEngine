"""G4 MQTT/V2N actual transport runner. Broker completion and SUT receipt stay separate."""
import argparse,json,os,queue,secrets,sys,threading,time
from datetime import datetime, timezone
from pathlib import Path
from catalog import CASES,MESSAGES,parse_config
from codec import Codec
from container import Container,encode,decode,validate,MAX_PAYLOAD
from transport import Transport,Stopped
from failures import Failure,describe
from publish_only import publish_bsm,CASE as BSM_PUBLISH_CASE,NOTICE as BSM_NOTICE
from readiness import write as write_readiness
from public_logs import present as public_log


class Events:
    def __init__(self,directory,titles=None):
        self.path=Path(directory);self.path.mkdir(parents=True,exist_ok=True)
        self.stream=(self.path/'events.jsonl').open('w',encoding='utf-8',newline='\n')
        self.diagnostics=(self.path/'diagnostic-events.jsonl').open('w',encoding='utf-8',newline='\n');self.titles=titles or {}
        self.lock=threading.RLock();self.test='MainScenario';self.sequence=0;self.terminal=False

    def emit(self,event):
        with self.lock:
            if self.terminal:raise RuntimeError('FINISH 이후 알림 발생')
            self.sequence+=1;event['sequence']=self.sequence
            self.stream.write(json.dumps(event,ensure_ascii=False)+'\n');self.stream.flush()
            if event.get('testName')=='MainScenario' and event.get('value')=='FINISH':self.terminal=True

    def state(self,test,value):self.emit(dict(kind='state',testName=test,value=value))

    def info(self,text,data=None,sender='시험 시스템',test=None):
        if self.terminal:raise RuntimeError('FINISH 이후 알림 발생')
        self.diagnostic(text,data,sender,test)
        visible=public_log(text,data,self.titles)
        if visible is None:return
        text,data=visible
        body=json.dumps(data or {},ensure_ascii=False,separators=(',',':'))
        if len(body.encode('utf-8'))<=10000:
            self.emit(dict(kind='info',testName=test or self.test,log=text,data=body,sender=sender));return
        # Store complete data; display parts remain valid JSON and preserve every character.
        parts=[body[i:i+1800] for i in range(0,len(body),1800)]
        attachment=secrets.token_hex(8)
        for i,part in enumerate(parts,1):
            self.emit(dict(kind='info',testName=test or self.test,log=f'{text} (자료 {i}/{len(parts)})',sender=sender,
                           data=json.dumps(dict(encoding='json-text-parts',attachment_id=attachment,part=i,parts=len(parts),value=part),ensure_ascii=False)))

    def diagnostic(self,text,data=None,sender='시험 시스템',test=None):
        with self.lock:
            self.diagnostics.write(json.dumps(dict(kind='info',testName=test or self.test,log=text,data=json.dumps(data or {},ensure_ascii=False),sender=sender),ensure_ascii=False)+'\n');self.diagnostics.flush()

    def close(self):self.stream.close();self.diagnostics.close()


class Receipt:
    """A live file observation adapter, not a required standard protocol or ACK topic."""
    def __init__(self,path):
        self.path=Path(path);st=self.path.stat() if self.path.exists() else None
        self.offset=st.st_size if st else 0;self.identity=(st.st_dev,st.st_ino) if st else None
    def poll(self):
        if not self.path.exists():return []
        st=self.path.stat();identity=(st.st_dev,st.st_ino)
        if st.st_size<self.offset or (self.identity is not None and self.identity!=identity):raise ValueError('대상 수신 관측 파일이 실행 중 교체 또는 축소됐습니다.')
        self.identity=identity
        result=[]
        with self.path.open('rb') as f:
            f.seek(self.offset)
            for _ in range(128):
                before=f.tell();line=f.readline(2*MAX_PAYLOAD+8192)
                if not line:break
                if not line.endswith(b'\n'):
                    if len(line)>=2*MAX_PAYLOAD+8192:raise ValueError('수신 관측 레코드 크기 초과')
                    f.seek(before);break
                result.append(json.loads(line.decode('utf-8')))
            self.offset=f.tell()
        return result


def wait(stop,seconds):
    until=time.monotonic()+seconds
    while True:
        if stop():raise Stopped()
        remaining=until-time.monotonic()
        if remaining<=0:return
        time.sleep(min(.05,remaining))


def security(config):
    from credentials import connection
    return connection(config)


class Runner:
    def __init__(self,case,config,output,codec,stop):
        self.case=case;self.role=CASES[case];self.c=parse_config(case,config)
        self.events=Events(output,{x[0]:x[3] for x in self.c['selected']});self.codec=Codec(codec);self.stop=stop;self.round=0;self.current=''
        self.results=[];self.completed=0;self.failure_details=[]
        self.client_id=self.c['client_id'].strip() or 'g4-mqtt-'+secrets.token_hex(8)
        self.message_sequence=0

    def observe(self,direction,kind,detail):
        sender=self.role['engine'] if direction in ('send','local') else ('MQTT Broker' if kind!='PUBLISH' else self.role['sut'])
        self.events.diagnostic(f'{kind} '+{'send':'전송 요청','receive':'수신 확인','local':'전송 완료'}[direction],
                         dict(direction=direction,packet=kind,round=self.round,**detail),sender)

    def client(self):
        return Transport(self.c['host'],self.c['port'],client_id=self.client_id,keepalive=self.c['keepalive'],
                         stop=self.stop,observe=self.observe,**security(self.c))

    def decoded(self,key,wire):
        message=MESSAGES[key];c=validate(wire,message,self.c)
        d=self.codec.validate(message['frame'],c.payload)
        return c,dict(container_type=4,version=c.version,fid=c.fid,psid=c.psid,standard_type=c.standard_type,
            message_id=c.message_id,message_length=len(c.payload),sem_length=len(c.metadata),flags=c.flags,
            metadata_hex=c.metadata.hex(),frame_id=message['frame'],decoded=d.get('decoded'),validation=d.get('validation'),
            **(dict(tim_profile=d.get('timProfile'),tim_regional=d.get('timRegional')) if key=='tim' else {}))

    def received(self,key,packet,result,*,view=None,error=None,test=None,progress=None):
        title='TIM '+view['title'] if key=='tim' and view and view.get('title') else MESSAGES[key]['title']
        data=dict(direction='수신',message=title,topic=packet['topic'],
                  observed_at=packet.get('received_utc'),sequence=packet['sequence'],
                  payload_hex=packet['payload'].hex(),message_result=result)
        if view:data.update(view)
        if progress:data.update(progress)
        if error:data.update(describe(error).details())
        summary=f'{title} {packet["sequence"]}번 수신 · {result}'
        if progress:summary+=f' · {progress["validated"]}/{progress["expected"]}건 확인'
        if error:summary+=' · '+describe(error).finding
        self.events.info(summary,data,self.role['sut'],test=test)

    def number_message(self,packet):
        self.message_sequence+=1
        packet['sequence']=self.message_sequence

    def receiving(self,client,key):
        count=self.c['repetitions']
        topic=self.c['topic_'+key]
        response_timeout=self.c['timeout_seconds']
        pending=queue.Queue(maxsize=128)
        failed=threading.Event()
        errors=[]
        ready=self.events.path/'ready.json'
        generation=secrets.token_hex(8)
        subscribed=False
        collected=0
        collection_error=None

        def readiness(active):
            write_readiness(ready,dict(test=self.events.test,tests=[self.events.test],
                message=key,topic=topic,active=active,generation=generation,expected=count))

        def validate_samples():
            while True:
                task=pending.get()
                if task is None:return
                message_key,packet,skip=task
                if skip:
                    self.received(message_key,packet,skip)
                    continue
                if self.stop() or failed.is_set():
                    self.received(key,packet,'수신 완료 · 검사 미실행')
                    continue
                try:
                    if packet['topic']!=topic:
                        raise Failure('TOPIC_MISMATCH','설정 토픽과 수신 토픽이 다릅니다.',
                            observed=dict(field='토픽',expected=topic,actual=packet['topic']))
                    _,view=self.decoded(key,packet['payload'])
                except Exception as error:
                    error.sample=packet['sequence']
                    errors.append(error)
                    self.received(key,packet,'정합성 실패',error=error)
                    failed.set()
                else:
                    self.completed+=1
                    self.received(key,packet,'정합성 확인',view=view,
                                  progress=dict(validated=self.completed,expected=count))

        def run_validator():
            try:validate_samples()
            except Exception as error:
                errors.append(error)
                failed.set()

        validator=threading.Thread(target=run_validator,name='mqtt-v2n-validator')
        validator.start()
        try:
            client.subscribe({topic:self.c['qos']},response_timeout)
            subscribed=True
            readiness(True)
            self.events.info(f'{MESSAGES[key]["title"]} 구독 완료 · {count}건 수신 대기',
                             dict(message=key,expected=count,topic=topic))
            while collected<count:
                client.check()
                if self.stop():raise Stopped('사용자가 시험을 중지했습니다.')
                if failed.is_set():raise errors[0]
                packet=client.receive(.05,observe=False)
                if not packet:continue
                self.number_message(packet)
                client.record_message(packet)
                skip=None
                message_key=key
                if packet['retain']:
                    skip='이전 보관 메시지 · 집계 제외'
                else:
                    try:envelope=decode(packet['payload'],self.c['byte_order'])
                    except ValueError:envelope=None
                    if envelope:
                        other=next((name for name in self.role['messages'] if name!=key
                            and MESSAGES[name]['fid']==envelope.fid and MESSAGES[name]['psid']==envelope.psid),None)
                        if other and packet['topic']==topic and self.c.get('topic_'+other) in (None,topic):
                            message_key=other
                            skip='공유 토픽의 다른 메시지 · 집계 제외'
                if not skip:
                    collected+=1
                    self.round=collected
                try:pending.put_nowait((message_key,packet,skip))
                except queue.Full:
                    self.received(message_key,packet,'수신 완료 · 검사 대기열 초과')
                    raise RuntimeError('메시지 검증 대기열 용량을 초과했습니다.')
        except Exception as error:
            collection_error=error
        finally:
            if subscribed:
                try:client.unsubscribe(topic,response_timeout)
                except Exception as error:
                    if collection_error is None:collection_error=error
                finally:
                    try:readiness(False)
                    except Exception as error:
                        if collection_error is None:collection_error=error
            while validator.is_alive():
                try:pending.put(None,timeout=.05);break
                except queue.Full:continue
            validator.join()
        if self.stop():raise Stopped('사용자가 시험을 중지했습니다.')
        if collection_error:raise collection_error
        if errors:raise errors[0]

    def report_failure(self,error,test,key,received=None,validated=None):
        failure=describe(error)
        details=failure.details(message=key,topic=self.c.get('topic_'+key),sample=getattr(error,'sample',None),
            received=self.round if received is None else received,validated=self.completed if validated is None else validated)
        summary=failure.summary()
        self.events.info(summary,details,test=test)
        self.failure_details.append(dict(test=test,summary=summary,**details))
        return summary,details

    def run_tim_group(self,selected):
        from tim_five import collect,CONTENT_REVIEW
        self.round=0;self.completed=0;self.events.test=selected[0][0];client=None
        for test,_,_,_ in selected:self.events.state(test,'START')
        def finish(kind,state,completed,error=None):
            test=next(x[0] for x in selected if x[2]==kind)
            if any(r['test']==test for r in self.results):return
            result=dict(test=test,result=state,completed=completed)
            result.update(duplicates=getattr(self,'tim_summary',{}).get('types',{}).get(kind,{}).get('duplicates',0),content_review=CONTENT_REVIEW)
            if error:
                if isinstance(error,Stopped):
                    result['reason']='사용자가 시험을 중지했습니다.';self.events.info(result['reason'],test=test)
                else:
                    counts=getattr(self,'tim_summary',{}).get('types',{}).get(kind,{})
                    reason,details=self.report_failure(error,test,'tim',received=counts.get('received',0),validated=completed);result.update(reason=reason,failure=details)
            self.events.state(test,state);self.results.append(result)
        try:
            client=self.client();client.connect(self.c['timeout_seconds'])
            collect(self,client,selected,finish)
        except Exception as error:
            state='STOPPED' if isinstance(error,Stopped) else 'FAIL'
            for _,_,kind,_ in selected:finish(kind,state,getattr(self,'tim_summary',{}).get('types',{}).get(kind,{}).get('validated',0),error)
            raise
        finally:
            if client:client.close()

    def publishing(self,client,key):
        if self.case==BSM_PUBLISH_CASE:return publish_bsm(self,client)
        receipt=Receipt(self.c['observation_file']);message=MESSAGES[key];payload=self.codec.sample(message['frame'])
        # Verify the chosen sample before using it as SUT stimulus.
        self.codec.validate(message['frame'],payload);seed=secrets.randbelow(256)
        for n in range(self.c['repetitions']):
            self.round=n+1;wire=encode(Container(self.c['container_version'],message['fid'],self.c['standard_type'],0,b'',(seed+n)%256,message['psid'],payload),self.c['byte_order'])
            _,view=self.decoded(key,wire);topic=self.c['topic_'+key]
            self.message_sequence+=1
            sent=dict(direction='송신',message=message['title'],sequence=self.message_sequence,topic=topic,
                      payload_hex=wire.hex(),observed_at=datetime.now(timezone.utc).isoformat(timespec='milliseconds'),**view)
            try:completion=client.publish(topic,wire,qos=self.c['qos'],retain=False,timeout=self.c['timeout_seconds'])
            except Exception as error:
                self.events.info(f'{message["title"]} {self.message_sequence}번 발행 시도',
                                 dict(**sent,message_result='발행 미완료',**describe(error).details()),self.role['engine'])
                raise
            self.events.info(f'{message["title"]} {self.message_sequence}번 발행 완료',
                             dict(**sent,message_result='발행 완료 · 대상 수신 확인 대기'),self.role['engine'])
            self.events.info('MQTT 발행 완료 후 대상의 실제 수신 관측을 기다립니다.',dict(**completion,sut_receive_confirmed=False))
            deadline=time.monotonic()+self.c['timeout_seconds'];matched=False
            while time.monotonic()<deadline and not matched:
                client.check()
                for row in receipt.poll():
                    if not isinstance(row,dict):raise ValueError('대상 수신 관측 레코드는 JSON 객체여야 합니다.')
                    observation={k:row[k] for k in ('topic','payload_hex','frame_id','valid','received_unix') if k in row}
                    if isinstance(row.get('payload_hex'),str):
                        self.message_sequence+=1
                        observation.update(direction='수신',message=message['title'],sequence=self.message_sequence,
                            topic=row.get('topic',''),message_result='대상 수신 관측 자료')
                    self.events.info('대상 수신 관측 자료를 확인합니다.',observation,self.role['sut'])
                    if row.get('topic')==topic and row.get('payload_hex')==wire.hex():
                        if row.get('valid') is not True or row.get('frame_id')!=message['frame']:raise ValueError('대상 수신 관측에서 메시지 검사 실패 또는 종류 불일치')
                        matched=True
                if not matched:wait(self.stop,.025)
            if not matched:raise TimeoutError('Broker 발행 완료는 확인했으나 대상 수신 관측이 없습니다.')
            self.completed=n+1
            self.events.info(f'{message["title"]} 대상 수신 {n+1}/{self.c["repetitions"]}회 확인',dict(round=n+1,topic=topic,observation='새 JSONL 레코드의 Topic·원문·디코딩 결과 일치'))
            if n+1<self.c['repetitions']:wait(self.stop,self.c['publish_interval_seconds'])

    def run(self):
        overall='SUCCESS';self.events.state('MainScenario','START')
        try:
            self.events.info('차량–센터 MQTT/V2N 시험을 시작합니다.',dict(case=self.case,sut=self.role['sut'],engine=self.role['engine'],profile='G4-SINGLE-04-DEV-1',
                byte_order=self.c['byte_order'],version=self.c['container_version'],standard_type=self.c['standard_type'],
                repetitions=self.c['repetitions'],topics={k:self.c.get('topic_'+k) for k in self.role['messages']},selected=[x[0] for x in self.c['selected']]))
            tim_items=[item for item in self.c['selected'] if item[1]=='tim'] if self.role.get('center_provider') else []
            for test,key,mode,title in self.c['selected']:
                if key=='tim' and tim_items:
                    if test==tim_items[0][0]:
                        if self.stop():raise Stopped()
                        self.run_tim_group(tim_items)
                    continue
                if self.stop():raise Stopped()
                self.events.test=test;self.round=0;self.completed=0;self.events.state(test,'START');client=None
                try:
                    self.events.info(title+'을 시작합니다.',dict(purpose='설정 토픽·컨테이너·UPER와 실제 송수신 관측 확인',message=key))
                    client=self.client();client.connect(self.c['timeout_seconds'])
                    if self.role['receive']:self.receiving(client,key)
                    else:self.publishing(client,key)
                    client.close();client=None
                    self.events.state(test,'SUCCESS');self.results.append(dict(test=test,result='SUCCESS',completed=self.completed))
                except Exception as e:
                    if client:client.close();client=None
                    state='STOPPED' if isinstance(e,Stopped) else 'FAIL'
                    if state=='STOPPED':
                        reason='사용자가 시험을 중지했습니다.'
                        detail=None
                        self.events.info(reason,dict(completed=self.completed,received=self.round,expected=self.c['repetitions']))
                    else:
                        reason,detail=self.report_failure(e,test,key)
                    self.events.state(test,state)
                    self.results.append(dict(test=test,result=state,completed=self.completed,reason=reason,failure=detail))
                    raise
                finally:
                    if client:client.close()
        except Exception as e:
            overall='STOPPED' if isinstance(e,Stopped) else 'FAIL'
            self.events.test='MainScenario';self.events.info('전체 시험 종료: '+str(e))
        finally:
            self.events.test='MainScenario'
            for test,key,mode,title in self.c['selected']:
                if not any(r['test']==test for r in self.results):
                    reason='앞선 항목의 실패 또는 중지로 실행하지 않았습니다.'
                    self.events.info(title+' — 미실행. '+reason,dict(result='NOT_RUN',reason=reason),test=test)
                    self.results.append(dict(test=test,result='NOT_RUN',completed=0,reason=reason))
            result=dict(case=self.case,result=overall,tests=self.results,failures=self.failure_details,profile='G4-SINGLE-04-DEV-1',sut=self.role['sut'])
            if hasattr(self,'tim_summary'):result['tim_summary']=self.tim_summary
            if self.case==BSM_PUBLISH_CASE:
                result.update(automatic_result_scope='BSM 발행 절차',sut_receive_confirmed=False,final_verdict='PENDING_RECEIVER_LOG_REVIEW',notice=BSM_NOTICE,publish_summary=getattr(self,'publish_summary',None))
                self.events.info(BSM_NOTICE,dict(automatic_result=overall,published=self.completed,expected=self.c['repetitions'],sut_receive_confirmed=False,final_verdict='PENDING_RECEIVER_LOG_REVIEW'))
            (self.events.path/'result.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
            self.events.info('선택 시험의 결과와 수집 자료를 저장했습니다.',result)
            self.events.state('MainScenario',overall);self.events.state('MainScenario','FINISH');self.events.close()
        return result


def main():
    p=argparse.ArgumentParser();p.add_argument('--case',required=True);p.add_argument('--config',required=True)
    p.add_argument('--output',required=True);p.add_argument('--work',required=True);p.add_argument('--codec')
    a=p.parse_args();config=json.loads(Path(a.config).read_text(encoding='utf-8-sig'));work=Path(a.work)
    codec=a.codec or str(Path(__file__).resolve().parents[1]/'bin/MqttPayload.exe')
    r=Runner(a.case,config,a.output,codec,lambda:(work/'mqttv2n-stop').exists());r.run()
    # A completed FAIL/STOPPED is carried by result events, not a worker crash.
    return 0
if __name__=='__main__':sys.exit(main())
