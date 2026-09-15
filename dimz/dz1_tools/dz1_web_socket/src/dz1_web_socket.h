#ifndef DZ1_WEB_SOCKET_H_LOCAL
#define DZ1_WEB_SOCKET_H_LOCAL

#include <dz1_web_socket.h>


DZ1_CPPLINK Dz1WebSockDecCtx *Dz1WebSockDecCtx_generate(Dz1Error *err);

typedef struct Dz1WebSockDecEnv
{
	u8_t				*sp;
	size_t				 size;
} Dz1WebSockDecEnv;
DZ1_CPPLINK bool_t Dz1WebSockDecCtx_decode(Dz1WebSockDecCtx *p, Dz1WebSockDecEnv *src, Dz1WebSockMsg **_ret, Dz1Error *err);

#endif
