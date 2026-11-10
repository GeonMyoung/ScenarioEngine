"""Regression for the deadline race observed in real launcher web run 329."""
import sys
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import Mock,patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
import worker
from transport import Stopped

class WaitDeadlineTests(unittest.TestCase):
    def test_clock_crosses_deadline_between_reads(self):
        sleeps=[]
        def sleep(seconds):
            if seconds<0:raise ValueError('sleep length must be non-negative')
            sleeps.append(seconds)
        clock=SimpleNamespace(monotonic=Mock(side_effect=[0,.9999999,1.0000001]),sleep=sleep)
        with patch.object(worker,'time',clock):worker.wait(lambda:False,1)
        self.assertTrue(all(0<=s<=.05 for s in sleeps))

    def test_cancellation_during_wait(self):
        clock=SimpleNamespace(monotonic=Mock(return_value=0),sleep=Mock())
        with patch.object(worker,'time',clock):
            with self.assertRaises(Stopped):worker.wait(lambda:True,1)
        clock.sleep.assert_not_called()

    def test_expired_wait_does_not_sleep(self):
        clock=SimpleNamespace(monotonic=Mock(side_effect=[0,1]),sleep=Mock())
        with patch.object(worker,'time',clock):worker.wait(lambda:False,0)
        clock.sleep.assert_not_called()

if __name__=='__main__':unittest.main()
