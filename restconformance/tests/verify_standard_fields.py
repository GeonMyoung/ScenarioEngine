"""Part 3 VDS/UTIC boundary, wire and fixture-preflight regressions."""
import argparse
import copy
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'emulator'))
from ut_center_vds import default_records
from utic_provider import fixture
from standard_fields import vds, utic


def cases():
    rows = []
    def v(name, changes=None, remove=(), expected=True, raw=None):
        data = default_records()
        data[0].update(changes or {})
        for key in remove:
            data[0].pop(key)
        body = json.dumps(data, ensure_ascii=False)
        if raw:
            for key, token in raw.items():
                body = body.replace(json.dumps(data[0][key]), token, 1)
        rows.append(dict(name='vds-' + name, kind='vds', body=body.encode(), expected=expected))
    def u(name, changes=None, remove=(), expected=True):
        root = ET.fromstring(fixture())
        record = root.find('record')
        for key, value in (changes or {}).items():
            record.find(key).text = value
        for key in remove:
            record.remove(record.find(key))
        rows.append(dict(name='utic-' + name, kind='utic', body=ET.tostring(root, encoding='utf-8'), expected=expected))

    v('normal')
    v('optional-omitted', remove=('volS', 'volM', 'volL'))
    v('boundaries', dict(collectDate='20240229235959', stnId='S'*12, linkId='L'*12, vdsId='V'*12,
                         stnLocation='가'*50, laneNo=9, errCode=9, vol=9999999, spd=999.99, occ=999.99,
                         volS=9999999, volM=9999999, volL=9999999))
    v('signed-boundaries', dict(laneNo=-9, errCode=-9, vol=-9999999, spd=-999.99, occ=-999.99))
    for field, length in [('stnId', 12), ('linkId', 12), ('vdsId', 12), ('stnLocation', 50)]:
        for suffix, value, ok in [('unicode-limit', '😀'*length, True), ('overflow', 'X'*(length+1), False), ('empty', '', False), ('type', 1, False)]:
            v(field+'-'+suffix, {field: value}, expected=ok)
    for key in ['collectDate','stnId','laneNo','vol','spd','occ','errCode','linkId','vdsId','stnLocation']:
        v(key+'-missing', remove=(key,), expected=False)
    for value in ['20260230120000','20230229120000','19000229120000','20261301120000','20260100120000',
                  '20260101240000','20260101126000','20260101120060','00000101120000','2026-01-01','２０２６０１０１１２００００',None]:
        v('date-'+str(value), {'collectDate':value}, expected=False)
    v('leap-century', {'collectDate':'20000229120000'})
    for key in ['laneNo','errCode']:
        for value in [10,-10,1.5,True,'1',None]:
            v(key+'-'+str(value), {key:value}, expected=False)
    for key in ['vol','volS','volM','volL']:
        for value in [10000000,1.5,True,'1',None]:
            v(key+'-'+str(value), {key:value}, expected=False)
    for key in ['spd','occ']:
        for value in [1000,52.351,True,'52.35',None]:
            v(key+'-'+str(value), {key:value}, expected=False)
    for name, token, ok in [('exact','52.350000000000001',False),('trailing-zero','52.3500',True),
                            ('exponent','5235e-2',True),('large-exponent','1e999999',False),
                            ('tiny','1e-999999',False),('negative-zero','-0.0000',True)]:
        v('decimal-'+name, {'spd':'TOKEN'}, raw={'spd':token}, expected=ok)
    v('integer-exponent', {'vol':'TOKEN'}, raw={'vol':'2400e-2'})
    v('integer-rounded-fraction', {'vol':'TOKEN'}, raw={'vol':'1.00000000000000001'}, expected=False)

    u('normal')
    u('optional-omitted', remove=('sourceCode','locationData','locationTypeCd'))
    u('optional-empty', {'sourceCode':'','locationData':'','locationTypeCd':''})
    u('boundaries', {'sourceCode':'ABCDE','locationData':'가'*3000,'locationTypeCd':'C1013',
                      'locationDataX':'999999.999999999','locationDataY':'-999999.999999999',
                      'startDate':'20240229235959','endDate':'2024년 02월 29일 23시 59분'})
    for key, length in [('sourceCode',5),('locationData',3000),('incidentId',12),('incidentTitle',500),('roadName',50)]:
        u(key+'-unicode-limit', {key:'😀'*length})
        u(key+'-overflow', {key:'가'*(length+1)}, expected=False)
    for code, ok in [('C0101',True),('C0102',True),('C1013',True),('C0103',False),('BAD',False),('C01010',False)]:
        u('location-code-'+code, {'locationTypeCd':code}, expected=ok)
    for key in ['locationDataX','locationDataY']:
        for name, token, ok in [('overflow','1000000',False),('fraction','126.9784000001',False),
                               ('tiny','0.0000000001',False),('minimum','0.000000001',True),
                               ('trailing','126.9784000000',True),('exponent','1269784e-4',True),
                               ('zero','-0.0000000000',True),('nonfinite','NaN',False),
                               ('hex','0x1',False),('junk','12x',False),('empty','',False)]:
            u(key+'-'+name, {key:token}, expected=ok)
        u(key+'-missing', remove=(key,), expected=False)
    for field in ['startDate','endDate','updateDate']:
        u(field+'-bad', {field:'20260230120000'}, expected=False)
    for field, value in [('incidenteTypeCd','99'),('incidenteTrafficCd','X'),('incidenteGradeCd','X'),('controlType','9'),('important','9')]:
        u(field+'-bad', {field:value}, expected=False)
    return rows


def call(exe, arguments, work):
    return subprocess.run([str(exe), *arguments], cwd=work, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          timeout=30, creationflags=subprocess.CREATE_NO_WINDOW)


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--exe',type=Path,required=True);parser.add_argument('--output',type=Path,required=True);parser.add_argument('--kind',choices=['vds','utic'])
    args=parser.parse_args();exe=args.exe.resolve();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    results=[];allcases=[c for c in cases() if not args.kind or c['kind']==args.kind]
    for index,case in enumerate(allcases):
        bodyPath=out/f'{index:03d}.body';bodyPath.write_bytes(case['body'])
        run=call(exe,['--validate-'+case['kind'],'--config',str(bodyPath)],out)
        (out/f'{index:03d}.log').write_bytes(run.stdout)
        native=run.returncode==0
        try:(vds if case['kind']=='vds' else utic)(case['body']);peer=True
        except (ValueError,ET.ParseError,UnicodeError):peer=False
        results.append(dict(name=case['name'],kind='field',expected=case['expected'],native=native,peer=peer,
                            passed=native==peer==case['expected']))
    print('Field checks:',len(results),'passed:',sum(r['passed'] for r in results),flush=True)

    # Original false-positive inputs plus valid boundaries exercise transport
    # and setup paths. Each invalid setup must fail before opening a listener.
    wanted=['vds-date-20260230120000','vds-stnId-overflow','vds-laneNo-10','vds-spd-52.351','vds-vol-1.5',
            'utic-locationDataX-fraction','utic-sourceCode-overflow','vds-boundaries','utic-boundaries']
    if args.kind:wanted=[name for name in wanted if name.startswith(args.kind+'-')]
    for index,name in enumerate(wanted):
        case=next(c for c in allcases if c['name']==name);xml=case['kind']=='utic';work=out/f'w{index}';work.mkdir()
        media='application/xml' if xml else 'application/json';counter=[0]
        class Handler(BaseHTTPRequestHandler):
            def log_message(self,*args):pass
            def do_GET(self):
                counter[0]+=1
                self.send_response(200);self.send_header('Content-Type',media);self.send_header('Content-Length',str(len(case['body'])))
                self.send_header('X-Scenario-Run','standard-field-peer-probe');self.send_header('X-Scenario-Exchange',str(counter[0]));self.end_headers();self.wfile.write(case['body'])
        server=ThreadingHTTPServer(('127.0.0.1',0),Handler);thread=threading.Thread(target=server.serve_forever,daemon=True);thread.start()
        provider='centerClient2utic_v1' if xml else 'microClient2center_v1'
        requester='uticServer2center_v1' if xml else 'centerServer2micro_v1'
        try:
            config=json.loads((ROOT/f'registration/{provider}.example.json').read_text())
            for k in list(config):
                if k.startswith('test_'):config[k]=k==('test_provide_utic' if xml else 'test_normal_vds')
            config.update(sut_base_url=f'http://127.0.0.1:{server.server_port}',request_timeout_s=2,connect_timeout_s=1)
            configPath=work/'config.json';configPath.write_text(json.dumps(config),encoding='utf8')
            run=call(exe,['--method-case',provider,'--config',str(configPath)],work);(work/'provider.log').write_bytes(run.stdout)
            report=json.loads(next(work.glob('rest-results/*/result.json')).read_text())
            expected='SUCCESS' if case['expected'] else 'FAIL'
            results.append(dict(name=name,kind='provider-wire',expected=expected,actual=report['automaticVerdict'],exchanges=report['completedExchanges'],
                                passed=report['automaticVerdict']==expected and report['completedExchanges']==(10 if case['expected'] else 0)))
            if not case['expected']:
                fixturePath=work/'invalid.body';fixturePath.write_bytes(case['body'])
                config=json.loads((ROOT/f'registration/{requester}.example.json').read_text())
                config['response_xml_file' if xml else 'response_json_file']=str(fixturePath)
                setupPath=work/'setup.json';setupPath.write_text(json.dumps(config),encoding='utf8')
                run=call(exe,['--method-case',requester,'--config',str(setupPath)],work);(work/'setup.log').write_bytes(run.stdout)
                results.append(dict(name=name,kind='requester-setup',passed=run.returncode==2 and b'LISTENING' not in run.stdout))
            # Test the independent requesting emulator against real HTTP input.
            counter[0]=0
            command=[sys.executable,'-X','utf8',str(ROOT/'emulator/rest_method_sut.py'),'--role','requester','--format','xml' if xml else 'json',
                     '--port',str(server.server_port),'--requests','1','--output',str(work/'peer')]
            run=subprocess.run(command,cwd=work,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=15,creationflags=subprocess.CREATE_NO_WINDOW)
            (work/'peer.log').write_bytes(run.stdout)
            processed=json.loads((work/'peer/processed.json').read_text(encoding='utf8'))
            expectedAction='normal' if case['expected'] else 'malformed'
            results.append(dict(name=name,kind='requester-peer-wire',expected=expectedAction,actual=processed[0]['action'],
                                passed=run.returncode==0 and processed[0]['action']==expectedAction))
        finally:server.shutdown();server.server_close();thread.join()
    summary=dict(executableSha256=hashlib.sha256(exe.read_bytes()).hexdigest(),checks=len(results),passed=sum(x['passed'] for x in results),results=results)
    (out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
    print('Total:',summary['checks'],'passed:',summary['passed'])
    for r in results:
        if not r['passed']:print('FAIL',r)
    return 0 if all(r['passed'] for r in results) else 1


if __name__=='__main__':raise SystemExit(main())
