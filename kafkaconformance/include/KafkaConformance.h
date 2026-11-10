#ifndef KAFKA_CONFORMANCE_H
#define KAFKA_CONFORMANCE_H
#include <dz1_task.h>
#ifdef __cplusplus
extern "C" {
#endif
void *KafkaConformance_new(void *mainTask, Dz1Str scenario, void (*exception)(void *, Dz1Error *),
                          void *exceptionArg, Dz1Error *error);
#ifdef __cplusplus
}
#endif
#endif
