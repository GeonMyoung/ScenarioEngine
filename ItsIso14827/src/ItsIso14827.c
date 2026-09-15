#include <dz1_task.h>
#include "ItsIso14827_license.h"

#include "ItsIso14827Arg.h"
#include "ItsIso14827Env.h"
#include "ItsIso14827Timer.h"
#include "ItsIso14827Msg.h"

#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827SessionMgr_main.h"

#include <ItsIso14827.h>

static Dz1Error ItsIso14827_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer)
{
	ItsIso14827Env *env = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (((*uRsc) = env = ItsIso14827Env_new(tSelf, NULL, NULL, ITS_ISO14827_PACKET_DUMP_DEFAULT, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827Env_delAndSetNull,(void *)uRsc);
		if (0) { }
		else if ((env->domainMgr = ItsIso14827DomainMgr_init(tSelf, &err)) == NULL) ERR_OUT(&err);
		else if ((env->sessionMgr = ItsIso14827SessionMgr_init(tSelf, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1Error_set(&err, 0);
		}
		pthread_cleanup_pop(err.code); // (ItsIso14827Env_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void ItsIso14827_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	ItsIso14827Arg *arg = (ItsIso14827Arg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void ItsIso14827_cleanup(void *uRsc)
{
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	// Individual Cleanup Code Here
	ItsIso14827SessionMgr_cleanup(env->sessionMgr); env->sessionMgr = NULL;
	ItsIso14827DomainMgr_terminate(env->domainMgr); env->domainMgr = NULL;
	ItsISo14827SessionMgr_terminate(env->sessionMgr); env->sessionMgr = NULL;
	ItsIso14827Env_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

static Dz1TaskProcStatus _openPort(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *mgr = env->domainMgr;
	ItsIso14827DomainList *domains = mgr->domains;

	ItsIso14827OpenPort *msg = (ItsIso14827OpenPort *)Dz1TaskSigMsg_getData(*sg);

	if (domains->count(domains) == 0) ERR_SET_OUT(errp, ENOENT);
	else if ((*errp = ItsIso14827SessionMgr_openPort(env->sessionMgr, msg->port, msg->initialCodec, msg->initialCRCMode)).code) ERR_OUT(errp);

	return ret;
}

static Dz1TaskProcStatus _closePort(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ClosePort *msg = (ItsIso14827ClosePort *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827SessionMgr_closePort(env->sessionMgr, msg->port);

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DEBUG_STATUS
typedef struct DebugStatusArg
{
	ItsIso14827DomainPresent present;
	int tab;
} DebugStatusArg;

static Dz1Error __debugStatus(void *ptr, ItsIso14827Domain *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	DebugStatusArg *arg = (DebugStatusArg *)ptr;
	if (p->present == arg->present)
	{
		Dz1Thread_tprintf(arg->tab, Dz1T("domain = "));
		switch(p->present)
		{
		case ItsIso14827DomainPresent_server: ItsIso14827ServerDomain_dump(p->x.server, arg->tab); break;
		case ItsIso14827DomainPresent_client: ItsIso14827ClientDomain_dump(p->x.client, arg->tab); break;
		default: Dz1Thread_printf(Dz1T("unknown type(%d)\n"), p->present);
		}
	}
	return err;
}

static void ItsIso14827DomainMgr_dumpKind(ItsIso14827DomainMgr *p, int tab, ItsIso14827DomainType type)
{
	ItsIso14827DomainList *list = NULL;
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else if ((list = p->domains) == NULL) Dz1Thread_printf(Dz1T("[ NULL ]\n"));
	else
	{
		DebugStatusArg arg = { ItsIso14827DomainPresent_max, tab };
		switch(type)
		{
		case ItsIso14827DomainType_server: arg.present = ItsIso14827DomainPresent_server; break;
		case ItsIso14827DomainType_client: arg.present = ItsIso14827DomainPresent_client; break;
		default: Dz1Thread_printf(Dz1T("Unknown domain type = %d\n"), type); return;
		}

		Dz1Thread_printf(Dz1T("{\n")); tab++;

		list->travel(list, __debugStatus, (void *)&arg);

		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}

static Dz1TaskProcStatus _debugStatus(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *mgr = env->domainMgr;

	ItsIso14827DebugStatus *msg = (ItsIso14827DebugStatus *)Dz1TaskSigMsg_getData(*sg);

	if (msg->type == ItsIso14827DomainType_max)
	{
		Dz1Thread_printf("Entire Domain Status = ");
		ItsIso14827DomainMgr_dump(mgr, 0);
	}
	else if (msg->myDomain == NULL)
	{
		Dz1Thread_printf(Dz1T("Entire %s Domain Status = "), ItsIso14827DomainTypeStr(msg->type));
		ItsIso14827DomainMgr_dumpKind(mgr, 0, msg->type);
	}
	else
	{
		ItsIso14827DomainKey key = { msg->type, msg->myDomain };
		ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, &key);

		if (domain == NULL)
		{
			Dz1Thread_printf("ItsIso14827 DEBUG Status = No Such Domain = "); 
			ItsIso14827DebugStatus_dump(msg, 0);
		}
		else
		{
			Dz1Thread_printf("Domain Status = ");
			ItsIso14827Domain_dump(domain, 0);
		}
	}
	Dz1Thread_printf("Session Manager = ");
	ItsIso14827SessionMgr_dump(env->sessionMgr, 0);
	return ret;
}

Dz1Error ItsIso14827_debugStatus(void *t14827, ItsIso14827DomainType type, Dz1Asn1UTF8Str *domainName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827DebugStatus *msg = ItsIso14827DebugStatus_new(type, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DebugStatus_delAndSetNull, (void *)&msg);
		if (domainName != NULL && (msg->myDomain = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO_14827_DEBUG_STATUS, (void *)msg,
									(Dz1DumpFunc)ItsIso14827DebugStatus_dump,
									NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DebugStatus_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO_14827_DEBUG_STATUS
///////////////////////////////////////////////////////////////////////////////

static Dz1Error ItsIso14827_pktDump(void *t14827, u32_t cmd, u32_t flag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DebugPktDump *msg = ItsIso14827DebugPktDump_new(flag, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DebugPktDump_delAndSetNull, (void *)&msg);
		if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
								cmd, (void **)&msg,
								(Dz1DelFunc)ItsIso14827DebugPktDump_del,
								(Dz1DumpFunc)ItsIso14827DebugPktDump_dump,
								NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DebugPktDump_delAndSetNull, (void *)&msg);
	}

	return err;
}

static Dz1TaskProcStatus _debugPktDumpOn(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DebugPktDump *msg = (ItsIso14827DebugPktDump *)Dz1TaskSigMsg_getData(*sg);

	env->pktDumpFlag |= msg->flag;
	env->sessionMgr->debug_dump = (env->pktDumpFlag & ITS_ISO14827_SESSION_DUMP) ? TRUE : FALSE;

	return ret;
}

Dz1Error ItsIso14827_pktDumpOn(void *t14827, u32_t flag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = ItsIso14827_pktDump(t14827, ITS_ISO_14827_DEBUG_PKT_DUMP_ON, flag)).code) ERR_OUT(&err);
	return err;
}

static Dz1TaskProcStatus _debugPktDumpOff(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DebugPktDump *msg = (ItsIso14827DebugPktDump *)Dz1TaskSigMsg_getData(*sg);

	env->pktDumpFlag &= (~msg->flag);
	env->sessionMgr->debug_dump = (env->pktDumpFlag & ITS_ISO14827_SESSION_DUMP) ? TRUE : FALSE;

	return ret;
}

Dz1Error ItsIso14827_pktDumpOff(void *t14827, u32_t flag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = ItsIso14827_pktDump(t14827, ITS_ISO_14827_DEBUG_PKT_DUMP_OFF, flag)).code) ERR_OUT(&err);
	return err;
}

static Dz1TaskProcStatus _debugPktDumpSet(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DebugPktDump *msg = (ItsIso14827DebugPktDump *)Dz1TaskSigMsg_getData(*sg);

	env->pktDumpFlag = msg->flag;
	env->sessionMgr->debug_dump = (env->pktDumpFlag & ITS_ISO14827_SESSION_DUMP) ? TRUE : FALSE;

	return ret;
}

Dz1Error ItsIso14827_pktDumpSet(void *t14827, u32_t flag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = ItsIso14827_pktDump(t14827, ITS_ISO_14827_DEBUG_PKT_DUMP_SET, flag)).code) ERR_OUT(&err);
	return err;
}

void *ItsIso14827_new(ItsIso14827Exception exceptionProc, void *exceptionArg, Dz1Error *err)
{
	void *ret = NULL;
	ItsIso14827Arg *arg = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	//Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "pattern = %p\n", license_ItsIso14827_pattern);

	if (0) { }
	//else if (GitsnLicenseChk_execute(license_ItsIso14827_preamble1, license_ItsIso14827_preamble2, license_ItsIso14827_pattern, errp) == FALSE) ERR_OUT(errp);
	else if ((arg = ItsIso14827Arg_new(exceptionProc, exceptionArg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827Arg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new((str_t)"ItsIso14827", 1024,
							   (void **)&arg, (Dz1DelFunc)ItsIso14827Arg_del,
							   (Dz1CmpFunc)ItsIso14827Timer_cmp,
							   ItsIso14827_init,
							   ItsIso14827_exception,
							   ItsIso14827_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_OPEN_PORT), _openPort)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_CLOSE_PORT), _closePort)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DEBUG_STATUS), _debugStatus)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DEBUG_PKT_DUMP_ON), _debugPktDumpOn)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DEBUG_PKT_DUMP_OFF), _debugPktDumpOff)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DEBUG_PKT_DUMP_SET), _debugPktDumpSet)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (ItsIso14827Arg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ItsIso14827_del(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (task == NULL) return;
	else if ((err = Dz1Task_del(task)).code) ERR_OUT(&err);
}

Dz1Error ItsIso14827_openPort(void *t14827, u16_t port, Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (t14827 == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (initialCodec <= 0 || initialCodec >= Dz1Asn1Codec_max) { Dz1Thread_printf("invalid code = %d\n", initialCodec); ERR_SET_OUT(errp, EINVAL); }
	else if (initialCRCMode < 0 || initialCRCMode >= ItsIso14827CRCCheck_max) { Dz1Thread_printf("invalid CRC mode = %d\n", initialCRCMode); ERR_SET_OUT(&err, EINVAL); }
	else
	{
		ItsIso14827OpenPort *msg = ItsIso14827OpenPort_new(port, initialCodec, initialCRCMode, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827OpenPort_delAndSetNull, (void *)&msg);
			if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_OPEN_PORT, (void *)msg,
									(Dz1DumpFunc)ItsIso14827OpenPort_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827OpenPort_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

Dz1Error ItsIso14827_closePort(void *t14827, u16_t port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827ClosePort *msg = ItsIso14827ClosePort_new(port, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827OpenPort_delAndSetNull, (void *)&msg);
			if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_CLOSE_PORT, (void *)msg,
									(Dz1DumpFunc)ItsIso14827ClosePort_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827OpenPort_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}