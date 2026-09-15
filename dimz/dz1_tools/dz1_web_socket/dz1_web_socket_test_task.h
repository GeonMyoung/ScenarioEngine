#ifndef DZ1_WEB_SOCKET_TEST_TASK_H_LOCAL
#define DZ1_WEB_SOCKET_TEST_TASK_H_LOCAL

#include "dz1_web_socket_test_task_def.h"

#define DZ1_WEB_SOCK_MSG			0xF0000000
#define DZ1_WEB_SOCK_MSG_DEFAULT	(DZ1_WEB_SOCK_MSG | 0x00000001)
#define DZ1_WEB_SOCK_MSG_OPEN		(DZ1_WEB_SOCK_MSG | 0x00000002)
#define DZ1_WEB_SOCK_MSG_SEND		(DZ1_WEB_SOCK_MSG | 0x00000003)
#define DZ1_WEB_SOCK_MSG_CLOSE		(DZ1_WEB_SOCK_MSG | 0x00000004)

DZ1_CPPLINK Dz1Task *Dz1WebSocketTask_create(Dz1WebSocketTaskExceptionCB cb, void *cb_param, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1WebSocketTask_open(Dz1Task *task, Dz1Asn1UTF8Str *uri, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocketTask_sendText(Dz1Task *task, Dz1Asn1UTF8Str *text, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocketTask_sendBin(Dz1Task *task, Dz1Binary *bin, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocketTask_sendPing(Dz1Task *task, Dz1Binary *bin, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocketTask_close(Dz1Task *task, Dz1Asn1UTF8Str *opt_text, Dz1Error *err);

#endif
