"""기상정보 native field boundaries and real peer exchanges."""
import argparse,hashlib,json,os,socket,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'emulator')]
from review_method_evidence import review
from weather_fields import fixture,decode,PATH,FORECAST

def field_cases():
    result=[]
    def add(name,changes=None,missing=None,expected=True,root=None,raw=None):
        value=json.loads(fixture());row=value['response']['body']['items']['item'][0];row.update(changes or {})
        if missing:row.pop(missing)
        if root is not None:value=root(value)
        result.append((name,raw or json.dumps(value,ensure_ascii=False).encode(),expected))
    add('normal')
    fields=['baseDate','updateDt','nx','ny','t1h','rn1','sky','uuu','vvv','reh','pty','lgt','vec','wsd','adstrdCode','fcstTime']
    for k in fields:add('missing-'+k,missing=k,expected=False)
    add('boundaries',dict(baseDate='20240229',adstrdCode='20240229',updateDt='235959',fcstTime='000000',nx=-199999999,ny=900000001,t1h=-999.9,uuu=999.9,vvv=-999.9,reh=999.9,wsd=-999.9,sky=4,pty=7,rn1='가'*10,lgt='180',vec='359'))
    for k,lo,hi in [('nx',-199999999,1800000001),('ny',-900000000,900000001),('pty',0,7)]:
        for v in [lo,hi]:add(k+'-boundary-'+str(v),{k:v})
        for v in [lo-1,hi+1,1.1,'1',True,None]:add(k+'-invalid-'+str(v),{k:v},expected=False)
    for k in ['t1h','uuu','vvv','reh','wsd']:
        for v in [1000,1.01,'1',False,None]:add(k+'-'+str(v),{k:v},expected=False)
        add(k+'-trailing-zero',{k:1.0})
    for k in ['baseDate','adstrdCode']:
        for v in ['20260230','11680640','2026-09-24',20260924,'00000101']:add(k+'-'+str(v),{k:v},expected=False)
    for k in ['updateDt','fcstTime']:
        for v in ['240000','235960','0600',60000]:add(k+'-'+str(v),{k:v},expected=False)
    for k,limit in [('rn1',10),('lgt',3),('vec',3)]:
        for v in ['',1,None,'가'*(limit+1)]:add(k+'-'+str(v),{k:v},expected=False)
    for v in [1,3,4]:add('sky-valid-'+str(v),{'sky':v})
    for v in [0,2,5,'1',1.1,True]:add('sky-invalid-'+str(v),{'sky':v},expected=False)
    add('api-example-fields',root=lambda v:[dict(baseDt='string',fcstDt='string')],expected=False)
    for name,mutate in [('wrong-code',lambda v:v['response']['header'].update(resultCode='03')),('numeric-code',lambda v:v['response']['header'].update(resultCode=0)),('short-code',lambda v:v['response']['header'].update(resultCode='0')),('count',lambda v:v['response']['body'].update(totalCount=2)),('metadata-string',lambda v:v['response']['body'].update(pageNo='1')),('dataType',lambda v:v['response']['body'].update(dataType='XML'))]:
        add(name,root=lambda v,mutate=mutate:(mutate(v),v)[1],expected=False)
    base=fixture().decode()
    add('exact-precision',raw=base.replace('"t1h": 23.5','"t1h": 23.50000000000000001').encode(),expected=False)
    add('exponent',raw=base.replace('"t1h": 23.5','"t1h": 235e-1').encode())
    add('duplicate',raw=base.replace('"sky": 1','"sky": 1,"sky": 3').encode(),expected=False)
    return result


def run(exe,work,provider,phase='all',fault='none',path=PATH,encoded=False,optional=False,variant='default'):
    work.mkdir(parents=True,exist_ok=False)
    case='centerClient2weather_v1' if provider else 'weatherServer2center_v1'
    config=json.loads((ROOT/f'registration/{case}.example.json').read_text())
    normal='test_normal_weather' if provider else 'test_request_weather'
    selected=[normal,'test_invalid_request','test_missing_credential','test_wrong_credential','test_missing_path'] if provider else [normal,'test_no_data_error_response','test_response_parameter_error','test_response_service_error','test_response_server_error','test_empty_response','test_malformed_response']
    if phase=='normal':selected=[normal]
    if phase=='invalid':selected=['test_invalid_request']
    if phase=='absent':selected=['test_no_data_error'];config['confirm_data_absent']=True
    if phase=='empty':selected=['test_no_data']
    for key in config:
        if key.startswith('test_'):config[key]=key in selected
    with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
    config.update(api_path=path,request_timeout_s=2,evidence_directory='')
    if variant=='upper':config['service_key_name']='ServiceKey'
    if variant=='page2':config['pageNo']='2'
    if variant=='forecast':config['base_time']='0630'
    if variant=='http-errors':config.update(bad_request_status=400,unauthorized_status=401,no_data_error_status=404)
    if variant=='empty204':config['no_data_status']=204
    if optional:config.update(evidence_directory=str(work/'sut'),evidence_wait_s=3)
    if encoded:config['api_key']='ntic +&=%한글'
    if provider:config.update(sut_base_url=f'http://127.0.0.1:{port}',connect_timeout_s=1)
    else:config['local_port']=port
    configPath=work/'config.json';configPath.write_text(json.dumps(config,ensure_ascii=False),encoding='utf8')
    env=os.environ.copy();env['REST_TEST_CREDENTIAL']=config['api_key']
    peerArgs=[sys.executable,'-X','utf8',str(ROOT/'emulator/weather_sut.py'),'--role','provider' if provider else 'requester','--port',str(port),'--path',path,'--key-name',config['service_key_name'],'--params',json.dumps({k:str(config[k]) for k in ['pageNo','numOfRows','base_date','base_time','nx','ny']}),'--bad-request-status',str(config['bad_request_status']),'--auth-status',str(config['unauthorized_status']),'--absence-status',str(config['no_data_error_status']),'--empty-status',str(config['no_data_status']),
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
            native=subprocess.run([str(exe),'--validate-weather','--config',str(f)],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=10,creationflags=subprocess.CREATE_NO_WINDOW)
            try:decode(body);peer=True
            except (ValueError,UnicodeError):peer=False
            results.append(dict(kind='field',name=name,expected=expected,native=native.returncode==0,peer=peer,passed=(native.returncode==0)==peer==expected))
    if a.only!='fields':
        jobs=[(False,'all','none'),(True,'all','none'),(True,'absent','none'),(True,'empty','none')]
        for provider in [False,True]:
            jobs.extend([(provider,'normal','none',FORECAST,False,False,'forecast'),(provider,'normal','none',PATH,True),(provider,'normal','none',PATH,False,False,'upper'),(provider,'normal','none',PATH,False,False,'page2'),(provider,'normal','none',PATH,False,True)])
        for fault in ['numeric-string','bad-date','fraction','sky','api-fields','envelope','count','page','media','delay']:jobs.append((True,'normal',fault))
        for fault in ['wrong-code','success-on-error','wrong-status','no-message','error-data']:jobs.append((True,'invalid',fault))
        jobs.extend([(True,'absent','wrong-code'),(True,'all','none',PATH,False,False,'http-errors'),(True,'absent','none',PATH,False,False,'http-errors'),(True,'empty','none',PATH,False,False,'empty204')])
        for fault in ['missing-json','missing-date','wrong-name','duplicate','bad-time','unknown','body','wrong-path','wrong-key','method','stop','no-processing','reordered']:jobs.append((False,'normal',fault))
        for i,job in enumerate(jobs):
            result=run(exe,out/str(i),*job);results.append(result);print(i,job,'PASS' if result['passed'] else result.get('error'),flush=True)
    summary=dict(checks=len(results),passed=sum(x['passed'] for x in results),results=results)
    (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
    for r in results:
        if not r['passed']:print('FAIL',r)
    print('기상정보 checks:',summary['passed'],'/',summary['checks'])
    return 0 if all(x['passed'] for x in results) else 1
if __name__=='__main__':raise SystemExit(main())
