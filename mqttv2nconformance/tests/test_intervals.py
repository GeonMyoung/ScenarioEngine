import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from intervals import assess

class Intervals(unittest.TestCase):
    def test_maximum_gap_accepts_fast_and_boundary_rejects_late(self):
        a=assess([.0,.3,.5,1,1.1,1.10000000005,2.69],1,.1)
        self.assertEqual(a['outliers'],[dict(interval=7,seconds=2.69)])
        self.assertIsNone(a['lower_seconds'])
    def test_previous_symmetric_check_is_retained(self):
        self.assertEqual([x['interval'] for x in assess([.3,.5,1,1.3],1,.1,'periodic')['outliers']],[1,2,4])

if __name__=='__main__':unittest.main()
