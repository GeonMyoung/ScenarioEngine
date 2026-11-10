#pragma once
#include <stddef.h>

typedef struct MqttPayloadCheck {
    const char *code;
    const char *stage;
    size_t frame_bits;
    size_t message_bits;
} MqttPayloadCheck;

#ifdef __cplusplus
extern "C" {
#endif
int MqttPayload_validateStrict(unsigned expected, unsigned char *bytes, size_t size,
                               MqttPayloadCheck *check);
#ifdef __cplusplus
}
#endif
