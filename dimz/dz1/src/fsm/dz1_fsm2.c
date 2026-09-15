#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_fsm2.h>

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

static void Dz1Fsm2LogA_dumpEntrance(Dz1Fsm2LogA *p, int tab)
{
	if (!p) return;
	Dz1ThreadA_tprintf(tab, "[S:%02d][E:%02d][F:%p]\n", p->state, p->event, p->func, p->ret, p->nextState);
}

static void Dz1Fsm2LogA_dump(Dz1Fsm2LogA *p, int tab)
{
	if (!p) return;
	if (p->err.code == 0)
		Dz1ThreadA_tprintf(tab, "[S:%02d][E:%02d][F:%p]:[RET:%d][NS:%02d]\n",
								p->state, p->event, p->func, p->ret, p->nextState);
	else
		Dz1ThreadA_tprintf(tab, "[S:%02d][E:%02d][F:%p]:[%s(%d)][NS:%02d]\n",
								p->state, p->event, p->func, Dz1ErrorStrA(p->err.code), p->err.code, p->nextState);
}

/*
typedef struct Dz1Fsm2
{
	int state;

	// FSM Trace Log
	Dz1Fsm2Log *fsmLog;
	int fsmLogSize;
	int fsmLogIdx;
  
	Dz1FsmGetEvent getEvent;
	Dz1Fsm2GetFunc getFunc;
	
	void *fsmArg;
	Dz1DelFunc fsmArgDel;
	  
} Dz1Fsm2;
*/

Dz1Fsm2A *_Dz1Fsm2A_new(str_t name, bool_t trace, u32_t fsmLogSize, Dz1Fsm2GetEventByDataA getEventByData, Dz1Fsm2GetEventByNameA getEventByName, Dz1Fsm2GetFuncA getFunc, void **arg, Dz1DelFunc argDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Fsm2A *ret = NULL;
	
	if (getEventByData == NULL || getFunc == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Fsm2A *)Dz1Calloc(sizeof(Dz1Fsm2A), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Fsm2_delAndSetNull, (void *)&ret);

		// fix log size;
		if (fsmLogSize == 0) fsmLogSize = 1;

		if ((ret->fsmLog = (Dz1Fsm2LogA *)Dz1Calloc(sizeof(Dz1Fsm2LogA), (ret->fsmLogSize = fsmLogSize), errp)) == NULL) ERR_OUT(errp);
		else if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->state = 0;
			ret->trace = trace;
			ret->fsmLogIdx = 0;
			ret->getEventByData = getEventByData;
			ret->getEventByName = getEventByName;
			ret->getFunc = getFunc;
			if (arg) ret->fsmArg = *arg;
			ret->fsmArgDel = argDel;
			if (argDel && arg) *arg = NULL;
		}
		pthread_cleanup_pop(errp->code); // (Dz1Fsm2_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Fsm2A_del(Dz1Fsm2A *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	if (p->fsmArg && p->fsmArgDel) p->fsmArgDel(p->fsmArg);
	if (p->fsmLog) Dz1Free(p->fsmLog);
	Dz1Free(p);
}

static void _Dz1Fsm2A_proc(Dz1Fsm2A *fsm, void *user_param, void *user_resource, void *user_timer, Dz1Fsm2LogA *fsmLog, void **msg)
{
	if ((fsmLog->err = fsm->getFunc(fsmLog->state, fsmLog->event, &fsmLog->func)).code) FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
	else
	{
		if (fsm->trace) { Dz1ThreadA_printf("FSM(%s):<<",fsm->name); Dz1Fsm2LogA_dumpEntrance(fsmLog, 0); }

		if (fsmLog->func == NULL)
		{
			fsmLog->ret = Dz1FsmReturn_continue;
			fsmLog->nextState = fsmLog->state;
		}
		else if ((fsmLog->ret = fsmLog->func(fsm, user_param, user_resource, user_timer, fsmLog->event, msg, &fsmLog->err)) == Dz1FsmReturn_error) FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
		else fsmLog->nextState = fsm->state;

		if (fsm->trace) { Dz1ThreadA_printf("FSM(%s):>>",fsm->name); Dz1Fsm2LogA_dump(fsmLog, 0); }
	}
}

Dz1FsmReturn Dz1Fsm2A_proc(Dz1Fsm2A *fsm, void *user_param, void *user_resource, void *user_timer, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL) { ERR_SET_OUT(errp, EINVAL); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogA *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;

		if ((fsmLog->event = fsm->getEventByData(fsm, user_param, user_resource, *msg)) < 0) FSM_ERR_SET_OUT(fsmLog->ret, &fsmLog->err, EINVAL);
		else _Dz1Fsm2A_proc(fsm, user_param, user_resource, user_timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}

Dz1FsmReturn Dz1Fsm2A_proc2(Dz1Fsm2A *fsm, void *user_param, void *user_resource, void *user_timer, int ev, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL) { ERR_SET_OUT(errp, EINVAL); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogA *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;
		fsmLog->event = ev;

		_Dz1Fsm2A_proc(fsm, user_param, user_resource, user_timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}

Dz1FsmReturn Dz1Fsm2A_proc3(Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *timer, void *evName, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL || fsm->getEventByName == NULL) { ERR_SET_OUT(errp, ENOSYS); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogA *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;
		fsmLog->event = fsm->getEventByName(fsm, uArg, uRsc, evName);

		_Dz1Fsm2A_proc(fsm, uArg, uRsc, timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}
#ifndef UNIX_SYSTEM
static void Dz1Fsm2LogW_dumpEntrance(Dz1Fsm2LogW *p, int tab)
{
	if (!p) return;
	Dz1ThreadW_tprintf(tab, L"[S:%02d][E:%02d][F:%p]\n", p->state, p->event, p->func, p->ret, p->nextState);
}

static void Dz1Fsm2LogW_dump(Dz1Fsm2LogW *p, int tab)
{
	if (!p) return;
	if (p->err.code == 0)
		Dz1ThreadW_tprintf(tab, L"[S:%02d][E:%02d][F:%p]:[RET:%d][NS:%02d]\n",
								p->state, p->event, p->func, p->ret, p->nextState);
	else
		Dz1ThreadW_tprintf(tab, L"[S:%02d][E:%02d][F:%p]:[%s(%d)][NS:%02d]\n",
								p->state, p->event, p->func, Dz1ErrorStrW(p->err.code), p->err.code, p->nextState);
}
Dz1Fsm2W *_Dz1Fsm2W_new(wstr_t name, bool_t trace, u32_t fsmLogSize, Dz1Fsm2GetEventByDataW getEventByData, Dz1Fsm2GetEventByNameW getEventByName, Dz1Fsm2GetFuncW getFunc, void **arg, Dz1DelFunc argDel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Fsm2W *ret = NULL;
	
	if (getEventByData == NULL || getFunc == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Fsm2W *)Dz1Calloc(sizeof(Dz1Fsm2W), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Fsm2_delAndSetNull, (void *)&ret);

		// fix log size;
		if (fsmLogSize == 0) fsmLogSize = 1;

		if ((ret->fsmLog = (Dz1Fsm2LogW *)Dz1Calloc(sizeof(Dz1Fsm2LogW), (ret->fsmLogSize = fsmLogSize), errp)) == NULL) ERR_OUT(errp);
		else if ((ret->name = Dz1StrW_dup(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->state = 0;
			ret->trace = trace;
			ret->fsmLogIdx = 0;
			ret->getEventByData = getEventByData;
			ret->getEventByName = getEventByName;
			ret->getFunc = getFunc;
			if (arg) ret->fsmArg = *arg;
			ret->fsmArgDel = argDel;
			if (argDel && arg) *arg = NULL;
		}
		pthread_cleanup_pop(errp->code); // (Dz1Fsm2_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Fsm2W_del(Dz1Fsm2W *p)
{
	if (!p) return;
	if (p->name) Dz1StrW_del(p->name);
	if (p->fsmArg && p->fsmArgDel) p->fsmArgDel(p->fsmArg);
	if (p->fsmLog) Dz1Free(p->fsmLog);
	Dz1Free(p);
}

static void _Dz1Fsm2W_proc(Dz1Fsm2W *fsm, void *user_param, void *user_resource, void *user_timer, Dz1Fsm2LogW *fsmLog, void **msg)
{
	if ((fsmLog->err = fsm->getFunc(fsmLog->state, fsmLog->event, &fsmLog->func)).code) FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
	else
	{
		if (fsm->trace) { Dz1ThreadW_printf(L"FSM(%s):<<",fsm->name); Dz1Fsm2LogW_dumpEntrance(fsmLog, 0); }

		if (fsmLog->func == NULL)
		{
			fsmLog->ret = Dz1FsmReturn_continue;
			fsmLog->nextState = fsmLog->state;
		}
		else if ((fsmLog->ret = fsmLog->func(fsm, user_param, user_resource, user_timer, fsmLog->event, msg, &fsmLog->err)) == Dz1FsmReturn_error) FSM_ERR_OUT(fsmLog->ret, &fsmLog->err);
		else fsmLog->nextState = fsm->state;

		if (fsm->trace) { Dz1ThreadW_printf(L"FSM(%s):>>",fsm->name); Dz1Fsm2LogW_dump(fsmLog, 0); }
	}
}

Dz1FsmReturn Dz1Fsm2W_proc(Dz1Fsm2W *fsm, void *user_param, void *user_resource, void *user_timer, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL) { ERR_SET_OUT(errp, EINVAL); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogW *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;

		if ((fsmLog->event = fsm->getEventByData(fsm, user_param, user_resource, *msg)) < 0) FSM_ERR_SET_OUT(fsmLog->ret, &fsmLog->err, EINVAL);
		else _Dz1Fsm2W_proc(fsm, user_param, user_resource, user_timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}

Dz1FsmReturn Dz1Fsm2W_proc2(Dz1Fsm2W *fsm, void *user_param, void *user_resource, void *user_timer, int ev, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL) { ERR_SET_OUT(errp, EINVAL); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogW *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;
		fsmLog->event = ev;

		_Dz1Fsm2W_proc(fsm, user_param, user_resource, user_timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}

Dz1FsmReturn Dz1Fsm2W_proc3(Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *timer, void *evName, void **_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fsm == NULL || fsm->getEventByName == NULL) { ERR_SET_OUT(errp, ENOSYS); return Dz1FsmReturn_error; }
	else
	{
		Dz1Fsm2LogW *fsmLog = &fsm->fsmLog[fsm->fsmLogIdx++];
		void *temp = NULL, **msg = _msg ? _msg : &temp;

		fsm->fsmLogIdx %= fsm->fsmLogSize;

		fsmLog->ret = Dz1FsmReturn_continue;
		fsmLog->nextState = -1;
		fsmLog->state = fsm->state;
		fsmLog->event = fsm->getEventByName(fsm, uArg, uRsc, evName);

		_Dz1Fsm2W_proc(fsm, uArg, uRsc, timer, fsmLog, msg);

		*errp = fsmLog->err;

		return fsmLog->ret;
	}
}
#endif
