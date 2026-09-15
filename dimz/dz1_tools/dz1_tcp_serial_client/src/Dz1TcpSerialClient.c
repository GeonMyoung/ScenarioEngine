#include <dz1_task.h>

#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientTimerUtil.h"
#include "Dz1TcpSerialClientMsg.h"

#include "Dz1TcpSerialClient.h"

static Dz1Error Dz1TcpSerialClient_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (((*uRsc) = env = Dz1TcpSerialClientEnv_new(tSelf, NULL, -1, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1TimeVal to = { 5, 0 };
		Dz1SockAddr local;
		pthread_cleanup_push(Dz1TcpSerialClientEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
		else if ((env->rxBuf = Dz1SocketBuf_new(4096, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((env->sock = Dz1TcpClientSocket_open(arg->serverAddr, &local, &to, errp)) == NULL) ERR_OUT(errp);
		else if ((env->rcvr = Dz1TcpSerialClientReceiver_start(arg->serverAddr, &local, env->sock, my_queue_id, errp)) == -1) ERR_OUT(errp);
		else
		{
			Dz1Error_set(&err, 0);
		}
		pthread_cleanup_pop(err.code); // (Dz1TcpSerialClientEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Dz1TcpSerialClient_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Dz1TcpSerialClient_cleanup(void *uRsc)
{
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	// Individual Cleanup Code Here
	Dz1TcpSerialClientEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

void *Dz1TcpSerialClient_new(Dz1SockAddr *serverAddr, Dz1TcpSerialClientException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialClientArg *arg = Dz1TcpSerialClientArg_new(NULL, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientArg_delAndSetNull, (void *)&arg);

		if ((arg->serverAddr = Dz1SockAddr_clone(serverAddr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1Task_new("Dz1TcpSerialClient", 1024,
								   (void **)&arg, (Dz1DelFunc)Dz1TcpSerialClientArg_del,
								   (Dz1CmpFunc)Dz1TcpSerialClientTimer_cmp,
								   Dz1TcpSerialClient_init,
								   Dz1TcpSerialClient_exception,
								   Dz1TcpSerialClient_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_OPEN), Dz1TcpSerialClient_m_open)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_CLOSE), Dz1TcpSerialClient_m_close)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_SET_RTS), Dz1TcpSerialClient_m_setRTS)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_SET_DTR), Dz1TcpSerialClient_m_setDTR)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_GET_DSR), Dz1TcpSerialClient_m_getDSR)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_GET_CTS), Dz1TcpSerialClient_m_getCTS)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_WRITE), Dz1TcpSerialClient_m_write)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_WRITE_DONE), Dz1TcpSerialClient_m_writeDone)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_SET_BYTE_CONSUME), Dz1TcpSerialClient_m_setByteConsume)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_DISCONNECTED), Dz1TcpSerialClient_m_disconnected)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_CLIENT_RECEIVED), Dz1TcpSerialClient_m_recv)).code) ERR_OUT(errp);

			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialClientArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Dz1TcpSerialClient_del(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (task == NULL) return;
	else if ((err = Dz1Task_del(task)).code) ERR_OUT(&err);
}
