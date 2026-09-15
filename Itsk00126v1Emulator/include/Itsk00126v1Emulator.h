#ifndef ITSK00126_V1_EMULATOR_H
#define ITSK00126_V1_EMULATOR_H

#include <Itsk00126v1EmulatorDef.h>

#define ITSK_00126_V1_LOCAL_CENTER_ID Dz1T("2-11110-0001")

DZ1_CPPLINK void *Itsk00126V1Emulator_new(Itsk00126V1EmulatorException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Itsk00126V1Emulator_del(void *task);


DZ1_CPPLINK bool_t Itsk00126v1EmulatorClient_init(void* task, u16_t port, Dz1Error* err);
DZ1_CPPLINK bool_t Itsk00126v1EmulatorClient_send(void* task, u16_t msg, Dz1Error *err);
DZ1_CPPLINK bool_t Itsk00126v1EmulatorClient_clear(void* task, Dz1Error* err);

DZ1_CPPLINK bool_t Itsk00126v1EmulatorClient_json(void* task, Dz1Error* err);


#endif // ITSK00126_V1_EMULATOR
