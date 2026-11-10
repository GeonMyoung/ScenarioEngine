"""Real Broker checks with no receiver and an independent wire observer."""
import argparse,json,socket,subprocess,sys,time,hashlib
from pathlib import Path

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle',type=Path,required=True);p.add_argument('--output',type=Path,required=True)
    a=p.parse_args();module=a.bundle.resolve()/'mqttv2nconformance';out=a.output.resolve();out.mkdir(parents=True,exist_ok=False)
    sys.path.insert(0,str(module/'runtime'))
    from transport import Transport
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    conf=out/'broker.conf';conf.write_text(f'listener {port} 127.0.0.1\nallow_anonymous true\npersistence false\n',encoding='ascii')
    log=(out/'broker.log').open('wb');broker=subprocess.Popen([str(module/'runtime/broker/mosquitto/mosquitto.exe'),'-c',str(conf)],stdout=log,stderr=log,creationflags=subprocess.CREATE_NO_WINDOW)
    results=[]
    try:
        end=time.monotonic()+10
        while True:
            try:
                with socket.create_connection(('127.0.0.1',port),.1):break
            except OSError:
                if time.monotonic()>end or broker.poll() is not None:raise RuntimeError('broker not ready')
                time.sleep(.02)
        for name,count,observe in [('no-receiver',3,False),('observed-wire',10,True)]:
            d=out/name;d.mkdir();topic='BSM-publish-only/'+name
            config=dict(host='127.0.0.1',port=port,client_id='publish-only-'+name,topic_bsm=topic,repetitions=count,test_bsm_normal=True)
            (d/'config.json').write_text(json.dumps(config),encoding='utf-8');received=[];observer=None;worker=None
            with (d/'worker.log').open('wb') as output:
                try:
                    if observe:
                        observer=Transport('127.0.0.1',port,client_id='independent-observer');observer.connect(10);observer.subscribe({topic:0},10)
                    worker=subprocess.Popen([sys.executable,'-X','utf8',str(module/'runtime/worker.py'),'--case','vehiclePublisher2center_mqtt_v1','--config',str(d/'config.json'),'--work',str(d),'--output',str(d/'result')],stdout=output,stderr=output,creationflags=subprocess.CREATE_NO_WINDOW)
                    end=time.monotonic()+25
                    while worker.poll() is None:
                        if time.monotonic()>end:raise TimeoutError('worker did not finish')
                        if observer:
                            message=observer.receive(.05)
                            if message:received.append(message)
                        else:time.sleep(.05)
                    if observer:
                        while True:
                            message=observer.receive(.05)
                            if not message:break
                            received.append(message)
                    assert worker.returncode==0
                    result=json.loads((d/'result/result.json').read_text(encoding='utf-8'))
                    journal=[json.loads(s) for s in (d/'result/bsm-transmit.jsonl').read_text(encoding='utf-8').splitlines()]
                    assert result['result']=='SUCCESS' and result['sut_receive_confirmed']==False
                    assert result['final_verdict']=='PENDING_RECEIVER_LOG_REVIEW'
                    assert len(journal)==count and all(r['status']=='PUBLISHED' and r['completion']=='socket-send' and r['qos']==0 for r in journal)
                    assert all(bytes.fromhex(r['payload_hex'])[1]==0 and r['container_version']==0 for r in journal)
                    assert len(set(bytes.fromhex(r['payload_hex'])[16:] for r in journal))==count
                    assert [r['msgCnt'] for r in journal]==list(range(count))
                    assert [r['speed'] for r in journal]==list(range(500,500+count))
                    assert len(set(r['vehicle_id'] for r in journal))==1
                    assert all(r['schema_review']=='J2735_20240923_KSR1600_ADOPTED' for r in journal)
                    intervals=[r['interval_from_previous_seconds'] for r in journal[1:]]
                    assert all(.99<=v<=1.1 for v in intervals),intervals
                    if observe:
                        assert len(received)==count,(len(received),count)
                        assert [m['payload'].hex() for m in received]==[r['payload_hex'] for r in journal]
                        assert all(m['topic']==topic and m['qos']==0 and not m['retain'] for m in received)
                        (d/'independent-capture.json').write_text(json.dumps([dict(topic=m['topic'],qos=m['qos'],received=m['received'],payload_hex=m['payload'].hex()) for m in received],indent=2))
                    events=[json.loads(s) for s in (d/'result/events.jsonl').read_text(encoding='utf-8').splitlines()]
                    assert events[-1]['value']=='FINISH' and sum(e.get('value')=='FINISH' for e in events)==1
                    assert not any('수신 관측을 기다립니다' in e.get('log','') for e in events)
                    results.append(dict(name=name,published=count,receiverPresent=observe,wireMatched=len(received),containerVersion=0,distinctBodies=count,intervals=intervals,result=result['result'],finalVerdict=result['final_verdict']))
                    print('PASS',name,flush=True)
                finally:
                    if worker and worker.poll() is None:worker.terminate();worker.wait(5)
                    if observer:observer.close()
        (out/'verification.json').write_text(json.dumps(dict(passed=True,trials=results),indent=2),encoding='utf-8')
    finally:
        broker.terminate();broker.wait(5);log.close()

if __name__=='__main__':main()
