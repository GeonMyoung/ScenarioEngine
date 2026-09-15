#ifndef DZ1_WEB_SOCKET_STRUCT_H_LOCAL
#define DZ1_WEB_SOCKET_STRUCT_H_LOCAL

#include <dz1_uuid.h>

#include "dz1_web_socket.h"
#include "dz1_web_socket_struct_def.h"

DZ1_CPPLINK Dz1WebSocketAuth *Dz1WebSocketAuth_generate(Dz1UniversalUniqueID *uu_id, Dz1Error *err);

DZ1_CPPLINK Dz1Asn1UTF8Str *Dz1WebSockInitInfo_getRequest(Dz1WebSockInitInfo *p, Dz1Binary *key_bin, Dz1Error *errp);
DZ1_CPPLINK Dz1WebSockInitInfo *Dz1WebSockInitInfo_generate(str_t uri_u8, Dz1Error *err);

#endif
