#ifndef MQTT_V2N_CONFORMANCE_H
#define MQTT_V2N_CONFORMANCE_H
#include <dz1_task.h>
#ifdef __cplusplus
extern "C" {
#endif
bool_t MqttV2NConformance_isTask(void *task);
void *MqttV2NConformance_new(void *mainTask, Dz1Str scenario, void (*exception)(void *, Dz1Error *),
                          void *exceptionArg, Dz1Error *error);
#ifdef __cplusplus
}
#endif
#endif
