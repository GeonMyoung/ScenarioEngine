#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif
#include <Dz1TcpCallbackMsgCodec.h>

#include "Dz1TcpCallbackClientArg.h"
#include "Dz1TcpCallbackClientEnvUtil.h"
#include "Dz1TcpCallbackClientTimerUtil.h"
#include "Dz1TcpCallbackClientMsg.h"
#include "Dz1TcpCallbackClientSocket.h"

static Dz1Binary *_getBinary(Dz1TcpCallbackMsg *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);

		if ((sz = Dz1TcpCallbackMsg_enc(NULL, -1, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1TcpCallbackMsg_enc(ret->data, ret->size, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// TX FIFO Helper
static Dz1Error _tx_fifo_fwd(Dz1SocketFifo *fifo, Dz1TcpClientSocket *sock)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary *packet = NULL;
	if ((packet = (Dz1Binary *)Dz1SocketFifo_peek(fifo, errp)) != NULL)
	{
		ssize_t sz = 0;
		if ((sz = sock->send(sock, packet->data, packet->size, DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, errp)) < 0) ERR_OUT(errp);
		else if (sz == 0) ERR_SET_OUT(errp, EPIPE);
		else if (sz != packet->size) ERR_SET_OUT(errp, EFAULT);
//		else Dz1Thread_printf(">>> send %u\n", sz);
	}
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _tx_fifo_send(Dz1SocketFifo *fifo, Dz1TcpClientSocket *sock, Dz1Binary **bin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	bool_t doSend = Dz1SocketFifo_count(fifo) == 0 ? TRUE : FALSE;
	if ((err = Dz1SocketFifo_push(fifo, bin)).code) ERR_OUT(&err);
	else if (doSend)
	{
		if ((err = _tx_fifo_fwd(fifo, sock)).code) ERR_OUT(&err);
	}
	return err;
}
// TX FIFO Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TX Helper
Dz1Error _encode_and_send_msg(Dz1TcpCallbackSession *session, Dz1TcpCallbackMsg *m)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Binary *bin = _getBinary(m, &err);
	if (bin == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((err = _tx_fifo_send(session->tx_fifo, session->sock, &bin)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

// TX Helper
///////////////////////////////////////////////////////////////////////////////

Dz1Error _send_echo(Dz1TcpCallbackSession *session)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpCallbackMsg *msg = Dz1TcpCallbackMsg_new(Dz1TcpCallbackMsgPresent_echo, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		Dz1TimeVal tNow = Dz1TimeVal_get();

		Dz1TcpCallbackEcho *e = NULL;
		pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&msg);
		if ((msg->x.echo = e = Dz1TcpCallbackEcho_new(session->echoID++, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((e->stamp = Dz1TimeVal_clone(&tNow, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encode_and_send_msg(session, msg)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Received
static __inline__ void _rx_fwd(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *io_err)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpCallbackClientMsgReceived *msg = Dz1TcpCallbackClientMsgReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientMsgReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if (data == NULL || size == 0)
		{
			if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
								DZ1_TCP_CALLBACK_CLIENT_RECEIVER_DISCONNECTED, (void **)&msg,
								(Dz1DelFunc)Dz1TcpCallbackClientMsgReceived_del,
								(Dz1DumpFunc)Dz1TcpCallbackClientMsgReceived_dump,
								NULL, NULL, io_err)).code) ERR_OUT(errp);
		}
		else if ((msg->packet = Dz1Binary_new(data, size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
								DZ1_TCP_CALLBACK_CLIENT_RECEIVER_RECEIVED, (void **)&msg,
								(Dz1DelFunc)Dz1TcpCallbackClientMsgReceived_del,
								(Dz1DumpFunc)Dz1TcpCallbackClientMsgReceived_dump,
								NULL, NULL, NULL)).code) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientMsgReceived_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _rx_m_received(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;

	Dz1TcpCallbackClientMsgReceived *msg = (Dz1TcpCallbackClientMsgReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->find(env->sessions, &key);
	if (session != NULL)
	{
		ssize_t sz = 0;
		Dz1SocketBuf *buf = session->rx_buf;
		Dz1Binary *packet = msg->packet;

//		Dz1Thread_printf("<<< RX %u\n", packet->size);
		if ((sz = Dz1SocketBuf_push(buf, packet->data, packet->size, errp)) < 0)
		{
			Dz1Thread_printf("!!! Buffer PUSH Fail\n");
			env->sessions->extract(env->sessions, &key);
			_session_runtime_terminate(timer, session);
			ERR_OUT(errp);
		}
		else
		{
			if (sz != packet->size)
			{
				char strAddr[64];
				Dz1Thread_printf("!!! Warning : Socket Buffer Overflow %s\n",
					Dz1SockAddr_printable(session->peer, strAddr, FALSE, NULL));
			}

			if ((*errp = _decode_proc(arg, env, timer, session, buf)).code)
			{
				Dz1Thread_printf("!!! Processing Fail\n");
				env->sessions->extract(env->sessions, &key);
				_session_runtime_terminate(timer, session);
				ERR_OUT(errp);
			}
		}
	}
	return ret;
}

static Dz1TaskProcStatus _rx_m_disconnected(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
//	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;

	Dz1TcpCallbackClientMsgReceived *msg = (Dz1TcpCallbackClientMsgReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Thread_printf("!!! Disconnected\n");
		_session_runtime_terminate(timer, session);
	}
	return ret;
}
// Received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Transmit Complete
static __inline__ void _tx_cnf(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *io_err)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t code = ((io_err == NULL) || (io_err->code == 0)) ? DZ1_TCP_CALLBACK_CLIENT_SENDER_SENT : DZ1_TCP_CALLBACK_CLIENT_SENDER_EXCEPTION;
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpCallbackClientMsgSent *msg = Dz1TcpCallbackClientMsgSent_new(NULL, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientMsgSent_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, code, (void **)&msg,
										(Dz1DelFunc)Dz1TcpCallbackClientMsgSent_del,
										(Dz1DumpFunc)Dz1TcpCallbackClientMsgSent_dump,
										NULL, NULL, io_err)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientMsgSent_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _tx_m_done(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

//	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
	Dz1TcpCallbackClientMsgSent *msg = (Dz1TcpCallbackClientMsgSent *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->find(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Binary *packet = Dz1SocketFifo_pop(session->tx_fifo, errp);
//		Dz1Thread_printf(">>> TX Done\n");
		if (packet != NULL) Dz1Binary_delAndSetNull(&packet);

		if ((*errp = _tx_fifo_fwd(session->tx_fifo, session->sock)).code)
		{
			Dz1Thread_printf("!!! TX Forward Fail\n");
			env->sessions->extract(env->sessions, &key);
			_session_runtime_terminate(timer, session);
			ERR_OUT(errp);
		}
	}

	return ret;
}

static Dz1TaskProcStatus _tx_m_fail(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

//	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
	Dz1TcpCallbackClientMsgSent *msg = (Dz1TcpCallbackClientMsgSent *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Thread_printf("!!! TX Fail\n");
		_session_runtime_terminate(timer, session);
	}
	return ret;
}
// Transmit Complete
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Initial
static Dz1Error _negotiate(Dz1TcpCallbackSession *node, u32_t myQueueID, bool_t useSSL)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void *_arg = (void *)DZ1_VAL2PTR32(myQueueID);
	if (useSSL == FALSE)
	{
// 		if ((*errp = Dz1TcpClientSocket_modeCallback(node->sock, node->peer, node->local, 4096,
// 													_rx_fwd, _arg, NULL,
// 													_tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
		if ((*errp = Dz1SocketCallback2_associate(node->sock, node->peer, node->local, 4096,
												  _rx_fwd, _tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if ((*errp = Dz1SocketCallback2SSL_assoClient(node->sock, node->peer, node->local, 4096,
													  _rx_fwd, _tx_cnf, _arg, NULL, Dz1SocketCallback2SSLVer_23,
													  "SEED:" DZ1_SSL_DEFAULT_CIPHER_LIST)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _alive(Dz1TcpCallbackSessionList *sessions, Dz1TcpCallbackSession *node, void *timer,
					   u32_t myQueueID, u32_t alive_sec, bool_t useSSL)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _negotiate(node, myQueueID, useSSL)).code) ERR_OUT(errp);
	else if ((*errp = _send_echo(node)).code) ERR_OUT(errp);
	else if ((*errp = sessions->add(sessions, node)).code) ERR_OUT(errp);
	else
	{
		_reg_retry_timer(timer, node);
		if (alive_sec != 0) _reg_term_timer(timer, node, alive_sec);
	}
	return err;
}

Dz1Error _connect_and_go(Dz1TcpCallbackClientArg *arg, Dz1TcpCallbackClientEnv *env, void *timer, u32_t myQueueID)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpCallbackClientCmd *cmd = env->cmd;

	Dz1SockAddr local;
	struct timeval to;
	Dz1TcpCallbackSession *node = NULL;
	Dz1TcpCallbackSessionLife life = cmd->stress_mode ? (Dz1TcpCallbackSessionLife)(rand() % Dz1TcpCallbackSessionLife_max) : Dz1TcpCallbackSessionLife_immotal0;

	Dz1Thread_printf("@@@ life = %s(%d)\n", Dz1TcpCallbackSessionLifeStr(life), life);
	if ((node = Dz1TcpCallbackSession_new(NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackSession_delAndSetNull, (void *)&node);
		to.tv_sec = 5;
		to.tv_usec = 0;
		if ((*errp = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((node->peer = Dz1SockAddr_clone(cmd->server_addr, errp)) == NULL) ERR_OUT(errp);
		else if ((node->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((node->rx_buf = Dz1SocketBuf_new(4096, errp)) == NULL) ERR_OUT(errp);
		else if ((node->tx_fifo = Dz1SocketFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((node->sock = Dz1TcpClientSocket_open(node->peer, node->local, &to, errp)) == NULL) ERR_OUT(errp);
		else
		{
			switch(life)
			{
			case Dz1TcpCallbackSessionLife_negotiationAndDie:
				if ((*errp = _negotiate(node, myQueueID, cmd->use_ssl)).code) ERR_OUT(errp);
				break;
			default:
			case Dz1TcpCallbackSessionLife_immediateDie:
				break;
			case Dz1TcpCallbackSessionLife_sendAndDie:
				if ((*errp = _negotiate(node, myQueueID, cmd->use_ssl)).code) ERR_OUT(errp);
				else if ((*errp = _send_echo(node)).code) ERR_OUT(errp);
				break;
			case Dz1TcpCallbackSessionLife_tenSecond:
				if ((*errp = _alive(env->sessions, node, timer, myQueueID, 10, cmd->use_ssl)).code) ERR_OUT(errp);
				else node = NULL;
				break;
			case Dz1TcpCallbackSessionLife_halfHour:
				if ((*errp = _alive(env->sessions, node, timer, myQueueID, 30 * 60, cmd->use_ssl)).code) ERR_OUT(errp);
				else node = NULL;
				break;
			case Dz1TcpCallbackSessionLife_immotal0:
			case Dz1TcpCallbackSessionLife_immotal1:
			case Dz1TcpCallbackSessionLife_immotal2:
			case Dz1TcpCallbackSessionLife_immotal3:
			case Dz1TcpCallbackSessionLife_immotal4:
			case Dz1TcpCallbackSessionLife_immotal5:
				if ((*errp = _alive(env->sessions, node, timer, myQueueID, 0, cmd->use_ssl)).code) ERR_OUT(errp);
				else node = NULL;
				break;
			}
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackSession_delAndSetNull, (void *)&node);
	}
	return err;
}
// Initial
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1TcpCallbackClientSocket_msgInit(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_RECEIVER_RECEIVED),		_rx_m_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_RECEIVER_DISCONNECTED),	_rx_m_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_SENDER_SENT),				_tx_m_done)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_SENDER_EXCEPTION),		_tx_m_fail)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}