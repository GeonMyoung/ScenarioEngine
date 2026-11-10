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
      descriptor=base64.b64encode(json.dumps(dict(category='ITSK-00143-REST-V1',testScenario=self.case)).encode()).decode();await ws.send(json.dumps(dict(method='INITIALIZE',seq=2,testScenario=descriptor)))
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
  try:code=await asyncio.wait_for(proc.wait(),90)
  finally:
   if proc.returncode is None:proc.kill();await proc.wait()
   web.stopped=True;await task
 runs=[p for p in set((bundle/'runs').glob('*'))-before if json.loads((p/'session.json').read_text())['agentUrl'].endswith('/'+str(channel)+'/')];assert len(runs)==1,(scenario['id'],code,runs)
 run=runs[0];outcome=json.loads((run/'easy-outcome.json').read_text(encoding='utf8'));error=(run/'easy-error.txt').read_text(encoding='utf8') if (run/'easy-error.txt').exists() else ''
 assert outcome['Verdict']==expected,(scenario['id'],code,outcome['Verdict'],error)
 assert not any(c in ['SETUP','START'] for c in hub.commands),hub.commands
 if expected=='SUCCESS':
  wanted=[x['key'] for x in scenario['tests']] if selected=='all' else selected.split(',');native=outcome['Report'];assert [x['test'] for x in native['items']]==['test_'+k for k in wanted]
  actual=json.loads((run/'rest-selection.json').read_text(encoding='utf8'));assert actual['valid'] and actual['case']==scenario['case']
  peer=json.loads((run/'sut-config.json').read_text(encoding='utf8'));assert peer==actual['effectiveConfiguration']
  if staged:assert int(peer['repetitions'])==11 and web.actions[:3]==['SETUP','SETUP','START']
  if manual:assert int(peer['repetitions'])==12 and web.actions[:3]==['SETUP','SETUP','START']
  assert sum(e.get('data',{}).get('testName')=='MainScenario' and e.get('data',{}).get('state')=='FINISH' for e in hub.events)==1
  states=[e['data']['state'] for e in hub.events if e.get('level')=='state'];assert 'COMPLETE' not in states
  if not scenario['provider']:assert len(json.loads((run/'sut/processed.json').read_text()))==native['completedExchanges']
 if prepare:assert not (run/'sut-process.json').exists() and not (run/'rest-results').exists()
 for file in run.glob('*-process.json'):
  pid=json.loads(file.read_text())['pid'];h=ctypes.windll.kernel32.OpenProcess(0x1000,False,pid)
  if h:
   value=ctypes.c_ulong();ctypes.windll.kernel32.GetExitCodeProcess(h,ctypes.byref(value));ctypes.windll.kernel32.CloseHandle(h);assert value.value!=259,(pid,'still running')
 (run/'bridge-verification.json').write_text(json.dumps(dict(actions=web.actions,launcherCommands=hub.commands,expected=expected,passed=True),ensure_ascii=False,indent=2),encoding='utf8')
 result=dict(scenario=scenario['id'],selected=selected,expected=expected,passed=True,run=str(run));print(result,flush=True);return result

async def main():
 p=argparse.ArgumentParser();p.add_argument('bundle',type=Path);p.add_argument('--suite',choices=['smoke','all'],default='smoke');a=p.parse_args();bundle=a.bundle.resolve();catalog=json.loads((bundle/'scenarios.json').read_text(encoding='utf8'));items=catalog['scenarios'];by_id={s['id']:s for s in items};channel=int(time.time());results=[]
 jobs=[(51,'normal_utic',dict(staged=True)),(57,'normal_vds',{}),(66,'request_weather',dict(manual=True)),(65,'no_data_error',dict(custom={'confirm_data_absent':True})),(67,'no_data',{}),(51,'normal_utic',dict(prepare=True,expected='NOT_RUN')),(51,'normal_utic',dict(custom={'repetitions':1000},stop=200,expected='STOPPED')),(51,'normal_utic',dict(wrong_case='weatherServer2center_v1',expected='ERROR')),(51,'normal_utic',dict(occupied=True,expected='ERROR'))]
 if a.suite=='all':jobs=[(s['id'],','.join(t['key'] for t in s['tests'] if not s['provider'] or t['key'] not in ['no_data_error','no_data']),{}) for s in items]+[(s['id'],'no_data_error',dict(custom={'confirm_data_absent':True})) for s in items if s['provider']]+[(s['id'],'no_data',{}) for s in items if s['provider']]
 try:
  for index,(sid,selected,options) in enumerate(jobs):results.append(await execute(bundle,by_id[sid],selected,channel+index,**options))
 finally:(bundle/('bridge-'+a.suite+'-results.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
if __name__=='__main__':asyncio.run(main())
