#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_fsm.h>

/*
typedef struct Dz1FsmLog
{
	int state;
	int event;
	Dz1FsmFunc func;
	Dz1FsmReturn ret;
	Dz1Error err;
	int nextState;
} Dz1FsmLog;
*/

static void Dz1FsmLogA_dump(Dz1FsmLog *p, int tab)
{
	if (!p) return;
	if (p->err.code == 0)
		Dz1ThreadA_tprintf(tab, "[S:%02d][E:%02d][F:%p]:[RET:%d][NS:%02d]\n", p->state, p->event, p->func, p->ret, p->nextState);
	else Dz1ThreadA_tprintf(tab, "[S:%02d][E:%02d][F:%p]:[%s(%d)][NS:%02d]\n", p->state, p->event, p->func, Dz1ErrorStr(p->err.code), p->err.code, p->nextState);
}
#ifndef UNIX_SYSTEM
static void Dz1FsmLogW_dump(Dz1FsmLog *p, int tab)
{
	if (!p) return;
	if (p->err.code == 0)
		Dz1ThreadW_tprintf(tab, L"[S:%02d][E:%02d][F:%p]:[RET:%d][NS:%02d]\n", p->state, p->event, p->func, p->ret, p->nextState);
	else Dz1ThreadW_tprintf(tab, L"[S:%02d][E:%02d][F:%p]:[%s(%d)][NS:%02d]\n", p->state, p->event, p->func, Dz1ErrorStr(p->err.code), p->err.code, p->nextState);
}
#endif
/*
typedef struct Dz1Fsm
{
	int state;

	// FSM Trace Log
	Dz1FsmLog *fsmLog;
	int fsmLogSize;
	int fsmLogIdx;
  
	Dz1FsmGetEvent getEvent;
	Dz1FsmGetFunc getFunc;
	
	void *fsmArg;
	Dz1DelFunc fsmArgDel;
	  
} Dz1Fsm;
*/

Dz1Fsm *Dz1Fsm_new(bool_t trace, u32_t fsmLogSize, Dz1FsmGetEvent getEvent, Dz1FsmGetFunc getFunc, void **arg, Dz1DelFunc argDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Fsm *ret = (Dz1Fsm *)Dz1Calloc(sizeof(Dz1Fsm), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Fsm_delAndSetNull, (void *)&ret);

		// fix log size;
		if (fsmLogSize == 0) fsmLogSize = 1;

		if ((ret->fsmLog = (Dz1FsmLog *)Dz1Calloc(sizeof(Dz1FsmLog), (ret->fsmLogSize = fsmLogSize), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->state = 0;
			ret->trace = trace;
			ret->fsmLogIdx = 0;
			ret->getEvent = getEvent;
			ret->getFunc = getFunc;
			if (arg)
			{
				ret->fsmArg = *arg;
			}
			ret->fsmArgDel = argDel;
			if (argDel && arg) *arg = NULL;
		}
		pthread_cleanup_pop(errp->code); // (Dz1Fsm_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Fsm_del(Dz1Fsm *p)
{
	if (!p) return;
	if (p->fsmArg && p->fsmArgDel) p->fsmArgDel(p->fsmArg);
	if (p->fsmLog) Dz1Free(p->fsmLog);
	Dz1Free(p);
}

static void _Dz1Fsm_proc(Dz1Fsm *fsm, void *user_param, void *user_resource, void **msg, Dz1Error *errp)
{
	Dz1FsmLog *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];

	fsm->fsmLogIdx %= fsm->fsmLogSize;

	fsmLog->ret = Dz1FsmReturn_continue;
	fsmLog->nextState = -1;
	fsmLog->state = fsm->state;

	if ((fsmLog->event = fsm->getEvent(fsm, user_param, user_resource, *msg)) < 0) FSM_ERR_SET_OUT(fsmLog->ret, &fsmLog->err, EINVAL);
	else
	{
		if ((fsmLog->err = fsm->getFunc(fsmLog->state, fsmLog->event, &fsmLog->func)).code) FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
		else if (fsmLog->func == NULL) { fsmLog->ret = Dz1FsmReturn_continue; fsmLog->nextState = fsmLog->state; }
		else
		{
			if ((fsmLog->ret = fsmLog->func(fsm, user_param, user_resource, fsmLog->event, msg, &fsmLog->err)) == Dz1FsmReturn_error)
				FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
		}
	}

	*errp = fsmLog->err;
}


Dz1FsmReturn Dz1FsmA_proc(Dz1Fsm *fsm, void *user_param, void *user_resource, void **msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1FsmLog *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx];

	_Dz1Fsm_proc(fsm, user_param, user_resource, msg, errp);

	if (fsm->trace) Dz1FsmLogA_dump(fsmLog, 0);

	return fsmLog->ret;
}
#ifndef UNIX_SYSTEM
Dz1FsmReturn Dz1FsmW_proc(Dz1Fsm *fsm, void *user_param, void *user_resource, void **msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1FsmLog *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx];

	_Dz1Fsm_proc(fsm, user_param, user_resource, msg, errp);

	if (fsm->trace) Dz1FsmLogW_dump(fsmLog, 0);

	return fsmLog->ret;
}
#endif
