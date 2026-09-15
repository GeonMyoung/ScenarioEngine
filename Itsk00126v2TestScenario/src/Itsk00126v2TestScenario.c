#include <dz1_task.h>

#include "Itsk00126v2TestScenarioArg.h"
#include "Itsk00126v2TestScenarioEnvUtil.h"
#include "Itsk00126v2TestScenarioTimerUtil.h"
#include "Itsk00126v2TestScenarioMsg.h"
#include "Itsk00126v2TestScenarioProc.h"

#include <Itsk00126v2TestScenario.h>
#include <Itsk00126v2TestScenarioDefJson.h>

static Dz1Error Itsk00126V2TestScenario_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Itsk00126V2TestScenarioArg *arg = (Itsk00126V2TestScenarioArg *)uArg;
	Itsk00126V2TestScenarioEnv *env = NULL;

	if (((*uRsc) = env = Itsk00126V2TestScenarioEnv_new(tSelf, arg->tMain, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126V2TestScenarioEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = Itsk00126v2TestScenarioDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Itsk00126V2TestScenarioEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Itsk00126V2TestScenario_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Itsk00126V2TestScenarioArg *arg = (Itsk00126V2TestScenarioArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Itsk00126V2TestScenario_cleanup(void *uRsc)
{
	Itsk00126V2TestScenarioEnv *env = (Itsk00126V2TestScenarioEnv *)uRsc;
	// Individual Cleanup Code Here
	Itsk00126V2TestScenarioEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V2TestScenarioArg *arg = (Itsk00126V2TestScenarioArg *)uArg;
	Itsk00126V2TestScenarioEnv *env = (Itsk00126V2TestScenarioEnv *)uRsc;

	if (Itsk00126V2TestScenarioEnvUtil_sendUIConfigure(env, arg->testScenario, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

void *Itsk00126V2TestScenario_new(void *tMain, Dz1Str testScenario, Itsk00126V2TestScenarioException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126V2TestScenarioArg *arg = Itsk00126V2TestScenarioArg_new(tMain, testScenario, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126V2TestScenarioArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Itsk00126V2TestScenario" , 1024,
							   (void **)&arg, (Dz1DelFunc)Itsk00126V2TestScenarioArg_del,
							   (Dz1CmpFunc)Itsk00126V2TestScenarioTimer_cmp,
							   Itsk00126V2TestScenario_init,
							   Itsk00126V2TestScenario_exception,
							   Itsk00126V2TestScenario_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (Itsk00126v2TestScenario_commandMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (Itsk00126v2TestScenarioProc_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Itsk00126V2TestScenarioArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Itsk00126V2TestScenario_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
