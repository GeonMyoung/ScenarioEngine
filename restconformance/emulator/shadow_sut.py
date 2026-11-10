"""음영구간 플랫폼 제공자 / 통합교통관제시스템 요청자 에뮬레이터."""
import argparse,hashlib,http.client,json,threading,time
from pathlib import Path
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from urllib.parse import parse_qsl,urlencode
from shadow_fields import fixture,decode,error_body,error,query_values

def main():
    p=argparse.ArgumentParser();p.add_argument('--role',choices=['provider','requester'],required=True);p.add_argument('--port',type=int,required=True)
    p.add_argument('--output',type=Path,required=True);p.add_argument('--data',choices=['normal','absent','empty'],default='normal');p.add_argument('--requests',type=int,default=70)
    p.add_argument('--params',default='{}');p.add_argument('--empty-status',type=int,default=200);p.add_argument('--absence-status',type=int,default=404)
    p.add_argument('--fault',default='none');a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);lock=threading.Lock();params=json.loads(a.params)
    def log(event,**values):
        with lock:
            with (a.output/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,**values),ensure_ascii=False)+'\n')
    def save(name,value):(a.output/name).write_text(json.dumps(value,ensure_ascii=False,indent=2),encoding='utf8')
    if a.role=='provider':
        source=fixture(a.data!='normal');sourceRows=decode(source);sourceHash=hashlib.sha256(source).hexdigest();(a.output/'source-data.body').write_bytes(source)
        save('preparation.json',dict(port=a.port,path='/data',requestMode='single',dataState='available' if sourceRows else 'absent',recordCount=len(sourceRows),sourceSha256=sourceHash))
        class Handler(BaseHTTPRequestHandler):
            def log_message(self,*args):pass
            def do_GET(self):
                path,_,query=self.requestline.split(' ')[1].partition('?');values=parse_qsl(query,keep_blank_values=True);size=int(self.headers.get('Content-Length','0'));status=200
                if path!='/data':status=404
                else:
                    try:query_values(values)
                    except ValueError:status=422
                if size:status=400
                run=self.headers.get('X-Test-Run-Id','');n=int(self.headers.get('X-Test-Exchange','0'))
                log('request',runId=run,exchange=n,requestNumber=n,method='GET',path=path,queryNames=[k for k,v in values],queryParameters=dict(values),credentialPresent=bool(self.headers.get('Authorization')),bodyBytes=size)
                if status==200:
                    log('data_lookup',runId=run,exchange=n,path=path,routeMatched=True,recordCount=len(sourceRows),sourceSha256=sourceHash)
                    status=a.absence_status if a.data=='absent' else a.empty_status if a.data=='empty' else 200
                body=source if status==200 else b'' if status==204 else error_body() if status==422 else b'Request could not be completed'
                media='application/json' if status in [200,422] else 'text/plain'
                if a.fault=='wrong-code' and status>=400:status=400
                if status==422:
                    if a.fault=='bad-error':body=b'{"detail":[{"msg":"x","type":"x"}]}'
                    if a.fault=='optional-error':body=b'{}'
                if status==200 and sourceRows:
                    value=json.loads(body)
                    if a.fault=='numeric-string':value[0]['node_link']='12345'
                    if a.fault=='range':value[0]['node_link']=100000
                    if a.fault=='bad-date':value[0]['time']='2026-07-24 13:20'
                    if a.fault=='fraction':value[0]['lane_speed']=42.5
                    if a.fault=='envelope':value=dict(items=value)
                    body=json.dumps(value).encode()
                if a.fault=='media':media='text/plain'
                if a.fault=='delay':time.sleep(5)
                (a.output/f'response-{n}.body').write_bytes(body)
                try:
                    self.send_response(status);self.send_header('Content-Type',media);self.send_header('Content-Length',str(len(body)));self.end_headers();self.wfile.write(body);self.wfile.flush()
                    log('response_sent',runId=run,exchange=n,status=status,bodySha256=hashlib.sha256(body).hexdigest())
                except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):log('peer_closed',exchange=n)
        server=ThreadingHTTPServer(('127.0.0.1',a.port),Handler);server.daemon_threads=True;log('listening',port=a.port);print('LISTENING',flush=True)
        try:server.serve_forever(poll_interval=.05)
        finally:server.server_close()
    else:
        save('requester-config.json',dict(baseUrl=f'http://127.0.0.1:{a.port}',path='/data',queryNames=list(params),queryParameters=params,requestMode='single',credentialConfigured=False))
        processed=[]
        for n in range(1,a.requests+1):
            values=list(params.items())
            if a.fault=='reordered':values.reverse()
            if a.fault=='duplicate':values += [('latest','0'),('latest','0')]
            if a.fault=='invalid-latest':values=[('latest','501')]
            if a.fault=='invalid-since':values=[('since','1.5')]
            if a.fault=='unknown':values=[('extra','1')]
            path='/wrong' if a.fault=='wrong-path' else '/data';method='POST' if a.fault=='method' else 'GET';body=b'{}' if a.fault=='body' else None
            conn=http.client.HTTPConnection('127.0.0.1',a.port,timeout=10)
            try:
                conn.request(method,path+('?' + urlencode(values) if values else ''),body=body,headers={'Accept':'application/json'})
                log('request_sent',requestNumber=n,method=method,path=path,queryNames=[k for k,v in values],queryParameters=dict(values),credentialPresent=False,bodyBytes=len(body or b''))
                response=conn.getresponse();raw=response.read(1024*1024+1);run=response.getheader('X-Scenario-Run');exchange=int(response.getheader('X-Scenario-Exchange','0'));status=response.status
                digest=hashlib.sha256(raw).hexdigest();(a.output/f'response-{n}.body').write_bytes(raw);log('response_received',runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest)
                if a.fault=='no-processing':continue
                rows=[];details=None
                if status==422:
                    try:details=error(raw);action='shadow-error'
                    except (ValueError,UnicodeError):action='malformed_error'
                elif status>=400:action='error'
                elif status==204:action='empty'
                elif status==200:
                    try:rows=decode(raw);action='normal' if rows else 'empty'
                    except (ValueError,UnicodeError):action='malformed'
                else:action='unexpected_status'
                item=dict(runId=run,exchange=exchange,requestNumber=n,status=status,bodySha256=digest,action=action,records=rows)
                if details is not None:item['errorDetails']=details
                if action not in ['normal','empty']:item['errorItems']=[dict(field='response.status' if status>=400 else 'response.body',actualStatus=status,reason='음영구간 정보 오류응답 또는 자료 형식 오류')]
                processed.append(item);save('processed.json',processed);log('application_processed',**item)
            finally:conn.close()
        log('finished',processedExchanges=len(processed))
if __name__=='__main__':main()
