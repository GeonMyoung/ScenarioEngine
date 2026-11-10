"""Native engine -> independent peer -> review worker -> result/notification."""
import argparse,hashlib,json,os,shutil,socket,subprocess,sys,time
from pathlib import Path
from verify_method import CASES
ROOT=Path(__file__).resolve().parents[1]


def run(exe,work,case,kind='all',fault='none',mode='normal'):
    work.mkdir(parents=True,exist_ok=False);fmt,provider,normal=CASES[case]
    config=json.loads((ROOT/f'registration/{case}.example.json').read_text(encoding='utf8'))
    for key in list(config):
        if key.startswith('test_'):config[key]=False
    tests=[normal,'test_invalid_request','test_missing_credential','test_wrong_credential','test_missing_path'] if provider else [normal,'test_no_data_error_response','test_response_400','test_response_404','test_response_500','test_empty_response','test_malformed_response']
    if kind=='normal':tests=[normal]
    if kind=='absent':tests=['test_no_data_error'] if provider else ['test_no_data_error_response'];config.update(confirm_data_absent=True,no_data_error_status=404)
    if kind=='empty':tests=['test_no_data'];config['no_data_status']=200
    for key in tests:config[key]=True
    with socket.socket() as sock:sock.bind(('127.0.0.1',0));port=sock.getsockname()[1]
    config.update(repetitions=10,request_timeout_s=3,evidence_directory=str(work/'sut'),evidence_wait_s=2)
    if provider:config.update(sut_base_url=f'http://127.0.0.1:{port}',connect_timeout_s=1)
    else:config['local_port']=port
    if mode in ('missing','stop-review'):config.update(evidence_directory=str(work/'not ready 한글'),evidence_wait_s=5 if mode=='stop-review' else 1)
    if mode=='not-requested':config['evidence_directory']=''
    if mode=='wrong-run':
        stale=work/'old';stale.mkdir();config['evidence_directory']=str(stale)
        (stale/'events.jsonl').write_text(json.dumps(dict(event='response_sent' if provider else 'response_received',runId='older-run'))+'\n',encoding='utf8')
    runtime=exe
    if mode in ('no-runtime','wrong-binding'):
        binpath=work/'runtime';binpath.mkdir();runtime=binpath/exe.name;shutil.copy2(exe,runtime)
        for dll in exe.parent.glob('*.dll'):shutil.copy2(dll,binpath/dll.name)
        if mode=='wrong-binding':
            worker=binpath/'rest-review';worker.mkdir()
            (binpath/'rest-review-runtime.json').write_text(json.dumps(dict(schemaVersion=1,pythonExecutable=sys.executable,worker='rest-review/engine_review_worker.py')),encoding='utf8')
            (worker/'engine_review_worker.py').write_text("import json,sys\np=sys.argv[sys.argv.index('--output')+1]\nopen(p,'x').write(json.dumps({'schemaVersion':1,'integrationProfile':'REST-REVIEW-LINK-001','runId':'other-run','reviewStatus':'PASS','finalVerdict':'SUCCESS'}))\n",encoding='utf8')
    (work/'config.json').write_text(json.dumps(config,ensure_ascii=False),encoding='utf8')
    env=os.environ.copy();env['REST_TEST_CREDENTIAL']=config['api_key' if fmt=='xml' else 'bearer_token']
    peer_command=[sys.executable,'-X','utf8',str(ROOT/'emulator/rest_method_sut.py'),'--role','provider' if provider else 'requester','--format',fmt,
                  '--port',str(port),'--output',str(work/'sut'),'--requests',str(len(tests)*10),'--data','absent' if kind=='absent' and fault!='fake-absence' else 'empty' if kind=='empty' else 'normal','--fault',fault]
    if '_smart_' in case:peer_command+=['--information','smart']
    command=[str(runtime),'--method-case',case,'--config',str(work/'config.json')]
    if mode=='stop-review':command+=['--stop-after-ms','1000']
    handles=[];processes=[]
    def start(cmd,label):
        handle=(work/(label+'.log')).open('wb');handles.append(handle)
        proc=subprocess.Popen(cmd,cwd=work,env=env,stdout=handle,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW);processes.append(proc);return proc
    def ready(label,proc):
        until=time.monotonic()+10
        while time.monotonic()<until:
            if b'LISTENING' in (work/(label+'.log')).read_bytes():return
            if proc.poll() is not None:raise RuntimeError(label+' ended before listening')
            time.sleep(.03)
        raise RuntimeError('Readiness timeout')
    result=dict(case=case,kind=kind,fault=fault,mode=mode,passed=False)
    try:
        if provider:peer=start(peer_command,'peer');ready('peer',peer)
        started=time.monotonic();engine=start(command,'engine')
        if not provider:ready('engine',engine);peer=start(peer_command,'peer')
        engine.wait(timeout=30)
        if not provider:peer.wait(timeout=10)
        reportPath=next(work.glob('rest-results/*/result.json'));raw=reportPath.read_bytes();native=json.loads(raw)
        linkedPath=reportPath.parent/'review-link.json';linked=json.loads(linkedPath.read_text(encoding='utf8'))
        assert linked['runId']==native['runId'] and linked['case']==case and linked['automaticResultSha256']==hashlib.sha256(raw).hexdigest()
        assert linked['automaticVerdict']==native['automaticVerdict']
        notes=[json.loads(x) for x in (work/'notifications.jsonl').read_text(encoding='utf8').splitlines()]
        evidence=[x for x in notes if x['type']=='info' and x['data'].get('자료 구분')=='증적 검토 결과']
        main=[x for x in notes if x['type']=='info' and x['data'].get('자료 구분')=='전체 증적 검토 결과']
        assert len(evidence)==len(tests) and len(main)==1
        assert all(x['data']['실행 ID']==native['runId'] for x in evidence+main)
        expected_status='PASS';expected_final='SUCCESS'
        if mode in ('missing','wrong-run') or fault in ('no-processing',):expected_status='NOT_CONFIRMED'
        if mode in ('no-runtime','wrong-binding'):expected_status='UNAVAILABLE'
        if mode=='not-requested':expected_status='NOT_REQUESTED'
        if mode=='stop-review':expected_status='STOPPED';expected_final='STOPPED';assert time.monotonic()-started<5 and native['automaticVerdict']=='SUCCESS'
        if fault in ('wrong-valid-data','fake-absence','no-error-log'):expected_status='FAIL';expected_final='FAIL'
        if fault=='wrong-code':expected_status='SKIPPED';expected_final='FAIL';assert linked['items'][0]['automaticVerdict']=='SUCCESS' and linked['items'][0]['finalVerdict']=='SUCCESS'
        assert linked['reviewStatus']==expected_status and linked['finalVerdict']==expected_final,linked
        assert engine.returncode==(3 if expected_final=='STOPPED' else 2 if expected_final=='FAIL' else 0)
        assert native['schemaVersion']==4 and native['assessmentProfile']=='REST-AUTO-001'
        assert native['assessmentScope']=='ENGINE_OBSERVABLE' and all(i['unobserved'] for i in native['items'])
        states=[x for x in notes if x['type']=='state']
        assert all(x['value'] in ['START','SUCCESS','FAIL','STOPPED','FINISH'] for x in states)
        assert [x['value'] for x in states if x['test']=='MainScenario']==['START',expected_final,'FINISH']
        assert all(x['test']=='MainScenario' for x in states if x['value']=='FINISH')
        for i in linked['items']:
            actual=[x['value'] for x in states if x['test']==i['test']]
            assert actual==([] if i['automaticVerdict']=='NOT_RUN' else ['START',i['finalVerdict']]),(i,actual)
        if expected_status=='PASS':
            assert all(i['finalVerdict']=='SUCCESS' for i in linked['items'])
            assert linked['review']['verifiedExchanges']==len(tests)*10
            assert all(any(x['type']=='state' and x['test']==i['test'] and x['value']=='SUCCESS' for x in notes) for i in linked['items'])
        result.update(passed=True,automaticVerdict=native['automaticVerdict'],reviewStatus=linked['reviewStatus'],finalVerdict=linked['finalVerdict'],items=len(tests),exchanges=native['completedExchanges'],report=str(reportPath),review=str(linkedPath))
    except Exception as e:result['error']=repr(e)
    finally:
        for p in processes:
            if p.poll() is None:p.terminate()
            p.wait(timeout=5)
        for f in handles:f.close()
    (work/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8')
    return result


def main():
    p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--only',choices=['happy','negative','all'],default='all');p.add_argument('--review-mode',choices=['normal','not-requested'],default='normal');a=p.parse_args()
    out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);jobs=[]
    if a.only in ('happy','all'):
        for case,(_,provider,_) in CASES.items():
            jobs.append((case,'all','none',a.review_mode))
            if provider:jobs.extend([(case,'absent','none',a.review_mode),(case,'empty','none',a.review_mode)])
    if a.only in ('negative','all'):
        case='microClient2center_v1'
        for mode in ['missing','not-requested','wrong-run','stop-review','no-runtime','wrong-binding']:jobs.append((case,'normal','none',mode))
        jobs.extend([(case,'normal','wrong-valid-data','normal'),(case,'absent','fake-absence','normal'),(case,'all','wrong-code','normal'),
                     ('centerServer2micro_v1','all','no-processing','normal'),('centerServer2micro_v1','all','no-error-log','normal')])
    results=[]
    for i,job in enumerate(jobs):
        r=run(a.exe.resolve(),out/str(i),*job);results.append(r);print(i,*job,'PASS' if r['passed'] else r.get('error'),flush=True)
        (out/'summary.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
    return 0 if all(r['passed'] for r in results) else 1


if __name__=='__main__':raise SystemExit(main())
