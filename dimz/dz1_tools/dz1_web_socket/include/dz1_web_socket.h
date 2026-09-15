#ifndef DZ1_WEB_SOCKET_H
#define DZ1_WEB_SOCKET_H

#include <dz1_web_socket_conf.h>

#include <dz1_asn1.h>
#include <dz1_web_socket_def.h>

DZ1_CPPLINK Dz1WebSocket	*Dz1WebSocket_createU(Dz1Asn1UTF8Str *uri, u32_t my_queue_id, bool_t masking, Dz1Error *err);
DZ1_CPPLINK Dz1WebSocket	*Dz1WebSocket_createA(str_t			  uri, u32_t my_queue_id, bool_t masking, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK Dz1WebSocket	*Dz1WebSocket_createW(wstr_t		  uri, u32_t my_queue_id, bool_t masking, Dz1Error *err);
#ifdef UNICODE
#define						 Dz1WebSocket_create	Dz1WebSocket_createW
#else // UNICODE
#define						 Dz1WebSocket_create	Dz1WebSocket_createA
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1WebSocket_create	Dz1WebSocket_createA
#endif // UNIS_SYSTEM

DZ1_CPPLINK bool_t Dz1WebSocket_onReceived(Dz1WebSocket *p, Dz1SockUtilReceiverReceived *msg, Dz1WebSockMsgList *ret_msgs, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocket_onSent(Dz1WebSocket *p, Dz1SockUtilTransmiterSent *notify, Dz1Error *err);

DZ1_CPPLINK bool_t Dz1WebSocket_sendText(Dz1WebSocket *p, Dz1Asn1UTF8Str *str, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocket_sendBin(Dz1WebSocket *p, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocket_sendPing(Dz1WebSocket *p, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1WebSocket_sendClose(Dz1WebSocket *p, Dz1WebSocketCloseReason reason, Dz1Asn1UTF8Str *opt_debug_info, Dz1Error *err);

#endif // DZ1_WEB_SOCKET_H
