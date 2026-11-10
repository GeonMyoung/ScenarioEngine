import argparse,json,os,socket,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from review_method_evidence import review
CASES={'uticServer2center_v1':('xml',False,'test_normal_utic'), 'microClient2center_v1':('json',True,'test_normal_vds'),'centerServer2micro_v1':('json',False,'test_request_vds'),'centerClient2utic_v1':('xml',True,'test_provide_utic'),'microClient2center_smart_v1':('json',True,'test_normal_smart'),'centerServer2micro_smart_v1':('json',False,'test_request_smart')}
def run(exe,out,case,kind='all',fault='none',status=200,overrides=False):
    out.mkdir(parents=True,exist_ok=False);fmt,provider,normal=CASES[case]
    config=json.loads((ROOT/f'registration/{case}.example.json').read_text(encoding='utf8'))
    for k in list(config):
        if k.startswith('test_'):config[k]=False
    selected=[normal,'test_invalid_request','test_missing_credential','test_wrong_credential','test_missing_path'] if provider else [normal,'test_no_data_error_response','test_response_400','test_response_404','test_response_500','test_empty_response','test_malformed_response']
    if kind=='absent':selected=['test_no_data_error'] if provider else ['test_no_data_error_response'];config['no_data_error_status']=status;config['confirm_data_absent']=True
    if kind=='empty':selected=['test_no_data'];config['no_data_status']=status
    if kind=='invalid':selected=['test_invalid_request']
    if kind=='malformed':selected=['test_malformed_response'] if not provider else [normal]
    if kind=='normal':selected=[normal]
    if kind=='auth':selected=['test_missing_credential','test_wrong_credential']
    for k in selected:config[k]=True
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    config.update(repetitions=10,request_timeout_s=2)
    if provider:config.update(sut_base_url=f'http://127.0.0.1:{port}',connect_timeout_s=1)
    else:config['local_port']=port
    if overrides:config.update(bad_request_status=422 if fmt=='xml' else 400,unauthorized_status=403)
    (out/'config.json').write_text(json.dumps(config,ensure_ascii=False),encoding='utf8')
    env=os.environ.copy();env['REST_TEST_CREDENTIAL']=config['api_key'] if fmt=='xml' else config['bearer_token']
    sutArgs=[sys.executable,'-X','utf8',str(ROOT/'emulator/rest_method_sut.py'),'--role','provider' if provider else 'requester','--format',fmt,'--port',str(port),'--output',str(out/'sut'),'--requests',str(len(selected)*10),'--data','absent' if kind=='absent' and fault not in ['unprepared','fake-absence'] else 'empty' if kind=='empty' and fault!='unprepared' else 'normal','--empty-status',str(status if kind=='empty' else 200),'--absence-status',str(status if kind=='absent' else 404),'--fault','none' if fault in ['unprepared','stop'] else fault]
    if '_smart_' in case:sutArgs+=['--information','smart']
    if overrides:sutArgs+=['--bad-request-status','422' if fmt=='xml' else '400','--auth-status','403']
    command=[str(exe),'--method-case',case,'--config',str(out/'config.json')]
    if fault=='stop':command+=['--stop-after-ms','300']
    procs=[];files=[];result=dict(case=case,kind=kind,fault=fault,passed=False)
    def launch(args,name):
        f=(out/(name+'.log')).open('wb');files.append(f);p=subprocess.Popen(args,cwd=out,env=env,stdout=f,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW);procs.append(p);return p
    def ready(name,proc):
        until=time.monotonic()+8
        while time.monotonic()<until:
            if b'LISTENING' in (out/(name+'.log')).read_bytes():return
            if proc.poll() is not None:raise RuntimeError('Ended before listening')
            time.sleep(.03)
        raise RuntimeError('Readiness timeout')
    try:
        if provider:sut=launch(sutArgs,'sut');ready('sut',sut)
        tester=launch(command,'tester')
        if not provider and fault!='stop':ready('tester',tester);sut=launch(sutArgs,'sut')
        tester.wait(timeout=30)
        if not provider and fault!='stop':sut.wait(timeout=15)
        reports=list(out.glob('rest-results/*/result.json'));assert len(reports)==1
        report=json.loads(reports[0].read_text(encoding='utf8'));result['report']=str(reports[0]);result['actual']=report['automaticVerdict']
        if fault=='stop':assert result['actual']=='STOPPED'
        elif fault in ['wrong-code','success-on-error','malformed-normal','unprepared','delay','malformed-error','wrong-error-type','wrong-error-date','invalid-error-utf8','api-schema','wrong-smart-type','smart-missing-field','smart-bad-date','smart-precision'] or fault=='empty-error-body' and case=='microClient2center_v1' and kind=='invalid':assert result['actual']=='FAIL',report
        elif fault in ['no-processing','accept-malformed','fake-absence','path-not-found','no-error-log','wrong-valid-data']:
            assert result['actual'] in ['SUCCESS','EVIDENCE_PENDING']
            try:review(reports[0],out/'sut')
            except (AssertionError,OSError):result['invalidEvidenceRejected']=True
            else:raise AssertionError('Invalid SUT evidence accepted')
        else:result['evidence']=review(reports[0],out/'sut')
        result['passed']=True
    except Exception as e:result['error']=repr(e)
    finally:
        for proc in procs:
            if proc.poll() is None:proc.terminate()
            proc.wait(timeout=5)
        for f in files:f.close()
    (out/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8');return result
def main():
    p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--case',choices=list(CASES),action='append');p.add_argument('--only',choices=['happy','negative','all'],default='all');a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();jobs=[]
    for case,(_,provider,_) in CASES.items():
        if a.case and case not in a.case:continue
        if a.only in ['happy','all']:
            jobs.append((case,'all','none',200,False))
            if provider:jobs.extend([(case,'absent','none',404,False),(case,'empty','none',200,False)])
        if a.only in ['negative','all']:
            if provider:
                jobs.extend([(case,'invalid','wrong-code',200,False),(case,'invalid','success-on-error',200,False),(case,'malformed','malformed-normal',200,False),(case,'empty','unprepared',200,False),(case,'empty','none',204,False),(case,'absent','none',404,False),(case,'auth','none',200,True)])
            else:jobs.extend([(case,'all','no-processing',200,False),(case,'malformed','accept-malformed',200,False),(case,'normal','stop',200,False)])
    results=[]
    for index,(case,kind,fault,status,overrides) in enumerate(jobs):
        r=run(exe,out/f'{index:02d}',case,kind,fault,status,overrides);results.append(r);print(index,case,kind,fault,'PASS' if r['passed'] else r.get('error'),flush=True)
        (out/'summary.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
    return 0 if all(r['passed'] for r in results) else 1
if __name__=='__main__':raise SystemExit(main())
