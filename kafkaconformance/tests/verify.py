"""Real broker integration: independent peers, negative paths and lossless events."""
import argparse,base64,copy,json,subprocess,sys,time,uuid
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'runtime'))
from catalog import CASES,items,parse_config
from fields import validate,strict_json,decode
from confluent_kafka.admin import AdminClient,NewTopic

def check_fields():
    count=0
    for s in ['open','platform','map','i2x']:
        v=json.loads((ROOT/'fixtures'/(s+'.json')).read_text(encoding='utf8'));assert validate(s,v)
    source=json.loads((ROOT/'fixtures/open.json').read_text(encoding='utf8'))
    for val in [True,'1',None,-1,256,1.5]:
        v=copy.deepcopy(source);v['objectData']['objectID']=val
        try:validate('open',v)
        except ValueError:count+=1
        else:raise AssertionError('invalid objectID accepted')
    v=copy.deepcopy(source);del v['objectData']['objectID']
    try:validate('open',v)
    except ValueError:count+=1
    else:raise AssertionError('missing mandatory field accepted')
    v=copy.deepcopy(source);del v['tailLampIntensity'];del v['objectData']['reliability'];assert validate('open',v);count+=1
    v=copy.deepcopy(source);del v['weatherData']
    try:validate('open',v)
    except ValueError:count+=1
    else:raise AssertionError('mandatory weatherData accepted when missing')
    v=copy.deepcopy(source);v['objectData']['refPosition']={};assert validate('open',v);count+=1
    for raw in ['{"a":1,"a":2}','{"a":NaN}']:
        try:strict_json(raw)
        except ValueError:count+=1
        else:raise AssertionError('ambiguous JSON accepted')
    assert decode(base64.b64encode(json.dumps(source).encode()),'open','base64-json')==source;count+=1
    return count

def audit(work,expected):
    result=json.loads((work/'result/result.json').read_text(encoding='utf8'));assert result['verdict']==expected,result
    events=[json.loads(l) for l in (work/'result/events.jsonl').read_text(encoding='utf8').splitlines()]
    states=[e for e in events if e['kind']=='state'];assert all(e['value']!='COMPLETE' for e in states)
    assert [e['value'] for e in states if e['testName']=='MainScenario']==['START',expected,'FINISH']
    assert events[-1]['value']=='FINISH'
    for row in result['items']:
        actual=[e['value'] for e in states if e['testName']==row['test']]
        assert actual==([] if row['verdict']=='NOT_RUN' else ['START',row['verdict']])
    records=[json.loads(l) for l in (work/'result/records.jsonl').read_text(encoding='utf8').splitlines()]
    assert len(records)==result['observations'] and [x['sequence'] for x in records]==list(range(1,len(records)+1))
    displayed=[];parts=[]
    for e in events:
        if e['kind']!='info' or 'data' not in e:continue
        v=json.loads(e['data'])
        if v.get('자료 구분')=='분할 자료':
            parts.append(v)
            if v['분할 번호']==v['전체 분할 수']:
                assert [p['분할 번호'] for p in parts]==list(range(1,len(parts)+1));displayed.append(json.loads(''.join(p['분할 데이터'] for p in parts)));parts=[]
        else:displayed.append(v)
    assert not parts
    if result.get('presentationVersion',1)>=2:assert len([v for v in displayed if v.get('자료 구분')=='송수신 데이터'])==result['messages']
    else:assert len([v for v in displayed if v.get('자료 구분')=='Kafka 관측'])==len(records)
    if expected=='SUCCESS':
        peers=[json.loads(l) for l in (work/'peer-records.jsonl').read_text(encoding='utf8').splitlines()]
        wire=[r for r in records if r['event'] in ('업무 value 수신','업무 value 발행 시도')]
        remote=[r for r in peers if r['event'] in ('published','received')]
        assert len(wire)==len(remote)==result['messages']
        for a,b in zip(wire,remote):assert (a['runId'],a['testName'],a['round'],a['sha256'],a['valueBase64'])==(b['runId'],b['testName'],b['round'],b['sha256'],b['valueBase64'])
    return dict(case=result['case'],verdict=expected,items=len(result['items']),messages=result['messages'],observations=len(records),work=str(work))

def run_case(out,case,broker,fault='none',encoding='json',cancel=False,sync=True):
    ident=uuid.uuid4().hex[:10];work=out/(case+'-'+fault+'-'+encoding+'-'+ident);work.mkdir()
    c=json.loads((ROOT/'registration'/(case+'.example.json')).read_text(encoding='utf8'))
    c.update(bootstrap_servers=broker,group_id='g4-'+ident,timeout_seconds=8,period_tolerance_seconds=.6,development_peer_sync=sync,open_encoding=encoding)
    topics=[]
    for s in CASES[case][3]:c['topic_'+s]='g4.'+ident+'.'+s;c['period_'+s]=3;topics.append(c['topic_'+s])
    if fault!='none' or encoding!='json' or cancel:
        first=items(case)[0][0]
        for k,s,m,t in items(case):c[k]=k==first
    config=work/'config.json';config.write_text(json.dumps(c,ensure_ascii=False),encoding='utf8')
    admin=AdminClient({'bootstrap.servers':broker})
    for f in admin.create_topics([NewTopic(t,1,1) for t in topics]).values():f.result()
    commands=[[sys.executable,'-X','utf8',str(ROOT/'emulator/sut.py'),'--config',str(config),'--work',str(work),'--role','producer' if CASES[case][1] else 'consumer','--fault',fault],
              [sys.executable,'-X','utf8',str(ROOT/'runtime/worker.py'),'--case',case,'--config',str(config),'--output',str(work/'result')]]
    logs=[(work/'peer.log').open('wb'),(work/'worker.log').open('wb')];procs=[]
    try:
        for cmd,log in zip(commands,logs):procs.append(subprocess.Popen(cmd,cwd=work,stdout=log,stderr=subprocess.STDOUT,creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0)))
        if cancel:time.sleep(.25);(work/'kafka-stop').write_text('stop')
        procs[1].wait(timeout=90)
        if fault=='none' and not cancel:procs[0].wait(timeout=15)
        expected='STOPPED' if cancel else 'FAIL' if fault in ('invalid-json','bad-field','no-commit','wrong-topic') else 'SUCCESS'
        value=audit(work,expected);print(json.dumps(value,ensure_ascii=False),flush=True);return value
    finally:
        for proc in procs:
            if proc.poll() is None:proc.terminate();proc.wait(timeout=5)
        for log in logs:log.close()

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--broker',required=True);p.add_argument('--output',required=True);a=p.parse_args();out=Path(a.output).resolve();out.mkdir(exist_ok=False)
    checks=check_fields();results=[run_case(out,c,a.broker) for c in CASES]
    results += [run_case(out,'ut2platform_kafka_v1',a.broker,fault=f) for f in ['invalid-json','bad-field']]
    results += [run_case(out,'platform2ut_kafka_v1',a.broker,fault='no-commit'),run_case(out,'ut2platform_kafka_v1',a.broker,encoding='base64-json'),run_case(out,'platform2ut_kafka_v1',a.broker,encoding='base64-json'),run_case(out,'ut2i2x_kafka_v1',a.broker,cancel=True)]
    (out/'verification.json').write_text(json.dumps(dict(fieldChecks=checks,runs=results),ensure_ascii=False,indent=2),encoding='utf8')
