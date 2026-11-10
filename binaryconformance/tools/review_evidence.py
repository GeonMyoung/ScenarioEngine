"""Binary 검증용 양측 실제 프레임·처리 기록 대조. 원문은 수정하지 않는다."""
import hashlib,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'emulator'))
from signal_codec import Assembler

def same(a,b):
 if isinstance(a,bool) or isinstance(b,bool):return type(a) is type(b) and a==b
 if isinstance(a,(int,float)) and isinstance(b,(int,float)):return a==b
 if type(a) is not type(b):return False
 if isinstance(a,dict):return a.keys()==b.keys() and all(same(a[k],b[k]) for k in a)
 if isinstance(a,list):return len(a)==len(b) and all(same(x,y) for x,y in zip(a,b))
 return a==b

def require(condition,message):
 if not condition:raise AssertionError(message)
def read_events(p):return [json.loads(x) for x in p.read_text(encoding='utf8').splitlines() if x]
def review(report_path,peer_path):
 report_path=Path(report_path);peer_path=Path(peer_path);report=json.loads(report_path.read_text(encoding='utf8'));events=read_events(report_path.parent/'events.jsonl');peer=read_events(peer_path/'events.jsonl');run=report['runId']
 binding=json.loads((peer_path/'run-binding.json').read_text(encoding='utf8'));require(binding['runId']==run and binding['configSha256']==report['configSha256'],'다른 실행의 상대 기록입니다.')
 require(report['automaticVerdict']=='SUCCESS' and report['assessmentScope']=='ENGINE_OBSERVABLE','성공한 자동 관측 결과가 아닙니다.')
 require(all(e['runId']==run for e in events+peer),'다른 실행의 이벤트가 섞였습니다.');require(not any(e['event']=='error' for e in peer),'상대 처리 오류가 있습니다.')
 native=[e for e in events if e['event']=='message'];other=[e for e in peer if e['event']=='message'];require(len(native)==len(other)==report['messages'],'송수신 메시지 수가 다릅니다.')
 for item in report['items']:
  key=item['test'];require(item['verdict']=='SUCCESS' and item['completedExchanges']==item['requestedExchanges'],'실행 횟수 또는 판정이 다릅니다.')
  single_session=report.get('sessionPolicy')=='single_connection_per_item'
  if single_session:
   own_sessions=[e for e in events if e.get('test')==key and e['event']=='connected'];peer_sessions=[e for e in peer if e.get('test')==key and e['event']=='connected']
   require(len(own_sessions)==len(peer_sessions)==item['connections']==1,'한 항목에서 한 번만 접속해야 합니다.')
   closed=[e for e in events if e.get('test')==key and e['event']=='session_closed'];peer_closed=[e for e in peer if e.get('test')==key and e['event']=='session_closed']
   require(item['sessionClosed'] and len(closed)==len(peer_closed)==1,'교환 후 양측 세션 정리가 확인되지 않았습니다.')
   for stream in (events,peer):
    rounds=[e['iteration'] for e in stream if e.get('test')==key and e['event']=='exchange_complete']
    require(rounds==list(range(1,item['requestedExchanges']+1)),'한 세션의 반복 교환 회차가 누락되거나 중복됐습니다.')
  own=[e for e in native if e['test']==key];target=[e for e in other if e['test']==key];require(len(own)==len(target)==item['messageCount'],'항목별 메시지 수가 다릅니다.')
  for direction,opposite in [('send','receive'),('receive','send')]:
   a=[e for e in own if e['direction']==direction];b=[e for e in target if e['direction']==opposite]
   require(len(a)==len(b),'방향별 프레임 수가 다릅니다.')
   for x,y in zip(a,b):
    require(not x['partial'] and x['iteration']==y['iteration'] and x['hex']==y['hex'],'상대 송수신의 원문·회차가 다릅니다.')
    require(x['sha256']==y['sha256']==hashlib.sha256(bytes.fromhex(x['hex'])).hexdigest(),'원문 해시가 다릅니다.')
  if report['sutRole']=='receiver':
   processed=[e for e in peer if e['event']=='processed' and e['test']==key];expected=item['requestedExchanges']*(2 if item['mode']=='change' else 1) if item['mode']!='heartbeat' else 1
   if single_session and item['mode']=='change':expected=item['requestedExchanges']+1
   if single_session and item['mode']=='bad_sequence':expected=item['requestedExchanges']*2
   require(len(processed)==expected,'대상의 수신·분석 기록이 누락됐습니다.')
   if single_session and item['mode']=='bad_sequence':
    require([e['accepted'] for e in processed]==[False,True]*item['requestedExchanges'],'순서번호 오류 거부·정상 끝 프레임 수용 기록이 다릅니다.')
   else:require(all(e['accepted'] is (not item['mode'].startswith('bad_')) for e in processed),'대상 수용·거부 결과가 다릅니다.')
   stored=json.loads((peer_path/'processed.json').read_text(encoding='utf8'));subset=[e for e in stored if e['test']==key]
   require(same([{k:e[k] for k in ['runId','test','iteration','message','accepted','records']} for e in processed],subset),'상대 처리·저장 값이 다릅니다.')
   cfg=json.loads((report_path.parent/'config.json').read_text(encoding='utf8'));expected_records=[];assembler=None
   for e in events:
    if e.get('test')!=key:continue
    if e['event']=='connected':assembler=Assembler(int(cfg.get('first_sequence',0)))
    if e['event']!='message' or e['direction']!='send':continue
    raw=bytes.fromhex(e['hex']);accepted=True
    try:rows=assembler.accept(raw,cfg)
    except ValueError:accepted=False;rows=[]
    if rows is None or item['mode']=='heartbeat' and rows==[] and e['iteration']>0:continue
    expected_records.append(dict(runId=run,test=key,iteration=e['iteration'],message=raw[0],accepted=accepted,records=rows))
   require(same(expected_records,subset),'실제 송신 프레임과 대상의 해석·저장 값이 다릅니다.')
  else:
   supplied=[e for e in peer if e['event']=='provided' and e['test']==key];decoded=[e for e in events if e['event']=='information' and e['test']==key]
   require(same([[e['iteration'],e['message'],e['records']] for e in supplied],[[e['iteration'],e['message'],e['records']] for e in decoded]),'대상의 준비정보와 수신·해석 결과가 다릅니다.')
 return dict(runId=run,result='PASS',items=len(report['items']),exchanges=report['completedExchanges'],messages=report['messages'])
