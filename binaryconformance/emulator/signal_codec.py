"""표준의 필드 폭과 명시된 개발 운용 기준을 독립 구현한다."""
import json,struct
import extended_codec

def fields(message):
 if message==70:return [('LC_NO',4,False),('START_HOUR',1,False),('START_MIN',1,False),('CYCLE',2,False),('OFFSET',2,False)]+[(f'{ring}_{n}PHASE',2,False) for ring in ['ARING','BRING'] for n in range(1,9)]
 if message not in [68,69]:raise ValueError('Unknown message')
 return [('LC_NO',1,False),('LC_NAME',100,True),('LC_TYPE',1,False),('LC_LAT',20,True),('LC_LNG',20,True),('LC_STATUS',1,False),('LC_COUNT',1,False)]+[f for ring in ['A','B'] for f in [(f'LC_{ring}_FLONUMBER',1,False)]+[(f'LC_{ring}_{point}_{axis}',20,True) for point in ['START','MIDDLE','END'] for axis in ['LAT','LNG']]]

def fixture(message,iteration=0,count=1):
 if message in [67,71,72]:return extended_codec.fixture(message,iteration,count)
 rows=[]
 for i in range(count):
  row={k:('시청앞교차로' if k=='LC_NAME' else '37.566535' if 'LAT' in k else '126.977969') if text else 0 for k,width,text in fields(message)};row['LC_NO']=(1001 if message==70 else 101)+i
  if message==70:
   row.update(START_HOUR=7,START_MIN=30,CYCLE=120,OFFSET=30)
   for ring in ['ARING','BRING']:
    for n in range(1,9):row[f'{ring}_{n}PHASE']=25 if n%2 else 5
  else:row.update(LC_TYPE=1,LC_STATUS=1,LC_COUNT=iteration%256,LC_A_FLONUMBER=1,LC_B_FLONUMBER=2)
  rows.append(row)
 return rows

def encode(message,rows,encoding='UTF-8'):
 if message in [67,71,72]:return extended_codec.encode(message,rows,encoding)
 out=bytearray()
 for row in rows:
  for key,width,text in fields(message):
   value=row[key]
   if text:
    if not isinstance(value,str) or not value or '\0' in value:raise ValueError('Invalid CHAR')
    b=value.encode(encoding)
    if len(b)>width:raise ValueError('CHAR overflow')
    out.extend(b.ljust(width,b'\0'))
   else:
    if type(value) is not int or not 0<=value<1<<(width*8):raise ValueError('Integer width')
    if key=='START_HOUR' and value>23 or key=='START_MIN' and value>59:raise ValueError('TOD time')
    out.extend(value.to_bytes(width,'big'))
 return bytes(out)

def decode(message,payload,encoding='UTF-8'):
 if message in [67,71,72]:return extended_codec.decode(message,payload,encoding)
 spec=fields(message);size=sum(f[1] for f in spec)
 if not payload or len(payload)%size:raise ValueError('Invalid record width')
 rows=[]
 for start in range(0,len(payload),size):
  row={};offset=start
  for key,width,text in spec:
   b=payload[offset:offset+width];offset+=width
   if text:
    head,separator,tail=b.partition(b'\0')
    if not head or any(tail):raise ValueError('Invalid padding')
    row[key]=head.decode(encoding)
   else:row[key]=int.from_bytes(b,'big')
  if message==70 and (row['START_HOUR']>23 or row['START_MIN']>59):raise ValueError('Invalid TOD time')
  rows.append(row)
 return rows

def checksum(b,mode='xor8'):
 if mode=='sum8':return (-sum(b))&255
 if mode!='xor8':raise ValueError('Invalid LRC mode')
 n=0
 for v in b:n^=v
 return n

def packet(message,flag,seq,payload=b'',mode='xor8'):
 if len(payload)>65529:raise ValueError('Packet size')
 b=struct.pack('!BHBB',message,len(payload)+6,flag,seq)+payload;return b+bytes([checksum(b,mode)])

def frame(b,mode='xor8'):
 if len(b)<6:raise ValueError('Header length')
 message,size,flag,seq=struct.unpack('!BHBB',b[:5])
 if size!=len(b) or message not in [67,68,69,70,71,72] or flag not in [0,1,2] or checksum(b[:-1],mode)!=b[-1]:raise ValueError('Invalid frame')
 return message,flag,seq,b[5:-1]

def ack(message,seq,accepted=True,mode='echo'):return struct.pack('!BHBB',message,5,1 if mode=='fixed1' else seq,int(accepted))
def check_ack(b,message,seq,accepted=True,mode='echo'):
 if b!=ack(message,seq,accepted,mode):raise ValueError('ACK mismatch')

class Assembler:
 def __init__(self,seq=0):self.seq=seq;self.partial=None;self.message=None
 def accept(self,b,cfg):
  message,flag,seq,payload=frame(b,cfg['lrc_mode'])
  if seq!=self.seq:raise ValueError('Sequence mismatch')
  self.seq=(seq+1)%256
  if flag==0:
   if self.partial is not None or not payload:raise ValueError('Unexpected start')
   self.partial=payload;self.message=message;return None
  if flag==1:
   if self.partial is None or message!=self.message:raise ValueError('Unexpected end')
   payload=self.partial+payload;self.partial=None
  elif self.partial is not None:raise ValueError('Single during fragment')
  if not payload:
   if message in [70,71,72] and flag==2:return []
   raise ValueError('Empty data')
  return decode(message,payload,cfg['char_encoding'])

def catalog(provider):
 prefix='test_provide_' if provider else 'test_receive_'
 values=[(prefix+'all_status','normal',68),(prefix+'alter_status','change',69),(prefix+'tod','normal',70),(prefix+'split_status','split',68),(prefix+'multiple_status','multiple',68),(prefix+'tod_heartbeat','heartbeat',70)]
 if not provider:values += [('test_reject_bad_lrc','bad_lrc',68),('test_reject_bad_payload','bad_payload',68),('test_reject_bad_sequence','bad_sequence',68)]
 return values
