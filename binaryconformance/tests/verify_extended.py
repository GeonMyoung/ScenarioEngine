import argparse,copy,json,math,struct,subprocess,sys
from pathlib import Path
from verify_binary import run
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'emulator'))
from signal_codec import fixture,encode,decode,packet,frame
from extended_codec import CASES

def codec(exe,out):
 results=[]
 def check(name,msg,rows,ok=True):
  p=out/(str(len(results))+'.json');p.write_text(json.dumps(rows,ensure_ascii=False),encoding='utf8')
  native=subprocess.run([str(exe),'--operation','encode','--message',str(msg),'--config',str(p)],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10)
  try:b=packet(msg,2,0,encode(msg,rows));peer=True
  except (ValueError,OverflowError,UnicodeError,KeyError):peer=False;b=None
  passed=(native.returncode==0)==peer==ok
  if passed and ok:
   raw=bytes.fromhex(native.stdout.decode());passed=raw==b
   back=subprocess.run([str(exe),'--operation','decode','--hex',raw.hex()],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10)
   passed=passed and back.returncode==0 and json.loads(back.stdout)==decode(msg,b[5:-1])
  results.append(dict(kind='codec',name=name,message=msg,passed=passed))
 for msg in [67,71,72]:
  rows=fixture(msg,count=2);check('normal-multiple',msg,rows)
  if msg==67:assert len(encode(msg,fixture(msg)))==64
  if msg==71:
   b=encode(msg,fixture(msg));assert len(b)==97 and b[:7].hex()=='07ea09190a1e00' and b[23]==1 and b[48]==2 and b[49:69]==(1).to_bytes(20,'big')
  if msg==72:assert len(encode(msg,fixture(msg)))==633
  for k in list(rows[0]):
   r=copy.deepcopy(rows);r[0].pop(k);check('missing-'+k,msg,r,False)
 for k in ['LONGITUDE','LATITUDE','ALTITUDE','ANGLE','SPEED']:
  for value,ok in [(0.1,True),(-123.25,True),('1',False),(True,False),(float('inf'),False),(float('nan'),False),(1e300,k in ['LONGITUDE','LATITUDE']),(1e-100,k in ['LONGITUDE','LATITUDE'])]:
   r=fixture(67);r[0][k]=value;check(k+'-'+str(value),67,r,ok)
 for k,width in [('CREDATE',8),('VEH_ID',16),('VEH_NO',8),('GEAR',4)]:
  for value in [1,'', 'X'*(width+1)]:
   r=fixture(67);r[0][k]=value;check(k+'-invalid',67,r,False)
 for value in ['20260230','00000101']:
  r=fixture(67);r[0]['CREDATE']=value;check('CREDATE-calendar',67,r,False)
 for msg in [71,72]:
  for key,v in [('Month',13),('Day',32),('Hour',24),('Minute',60),('Second',60),('Year',0)]:
   r=fixture(msg);r[0][key.upper() if msg==72 else key]=v;check(key+'-range',msg,r,False)
  r=fixture(msg);r[0].update({'YEAR':2024,'MONTH':2,'DAY':29} if msg==72 else dict(Year=2024,Month=2,Day=29));check('leap',msg,r)
 for value,ok in [('0',True),(str((1<<160)-1),True),(str(1<<160),False),('-1',False),('1.1',False),(True,False)]:
  r=fixture(71);r[0]['pol6IndivAdInfoDtoList'][0]['pol6RouteIntoDtoList'][0]['viaLinkSeq']=value;check('wide-'+str(value),71,r,ok)
 for field,value,ok in [('linkPos',16777215,True),('linkPos',16777216,False),('linkInfoType',255,True),('linkInfoType',256,False),('viaLinkNo',3,False)]:
  r=fixture(71);r[0]['pol6IndivAdInfoDtoList'][0][field]=value;check(field+'-count/width',71,r,ok)
 for field,width in [('EVENT_ID',18),('EVENT_NM',499),('INC_TY',2),('INC_DTL_TY',4),('OCRN_LOT',20),('OCRN_LAT',20),('OCRN_LINK_ID',10),('CNTRL_TY',1),('PRGRS_STTS',2)]:
  for value,ok in [('X'*width,True),('X'*(width+1),False),('',False),(None,False)]:
   r=fixture(72);r[0][field]=value;check(field+'-'+str(len(value) if isinstance(value,str) else value),72,r,ok)
 for field in ['OCRN_DT','END_DT']:
  for value,ok in [('00000000000000',field=='END_DT'),('20260230000000',False),('20240229235959',True)]:
   r=fixture(72);r[0][field]=value;check(field+'-date',72,r,ok)
 for msg in [71,72]:
  r=fixture(msg)
  if msg==71:r[0]['indivAdIdNo']=2
  else:r[0]['LINK_COUNT']=3
  check('count-mismatch',msg,r,False)
 # Receive-side NaN, invalid variable count, and trailing bytes must fail too.
 for msg in [67,71,72]:
  b=bytearray(encode(msg,fixture(msg)))
  if msg==67:b[60:64]=bytes.fromhex('7fc00000')
  elif msg==71:b[48]=3
  else:b[612]=3
  for name,payload in [('mutated',bytes(b)),('trailing',encode(msg,fixture(msg))+b'\x00')]:
   raw=packet(msg,2,0,payload);r=subprocess.run([str(exe),'--operation','decode','--hex',raw.hex()],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=10);results.append(dict(kind='decode',name=name,message=msg,passed=r.returncode!=0))
 return results

def main():
 p=argparse.ArgumentParser();p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();out=a.output.resolve();out.mkdir(parents=True,exist_ok=False);exe=a.exe.resolve();results=codec(exe,out);jobs=[]
 for case,(provider,msg,_) in CASES.items():
  jobs.append((case,provider,'all','none',None,0))
  jobs.append((case,provider,'split','coalesced' if provider else 'none',{'first_sequence':255,'char_encoding':'CP949','lrc_mode':'sum8','ack_seq_mode':'fixed1'},0))
  if provider:
   for fault in ['bad-date','legacy-layout','large-data']:jobs.append((case,provider,'multiple' if fault=='large-data' else 'normal',fault,None,0))
   if msg in [67,71]:jobs.append((case,provider,'normal','nonfinite',None,0))
   if msg!=67:
    jobs.append((case,provider,'normal','count-mismatch',None,0));jobs.append((case,provider,'empty','nonempty-heartbeat',None,0));jobs.append((case,provider,'change','same-event',None,0))
  else:
   jobs.append((case,provider,'bad_payload','accept-errors',None,0));jobs.append((case,provider,'normal','no-processing',None,0));jobs.append((case,provider,'normal','none',None,300))
  if msg!=67:jobs.append((case,provider,'empty','none',{'heartbeat_ack':False},0))
 # Same executable also runs both existing signal/TOD scenarios.
 jobs += [('signalServer2center_binary_v1',False,'all','none',None,0),('centerClient2signal_binary_v1',True,'all','none',None,0)]
 for i,(case,provider,selection,fault,overrides,stop) in enumerate(jobs):
  r=run(exe,out/('r'+str(i)),provider,selection,fault,overrides,stop,case);results.append(r);print(i,case,selection,fault,'PASS' if r['passed'] else r.get('error'),flush=True)
 summary=dict(checks=len(results),passed=sum(r['passed'] for r in results),results=results);(out/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf8')
 for r in results:
  if not r['passed']:print('FAIL',r)
 print('Extended Binary checks:',summary['passed'],'/',summary['checks']);return 0 if all(r['passed'] for r in results) else 1
if __name__=='__main__':raise SystemExit(main())
