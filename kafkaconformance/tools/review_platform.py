"""Compare worker, independent SUT, engine ACKs, progress view and saved report."""
import argparse,ast,collections,json,re
from pathlib import Path

def assemble(values):
    logical=[];pending=[]
    for v in values:
        if v.get('자료 구분')!='분할 자료':logical.append(v);continue
        pending.append(v)
        if v['분할 번호']==v['전체 분할 수']:
            assert [p['분할 번호'] for p in pending]==list(range(1,len(pending)+1))
            assert all(p.get('자료 번호',p.get('원자료 순번'))==pending[0].get('자료 번호',pending[0].get('원자료 순번')) for p in pending)
            logical.append(json.loads(''.join(p['분할 데이터'] for p in pending)));pending=[]
    assert not pending
    return logical

def states_from_native(work):
    path=work/'engine.log'
    if not path.exists():path=work/'engine-stdout.log'
    text=path.read_bytes().decode('latin1');text=re.sub(r'(?m)^\[[^\r\n]+\] ','',text)
    states=[]
    for size,block in re.findall(r'(?ms)^@@@ TEXT Frame = \{ (\d+) Byte\r?\n(.*?)^\}\r?$',text):
        if int(size)>2048:continue
        data=bytearray();rows=list(re.finditer(r'(?m)^\s*([0-9A-Fa-f]{8})\s*:',block))
        try:
            for i,row in enumerate(rows):
                assert int(row[1],16)==len(data)
                cell=block[row.end():rows[i+1].start() if i+1<len(rows) else len(block)].split(':',1)[0];data.extend(bytes.fromhex(cell.strip()))
            assert len(data)==int(size)
            n=data[1]&127;off=2
            if n==126:n=int.from_bytes(data[2:4],'big');off=4
            elif n==127:n=int.from_bytes(data[2:10],'big');off=10
            key=data[off:off+4];off+=4;payload=bytes(b^key[i%4] for i,b in enumerate(data[off:off+n]));m=json.loads(payload)
        except (AssertionError,ValueError,IndexError,UnicodeError):continue
        if m.get('method')=='NOTIFY' and m.get('level')=='state' and m['data'].get('state'):states.append(m)
    acks=set()
    for block in re.findall(r'(?ms)^Received Message = \{\r?\n(.*?)^\}\r?$',text):
        seq=re.search(r'\bseq = [0-9A-Fa-f]+\((\d+)\)',block)
        if seq and 'code = OK(200)' in block and 'method = [' not in block:acks.add(int(seq[1]))
    assert states and all(s['seq'] in acks for s in states),'native state missing server ACK'
    return [m['data'] for m in states]

def review(job):
    work=Path(job['work']);results=list(work.glob('kafka-results/*/result.json'));assert len(results)==1
    result=json.loads(results[0].read_text(encoding='utf8'));events=[json.loads(l) for l in (results[0].parent/'events.jsonl').read_text(encoding='utf8').splitlines()]
    records=[json.loads(l) for l in (results[0].parent/'records.jsonl').read_text(encoding='utf8').splitlines()]
    expected=job.get('expectedVerdict','SUCCESS');assert result['verdict']==expected and result['case']==job['case']
    states=states_from_native(work)
    assert [s['state'] for s in states if s['testName']=='MainScenario']==['START',expected,'FINISH']
    for item in result['items']:
        assert [s['state'] for s in states if s['testName']==item['test']]==([] if item['verdict']=='NOT_RUN' else ['START',item['verdict']])
        if expected=='SUCCESS':assert item['verdict']=='SUCCESS' and item['completed']==item['requested']
    assert not any(s['state']=='COMPLETE' for s in states)
    delivery=json.loads((work/'kafka-delivery.json').read_text());assert delivery['pending']==delivery['error']==delivery['discarded']==0
    display=json.loads((work/'platform.json').read_text(encoding='utf8'));shown=list(reversed(display['data']))
    expected_data=[json.loads(e['data']) for e in events if e['kind']=='info' and 'data' in e]
    assert shown==expected_data,'progress attachment lost or reordered'
    logical=assemble(shown)
    if result.get('presentationVersion',1)>=2:
        assert len([v for v in logical if v.get('자료 구분')=='송수신 데이터'])==result['messages']
        assert len([v for v in logical if v.get('자료 구분')=='시험 안내'])==len([i for i in result['items'] if i['verdict']!='NOT_RUN'])
    else:assert len([v for v in logical if v.get('자료 구분')=='Kafka 관측'])==len(records)==result['observations']
    stored=json.loads((work/'report.json').read_text(encoding='utf8'));report=[ast.literal_eval(x) for x in stored['data']]
    wanted=[json.loads(e['data']) for e in events if e['kind']=='info' and 'data' in e and e['testName']!='MainScenario']
    canonical=lambda x:json.dumps(x,sort_keys=True,ensure_ascii=False)
    counts=collections.Counter(map(canonical,report));expected_counts=collections.Counter(map(canonical,wanted))
    assert counts.keys()==expected_counts.keys(),'saved report has missing/extra attachments'
    copies={counts[k]//v for k,v in expected_counts.items()};assert len(copies)==1 and next(iter(copies))>=1
    multiplicity=next(iter(copies));assert counts==collections.Counter({k:v*multiplicity for k,v in expected_counts.items()})
    peers=[json.loads(l) for l in (work/'peer-records.jsonl').read_text(encoding='utf8').splitlines()]
    wire=[r for r in records if r['event'] in ('업무 value 수신','업무 value 발행 시도')]
    peer_wire=[r for r in peers if r['event'] in ('published','received')]
    if expected=='SUCCESS':
        assert len(wire)==len(peer_wire)==result['messages']
        for a,b in zip(wire,peer_wire):
            assert (a['runId'],a['testName'],a['round'],a['topic'],a['sha256'],a['valueBase64'])==(b['runId'],b['testName'],b['round'],b['topic'],b['sha256'],b['valueBase64'])
            if not job['provider']:assert b['processed'] is True
    periods=[r for r in records if r['event']=='주기 관측']
    for p in periods:assert abs(p['actualSeconds']-p['expectedSeconds'])<=p['toleranceSeconds']
    audit=dict(case=result['case'],designId=job['designId'],platformId=job['platformId'],job=job['job'],channel=job['channel'],runId=result['runId'],verdict=result['verdict'],items=len(result['items']),messages=result['messages'],observations=result['observations'],displayParts=len(expected_data),reportCopies=multiplicity,reportUrl=stored['url'],allStateNotificationsAcknowledged=True,states=states,periods=periods,defaultTiming=all(i['defaultTiming'] is True for i in result['items'] if i['mode']=='period'),peerWireEqual=expected=='SUCCESS',passed=True)
    (work/'audit.json').write_text(json.dumps(audit,ensure_ascii=False,indent=2),encoding='utf8');return audit

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('jobs');p.add_argument('indices',type=int,nargs='*');a=p.parse_args();jobs=json.loads(Path(a.jobs).read_text(encoding='utf8'))
    results=[review(jobs[i]) for i in a.indices or range(len(jobs))];print(json.dumps(results,ensure_ascii=False,indent=2))
