"""Independent UTIC HTTP server SUT for the SC28 incident providing test."""
import argparse,hashlib,json,os,threading,time
from pathlib import Path
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from urllib.parse import urlsplit,parse_qsl
import xml.etree.ElementTree as ET

def fixture(mode='normal'):
    fields={'incidentId':'202609240001','incidenteTypeCd':'1','incidenteSubTypeCd':'101',
        'addressJibun':'시험시 시험구 시험동','addressJibunCd':'1114010300','addressNew':'시험시 시험로',
        'linkId':'1234567890','locationDataX':'126.978400000','locationDataY':'37.566500000',
        'locationTypeCd':'C0101','locationData':'','incidenteTrafficCd':'A0503','incidenteGradeCd':'A0401',
        'incidentTitle':'시험용 돌발정보','incidentRegionCd':'11','startDate':'2026년 09월 24일 09시 00분',
        'endDate':'2026년 09월 24일 10시 00분','lane':'2','roadName':'시험로','sourceCode':'UTIC',
        'controlType':'1','lineLinkId':'1234567890','important':'01','updateDate':'2026년 09월 24일 09시 01분'}
    if mode=='missing':del fields['incidentId']
    if mode=='code':fields['incidenteTypeCd']='99'
    if mode=='date':fields['startDate']='20260230090000'
    if mode=='numeric':fields['locationDataX']='NaN'
    root=ET.Element('wrong' if mode=='root' else 'result')
    if mode=='namespace':root.set('xmlns','urn:unexpected')
    if mode!='empty':
        row=ET.SubElement(root,'record')
        for k,v in fields.items():ET.SubElement(row,k).text=v
        if mode=='duplicate':ET.SubElement(row,'incidentId').text='duplicate'
    data=ET.tostring(root,encoding='utf-8',xml_declaration=True)
    if mode=='malformed':data=b'<result><record>'
    if mode=='dtd':data=b'<!DOCTYPE result [<!ENTITY x "entity">]>'+data.split(b'?>',1)[1]
    if mode=='utf8':data=data.replace('시험용'.encode(),b'\xff')
    if mode=='large':data=b' '*(1024*1024+1)
    return data

def main():
    p=argparse.ArgumentParser();p.add_argument('--bind',default='127.0.0.1');p.add_argument('--port',type=int,default=55328)
    p.add_argument('--output',required=True);p.add_argument('--fixture');p.add_argument('--mode',default='normal',choices=['normal','text-xml','missing','duplicate','code','date','numeric','root','namespace','empty','malformed','dtd','utf8','status','content-type','large','delay']);p.add_argument('--delay',type=float,default=5)
    a=p.parse_args();out=Path(a.output);out.mkdir(parents=True,exist_ok=False);key=os.environ.get('UTIC_TEST_API_KEY','SC28_LOCAL_KEY');lock=threading.Lock();count=0
    def record(event,**fields):
        with lock:
            with (out/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,**fields),ensure_ascii=False)+'\n')
    class Handler(BaseHTTPRequestHandler):
        def log_message(self,*args):pass
        def do_GET(self):
            nonlocal count
            with lock:count+=1;n=count
            path=urlsplit(self.path);query=parse_qsl(path.query,keep_blank_values=True);bodyBytes=int(self.headers.get('Content-Length','0'))
            accepted=path.path=='/guide/imsOpenData.do' and query==[('key',key)] and bodyBytes==0
            run=self.headers.get('X-Test-Run-Id','');exchange=self.headers.get('X-Test-Exchange','')
            record('request',requestNumber=n,runId=run,exchange=exchange,method=self.command,path=path.path,queryNames=[x[0] for x in query],queryKeyRedacted=True,keyMatched=query==[('key',key)],bodyBytes=bodyBytes,accept=self.headers.get('Accept'),accepted=accepted)
            data=Path(a.fixture).read_bytes() if a.fixture else fixture(a.mode)
            if a.mode=='delay':time.sleep(a.delay)
            status=200 if accepted else 400
            if a.mode=='status':status=500
            media='application/json' if a.mode=='content-type' else 'text/xml' if a.mode=='text-xml' else 'application/xml'
            (out/f'response-{n}.xml').write_bytes(data)
            try:
                self.send_response(status);self.send_header('Content-Type',media+';charset=UTF-8');self.send_header('Content-Length',str(len(data)));self.end_headers();self.wfile.write(data);self.wfile.flush()
                record('response_sent',requestNumber=n,runId=run,exchange=exchange,status=status,bodySha256=hashlib.sha256(data).hexdigest())
            except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):record('peer_closed',requestNumber=n)
    server=ThreadingHTTPServer((a.bind,a.port),Handler);server.daemon_threads=True
    record('listening',port=a.port);print('LISTENING',a.port,flush=True)
    try:server.serve_forever(poll_interval=.05)
    finally:server.server_close();record('stopped')
if __name__=='__main__':main()
