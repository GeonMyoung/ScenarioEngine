"""Direct SETUP credentials through the native engine into a password-required Broker."""
import argparse,asyncio,base64,json,os,secrets,socket,subprocess,sys,time
from pathlib import Path
import websockets

async def main():
    parser=argparse.ArgumentParser();parser.add_argument('--bundle',type=Path,required=True);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--passwd-tool',type=Path,required=True);parser.add_argument('--broker-exe',type=Path)
    args=parser.parse_args();bundle=args.bundle.resolve();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    module=bundle/'mqttv2nconformance'
    sys.path.insert(0,str(module/'runtime'))
    from credentials import unprotect
    password='test-only-'+secrets.token_hex(16)+'!@#';username='mqtt-direct-input-test'
    password_file=out/'broker-passwords';subprocess.run([str(args.passwd_tool),'-H','sha512-pbkdf2','-c','-b',str(password_file),username,password],check=True,capture_output=True,creationflags=subprocess.CREATE_NO_WINDOW)
    # This installed passwd utility emits a domain SID without the user's RID.
    # Give only the current owner access to this newly generated test fixture.
    acl_script=out/'fixture-acl.ps1'
    acl_script.write_text('param([string]$FixturePath)\n$ErrorActionPreference="Stop"\n$taskSid=[Security.Principal.WindowsIdentity]::GetCurrent().User.Value\n& icacls.exe $FixturePath /grant ("*"+$taskSid+":(F)")\nif($LASTEXITCODE -ne 0){throw "Test fixture ACL failed"}\n',encoding='utf-8')
    subprocess.run(['powershell','-NoProfile','-File',str(acl_script),str(password_file)],check=True,capture_output=True,creationflags=subprocess.CREATE_NO_WINDOW)
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    conf=out/'broker.conf';conf.write_text(f'listener {port} 127.0.0.1\nallow_anonymous false\npassword_file broker-passwords\npersistence false\n',encoding='utf-8')
    brokerlog=(out/'broker.log').open('wb');broker=subprocess.Popen([str(args.broker_exe or module/'runtime/broker/mosquitto/mosquitto.exe'),'-c',str(conf)],cwd=out,stdout=brokerlog,stderr=brokerlog,creationflags=subprocess.CREATE_NO_WINDOW)
    cases=[]
    try:
        end=time.monotonic()+10
        while True:
            try:
                with socket.create_connection(('127.0.0.1',port),.1):break
            except OSError:
                if time.monotonic()>end or broker.poll() is not None:raise RuntimeError('Broker did not start')
                await asyncio.sleep(.05)
        for name,pwd,expected in [('correct',password,'SUCCESS'),('wrong','wrong-'+password,'FAIL')]:
            d=out/name;d.mkdir();events=[];connected=[];ui=asyncio.Event();finished=asyncio.Event()
            config=dict(host='127.0.0.1',port=port,client_id='native-auth-'+name,username=username,password=pwd,topic_bsm='test/auth/bsm',repetitions=1,test_bsm_normal=True)
            async def handler(ws):
                connected.append(ws)
                try:
                    async for raw in ws:
                        msg=json.loads(raw);events.append(msg)
                        if msg.get('method')=='DESCRIBE':
                            await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
                            await ws.send(json.dumps(dict(method='INITIALIZE',seq=2,testScenario=base64.b64encode(json.dumps(dict(category='ITSK-00143-MQTT-V1',testScenario='vehiclePublisher2center_mqtt_v1')).encode()).decode())))
                        elif msg.get('method') in ('UI_CONFIGURE','NOTIFY'):
                            await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
                            if msg['method']=='UI_CONFIGURE':ui.set()
                            if msg.get('data',{}).get('testName')=='MainScenario' and msg.get('data',{}).get('state')=='FINISH':finished.set()
                except websockets.ConnectionClosed:pass
            with (d/'engine.log').open('wb') as log:
                async with websockets.serve(handler,'127.0.0.1',0,max_size=8*1024*1024,compression=None,ping_interval=None) as server:
                    endpoint=f'ws://127.0.0.1:{server.sockets[0].getsockname()[1]}/ws/test/agent/912/'
                    engine=subprocess.Popen([str(bundle/'ScenarioEngineTest.exe'),endpoint],cwd=d,stdout=log,stderr=log,creationflags=subprocess.CREATE_NO_WINDOW)
                    try:
                        await asyncio.wait_for(ui.wait(),20)
                        await connected[0].send(json.dumps(dict(method='SETUP',seq=101,testConfiguration=json.dumps(config))))
                        end=time.monotonic()+15
                        while True:
                            receipt=d/'mqttv2n-selection.json'
                            if receipt.exists():
                                try:
                                    if json.loads(receipt.read_text(encoding='utf-8')).get('valid'):break
                                except ValueError:pass
                            if time.monotonic()>end:raise TimeoutError('SETUP not accepted')
                            await asyncio.sleep(.03)
                        effective=json.loads(receipt.read_text(encoding='utf-8'))['effectiveConfiguration']
                        assert 'password' not in effective and effective['password_protected'].startswith('dpapi-v1:')
                        assert unprotect(effective)['password']==pwd,'Password changed between SETUP and runtime'
                        await connected[0].send(json.dumps(dict(method='START',seq=102,data='')))
                        await asyncio.wait_for(finished.wait(),40)
                        result=json.loads(next((d/'mqttv2n-results').glob('*/result.json')).read_text(encoding='utf-8'))
                        assert result['result']==expected,(name,result)
                        await asyncio.sleep(.3)
                    finally:
                        if engine.poll() is None:engine.terminate();engine.wait(5)
            encoded=json.dumps(events,ensure_ascii=False)
            assert password not in encoded and ('wrong-'+password) not in encoded
            (d/'events.json').write_text(encoded,encoding='utf-8')
            leaks=[]
            for p in d.rglob('*'):
                if not p.is_file():continue
                data=p.read_bytes();decoded=data.decode('utf-8',errors='replace')
                if password.encode() in data or json.dumps(password)[1:-1] in decoded or password.encode().hex() in ''.join(decoded.lower().split()):leaks.append(p.name)
            assert not leaks,(name,leaks)
            cases.append(dict(name=name,expected=expected,result=result['result'],passwordLeaked=False,protectedReceipt=True));print('PASS',name,expected,flush=True)
        (out/'verification.json').write_text(json.dumps(dict(realNativeEngine=True,brokerRequiresAuthentication=True,cases=cases),indent=2),encoding='utf-8')
    finally:
        broker.terminate();broker.wait(5);brokerlog.close()

if __name__=='__main__':asyncio.run(main())
