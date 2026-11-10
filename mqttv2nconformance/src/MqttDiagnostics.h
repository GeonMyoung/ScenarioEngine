#pragma once
#include <PER/ASN1persrc.h>
#include <TOOL/ASN1Tool.h>
#include <stddef.h>

typedef struct MqttDiagnostic {
    char field[1024];
    char expected[512];
    long long actual;
    int has_actual;
    size_t bit_offset;
    int has_offset;
    int constraint;
} MqttDiagnostic;

#ifdef __cplusplus
extern "C" {
#endif
void MqttDiag_reset(const char *root);
size_t MqttDiag_enter(const char *field, unsigned index);
void MqttDiag_leave(size_t saved);
void MqttDiag_failure(ASN1WorkSpace *ws);
const MqttDiagnostic *MqttDiag_get(void);
int MqttDiag_check_integer(INTEGER *value, ASNUINT8 *constraint,size_t size);
int MqttDiag_check_enum(ASNINT32 *value, ASNUINT8 *constraint,size_t size);
#ifdef __cplusplus
}
#endif
