"""Execute the native UTIC tester and independent Python SUT in scoped processes."""
import argparse
import hashlib
import json
from pathlib import Path
import socket
import subprocess
import sys
import time

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from review_utic_evidence import review


def available_port():
    with socket.socket() as sock:
        sock.bind(('127.0.0.1',0));return sock.getsockname()[1]


def run_case(exe, out, name, port=None):
    out.mkdir(parents=True,exist_ok=False)
    port=port or available_port()
    key='SC07_LOCAL_KEY' if name!='encoded-key' else 'SC07+key&value=100%'
    config={'bind_ip':'127.0.0.1','local_port':port,'api_key':key,'repetitions':10,
            'request_timeout_s':2,'test_normal_utic':True}
    if name=='malformed-fixture':
        (out/'broken.xml').write_text('<result><record>',encoding='utf-8')
        config['response_xml_file']=str(out/'broken.xml')
    if name=='dtd-fixture':
        (out/'broken.xml').write_text('<!DOCTYPE result [<!ENTITY v SYSTEM "file:///missing">]><result>&v;</result>',encoding='utf-8')
        config['response_xml_file']=str(out/'broken.xml')
    (out/'tester.json').write_text(json.dumps(config),encoding='utf-8')
    sut_config=dict(config,base_url=f'http://127.0.0.1:{port}')
    (out/'sut.json').write_text(json.dumps(sut_config),encoding='utf-8')
    processes=[];files=[];started=time.monotonic();result={'case':name,'port':port,'status':'FAIL'}
    try:
        log=(out/'tester.console.txt').open('wb');files.append(log)
        command=[str(exe),'--config',str(out/'tester.json')]
        if name=='stop':command+=['--stop-after-ms','300']
        tester=subprocess.Popen(command,cwd=out,stdin=subprocess.DEVNULL,stdout=log,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
        processes.append(tester)
        if name not in ['malformed-fixture','dtd-fixture','stop']:
            until=time.monotonic()+10
            while time.monotonic()<until:
                if b'LISTENING' in (out/'tester.console.txt').read_bytes():break
                if tester.poll() is not None:raise AssertionError('Tester ended before LISTENING')
                time.sleep(.03)
            else:raise AssertionError('Tester did not start listening')
            fault='none' if name in ['normal','encoded-key','rebind'] else name
            log=(out/'sut.console.txt').open('wb');files.append(log)
            sut=subprocess.Popen([sys.executable,'-X','utf8',str(ROOT/'emulator/ut_center_utic.py'),'--config',str(out/'sut.json'),'--output',str(out/'sut-evidence'),'--fault',fault],cwd=out,stdin=subprocess.DEVNULL,stdout=log,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW)
            processes.append(sut)
            result['sutExit']=sut.wait(timeout=20)
        result['testerExit']=tester.wait(timeout=20)
        reports=list((out/'rest-results').glob('*/result.json'))
        assert len(reports)==1, 'One immutable result report is required'
        document=json.loads(reports[0].read_text(encoding='utf-8'))
        result['automaticVerdict']=document['automaticVerdict'];result['detail']=document['detail']
        if name in ['normal','encoded-key','rebind']:
            assert result['testerExit']==result['sutExit']==0
            result['review']=review(reports[0],out/'sut-evidence')
        elif name=='no-processing':
            assert result['testerExit']==0 and document['automaticVerdict']=='EVIDENCE_PENDING'
            try:review(reports[0],out/'sut-evidence')
            except (AssertionError,OSError):result['missingEvidenceRejected']=True
            else:raise AssertionError('Missing SUT processing evidence was accepted')
        elif name=='stop':
            assert result['testerExit']==3 and document['automaticVerdict']=='STOPPED'
            assert time.monotonic()-started<4, 'STOP exceeded the bounded cleanup window'
        else:
            assert result['testerExit']==2 and document['automaticVerdict']=='FAIL'
            expected={'wrong-method':'method 불일치','wrong-path':'경로 불일치','wrong-key':'값 불일치',
                      'missing-key':'한 번만','duplicate-key':'한 번만','too-few':'대기 시간 초과',
                      'malformed-fixture':'XML','dtd-fixture':'XML'}[name]
            assert expected in document['detail'], 'An unrelated error is not a valid rejection'
        text=(out/'tester.console.txt').read_text(encoding='utf-8',errors='replace')
        traces=''.join(p.read_text(encoding='utf-8') for p in (out/'rest-results').glob('*/events.jsonl'))
        assert key not in text+traces, 'Request key leaked in execution evidence'
        result['status']='PASS'
    except Exception as error:result['error']=repr(error)
    finally:
        for process in processes:
            if process.poll() is None:process.kill()
            process.wait()
        for stream in files:stream.close()
    result['elapsedSeconds']=round(time.monotonic()-started,3)
    (out/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    return result


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--case',action='append')
    args=parser.parse_args();exe=args.exe.resolve();out=args.output.resolve();out.mkdir(parents=True,exist_ok=True)
    names=args.case or ['normal','encoded-key','wrong-method','wrong-path','wrong-key','missing-key','duplicate-key','too-few','malformed-fixture','dtd-fixture','no-processing','stop','rebind']
    results=[];rebind_port=None
    for name in names:
        result=run_case(exe,out/name,name,rebind_port if name=='rebind' else None)
        if name=='stop':rebind_port=result['port']
        results.append(result);print(result['status'],name,result.get('error',result.get('automaticVerdict')),flush=True)
        summary={'executable':str(exe),'sha256':hashlib.sha256(exe.read_bytes()).hexdigest(),
                 'passed':sum(r['status']=='PASS' for r in results),'total':len(results),'results':results}
        (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
    return 0 if all(r['status']=='PASS' for r in results) else 1


if __name__=='__main__':raise SystemExit(main())
