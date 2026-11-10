"""실장비를 대신하는 경6 제공 서버 / 경4 수신 클라이언트."""
import argparse,hashlib,json,socket,struct,time
import extended_codec
from pathlib import Path
from signal_codec import fixture,encode,decode,packet,frame,ack,check_ack,Assembler,catalog

def main():
 p=argparse.ArgumentParser();p.add_argument('--config',type=Path,required=True);p.add_argument('--run-manifest',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--role',choices=['provider','receiver'],required=True);p.add_argument('--fault',default='none');a=p.parse_args();cfg=json.loads(a.config.read_text(encoding='utf8'));provider=a.role=='provider';a.output.mkdir(parents=True,exist_ok=False)
 cfg.setdefault('period_ms',1000);cfg.setdefault('period_tolerance_ms',200)
 for k in ['period_ms','period_tolerance_ms','tcp_port','repetitions','socket_timeout_ms','initial_limit_ms','first_sequence','heartbeat_period_ms','heartbeat_tolerance_ms','heartbeat_samples','change_delay_ms']:cfg[k]=int(cfg[k])
 run=None;test='';iteration=0;ordinal=0;current_socket=None;processed=[]
 def log(event,**v):
  with (a.output/'events.jsonl').open('a',encoding='utf8') as f:f.write(json.dumps(dict(event=event,monotonicUs=time.monotonic_ns()//1000,runId=run['runId'] if run else None,test=test,iteration=iteration,**v),ensure_ascii=False)+'\n')
 def message(b,sending):
  nonlocal ordinal;ordinal+=1;log('message',direction='send' if sending else 'receive',ordinal=ordinal,hex=b.hex().upper(),sha256=hashlib.sha256(b).hexdigest())
 def send(b):
  if a.fault=='tcp-fragment':
   for offset in range(0,len(b),7):current_socket.sendall(b[offset:offset+7])
  else:current_socket.sendall(b)
  message(b,True)
 def receive():
  b=b'';needed=3
  try:
   while len(b)<needed:
    part=current_socket.recv(needed-len(b))
    if not part:raise EOFError('Peer closed mid-frame')
    b+=part
    if len(b)==3:
     needed=int.from_bytes(b[1:3],'big')
     if needed<5:raise ValueError('Invalid size')
  except Exception:
   if b:message(b,False)
   raise
  message(b,False);return b
 def data_send(msg,seq,rows,mode):
  if mode=='empty' and a.fault!='nonempty-heartbeat':
   send(packet(msg,2,seq,b'',cfg['lrc_mode']))
   if cfg['heartbeat_ack']:check_ack(receive(),msg,seq,True,cfg['ack_seq_mode'])
   log('provided',message=msg,records=[]);return (seq+1)%256
  if a.fault=='duplicate-id':
   if msg==71:rows[0]['pol6IndivAdInfoDtoList'][1]['indivAdId']=rows[0]['pol6IndivAdInfoDtoList'][0]['indivAdId']
   elif len(rows)>1:rows[1]=dict(rows[0])
  if a.fault=='large-data':
   if msg==67:
    row=rows[0];rows=[dict(row,VEH_ID=f'AV{k:014d}') for k in range(128)]
   elif msg==71:
    for v in rows[0]['pol6IndivAdInfoDtoList']:
     v['viaLinkNo']=255;v['pol6RouteIntoDtoList']=[dict(viaLinkSeq=str((1<<160)-1 if k==0 else k+1),viaLinkId=str(100+k),viaLinkTurn=0) for k in range(255)]
   elif msg==72:
    for row in rows:row['LINK_COUNT']=255;row['EVENT_CTRL']=[dict(LINK_ID=str(1234567890+k)) for k in range(255)];row['EVENT_NM']='가'*166
  if a.fault=='same-event':rows=fixture(msg,0,len(rows[0]['pol6IndivAdInfoDtoList']) if msg==71 else len(rows))
  payload=encode(msg,rows,cfg['char_encoding']);frames=[]
  if mode=='split':
   cut=len(payload)//2;frames=[packet(msg,0,seq,payload[:cut],cfg['lrc_mode']),packet(msg,1,(seq+1)%256,payload[cut:],cfg['lrc_mode'])];seq=(seq+2)%256
  else:frames=[packet(msg,2,seq,payload,cfg['lrc_mode'])];seq=(seq+1)%256
  if a.fault in ['bad-date','nonfinite','count-mismatch','legacy-layout']:
   b=bytearray(payload)
   if a.fault=='bad-date':
    if msg==67:b[:8]=b'20260230'
    else:b[2]=13
   elif a.fault=='nonfinite':
    if msg==67:b[60:64]=bytes.fromhex('7fc00000')
    elif msg==71:b[7:15]=bytes.fromhex('7ff0000000000000')
   elif a.fault=='count-mismatch':b[23 if msg==71 else 612]+=1
   elif a.fault=='legacy-layout':
    if msg==67:b[56:60]=b'\x00\x00\x00\x01'
    elif msg==71:b=b[:49]+b'B'*20+b'0'+b'C'*20+b'1'
    else:b[25:525]=b'A'*500
   frames=[packet(msg,2,frames[0][4],bytes(b),cfg['lrc_mode'])]
  if a.fault=='bad-lrc':frames=[b[:-1]+bytes([b[-1]^1]) for b in frames]
  if a.fault=='bad-sequence':frames=[packet(msg,2,(b[4]+1)%256,b[5:-1],cfg['lrc_mode']) for b in frames]
  if a.fault=='wide-id':frames=[packet(msg,2,b[4],int(payload[0]).to_bytes(4,'big')+payload[1:],cfg['lrc_mode']) for b in frames]
  if a.fault=='invalid-tod':
   payload=payload[:4]+b'\x18'+payload[5:];frames=[packet(msg,2,frames[0][4],payload,cfg['lrc_mode'])]
  if a.fault=='little-size':frames=[b[:1]+b[1:3][::-1]+b[3:] for b in frames]
  if a.fault=='delay':time.sleep(cfg['socket_timeout_ms']/1000+1)
  if a.fault=='partial':
   send(frames[0][:10]);time.sleep(cfg['socket_timeout_ms']/1000+1);return seq
  if a.fault=='coalesced' and len(frames)==2:
   current_socket.sendall(b''.join(frames))
   for b in frames:message(b,True)
   for b in frames:check_ack(receive(),msg,b[4],True,cfg['ack_seq_mode'])
  else:
   for b in frames:
    send(b)
    if a.fault=='truncated':current_socket.shutdown(socket.SHUT_RDWR);return seq
    check_ack(receive(),msg,b[4],True,cfg['ack_seq_mode'])
  log('provided',message=msg,records=decode(msg,payload,cfg['char_encoding']));return seq
 def data_receive(assembler,msg,mode='normal'):
  for part in range(2):
   raw=receive();seq=raw[4] if len(raw)>4 else 0;accepted=True;rows=None
   try:
    if raw[0]!=msg:raise ValueError('Unexpected message')
    rows=assembler.accept(raw,cfg)
    if mode=='empty' and rows!=[]:raise ValueError('Expected empty heartbeat')
   except ValueError:accepted=False
   if a.fault=='accept-errors':accepted=True
   reply=ack(raw[0],seq,accepted,cfg['ack_seq_mode'])
   if a.fault=='wrong-ack':reply=reply[:-1]+bytes([1-reply[-1]])
   if a.fault=='wrong-ack-seq':reply=reply[:3]+bytes([(reply[3]+1)%256])+reply[4:]
   if a.fault=='wrong-ack-message':reply=bytes([70 if reply[0]==68 else 68])+reply[1:]
   if mode!='empty' or cfg['heartbeat_ack']:
    if a.fault=='no-ack':time.sleep(cfg['socket_timeout_ms']/1000+1)
    else:send(reply)
   if not accepted or rows is not None:
    record=dict(runId=run['runId'],test=test,iteration=iteration,message=msg,accepted=accepted,records=rows if accepted and rows is not None else [])
    if a.fault!='no-processing':processed.append(record);log('processed',message=msg,accepted=accepted,records=record['records']);(a.output/'processed.json').write_text(json.dumps(processed,ensure_ascii=False,indent=2),encoding='utf8')
    return record
  raise ValueError('Missing end')
 listener=None
 if provider:
  listener=socket.socket();listener.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1);listener.bind(('127.0.0.1',cfg['tcp_port']));listener.listen();listener.settimeout(15);print('LISTENING',flush=True)
 until=time.monotonic()+15
 while not a.run_manifest.exists():
  if time.monotonic()>until:raise TimeoutError('Run manifest timeout')
  time.sleep(.02)
 run=json.loads(a.run_manifest.read_text(encoding='utf8'));(a.output/'run-binding.json').write_text(json.dumps(run),encoding='utf8');(a.output/'config.json').write_text(json.dumps(cfg,ensure_ascii=False,indent=2),encoding='utf8')
 try:
  plan=extended_codec.catalog(run['case']) if run['case'] in extended_codec.CASES else catalog(provider)
  for test,mode,msg in plan:
   if not cfg.get(test):continue
   ordinal=0;iteration=0
   if provider:current_socket,_=listener.accept()
   else:
    until=time.monotonic()+cfg['socket_timeout_ms']/1000
    while True:
     try:current_socket=socket.create_connection(('127.0.0.1',cfg['tcp_port']),timeout=1);break
     except OSError:
      if time.monotonic()>until:raise
      time.sleep(.01)
   current_socket.setsockopt(socket.IPPROTO_TCP,socket.TCP_NODELAY,1)
   current_socket.settimeout((cfg['heartbeat_period_ms']+cfg['socket_timeout_ms']+cfg['heartbeat_tolerance_ms'])/1000 if mode=='heartbeat' else cfg['socket_timeout_ms']/1000+1)
   try:
    log('connected',localPort=current_socket.getsockname()[1],peerPort=current_socket.getpeername()[1]);seq=cfg['first_sequence'];assembler=Assembler(seq)
    if mode=='change':
     baseline=68 if msg==69 else msg
     if provider:seq=data_send(baseline,seq,fixture(baseline),'normal')
     else:data_receive(assembler,baseline)
    if mode=='heartbeat':
     if provider:seq=data_send(70,seq,fixture(70),'normal')
     else:data_receive(assembler,70)
     due=time.monotonic()
     for iteration in range(1,cfg['heartbeat_samples']+1):
      if provider:
       due+=cfg['heartbeat_period_ms']/1000;time.sleep(max(0,due-time.monotonic()));send(packet(70,2,seq,b'',cfg['lrc_mode']))
       if cfg['heartbeat_ack']:check_ack(receive(),70,seq,True,cfg['ack_seq_mode'])
       seq=(seq+1)%256
      else:
       raw=receive();rows=assembler.accept(raw,cfg)
       if rows!=[]:raise ValueError('Expected heartbeat')
       if cfg['heartbeat_ack']:send(ack(70,raw[4],True,cfg['ack_seq_mode']))
      log('heartbeat');log('exchange_complete')
    else:
     if mode=='periodic':current_socket.settimeout((cfg['period_ms']+cfg['socket_timeout_ms']+cfg['period_tolerance_ms'])/1000)
     due=time.monotonic()
     for iteration in range(1,cfg['repetitions']+1):
      if provider:
       if mode=='periodic' and iteration>1:due+=cfg['period_ms']/1000;time.sleep(max(0,due-time.monotonic()))
       if mode=='change':time.sleep(cfg['change_delay_ms']/1000)
       seq=data_send(msg,seq,fixture(msg,iteration if mode in ['change','periodic'] else 0,2 if mode=='multiple' else 1),'normal' if mode=='periodic' else mode)
      else:
       data_receive(assembler,msg,mode)
       if mode=='bad_sequence':data_receive(assembler,msg);log('fragment_recovered')
      log('exchange_complete')
      if a.fault=='close-after-three' and iteration==3:
       current_socket.shutdown(socket.SHUT_RDWR);break
    # EOF must be caused by the test controller after the configured exchanges.
    trailing=current_socket.recv(1)
    if trailing:message(trailing,False);raise ValueError('Unexpected trailing message')
    log('session_closed')
   finally:current_socket.close();current_socket=None
 except Exception as e:log('error',reason=str(e));raise
 finally:
  if current_socket:current_socket.close()
  if listener:listener.close()
 log('finished')
if __name__=='__main__':main()
