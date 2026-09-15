#include <dz1_task.h>
#include <dz1_task_timer.h>
#include <dz1_usleep.h>

#include <dz1_socket_acceptor.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif
#include <Dz1TcpCallbackMsgCodec.h>

#include "Dz1TcpCallbackServerArg.h"
#include "Dz1TcpCallbackServerEnvUtil.h"
#include "Dz1TcpCallbackServerTimer.h"
#include "Dz1TcpCallbackServerMsg.h"

#include "Dz1TcpCallbackServerSocket.h"

#include <Dz1TcpCallbackServer.h>

static Dz1Error Dz1TcpCallbackServer_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1TcpCallbackServerArg *arg = (Dz1TcpCallbackServerArg *)uArg;
	Dz1TcpCallbackServerEnv *env = NULL;

	srand((u32_t)(time(NULL) & 0xFFFFFFFF));

	if (((*uRsc) = env = Dz1TcpCallbackServerEnv_new(tSelf, -1, -1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerEnv_delAndSetNull,(void *)uRsc);
		if ((env->acceptor = Dz1TcpCallbackServerAcceptor_start(my_queue_id, arg->port, errp)) == -1) ERR_OUT(errp);
#ifdef _DZ1_USE_SSL
		else if ((env->acceptor_ssl = Dz1TcpCallbackServerAcceptor_start(my_queue_id, arg->port+1, errp)) == -1) ERR_OUT(errp);
#endif
		else
		{
			Dz1Error_set(errp, 0);
			Dz1Task_queuePostSimple(my_queue_id, my_queue_id, DZ1_TCP_CALLBACK_SERVER_DO_DEFAULT);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TcpCallbackServerEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Dz1TcpCallbackServer_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1TcpCallbackServerArg *arg = (Dz1TcpCallbackServerArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Dz1TcpCallbackServer_cleanup(void *uRsc)
{
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;
	// Individual Cleanup Code Here
	Dz1TcpCallbackServerAcceptor_stopAndSetNull(&env->acceptor);
	Dz1TcpCallbackServerAcceptor_stopAndSetNull(&env->acceptor_ssl);
	Dz1TcpCallbackServerEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1Thread_usleep(1000);

	ret = _summary(uArg, uRsc, timer, NULL, errp);

	return ret;
}

void *Dz1TcpCallbackServer_new(u16_t port, Dz1TcpCallbackServerException exceptionProc, void *exceptionArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpCallbackServerArg *arg = Dz1TcpCallbackServerArg_new(port, exceptionProc, exceptionArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Dz1TcpCallbackServer", 1024,
							   (void **)&arg, (Dz1DelFunc)Dz1TcpCallbackServerArg_del,
							   (Dz1CmpFunc)Dz1TcpCallbackServerTimer_cmp,
							   Dz1TcpCallbackServer_init,
							   Dz1TcpCallbackServer_exception,
							   Dz1TcpCallbackServer_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_CALLBACK_SERVER_DO_DEFAULT),				_doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpCallbackServerSocketMsg_init(ret)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Dz1TcpCallbackServer_del(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (task == NULL) return;
	else if ((err = Dz1Task_del(task)).code) ERR_OUT(&err);
}
