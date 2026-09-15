#include <dz1_task_timer.h>
#include "Dz1TcpCallbackClientArg.h"
#include "Dz1TcpCallbackClientEnvUtil.h"
#include "Dz1TcpCallbackClientTimerUtil.h"
#include "Dz1TcpCallbackClientSocket.h"

Dz1Error Dz1TcpCallbackClientTimer_reg(void *timer, u32_t id, Dz1SockAddr *peer, Dz1SockAddr *local,
									   u64_t duration_us, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1TcpCallbackClientTimer *tmr = Dz1TcpCallbackClientTimer_new(id, NULL, NULL, &err);
	if (tmr == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackClientTimer_delAndSetNull, (void *)&tmr);
		if ((tmr->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((tmr->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_reg(timer, duration_us, (void **)&tmr,
										(Dz1DelFunc)Dz1TcpCallbackClientTimer_del,
										timeout, TRUE)).code) ERR_OUT(&err);
		else tmr = NULL;
		pthread_cleanup_pop(1); // (Dz1TcpCallbackClientTimer_delAndSetNull, (void *)&tmr);
	}
	return err;	
}

void Dz1TcpCallbackClientTimer_dereg(void *timer, u32_t id, Dz1SockAddr *peer, Dz1SockAddr *local)
{
	Dz1TcpCallbackClientTimer key = { id, peer, local };
	Dz1TaskTimer_dereg(timer, &key);
}

///////////////////////////////////////////////////////////////////////////////
// TX Timeout Process
static __inline__ Dz1TaskProcStatus _tx_timeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
//	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;

	Dz1TcpCallbackClientTimer *tmr = (Dz1TcpCallbackClientTimer *)(*tData);

	Dz1TcpCallbackSession key = { tmr->peer, tmr->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Thread_printf("!!! TX Timeout\n");
		_session_runtime_terminate(timer, session);
	}

	return ret;
}
// TX Timeout Process
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TX Timeout Process
static Dz1TaskProcStatus _die_timeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
//	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;

	Dz1TcpCallbackClientTimer *tmr = (Dz1TcpCallbackClientTimer *)(*tData);

	Dz1TcpCallbackSession key = { tmr->peer, tmr->local }, *session = env->sessions->extract(env->sessions, &key);
	if (session != NULL)
	{
		Dz1Thread_printf("!!! Time to DIE\n");
		_session_runtime_terminate(timer, session);
	}

	return ret;
}
// TX Timeout Process
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timer Helper
Dz1Error _reg_retry_timer(void *timer, Dz1TcpCallbackSession *session)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

//	if ((err = Dz1TcpCallbackClientTimer_reg(timer, TX_TIMEOUT, session->peer, session->local, 3000000, _tx_timeout)).code) ERR_OUT(&err);

	return err;
}

void _dereg_retry_timer(void *timer, Dz1TcpCallbackSession *session)
{
	Dz1TcpCallbackClientTimer_dereg(timer, TX_TIMEOUT, session->peer, session->local);
}

Dz1Error _reg_term_timer(void *timer, Dz1TcpCallbackSession *session, u32_t dur_sec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = Dz1TcpCallbackClientTimer_reg(timer, TERM_TIMEOUT, session->peer, session->local,
											(u64_t)dur_sec * 1000000, _die_timeout)).code) ERR_OUT(&err);

	return err;
}

void _dereg_term_timer(void *timer, Dz1TcpCallbackSession *session)
{
	Dz1TcpCallbackClientTimer_dereg(timer, TERM_TIMEOUT, session->peer, session->local);
}

static Dz1TaskProcStatus _session_check(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1TcpCallbackClientArg *arg = (Dz1TcpCallbackClientArg *)uArg;
	Dz1TcpCallbackClientEnv *env = (Dz1TcpCallbackClientEnv *)uRsc;
	Dz1TcpCallbackClientCmd *cmd = env->cmd;
	if (cmd != NULL)
	{
		u32_t i, myQueueID = Dz1Task_getQueueID(env->tSelf);
		for (i = env->sessions->count(env->sessions); errp->code == 0 && i < cmd->max_conn; i++)
			if ((*errp = _connect_and_go(arg, env, timer, myQueueID)).code) ERR_OUT(errp);
		_reg_session_check(timer);
	}
	return ret;
}

Dz1Error _reg_session_check(void *timer)
{
	Dz1SockAddr addr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1SockAddr_setAddrStr(&addr, "0.0.0.0")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&addr, 0)).code) ERR_OUT(&err);
	else if ((err = Dz1TcpCallbackClientTimer_reg(timer, SESSION_CHK, &addr, &addr, 5000000, _session_check)).code) ERR_OUT(&err);
	return err;
}
// Timer Helper
///////////////////////////////////////////////////////////////////////////////

