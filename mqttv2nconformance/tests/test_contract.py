import json,sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from container import Container,encode,decode,validate
from catalog import CASES,CENTER_SINGLE_CASES,MESSAGES,parse_config,topic,items,ui
from worker import Receipt,Events

class Contracts(unittest.TestCase):
    def config(self,case=None):
        case=case or next(iter(CASES))
        c=dict(host='localhost',client_id='g4-test',observation_file='live.jsonl')
        for k in CASES[case]['messages']:c['topic_'+k]='chosen/Case/ '+k;c['test_'+k+'_normal']=True
        return c

    def test_independent_wire_vector(self):
        c=Container(1,0xff10,1,0,b'',4,82050,b'\x00\x14')
        self.assertEqual(encode(c).hex(),'0401ff100100000400014082000000020014')
        self.assertEqual(decode(bytes.fromhex('0401ff100100000400014082000000020014')),c)

    def test_metadata_and_endianness(self):
        c=Container(2,0xff12,1,0x80,b'\x01\x02',247,82176,b'abcd')
        for order in ('big','little'):self.assertEqual(decode(encode(c,order),order),c)
        with self.assertRaises(ValueError):decode(encode(c,'little'),'big')

    def test_all_header_truncations_and_length(self):
        w=encode(Container(1,0xff10,1,0,b'abc',1,82050,b'test'))
        for n in range(len(w)):
            with self.subTest(n=n),self.assertRaises(ValueError):decode(w[:n])
        for invalid in (bytes([2])+w[1:],w+b'\0',w[:15]+b'\xff'+w[16:]):
            with self.assertRaises(ValueError):decode(invalid)

    def test_type_psid_and_message_id_are_independent(self):
        c=parse_config(next(iter(CASES)),self.config());m=MESSAGES['bsm']
        w=encode(Container(0,m['fid'],1,0,b'',251,m['psid'],b'x'))
        self.assertEqual(validate(w,m,c).message_id,251)
        for fid,psid,version,std in [(0xff00,m['psid'],0,1),(m['fid'],82055,0,1),(m['fid'],m['psid'],1,1),(m['fid'],m['psid'],0,2)]:
            with self.assertRaises(ValueError):validate(encode(Container(version,fid,std,0,b'',1,psid,b'x')),m,c)

    def test_all_roles_require_version_zero(self):
        for case,role in CASES.items():
            with self.subTest(case=case):
                c=parse_config(case,self.config(case))
                self.assertEqual(c['container_version'],0)
                for key in role['messages']:
                    m=MESSAGES[key]
                    validate(encode(Container(0,m['fid'],1,0,b'',1,m['psid'],b'x')),m,c)
                    with self.assertRaisesRegex(ValueError,'version'):
                        validate(encode(Container(1,m['fid'],1,0,b'',1,m['psid'],b'x')),m,c)
                with self.assertRaises(ValueError):parse_config(case,dict(self.config(case),container_version=1))
                fields=[f['option'] for div in ui(case)['configuration'] for group in div['components'] for f in group['components']]
                versions=[f for f in fields if f['name']=='container_version']
                self.assertTrue(not versions or versions[0]['value']=='0')
                if role.get('center_provider'):
                    fixed={'container_version','standard_type','byte_order'}
                    self.assertTrue(fixed.isdisjoint(f['name'] for f in fields))
                    self.assertEqual((c['container_version'],c['standard_type'],c['byte_order']),(0,1,'big'))
                    legacy=dict(self.config(case),container_version='0',standard_type='1',byte_order='big')
                    self.assertEqual(parse_config(case,legacy),c)
                    with self.assertRaisesRegex(ValueError,'big'):
                        parse_config(case,dict(legacy,byte_order='little'))

    def test_topic_exactness_and_no_implicit_default(self):
        self.assertEqual(topic(' A/BSM '),' A/BSM ')
        for bad in ('','   ','a/#','a/+','a\0b'):
            with self.assertRaises(ValueError):topic(bad)
        c=self.config();del c['topic_bsm']
        with self.assertRaises(ValueError):parse_config(next(iter(CASES)),c)

    def test_shared_topics_and_selection_boundaries(self):
        case='vehicleSubscriber2center_mqtt_v1';c=self.config(case)
        for k in CASES[case]['messages']:c['topic_'+k]='shared/信号'
        v=parse_config(case,c);self.assertEqual(len(v['selected']),7)
        self.assertEqual(sum(len(items(k)) for k in CASES),19)
        self.assertTrue(all(m['fid']>=0xff10 for m in MESSAGES.values()))
        self.assertEqual(MESSAGES['spat']['psid'],int('014087',16))
        c['test_tim_period']=True
        with self.assertRaises(ValueError):parse_config(case,c)

    def test_individual_scenarios_only_expose_their_message_conditions(self):
        removed={'qos','keepalive','timeout_seconds','period_samples','period_tolerance_seconds','tim_timeout_seconds'}
        for case,message in CENTER_SINGLE_CASES.items():
            with self.subTest(message=message):
                fields={f['option']['name'] for div in ui(case)['configuration'] for g in div['components'] for f in g['components']}
                self.assertEqual({name for name in fields if name.startswith('topic_')},{'topic_'+message})
                self.assertTrue(fields.isdisjoint(removed))
                self.assertEqual(fields & {'repetitions','tim_per_type'},{'tim_per_type'} if message=='tim' else {'repetitions'})
                self.assertEqual(len(items(case)),5 if message=='tim' else 1)
                self.assertTrue(all(item[1]==message for item in items(case)))

    def test_numbers_and_credentials(self):
        case=next(iter(CASES))
        for field,bad in [('repetitions',0),('repetitions',1.2),('qos',3),('port',0),('standard_type',2),('standard_type',3),('standard_type',4)]:
            c=self.config();c[field]=bad
            with self.assertRaises(ValueError):parse_config(case,c)
        c=self.config();c['password']='do-not-log'
        with self.assertRaises(ValueError):parse_config(case,c)

    def test_consumer_requires_observation(self):
        case='centerPublisher2vehicle_mqtt_v1';c=self.config(case);c.pop('observation_file')
        with self.assertRaises(ValueError):parse_config(case,c)

    def test_receipt_watermark_partial_and_truncation(self):
        with tempfile.TemporaryDirectory() as d:
            p=Path(d)/'receipt.jsonl';p.write_bytes(b'{"old":true}\n');r=Receipt(p)
            with p.open('ab') as f:f.write(b'{"new":')
            self.assertEqual(r.poll(),[])
            with p.open('ab') as f:f.write(b'true}\n')
            self.assertEqual(r.poll(),[{'new':True}]);self.assertEqual(r.poll(),[])
            p.write_bytes(b'')
            with self.assertRaises(ValueError):r.poll()

    def test_long_data_lossless_and_single_finish(self):
        with tempfile.TemporaryDirectory() as d:
            events=Events(d)
            raw='12345678'*2000
            data=dict(direction='수신',sequence=3,topic='topic',message='SPaT',message_result='정합성 확인',
                      payload_hex=raw,decoded=dict(description='한글 🌐'*1000))
            events.info('SPaT 3번 수신',data)
            events.state('MainScenario','FINISH')
            with self.assertRaises(RuntimeError):events.info('late')
            events.close()
            rows=[json.loads(l) for l in (Path(d)/'events.jsonl').read_text(encoding='utf-8').splitlines()]
            parts=[json.loads(x['data']) for x in rows if x['kind']=='info']
            self.assertGreater(len(parts),1)
            attachment=json.loads(''.join(p['value'] for p in parts))
            self.assertEqual(attachment['송수신 원문 HEX'],raw)
            self.assertEqual(attachment['메시지 순번'],3)
            self.assertEqual(attachment['ASN.1 해석 결과'],data['decoded'])
            self.assertEqual(sum(x.get('value')=='FINISH' for x in rows),1)

if __name__=='__main__':unittest.main()
