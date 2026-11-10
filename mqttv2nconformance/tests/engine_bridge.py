"""Real ScenarioEngineTest.exe against a loopback WebSocket controller and MQTT peer."""
import argparse,asyncio,base64,json,os,socket,subprocess,sys,time
from pathlib import Path
import websockets

async def run(a):
    bundle=Path(a.bundle).resolve();out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=True)
    if any(out.iterdir()):raise ValueError('검증 출력은 새 폴더 또는 비어 있는 폴더를 사용하세요.')
    module=bundle/'mqttv2nconformance';sys.path.insert(0,str(module/'runtime'))
    from catalog import CASES,items
    peer_module=Path(a.peer_module).resolve() if a.peer_module else module
    broker_runtime=Path(a.broker_runtime).resolve() if a.broker_runtime else module/'runtime/broker/mosquitto'
    engine_env=dict(os.environ)
    engine_env.pop('PYTHONHOME',None);engine_env.pop('PYTHONPATH',None)
    if a.isolate_engine_path:
        windows=Path(os.environ['SystemRoot'])
        engine_env['PATH']=str(windows/'System32')+os.pathsep+str(windows)
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    conf=out/'broker.conf';conf.write_text(f'listener {port} 127.0.0.1\nallow_anonymous true\npersistence false\n',encoding='ascii')
    blog=(out/'broker.log').open('wb');broker=subprocess.Popen([str(broker_runtime/'mosquitto.exe'),'-c',str(conf)],stdout=blog,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
    results=[]
    try:
        await asyncio.sleep(.4)
        for index,case in enumerate(CASES):
            if a.case and case!=a.case:continue
            d=out/str(index);d.mkdir(exist_ok=True);events=[];finished=asyncio.Event();ui_received=asyncio.Event();start_sent=asyncio.Event();error=[];connection=[];sequence=100
            c=dict(host='127.0.0.1',port=port,client_id=f'g4-native-{index}',qos=0,repetitions=10,timeout_seconds=4,
                   publish_interval_seconds=.02,observation_file=str(d/'receipt.jsonl'))
            if CASES[case].get('publish_only'):c.update(qos=0,publish_interval_seconds=1)
            for k in CASES[case]['messages']:c['topic_'+k]=f'engine/{index}/{k}'
            for name,_,mode,_ in items(case):
                if mode!='period':c[name]=True
            if a.tim_timeout is not None:c['tim_timeout_seconds']=a.tim_timeout
            if a.tim_per_type is not None:c['tim_per_type']=a.tim_per_type
            if a.all_items:
                for name,_,_,_ in items(case):c[name]=True
                c.update(period_samples=3,period_tolerance_seconds=.1)
            if a.tests:
                chosen=a.tests.split(',')
                for name,_,_,_ in items(case):c[name]=name in chosen
            config=d/'config.json';config.write_text(json.dumps(c),encoding='utf-8')
            async def handle(ws):
                connection.append(ws)
                try:
                    async for raw in ws:
                        msg=json.loads(raw);events.append(msg);method=msg.get('method')
                        if method=='DESCRIBE':
                            await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
                            await ws.send(json.dumps(dict(method='INITIALIZE',seq=2,testScenario=base64.b64encode(json.dumps(dict(category='ITSK-00143-MQTT-V1',testScenario=case)).encode()).decode())))
                        elif method in ('UI_CONFIGURE','NOTIFY'):
                            await ws.send(json.dumps(dict(seq=msg['seq'],result=dict(code=200,reason='OK',data=None))))
                            if method=='UI_CONFIGURE':ui_received.set()
                            data=msg.get('data')
                            if method=='NOTIFY' and isinstance(data,dict) and data.get('testName')=='MainScenario' and data.get('state')=='FINISH':finished.set()
                except websockets.ConnectionClosed:pass
                except Exception as e:error.append(repr(e));finished.set()
            plog=(d/'peer.log').open('wb');elog=(d/'engine.log').open('wb');peer=None;engine=None
            try:
                async with websockets.serve(handle,'127.0.0.1',0,max_size=8*1024*1024,compression=None,ping_interval=None) as server:
                    wsport=server.sockets[0].getsockname()[1]
                    engine=subprocess.Popen([str(bundle/'ScenarioEngineTest.exe'),f'ws://127.0.0.1:{wsport}/ws/test/agent/901/'],cwd=d,env=engine_env,stdin=subprocess.DEVNULL,stdout=elog,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
                    await asyncio.wait_for(ui_received.wait(),15)
                    ui_event=next(e for e in events if e.get('method')=='UI_CONFIGURE')
                    ui=json.loads(base64.b64decode(ui_event['conf']))
                    assert len(ui['scenarios'])>0
                    fields=[f['option'] for div in ui['configuration'] for group in div['components'] for f in group['components']]
                    assert all(next(f for f in fields if f['name']=='topic_'+k)['value']=='' for k in CASES[case]['messages'])
                    (d/'ui-event.json').write_text(json.dumps(ui_event,ensure_ascii=False,indent=2),encoding='utf-8')
                    # Engine module is rooted beside its executable, not the test CWD.
                    if not CASES[case].get('publish_only'):
                        peer=subprocess.Popen([sys.executable,'-X','utf8',str(peer_module/'emulator/peer.py'),'--case',case,'--config',str(config),'--codec',str(module/'bin/MqttPayload.exe'),
                            '--subscriptions',str(d/'mqttv2n-results'),'--ready',str(d/'peer.ready'),'--go',str(d/'go'),'--stop',str(d/'peer.stop'),'--interval',str(a.peer_interval) if a.peer_interval is not None else '1' if a.all_items else '.1','--fault',a.fault],stdout=plog,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
                        deadline=time.monotonic()+10
                        while not (d/'peer.ready').exists():
                            if time.monotonic()>deadline or peer.poll() is not None:raise RuntimeError('Peer readiness failure')
                            await asyncio.sleep(.025)
                    await connection[0].send(json.dumps(dict(method='SETUP',seq=101,testConfiguration=json.dumps(c))))
                    deadline=time.monotonic()+10
                    while True:
                        receipt=d/'mqttv2n-selection.json'
                        if receipt.exists():
                            try:
                                if json.loads(receipt.read_text(encoding='utf-8')).get('valid'):break
                            except (OSError,ValueError):pass
                        if time.monotonic()>deadline:raise RuntimeError('SETUP receipt missing')
                        await asyncio.sleep(.025)
                    if a.setup_guard:
                        invalid=dict(c);invalid['topic_'+CASES[case]['messages'][0]]=''
                        await connection[0].send(json.dumps(dict(method='SETUP',seq=102,testConfiguration=json.dumps(invalid))))
                        deadline=time.monotonic()+10
                        while True:
                            receipt=d/'mqttv2n-selection.json'
                            try:
                                if receipt.exists() and json.loads(receipt.read_text(encoding='utf-8')).get('valid') is False:break
                            except ValueError:pass
                            if time.monotonic()>deadline:raise RuntimeError('Invalid SETUP did not invalidate selection')
                            await asyncio.sleep(.025)
                        await connection[0].send(json.dumps(dict(method='START',seq=103,data='')))
                        await asyncio.sleep(.5)
                        assert not any(e.get('level')=='state' and e.get('data',{}).get('state')=='START' for e in events)
                        results.append(dict(case=case,invalidSetupRejected=True,staleStartBlocked=True))
                        print('PASS native invalid SETUP',case,flush=True)
                        continue
                    await connection[0].send(json.dumps(dict(method='START',seq=102,data='')))
                    if CASES[case]['receive']:
                        deadline=time.monotonic()+10
                        while not list((d/'mqttv2n-results').glob('*/ready.json')):
                            if time.monotonic()>deadline:raise RuntimeError('Native worker SUBACK readiness missing')
                            await asyncio.sleep(.025)
                    if a.stop:
                        if a.stop_delay:
                            (d/'go').write_text('go')
                            await asyncio.sleep(a.stop_delay)
                        assert not finished.is_set(),'수신 대기 중 자동 종료'
                        await connection[0].send(json.dumps(dict(method='STOP',seq=103,data='')))
                    else:(d/'go').write_text('go')
                    await asyncio.wait_for(finished.wait(),60)
                    if error:raise RuntimeError(error)
                    states=[e.get('data',{}).get('state') for e in events if e.get('method')=='NOTIFY' and e.get('level')=='state']
                    main=[e['data']['state'] for e in events if e.get('method')=='NOTIFY' and e.get('level')=='state' and e.get('data',{}).get('testName')=='MainScenario']
                    expected=a.expected_result or ('STOPPED' if a.stop else 'FAIL' if a.fault and a.fault!='tim_duplicate' else 'SUCCESS')
                    assert main==['START',expected,'FINISH'],(case,main)
                    assert 'COMPLETE' not in states and states.count('FINISH')==1
                    infos=[e for e in events if e.get('method')=='NOTIFY' and e.get('level')=='info']
                    assert infos
                    evidence=[json.loads(base64.b64decode(e['data']['data'])) for e in infos
                              if e['data'].get('dataType')=='JSON' and e['data'].get('data')]
                    payloads=[row for row in evidence if '송수신 원문 HEX' in row]
                    if expected=='SUCCESS':
                        assert payloads and all(bytes.fromhex(row['송수신 원문 HEX']) for row in payloads)
                    if CASES[case]['receive']:
                        removed={'qos','timeout_seconds','period_samples','period_tolerance_seconds','tim_timeout_seconds'}
                        assert not removed.intersection(f['name'] for f in fields)
                    detail_results={e['data']['testName']:e['data']['state'] for e in events if e.get('method')=='NOTIFY' and e.get('level')=='state' and e.get('data',{}).get('testName')!='MainScenario' and e['data']['state']!='START'}
                    if expected=='FAIL' and a.fault:
                        assert 'FAIL' in detail_results.values(),detail_results
                        final_result=json.loads(next((d/'mqttv2n-results').glob('*/result.json')).read_text(encoding='utf-8'))
                        code='CONTAINER_FIELD_MISMATCH' if a.fault=='wrong_psid' else 'UPER_'
                        assert code in json.dumps(final_result['failures'],ensure_ascii=False),'Failure detail missing'
                        assert any(row.get('메시지 결과')=='정합성 실패' for row in payloads),'Failed payload missing'
                    elif expected=='SUCCESS':
                        selected={name for name,_,_,_ in items(case) if c.get(name)}
                        assert set(detail_results)==selected and all(v=='SUCCESS' for v in detail_results.values()),detail_results
                    if expected=='FAIL':assert 'FAIL' in detail_results.values()
                    results.append(dict(case=case,mainStates=main,notifications=len(states),infos=len(infos),payloads=len(payloads),detailResults=detail_results,
                                        executable=str(bundle/'ScenarioEngineTest.exe'),enginePathIsolated=a.isolate_engine_path))
                    print('PASS native engine',case,flush=True)
            finally:
                (d/'peer.stop').write_text('stop')
                for process in [peer,engine]:
                    if process and process.poll() is None:
                        process.terminate();process.wait(10)
                plog.close();elog.close()
                (d/'events.json').write_text(json.dumps(events,ensure_ascii=False,indent=2),encoding='utf-8')
        (out/'verification.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
    finally:
        if broker.poll() is None:broker.terminate();broker.wait(5)
        blog.close()
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--bundle',required=True);p.add_argument('--output',required=True);p.add_argument('--case');p.add_argument('--stop',action='store_true');p.add_argument('--stop-delay',type=float,default=0);p.add_argument('--setup-guard',action='store_true')
    p.add_argument('--broker-runtime');p.add_argument('--peer-module');p.add_argument('--all-items',action='store_true');p.add_argument('--isolate-engine-path',action='store_true')
    p.add_argument('--tests');p.add_argument('--peer-interval',type=float);p.add_argument('--expected-result',choices=['SUCCESS','FAIL','STOPPED']);p.add_argument('--fault',default='');p.add_argument('--tim-timeout',type=float);p.add_argument('--tim-per-type',type=int)
    asyncio.run(run(p.parse_args()))
