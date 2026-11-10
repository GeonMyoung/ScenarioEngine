"""Mutate copies of real runs to exercise false-pass boundaries in review."""
import argparse
import copy
import hashlib
from decimal import Decimal
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from evidence_values import loads, read_json, read_events, same_value, same_rows, EvidenceError
from review_method_evidence import review


def exact_json(value):
    if isinstance(value,Decimal):return str(value)
    if isinstance(value,dict):return '{'+','.join(json.dumps(k)+':'+exact_json(v) for k,v in value.items())+'}'
    if isinstance(value,list):return '['+','.join(exact_json(v) for v in value)+']'
    return json.dumps(value,ensure_ascii=False,allow_nan=False)


class Copy:
    def __init__(self,root,report):
        root.mkdir(parents=True,exist_ok=False)
        self.root=root;self.t=root/'t';self.s=root/'s'
        shutil.copytree(report.parent,self.t);shutil.copytree(report.parent.parent.parent/'sut',self.s)
        self.report=read_json(self.t/'result.json');self.source=read_events(self.t/'events.jsonl');self.peer=read_events(self.s/'events.jsonl')
        self.stored=read_json(self.s/'processed.json') if (self.s/'processed.json').exists() else None
    def save(self):
        (self.t/'result.json').write_text(exact_json(self.report),encoding='utf8')
        for path,data in [(self.t/'events.jsonl',self.source),(self.s/'events.jsonl',self.peer)]:
            path.write_text(''.join(exact_json(x)+'\n' for x in data),encoding='utf8')
        if self.stored is not None:(self.s/'processed.json').write_text(exact_json(self.stored),encoding='utf8')
    def event(self,name,peer=False):return next(e for e in (self.peer if peer else self.source) if e['event']==name)
    def processed(self,field,value):
        self.event('application_processed',True)['records'][0][field]=value
        self.stored[0]['records'][0][field]=value


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--baseline',type=Path,required=True);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--additional-only',action='store_true')
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    baseline=read_json(args.baseline)
    def original(case,kind='all'):return Path(next(x['report'] for x in baseline if x['case']==case and x['kind']==kind))
    request=original('centerServer2micro_v1');provider=original('microClient2center_v1');absence=original('microClient2center_v1','absent')
    results=[]
    def scalar(name,left,right,expected,unordered=False):
        actual=(same_rows if unordered else same_value)(loads(left),loads(right))
        results.append(dict(name=name,kind='comparison',passed=actual==expected))
    scalar('number-not-boolean','[{"laneNo":1}]','[{"laneNo":true}]',False,True)
    scalar('decimal-not-rounded','[{"spd":52.350000000000001}]','[{"spd":52.35}]',False,True)
    scalar('decimal-context-precision','0.1234567890123456789012345678901','0.1234567890123456789012345678902',False)
    scalar('large-integer','100000000000000000000000000000000001','100000000000000000000000000000000000',False)
    scalar('trailing-zeroes','52.3500','52.35',True)
    scalar('exponent-number','5235e-2','52.35',True)
    scalar('integer-number','1','1.0000',True)
    scalar('number-not-string','1','"1"',False)
    scalar('null-not-zero','null','0',False)
    scalar('signed-zero','-0.0000','0',True)
    scalar('field-order','{"b":2,"a":1}','{"a":1,"b":2}',True)
    scalar('row-order','[{"a":1},{"a":2}]','[{"a":2},{"a":1}]',True,True)
    scalar('row-multiplicity','[{"a":1},{"a":1}]','[{"a":1}]',False,True)
    scalar('nested-array-order','[{"a":[1,2]}]','[{"a":[2,1]}]',False,True)
    scalar('nested-type','{"request":{"enabled":true}}','{"request":{"enabled":1}}',False)
    for name,raw in [('duplicate-json','{"a":1,"a":2}'),('nan','NaN'),('infinity','Infinity')]:
        try:loads(raw);passed=False
        except EvidenceError:passed=True
        results.append(dict(name=name,kind='parser',passed=passed))

    mutations=[]
    def add(name,fn,base=request,expected=False):mutations.append((name,fn,base,expected))
    add('processed-number-as-bool',lambda d:d.processed('laneNo',True))
    add('processed-fine-decimal',lambda d:d.processed('spd',Decimal('52.350000000000001')))
    add('processed-number-as-string',lambda d:d.processed('laneNo','1'))
    add('stored-only-wrong-value',lambda d:d.stored[0]['records'][0].update(vol=999))
    add('processed-missing-row',lambda d:d.event('application_processed',True).update(records=[]))
    add('processed-duplicate-row',lambda d:d.stored[0]['records'].append(copy.deepcopy(d.stored[0]['records'][0])))
    add('same-numeric-value',lambda d:d.processed('laneNo',Decimal('1.00')),expected=True)
    add('same-decimal-spelling',lambda d:d.processed('spd',Decimal('52.35000')),expected=True)
    add('missing-processing',lambda d:d.peer.remove(d.event('application_processed',True)))
    add('duplicate-processing',lambda d:d.peer.append(copy.deepcopy(d.event('application_processed',True))))
    add('duplicate-stored',lambda d:d.stored.append(copy.deepcopy(d.stored[0])))
    add('missing-response',lambda d:d.source.remove(d.event('response_sent')))
    add('duplicate-source-response',lambda d:d.source.append(copy.deepcopy(d.event('response_sent'))))
    add('duplicate-peer-response',lambda d:d.peer.append(copy.deepcopy(d.event('response_received',True))))
    add('missing-request',lambda d:d.source.remove(d.event('request')))
    add('duplicate-request',lambda d:d.source.insert(4,copy.deepcopy(d.event('request'))))
    add('wrong-response-test',lambda d:d.event('response_sent').update(test='test_empty_response'))
    add('wrong-request-test',lambda d:d.event('request').update(test='test_empty_response'))
    add('wrong-iteration',lambda d:d.event('response_sent').update(iteration=2))
    add('boolean-exchange',lambda d:d.event('response_sent').update(exchange=True))
    add('boolean-iteration',lambda d:d.event('response_sent').update(iteration=True))
    add('wrong-response-check',lambda d:d.event('response_sent').update(validation='empty'))
    add('wrong-response-expectation',lambda d:d.event('response_sent').update(expectedStatus=404))
    add('wrong-start-check',lambda d:d.event('item_start').update(validation='empty'))
    add('wrong-finish-count',lambda d:d.event('item_result').update(completedExchanges=9))
    add('wrong-summary-count',lambda d:d.report['items'][0].update(completedExchanges=9))
    add('missing-item-start',lambda d:d.source.remove(d.event('item_start')))
    add('missing-item-finish',lambda d:d.source.remove(d.event('item_result')))
    add('missing-final',lambda d:d.source.pop())
    add('wrong-final',lambda d:d.event('result').update(verdict='SUCCESS'))
    add('wrong-peer-run',lambda d:d.event('response_received',True).update(runId='other-run'))
    add('wrong-source-run',lambda d:d.event('request').update(runId='other-run'))
    add('reused-request-number',lambda d:[e.update(requestNumber=1) for e in d.peer if e['event']=='response_received' and e['exchange']==2])
    add('wrong-stored-request',lambda d:d.stored[0].update(requestNumber=2))
    add('wrong-target-role',lambda d:d.report.update(sutRole='provider'))
    add('unknown-selection',lambda d:d.report['items'][0].update(test='test_unknown'))
    add('duplicate-selection',lambda d:d.report['items'].append(copy.deepcopy(d.report['items'][0])))
    add('wrong-classification',lambda d:d.report['items'][0].update(classification='supplementary'))
    add('lookup-wrong-test',lambda d:d.event('data_lookup').update(test='test_empty_response'))
    add('lookup-missing',lambda d:d.source.remove(d.event('data_lookup')))
    add('lookup-duplicate',lambda d:d.source.insert(5,copy.deepcopy(d.event('data_lookup'))))
    add('lookup-boolean-count',lambda d:d.event('data_lookup').update(recordCount=True))
    add('response-before-request',lambda d:d.event('response_sent').update(monotonicUs=0))
    add('processing-before-receipt',lambda d:d.event('application_processed',True).update(monotonicUs=0))
    add('peer-request-missing',lambda d:d.peer.remove(d.event('request_sent',True)))
    add('peer-request-duplicate',lambda d:d.peer.append(copy.deepcopy(d.event('request_sent',True))))
    add('wrong-provider-stimulus',lambda d:d.event('request',True).update(queryNames=['unsupported']),provider)
    add('provider-missing-response',lambda d:d.peer.remove(d.event('response_sent',True)),provider)
    add('provider-invalid-query-count',lambda d:d.event('request').update(queryCount=1),provider)
    add('absence-labelled-normal',lambda d:d.report['items'][0].update(test='test_normal_vds'),absence)
    add('absence-labelled-normal-coherent-summary',lambda d:d.report['items'][0].update(test='test_normal_vds',validation='normal',expectedStatus=200,verdict='SUCCESS'),absence)
    add('automatic-fail-preserved',lambda d:d.report.update(automaticVerdict='FAIL'))
    add('automatic-stop-preserved',lambda d:d.report.update(automaticVerdict='STOPPED'))
    add('not-run-preserved',lambda d:d.report['items'][0].update(verdict='NOT_RUN'))
    original_count=len(mutations)
    def source_value(d):
        source=read_json(d.s/'source-data.body');source[0]['spd']=Decimal('52.350000000000001')
        body=exact_json(source).encode();digest=hashlib.sha256(body).hexdigest()
        (d.s/'source-data.body').write_bytes(body)
        prep=read_json(d.s/'preparation.json');prep['sourceSha256']=digest
        (d.s/'preparation.json').write_text(exact_json(prep),encoding='utf8')
        for e in d.peer:
            if e['event']=='data_lookup':e['sourceSha256']=digest
    def prepare_value(d):
        pre=d.event('precondition');p=d.t/pre['sourceFile'];source=read_json(p);source[0]['vol']=999
        body=exact_json(source).encode();p.write_bytes(body);digest=hashlib.sha256(body).hexdigest();pre['sourceSha256']=digest
        for e in d.source:
            if e['event']=='data_lookup' and e['test']==pre['test']:e['sourceSha256']=digest
    def error_nested_value(d):
        process=next(e for e in d.peer if e['event']=='application_processed' and e['action']=='error-schema');n=process['exchange']
        value=read_json(d.t/f'response-{n}.body');value['request']={'enabled':1};body=exact_json(value).encode();digest=hashlib.sha256(body).hexdigest()
        (d.t/f'response-{n}.body').write_bytes(body);(d.s/f'response-{n}.body').write_bytes(body)
        for e in d.source+d.peer+d.stored:
            if e.get('exchange')==n and 'bodySha256' in e:e['bodySha256']=digest
        process['errorDetails']=copy.deepcopy(value);process['errorDetails']['request']['enabled']=True
        stored=next(e for e in d.stored if e['exchange']==n);stored['errorDetails']=copy.deepcopy(process['errorDetails'])
    add('prepared-provider-fine-decimal',source_value,provider)
    add('prepared-tester-value-differs',prepare_value)
    add('nested-error-number-as-bool',error_nested_value)
    add('schema-downgrade',lambda d:d.report.update(schemaVersion=2),provider)
    add('wrong-data-profile',lambda d:d.report.update(profile='SMART-STANDARD-001'))
    add('provider-missing-request-run',lambda d:d.event('request',True).pop('runId'),provider)
    add('received-request-body-mismatch',lambda d:(d.t/'request-1.body').write_bytes(b'not empty'))
    if args.additional_only:mutations=mutations[original_count:];results=[]
    copies=[]
    for i,(name,mutate,base,expected_pass) in enumerate(mutations):
        d=Copy(out/f'{i:02d}',base);mutate(d);d.save();copies.append(d)
        try:result=review(d.t/'result.json',d.s);actual=True;reason='PASS'
        except (AssertionError,ValueError,KeyError,TypeError,OSError) as e:actual=False;reason=str(e)
        result=dict(name=name,kind='evidence-copy',expected=expected_pass,actual=actual,passed=actual==expected_pass,reason=reason)
        results.append(result)
        if not result['passed']:print('FAIL',result,flush=True)
    # Assertions must not disappear under Python optimization. Exercise the
    # public CLI and confirm a failure artifact, not a successful review.
    d=copies[0]
    command=[sys.executable,'-O','-X','utf8',str(ROOT/'tools/review_method_evidence.py'),'--report',str(d.t/'result.json'),'--sut',str(d.s),'--output',str(out/'optimized-cli.json')]
    p=subprocess.run(command,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=15,creationflags=subprocess.CREATE_NO_WINDOW)
    result=read_json(out/'optimized-cli.json')
    results.append(dict(name='optimized-cli-rejects-false-pass',kind='cli',passed=p.returncode==1 and result['developmentVerification']=='FAIL'))
    summary=dict(checks=len(results),passed=sum(r['passed'] for r in results),results=results)
    (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
    print('Evidence boundary checks:',summary['passed'],'/',summary['checks'])
    return 0 if all(r['passed'] for r in results) else 1


if __name__=='__main__':raise SystemExit(main())
