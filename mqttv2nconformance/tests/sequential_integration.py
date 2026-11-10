"""QoS 0 center Publisher campaign using an isolated real Mosquitto and native codec."""
import argparse,json,socket,subprocess,sys,time
from pathlib import Path

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle',type=Path,required=True);p.add_argument('--output',type=Path,required=True)
    a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False)
    module=a.bundle.resolve()/'mqttv2nconformance';sys.path.insert(0,str(module/'runtime'))
    from catalog import items
    case='vehicleSubscriber2center_mqtt_v1'
    with socket.socket() as sock:sock.bind(('127.0.0.1',0));port=sock.getsockname()[1]
    conf=out/'broker.conf';conf.write_text(f'listener {port} 127.0.0.1\nallow_anonymous true\npersistence false\n',encoding='ascii')
    log=(out/'broker.log').open('wb')
    broker=subprocess.Popen([str(module/'runtime/broker/mosquitto/mosquitto.exe'),'-c',str(conf),'-v'],stdout=log,stderr=log,creationflags=subprocess.CREATE_NO_WINDOW)
    results=[]
    try:
        until=time.monotonic()+10
        while True:
            try:
                with socket.create_connection(('127.0.0.1',port),.1):break
            except OSError:
                if time.monotonic()>until or broker.poll() is not None:raise RuntimeError('broker not ready')
                time.sleep(.05)
        trials=[('default',{},'',1,'SUCCESS'),
                ('shared-custom',dict(repetitions=2),'',1,'SUCCESS'),
                ('tim-only',dict(repetitions=2,**{x[0]:x[1]=='tim' for x in items(case)}),'',.1,'SUCCESS'),
                ('slow-receive',dict(repetitions=3,**{x[0]:x[1]=='spat' for x in items(case)}),'',1.3,'SUCCESS'),
                ('trailing',{},'uper_outer_tail',1,'FAIL'),
                ('field',{},'spat_timestamp',1,'FAIL'),
                ('silent',dict(timeout_seconds=2), 'silence',1,'STOPPED'),
                ('stop',{},'',1,'STOPPED')]
        for name,overrides,fault,interval,expected in trials:
            d=out/name;d.mkdir();c=dict(host='127.0.0.1',port=port,client_id='seq-'+name,
                **{x[0]:True for x in items(case)})
            c.update(overrides)
            for key in ('spat','tlsm','tim'):c['topic_'+key]='seq/'+name+('/shared' if name.startswith('shared') else '/'+key)
            config=d/'config.json';config.write_text(json.dumps(c),encoding='utf-8')
            logs=[];processes=[]
            try:
                def start(args,label):
                    stream=(d/(label+'.log')).open('wb');logs.append(stream)
                    proc=subprocess.Popen([sys.executable,'-X','utf8',*args],stdout=stream,stderr=stream,creationflags=subprocess.CREATE_NO_WINDOW);processes.append(proc);return proc
                peer=start([str(module/'emulator/peer.py'),'--case',case,'--config',str(config),
                    '--codec',str(module/'bin/MqttPayload.exe'),'--ready',str(d/'peer.ready'),
                    '--go',str(d/'result/ready.json'),'--stop',str(d/'peer.stop'),'--interval',str(interval),'--fault',fault],'peer')
                until=time.monotonic()+10
                while not (d/'peer.ready').exists():
                    if peer.poll() is not None or time.monotonic()>until:raise RuntimeError('peer not ready')
                    time.sleep(.02)
                worker=start([str(module/'runtime/worker.py'),'--case',case,'--config',str(config),
                    '--output',str(d/'result'),'--work',str(d)],'worker')
                if expected=='STOPPED':
                    until=time.monotonic()+10
                    while not (d/'result/ready.json').exists():
                        if worker.poll() is not None or time.monotonic()>until:raise RuntimeError('worker not ready')
                        time.sleep(.02)
                    if name=='silent':
                        time.sleep(3)
                        assert worker.poll() is None,'무수신 대기 중 자동 종료'
                    (d/'mqttv2n-stop').write_text('stop')
                worker.wait(85)
                r=json.loads((d/'result/result.json').read_text(encoding='utf-8'))
                assert worker.returncode==0 and r['result']==expected,(name,r)
                events=[json.loads(l) for l in (d/'result/events.jsonl').read_text(encoding='utf-8').splitlines()]
                assert sum(e.get('value')=='FINISH' for e in events)==1 and events[-1]['value']=='FINISH'
                data=[json.loads(e['data']) for e in events if e['kind']=='info']
                if expected=='SUCCESS':
                    keys=['tim'] if name=='tim-only' else ['spat'] if name=='slow-receive' else ['spat','tlsm','tim']
                    diagnostics=[json.loads(json.loads(line)['data']) for line in (d/'result/diagnostic-events.jsonl').read_text(encoding='utf-8').splitlines()]
                    assert len([x for x in diagnostics if x.get('packet')=='SUBSCRIBE'])==len(keys)
                    assert len([x for x in diagnostics if x.get('packet')=='UNSUBACK'])==len(keys)
                    assert all(x['qos']==0 for x in diagnostics if x.get('packet')=='PUBLISH')
                    assert not any(x.get('packet') in ('PUBACK','PUBCOMP') for x in diagnostics)
                    assert any('송수신 원문 HEX' in x for x in data)
                    assert all(x['completed']==(1 if x['test'].startswith('test_tim_') else c.get('repetitions',10)) for x in r['tests'])
                if name=='trailing':assert 'UPER_TRAILING_DATA' in r['tests'][0]['reason']
                if name=='field':
                    detail=r['tests'][0]['failure']
                    assert detail['observed']['field']=='SPaT.timeStamp' and detail['observed']['actual']==1048575
                    assert detail['observed']['expected']=='0..527040'
                    assert [t['result'] for t in r['tests']][1:]==['NOT_RUN']*6
                results.append(dict(name=name,expected=expected,actual=r,events=len(events)))
                print('PASS',name,r['result'],flush=True)
            finally:
                (d/'peer.stop').write_text('stop')
                for proc in reversed(processes):
                    if proc.poll() is None:
                        try:proc.wait(3)
                        except subprocess.TimeoutExpired:proc.terminate();proc.wait(5)
                for stream in logs:stream.close()
        (out/'verification.json').write_text(json.dumps(dict(passed=True,qos=0,cases=results),ensure_ascii=False,indent=2),encoding='utf-8')
    finally:
        broker.terminate();broker.wait(5);log.close()

if __name__=='__main__':main()
