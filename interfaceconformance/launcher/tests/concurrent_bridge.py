"""Five real launchers/engines/peers through the common service worker and mock web forms."""
import asyncio,base64,ctypes,json,subprocess,sys,time,urllib.request
from pathlib import Path
import websockets
ROOT=Path(__file__).resolve().parents[3]
CATEGORIES={'datex':'ITSK-00143-DATEX-V2','rest':'ITSK-00143-REST-V1','binary':'ITSK-00143-TCP-V1','kafka':'ITSK-00143-KAFKA-V1'}
def read(p):return json.loads(p.read_text(encoding='utf-8-sig'))
class Hub:
 def __init__(self,kind,case):self.kind=kind;self.case=case;self.agent=None;self.controller=None;self.events=[];self.commands=[]
 async def handle(self,ws):
  role=ws.request.path.split('/')[3]
  if role=='agent':self.agent=ws
  else:self.controller=ws
  try:
   async for raw in ws:
    m=json.loads(raw);method=m.get('method')
    if method=='DESCRIBE':
     await ws.send(json.dumps({'seq':m['seq'],'result':{'code':200,'reason':'OK','data':{'currConnList':[]} if role=='controller' else None}}))
     if role=='agent':await ws.send(json.dumps({'method':'INITIALIZE','seq':2,'testScenario':base64.b64encode(json.dumps({'category':CATEGORIES[self.kind],'testScenario':self.case}).encode()).decode()}))
    elif role=='controller' and method in ['SETUP','START','STOP']:self.commands.append(method);raise AssertionError('Launcher bypassed web')
    elif role=='agent' and method in ['UI_CONFIGURE','NOTIFY']:
     self.events.append(m);await self.controller.send(raw);await ws.send(json.dumps({'seq':m['seq'],'result':{'code':200,'reason':'OK','data':None}}))
    elif role=='agent' and method=='VALIDATE':await ws.send(json.dumps({'seq':m['seq'],'testIdx':m['testIdx'],'result':'SUCCESS','validate':m['validate']}))
  except websockets.ConnectionClosed:pass
class Web:
 def __init__(self,router,channel,hub,barrier,stop=False):self.router=router;self.channel=str(channel);self.hub=hub;self.barrier=barrier;self.stop=stop;self.token='';self.done=False;self.last='';self.values={};self.actions=[];self.seq=900000;self.error=None
 async def call(self,kind,data=None,**changes):
  request={'kind':kind,'channel':self.channel,'clientId':'window-'+self.channel,'token':self.token,'data':data or {}};request.update(changes)
  body=json.dumps({'request':request,'sender':{'url':'https://106.250.189.37:8443/static/test/index.html','tab':{'id':int(self.channel)},'frameId':0,'documentId':'doc-'+self.channel}}).encode()
  def invoke():
   r=urllib.request.Request(f'http://127.0.0.1:{self.router}/bridge',data=body,headers={'Content-Type':'application/json'});return json.loads(urllib.request.urlopen(r,timeout=100).read())
  result=await asyncio.to_thread(invoke)
  if result.get('error'):raise RuntimeError(result['error'])
  return result
 async def send(self,kind):
  self.seq+=1;self.actions.append(kind);m={'seq':self.seq,'method':kind}
  if kind=='SETUP':m['testConfiguration']=json.dumps(self.values,ensure_ascii=False)
  else:m['data']=''
  await self.hub.agent.send(json.dumps(m,ensure_ascii=False))
 async def loop(self):
  try:
   while not self.done:
    if not self.token:
     try:hello=await self.call('hello')
     except (OSError,RuntimeError):await asyncio.sleep(.1);continue
     if not hello.get('linked'):await asyncio.sleep(.1);continue
     self.token=hello['token']
    result=await self.call('poll');cmd=result.get('command')
    if cmd and cmd['id']!=self.last:
     self.last=cmd['id'];error=''
     try:
      assert cmd['kind']=='apply',cmd
      self.values={k:v if isinstance(v,bool) else str(v) for k,v in cmd['data']['values'].items()};await self.call('before-setup',{'values':self.values});await self.send('SETUP');await self.call('after-setup',{'values':self.values})
     except Exception as e:error=str(e)
     await self.call('result',{'id':cmd['id'],'error':error})
     if error:raise RuntimeError(error)
     rejected=False
     try:await self.call('web-dirty',token='wrong-token')
     except RuntimeError:rejected=True
     assert rejected,'Wrong token was accepted'
     if self.hub.kind=='datex':
      await self.call('web-dirty');blocked=False
      try:await self.call('before-start',{'values':self.values})
      except RuntimeError:blocked=True
      assert blocked,'DATEX dirty configuration did not block start'
      await self.call('before-setup',{'values':self.values});await self.send('SETUP');await self.call('after-setup',{'values':self.values})
     # All five peers reserve their protocol port before any starts.
     await self.barrier.wait()
     await self.call('before-start',{'values':self.values});await self.send('START');await self.call('after-start')
     if self.stop:
      await asyncio.sleep(1.2);await self.call('before-stop');await self.send('STOP');await self.call('after-stop')
    await asyncio.sleep(.05)
  except Exception as e:
   if not self.done:self.error=str(e)
async def execute(root,router,kind,sid,selected,channel,barrier,stop=False):
 bundle=root/'bundles'/kind;scenario=next(s for s in read(bundle/'scenarios.json')['scenarios'] if s['id']==sid);hub=Hub(kind,scenario['case']);web=Web(router,channel,hub,barrier,stop)
 # Deliberately give every process the same preferred TCP port.
 values={'datex':{'peer_port':45600},'rest':{'local_port':45600},'binary':{'tcp_port':45600},'kafka':{'bootstrap_servers':'127.0.0.1:45600'}}[kind]
 if stop:values['repetitions']=100
 cfg=root/f'config-{channel}.json';cfg.write_text(json.dumps(values),encoding='utf8')
 async with websockets.serve(hub.handle,'127.0.0.1',0,max_size=33554432,compression=None,ping_interval=None) as server:
  port=server.sockets[0].getsockname()[1];url=f'ws://127.0.0.1:{port}/ws/test/agent/{channel}/';task=asyncio.create_task(web.loop());proc=await asyncio.create_subprocess_exec(str(bundle/'시작하기.exe'),'--run-local',str(bundle),str(sid),selected,url,'--web-wait','--config',str(cfg),creationflags=subprocess.CREATE_NO_WINDOW)
  try:code=await asyncio.wait_for(proc.wait(),180)
  finally:
   if proc.returncode is None:proc.kill();await proc.wait()
   web.done=True
   if not task.done():task.cancel()
   await asyncio.gather(task,return_exceptions=True)
 run=next(p.parent for p in (bundle/'runs').glob('*/session.json') if read(p)['agentUrl']==url);result=read(run/'easy-outcome.json');expected='STOPPED' if stop else 'SUCCESS'
 assert result['Verdict']==expected,(kind,sid,code,result['Verdict'],web.error,(run/'easy-error.txt').read_text(encoding='utf8') if (run/'easy-error.txt').exists() else '')
 assert not hub.commands;bridge=read(run/'web-bridge.json');actual=read(run/'platform-setup.json');port=int(actual['peer_port'] if kind=='datex' else actual['local_port'] if kind=='rest' else actual['tcp_port'] if kind=='binary' else actual['bootstrap_servers'].split(':')[-1])
 assert web.actions==(['SETUP','START','STOP'] if stop else ['SETUP','SETUP','START'] if kind=='datex' else ['SETUP','START']),web.actions
 states=[e['data'].get('state') for e in hub.events if e.get('level')=='state'];assert 'COMPLETE' not in states
 assert sum(e.get('data',{}).get('testName')=='MainScenario' and e.get('data',{}).get('state')=='FINISH' for e in hub.events)==1
 row={'kind':kind,'scenario':sid,'channel':channel,'bridgePort':bridge['port'],'peerPort':port,'verdict':result['Verdict'],'webActions':web.actions,'run':str(run)};print(json.dumps(row,ensure_ascii=False),flush=True);return row
async def main():
 root=Path(sys.argv[1]).resolve();ready=root/f'router-ready-{time.time_ns()}.json'
 process=subprocess.Popen(['node',str(Path(__file__).with_name('router_host.mjs')),str(ready)],stdout=(root/'router.out').open('wb'),stderr=(root/'router.err').open('wb'),creationflags=subprocess.CREATE_NO_WINDOW)
 try:
  while not ready.exists():await asyncio.sleep(.05)
  router=read(ready)['port'];base=int(time.time());barrier=asyncio.Barrier(5)
  cases=[('datex',42,'normal_bsm',False),('rest',51,'normal_utic',False),('binary',70,'provide_bsm',False),('binary',71,'receive_bsm_periodic',True),('kafka',76,'open_normal',False)]
  results=await asyncio.gather(*(execute(root,router,kind,sid,sel,base+i,barrier,stop) for i,(kind,sid,sel,stop) in enumerate(cases)),return_exceptions=True)
  errors=[repr(x) for x in results if isinstance(x,BaseException)];valid=[x for x in results if isinstance(x,dict)]
  if not errors:assert len({x['bridgePort'] for x in valid})==len({x['peerPort'] for x in valid})==5
  report={'runs':valid,'errors':errors,'samePreferredPort':45600,'passed':not errors};(root/'concurrency.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf8');assert not errors,errors
 finally:process.terminate();process.wait(timeout=5)
if __name__=='__main__':asyncio.run(main())
