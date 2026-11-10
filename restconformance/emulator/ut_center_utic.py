"""UT center HTTP client SUT for the UTIC information-request test."""
import argparse
import hashlib
import json
from pathlib import Path
import time
import urllib.parse
import urllib.request
from standard_fields import utic as validate_utic


def execute(config, output, fault='none'):
    output = Path(output)
    output.mkdir(parents=True, exist_ok=False)
    records = []
    def event(name, **data):
        row = dict(event=name, utcUnixMs=time.time_ns()//1_000_000,
                   monotonicUs=time.monotonic_ns()//1000, **data)
        with (output/'events.jsonl').open('a', encoding='utf-8') as stream:
            stream.write(json.dumps(row, ensure_ascii=False)+'\n')
    count = config.get('repetitions', 10)
    if fault == 'too-few': count -= 1
    try:
        for number in range(1, count+1):
            path = '/wrong' if fault == 'wrong-path' else '/guide/imsOpenData.do'
            key = 'wrong-test-key' if fault == 'wrong-key' else config['api_key']
            query = [] if fault == 'missing-key' else [('key',key)]
            if fault == 'duplicate-key': query.append(('key',key))
            url = config['base_url'].rstrip('/')+path+'?'+urllib.parse.urlencode(query)
            request = urllib.request.Request(url, method='POST' if fault == 'wrong-method' else 'GET')
            event('request_sent', exchange=number, method=request.method, path=path, keyRedacted=True)
            with urllib.request.urlopen(request, timeout=config.get('request_timeout_s',30)) as response:
                body = response.read(1024*1024+1)
                run_id = response.headers.get('X-Scenario-Run')
                exchange = int(response.headers.get('X-Scenario-Exchange','0'))
                if response.status != 200 or len(body)>1024*1024:
                    raise ValueError('Invalid normal response')
            digest = hashlib.sha256(body).hexdigest()
            (output/f'response-{number:04d}.xml').write_bytes(body)
            event('response_received', exchange=exchange, runId=run_id, bodySha256=digest, bodyBytes=len(body))
            if fault == 'no-processing': continue
            decoded = validate_utic(body)
            if not decoded: raise ValueError('No incident records')
            records.append(dict(runId=run_id,exchange=exchange,bodySha256=digest,records=decoded))
            (output/'processed-records.json').write_text(json.dumps(records,ensure_ascii=False,indent=2),encoding='utf-8')
            event('application_processed', runId=run_id,exchange=exchange,bodySha256=digest,
                  incidentIds=[row['incidentId'] for row in decoded],recordCount=len(decoded))
        event('finished', processedExchanges=len(records))
        return 0
    except Exception as error:
        # Never include the full URL or authentication key in error evidence.
        event('error', errorType=type(error).__name__, httpStatus=getattr(error,'code',None))
        return 2


if __name__ == '__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--config',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--fault',choices=['none','wrong-method','wrong-path','wrong-key','missing-key','duplicate-key','too-few','no-processing'],default='none')
    args=parser.parse_args()
    raise SystemExit(execute(json.loads(args.config.read_text(encoding='utf-8-sig')),args.output,args.fault))
