"""기상정보 표 4-15의 독립 필드 검사와 채택한 API JSON 계층."""
import json,re
from decimal import Decimal
from standard_fields import unique,number,text,timestamp
PATH='/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst'
FORECAST='/1360000/VilageFcstInfoService_2.0/getUltraSrtFcst'
DEFAULT=dict(pageNo='1',numOfRows='10',base_date='20260924',base_time='0600',nx='55',ny='127',dataType='JSON')
def load(body):return json.loads(body.decode('utf8'),parse_float=Decimal,parse_int=Decimal,object_pairs_hook=unique,parse_constant=lambda s:(_ for _ in ()).throw(ValueError(s)))
def fixture(empty=False,params=None):
 p=DEFAULT|dict(params or {});page=int(p['pageNo']);size=int(p['numOfRows'])
 row=dict(baseDate=p['base_date'],updateDt=p['base_time']+'00',nx=int(p['nx']),ny=int(p['ny']),t1h=23.5,rn1='0',sky=1,uuu=-1.2,vvv=2.3,reh=65.0,pty=0,lgt='0',vec='180',wsd=2.5,adstrdCode=p['base_date'],fcstTime=p['base_time']+'00')
 return json.dumps(dict(response=dict(header=dict(resultCode='00',resultMsg='NORMAL_SERVICE'),body=dict(dataType='JSON',items=dict(item=[] if empty else [row]),pageNo=page,numOfRows=size,totalCount=0 if empty else (page-1)*size+1)))).encode()
def bounded(v,lo,hi,name):
 if not isinstance(v,Decimal) or not v.is_finite() or v!=v.to_integral_value() or not lo<=v<=hi:raise ValueError('Invalid integer: '+name)
 return int(v)
def header(value):
 if not isinstance(value,dict) or not isinstance(value.get('response'),dict) or not isinstance(value['response'].get('header'),dict):raise ValueError('Missing response/header')
 h=value['response']['header'];code=h.get('resultCode');msg=h.get('resultMsg')
 if not isinstance(code,str) or not re.fullmatch('[0-9]{2}',code):raise ValueError('Invalid resultCode')
 text(msg,100,'resultMsg');return code
def decode(body):
 root=load(body)
 if header(root)!='00':raise ValueError('Nonzero business result')
 b=root['response'].get('body')
 if not isinstance(b,dict) or b.get('dataType')!='JSON' or not isinstance(b.get('items'),dict) or not isinstance(b['items'].get('item'),list):raise ValueError('Missing normal body/items/item')
 page=bounded(b.get('pageNo'),1,9999,'pageNo');size=bounded(b.get('numOfRows'),1,9999,'numOfRows');total=bounded(b.get('totalCount'),0,9999999999,'totalCount');rows=b['items']['item']
 if len(rows)!=min(size,max(0,total-(page-1)*size)):raise ValueError('Inconsistent pagination')
 for row in rows:
  if not isinstance(row,dict) or any(k not in row for k in ['baseDate','updateDt','nx','ny','t1h','rn1','sky','uuu','vvv','reh','pty','lgt','vec','wsd','adstrdCode','fcstTime']):raise ValueError('Missing weather field')
  for k in ['baseDate','adstrdCode']:
   if not isinstance(row[k],str) or len(row[k])!=8:raise ValueError(k+' must be YYYYMMDD')
   timestamp(row[k]+'000000',k)
  for k in ['updateDt','fcstTime']:
   if not isinstance(row[k],str) or len(row[k])!=6:raise ValueError(k+' must be hhmmss')
   timestamp('20000101'+row[k],k)
  bounded(row['nx'],-199999999,1800000001,'nx');bounded(row['ny'],-900000000,900000001,'ny')
  for k in ['t1h','uuu','vvv','reh','wsd']:number(row[k],4,1,k)
  for k in ['rn1','lgt','vec']:text(row[k],10 if k=='rn1' else 3,k)
  if bounded(row['sky'],0,9,'sky') not in [1,3,4]:raise ValueError('Invalid sky')
  bounded(row['pty'],0,7,'pty')
 return json.loads(body)['response']['body']['items']['item']
def error_body(code):return json.dumps(dict(response=dict(header=dict(resultCode=code,resultMsg='NODATA_ERROR' if code=='03' else 'WEATHER_SERVICE_ERROR')))).encode()
def error(body,expected=None):
 root=load(body);code=header(root)
 if code=='00' or (expected is not None and code!=expected):raise ValueError('Business error mismatch')
 b=root['response'].get('body')
 if b is not None:
  if not isinstance(b,dict):raise ValueError('Invalid error body')
  if 'items' in b and (not isinstance(b['items'],dict) or b['items'].get('item')!=[]):raise ValueError('Error with normal data')
 return json.loads(body)
def query_values(q,key_name='serviceKey'):
 m={}
 for k,v in q:
  if k in m or k not in [*DEFAULT,key_name]:raise ValueError('Duplicate or unknown query')
  m[k]=v
 if any(k not in m for k in DEFAULT) or m['dataType']!='JSON':raise ValueError('Missing query or JSON dataType')
 for k in ['pageNo','numOfRows','nx','ny']:
  if not re.fullmatch('[+-]?[0-9]+',m[k]) or len(m[k])>11:raise ValueError('Invalid integer query')
  n=int(m[k]);lo,hi=(1,9999) if k in ['pageNo','numOfRows'] else (-2147483648,2147483647)
  if not lo<=n<=hi:raise ValueError('Query range')
  m[k]=str(n)
 if len(m['base_date'])!=8 or len(m['base_time'])!=4:raise ValueError('Query date/time width')
 timestamp(m['base_date']+m['base_time']+'00','query date/time');return m
