"""SETUP validation only; never contacts a Broker."""
import argparse,json,os,sys
from pathlib import Path
from catalog import parse_config
from credentials import protect


def main():
    p=argparse.ArgumentParser();p.add_argument('--case',required=True);p.add_argument('--config',required=True)
    p.add_argument('--receipt',required=True);p.add_argument('--owner',type=int);p.add_argument('--index',type=int)
    a=p.parse_args();result=dict(valid=False,case=a.case,processId=a.owner,testIdx=a.index)
    code=0
    try:
        c=parse_config(a.case,json.loads(Path(a.config).read_text(encoding='utf-8-sig')))
        result.update(valid=True,tests=[x[0] for x in c['selected']],effectiveConfiguration=protect(c))
    except Exception as e:result['error']=str(e);code=2
    dest=Path(a.receipt);temp=dest.with_suffix('.tmp');temp.write_text(json.dumps(result,ensure_ascii=False),encoding='utf-8');os.replace(temp,dest)
    return code
if __name__=='__main__':sys.exit(main())
