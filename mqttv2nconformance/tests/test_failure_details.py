import json,sys,subprocess,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from codec import Codec
from failures import Failure,describe

class FailureDetails(unittest.TestCase):
    def test_native_field_value_range_reaches_user_summary(self):
        def native(args,**kwargs):
            Path(args[-1]).write_text(json.dumps(dict(valid=False,code='UPER_CONSTRAINT',
                stage='MessageFrame.value',field='SPaT.timeStamp',actual=1048575,expected='0..527040')),encoding='utf-8')
            return subprocess.CompletedProcess(args,2)
        with patch('codec.subprocess.run',side_effect=native):
            with self.assertRaises(Failure) as caught:Codec(sys.executable).validate(19,b'fixture')
        failure=caught.exception
        self.assertIn('SPaT.timeStamp',failure.summary());self.assertIn('1048575',failure.summary())
        self.assertEqual(failure.observed['expected'],'0..527040')
    def test_truncation_does_not_invent_actual_value(self):
        def native(args,**kwargs):
            Path(args[-1]).write_text(json.dumps(dict(valid=False,code='UPER_TRUNCATED',
                stage='MessageFrame.value',field='SPaT.intersections[1].states',actual=None,bitOffset=42)),encoding='utf-8')
            return subprocess.CompletedProcess(args,2)
        with patch('codec.subprocess.run',side_effect=native):
            with self.assertRaises(Failure) as caught:Codec(sys.executable).validate(19,b'fixture')
        self.assertIsNone(caught.exception.observed['actual'])
        self.assertIn('읽지 못했습니다',caught.exception.summary())
    def test_connection_is_not_reported_as_payload_violation(self):
        result=describe(ConnectionError('MQTT 연결이 종료되었습니다 (code 7).'))
        self.assertEqual(result.category,'시험환경·통신 확인 필요')
        self.assertTrue(result.checks)
    def test_codec_timeout_is_a_tool_problem(self):
        with patch('codec.subprocess.run',side_effect=subprocess.TimeoutExpired('codec',15)):
            with self.assertRaises(Failure) as caught:Codec(sys.executable).validate(19,b'fixture')
        self.assertEqual(caught.exception.category,'시험 도구 확인 필요')
        self.assertNotIn('codec',caught.exception.summary())

if __name__=='__main__':unittest.main()
