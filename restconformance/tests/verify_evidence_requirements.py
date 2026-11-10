"""Reject observations that do not satisfy the Open API evidence requirements."""
import argparse,json
from pathlib import Path
from verify_method import run


def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    checks=[
        ('microClient2center_smart_v1','absent','fake-absence',404),
        ('microClient2center_smart_v1','absent','path-not-found',404),
        ('microClient2center_smart_v1','absent','unprepared',404),
        ('microClient2center_smart_v1','normal','wrong-valid-data',200),
        ('centerServer2micro_smart_v1','all','no-error-log',200),
        ('centerServer2micro_smart_v1','all','no-processing',200),
        ('centerServer2micro_smart_v1','malformed','accept-malformed',200),
        ('centerServer2micro_smart_v1','normal','stop',200),
        ('microClient2center_v1','absent','none',400),
        ('centerServer2micro_v1','absent','none',400),
    ]
    results=[]
    for index,(case,kind,fault,status) in enumerate(checks):
        result=run(args.exe.resolve(),out/str(index),case,kind,fault,status)
        results.append(result)
        print(index,fault,'PASS' if result['passed'] else result.get('error'),flush=True)
        (out/'summary.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf8')
    return 0 if all(x['passed'] for x in results) else 1


if __name__=='__main__':raise SystemExit(main())
