#ifndef DZ1_INET_FTP_RECEIVER_H_LOCAL
#define DZ1_INET_FTP_RECEIVER_H_LOCAL

#include <dz1_socket.h>
#include <dz1_sock_addr.h>

DZ1_CPPLINK u32_t Dz1InetFtpReceiver_start(void *tControl, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, Dz1Error *err);

DZ1_CPPLINK void Dz1InetFtpReceiver_stop(u32_t id);
static __inline__ void Dz1InetFtpReceiver_startCancel(void *ptr)
{
	u32_t *id = (u32_t *)ptr;
	if ((*id) != (u32_t)-1)
		Dz1InetFtpReceiver_stop((*id));
	(*id) = -1;
}


#endif

