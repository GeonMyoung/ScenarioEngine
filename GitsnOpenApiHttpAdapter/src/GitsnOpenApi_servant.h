#ifndef GITSN_OPEN_API_SERVANT_H_LOCAL
#define GITSN_OPEN_API_SERVANT_H_LOCAL

#include <dz1_task.h>
DZ1_CPPLINK bool_t GitsnOpenApi_servantDeferResponse(void *uRsc, void *timer, u32_t session_id, void **signal, Dz1Error *err);
DZ1_CPPLINK bool_t GitsnOpenApi_shutdownSend(Dz1TcpClientSocket *socket, Dz1Error *err);
DZ1_CPPLINK bool_t GitsnOpenApi_servantDoRsp(void *uArg, void *uRsc, void *timer, u32_t session_id, GitsnOpenApiHttpRsp *msg, Dz1Error *err);
DZ1_CPPLINK bool_t GitsnOpenApi_servantWsSend(void *uArg, void *uRsc, void *timer, u32_t session_id, Dz1Binary *ws_payload, Dz1Error *err);
DZ1_CPPLINK bool_t GitsnOpenApi_servantRemoveSession(void *uArg, void *uRsc, void *timer, u32_t session_id, Dz1Error *err);

DZ1_CPPLINK bool_t GitsnOpenApi_servantMsgInit(Dz1Task *task, Dz1Error *err);

#endif
