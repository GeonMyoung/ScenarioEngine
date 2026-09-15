#include <dz1_task.h>

#include "GitsnDsrcEmulatorArg.h"
#include "GitsnDsrcEmulatorEnv.h"
#include "GitsnDsrcEmulatorTimerUtil.h"
#include "GitsnDsrcEmulatorMsg.h"

#include <GitsnDsrcEmulator.h>
#include <GitsnAsnUtilSampleMsg.h>

static Dz1Error GitsnDsrcEmulator_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//GitsnDsrcEmulatorArg *arg = (GitsnDsrcEmulatorArg *)uArg;
	GitsnDsrcEmulatorEnv *env = NULL;

	if (((*uRsc) = env = GitsnDsrcEmulatorEnv_new(tSelf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, GITSN_DSRC_EMULATOR_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (GitsnDsrcEmulatorEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void GitsnDsrcEmulator_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	GitsnDsrcEmulatorArg *arg = (GitsnDsrcEmulatorArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void GitsnDsrcEmulator_cleanup(void *uRsc)
{
	GitsnDsrcEmulatorEnv *env = (GitsnDsrcEmulatorEnv *)uRsc;
	// Individual Cleanup Code Here
	GitsnDsrcEmulatorEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// GitsnDsrcEmulatorArg *arg = (GitsnDsrcEmulatorArg *)uArg;
	// GitsnDsrcEmulatorEnv *env = (GitsnDsrcEmulatorEnv *)uRsc;

	if (GitsnAsnUtil_initSample(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

void *GitsnDsrcEmulator_new(GitsnDsrcEmulatorException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDsrcEmulatorArg *arg = GitsnDsrcEmulatorArg_new(e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("GitsnDsrcEmulator" , 1024,
							   (void **)&arg, (Dz1DelFunc)GitsnDsrcEmulatorArg_del,
							   (Dz1CmpFunc)GitsnDsrcEmulatorTimer_cmp,
							   GitsnDsrcEmulator_init,
							   GitsnDsrcEmulator_exception,
							   GitsnDsrcEmulator_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) {}
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(GITSN_DSRC_EMULATOR_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if (GitsnDsrcmEmulator_msgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (GitsnDsrcEmulator_clientSockMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (GitsnDsrcEmulatorArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void GitsnDsrcEmulator_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
