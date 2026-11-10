"""Independent Part 3 table 4-12 field checks and adopted NTIC envelope."""
import json
from decimal import Decimal
from standard_fields import text,number,timestamp,unique

def fixture(empty=False):
    rows=[] if empty else [dict(vdsId='VDS0000001',linkIds='1400006000',laneNo=1,colctedDate='20260807173900',speed=62.5,volume=9,occupancy=1.5)]
    return json.dumps(dict(resultCode='0',resultMsg='SUCCESS',totalCount=str(len(rows)),items=rows),ensure_ascii=False).encode()

def error_body(code=None):
    return json.dumps(dict(resultCode=code,resultMsg='Request could not be completed',totalCount='0',items=[]) if code else dict(resultMsg='Requested information is unavailable')).encode()

def decode(body):
    data=json.loads(body.decode('utf8'),parse_float=Decimal,parse_int=Decimal,object_pairs_hook=unique)
    if not isinstance(data,dict) or not isinstance(data.get('items'),list):raise ValueError('Expected root items array')
    if 'resultCode' in data and data['resultCode']!='0':raise ValueError('Unexpected NTIC resultCode')
    if 'resultMsg' in data and (not isinstance(data['resultMsg'],str) or not data['resultMsg']):raise ValueError('Invalid resultMsg')
    if 'totalCount' in data:
        value=data['totalCount']
        if not isinstance(value,str) or not value.isascii() or not value.isdigit() or int(value)!=len(data['items']):raise ValueError('Invalid totalCount')
    for row in data['items']:
        if not isinstance(row,dict) or any(k not in row for k in ['vdsId','linkIds','laneNo','colctedDate','speed','volume','occupancy']):raise ValueError('Missing NTIC field')
        text(row['vdsId'],10,'vdsId');text(row['linkIds'],20,'linkIds');timestamp(row['colctedDate'],'colctedDate')
        number(row['laneNo'],2,0,'laneNo')
        for key in ['speed','volume','occupancy']:number(row[key],5,2,key)
    return json.loads(body)['items']

def error(body,code):
    data=json.loads(body.decode('utf8'),object_pairs_hook=unique)
    if not isinstance(data,dict) or data.get('resultCode')!=code or not isinstance(data.get('resultMsg'),str) or not data['resultMsg']:raise ValueError('Invalid NTIC error result')
    if 'items' in data and data['items']!=[]:raise ValueError('Error contains normal data')
    return data
