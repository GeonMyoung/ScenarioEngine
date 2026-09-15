#ifndef DZ1_SOCKET_H_LOCAL
#define DZ1_SOCKET_H_LOCAL

#include <dz1_socket.h>

typedef struct Dz1Socket
{
	SOCKET fd;
} Dz1Socket;

#define					 Dz1Socket_open(lp, t, p, op, ep) _Dz1Socket_open((lp), (t), (p), (op), (ep), __FILE__, __LINE__)
DZ1_CPPLINK Dz1Socket  *_Dz1Socket_open(Dz1SockAddr *local, int type, int protocol, in_port_t *o_port, Dz1Error *err, const char *__file__, int __line__);
DZ1_CPPLINK ssize_t		 Dz1Socket_send(Dz1Socket *p, Dz1SockAddr *dst, u8_t *data, size_t size, bool_t isUrgent, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1Socket_recv(Dz1Socket *p, Dz1SockAddr *peer, u8_t *buf, size_t size, Dz1Error *err);
DZ1_CPPLINK void		 Dz1Socket_close(Dz1Socket *p);
DZ1_CPPLINK Dz1Error	 Dz1Socket_listen(Dz1Socket *p, int backlog);
DZ1_CPPLINK Dz1Socket	*Dz1Socket_accept(Dz1Socket *p, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *err);
DZ1_CPPLINK Dz1Error	 Dz1Socket_connect(Dz1Socket *p, Dz1SockAddr *dst, struct timeval *to);
DZ1_CPPLINK int			 Dz1Socket_wait(Dz1Socket *p, int flag, struct timeval *to, Dz1Error *err);
DZ1_CPPLINK Dz1Error	 Dz1Socket_getLocalAddr(Dz1Socket *p, Dz1SockAddr *local);
#define					 Dz1Socket_getLocalName		Dz1Socket_getLocalAddr

#endif