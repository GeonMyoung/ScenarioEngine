/* Keep the existing C ASN.1 headers (including fields named 'class') behind a
   C ABI. No generated or legacy declarations are modified for C++ callers. */
#include <GitsnAsnUtil.h>
#include <GitsnAsnUtilDefJson.h>
#include <Iso14827TestHelperDefJson.h>
#include <stdint.h>
#include "DatexTlsmJson.inc"
#include "DatexTimRegional.inc"
#include "DatexTimProfile.inc"
bool_t DatexMapFromASN(MapData *, Gitsn_MapData *, Dz1Error *);
#define GitsnAsnUtil_Gitsn_MapDataFromASN DatexMapFromASN
bool_t DatexTravelerFromASN(TravelerInformation *, Gitsn_TravelerInformation *, Dz1Error *);
#define GitsnAsnUtil_Gitsn_TravelerInformationFromASN DatexTravelerFromASN
bool_t DatexSpatFromASN(SPAT *, Gitsn_SPAT *, Dz1Error *);
#define GitsnAsnUtil_Gitsn_SPATFromASN DatexSpatFromASN

static Dz1Binary *payload_json(Dz1JsonSpec *spec, char *name, void *value, Dz1Error *err) {
    Dz1Binary *result = NULL;
    Dz1Json *json = Dz1Json_new("UTF-8", spec, name, err);
    if (json) {
        if (Dz1Json_stringify(json, name, value, Dz1JsonNewLine_continuous, err)) {
            Dz1Str text = Dz1Json_stringified(json, err);
            if (text) {
                size_t length = strlen(text);
                if (length <= UINT32_MAX)
                    result = Dz1Binary_new((u8_t *)text, (u32_t)length, err);
                Dz1Str_del(text);
            }
        }
        Dz1Json_del(json);
    }
    return result;
}

Dz1Binary *DatexPayload_json(unsigned expected, unsigned char *bytes, size_t size) {
    Dz1Error err = DZ1_ERROR_INITIALIZER;
    Dz1Binary src = {bytes, (u32_t)size}, *raw = NULL, *result = NULL;
    Dz1JsonSpec *spec = NULL;
    ASN1WorkSpace ws;
    int id = 0;
    if (!bytes || !size || size > UINT32_MAX)
        return NULL;
    raw = GitsnAsnUtil_getValueFromMessageFrame(&src, &id, &err);
    if (!raw || id != (int)expected) {
        Dz1Binary_del(raw);
        return NULL;
    }
    spec = Iso14827TestHelperDef_genJsonSpec(&err);
    ASN1_INIT_WS_INFO(&ws);
#define AS_JSON(num, type)                                                                                   \
    case num: {                                                                                              \
        type asn;                                                                                            \
        Gitsn_##type value;                                                                                  \
        memset(&value, 0, sizeof(value));                                                                    \
        int decoded = type##_uper_decode(&ws, raw, &asn, &err);                                              \
        int converted = decoded && GitsnAsnUtil_Gitsn_##type##FromASN(&asn, &value, &err);                   \
        if (spec && converted)                                                                               \
            result = payload_json(spec, "Gitsn_" #type, &value, &err);                                       \
        Gitsn_##type##_purge(&value);                                                                        \
        break;                                                                                               \
    }
    switch (id) {
        AS_JSON(20, BasicSafetyMessage)
        AS_JSON(18, MapData)
        AS_JSON(19, SPAT)
        AS_JSON(27, RoadSideAlert)
        AS_JSON(31, TravelerInformation)
        case 50: {
            TrafficLightStatusMessage asn;
            if (TrafficLightStatusMessage_uper_decode(&ws, raw, &asn, &err))
                result = tlsm_json(&asn, &err);
            break;
        }
    default:
        break;
    }
#undef AS_JSON
    ASN1_INIT_WS_INFO_cancel(&ws);
    Dz1JsonSpec_del(spec);
    Dz1Binary_del(raw);
    return result;
}
int DatexPayload_messageId(unsigned char *bytes, size_t size) {
    Dz1Error err = DZ1_ERROR_INITIALIZER;
    if (!bytes || !size || size > UINT32_MAX) return -1;
    Dz1Binary src = {bytes, (u32_t)size};
    int id = -1;
    Dz1Binary *value = GitsnAsnUtil_getValueFromMessageFrame(&src, &id, &err);
    if (!value || err.code) id = -1;
    Dz1Binary_del(value);
    return id;
}
int DatexPayload_validate(unsigned expected, unsigned char *bytes, size_t size) {
    Dz1Error err = DZ1_ERROR_INITIALIZER;
    Dz1Binary src = {bytes, (u32_t)size};
    Dz1Binary *value = NULL;
    int id = 0, valid = 0;
    ASN1WorkSpace ws;
    if (!bytes || !size || size > UINT32_MAX)
        return 0;
    value = GitsnAsnUtil_getValueFromMessageFrame(&src, &id, &err);
    if (!value)
        return 0;
    ASN1_INIT_WS_INFO(&ws);
    if (id == (int)expected) {
        switch (id) {
        case 20: {
            BasicSafetyMessage v;
            valid = BasicSafetyMessage_uper_decode(&ws, value, &v, &err);
            break;
        }
        case 18: {
            MapData v;
            valid = MapData_uper_decode(&ws, value, &v, &err);
            break;
        }
        case 19: {
            SPAT v;
            valid = SPAT_uper_decode(&ws, value, &v, &err);
            break;
        }
        case 27: {
            RoadSideAlert v;
            valid = RoadSideAlert_uper_decode(&ws, value, &v, &err);
            break;
        }
        case 31: {
            TravelerInformation v;
            TimRegionalCounts counts;
            valid = TravelerInformation_uper_decode(&ws, value, &v, &err) && tim_regional(&v, &counts);
            break;
        }
        case 50: {
            TrafficLightStatusMessage v;
            valid = TrafficLightStatusMessage_uper_decode(&ws, value, &v, &err);
            break;
        }
        default:
            break;
        }
    }
    ASN1_INIT_WS_INFO_cancel(&ws);
    Dz1Binary_del(value);
    return valid && !err.code;
}
