#include <dz1_task.h>

#include "ScenarioEngineArg.h"
#include "ScenarioEngineEnvUtil.h"
#include "ScenarioEngineTimerUtil.h"
#include "ScenarioEngineMsg.h"

#include <ScenarioEngine.h>

static Dz1Error ScenarioEngine_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ScenarioEngineArg *arg = (ScenarioEngineArg *)uArg;
	ScenarioEngineEnv *env = NULL;

	if (((*uRsc) = env = ScenarioEngineEnv_new(tSelf, NULL, NULL, NULL, 1, 0, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = ScenarioEngineWebSockMsgDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else if ((ScenarioEngineEnv_establishWS(env, arg->ws_server, errp)) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ScenarioEngineEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void ScenarioEngine_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	ScenarioEngineArg *arg = (ScenarioEngineArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void ScenarioEngine_cleanup(void *uRsc)
{
	ScenarioEngineEnv *env = (ScenarioEngineEnv *)uRsc;
	// Individual Cleanup Code Here
	ScenarioEngineEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	 ScenarioEngineArg *arg = (ScenarioEngineArg *)uArg;
	 ScenarioEngineEnv *env = (ScenarioEngineEnv *)uRsc;
	if (ScenarioEngineEnv_sendDescribe(env, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *ScenarioEngine_new(Dz1Asn1UTF8Str *server_uri, ScenarioEngineException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineArg *arg = ScenarioEngineArg_new(server_uri, e , eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("ScenarioEngine" , 1024,
							   (void **)&arg, (Dz1DelFunc)ScenarioEngineArg_del,
							   (Dz1CmpFunc)ScenarioEngineTimer_cmp,
							   ScenarioEngine_init,
							   ScenarioEngine_exception,
							   ScenarioEngine_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (ScenarioEngine_webSockMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (ScenarioEngine_IPCMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (ScenarioEngineArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ScenarioEngine_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
