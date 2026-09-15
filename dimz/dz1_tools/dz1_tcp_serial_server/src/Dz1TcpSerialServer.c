#include <dz1_socket_acceptor.h>
#include <Dz1SockUtil.h>

#include "Dz1TcpSerialServerArg.h"
#include "Dz1TcpSerialServerEnvUtil.h"
#include "Dz1TcpSerialServerTimerUtil.h"
#include "Dz1TcpSerialServerMsg.h"
#include "Dz1TcpSerialServerSerialIO.h"
#include "Dz1TcpSerialServerSocketIO.h"

#include <Dz1TcpSerialServer.h>

static Dz1Error _open_preset_port(void *ptr, Dz1TcpSerialServerPreset *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)ptr;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1TcpSerialServerPresetPortList *presets = env->presets;
	Dz1TcpSerialServerPresetPort *node = Dz1TcpSerialServerPresetPort_new(p->serialPort, -1, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPresetPort_delAndSetNull, (void *)&node);
		if ((node->thid = Dz1SockUtilAcceptorForTask_start(node->presetPortNum, p->presetListen, myQueueID, errp)) == -1) ERR_OUT(errp);
		else if ((*errp = presets->add(presets, node)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			node = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerPresetPort_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error Dz1TcpSerialServer_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	Dz1TcpSerialServerArg *arg = (Dz1TcpSerialServerArg *)uArg;
	Dz1TcpSerialServerConfig *cfg = arg->config;
	Dz1TcpSerialServerEnv *env = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (((*uRsc) = env = Dz1TcpSerialServerEnv_new(tSelf, -1, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
		else if ((env->emulator = Dz1SockUtilAcceptorForTask_start(0, cfg->emulater, my_queue_id, errp)) == -1) ERR_OUT(errp);
		else if ((*errp = cfg->presets->travel(cfg->presets, _open_preset_port, env)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(&err, 0);
		}
		pthread_cleanup_pop(err.code); // (Dz1TcpSerialServerEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void Dz1TcpSerialServer_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1TcpSerialServerArg *arg = (Dz1TcpSerialServerArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static Dz1Error _close_preset(void *ptr, Dz1TcpSerialServerPresetPort *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p->thid != -1) Dz1TcpSocketAcceptor_stop(p->thid);
	p->thid = -1;
	return err;
}

static Dz1Error _serial_cleanup(void *ptr, Dz1TcpSerialServerSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->serial != NULL)
		Dz1TcpSerialServerSerial_cleanupAndSetNull(&p->serial);
	return err;
}

static void Dz1TcpSerialServer_cleanup(void *uRsc)
{
	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	// Individual Cleanup Code Here
	if (env->emulator != -1) Dz1TcpSocketAcceptor_stop(env->emulator); env->emulator = -1;

	env->presets->travel(env->presets, _close_preset, NULL);
	env->sessions->travel(env->sessions, _serial_cleanup, NULL);

	Dz1TcpSerialServerEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

void *Dz1TcpSerialServer_new(Dz1TcpSerialServerConfig *cfg, Dz1TcpSerialServerException e, void *eArg, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialServerArg *arg = Dz1TcpSerialServerArg_new(NULL, e, eArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerArg_delAndSetNull, (void *)&arg);
		if ((arg->config = Dz1TcpSerialServerConfig_clone(cfg, errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1Task_new("Dz1TcpSerialServer", 1024,
									(void **)&arg, (Dz1DelFunc)Dz1TcpSerialServerArg_del,
									(Dz1CmpFunc)Dz1TcpSerialServerTimer_cmp,
									Dz1TcpSerialServer_init,
									Dz1TcpSerialServer_exception,
									Dz1TcpSerialServer_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpSerialServerSerialIO_init(ret)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpSerialServerSocketIO_init(ret)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Dz1TcpSerialServer_del(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (task == NULL) return;
	else if ((err = Dz1Task_del(task)).code) ERR_OUT(&err);
}
