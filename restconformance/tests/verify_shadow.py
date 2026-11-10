"""음영구간 데이터 경계·양측 HTTP 교환 및 증거 대조 검증."""
import argparse,json,socket,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'emulator')]
from review_method_evidence import review
from shadow_fields import fixture,decode,error

def field_cases():
 out=[]
 def add(name,changes=None,missing=None,expected=True,root=None,raw=None):
  value=json.loads(fixture());value[0].update(changes or {})
  if missing:value[0].pop(missing)
  if root is not None:value=root(value)
  out.append((name,raw or json.dumps(value,ensure_ascii=False).encode(),expected))
 add('normal');add('zero',dict.fromkeys(['node_link','lane_no','lane_speed','lane_volume','lane_density'],0))
 add('limits',dict(time='20240229235959',node_link=99999,lane_no=350,lane_speed=350,lane_volume=99999,lane_density=350))
 for k in ['time','node_link','lane_no','lane_speed','lane_volume','lane_density']:add('missing-'+k,missing=k,expected=False)
 for k in ['node_link','lane_no','lane_speed','lane_volume','lane_density']:
  for v in [-1,100000 if k in ['node_link','lane_volume'] else 351,1.5,'1',True,None]:add(k+'-'+str(v),{k:v},expected=False)
  add(k+'-integral-decimal',{k:18.0})
 for v in ['2026-07-24 13:20','20260230000000','20260101240000','00000101000000',20260724132000]:add('date-'+str(v),{'time':v},expected=False)
 add('wrong-envelope',root=lambda x:dict(items=x),expected=False)
 add('empty',root=lambda x:[])
 base=fixture().decode()
 add('exact-fraction',raw=base.replace('"lane_speed": 42','"lane_speed": 42.000000000000000001').encode(),expected=False)
 add('exponent',raw=base.replace('"lane_speed": 42','"lane_speed": 42e0').encode())
 add('duplicate',raw=base.replace('"lane_no": 1','"lane_no": 1,"lane_no": 2').encode(),expected=False)
 return out

def run(exe,work,provider,phase='all',fault='none',params=None,optional=False,empty_status=200):
 work.mkdir(parents=True,exist_ok=False);params=params or {};case='centerClient2micro_shadow_v1' if provider else 'microServer2center_shadow_v1'
 cfg=json.loads((ROOT/f'registration/{case}.example.json').read_text());normal='test_normal_shadow' if provider else 'test_request_shadow'
 selected=[normal,'test_invalid_request','test_missing_path'] if provider else [normal,'test_no_data_error_response','test_response_422','test_response_404','test_response_500','test_empty_response','test_malformed_response']
 if phase=='normal':selected=[normal]
 if phase=='invalid':selected=['test_invalid_request']
 if phase=='absent':selected=['test_no_data_error'];cfg['confirm_data_absent']=True
 if phase=='empty':selected=['test_no_data'];cfg['no_data_status']=empty_status
 for k in cfg:
  if k.startswith('test_'):cfg[k]=k in selected
 with socket.socket() as s:s.bind(('127.0.0.1',0));port=s.getsockname()[1]
 cfg.update(params);cfg.update(request_timeout_s=2,evidence_directory=str(work/'sut') if optional else '',evidence_wait_s=3)
 if provider:cfg.update(sut_base_url=f'http://127.0.0.1:{port}',connect_timeout_s=1)
 else:cfg['local_port']=port
 config=work/'config.json';config.write_text(json.dumps(cfg,ensure_ascii=False),encoding='utf8')
 peerArgs=[sys.executable,'-X','utf8',str(ROOT/'emulator/shadow_sut.py'),'--role','provider' if provider else 'requester','--port',str(port),'--params',json.dumps(params,ensure_ascii=False),'--data','absent' if phase=='absent' else 'empty' if phase=='empty' else 'normal','--requests',str(len(selected)*10),'--fault','none' if fault=='stop' else fault,'--empty-status',str(empty_status),'--output',str(work/'sut')]
 command=[str(exe),'--method-case',case,'--config',str(config)]
 if fault=='stop':command+=['--stop-after-ms','300']
 processes=[];handles=[]
 def start(args,name):
  f=(work/(name+'.log')).open('wb');handles.append(f);p=subprocess.Popen(args,cwd=work,stdout=f,stderr=subprocess.STDOUT,creationflags=subprocess.CREATE_NO_WINDOW);processes.append(p);return p
 def ready(p,name):
  until=time.monotonic()+8
  while time.monotonic()<until:
   if b'LISTENING' in (work/(name+'.log')).read_bytes():return
   if p.poll() is not None:raise RuntimeError('Ended before listening')
   time.sleep(.03)
  raise RuntimeError('Readiness timeout')
 result=dict(case=case,phase=phase,fault=fault,parameters=params,passed=False)
 try:
  if provider:peer=start(peerArgs,'peer');ready(peer,'peer')
  engine=start(command,'engine')
  if not provider and fault!='stop':ready(engine,'engine');peer=start(peerArgs,'peer')
  engine.wait(timeout=30)
  reportPath=next(work.glob('rest-results/*/result.json'));report=json.loads(reportPath.read_text(encoding='utf8'))
  expected='STOPPED' if fault=='stop' else 'SUCCESS' if fault in ['none','reordered','no-processing','optional-error'] else 'FAIL'
  assert report['automaticVerdict']==expected,report
  notes=[json.loads(x) for x in (work/'notifications.jsonl').read_text(encoding='utf8').splitlines()];states=[x for x in notes if x['type']=='state']
  assert all(x['value'] in ['START','SUCCESS','FAIL','STOPPED','FINISH'] for x in states)
  assert [x['value'] for x in states if x['test']=='MainScenario']==['START',expected,'FINISH']
  if fault in ['none','reordered','optional-error']:
   if not provider:peer.wait(timeout=10)
   checked=review(reportPath,work/'sut');assert checked['verifiedExchanges']==10*len(selected);result['review']=checked
   payloads=[x for x in notes if x['type']=='info' and '메시지 순번' in x['data']];assert len(payloads)==len(selected)*20
   assert all('음영구간 미시교통정보' in x['data']['연계정보'] for x in payloads)
   if optional:
    linked=json.loads((reportPath.parent/'review-link.json').read_text(encoding='utf8'));assert linked['reviewStatus']=='PASS' and linked['finalVerdict']=='SUCCESS';result['optionalReview']='PASS'
  if fault=='no-processing':
   peer.wait(timeout=10)
   try:review(reportPath,work/'sut')
   except (AssertionError,OSError):pass
   else:raise AssertionError('Missing peer processing accepted')
  result.update(passed=True,actual=report['automaticVerdict'],items=len(selected),exchanges=report['completedExchanges'],report=str(reportPath))
 except Exception as e:result['error']=repr(e)
 finally:
  for p in processes:
   if p.poll() is None:p.terminate()
   p.wait(timeout=5)
  for f in handles:f.close()
 (work/'verification.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf8');return result

def main():
 p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();results=[]
 fields=[('field',*x) for x in field_cases()]
 errors=[('optional',{},True),('detail-empty',{'detail':[]},True),('detail-null',{'detail':None},False),('detail-type',{'detail':'bad'},False),('missing-loc',{'detail':[{'msg':'m','type':'t'}]},False),('bad-loc',{'detail':[{'loc':[True],'msg':'m','type':'t'}]},False),('bad-msg',{'detail':[{'loc':[],'msg':1,'type':'t'}]},False),('good-loc',{'detail':[{'loc':['query',1.0],'msg':'','type':''}]},True),('fraction-loc',{'detail':[{'loc':[1.1],'msg':'m','type':'t'}]},False)]
 fields += [('error',name,json.dumps(body).encode(),expected) for name,body,expected in errors]
 for i,(kind,name,body,expected) in enumerate(fields):
  f=out/f'f{i}.json';f.write_bytes(body);native=subprocess.run([str(exe),'--validate-shadow-error' if kind=='error' else '--validate-shadow','--config',str(f)],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,timeout=10,creationflags=subprocess.CREATE_NO_WINDOW)
  try:(error if kind=='error' else decode)(body);peer=True
  except (ValueError,UnicodeError):peer=False
  results.append(dict(kind=kind,name=name,expected=expected,native=native.returncode==0,peer=peer,passed=(native.returncode==0)==peer==expected))
 jobs=[(False,'all','none'),(True,'all','none'),(True,'absent','none'),(True,'empty','none')]
 for fault in ['numeric-string','range','bad-date','fraction','envelope','media','delay']:jobs.append((True,'normal',fault))
 for fault in ['wrong-code','bad-error','optional-error']:jobs.append((True,'invalid',fault))
 for fault in ['duplicate','invalid-latest','invalid-since','unknown','wrong-path','method','body','stop','no-processing']:jobs.append((False,'normal',fault))
 jobs += [(False,'normal','reordered',dict(since='-1',node_link='12345',latest='500')),(True,'normal','none',dict(since='-1',node_link='공백 +&=%',latest='500')),(False,'normal','none',dict(since='0',latest='0')),(True,'empty','none',{},False,204),(False,'normal','none',{},True),(True,'normal','none',{},True)]
 for i,job in enumerate(jobs):
  result=run(exe,out/str(i),*job);results.append(result);print(i,job,'PASS' if result['passed'] else result.get('error'),flush=True)
 summary=dict(checks=len(results),passed=sum(x['passed'] for x in results),results=results);(out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
 for r in results:
  if not r['passed']:print('FAIL',r)
 print('Shadow checks:',summary['passed'],'/',summary['checks']);return 0 if all(x['passed'] for x in results) else 1
if __name__=='__main__':raise SystemExit(main())
