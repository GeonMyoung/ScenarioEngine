import argparse,hashlib,json,os,socket,subprocess,sys,time
from pathlib import Path

def main():
    p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--case',action='append');a=p.parse_args()
    root=Path(__file__).resolve().parents[1];exe=a.exe.resolve();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);results=[]
    cases={'normal':('SUCCESS',None),'encoded-key':('SUCCESS',None),'text-xml':('SUCCESS',None),'missing':('FAIL','필수 필드'),'duplicate':('FAIL','중복'),'code':('FAIL','코드'),'date':('FAIL','일시'),'numeric':('FAIL','숫자'),'root':('FAIL','result'),'namespace':('FAIL','네임스페이스'),'malformed':('FAIL','XML'),'dtd':('FAIL','XML'),'utf8':('FAIL','UTF-8'),'status':('FAIL','상태 코드'),'content-type':('FAIL','Content-Type'),'empty':('EVIDENCE_PENDING','자료'),'large':('FAIL','응답 수신 실패'),'delay':('FAIL','응답 수신 실패'),'stop':('STOPPED','중지'),'refused':('FAIL','응답 수신 실패')}
    if a.case:
        if set(a.case)-cases.keys():p.error('Unknown case')
        cases={k:v for k,v in cases.items() if k in a.case}
    for mode,(wanted,reason) in cases.items():
        d=out/mode;d.mkdir();sut=None;entry=dict(case=mode,expected=wanted,passed=False);fh=(d/'sut.log').open('wb')
        with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
        key='SC28+한글&value=100%' if mode=='encoded-key' else 'SC28_LOCAL_KEY'
        config=dict(sut_base_url=f'http://127.0.0.1:{port}',api_key=key,repetitions=10,connect_timeout_s=1,request_timeout_s=2,test_provide_utic=True)
        (d/'config.json').write_text(json.dumps(config,ensure_ascii=False),encoding='utf8')
        try:
            if mode!='refused':
                env=os.environ.copy();env['UTIC_TEST_API_KEY']=key
                sut=subprocess.Popen([sys.executable,'-X','utf8',str(root/'emulator/utic_provider.py'),'--port',str(port),'--output',str(d/'sut'),'--mode','normal' if mode=='encoded-key' else 'delay' if mode=='stop' else mode],env=env,stdout=fh,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
                until=time.monotonic()+5
                while time.monotonic()<until:
                    events=d/'sut/events.jsonl'
                    if events.exists() and 'listening' in events.read_text(encoding='utf8'):break
                    if sut.poll() is not None:raise RuntimeError('SUT failed to start')
                    time.sleep(.025)
                else:raise RuntimeError('SUT readiness timeout')
            cmd=[str(exe),'--utic-provider','--config',str(d/'config.json')]
            if mode=='stop':cmd+=['--stop-after-ms','300']
            started=time.monotonic();run=subprocess.run(cmd,cwd=d,capture_output=True,timeout=15);(d/'tester.log').write_bytes(run.stdout+run.stderr)
            reports=list(d.glob('rest-results/*/result.json'));assert len(reports)==1,run.stdout[-900:]
            report=json.loads(reports[0].read_text(encoding='utf8'));entry['actual']=report['automaticVerdict'];entry['report']=str(reports[0]);assert entry['actual']==wanted,report
            if reason:assert reason in report['detail'],report
            if mode=='stop':assert time.monotonic()-started<4
            if wanted=='SUCCESS':
                assert report['completedExchanges']==10
                tester=[json.loads(x) for x in (reports[0].parent/'events.jsonl').read_text(encoding='utf8').splitlines()];peer=[json.loads(x) for x in (d/'sut/events.jsonl').read_text(encoding='utf8').splitlines()]
                received=[x for x in tester if x['event']=='response'];sent=[x for x in peer if x['event']=='response_sent'];requests=[x for x in peer if x['event']=='request']
                assert len(received)==len(sent)==len(requests)==10
                for r,s,q in zip(received,sent,requests):
                    assert r['bodySha256']==s['bodySha256'] and s['runId']==report['runId'] and int(s['exchange'])==r['exchange']
                    assert q['accepted'] and q['keyMatched'] and q['queryNames']==['key'] and q['accept']=='application/xml' and q['bodyBytes']==0
                    assert hashlib.sha256((reports[0].parent/f"response-{r['exchange']}.xml").read_bytes()).hexdigest()==r['bodySha256']
            assert key.encode() not in run.stdout+run.stderr
            assert all(key not in path.read_text(encoding='utf8') for path in reports[0].parent.glob('*.txt'))
            entry['passed']=True
        except Exception as e:entry['error']=repr(e)
        finally:
            if sut and sut.poll() is None:sut.terminate();sut.wait(timeout=5)
            fh.close()
        results.append(entry);print(mode,'PASS' if entry['passed'] else entry.get('error'),flush=True)
        (out/'summary.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
    return 0 if all(x['passed'] for x in results) else 1
if __name__=='__main__':raise SystemExit(main())
