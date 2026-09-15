#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif

#include "dz1_tcp_socket_server_task_env.h"

#include "dz1_tcp_socket_server_task.h"
#include "dz1_tcp_socket_server_msg.h"

#include "dz1_tcp_socket_server_acceptor.h"
#include "dz1_tcp_socket_server_receiver.h"

#define SOCKET_NATIVE			0
#define SOCKET_CALLBACK			1
#define SOCKET_CALLBACK_SSL		2
//#define SOCKET_MODE				SOCKET_NATIVE
#define SOCKET_MODE				SOCKET_CALLBACK
//#define SOCKET_MODE				SOCKET_CALLBACK_SSL

#if (SOCKET_MODE != SOCKET_NATIVE)
static Dz1Error ReceiverEntry_fwd(ReceiverEntry *p)
{
	ssize_t status = 0;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary const * const bin = Dz1SocketFifo_peek(p->tx, errp);
	if (bin == NULL) ERR_OUT(errp);
	else if ((status = p->sock->send(p->sock, bin->data, bin->size, DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, errp)) < 0) ERR_OUT(errp);
	else if (status == 0) ERR_SET_OUT(errp, EPIPE);
	return err;
}

static Dz1Error ReceiverEntry_send(ReceiverEntry *p, Dz1Binary **bin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	bool_t doSend = Dz1SocketFifo_count(p->tx) == 0 ? TRUE : FALSE;
	if ((*errp = Dz1SocketFifo_push(p->tx, bin)).code) ERR_OUT(errp);
	else if (doSend)
	{
		if ((*errp = ReceiverEntry_fwd(p)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error ReceiverEntry_continue(ReceiverEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary *bin = Dz1SocketFifo_pop(p->tx, errp);
	if (bin != NULL) Dz1Binary_delAndSetNull(&bin);

	if (Dz1SocketFifo_count(p->tx) > 0)
	{
		if ((err = ReceiverEntry_fwd(p)).code) ERR_OUT(errp);
	}
	return err;
}
#endif

///////////////////////////////////////
// Time Entry
///////////////////////////////////////
typedef struct Dz1TcpSocketServerTaskTimer
{
	u32_t id;
} Dz1TcpSocketServerTaskTimer;

static int Dz1TcpSocketServerTaskTimer_cmp(Dz1TcpSocketServerTaskTimer *a, Dz1TcpSocketServerTaskTimer *b)
{
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (a->id < b->id) return -1;
	else if (a->id > b->id) return 1;
	else return 0;
}


///////////////////////////////////////
// Receiver Entry Helper
///////////////////////////////////////
static void ReceiverEntry_cleanup(ReceiverEntry *p)
{
	if (p == NULL) return;
	if (p->rcvr != (u32_t)-1) { Dz1TcpSocketServerReceiver_stop(p->rcvr); p->rcvr = -1; }
	if (p->sock != NULL) Dz1TcpClientSocket_closeAndSetNull(&p->sock);
}

static void ReceiverEntry_cleanupAndDel(void *ptr)
{
	ReceiverEntry *p = (ReceiverEntry *)ptr;
	ReceiverEntry_cleanup(p);
	ReceiverEntry_del(p);
}

static void ReceiverEntry_cleanupAndSetNull(void *ptr)
{
	ReceiverEntry **p = (ReceiverEntry **)ptr;
	ReceiverEntry_cleanupAndDel(*p); *p = NULL;
}

static Dz1Error _ReceiverList_cleanup(void *ptr, ReceiverEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ReceiverEntry_cleanup(p);
	return err;
}

static void ReceiverList_cleanup(ReceiverList *list)
{
	list->travel(list, _ReceiverList_cleanup, NULL);
}


///////////////////////////////////////
// Acceptor Entry Helper
///////////////////////////////////////
static void AcceptorEntry_cleanup(AcceptorEntry *p)
{
	if (p == NULL) return;
	if (p->acceptor != (u32_t)-1) { Dz1TcpSocketServerAcceptor_stop(p->acceptor); p->acceptor = -1; }
}

static Dz1Error _AcceptorList_cleanup(void *ptr, AcceptorEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	AcceptorEntry_cleanup(p);
	return err;
}

static void AcceptorList_cleanup(AcceptorList *list)
{
	list->travel(list, _AcceptorList_cleanup, NULL);
}

///////////////////////////////////////
// INIT
///////////////////////////////////////
static Dz1Error Dz1TcpSocketServerTask_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1TcpSocketServerTaskEnv *env = NULL;

	if (( (*uRsc) = env = Dz1TcpSocketServerTaskEnv_new(tSelf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

///////////////////////////////////////
// CLEANUP
///////////////////////////////////////
static void Dz1TcpSocketServerTask_cleanup(void *uRsc)
{
	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;

	if (env->receivers) ReceiverList_cleanup(env->receivers);
	ReceiverList_delAndSetNull(&env->receivers);

	if (env->acceptors) AcceptorList_cleanup(env->acceptors);
	AcceptorList_delAndSetNull(&env->acceptors);

	Dz1TcpSocketServerTaskEnv_del(env);
}

///////////////////////////////////////
// EXCEPTION
///////////////////////////////////////
static void Dz1TcpSocketServerTask_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1Thread_printf("!!! Dz1TcpSocketServerTask() : Exception\n");
	ERR_OUT(reason);
}

///////////////////////////////////////
// Acceptor Connected Message Proc
///////////////////////////////////////
#if (SOCKET_MODE != SOCKET_NATIVE)
static void rx_fwd(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, u8_t *data, size_t size, Dz1Error *errp)
{
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpSocketServerReceived *msg = Dz1TcpSocketServerReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (data != NULL || size != 0)
			{
				if ((msg->pkt = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
												DZ1_TCP_SOCKET_SERVER_RECEIVER_RECEIVED, (void **)&msg,
												(Dz1DelFunc)Dz1TcpSocketServerReceived_del,
												(Dz1DumpFunc)Dz1TcpSocketServerReceived_dump,
												errp, NULL, NULL)).code) ERR_OUT(errp);
			}
			else
			{
				if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
												DZ1_TCP_SOCKET_SERVER_RECEIVER_DISCONNECTED, (void **)&msg,
												(Dz1DelFunc)Dz1TcpSocketServerReceived_del,
												(Dz1DumpFunc)Dz1TcpSocketServerReceived_dump,
												NULL, NULL, NULL)).code) ERR_OUT(errp);
			}
		}
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerReceived_delAndSetNull, (void *)&msg);
	}
}

static void tx_cnf(void *cb_param, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *errp)
{
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(cb_param);
	Dz1TcpSocketServerReceived *msg = Dz1TcpSocketServerReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, 
										DZ1_TCP_SOCKET_SERVER_RECEIVER_TRANSFERED, (void **)&msg,
										(Dz1DelFunc)Dz1TcpSocketServerReceived_del,
										(Dz1DumpFunc)Dz1TcpSocketServerReceived_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerReceived_delAndSetNull, (void *)&msg);
	}
}
#endif

static Dz1TaskProcStatus _m_connected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);
#if (SOCKET_MODE != SOCKET_NATIVE)
	void *_arg = (void *)DZ1_VAL2PTR32(myQueueID);
#endif

	Dz1TcpSocketServerConnected *msg = (Dz1TcpSocketServerConnected *)Dz1TaskSigMsg_getData(*sg);

	ReceiverEntry key = { msg->peer, msg->local }, *node = env->receivers->find(env->receivers, &key);
	if (node == NULL)
	{
		if ((node = ReceiverEntry_new(msg->peer, msg->local, msg->sock, -1, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			msg->sock = NULL;
			msg->peer = msg->local = NULL;
			pthread_cleanup_push(ReceiverEntry_cleanupAndSetNull, (void *)&node);
			if ((node->tx = Dz1SocketFifo_new(errp)) == NULL) ERR_OUT(errp);
#if (SOCKET_MODE == SOCKET_NATIVE)
			else if ((node->rcvr = Dz1TcpSocketServerReceiver_start(myQueueID, node->peer, node->local, node->sock, errp)) == -1) ERR_OUT(errp);
#elif (SOCKET_MODE == SOCKET_CALLBACK)
// 			else if ((*errp = Dz1TcpClientSocket_modeCallback(node->sock, node->peer, node->local,
// 															  4096,
// 															  rx_fwd, _arg, NULL,
// 															  tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SocketCallback2_associate(node->sock, node->peer, node->local, 4096,
														   rx_fwd, tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
#elif (SOCKET_MODE == SOCKET_CALLBACK_SSL)
#ifdef _DZ1_USE_SSL
			else if ((*errp = Dz1TcpClientSocket_modeSSLServer(node->sock, node->peer, node->local,
														  4096,
														  rx_fwd, _arg, NULL,
														  tx_cnf, _arg, NULL,
														  Dz1TcpClientSocketSSLServerMode_v3, "xxx.crt", "xxx.key")).code) ERR_OUT(errp);
#else
#error "Choose SSL Build Mode or change SOCKET_MODE to non SSL"
#endif
#endif
			else if ((*errp = env->receivers->add(env->receivers, node)).code) ERR_OUT(errp);
			else node = NULL;
			pthread_cleanup_pop(1); // (ReceiverEntry_delAndSetNull, (void *)&node);
		}
	}

	return ret;
}

static Dz1TaskProcStatus _m_connected2(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);
#if (SOCKET_MODE != SOCKET_NATIVE)
	void *_arg = (void *)DZ1_VAL2PTR32(myQueueID);
#endif

	Dz1TcpSocketServerConnected *msg = (Dz1TcpSocketServerConnected *)Dz1TaskSigMsg_getData(*sg);

	ReceiverEntry key = { msg->peer, msg->local }, *node = env->receivers->find(env->receivers, &key);
	if (node == NULL)
	{
		if ((node = ReceiverEntry_new(msg->peer, msg->local, msg->sock, -1, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			msg->sock = NULL;
			msg->peer = msg->local = NULL;
			pthread_cleanup_push(ReceiverEntry_cleanupAndSetNull, (void *)&node);

			if ((node->tx = Dz1SocketFifo_new(errp)) == NULL) ERR_OUT(errp);
#if (SOCKET_MODE == SOCKET_NATIVE)
			else if ((node->rcvr = Dz1TcpSocketServerReceiver_start(myQueueID, node->peer, node->local, node->sock, errp)) == -1) ERR_OUT(errp);
#elif (SOCKET_MODE == SOCKET_CALLBACK)
// 			else if ((*errp = Dz1TcpClientSocket_modeCallback(node->sock, node->peer, node->local,
// 															  4096,
// 															  rx_fwd, _arg, NULL,
// 															  tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SocketCallback2_associate(node->sock, node->peer, node->local, 4096,
														   rx_fwd, tx_cnf, _arg, NULL)).code) ERR_OUT(errp);
#elif (SOCKET_MODE == SOCKET_CALLBACK_SSL)
#ifdef _DZ1_USE_SSL
			else if ((*errp = Dz1TcpClientSocket_modeSSLServer(node->sock, node->peer, node->local,
														  4096,
														  rx_fwd, _arg, NULL,
														  tx_cnf, _arg, NULL,
														  Dz1TcpClientSocketSSLServerMode_v3, "xxx.crt", "xxx.key")).code) ERR_OUT(errp);
#else
#error "Choose SSL Build Mode or change SOCKET_MODE to non SSL"
#endif
#endif
			pthread_cleanup_pop(1); // (ReceiverEntry_delAndSetNull, (void *)&node);
		}
	}

	return ret;
}

///////////////////////////////////////
// Acceptor Exception Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_exception(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1Thread_printf("!!! Socket Acceptor Fault\n");
	return Dz1TaskProcStatus_error;
}

///////////////////////////////////////
// User Open Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_open(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1TcpSocketServerOpen *msg = (Dz1TcpSocketServerOpen *)Dz1TaskSigMsg_getData(*sg);

	Dz1SockAddr addr;
	AcceptorEntry key = { msg->port }, *node = env->acceptors->find(env->acceptors, &key);
	
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((*errp = Dz1SockAddr_setAddrStr(&addr, "0.0.0.0")).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&addr, msg->port)).code) ERR_OUT(errp);
	else if ((node = AcceptorEntry_new(msg->port, -1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(AcceptorEntry_delAndSetNull, (void *)&node);
		if ((node->acceptor = Dz1TcpSocketServerAcceptor_start(myQueueID, &addr, errp)) == (u32_t)-1) ERR_OUT(errp);
		else if ((*errp = env->acceptors->add(env->acceptors, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (AcceptorEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1Error Dz1TcpSocketServerTask_open(void *task, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSocketServerOpen *msg = Dz1TcpSocketServerOpen_new(port, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SOCKET_SERVER_USER_OPEN,
							(void *)msg, (Dz1DumpFunc)Dz1TcpSocketServerOpen_dump, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////
// User Open2 Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_open2(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1TcpSocketServerOpen *msg = (Dz1TcpSocketServerOpen *)Dz1TaskSigMsg_getData(*sg);

	Dz1SockAddr addr;
	AcceptorEntry key = { msg->port }, *node = env->acceptors->find(env->acceptors, &key);
	
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((*errp = Dz1SockAddr_setAddrStr(&addr, "0.0.0.0")).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&addr, msg->port)).code) ERR_OUT(errp);
	else if ((node = AcceptorEntry_new(msg->port, -1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(AcceptorEntry_delAndSetNull, (void *)&node);
		if ((node->acceptor = Dz1TcpSocketServerAcceptor2_start(myQueueID, &addr, errp)) == (u32_t)-1) ERR_OUT(errp);
		else if ((*errp = env->acceptors->add(env->acceptors, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (AcceptorEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1Error Dz1TcpSocketServerTask_open2(void *task, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSocketServerOpen *msg = Dz1TcpSocketServerOpen_new(port, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SOCKET_SERVER_USER_OPEN2,
							(void *)msg, (Dz1DumpFunc)Dz1TcpSocketServerOpen_dump, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////
// User Open2 Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_open3(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1TcpSocketServerOpen *msg = (Dz1TcpSocketServerOpen *)Dz1TaskSigMsg_getData(*sg);

	Dz1SockAddr addr;
	AcceptorEntry key = { msg->port }, *node = env->acceptors->find(env->acceptors, &key);
	
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((*errp = Dz1SockAddr_setAddrStr(&addr, "0.0.0.0")).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&addr, msg->port)).code) ERR_OUT(errp);
	else if ((node = AcceptorEntry_new(msg->port, -1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(AcceptorEntry_delAndSetNull, (void *)&node);
		if ((node->acceptor = Dz1TcpSocketServerAcceptor3_start(myQueueID, &addr, errp)) == (u32_t)-1) ERR_OUT(errp);
		else if ((*errp = env->acceptors->add(env->acceptors, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (AcceptorEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1Error Dz1TcpSocketServerTask_open3(void *task, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSocketServerOpen *msg = Dz1TcpSocketServerOpen_new(port, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SOCKET_SERVER_USER_OPEN3,
							(void *)msg, (Dz1DumpFunc)Dz1TcpSocketServerOpen_dump, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////
// User Close Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_close(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	//u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1TcpSocketServerOpen *msg = (Dz1TcpSocketServerOpen *)Dz1TaskSigMsg_getData(*sg);

	AcceptorEntry key = { msg->port }, *node = env->acceptors->extract(env->acceptors, &key);
	
	if (node == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		pthread_cleanup_push(AcceptorEntry_delAndSetNull, (void *)&node);

		AcceptorEntry_cleanup(node);

		pthread_cleanup_pop(1); // (AcceptorEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1Error Dz1TcpSocketServerTask_close(void *task, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSocketServerOpen *msg = Dz1TcpSocketServerOpen_new(port, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SOCKET_SERVER_USER_CLOSE,
							(void *)msg, (Dz1DumpFunc)Dz1TcpSocketServerOpen_dump, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpSocketServerOpen_delAndSetNull, (void *)&msg);
	}
	return err;
}

///////////////////////////////////////
// User Status Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_status(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;

	Dz1Thread_printf("Status = ");
	Dz1TcpSocketServerTaskEnv_dump(env, 0);

	return ret;
}

Dz1Error Dz1TcpSocketServerTask_status(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1Task_callSimple(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SOCKET_SERVER_USER_STATUS, NULL)).code) ERR_OUT(&err);
	return err;
}

#if (SOCKET_MODE != SOCKET_NATIVE)
///////////////////////////////////////
// Receiver Received Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_received(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	Dz1TcpSocketServerReceived *msg = (Dz1TcpSocketServerReceived *)Dz1TaskSigMsg_getData(*sg);
	ReceiverEntry key = { msg->peer, msg->local }, *node = env->receivers->find(env->receivers, &key);

	if (node != NULL)
	{
		if ((*errp = ReceiverEntry_send(node, &msg->pkt)).code) ERR_OUT(errp);
	}

	return ret;
}

static Dz1TaskProcStatus _m_sent(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;
	Dz1TcpSocketServerReceived *msg = (Dz1TcpSocketServerReceived *)Dz1TaskSigMsg_getData(*sg);
	ReceiverEntry key = { msg->peer, msg->local }, *node = env->receivers->find(env->receivers, &key);

	if (node != NULL)
	{
		if ((*errp = ReceiverEntry_continue(node)).code) ERR_OUT(errp);
	}

	return ret;
}
#endif
///////////////////////////////////////
// Receiver Disconnected Message Proc
///////////////////////////////////////
static Dz1TaskProcStatus _m_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSocketServerTaskEnv *env = (Dz1TcpSocketServerTaskEnv *)uRsc;

	Dz1TcpSocketServerReceived *msg = (Dz1TcpSocketServerReceived *)Dz1TaskSigMsg_getData(*sg);
	ReceiverEntry key = { msg->peer, msg->local }, *node = env->receivers->extract(env->receivers, &key);
	if (node != NULL)
	{
		pthread_cleanup_push(ReceiverEntry_delAndSetNull, (void *)&node);
		ReceiverEntry_cleanup(node);
		pthread_cleanup_pop(1); // (ReceiverEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

void *Dz1TcpSocketServerTask_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	void *ret = NULL;;

	if ((ret = Dz1Task_new("Dz1TcpSocketServer", 64,
							NULL, NULL,
							(Dz1CmpFunc)Dz1TcpSocketServerTaskTimer_cmp,
							Dz1TcpSocketServerTask_init,
							Dz1TcpSocketServerTask_exception,
							Dz1TcpSocketServerTask_cleanup,
							errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
		if		((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_ACCEPTOR_CONNECTED), _m_connected)).code) ERR_OUT(errp);
		else if	((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_ACCEPTOR_CONNECTED2), _m_connected2)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_ACCEPTOR_EXCEPTION), _m_exception)).code) ERR_OUT(errp);
#if (SOCKET_MODE != SOCKET_NATIVE)
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_RECEIVER_RECEIVED), _m_received)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_RECEIVER_TRANSFERED), _m_sent)).code) ERR_OUT(errp);
#endif
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_RECEIVER_DISCONNECTED), _m_disconnected)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_USER_OPEN), _m_open)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_USER_OPEN2), _m_open2)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_USER_OPEN3), _m_open3)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_USER_CLOSE), _m_close)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SOCKET_SERVER_USER_STATUS), _m_status)).code) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
	}
	return ret;
}
