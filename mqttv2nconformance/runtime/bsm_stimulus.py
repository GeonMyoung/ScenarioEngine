"""Deterministic synthetic BSM values for per-message receiver-log comparison."""
PROFILE = 'BSM-VARIED-001'
SCHEMA_REVIEW = 'J2735_20240923_KSR1600_ADOPTED'
SCHEMA_NOTICE = 'J2735_20240923_KSR1600 스키마를 적용합니다. vert는 필수이며 C 필드명은 lon입니다.'


def expected_fields(sequence, sec_mark, vehicle_id):
    n = sequence - 1
    return dict(msgCnt=n % 128, id=vehicle_id.lower(), secMark=sec_mark,
                lat=370000000+n*100, lon=1270000000+n*100, elev=100+n % 100,
                transmission='forwardGears', speed=500+n % 100,
                heading=7200+n % 100, angle=n % 21)


def verify_fields(decoded, expected):
    core = decoded['coreData']
    actual = {key: core[key] for key in expected}
    text = actual['id'].lower()
    actual['id'] = (bytes(int(part,16) for part in text.split()) if text.startswith('0x') else bytes.fromhex(text)).hex()
    if actual != expected:
        raise ValueError('BSM 시험 자료 생성값과 인코딩 후 해석값이 일치하지 않습니다.')
