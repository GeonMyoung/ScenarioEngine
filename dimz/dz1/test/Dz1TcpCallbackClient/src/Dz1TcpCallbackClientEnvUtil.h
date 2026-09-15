#ifndef DZ1_TCP_CALLBACK_CLIENT_ENV_UTIL_H_LOCAL
#define DZ1_TCP_CALLBACK_CLIENT_ENV_UTIL_H_LOCAL

#include "Dz1TcpCallbackClientArg.h"
#include "Dz1TcpCallbackClientEnv.h"

DZ1_CPPLINK void _session_runtime_terminate(void *timer, Dz1TcpCallbackSession *session);
DZ1_CPPLINK Dz1Error _decode_proc(Dz1TcpCallbackClientArg *arg, Dz1TcpCallbackClientEnv *env, void *timer,
								  Dz1TcpCallbackSession *session, Dz1SocketBuf *buf);

#endif
