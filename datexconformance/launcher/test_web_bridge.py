"""Loopback integration of the launcher/extension contract, separate from installed Chrome QA."""
import asyncio,json,subprocess,sys,time,urllib.request,urllib.error
from pathlib import Path
from test_launcher import Hub
import websockets

class FakeWeb:
    def __init__(self,bundle,channel,hub,manual=False):
        self.bundle=bundle;self.channel=str(channel);self.hub=hub;self.manual=manual
        self.ext=(bundle/'extension-id.txt').read_text().strip();self.token='';self.client='contract-test';self.seq=900000
        self.commands=[];self.web_actions=[];self.values={};self.last='';self.stopped=False
    async def call(self,kind,data=None,origin=None,ext=None):
        body=json.dumps(dict(kind=kind,channel=self.channel,clientId=self.client,token=self.token,data=data or {})).encode()
        def request():
            r=urllib.request.Request('http://127.0.0.1:43763/bridge',data=body,headers={'Content-Type':'application/json','X-Rest-Extension':ext or self.ext,'Origin':origin or 'chrome-extension://'+self.ext})
            return json.loads(urllib.request.urlopen(r,timeout=25).read())
        return await asyncio.to_thread(request)
    async def send(self,kind):
        self.seq+=1;self.web_actions.append(kind)
        request={'method':kind,'seq':self.seq}
        if kind=='SETUP':request['testConfiguration']=json.dumps(self.values)
        else:request['data']=''
        await self.hub.agent.send(json.dumps(request))
    async def setup(self,values):
        # HTML number inputs yield strings; checkboxes yield booleans.
        self.values={k:v if isinstance(v,bool) else str(v) for k,v in values.items()}
        await self.call('before-setup',{'values':self.values});await self.send('SETUP');await self.call('after-setup',{'values':self.values})
    async def start(self):
        await self.call('before-start',{'values':self.values});await self.send('START');await self.call('after-start')
    async def loop(self):
        while not self.stopped:
            try:
                if not self.token:
                    hello=await self.call('hello')
                    if not hello.get('linked'):await asyncio.sleep(.1);continue
                    self.token=hello['token']
                result=await self.call('poll');cmd=result.get('command')
                if cmd and cmd['id']!=self.last:
                    self.last=cmd['id'];self.commands.append(cmd['kind']);error=''
                    try:
                        if cmd['kind']=='apply':await self.setup(cmd['data']['values'])
                        elif cmd['kind']=='start':await self.start()
                        elif cmd['kind']=='stop':await self.call('before-stop');await self.send('STOP');await self.call('after-stop')
                    except Exception as e:error=str(e)
                    await self.call('result',dict(id=cmd['id'],error=error))
                    if self.manual and cmd['kind']=='apply' and not error:
                        await asyncio.sleep(.4);await self.start()
            except (OSError,urllib.error.URLError):pass
            await asyncio.sleep(.05)

async def check(bundle,sid,manual=False,ui=False):
    catalog=json.loads((bundle/'scenarios.json').read_text(encoding='utf-8-sig'));scenario=next(s for s in catalog['scenarios'] if s['id']==sid)
    channel=int(time.time()*1000);hub=Hub(scenario['case']);front=FakeWeb(bundle,channel,hub,manual)
    async with websockets.serve(hub.handle,'127.0.0.1',0,max_size=33554432,compression=None,ping_interval=None) as server:
        port=server.sockets[0].getsockname()[1];url=f'ws://127.0.0.1:{port}/ws/test/agent/{channel}/'
        args=[str(bundle/'시작하기.exe'),'--run-local',str(bundle),str(sid),'normal_bsm',url]
        if manual:args+=['--web-wait']
        if ui:args=[str(bundle/'시작하기.exe'),'--ui-run-check',str(bundle),url,str(bundle/'ui-web-flow.json')]
        worker=asyncio.create_task(front.loop())
        proc=await asyncio.create_subprocess_exec(*args,creationflags=subprocess.CREATE_NO_WINDOW)
        try:code=await asyncio.wait_for(proc.wait(),150)
        finally:front.stopped=True;await worker
    assert code==0,(sid,manual,ui,code)
    runs=[p for p in (bundle/'runs').iterdir() if json.loads((p/'session.json').read_text(encoding='utf-8')).get('agentUrl')==url]
    assert len(runs)==1;r=runs[0];outcome=json.loads((r/'easy-outcome.json').read_text(encoding='utf-8'));assert outcome['Verdict']=='SUCCESS'
    assert not any(m.get('method') in ('SETUP','START') for role,m in hub.messages if role=='controller'),'Launcher bypassed browser'
    assert front.web_actions==(['SETUP','SETUP','START'] if ui else ['SETUP','START']),front.web_actions
    summary={'id':sid,'manualWebStart':manual,'guiFlow':ui,'webActions':front.web_actions,'launcherCommands':front.commands,'verdict':outcome['Verdict'],'noDirectSetupStart':True,'run':str(r)}
    print(json.dumps(summary,ensure_ascii=False),flush=True);return summary

async def main():
    bundle=Path(sys.argv[1]).resolve();results=[]
    for sid,manual,ui in [(42,False,False),(43,True,False),(42,False,True)]:results.append(await check(bundle,sid,manual,ui))
    (bundle.parent/'web-bridge-contract-verification.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
if __name__=='__main__':asyncio.run(main())
