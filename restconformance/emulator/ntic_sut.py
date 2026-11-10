"""Independent NTIC server and requesting traffic-center peer."""
import argparse,hashlib,http.client,json,os,threading,time
from pathlib import Path
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from urllib.parse import parse_qsl,urlencode
from ntic_fields import fixture,error_body,decode,error

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--role',choices=['provider','requester'],required=True);p.add_argument('--port',type=int,required=True)
    p.add_argument('--path',choices=['/vdsInfo','//vdsInfo'],default='/vdsInfo');p.add_argument('--output',type=Path,required=True)
    p.add_argument('--data',choices=['normal','absent','empty'],default='normal');p.add_argument('--requests',type=int,default=70)
    p.add_argument('--empty-status',type=int,default=200);p.add_argument('--absence-status',type=int,default=404)
    p.add_argument('--bad-request-status',type=int,default=400);p.add_argument('--auth-status',type=int,default=401)
    p.add_argument('--fault',choices=['none','reordered','wrong-code','wrong-business','numeric-strings','wide-id','bad-date','precision','envelope','count','no-processing','missing-gettype','wrong-gettype','duplicate-key','body','wrong-path','wrong-key','method','delay'],default='none')
    a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);lock=threading.Lock()
    key=os.environ.get('REST_TEST_CREDENTIAL','NTIC_LOCAL_KEY')
    def log(event,**values):
        with lock:
            with (a.output/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,**values),ensure_ascii=False)+'\n')
    if a.role=='provider':
        source=fixture(a.data!='normal');sourceHash=hashlib.sha256(source).hexdigest();sourceRows=decode(source)
        (a.output/'source-data.body').write_bytes(source)
        (a.output/'preparation.json').write_text(json.dumps(dict(port=a.port,path=a.path,requestMode='single',dataState='available' if sourceRows else 'absent',recordCount=len(sourceRows),sourceSha256=sourceHash)),encoding='utf8')
        class Handler(BaseHTTPRequestHandler):
            def log_message(self,*args):pass
            def do_GET(self):
                raw=self.requestline.split(' ')[1];path,_,query=raw.partition('?');values=parse_qsl(query,keep_blank_values=True)
                keys=[v for k,v in values if k=='apiKey'];formats=[v for k,v in values if k=='getType'];size=int(self.headers.get('Content-Length','0'))
                status,code=200,None
                if path!=a.path:status,code=404,'4004'
                elif keys!=[key]:status,code=a.auth_status,'4005'
                elif formats!=['json'] or len(values)!=2 or size:status,code=a.bad_request_status,'4002'
                run=self.headers.get('X-Test-Run-Id','');n=int(self.headers.get('X-Test-Exchange','0'))
                log('request',runId=run,exchange=n,requestNumber=n,method='GET',path=path,queryNames=[k for k,v in values],getType=formats[0] if len(formats)==1 else None,credentialPresent=bool(keys),bodyBytes=size)
                if code is None:
                    log('data_lookup',runId=run,exchange=n,path=path,routeMatched=True,recordCount=len(sourceRows),sourceSha256=sourceHash)
                    status=a.absence_status if a.data=='absent' else a.empty_status if a.data=='empty' else 200
                body=source if status==200 and code is None else error_body(code)
                if status==204:body=b''
                if a.fault=='wrong-code' and status>=400:status=500
                if a.fault=='wrong-business' and code:body=error_body('4009')
                if status==200 and sourceRows and a.fault in ['numeric-strings','wide-id','bad-date','precision','envelope','count']:
                    value=json.loads(body)
                    if a.fault=='numeric-strings':
                        for k in ['laneNo','speed','volume','occupancy']:value['items'][0][k]=str(value['items'][0][k])
                    if a.fault=='wide-id':value['items'][0]['vdsId']='0010VDE00100'
                    if a.fault=='bad-date':value['items'][0]['colctedDate']='20260230000000'
                    if a.fault=='precision':value['items'][0]['speed']=62.501
                    if a.fault=='envelope':value={'body':value}
                    if a.fault=='count':value['totalCount']='9'
                    body=json.dumps(value).encode()
                if a.fault=='delay':time.sleep(5)
                (a.output/f'response-{n}.body').write_bytes(body)
                try:
                    self.send_response(status);self.send_header('Content-Type','application/json');self.send_header('Content-Length',str(len(body)));self.end_headers();self.wfile.write(body);self.wfile.flush()
                    log('response_sent',runId=run,exchange=n,status=status,bodySha256=hashlib.sha256(body).hexdigest())
                except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):log('peer_closed',exchange=n)
        server=ThreadingHTTPServer(('127.0.0.1',a.port),Handler);server.daemon_threads=True;log('listening',port=a.port);print('LISTENING',flush=True)
        try:server.serve_forever(poll_interval=.05)
        finally:server.server_close()
    else:
        (a.output/'requester-config.json').write_text(json.dumps(dict(baseUrl=f'http://127.0.0.1:{a.port}',path=a.path,queryNames=['apiKey','getType'],requestMode='single',credentialConfigured=True)),encoding='utf8')
        processed=[]
        for n in range(1,a.requests+1):
            query=[('apiKey','INVALID' if a.fault=='wrong-key' else key)]
            if a.fault!='missing-gettype':query.append(('getType','unsupported' if a.fault=='wrong-gettype' else 'json'))
            if a.fault=='duplicate-key':query.append(('apiKey',key))
            if a.fault=='reordered':query.reverse()
            path='/wrong' if a.fault=='wrong-path' else a.path;method='POST' if a.fault=='method' else 'GET';body=b'{}' if a.fault=='body' else None
            conn=http.client.HTTPConnection('127.0.0.1',a.port,timeout=10)
            try:
                conn.request(method,path+'?'+urlencode(query),body=body,headers={'Accept':'application/json'})
                log('request_sent',requestNumber=n,method=method,path=path,queryNames=[k for k,v in query],getType='json',credentialPresent=True,bodyBytes=len(body or b''))
                response=conn.getresponse();raw=response.read(1024*1024+1);run=response.getheader('X-Scenario-Run');exchange=int(response.getheader('X-Scenario-Exchange','0'));status=response.status
                digest=hashlib.sha256(raw).hexdigest();(a.output/f'response-{n}.body').write_bytes(raw)
                log('response_received',runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest)
                if a.fault=='no-processing':continue
                rows=[];details=None
                if status>=400:
                    action='error'
                    try:
                        data=json.loads(raw);code=data.get('resultCode')
                        if code in ['4002','4004','4005','4009']:details=error(raw,code);action='ntic-error'
                    except (ValueError,UnicodeError):action='malformed_error'
                elif status==204:action='empty'
                elif status==200:
                    try:rows=decode(raw);action='normal' if rows else 'empty'
                    except (ValueError,UnicodeError):action='malformed'
                else:action='unexpected_status'
                item=dict(runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest,action=action,records=rows)
                if details is not None:item['errorDetails']=details
                if action not in ['normal','empty']:item['errorItems']=[dict(field='response.status' if status>=400 else 'response.body',actualStatus=status,reason='NTIC error response or invalid data')]
                processed.append(item);(a.output/'processed.json').write_text(json.dumps(processed,ensure_ascii=False,indent=2),encoding='utf8');log('application_processed',**item)
            finally:conn.close()
        log('finished',processedExchanges=len(processed))
if __name__=='__main__':main()
