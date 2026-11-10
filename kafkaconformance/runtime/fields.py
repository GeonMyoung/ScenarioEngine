"""표 4-18~20 명확한 필드 제약. 불명확한 의미는 만들지 않는다."""
import base64
import datetime
import json
import math
from presentation import field_name

class FieldFailure(ValueError):
    def __init__(self,message):
        super().__init__(message);self.public_message=message

def strict_json(raw):
    def pairs(values):
        out = {}
        for k,v in values:
            if k in out: raise ValueError('중복 JSON 키: '+k)
            out[k]=v
        return out
    return json.loads(raw, object_pairs_hook=pairs, parse_constant=lambda s: (_ for _ in ()).throw(ValueError('비유한 숫자: '+s)))

def decode(raw, stream, encoding):
    if stream=='open' and encoding=='base64-json': raw=base64.b64decode(raw, validate=True)
    return strict_json(raw.decode('utf8'))

def validate(stream, value, evidence=None):
    checks=[]
    evidence=evidence if evidence is not None else []
    def record(key,expected,actual,result,scope=''):
        label=(field_name(scope)+' / ' if scope and scope not in ('open','platform','i2x','MAP 예시 profile') else '')+field_name(key)
        evidence.append({'항목':label,'기준':expected,'실제':actual,'결과':result})
    def obj(v,p):
        if not isinstance(v,dict):
            record(p,'JSON 객체',v,'불일치');raise FieldFailure(field_name(p)+'의 구조가 JSON 객체가 아닙니다.')
    def field(v,k,kind,lo=None,hi=None,required=True,p=''):
        path=p+'.'+k
        if k not in v:
            if required:
                record(k,'필수 항목','제공되지 않음','불일치',p);raise FieldFailure(field_name(k)+' 필수 항목이 없습니다.')
            record(k,'선택 항목','제공되지 않음','선택 항목 미제공',p)
            return
        x=v[k]
        good = (type(x) is int if kind=='int' else type(x) in (int,float) and math.isfinite(x) if kind=='number' else isinstance(x,str))
        expected={'int':'정수','number':'숫자','str':'문자열'}[kind]+(' · 필수' if required else ' · 제공된 선택 항목')
        if lo is not None:expected+=f' · {lo}~{hi}'
        if not good:
            record(k,expected,x,'불일치',p);raise FieldFailure(field_name(k)+'의 자료형이 기준과 다릅니다.')
        if lo is not None and not lo<=x<=hi:
            record(k,expected,x,'불일치',p);raise FieldFailure(field_name(k)+f' 값이 허용 범위 {lo}~{hi}를 벗어났습니다.')
        record(k,expected,x,'확인',p)
        checks.append(path)
    def group(v,k,required=False,p=''):
        if k not in v:
            if required:
                record(k,'필수 자료 묶음','제공되지 않음','불일치');raise FieldFailure(field_name(k)+' 필수 자료 묶음이 없습니다.')
            return None
        obj(v[k],p+'.'+k);return v[k]
    def nums(v,p,rules,required=True):
        for k,lo,hi in rules: field(v,k,'int',lo,hi,required,p)
    obj(value,stream)
    if stream=='facility':
        record('자료 형식','UTF-8 JSON 객체','JSON 객체','형식 확인 · 업무 의미 미확인')
        return ['JSON 객체·UTF-8·원문 전달 범위만 검사. 시설 업무 필드·두 토픽의 의미 분담 미확인.']
    if stream=='map':
        field(value,'messageId','int',18,18,p='MAP 예시 profile')
        v=group(value,'value',True,'MAP');field(v,'msgIssueRevision','int',0,127,p='MAP.value')
        if not isinstance(v.get('intersections'),list) or not v['intersections']:
            record('교차로 목록','비어 있지 않은 배열 (예시 기준)',v.get('intersections'),'불일치');raise FieldFailure('MAP 교차로 목록이 예시 기준의 배열 구조와 다릅니다.')
        record('교차로 목록','비어 있지 않은 배열 (예시 기준)',str(len(v['intersections']))+'개','확인')
        for i,inter in enumerate(v['intersections']):
            obj(inter,'intersection'); ident=group(inter,'id',True); nums(ident,'intersection.id',[('id',0,65535)])
            ref=group(inter,'refPoint',True);nums(ref,'refPoint',[('lat',-900000000,900000001),('long',-1799999999,1800000001)])
            if not isinstance(inter.get('laneSet'),list) or not inter['laneSet']:
                record('차로 목록','비어 있지 않은 배열 (예시 기준)',inter.get('laneSet'),'불일치');raise FieldFailure('MAP 차로 목록이 예시 기준의 배열 구조와 다릅니다.')
            record('차로 목록','비어 있지 않은 배열 (예시 기준)',str(len(inter['laneSet']))+'개','확인')
            for lane in inter['laneSet']: obj(lane,'lane');field(lane,'laneID','int',0,255,p='lane')
        return checks+['제3부 MAP JSON 예시 profile. 전체 ASN.1/UPER·ITSK-00144-2 적합성 미확인.']
    if stream=='i2x':
        for k in ('i2xID','i2xInterId','i2xConId','i2xConName','SDateTime'): field(value,k,'str',p=stream)
        loc=group(value,'i2xLocation',True);field(loc,'latitude','str',p='i2xLocation');field(loc,'longitude','str',p='i2xLocation')
        nums(value,stream,[(k,0,1) for k in ('i2xCnncSttus','iotCnncSttus','citsCnncSttus','i2xDoorSttus','i2xFanSttus','i2xHeaterSttus')]+[('i2xStrgTemp',-40,999),('i2xStrgHum',0,100)])
    elif stream=='platform':
        for g,rules in [('INTER_SERVER_STATUS',[('SERVER_STAT',0,1)]),('KAFKA_FCLTY_STATUS',[('KAFKA_STAT',0,1),('KAFKA_PORT',0,65535),('KAFKA_STTUS',0,1)]),('DATAHUB_PLATFORM_STATUS',[(k,0,65535) for k in ('DATAMANAGER_PORT','DATASERVICEBROKER_PORT','INGESTINTERFACE_PORT')]+[(k,0,1) for k in ('DATAMANAGER_STTUS','DATASERVICEBROKER_STTUS','INGESTINTERFACE_STTUS')])]:
            v=group(value,g)
            if v is None: continue
            nums(v,g,rules)
            if g=='INTER_SERVER_STATUS':
                field(v,'SERVER_DT','str',p=g);s=v['SERVER_DT']
                try:
                    if len(s)!=14 or not s.isascii() or not s.isdigit():raise ValueError()
                    datetime.datetime.strptime(s,'%Y%m%d%H%M%S')
                except ValueError:
                    record('SERVER_DT','유효한 YYYYMMDDhhmmss 시각',s,'불일치');raise FieldFailure('서버 시각의 날짜·시간 형식이 기준과 다릅니다.')
                record('SERVER_DT','유효한 YYYYMMDDhhmmss 시각',s,'확인')
    elif stream=='open':
        v=group(value,'utctime')
        if v is not None: nums(v,'utctime',[('year',0,4095),('month',0,12),('day',0,31),('hour',0,31),('minute',0,60),('second',0,65535)])
        v=group(value,'objectData')
        if v is not None:
            nums(v,'objectData',[('objectType',0,2),('objectID',0,255),('novelty',0,1)]);field(v,'reliability','int',0,100,False,'objectData')
            r=group(v,'refPosition',True);nums(r,'refPosition',[('long',-199999999,1800000001),('lat',-900000000,900000001)],False)
            f=group(v,'FullPositionVector')
            if f is not None:
                nums(f,'FullPositionVector',[('long',-199999999,1800000001),('lat',-900000000,900000001),('heading',0,28800)]);field(f,'elevation','int',-4096,61439,False,'FullPositionVector')
                for g,rules,mandatory in [('speed',[('speed',0,8191)],True),('posAccuracy',[('semiMajor',0,255),('semiMinor',0,255),('orientation',0,65535)],False),('posConfidence',[('timeConfidence',0,39),('pos',0,15),('elevation',0,15)],False),('speedConfidence',[('heading',0,7),('speed',0,7),('throttle',0,3)],False)]:
                    a=group(f,g)
                    if a is not None:
                        nums(a,g,rules,mandatory)
                        if g=='speed': field(a,'transmission','int',0,7,False,g)
        v=group(value,'weatherData',True)
        if v is not None:
            field(v,'macAddr','str',p='weatherData');nums(v,'weatherData',[('device-state',0,1),('installationStatus',0,1),('trafficCount',0,65535),('roadCondition',0,1)])
            for k in ('forwardAxialStiffness','transverseAxialStiffness'): field(v,k,'number',-100,100,p='weatherData')
            field(v,'waterLevel','number',p='weatherData')
            good=0<=v['waterLevel']<=4000 or v['waterLevel']==65535
            record('waterLevel','0~4000 또는 측정불가 코드 65535',v['waterLevel'],'확인' if good else '불일치')
            if not good:raise FieldFailure('수막 두께가 허용 범위 또는 측정불가 코드와 다릅니다.')
            w=group(v,'weather',True)
            for k,lo,hi in [('temperature',-400,800),('humidity',0,1000),('view-range',1,1000),('wind-dir',1,359),('wind-speed',1,400),('air-pressure',1500,11000),('rain',0,1000),('sun',0,20000),('surface-temp',-5000,11000),('underground-temp',-5000,11000),('freezing-temp',-5000,11000),('salt-concentration',0,3000)]: field(w,k,'number',lo,hi,p='weather')
            field(w,'w-condition','int',0,4,p='weather')
        v=group(value,'tailLampIntensity')
        if v is not None: field(v,'intensity','int',0,9,False,'tailLampIntensity')
        v=group(value,'safetyMessage')
        if v is not None:
            nums(v,'safetyMessage',[('limitspeed',10,120),('trafficsign',0,60)])
            nums(v,'safetyMessage',[('safetylevel',0,3),('messageclass',0,4),('vmsmessage',0,60)],False)
        v=group(value,'systemStatus')
        if v is not None: nums(v,'systemStatus',[(k,0,1) for k in ('ObjectDetectionSystem','WeatherSensorSystem','InfraEdgePlatform')])
    if not checks: raise ValueError('검사할 알려진 업무 필드가 없습니다 (개발 시험 자료 준비 조건).')
    return checks
