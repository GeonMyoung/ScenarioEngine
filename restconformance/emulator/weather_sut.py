"""기상청 제공자 / 통합교통관제시스템 요청자 역할의 독립 HTTP 상대."""
import argparse,hashlib,http.client,json,os,threading,time
from pathlib import Path
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from urllib.parse import parse_qsl,urlencode
from weather_fields import DEFAULT,PATH,FORECAST,fixture,decode,error_body,error,query_values

def main():
 p=argparse.ArgumentParser();p.add_argument('--role',choices=['provider','requester'],required=True);p.add_argument('--port',type=int,required=True);p.add_argument('--output',type=Path,required=True)
 p.add_argument('--path',choices=[PATH,FORECAST],default=PATH);p.add_argument('--key-name',choices=['serviceKey','ServiceKey'],default='serviceKey');p.add_argument('--params',default='{}')
 p.add_argument('--data',choices=['normal','absent','empty'],default='normal');p.add_argument('--requests',type=int,default=70);p.add_argument('--fault',default='none')
 for name,value in [('empty',200),('absence',200),('bad-request',200),('auth',200),('missing-path',404)]:p.add_argument('--'+name+'-status',type=int,default=value)
 a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);key=os.environ.get('REST_TEST_CREDENTIAL','WEATHER_LOCAL_KEY');params=DEFAULT|json.loads(a.params);lock=threading.Lock()
 def log(event,**v):
  with lock:
   with (a.output/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,**v),ensure_ascii=False)+'\n')
 def save(name,v):(a.output/name).write_text(json.dumps(v,ensure_ascii=False,indent=2),encoding='utf8')
 if a.role=='provider':
  source=fixture(a.data!='normal',params);sourceRows=decode(source);sourceHash=hashlib.sha256(source).hexdigest();(a.output/'source-data.body').write_bytes(source)
  save('preparation.json',dict(port=a.port,path=a.path,requestMode='single',dataState='available' if sourceRows else 'absent',recordCount=len(sourceRows),sourceSha256=sourceHash))
  class Handler(BaseHTTPRequestHandler):
   def log_message(self,*args):pass
   def do_GET(self):
    path,_,q=self.requestline.split(' ')[1].partition('?');values=parse_qsl(q,keep_blank_values=True);keys=[v for k,v in values if k==a.key_name];size=int(self.headers.get('Content-Length','0'));code=None;status=200
    if path!=a.path:status,code=a.missing_path_status,'12'
    elif not keys:status,code=a.auth_status,'20'
    elif keys!=[key]:status,code=a.auth_status,'30'
    else:
     try:query_values(values,a.key_name)
     except ValueError:status,code=a.bad_request_status,'10'
    if size:status,code=a.bad_request_status,'10'
    run=self.headers.get('X-Test-Run-Id','');n=int(self.headers.get('X-Test-Exchange','0'))
    log('request',runId=run,exchange=n,requestNumber=n,method='GET',path=path,queryNames=[k for k,v in values],queryParameters={k:v for k,v in values if k!=a.key_name},credentialPresent=bool(keys),bodyBytes=size)
    if code is None:
     log('data_lookup',runId=run,exchange=n,path=path,routeMatched=True,recordCount=len(sourceRows),sourceSha256=sourceHash)
     if a.data=='absent':status,code=a.absence_status,'03'
     elif a.data=='empty':status=a.empty_status
    body=error_body(code) if code else b'' if status==204 else source;media='application/json'
    if a.fault=='wrong-code' and code:body=error_body('99')
    if a.fault=='success-on-error' and code:body=fixture(False,params)
    if a.fault=='wrong-status' and code:status=500
    if a.fault=='no-message' and code:body=json.dumps({'response':{'header':{'resultCode':code}}}).encode()
    if a.fault=='error-data' and code:body=json.dumps({'response':{'header':{'resultCode':code,'resultMsg':'bad'},'body':{'items':{'item':[{}]}}}}).encode()
    if not code and status==200 and sourceRows:
     value=json.loads(body);row=value['response']['body']['items']['item'][0]
     if a.fault=='numeric-string':row['t1h']='23.5'
     if a.fault=='bad-date':row['adstrdCode']='11680640'
     if a.fault=='fraction':row['t1h']=23.55
     if a.fault=='sky':row['sky']=2
     if a.fault=='api-fields':value['response']['body']['items']['item']=[dict(baseDate='20260924',baseTime='0600',nx=55,ny=127,category='T1H',obsrValue='23.5')]
     if a.fault=='envelope':value=value['response']['body']['items']['item']
     if a.fault=='count':value['response']['body']['totalCount']=2
     if a.fault=='page':value['response']['body']['pageNo']=2;value['response']['body']['totalCount']=11
     body=json.dumps(value).encode()
    if a.fault=='media':media='text/plain'
    if a.fault=='delay':time.sleep(5)
    (a.output/f'response-{n}.body').write_bytes(body)
    try:
     self.send_response(status);self.send_header('Content-Type',media);self.send_header('Content-Length',str(len(body)));self.end_headers();self.wfile.write(body);self.wfile.flush();log('response_sent',runId=run,exchange=n,status=status,bodySha256=hashlib.sha256(body).hexdigest())
    except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):log('peer_closed',exchange=n)
  server=ThreadingHTTPServer(('127.0.0.1',a.port),Handler);server.daemon_threads=True;log('listening',port=a.port);print('LISTENING',flush=True)
  try:server.serve_forever(poll_interval=.05)
  finally:server.server_close()
 else:
  save('requester-config.json',dict(baseUrl=f'http://127.0.0.1:{a.port}',path=a.path,queryNames=[*params,a.key_name],queryParameters=params,requestMode='single',credentialConfigured=True,serviceKeyName=a.key_name));processed=[]
  for n in range(1,a.requests+1):
   values=list(params.items())+[(a.key_name,'INVALID' if a.fault=='wrong-key' else key)]
   if a.fault=='reordered':values.reverse()
   if a.fault=='duplicate':values.append(('nx','55'))
   if a.fault=='missing-json':values=[(k,v) for k,v in values if k!='dataType']
   if a.fault=='missing-date':values=[(k,v) for k,v in values if k!='base_date']
   if a.fault=='wrong-name':values=[('ServiceKey' if a.key_name=='serviceKey' else 'serviceKey',v) if k==a.key_name else (k,v) for k,v in values]
   if a.fault=='bad-time':values=[(k,'2500' if k=='base_time' else v) for k,v in values]
   if a.fault=='unknown':values.append(('extra','1'))
   path='/wrong' if a.fault=='wrong-path' else a.path;method='POST' if a.fault=='method' else 'GET';body=b'{}' if a.fault=='body' else None
   conn=http.client.HTTPConnection('127.0.0.1',a.port,timeout=10)
   try:
    conn.request(method,path+'?'+urlencode(values),body=body,headers={'Accept':'application/json'});log('request_sent',requestNumber=n,method=method,path=path,queryNames=[k for k,v in values],queryParameters={k:v for k,v in values if k not in ['serviceKey','ServiceKey']},credentialPresent=True,bodyBytes=len(body or b''))
    response=conn.getresponse();raw=response.read(1024*1024+1);run=response.getheader('X-Scenario-Run');exchange=int(response.getheader('X-Scenario-Exchange','0'));status=response.status;digest=hashlib.sha256(raw).hexdigest();(a.output/f'response-{n}.body').write_bytes(raw)
    log('response_received',runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest)
    if a.fault=='no-processing':continue
    rows=[];details=None
    try:
     value=json.loads(raw) if raw else {};code=value.get('response',{}).get('header',{}).get('resultCode') if isinstance(value,dict) else None
     if code and code!='00':details=error(raw);action='error' if code=='03' else 'weather-error'
     elif status==204:action='empty'
     elif status==200:rows=decode(raw);action='normal' if rows else 'empty'
     else:action='error'
    except (ValueError,UnicodeError):action='malformed'
    item=dict(runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest,action=action,records=rows)
    if details is not None:item['errorDetails']=details
    if action not in ['normal','empty']:item['errorItems']=[dict(field='response.body' if status==200 else 'response.status',actualStatus=status,reason='기상정보 업무 오류 또는 자료 형식 오류')]
    processed.append(item);save('processed.json',processed);log('application_processed',**item)
   finally:conn.close()
  log('finished',processedExchanges=len(processed))
if __name__=='__main__':main()
