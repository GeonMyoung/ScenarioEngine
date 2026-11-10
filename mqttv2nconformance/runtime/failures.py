"""Observed failures and follow-up checks; never infer a remote internal cause."""

class Failure(ValueError):
    def __init__(self,code,finding,*,category='수신 데이터 부적합',criterion='',observed=None,checks=None):
        super().__init__(finding)
        self.code=code;self.finding=finding;self.category=category
        self.criterion=criterion;self.observed=observed or {};self.checks=checks or []
    def details(self,**context):
        return dict(kind='failure',code=self.code,classification=self.category,
            finding=self.finding,criterion=self.criterion,observed=self.observed,
            next_checks=self.checks,**context)
    def summary(self):
        text=f'[{self.category}] {self.finding}'
        if self.criterion:text+=' 기준: '+self.criterion+'.'
        if self.checks:text+=' 확인할 사항: '+' / '.join(self.checks)+'.'
        return text

def describe(error):
    if isinstance(error,Failure):return error
    reason=str(error)
    if isinstance(error,TimeoutError) or 'CONNACK' in reason or 'SUBACK' in reason or 'UNSUBACK' in reason:
        return Failure('MQTT_RESPONSE_TIMEOUT',reason,category='시험환경·통신 확인 필요',
            criterion='설정 시간 안에 해당 MQTT 응답 수신',
            checks=['Broker 주소·포트·접속 상태 확인','인증·구독 권한과 Broker 로그 확인','대상 내부 오류 여부는 이 로그만으로 확정할 수 없음'])
    if isinstance(error,ConnectionError) or reason.startswith('MQTT'):
        return Failure('MQTT_CONNECTION_ERROR',reason,category='시험환경·통신 확인 필요',
            checks=['Broker 접속·인증·TLS 설정 확인','네트워크 상태와 Broker 로그 확인'])
    return Failure('TEST_EXECUTION_ERROR',reason,category='시험 도구·설정 확인 필요',
        checks=['실행 환경과 상세 진단 확인','시험대상의 부적합으로 단정하지 않음'])
