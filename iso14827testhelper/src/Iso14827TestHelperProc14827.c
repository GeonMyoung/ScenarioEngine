#include <dz1_asn1.h>
#include <ItsIso14827TaskSupport.h>

#include "Iso14827TestHelperArg.h"
#include "Iso14827TestHelperEnv.h"
// #include "Iso14827TestMsg.h"

#include "Iso14827TestHelper.h"
#include "Iso14827TestHelperScenario.h"

#include "Iso14827TestHelperProc14827.h"


static Dz1TaskProcStatus _server_auth(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 클라이언트가 Login 하려고 함
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventAuth* msg = (ItsIso14827ServerEventAuth*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_auth, msg, errp) == FALSE)
	{
		if (errp->code |= ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827RejectLogin_unknownDomainName);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}


static Dz1TaskProcStatus _server_connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 클라이언트가 로그인에 성공함
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventConnected* msg = (ItsIso14827ServerEventConnected*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_connected, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_terminateClient(arg->t14827, msg->myDomain, msg->peerDomain, msg->user);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _server_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 클라이언트 접속 해제
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827EventDisconnected* msg = (ItsIso14827EventDisconnected*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_logout, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _server_echo(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 허트비트가 수신됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventEcho* msg = (ItsIso14827ServerEventEcho*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_heartbeat, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _server_single(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 단일 서브스크립션 요청됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubSignle* msg = (ItsIso14827ServerEventSubSignle*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_req_single, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_prepareReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _server_ed_prepare(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 이벤트 서브스크립션 요청됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubPrepareED* msg = (ItsIso14827ServerEventSubPrepareED*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_req_event_driven, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_prepareReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _server_pr_prepare(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 주기형 서브스크립션 요청됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventSubPrepareP* msg = (ItsIso14827ServerEventSubPrepareP*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_req_periodic, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_prepareReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _server_pub_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 서브스크립션 시작/재개
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStart* msg = (ItsIso14827ServerEventPubStart*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_data_start, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _server_pub_invoke(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 퍼블리케이션 주기 도래
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStart* msg = (ItsIso14827ServerEventPubStart*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_data_period, msg, NULL);

	return ret;
}



static Dz1TaskProcStatus _server_pub_inform(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 서브스크립션 취소/관리
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubInform* msg = (ItsIso14827ServerEventPubInform*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_pubdata_rejected, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _server_pub_stopped(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 서브스크립션 일시 정지
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubStop* msg = (ItsIso14827ServerEventPubStop*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_data_stop, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _server_pub_expired(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 서브스크립션 만료
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ServerEventPubExpire* msg = (ItsIso14827ServerEventPubExpire*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestServerEvent_req_expired, msg, NULL);
	return ret;
}

static Dz1TaskProcStatus _server_overloaded(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	return ret;
}
static ItsIso14827ServerTaskHandler _server_handler =
{
	_server_auth,
	_server_connected,
	_server_disconnected,
	_server_echo,
	_server_single,
	_server_ed_prepare,
	_server_pr_prepare,
	_server_pub_start,
	_server_pub_invoke,
	_server_pub_inform,
	_server_pub_stopped,
	_server_pub_expired,
	_server_overloaded
};



static Dz1TaskProcStatus _client_initiate(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// Login 요청이 수신됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827ClientEventInitiate* msg = (ItsIso14827ClientEventInitiate*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_initiated, msg, NULL);
	return ret;
}

static Dz1TaskProcStatus _client_echo(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// Heartbeat에 대한 응답을 수신함
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827EventDisconnected* msg = (ItsIso14827EventDisconnected*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_echo, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_disconnectFromServer(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827Logout_clientShutdown);
			Dz1Error_set(errp, 0);
		}

	}
	return ret;
}

static Dz1TaskProcStatus _client_terminate(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 접속 해제 요청이 수신됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ClientEventTerminate* msg = (ItsIso14827ClientEventTerminate*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_terminate, msg, errp) == FALSE)
	{
		if (errp->code != ENOSYS) ERR_OUT(errp);
		else
		{
			ItsIso14827_disconnectFromServer(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827Logout_serverRequested);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _client_publication(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 퍼블리케이션이 수신됨
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ClientEventPublication* msg = (ItsIso14827ClientEventPublication*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_data, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _client_pub_control(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	//서브스크립션 취소/관리
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827ClientEventPubControl* msg = (ItsIso14827ClientEventPubControl*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_data_ctrl, msg, NULL);

	return ret;
}

static Dz1TaskProcStatus _client_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	// 서버와 연결이 끊어짐
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827EventDisconnected* msg = (ItsIso14827EventDisconnected*)Dz1TaskSigMsg_getData(*sg);

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario_proc14827(arg, env, timer, Iso14827TestClientEvent_disconnected, msg, NULL);
	return ret;
}

static ItsIso14827ClientTaskHandler _client_handler =
{
	_client_initiate,
	_client_echo,
	_client_terminate,
	_client_publication,
	_client_pub_control,
	_client_disconnected,
};


bool_t Iso14827TestHelperProc14827_init(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = ItsIso14827_bothTaskMsgInit(task, &_server_handler, &_client_handler)).code) ERR_OUT(errp);
	//else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TECHNICAL_REGULATION1_14827_PUB_RCVD), _server_recv_pub)).code) ERR_OUT(errp);
	//else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TECHNICAL_REGULATION1_14827_SUB_RCVD), _client_recv_sub)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
