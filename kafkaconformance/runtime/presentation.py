"""Public Korean evidence. Internal correlation/diagnostics stay in records.jsonl."""
import base64,html,json
from pathlib import Path
from catalog import CASES,STREAMS

VERDICTS={'SUCCESS':'성공','FAIL':'실패','STOPPED':'중지','NOT_RUN':'미실행'}
NAMES={'utctime':'자료 시각','year':'년','month':'월','day':'일','hour':'시','minute':'분','second':'초',
 'objectType':'객체 종류','objectID':'객체 번호','novelty':'신규·갱신 구분','reliability':'신뢰도','refPosition':'기준 위치',
 'FullPositionVector':'객체 위치·이동 정보','long':'경도','longitude':'경도','lat':'위도','latitude':'위도','elevation':'고도','heading':'방향',
 'speed':'속도','transmission':'변속 상태','semiMajor':'위치 오차 장축','semiMinor':'위치 오차 단축','orientation':'오차 방향',
 'timeConfidence':'시각 신뢰도','pos':'위치 신뢰도','throttle':'가속 신뢰도','macAddr':'기기 식별값','device-state':'기기 상태',
 'temperature':'온도','humidity':'습도','view-range':'시정 거리','wind-dir':'풍향','wind-speed':'풍속','air-pressure':'대기압',
 'w-condition':'기상 구분','rain':'강수량','sun':'일사량','surface-temp':'노면 온도','underground-temp':'지중 온도',
 'freezing-temp':'결빙 온도','salt-concentration':'염분 농도','installationStatus':'설치 상태','trafficCount':'차량 통행 수',
 'forwardAxialStiffness':'종축 기울기','transverseAxialStiffness':'횡축 기울기','roadCondition':'노면 상태','waterLevel':'수막 두께',
 'intensity':'램프 광도','safetylevel':'안전 등급','messageclass':'안전정보 분류','limitspeed':'제한속도','trafficsign':'안전표지',
 'vmsmessage':'전광판 메시지 번호','ObjectDetectionSystem':'객체 검지 시스템 상태','WeatherSensorSystem':'기상센서 상태','InfraEdgePlatform':'인프라 엣지 플랫폼 상태',
 'weatherData':'기상·노면 정보','weather':'기상 측정값','i2xID':'I2X 장비 번호','i2xInterId':'설치 교차로','i2xConId':'국가 코드',
 'i2xConName':'국가 이름','SDateTime':'송신 날짜','i2xLocation':'장비 위치','i2xCnncSttus':'장비 동작 상태','iotCnncSttus':'IoT 통신 상태',
 'citsCnncSttus':'C-ITS 통신 상태','i2xStrgTemp':'함체 온도','i2xStrgHum':'함체 습도','i2xDoorSttus':'문 상태','i2xFanSttus':'팬 상태','i2xHeaterSttus':'히터 상태',
 'SERVER_DT':'서버 시각','SERVER_STAT':'서버 동작 상태','KAFKA_STAT':'Kafka 동작 상태','KAFKA_PORT':'Kafka 접속 포트','KAFKA_STTUS':'Kafka 연결 상태',
 'DATAMANAGER_PORT':'데이터매니저 포트','DATAMANAGER_STTUS':'데이터매니저 상태','DATASERVICEBROKER_PORT':'데이터서비스브로커 포트',
 'DATASERVICEBROKER_STTUS':'데이터서비스브로커 상태','INGESTINTERFACE_PORT':'수집 인터페이스 포트','INGESTINTERFACE_STTUS':'수집 인터페이스 상태',
 'messageId':'메시지 종류','msgIssueRevision':'자료 개정 번호','id':'교차로 번호','laneID':'차로 번호'}

NAMES.update({'objectData':'객체 정보','posAccuracy':'위치 정확도','posConfidence':'위치 신뢰도','speedConfidence':'속도·방향 신뢰도',
              'intersection.id':'교차로 참조정보','refPoint':'교차로 기준 위치','lane':'차로 정보',
              'INTER_SERVER_STATUS':'서버 상태','KAFKA_FCLTY_STATUS':'Kafka 상태','DATAHUB_PLATFORM_STATUS':'데이터허브 상태'})
def field_name(key):
    aliases={'open':'인프라 오픈데이터','platform':'플랫폼 상태정보','i2x':'I2X 상태정보','map':'MAP 자료','facility':'시설정보'}
    if key in aliases:return aliases[key]
    return NAMES.get(key,key)+' ('+key+')' if key in NAMES else key
def mask(value):
    if isinstance(value,dict):return {k:('***' if any(s in str(k).lower() for s in ('password','secret','token','authorization','apikey','api_key')) else mask(v)) for k,v in value.items()}
    if isinstance(value,list):return [mask(v) for v in value]
    return value
def offset(value):return '이전 소비 기록 없음' if value is None or value<0 else value
def basis(stream):
    return {'open':'제3부 표 4-18의 명확한 필수 항목·자료형·값 범위와 사전 합의한 JSON 포장',
      'platform':'제3부 표 4-20의 명확한 필드 제약 및 문서 차이를 정리한 프로젝트 적용 기준',
      'i2x':'제3부 표 4-19의 필수 항목·문자열/정수 자료형·값 범위',
      'map':'제3부 표 4-17의 MAP JSON 예시 중 현재 검사하는 주요 구조',
      'facility':'사전 합의한 시설정보 JSON의 형식과 전달·소비 위치 관측'}[stream]
def limits(stream,provider):
    values=['대상 시스템 내부 업무 처리·데이터베이스 반영은 직접 확인하지 않았습니다.',
            'Kafka 브로커 제품 전체의 적합성은 이번 시험의 판정 대상이 아닙니다.']
    if stream=='facility':values.insert(0,'시설 업무 필드의 의미·필수성 및 두 시설 토픽의 역할 분담은 미확인입니다.')
    if stream=='map':values.insert(0,'전체 MAP 필드의 의미와 BER/UPER 인코딩 적합성은 검사하지 않습니다.')
    if not provider:values.insert(0,'브로커에 저장된 대상의 소비 위치로 확인합니다. 대상 내부 처리를 직접 확인한 결과는 아닙니다.')
    return values
def introduction(case,c,stream,mode,title):
    _,provider,source,_=CASES[case];count=c['period_samples'] if mode=='period' else c['repetitions']
    check='받은 자료의 형식·필드를 검사하고, 검사한 다음 읽기 위치가 브로커에 저장됐는지 대조합니다.' if provider else '유효 자료를 보내고, 브로커 수용과 대상 소비 위치의 진전을 각각 확인합니다.'
    v={'자료 구분':'시험 안내','시험':title,'목적':STREAMS[stream][0]+'의 '+('제공' if provider else '수신')+' 기능 확인',
       '시험 대상':source+' (정보 제공)' if provider else '통합교통관제시스템 (정보 수신)',
       '정보 방향':source+' → 브로커 → 통합교통관제시스템','토픽':c['topic_'+stream],
       '진행 절차':['합의한 토픽과 시험 시작 위치를 준비합니다.',check,f'{count}회 수행하고 실제 결과를 기대 조건과 대조합니다.'],
       '판정 기준':basis(stream),'시험방법 적용':('제4부 3.1.1의 읽기·저장 위치 확인을 시험 시스템에 적용하여 대상의 제공 자료를 확인합니다.' if provider else '제4부 3.2.1의 소비·저장 위치 확인 절차 중 직접 관측할 수 있는 범위를 적용합니다.'),
       '성공 조건':f'선택한 {count}회의 자료 교환과 해당 관측 검사를 모두 충족해야 합니다.',
       '준비자료':('대상이 발행하는 실제 수신 자료' if provider else '표준 정의와 프로젝트 적용 기준에 맞춰 준비한 시험 자료'),
       '확인 범위':limits(stream,provider)}
    if stream=='facility':v['준비자료']+=' · 합의한 JSON 자료이며 시설 업무 의미 전체의 적합성을 뜻하지 않습니다.'
    if mode=='period':
        v['주기 기준']={'합의 주기(초)':c['period_'+stream],'허용오차(초)':c['period_tolerance_seconds'],'측정 표본':count,
                     '시간 조건':'엑셀 기본 주기' if c['period_'+stream]==STREAMS[stream][2] else '변경된 개발 시간 조건'}
        v['성공 조건']+= ' 측정한 모든 간격이 합의 주기와 허용오차 안에 있어야 합니다.'
    return v

def observation(event,detail):
    """Return meaningful evidence only. The complete adapter trace remains local."""
    if event=='토픽 Metadata 조회':return ('전달 경로 확인','합의한 토픽을 브로커에서 확인했습니다.',{'토픽':detail['topic'],'결과':'준비 완료'})
    if event=='초기 저장 offset 조회':
        return ('소비 위치 준비','이전 자료와 구분하여 이번 시험의 시작 위치를 준비했습니다.',
                {'이전 소비 기록':[{'자료 구간':p,'다음 읽기 위치':offset(v)} for p,v in detail['committed'].items()]})
    if event=='OffsetCommit 요청':return None
    if event=='발행 저장 ACK':return ('브로커 수용 확인','브로커가 보낸 자료를 수용했습니다. 대상의 소비 여부는 이어서 확인합니다.',{'기대':'브로커의 정상 수용','실제':'정상 수용','결과':'확인'})
    if event in ('commit 후 저장 offset 재조회','대상 Group 저장 offset 관측'):
        minimum=event=='대상 Group 저장 offset 관측';expected=detail['expectedAtLeast'] if minimum else detail['expected'];actual=detail['actual']
        good=actual>=expected if minimum else actual==expected
        return ('소비 위치 확인',('대상의 소비 위치가 보낸 자료 다음으로 진전했습니다.' if minimum else '검사 후 저장한 소비 위치가 기대값과 일치합니다.') if good else '저장된 소비 위치가 기대 조건을 충족하지 못했습니다.',
                {'확인 방법':'브로커가 보관한 다음 읽기 위치를 조회하여 대조','기대':str(expected)+(' 이상' if minimum else ''),'실제':offset(actual),'결과':'확인' if good else '불일치'})
    if event=='주기 관측':
        expected=detail['expectedSeconds'];actual=detail['actualSeconds'];tolerance=detail['toleranceSeconds'];good=abs(actual-expected)<=tolerance
        return ('전송 주기 확인',f'기대 {expected:g}초, 실제 {actual:.3f}초, 허용오차 ±{tolerance:g}초를 대조했습니다.',
                {'기대 주기(초)':expected,'실제 간격(초)':round(actual,6),'허용오차(초)':tolerance,'결과':'확인' if good else '불일치'})
    return None

def failure(error):
    # Field failures carry controlled public evidence, not Python exceptions.
    if hasattr(error,'public_message'):return error.public_message
    if isinstance(error,TimeoutError):return '제한시간 안에 필요한 자료 또는 소비 위치의 진전을 확인하지 못했습니다. 대상 준비 상태·토픽·소비 그룹과 대기시간을 확인하세요.'
    if isinstance(error,UnicodeError):return '받은 자료를 UTF-8 문자로 읽을 수 없습니다. 양측의 전송 형식을 확인하세요.'
    if isinstance(error,json.JSONDecodeError):return '받은 자료의 JSON 구조를 읽을 수 없습니다. 전송 내용과 합의한 포장을 확인하세요.'
    if isinstance(error,ValueError):
        text=str(error)
        if any(s in text for s in ('base64','padding','ASCII','alphabet')):return '합의한 Base64 포장으로 자료를 해석하지 못했습니다. 양측의 포장 설정을 확인하세요.'
        if any(s in text for s in ('범위','필수','자료형','누락','JSON','주기','설정')) and not any(s in text for s in ('\\', 'Traceback', 'C:/')):return text
    if isinstance(error,FileNotFoundError):return '준비자료 또는 실행환경을 찾을 수 없습니다. 선택한 자료와 간편 실행 묶음을 확인하세요.'
    return '시험 준비 또는 통신을 완료하지 못했습니다. 연결·대상 준비 상태를 확인하고 필요하면 진단 기록을 확인하세요.'

def write_report(path,summary,entries):
    esc=html.escape
    def render(v,depth=0):
        if depth>=2 and isinstance(v,(dict,list)):return '<pre>'+esc(json.dumps(v,ensure_ascii=False,indent=2))+'</pre>'
        if isinstance(v,dict):return '<dl>'+''.join('<dt>'+esc(str(k))+'</dt><dd>'+render(x,depth+1)+'</dd>' for k,x in v.items())+'</dl>'
        if isinstance(v,list):
            if v and all(isinstance(x,dict) and '항목' in x and '기준' in x for x in v):
                keys=['항목','기준','실제','결과'];return '<div class="table"><table><thead><tr>'+''.join('<th>'+k+'</th>' for k in keys)+'</tr></thead><tbody>'+''.join('<tr>'+''.join('<td>'+render(x.get(k,''))+'</td>' for k in keys)+'</tr>' for x in v)+'</tbody></table></div>'
            return '<ul>'+''.join('<li>'+render(x,depth+1)+'</li>' for x in v)+'</ul>'
        return '<span>'+esc('없음' if v is None else str(v))+'</span>'
    doc='''<!doctype html><html lang="ko"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Kafka 시험 결과</title><style>
body{margin:0;background:#f6f4ed;color:#243b30;font:15px/1.7 "Malgun Gothic",sans-serif}main{max-width:1100px;margin:auto;padding:32px 24px}h1{font-size:30px}h2{margin-top:36px;border-bottom:2px solid #42634c}h3{font-size:18px;margin:0 0 12px}article{padding:24px 0;border-bottom:1px solid #c9d1c4}dl{display:grid;grid-template-columns:minmax(130px,22%) minmax(0,1fr);margin:8px 0;gap:0 16px}dt,dd{margin:0;padding:7px 0;border-bottom:1px solid #e1e4dc}dt{font-weight:600}dd{overflow-wrap:anywhere}.sender{color:#53685c}.summary{background:#e5ecdf;padding:20px}.table{overflow:auto}table{border-collapse:collapse;width:100%;background:white}th,td{border:1px solid #d1d8cd;padding:8px;text-align:left}th{background:#e5ecdf}ul{padding-left:22px;margin:0}pre{white-space:pre-wrap;overflow-wrap:anywhere;background:white;padding:12px;border:1px solid #d1d8cd}@media(max-width:650px){dl{display:block}dt{border:0;padding-bottom:0}main{padding:20px 14px}}@media print{body{background:white}article{break-inside:avoid}}</style><main><h1>Kafka 시험 결과</h1><p>목적・기준・실제 자료와 판정 근거를 확인하세요. 자세한 기술 진단은 별도로 보존합니다.</p><section class="summary">'''+render(summary)+'</section><h2>진행 기록과 시험 자료</h2>'
    with Path(path).open('w',encoding='utf8') as f:
        f.write(doc)
        for e in entries:f.write('<article><h3>'+esc(e['log'])+'</h3>'+('<p class="sender">발송: '+esc(e['sender'])+'</p>' if e.get('sender') else '')+(render(e['data']) if e.get('data') else '')+'</article>')
        f.write('</main></html>')


def stage(message,data=None):
    if data:
        kind=data.get('자료 구분','')
        if kind=='송수신 데이터':return '수신' if data.get('방향')=='수신' else '송신'
        if '결과' in kind:return '결과'
        if kind=='시험 안내':return '시험 안내'
        if data.get('단계') in ('전달 경로 확인','소비 위치 준비'):return '준비'
        return '판정 근거'
    if '시작' in message:return '시험 안내'
    if '중지' in message or '종료' in message:return '결과'
    return '진행'

