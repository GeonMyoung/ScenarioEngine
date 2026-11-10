"""Five-kind TIM coverage by furtherInfoID and ITIS. Record the content format."""
import hashlib,json,re,time
from failures import Failure
from transport import Stopped
from readiness import write as write_readiness

TYPES = {
    'limit_speed': ('통행지시 제한속도 변경',0x0c01,7443),
    'maintain_speed': ('통행지시 속도 유지',0x0c01,7444),
    'left_lane': ('통행지시 좌측 차로 변경',0x0c02,7428),
    'right_lane': ('통행지시 우측 차로 변경',0x0c02,7427),
    'shoulder': ('통행지시 갓길 주행',0x0c02,7436),
}
CONTENT_REVIEW='RECORD_ONLY'
CONTENT_NOTE='TIM content 형식은 수신 기록에 남기며 합불 기준에서 제외합니다.'

def invalid(field,actual,expected):
    raise Failure('TIM_PROFILE_MISMATCH',f'TIM {field}: 기대 {expected} / 실제 {actual}',
                  criterion=expected,observed=dict(field=field,actual=actual),checks=['TIM 통행지시 5종 프로파일과 원문 대조'])

def _inspect(view):
    d=view['decoded'];frames=d.get('dataFrames',[])
    if len(frames)!=1:invalid('dataFrames 개수',len(frames),'1')
    f=frames[0];content=f.get('content') or {}
    codes=[]
    def visit(node):
        if isinstance(node,dict):
            for k,v in node.items():
                if k=='itis':codes.append(v)
                else:visit(v)
        elif isinstance(node,list):
            for v in node:visit(v)
    visit(content)
    info=(f.get('msgId') or {}).get('furtherInfoID')
    kind=next((k for k,(_,i,c) in TYPES.items() if info==i and codes==[c]),None)
    if kind is None:
        if any(code in [v[2] for v in TYPES.values()] for code in codes):invalid('furtherInfoID / ITIS',(info,codes),'0C01:7443·7444 / 0C02:7428·7427·7436')
        return None
    p=view.get('tim_profile');regional=view.get('tim_regional')
    if not isinstance(p,dict) or not isinstance(regional,dict):
        raise Failure('TIM_METADATA_UNAVAILABLE','TIM 필수값·국내 확장 추출 기능을 확인하세요.',category='시험 도구 확인 필요')
    if not p.get('packetIdPresent') or len(p.get('packetIdHex',''))!=18:invalid('packetID',p.get('packetIdHex'),'9바이트 필수')
    if not p.get('startYearPresent'):invalid('startYear',None,'필수')
    if p.get('frameCount')!=1 or p.get('regionCount')!=1:invalid('프레임/구간 개수',(p.get('frameCount'),p.get('regionCount')),'각 1개')
    if f.get('frameType')!='roadSignage':invalid('frameType',f.get('frameType'),'roadSignage')
    for key in ['notUsed','notUsed1','notUsed2','notUsed3']:
        if f.get(key)!=0:invalid(key,f.get(key),'0')
    if regional.get('summaryOmitted'):
        raise Failure('TIM_METADATA_INCOMPLETE','TIM 국내 확장 자료 추출이 일부 누락됐습니다.',category='시험 도구 확인 필요')
    values=regional.get('values',[])
    targets=[v['value'] for v in values if v.get('kind')=='path' and v.get('type')==2 and isinstance(v.get('value'),str) and v['value']]
    if not targets:invalid('대상 LaneBelt ID',targets,'GeographicalPath-KOR(regionId=4)의 linkID')
    text=[v for v in values if v.get('kind')=='text']
    if any(v.get('frameIndex')!=0 for v in text):invalid('dataFrameIndex',[v.get('frameIndex') for v in text],'0 (단일 프레임)')
    return dict(kind=kind,title=TYPES[kind][0],furtherInfoID=f'{info:04X}',itis=codes[0],
                packet_id_hex=p['packetIdHex'],content_choice=list(content),content_review=CONTENT_REVIEW,
                target_ids=targets,texts=[v['value'] for v in text],
                speeds=[int(m[1]) for v in text if (m:=re.search(r'\bSPEED\s+(\d+)\b',v.get('value','')))],
                startYear=f['startYear'],startTime=f['startTime'],durationTime=f['durationTime'],priority=f['priority'])

def identify(view):
    frames=(view.get('decoded') or {}).get('dataFrames',[])
    if not frames:return None
    frame=frames[0];codes=[]
    def visit(node):
        if isinstance(node,dict):
            for k,v in node.items():
                if k=='itis':codes.append(v)
                else:visit(v)
        elif isinstance(node,list):
            for v in node:visit(v)
    visit(frame.get('content',{}));info=(frame.get('msgId') or {}).get('furtherInfoID')
    kind=next((k for k,(_,i,c) in TYPES.items() if codes==[c]),None)
    if kind and info!=TYPES[kind][1]:
        try:invalid('종류 식별값',(info,codes),'해당 ITIS 코드와 일치하는 furtherInfoID')
        except Failure as e:e.tim_kind=kind;raise
    return kind


def inspect(view):
    kind=identify(view)
    try:return _inspect(view)
    except Exception as e:e.tim_kind=kind;raise


def collect(runner,client,selected,finish=None):
    finish=finish or (lambda *a:None)
    c=runner.c;target=c['tim_per_type'];topic=c['topic_tim'];folder=runner.events.path
    keys=[item[2] for item in selected]
    state={k:dict(title=TYPES[k][0],received=0,validated=0,duplicates=0,result='MISSING') for k in keys}
    summary=dict(required_kinds=len(state),target_per_kind=target,received=0,duplicates=0,ignored=0,types=state,
                 missing=list(keys),content_review=CONTENT_REVIEW,notice=CONTENT_NOTE,complete=False)
    runner.tim_summary=summary;seen=set();subscribed=False;ready=folder/'ready.json'
    terminal=('CONFIRMED','FAIL','STOPPED')
    def save():
        summary['missing']=[k for k,v in state.items() if v.get('missing') or v['result'] in ('MISSING','PARTIAL')]
        summary['complete']=all(v['result']=='CONFIRMED' for v in state.values())
        runner.completed=sum(v['validated'] for v in state.values())
        (folder/'tim-summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
    def progress():
        save();return ' / '.join(v['title']+f' {v["validated"]}/{target}건 (중복 {v["duplicates"]})' for v in state.values())
    def end(kind,status,error=None):
        entry=state[kind]
        if entry['result'] in terminal:return
        entry['result']=status
        if error:entry['reason']=str(error)
        finish(kind,'SUCCESS' if status=='CONFIRMED' else status,entry['validated'],error)
    try:
        client.subscribe({topic:c['qos']},c['timeout_seconds']);subscribed=True
        write_readiness(ready,dict(message='tim',active=True,generation=str(time.monotonic_ns()),expected=len(state)*target,selected_kinds=keys))
        runner.events.info(f'선택한 TIM {len(state)}종을 각각 {target}건 확인합니다. '+CONTENT_NOTE,summary,test='MainScenario')
        with (folder/'tim-messages.jsonl').open('w',encoding='utf-8') as journal:
            while any(v['result'] not in terminal for v in state.values()):
                client.check()
                if runner.stop():raise Stopped('사용자가 시험을 중지했습니다.')
                m=client.receive(.05,observe=False)
                if not m:continue
                runner.number_message(m)
                client.record_message(m);summary['received']+=1;runner.round=summary['received']
                if m['retain']:
                    runner.received('tim',m,'이전 보관 메시지 · 집계 제외')
                    continue
                from container import decode
                from catalog import MESSAGES
                view=None
                try:
                    if m['topic']!=topic:invalid('수신 토픽',m['topic'],topic)
                    envelope=decode(m['payload'],c['byte_order'])
                    other=next((k for k in ('spat','tlsm') if MESSAGES[k]['fid']==envelope.fid and MESSAGES[k]['psid']==envelope.psid),None)
                    if other and c.get('topic_'+other)==topic:
                        runner.received(other,m,'공유 토픽의 다른 메시지 · 집계 제외')
                        continue
                    _,view=runner.decoded('tim',m['payload'])
                except Exception as error:
                    error.sample=m['sequence']
                    runner.received('tim',m,'정합성 실패',view=view,error=error)
                    raise
                counted=None
                try:
                    kind=identify(view)
                    if kind not in state:
                        summary['ignored']+=1
                        runner.received('tim',m,'미선택 종류 · 집계 제외',view=view)
                        continue
                    state[kind]['received']+=1;counted=kind
                    detail=inspect(view)
                except Exception as error:
                    kind=getattr(error,'tim_kind',None)
                    if kind and kind not in state:
                        summary['ignored']+=1
                        runner.received('tim',m,'미선택 종류 · 집계 제외',view=view)
                        continue
                    error.sample=m['sequence']
                    runner.received('tim',m,'정합성 실패',view=view,error=error,
                                    test='test_tim_'+kind if kind in state else None)
                    if kind in state:
                        if counted!=kind:state[kind]['received']+=1
                        end(kind,'FAIL',error);save();continue
                    raise
                entry=state[kind];fingerprint=(kind,hashlib.sha256(envelope.payload).hexdigest())
                duplicate=fingerprint in seen or entry['result'] in terminal
                if duplicate:entry['duplicates']+=1;summary['duplicates']+=1
                else:seen.add(fingerprint);entry['validated']+=1
                entry['last_verified']=detail
                if entry['result'] not in terminal:entry['result']='PARTIAL'
                record=dict(sequence=m['sequence'],testName='test_tim_'+kind,topic=topic,payload_hex=m['payload'].hex(),duplicate=duplicate,**detail,**view)
                journal.write(json.dumps(record,ensure_ascii=False)+'\n');journal.flush()
                runner.received('tim',m,'중복 수신 · 집계 제외' if duplicate else '정합성 확인',
                                view=dict(**detail,**view),test='test_tim_'+kind,
                                progress=dict(validated=entry['validated'],expected=target,duplicates=entry['duplicates']))
                if entry['result'] not in terminal and entry['validated']>=target:end(kind,'CONFIRMED')
                save()
        if not summary['complete']:
            raise Failure('TIM_SELECTED_FAILED','선택한 TIM 중 검증하지 못한 항목이 있습니다.',category='관측 조건 미충족',observed=summary)
        runner.events.info('선택한 TIM 종류를 모두 확인했습니다.',summary,test='MainScenario')
    except Exception as error:
        status='STOPPED' if isinstance(error,Stopped) else 'FAIL'
        for kind,entry in state.items():
            if entry['result'] not in terminal and entry['validated']<target:entry['missing']=True
            end(kind,status,error)
        save();raise
    finally:
        try:
            if subscribed:client.unsubscribe(topic,c['timeout_seconds'])
        finally:
            save();write_readiness(ready,dict(message='tim',active=False))
            runner.events.info('TIM 확인 결과: '+progress(),summary,test='MainScenario')
    return None
