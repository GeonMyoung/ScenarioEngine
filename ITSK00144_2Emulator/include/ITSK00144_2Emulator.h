#ifndef ITSK00144_2_EMULATOR_H
#define ITSK00144_2_EMULATOR_H

#include <ITSK00144_2EmulatorDef.h>

DZ1_CPPLINK void *ITSK001442Emulator_new(ITSK001442EmulatorException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void ITSK001442Emulator_del(void *task);


// client
DZ1_CPPLINK bool_t ITSK00144_2EmulatorClient_init(void* task, u16_t port, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2EmulatorClient_clear(void* task, Dz1Error* err);

// server
DZ1_CPPLINK bool_t ITSK00144_2EmulatorServer_open(void* task, u16_t port, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2EmulatorServer_send(void* task, Dz1Str opcode, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2EmulatorServer_dsrc(void* task, u16_t id, Dz1Error* err);
DZ1_CPPLINK bool_t ITSK00144_2EmulatorServer_clear(void* task, Dz1Error* err);



#endif // ITSK00144_2_EMULATOR
