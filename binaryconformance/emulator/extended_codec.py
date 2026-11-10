"""표준 4-27/28/29의 독립 Binary 인코더·디코더."""
import math,struct

def fixed(s,width,encoding,terminated=False):
 if not isinstance(s,str) or not s or '\0' in s:raise ValueError('Invalid CHAR')
 b=s.encode(encoding)
 if len(b)>width or terminated and len(b)==width:raise ValueError('CHAR width/terminator')
 return b.ljust(width,b'\0')
def text(b,encoding,terminated=False):
 head,sep,tail=b.partition(b'\0')
 if not head or any(tail) or terminated and not sep:raise ValueError('CHAR padding/terminator')
 return head.decode(encoding)
def date_parts(j,upper=False):
 k=lambda s:s.upper() if upper else s
 y,m,d,h,n,s=[j[k(key)] for key in ['Year','Month','Day','Hour','Minute','Second']]
 if any(type(v) is not int for v in [y,m,d,h,n,s]) or not 1<=y<=65535 or not 1<=m<=12:raise ValueError('Date fields')
 days=[31,28+int(y%400==0 or y%4==0 and y%100!=0),31,30,31,30,31,31,30,31,30,31]
 if not 1<=d<=days[m-1] or not 0<=h<=23 or not 0<=n<=59 or not 0<=s<=59:raise ValueError('Date/time bounds')
def date_string(s,day_only=False,unknown=False):
 if unknown and s=='00000000000000':return
 if not isinstance(s,str) or len(s)!=(8 if day_only else 14) or not s.isascii() or not s.isdigit():raise ValueError('Date string')
 if day_only:s+='000000'
 date_parts(dict(zip(['Year','Month','Day','Hour','Minute','Second'],[int(s[:4]),int(s[4:6]),int(s[6:8]),int(s[8:10]),int(s[10:12]),int(s[12:14])])))
def uint(n,width):
 if type(n) is not int or not 0<=n<1<<(width*8):raise ValueError('Unsigned width')
 return n.to_bytes(width,'big')
def wide(n):
 if type(n) not in [int,str] or not str(n).isascii() or not str(n).isdigit() or len(str(n))>49:raise ValueError('Wide integer')
 return uint(int(n),20)
def fp(v,width):
 if type(v) not in [int,float] or not math.isfinite(v):raise ValueError('Finite float required')
 b=struct.pack('!f' if width==4 else '!d',v)
 if v!=0 and struct.unpack('!f' if width==4 else '!d',b)[0]==0:raise ValueError('Float underflow')
 return b
INC=[('EVENT_ID',18),('EVENT_NM',500),('INC_TY',2),('INC_DTL_TY',4),('OCRN_DT',14),('END_DT',14),('OCRN_LOT',20),('OCRN_LAT',20),('OCRN_LINK_ID',10),('CNTRL_TY',1),('PRGRS_STTS',2)]
DATE=[('Year',2),('Month',1),('Day',1),('Hour',1),('Minute',1),('Second',1)]
def encode(message,rows,encoding='UTF-8'):
 if not isinstance(rows,list) or not rows or message==71 and len(rows)!=1:raise ValueError('Record shape')
 out=bytearray()
 for j in rows:
  if message==67:
   date_string(j['CREDATE'],True)
   for k,w in [('CREDATE',8),('VEH_ID',16),('VEH_NO',8)]:out.extend(fixed(j[k],w,encoding))
   for k,w in [('LONGITUDE',8),('LATITUDE',8),('ALTITUDE',4),('ANGLE',4)]:out.extend(fp(j[k],w))
   out.extend(fixed(j['GEAR'],4,encoding));out.extend(fp(j['SPEED'],4))
  elif message==71:
   date_parts(j)
   for k,w in DATE:out.extend(uint(j[k],w))
   out.extend(fp(j['lot'],8));out.extend(fp(j['lat'],8));vs=j['pol6IndivAdInfoDtoList']
   if j['indivAdIdNo']!=len(vs):raise ValueError('Vehicle count')
   out.extend(uint(j['indivAdIdNo'],1))
   for v in vs:
    out.extend(fixed(v['indivAdId'],10,encoding));out.extend(fixed(v['linkId'],10,encoding));out.extend(uint(v['linkPos'],3));out.extend(uint(v['linkInfoType'],1));links=v['pol6RouteIntoDtoList']
    if v['viaLinkNo']!=len(links):raise ValueError('Route count')
    out.extend(uint(v['viaLinkNo'],1))
    for link in links:out.extend(wide(link['viaLinkSeq']));out.extend(fixed(link['viaLinkId'],3,encoding));out.extend(uint(link['viaLinkTurn'],1))
  elif message==72:
   date_parts(j,True);date_string(j['OCRN_DT']);date_string(j['END_DT'],unknown=True)
   for k,w in DATE:out.extend(uint(j[k.upper()],w))
   for k,w in INC:out.extend(fixed(j[k],w,encoding,k=='EVENT_NM'))
   if j['LINK_COUNT']!=len(j['EVENT_CTRL']):raise ValueError('Controlled link count')
   out.extend(uint(j['LINK_COUNT'],1))
   for link in j['EVENT_CTRL']:out.extend(fixed(link['LINK_ID'],10,encoding))
  else:raise ValueError('Message')
 if len(out)>1024*1024:raise ValueError('Assembly limit')
 return bytes(out)
class Reader:
 def __init__(self,b,encoding):self.b=b;self.p=0;self.encoding=encoding
 def take(self,n):
  if n>len(self.b)-self.p:raise ValueError('Count/length mismatch')
  b=self.b[self.p:self.p+n];self.p+=n;return b
 def u(self,n):return int.from_bytes(self.take(n),'big')
 def s(self,n,terminated=False):return text(self.take(n),self.encoding,terminated)
 def f(self,n):
  v=struct.unpack('!f' if n==4 else '!d',self.take(n))[0]
  if not math.isfinite(v):raise ValueError('Nonfinite float')
  return v
def decode(message,payload,encoding='UTF-8'):
 if not payload:raise ValueError('Empty business data')
 r=Reader(payload,encoding);out=[]
 while r.p<len(payload):
  j={}
  if message==67:
   for k,w in [('CREDATE',8),('VEH_ID',16),('VEH_NO',8)]:j[k]=r.s(w)
   for k,w in [('LONGITUDE',8),('LATITUDE',8),('ALTITUDE',4),('ANGLE',4)]:j[k]=r.f(w)
   j['GEAR']=r.s(4);j['SPEED']=r.f(4);date_string(j['CREDATE'],True)
  elif message==71:
   for k,w in DATE:j[k]=r.u(w)
   date_parts(j);j['lot']=r.f(8);j['lat']=r.f(8);j['indivAdIdNo']=r.u(1);vs=[]
   for _ in range(j['indivAdIdNo']):
    v=dict(indivAdId=r.s(10),linkId=r.s(10),linkPos=r.u(3),linkInfoType=r.u(1),viaLinkNo=r.u(1));links=[]
    for _ in range(v['viaLinkNo']):links.append(dict(viaLinkSeq=str(r.u(20)),viaLinkId=r.s(3),viaLinkTurn=r.u(1)))
    v['pol6RouteIntoDtoList']=links;vs.append(v)
   j['pol6IndivAdInfoDtoList']=vs
   if r.p!=len(payload):raise ValueError('Trailing route data')
  elif message==72:
   for k,w in DATE:j[k.upper()]=r.u(w)
   date_parts(j,True)
   for k,w in INC:j[k]=r.s(w,k=='EVENT_NM')
   date_string(j['OCRN_DT']);date_string(j['END_DT'],unknown=True);j['LINK_COUNT']=r.u(1);j['EVENT_CTRL']=[dict(LINK_ID=r.s(10)) for _ in range(j['LINK_COUNT'])]
  else:raise ValueError('Message')
  out.append(j)
 return out
def fixture(message,iteration=0,count=1):
 out=[]
 for i in range(1 if message==71 else count):
  if message==67:j=dict(CREDATE='20260925',VEH_ID='AV000000000000'+str(10+i),VEH_NO='12A3456',LONGITUDE=126.9784,LATITUDE=37.5665,ALTITUDE=35.5,ANGLE=90.0,GEAR='D',SPEED=45.5+iteration*.5)
  else:
   j=dict(zip([k.upper() if message==72 else k for k,w in DATE],[2026,9,25,10,30,iteration%60]))
   if message==71:j.update(lot=126.9784,lat=37.5665,indivAdIdNo=count,pol6IndivAdInfoDtoList=[dict(indivAdId='CAR00000'+str(10+n),linkId='LINK0000'+str(10+n),linkPos=150+iteration,linkInfoType=1,viaLinkNo=2,pol6RouteIntoDtoList=[dict(viaLinkSeq=str(k+1),viaLinkId=str(101+k),viaLinkTurn=k) for k in range(2)]) for n in range(count)])
   else:j.update(EVENT_ID='INC2026092500000'+str(10+i),EVENT_NM='교통사고 상태 변경' if iteration else '교통사고 발생',INC_TY='01',INC_DTL_TY='0101',OCRN_DT='20260925103000',END_DT='00000000000000',OCRN_LOT='126.978400',OCRN_LAT='37.566500',OCRN_LINK_ID='1234567890',CNTRL_TY='1',PRGRS_STTS='01',LINK_COUNT=2,EVENT_CTRL=[dict(LINK_ID=str(1234567890+n)) for n in range(2)])
  out.append(j)
 return out
CASES={
 'signalClient2center_bsm_binary_v1':(True,67,'SC16'),'centerServer2signal_bsm_binary_v1':(False,67,'SC37'),
 'routeServer2center_binary_v1':(False,71,'SC15'),'centerClient2route_binary_v1':(True,71,'SC36'),
 'signalClient2center_incident_binary_v1':(True,72,'SC17'),'centerServer2signal_incident_binary_v1':(False,72,'SC38')}
def catalog(case):
 provider,msg,_=CASES[case];base=('test_provide_' if provider else 'test_receive_')+{67:'bsm',71:'route',72:'incident'}[msg]
 out=[(base,'normal',msg),(base+('_periodic' if msg==67 else '_change'),'periodic' if msg==67 else 'change',msg),(base+'_split','split',msg),(base+'_multiple','multiple',msg)]
 if msg!=67:out.append((base+'_empty','empty',msg))
 if not provider:out += [(base+'_reject_'+m,m,msg) for m in ['bad_lrc','bad_payload','bad_sequence']]
 return out
