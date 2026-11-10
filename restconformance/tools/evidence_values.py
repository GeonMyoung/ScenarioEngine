"""Exact JSON evidence decoding and type-aware value comparison."""
from decimal import Decimal
import json
from pathlib import Path
import xml.etree.ElementTree as ET


class EvidenceError(AssertionError):
    """An explicit check; remains active under python -O."""


def require(condition, message):
    if not condition:
        raise EvidenceError(message)


def unique(pairs):
    result = {}
    for key, value in pairs:
        require(key not in result, '증적 JSON에 중복 필드가 있습니다: ' + key)
        result[key] = value
    return result


def invalid_constant(value):
    raise EvidenceError('증적 JSON에 유효하지 않은 숫자가 있습니다: ' + value)


def loads(data):
    if isinstance(data, bytes):
        data = data.decode('utf-8-sig')
    return json.loads(data, parse_float=Decimal, object_pairs_hook=unique, parse_constant=invalid_constant)


def read_json(path):
    return loads(Path(path).read_bytes())


def read_events(path):
    result = [loads(line) for line in Path(path).read_text(encoding='utf-8-sig').splitlines() if line.strip()]
    require(all(isinstance(e, dict) and isinstance(e.get('event'), str) for e in result), '증적 이벤트 형식이 올바르지 않습니다.')
    return result


def normalize(value):
    if isinstance(value, bool):
        return ('bool', value)
    if isinstance(value, (int, Decimal, float)):
        # Float is supported for callers with in-memory values only. All files
        # must enter through loads(), so their original precision is preserved.
        number = Decimal(str(value))
        require(number.is_finite(), '증적 숫자는 유한해야 합니다.')
        sign, digits, exponent = number.as_tuple()
        digits = list(digits)
        if not any(digits):
            return ('number', 0, (0,), 0)
        while digits[-1] == 0:
            digits.pop()
            exponent += 1
        return ('number', sign, tuple(digits), exponent)
    if isinstance(value, dict):
        return ('object', tuple((k, normalize(v)) for k, v in sorted(value.items())))
    if isinstance(value, list):
        return ('array', tuple(normalize(v) for v in value))
    if value is None or isinstance(value, str):
        return (type(value).__name__, value)
    raise EvidenceError('지원하지 않는 증적 값 형식입니다.')


def same_value(left, right):
    return normalize(left) == normalize(right)


def same_rows(left, right):
    """Top-level record order may change, but counts and nested order may not."""
    require(isinstance(left, list) and isinstance(right, list), '증적 레코드는 배열이어야 합니다.')
    return sorted(map(normalize, left), key=repr) == sorted(map(normalize, right), key=repr)


def rows(body, xml, ntic=False, weather=False):
    if not xml:
        value = loads(body)
        if weather:
            require(isinstance(value,dict) and isinstance(value.get('response'),dict),'기상정보 response 증적이 없습니다.')
            response=value['response'];require(isinstance(response.get('body'),dict),'기상정보 body 증적이 없습니다.')
            body=response['body'];require(isinstance(body.get('items'),dict) and isinstance(body['items'].get('item'),list),'기상정보 items/item 증적이 없습니다.')
            value=body['items']['item']
        if ntic:
            require(isinstance(value,dict) and isinstance(value.get("items"),list), "NTIC items 증적이 없습니다.")
            value=value["items"]
        require(isinstance(value, list) and all(isinstance(row, dict) for row in value), '본문 증적은 레코드 객체의 배열이어야 합니다.')
        return value
    text = body.decode('utf-8-sig') if isinstance(body, bytes) else body
    require('<!DOCTYPE' not in text and '<!ENTITY' not in text, '증적 XML의 DTD/entity는 허용하지 않습니다.')
    tree = ET.fromstring(text)
    require(tree.tag == 'result' and not (tree.text or '').strip(), '증적 XML의 result 구조가 올바르지 않습니다.')
    result = []
    for record in tree:
        require(record.tag == 'record' and not (record.text or '').strip() and not (record.tail or '').strip(), '증적 XML의 record 구조가 올바르지 않습니다.')
        fields = {}
        for field in record:
            require(field.tag not in fields and not list(field) and '}' not in field.tag and not (field.tail or '').strip(), '증적 XML 필드가 중복되거나 구조가 올바르지 않습니다.')
            fields[field.tag] = field.text or ''
        result.append(fields)
    return result
