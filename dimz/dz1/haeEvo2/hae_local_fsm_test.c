#include <hae_output.h>
#include <hae_local_fsm.h>

#define EVENT_0			0
#define EVENT_1			1
#define EVENT_EXIT		2
#define EVENT_UNKNOWN	3
#define EVENT_MAX		4

#define S0				0
#define S1				1
#define SMAX			2

static int doEvent0Go1(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Get Event_0(%c) and Go S1 State\n", c);

	fsm->state = S1;

	return HAE_FSM_SUCCESS;
}

static int doEvent1Go0(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Get Event_1(%c) and Go S0 State\n", c);

	fsm->state = S0;

	return HAE_FSM_SUCCESS;
}

static int nop(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Not Acceptable Event(%c)->Ignode\n", c);
	return HAE_FSM_SUCCESS;
}

static int term(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Get Event_EXIT(%c) and Go S0 State\n", c);
	return HAE_FSM_TERM;
}

static int unknown_term(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Get Unknown Event(%c)->Terminate\n", c);
	return HAE_FSM_TERM;
}

static int unknown_nop(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, void *eventMsg, int *err)
{
	int c = HAE_PTR_CAST(int, eventMsg);
	*err = 0;
	HaeOut->printf(0, "Get Unknown Event(%c)->Ignode\n", c);
	return HAE_FSM_SUCCESS;
}

static int myFsmInit(HaeFsmFunc *funcs, int *err)
{
	HaeFsmFunc temp[SMAX][EVENT_MAX] =
	{//   Ev0           Ev1          Ev2   Ev3                                        
/*S0*/	{ doEvent0Go1, 	NULL,		 term, unknown_term },
/*S1*/	{ nop, 			doEvent1Go0, term, unknown_nop },
	};
	memcpy(funcs, temp, sizeof(temp));
	*err = 0;
	return HAE_FSM_SUCCESS;
}

static int myFsmStart(HaeLocalFsm *fsm, void *globalData, void *threadData, void *fsmArg, int *err)
{
	*err = 0;
	HaeOut->printf(0, "FSM Start\n");
	return HAE_FSM_SUCCESS;
}

static u32_t myGetEvent(void *globalData, void *threadData, void *fsmArg, void *msg, int *err)
{
	int c = HAE_PTR_CAST(int, msg);
	*err = 0;
	switch(c)
	{
		case 'a': case 'A':
			return EVENT_0;
		case 's': case 'S':
			return EVENT_1;
		case 'x': case 'X':
			return EVENT_EXIT;
		default:
			return EVENT_UNKNOWN;
	}
}

int main(void)
{
	int c;
	int err = 0;
	int status = 0;
	HaeLocalFsm *fsm = haeLocalFsm_create("test", S0, EVENT_MAX, SMAX,
										NULL, NULL, NULL,
										myFsmInit, myFsmStart, myGetEvent,
										FALSE, 10, &err);
	if (fsm)
	{
		if (fsm->start(fsm, NULL, NULL, &err) == HAE_FSM_SUCCESS)
		{
			while(1)
			{
				c = getchar(); getchar();
				if ((status = fsm->proc(fsm, NULL, NULL, HAE_PTR_CAST(void *, c), &err)) != HAE_FSM_SUCCESS) break;
			}
			if (status == HAE_FSM_TERM)
				HaeOut->printf(0, "FSM Normally Terminated\n");
			else
				HaeOut->printf(0, "FSM Abnomally Terminated = %s(%d)\n", strerror(err), err);
		}
		else
			HaeOut->printf(0, "fsm->start() = %s(%d)\n", strerror(err), err);
	}
	else
		HaeOut->printf(0, "No Memory\n");
	return 0;
}
