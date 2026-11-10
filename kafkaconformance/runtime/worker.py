"""Isolated Kafka test worker. Emits ordered ScenarioEngine events to JSONL."""
import argparse, base64, hashlib, json, os, time, uuid, traceback
from pathlib import Path
from confluent_kafka import TopicPartition
from catalog import CASES, STREAMS, parse_config, fixture, items
from fields import decode, validate
import presentation as view
from kafka_io import consumer, producer, metadata, offsets, commit_checked

def dump(v): return json.dumps(v,ensure_ascii=False,separators=(',',':'),allow_nan=False)
def save(path,v):
    temp=path.with_suffix(path.suffix+'.tmp');temp.write_text(dump(v),encoding='utf8')
    # Windows readers can briefly hold a sharing lock while reading control JSON.
    for attempt in range(100):
        try:os.replace(temp,path);return
        except PermissionError:
            if attempt==99:raise
            time.sleep(.02)
def masked(v):
    if isinstance(v,dict): return {k:('***' if any(s in str(k).lower() for s in ('password','secret','token','authorization','apikey','api_key')) else masked(x)) for k,x in v.items()}
    if isinstance(v,list):return [masked(x) for x in v]
    return v
class Stopped(Exception):pass

class Runner:
    def __init__(self,case,raw,output,work=None):
        self.case=case;self.raw=raw;self.out=Path(output);self.out.mkdir(parents=True,exist_ok=False)
        self.id=uuid.uuid4().hex;self.test='MainScenario';self.round=0;self.seq=0
        self.events=(self.out/'events.jsonl').open('w',encoding='utf8',buffering=1)
        self.records=(self.out/'records.jsonl').open('w',encoding='utf8',buffering=1)
        self.work=Path(work) if work else self.out.parent
        self.control=self.work/'kafka-run.json';self.stop=self.work/'kafka-stop'
        self.rows=[];self.messages=0;self.display_index=0;self.title='시험 준비';self.config=None
        self.public=(self.out/'user-events.jsonl').open('w',encoding='utf8',buffering=1)
    def emit(self,kind,**args):
        self.events.write(dump(dict(kind=kind,testName=self.test,time=time.time(),**args))+'\n')
    def state(self,value):self.emit('state',value=value)
    def log(self,text,sender='시험 시스템'):
        sender=sender.replace('Kafka Broker','Kafka 브로커')
        text='['+view.stage(text)+'] '+text
        self.public.write(dump(dict(log=text,sender=sender))+'\n');self.emit('info',log=text,sender=sender)
    def data(self,text,value,sender='시험 시스템'):
        sender=sender.replace('Kafka Broker','Kafka 브로커')
        phase=view.stage(text,value);text='['+phase+'] '+text
        value={'인터페이스':'Kafka',**view.mask(value),'단계':phase};self.display_index+=1
        self.public.write(dump(dict(log=text,sender=sender,data=value))+'\n')
        raw=dump(value)
        if len(raw.encode('utf8'))>6000:
            parts=[raw[i:i+1500] for i in range(0,len(raw),1500)]
            for i,part in enumerate(parts):self.emit('info',log=text+f' · 자료 {self.display_index} ({i+1}/{len(parts)})',sender=sender,data=dump({'자료 구분':'분할 자료','자료 번호':self.display_index,'분할 번호':i+1,'전체 분할 수':len(parts),'분할 데이터':part}))
        else:self.emit('info',log=text,sender=sender,data=raw)
    def diagnostic(self,error):
        with (self.out/'diagnostics.jsonl').open('a',encoding='utf8') as f:f.write(dump(dict(testName=self.test,round=self.round,error=type(error).__name__,detail=str(error),traceback=traceback.format_exc()))+'\n')
    def check_stop(self):
        if self.stop.exists(): raise Stopped('사용자 중지. 실제 관측 기록을 보존했습니다.')
    def wait(self,seconds):
        end=time.monotonic()+seconds
        while time.monotonic()<end:self.check_stop();time.sleep(min(.05,max(0,end-time.monotonic())))
    def record(self,event,sender,**detail):
        self.seq+=1
        v=dict(runId=self.id,testName=self.test,round=self.round,sequence=self.seq,event=event,sender=sender,monotonic=time.monotonic(),**detail)
        self.records.write(dump(v)+'\n')
        shown=view.observation(event,detail)
        if shown:
            phase,log,data=shown;prefix='준비' if self.round==0 else f'{self.round}/{self.wanted}회'
            self.data(prefix+' · '+log,{'자료 구분':'시험 근거','시험':self.title,'단계':phase,**data},sender)
    def message(self,event,sender,msg=None,raw=None,topic=None,partition=None,offset=None,key=None):
        if msg is not None:raw=msg.value();topic=msg.topic();partition=msg.partition();offset=msg.offset();key=msg.key()
        self.messages+=1;encoded=self.stream=='open' and self.encoding=='base64-json';parsed=None;parse_ok=False
        try:parsed=decode(raw,self.stream,self.encoding);parse_ok=True
        except (ValueError,UnicodeError,AttributeError,TypeError):pass
        public_value=view.mask(parsed) if parse_ok else None
        # Correlation bytes, hash and transport diagnostics are local only.
        detail=dict(topic=topic,partition=partition,offset=offset,keyBase64=base64.b64encode(key).decode() if key else None,
                    value=dump(public_value) if parse_ok else raw.decode('utf8',errors='backslashreplace') if raw is not None else None,
                    valueBase64=base64.b64encode(raw).decode() if raw is not None else None,sha256=hashlib.sha256(raw).hexdigest() if raw is not None else None)
        self.record(event,sender,**detail)
        receiving=msg is not None
        data={'자료 구분':'송수신 데이터','시험':self.title,'회차':self.round,'메시지 번호':self.messages,
              '방향':'수신' if receiving else '송신 요청','발송 주체':sender,'토픽':topic,'정보':STREAMS[self.stream][0],
              '포장':'Base64 JSON' if encoded else 'JSON','업무 데이터':public_value if parse_ok else '자료를 해석하지 못했습니다.'}
        redacted=parse_ok and parsed!=public_value
        if encoded and parse_ok:
            data['전송 원문 (Base64)']=base64.b64encode(dump(public_value).encode()).decode() if redacted else raw.decode('ascii',errors='backslashreplace')
        elif not parse_ok:
            data['원문 보존']='해석할 수 없는 원문은 인증정보 노출을 피하기 위해 진단 기록에 보존했습니다.'
            data['수집 크기(바이트)']=len(raw) if raw is not None else 0
        if key is not None:
            try:data['메시지 키']=key.decode('utf8')
            except UnicodeError:data['메시지 키 (16진수)']=key.hex()
        if redacted:data['표시 안내']='인증값은 가렸습니다. 표시 자료와 수집 원문을 구분하여 보존합니다.'
        self.data(f'{self.round}/{self.wanted}회 · {STREAMS[self.stream][0]} '+('수신' if receiving else '송신 요청'),data,sender)
    def check_data(self,stream,parsed,provider):
        evidence=[];checks=[]
        try:checks=validate(stream,parsed,evidence)
        except Exception:
            if evidence:self.data(f'{self.round}/{self.wanted}회 · 데이터 기준 불일치',{'자료 구분':'데이터 검사','시험':self.title,'회차':self.round,'판정 기준':view.basis(stream),'검사 내역':evidence,'결과':'불일치'})
            raise
        self.record('데이터 검사' if provider else '송신 자료 검사','시험 시스템',stream=stream,checkedFields=checks,evidence=evidence)
        note='자료 형식만 확인 · 업무 필드 의미 미확인' if stream=='facility' else '아래에 제시한 항목의 자료형·명확한 범위를 확인했습니다.'
        known={'open':{'utctime','objectData','weatherData','tailLampIntensity','safetyMessage','systemStatus'},'platform':{'INTER_SERVER_STATUS','KAFKA_FCLTY_STATUS','DATAHUB_PLATFORM_STATUS'},'map':{'messageId','value'},'i2x':{'i2xID','i2xInterId','i2xConId','i2xConName','i2xLocation','SDateTime','i2xCnncSttus','iotCnncSttus','citsCnncSttus','i2xStrgTemp','i2xStrgHum','i2xDoorSttus','i2xFanSttus','i2xHeaterSttus'}}
        data={'자료 구분':'데이터 검사','시험':self.title,'회차':self.round,'판정 기준':view.basis(stream),'검사 내역':evidence,'결과':note,'확인 범위':'검사 내역에 없는 항목의 업무 의미는 이번 판정에 포함하지 않습니다.'}
        extras=sorted(set(parsed)-known.get(stream,set(parsed)))
        if extras:data['검사 범위 밖의 추가 항목']=extras
        self.data(f'{self.round}/{self.wanted}회 · '+('받은 자료' if provider else '보낼 자료')+'의 기준·실제값 확인',data)
        return checks
    def stage(self,c,stream,mode,baseline):
        save(self.control,dict(runId=self.id,case=self.case,testName=self.test,stream=stream,mode=mode,output=str(self.out.resolve()),baseline=baseline,
                              count=c['period_samples'] if mode=='period' else c['repetitions'],period=c['period_'+stream],phase='ready'))
        if c.get('development_peer_sync'):
            ready=self.work/'peer-ready.json';end=time.monotonic()+c['timeout_seconds']
            while time.monotonic()<end:
                self.check_stop()
                try:
                    v=json.loads(ready.read_text(encoding='utf8'))
                    if v.get('runId')==self.id and v.get('testName')==self.test:return
                except (OSError,ValueError):pass
                time.sleep(.05)
            raise TimeoutError('독립 개발 상대 준비 제한시간 초과')
    def item(self,c,stream,mode,provider,source):
        self.stream=stream;self.encoding=c['open_encoding']
        topic=c['topic_'+stream];timeout=c['timeout_seconds'];want=c['period_samples'] if mode=='period' else c['repetitions'];self.wanted=want
        client=consumer(c);prod=None
        try:
            partitions=metadata(client,topic,timeout)
            self.record('토픽 Metadata 조회','Kafka Broker',topic=topic,partitions=partitions,group=c['group_id'])
            baseline={p:client.get_watermark_offsets(TopicPartition(topic,p),timeout=timeout)[1] for p in partitions}
            before=offsets(client,topic,partitions,timeout)
            self.record('초기 저장 offset 조회','Kafka Broker',topic=topic,committed=before,runStartOffsets=baseline,policy=c['auto_offset_reset'])
            if provider:
                # Explicit run boundary prevents historical records from passing a new test.
                client.assign([TopicPartition(topic,p,baseline[p]) for p in partitions])
            else:prod=producer(c)
            self.stage(c,stream,mode,baseline)
            period=c['period_'+stream];last=None;due=time.monotonic();intervals=[]
            self.log(('대상이 제공하는 자료를 받아 기준과 비교합니다.' if provider else '준비한 자료를 보내고 대상의 소비 위치를 확인합니다.')+f' 총 {want}회 진행합니다.')
            if mode=='period':self.log(f'합의 주기 {period}초, 허용오차 ±{c["period_tolerance_seconds"]}초. 엑셀 기본값 {STREAMS[stream][2]}초. '+('기본 시간 조건입니다.' if period==STREAMS[stream][2] else '변경된 개발 시간 조건입니다.'))
            for n in range(want):
                self.round=n+1;self.check_stop()
                if provider:
                    deadline=time.monotonic()+timeout+(period if mode=='period' and n else 0)
                    msg=None
                    while time.monotonic()<deadline:
                        self.check_stop();msg=client.poll(.1)
                        if msg is None:continue
                        if msg.error():raise RuntimeError('Kafka 수신 오류: '+str(msg.error().code()))
                        break
                    if msg is None:raise TimeoutError('기대한 시험 대상 발행 자료가 제한시간 내 수신되지 않았습니다.')
                    observed=time.monotonic();self.message('업무 value 수신',source,msg=msg)
                    parsed=decode(msg.value(),stream,c['open_encoding']);checks=self.check_data(stream,parsed,True)
                    self.record('OffsetCommit 요청','통합교통관제시스템 (시험 Consumer)',topic=topic,partition=msg.partition(),nextOffset=msg.offset()+1)
                    stored=commit_checked(client,msg,timeout)
                    self.record('commit 후 저장 offset 재조회','Kafka Broker',topic=topic,partition=msg.partition(),expected=msg.offset()+1,actual=stored)
                else:
                    if mode=='period' and n:self.wait(max(0,due-time.monotonic()))
                    parsed=fixture(stream,c);checks=self.check_data(stream,parsed,False);raw=dump(parsed).encode('utf8')
                    if stream=='open' and c['open_encoding']=='base64-json':raw=base64.b64encode(raw)
                    delivered=[]
                    self.message('업무 value 발행 시도',source,raw=raw,topic=topic,partition=partitions[0])
                    observed=time.monotonic();prod.produce(topic,value=raw,partition=partitions[0],on_delivery=lambda e,m:delivered.append((e,m)))
                    end=time.monotonic()+timeout
                    while not delivered and time.monotonic()<end:self.check_stop();prod.poll(.05)
                    if not delivered or delivered[0][0]:raise RuntimeError('브로커 발행 완료 확인 실패')
                    msg=delivered[0][1];self.record('발행 저장 ACK','Kafka Broker',topic=topic,partition=msg.partition(),offset=msg.offset(),scope='브로커 저장. 대상 소비/내부 처리와 별도')
                    end=time.monotonic()+timeout;stored=before.get(msg.partition(),-1001)
                    while time.monotonic()<end:
                        self.check_stop();stored=offsets(client,topic,[msg.partition()],min(timeout,5))[msg.partition()]
                        if stored>=msg.offset()+1:break
                        time.sleep(.1)
                    self.record('대상 Group 저장 offset 관측','Kafka Broker',topic=topic,partition=msg.partition(),group=c['group_id'],expectedAtLeast=msg.offset()+1,actual=stored)
                    if stored<msg.offset()+1:raise TimeoutError('대상 Consumer의 저장 offset이 해당 자료 다음 위치까지 진전하지 않았습니다.')
                if mode=='period' and last is not None:
                    actual=observed-last;intervals.append(actual)
                    self.record('주기 관측','시험 시스템',expectedSeconds=period,actualSeconds=actual,toleranceSeconds=c['period_tolerance_seconds'])
                    if abs(actual-period)>c['period_tolerance_seconds']:raise ValueError('관측 주기가 합의한 허용범위를 벗어났습니다.')
                last=observed;due=observed+period
                self.completed+=1
            return intervals
        finally:client.close()
    def run(self):
        overall='SUCCESS';self.state('START');c=None
        try:
            c=parse_config(self.case,self.raw);design,provider,source,_=CASES[self.case]
            self.config=c
            self.log('선택한 Kafka 시험을 시작합니다. 상세 항목마다 목적·확인 기준과 실제 자료를 함께 기록합니다.')
            for key,stream,mode,title in c['selected']:
                self.test=key;self.title=title;self.round=0;self.completed=0;intervals=[];reason='';verdict='NOT_RUN'
                if overall=='SUCCESS':
                    self.state('START');self.data('시험 안내 · '+title,view.introduction(self.case,c,stream,mode,title))
                    try:intervals=self.item(c,stream,mode,provider,source);verdict='SUCCESS';reason='선택한 자동 관측 범위 통과. 내부 업무 처리 미관측.'
                    except Stopped as e:verdict='STOPPED';reason=str(e)
                    except Exception as e:verdict='FAIL';self.diagnostic(e);reason=view.failure(e)
                    if verdict!='SUCCESS':overall=verdict
                else:reason='이전 항목 실패 또는 중지로 미실행'
                row=dict(test=key,title=title,stream=stream,mode=mode,verdict=verdict,completed=self.completed,requested=c['period_samples'] if mode=='period' else c['repetitions'],intervals=intervals,detail=reason,defaultTiming=c['period_'+stream]==STREAMS[stream][2] if mode=='period' else None)
                self.rows.append(row);self.data('시험 결과 · '+view.VERDICTS[verdict],{'자료 구분':'시험 결과','시험':title,'판정':view.VERDICTS[verdict],'계획 횟수':row['requestedExchanges'] if 'requestedExchanges' in row else row['requested'],'완료 횟수':self.completed,'판정 설명':reason,'확인 범위':view.limits(stream,provider)})
                if verdict!='NOT_RUN':self.state(verdict)
        except Stopped as e:overall='STOPPED';self.log(str(e))
        except Exception as e:overall='FAIL';self.diagnostic(e);self.log(view.failure(e))
        finally:
            self.test='MainScenario'
            result=dict(presentationVersion=2,runId=self.id,case=self.case,verdict=overall,items=self.rows,messages=self.messages,observations=self.seq,assessmentScope='ENGINE_OBSERVABLE',notObserved=['대상 내부 업무 처리','원시 Kafka 내부 제어 패킷','Broker 제품 전체 적합성'],unselected=[x[0] for x in items(self.case) if not c or x[0] not in [i[0] for i in c['selected']]])
            save(self.out/'result.json',result);save(self.control,dict(runId=self.id,case=self.case,phase='finished',verdict=overall))
            summary={'자료 구분':'전체 결과','판정':view.VERDICTS[overall],'선택 항목 결과':[{'시험':r['title'],'판정':view.VERDICTS[r['verdict']],'완료':str(r['completed'])+' / '+str(r['requested'])} for r in self.rows],'업무 메시지 수':self.messages,'미선택 항목':[title for key,_,_,title in items(self.case) if key in result['unselected']],'결과 해석':'선택한 관측 범위의 결과입니다. 대상 내부 처리와 전체 시스템 적합성의 확인으로 확대하지 않습니다.'}
            self.data('전체 시험 '+view.VERDICTS[overall],summary)
            self.public.flush()
            view.write_report(self.work/'시험결과.html',summary,(json.loads(line) for line in (self.out/'user-events.jsonl').open(encoding='utf8')))
            self.state(overall);self.state('FINISH');self.events.close();self.records.close();self.public.close()
        return overall

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--case',required=True,choices=CASES);p.add_argument('--config',required=True);p.add_argument('--output',required=True);p.add_argument('--work');a=p.parse_args()
    raw=json.loads(Path(a.config).read_text(encoding='utf-8-sig'));r=Runner(a.case,raw,a.output,a.work);r.run()
