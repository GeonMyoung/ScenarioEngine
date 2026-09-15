#include <dz1_task.h>

#include "ITSK00144_2TestScenarioArg.h"
#include "ITSK00144_2TestScenarioEnvUtil.h"
#include "ITSK00144_2TestScenarioTimerUtil.h"
#include "ITSK00144_2TestScenarioMsg.h"
#include "ITSK00144_2TestScenarioProc.h"

#include <ITSK00144_2TestScenario.h>
#include <ITSK00144_2TestScenarioDefJson.h>
#include <ITSK00144_2TestScenarioTest.h>


static Dz1Error ITSK001442TestScenario_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ITSK001442TestScenarioArg *arg = (ITSK001442TestScenarioArg *)uArg;
	ITSK001442TestScenarioEnv *env = NULL;

	if (((*uRsc) = env = ITSK001442TestScenarioEnv_new(tSelf, arg->tMain, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK001442TestScenarioEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = ITSK00144_2TestScenarioDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ITSK001442TestScenarioEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void ITSK001442TestScenario_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	ITSK001442TestScenarioArg *arg = (ITSK001442TestScenarioArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void ITSK001442TestScenario_cleanup(void *uRsc)
{
	ITSK001442TestScenarioEnv *env = (ITSK001442TestScenarioEnv *)uRsc;
	// Individual Cleanup Code Here
	ITSK001442TestScenarioEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg *arg = (ITSK001442TestScenarioArg *)uArg;
	ITSK001442TestScenarioEnv *env = (ITSK001442TestScenarioEnv *)uRsc;

	if (ITSK00144_2TestScenarioEnvUtil_sendUIConfigure(env, arg->testScenario, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *ITSK001442TestScenario_new(void *tMain, Dz1Str testScenario, ITSK001442TestScenarioException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK001442TestScenarioArg *arg = ITSK001442TestScenarioArg_new(tMain, testScenario, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK001442TestScenarioArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("ITSK001442TestScenario" , 1024,
							   (void **)&arg, (Dz1DelFunc)ITSK001442TestScenarioArg_del,
							   (Dz1CmpFunc)ITSK001442TestScenarioTimer_cmp,
							   ITSK001442TestScenario_init,
							   ITSK001442TestScenario_exception,
							   ITSK001442TestScenario_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (ITSK00144_2TestScenario_commandMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (ITSK00144_2TestScenarioProc_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (ITSK00144_2TestScenarioTest_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (ITSK001442TestScenarioArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ITSK001442TestScenario_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
