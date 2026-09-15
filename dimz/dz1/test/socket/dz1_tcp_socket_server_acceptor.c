#include <dz1_task.h>
#include <dz1_socket_acceptor.h>
#include "dz1_tcp_socket_server_acceptor.h"
#include "dz1_tcp_socket_server_msg.h"

static Dz1TcpSocketAcceptorBehavior acceptorForward(void *ptr, void *uRsc,
													Dz1TcpClientSocket **s,
													Dz1SockAddr *local, Dz1SockAddr *peer,
													Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;

	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(ptr);

	Dz1TcpSocketServerConnected *msg = Dz1TcpSocketServerConnected_new(NULL, NULL, (*s), errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		(*s) = NULL;
		pthread_cleanup_push(Dz1TcpSocketServerConnected_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
										DZ1_TCP_SOCKET_SERVER_ACCEPTOR_CONNECTED, (void **)&msg,
										(Dz1DelFunc)Dz1TcpSocketServerConnected_del,
										(Dz1DumpFunc)Dz1TcpSocketServerConnected_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (ReceiverEntry_cleanupAndSetNull, (void *)&node);
	}
	return ret;
}

static Dz1TcpSocketAcceptorBehavior acceptorForward2(void *ptr, void *uRsc,
													Dz1TcpClientSocket **s,
													Dz1SockAddr *local, Dz1SockAddr *peer,
													Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;
	return ret;
}

static Dz1TcpSocketAcceptorBehavior acceptorForward3(void *ptr, void *uRsc,
													Dz1TcpClientSocket **s,
													Dz1SockAddr *local, Dz1SockAddr *peer,
													Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;

	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(ptr);

	Dz1TcpSocketServerConnected *msg = Dz1TcpSocketServerConnected_new(NULL, NULL, (*s), errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		(*s) = NULL;
		pthread_cleanup_push(Dz1TcpSocketServerConnected_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
										DZ1_TCP_SOCKET_SERVER_ACCEPTOR_CONNECTED2, (void **)&msg,
										(Dz1DelFunc)Dz1TcpSocketServerConnected_del,
										(Dz1DumpFunc)Dz1TcpSocketServerConnected_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (ReceiverEntry_cleanupAndSetNull, (void *)&node);
	}
	return ret;
}

static void accceptorException(void *ptr, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(ptr);

	if ((*errp = Dz1Task_queuePostSimpleErr(dstQueueID,
											DZ1_TASK_QUEUE_NONE, 
											DZ1_TCP_SOCKET_SERVER_ACCEPTOR_EXCEPTION,
											reason)).code) ERR_OUT(errp);
}

u32_t Dz1TcpSocketServerAcceptor_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1TcpServerSocket *s;
	void *_arg = (void *)DZ1_VAL2PTR32(parentQueueID);
	if ((s = Dz1TcpServerSocket_open(server, NULL, 5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpServerSocket_delAndSetNull, (void *)&s);
		if ((ret = Dz1TcpSocketAcceptor_start(s, TRUE, 0, 0,
											  NULL,
											  acceptorForward,
											  accceptorException,
											  NULL,
											  NULL,
											  &_arg, NULL, errp)) == (u32_t)-1) ERR_OUT(errp);
		else
		{
			s = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpServerSocket_delAndSetNull, (void *)&s);
	}
	return ret;
}

u32_t Dz1TcpSocketServerAcceptor2_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1TcpServerSocket *s;
	void *_arg = (void *)DZ1_VAL2PTR32(parentQueueID);
	if ((s = Dz1TcpServerSocket_open(server, NULL, 5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpServerSocket_delAndSetNull, (void *)&s);
		if ((ret = Dz1TcpSocketAcceptor_start(s, TRUE, 0, 0,
											  NULL,
											  acceptorForward2,
											  accceptorException,
											  NULL,
											  NULL,
											  &_arg, NULL, errp)) == (u32_t)-1) ERR_OUT(errp);
		else
		{
			s = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpServerSocket_delAndSetNull, (void *)&s);
	}
	return ret;
}

u32_t Dz1TcpSocketServerAcceptor3_start(u32_t parentQueueID, Dz1SockAddr *server, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1TcpServerSocket *s;
	void *_arg = (void *)DZ1_VAL2PTR32(parentQueueID);
	if ((s = Dz1TcpServerSocket_open(server, NULL, 5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpServerSocket_delAndSetNull, (void *)&s);
		if ((ret = Dz1TcpSocketAcceptor_start(s, TRUE, 0, 0,
											  NULL,
											  acceptorForward3,
											  accceptorException,
											  NULL,
											  NULL,
											  &_arg, NULL, errp)) == (u32_t)-1) ERR_OUT(errp);
		else
		{
			s = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpServerSocket_delAndSetNull, (void *)&s);
	}
	return ret;
}

void Dz1TcpSocketServerAcceptor_stop(u32_t thid)
{
	if (thid == (u32_t)-1) return;
	Dz1TcpSocketAcceptor_stop(thid);
}