#include <dz1_task.h>

#include "GitsnDSRCMsgTestScenarioArg.h"
#include "GitsnDSRCMsgTestScenarioEnvUtil.h"
#include "GitsnDSRCMsgTestScenarioTimerUtil.h"
#include "GitsnDSRCMsgTestScenarioMsg.h"
#include "GitsnDSRCMsgTestScenarioProc.h"

#include <GitsnDSRCMsgTestScenario.h>
#include <GitsnDSRCMsgTestScenarioDefJson.h>

static Dz1Error GitsnDSRCMsgTestScenario_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	GitsnDSRCMsgTestScenarioArg *arg = (GitsnDSRCMsgTestScenarioArg *)uArg;
	GitsnDSRCMsgTestScenarioEnv *env = NULL;

	if (((*uRsc) = env = GitsnDSRCMsgTestScenarioEnv_new(tSelf, arg->tMain, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestScenarioEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = GitsnDSRCMsgTestScenarioDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (GitsnDSRCMsgTestScenarioEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void GitsnDSRCMsgTestScenario_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	GitsnDSRCMsgTestScenarioArg *arg = (GitsnDSRCMsgTestScenarioArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void GitsnDSRCMsgTestScenario_cleanup(void *uRsc)
{
	GitsnDSRCMsgTestScenarioEnv *env = (GitsnDSRCMsgTestScenarioEnv *)uRsc;
	// Individual Cleanup Code Here
	GitsnDSRCMsgTestScenarioEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg *arg = (GitsnDSRCMsgTestScenarioArg *)uArg;
	GitsnDSRCMsgTestScenarioEnv *env = (GitsnDSRCMsgTestScenarioEnv *)uRsc;

	if (GitsnDSRCMsgTestScenarioEnvUtil_sendUIConfigure(env, arg->testScenario, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *GitsnDSRCMsgTestScenario_new(void *tMain, Dz1Str testScenario, GitsnDSRCMsgTestScenarioException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgTestScenarioArg *arg = GitsnDSRCMsgTestScenarioArg_new(tMain, testScenario, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgTestScenarioArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("GitsnDSRCMsgTestScenario" , 1024,
							   (void **)&arg, (Dz1DelFunc)GitsnDSRCMsgTestScenarioArg_del,
							   (Dz1CmpFunc)GitsnDSRCMsgTestScenarioTimer_cmp,
							   GitsnDSRCMsgTestScenario_init,
							   GitsnDSRCMsgTestScenario_exception,
							   GitsnDSRCMsgTestScenario_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (GitsnDSRCMsgTestScenario_commandMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (GitsnDSRCMsgTestScenarioProc_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (GitsnDSRCMsgTestScenarioObu2Rsu_sockMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (GitsnDSRCMsgTestScenarioArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void GitsnDSRCMsgTestScenario_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
