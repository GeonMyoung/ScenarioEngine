"""Atomic readiness updates tolerate short Windows reader sharing locks."""
import json,os,secrets,time

def write(path,value):
    temp=path.with_name(path.name+'.'+secrets.token_hex(4)+'.tmp')
    try:
        temp.write_text(json.dumps(value),encoding='utf-8')
        for attempt in range(20):
            try:os.replace(temp,path);return
            except PermissionError:
                if attempt==19:raise
                time.sleep(.01)
    finally:
        if temp.exists():temp.unlink()
