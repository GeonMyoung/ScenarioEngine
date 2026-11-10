"""제3부 음영구간 정보 정의표 및 OpenAPI 1.3의 독립 검사."""
import json,re
from decimal import Decimal
from standard_fields import timestamp,unique

def load(body):
    return json.loads(body.decode('utf8'),parse_float=Decimal,parse_int=Decimal,object_pairs_hook=unique,parse_constant=lambda s:(_ for _ in ()).throw(ValueError(s)))

def fixture(empty=False):
    return json.dumps([] if empty else [dict(time='20260724132000',node_link=12345,lane_no=1,lane_speed=42,lane_volume=18,lane_density=9)]).encode()

def decode(body):
    data=load(body)
    if not isinstance(data,list):raise ValueError('Expected root array')
    for row in data:
        if not isinstance(row,dict) or any(k not in row for k in ['time','node_link','lane_no','lane_speed','lane_volume','lane_density']):raise ValueError('Missing shadow field')
        timestamp(row['time'],'time')
        for key in ['node_link','lane_no','lane_speed','lane_volume','lane_density']:
            value=row[key];maximum=99999 if key in ['node_link','lane_volume'] else 350
            if not isinstance(value,Decimal) or not value.is_finite() or value!=value.to_integral_value() or not 0<=value<=maximum:raise ValueError('Invalid INTEGER: '+key)
    return json.loads(body)

def error_body():
    return b'{"detail":[{"loc":["query","latest"],"msg":"Input should be less than or equal to 500","type":"less_than_equal"}]}'

def error(body):
    value=load(body)
    if not isinstance(value,dict):raise ValueError('Expected error object')
    if 'detail' in value:
        if not isinstance(value['detail'],list):raise ValueError('detail must be array')
        for item in value['detail']:
            if not isinstance(item,dict) or not isinstance(item.get('loc'),list) or not isinstance(item.get('msg'),str) or not isinstance(item.get('type'),str):raise ValueError('Invalid loc/msg/type')
            for loc in item['loc']:
                if not isinstance(loc,str) and not (isinstance(loc,Decimal) and loc.is_finite() and loc==loc.to_integral_value()):raise ValueError('loc must be string or integer')
    return json.loads(body)

def query_values(query):
    values={}
    for key,value in query:
        if key in values or key not in ['since','node_link','latest']:raise ValueError('Duplicate or unknown query')
        if key!='node_link':
            if not re.fullmatch(r'[+-]?[0-9]+',value):raise ValueError('Query must be integer')
            value=int(value)
            if key=='latest' and not 0<=value<=500:raise ValueError('latest out of range')
        values[key]=value
    return dict(since=0,latest=0,**{})|values
