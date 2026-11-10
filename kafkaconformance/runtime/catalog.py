"""Case IDs, selectable tests and explicit environment settings (KAFKA-G4-001)."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STREAMS = {
    'open': ('인프라 오픈데이터', 'InfraOpenData', 60),
    'platform': ('플랫폼 서버 상태', 'ServPlatformStat', 600),
    'facility': ('교통안전시설정보', 'xcms-external-collect.pol1.i2x_fclty_info', 60),
    'map': ('MAP 시설정보', 'xcms-external-collect.pol1.map', 60),
    'i2x': ('I2X 상태·관리정보', 'xcms-external-collect.pol1.i2x_inter_status', 10),
}
CASES = {
    'platform2ut_kafka_v1': ('SC12', False, '교통안전인프라 플랫폼', ['open', 'platform']),
    'ut2platform_kafka_v1': ('SC33', True, '교통안전인프라 플랫폼', ['open', 'platform']),
    'i2x2ut_kafka_v1': ('SC13', False, 'I2X 연계장치', ['facility', 'map', 'i2x']),
    'ut2i2x_kafka_v1': ('SC34', True, 'I2X 연계장치', ['facility', 'map', 'i2x']),
}

def items(case):
    return [(f'test_{s}_{mode}', s, mode, STREAMS[s][0] + (' 정보교환·소비 확인' if mode == 'normal' else ' 합의 주기 확인 [추가]'))
            for s in CASES[case][3] for mode in ('normal', 'period')]

def ui(case):
    _, provider, source, streams = CASES[case]
    groups = []
    def group(label):
        groups.append(dict(type='FieldSet', option=dict(label=label), components=[]))
    def field(name, label, value='', kind='text'):
        option = dict(name=name, label=label, type=kind)
        if kind != 'checkbox': option['value'] = str(value)
        groups[-1]['components'].append(dict(type='Input', option=option))
    group('사전 합의한 Kafka 시험환경')
    field('bootstrap_servers', '브로커 주소 목록 (host:port, 쉼표 구분)', '127.0.0.1:29092')
    field('group_id', '시험 시스템 소비 그룹 ID' if provider else '시험 대상 소비 그룹 ID')
    field('security_file', '인증·TLS 설정 JSON 파일 (미입력: PLAINTEXT)')
    field('auto_offset_reset', '기존 자료의 시작 위치 설정 (earliest / latest)', 'latest')
    field('timeout_seconds', '자료 수신·소비 확인 대기시간 (초)', 30, 'number')
    field('repetitions', '정보교환 반복 횟수 (최소 10)', 10, 'number')
    field('period_samples', '주기 표본 수 (최소 2)', 2, 'number')
    field('period_tolerance_seconds', '주기 허용오차 (초, 시험환경 합의값)', 2, 'number')
    group('연계정보별 합의 토픽과 주기 — 빈 토픽은 실행할 수 없습니다')
    for s in streams:
        title, example, period = STREAMS[s]
        field('topic_'+s, title+' 토픽 (자료의 예: '+example+')')
        field('period_'+s, title+' 주기 (초, 엑셀 기본값)', period, 'number')
    if 'open' in streams:
        field('open_encoding', '오픈데이터 포장 (json / base64-json, 사전 합의)', 'json')
    if 'facility' in streams:
        field('facility_fixture', '시설정보 합의 자료 (기본 제공 자료 또는 선택한 JSON 파일)')
    group('선택 시험 — 목적과 역할은 시험 대상 기준')
    for key, _, _, title in items(case): field(key, title, kind='checkbox')
    return dict(scenarios=[dict(key=k, title=t) for k,s,m,t in items(case)],
                configuration=[dict(type='Div', option=dict(direction='col'), components=groups)])

def parse_config(case, raw):
    c = dict(raw)
    c['case'] = case
    for name, default, low, high in [('repetitions',10,10,1000), ('period_samples',2,2,100), ('timeout_seconds',30,1,300), ('period_tolerance_seconds',2,0,60)]:
        label={'repetitions':'반복 횟수','period_samples':'주기 표본 수','timeout_seconds':'대기시간','period_tolerance_seconds':'주기 허용오차'}[name]
        try: v=float(c.get(name, default))
        except (ValueError, TypeError): raise ValueError(label+'에 숫자를 입력하세요.')
        if not low <= v <= high or (name in ('repetitions','period_samples') and v != int(v)): raise ValueError(label+f'는 {low}~{high} 범위로 입력하세요.')
        c[name] = int(v) if name in ('repetitions','period_samples') else v
    c['selected'] = [x for x in items(case) if c.get(x[0]) in (True, 'true', 'on', 1)]
    if not c['selected']: raise ValueError('시험 항목을 하나 이상 선택하세요.')
    if not str(c.get('bootstrap_servers','')).strip() or not str(c.get('group_id','')).strip(): raise ValueError('브로커와 Consumer Group ID를 입력하세요.')
    c.setdefault('auto_offset_reset','latest')
    if c['auto_offset_reset'] not in ('earliest','latest'): raise ValueError('offset 정책 오류')
    c.setdefault('open_encoding','json')
    if c['open_encoding'] not in ('json','base64-json'): raise ValueError('오픈데이터 포장을 명시적으로 선택하세요.')
    topics = []
    for s in dict.fromkeys(x[1] for x in c['selected']):
        topic = str(c.get('topic_'+s,'')).strip()
        if not topic or len(topic)>249 or topic in ('.','..') or any(ch not in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-' for ch in topic): raise ValueError(STREAMS[s][0]+': 합의 토픽을 입력하세요.')
        topics.append(topic); c['topic_'+s]=topic
        c['period_'+s]=float(c.get('period_'+s,STREAMS[s][2]))
        if not 0 < c['period_'+s] <= 86400: raise ValueError('주기 범위 오류')
        if any(x[1]==s and x[2]=='period' for x in c['selected']) and c['period_tolerance_seconds']>=c['period_'+s]: raise ValueError('주기 허용오차는 주기보다 작아야 합니다.')
    if len(topics)!=len(set(topics)): raise ValueError('정보별 토픽은 이 실행에서 서로 구분되어야 합니다.')
    if c.get('facility_fixture')=='기본 제공 자료':c['facility_fixture']=str(ROOT/'fixtures/map.json')
    if any(x[1]=='facility' for x in c['selected']) and not Path(c.get('facility_fixture','')).is_file(): raise ValueError('시설정보 사전 합의 JSON 파일을 준비하세요.')
    return c

def fixture(stream, config):
    path = Path(config['facility_fixture']) if stream == 'facility' else ROOT/'fixtures'/(stream+'.json')
    return json.loads(path.read_text(encoding='utf-8-sig'))
