import argparse,copy,json,socket,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path[:0]=[str(ROOT/'emulator'),str(ROOT/'tools')]
from signal_codec import fixture,encode,decode,packet,frame,catalog
from extended_codec import CASES as EXTENDED_CASES,catalog as extended_catalog
from review_evidence import review

def run(exe,out,provider,selection='all',fault='none',overrides=None,stop_after=0,case_override=None):
 out.mkdir(parents=True,exist_ok=False);case=case_override or ('centerClient2signal_binary_v1' if provider else 'signalServer2center_binary_v1');cfg=json.loads((ROOT/f'registration/{case}.example.json').read_text(encoding='utf8'))
 plan=extended_catalog(case) if case in EXTENDED_CASES else catalog(provider)
 keys=[k for k,mode,msg in plan if selection=='all' or selection==mode or selection==k]
 for k in cfg:
  if k.startswith('test_'):cfg[k]=k in keys
 with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
 cfg.update(period_ms=100,period_tolerance_ms=70,tcp_port=port,socket_timeout_ms=1500,initial_limit_ms=1000,heartbeat_period_ms=100,heartbeat_tolerance_ms=70,change_delay_ms=30);cfg.update(overrides or {})
 config=out/'config.json';config.write_text(json.dumps(cfg,ensure_ascii=False,indent=2),encoding='utf8');peer_cmd=[sys.executable,'-X','utf8',str(ROOT/'emulator/signal_sut.py'),'--config',str(config),'--run-manifest',str(out/'binary-run.json'),'--output',str(out/'peer'),'--role','provider' if provider else 'receiver','--fault',fault]
 cmd=[str(exe),'--case',case,'--config',str(config)]
 if stop_after:cmd+=['--stop-after-ms',str(stop_after)]
 processes=[];handles=[]
 def start(args,name):
  f=(out/(name+'.log')).open('wb');handles.append(f);p=subprocess.Popen(args,cwd=out,stdout=f,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW);processes.append(p);return p
 def ready(p,name):
  until=time.monotonic()+10
  while time.monotonic()<until:
   if b'LISTENING' in (out/(name+'.log')).read_bytes():return
   if p.poll() is not None:raise RuntimeError(name+' ended before listening')
   time.sleep(.02)
  raise TimeoutError('Ready timeout')
 result=dict(case=case,selection=selection,fault=fault,passed=False)
 try:
  if provider:peer=start(peer_cmd,'peer');ready(peer,'peer')
  engine=start(cmd,'engine')
  if not provider and not stop_after:ready(engine,'engine');peer=start(peer_cmd,'peer')
  engine.wait(timeout=35);report_path=next(out.glob('binary-results/*/result.json'));report=json.loads(report_path.read_text(encoding='utf8'))
  expected='STOPPED' if stop_after else 'SUCCESS' if fault in ['none','coalesced','tcp-fragment','no-processing','large-data'] else 'FAIL';assert report['automaticVerdict']==expected,report
  notes=[json.loads(x) for x in (out/'notifications.jsonl').read_text(encoding='utf8').splitlines()];states=[x for x in notes if x['type']=='state'];assert all(x['value'] in ['START','SUCCESS','FAIL','STOPPED','FINISH'] for x in states)
  assert [x['value'] for x in states if x['test']=='MainScenario']==['START',expected,'FINISH']
  if expected=='SUCCESS':
   peer.wait(timeout=10)
   if fault=='no-processing':
    try:review(report_path,out/'peer')
    except (AssertionError,FileNotFoundError):pass
    else:raise AssertionError('Unobserved internal processing accepted')
   else:result['peerReview']=review(report_path,out/'peer')
   messages=[x for x in notes if x['type']=='info' and '메시지 순번' in x['data']];assert len({(x['test'],x['data']['메시지 순번']) for x in messages})==report['messages']
  result.update(passed=True,verdict=expected,report=str(report_path),items=len(report['items']),exchanges=report['completedExchanges'],messages=report['messages'])
 except Exception as e:result['error']=repr(e)
 finally:
  for p in processes:
   if p.poll() is None:p.terminate()
   p.wait(timeout=5)
  for f in handles:f.close()
 (out/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8');return result

def codec_checks(exe,out):
 results=[]
 for msg in [68,69,70]:
  for encoding in ['UTF-8','CP949']:
   for mode in ['xor8','sum8']:
    rows=fixture(msg,count=2);p=out/f'{msg}-{encoding}-{mode}.json';p.write_text(json.dumps(rows,ensure_ascii=False),encoding='utf8')
    response=subprocess.run([str(exe),'--operation','encode','--message',str(msg),'--config',str(p),'--encoding',encoding,'--lrc',mode],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10)
    expected=packet(msg,2,0,encode(msg,rows,encoding),mode);raw=bytes.fromhex(response.stdout.decode());assert raw==expected
    decoded=subprocess.run([str(exe),'--operation','decode','--hex',raw.hex(),'--encoding',encoding,'--lrc',mode],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10)
    results.append(dict(kind='codec',message=msg,encoding=encoding,mode=mode,passed=decoded.returncode==0 and json.loads(decoded.stdout)==rows))
 # Hand-specified TOD fields verify endian, offsets and the 42-byte record.
 tod=encode(70,fixture(70));assert len(tod)==42 and tod[:10].hex()=='000003e9071e0078001e'
 cases=[]
 def add(msg,name,key,value,expected):
  rows=fixture(msg);rows[0][key]=value;cases.append((msg,name,rows,expected))
 for key in ['LC_NO','LC_TYPE','LC_STATUS','LC_COUNT','LC_A_FLONUMBER','LC_B_FLONUMBER']:
  for value,ok in [(0,True),(255,True),(256,False),(-1,False),('1',False),(True,False)]:add(68,key+str(value),key,value,ok)
 for value,ok in [(4294967295,True),(4294967296,False),(-1,False)]:add(70,'TOD ID'+str(value),'LC_NO',value,ok)
 for key,limit in [('START_HOUR',23),('START_MIN',59),('CYCLE',65535),('OFFSET',65535),('ARING_1PHASE',65535),('BRING_8PHASE',65535)]:
  for value,ok in [(limit,True),(limit+1,False)]:add(70,key+str(value),key,value,ok)
 for key,width in [('LC_NAME',100),('LC_LAT',20),('LC_A_START_LAT',20)]:
  for value,ok in [('A'*width,True),('A'*(width+1),False),('',False),('가'*(width//3),True),('가'*(width//3+1),False),('a\0b',False)]:add(68,key+str(len(value)),key,value,ok)
 for i,(msg,name,rows,expected) in enumerate(cases):
  p=out/f'b{i}.json';p.write_text(json.dumps(rows,ensure_ascii=False),encoding='utf8');r=subprocess.run([str(exe),'--operation','encode','--message',str(msg),'--config',str(p)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10)
  try:encode(msg,rows);peer=True
  except (ValueError,OverflowError,UnicodeError):peer=False
  results.append(dict(kind='boundary',name=name,passed=(r.returncode==0)==peer==expected))
 return results

def main():
 p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();results=codec_checks(exe,out)
 jobs=[(False,'all'),(True,'all'),(False,'split','none',{'first_sequence':255}),(True,'split','coalesced',{'first_sequence':255}),(False,'all','none',{'lrc_mode':'sum8','ack_seq_mode':'fixed1','char_encoding':'CP949','first_sequence':254}),(True,'all','none',{'lrc_mode':'sum8','ack_seq_mode':'fixed1','char_encoding':'CP949','first_sequence':254}),(True,'normal','tcp-fragment'),(False,'normal','none',{'tcp_write_chunk_bytes':7}),(False,'heartbeat','none',{'heartbeat_ack':False}),(True,'heartbeat','none',{'heartbeat_ack':False})]
 for fault in ['bad-lrc','bad-sequence','wide-id','little-size','delay']:jobs.append((True,'test_provide_all_status',fault))
 jobs.append((True,'test_provide_tod','invalid-tod'))
 for fault in ['wrong-ack','wrong-ack-seq','wrong-ack-message','no-ack','no-processing']:jobs.append((False,'test_receive_all_status',fault))
 jobs.extend([(False,'bad_lrc','accept-errors'),(False,'test_receive_all_status','none',None,300)])
 for i,job in enumerate(jobs):
  r=run(exe,out/str(i),*job);results.append(r);print(i,job,'PASS' if r['passed'] else r.get('error'),flush=True)
 summary=dict(checks=len(results),passed=sum(r['passed'] for r in results),results=results);(out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
 for r in results:
  if not r['passed']:print('FAIL',r)
 print('Binary checks',summary['passed'],'/',summary['checks']);return 0 if all(r['passed'] for r in results) else 1
if __name__=='__main__':raise SystemExit(main())
