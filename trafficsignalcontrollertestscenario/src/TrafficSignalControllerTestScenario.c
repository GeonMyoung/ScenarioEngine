#include <dz1_task.h>

#include "TrafficSignalControllerTestScenarioArg.h"
#include "TrafficSignalControllerTestScenarioEnvUtil.h"
#include "TrafficSignalControllerTestScenarioTimerUtil.h"
#include "TrafficSignalControllerTestScenarioMsg.h"
#include "TrafficSignalControllerTestScenarioProc.h"

#include <TrafficSignalControllerTestScenario.h>


static Dz1Error TrafficSignalControllerTestScenario_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TrafficSignalControllerTestScenarioArg *arg = (TrafficSignalControllerTestScenarioArg *)uArg;
	TrafficSignalControllerTestScenarioEnv *env = NULL;

	if (((*uRsc) = env = TrafficSignalControllerTestScenarioEnv_new(tSelf, arg->tMain, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestScenarioEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = TrafficSignalControllerTestMsgDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestScenarioEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void TrafficSignalControllerTestScenario_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	TrafficSignalControllerTestScenarioArg *arg = (TrafficSignalControllerTestScenarioArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void TrafficSignalControllerTestScenario_cleanup(void *uRsc)
{
	TrafficSignalControllerTestScenarioEnv *env = (TrafficSignalControllerTestScenarioEnv *)uRsc;
	// Individual Cleanup Code Here
	TrafficSignalControllerTestScenarioEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	 TrafficSignalControllerTestScenarioArg *arg = (TrafficSignalControllerTestScenarioArg *)uArg;
	 TrafficSignalControllerTestScenarioEnv *env = (TrafficSignalControllerTestScenarioEnv *)uRsc;

	 if (TrafficSignalControllerTestScenarioEnvUtil_sendUIConfigure(env, arg->testScenario, errp) == FALSE) ERR_OUT(errp);
	 else Dz1Error_set(errp, 0);

	return ret;
}

void *TrafficSignalControllerTestScenario_new(void *tMain, Dz1Str testScenario, TrafficSignalControllerTestScenarioException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestScenarioArg *arg = TrafficSignalControllerTestScenarioArg_new(tMain, testScenario, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestScenarioArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("TrafficSignalControllerTestScenario" , 1024,
							   (void **)&arg, (Dz1DelFunc)TrafficSignalControllerTestScenarioArg_del,
							   (Dz1CmpFunc)TrafficSignalControllerTestScenarioTimer_cmp,
							   TrafficSignalControllerTestScenario_init,
							   TrafficSignalControllerTestScenario_exception,
							   TrafficSignalControllerTestScenario_cleanup, errp)) == NULL) ERR_OUT(errp);	
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (TrafficSignalControllerTestScenario_commandMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (TrafficSignalControllerTestScenario_sockMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (TrafficSignalControllerTestScenarioProc_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerTestScenarioArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void TrafficSignalControllerTestScenario_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
