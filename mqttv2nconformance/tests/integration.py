"""Actual isolated loopback Broker, independent peer process and worker checks."""
import argparse,json,socket,subprocess,sys,time
from pathlib import Path

def wait_file(p,process=None,timeout=10):
    end=time.monotonic()+timeout
    while time.monotonic()<end:
        if p.exists():return
        if process and process.poll() is not None:raise RuntimeError('Peer stopped before ready')
        time.sleep(.025)
    raise TimeoutError(str(p))

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle',required=True);p.add_argument('--output',required=True)
    p.add_argument('--only',default='all');a=p.parse_args();bundle=Path(a.bundle).resolve();out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=True)
    if any(out.iterdir()):raise ValueError('검증 출력은 새 폴더 또는 비어 있는 폴더를 사용하세요.')
    module=bundle/'mqttv2nconformance';sys.path.insert(0,str(module/'runtime'))
    from catalog import CASES,items
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    conf=out/'broker.conf';conf.write_text(f'listener {port} 127.0.0.1\nallow_anonymous true\npersistence false\n',encoding='ascii')
    logfile=(out/'broker.log').open('wb');broker=subprocess.Popen([str(module/'runtime/broker/mosquitto/mosquitto.exe'),'-c',str(conf)],stdout=logfile,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
    results=[]
    try:
        deadline=time.monotonic()+10
        while True:
            try:
                with socket.create_connection(('127.0.0.1',port),.2):break
            except OSError:
                if broker.poll() is not None or time.monotonic()>deadline:raise RuntimeError('Loopback Broker start failed')
                time.sleep(.05)
        trials=[(case,'normal','',False) for case in CASES]
        trials += [('vehicleSubscriber2center_mqtt_v1','shared','',False),
                   ('centerSubscriber2vehicle_mqtt_v1','slow_receive','',False),
                   ('centerSubscriber2vehicle_mqtt_v1','bad_psid','wrong_psid',False),
                   ('centerSubscriber2vehicle_mqtt_v1','bad_length','bad_length',False),
                   ('centerSubscriber2vehicle_mqtt_v1','bad_uper','bad_uper',False),
                   ('centerSubscriber2vehicle_mqtt_v1','uper_outer_tail','uper_outer_tail',False),
                   ('centerSubscriber2vehicle_mqtt_v1','uper_inner_tail','uper_inner_tail',False),
                   ('centerSubscriber2vehicle_mqtt_v1','uper_inner_cut','uper_inner_cut',False),
                   ('centerSubscriber2vehicle_mqtt_v1','uper_padding','uper_padding',False),
                   ('centerPublisher2vehicle_mqtt_v1','no_receipt','no_receipt',False),
                   ('centerSubscriber2vehicle_mqtt_v1','stop','',True)]
        if a.only!='all':trials=[t for t in trials if t[1] in a.only.split(',')]
        for index,(case,name,fault,stop_trial) in enumerate(trials):
            d=out/f'{index:02}-{name}-{case}';d.mkdir(exist_ok=True)
            c=dict(host='127.0.0.1',port=port,client_id=f'g4-test-{index}',qos=0,repetitions=3 if name=='slow_receive' else 10,
                   timeout_seconds=2,publish_interval_seconds=0,
                   observation_file=str(d/'receipt.jsonl'))
            if CASES[case].get('publish_only'):c.update(qos=0,publish_interval_seconds=1)
            for key in CASES[case]['messages']:
                c['topic_'+key]=f'custom/{index}/SHARED' if name=='shared' else f'custom/{index}/{key.upper()}'
            for test,_,_,_ in items(case):c[test]=True
            config=d/'config.json';config.write_text(json.dumps(c),encoding='utf-8');peer=None;worker=None
            logs=[]
            try:
                if not stop_trial and not CASES[case].get('publish_only'):
                    plog=(d/'peer.log').open('wb');logs.append(plog)
                    peer=subprocess.Popen([sys.executable,'-X','utf8',str(module/'emulator/peer.py'),'--case',case,'--config',str(config),'--codec',str(module/'bin/MqttPayload.exe'),
                       '--ready',str(d/'peer.ready'),'--go',str(d/'result/ready.json') if CASES[case]['receive'] else str(d/'peer.ready'),
                       '--stop',str(d/'peer.stop'),'--interval','1.3' if name=='slow_receive' else '.08','--fault',fault],stdout=plog,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
                    wait_file(d/'peer.ready',peer)
                wlog=(d/'worker.log').open('wb');logs.append(wlog)
                worker=subprocess.Popen([sys.executable,'-X','utf8',str(module/'runtime/worker.py'),'--case',case,'--config',str(config),'--output',str(d/'result'),'--work',str(d)],stdout=wlog,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
                if stop_trial:
                    wait_file(d/'result/ready.json',worker);(d/'mqttv2n-stop').write_text('stop')
                worker.wait(50)
                r=json.loads((d/'result/result.json').read_text(encoding='utf-8'))
                expected='STOPPED' if stop_trial else 'FAIL' if fault else 'SUCCESS'
                assert worker.returncode==0,(name,worker.returncode)
                assert r['result']==expected,(name,r)
                events=[json.loads(l) for l in (d/'result/events.jsonl').read_text(encoding='utf-8').splitlines()]
                assert events[-1].get('value')=='FINISH' and sum(e.get('value')=='FINISH' for e in events)==1
                assert not any(e.get('value')=='COMPLETE' for e in events)
                if expected=='SUCCESS':assert all(x['completed']==(1 if CASES[case].get('center_provider') and x['test'].startswith('test_tim_') else c['repetitions']) for x in r['tests']),r
                if expected=='STOPPED':assert r['tests'][0]['completed']==0
                if name.startswith('uper_'):
                    reason=r['tests'][0]['reason']
                    assert 'UPER_' in reason,(name,reason)
                    assert r['tests'][0]['completed']==0
                    assert 'Timeout' not in reason and '응답 형식' not in reason,reason
                results.append(dict(case=case,trial=name,expected=expected,result=r['result'],tests=r['tests'],events=len(events)))
                print('PASS',name,case,flush=True)
            finally:
                (d/'peer.stop').write_text('stop')
                for process in [worker,peer]:
                    if process and process.poll() is None:
                        try:process.wait(2)
                        except subprocess.TimeoutExpired:process.terminate();process.wait(5)
                for f in logs:f.close()
        (out/'verification.json').write_text(json.dumps(dict(broker='isolated loopback',results=results),ensure_ascii=False,indent=2),encoding='utf-8')
    finally:
        if broker.poll() is None:broker.terminate();broker.wait(5)
        logfile.close()
if __name__=='__main__':main()
