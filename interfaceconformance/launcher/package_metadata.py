"""Record the public-log source and actual deliverable files at package time."""
import hashlib
from pathlib import Path

def finalize_manifest(output, manifest, protocol):
    root = Path(__file__).resolve().parents[2]
    output = Path(output)
    module = root / (protocol + 'conformance')
    sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
    files = lambda folder: sorted(p for p in folder.rglob('*') if p.is_file() and '__pycache__' not in p.parts and p.suffix != '.pyc')
    manifest['publicLogPolicy'] = 'ITR-011 / 2026-09-25'
    manifest['engineChanges'] = 'Common public log stages, evidence presentation and separate user report'
    manifest['runtimeSha256'] = {p.relative_to(output/'runtime').as_posix(): sha(p) for p in files(output/'runtime')}
    manifest['launcherSha256'] = sha(output/'시작하기.exe')
    manifest['launcherSourceSha256'] = {p.name: sha(p) for p in (module/'launcher').glob('*.cs')}
    manifest['commonSourceSha256'] = {p.relative_to(root).as_posix(): sha(p) for p in files(root/'interfaceconformance')}
    manifest['engineSourceSha256'] = {p.relative_to(root).as_posix(): sha(p) for folder in ['src','include','runtime'] for p in files(module/folder)}
    manifest['filesSha256'] = {p.relative_to(output).as_posix(): sha(p) for p in files(output) if p.name != 'bundle-manifest.json'}
    return manifest
