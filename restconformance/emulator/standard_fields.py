"""Independent peer checks for Part 3 tables 4-16 and 4-22.

Validate decimal tokens before ordinary JSON decoding for evidence serialization.
This module does not implement the separate cross-peer evidence review.
"""
from datetime import datetime
from decimal import Decimal
import json
import re
import xml.etree.ElementTree as ET


def text(value, length, field, required=True):
    if not isinstance(value, str) or (required and not value) or len(value) > length:
        raise ValueError('Invalid string: ' + field)
    value.encode('utf8', errors='strict')


def number(value, precision, scale, field, xml=False):
    if xml:
        if not re.fullmatch(r'[+-]?[0-9]+(?:\.[0-9]+)?(?:[eE][+-]?[0-9]+)?', value):
            raise ValueError('Invalid decimal: ' + field)
    elif isinstance(value, bool) or not isinstance(value, (int, Decimal)):
        raise ValueError('Invalid number type: ' + field)
    n = Decimal(value)
    if not n.is_finite():
        raise ValueError('Nonfinite number: ' + field)
    if not n:
        return
    _, digits, exponent = n.as_tuple()
    digits = list(digits)
    while digits[-1] == 0:
        digits.pop()
        exponent += 1
    if max(0, -exponent) > scale or max(0, len(digits) + exponent) > precision - scale:
        raise ValueError('Invalid decimal precision: ' + field)


def timestamp(value, field, korean=False):
    if not isinstance(value, str):
        raise ValueError('Invalid date type: ' + field)
    compact = re.fullmatch(r'([0-9]{4})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})', value)
    local = re.fullmatch(r'([0-9]{4})년 ([0-9]{1,2})월 ([0-9]{1,2})일 ([0-9]{1,2})시 ([0-9]{1,2})분', value) if korean else None
    match = compact or local
    if not match:
        raise ValueError('Invalid date format: ' + field)
    datetime(*map(int, match.groups()))


def unique(pairs):
    result = {}
    for key, value in pairs:
        if key in result:
            raise ValueError('Duplicate key: ' + key)
        result[key] = value
    return result


def vds(body):
    raw = body.decode('utf8')
    rows = json.loads(raw, parse_float=Decimal, parse_int=Decimal, object_pairs_hook=unique)
    if not isinstance(rows, list):
        raise ValueError('Expected VDS array')
    required = ('collectDate', 'stnId', 'laneNo', 'vol', 'spd', 'occ', 'errCode', 'linkId', 'vdsId', 'stnLocation')
    for row in rows:
        if not isinstance(row, dict) or any(k not in row for k in required):
            raise ValueError('Missing VDS field')
        timestamp(row['collectDate'], 'collectDate')
        for key, size in [('stnId', 12), ('linkId', 12), ('vdsId', 12), ('stnLocation', 50)]:
            text(row[key], size, key)
        for key, precision, scale in [('laneNo', 1, 0), ('errCode', 1, 0), ('vol', 7, 0), ('spd', 5, 2), ('occ', 5, 2), ('volS', 7, 0), ('volM', 7, 0), ('volL', 7, 0)]:
            if key in row:
                number(row[key], precision, scale, key)
    return json.loads(raw)


def utic(body):
    raw = body.decode('utf8')
    if '<!DOCTYPE' in raw or '<!ENTITY' in raw:
        raise ValueError('Unsupported XML DTD/entity')
    tree = ET.fromstring(raw)
    if tree.tag != 'result' or (tree.text or '').strip():
        raise ValueError('Unexpected XML root/text')
    rows = []
    required = {'incidentId': 12, 'incidenteTypeCd': 10, 'incidenteSubTypeCd': 10,
                'addressJibun': 100, 'addressJibunCd': 20, 'addressNew': 100, 'linkId': 10,
                'incidenteTrafficCd': 10, 'incidenteGradeCd': 10, 'incidentTitle': 500,
                'incidentRegionCd': 2, 'startDate': 40, 'endDate': 40, 'lane': 10,
                'roadName': 50, 'controlType': 2, 'lineLinkId': 1000, 'important': 5, 'updateDate': 40}
    codes = {'incidenteTypeCd': {'1', '2', '3', '4', '5', '6'},
             'incidenteTrafficCd': {'A0501', 'A0502', 'A0503'},
             'incidenteGradeCd': {'A0401', 'A0402', 'A0403'},
             'controlType': {'0', '1', '2'}, 'important': {'00', '01'}}
    for record in tree:
        if record.tag != 'record' or (record.text or '').strip() or (record.tail or '').strip():
            raise ValueError('Unexpected record/text')
        row = {}
        for field in record:
            if field.tag in row or list(field) or '}' in field.tag or (field.tail or '').strip():
                raise ValueError('Invalid XML field')
            row[field.tag] = field.text or ''
        for key, size in required.items():
            text(row.get(key), size, key)
        for key in ('locationDataX', 'locationDataY'):
            if not row.get(key):
                raise ValueError('Missing coordinate: ' + key)
            number(row[key], 15, 9, key, xml=True)
        for key, size in [('sourceCode', 5), ('locationTypeCd', 5), ('locationData', 3000)]:
            if key in row:
                text(row[key], size, key, required=False)
        if row.get('locationTypeCd') and row['locationTypeCd'] not in {'C0101', 'C0102', 'C1013'}:
            raise ValueError('Invalid locationTypeCd')
        for key in ('startDate', 'endDate', 'updateDate'):
            timestamp(row[key], key, korean=True)
        for key, allowed in codes.items():
            if row[key] not in allowed:
                raise ValueError('Invalid code: ' + key)
        rows.append(row)
    return rows
