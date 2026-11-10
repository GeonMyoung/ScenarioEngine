/* MQTT-only strict boundary checks. Keep the shared DATEX/legacy codec ABI intact. */
#include "MqttTraceAliases.h"
#include <GitsnAsnUtil.h>
#include "MqttDiagnostics.h"
#include <stdint.h>
#include <excpt.h>
#include "MqttPayloadStrict.h"

static int fail(MqttPayloadCheck *check, const char *code) {
    check->code = code;
    return 0;
}

/* Check the root MessageFrame open-type determinants before calling legacy code.
   Its generated schema is: extension bit + messageId(15 bits) + value(open type).
   Fragmented length determinants are bounded as well as short/14-bit lengths. */
static int frame_bounds(const unsigned char *bytes, size_t size, MqttPayloadCheck *check) {
    size_t pos = 2;
    int more;
    if (size < 3) return fail(check, "UPER_TRUNCATED");
    do {
        size_t length;
        unsigned first;
        if (pos == size) return fail(check, "UPER_TRUNCATED");
        first = bytes[pos++];
        more = (first & 0xc0) == 0xc0;
        if (!(first & 0x80)) length = first;
        else if (!more) {
            if (pos == size) return fail(check, "UPER_TRUNCATED");
            length = ((first & 0x3f) << 8) | bytes[pos++];
        } else {
            unsigned multiplier = first & 0x3f;
            if (multiplier < 1 || multiplier > 4) return fail(check, "UPER_DECODE_OR_CONSTRAINT");
            length = (size_t)multiplier * 16384;
        }
        if (length > size - pos) return fail(check, "UPER_TRUNCATED");
        pos += length;
    } while (more);
    if (!(bytes[0] & 0x80) && pos != size) return fail(check, "UPER_TRAILING_DATA");
    return 1;
}

/* UPER complete encodings may end with 0..7 zero padding bits, never extra octets.
   Check after every decoder: legacy primitives can read allocated workspace bytes
   beyond the supplied open type without reporting an error. */
static int exact_end(ASN1WorkSpace *ws, const unsigned char *bytes, size_t size,
                     size_t *bits, MqttPayloadCheck *check) {
    size_t consumed;
    unsigned padding;
    if (ws->buffer.current < ws->buffer.data || ws->buffer.bitOffset > 8)
        return fail(check, "UPER_DECODE_OR_CONSTRAINT");
    consumed = (size_t)(ws->buffer.current - ws->buffer.data) * 8 + (8 - ws->buffer.bitOffset);
    *bits = consumed;
    if (consumed > size * 8) return fail(check, "UPER_TRUNCATED");
    if ((consumed + 7) / 8 != size) return fail(check, "UPER_TRAILING_DATA");
    padding = (unsigned)(size * 8 - consumed);
    if (padding && (bytes[size - 1] & ((1u << padding) - 1)))
        return fail(check, "UPER_NONZERO_PADDING");
    return 1;
}

/* General TIM does not require Annex II directive fields. For the two KOR open
   types already supported by the current validator, validate their boundaries
   too. Other regional schemas remain opaque, as in the existing implementation. */
static int tim_region_list(ASN1List *list, int path, MqttPayloadCheck *check) {
    for (unsigned i = 1; i <= list->count; ++i) {
        RegionalExtension *ext = ASN1_Get_Node_Index(list, i);
        if (!ext) return fail(check, "UPER_DECODE_OR_CONSTRAINT");
        if (ext->regionId != 4) continue;
        check->stage = path ? "GeographicalPath-KOR" : "TravelerInformation-KOR";
        if (!ext->regExtValue.data || !ext->regExtValue.numocts)
            return fail(check, "UPER_TRUNCATED");
        ASN1WorkSpace ws;
        ASN1_INIT_WS_INFO(&ws);
        ASN1_Save_WORKSPACE(&ws, ext->regExtValue.data, ext->regExtValue.numocts);
        ws.dataSize = ext->regExtValue.numocts;
        int decoded;
        size_t bits = 0;
        if (path) {
            GeographicalPath_KOR value = {0};
            decoded = ASN1_PER_UNAlign_Dec_GeographicalPath_KOR(&ws, &value);
        } else {
            TravelerInformation_KOR value = {0};
            decoded = ASN1_PER_UNAlign_Dec_TravelerInformation_KOR(&ws, &value);
        }
        int valid = decoded >= 0 && exact_end(&ws, ext->regExtValue.data,
                                               ext->regExtValue.numocts, &bits, check);
        if (decoded < 0) fail(check, "UPER_DECODE_OR_CONSTRAINT");
        ASN1_INIT_WS_INFO_cancel(&ws);
        if (!valid) return 0;
    }
    return 1;
}

static int tim_regions(TravelerInformation *tim, MqttPayloadCheck *check) {
    if (tim->DEF_TravelerInformation_regional && !tim_region_list(&tim->regional, 0, check)) return 0;
    for (unsigned i = 1; i <= tim->dataFrames.count; ++i) {
        TravelerDataFrame *frame = ASN1_Get_Node_Index(&tim->dataFrames, i);
        if (!frame) return fail(check, "UPER_DECODE_OR_CONSTRAINT");
        for (unsigned j = 1; j <= frame->regions.count; ++j) {
            GeographicalPath *path = ASN1_Get_Node_Index(&frame->regions, j);
            if (!path) return fail(check, "UPER_DECODE_OR_CONSTRAINT");
            if (path->DEF_GeographicalPath_regional && !tim_region_list(&path->regional, 1, check)) return 0;
        }
    }
    return 1;
}

static int validate_core(unsigned expected, unsigned char *bytes, size_t size,
                         MqttPayloadCheck *check) {
    ASN1WorkSpace outer, inner;
    MessageFrame frame = {0};
    int valid = 0, decoded = -1;
    check->code = "UPER_DECODE_OR_CONSTRAINT";
    check->stage = "MessageFrame";
    MqttDiag_reset("MessageFrame");
    check->frame_bits = check->message_bits = 0;
    if (!bytes || !size || size > 1024 * 1024) return fail(check, "UPER_LENGTH");
    if (!frame_bounds(bytes, size, check)) return 0;
    ASN1_INIT_WS_INFO(&outer);
    ASN1_INIT_WS_INFO(&inner);
    ASN1_Save_WORKSPACE(&outer, bytes, (ASNINT32)size);
    outer.dataSize = size;
    if (ASN1_PER_UNAlign_Dec_MessageFrame(&outer, &frame) < 0) goto done;
    if (!exact_end(&outer, bytes, size, &check->frame_bits, check)) goto done;
    if (frame.messageId != expected) { fail(check, "MESSAGE_ID_MISMATCH"); goto done; }
    check->stage = "MessageFrame.value";
    MqttDiag_reset(expected==19?"SPaT":expected==50?"TLSM":expected==31?"TIM":"BSM");
    if (!frame.value.data || !frame.value.numocts) { fail(check, "UPER_TRUNCATED"); goto done; }
    if (frame.value.numocts > size) { fail(check, "UPER_TRUNCATED"); goto done; }
    ASN1_Save_WORKSPACE(&inner, frame.value.data, frame.value.numocts);
    inner.dataSize = frame.value.numocts;
    /* Each generated decoder calls ASN1_CHECK_<type> recursively. This preserves
       required ASN.1 members, ranges, SIZE and CHOICE constraints without inventing
       G4 requirements for ASN.1 OPTIONAL members or unavailable sentinel values. */
    switch (expected) {
    case 20: {
        BasicSafetyMessage value = {0};
        decoded = ASN1_PER_UNAlign_Dec_BasicSafetyMessage(&inner, &value);
        break;
    }
    case 19: {
        SPAT value = {0};
        decoded = ASN1_PER_UNAlign_Dec_SPAT(&inner, &value);
        break;
    }
    case 50: {
        TrafficLightStatusMessage value = {0};
        decoded = ASN1_PER_UNAlign_Dec_TrafficLightStatusMessage(&inner, &value);
        break;
    }
    case 31: {
        TravelerInformation value = {0};
        decoded = ASN1_PER_UNAlign_Dec_TravelerInformation(&inner, &value);
        if (decoded >= 0) {
            if (!exact_end(&inner, frame.value.data, frame.value.numocts, &check->message_bits, check)) goto done;
            if (!tim_regions(&value, check)) goto done;
            check->stage = "MessageFrame.value";
        }
        break;
    }
    default:
        fail(check, "UNSUPPORTED_MESSAGE"); goto done;
    }
    if (decoded < 0) goto done;
    if (!exact_end(&inner, frame.value.data, frame.value.numocts, &check->message_bits, check)) goto done;
    check->code = "OK";
    check->stage = "complete";
    valid = 1;
done:
    ASN1_INIT_WS_INFO_cancel(&inner);
    ASN1_INIT_WS_INFO_cancel(&outer);
    return valid;
}

int MqttPayload_validateStrict(unsigned expected, unsigned char *bytes, size_t size,
                               MqttPayloadCheck *check) {
    /* MqttPayload is a short-lived, one-input subprocess. Malformed nested
       lengths in the legacy decoder must produce an explicit failure JSON.
       Do not unwind a possibly damaged decoder pool after a native exception;
       the process exits immediately after reporting this failure. */
    __try {
        return validate_core(expected, bytes, size, check);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        MqttDiag_failure(NULL);
        return fail(check, GetExceptionCode() == 0xe0470001u ? "UPER_TRUNCATED" : "UPER_NATIVE_REJECTED");
    }
}

extern Dz1Binary *DatexPayload_json(unsigned, unsigned char *, size_t);
Dz1Binary *MqttPayload_jsonStrict(unsigned expected, unsigned char *bytes, size_t size) {
    __try {
        return DatexPayload_json(expected, bytes, size);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return NULL;
    }
}
