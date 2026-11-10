"""Correlate UTIC tester reports with independently recorded SUT processing."""
import argparse
import hashlib
import json
from pathlib import Path
import xml.etree.ElementTree as ET


def review(report_path, sut_directory):
    report=json.loads(Path(report_path).read_text(encoding='utf-8'))
    sut_directory=Path(sut_directory)
    events=[json.loads(line) for line in (sut_directory/'events.jsonl').read_text(encoding='utf-8').splitlines() if line]
    stored=json.loads((sut_directory/'processed-records.json').read_text(encoding='utf-8'))
    assert report['automaticVerdict']=='EVIDENCE_PENDING', 'Automatic failure/stop cannot be overridden'
    assert report['standardConditionsMet'] and report['completedExchanges']==report['requestedExchanges']>=10
    expected=set(range(1,report['requestedExchanges']+1))
    source_path=Path(report_path).parent/'events.jsonl'
    source=[json.loads(line) for line in source_path.read_text(encoding='utf-8').splitlines() if line]
    sent=[e for e in source if e['event']=='response_sent' and e['runId']==report['runId']]
    requests=[e for e in source if e['event']=='request' and e['runId']==report['runId']]
    assert len(sent)==len(requests)==len(expected)
    assert {e['exchange'] for e in sent}=={e['exchange'] for e in requests}==expected
    assert all(e['accepted'] and e['method']=='GET' and e['path']=='/guide/imsOpenData.do' for e in requests)
    assert all(e['status']==200 and e['bodySha256']==report['responseSha256'] for e in sent)
    assert hashlib.sha256((Path(report_path).parent/'response.xml').read_bytes()).hexdigest()==report['responseSha256']
    processed=[e for e in events if e['event']=='application_processed' and e.get('runId')==report['runId']]
    assert len(processed)==len(expected) and {e['exchange'] for e in processed}==expected, 'Missing or duplicate processing evidence'
    for item in processed:
        assert item['bodySha256']==report['responseSha256']
        received=next(e for e in events if e['event']=='response_received' and e.get('runId')==report['runId'] and e['exchange']==item['exchange'])
        assert received['bodySha256']==item['bodySha256'] and received['monotonicUs']<=item['monotonicUs']
        raw=(sut_directory/f"response-{item['exchange']:04d}.xml").read_bytes()
        assert hashlib.sha256(raw).hexdigest()==item['bodySha256']
        xml=ET.fromstring(raw)
        records=[{f.tag:f.text or '' for f in r} for r in xml.findall('record')]
        record=next(r for r in stored if r['runId']==report['runId'] and r['exchange']==item['exchange'])
        assert record['records']==records and item['incidentIds']==[r['incidentId'] for r in records]
    return {'runId':report['runId'],'automaticVerdict':report['automaticVerdict'],
            'developmentVerification':'PASS','reviewMethod':'correlated_emulator_evidence',
            'verifiedExchanges':len(expected),'reportSha256':hashlib.sha256(Path(report_path).read_bytes()).hexdigest(),
            'testerEventsSha256':hashlib.sha256(source_path.read_bytes()).hexdigest(),
            'sutEvidenceSha256':hashlib.sha256((sut_directory/'events.jsonl').read_bytes()).hexdigest(),
            'note':'Original automatic result is preserved; physical SUT certification is not claimed.'}


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--report',type=Path,required=True)
    parser.add_argument('--sut',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    if args.output.exists(): parser.error('Output already exists')
    result=review(args.report,args.sut)
    args.output.write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result,ensure_ascii=False))
