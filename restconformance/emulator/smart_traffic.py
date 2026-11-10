"""Independent standard table 4-23 fixtures and receiver validation."""
from datetime import datetime
from decimal import Decimal


def default_records():
    return [dict(collectDate='20260811153000', nodeId='NODE000001',
                 linkId='LINK000001', ascrId='ASCR000001', laneNo=1,
                 vkndCd=1, spd=42.50, vol=15)]


def validate_records(rows):
    if not isinstance(rows, list):
        raise ValueError('Expected a standard JSON array')
    for row in rows:
        if not isinstance(row, dict):
            raise ValueError('Expected a record')
        for field in ('collectDate', 'nodeId', 'linkId', 'ascrId', 'laneNo', 'vkndCd', 'spd', 'vol'):
            if field not in row:
                raise ValueError('Missing ' + field)
        date = row['collectDate']
        if not isinstance(date, str) or len(date) != 14 or not date.isascii() or not date.isdigit():
            raise ValueError('Invalid collection timestamp')
        datetime.strptime(date, '%Y%m%d%H%M%S')
        for field in ('nodeId', 'linkId', 'ascrId'):
            if not isinstance(row[field], str) or not 1 <= len(row[field]) <= 10:
                raise ValueError('Invalid ' + field)
        for field, precision, scale in [('laneNo', 1, 0), ('vkndCd', 1, 0), ('spd', 5, 2), ('vol', 7, 0)]:
            value = row[field]
            if isinstance(value, bool) or not isinstance(value, (int, float, Decimal)):
                raise ValueError('Invalid numeric type: ' + field)
            number = Decimal(str(value))
            if not number.is_finite():
                raise ValueError('Invalid numeric value')
            normalized = number.normalize()
            fraction = max(0, -normalized.as_tuple().exponent) if number else 0
            integer = max(0, normalized.adjusted() + 1) if number else 0
            if fraction > scale or integer > precision - scale:
                raise ValueError('Invalid numeric precision: ' + field)
    return rows
