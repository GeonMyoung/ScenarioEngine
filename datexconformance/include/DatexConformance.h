#ifndef DATEX_CONFORMANCE_H
#define DATEX_CONFORMANCE_H
#include <dz1_task.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Independent entry point: legacy ISO14827 categories never call this module. */
void *DatexConformance_new(void *mainTask, Dz1Str scenario, void (*exceptionProc)(void *, Dz1Error *),
                           void *exceptionArg, Dz1Error *error);
/* Returns TRUE only for a task owned by this module; preserves legacy routing. */
bool_t DatexConformance_isTask(void *task);
bool_t DatexConformance_validation(void *task, void *response, Dz1Error *error);
#ifdef __cplusplus
}
#endif
#endif
