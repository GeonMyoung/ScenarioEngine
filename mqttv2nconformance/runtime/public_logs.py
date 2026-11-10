"""User-facing summaries and message evidence, separate from transport diagnostics."""
import re

STATE={'SUCCESS':'성공','FAIL':'실패','STOPPED':'중지','NOT_RUN':'미실행'}

def safe_text(text):
    if re.search(r'(?i)([a-z]:[\\/]|traceback|winerror|system\.|\.py:|\.cpp:|\.cs:)',text):
        return '시험을 진행하지 못했습니다. 접속·환경설정을 확인하세요. 상세 원인은 진단 기록에 보관했습니다.'
    return re.sub(r'\s*\[[A-Z][A-Z0-9_]+\]','',text)

def present(text,data,titles):
    d=data if isinstance(data,dict) else {}
    # Protocol handshakes, raw messages, internal worker phases and serialized results.
    if 'packet' in d or 'case' in d or ('tests' in d and 'profile' in d):return None
    if d.get('phase') in ('collect','collection_complete','unsubscribed','validation_complete'):return None
    public={}
    for key,label in [('received','수신 건수'),('validated','검증 건수'),('completed','완료 건수'),('published','발행 건수'),('expected','목표 건수'),('duplicates','중복 건수'),('target_per_kind','종류별 목표 건수')]:
        if key in d and isinstance(d[key],(int,float)):public[label]=d[key]
    for key,label in [('criterion','판정 기준'),('finding','확인 내용')]:
        if d.get(key):public[label]=safe_text(str(d[key]))
    if 'observed_seconds' in d:
        public.update({'판정 기준':d['criterion'],'실제 간격(초)':[round(v,3) for v in d['observed_seconds']],
                       '상한(초)':d['upper_seconds'],'초과 구간':[x['interval'] for x in d['outliers']]})
    if 'types' in d:
        public['종류별 결과']=[dict(종류=v['title'],검증=v['validated'],중복=v['duplicates'],결과={'CONFIRMED':'성공','MISSING':'미확인','PARTIAL':'확인 중','FAIL':'실패','STOPPED':'중지'}.get(v['result'],v['result'])) for v in d['types'].values()]
        public['미확인 종류']=[d['types'][key]['title'] for key in d.get('missing',[]) if key in d['types']]
    if 'result' in d:public['결과']=STATE.get(d['result'],d['result'])
    for key,label in [('title','정보 종류'),('target_ids','대상 구간'),('texts','제공 문구'),('speeds','제공 속도')]:
        if key in d:public[label]=d[key]
    if d.get('content_review')=='HELD':public['보류 사항']='content 선택값 차이의 적합성은 판정 보류'
    if 'content_choice' in d:public['TIM 내용 형식']=d['content_choice']
    if d.get('content_review')=='RECORD_ONLY':public['TIM 형식 처리']='수신 형식 기록 · 합불 기준 제외'
    if d.get('kind')=='failure':
        observed=d.get('observed') or {}
        if isinstance(observed,dict):
            for key,label in [('expected','기대값'),('actual','실제값'),('field','확인 위치')]:
                if key in observed:public[label]=observed[key]
        if d.get('next_checks'):public['확인할 사항']=[safe_text(str(x)) for x in d['next_checks']]
    if 'payload_hex' in d and d.get('direction') in ('송신','수신'):
        public.update({'메시지 순번':d['sequence'],'방향':d['direction'],'메시지 종류':d['message'],
                       '토픽':d['topic'],'관측 시각':d.get('observed_at'),
                       '메시지 결과':d['message_result'],'송수신 원문 HEX':d['payload_hex']})
        for key,label in [('version','V2N 버전'),('psid','PSID'),('message_id','메시지 ID'),
                          ('frame_id','MessageFrame ID'),('furtherInfoID','통행지시 식별값'),('itis','ITIS 코드'),
                          ('payload_sha256','원문 SHA-256')]:
            if key in d:public[label]=d[key]
        if 'fid' in d:public['FID']=f'0x{d["fid"]:04X}'
        if d.get('reason'):public['사유']=safe_text(d['reason'])
        if d.get('decoded') is not None:public['ASN.1 해석 결과']=d['decoded']
        if d['message_result']=='정합성 확인':
            public['판정 기준']='설정 토픽, V2N 식별값과 길이, ASN.1 구조와 필수 필드 일치'
            if 'itis' in d:public['판정 기준']+=' 및 furtherInfoID·ITIS 조합과 국내 확장 확인'
        return safe_text(text),public
    if 'decoded' in d and not d.get('title'):
        return '수신 정보의 형식과 필수값을 확인했습니다.',public
    return safe_text(text),public
