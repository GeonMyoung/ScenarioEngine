#include <dz1_thread.h>
#include "dz1_socket.h"
#include "dz1_socket_callback.h"

Dz1Error Dz1SocketCallback2_init(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1SocketCallback2_sys_init()).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

void Dz1SocketCallback2_cleanup(void)
{
	Dz1SocketCallback2_sys_cleanup();
}

Dz1Error Dz1SocketCallback2_associate(Dz1TcpClientSocket *sock,
									  Dz1SockAddr *peer,
									  Dz1SockAddr *local,
									  size_t rx_buf_size,
									  Dz1SocketCallback2Rcvd rx_cb,
									  Dz1SocketCallback2Sent tx_cb,
									  void **user_ptr, Dz1DelFunc user_ptr_del)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (Dz1SocketCallback2Spec_skel_gen(sock, peer, local, rx_buf_size, rx_cb, tx_cb, user_ptr, user_ptr_del, FALSE, errp) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Dz1SocketCallback2Spec
///////////////////////////////////////////////////////////////////////////////
