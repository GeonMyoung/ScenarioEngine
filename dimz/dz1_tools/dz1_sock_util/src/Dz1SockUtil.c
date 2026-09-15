#include <dz1_socket_acceptor.h>
#include <dz1_socket_receiver.h>
#include <dz1_socket_callback.h>

#include "Dz1SockUtil.h"
#include "Dz1SockUtilData.h"


static Dz1TcpSocketAcceptorBehavior Dz1SockUtilAcceptor_callback(void *uArg, void *uRsc,
																 Dz1TcpClientSocket **s,
																 Dz1SockAddr *local,
																 Dz1SockAddr *peer,
																 Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;

	Dz1SockUtilAcceptorArg *arg = (Dz1SockUtilAcceptorArg *)uArg;
	Dz1SockUtilAcceptorConnected *msg = NULL;
	
	char strAddr[64];
	if (Dz1SockAddrA_printable(peer, strAddr, FALSE, NULL) == NULL) strcpy(strAddr, "#error");
	Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "<<< Connected from %s\n", strAddr);

	if ((msg = Dz1SockUtilAcceptorConnected_new(NULL, NULL, arg->acceptorID, (*s), errp)) == NULL) ERR_OUT(errp);
	else
	{
		(*s) = NULL;
		pthread_cleanup_push(Dz1SockUtilAcceptorConnected_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilAcceptorConnected_del,
										(Dz1DumpFunc)Dz1SockUtilAcceptorConnected_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilAcceptorConnected_delAndSetNull, (void *)&msg);
	}
	return ret;
}

static void Dz1SockUtilAcceptor_exception(void *uArg, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockUtilAcceptorArg *arg = (Dz1SockUtilAcceptorArg *)uArg;
	Dz1SockUtilAcceptorException *msg = Dz1SockUtilAcceptorException_new(arg->acceptorID, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1SockUtilAcceptorException_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
									DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION, (void **)&msg,
									(Dz1DelFunc)Dz1SockUtilAcceptorException_del,
									(Dz1DumpFunc)Dz1SockUtilAcceptorException_dump,
									reason, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1SockUtilAcceptorException_delAndSetNull, (void *)&msg);
	}
}

u32_t Dz1SockUtilAcceptorForTask_start(u32_t acceptorID, Dz1SockAddr *listenAddr, u32_t parentTaskQueueID, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockUtilAcceptorArg *arg = Dz1SockUtilAcceptorArg_new(parentTaskQueueID, acceptorID, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		u16_t _port = 0;
		Dz1TcpServerSocket *sock = NULL;
		pthread_cleanup_push(Dz1SockUtilAcceptorArg_delAndSetNull, (void *)&arg);
		if ((sock = Dz1TcpServerSocket_open(listenAddr, &_port, 10, errp)) == NULL) ERR_OUT(errp);
		else
		{
			char str_addr[53];
			pthread_cleanup_push(Dz1TcpServerSocket_closeAndSetNull, (void *)&sock);

			if (_Dz1SockAddr_setPort(listenAddr, _port, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "Dz1SockUtilAcceptorForTask_start() : Listen = %s\n", Dz1SockAddrA_printable(listenAddr, str_addr, FALSE, NULL));

				if ((ret = Dz1TcpSocketAcceptor_start(sock, TRUE, 0, 0,
													NULL, // init
													Dz1SockUtilAcceptor_callback, // forward
													Dz1SockUtilAcceptor_exception, // exception,
													NULL,
													NULL,
													(void *)&arg, (Dz1DelFunc)Dz1SockUtilAcceptorArg_del, errp)) == -1) ERR_OUT(errp);
				else
				{
					sock = NULL;
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1TcpServerSocket_closeAndSetNull, (void *)&sock);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilAcceptorArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Native Socket Mode 1
///////////////////////////////////////////////////////////////////////////////
static Dz1SocketReceierBehavior Dz1SockeUtilTcpReceiver_forward(void *uArg, void *uRsc,
																Dz1SockAddr *peer, Dz1SockAddr *local,
																Dz1TcpClientSocket *s,
																u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	Dz1SockUtilReceiverArg *arg = (Dz1SockUtilReceiverArg *)uArg;
	Dz1SockUtilReceiverReceived *msg = Dz1SockUtilReceiverReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->stream = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_RECEIVER_RECEIVED, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiverReceived_del,
										(Dz1DumpFunc)Dz1SockUtilReceiverReceived_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
	}
	return ret;
}

static void Dz1SockeUtilTcpReceiver_exception(void *uArg, void *uRsc,
											  Dz1SockAddr *peer, Dz1SockAddr *local,
											  Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1SockUtilReceiverArg *arg = (Dz1SockUtilReceiverArg *)uArg;
	Dz1SockUtilReceiverReceived *msg = Dz1SockUtilReceiverReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiverReceived_del,
										(Dz1DumpFunc)Dz1SockUtilReceiverReceived_dump,
										reason, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
	}
}

u32_t Dz1SockUtilTcpReceiverForTask_start(Dz1TcpClientSocket **sock, bool_t autoClose,
										  Dz1SockAddr *peer, Dz1SockAddr *local,
										  size_t bufSize, u32_t parentTaskQueueID,
										  Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1SockUtilReceiverArg *arg = NULL;
	if ((arg = Dz1SockUtilReceiverArg_new(parentTaskQueueID, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1TcpSocketReceiver_start(peer, local, bufSize, 0, sock, autoClose,
											  NULL, // init
											  Dz1SockeUtilTcpReceiver_forward,
											  Dz1SockeUtilTcpReceiver_exception,
											  NULL,	// timeout
											  NULL,	// cleanup
											  (void **)&arg, (Dz1DelFunc)Dz1SockUtilReceiverArg_del,
											  errp)) == -1) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiverArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Callback Socket Mode 1
///////////////////////////////////////////////////////////////////////////////
static void Dz1SockUtil_callbackRx(void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local,
								   u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockUtilReceiverArg *arg = (Dz1SockUtilReceiverArg *)uArg;
	Dz1SockUtilReceiverReceived *msg = Dz1SockUtilReceiverReceived_new(NULL, NULL, NULL, errp);
	u32_t type = (data == NULL || size == 0) ? DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED : DZ1_SOCK_UTIL_RECEIVER_RECEIVED;
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if (data != NULL && size > 0 && (msg->stream = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										type, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiverReceived_del,
										(Dz1DumpFunc)Dz1SockUtilReceiverReceived_dump,
										errp, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiverReceived_delAndSetNull, (void *)&msg);
	}
}

static void Dz1SockUtil_callbackTx(void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SockUtilReceiverArg *arg = (Dz1SockUtilReceiverArg *)uArg;
	Dz1SockUtilTransmiterSent *msg = Dz1SockUtilTransmiterSent_new(NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilTransmiterSent_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_TRANSMITER_SENT, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilTransmiterSent_del,
										(Dz1DumpFunc)Dz1SockUtilTransmiterSent_dump,
										status, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilTransmiterSent_delAndSetNull, (void *)&msg);
	}
}

Dz1Error Dz1SockUtilTcpClient_modeCallback(Dz1TcpClientSocket *sock,
										   Dz1SockAddr *peer, Dz1SockAddr *local,
										   size_t rx_buf_size, u32_t parentTaskQueueID)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1SockUtilReceiverArg *cb_arg = NULL;
	if ((cb_arg = Dz1SockUtilReceiverArg_new(parentTaskQueueID, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiverArg_delAndSetNull, (void *)&cb_arg);
// 		if ((err = Dz1TcpClientSocket_modeCallback(sock, peer, local, rx_buf_size,
// 												   Dz1SockUtil_callbackRx, (void *)rx_arg,
// 												   (Dz1DelFunc)Dz1SockUtilReceiverArg_del,
// 												   Dz1SockUtil_callbackTx, (void *)tx_arg,
// 												   (Dz1DelFunc)Dz1SockUtilReceiverArg_del)).code) ERR_OUT(errp);
		if ((*errp = Dz1SocketCallback2_associate(sock, peer, local, rx_buf_size,
												  Dz1SockUtil_callbackRx,
												  Dz1SockUtil_callbackTx,
												  (void **)&cb_arg, (Dz1DelFunc)Dz1SockUtilReceiverArg_del)).code) ERR_OUT(errp);
		else
		{
			cb_arg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiverArg_delAndSetNull, (void *)&cb_arg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Native Socket Mode 2
///////////////////////////////////////////////////////////////////////////////
static Dz1SocketReceierBehavior Dz1SockeUtilTcpReceiver2_forward(void *uArg, void *uRsc,
																 Dz1SockAddr *peer, Dz1SockAddr *local,
																 Dz1TcpClientSocket *s,
																 u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	Dz1SockUtilReceiver2Arg *arg = (Dz1SockUtilReceiver2Arg *)uArg;
	Dz1SockUtilReceiver2Received *msg = Dz1SockUtilReceiver2Received_new(arg->sessionID, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
		if ((msg->stream = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_RECEIVER2_RECEIVED, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiver2Received_del,
										(Dz1DumpFunc)Dz1SockUtilReceiver2Received_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
	}
	return ret;
}

static void Dz1SockeUtilTcpReceiver2_exception(void *uArg, void *uRsc,
											   Dz1SockAddr *peer, Dz1SockAddr *local,
											   Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1SockUtilReceiver2Arg *arg = (Dz1SockUtilReceiver2Arg *)uArg;
	Dz1SockUtilReceiver2Received *msg = Dz1SockUtilReceiver2Received_new(arg->sessionID, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
		if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiver2Received_del,
										(Dz1DumpFunc)Dz1SockUtilReceiver2Received_dump,
										reason, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
	}
}

u32_t Dz1SockUtilTcpReceiver2ForTask_start(u32_t sessionID, bool_t autoClose,
										   Dz1TcpClientSocket **sock,
										   Dz1SockAddr *peer, Dz1SockAddr *local,
										   size_t bufSize, u32_t parentTaskQueueID,
										   Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1SockUtilReceiver2Arg *arg = NULL;
	if ((arg = Dz1SockUtilReceiver2Arg_new(parentTaskQueueID, sessionID, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1TcpSocketReceiver_start(peer, local, bufSize, 0, sock, autoClose,
											  NULL, // init
											  Dz1SockeUtilTcpReceiver2_forward,
											  Dz1SockeUtilTcpReceiver2_exception,
											  NULL,	// timeout
											  NULL,	// cleanup
											  (void **)&arg, (Dz1DelFunc)Dz1SockUtilReceiver2Arg_del,
											  errp)) == -1) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Callback Socket Mode 2
///////////////////////////////////////////////////////////////////////////////
static void Dz1SockUtil_callback2Rx(void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local,
									u8_t *data, size_t size, Dz1Error *status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SockUtilReceiver2Arg *arg = (Dz1SockUtilReceiver2Arg *)uArg;
	u32_t type = (data == NULL || size == 0) ? DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED : DZ1_SOCK_UTIL_RECEIVER2_RECEIVED;
	Dz1SockUtilReceiver2Received *msg = Dz1SockUtilReceiver2Received_new(arg->sessionID, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
		/*
		// debug code
		if (type == DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Disconnect detected\n");
			ERR_OUT(status);
		}
		*/

		if ((msg->stream = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
										type, (void **)&msg,
										(Dz1DelFunc)Dz1SockUtilReceiver2Received_del,
										(Dz1DumpFunc)Dz1SockUtilReceiver2Received_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiver2Received_delAndSetNull, (void *)&msg);
	}
}

static void Dz1SockUtil_callback2Tx(void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SockUtilReceiver2Arg *arg = (Dz1SockUtilReceiver2Arg *)uArg;
	Dz1SockUtilTransmiter2Sent *msg = Dz1SockUtilTransmiter2Sent_new(arg->sessionID, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilTransmiter2Sent_delAndSetNull, (void *)&msg);
		if ((*errp = Dz1Task_queuePost(arg->parentQueueID, DZ1_TASK_QUEUE_NONE,
									DZ1_SOCK_UTIL_TRANSMITER2_SENT, (void **)&msg,
									(Dz1DelFunc)Dz1SockUtilTransmiter2Sent_del,
									(Dz1DumpFunc)Dz1SockUtilTransmiter2Sent_dump,
									status, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1SockUtilTransmiter2Sent_delAndSetNull, (void *)&msg);
	}
}

Dz1Error Dz1SockUtilTcpClient_mode2Callback(u32_t sessionID, Dz1TcpClientSocket *sock, 
											Dz1SockAddr *peer, Dz1SockAddr *local,
											size_t rx_buf_size, u32_t parentTaskQueueID)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SockUtilReceiver2Arg *cb_arg = NULL;
	if ((cb_arg = Dz1SockUtilReceiver2Arg_new(parentTaskQueueID, sessionID, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&cb_arg);
		if ((err = Dz1SocketCallback2_associate(sock, peer, local, rx_buf_size,
												Dz1SockUtil_callback2Rx,
												Dz1SockUtil_callback2Tx,
												(void **)&cb_arg, (Dz1DelFunc)Dz1SockUtilReceiver2Arg_del)).code) ERR_OUT(errp);
		else
		{
			cb_arg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilReceiver2Arg_delAndSetNull, (void *)&cb_arg);
	}
	return err;
}

Dz1SockUtilRxBuf *Dz1SockUtilRxBuf_new(u32_t elastic_size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilRxBuf *__internal_ret = (Dz1SockUtilRxBuf *)Dz1Calloc(sizeof(Dz1SockUtilRxBuf), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilRxBuf_delAndSetNull, (void *)&__internal_ret);
		if (0) { }
		else if ((__internal_ret->elb = Dz1ElasticBuf_new(elastic_size, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->st = Dz1Stream_openRefElasticBuf(__internal_ret->elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->elastic_size = elastic_size;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilRxBuf_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SockUtilRxBuf_load(Dz1SockUtilRxBuf *dst, u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || data == NULL || sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1ElasticBuf_push(dst->elb, data, sz)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxFifo
void Dz1SockUtilTxFifo_del(Dz1SockUtilTxFifo *p)
{
	if (p == NULL) return;
	else
	{
		Dz1SockUtilTxEntry *i = p->head, *next = NULL;
		while(i)
		{
			next = i->next;
			Dz1SockUtilTxEntry_del(i);
			i = next;
		}
		p->head = p->tail = NULL;
		Dz1Free(p);
	}
}

bool_t Dz1SockUtilTxFifo_isEmpty(Dz1SockUtilTxFifo *p)
{
	bool_t ret = TRUE;
	if (p != NULL)
	{
		if (p->head == NULL && p->tail == NULL) ret = TRUE;
		else ret = FALSE;
	}
	return ret;
}

static void _Dz1SockUtilTxFifo_push(Dz1SockUtilTxFifo *p, Dz1SockUtilTxEntry *node)
{
	if (Dz1SockUtilTxFifo_isEmpty(p))
		p->head = p->tail = node;
	else
	{
		p->tail->next = node;
		p->tail = node;
	}
}

static bool_t Dz1SockUtilTxFifo_push(Dz1SockUtilTxFifo *p, u8_t *data, size_t sz, Dz1Error *errp)
{
	Dz1SockUtilTxEntry *node = Dz1SockUtilTxEntry_new(NULL, NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SockUtilTxEntry_delAndSetNull, (void *)&node);
		if ((node->chunk = Dz1Binary_new(data, (u32_t)sz, errp)) == NULL) ERR_OUT(errp);
		else
		{
			_Dz1SockUtilTxFifo_push(p, node);
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilTxEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1SockUtilTxFifo_push2(Dz1SockUtilTxFifo *p, Dz1Binary **_bin, Dz1Error *errp)
{
	Dz1SockUtilTxEntry *node = NULL;
	if ((node = Dz1SockUtilTxEntry_new(NULL, *_bin, errp)) == NULL) ERR_OUT(errp);
	else
	{
		*_bin = NULL;
		_Dz1SockUtilTxFifo_push(p, node);
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1SockUtilTxEntry *Dz1SockUtilTxFifo_pop(Dz1SockUtilTxFifo *p, Dz1Error *errp)
{
	Dz1SockUtilTxEntry *ret = p->head;				// pick head
	if (ret == NULL) Dz1Error_set(errp, ENOENT);	// is empty
	else if (ret == p->tail)						// this is last entry
		p->head = p->tail = NULL;
	else
	{	// many entry
		Dz1SockUtilTxEntry *head = p->head;			// get next head ptr
		p->head = head->next;						// set head ptr
	}
	ret->next = NULL;								// unlink node
	return ret;
}

static bool_t _Dz1SockUtilTxFifo_send(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, Dz1Error *errp)
{
	Dz1SockUtilTxEntry *txe = p->head;
	if (txe != NULL)
	{
		Dz1Binary *bin = txe->chunk;
		ssize_t sz = 0;
		/*
		u32_t log_lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), & log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG)
		{
			_Dz1Thread_log(">>> Socket TX = ");
			DZ1_DUMP(Dz1Binary, bin, 0);
		}
		*/

		if ((sz = sock->send(sock, bin->data, bin->size, DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SockUtilTxFifo_send(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (p == NULL || sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (sz == 0) Dz1Error_set(errp, 0);			// just return
	else if (data == NULL) ERR_SET_OUT(errp, EINVAL);	// sz > 0, data != NULL
	else
	{
		bool_t do_send = FALSE;
		if (Dz1SockUtilTxFifo_isEmpty(p)) do_send = TRUE;

		if (Dz1SockUtilTxFifo_push(p, data, sz, errp) == FALSE) ERR_OUT(errp);
		else if (do_send && _Dz1SockUtilTxFifo_send(p, sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Dz1SockUtilTxFifo_count(Dz1SockUtilTxFifo *p)
{
	u32_t cnt = 0;
	Dz1SockUtilTxEntry *i = NULL;
	for (i = p->head; i != NULL; i = i->next) cnt++;
	return cnt;
}

bool_t Dz1SockUtilTxFifo_send2(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, Dz1Binary **_bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	if (p == NULL || sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_bin == NULL || (bin = *_bin) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (bin->size == 0) Dz1Error_set(errp, 0);
	else if (bin->data == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		bool_t do_send = FALSE;
		if (Dz1SockUtilTxFifo_isEmpty(p)) do_send = TRUE;

// 		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "&&& Dz1SockUtilTxFifo_send2() FIFO Count = %u(%d)\n", Dz1SockUtilTxFifo_count(p), do_send);

		if (Dz1SockUtilTxFifo_push2(p, _bin, errp) == FALSE) ERR_OUT(errp);
		else if (do_send == 0)
		{
//			Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "&&& Dz1SockUtilTxFifo_send2() TX Suspended\n");
			Dz1Error_set(errp, 0);
		}
		else if (_Dz1SockUtilTxFifo_send(p, sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t _Dz1SockUtilTxFifo_sentProc(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, u32_t *ret_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockUtilTxEntry *node = NULL;
	if (p == NULL || sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
// 		Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "&&& Dz1SockUtilTxFifo_sentProc() FIFO Count = %u\n", Dz1SockUtilTxFifo_count(p));
		if ((node = Dz1SockUtilTxFifo_pop(p, errp)) == NULL)
		{	// no more data to send
			if (ret_sz != NULL)
				*ret_sz = 0;
		}
		else
		{
			pthread_cleanup_push(Dz1SockUtilTxEntry_delAndSetNull, (void *)&node);

			if (ret_sz != NULL)
			{
				Dz1Binary *chunk = node->chunk;
				(*ret_sz) = (chunk != NULL) ? chunk->size : 0;
			}

			if (_Dz1SockUtilTxFifo_send(p, sock, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1SockUtilTxEntry_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1SockUtilTxFifo
///////////////////////////////////////////////////////////////////////////////

Dz1CallbackSockIO *Dz1CallbackSockIO_new(Dz1SockAddr *peer, u32_t rx_buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1CallbackSockIO *ret = NULL;
	if (peer == NULL || rx_buf_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CallbackSockIO *)Dz1Calloc(sizeof(Dz1CallbackSockIO), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr local;
		pthread_cleanup_push(Dz1CallbackSockIO_delAndSetNull, (void *)&ret);
		if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1SockAddr_setAddrZero(&local, peer, errp) == FALSE) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_buf = Dz1ElasticBuf_new(rx_buf_sz, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_stream = Dz1Stream_openRefElasticBuf(ret->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1CallbackSockIO_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1CallbackSockIO *Dz1CallbackSockIO_wrap(Dz1SockAddr **peer, Dz1SockAddr **local, u32_t rx_buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1CallbackSockIO *ret = NULL;
	if (peer == NULL || *peer == NULL || local == NULL || *local == NULL || rx_buf_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CallbackSockIO *)Dz1Calloc(sizeof(Dz1CallbackSockIO), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CallbackSockIO_delAndSetNull, (void *)&ret);
		ret->peer = *peer; *peer = NULL;
		ret->local = *local; *local = NULL;
		if ((ret->rx_buf = Dz1ElasticBuf_new(rx_buf_sz, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rx_stream = Dz1Stream_openRefElasticBuf(ret->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1CallbackSockIO_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TcpClientSocket *Dz1CallbackSockIO_prepareMode1(Dz1CallbackSockIO *io, u32_t my_queue_id, Dz1TimeVal *conn_to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1TcpClientSocket *ret = NULL;
	if (io == NULL || io->peer == NULL || io->local == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char strA_peer[64];
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, ">>> TCP Client Session to %s\n",
					Dz1SockAddrA_printable(io->peer, strA_peer, FALSE, NULL));

		if ((ret = Dz1TcpClientSocket_open(io->peer, io->local, conn_to, errp)) == NULL) ERR_OUT(errp);
		else
		{
			char strA_local[64];
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "@@@ TCP Client Session Established %s-%s\n",
						Dz1SockAddrA_printable(io->local, strA_local, FALSE, NULL), strA_peer);

			if ((*errp = Dz1SockUtilTcpClient_modeCallback(ret, io->peer, io->local, 1024, my_queue_id)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (UnifaceSocketIO_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

Dz1TcpClientSocket *Dz1CallbackSockIO_prepareMode2(Dz1CallbackSockIO *io, u32_t my_queue_id, u16_t sid, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1TcpClientSocket *ret = NULL;
	struct timeval conn_to = { 1, 5000000 };
	if (io == NULL || io->peer == NULL || io->local == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char strA_peer[64];
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, ">>> TCP Client Session to %s\n",
					Dz1SockAddrA_printable(io->peer, strA_peer, FALSE, NULL));

		if ((ret = Dz1TcpClientSocket_open(io->peer, io->local, &conn_to, errp)) == NULL) ERR_OUT(errp);
		else
		{
			char strA_local[64];
			u32_t session_id = (u32_t)sid & 0xFFFF;
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "@@@ TCP Client Session Established %s-%s\n",
						Dz1SockAddrA_printable(io->local, strA_local, FALSE, NULL), strA_peer);

			if ((*errp = Dz1SockUtilTcpClient_mode2Callback(session_id, ret, io->peer, io->local, 1024, my_queue_id)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

