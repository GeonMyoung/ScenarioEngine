"""Role-scoped tests and explicit topic configuration (MQTT-TOPIC-001)."""
import math
from pathlib import Path
from credentials import unprotect,validate as validate_credentials
from tim_five import TYPES as TIM_TYPES

MESSAGES = {
    'bsm': dict(title='BSM 차량 안전정보',fid=0xff10,psid=82050,frame=20,period=1),
    'spat': dict(title='SPaT 신호정보',fid=0xff11,psid=82055,frame=19,period=1),
    'tlsm': dict(title='TLSM 신호등 상태정보',fid=0xff12,psid=82176,frame=50,period=1),
    'tim': dict(title='TIM 여행자 정보',fid=0xff13,psid=82054,frame=31,period=None),
}
BSM_PUBLISH_CASE='vehiclePublisher2center_mqtt_v1'
MQTT_RESPONSE_TIMEOUT=30
CENTER_PROVIDER_CASE='vehicleSubscriber2center_mqtt_v1'
CENTER_SINGLE_CASES={
    'vehicleSubscriber2center_spat_mqtt_v1':'spat',
    'vehicleSubscriber2center_tlsm_mqtt_v1':'tlsm',
    'vehicleSubscriber2center_tim_mqtt_v1':'tim',
}
CASES = {
    'centerSubscriber2vehicle_mqtt_v1': dict(sut='자율주행차량',engine='통합교통관제시스템',receive=True,messages=['bsm']),
    'vehiclePublisher2center_mqtt_v1': dict(sut='통합교통관제시스템',engine='자율주행차량',receive=False,messages=['bsm'],publish_only=True),
    CENTER_PROVIDER_CASE: dict(sut='통합교통관제시스템',engine='자율주행차량',receive=True,center_provider=True,messages=['spat','tlsm','tim']),
    'centerPublisher2vehicle_mqtt_v1': dict(sut='자율주행차량',engine='통합교통관제시스템',receive=False,messages=['spat','tlsm','tim']),
}
for case,message in CENTER_SINGLE_CASES.items():
    CASES[case]=dict(CASES[CENTER_PROVIDER_CASE],messages=[message])


def items(case):
    c=CASES[case]; result=[]
    for key in c['messages']:
        if c.get('center_provider') and key=='tim':
            result.extend((f'test_tim_{kind}','tim',kind,'TIM '+definition[0]+' 제공 확인') for kind,definition in TIM_TYPES.items())
            continue
        result.append((f'test_{key}_normal',key,'normal',('BSM 발행 절차 확인 (최종 합격은 사후 로그 대조)' if c.get('publish_only') else MESSAGES[key]['title']+(' 제공 확인' if c['receive'] else ' 수신 관측 확인'))))
    return result


def topic(value):
    if not isinstance(value,str) or not value.strip() or len(value.encode('utf-8'))>65535 or any(x in value for x in ('\0','#','+')):
        raise ValueError('실제 발행·수신 토픽을 입력하세요. 빈 값·NUL·와일드카드는 사용할 수 없습니다.')
    # Preserve spaces, case and slashes; never normalize the configured topic.
    return value


def number(c,key,default,low,high,integer=False):
    value=c.get(key,default)
    if isinstance(value,bool):raise ValueError(key+': 숫자를 입력하세요.')
    try:value=float(value)
    except (TypeError,ValueError):raise ValueError(key+': 숫자를 입력하세요.')
    if not math.isfinite(value) or not low<=value<=high or (integer and value!=int(value)):
        raise ValueError(f'{key}: {low}~{high} 범위로 입력하세요.')
    c[key]=int(value) if integer else value


def parse_config(case,raw):
    if case not in CASES or not isinstance(raw,dict):raise ValueError('지원하지 않는 MQTT 시험 또는 설정입니다.')
    c=unprotect(raw);c['case']=case
    role=CASES[case]
    center_provider=role.get('center_provider',False)
    tim_enabled=center_provider and 'tim' in role['messages']
    if center_provider:
        if c.get('byte_order','big')!='big':
            raise ValueError('센터 정보제공시험의 바이트 순서는 big으로 고정됩니다. 새 시험환경설정을 적용하세요.')
    if tim_enabled:
        old=c.pop('test_tim_normal',False)
        if old in (True,'true','on',1) and not any('test_tim_'+kind in c for kind in TIM_TYPES):
            for kind in TIM_TYPES:c['test_tim_'+kind]=True
    if role['receive']:
        # Saved selections for the former interval check become content checks.
        for key in role['messages']:
            if MESSAGES[key]['period'] and c.pop(f'test_{key}_period',False) in (True,'true','on',1):
                c[f'test_{key}_normal']=True
        for key in ('period_mode','period_samples','period_tolerance_seconds','tim_timeout_seconds'):
            c.pop(key,None)
        c['timeout_seconds']=MQTT_RESPONSE_TIMEOUT
    if str(c.get('qos',0)) not in ('0','0.0'):
        raise ValueError('MQTT QoS는 0으로 고정됩니다.')
    c['qos']=0
    validate_credentials(c)
    if case==BSM_PUBLISH_CASE:
        for key,value in dict(publish_interval_seconds=1,container_version=0,standard_type=1).items():
            if key in c and (isinstance(c[key],bool) or str(c[key]) not in (str(value),str(float(value)))):raise ValueError(f'BSM 발행시험의 {key}는 {value}로 고정됩니다.')
            c[key]=value
        if c.get('byte_order','big')!='big':raise ValueError('BSM 발행시험의 바이트 순서는 big으로 고정됩니다.')
        c.pop('observation_file',None)
    known={x[0] for x in items(case)}
    if any(k.startswith('test_') and v in (True,'true','on',1) and k not in known for k,v in c.items()):
        raise ValueError('현재 역할에서 지원하지 않는 시험 항목이 선택되었습니다.')
    selected=[x for x in items(case) if c.get(x[0]) in (True,'true','on',1)]
    if not selected:raise ValueError('시험 항목을 하나 이상 선택하세요.')
    c['selected']=selected
    if tim_enabled:
        number(c,'tim_per_type',1,1,100,True)
    for key,default,low,high,integer in [
        ('port',1883,1,65535,True),('keepalive',30,5,3600,True),
        ('repetitions',10,1,1000,True),('timeout_seconds',30,1,300,False),
        ('publish_interval_seconds',1,0,60,False),('container_version',0,0,0,True),
        ('standard_type',1,1,1,True)]:number(c,key,default,low,high,integer)
    if not isinstance(c.get('host'),str) or not c['host'].strip() or '\0' in c['host']:
        raise ValueError('Broker 주소를 입력하세요.')
    c.setdefault('client_id','')
    if not isinstance(c['client_id'],str) or '\0' in c['client_id']:
        raise ValueError('시험 시스템 Client ID를 확인하세요.')
    c.setdefault('byte_order','big')
    if c['byte_order'] not in ('big','little'):raise ValueError('byte_order는 big 또는 little로 입력하세요.')
    for key in CASES[case]['messages']:
        if any(x[1]==key for x in selected):c['topic_'+key]=topic(c.get('topic_'+key))
        elif c.get('topic_'+key):c['topic_'+key]=topic(c['topic_'+key])
    if c.pop('security_file',''):raise ValueError('Username·Password 입력칸을 사용하세요. 별도 인증 파일은 사용하지 않습니다.')
    c.setdefault('ca_file','')
    if c['ca_file'] and not Path(c['ca_file']).is_file():raise ValueError('TLS CA 인증서 파일을 찾을 수 없습니다.')
    if not CASES[case]['receive'] and case!=BSM_PUBLISH_CASE:
        if not isinstance(c.get('observation_file'),str) or not c['observation_file'].strip():
            raise ValueError('대상 수신 확인용 실시간 관측 JSONL 파일을 지정하세요. Broker ACK만으로 대상 수신을 판정하지 않습니다.')
    return c


def ui(case):
    c=CASES[case];groups=[]
    center_provider=c.get('center_provider',False)
    tim_only=center_provider and c['messages']==['tim']
    def group(label):groups.append(dict(type='FieldSet',option=dict(label=label),components=[]))
    def field(name,label,value='',kind='text'):
        option=dict(name=name,label=label,type=kind)
        if kind!='checkbox':option['value']=str(value)
        groups[-1]['components'].append(dict(type='Input',option=option))
    group('MQTT 접속 · QoS 0 고정')
    field('host','Broker 주소','127.0.0.1');field('port','Broker 포트',1883,'number')
    field('username','Username (인증 시 입력)');field('password','Password (인증 시 입력)')
    group('선택 접속 설정')
    field('client_id','시험 시스템 Client ID (비우면 자동 생성)')
    field('ca_file','TLS CA 인증서 경로 (필요한 경우)')
    if case==BSM_PUBLISH_CASE:
        group('BSM 발행 조건 — V2N version 0 · 1초 주기·QoS 0 · 회차별 다른 시험값')
        field('topic_bsm','BSM 발행 토픽');field('repetitions','메시지 발행 횟수',10,'number')
        group('자동 성공은 발행 절차 완료 / 최종 합격은 센터 수신 로그 사후 대조')
        for key,_,_,title in items(case):field(key,title,kind='checkbox')
        return dict(scenarios=[dict(key=k,title=t) for k,_,_,t in items(case)],configuration=[dict(type='Div',option=dict(direction='col'),components=groups)])
    group('메시지별 실제 토픽')
    for key in c['messages']:field('topic_'+key,MESSAGES[key]['title']+' 토픽')
    if not tim_only:
        group('수신 조건 · 필요한 건수를 확인할 때까지 대기' if c['receive'] else '시험 조건')
        field('repetitions','수신 건수' if c['receive'] else '정보교환 횟수',10,'number')
        if not c['receive']:
            field('timeout_seconds','대상 수신 증적 대기 제한 (초)',30,'number')
            field('publish_interval_seconds','시험 자료 발행 간격 (초)',1,'number')
            field('observation_file','대상 수신 관측 JSONL 경로 (실시간 어댑터)')
    if center_provider and 'tim' in c['messages']:
        group('TIM 통행지시 · 선택한 모든 종류를 확인할 때까지 대기')
        field('tim_per_type','선택한 TIM 종류별 확인 건수',1,'number')
    if not center_provider:
        group('경4 컨테이너 적용값')
        field('container_version','V2N 컨테이너 버전 (0 고정)',0,'number')
        field('standard_type','표준 유형 (현재 KS 코덱 지원: 1)',1,'number')
        field('byte_order','바이트 순서 (개발 기본 big / 합의값 little)','big')
    group('선택 시험')
    for key,_,_,title in items(case):field(key,title,kind='checkbox')
    return dict(scenarios=[dict(key=k,title=t) for k,_,_,t in items(case)],
                configuration=[dict(type='Div',option=dict(direction='col'),components=groups)])
