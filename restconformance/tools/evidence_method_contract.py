"""Bind engine selections and every observed exchange to the adopted profile."""
from evidence_values import require

CASES = {
    'weatherServer2center_v1': (False, False, False, 'test_request_weather'),
    'centerClient2weather_v1': (True, False, False, 'test_normal_weather'),
    'microServer2center_shadow_v1': (False, False, False, 'test_request_shadow'),
    'centerClient2micro_shadow_v1': (True, False, False, 'test_normal_shadow'),
    'nticServer2center_v1': (False, False, False, 'test_request_ntic'),
    'centerClient2ntic_v1': (True, False, False, 'test_normal_ntic'),
    'uticServer2center_v1': (False, True, False, 'test_normal_utic'),
    'centerClient2utic_v1': (True, True, False, 'test_provide_utic'),
    'microClient2center_v1': (True, False, False, 'test_normal_vds'),
    'centerServer2micro_v1': (False, False, False, 'test_request_vds'),
    'microClient2center_smart_v1': (True, False, True, 'test_normal_smart'),
    'centerServer2micro_smart_v1': (False, False, True, 'test_request_smart'),
}


def integer(value, label, minimum=0, string=False):
    if string and isinstance(value, str):
        require(value.isascii() and value.isdigit() and str(int(value)) == value, label + ': 정수 표기가 올바르지 않습니다.')
        value = int(value)
    require(type(value) is int and value >= minimum, label + ': 정수 값이 올바르지 않습니다.')
    return value


def index(records, key, expected, label, string=False):
    result = {}
    for record in records:
        n = integer(record[key], label, 1, string)
        require(n not in result, label + ': 중복 기록이 있습니다.')
        result[n] = record
    require(set(result) == set(expected), label + ': 누락되거나 예상하지 않은 번호가 있습니다.')
    return result


def by_test(events, name, keys):
    selected = [e for e in events if e['event'] == name]
    require([e['test'] for e in selected] == keys, name + ': 시험 항목 순서·누락·중복이 요약과 다릅니다.')
    return {e['test']: e for e in selected}


def catalog(case, v3):
    require(case in CASES, '알 수 없는 시험 시나리오입니다.')
    provider, xml, smart, normal = CASES[case]
    ntic=case in ('nticServer2center_v1','centerClient2ntic_v1')
    shadow=case in ('microServer2center_shadow_v1','centerClient2micro_shadow_v1')
    error = 'ntic-error' if ntic else 'status' if xml or smart else 'error-schema'
    values = {normal: {'normal': {200}}}
    if provider:
        values.update(test_invalid_request={error: {400, 422} if xml or smart or ntic else {400}},
                      test_missing_credential={'status': {401, 403}}, test_wrong_credential={'status': {401, 403}},
                      test_missing_path={'status': {404}}, test_no_data={'empty': {200}, 'status': {204}})
        if ntic:
            values['test_missing_credential']={'ntic-error':{401,403}}
            values['test_wrong_credential']={'ntic-error':{401,403}}
            values['test_missing_path']={'ntic-error':{404}}
        if not v3:
            values['test_no_data']['status'].add(404)
            # Earlier schema-2 VDS runs checked only HTTP status. Keep their
            # historical scope; never promote them to current standard coverage.
            if not xml and not smart:
                values['test_invalid_request']['status'] = {400}
        if v3:
            values['test_no_data_error'] = {'absence-error': {400, 404, 410, 422}}
    else:
        error = 'ntic-error' if ntic else 'error' if xml or smart else 'error-schema'
        values.update(test_response_400={error: {400}}, test_response_404={'error': {404}},
                      test_response_500={error: {500}}, test_empty_response={'empty': {200}},
                      test_malformed_response={'malformed': {200}})
        if ntic:values['test_response_404']={'ntic-error':{404}}
        if not v3 and not xml and not smart and not ntic:
            values['test_response_400']['error'] = {400}
            values['test_response_500']['error'] = {500}
        if v3:
            values['test_no_data_error_response'] = {'absence-error': {400, 404, 410, 422}}
    if shadow:
        if provider:
            values.pop('test_missing_credential');values.pop('test_wrong_credential')
            values['test_invalid_request']={'shadow-error':{422}}
        else:
            values.pop('test_response_400');values['test_response_422']={'shadow-error':{422}}
            values['test_response_500']={'error':{500}}
    if case in ('weatherServer2center_v1','centerClient2weather_v1'):
        if provider:
            values={normal:{'normal':{200}},'test_invalid_request':{'weather-error':{200,400,422}},'test_no_data_error':{'absence-error':{200,400,404,410,422}},'test_missing_credential':{'weather-error':{200,401,403}},'test_wrong_credential':{'weather-error':{200,401,403}},'test_missing_path':{'weather-error':{200,404}},'test_no_data':{'empty':{200},'status':{204}}}
        else:
            values={normal:{'normal':{200}},'test_no_data_error_response':{'absence-error':{200,400,404,410,422}},'test_response_parameter_error':{'weather-error':{200,400,422}},'test_response_service_error':{'weather-error':{200,404}},'test_response_server_error':{'weather-error':{200,500}},'test_empty_response':{'empty':{200}},'test_malformed_response':{'malformed':{200}}}
    return values


def correlate(report, source):
    version = integer(report['schemaVersion'], '결과 schema', 2)
    require(version in (2, 3, 4), '지원하지 않는 결과 schema입니다.')
    v3 = version >= 3
    automatic_scope = version == 4
    if automatic_scope:
        require(report.get('assessmentProfile') == 'REST-AUTO-001' and report.get('assessmentScope') == 'ENGINE_OBSERVABLE', '자동 검증 범위가 올바르지 않습니다.')
    case = report['case']; rules = catalog(case, v3)
    provider, xml, smart, normal = CASES[case]
    if v3:
        require(report['sutRole'] == ('provider' if provider else 'requester'), '시나리오와 시험 대상 역할이 다릅니다.')
        require(report['methodProfile'] == 'REST-EVIDENCE-002', '시험방법 profile이 다릅니다.')
    else:
        require('methodProfile' not in report and 'sutRole' not in report and
                not any(e['event'] in ('precondition', 'data_lookup') for e in source), '새 형식의 증적을 구형 결과로 검토할 수 없습니다.')
    require(report['profile'] in ({'WEATHER-STANDARD-001'} if case in ('weatherServer2center_v1','centerClient2weather_v1') else {'SHADOW-STANDARD-001'} if case in ('microServer2center_shadow_v1','centerClient2micro_shadow_v1') else {'NTIC-STANDARD-001'} if case in ('nticServer2center_v1','centerClient2ntic_v1') else {'SMART-STANDARD-001'} if smart else {'REST-PROFILE-001', 'REST-DATA-003'}), '시나리오와 데이터 검사 profile이 다릅니다.')
    count = integer(report['requestedRepetitions'], '반복수', 10)
    require(count <= 3600, '엔진이 지원하는 반복수 범위를 벗어났습니다.')
    items = report['items']; require(isinstance(items, list) and 0 < len(items) <= len(rules), '선택 항목 목록이 올바르지 않습니다.')
    keys = [item['test'] for item in items]
    require(len(set(keys)) == len(keys), '선택 항목이 중복되었습니다.')
    core = {normal, 'test_invalid_request', 'test_no_data_error'} if provider else {normal, 'test_no_data_error_response'}
    pending = False
    for item in items:
        key = item['test']; check = item['validation']; status = integer(item['expectedStatus'], key + ' 기대 상태', 100)
        require(key in rules and check in rules[key] and status in rules[key][check], key + ': 시험명·검사 방식·기대 응답의 조합이 잘못됐습니다.')
        expected = 'SUCCESS' if automatic_scope else 'EVIDENCE_PENDING' if not provider or check == 'absence-error' else 'SUCCESS'
        require(item['verdict'] == expected and integer(item['completedExchanges'], key + ' 완료 횟수') == count, key + ': 실패·중지·미실행 또는 반복 횟수 부족입니다.')
        pending |= expected == 'EVIDENCE_PENDING'
        if v3:
            require(item['classification'] == ('standard_requirement' if key in core else 'supplementary') and isinstance(item['basis'], str) and item['basis'], key + ': 시험 분류·근거가 올바르지 않습니다.')
        else:
            require('classification' not in item and 'basis' not in item, '구형 결과에 새 시험 분류가 섞여 있습니다.')
    require(report['automaticVerdict'] == ('EVIDENCE_PENDING' if pending else 'SUCCESS'), '전체 판정과 세부 항목 판정이 다르거나 실패·중지 상태입니다.')
    total = len(items) * count
    require(integer(report['completedExchanges'], '전체 완료 횟수') == total, '전체 교환 횟수가 선택 항목과 다릅니다.')
    run = report['runId']; require(isinstance(run, str) and run, '실행 ID가 없습니다.')
    require(all(e.get('runId') == run for e in source), '다른 실행의 시험기 증적이 섞여 있습니다.')
    times = [integer(e['monotonicUs'], '시험기 시각') for e in source]
    require(times == sorted(times), '시험기 이벤트 시각 순서가 잘못됐습니다.')
    allowed = {'listening', 'precondition', 'item_start', 'request', 'data_lookup', 'response' if provider else 'response_sent', 'item_result', 'result'}
    require(all(e['event'] in allowed for e in source), '시험기 증적에 예상하지 않은 처리·거부·오류 이벤트가 있습니다.')
    starts = by_test(source, 'item_start', keys); finishes = by_test(source, 'item_result', keys)
    pre = by_test(source, 'precondition', keys) if v3 else {}
    finals = [e for e in source if e['event'] == 'result']
    require(len(finals) == 1 and source[-1] is finals[0] and finals[0]['verdict'] == report['automaticVerdict'], '전체 종료 기록이 없거나 판정이 다릅니다.')
    all_numbers = range(1, total + 1)
    requests = index([e for e in source if e['event'] == 'request'], 'exchange', all_numbers, '시험기 요청')
    responses = index([e for e in source if e['event'] == ('response' if provider else 'response_sent')], 'exchange', all_numbers, '시험기 응답')
    positions = {id(e): i for i, e in enumerate(source)}
    previous_finish = -1
    for order, item in enumerate(items):
        key = item['test']; start = starts[key]; finish = finishes[key]
        require(previous_finish < positions[id(start)] < positions[id(finish)], key + ': 시작·종료 순서가 다릅니다.')
        previous_finish = positions[id(finish)]
        require(start['validation'] == item['validation'] and integer(start['expectedStatus'], '시작 응답 코드') == item['expectedStatus'] and start['profile'] == report['profile'], key + ': 시작 조건과 결과 요약이 다릅니다.')
        require(finish['verdict'] == item['verdict'] and integer(finish['completedExchanges'], '종료 횟수') == count, key + ': 종료 기록과 결과 요약이 다릅니다.')
        if v3:
            require(positions[id(pre[key])] < positions[id(start)] and pre[key]['basis'] == item['basis'], key + ': 사전조건과 근거가 연결되지 않습니다.')
        previous_response = positions[id(start)]
        for iteration in range(1, count + 1):
            n = order * count + iteration
            q, r = requests[n], responses[n]
            for event in (q, r):
                require(event['test'] == key and integer(event['iteration'], '회차', 1) == iteration and event['validation'] == item['validation'] and integer(event['expectedStatus'], '교환 기대 코드') == item['expectedStatus'], key + ': 다른 시험·회차·조건의 교환 증적입니다.')
            require(integer(r['status'], '실제 응답 코드') == item['expectedStatus'], key + ': 실제 응답 코드가 다릅니다.')
            require(previous_response < positions[id(q)] < positions[id(r)] < positions[id(finish)], key + ': 요청·응답 순서가 올바르지 않습니다.')
            previous_response = positions[id(r)]
    return dict(provider=provider, xml=xml, smart=smart, v3=v3, core=core, total=total,
                requests=requests, responses=responses, preconditions=pre)
