#include <dz1_socket_acceptor.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif

#include "Dz1TcpCallbackServerEnvUtil.h"
#include "Dz1TcpCallbackServerTimerUtil.h"
#include "Dz1TcpCallbackServerMsg.h"

#include "Dz1TcpCallbackServerSocket.h"

///////////////////////////////////////////////////////////////////////////////
// Received
static __inline__ void _rx_fwd(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *io_err)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpCallbackServerMsgReceived *msg = NULL;
	
//	Dz1Thread_printf("_rx_fwd() = %u\n", size);
	if ((msg = Dz1TcpCallbackServerMsgReceived_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if (data == NULL || size == 0)
		{
			if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
								DZ1_TCP_CALLBACK_SERVER_RECEIVER_DISCONNECTED, (void **)&msg,
								(Dz1DelFunc)Dz1TcpCallbackServerMsgReceived_del,
								(Dz1DumpFunc)Dz1TcpCallbackServerMsgReceived_dump,
								NULL, NULL, io_err)).code) ERR_OUT(errp);
		}
		else if ((msg->packet = Dz1Binary_new(data, size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
								DZ1_TCP_CALLBACK_SERVER_RECEIVER_RECEIVED, (void **)&msg,
								(Dz1DelFunc)Dz1TcpCallbackServerMsgReceived_del,
								(Dz1DumpFunc)Dz1TcpCallbackServerMsgReceived_dump,
								NULL, NULL, NULL)).code) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerMsgReceived_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _rx_m_received(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpCallbackServerArg *arg = (Dz1TcpCallbackServerArg *)uArg;
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	Dz1TcpCallbackServerMsgReceived *msg = (Dz1TcpCallbackServerMsgReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1Binary *packet = msg->packet;

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = NULL;

//	Dz1Thread_printf("<<< RX = %u\n", packet->size);
	env->rx_amt += packet->size;

	if ((session = env->sessions->find(env->sessions, &key)) != NULL)
	{
		ssize_t sz = 0;
		Dz1SocketBuf *buf = session->rx_buf;
		if ((sz = Dz1SocketBuf_push(buf, packet->data, packet->size, errp)) < 0)
		{
			env->sessions->extract(env->sessions, &key);
			Dz1TcpCallbackSession_del(session);
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
			
			if ((*errp = _decode_and_process(arg, env, timer, session, buf)).code)
			{
				env->sessions->extract(env->sessions, &key);
				Dz1TcpCallbackSession_del(session);
				ERR_OUT(errp);
			}
		}
	}
	return ret;
}

static Dz1TaskProcStatus _rx_m_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

//	Dz1TcpCallbackServerArg *arg = (Dz1TcpCallbackServerArg *)uArg;
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	Dz1TcpCallbackServerMsgReceived *msg = (Dz1TcpCallbackServerMsgReceived *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1TcpCallbackSession_delAndSetNull(&session);
	}
	return ret;
}
// Received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Transmit Complete
static __inline__ void _tx_cnf(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *io_err)
{	// callback
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t code = ((io_err == NULL) || (io_err->code == 0)) ? DZ1_TCP_CALLBACK_SERVER_SENDER_SENT : DZ1_TCP_CALLBACK_SERVER_SENDER_EXCEPTION;
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpCallbackServerMsgSent *msg = NULL;
	
//	Dz1Thread_printf("_tx_cnf() : Called\n");
	if ((msg = Dz1TcpCallbackServerMsgSent_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerMsgSent_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, code, (void **)&msg,
											(Dz1DelFunc)Dz1TcpCallbackServerMsgSent_del,
											(Dz1DumpFunc)Dz1TcpCallbackServerMsgSent_dump,
											NULL, NULL, io_err)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerMsgSent_delAndSetNull, (void *)&msg);
	}
}
static Dz1TaskProcStatus _tx_m_done(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	Dz1TcpCallbackServerMsgSent *msg = (Dz1TcpCallbackServerMsgSent *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->find(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Binary *packet = NULL;
//		Dz1Thread_printf(">>> TX Done\n");
		if ((packet = Dz1SocketFifo_pop(session->tx_fifo, errp)) != NULL)
		{
			env->tx_amt += packet->size;
			Dz1Binary_delAndSetNull(&packet);
		}

		if ((*errp = _tx_fifo_fwd(session->tx_fifo, session->sock)).code)
		{
			env->sessions->extract(env->sessions, &key);
			Dz1TcpCallbackSession_del(session);
			ERR_OUT(errp);
		}
	}

	return ret;
}

static Dz1TaskProcStatus _tx_m_fail(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	Dz1TcpCallbackServerMsgSent *msg = (Dz1TcpCallbackServerMsgSent *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1TcpCallbackSession_delAndSetNull(&session);
	}
	return ret;
}
// Transmit Complete
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Accept Socket
static Dz1TcpSocketAcceptorBehavior _acceptor_fwd(void *uArg, void *uRsc,
												 Dz1TcpClientSocket **s,
												 Dz1SockAddr *local, Dz1SockAddr *peer,
												 Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(uArg);
	Dz1TcpCallbackServerMsgConnected *msg = Dz1TcpCallbackServerMsgConnected_new(NULL, NULL, *s, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		*s = NULL;
		pthread_cleanup_push(Dz1TcpCallbackServerMsgConnected_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_CALLBACK_SERVER_ACCEPTOR_CONNECTED, (void **)&msg,
											(Dz1DelFunc)Dz1TcpCallbackServerMsgConnected_del,
											(Dz1DumpFunc)Dz1TcpCallbackServerMsgConnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerMsgConnected_delAndSetNull, (void *)&msg);
	}
	return ret;
}

typedef struct SessionAddCancelArg
{
	Dz1TcpCallbackSessionList *list;
	Dz1TcpCallbackSession *node;
} SessionAddCancelArg;

static void _session_add_cancel(void *ptr)
{
	SessionAddCancelArg *arg = (SessionAddCancelArg *)ptr;
	arg->list->extract(arg->list, arg->node);
}

static Dz1TcpCallbackSession *_register_session(Dz1TcpCallbackSessionList *dst,
												Dz1TcpCallbackServerMsgConnected *msg,
												u32_t myQueueID, bool_t isNATIVE, Dz1Error *errp)
{
	Dz1TcpCallbackSession *ret = NULL, *node = NULL;
	if ((node = Dz1TcpCallbackSession_new(msg->peer, msg->local, msg->sock, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		
		msg->sock = NULL;
		msg->peer = msg->local = NULL;
		pthread_cleanup_push(Dz1TcpCallbackSession_delAndSetNull, (void *)&node);

		if ((node->rx_buf = Dz1SocketBuf_new(4096, errp)) == NULL) ERR_OUT(errp);
		else if ((node->tx_fifo = Dz1SocketFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			void *_arg = (void *)DZ1_VAL2PTR32(myQueueID);
			SessionAddCancelArg _add_cancel_arg = { dst, node };
			pthread_cleanup_push(_session_add_cancel, (void *)&_add_cancel_arg);
			if (isNATIVE)
			{
// 				if ((*errp = Dz1TcpClientSocket_modeCallback(node->sock, node->peer, node->local, 4096,
// 															 _rx_fwd, _arg, NULL,
// 															 _tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
				if ((*errp = Dz1SocketCallback2_associate(node->sock, node->peer, node->local, 4096,
														  _rx_fwd, _tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
				else
				{
					ret = node;
					node = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			else
			{
#ifdef _DZ1_USE_SSL

#ifdef WIN32
#define CERT_PATH			"..\\cert\\"
#else
#define CERT_PATH			"project/cert/"
#endif

// 				if ((*errp = Dz1TcpClientSocket_modeSSLServer(node->sock, node->peer, node->local, 4096,
// 															  _rx_fwd, _arg, NULL,
// 															  _tx_cnf, _arg, NULL,
// 															  Dz1TcpClientSocketSSLServerMode_v3,
// 															  CERT_PATH "xxx.crt",
// 															  CERT_PATH "xxx.key"
// 															  )).code) { /* ERR_OUT(errp); */ }
				if ((*errp = Dz1SocketCallback2SSL_assoServer(node->sock, node->peer, node->local, 4096,
															  _rx_fwd, _tx_cnf, _arg, NULL,
															  Dz1SocketCallback2SSLVer_23,
															  CERT_PATH "xxx.crt",
															  CERT_PATH "xxx.key")).code) ERR_OUT(errp);
				else
				{
					ret = node;
					node = NULL;
					Dz1Error_set(errp, 0);
				}
#else
				ERR_SET_OUT(errp, ENOSYS);
#endif
			}
			pthread_cleanup_pop(errp->code); // (_session_add_cancel, (void *)&_add_cancel_arg);
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackSession_delAndSetNull, (void *)&node);
	}
	return ret;
}

static Dz1TaskProcStatus _acceptor_m_fwd(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpCallbackServerArg *arg = (Dz1TcpCallbackServerArg *)uArg;
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);
	Dz1TcpCallbackServerMsgConnected *msg = (Dz1TcpCallbackServerMsgConnected *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpCallbackSession key = { msg->peer, msg->local }, *node = env->sessions->find(env->sessions, &key);
	if (node == NULL)
	{
		void *_arg = (void *)DZ1_VAL2PTR32(myQueueID);

		u16_t local_port = 0;		
		bool_t isNATIVE = FALSE;

#ifdef _DZ1_USE_SSL
		bool_t isSSL = FALSE;
#endif

		if ((*errp = Dz1SockAddr_getPort(msg->local, &local_port)).code) ERR_OUT(errp);
		else if ((isNATIVE = (local_port == arg->port)) == FALSE &&
#ifdef _DZ1_USE_SSL
				 (isSSL = (local_port == arg->port + 1)) == FALSE &&
#endif
				 TRUE) { }
		else
		{
// 			Dz1TcpCallbackSessionLife life = (Dz1TcpCallbackSessionLife)(rand() % Dz1TcpCallbackSessionLife_max);
			Dz1TcpCallbackSessionLife life = Dz1TcpCallbackSessionLife_immotal0;
// 			Dz1Thread_printf("@@@ life = %s(%d)\n", Dz1TcpCallbackSessionLifeStr(life), life);
			switch(life)
			{
			case Dz1TcpCallbackSessionLife_negotiateAndDie:
				if (isNATIVE)
				{
// 					if ((*errp = Dz1TcpClientSocket_modeCallback(msg->sock, msg->peer, msg->local, 4096,
// 																 _rx_fwd, _arg, NULL,
// 																 _tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
					if ((*errp = Dz1SocketCallback2_associate(msg->sock, msg->peer, msg->local, 4096,
															  _rx_fwd, _tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
				}
#ifdef _DZ1_USE_SSL
				else if (isSSL)
				{
					if ((*errp = Dz1SocketCallback2SSL_assoServer(node->sock, node->peer, node->local, 4096,
																  _rx_fwd, _tx_cnf, _arg, NULL,
																  Dz1SocketCallback2SSLVer_23,
																  CERT_PATH "xxx.crt",
																  CERT_PATH "xxx.key")).code) ERR_OUT(errp);
				}
#endif
			default:
			case Dz1TcpCallbackSessionLife_immediateDie:
				break;
			case Dz1TcpCallbackSessionLife_tenSeconds:
				if ((node = _register_session(env->sessions, msg, myQueueID, isNATIVE, errp)) == NULL) { /* ERR_OUT(errp); */ }
				else if ((*errp = _reg_session_term_timer(timer, node, 10)).code) ERR_OUT(errp);
				break;
			case Dz1TcpCallbackSessionLife_halfHour:
				if ((node = _register_session(env->sessions, msg, myQueueID, isNATIVE, errp)) == NULL) { /* ERR_OUT(errp); */ }
				else if ((*errp = _reg_session_term_timer(timer, node, 60 * 30)).code) ERR_OUT(errp);
				break;
			case Dz1TcpCallbackSessionLife_immotal0:
			case Dz1TcpCallbackSessionLife_immotal1:
			case Dz1TcpCallbackSessionLife_immotal2:
			case Dz1TcpCallbackSessionLife_immotal3:
			case Dz1TcpCallbackSessionLife_immotal4:
				if ((node = _register_session(env->sessions, msg, myQueueID, isNATIVE, errp)) == NULL) { /* ERR_OUT(errp); */ }
				break;
			}
		}
	}
	return ret;
}
// Accept Socket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Acceptor Exception
static void _acceptor_exception(void *uArg, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason)
{
}
// Acceptor Exception
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Acceptor
u32_t Dz1TcpCallbackServerAcceptor_start(u32_t parent_queue_id, u16_t port, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockAddr local;
	Dz1TcpServerSocket *sock = NULL;
	if (0) { }
	else if ((*errp = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&local, port)).code) ERR_OUT(errp);
	else if ((sock = Dz1TcpServerSocket_open(&local, NULL, 5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		void *_arg = (void *)DZ1_VAL2PTR32(parent_queue_id);
		pthread_cleanup_push(Dz1TcpServerSocket_closeAndSetNull, (void *)&sock);
		if ((ret = Dz1TcpSocketAcceptor_start(sock, TRUE, 0, 0,
											  NULL,
											  _acceptor_fwd,
											  _acceptor_exception,
											  NULL,
											  NULL,
											  &_arg, NULL, errp)) == -1) ERR_OUT(errp);
		else
		{
			sock = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpServerSocket_closeAndSetNull, (void *)&sock);
	}
	return ret;
}

void Dz1TcpCallbackServerAcceptor_stop(u32_t id)
{
	if (id != -1)
	{
		Dz1TcpSocketAcceptor_stop(id);
		id = -1;
	}
}
// Acceptor
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1TcpCallbackServerSocketMsg_init(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_ACCEPTOR_CONNECTED),		_acceptor_m_fwd)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_RECEIVER_RECEIVED),		_rx_m_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_RECEIVER_DISCONNECTED),	_rx_m_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_SENDER_SENT),				_tx_m_done)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_SENDER_EXCEPTION),		_tx_m_fail)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
