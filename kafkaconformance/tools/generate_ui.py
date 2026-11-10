"""Regenerate only case UI descriptors, preserving registrations and evidence."""
import json,sys
from pathlib import Path
root=Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'runtime'))
from catalog import CASES,ui
for case in CASES:
    (root/'registration'/(case+'.ui.json')).write_text(json.dumps(ui(case),ensure_ascii=False),encoding='utf8')
