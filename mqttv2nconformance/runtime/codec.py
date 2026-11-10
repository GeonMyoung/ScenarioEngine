import json
from pathlib import Path
import subprocess
import tempfile
from container import MAX_PAYLOAD
from failures import Failure

ERRORS = {
    'UPER_CONSTRAINT': 'ASN.1 필드 값이 허용 범위를 벗어났습니다.',
    'UPER_LENGTH': 'UPER 메시지 길이가 허용 범위를 벗어났습니다.',
    'UPER_TRUNCATED': 'UPER 메시지가 잘려 필수 데이터를 모두 읽을 수 없습니다.',
    'UPER_TRAILING_DATA': 'UPER 메시지 뒤에 불필요한 데이터가 있습니다.',
    'UPER_NONZERO_PADDING': 'UPER 마지막 바이트의 패딩 비트가 0이 아닙니다.',
    'UPER_DECODE_OR_CONSTRAINT': 'UPER 구조 또는 ASN.1 필드·값 범위 검사에 실패했습니다.',
    'UPER_NATIVE_REJECTED': 'UPER 검사 중 코덱 오류가 발생하여 메시지를 거부했습니다.',
    'MESSAGE_ID_MISMATCH': 'MessageFrame의 메시지 종류가 시험 항목과 다릅니다.',
    'UNSUPPORTED_MESSAGE': '현재 시험 범위에서 지원하지 않는 메시지입니다.',
    'JSON_CONVERSION': '디코딩한 메시지를 결과 표시 자료로 변환하지 못했습니다.',
}


class Codec:
    def __init__(self,executable):
        self.executable=Path(executable)
        if not self.executable.is_file():raise ValueError('UPER 검사 실행 파일을 찾을 수 없습니다.')

    def call(self,args):
        with tempfile.TemporaryDirectory(prefix='g4-mqtt-result-') as d:
            output=Path(d)/'result.json'
            try:
                p=subprocess.run([str(self.executable),*args,str(output)],capture_output=True,timeout=15,
                                 creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0))
            except subprocess.TimeoutExpired:
                raise Failure('CODEC_TIMEOUT','메시지 검사 도구가 15초 안에 응답하지 않았습니다.',category='시험 도구 확인 필요',checks=['수신 원문과 코덱 진단 확인','대상 메시지 부적합 여부는 판정하지 못함']) from None
            try:r=json.loads(output.read_text(encoding='utf-8'))
            except (OSError,ValueError,UnicodeError):raise ValueError('UPER 검사 도구의 응답 형식이 올바르지 않습니다.')
            if p.returncode or not r.get('valid'):
                code=r.get('code','UPER_DECODE_OR_CONSTRAINT')
                stage=r.get('stage','MessageFrame/value')
                field=r.get('field') or stage;actual=r.get('actual');expected=r.get('expected') or ''
                finding=f'{ERRORS.get(code,"UPER 검사에 실패했습니다.")} 검사 위치: {field} [{code}]'
                if actual is not None:finding+=f' 실제값: {actual}.'
                elif code in ('UPER_TRUNCATED','UPER_DECODE_OR_CONSTRAINT'):finding+=' 해당 필드의 실제값은 끝까지 읽지 못했습니다.'
                if expected:finding+=' 허용 범위: '+expected+'.'
                category='시험 도구 확인 필요' if code in ('JSON_CONVERSION','UPER_NATIVE_REJECTED') else '수신 데이터 부적합'
                raise Failure(code,finding,category=category,criterion=expected or '채택한 ASN.1 스키마와 완전한 UPER 인코딩',
                    observed=dict(stage=stage,field=field,actual=actual,expected=expected or None,bit_offset=r.get('bitOffset')),
                    checks=['동일 원문과 송신 측 인코딩·스키마 버전 대조'])
            return r

    def sample(self,frame):
        return bytes.fromhex(self.call(['sample',str(frame)])['hex'])

    def bsm_sample(self,sequence,sec_mark,vehicle_id):
        return bytes.fromhex(self.call(['bsm-sample',str(sequence),str(sec_mark),vehicle_id])['hex'])

    def validate(self,frame,payload):
        if not 1<=len(payload)<=MAX_PAYLOAD:raise ValueError('UPER payload 크기 오류')
        with tempfile.TemporaryDirectory(prefix='g4-mqtt-uper-') as d:
            # Keep native command arguments small, and use a path independent of input text.
            p=Path(d)/'payload.hex';p.write_text(payload.hex(),encoding='ascii')
            return self.call(['decode',str(frame),str(p)])
