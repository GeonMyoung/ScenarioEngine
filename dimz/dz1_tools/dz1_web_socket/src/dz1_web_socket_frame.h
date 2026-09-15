#ifndef DZ1_WEB_SOCKET_FRAME_H_LOCAL
#define DZ1_WEB_SOCKET_FRAME_H_LOCAL

#include <dz1_bin.h>
#include "dz1_web_socket.h"
#include "dz1_web_socket_struct_def.h"

DZ1_CPPLINK Dz1Binary	*Dz1WebSocket_binFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err);
DZ1_CPPLINK Dz1Binary	*Dz1WebSocket_textFrame(Dz1Asn1UTF8Str *str, bool_t masking, Dz1Error *err);

DZ1_CPPLINK Dz1Binary	*Dz1WebSocket_pingFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err);
DZ1_CPPLINK Dz1Binary	*Dz1WebSocket_pongFrame(u8_t *data, size_t size, bool_t masking, Dz1Error *err);
DZ1_CPPLINK Dz1Binary	*Dz1WebSocket_closeFrame(Dz1WebSocketCloseReason reason, Dz1Asn1UTF8Str *opt_debug_info, bool_t masking, Dz1Error *err);

#endif
