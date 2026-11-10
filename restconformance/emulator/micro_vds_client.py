"""Independent microscopic traffic platform HTTP client SUT for SC32."""
import argparse, hashlib, http.client, json, time
from pathlib import Path
from urllib.parse import urlsplit
from standard_fields import vds as validate_vds

def execute(config,output,fault='none'):
    output=Path(output);output.mkdir(parents=True,exist_ok=False);processed=[]
    def event(name,**fields):
        with (output/'events.jsonl').open('a',encoding='utf8') as f:
            f.write(json.dumps(dict(event=name,monotonicUs=time.monotonic_ns()//1000,**fields),ensure_ascii=False)+'\n')
    base=urlsplit(config['base_url']);count=config.get('repetitions',10)-(fault=='too-few')
    try:
        for n in range(1,count+1):
            method='POST' if fault=='wrong-method' else 'GET'
            path='/wrong' if fault=='wrong-path' else '/v1/adxc/vds-l-raws'
            if fault=='query':path+='?unexpected=1'
            body=b'{}' if fault=='body' else b''
            token='wrong-token' if fault=='wrong-token' else config['bearer_token']
            auth=('bearer' if fault=='lowercase-auth' else 'Bearer')+' '+token
            cls=http.client.HTTPSConnection if base.scheme=='https' else http.client.HTTPConnection
            conn=cls(base.hostname,base.port,timeout=config.get('request_timeout_s',30))
            try:
                conn.putrequest(method,path);conn.putheader('Accept','application/json')
                if fault!='missing-auth':conn.putheader('authorization' if fault=='lowercase-auth' else 'Authorization',auth)
                if fault=='duplicate-auth':conn.putheader('Authorization',auth)
                if body or method=='POST':conn.putheader('Content-Length',str(len(body)))
                conn.endheaders(body or None);event('request_sent',exchange=n,method=method,path=path,bodyBytes=len(body),authorizationRedacted=True)
                response=conn.getresponse();data=response.read(1024*1024+1)
                if response.status!=200 or len(data)>1024*1024:raise ValueError('Unexpected HTTP status or body size')
                if response.headers.get_content_type()!='application/json':raise ValueError('Unexpected media type')
                run=response.getheader('X-Scenario-Run');exchange=int(response.getheader('X-Scenario-Exchange','0'))
            finally:conn.close()
            digest=hashlib.sha256(data).hexdigest();(output/f'response-{n:04d}.json').write_bytes(data)
            event('response_received',runId=run,exchange=exchange,bodySha256=digest,bodyBytes=len(data),status=200)
            if fault=='no-processing':continue
            value=validate_vds(data)
            if not value:raise ValueError('Expected VDS records')
            processed.append(dict(runId=run,exchange=exchange,bodySha256=digest,records=value))
            (output/'processed-records.json').write_text(json.dumps(processed,ensure_ascii=False,indent=2),encoding='utf8')
            event('application_processed',runId=run,exchange=exchange,bodySha256=digest,recordCount=len(value),stationIds=[r['stnId'] for r in value])
        event('finished',processedExchanges=len(processed));return 0
    except Exception as e:event('error',errorType=type(e).__name__);return 2

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--config',type=Path,required=True);p.add_argument('--output',required=True)
    p.add_argument('--fault',default='none',choices=['none','lowercase-auth','wrong-method','wrong-path','query','body','wrong-token','missing-auth','duplicate-auth','too-few','no-processing'])
    a=p.parse_args();raise SystemExit(execute(json.loads(a.config.read_text(encoding='utf-8-sig')),a.output,a.fault))
