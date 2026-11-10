/* Link these primitives into MqttPayload only. The original library objects are
   not pulled into this executable because their symbols are supplied here.
   Reuse the remaining functions verbatim; no shared SDK/generated files change. */
#include <windows.h>
#include "MqttDiagnostics.h"
#define ASN1_ReadBuffer MqttLegacyReadBuffer
#include "../../ASN.1.GITSN.LIB2/SupportLib/TOOL/ASN1_Operate_Byte.c"
#undef ASN1_ReadBuffer

#define MQTT_BOUNDS_EXCEPTION 0xe0470001u
static ASNINT32 bounds_failure(ASN1WorkSpace *ws) {
    /* Several legacy callers ignore a negative read result. Stop immediately,
       before a partial length or CHOICE discriminator can drive allocations. */
    MqttDiag_failure(ws);
    RaiseException(MQTT_BOUNDS_EXCEPTION, 0, 0, NULL);
    return -403;
}

ASNINT32 ASN1_ReadBuffer(ASN1WorkSpace *ws, ASNUINT8 *value, ASNUINT32 length, ASN1PERAlign align) {
    size_t available, skip;
    if (!length) return 0;
    if (!ws || !value || ws->buffer.bitOffset > 8 ||
        ws->buffer.current < ws->buffer.data || ws->buffer.current > ws->buffer.Vdeocd_valid)
        return bounds_failure(ws);
    available = (size_t)(ws->buffer.Vdeocd_valid - ws->buffer.current) * 8;
    skip = 8 - ws->buffer.bitOffset;
    if (align == ALIGN && ws->buffer.bitOffset != 8) skip = 8;
    if (skip > available || length > available - skip) return bounds_failure(ws);
    return MqttLegacyReadBuffer(ws, value, length, align);
}

#define ASN1_PER_UNAlign_Dec_OpenType MqttLegacyOpenType
#include "../../ASN.1.GITSN.LIB2/SupportLib/PER/ASN1_PER_OpenType.c"
#undef ASN1_PER_UNAlign_Dec_OpenType

/* Read open types without moving the workspace or peeking outside the input.
   Keep fragment determinants and payload octets in their original positions. */
ASNINT32 ASN1_PER_UNAlign_Dec_OpenType(ASN1WorkSpace *ws, OpenType *value) {
    ASNUINT8 first, second;
    size_t total = 0;
    int more;
    value->data = NULL;
    value->numocts = 0;
    do {
        size_t length, available, skip;
        ASN1_ReadBuffer(ws, &first, 8, UNALIGN);
        more = (first & 0xc0) == 0xc0;
        if (!(first & 0x80)) length = first;
        else if (!more) {
            ASN1_ReadBuffer(ws, &second, 8, UNALIGN);
            length = ((first & 0x3f) << 8) | second;
        } else {
            unsigned multiplier = first & 0x3f;
            if (multiplier < 1 || multiplier > 4) return bounds_failure(ws);
            length = (size_t)multiplier * 16384;
        }
        if (ws->buffer.current > ws->buffer.Vdeocd_valid || ws->buffer.bitOffset > 8)
            return bounds_failure(ws);
        available = (size_t)(ws->buffer.Vdeocd_valid - ws->buffer.current) * 8;
        skip = 8 - ws->buffer.bitOffset;
        if (skip > available || length > (available - skip) / 8 || total + length > 1024 * 1024)
            return bounds_failure(ws);
        if (length) {
            value->data = total ? mpool_realloc(ws->Pmemory, value->data, total + length)
                                : mpool_malloc(ws->Pmemory, length);
            if (!value->data) return bounds_failure(ws);
            ASN1_ReadBuffer(ws, value->data + total, (ASNUINT32)(length * 8), UNALIGN);
            total += length;
        }
    } while (more);
    value->numocts = (ASNUINT32)total;
    return 0;
}
