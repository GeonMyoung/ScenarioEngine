#include <dz1_task.h>

#include "ITSK00144_2EmulatorArg.h"
#include "ITSK00144_2EmulatorEnv.h"
#include "ITSK00144_2EmulatorTimerUtil.h"
#include "ITSK00144_2EmulatorMsg.h"

#include <ITSK00144_2Emulator.h>
#include <ITSK00144_2TestMsgSample.h>
#include <GitsnAsnUtilSampleMsg.h>

static Dz1Error ITSK001442Emulator_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//ITSK001442EmulatorArg *arg = (ITSK001442EmulatorArg *)uArg;
	ITSK001442EmulatorEnv *env = NULL;

	if (((*uRsc) = env = ITSK001442EmulatorEnv_new(tSelf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, ITSK00144_2_EMULATOR_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ITSK001442EmulatorEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void ITSK001442Emulator_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	ITSK001442EmulatorArg *arg = (ITSK001442EmulatorArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void ITSK001442Emulator_cleanup(void *uRsc)
{
	ITSK001442EmulatorEnv *env = (ITSK001442EmulatorEnv *)uRsc;
	// Individual Cleanup Code Here
	ITSK001442EmulatorEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// ITSK001442EmulatorArg *arg = (ITSK001442EmulatorArg *)uArg;
	// ITSK001442EmulatorEnv *env = (ITSK001442EmulatorEnv *)uRsc;
	if (ITSK00144_2TestMsg_initSample(errp) == FALSE) ERR_OUT(errp);
	else if (GitsnAsnUtil_initSample(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *ITSK001442Emulator_new(ITSK001442EmulatorException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK001442EmulatorArg *arg = ITSK001442EmulatorArg_new(e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK001442EmulatorArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("ITSK001442Emulator" , 1024,
							   (void **)&arg, (Dz1DelFunc)ITSK001442EmulatorArg_del,
							   (Dz1CmpFunc)ITSK001442EmulatorTimer_cmp,
							   ITSK001442Emulator_init,
							   ITSK001442Emulator_exception,
							   ITSK001442Emulator_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITSK00144_2_EMULATOR_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (ITSK00144_2EmulatorClient_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (ITSK00144_2EmulatorServer_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (ITSK001442EmulatorArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ITSK001442Emulator_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
