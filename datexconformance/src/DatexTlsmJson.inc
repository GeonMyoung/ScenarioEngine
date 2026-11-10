/* TLSM uses the KOR scalar layout. The legacy JSON registry has no TLSM root. */
#include <stdarg.h>
#include <stdio.h>
static int append_json(char *text, size_t capacity, size_t *used, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int written = vsnprintf(text + *used, capacity - *used, format, args);
    va_end(args);
    if (written < 0 || (size_t)written >= capacity - *used) return 0;
    *used += written;
    return 1;
}
static Dz1Binary *tlsm_json(TrafficLightStatusMessage *p, Dz1Error *err) {
    if (!p || !p->currentTime || p->trafficLightStatus.count > 1024) return NULL;
    size_t capacity = 4096 + (size_t)p->trafficLightStatus.count * 768, used = 0;
    char *text = Dz1Calloc(capacity, 1, err);
    Dz1Binary *result = NULL;
    if (!text) return NULL;
#define APP(...) do { if (!append_json(text, capacity, &used, __VA_ARGS__)) goto tlsm_done; } while (0)
    APP("{\"trafficLightID\":%lld,\"cycleCounter\":%lld,\"cycleTime\":%lld",
        (long long)p->traffiLightID, (long long)p->cycleCounter, (long long)p->cycleTime);
    if (p->DEF_TrafficLightStatusMessage_lat) APP(",\"lat\":%lld", (long long)p->lat);
    if (p->DEF_TrafficLightStatusMessage_lon) APP(",\"lon\":%lld", (long long)p->lon);
    BITSTRING *bits[2] = {&p->operationStatus, &p->controllerStatus};
    const char *names[2] = {"operationStatus", "controllerStatus"};
    for (int i = 0; i < 2; ++i) {
        if (bits[i]->numbits > 256 || (!bits[i]->data && bits[i]->numbits)) goto tlsm_done;
        APP(",\"%s\":{\"bitLength\":%u,\"hex\":\"", names[i], (unsigned)bits[i]->numbits);
        for (unsigned j = 0; j < (bits[i]->numbits + 7) / 8; ++j) APP("%02x", bits[i]->data[j]);
        APP("\"}");
    }
    APP(",\"currentTime\":{");
    int first = 1;
#define DATE_FIELD(name) if (p->currentTime->DEF_DDateTime_##name) { APP("%s\"" #name "\":%lld", first ? "" : ",", (long long)p->currentTime->name); first = 0; }
    DATE_FIELD(year); DATE_FIELD(month); DATE_FIELD(day); DATE_FIELD(hour);
    DATE_FIELD(minute); DATE_FIELD(second); DATE_FIELD(offset);
#undef DATE_FIELD
    APP("},\"trafficLightStatus\":[");
    for (unsigned i = 1; i <= p->trafficLightStatus.count; ++i) {
        TrafficLightStatus_KOR *v = ASN1_Get_Node_Index(&p->trafficLightStatus, i);
        if (!v) goto tlsm_done;
        APP("%s{\"trafficLightType\":%lld,\"consecutiveTrafficLight\":%lld,\"trafficLightIntervalType\":%d,"
            "\"pedestrianCall\":%s,\"actuatedinterval\":%s,\"permissiveNonProtected\":%s,"
            "\"lightingStatus\":%lld,\"maxIntervalLength\":%lld,\"remainingTime\":%lld,"
            "\"directionCode\":%lld,\"reserved\":%s}", i == 1 ? "" : ",",
            (long long)v->trafficLightType, (long long)v->consecutiveTrafficLight,
            (int)v->trafficLightIntervalType, v->pedestrianCall ? "true" : "false",
            v->actuatedinterval ? "true" : "false", v->permissiveNonProtected ? "true" : "false",
            (long long)v->lightingStatus, (long long)v->maxIntervalLength,
            (long long)v->remainingTime, (long long)v->directionCode, v->reserved ? "true" : "false");
    }
    APP("]}");
    result = Dz1Binary_new((unsigned char *)text, (u32_t)used, err);
tlsm_done:
    Dz1Free(text);
#undef APP
    return result;
}
