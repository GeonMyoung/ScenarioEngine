#ifndef DZ1_TCP_CALLBACK_SERVER_ENV_UTIL_H_LOCAL
#define DZ1_TCP_CALLBACK_SERVER_ENV_UTIL_H_LOCAL

#include "Dz1TcpCallbackServerArg.h"
#include "Dz1TcpCallbackServerEnv.h"

DZ1_CPPLINK Dz1Error _tx_fifo_fwd(Dz1SocketFifo *fifo, Dz1TcpClientSocket *sock);

DZ1_CPPLINK Dz1Error _decode_and_process(Dz1TcpCallbackServerArg *arg, Dz1TcpCallbackServerEnv *env, void *timer,
										 Dz1TcpCallbackSession *session, Dz1SocketBuf *buf);

DZ1_CPPLINK Dz1TaskProcStatus _summary(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp);

#endif