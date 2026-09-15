#include <dz1_task.h>

#include "Itsk00126v1EmulatorArg.h"
#include "Itsk00126v1EmulatorEnv.h"
#include "Itsk00126v1EmulatorTimerUtil.h"
#include "Itsk00126v1EmulatorMsg.h"

#include <Itsk00126v1Emulator.h>
#include <Itsk00126v1EmulatorDefJson.h>





static Dz1Error Itsk00126V1Emulator_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//Itsk00126V1EmulatorArg *arg = (Itsk00126V1EmulatorArg *)uArg;
	Itsk00126V1EmulatorEnv *env = NULL;

	if (((*uRsc) = env = Itsk00126V1EmulatorEnv_new(tSelf, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{

		pthread_cleanup_push(Itsk00126V1EmulatorEnv_delAndSetNull,(void *)uRsc);
		if (0) {}
		else if ((env->spec = Itsk00126v1EmulatorDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, ITSK00126_V1_EMULATOR_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Itsk00126V1EmulatorEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Itsk00126V1Emulator_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Itsk00126V1EmulatorArg *arg = (Itsk00126V1EmulatorArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void Itsk00126V1Emulator_cleanup(void *uRsc)
{
	Itsk00126V1EmulatorEnv *env = (Itsk00126V1EmulatorEnv *)uRsc;
	// Individual Cleanup Code Here
	Itsk00126V1EmulatorEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// Itsk00126V1EmulatorArg *arg = (Itsk00126V1EmulatorArg *)uArg;
	// Itsk00126V1EmulatorEnv *env = (Itsk00126V1EmulatorEnv *)uRsc;

	return ret;
}

void *Itsk00126V1Emulator_new(Itsk00126V1EmulatorException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126V1EmulatorArg *arg = Itsk00126V1EmulatorArg_new(e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126V1EmulatorArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Itsk00126V1Emulator" , 1024,
							   (void **)&arg, (Dz1DelFunc)Itsk00126V1EmulatorArg_del,
							   (Dz1CmpFunc)Itsk00126V1EmulatorTimer_cmp,
							   Itsk00126V1Emulator_init,
							   Itsk00126V1Emulator_exception,
							   Itsk00126V1Emulator_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITSK00126_V1_EMULATOR_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (Itsk00126v1EmulatorClient_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Itsk00126V1EmulatorArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Itsk00126V1Emulator_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
