"""Offline validation and atomic engine SETUP receipt; no network operations."""
import argparse,json,os,sys,time
from pathlib import Path
from catalog import parse_config

def atomic(path,value):
    p=Path(path);tmp=p.with_suffix(p.suffix+'.tmp');tmp.write_text(json.dumps(value,ensure_ascii=False),encoding='utf8')
    for n in range(100):
        try:os.replace(tmp,p);return
        except PermissionError:
            if n==99:raise
            time.sleep(.02)

def main():
    p=argparse.ArgumentParser();p.add_argument('--case',required=True);p.add_argument('--config',required=True);p.add_argument('--receipt');p.add_argument('--owner',type=int);p.add_argument('--index',type=int);a=p.parse_args()
    record=dict(valid=False,case=a.case,processId=a.owner,testIdx=a.index)
    try:
        raw=json.loads(Path(a.config).read_text(encoding='utf-8-sig'));effective=parse_config(a.case,raw)
        if effective.get('security_file') and not Path(effective['security_file']).is_file():raise ValueError('인증 설정 파일을 찾을 수 없습니다.')
        record.update(valid=True,configuration=raw,effectiveConfiguration=effective,tests=[i[0] for i in effective['selected']])
        if a.receipt:atomic(a.receipt,record)
        print(json.dumps(effective,ensure_ascii=False));return 0
    except Exception as e:
        record['error']=str(e)
        if a.receipt:atomic(a.receipt,record)
        print(str(e),file=sys.stderr);return 2
if __name__=='__main__':sys.exit(main())
