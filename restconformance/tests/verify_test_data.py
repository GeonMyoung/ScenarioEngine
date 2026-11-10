from pathlib import Path
import argparse,json,subprocess,sys,threading,xml.etree.ElementTree as ET
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
parser=argparse.ArgumentParser(description='Verify every REST message, complete multipart data, credential masking and failed-response preservation')
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--output',type=Path,required=True)
args=parser.parse_args()
exe=args.exe.resolve();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
root=Path(__file__).resolve().parents[2];sys.path.insert(0,str(root/'restconformance/emulator'))
from utic_provider import fixture
from ut_center_vds import default_records
results=[]
for mode in ['equal-repeat','xml-credential','json-escaped-credential','large-unique','invalid-utf8']:
 d=out/mode;d.mkdir();counter=[0]
 xml=mode=='xml-credential';case='centerClient2utic_v1' if xml else 'microClient2center_v1';secret='MASK&한글"' if xml else 'MASKME'
 if xml:
  tree=ET.fromstring(fixture());tree.find('record/incidentTitle').text='응답 '+secret+' 제목';payload=ET.tostring(tree,encoding='utf-8',xml_declaration=True)
 else:
  rows=default_records();rows[0]['stnLocation']=secret
  payload=json.dumps(rows,ensure_ascii=False).encode().replace(secret.encode(),b'\\u004d\\u0041\\u0053\\u004b\\u004d\\u0045')
 class Server(BaseHTTPRequestHandler):
  def log_message(self,*args):pass
  def do_GET(self):
   counter[0]+=1;body=payload
   if mode=='large-unique':
    rows=default_records();rows[0].update(padding='가나다X'*5000,zzSuffix=counter[0]);body=json.dumps(rows).encode()
   if mode=='invalid-utf8':body=b'\xff\x00A'*2000
   (d/f'wire-{counter[0]}.body').write_bytes(body)
   self.send_response(200);self.send_header('Content-Type','application/xml' if xml else 'application/json');self.send_header('Content-Length',str(len(body)));self.end_headers();self.wfile.write(body)
 server=ThreadingHTTPServer(('127.0.0.1',0),Server);t=threading.Thread(target=server.serve_forever,daemon=True);t.start()
 try:
  c=json.loads((root/f'restconformance/registration/{case}.example.json').read_text(encoding='utf8'));c['repetitions']=15 if mode=='large-unique' else 10;c['sut_base_url']=f'http://127.0.0.1:{server.server_port}';c['api_key' if xml else 'bearer_token']=secret;(d/'config.json').write_text(json.dumps(c),encoding='utf8')
  p=subprocess.run([str(exe),'--method-case',case,'--config',str(d/'config.json')],cwd=d,capture_output=True,timeout=15);(d/'tester.log').write_bytes(p.stdout+p.stderr)
  rpath=next(d.glob('rest-results/*/result.json'));r=json.loads(rpath.read_text(encoding='utf8'));text=next(rpath.parent.glob('test-data-*.txt')).read_text(encoding='utf8')
  if mode=='invalid-utf8':assert r['automaticVerdict']=='FAIL' and 'FF 00 41' in text
  else:assert r['automaticVerdict']=='SUCCESS'
  if 'credential' in mode:assert secret not in text and '[비공개]' in text and 'MASK&amp;' not in text and '\\u004d' not in text
  rows=[json.loads(line) for line in next(rpath.parent.glob('test-data-*.jsonl')).read_text(encoding='utf8').splitlines()]
  logical=[];index=0
  while index<len(rows):
   row=rows[index];number=row['메시지 순번']
   assert number==len(logical)+1
   if '분할 번호' in row:
    count=row['전체 분할 수'];parts=rows[index:index+count];assert len(parts)==count
    assert [x['분할 번호'] for x in parts]==list(range(1,count+1))
    assert all(x['메시지 순번']==number and x['회차']==row['회차'] and x['구분']==row['구분'] for x in parts)
    detail=json.loads(''.join(x['분할 데이터'] for x in parts));index+=count
   else:detail=row['상세'];index+=1
   logical.append(dict(iteration=row['회차'],direction=row['구분'],detail=detail))
  exchanges=1 if mode=='invalid-utf8' else c['repetitions']
  assert len(logical)==exchanges*2
  assert [x['direction'] for x in logical]==['송신 요청','수신 응답']*exchanges
  assert [x['iteration'] for x in logical]==[n for n in range(1,exchanges+1) for _ in (0,1)]
  for n in range(1,exchanges+1):
   assert logical[2*n-1]['detail']['HTTP 상태 코드']==200
   wire=(d/f'wire-{n}.body').read_bytes()
   assert (rpath.parent/f'response-{n}.body').read_bytes()==wire
   if mode=='large-unique':
    shown=logical[2*n-1]['detail']['본문'][0]
    assert shown['padding']=='가나다X'*5000 and shown['zzSuffix']==n
   if mode=='invalid-utf8':assert logical[2*n-1]['detail']['본문']['바이트']==' '.join(f'{b:02X}' for b in wire)
  assert all(len(json.dumps(x,ensure_ascii=False).encode())<40000 for x in rows)
  attachment=json.loads(next(rpath.parent.glob('test-data-*.json')).read_text(encoding='utf8'))
  assert attachment['요청 메시지 수']==exchanges and attachment['응답 메시지 수']==exchanges
  if 'credential' in mode:assert secret not in json.dumps(rows,ensure_ascii=False)
  if mode=='large-unique':assert len(rows)>len(logical)
  results.append(dict(test=mode,passed=True,logicalMessages=len(logical),notifications=len(rows),displayBytes=len(text.encode())));print(mode,'PASS',flush=True)
 finally:server.shutdown();server.server_close();t.join(timeout=2)
(out/'boundary-results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
