#ifndef DZ1_TCP_CALLBACK_SERVER_H
#define DZ1_TCP_CALLBACK_SERVER_H

#include <Dz1TcpCallbackServerDef.h>

DZ1_CPPLINK void *Dz1TcpCallbackServer_new(u16_t base_port, 
										   Dz1TcpCallbackServerException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Dz1TcpCallbackServer_del(void *task);

#endif
