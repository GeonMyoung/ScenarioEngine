import json
import subprocess
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'runtime'))
from codec import Codec


class CodecErrors(unittest.TestCase):
    def test_native_reason_is_preserved(self):
        def native(args, **kwargs):
            Path(args[-1]).write_text(json.dumps(dict(valid=False, code='UPER_TRAILING_DATA',
                                                     stage='MessageFrame.value')), encoding='utf-8')
            return subprocess.CompletedProcess(args, 2)
        with patch('codec.subprocess.run', side_effect=native):
            with self.assertRaisesRegex(ValueError, r'불필요한 데이터.*MessageFrame.value.*UPER_TRAILING_DATA'):
                Codec(sys.executable).validate(20, b'\x00')

    def test_success_exit_cannot_override_invalid_verdict(self):
        def native(args, **kwargs):
            Path(args[-1]).write_text('{"valid": false}', encoding='utf-8')
            return subprocess.CompletedProcess(args, 0)
        with patch('codec.subprocess.run', side_effect=native):
            with self.assertRaises(ValueError):
                Codec(sys.executable).validate(20, b'\x00')


if __name__ == '__main__':
    unittest.main()
