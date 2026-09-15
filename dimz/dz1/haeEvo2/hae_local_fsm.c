#include <errno.h>
#include <hae_output.h>
#include <hae_local_thread.h>
#include <hae_local_memory.h>
#include <hae_misc.h>

#include <hae_local_fsm.h>

#define HAE_FSM_UNKNOWN				9999

static struct __ValueStrMap__
{
	int status;
	str_t str;
} HaeLocalFsmStatusMap[] =
{
	{ HAE_FSM_UNKNOWN,	"UNK " },
	{ HAE_FSM_TERM,		"TERM" },
	{ HAE_FSM_ERROR,	"ERR " },
	{ HAE_FSM_SUCCESS,	"SUCC" },
	{ 0,				NULL   }
};

static str_t HaeLocalFsmStatusStr(int status)
{
	struct __ValueStrMap__ *i;
	for (i = HaeLocalFsmStatusMap; i->str != NULL; i++)
		if (status == i->status) return i->str;
	return HaeLocalFsmStatusMap[0].str;
}

static void HaeLocalFsmLogEntry_init(HaeLocalFsmLogEntry *p)
{
	p->state = -1;
	p->event = -1;
	p->func = NULL;
	p->err = -1;
	p->status = HAE_FSM_UNKNOWN;
	p->next_state = -1;
}

static void HaeLocalFsmLogEntry_dump(HaeLocalFsmLogEntry *p, int *cnt, int tab)
{
	if (!p) return;
	if (p->state == -1) return;
	HaeOut->printf(tab, "[%02d][S:%02d][E:%02d][F:%p]-%s(%s(%d))->[S:%02d]\n",
			(*cnt)++, p->state, p->event, p->func,
			HaeLocalFsmStatusStr(p->status),
			strerror(p->err), p->err, p->next_state);
}

static void HaeLocalFsmLog_del(HaeLocalFsmLog *p)
{
	if (!p) return;
	if (p->entries) LOCAL_FREE(p->entries);
	LOCAL_FREE(p);
}

static void HaeLocalFsmLog_delAndSetNull(void *ptr)
{
	HaeLocalFsmLog **p = (HaeLocalFsmLog **)ptr;
	HaeLocalFsmLog_del(*p); *p = NULL;
}

static HaeLocalFsmLogEntry *HaeLocalFsmLog_get(HaeLocalFsmLog *p)
{
	HaeLocalFsmLogEntry *ret = &p->entries[p->logPos++];
	p->logPos %= p->logSize;
	return ret;
}

static HaeLocalFsmLog *HaeLocalFsmLog_new(int logSize, int *err)
{
	int _err, *errp = err ? err : &_err;
	HaeLocalFsmLog *ret = (HaeLocalFsmLog *)LOCAL_MALLOC(sizeof(HaeLocalFsmLog));
	if (ret == NULL) { *errp = ENOMEM; }
	else
	{
		memset(ret, 0, sizeof(HaeLocalFsmLog));
		pthread_cleanup_push(HaeLocalFsmLog_delAndSetNull, (void *)&ret);
		if ((ret->entries = (HaeLocalFsmLogEntry *)LOCAL_MALLOC(sizeof(HaeLocalFsmLogEntry) * logSize)) == NULL) { *errp = ENOMEM; }
		else
		{
			int i = 0;
			ret->logSize = logSize;
			ret->logPos = 0;
			ret->get = HaeLocalFsmLog_get;
			for (i = 0; i < ret->logSize; i++) HaeLocalFsmLogEntry_init(&ret->entries[i]);
			*errp = 0;
		}
		pthread_cleanup_pop(*errp); // (HaeLocalFsmLog_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void HaeLocalFsmLog_dump(HaeLocalFsmLog *p, int tab)
{
	int cnt = 0, i;
	for (i = p->logPos; i >= 0; i--)
		HaeLocalFsmLogEntry_dump(&p->entries[i], &cnt, tab);
	for (i = p->logSize - 1; i > p->logPos; i--)
		HaeLocalFsmLogEntry_dump(&p->entries[i], &cnt, tab);
}

static int haeLocalFsm_start(HaeLocalFsm *fsm, void *globalData, void *threadData, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	int status = 0;
	
	HaeLocalThreadBackTracking_pushComment("%s:%p", fsm->name, fsm->fsmStartFunc);
	if ((status = fsm->fsmStartFunc(fsm, globalData, threadData, fsm->fsmArg, errp)) == HAE_FSM_ERROR)
		{ if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_start(%s) : %s(%d)\n", fsm->name, strerror(*errp), *errp); }
	else if (status == HAE_FSM_TERM) { HaeOut->printf(0, "haeLocalFsm_start(%s) : FSM_TERM retrun on Start time\n", fsm->name); }
	else { if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_start(%s) : Success\n", fsm->name); }

	HaeLocalThreadBackTracking_pop();

	return status;
}

static int haeLocalFsm_proc(HaeLocalFsm *fsm, void *globalData, void *threadData, void *msg, int *err)
{
	int local_err, *errp = err ? err : &local_err;

	HaeLocalFsmLogEntry *job = fsm->fsmLog->get(fsm->fsmLog);
	HaeLocalFsmLogEntry_init(job);

	if (fsm->state >= fsm->maxState)
	{
		if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : Invalid State[%d]\n", fsm->name, fsm->state);
		job->status = HAE_FSM_ERROR;
		job->err = *errp = EFAULT;
	}
	else
	{
		job->state = fsm->state;
		if ((job->event = fsm->getEventFromMsg(globalData, threadData, fsm->fsmArg, msg, errp)) == (u32_t)-1)
		{
			if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : Unknown Event[%08x]\n", fsm->name, job->event);
			job->status = HAE_FSM_SUCCESS;
			job->err = *errp = 0;
		}
		else if (job->event == (u32_t)-2)
		{
			if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : Event Ignored\n", fsm->name);
			job->status = HAE_FSM_SUCCESS;
			job->err = *errp = 0;
		}
		else if (job->event >= fsm->maxEvent)
		{
			if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : Invalid Event[%d]\n", fsm->name, job->event);
			job->status = HAE_FSM_ERROR;
			job->err = *errp = EINVAL;
		}
		else
		{
			job->err = 0;
			job->func = fsm->funcs[fsm->state * fsm->maxEvent + job->event];
			if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : [S:%02d][E:%02d][F:%p]\n",
																fsm->name, fsm->state, job->event, job->func);

			if (job->func == NULL) { job->status = HAE_FSM_SUCCESS; }
			else
			{
				HaeLocalThreadBackTracking_pushComment("%s:S=%d:E=%d:F=%p:Gp=%p,Tp=%p,Ap=%p,msg=%p",
						fsm->name, fsm->state, job->event, job->func, globalData, threadData, fsm->fsmArg, msg);

				if ((job->status = job->func(fsm, globalData, threadData, fsm->fsmArg, msg, &job->err)) == HAE_FSM_ERROR)
				{
					if (fsm->trace) HaeOut->printf(0, "haeLocalFsm_proc(%s) : State : %d, Event : %d, Error : %s(%d)\n",
															fsm->name, fsm->state, job->event, strerror(job->err), job->err);
				}
				*errp = job->err;
				job->next_state = fsm->state;

				HaeLocalThreadBackTracking_pop();
			}
		}
	}

	return job->status;
}

HaeLocalFsm *haeLocalFsm_create(str_t name, u32_t initial_state, int maxEvent, int maxState,
								void *fsmArg, HaeGeneralDelFunc fsmArgDel, HaeGeneralDumpFunc fsmArgDump,
								HaeFsmInitFunc fsmInitFunc, HaeFsmStartFunc fsmStartFunc, HaeFsmMsgConvFunc getEventFromMsg, 
								int trace, int logSize, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	HaeLocalFsm *ret = NULL;

	if (!maxEvent || !maxState) { *errp = EINVAL; }
	else if (!getEventFromMsg || !fsmInitFunc) { *errp = EINVAL; }
	else if ((ret = (HaeLocalFsm *)LOCAL_MALLOC(sizeof(HaeLocalFsm))) == NULL) { *errp = ENOMEM; }
	else
	{
		memset(ret, 0, sizeof(HaeLocalFsm));
		pthread_cleanup_push(HaeLocalFsm_delAndSetNull, (void *)&ret);

		if ((ret->name = haeMiscStr_cloneToLocal(name, NULL)) == NULL) { *errp = ENOMEM; }
		else if ((ret->fsmLog = HaeLocalFsmLog_new(logSize, errp)) == NULL) { *errp = ENOMEM; }
		else if (!(ret->funcs = (HaeFsmFunc *)LOCAL_MALLOC(sizeof(HaeFsmFunc) * maxEvent * maxState))) { *errp = ENOMEM; }
		else if ((*errp = fsmInitFunc(ret->funcs, errp)) != 0) { }
		else
		{
			ret->state = initial_state;
			ret->maxEvent = maxEvent;
			ret->maxState = maxState;
			ret->fsmArg = fsmArg;
			ret->fsmArgDel = fsmArgDel;
			ret->fsmArgDump = fsmArgDump;
			ret->fsmStartFunc = fsmStartFunc;
			ret->getEventFromMsg = getEventFromMsg;
			ret->trace = trace;
			ret->start = haeLocalFsm_start;
			ret->proc = haeLocalFsm_proc;
			*errp = 0;
		}

		pthread_cleanup_pop(*errp); // (HaeLocalFsm_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void haeLocalFsm_del(HaeLocalFsm *p)
{
	if (!p) return;
	if (p->name) LOCAL_FREE(p->name);
	if (p->fsmArg && p->fsmArgDel) p->fsmArgDel(p->fsmArg);
	if (p->funcs) LOCAL_FREE(p->funcs);
	if (p->fsmLog) HaeLocalFsmLog_del(p->fsmLog);
	LOCAL_FREE(p);
}

void haeLocalFsm_dump(HaeLocalFsm *p, int tab)
{
	if (!p) return;
	HaeOut->printf(tab, "[FSM : %s]\n", p->name);
	HaeOut->printf(tab, "[State : %d/%d][Max Event : %d]\n", p->state, p->maxState, p->maxEvent);
	if (p->fsmLog) HaeLocalFsmLog_dump(p->fsmLog, tab);
	if (p->fsmArg && p->fsmArgDump) p->fsmArgDump(p->fsmArg, tab);
}
