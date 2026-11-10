"""Run the independent counterpart with the installed MSI's codec/client runtime."""
import argparse
from pathlib import Path
import runpy
import sys

parser=argparse.ArgumentParser(add_help=False)
parser.add_argument('--engine-root',required=True)
args,remaining=parser.parse_known_args()
module=Path(args.engine_root).resolve()/'mqttv2nconformance/runtime'
sys.path.insert(0,str(module))
peer=Path(__file__).with_name('peer.py')
sys.argv=[str(peer),*remaining]
from transport import Stopped
try:
    runpy.run_path(str(peer),run_name='__main__')
except Stopped:
    # Cancellation during a pending MQTT acknowledgement is a normal owned stop.
    if '--stop' not in remaining or not Path(remaining[remaining.index('--stop')+1]).exists():
        raise
