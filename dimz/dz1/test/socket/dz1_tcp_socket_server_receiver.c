#include <dz1_socket_receiver.h>
#include "dz1_tcp_socket_server_msg.h"
#include "dz1_tcp_socket_server_receiver.h"

static Dz1SocketReceierBehavior Dz1TcpSocketServerReceiver_fwd(void *uArg, void *uRsc,
															   Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s,
															   u8_t *data, size_t size, Dz1Error *errp)
{
	ssize_t status;
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	if ((status = s->send(s, data, size, DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, errp)) < 0) ERR_OUT(errp);
	else if (status == 0) ERR_SET_OUT(errp, EPIPE);
	if (errp->code) ret = Dz1SocketReceierBehavior_exception;

	return ret;
}

static void Dz1TcpSocketServerReceiver_exception(void *uArg, void *uRsc,
												 Dz1SockAddr *peer, Dz1SockAddr *local,
												 Dz1TcpClientSocket *s, Dz1Error *reason)
{
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(uArg);
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSocketServerReceived *msg = Dz1TcpSocketServerReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
									DZ1_TCP_SOCKET_SERVER_RECEIVER_DISCONNECTED, (void **)&msg,
									(Dz1DelFunc)Dz1TcpSocketServerReceived_del,
									(Dz1DumpFunc)Dz1TcpSocketServerReceived_dump,
									reason, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerConnected_delAndSetNull, (void *)&msg);
	}
}

u32_t Dz1TcpSocketServerReceiver_start(u32_t parentQueueID, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;

	void *_arg = (void *)DZ1_VAL2PTR32(parentQueueID);
	if ((ret = Dz1TcpSocketReceiver_start(peer, local, 4096, 0, &sock, FALSE,
										NULL,
										Dz1TcpSocketServerReceiver_fwd,
										Dz1TcpSocketServerReceiver_exception,
										NULL,
										NULL,
										&_arg, NULL, errp)) == (u32_t)-1) ERR_OUT(errp);
	return ret;
}

void Dz1TcpSocketServerReceiver_stop(u32_t id)
{
	Dz1SocketReceiver_stop(id);
}

