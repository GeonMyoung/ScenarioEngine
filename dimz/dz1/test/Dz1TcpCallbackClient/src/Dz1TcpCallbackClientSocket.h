#ifndef DZ1_TCP_CALLBACK_CLIENT_SOCKET_H_LOCAL
#define DZ1_TCP_CALLBACK_CLIENT_SOCKET_H_LOCAL

#include <Dz1TcpCallbackMsgDef.h>
#include "Dz1TcpCallbackClientEnv.h"
DZ1_CPPLINK Dz1Error _encode_and_send_msg(Dz1TcpCallbackSession *session, Dz1TcpCallbackMsg *m);
DZ1_CPPLINK Dz1Error _send_echo(Dz1TcpCallbackSession *session);

DZ1_CPPLINK Dz1Error _connect_and_go(Dz1TcpCallbackClientArg *arg, Dz1TcpCallbackClientEnv *env, void *timer, u32_t myQueueID);

DZ1_CPPLINK Dz1Error Dz1TcpCallbackClientSocket_msgInit(void *task);

#endif
