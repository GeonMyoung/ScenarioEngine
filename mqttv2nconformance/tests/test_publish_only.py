import csv,hashlib,json,sys,tempfile,types,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from catalog import parse_config,ui
from publish_only import CASE
from bsm_stimulus import expected_fields
from worker import Runner
from transport import Stopped

def config(**extra):return dict(host='localhost',client_id='bsm-test',topic_bsm='test/BSM',repetitions=3,test_bsm_normal=True,**extra)

class PublishOnly(unittest.TestCase):
    def test_receipt_is_not_required_and_old_path_is_not_opened(self):
        self.assertNotIn('observation_file',parse_config(CASE,config(observation_file='does-not-exist.jsonl')))
        fields=[]
        def visit(node):
            if isinstance(node,dict):
                if node.get('type')=='Input':fields.append(node['option']['name'])
                for v in node.values():visit(v)
            elif isinstance(node,list):
                for v in node:visit(v)
        visit(ui(CASE))
        self.assertEqual(set(fields),{'host','port','client_id','username','password','ca_file','topic_bsm','repetitions','test_bsm_normal'})
    def test_fixed_profile_cannot_be_overridden(self):
        self.assertEqual(parse_config(CASE,config())['container_version'],0)
        for key,value in [('qos',1),('publish_interval_seconds',.1),('container_version',1),('container_version',2),('byte_order','little')]:
            with self.subTest(key=key),self.assertRaises(ValueError):parse_config(CASE,config(**{key:value}))
    def execute(self,fault=False,stop=False):
        clock=types.SimpleNamespace(now=0)
        def sleep(seconds):clock.now+=round(seconds*1e9)
        fake_time=types.SimpleNamespace(monotonic_ns=lambda:clock.now,sleep=sleep)
        calls=[];stopped=[False]
        class Client:
            def check(self):
                if stopped[0]:raise Stopped('사용자가 시험을 중지했습니다.')
            def connect(self,*a):pass
            def close(self):pass
            def publish(self,topic,wire,**kwargs):
                calls.append(dict(time=clock.now,topic=topic,wire=wire,kwargs=kwargs));sleep(.2)
                if fault and len(calls)==2:raise ConnectionError('MQTT 연결 종료')
                if stop and len(calls)==2:stopped[0]=True
                return dict(completion='socket-send')
        with tempfile.TemporaryDirectory() as directory:
            runner=Runner(CASE,config(),directory,__file__,lambda:stopped[0])
            expected={}
            def sample(sequence,sec_mark,vehicle_id):
                expected.clear();expected.update(expected_fields(sequence,sec_mark,vehicle_id))
                return b'known-valid-test-body'+bytes([sequence])
            runner.codec=types.SimpleNamespace(bsm_sample=sample)
            runner.decoded=lambda *a:(None,dict(decoded={'coreData':dict(expected)},validation={'fixture':True}))
            runner.client=lambda:Client()
            with patch('publish_only.time',fake_time),patch('worker.Receipt',side_effect=AssertionError('receipt wait used')):
                result=runner.run()
            folder=Path(directory)
            records=[json.loads(s) for s in (folder/'bsm-transmit.jsonl').read_text(encoding='utf-8').splitlines()]
            with (folder/'bsm-transmit.csv').open(encoding='utf-8-sig',newline='') as f:csv_rows=list(csv.DictReader(f))
            self.assertEqual(len(records),len(csv_rows))
            for row,call in zip(records,calls):
                self.assertEqual(row['payload_hex'],call['wire'].hex())
                self.assertEqual(row['payload_sha256'],hashlib.sha256(call['wire']).hexdigest())
                self.assertEqual(call['kwargs']['qos'],0)
                self.assertEqual(call['wire'][1],0)
                self.assertEqual(row['schema_review'],'J2735_20240923_KSR1600_ADOPTED')
            self.assertFalse(result['sut_receive_confirmed'])
            self.assertEqual(result['final_verdict'],'PENDING_RECEIVER_LOG_REVIEW')
            events=[json.loads(s) for s in (folder/'events.jsonl').read_text(encoding='utf-8').splitlines()]
            self.assertEqual(sum(e.get('value')=='FINISH' for e in events),1)
            self.assertNotIn('COMPLETE',[e.get('value') for e in events])
            return result,records,calls
    def test_ack_processing_does_not_add_to_one_second_schedule(self):
        result,records,calls=self.execute()
        self.assertEqual([c['time'] for c in calls],[0,1_000_000_000,2_000_000_000])
        self.assertEqual(result['result'],'SUCCESS');self.assertEqual(result['publish_summary']['published'],3)
        self.assertTrue(all(r['status']=='PUBLISHED' for r in records))
        self.assertEqual([r['msgCnt'] for r in records],[0,1,2])
        self.assertEqual([r['speed'] for r in records],[500,501,502])
        self.assertEqual(len(set(r['vehicle_id'] for r in records)),1)
        self.assertEqual(len(set(r['decoded_json'] for r in records)),3)
    def test_partial_failure_is_retained(self):
        result,records,_=self.execute(fault=True)
        self.assertEqual(result['result'],'FAIL')
        self.assertEqual([r['status'] for r in records],['PUBLISHED','FAILED'])
        self.assertEqual(result['publish_summary']['published'],1)
    def test_stop_keeps_sent_records_without_success(self):
        result,records,_=self.execute(stop=True)
        self.assertEqual(result['result'],'STOPPED');self.assertEqual(len(records),2)

if __name__=='__main__':unittest.main()
