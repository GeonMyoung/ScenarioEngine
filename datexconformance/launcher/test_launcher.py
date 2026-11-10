"""Local launcher contract tests with unchanged v9 engine and emulator.

The loopback hub emulates web routing and accepts decoded payloads as a fixture.
This is not a test of the production web server or its schema validator.
"""
import argparse, asyncio, base64, json, os, subprocess, time
from pathlib import Path
import websockets

class Hub:
    def __init__(self, case, reject=False, occupied=False):
        self.case=case; self.reject=reject; self.occupied=occupied; self.agent=None; self.controller=None
        self.commands=[]; self.events=[]; self.messages=[]
    async def handle(self, ws):
        role=ws.request.path.split('/')[3]
        if role=='agent': self.agent=ws
        else: self.controller=ws
        try:
            async for raw in ws:
                msg=json.loads(raw); self.messages.append([role,msg]); method=msg.get('method')
                if method=='DESCRIBE':
                    await ws.send(json.dumps({'seq':msg['seq'],'result':{'code':200,'reason':'OK','data':({'currConnList':[{'clientType':'Agent'}] if self.occupied else []} if role=='controller' else None)}}))
                    if role=='agent':
                        init=base64.b64encode(json.dumps({'category':'ITSK-00143-DATEX-V2','testScenario':self.case}).encode()).decode()
                        await ws.send(json.dumps({'method':'INITIALIZE','seq':2,'testScenario':init}))
                elif role=='controller' and method in ('SETUP','START','STOP'):
                    self.commands.append(method)
                    command={'method':method,'seq':msg['seq']}
                    if method=='SETUP': command['testConfiguration']=msg['data']
                    else: command['data']=''
                    await self.agent.send(json.dumps(command))
                elif role=='agent' and method in ('UI_CONFIGURE','NOTIFY'):
                    self.events.append(msg)
                    await self.controller.send(json.dumps(msg))
                    await ws.send(json.dumps({'seq':msg['seq'],'result':{'code':200,'reason':'OK','data':None}}))
                elif role=='agent' and method=='VALIDATE':
                    validation=msg['validate']
                    # Keep identity, raw/data and correlation exactly as issued.
                    await ws.send(json.dumps({'seq':msg['seq'],'testIdx':msg['testIdx'],'result':'FAILURE' if self.reject else 'SUCCESS','validate':validation}))
                elif role=='agent' and isinstance(msg.get('result'),dict) and msg.get('seq',0)>=700000:
                    await self.controller.send(json.dumps(msg))
        except websockets.ConnectionClosed: pass

async def execute(bundle, sid, selected, channel, *, web_case=None, stop=None, reject=False, multi=False, occupied=False, staged=False, prepare_only=False, ui=False, expected='SUCCESS'):
    catalog=json.loads((bundle/'scenarios.json').read_text(encoding='utf-8-sig'))
    scenario=next(x for x in catalog['scenarios'] if x['id']==sid)
    hub=Hub(web_case or scenario['case'],reject,occupied)
    async with websockets.serve(hub.handle,'127.0.0.1',0,max_size=33554432,compression=None,ping_interval=None) as server:
        port=server.sockets[0].getsockname()[1]
        args=[str(bundle/'시작하기.exe'),'--run-local',str(bundle),str(sid),selected,f'ws://127.0.0.1:{port}/ws/test/agent/{channel}/']
        if stop: args+=['--stop-after-ms',str(stop)]
        if multi: args+=['--multi-tim']
        if staged: args+=['--staged-check']
        if prepare_only: args+=['--prepare-only']
        if ui: args=[str(bundle/'시작하기.exe'),'--ui-run-check',str(bundle),args[4+1],str(bundle/'ui-flow-verification.json')]
        before=set((bundle/'runs').glob('*')) if (bundle/'runs').exists() else set()
        proc=await asyncio.create_subprocess_exec(*args,creationflags=subprocess.CREATE_NO_WINDOW)
        try: code=await asyncio.wait_for(proc.wait(),600)
        except asyncio.TimeoutError: proc.kill();raise
    runs={p for p in (set((bundle/'runs').glob('*'))-before) if json.loads((p/'session.json').read_text(encoding='utf-8')).get('agentUrl','').endswith('/'+str(channel)+'/')}
    assert len(runs)==1, (sid,code,runs)
    run=runs.pop(); outcome=json.loads((run/'easy-outcome.json').read_text(encoding='utf-8-sig'))
    assert outcome['Verdict']==expected, (sid,code,outcome['Verdict'], (run/'easy-error.txt').read_text(encoding='utf-8-sig') if (run/'easy-error.txt').exists() else '')
    if expected in ('ERROR','NOT_RUN'): assert 'START' not in hub.commands
    elif expected!='STOPPED':
        names=[x['test'] for x in outcome['Report']['results']]
        wanted=[x['key'] for x in scenario['tests']] if selected=='all' else selected.split(',')
        assert names==wanted,(names,wanted)
        assert sum(e.get('data',{}).get('testName')=='MainScenario' and e.get('data',{}).get('state')=='FINISH' for e in hub.events)==1
    sent=received=0
    for event in hub.events:
        data=event.get('data',{}); text=data.get('log','')
        if text.startswith('[송신 메시지'):
            assert data['sender']==scenario['testerSystem'],data
            sent+=1
        elif text.startswith('[수신 메시지'):
            assert data['sender']==scenario['targetSystem'],data
            received+=1
    if expected in ('SUCCESS','FAIL'): assert sent>0 and received>0
    if staged:
        assert hub.commands[:3]==['SETUP','SETUP','START'],hub.commands
        actual=json.loads((run/'datex-selection.json').read_text(encoding='utf-8'))['configuration']
        assert actual['my_domain']=='MANUAL-EDIT-TESTER' and actual['peer_domain']=='MANUAL-EDIT-TARGET'
        peer=json.loads((run/'sut-config.json').read_text(encoding='utf-8'))
        assert peer['my_domain']==actual['peer_domain'] and peer['peer_domain']==actual['my_domain'] and peer['pass']==actual['pass']
    if prepare_only: assert not (run/'sut-process.json').exists() and not (run/'datex-results').exists()
    # Every owned process has exited; no unrelated process is stopped.
    for p in run.glob('*-process.json'):
        pid=json.loads(p.read_text())['pid']
        import ctypes
        handle=ctypes.windll.kernel32.OpenProcess(0x1000,False,pid)
        if handle:
            exitcode=ctypes.c_ulong();ctypes.windll.kernel32.GetExitCodeProcess(handle,ctypes.byref(exitcode));ctypes.windll.kernel32.CloseHandle(handle)
            assert exitcode.value!=259,(pid,'still running')
    (run/'local-hub.json').write_text(json.dumps({'scope':'loopback routing/fixture validator', 'commands':hub.commands,'messages':hub.messages},ensure_ascii=False),encoding='utf-8')
    summary={'id':sid,'selected':selected,'expected':expected,'actual':outcome['Verdict'],'commands':hub.commands,'senderChecked':{'sent':sent,'received':received},'run':str(run),'exit':code}
    print(json.dumps(summary,ensure_ascii=False),flush=True)
    return summary

async def main():
    p=argparse.ArgumentParser();p.add_argument('bundle',type=Path);p.add_argument('--suite',default='smoke');args=p.parse_args()
    results=[];b=args.bundle.resolve();channel=int(time.time())
    if args.suite=='smoke':
        results.append(await execute(b,42,'normal_bsm',channel,staged=True))
        results.append(await execute(b,43,'normal_bsm',channel+1))
        results.append(await execute(b,44,'normal_map,normal_tim',channel+2,multi=True))
        results.append(await execute(b,42,'normal_bsm',channel+3,web_case='centerClient2vehicle_v2',expected='ERROR'))
        results.append(await execute(b,43,'login_retry',channel+4,stop=8000,expected='STOPPED'))
        results.append(await execute(b,42,'normal_bsm',channel+5,reject=True,expected='FAIL'))
    elif args.suite=='all': results.append(await execute(b,43,'all',channel))
    elif args.suite=='ui': results.append(await execute(b,42,'normal_bsm',channel,ui=True))
    elif args.suite=='prepare': results.append(await execute(b,42,'normal_bsm',channel,prepare_only=True,expected='NOT_RUN'))
    elif args.suite=='actors':
        for i,(sid,key) in enumerate([(47,'normal_bsm'),(50,'normal_spat'),(54,'normal_bsm'),(56,'normal_tls'),(52,'normal_bsm')]):
            results.append(await execute(b,sid,key,channel+i))
        results.append(await execute(b,42,'normal_bsm',channel+6,prepare_only=True,expected='NOT_RUN'))
    elif args.suite=='guards':
        results.append(await execute(b,42,'normal_bsm',channel,occupied=True,expected='ERROR'))
        before=set((b/'runs').glob('*'))
        prior=json.loads(next((b/'runs').glob('*/session.json')).read_text())['agentUrl']
        for address in [prior,'https://example.com/','wss://example.com/ws/test/agent/1/']:
            proc=await asyncio.create_subprocess_exec(str(b/'시작하기.exe'),'--run-local',str(b),'42','normal_bsm',address,creationflags=subprocess.CREATE_NO_WINDOW)
            assert await asyncio.wait_for(proc.wait(),8)==2
            assert set((b/'runs').glob('*'))==before
        results.append({'guards':'reused URL, invalid shape, wrong host','result':'rejected before starting processes'})
    (b/('local-launcher-'+args.suite+'-verification.json')).write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
if __name__=='__main__':asyncio.run(main())
