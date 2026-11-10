"""실제 엔진·상대를 사용하는 로컬 웹 연결 계약 검증. 설치된 Chrome 검증은 별도."""
import argparse,asyncio,base64,ctypes,json,os,subprocess,time,urllib.request,urllib.error
from pathlib import Path
import websockets

class Hub:
 def __init__(self,case,occupied=False):self.case=case;self.occupied=occupied;self.agent=None;self.controller=None;self.commands=[];self.messages=[];self.events=[]
 async def handle(self,ws):
  role=ws.request.path.split('/')[3]
  if role=='agent':self.agent=ws
  else:self.controller=ws
  try:
   async for raw in ws:
    msg=json.loads(raw);self.messages.append([role,msg]);method=msg.get('method')
    if method=='DESCRIBE':
     await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=({'currConnList':[{'clientType':'Agent'}] if self.occupied else []} if role=='controller' else None)))))
     if role=='agent':
      descriptor=base64.b64encode(json.dumps(dict(category='ITSK-00143-KAFKA-V1',testScenario=self.case)).encode()).decode();await ws.send(json.dumps(dict(method='INITIALIZE',seq=2,testScenario=descriptor)))
    elif role=='controller' and method in ['SETUP','START','STOP']:
     self.commands.append(method);await self.agent.send(json.dumps(dict(method=method,seq=msg['seq'],data=msg.get('data'))))
    elif role=='agent' and method in ['UI_CONFIGURE','NOTIFY']:
     self.events.append(msg);await self.controller.send(json.dumps(msg));await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
    elif role=='agent' and isinstance(msg.get('result'),dict) and msg.get('seq',0)>=700000:await self.controller.send(json.dumps(msg))
  except websockets.ConnectionClosed:pass

class Web:
 def __init__(self,bundle,channel,hub,manual=False):self.bundle=bundle;self.ext=(bundle/'extension-id.txt').read_text().strip();self.channel=str(channel);self.hub=hub;self.token='';self.client='local-bridge-check';self.seq=900000;self.last='';self.stopped=False;self.values={};self.actions=[];self.manual=manual
 async def call(self,kind,data=None,origin=None,extension=None):
  body=json.dumps(dict(kind=kind,channel=self.channel,clientId=self.client,token=self.token,data=data or {})).encode()
  def do():
   r=urllib.request.Request('http://127.0.0.1:43763/bridge',data=body,headers={'Content-Type':'application/json','X-Rest-Extension':extension or self.ext,'Origin':origin or 'chrome-extension://'+self.ext})
   return json.loads(urllib.request.urlopen(r,timeout=30).read())
  return await asyncio.to_thread(do)
 async def send(self,kind):
  self.seq+=1;self.actions.append(kind);request=dict(method=kind,seq=self.seq)
  if kind=='SETUP':request['testConfiguration']=json.dumps(self.values,ensure_ascii=False)
  else:request['data']=''
  await self.hub.agent.send(json.dumps(request,ensure_ascii=False))
 async def setup(self,values):
  self.values={k:v if isinstance(v,bool) else str(v) for k,v in values.items()};await self.call('before-setup',dict(values=self.values));await self.send('SETUP');await self.call('after-setup',dict(values=self.values))
 async def start(self):await self.call('before-start',dict(values=self.values));await self.send('START');await self.call('after-start')
 async def loop(self):
  while not self.stopped:
   try:
    if not self.token:
     hello=await self.call('hello')
     if not hello.get('linked'):await asyncio.sleep(.1);continue
     self.token=hello['token']
    result=await self.call('poll');cmd=result.get('command')
    if cmd and cmd['id']!=self.last:
     self.last=cmd['id'];error=''
     try:
      if cmd['kind']=='apply':await self.setup(cmd['data']['values'])
      elif cmd['kind']=='start':await self.start()
      elif cmd['kind']=='stop':await self.call('before-stop');await self.send('STOP');await self.call('after-stop')
     except Exception as e:error=str(e)
     await self.call('result',dict(id=cmd['id'],error=error))
     if self.manual and cmd['kind']=='apply' and not error:
      await asyncio.sleep(.5);await self.call('web-dirty');changed=dict(self.values,repetitions='12')
      if self.manual=='evidence':
       directory=next(p.parent for p in (self.bundle/'runs').glob('*/session.json') if json.loads(p.read_text())['agentUrl'].endswith('/'+self.channel+'/'));changed['evidence_directory']=str(directory/'sut')
      await self.setup(changed);await self.start()
   except (OSError,urllib.error.URLError):pass
   await asyncio.sleep(.05)

async def execute(bundle,scenario,selected,channel,*,custom=None,staged=False,manual=False,prepare=False,stop=None,wrong_case=None,occupied=False,expected='SUCCESS'):
 hub=Hub(wrong_case or scenario['case'],occupied);web=Web(bundle,channel,hub,manual);before=set((bundle/'runs').glob('*')) if (bundle/'runs').exists() else set()
 async with websockets.serve(hub.handle,'127.0.0.1',0,max_size=33554432,compression=None,ping_interval=None) as server:
  port=server.sockets[0].getsockname()[1];args=[str(bundle/'시작하기.exe'),'--run-local',str(bundle),str(scenario['id']),selected,f'ws://127.0.0.1:{port}/ws/test/agent/{channel}/']
  if staged:args+=['--staged-check']
  if manual:args+=['--web-wait']
  if prepare:args+=['--prepare-only']
  if stop:args+=['--stop-after-ms',str(stop)]
  if custom:
   config=bundle/f'check-{channel}.json';config.write_text(json.dumps(custom,ensure_ascii=False),encoding='utf8');args+=['--config',str(config)]
  task=asyncio.create_task(web.loop());proc=await asyncio.create_subprocess_exec(*args,creationflags=subprocess.CREATE_NO_WINDOW)
  try:code=await asyncio.wait_for(proc.wait(),150)
  finally:
   if proc.returncode is None:proc.kill();await proc.wait()
   web.stopped=True;await task
 runs=[p for p in set((bundle/'runs').glob('*'))-before if json.loads((p/'session.json').read_text())['agentUrl'].endswith('/'+str(channel)+'/')];assert len(runs)==1,(scenario['id'],code,runs)
 run=runs[0];outcome=json.loads((run/'easy-outcome.json').read_text(encoding='utf8'));assert outcome['Verdict']==expected,(outcome,(run/'easy-error.txt').read_text(encoding='utf-8-sig') if (run/'easy-error.txt').exists() else '')
 assert not hub.commands or all(x=='STOP' for x in hub.commands),'SETUP/START bypassed real web flow'
 if expected=='SUCCESS':
  native=outcome['Report'];wanted=[x['key'] for x in scenario['tests']] if selected=='all' else selected.split(',')
  assert [x['test'] for x in native['items']]==['test_'+k for k in wanted]
  receipt=json.loads((run/'kafka-selection.json').read_text(encoding='utf8'));assert receipt['valid'] and receipt['case']==scenario['case']
  assert json.loads((run/'sut-config.json').read_text(encoding='utf8'))==receipt['effectiveConfiguration']
  if staged:assert receipt['effectiveConfiguration']['repetitions']==11 and web.actions[:3]==['SETUP','SETUP','START']
  if manual:assert receipt['effectiveConfiguration']['repetitions']==12 and web.actions[:3]==['SETUP','SETUP','START']
  rows=[json.loads(l) for f in (run/'kafka-results').glob('*/records.jsonl') for l in f.read_text(encoding='utf8').splitlines()]
  peer=[json.loads(l) for l in (run/'peer-records.jsonl').read_text(encoding='utf8').splitlines()]
  wire=[x for x in rows if x['event'] in ['업무 value 수신','업무 value 발행 시도']];other=[x for x in peer if x['event'] in ['published','received']]
  assert len(wire)==len(other)==native['messages']
  for a,b in zip(wire,other):assert [a[k] for k in ['runId','testName','round','topic','valueBase64','sha256']]==[b[k] for k in ['runId','testName','round','topic','valueBase64','sha256']]
 if expected in ['SUCCESS','STOPPED']:
  assert sum(e.get('data',{}).get('testName')=='MainScenario' and e.get('data',{}).get('state')=='FINISH' for e in hub.events)==1
  states=[e['data']['state'] for e in hub.events if e.get('level')=='state' and 'state' in e.get('data',{})];assert 'COMPLETE' not in states
 if prepare:assert not (run/'sut-process.json').exists() and not (run/'broker-process.json').exists() and not (run/'kafka-results').exists()
 for file in run.glob('*-process.json'):
  pid=json.loads(file.read_text())['pid'];h=ctypes.windll.kernel32.OpenProcess(0x1000,False,pid)
  if h:
   value=ctypes.c_ulong();ctypes.windll.kernel32.GetExitCodeProcess(h,ctypes.byref(value));ctypes.windll.kernel32.CloseHandle(h);assert value.value!=259,(pid,'still running')
 summary=dict(scenario=scenario['id'],selected=selected,expected=expected,passed=True,run=str(run),actions=web.actions,launcherCommands=hub.commands,messages=(outcome.get('Report') or {}).get('messages',0))
 (run/'bridge-verification.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8');print(json.dumps(summary,ensure_ascii=False),flush=True);return summary

async def main():
 p=argparse.ArgumentParser();p.add_argument('bundle',type=Path);p.add_argument('--suite',choices=['smoke','all','boundaries'],default='smoke');a=p.parse_args();bundle=a.bundle.resolve();catalog=json.loads((bundle/'scenarios.json').read_text(encoding='utf8'));scenarios=catalog['scenarios'];by_id={s['id']:s for s in scenarios};channel=int(time.time());results=[]
 fast={'period_open':3,'period_platform':3,'period_facility':3,'period_map':3,'period_i2x':3,'period_tolerance_seconds':1}
 jobs=[(76,'open_normal',dict(staged=True)),(77,'open_normal',dict(manual=True))]
 if a.suite=='all':jobs=[(s['id'],'all',dict(custom={k:v for k,v in fast.items() if k in s['tester']})) for s in scenarios]
 if a.suite=='boundaries':jobs=[(78,'i2x_normal',dict(prepare=True,expected='NOT_RUN')),(79,'map_period',dict(stop=12000,expected='STOPPED')),(76,'open_normal',dict(wrong_case='ut2platform_kafka_v1',expected='ERROR')),(76,'open_normal',dict(occupied=True,expected='ERROR'))]
 try:
  for i,(sid,selected,options) in enumerate(jobs):results.append(await execute(bundle,by_id[sid],selected,channel+i,**options))
 finally:(bundle/('bridge-'+a.suite+'-results.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
if __name__=='__main__':asyncio.run(main())

