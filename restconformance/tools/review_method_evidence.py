"""Review engine/peer evidence without modifying either source."""
import argparse
import hashlib
import json
import re
from pathlib import Path
from urllib.parse import urlsplit
import xml.etree.ElementTree as ET
from evidence_values import EvidenceError, loads, read_json, read_events, require, rows, same_rows, same_value
from evidence_method_contract import correlate, index, integer

REVIEW_PROFILE = 'REST-REVIEW-003'


def selected(events, name):
    return [e for e in events if e['event'] == name]


def count(value, expected, label):
    require(integer(value, label) == expected, label + ': 건수가 다릅니다.')


def status(value, expected):
    require(integer(value, '응답 코드') == expected, '교환에 연결된 응답 코드가 다릅니다.')

def query_names_match(actual, expected, ntic):
    return sorted(actual) == sorted(expected) if ntic and isinstance(actual,list) else actual == expected

def shadow_params(value):
    require(isinstance(value,dict) and set(value)<= {'since','node_link','latest'},'음영구간 조회변수가 다릅니다.')
    result={'since':0,'latest':0}
    for k,v in value.items():
        require(isinstance(v,str),'조회변수 원문은 문자열이어야 합니다.')
        if k!='node_link':
            require(re.fullmatch(r'[+-]?[0-9]+',v) is not None,'정수 조회변수가 아닙니다.')
            v=int(v)
        result[k]=v
    return result

def weather_error(raw, key):
    expected={'test_no_data_error':'03','test_no_data_error_response':'03','test_invalid_request':'10','test_response_parameter_error':'10','test_missing_credential':'20','test_wrong_credential':'30','test_missing_path':'12','test_response_service_error':'12','test_response_server_error':'01'}[key]
    value=loads(raw);require(isinstance(value,dict) and isinstance(value.get('response'),dict),'기상 오류 response가 없습니다.')
    h=value['response'].get('header');require(isinstance(h,dict) and h.get('resultCode')==expected and isinstance(h.get('resultMsg'),str) and 0<len(h['resultMsg'])<=100,'기상 오류 결과코드·메시지가 다릅니다.')
    return value

def review(report_path, sut_path):
    report_path, sut_path = Path(report_path), Path(sut_path)
    report = read_json(report_path); run = report['runId']
    source_path, peer_path = report_path.parent / 'events.jsonl', sut_path / 'events.jsonl'
    source, peer = read_events(source_path), read_events(peer_path)
    link = correlate(report, source)
    provider, xml, smart, v3 = (link[k] for k in ('provider', 'xml', 'smart', 'v3'))
    weather=report['case'] in ('weatherServer2center_v1','centerClient2weather_v1')
    key_name=report.get('serviceKeyName','serviceKey')
    shadow=report['case'] in ('microServer2center_shadow_v1','centerClient2micro_shadow_v1')
    params=report.get('queryParameters',{})
    ntic=report['case'] in ('nticServer2center_v1','centerClient2ntic_v1')
    total = link['total']; expected = range(1, total + 1)
    responses, requests = link['responses'], link['requests']
    path = report['apiPath'] if weather else '/data' if shadow else report['apiPath'] if ntic else '/guide/imsOpenData.do' if xml else '/v1/adxc/smt-l-raws' if smart else '/v1/adxc/vds-l-raws'
    if weather:require(path in ('/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst','/1360000/VilageFcstInfoService_2.0/getUltraSrtFcst') and key_name in ('serviceKey','ServiceKey'),'기상 API 경로·인증변수명이 다릅니다.')
    if ntic:require(path in ('/vdsInfo','//vdsInfo'),'NTIC 경로가 다릅니다.')
    require(all('runId' not in e or e['runId'] == run for e in peer), '다른 실행의 대상 증적이 섞여 있습니다.')
    require(not any(e['event'] in ('error', 'peer_closed') for e in peer), '대상 증적에 통신 또는 처리 오류가 기록되어 있습니다.')
    other = index(selected(peer, 'response_sent' if provider else 'response_received'), 'exchange', expected, '대상 응답', string=provider)
    if provider:
        peer_requests = index(selected(peer, 'request'), 'exchange', expected, '대상 요청 수신', string=True)
    else:
        processed = index(selected(peer, 'application_processed'), 'exchange', expected, '대상 처리')
        stored = index(read_json(sut_path / 'processed.json'), 'exchange', expected, '대상 처리 저장')
        if v3:
            sent = index(selected(peer, 'request_sent'), 'requestNumber', expected, '대상 요청 송신')
            index(list(other.values()), 'requestNumber', expected, '응답의 대상 요청 번호')
            settings = read_json(sut_path / 'requester-config.json')
            listening = selected(source, 'listening')
            require(len(listening) == 1 and settings['requestMode'] == 'single' and settings['credentialConfigured'] is (not shadow), '대상의 단일 요청·접속 설정 증거가 부족합니다.')
            count(listening[0]['port'], urlsplit(settings['baseUrl']).port, '대상에 저장된 접점 포트')
            require(settings['path'] == path and query_names_match(settings['queryNames'], ([*params,key_name] if weather else list(settings['queryParameters']) if shadow else ['apiKey','getType'] if ntic else ['key'] if xml else []), ntic or shadow or weather), '대상에 저장된 요청 경로·변수가 다릅니다.')

    if weather and not provider:require(settings['queryParameters']==params and settings['serviceKeyName']==key_name,'기상 요청 설정값이 다릅니다.')
    if shadow and not provider:require(shadow_params(settings['queryParameters'])==shadow_params(params),'설정한 조회변수와 대상 요청 설정이 다릅니다.')

    if v3 and provider:
        preparation = read_json(sut_path / 'preparation.json')
        prepared = (sut_path / 'source-data.body').read_bytes()
        require(hashlib.sha256(prepared).hexdigest() == preparation['sourceSha256'], '대상 준비자료 원문과 해시가 다릅니다.')
        source_rows = rows(prepared, xml, ntic, weather)
        count(preparation['recordCount'], len(source_rows), '대상 준비자료')
        require(preparation['dataState'] == ('available' if source_rows else 'absent') and preparation['requestMode'] == 'single' and preparation['path'] == path, '대상 준비자료 상태·요청 모드·경로가 다릅니다.')

    prepared_rows = {}
    if v3:
        for item in report['items']:
            key = item['test']; pre = link['preconditions'][key]
            require(pre['requestMode'] == 'single' and pre['path'] == path and pre['owner'] == ('tester_reference' if provider else 'test_system'), key + ': 시험 준비 조건이 다릅니다.')
            require(pre['sourceFile'] == 'prepared-' + key + '.body', key + ': 다른 시험의 준비자료입니다.')
            body = (report_path.parent / pre['sourceFile']).read_bytes()
            require(hashlib.sha256(body).hexdigest() == pre['sourceSha256'], key + ': 시험 준비자료 원문과 해시가 다릅니다.')
            prepared_rows[key] = rows(body, xml, ntic, weather)
            count(pre['recordCount'], len(prepared_rows[key]), key + ' 준비자료')
            require(pre['dataState'] == ('available' if prepared_rows[key] else 'absent'), key + ': 준비자료 상태가 다릅니다.')
            if provider:
                count(preparation['port'], urlsplit(pre['endpoint']).port, '대상 준비 접점 포트')
                if item['validation'] == 'absence-error':
                    require(pre['operatorConfirmed'] is True, '자료 부재 사전조건의 준비 확인이 없습니다.')

    lookup_numbers = {n for n, r in responses.items() if r['validation'] in ('normal', 'empty', 'absence-error')}
    # 204 is supplemental empty success, not the standard absence-error test.
    if v3 and provider:
        lookup_numbers |= {n for n, r in responses.items() if r['test'] == 'test_no_data' and r['status'] == 204}
    lookups = index(selected(peer if provider else source, 'data_lookup'), 'exchange', lookup_numbers, '자료 조회', string=provider) if v3 else {}
    item_exchanges = {item['test']: [] for item in report['items']}
    for n, response in responses.items():
        key, check, actual = response['test'], response['validation'], response['status']
        q, received = requests[n], other[n]
        require(received['runId'] == run, '응답 실행 ID가 다릅니다.')
        status(received['status'], actual)
        raw = (report_path.parent / f'response-{n}.body').read_bytes()
        digest = hashlib.sha256(raw).hexdigest()
        require(digest == response['bodySha256'] == received['bodySha256'] == hashlib.sha256((sut_path / f'response-{n}.body').read_bytes()).hexdigest(), key + ': 양측 수신·송신 원문 또는 해시가 다릅니다.')
        item_exchanges[key].append(n)
        if provider:
            target_request = peer_requests[n]
            require(target_request.get('runId') == run, '대상 요청 수신의 실행 ID가 없거나 다릅니다.')
            expected_path = path + ('/not-found' if key == 'test_missing_path' else '')
            query_names = (['key', 'key'] if xml else ['unsupported']) if key == 'test_invalid_request' else ([] if not xml or key == 'test_missing_credential' else ['key'])
            if weather:
                expected_params=dict(params)
                if key=='test_invalid_request':expected_params['nx']='invalid'
                query_names=[*expected_params]+([] if key=='test_missing_credential' else [key_name])
                require(q['queryParameters']==target_request['queryParameters']==expected_params,'기상 요청변수 원문과 설정이 다릅니다.')
            if shadow:
                expected_params=dict(params)
                if key=='test_invalid_request':expected_params['latest']='501'
                query_names=list(expected_params)
                require(q['queryParameters']==target_request['queryParameters']==expected_params,'조회변수 실제 전송값이 다릅니다.')
            if ntic:query_names=['getType'] if key=='test_missing_credential' else ['apiKey','getType']
            if ntic:require(target_request['getType']==('unsupported' if key=='test_invalid_request' else 'json'),'NTIC 조회 형식 자극이 다릅니다.')
            for request in (q, target_request):
                require(request['method'] == 'GET' and request['path'] == expected_path, key + ': 실제 요청 방법·경로가 다릅니다.')
            count(q['queryCount'], len(query_names), key + ' 요청변수')
            count(target_request['bodyBytes'], 0, '대상 수신 요청 본문')
            require(query_names_match(target_request['queryNames'], query_names, ntic or shadow or weather) and target_request['credentialPresent'] is (not shadow and key != 'test_missing_credential'), key + ': 요청변수·인증정보 유무가 다릅니다.')
            if v3 and n in lookups:
                lookup = lookups[n]
                require(lookup['runId'] == run and lookup['routeMatched'] is True and lookup['path'] == path, '같은 유효 경로의 조회 증거가 없습니다.')
                require(lookup['sourceSha256'] == preparation['sourceSha256'], '조회한 자료와 준비자료의 해시가 다릅니다.')
                count(lookup['recordCount'], len(source_rows), '대상 조회자료')
                if check == 'absence-error':
                    require(not source_rows and (weather_error(raw,key)['response']['header']['resultCode']=='03' if weather else actual>=400), '대상 자료가 없는 상태의 오류응답이 아닙니다.')
                elif check == 'normal':
                    require(bool(source_rows) and same_rows(rows(raw, xml, ntic, weather), source_rows), '대상이 반환한 자료와 준비자료의 값·자료형·건수가 다릅니다.')
                elif actual == 204:
                    require(not source_rows and not raw, 'HTTP 204의 자료 없음·빈 본문 증거가 다릅니다.')
                else:
                    require(not source_rows and not rows(raw, xml, ntic, weather), '빈 정상응답에 자료가 있습니다.')
            if weather and check in ('weather-error','absence-error'):weather_error(raw,key)
            if check=='ntic-error':
                error=loads(raw);expected_code={'test_invalid_request':'4002','test_missing_credential':'4005','test_wrong_credential':'4005','test_missing_path':'4004'}[key]
                require(isinstance(error,dict) and error.get('resultCode')==expected_code and isinstance(error.get('resultMsg'),str) and error['resultMsg'],'NTIC 업무 오류 코드/메시지가 다릅니다.')
            continue

        process, saved = processed[n], stored[n]
        action = 'error-schema' if check == 'absence-error' and not xml and not smart and not ntic and not shadow and not weather and actual == 400 else 'error' if check == 'absence-error' else check
        for record in (process, saved):
            require(record['runId'] == run and record['bodySha256'] == digest, '처리 증거의 실행 ID 또는 원문 해시가 다릅니다.')
            status(record['status'], actual)
            require(record['action'] == action, key + ': 대상 처리 동작이 기대와 다릅니다.')
        require(integer(received['monotonicUs'], '대상 수신 시각') <= integer(process['monotonicUs'], '대상 처리 시각'), '대상 처리 시각이 수신보다 빠릅니다.')
        if v3:
            request_number = integer(received['requestNumber'], '대상 요청 번호', 1)
            sent_request = sent[request_number]
            count(process['requestNumber'], request_number, '처리 요청 번호'); count(saved['requestNumber'], request_number, '저장 요청 번호')
            require(integer(sent_request['monotonicUs'], '대상 송신 시각') <= received['monotonicUs'], '대상 응답 수신이 요청 송신보다 빠릅니다.')
            for request in (sent_request, q):
                require(request['method'] == 'GET' and request['path'] == path, '대상의 유효 요청 송신·수신 증거가 다릅니다.')
                count(request['bodyBytes'], 0, '요청 본문')
            require(q['accepted'] is True and sent_request['credentialPresent'] is (not shadow) and query_names_match(sent_request['queryNames'], ([*params,key_name] if weather else list(sent_request['queryParameters']) if shadow else ['apiKey','getType'] if ntic else ['key'] if xml else []), ntic or shadow or weather), '요청 유효성·인증·요청변수 증거가 다릅니다.')
            count(q['queryCount'], len(params)+1 if weather else len(sent_request['queryParameters']) if shadow else 2 if ntic else 1 if xml else 0, '수신 요청변수')
            if weather:require(q['queryParameters']==sent_request['queryParameters']==params,'기상 실제 요청변수 값이 다릅니다.')
            if shadow:require(q['queryParameters']==sent_request['queryParameters'] and shadow_params(q['queryParameters'])==shadow_params(params),'실제 조회변수 값과 설정이 다릅니다.')
            require((report_path.parent / f'request-{n}.body').read_bytes() == b'', '수신 요청 원문에 예상하지 않은 본문이 있습니다.')
            if check not in ('normal', 'empty'):
                errors = process.get('errorItems')
                require(isinstance(errors, list) and bool(errors) and same_value(errors, saved.get('errorItems')), '미처리 정보의 오류항목 로그가 없거나 저장 기록과 다릅니다.')
                for error in errors:
                    require(error['field'] in ('response.status', 'response.body') and isinstance(error['reason'], str) and bool(error['reason']), '오류항목의 필드·사유가 올바르지 않습니다.')
                    status(error['actualStatus'], actual)
            if n in lookups:
                lookup, pre = lookups[n], link['preconditions'][key]
                require(lookup['test'] == key and lookup['path'] == path and lookup['sourceSha256'] == pre['sourceSha256'] and lookup['validation'] == check, key + ': 다른 항목의 조회 증거입니다.')
                count(lookup['iteration'], q['iteration'], '조회 회차'); status(lookup['expectedStatus'], actual)
                require(q['monotonicUs'] <= lookup['monotonicUs'] <= response['monotonicUs'], '조회 시각이 요청·응답 범위를 벗어났습니다.')
                count(lookup['recordCount'], len(prepared_rows[key]), '시험기 조회자료')
                if check == 'absence-error':
                    require(not prepared_rows[key] and (weather_error(raw,key)['response']['header']['resultCode']=='03' if weather else actual>=400), '자료 부재 조건의 오류응답이 아닙니다.')
        if check in ('normal', 'empty'):
            decoded = rows(raw, xml, ntic, weather)
            require(same_rows(process['records'], decoded) and same_rows(saved['records'], decoded), key + ': 수신·처리·저장 자료의 값·자료형·건수가 다릅니다.')
            require(bool(decoded) == (check == 'normal'), key + ': 정상/빈 자료 조건이 다릅니다.')
            if v3:
                require(same_rows(decoded, prepared_rows[key]), key + ': 준비자료와 전송 원문의 값·자료형·건수가 다릅니다.')
        else:
            require(same_value(process['records'], []) and same_value(saved['records'], []), '오류응답이 정상 자료로 처리되었습니다.')
            if weather and check in ('weather-error','absence-error'):
                value=weather_error(raw,key);require(same_value(process['errorDetails'],value) and same_value(saved['errorDetails'],value),'기상 업무 오류의 처리/저장 자료가 다릅니다.')
            if action in ('error-schema','ntic-error','shadow-error'):
                value = loads(raw)
                require(isinstance(value, dict) and same_value(process['errorDetails'], value) and same_value(saved['errorDetails'], value), '오류 응답 본문과 대상의 오류 처리 내용이 다릅니다.')
                require(all(k not in value or isinstance(value[k], str) for k in ('code', 'message', 'time', 'path')), '오류 응답 필드의 자료형이 다릅니다.')
                if action=='ntic-error':require(value.get('resultCode')=={'test_response_400':'4002','test_response_404':'4004','test_response_500':'4009'}[key] and isinstance(value.get('resultMsg'),str) and value['resultMsg'],'NTIC 업무 오류 코드/메시지가 다릅니다.')
            if check == 'malformed':
                try:
                    rows(raw, xml, ntic, weather)
                except (EvidenceError, ValueError, ET.ParseError):
                    pass
                else:
                    raise EvidenceError('손상 응답 시험에 정상 형식의 자료가 사용되었습니다.')

    checked = []
    if v3:
        for item in report['items']:
            if item['test'] not in link['core']:
                continue
            evidence = ['시험 항목·요청·응답·회차·종료 기록 일치', '최소 10회 교환']
            if provider:
                evidence += ['대상 준비자료·유효 경로 조회·실제 응답 대조'] if item['validation'] in ('normal', 'absence-error') else ['잘못된 요청과 실제 오류응답 대조']
            else:
                evidence += ['대상 요청 송신·응답 수신·처리·저장 기록 연결', '값·자료형·건수 대조']
                if item['validation'] == 'absence-error':
                    evidence += ['시험기 자료 부재·오류응답·대상 오류항목 로그 확인']
            checked.append(dict(test=item['test'], basis=item['basis'], result='PASS', evidence=evidence))
    return dict(reviewProfile=REVIEW_PROFILE, legacyProfile=not v3, standardCriteria=checked,
                standardCoverage=dict(verified=[x['test'] for x in checked], notSelected=sorted(link['core'] - {x['test'] for x in checked}), complete=bool(checked) and link['core'] == {x['test'] for x in checked}) if v3 else None,
                itemExchanges=item_exchanges, runId=run, automaticVerdict=report['automaticVerdict'], developmentVerification='PASS',
                verifiedItems=len(report['items']), verifiedExchanges=total, reviewMethod='correlated_peer_evidence',
                reportSha256=hashlib.sha256(report_path.read_bytes()).hexdigest(), testerEventsSha256=hashlib.sha256(source_path.read_bytes()).hexdigest(), sutEvidenceSha256=hashlib.sha256(peer_path.read_bytes()).hexdigest())


if __name__ == '__main__':
    parser = argparse.ArgumentParser(); parser.add_argument('--report', type=Path, required=True); parser.add_argument('--sut', type=Path, required=True); parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        parser.error('Output already exists')
    try:
        result = review(args.report, args.sut)
    except (AssertionError, OSError, ValueError, KeyError, TypeError, ET.ParseError) as error:
        result = dict(reviewProfile=REVIEW_PROFILE, developmentVerification='FAIL', error=str(error) or '송수신·준비자료·대상 처리 증적의 연결 또는 값이 일치하지 않습니다.')
        args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf8')
        print(json.dumps(result, ensure_ascii=False)); raise SystemExit(1)
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf8')
    print(json.dumps(result, ensure_ascii=False))
