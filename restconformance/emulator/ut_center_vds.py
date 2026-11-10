"""Independent SC11 UT center HTTP server, with transport evidence and fault fixtures."""
import argparse, hashlib, json, os, threading, time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

def default_records():
    return [{"collectDate":"20260924120000","stnId":"STN000000001","laneNo":1,
             "vol":24,"spd":52.35,"occ":12.50,"volS":20,"volM":3,"volL":1,
             "errCode":0,"linkId":"LNK000000001","vdsId":"VDS000000001","stnLocation":"시험 지점"}]

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--port',type=int,default=55311);p.add_argument('--bind',default='127.0.0.1')
    p.add_argument('--output',required=True);p.add_argument('--fixture')
    p.add_argument('--mode',default='normal',choices=['normal','optional-missing','missing','type','malformed','object','empty','null','status','content-type','duplicate','utf8','delay','large','integer'])
    p.add_argument('--max-requests',type=int,default=0);p.add_argument('--delay',type=float,default=5)
    a=p.parse_args();out=Path(a.output);out.mkdir(parents=True,exist_ok=False)
    token=os.environ.get('VDS_TEST_BEARER_TOKEN','vds-development-token')
    lock=threading.Lock();count=0
    def record(event,**data):
        with lock:
            with (out/'events.jsonl').open('a',encoding='utf8') as f:
                f.write(json.dumps(dict(event=event,monotonicNs=time.monotonic_ns(),**data),ensure_ascii=False)+'\n')
    class Handler(BaseHTTPRequestHandler):
        def log_message(self,*args): pass
        def do_GET(self):
            nonlocal count
            with lock: count+=1; n=count
            accepted=self.path=='/v1/adxc/vds-l-raws' and self.headers.get('Authorization')=='Bearer '+token and not self.headers.get('Content-Length','0').strip('0')
            run=self.headers.get('X-Test-Run-Id','');exchange=self.headers.get('X-Test-Exchange','')
            record('request',requestNumber=n,runId=run,exchange=exchange,method=self.command,path=self.path,
                   authorizationMatched=self.headers.get('Authorization')=='Bearer '+token,bodyBytes=int(self.headers.get('Content-Length','0')),accepted=accepted)
            value=default_records()
            if a.mode=='optional-missing':
                for key in ['volS','volM','volL']:del value[0][key]
            if a.mode=='missing':del value[0]['stnId']
            if a.mode=='type':value[0]['vol']='24'
            if a.mode=='integer':value[0]['laneNo']=1.5
            if a.mode=='null':value[0]['stnId']=None
            if a.mode=='object':value={'data':value}
            if a.mode=='empty':value=[]
            body=Path(a.fixture).read_bytes() if a.fixture else json.dumps(value,ensure_ascii=False,separators=(',',':')).encode()
            if a.mode=='malformed':body=b'[{'
            if a.mode=='duplicate':body=body.replace(b'"laneNo":1',b'"laneNo":1,"laneNo":2')
            if a.mode=='utf8':body=body.replace('시험'.encode(),b'\xff')
            if a.mode=='large':body=b' '* (1024*1024+1)
            if a.mode=='delay':time.sleep(a.delay)
            status=200 if accepted else 400
            if a.mode=='status':status=500
            content='text/plain' if a.mode=='content-type' else 'application/json;charset=UTF-8'
            (out/f'response-{n}.json').write_bytes(body)
            try:
                self.send_response(status);self.send_header('Content-Type',content);self.send_header('Content-Length',str(len(body)));self.end_headers();self.wfile.write(body);self.wfile.flush()
                record('response_sent',requestNumber=n,runId=run,exchange=exchange,status=status,bodySha256=hashlib.sha256(body).hexdigest())
            except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):record('peer_closed',requestNumber=n)
            if a.max_requests and n>=a.max_requests:threading.Thread(target=self.server.shutdown,daemon=True).start()
    server=ThreadingHTTPServer((a.bind,a.port),Handler);server.daemon_threads=True
    record('listening',ip=a.bind,port=a.port);print('LISTENING',a.port,flush=True)
    try:server.serve_forever(poll_interval=.05)
    finally:server.server_close();record('stopped')
if __name__=='__main__':main()
