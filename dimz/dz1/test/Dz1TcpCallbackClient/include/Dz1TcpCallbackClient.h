#ifndef DZ1_TCP_CALLBACK_CLIENT_H
#define DZ1_TCP_CALLBACK_CLIENT_H

#include <Dz1TcpCallbackClientDef.h>

DZ1_CPPLINK void *Dz1TcpCallbackClient_new(Dz1TcpCallbackClientException exceptionProc,
										   void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Dz1TcpCallbackClient_del(void *task);

DZ1_CPPLINK Dz1Error Dz1TcpCallbackClient_simulate_start(void *task, Dz1SockAddr *server, u32_t maxConnection,
														 bool_t use_ssl, bool_t stress_mode);
DZ1_CPPLINK Dz1Error Dz1TcpCallbackClient_simulate_stop(void *task);

#endif
