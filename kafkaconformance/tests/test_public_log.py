"""Offline presentation tests. Synthetic strings never go to Kafka/platform."""
import base64,copy,json,sys,tempfile,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'runtime'));sys.path.insert(0,str(ROOT/'tools'))
from fields import validate,FieldFailure
from worker import Runner
from presentation import observation,write_report
from review_platform import assemble

class PublicLog(unittest.TestCase):
    def payload(self):return json.loads((ROOT/'fixtures/open.json').read_text(encoding='utf8'))
    def runner(self,root):
        r=Runner('ut2platform_kafka_v1',{},Path(root)/'evidence');r.stream='open';r.encoding='json';r.round=1;r.wanted=10;r.title='오픈데이터 정보교환';return r
    def finish(self,r):r.events.close();r.records.close();r.public.close()
    def test_real_rules_supply_expected_actual(self):
        rows=[];checks=validate('open',self.payload(),rows)
        self.assertGreater(len(checks),40);self.assertTrue(all('기준' in x and '실제' in x for x in rows))
        row=next(x for x in rows if '(objectID)' in x['항목']);self.assertIn('0~255',row['기준']);self.assertEqual(37,row['실제'])
    def test_failure_keeps_actual_type_and_expected_range(self):
        value=self.payload();value['objectData']['objectID']=True;rows=[]
        with self.assertRaises(FieldFailure):validate('open',value,rows)
        self.assertEqual(rows[-1]['결과'],'불일치');self.assertIs(rows[-1]['실제'],True);self.assertIn('정수',rows[-1]['기준'])
    def test_preparation_is_not_iteration_zero_or_sentinel(self):
        item=observation('초기 저장 offset 조회',dict(committed={0:-1001},runStartOffsets={0:0},policy='latest'))
        text=json.dumps(item,ensure_ascii=False);self.assertIn('이전 소비 기록 없음',text);self.assertNotIn('-1001',text)
    def test_internal_data_does_not_escape_and_json_stays_structured(self):
        with tempfile.TemporaryDirectory() as tmp:
            r=self.runner(tmp);value=self.payload();r.message('업무 value 발행 시도','교통안전인프라 플랫폼',raw=json.dumps(value).encode(),topic='agreed.open',partition=0);self.finish(r)
            public=json.loads((r.out/'user-events.jsonl').read_text(encoding='utf8'))
            self.assertEqual(public['data']['업무 데이터'],value)
            for key in ('runId','testName','sha256','valueBase64','monotonic','partition'):self.assertNotIn(key,json.dumps(public))
            local=json.loads((r.out/'records.jsonl').read_text());self.assertIn('sha256',local);self.assertEqual(base64.b64decode(local['valueBase64']),json.dumps(value).encode())
    def test_base64_masking_and_offline_long_unicode_roundtrip(self):
        with tempfile.TemporaryDirectory() as tmp:
            r=self.runner(tmp);r.encoding='base64-json';value=self.payload();value['extra']={'text':'로컬 표시 점검 가나다 😀 '*1200,'token':'DO_NOT_SHOW'}
            raw=base64.b64encode(json.dumps(value,ensure_ascii=False).encode());r.message('업무 value 발행 시도','자료 제공자',raw=raw,topic='offline-only');self.finish(r)
            events=[json.loads(l) for l in (r.out/'events.jsonl').read_text(encoding='utf8').splitlines()];shown=assemble([json.loads(e['data']) for e in events])
            self.assertEqual(1,len(shown));self.assertGreater(len(events),5)
            public=shown[0];self.assertEqual(public['업무 데이터']['extra']['text'],value['extra']['text']);self.assertEqual('***',public['업무 데이터']['extra']['token'])
            self.assertNotIn('DO_NOT_SHOW',json.dumps(public));decoded=json.loads(base64.b64decode(public['전송 원문 (Base64)']));self.assertEqual('***',decoded['extra']['token'])
    def test_malformed_payload_does_not_publish_credentials(self):
        with tempfile.TemporaryDirectory() as tmp:
            r=self.runner(tmp);r.message('업무 value 발행 시도','자료 제공자',raw=b'{"token":"DO_NOT_SHOW",bad}',topic='offline-only');self.finish(r)
            text=(r.out/'user-events.jsonl').read_text(encoding='utf8');self.assertNotIn('DO_NOT_SHOW',text);self.assertIn('진단 기록',text)
    def test_html_escapes_data_and_does_not_include_framework_fields(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'시험결과.html';write_report(p,{'판정':'성공'},[{'log':'자료 수신','sender':'대상','data':{'자료 구분':'송수신 데이터','내용':'<script>alert(1)</script>'}}]);text=p.read_text(encoding='utf8')
            self.assertNotIn('<script>',text);self.assertIn('&lt;script&gt;',text)
    def test_shipped_peer_has_no_synthetic_large_mode(self):
        text=(ROOT/'emulator/sut.py').read_text(encoding='utf8');self.assertNotIn("a.fault=='large'",text);self.assertNotIn('KAFKA_DISPLAY_MASK_SENTINEL',text);self.assertNotIn('시험자료 한글',text)

if __name__=='__main__':unittest.main()
