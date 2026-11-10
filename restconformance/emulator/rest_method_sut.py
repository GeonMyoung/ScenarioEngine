"""Independent REST peers: act on wire requests/responses, never tester selection names."""
import argparse,hashlib,http.client,json,os,threading,time
import xml.etree.ElementTree as ET
from pathlib import Path
from urllib.parse import parse_qsl,urlsplit,urlencode
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from utic_provider import fixture
from ut_center_vds import default_records
from smart_traffic import default_records as smart_records, validate_records as validate_smart
from standard_fields import utic as validate_utic, vds as validate_vds

def decoded(body,fmt,information="vds"):
    if fmt=='xml':return validate_utic(body)
    if information=='smart':return validate_smart(json.loads(body.decode('utf8')))
    return validate_vds(body)

def main():
    p=argparse.ArgumentParser();p.add_argument('--role',choices=['provider','requester'],required=True);p.add_argument('--format',choices=['xml','json'],required=True)
    p.add_argument('--information',choices=['vds','smart'],default='vds')
    p.add_argument('--output',type=Path,required=True);p.add_argument('--port',type=int,required=True);p.add_argument('--requests',type=int,default=60)
    p.add_argument('--data',choices=['normal','empty','absent'],default='normal');p.add_argument('--bad-request-status',type=int,default=400);p.add_argument('--auth-status',type=int,default=401);p.add_argument('--empty-status',type=int,default=200)
    p.add_argument('--absence-status',type=int,choices=[400,404,410,422],default=404)
    p.add_argument('--fault',choices=['none','wrong-code','success-on-error','malformed-normal','no-processing','accept-malformed','delay','empty-error-body','malformed-error','wrong-error-type','wrong-error-date','invalid-error-utf8','minimal-error','api-schema','wrong-smart-type','smart-missing-field','smart-bad-date','smart-precision','fake-absence','path-not-found','no-error-log','wrong-valid-data'],default='none')
    a=p.parse_args();a.output.mkdir(parents=True,exist_ok=False);lock=threading.Lock();count=0
    credential=os.environ.get('REST_TEST_CREDENTIAL','SC07_LOCAL_KEY' if a.format=='xml' else 'vds-development-token')
    path='/guide/imsOpenData.do' if a.format=='xml' else '/v1/adxc/smt-l-raws' if a.information=='smart' else '/v1/adxc/vds-l-raws';media='application/xml' if a.format=='xml' else 'application/json'
    normal=fixture() if a.format=='xml' else json.dumps(smart_records() if a.information=='smart' else default_records(),ensure_ascii=False).encode()
    empty=b'<result/>' if a.format=='xml' else b'[]'
    def log(event,**values):
        with lock:
            with (a.output/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,**values),ensure_ascii=False)+'\n')
    if a.role=='provider':
        source=empty if a.data in ['empty','absent'] else normal
        sourceRows=decoded(source,a.format,a.information)
        sourceHash=hashlib.sha256(source).hexdigest()
        (a.output/'source-data.body').write_bytes(source)
        (a.output/'preparation.json').write_text(json.dumps(dict(port=a.port,path=path,requestMode='single',dataState='absent' if not sourceRows else 'available',recordCount=len(sourceRows),sourceSha256=sourceHash),ensure_ascii=False),encoding='utf8')
        class Handler(BaseHTTPRequestHandler):
            def log_message(self,*args):pass
            def do_GET(self):
                nonlocal count
                with lock:count+=1;n=count
                uri=urlsplit(self.path);query=parse_qsl(uri.query,keep_blank_values=True);bodyBytes=int(self.headers.get('Content-Length','0'))
                status=200
                if uri.path!=path:status=404
                elif bodyBytes:status=a.bad_request_status
                elif a.format=='xml':
                    keys=[v for k,v in query if k=='key']
                    if len(keys)>1 or any(k!='key' for k,v in query):status=a.bad_request_status
                    elif len(keys)!=1 or keys[0]!=credential:status=a.auth_status
                else:
                    if query:status=a.bad_request_status
                    elif self.headers.get_all('Authorization')!=['Bearer '+credential]:status=a.auth_status
                if status==200:
                    log('data_lookup',requestNumber=n,runId=self.headers.get('X-Test-Run-Id',''),exchange=self.headers.get('X-Test-Exchange',''),path=uri.path,routeMatched=a.fault!='path-not-found',recordCount=len(sourceRows),sourceSha256=sourceHash)
                    if a.data=='empty':status=a.empty_status
                    elif a.data=='absent':status=a.absence_status
                    if a.fault in ['fake-absence','path-not-found']:status=a.absence_status
                response=empty if a.data=='empty' and status==200 else normal if status==200 else b'Error response without a prescribed body schema'
                if a.format=='json' and a.information!='smart' and status in [400,500]:
                    error=dict(code=str(status),message='Request could not be completed',time='2026-09-24T00:00:00Z',path=uri.path)
                    if a.fault=='wrong-error-type':error['code']=400
                    if a.fault=='wrong-error-date':error['time']='2026-02-30T00:00:00Z'
                    response=json.dumps(error).encode()
                    if a.fault=='malformed-error':response=b'{'
                    if a.fault=='invalid-error-utf8':response=b'{"message":"\xff"}'
                    if a.fault=='minimal-error':response=b'{}'
                if status==204:response=b''
                if a.fault=='empty-error-body' and status>=400:response=b''
                if a.fault=='wrong-code' and status>=400:status=500
                if a.fault=='success-on-error' and status>=400:status=200;response=normal
                if a.fault=='malformed-normal' and status==200:response=b'<broken' if a.format=='xml' else b'[{'
                if a.information=='smart' and status==200 and a.fault in ['api-schema','wrong-smart-type','smart-missing-field','smart-bad-date','smart-precision']:
                    bad=smart_records()
                    if a.fault=='api-schema':bad=[dict(totDt='20260811153000',intId='NODE000001',acsrId='ASCR000001',drtcCd='1',laneNo=1,vkndCd='1',spd=42.5,vol=15,moctLinkId='LINK000001',collectDate='20260811153000')]
                    elif a.fault=='wrong-smart-type':bad[0]['vkndCd']='1'
                    elif a.fault=='smart-missing-field':del bad[0]['ascrId']
                    elif a.fault=='smart-bad-date':bad[0]['collectDate']='20260230153000'
                    elif a.fault=='smart-precision':bad[0]['spd']=42.501
                    response=json.dumps(bad).encode()
                if a.fault=='wrong-valid-data' and status==200:
                    if a.format=='xml':
                        root=ET.fromstring(response);root.find('record/incidentTitle').text='Different prepared data';response=ET.tostring(root,encoding='utf-8')
                    else:
                        value=json.loads(response);value[0]['vol']+=1;response=json.dumps(value).encode()
                if a.fault=='delay':time.sleep(5)
                run=self.headers.get('X-Test-Run-Id','');exchange=self.headers.get('X-Test-Exchange','')
                log('request',requestNumber=n,runId=run,exchange=exchange,method='GET',path=uri.path,queryNames=[k for k,v in query],credentialPresent=any(k=='key' for k,v in query) if a.format=='xml' else self.headers.get('Authorization') is not None,bodyBytes=bodyBytes)
                (a.output/f'response-{n}.body').write_bytes(response)
                try:
                    self.send_response(status);self.send_header('Content-Type',media if status==200 or a.format=='json' and a.information!='smart' and status in [400,500] else 'text/plain');self.send_header('Content-Length',str(len(response)));self.end_headers();self.wfile.write(response);self.wfile.flush()
                    log('response_sent',runId=run,exchange=exchange,status=status,bodySha256=hashlib.sha256(response).hexdigest())
                except (BrokenPipeError,ConnectionResetError,ConnectionAbortedError):log('peer_closed',requestNumber=n)
        server=ThreadingHTTPServer(('127.0.0.1',a.port),Handler);server.daemon_threads=True;log('listening',port=a.port);print('LISTENING',flush=True)
        try:server.serve_forever(poll_interval=.05)
        finally:server.server_close()
    else:
        (a.output/'requester-config.json').write_text(json.dumps(dict(baseUrl=f'http://127.0.0.1:{a.port}',path=path,requestMode='single',queryNames=['key'] if a.format=='xml' else [],credentialConfigured=True)),encoding='utf8')
        processed=[]
        for n in range(1,a.requests+1):
            conn=http.client.HTTPConnection('127.0.0.1',a.port,timeout=10)
            try:
                url=path+'?'+urlencode({'key':credential}) if a.format=='xml' else path
                headers={'Accept':media}
                if a.format=='json':headers['Authorization']='Bearer '+credential
                conn.request('GET',url,headers=headers);log('request_sent',requestNumber=n,method='GET',path=path,queryNames=['key'] if a.format=='xml' else [],credentialPresent=True,bodyBytes=0);r=conn.getresponse();body=r.read(1024*1024+1)
                run=r.getheader('X-Scenario-Run');exchange=int(r.getheader('X-Scenario-Exchange','0'));status=r.status
                digest=hashlib.sha256(body).hexdigest();(a.output/f'response-{n}.body').write_bytes(body)
                log('response_received',requestNumber=n,runId=run,exchange=exchange,status=status,bodySha256=digest)
                if a.fault=='no-processing':continue
                rows=[];errorDetails=None
                if status>=400:
                    action='error'
                    if a.format=='json' and a.information!='smart' and status in [400,500]:
                        try:
                            errorDetails=json.loads(body)
                            if not isinstance(errorDetails,dict) or any(k in errorDetails and not isinstance(errorDetails[k],str) for k in ['code','message','time','path']):raise ValueError('Error schema mismatch')
                            action='error-schema'
                        except (ValueError,UnicodeError):action='malformed_error'
                elif status==204:action='empty'
                elif status==200:
                    try:rows=decoded(body,a.format,a.information);action='normal' if rows else 'empty'
                    except (ValueError,ET.ParseError,UnicodeError):action='normal' if a.fault=='accept-malformed' else 'malformed'
                else:action='unexpected_status'
                record=dict(requestNumber=n,runId=run,exchange=exchange,status=status,bodySha256=digest,action=action,records=rows)
                if errorDetails is not None:record['errorDetails']=errorDetails
                if action not in ['normal','empty'] and a.fault!='no-error-log':
                    record['errorItems']=[dict(field='response.status' if status>=400 else 'response.body',actualStatus=status,reason='HTTP error response' if status>=400 else 'Information could not be parsed or processed')]
                processed.append(record);(a.output/'processed.json').write_text(json.dumps(processed,ensure_ascii=False,indent=2),encoding='utf8')
                log('application_processed',**record)
            finally:conn.close()
        log('finished',processedExchanges=len(processed))
if __name__=='__main__':main()
