#include <dz1_task.h>
#include <Dz1SockUtil.h>

#include "GitsnOpenApiArg.h"
#include "GitsnOpenApiEnv.h"
#include "GitsnOpenApiTimerUtil.h"
#include "GitsnOpenApiMsg.h"

#include "GitsnOpenApi_acceptor.h"
#include "GitsnOpenApi_servant.h"

#include "GitsnOpenApi.h"

static bool_t _prepare_acceptor(GitsnOpenApiEnv *env, Dz1SockAddr *addr, Dz1Error *errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((env->acceptor = Dz1SockUtilAcceptorForTask_start(0, addr, my_queue_id, errp)) == (u32_t)-1) ERR_SET_OUT(errp, EINVAL);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static Dz1Error GitsnOpenApi_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = NULL;

	if (((*uRsc) = env = GitsnOpenApiEnv_new(tSelf, -1, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiEnv_delAndSetNull,(void *)uRsc);
		if (0) { }
		else if ((env->sessions = GitsnOpenApiSessions_gen(errp)) == NULL) ERR_OUT(errp);
		else if (_prepare_acceptor(env, arg->listen_addr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Task_postSimple(tSelf, DZ1_TASK_QUEUE_NONE, GITSN_OPEN_API_DO_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiEnv_delAndSetNull,(void *)uRsc);
	}

	return err;
}

static void GitsnOpenApi_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	if (arg->exceptionProc)
		arg->exceptionProc(arg->exceptionArg, reason);
}

static void GitsnOpenApi_cleanup(void *uRsc)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	// Individual Cleanup Code Here
	if (env->acceptor != -1)
	{
		if ((*errp = Dz1TcpSocketAcceptor_stop(env->acceptor)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		env->acceptor = -1;
	}
	GitsnOpenApiEnv_del(env);
}

static Dz1TaskProcStatus _doDefault(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	// GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// GITSN_OPEN_API_DO_RESPONSE
static Dz1TaskProcStatus _userResponse(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{	// Task work starting point
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;

	GitsnOpenApiMsg *msg = (GitsnOpenApiMsg *)Dz1TaskSigMsg_getData(*sg);
	GitsnOpenApiHttpMsg *ctx = msg->ctx;
	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else switch(ctx->present)
	{
	case GitsnOpenApiHttpMsgPresent_req: ERR_SET_OUT(errp, EPERM); break;
	case GitsnOpenApiHttpMsgPresent_rsp:
		if (GitsnOpenApi_servantDoRsp(uArg, uRsc, timer, msg->session_id, ctx->x.rsp, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1TaskSigMsg_getType((Dz1TaskSigMsg *)*sg) == GITSN_OPEN_API_DO_RESPONSE_ASYNC) Dz1Error_set(errp, 0);
		else if (GitsnOpenApi_servantDeferResponse(uRsc, timer, msg->session_id, sg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case GitsnOpenApiHttpMsgPresent_ws_payload:
		if (GitsnOpenApi_servantWsSend(uArg, uRsc, timer, msg->session_id, ctx->x.ws_payload, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: GitsnOpenApi_servantRemoveSession(uArg, uRsc, timer, msg->session_id, NULL); Dz1Error_set(errp, 0); break;
	}

	return ret;
}

bool_t GitsnOpenApi_httpResponse(Dz1Task *task, u32_t session_id, GitsnOpenApiHttpRsp *rsp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t task_thid;
	if (task == NULL || rsp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((task_thid = Dz1Task_getThread(task)) == DZ1_THREAD_INVALID) ERR_SET_OUT(errp, ENOSYS);
	else if (task_thid == Dz1Thread_self()) ERR_SET_OUT(errp, EDEADLK);
	else
	{
		GitsnOpenApiHttpMsg ctx = { GitsnOpenApiHttpMsgPresent_rsp, { rsp } };
		GitsnOpenApiMsg msg = { session_id, &ctx };

		u32_t log_lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_DEBUG) { Dz1Thread_printf(Dz1T(">>> Send Response = ")); GitsnOpenApiHttpRsp_dump(rsp, 0); }

		if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE,
								GITSN_OPEN_API_DO_RESPONSE, (void *)&msg,
								GitsnOpenApiMsg_dump, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApi_webSockSend(Dz1Task *task, u32_t session_id, Dz1Binary *bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t task_thid;
	if (task == NULL || bin == NULL || bin->data != NULL || bin->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((task_thid = Dz1Task_getThread(task)) == DZ1_THREAD_INVALID) ERR_SET_OUT(errp, ENOSYS);
	else if (task_thid == Dz1Thread_self()) ERR_SET_OUT(errp, EDEADLK);
	else
	{
		GitsnOpenApiHttpMsg ctx = { GitsnOpenApiHttpMsgPresent_ws_payload, { bin } };
		GitsnOpenApiMsg msg = { session_id, &ctx };
		if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE,
								GITSN_OPEN_API_DO_RESPONSE, (void *)&msg,
								GitsnOpenApiMsg_dump, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApi_noResponse(Dz1Task *task, u32_t session_id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t task_thid;
	if (task == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((task_thid = Dz1Task_getThread(task)) == DZ1_THREAD_INVALID) ERR_SET_OUT(errp, ENOSYS);
	else if (task_thid == Dz1Thread_self()) ERR_SET_OUT(errp, EDEADLK);
	else
	{
		GitsnOpenApiHttpMsg ctx = { GitsnOpenApiHttpMsgPresent_max, { NULL } };
		GitsnOpenApiMsg msg = { session_id, &ctx };
		if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE,
								GITSN_OPEN_API_DO_RESPONSE, (void *)&msg,
								GitsnOpenApiMsg_dump, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// GITSN_OPEN_API_DO_RESPONSE
///////////////////////////////////////////////////////////////////////////////

void *GitsnOpenApi_newWithOptions(Dz1SockAddr *listen_addr, str_t server_name_u8, GitsnOpenApiCallback cb, void *cb_arg,
	GitsnOpenApiException e, void *eArg, const GitsnOpenApiServerOptions *options, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiArg *arg = NULL;
	
	if ((arg = GitsnOpenApiArg_new(NULL, server_name_u8, cb, cb_arg, e, eArg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiArg_delAndSetNull, (void *)&arg);
		if (options != NULL)
		{
			arg->server_idle_timeout_ms = options->server_idle_timeout_ms;
			arg->advertise_keep_alive = options->advertise_keep_alive;
			arg->connection_cb = options->connection_cb;
			arg->connection_cb_arg = options->connection_cb_arg;
		}
		if ((arg->listen_addr = Dz1SockAddr_clone(listen_addr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1Task_new("GitsnOpenApi" , 1024,
							   (void **)&arg, (Dz1DelFunc)GitsnOpenApiArg_del,
							   (Dz1CmpFunc)GitsnOpenApiTimer_cmp,
							   GitsnOpenApi_init,
							   GitsnOpenApi_exception,
							   GitsnOpenApi_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(GITSN_OPEN_API_DO_DEFAULT), _doDefault)).code) ERR_OUT(errp);

			else if (GitsnOpenApi_acceptorMsgInit(ret, errp) == FALSE) ERR_OUT(errp);
			else if (GitsnOpenApi_servantMsgInit(ret, errp) == FALSE) ERR_OUT(errp);

			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(GITSN_OPEN_API_DO_RESPONSE), _userResponse)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(GITSN_OPEN_API_DO_RESPONSE_ASYNC), _userResponse)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void *GitsnOpenApi_new(Dz1SockAddr *listen_addr, str_t server_name_u8, GitsnOpenApiCallback cb, void *cb_arg,
	GitsnOpenApiException e, void *eArg, Dz1Error *err)
{
	return GitsnOpenApi_newWithOptions(listen_addr, server_name_u8, cb, cb_arg, e, eArg, NULL, err);
}

void GitsnOpenApi_del(void *task)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (task == NULL) return;
	else if ((*errp = Dz1Task_del(task)).code) ERR_OUT(errp);
}
