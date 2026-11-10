"""Independent MQTT counterpart process; uses native UPER decoding for receipts."""
import argparse,json,sys,time
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from catalog import CASES,MESSAGES,parse_config
from codec import Codec
from container import Container,encode,validate
from transport import Transport
from credentials import connection

def damage_sample(payload, fault):
    """Only mutate our root MessageFrame fixtures; keep outer lengths consistent."""
    if fault == 'uper_outer_tail':return payload+b'\x00'
    if fault not in ('uper_inner_tail','uper_inner_cut','uper_padding'):return payload
    start=4 if payload[2]&0x80 else 3
    body=payload[start:]
    if fault=='uper_inner_tail':body+=b'\x00'
    elif fault=='uper_inner_cut':body=body[:-1]
    else:body=body[:-1]+bytes([body[-1]|1])
    length=len(body)
    determinant=bytes([length]) if length<128 else bytes([0x80|(length>>8),length&255])
    return payload[:2]+determinant+body

def main():
    p=argparse.ArgumentParser();p.add_argument('--case',required=True);p.add_argument('--config',required=True)
    p.add_argument('--codec',required=True);p.add_argument('--ready',required=True);p.add_argument('--go');p.add_argument('--stop',required=True)
    p.add_argument('--subscriptions');p.add_argument('--interval',type=float,default=1);p.add_argument('--fault',default='')
    a=p.parse_args();c=parse_config(a.case,json.loads(Path(a.config).read_text(encoding='utf-8-sig')))
    role=CASES[a.case];codec=Codec(a.codec);stopped=lambda:Path(a.stop).exists()
    selected=list(dict.fromkeys(x[1] for x in c['selected']));client=Transport(c['host'],c['port'],client_id=(c['client_id'].strip() or 'g4-mqtt-'+str(time.monotonic_ns()))+'-sut',stop=stopped,**connection(c))
    try:
        client.connect(10)
        if not role['receive']:
            dest=Path(c['observation_file']);dest.parent.mkdir(parents=True,exist_ok=True);dest.touch(exist_ok=True)
            client.subscribe({c['topic_'+k]:c['qos'] for k in selected},10)
        Path(a.ready).write_text('ready',encoding='ascii')
        if a.go:
            while not Path(a.go).exists():
                if stopped():return
                time.sleep(.02)
        if role['receive']:
            samples={k:codec.sample(MESSAGES[k]['frame']) for k in selected};n=0;event_generation=None;events_sent=0
            while not stopped():
                begin=time.monotonic()
                for key in selected:
                    if a.fault=='silence':continue
                    if key=='tim' and role.get('center_provider'):
                        # Generate a bounded series of events only after this subscription is ready.
                        paths=list(Path(a.subscriptions).glob('*/ready.json')) if a.subscriptions else [Path(a.go)] if a.go else []
                        state={}
                        if len(paths)==1:
                            try:state=json.loads(paths[0].read_text(encoding='utf-8'))
                            except (OSError,ValueError):pass
                        if state.get('message')!='tim' or not state.get('active'):continue
                        if state.get('generation')!=event_generation:event_generation=state['generation'];events_sent=0
                        fixtures=json.loads((Path(__file__).parent/'tim-five-fixtures.json').read_text(encoding='utf-8'))['samples']
                        from tim_five import TYPES
                        codes=[TYPES[item[2]][2] for item in c['selected'] if item[1]=='tim']
                        if a.fault=='tim_missing':codes=codes[:-1]
                        if a.fault=='tim_duplicate' and codes:codes=codes[:1]+codes
                        if not codes:continue
                        if events_sent>=len(codes)*c['tim_per_type']:continue
                        chosen=codes[events_sent%len(codes)]
                        original=bytes.fromhex(fixtures[str(chosen)]['hex'])
                        start=4 if original[2]&0x80 else 3
                        bits=list(''.join(f'{b:08b}' for b in original[start:]))
                        # Emulator fixture only: root ext + four optional bits, then msgCnt(7).
                        bits[5:12]=f'{events_sent//len(codes)%128:07b}'
                        samples[key]=original[:start]+int(''.join(bits),2).to_bytes(len(original)-start,'big')
                        events_sent+=1
                    m=MESSAGES[key];payload=damage_sample(samples[key],a.fault)
                    if a.fault=='spat_timestamp' and key=='spat':
                        # Root SPaT fixture: ext/presence(4), MinuteOfTheYear(20).
                        start=4 if payload[2]&0x80 else 3
                        bits=list(''.join(f'{b:08b}' for b in payload[start:]))
                        bits[4:24]='1'*20
                        payload=payload[:start]+int(''.join(bits),2).to_bytes(len(payload)-start,'big')
                    wire=encode(Container(c['container_version'],m['fid'],c['standard_type'],0,b'',n%256,m['psid'],payload),c['byte_order'])
                    if a.fault=='wrong_psid':wire=wire[:8]+b'\0\0\0\1'+wire[12:]
                    elif a.fault=='bad_length':wire=wire[:-1]
                    elif a.fault=='bad_uper':wire=wire[:16]+bytes(len(wire)-16)
                    client.publish(c['topic_'+key],wire,qos=c['qos'],retain=a.fault=='retained',timeout=10)
                n+=1
                while not stopped() and time.monotonic()-begin<a.interval:time.sleep(.01)
        else:
            with Path(c['observation_file']).open('a',encoding='utf-8',buffering=1) as out:
                while not stopped():
                    record=client.receive(.05)
                    if not record:continue
                    key=next((k for k in selected if c['topic_'+k]==record['topic'] and MESSAGES[k]['fid']==int.from_bytes(record['payload'][2:4],c['byte_order'])),None)
                    if not key:continue
                    body=validate(record['payload'],MESSAGES[key],c);v=codec.validate(MESSAGES[key]['frame'],body.payload)
                    if a.fault=='no_receipt':continue
                    result=dict(topic=record['topic'],payload_hex=record['payload'].hex(),frame_id=MESSAGES[key]['frame'],valid=v['valid'],received_unix=time.time())
                    if a.fault=='wrong_receipt':result['payload_hex']='00'
                    out.write(json.dumps(result,ensure_ascii=False)+'\n');out.flush()
    finally:client.close()
if __name__=='__main__':main()
