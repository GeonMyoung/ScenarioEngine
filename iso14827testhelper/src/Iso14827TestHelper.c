#include <dz1_task.h>
#include <ItsIso14827.h>

#include "Iso14827TestHelperArg.h"
#include "Iso14827TestHelperEnv.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperMsg.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperProc14827.h"

// #include <Iso14827TestMsg.h>
#include <Iso14827TestHelper.h>
#include <dz1_gasn_support.h>
#include <Iso14827TestHelperDefJson.h>



static Dz1Error Iso14827TestHelper_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827TestHelperArg *arg = (Iso14827TestHelperArg *)uArg;
	Iso14827TestHelperEnv *env = NULL;

	if (((*uRsc) = env = Iso14827TestHelperEnv_new(tSelf, arg->t14827, arg->tMain, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestHelperEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = Iso14827TestHelperDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->testIdx = 0;
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Iso14827TestHelperEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Iso14827TestHelper_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Iso14827TestHelperArg *arg = (Iso14827TestHelperArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Iso14827TestHelper_cleanup(void *uRsc)
{
	Iso14827TestHelperEnv *env = (Iso14827TestHelperEnv *)uRsc;
	// Individual Cleanup Code Here
	Iso14827TestHelperEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg *arg = (Iso14827TestHelperArg *)uArg;
	Iso14827TestHelperEnv *env = (Iso14827TestHelperEnv *)uRsc;


	if (Iso14827TestHelperEnvUtil_sendUIConfigure(env, arg->testScenario, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}


static void _14827task_exception_handler(void* ptr, Dz1Error* reason)
{
	Dz1Thread_printf(Dz1Text("ItsIso14827 : Exception Catch\n"));
	ERR_OUT(reason);
}

static void* _iso14827_task_init(Dz1Error* errp)
{
	void* ret = NULL;
	if ((ret = ItsIso14827_new(_14827task_exception_handler, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void*)&ret);
		if ((*errp = Dz1Task_start(ret, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void*)ret);
			if (0) {}
			else if ((*errp = ItsIso14827_pktDumpOff(ret, ITS_ISO14827_PACKET_DUMP_ALL)).code) ERR_OUT(errp);
			else if ((*errp = ItsIso14827_pktDumpOn(ret, MY14827_PKT_DUMP_FLAG)).code) ERR_OUT(errp);
			pthread_cleanup_pop(errp->code); // (Dz1Task_startCancel, (void*)&ret);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void*)&ret);
	}
	return ret;
}


void *Iso14827TestHelper_new(void* tMain, Dz1Str testScenario, Iso14827TestHelperException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	/// msg struct는 task생성 parameter로 전달하도록 수정 필요
	Iso14827TestHelperArg *arg = Iso14827TestHelperArg_new(tMain, NULL, testScenario, NULL, DZ1_ASN1_CODEC_BIT_BER, DEFAULT_HB_DUR, DEFAULT_RSP_TIMEOUT, DEFAULT_INITIAL_CODEC, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else if ((arg->t14827 = _iso14827_task_init(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestHelperArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Iso14827TestHelper" , 1024,
							   (void **)&arg, (Dz1DelFunc)Iso14827TestHelperArg_del,
							   (Dz1CmpFunc)Iso14827TestHelperTimer_cmp,
							   Iso14827TestHelper_init,
							   Iso14827TestHelper_exception,
							   Iso14827TestHelper_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (Iso14827TestHelper_commandMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if ((Iso14827TestScenario_msgInit(ret, errp)) == FALSE) ERR_OUT(errp);
			else if ((Iso14827TestHelperProc14827_init(ret, errp)) == FALSE) ERR_OUT(errp);
			else if (Iso14827TestHelper_testMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Iso14827TestHelperArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Iso14827TestHelper_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
