import json,sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from worker import Events
from public_logs import present

class PublicLogs(unittest.TestCase):
    def test_protocol_and_raw_data_are_preserved_only_in_diagnostics(self):
        with tempfile.TemporaryDirectory() as d:
            e=Events(d);e.info('CONNECT request',dict(packet='CONNECT',host='private-host'))
            e.info('수신 검증',dict(payload_hex='deadbeef',decoded=dict(raw='internal'),validated=1));e.close()
            visible=(Path(d)/'events.jsonl').read_text(encoding='utf-8');raw=(Path(d)/'diagnostic-events.jsonl').read_text(encoding='utf-8')
            self.assertNotIn('CONNECT',visible);self.assertNotIn('payload_hex',visible);self.assertNotIn('deadbeef',visible)
            self.assertIn('CONNECT',raw);self.assertIn('deadbeef',raw);self.assertIn('검증 건수',visible)
    def test_internal_exception_path_is_not_user_text(self):
        text,data=present('실패 C:\\private\\worker.py:3 WinError 5',{},{} )
        self.assertNotIn('private',text);self.assertIn('설정',text)
    def test_useful_failure_criterion_is_visible(self):
        text,data=present('종류 식별값이 다릅니다.',dict(kind='failure',criterion='ITIS=7443',observed=dict(expected=7443,actual=7444)),{})
        self.assertEqual(data['기대값'],7443);self.assertEqual(data['실제값'],7444)

if __name__=='__main__':unittest.main()
