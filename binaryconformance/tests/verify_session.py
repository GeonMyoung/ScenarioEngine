"""Real TCP session lifecycle checks against the independent counterpart.

Period/heartbeat timings are accelerated here. The delivered launcher campaign
separately checks its normal timing defaults and SDK notifications.
"""
import argparse,json
from pathlib import Path
from verify_binary import run,ROOT

def check(result):
 if not result['passed']:return result
 report_path=Path(result['report']);report=json.loads(report_path.read_text(encoding='utf8'))
 work=report_path.parents[2]
 events=[json.loads(x) for x in (report_path.parent/'events.jsonl').read_text(encoding='utf8').splitlines()]
 peer=[json.loads(x) for x in (work/'peer/events.jsonl').read_text(encoding='utf8').splitlines()]
 config=json.loads((work/'config.json').read_text(encoding='utf8'))
 assert report['sessionPolicy']=='single_connection_per_item'
 for item in report['items']:
  if item['verdict']=='NOT_RUN':continue
  own=[e for e in events if e.get('test')==item['test']]
  other=[e for e in peer if e.get('test')==item['test']]
  assert item['connections']==1 and item['sessionClosed']
  assert sum(e['event']=='connected' for e in own)==sum(e['event']=='connected' for e in other)==1
  assert sum(e['event']=='session_closed' for e in own)==1
  assert next(i for i,e in enumerate(own) if e['event']=='session_closed')<next(i for i,e in enumerate(own) if e['event']=='item_result')
  if item['verdict']=='SUCCESS':
   assert sum(e['event']=='session_closed' for e in other)==1
   if not item['mode'].startswith('bad_'):
    raw=[bytes.fromhex(e['hex']) for e in own if e['event']=='message']
    data=[x for x in raw if len(x)!=5]
    assert [x[4] for x in data]==[(config['first_sequence']+i)%256 for i in range(len(data))]
  if result['fault']=='close-after-three':assert item['completedExchanges']==3 and item['verdict']=='FAIL'
  if result['verdict']=='STOPPED':assert 0<item['completedExchanges']<item['requestedExchanges']
 result['sessionAssertionsPassed']=True
 return result

def main():
 p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--remaining-only',action='store_true');a=p.parse_args()
 out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();cases=json.loads((ROOT/'registration/manifest.json').read_text(encoding='utf8'))['cases'];jobs=[]
 for c in cases:
  if a.remaining_only and c['platformId'] in (68,69):continue
  jobs.append((c['case'],'TCP Server' in c['sutRole'],'all','none',{'repetitions':13,'first_sequence':250},0))
 for provider,case,key in [(True,'centerClient2signal_binary_v1','test_provide_all_status'),(False,'signalServer2center_binary_v1','test_receive_all_status')]:
  jobs.append((case,provider,key,'close-after-three',{'repetitions':17},0))
 for provider,case,key in [(True,'centerClient2signal_binary_v1','test_provide_split_status'),(False,'signalServer2center_binary_v1','test_receive_split_status')]:
  jobs.append((case,provider,key,'coalesced' if provider else 'none',{'repetitions':17,'first_sequence':255,'tcp_write_chunk_bytes':7},0))
 for fault in ['wrong-ack','wrong-ack-seq','no-ack','accept-errors']:
  jobs.append(('signalServer2center_binary_v1',False,'test_reject_bad_lrc' if fault=='accept-errors' else 'test_receive_all_status',fault,None,0))
 jobs.append(('centerClient2signal_binary_v1',True,'test_provide_all_status','partial',None,0))
 jobs.append(('signalClient2center_bsm_binary_v1',True,'test_provide_bsm_periodic','none',{'repetitions':100,'period_ms':100},650))
 results=[]
 for i,(case,provider,selection,fault,config,stop) in enumerate(jobs):
  result=run(exe,out/str(i),provider,selection,fault,config,stop,case)
  try:result=check(result)
  except Exception as error:result.update(passed=False,sessionAssertionError=repr(error))
  results.append(result);print(i,case,selection,fault,'PASS' if result['passed'] else result.get('error',result.get('sessionAssertionError')),flush=True)
  (out/'summary.json').write_text(json.dumps({'checks':len(results),'passed':sum(x['passed'] for x in results),'scope':'real loopback TCP; accelerated timing; not formal period conformance','results':results},ensure_ascii=False,indent=2),encoding='utf8')
 return 0 if all(x['passed'] for x in results) else 1
if __name__=='__main__':raise SystemExit(main())
