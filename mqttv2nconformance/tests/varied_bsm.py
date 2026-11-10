"""Offline encode/decode boundary checks for the adopted schema."""
import argparse,json,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from codec import Codec
from bsm_stimulus import expected_fields,verify_fields

def main():
    p=argparse.ArgumentParser();p.add_argument('--codec',required=True);p.add_argument('--output',type=Path,required=True)
    a=p.parse_args();codec=Codec(a.codec);rows=[]
    for seq in [1,2,10,60,61,128,129,256,257,1000]:
        sec_mark=(59999+(seq-1)*1000)%60000
        payload=codec.bsm_sample(seq,sec_mark,'41424344')
        view=codec.validate(20,payload);expected=expected_fields(seq,sec_mark,'41424344')
        verify_fields(view['decoded'],expected)
        # Required vert uses 293 core-message bits while preserving intended sample values.
        core=view['decoded']['coreData']
        assert core['accelSet']==dict(lon=0,lat=0,vert=0,yaw=0)
        assert core['size']==dict(width=400,length=300)
        assert view['validation']['messageBits']==293
        rows.append(dict(sequence=seq,expected=expected,payload_hex=payload.hex(),decoded=view['decoded']))
    assert len(set(r['payload_hex'] for r in rows))==len(rows)
    for vehicle_id in ['00000000','0001020f','63930400','ffffffff']:
        view=codec.validate(20,codec.bsm_sample(1,0,vehicle_id))
        verify_fields(view['decoded'],expected_fields(1,0,vehicle_id))
    # Old sample consumers (SPaT/TLSM/TIM and legacy BSM) retain their command contract.
    for frame in [20,19,50,31]:assert codec.validate(frame,codec.sample(frame))['valid']
    for seq,sec in [(0,0),(1001,0),(1,60000)]:
        try:codec.bsm_sample(seq,sec,'41424344')
        except ValueError:pass
        else:raise AssertionError('Invalid sample parameters accepted')
    a.output.write_text(json.dumps(dict(passed=True,rows=rows,legacyFrames=[20,19,50,31]),ensure_ascii=False,indent=2),encoding='utf-8')
    print('PASS varied BSM: bounds, counter wrap, simulated minute wrap, adopted schema, legacy samples')

if __name__=='__main__':main()
