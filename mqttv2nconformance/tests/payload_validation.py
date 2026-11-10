"""Real native codec regression checks; malformed inner lengths are rewrapped.

The fixtures use a root MessageFrame with a 16-bit prefix and one open type.
This test-only encoder supports unfragmented open types, not arbitrary J2735 data.
"""
import argparse
import hashlib
import json
import subprocess
import tempfile
from pathlib import Path


def unwrap(frame):
    assert frame[0] == 0
    length = frame[2]
    start = 3
    if length & 0x80:
        assert length & 0xc0 == 0x80
        length = ((length & 0x3f) << 8) | frame[3]
        start = 4
    assert start + length == len(frame)
    return frame[:2], frame[start:]


def wrap(prefix, body):
    n = len(body)
    assert n < 16384
    length = bytes([n]) if n < 128 else bytes([0x80 | (n >> 8), n & 255])
    return prefix + length + body


def replace_bits(body, offset, width, value):
    bits = list(''.join(f'{x:08b}' for x in body))
    bits[offset:offset + width] = f'{value:0{width}b}'
    return int(''.join(bits), 2).to_bytes(len(body), 'big')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--codec', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--baseline', action='store_true')
    parser.add_argument('--fixtures')
    parser.add_argument('--only-fixtures', action='store_true')
    args = parser.parse_args()
    codec = Path(args.codec).resolve()
    evidence = Path(args.output).resolve()
    evidence.parent.mkdir(parents=True, exist_ok=True)
    results = []
    with tempfile.TemporaryDirectory(prefix='g4-payload-check-') as directory:
        work = Path(directory)
        def call(command, frame, wire=None):
            params = [str(codec), command, str(frame)]
            if wire is not None:
                (work / 'wire.hex').write_text(wire.hex(), encoding='ascii')
                params.append(str(work / 'wire.hex'))
            destination = work / 'result.json'
            if destination.exists():
                destination.unlink()
            params.append(str(destination))
            try:
                proc = subprocess.run(params, capture_output=True, timeout=3 if args.baseline else 10,
                                      creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0))
            except subprocess.TimeoutExpired:
                if args.baseline:
                    return dict(valid=None, code='NATIVE_TIMEOUT', stage='timeout')
                raise
            # A crash or missing JSON must never count as correct rejection.
            if args.baseline and proc.returncode not in (0, 2):
                return dict(valid=None, code='NATIVE_CRASH', stage=f'exit:{proc.returncode}')
            assert proc.returncode in (0, 2), (frame, proc.returncode, proc.stderr[-500:])
            reply = json.loads(destination.read_text(encoding='utf-8'))
            assert reply['valid'] == (proc.returncode == 0)
            return reply

        def check(frame, name, wire, expected):
            reply = call('decode', frame, wire)
            results.append(dict(frame=frame, case=name, expected=expected,
                                valid=reply['valid'], code=reply.get('code'), stage=reply.get('stage'),
                                bytes=len(wire), sha256=hashlib.sha256(wire).hexdigest()))
            return reply

        for frame in (() if args.only_fixtures else (20, 19, 50, 31)):
            sample = call('sample', frame)
            assert sample['valid'], sample
            wire = bytes.fromhex(sample['hex'])
            prefix, body = unwrap(wire)
            normal = check(frame, 'normal', wire, True)
            for n in ([0, 1, len(wire)-1] if args.baseline else range(len(wire))):
                check(frame, f'outer-truncated-{n}', wire[:n], False)
            for suffix in (b'\x00', b'\xff', wire):
                check(frame, f'outer-trailing-{len(suffix)}-{suffix[0]:02x}', wire + suffix, False)
            for n in ([0, 1, len(body)-1] if args.baseline else range(len(body))):
                check(frame, f'value-truncated-{n}', wrap(prefix, body[:n]), False)
            for suffix in (b'\x00', b'\xff', body):
                check(frame, f'value-trailing-{len(suffix)}-{suffix[0]:02x}', wrap(prefix, body + suffix), False)
            check(frame, 'message-id-mismatch', wrap(bytes([0, 20 if frame != 20 else 19]), body), False)
            if not args.baseline:
                facts = normal['validation']
                assert facts['asn1Constraints'] and facts['exactLength'] and facts['zeroPadding']
                padding = len(body) * 8 - facts['messageBits']
                assert 0 <= padding <= 7
                for bit in range(padding):
                    malformed = body[:-1] + bytes([body[-1] | (1 << bit)])
                    check(frame, f'value-padding-bit-{bit}', wrap(prefix, malformed), False)
            if frame == 20:
                # ASN.1 root BSM: 3 presence bits, msgCnt(7), id(32), secMark(16),
                # lat(31), lon(32), elev(16), accuracy(32), transmission(3), speed(13).
                for name, offset, width, value, expected in (
                    ('msgCnt-127', 3, 7, 127, True),
                    ('latitude-min', 58, 31, 0, True),
                    ('latitude-max-sentinel', 58, 31, 1800000001, True),
                    ('latitude-outside-range', 58, 31, 2147483647, False),
                    ('speed-unavailable-8191', 172, 13, 8191, True),
                    ('heading-max-28800', 185, 15, 28800, True),
                    ('heading-outside-range', 185, 15, 28801, False),
                ):
                    check(frame, name, wrap(prefix, replace_bits(body, offset, width, value)), expected)
                check(frame, 'missing-coreData', wrap(prefix, b'\x00'), False)
            print(f'Checked MessageFrame {frame}: {len(results)} cases', flush=True)
        if args.fixtures:
            for fixture in json.loads(Path(args.fixtures).read_text(encoding='utf-8')):
                check(31, fixture['name'], bytes.fromhex(fixture['hex']), fixture['expected'])
        elif args.only_fixtures:
            raise ValueError('--only-fixtures requires --fixtures')
    failures = [r for r in results if r['expected'] != r['valid']]
    report = dict(codec=str(codec), codecSha256=hashlib.sha256(codec.read_bytes()).hexdigest(),
                  baseline=args.baseline, count=len(results), mismatches=len(failures), results=results)
    evidence.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(dict(cases=len(results), mismatches=len(failures), examples=failures[:8]), ensure_ascii=False))
    if not args.baseline:
        assert not failures, failures[:8]


if __name__ == '__main__':
    main()
