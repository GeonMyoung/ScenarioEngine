"""Correlate SC32 HTTP transmissions and independently recorded SUT processing."""
import argparse,hashlib,json
from pathlib import Path
from evidence_values import loads, same_rows, require

def review(report_path,sut_directory):
    report_path=Path(report_path);sut=Path(sut_directory)
    report=loads(report_path.read_text(encoding='utf8'));run=report['runId']
    require(report['case']=='centerServer2micro_v1' and report['automaticVerdict']=='EVIDENCE_PENDING', 'Failure/stop cannot be overridden')
    require(report['completedExchanges']==report['requestedExchanges']>=10, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
    expected=set(range(1,report['requestedExchanges']+1));digest=report['responseSha256']
    raw=(report_path.parent/'response.json').read_bytes();require(hashlib.sha256(raw).hexdigest()==digest, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
    values=loads(raw);require(len(values)==report['recordCount']>0, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
    source=[loads(x) for x in (report_path.parent/'events.jsonl').read_text(encoding='utf8').splitlines()]
    peer=[loads(x) for x in (sut/'events.jsonl').read_text(encoding='utf8').splitlines()]
    stored=loads((sut/'processed-records.json').read_text(encoding='utf8'))
    def group(rows,event):
        selected=[x for x in rows if x.get('runId')==run and x['event']==event]
        require(len(selected)==len(expected) and {x['exchange'] for x in selected}==expected, 'Missing/duplicate '+event)
        return {x['exchange']:x for x in selected}
    requests=group(source,'request');sent=group(source,'response_sent');received=group(peer,'response_received');processed=group(peer,'application_processed')
    require(len(stored)==len(expected) and {x['exchange'] for x in stored}==expected, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
    for n in expected:
        q=requests[n];require(q['accepted'] and q['method']=='GET' and q['path']=='/v1/adxc/vds-l-raws' and q['queryCount']==q['bodyBytes']==0 and q['authorizationCount']==1, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        require(sent[n]['status']==received[n]['status']==200, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        require(sent[n]['bodySha256']==received[n]['bodySha256']==processed[n]['bodySha256']==digest, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        require(received[n]['monotonicUs']<=processed[n]['monotonicUs'], '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        require(hashlib.sha256((sut/f'response-{n:04d}.json').read_bytes()).hexdigest()==digest, '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        record=next(x for x in stored if x['exchange']==n)
        require(record['runId']==run and record['bodySha256']==digest and same_rows(record['records'],values), '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
        require(processed[n]['recordCount']==len(values) and processed[n]['stationIds']==[x['stnId'] for x in values], '기존 VDS 시험의 송수신·처리 증적이 일치하지 않습니다.')
    return dict(runId=run,automaticVerdict='EVIDENCE_PENDING',developmentVerification='PASS',reviewMethod='correlated_emulator_evidence',verifiedExchanges=len(expected),reportSha256=hashlib.sha256(report_path.read_bytes()).hexdigest(),sutEvidenceSha256=hashlib.sha256((sut/'events.jsonl').read_bytes()).hexdigest())

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--report',type=Path,required=True);p.add_argument('--sut',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
    if a.output.exists():p.error('Output already exists')
    result=review(a.report,a.sut);a.output.write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8');print(json.dumps(result))
