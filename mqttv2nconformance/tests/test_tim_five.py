import copy,json,sys,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from worker import Runner
from container import Container,encode
from tim_five import inspect

CODES=[7443,7444,7428,7427,7436]
def view(index):
    return dict(decoded=dict(dataFrames=[dict(frameType='roadSignage',msgId=dict(furtherInfoID=0xc01 if index<2 else 0xc02),
        startYear=2026,startTime=100,durationTime=30,priority=7,notUsed=0,notUsed1=0,notUsed2=0,notUsed3=0,
        content=dict(advisory=[dict(item=dict(itis=CODES[index]))]))]),
        tim_profile=dict(packetIdPresent=True,packetIdHex='0123456789abcdef00',frameCount=1,startYearPresent=True,regionCount=1),
        tim_regional=dict(summaryOmitted=0,values=[dict(kind='path',type=2,value='belt-1'),dict(kind='text',frameIndex=0,value='SPEED 30')]))

class FiveKinds(unittest.TestCase):
    def run_case(self,packets,bad_index=None,stop_after=None,stop_when_empty=False,**extra):
        clock=[0.0];received=[];closed=[]
        class Client:
            def connect(self,*args):pass
            def subscribe(self,*args):pass
            def check(self):pass
            def receive(self,*args,**kw):
                clock[0]+=.01
                if not packets:return None
                idx,nonce=packets.pop(0);received.append(idx)
                return dict(topic='tim',payload=encode(Container(0,0xff13,1,0,b'',0,82054,bytes([idx,nonce]))),retain=False)
            def record_message(self,m):pass
            def unsubscribe(self,*args):closed.append('unsubscribe')
            def close(self):closed.append('close')
        with tempfile.TemporaryDirectory() as folder:
            c=dict(host='localhost',client_id='five',topic_tim='tim',test_tim_normal=True,tim_timeout_seconds=1,**extra)
            runner=Runner('vehicleSubscriber2center_mqtt_v1',c,folder,__file__,lambda:(stop_after is not None and len(received)>=stop_after) or (stop_when_empty and not packets and clock[0]>2))
            def decode(key,wire):
                v=view(wire[16])
                if wire[16]==bad_index:v['tim_profile']['startYearPresent']=False
                return None,v
            runner.client=Client;runner.decoded=decode
            with patch('tim_five.time.monotonic',lambda:clock[0]):result=runner.run()
            data=json.loads((Path(folder)/'tim-summary.json').read_text(encoding='utf-8'))
            events=[json.loads(s) for s in (Path(folder)/'events.jsonl').read_text(encoding='utf-8').splitlines()]
            self.assertEqual(events[-1]['value'],'FINISH');self.assertEqual(sum(e.get('value')=='FINISH' for e in events),1)
            self.assertIn('unsubscribe',closed)
            return result,data,received
    def test_duplicates_do_not_finish_and_order_is_free(self):
        r,s,received=self.run_case([(0,0)]*5+[(4,0),(2,0),(1,0),(3,0),(0,9)])
        self.assertEqual(r['result'],'SUCCESS');self.assertEqual(len(received),9)
        self.assertEqual(s['duplicates'],4);self.assertEqual(s['missing'],[])
        self.assertEqual(s['content_review'],'RECORD_ONLY')
    def test_missing_kind_waits_and_is_named_when_stopped(self):
        r,s,_=self.run_case([(0,0),(1,0),(2,0),(3,0)],stop_when_empty=True)
        self.assertEqual(r['result'],'STOPPED');self.assertEqual(s['missing'],['shoulder'])
        results={x['test']:x for x in r['tests']}
        self.assertEqual(results['test_tim_shoulder']['result'],'STOPPED')
        self.assertTrue(all(x['result']=='SUCCESS' for k,x in results.items() if k!='test_tim_shoulder'))
    def test_each_kind_can_be_selected_alone(self):
        names=['limit_speed','maintain_speed','left_lane','right_lane','shoulder']
        for index,name in enumerate(names):
            with self.subTest(name=name):
                r,s,received=self.run_case([(i,0) for i in range(5)],**{'test_tim_'+name:True})
                self.assertEqual(r['result'],'SUCCESS');self.assertEqual(set(s['types']),{name})
                self.assertEqual([x['test'] for x in r['tests']],['test_tim_'+name])
    def test_bad_selected_kind_does_not_replace_other_results(self):
        r,s,_=self.run_case([(i,0) for i in range(5)],bad_index=2)
        results={x['test']:x['result'] for x in r['tests']}
        self.assertEqual(results['test_tim_left_lane'],'FAIL')
        self.assertTrue(all(v=='SUCCESS' for k,v in results.items() if k!='test_tim_left_lane'))
    def test_invalid_unselected_kind_is_ignored(self):
        r,s,_=self.run_case([(i,0) for i in range(5)],bad_index=0,test_tim_right_lane=True)
        self.assertEqual(r['result'],'SUCCESS');self.assertEqual(s['ignored'],3)
    def test_stop_keeps_already_confirmed_result(self):
        r,s,_=self.run_case([(i,0) for i in range(5)],stop_after=1)
        self.assertEqual(r['result'],'STOPPED')
        results={x['test']:x['result'] for x in r['tests']}
        self.assertEqual(results['test_tim_limit_speed'],'SUCCESS')
        self.assertTrue(all(v=='STOPPED' for k,v in results.items() if k!='test_tim_limit_speed'))
    def test_per_kind_count_rejects_identical_bodies(self):
        packets=[(i,0) for i in range(5)]*2+[(i,1) for i in range(5)]
        r,s,_=self.run_case(packets,tim_per_type=2)
        self.assertEqual(r['result'],'SUCCESS');self.assertEqual(s['duplicates'],5)
        self.assertTrue(all(v['validated']==2 for v in s['types'].values()))
    def test_required_fields_and_pairing(self):
        for field in ['packetIdPresent','startYearPresent']:
            v=view(0);v['tim_profile'][field]=False
            with self.assertRaisesRegex(ValueError,'TIM'):inspect(v)
        v=view(0);v['decoded']['dataFrames'][0]['msgId']['furtherInfoID']=0xc02
        with self.assertRaisesRegex(ValueError,'ITIS'):inspect(v)
    def test_content_format_is_recorded_without_affecting_kind(self):
        v=view(0);c=v['decoded']['dataFrames'][0]['content'];c['speedLimit']=c.pop('advisory')
        detail=inspect(v)
        self.assertEqual(detail['kind'],'limit_speed')
        self.assertEqual(detail['content_choice'],['speedLimit'])
        self.assertEqual(detail['content_review'],'RECORD_ONLY')

if __name__=='__main__':unittest.main()
