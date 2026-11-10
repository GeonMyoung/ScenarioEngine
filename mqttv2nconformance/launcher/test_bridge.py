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
      descriptor=base64.b64encode(json.dumps(dict(category='ITSK-00143-MQTT-V1',testScenario=self.case)).encode()).decode();await ws.send(json.dumps(dict(method='INITIALIZE',seq=2,testScenario=descriptor)))
    elif role=='controller' and method in ['SETUP','START','STOP']:
     self.commands.append(method);await self.agent.send(json.dumps(dict(method=method,seq=msg['seq'],data=msg.get('data'))))
    elif role=='agent' and method in ['UI_CONFIGURE','NOTIFY']:
     self.events.append(msg);await self.controller.send(json.dumps(msg));await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
    elif role=='agent' and isinstance(msg.get('result'),dict) and msg.get('seq',0)>=700000:await self.controller.send(json.dumps(msg))
  except websockets.ConnectionClosed:pass

class Web:
 def __init__(self,bundle,channel,hub,manual=False):self.bundle=bundle;self.ext=(bundle/'extension-id.txt').read_text().strip();self.channel=str(channel);self.hub=hub;self.token='';self.client='local-bridge-check';self.seq=900000;self.last='';self.stopped=False;self.values={};self.actions=[];self.manual=manual;self.port=43763
 async def call(self,kind,data=None,origin=None,extension=None):
  for session in (self.bundle/'runs').glob('*/session.json'):
   if json.loads(session.read_text(encoding='utf-8'))['agentUrl'].endswith('/'+self.channel+'/'):
    bridge=session.with_name('web-bridge.json')
    if bridge.exists():self.port=json.loads(bridge.read_text(encoding='utf-8'))['port']
  body=json.dumps(dict(kind=kind,channel=self.channel,clientId=self.client,token=self.token,data=data or {})).encode()
  def do():
   r=urllib.request.Request('http://127.0.0.1:'+str(self.port)+'/bridge',data=body,headers={'Content-Type':'application/json','X-Rest-Extension':extension or self.ext,'Origin':origin or 'chrome-extension://'+self.ext})
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

async def execute(bundle,scenario,selected,channel,*,staged=False,prepare=False,stop=None,manual=False,occupied_port=False):
 expected='NOT_RUN' if prepare else 'STOPPED' if stop else 'SUCCESS'
 hub=Hub(scenario['case']);web=Web(bundle,channel,hub,manual)
 custom=dict(host='127.0.0.1',port=45000+scenario['id'],repetitions=100 if stop else 2,publish_interval_seconds=.05)
 if scenario.get('publishOnly'):custom.pop('publish_interval_seconds')
 for field in scenario['fields']:
  if field['name'].startswith('topic_'):custom[field['name']]='local/check/'+str(channel)+'/'+field['name']
 blocker=None
 if occupied_port:
  import socket
  blocker=socket.socket();blocker.bind(('127.0.0.1',custom['port']));blocker.listen()
 before=set((bundle/'runs').glob('*')) if (bundle/'runs').exists() else set()
 async with websockets.serve(hub.handle,'127.0.0.1',0,max_size=33554432,compression=None,ping_interval=None) as server:
  config=bundle/f'check-{channel}.json';config.write_text(json.dumps(custom),encoding='utf-8')
  args=[str(bundle/'시작하기.exe'),'--run-local',str(bundle),str(scenario['id']),selected,f'ws://127.0.0.1:{server.sockets[0].getsockname()[1]}/ws/test/agent/{channel}/','--config',str(config)]
  if staged:args+=['--staged-check']
  if prepare:args+=['--prepare-only']
  if manual:args+=['--web-wait']
  if stop:args+=['--stop-after-ms',str(stop)]
  task=asyncio.create_task(web.loop());proc=await asyncio.create_subprocess_exec(*args,creationflags=subprocess.CREATE_NO_WINDOW)
  try:code=await asyncio.wait_for(proc.wait(),90)
  finally:
   if proc.returncode is None:proc.kill();await proc.wait()
   web.stopped=True;await task
   if blocker:blocker.close()
 runs=[p for p in set((bundle/'runs').glob('*'))-before if (p/'session.json').exists() and json.loads((p/'session.json').read_text(encoding='utf-8'))['agentUrl'].endswith('/'+str(channel)+'/')]
 assert len(runs)==1,(scenario['id'],code,runs)
 run=runs[0];outcome=json.loads((run/'easy-outcome.json').read_text(encoding='utf-8'))
 assert outcome['Verdict']==expected,(outcome,(run/'easy-error.txt').read_text(encoding='utf-8-sig') if (run/'easy-error.txt').exists() else '')
 assert not hub.commands or all(x=='STOP' for x in hub.commands),'SETUP/START bypassed web bridge'
 receipt=json.loads((run/'mqttv2n-selection.json').read_text(encoding='utf-8'))
 assert receipt['valid'] and receipt['case']==scenario['case']
 assert json.loads((run/'sut-config.json').read_text(encoding='utf-8'))==receipt['effectiveConfiguration']
 if staged:assert receipt['testIdx']==2 and web.actions[:3]==['SETUP','SETUP','START']
 if manual:assert receipt['effectiveConfiguration']['repetitions']==12 and web.actions[:3]==['SETUP','SETUP','START']
 if occupied_port:assert receipt['effectiveConfiguration']['port']!=custom['port']
 if prepare:assert not (run/'sut-process.json').exists() and not (run/'broker-process.json').exists() and not (run/'mqttv2n-results').exists()
 else:
  main=[e['data']['state'] for e in hub.events if e.get('level')=='state' and e.get('data',{}).get('testName')=='MainScenario']
  assert main==['START',expected,'FINISH'],main
  assert (run/'시험결과.html').is_file()
  assert (run/'broker-ready.json').is_file()
  if scenario.get('publishOnly'):assert not (run/'sut-process.json').exists()
  else:assert (run/'peer.ready').is_file()
  if expected=='SUCCESS':assert all(t['result']=='SUCCESS' for t in outcome['Report']['tests'])
 for f in run.glob('*-process.json'):
  pid=json.loads(f.read_text(encoding='utf-8'))['pid'];handle=ctypes.windll.kernel32.OpenProcess(0x1000,False,pid)
  if handle:
   value=ctypes.c_ulong();ctypes.windll.kernel32.GetExitCodeProcess(handle,ctypes.byref(value));ctypes.windll.kernel32.CloseHandle(handle);assert value.value!=259,(pid,'still running')
 result=dict(scenario=scenario['id'],expected=expected,passed=True,run=str(run),webActions=web.actions,directControllerCommands=hub.commands,portAdjusted=occupied_port)
 (run/'bridge-verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(result,ensure_ascii=False),flush=True);return result

async def main():
 p=argparse.ArgumentParser();p.add_argument('bundle',type=Path);p.add_argument('--suite',choices=['smoke','boundaries'],default='smoke');a=p.parse_args();bundle=a.bundle.resolve()
 catalog=json.loads((bundle/'scenarios.json').read_text(encoding='utf-8'));byid={s['id']:s for s in catalog['scenarios']};channel=int(time.time());results=[]
 jobs=[(81,'bsm_normal',dict(staged=True,occupied_port=True))] if a.suite=='smoke' else [(82,'spat_normal',dict(prepare=True)),(80,'bsm_normal',dict(stop=1200)),(81,'bsm_normal',dict(manual=True))]
 try:
  for i,(sid,selected,options) in enumerate(jobs):results.append(await execute(bundle,byid[sid],selected,channel+i,**options))
 finally:(bundle/('bridge-'+a.suite+'-results.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')

if __name__=='__main__':asyncio.run(main())

