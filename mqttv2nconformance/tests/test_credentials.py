import json,sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from catalog import parse_config,ui,BSM_PUBLISH_CASE
from credentials import protect,unprotect,connection

class Credentials(unittest.TestCase):
    def config(self,**fields):return dict(host='localhost',client_id='auth-test',topic_bsm='auth/bsm',test_bsm_normal=True,**fields)
    def test_direct_fields_used_for_connection(self):
        c=parse_config(BSM_PUBLISH_CASE,self.config(username='test-user',password='test-password'))
        self.assertEqual(connection(c),dict(username='test-user',password='test-password'))
    def test_anonymous_configuration_still_works(self):
        self.assertEqual(connection(parse_config(BSM_PUBLISH_CASE,self.config())),{})
    def test_password_requires_user_and_invalid_values_are_not_echoed(self):
        for fields in [dict(password='do-not-echo'),dict(username=1),dict(username='user',password={'secret':1})]:
            with self.assertRaises(ValueError) as caught:parse_config(BSM_PUBLISH_CASE,self.config(**fields))
            self.assertNotIn('do-not-echo',str(caught.exception))
    def test_protected_snapshot_round_trip(self):
        original=self.config(username='utf8-user',password='test-quote-"\\한글')
        encoded=protect(original)
        self.assertNotIn('password',encoded)
        self.assertNotIn(original['password'],json.dumps(encoded,ensure_ascii=False))
        self.assertEqual(unprotect(encoded),original)
        self.assertEqual(connection(parse_config(BSM_PUBLISH_CASE,encoded)),dict(username=original['username'],password=original['password']))
    def test_user_auth_file_is_rejected(self):
        with self.assertRaisesRegex(ValueError,'입력칸'):parse_config(BSM_PUBLISH_CASE,self.config(security_file='old-secret.json'))

if __name__=='__main__':unittest.main()
