#ifndef GITSN_DSRC_EMULATOR_H
#define GITSN_DSRC_EMULATOR_H

#include <GitsnDsrcEmulatorDef.h>

DZ1_CPPLINK void *GitsnDsrcEmulator_new(GitsnDsrcEmulatorException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void GitsnDsrcEmulator_del(void *task);




// test

DZ1_CPPLINK bool_t GitsnDsrcEmulatorTest_init(void* task, u16_t port, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDsrcEmulatorTest_send(void* task, u16_t id, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDsrcEmulatorTest_tdpsend(void* task, u16_t id, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnDsrcEmulatorTest_clear(void* task, Dz1Error* err);
#endif // GITSN_DSRC_EMULATOR
