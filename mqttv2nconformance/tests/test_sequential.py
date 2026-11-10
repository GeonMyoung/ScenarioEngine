"""Observable collection/validation boundaries for center Publisher tests."""
import json
import sys
import tempfile
import threading
import time
import unittest
from pathlib import Path

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from catalog import items,parse_config
from container import Container,encode
from worker import Runner
from test_tim_five import view as tim_view
from transport import Stopped

CASE='vehicleSubscriber2center_mqtt_v1'

def wire(key):
    from catalog import MESSAGES
    m=MESSAGES[key]
    return encode(Container(0,m['fid'],1,0,b'',1,m['psid'],b'fixture'))

class Client:
    def __init__(self,key,count,order,spacing=1,retain=False):
        self.key=key;self.count=count;self.order=order;self.spacing=spacing;self.retain=retain
        self.sent=0;self.empty_polls=0;self.released=threading.Event();self.raw=[]
    def connect(self,timeout):self.order.append(('connect',self.key))
    def subscribe(self,topics,timeout):self.order.append(('subscribe',self.key));self.topic=next(iter(topics));assert list(topics.values())==[0]
    def check(self):pass
    def receive(self,timeout,observe=True):
        if self.sent>=self.count:
            self.empty_polls+=1
            time.sleep(min(timeout,.001))
            return None
        self.sent+=1
        return dict(topic=self.topic,payload=wire(self.key),received=self.sent*self.spacing,
                    retain=self.retain,qos=0,packet_id=0)
    def record_message(self,m):self.raw.append(m)
    def unsubscribe(self,topic,timeout):self.order.append(('unsubscribe',self.key));self.released.set()
    def close(self):self.order.append(('close',self.key))

class Sequential(unittest.TestCase):
    def test_readiness_write_failure_still_stops_decoder(self):
        from unittest.mock import patch
        with patch('worker.write_readiness',side_effect=PermissionError('readiness sharing lock')):
            result,_,_,_=self.execute()
        self.assertEqual(result['result'],'FAIL')
        self.assertFalse(any(t.name=='mqtt-v2n-validator' and t.is_alive() for t in threading.enumerate()))

    def runner(self,d,**overrides):
        c=dict(host='localhost',client_id='test',topic_spat='s',topic_tlsm='l',topic_tim='t',
               repetitions=2,**{x[0]:True for x in items(CASE)})
        c.update(overrides)
        return Runner(CASE,c,d,__file__,lambda:False)
    def execute(self,**options):
        with tempfile.TemporaryDirectory() as d:
            runner=self.runner(d,**options.pop('config',{}));order=[];clients=[]
            keys=list(dict.fromkeys(x[1] for x in runner.c['selected']))
            def make():
                key=keys[len(clients)]
                count=5 if key=='tim' else runner.c['repetitions']
                cl=Client(key,options.get('count',count),order,options.get('spacing',1),options.get('retain',False))
                clients.append(cl);return cl
            runner.client=make
            def decoded(key,payload):
                cl=clients[-1]
                if options.get('slow') and key!='tim':self.assertTrue(cl.released.wait(2),'unsubscribe waited for decoder')
                order.append(('validate',key))
                if options.get('bad'):raise ValueError('UPER_TRAILING_DATA fixture')
                return (None,tim_view((cl.sent-1)%5)) if key=='tim' else (None,{'frame_id':19})
            runner.decoded=decoded
            if options.get('stop_after_empty'):
                runner.c['timeout_seconds']=.001
                runner.stop=lambda: bool(clients and clients[-1].empty_polls>=10)
            result=runner.run()
            events=[json.loads(l) for l in (Path(d)/'events.jsonl').read_text(encoding='utf-8').splitlines()]
            self.assertEqual(events[-1]['value'],'FINISH')
            self.assertEqual(sum(e.get('value')=='FINISH' for e in events),1)
            self.assertNotIn('COMPLETE',[e.get('value') for e in events])
            diagnostics=[json.loads(l) for l in (Path(d)/'diagnostic-events.jsonl').read_text(encoding='utf-8').splitlines()]
            return result,events,order,clients
    def test_unsubscribe_before_slow_decode_finishes_and_groups_in_order(self):
        result,events,order,clients=self.execute(slow=True)
        self.assertEqual(result['result'],'SUCCESS')
        self.assertEqual([c.key for c in clients],['spat','tlsm','tim'])
        self.assertEqual([c.sent for c in clients],[2,2,5])
        self.assertEqual([t['completed'] for t in result['tests']],[2,2,1,1,1,1,1])
        for a,b in [('spat','tlsm'),('tlsm','tim')]:
            self.assertLess(max(i for i,x in enumerate(order) if x==('validate',a)),order.index(('subscribe',b)))
        data=[json.loads(e['data']) for e in events if e['kind']=='info']
        evidence=[d for d in data if '송수신 원문 HEX' in d]
        self.assertEqual([d['메시지 순번'] for d in evidence],list(range(1,10)))
        self.assertEqual(evidence[0]['송수신 원문 HEX'],wire('spat').hex())

    def test_sample_count_with_legacy_period_settings(self):
        result,events,_,clients=self.execute(spacing=4,config=dict(period_samples=4,repetitions=3,test_spat_period=True))
        self.assertEqual(result['result'],'SUCCESS')
        self.assertEqual([c.sent for c in clients],[3,3,5])
        self.assertFalse(any('test_spat_period'==e['testName'] for e in events))

    def test_malformed_payload_not_success(self):
        result,events,_,clients=self.execute(bad=True)
        self.assertEqual(result['result'],'FAIL')
        self.assertEqual([t['result'] for t in result['tests']],['FAIL']+['NOT_RUN']*6)
        self.assertTrue(clients[0].released.is_set())
        payloads=[json.loads(e['data']) for e in events if e['kind']=='info']
        failed=next(d for d in payloads if d.get('메시지 결과')=='정합성 실패')
        self.assertEqual(failed['송수신 원문 HEX'],wire('spat').hex())
    def test_insufficient_samples_wait_until_stopped(self):
        result,_,_,clients=self.execute(config=dict(repetitions=3),count=2,stop_after_empty=True)
        self.assertEqual(result['result'],'STOPPED')
        self.assertEqual(result['tests'][0]['completed'],2)
        self.assertEqual(clients[0].empty_polls,10)
        self.assertTrue(clients[0].released.is_set())
    def test_retained_samples_excluded(self):
        result,_,_,clients=self.execute(count=10,stop_after_empty=True,retain=True)
        self.assertEqual(result['tests'][0]['completed'],0)
        self.assertEqual(len(clients[0].raw),10)
    def test_tim_only_no_period_test(self):
        result,events,_,clients=self.execute(config={x[0]:x[1]=='tim' for x in items(CASE)})
        self.assertEqual(result['result'],'SUCCESS')
        self.assertEqual([c.key for c in clients],['tim'])
        self.assertEqual(clients[0].sent,5)
        self.assertFalse(any('observed_seconds' in e.get('data','') for e in events))
    def test_period_only_supported(self):
        result,_,_,clients=self.execute(config=dict({x[0]:False for x in items(CASE)},test_tlsm_period=True))
        self.assertEqual(result['result'],'SUCCESS')
        self.assertEqual([c.key for c in clients],['tlsm'])
        self.assertEqual(len(result['tests']),1)

if __name__=='__main__':unittest.main()
