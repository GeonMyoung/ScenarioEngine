"""NTIC native field boundaries and real peer exchanges."""
import argparse,hashlib,json,os,socket,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'emulator')]
from review_method_evidence import review
from ntic_fields import fixture,decode

def field_cases():
    result=[]
    def add(name,changes=None,missing=None,expected=True,root=None):
        value=json.loads(fixture());value['items'][0].update(changes or {})
        if missing:value['items'][0].pop(missing)
        if root is not None:value=root(value)
        result.append((name,json.dumps(value,ensure_ascii=False).encode(),expected))
    add('normal')
    add('metadata-optional',root=lambda x:dict(items=x['items']))
    add('boundaries',dict(vdsId='가'*10,linkIds='L'*20,laneNo=99,colctedDate='20240229235959',speed=999.99,volume=-999.99,occupancy=.01))
    for key in ['vdsId','linkIds','laneNo','colctedDate','speed','volume','occupancy']:add('missing-'+key,missing=key,expected=False)
    for key,size in [('vdsId',10),('linkIds',20)]:
        for name,value,ok in [('limit','😀'*size,True),('overflow','A'*(size+1),False),('empty','',False),('number',1,False)]:
            add(key+'-'+name,{key:value},expected=ok)
    for key in ['laneNo','speed','volume','occupancy']:
        for value in ['1',True,None]:add(key+'-type-'+str(value),{key:value},expected=False)
    for key in ['speed','volume','occupancy']:
        for value in [1000,1.001]:add(key+'-precision-'+str(value),{key:value},expected=False)
    for value in [100,1.1]:add('lane-'+str(value),{'laneNo':value},expected=False)
    for value in ['20260230000000','20260807240000','20260807176000','00000101000000','2026-08-07','２０２６０８０７１７３９００']:
        add('date-'+value,{'colctedDate':value},expected=False)
    add('count-mismatch',root=lambda x:dict(x,totalCount='2'),expected=False)
    add('count-type',root=lambda x:dict(x,totalCount=1),expected=False)
    add('business-error-on-200',root=lambda x:dict(x,resultCode='4009'),expected=False)
    add('business-code-type',root=lambda x:dict(x,resultCode=0),expected=False)
    add('wrong-envelope',root=lambda x:dict(body=x),expected=False)
    add('array-root',root=lambda x:x['items'],expected=False)
    return result

def run(exe,work,provider,phase='all',fault='none',path='/vdsInfo',encoded=False,optional=False):
    work.mkdir(parents=True,exist_ok=False)
    case='centerClient2ntic_v1' if provider else 'nticServer2center_v1'
    config=json.loads((ROOT/f'registration/{case}.example.json').read_text())
    normal='test_normal_ntic' if provider else 'test_request_ntic'
    selected=[normal,'test_invalid_request','test_missing_credential','test_wrong_credential','test_missing_path'] if provider else [normal,'test_no_data_error_response','test_response_400','test_response_404','test_response_500','test_empty_response','test_malformed_response']
    if phase=='normal':selected=[normal]
    if phase=='invalid':selected=['test_invalid_request']
    if phase=='absent':selected=['test_no_data_error'];config['confirm_data_absent']=True
    if phase=='empty':selected=['test_no_data']
    for key in config:
        if key.startswith('test_'):config[key]=key in selected
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    config.update(api_path=path,request_timeout_s=2,evidence_directory='')
    if optional:config.update(evidence_directory=str(work/'sut'),evidence_wait_s=3)
    if encoded:config['api_key']='ntic +&=%한글'
    if provider:config.update(sut_base_url=f'http://127.0.0.1:{port}',connect_timeout_s=1)
    else:config['local_port']=port
    configPath=work/'config.json';configPath.write_text(json.dumps(config,ensure_ascii=False),encoding='utf8')
    env=os.environ.copy();env['REST_TEST_CREDENTIAL']=config['api_key']
    peerArgs=[sys.executable,'-X','utf8',str(ROOT/'emulator/ntic_sut.py'),'--role','provider' if provider else 'requester','--port',str(port),'--path',path,
              '--data','absent' if phase=='absent' else 'empty' if phase=='empty' else 'normal','--requests',str(len(selected)*10),'--fault','none' if fault=='stop' else fault,'--output',str(work/'sut')]
    command=[str(exe),'--method-case',case,'--config',str(configPath)]
    if fault=='stop':command+=['--stop-after-ms','300']
    processes=[];handles=[]
    def start(args,name):
        f=(work/(name+'.log')).open('wb');handles.append(f);p=subprocess.Popen(args,cwd=work,env=env,stdout=f,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW);processes.append(p);return p
    def ready(p,name):
        until=time.monotonic()+8
        while time.monotonic()<until:
            if b'LISTENING' in (work/(name+'.log')).read_bytes():return
            if p.poll() is not None:raise RuntimeError('Ended before listening')
            time.sleep(.03)
        raise RuntimeError('Readiness timeout')
    result=dict(case=case,phase=phase,fault=fault,path=path,encodedKey=encoded,passed=False)
    try:
        if provider:peer=start(peerArgs,'peer');ready(peer,'peer')
        engine=start(command,'engine')
        if not provider and fault!='stop':ready(engine,'engine');peer=start(peerArgs,'peer')
        engine.wait(timeout=30)
        reportPath=next(work.glob('rest-results/*/result.json'));report=json.loads(reportPath.read_text(encoding='utf8'))
        expected='STOPPED' if fault=='stop' else 'SUCCESS' if fault in ['none','no-processing','reordered'] else 'FAIL'
        assert report['automaticVerdict']==expected,report
        notes=[json.loads(x) for x in (work/'notifications.jsonl').read_text(encoding='utf8').splitlines()]
        states=[x for x in notes if x['type']=='state'];assert all(x['value'] in ['START','SUCCESS','FAIL','STOPPED','FINISH'] for x in states)
        assert [x['value'] for x in states if x['test']=='MainScenario']==['START',expected,'FINISH']
        if fault in ['none','reordered']:
            if not provider:peer.wait(timeout=10)
            checked=review(reportPath,work/'sut');assert checked['verifiedExchanges']==10*len(selected)
            result['review']=checked
            payloads=[x for x in notes if x['type']=='info' and '메시지 순번' in x['data']]
            assert len(payloads)==len(selected)*20
            assert config['api_key'] not in '\n'.join(json.dumps(x,ensure_ascii=False) for x in payloads)
            if optional:
                linked=json.loads((reportPath.parent/'review-link.json').read_text(encoding='utf8'))
                assert linked['reviewStatus']=='PASS' and linked['finalVerdict']=='SUCCESS'
                result['optionalReview']='PASS'
        if fault=='no-processing':
            peer.wait(timeout=10)
            try:review(reportPath,work/'sut')
            except (AssertionError,OSError):pass
            else:raise AssertionError('Missing peer processing was accepted')
        result.update(passed=True,actual=report['automaticVerdict'],items=len(selected),exchanges=report['completedExchanges'],report=str(reportPath))
    except Exception as e:result['error']=repr(e)
    finally:
        for p in processes:
            if p.poll() is None:p.terminate()
            p.wait(timeout=5)
        for f in handles:f.close()
    (work/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8');return result

def main():
    p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--only',choices=['fields','wire','all'],default='all');a=p.parse_args()
    out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();results=[]
    if a.only!='wire':
        for i,(name,body,expected) in enumerate(field_cases()):
            f=out/f'f{i}.json';f.write_bytes(body)
            native=subprocess.run([str(exe),'--validate-ntic','--config',str(f)],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=10,creationflags=subprocess.CREATE_NO_WINDOW)
            try:decode(body);peer=True
            except (ValueError,UnicodeError):peer=False
            results.append(dict(kind='field',name=name,expected=expected,native=native.returncode==0,peer=peer,passed=(native.returncode==0)==peer==expected))
    if a.only!='fields':
        jobs=[(False,'all','none','/vdsInfo',False),(True,'all','none','/vdsInfo',False),(True,'absent','none','/vdsInfo',False),(True,'empty','none','/vdsInfo',False)]
        for provider in [False,True]:jobs.extend([(provider,'normal','none','//vdsInfo',False),(provider,'normal','none','/vdsInfo',True)])
        for fault in ['numeric-strings','wide-id','bad-date','precision','envelope','count','delay']:jobs.append((True,'normal',fault,'/vdsInfo',False))
        for fault in ['wrong-code','wrong-business']:jobs.append((True,'invalid',fault,'/vdsInfo',False))
        for fault in ['missing-gettype','wrong-gettype','duplicate-key','body','wrong-path','wrong-key','method','stop','no-processing']:jobs.append((False,'normal',fault,'/vdsInfo',False))
        for i,job in enumerate(jobs):
            result=run(exe,out/str(i),*job);results.append(result);print(i,job,'PASS' if result['passed'] else result.get('error'),flush=True)
    summary=dict(checks=len(results),passed=sum(x['passed'] for x in results),results=results)
    (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
    for r in results:
        if not r['passed']:print('FAIL',r)
    print('NTIC checks:',summary['passed'],'/',summary['checks'])
    return 0 if all(x['passed'] for x in results) else 1
if __name__=='__main__':raise SystemExit(main())
