#include <dz1_task.h>
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

#include <Dz1TcpCallbackClient.h>

static Dz1Error Dz1TcpCallbackClient_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer)
{
	Dz1TcpCallbackClientEnv *env = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	srand((u32_t)(time(NULL) & 0xFFFFFFFF));

	if (((*uRsc) = env = Dz1TcpCallbackClientEnv_new(tSelf, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
//		else if ((err = Dz1Task_queuePostSimple(my_queue_id, my_queue_id, DZ1_TCP_CALLBACK_CLIENT_DO_DEFAULT)).code) ERR_OUT(&err);
		else
		{
			Dz1Error_set(&err, 0);
		}
		pthread_cleanup_pop(err.code); // (Dz1TcpCallbackClientEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Dz1TcpCallbackClient_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Dz1TcpCallbackClient_cleanup(void *uRsc)
{
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
	// Individual Cleanup Code Here
	Dz1TcpCallbackClientEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
// 	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
// 	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
// 
// 	u32_t i, myQueueID = Dz1Task_getQueueID(env->tSelf);
// 	for (i = env->sessions->count(env->sessions); errp->code == 0 && i < arg->maxConnection; i++)
// 		if ((*errp = _connect_and_go(arg, env, timer, myQueueID)).code) ERR_OUT(errp);
// 	_reg_session_check(timer);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Simulate Start
static Dz1TaskProcStatus _sim_start(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;

	Dz1TcpCallbackClientCmd *msg = (Dz1TcpCallbackClientCmd *)Dz1TaskSigMsg_getData(*sg), *cmd = NULL;

	if (env->cmd != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->cmd = cmd = Dz1TcpCallbackClientCmd_clone(msg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i, myQueueID = Dz1Task_getQueueID(env->tSelf);
		for (i = env->sessions->count(env->sessions); errp->code == 0 && i < cmd->max_conn; i++)
			if ((*errp = _connect_and_go(arg, env, timer, myQueueID)).code) ERR_OUT(errp);
		_reg_session_check(timer);
	}
	return ret;
}

Dz1Error Dz1TcpCallbackClient_simulate_start(void *task, Dz1SockAddr *server, u32_t maxConnection, bool_t use_ssl, bool_t stress_mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1TcpCallbackClientCmd *msg = Dz1TcpCallbackClientCmd_new(NULL, maxConnection, use_ssl, stress_mode, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&msg);
		if ((msg->server_addr = Dz1SockAddr_clone(server, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE,
									DZ1_TCP_CALLBACK_CLIENT_USER_SIM_START, (void **)&msg,
									(Dz1DelFunc)Dz1TcpCallbackClientCmd_del,
									(Dz1DumpFunc)Dz1TcpCallbackClientCmd_dump,
									NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&msg);
	}
	return err;
}
// Simulate Start
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Simulate Stop
static __inline__ Dz1TaskProcStatus _sim_stop(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
	if (env->cmd == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1TcpCallbackSessionList *list = env->sessions;
		Dz1TcpCallbackSession *node = NULL;
		
		pthread_cleanup_push(Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&env->cmd);
		while((node = list->getHead(list)) != NULL)
		{
			list->extract(list, node);
			_session_runtime_terminate(timer, node);
			node = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientCmd_delAndSetNull, (void *)&env->cmd);
	}
	return ret;
}

Dz1Error Dz1TcpCallbackClient_simulate_stop(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1Task_callSimple(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_CALLBACK_CLIENT_USER_SIM_STOP, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Simulate Start
///////////////////////////////////////////////////////////////////////////////

void *Dz1TcpCallbackClient_new(Dz1TcpCallbackClientException exceptionProc, void *exceptionArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpCallbackClientArg *arg = NULL;
	
	if (0) { }
	else if ((arg = Dz1TcpCallbackClientArg_new(exceptionProc, exceptionArg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Dz1TcpCallbackClient", 1024,
							   (void **)&arg, (Dz1DelFunc)Dz1TcpCallbackClientArg_del,
							   (Dz1CmpFunc)Dz1TcpCallbackClientTimer_cmp,
							   Dz1TcpCallbackClient_init,
							   Dz1TcpCallbackClient_exception,
							   Dz1TcpCallbackClient_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_CLIENT_USER_SIM_START), _sim_start)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpCallbackClientSocket_msgInit(ret)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Dz1TcpCallbackClient_del(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (task == NULL) return;
	else if ((err = Dz1Task_del(task)).code) ERR_OUT(&err);
}

