#include <dz1_task_timer.h>
#include "Dz1TcpCallbackServerEnvUtil.h"
#include "Dz1TcpCallbackServerTimerUtil.h"

static Dz1TaskProcStatus _session_terminate(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp);
Dz1Error _reg_session_term_timer(void *timer, Dz1TcpCallbackSession *node, u32_t timeout_sec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpCallbackServerTimer *tmr = Dz1TcpCallbackServerTimer_new(Dz1TcpCallbackServerTimerPresent_session, NULL, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpCallbackServerSessionTimer *st = NULL;
		pthread_cleanup_push(Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&tmr);
		if ((tmr->x.session = st = Dz1TcpCallbackServerSessionTimer_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((st->peer = Dz1SockAddr_clone(node->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((st->local = Dz1SockAddr_clone(node->local, errp)) == NULL) ERR_OUT(errp);
		else if ((err = Dz1TaskTimer_reg(timer, 5000000, (void **)&tmr,
									   (Dz1DelFunc)Dz1TcpCallbackServerTimer_del,
									   _session_terminate, TRUE)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&tmr);
	}
	return err;
}

static Dz1TaskProcStatus _session_terminate(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;

	Dz1TcpCallbackServerTimer *tmr = (Dz1TcpCallbackServerTimer *)(*tData);
	Dz1TcpCallbackServerSessionTimer *st = tmr->x.session;

	Dz1TcpCallbackSession key = { st->peer, st->local }, *node = env->sessions->extract(env->sessions, &key);
	if (node != NULL) Dz1TcpCallbackSession_delAndSetNull((void *)&node);

	return ret;
}

Dz1Error _reg_summary_timer(void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	u32_t id = 0;
	Dz1TcpCallbackServerTimer *tmr = Dz1TcpCallbackServerTimer_new(Dz1TcpCallbackServerTimerPresent_id, &id, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&tmr);
		if ((err = Dz1TaskTimer_reg(timer, 5000000, (void **)&tmr,
								   (Dz1DelFunc)Dz1TcpCallbackServerTimer_del,
								   _summary, TRUE)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackServerTimer_delAndSetNull, (void *)&tmr);
	}
	return err;
}

