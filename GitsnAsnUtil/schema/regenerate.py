"""Regenerate the adopted C codec with the recorded compatible compiler."""
import argparse
import hashlib
import json
import subprocess
import tempfile
from pathlib import Path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--compiler', required=True, type=Path)
    args = parser.parse_args()
    module = Path(__file__).resolve().parents[1]
    record = json.loads((module / 'schema/adoption.json').read_text(encoding='utf-8'))
    compiler = args.compiler.resolve()
    if hashlib.sha256(compiler.read_bytes()).hexdigest() != record['compilerSha256']:
        raise ValueError('Use the compatible compiler recorded in adoption.json.')
    with tempfile.TemporaryDirectory(prefix='gitsn-asn-') as directory:
        work = Path(directory)
        (work / 'GitsnAsn1.asn').write_bytes((module / 'GitsnAsn1.asn').read_bytes())
        subprocess.run([str(compiler), 'GitsnAsn1.asn'], cwd=work, check=True)
        for filename, destination in [('GitsnAsn1.c', 'src'), ('GitsnAsn1.h', 'include')]:
            generated = (work / filename).read_bytes()
            if not generated:
                raise ValueError('Compiler produced an empty file.')
            (module / destination / filename).write_bytes(generated)


if __name__ == '__main__':
    main()
