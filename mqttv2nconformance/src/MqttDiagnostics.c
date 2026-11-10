/* One-input native subprocess: diagnostics never alter shared codec state. */
#include "MqttDiagnostics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static MqttDiagnostic detail;
static char path[1024];
void MqttDiag_reset(const char *root) { memset(&detail,0,sizeof(detail)); snprintf(path,sizeof(path),"%s",root); }
size_t MqttDiag_enter(const char *field,unsigned index) {
    size_t saved=strlen(path);
    if(index) snprintf(path+saved,sizeof(path)-saved,"[%u]",index);
    else if(field && *field) snprintf(path+saved,sizeof(path)-saved,".%s",field);
    return saved;
}
void MqttDiag_leave(size_t saved) { if(saved<sizeof(path)) path[saved]=0; }
void MqttDiag_failure(ASN1WorkSpace *ws) {
    if(!detail.field[0]) {
        snprintf(detail.field,sizeof(detail.field),"%s",path);
        if(ws && ws->buffer.current>=ws->buffer.data && ws->buffer.bitOffset<=8) {
            detail.bit_offset=(size_t)(ws->buffer.current-ws->buffer.data)*8+(8-ws->buffer.bitOffset);
            detail.has_offset=1;
        }
    }
}
const MqttDiagnostic *MqttDiag_get(void) { return &detail; }
static void numeric(long long actual, ASNUINT8 *encoded) {
    if(detail.field[0]) return;
    MqttDiag_failure(NULL); detail.actual=actual;detail.has_actual=1;detail.constraint=1;
    ASN1ConsCheck c=String_to_CheckStruct(&encoded,0);
    size_t pos=0;
    for(int i=0;i+1<c.Length[0] && pos<sizeof(detail.expected)-64;i+=2) {
        int n=snprintf(detail.expected+pos,sizeof(detail.expected)-pos,"%s%lld..%lld",i?", ":"",
                       (long long)c.StringforRange[i],(long long)c.StringforRange[i+1]);
        if(n>0) pos+=(size_t)n;
    }
    if(c.Length[0]) free(c.StringforRange);
}
int MqttDiag_check_integer(INTEGER *value, ASNUINT8 *constraint,size_t size) {
    ASNUINT8 copy[512];
    if(size<=sizeof(copy)) memcpy(copy,constraint,size);
    int ret=ASN1_CHECK_INTEGER(value,constraint);
    if(ret<0 && value && size<=sizeof(copy)) numeric(*value,copy);
    return ret;
}
int MqttDiag_check_enum(ASNINT32 *value, ASNUINT8 *constraint,size_t size) {
    ASNUINT8 copy[512];
    if(size<=sizeof(copy)) memcpy(copy,constraint,size);
    int ret=ASN1_CHECK_ENUMERATED(value,constraint);
    if(ret<0 && value && size<=sizeof(copy)) numeric(*value,copy);
    return ret;
}
