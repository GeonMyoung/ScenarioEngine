#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
// #include <ConformanceMsgUtil.h>

#include "Iso14827TestHelperEnv.h"
#include "Iso14827TestHelperMsg.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperMsgSet.h"
#include <TechnicalRegulation2MsgStructAPI.h>

#define DUO_SERVER_FLAG_CREATED				0x80000000			// need delete server
#define DUO_SERVER_FLAG_PORT_OPENED			0x40000000			// need close port
#define DUO_SERVER_FLAG_CONNECTED			0x20000000			// need terminate

#define DUO_CLIENT_FLAG_CREATED				0x08000000			// need delete client
#define DUO_CLIENT_FLAG_PORT_OPENED			0x04000000			// need close port
#define DUO_CLIENT_FLAG_CONNECTED			0x02000000			// need disconnect

#define DUO_SERVER_FLAG_HEARTBEAD			0x00800000
#define DUO_SERVER_FLAG_SUBSCRIBE			0x00400000
#define DUO_SERVER_FLAG_PUBLICATE			0x00200000

#define DUO_CLIENT_FLAG_HEARTBEAT			0x00080000
#define DUO_CLIENT_FLAG_SUBSCRIBE			0x00040000
#define DUO_CLIENT_FLAG_PUBLICATE			0x00020000
#define DUO_CLIENT_FLAG_TERMINATE			0x00010000

static Dz1Str test_name_test_duo_session = Dz1T("test_duo_session");


///////////////////////////////////////////////////////////////////////////////
// 14827 hook 
static Dz1Asn1UTF8Str* _get_stringify_u8(Dz1JsonSpec* spec, Dz1Str struct_name, void* struct_ptr, Dz1Error* errp)
{
	Dz1Asn1UTF8Str* ret = NULL;
	Dz1Json* json = NULL;
	if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, spec, struct_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
		Dz1Str src = NULL;
		if (Dz1Json_stringify(json, struct_name, struct_ptr, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
		else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
			if ((ret = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
	}
	return ret;
}

static void _14827_hook_func(void* hook_arg, Iso14827C2CAuthMsg* _msg, bool_t* _isReceived)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t isReceived = *_isReceived;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)hook_arg;

	Iso14827TestHelperC2CHookArg* arg = NULL;

	if ((arg = Iso14827TestHelperC2CHookArg_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestHelperC2CHookArg_delAndSetNull, (void*)&arg);
		if ((arg->msg = Iso14827C2CAuthMsg_clone(_msg, errp)) == NULL) ERR_OUT(errp);
		else if ((arg->current_test = Dz1Str_clone(env->current_test, errp)) == NULL) ERR_OUT(errp);
		else
		{
			arg->isReceived = *_isReceived;
			if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, ISO14827_TEST_HELPER_C2C_HOOK, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
			else
			{
				arg = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (Iso14827TestHelperC2CHookArg_delAndSetNull, (void*)&arg);
	}
}
// 14827 hook 
///////////////////////////////////////////////////////////////////////////////


static void _set_state_server(Iso14827TestHelperEnv* env, Iso14827TestDuoSessionServerState new_state)
{
	u32_t v = (u32_t)new_state << 16;
	env->state = (env->state & 0x0000FFFF) | v;
}

static Iso14827TestDuoSessionServerState _get_state_server(Iso14827TestHelperEnv* env)
{
	Iso14827TestDuoSessionServerState ret = (Iso14827TestDuoSessionServerState)((env->state >> 16) & 0xFFFF);
	return ret;
}

static void _set_state_client(Iso14827TestHelperEnv* env, Iso14827TestDuoSessionClientState new_state)
{
	u32_t v = (u32_t)new_state & 0xFFFF;
	env->state = (env->state & 0xFFFF0000) | v;
}

static Iso14827TestDuoSessionClientState _get_state_client(Iso14827TestHelperEnv* env)
{
	Iso14827TestDuoSessionClientState ret = (Iso14827TestDuoSessionClientState)(env->state & 0xFFFF);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// wait START : Duo Server
static bool_t _duo_session_server_initial_passive(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, u16_t port, Dz1Error* errp)
{
	if ((*errp = ItsIso14827_openPort(arg->t14827, port, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		char log[128];
		sprintf(log, Dz1T("SERVER : Port (%d)를 오픈했습니다. 접속 수신을 대기합니다."), port);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Port(%d) opened\n", port);
		env->flags |= DUO_SERVER_FLAG_PORT_OPENED;

		// notift to web
		// duo session server passive port opened!
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_initial_active(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ConfTestSocketAddress* c, Dz1Error* errp)
{
	Dz1SockAddr peer;
	if ((*errp = Dz1SockAddr_setAddrByName(&peer, c->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, c->port)).code) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_connectToClient(arg->t14827, &peer, s->my_domain, s->peer_client_domain, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : INITIATE sent\n");
		// notify to web
		// server initiate sent!

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("SERVER : 시험 대상에게 개시 요청을 전송하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* errp)
{
	Iso14827TestConnection* c = s->s_peer_client;
	switch (c->present)
	{
	case Iso14827TestConnectionPresent_passive:
		if (_duo_session_server_initial_passive(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestConnectionPresent_active:
		if (_duo_session_server_initial_active(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_wait_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;
	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_start:
		if (_duo_session_server_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else
		{
			_set_state_server(env, Iso14827TestDuoSessionServerState_wait_auth);
			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestDuoSessionEvent_logout:
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_wait_start() : EVENT %d(%s) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait START : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Heartbeat received : Duo Server
static bool_t _duo_session_server_heartbeat_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventEcho* msg, Dz1Error* errp)
{
	// notify to web
	// heartbeat 수신 됨!

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("SERVER : 하트비트 응답을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_echoReply(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, msg->echoID)).code) ERR_OUT(errp);
	else
	{
		if ((env->flags & DUO_SERVER_FLAG_HEARTBEAD) == 0)
		{
			env->flags |= DUO_SERVER_FLAG_HEARTBEAD;


		}
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Heartbeat received\n");
		// notify to web
		// echo reply!



		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Heartbeat received : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait AUTHENTICATE : Duo Server
static Iso14827TestAuth auth_func(ItsIso14827ServerEventAuth* msg, Dz1Asn1Codec* selected_codec)
{
	// TBD...
	*selected_codec = Dz1Asn1Codec_ber;
	return Iso14827TestAuth_success;
}

static bool_t _duo_session_server_wait_auth_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventAuth* msg, bool_t* is_authenticated, Dz1Error* errp)
{
	Dz1Asn1Codec selected_codec = Dz1Asn1Codec_max;
	Iso14827TestAuth auth_result = Iso14827TestAuth_max;

	// notify to web
	// login received!

	if (env->user != NULL)
	{
		// 중복 연결시 시험 종료
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Session duplicated\n");
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("SERVER : 중복 로그인 요청입니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827RejectLogin_sessionExist)).code) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);

		// notify to web
		// login reject : session exist
	}
	else if ((auth_result = auth_func(msg, &selected_codec)) == Iso14827TestAuth_success)
	{
		// 인증 성공 (auth check routine tbd...)
		if (selected_codec == Dz1Asn1Codec_max || selected_codec == Dz1Asn1Codec_unknown) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = _ItsIso14827_loginAccept(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, selected_codec, ItsIso14827CRCCheck_warning, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			*is_authenticated = TRUE;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Authenticate success\n");
			// notift to web
			// authenticate success!
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("SERVER : 인증 정보를 확인하여 로그인을 수락합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		// 인증 실패
		Iso14827RejectLogin reason = Iso14827RejectLogin_accessDenied;
		switch (auth_result)
		{
		case Iso14827TestAuth_not_found:
		case Iso14827TestAuth_invalid_passwd:				reason = Iso14827RejectLogin_invalidPassword; break;
		case Iso14827TestAuth_codec_not_support:					reason = Iso14827RejectLogin_other;	break;
		}
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Authenticate failed\n");
		if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, reason)).code) ERR_OUT(errp);
		else
		{
			// notify to web
			// authenticate fail!!!
			Dz1Error_set(errp, 0);
		}
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_wait_auth(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	bool_t go_next_state = FALSE;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_heartbeat:
		if (_duo_session_server_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_auth:
		if (_duo_session_server_wait_auth_received(arg, env, timer, s, (ItsIso14827ServerEventAuth*)_msg, &go_next_state, errp) == FALSE) ERR_OUT(errp);
		else if (go_next_state)
		{
			_set_state_server(env, Iso14827TestDuoSessionServerState_wait_connected);
		}
		else if (Iso14827TestConnection_isPassive(s->s_peer_client)) ERR_SET_OUT(errp, EFAULT); // 패시브에서 인증 실패 -> 오류 -> 시험종료
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_wait_auth() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait AUTHENTICATE : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait CONNECTED : Duo Server
static bool_t _duo_session_server_wait_connected_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventConnected* msg, Dz1Error* errp)
{
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Established\n");
	// notify to web
	// estabalished! (login success)

	env->flags |= DUO_SERVER_FLAG_CONNECTED;
	env->selected_codec = msg->selected;
	if ((env->user = Dz1Asn1OctetStr_clone(msg->user, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_wait_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_heartbeat:
		if (_duo_session_server_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_connected:
		if (_duo_session_server_wait_connected_received(arg, env, timer, s, (ItsIso14827ServerEventConnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_wait_connected() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & DUO_SERVER_FLAG_CONNECTED))
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("SERVER : 서브스크립션 수신 대기 상태로 전환합니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Ready...\n");
		_set_state_server(env, Iso14827TestDuoSessionServerState_established);
	}
	return ERR_IS_SUCCESS(errp);
}
// wait CONNECTED : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Data Provide : Duo Server
static bool_t __duo_session_server_data_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* errp)
{
	Dz1Binary* eam = NULL;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);
	if (0) {}
	else if ((eam = Iso14827TestMsgSet_getPublicationSampleData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_client_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
	else
	{
		// notify to web
		// data provide! (publicaiton)
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("SERVER : 시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);

		_publication_log_dump_(arg->msg_api, oidStr, eam->data, eam->size, env->selected_codec);
		env->flags |= DUO_SERVER_FLAG_PUBLICATE;
		Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&eam);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_registered_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventPubStart* msg, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;
	if ((node = Iso14827TestSubList_findByID(env->subs_reg, s->peer_client_domain, msg->subID)) == NULL)
	{
		if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_client_domain, msg->user, msg->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (__duo_session_server_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_single_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	// 단일 요청에 대한 응답
	if (__duo_session_server_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Data Provide : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PubData Reject received : Duo Server
static bool_t _duo_session_server_pubdata_reject_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventPubInform* msg, Dz1Error* errp)
{
	// just response cancel request
	Iso14827TestSubEntry* reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);
	if (reg_entry != NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Publication canceled(%u = %s)\n", msg->subID, reg_entry->oid);
		// notify to web
		// pub canceled!

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// PubData Reject received : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request expired : Duo Server
static bool_t _duo_session_server_pub_expire_received(Iso14827TestHelperEnv* env, ItsIso14827ServerEventPubExpire* msg, Dz1Error* errp)
{
	ItsIso14827SubscriptionExpireReason* reason = msg->reason;
	Iso14827TestSubEntry* reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);
	if (reg_entry != NULL)
	{
		TCHAR str_reason[64] = Dz1T("unknown");
		switch (reason->present)
		{
		case ItsIso14827SubscriptionExpireReasonPresent_subscriptionExpired: Dz1STRCPY(str_reason, Dz1T("timeout")); break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientDisconnected: Dz1STRCPY(str_reason, Dz1T("client logout")); break;
		case ItsIso14827SubscriptionExpireReasonPresent_clientRequested: Dz1STRCPY(str_reason, Iso14827SubscriptionCancelStrA(reason->x.clientRequested)); break;
		}
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Publication expired(%u = %s) = %s\n", msg->subID, reg_entry->oid, str_reason);
		Dz1Error_set(errp, 0);
		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
	}
	return ERR_IS_SUCCESS(errp);
}
// Request expired : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request Response : Duo Server
static bool_t _duo_session_server_request_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* errp)
{
	int oid_idx = 0;
	Iso14827TestMsgStructAPI* api = NULL;
	char log[128];
	sprintf(log, Dz1T("SERVER : 서브스크립션을 수신하였습니다. 요청 OID : %s"), oidStr);
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Subscription received = %s\n", oidStr);

	// notify to web
	// subscription 수신
	if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, oidStr, &oid_idx)) == NULL)
	{
		// 모르는 OID 수신
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Unknown OID = %s\n", oidStr);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("SERVER : 요청 OID가 유효하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_client_domain, user, subID, Iso14827RejectSubscription_unknownSubscriptionMsgId)).code) ERR_OUT(errp);
		else
		{
			// notify to web
			// single reject : unknown oid
			ERR_SET_OUT(errp, EPERM); // 모르는 OID 허용 안함 -> 오류 -> 시험종료
		}
	}
	// 아는 OID
	else if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_client_domain, user, subID)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : Subscription accepted\n");
		env->flags |= DUO_SERVER_FLAG_SUBSCRIBE;

		// notify to web
		// subscription accept!
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Request Response : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single Request : Duo Server
static bool_t _duo_session_server_single_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	if (_duo_session_server_request_response(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Single Request : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Registered Request : Duo Server
static bool_t _duo_session_server_registered_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Iso14827TestSubType subs_type, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;

	if ((node = Iso14827TestSubList_append(env->subs_reg, s->peer_client_domain, subID, oidStr, subs_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg add_cancel_arg = { env->subs_reg, (void**)&node };
		pthread_cleanup_push(Iso14827TestSubList_addCancel, (void*)&add_cancel_arg);
		if (_duo_session_server_request_response(arg, env, timer, s, user, subID, oidStr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestSubList_addCancel, (void*)&add_cancel_arg);
	}
	return ERR_IS_SUCCESS(errp);
}
// Registered Request : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Event-Driven Request : Duo Server
static bool_t _duo_session_server_event_driven_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubPrepareED* msg, Dz1Error* errp)
{
	// msg->latency_sec
	if (_duo_session_server_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_event_driven, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Event-Driven Request : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Periodic Request received : Duo Server
static bool_t _duo_session_server_periodic_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubPrepareP* msg, Dz1Error* errp)
{
	// msg->periodic_sec;
	if (_duo_session_server_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_periodic, errp) == FALSE)ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Periodic Request received : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ESTABLISHED : Duo Server
static bool_t _duo_session_server_established(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_heartbeat:
		if (_duo_session_server_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_single:
		if (_duo_session_server_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else if (_duo_session_server_single_provide(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_event_driven:
		if (_duo_session_server_event_driven_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareED*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_periodic:
		if (_duo_session_server_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_data_start:
	case Iso14827TestDuoSessionEvent_data_period:
		if (_duo_session_server_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_pubdata_rejected:
		if (_duo_session_server_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_data_stop:
		break;
	case Iso14827TestDuoSessionEvent_req_expired:
		if (_duo_session_server_pub_expire_received(env, (ItsIso14827ServerEventPubExpire*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_wait_established() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & DUO_SERVER_FLAG_HEARTBEAD) && (env->flags & DUO_SERVER_FLAG_SUBSCRIBE) && (env->flags & DUO_SERVER_FLAG_PUBLICATE))
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : test complete...\n");
		// notify to web
		// duo session server test complete!

		_set_state_server(env, Iso14827TestDuoSessionServerState_idle);
	}
	return ERR_IS_SUCCESS(errp);
}
// ESTABLISHED : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IDLE : Duo Server
static bool_t _duo_session_server_complete_auth(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventAuth* msg, Dz1Error* errp)
{
	// always_reject
	if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827RejectLogin_other)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventConnected* msg, Dz1Error* errp)
{
	// always terminate
	if ((*errp = ItsIso14827_terminateClient(arg->t14827, msg->myDomain, msg->peerDomain, msg->user)).code)ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_single_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	// always reject
	if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_ed_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubPrepareED* msg, Dz1Error* errp)
{
	// always reject
	if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_periodic_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventSubPrepareP* msg, Dz1Error* errp)
{
	// always reject
	if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, msg->myDomain, msg->peerDomain, msg->user, msg->subID, Iso14827RejectSubscription_other)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_registered_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ServerEventPubStart* msg, Dz1Error* errp)
{
	// cancel every subscription
	Iso14827TestSubEntry* reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);
	if (reg_entry != NULL)
	{
		if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_client_domain, env->user, msg->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
		else Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_complete_logout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	// cleanup user if it is own session
	if (Dz1Asn1UTF8Str_cmp(s->my_domain, msg->myDomain) == 0 &&
		Dz1Asn1UTF8Str_cmp(s->peer_client_domain, msg->peerDomain) == 0 &&
		env->user != NULL && Dz1Asn1OctetStr_cmp(env->user, msg->user) == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ SERVER : session disconnected\n");
		// notify to web
		// server : session disconnected

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("SERVER : 시험 대상으로부터 로그아웃을 수신하여 세션을 종료합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		Dz1Asn1OctetStr_delAndSetNull(&env->user);
		env->flags &= ~DUO_SERVER_FLAG_CONNECTED;
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_server_idle(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_auth:
		if (_duo_session_server_complete_auth(arg, env, timer, s, (ItsIso14827ServerEventAuth*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_connected:
		if (_duo_session_server_complete_connected(arg, env, timer, s, (ItsIso14827ServerEventConnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_heartbeat:
		if (_duo_session_server_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_single:
		if (_duo_session_server_complete_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_event_driven:
		if (_duo_session_server_complete_ed_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareED*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_req_periodic:
		if (_duo_session_server_complete_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_data_start:
	case Iso14827TestDuoSessionEvent_data_period:
		if (_duo_session_server_complete_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_pubdata_rejected:
		if (_duo_session_server_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_data_stop:
		break;
	case Iso14827TestDuoSessionEvent_req_expired:
		if (_duo_session_server_pub_expire_received(env, (ItsIso14827ServerEventPubExpire*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_logout:
		if (_duo_session_server_complete_logout(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_timeout:
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_idle() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0)
	{
		if (_get_state_client(env) >= Iso14827TestDuoSessionClientState_idle)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "### SERVER : session terminate : client session test complete\n");
			if (env->flags & DUO_SERVER_FLAG_CONNECTED)
			{
				if ((*errp = ItsIso14827_terminateClient(arg->t14827, s->my_domain, s->peer_client_domain, env->user)).code) ERR_OUT(errp);
				else
				{
					// notify to web
					// terminate client!
					_set_state_server(env, Iso14827TestDuoSessionServerState_wait_logout);
				}
			}
			else _set_state_server(env, Iso14827TestDuoSessionServerState_complete);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// IDLE : Duo Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait LOGOUT : Duo Server
static bool_t _duo_session_server_wait_logout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_logout:
		if (_duo_session_server_complete_logout(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_server_wait_logout() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & DUO_SERVER_FLAG_CONNECTED) == 0)
		_set_state_server(env, Iso14827TestDuoSessionServerState_complete);

	return ERR_IS_SUCCESS(errp);
}
// wait LOGOUT : Duo Server
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF duo_server_scenario[] =
{
	_duo_session_server_wait_start,
	_duo_session_server_wait_auth,
	_duo_session_server_wait_connected,
	_duo_session_server_established,
	_duo_session_server_idle,
	_duo_session_server_wait_logout,
	NULL
};

///////////////////////////////////////////////////////////////////////////////
// wait START : Duo Client
static bool_t _duo_session_client_passive_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, u16_t local_port, Dz1Error* errp)
{
	Iso14827TestConnection* sc = s->s_peer_client;
	if (sc->present != Iso14827TestConnectionPresent_passive || sc->x.passive != local_port)
	{
		// 서버와 다른 방식 또는 다른 포트 사용
		if ((*errp = ItsIso14827_openPort(arg->t14827, local_port, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : Port(%d) opened\n", local_port);

			// notify to web
			// CLIENT : port opened!
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		if (sc->present == Iso14827TestConnectionPresent_passive && sc->x.passive == local_port)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : Port(%d) shared with server\n", local_port);

			//notify to web
			// CLIENT share port!
		}
		Dz1Error_set(errp, 0);
	}
	if (errp->code == 0) env->flags |= DUO_CLIENT_FLAG_PORT_OPENED;

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_client_active_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ConfTestSocketAddress* dst, Dz1Error* errp)
{
	Dz1SockAddr peer;
	if ((*errp = Dz1SockAddr_setAddrByName(&peer, dst->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, dst->port)).code) ERR_OUT(errp);
	else
	{
		Dz1Asn1Codec codec = arg->initial_codec;
		Iso14827TestAccount* acc = s->c_account;
		Iso14827RejectLogin result = Iso14827RejectLogin_max;

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : Login(active)...\n");

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("CLIENT : 시험 대상에게 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

		if ((*errp = _ItsIso14827_connectToServer(arg->t14827, &peer, s->my_domain, s->peer_server_domain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code) ERR_OUT(errp);
		else
		{
			env->selected_codec_duo = codec;
			env->flags |= DUO_CLIENT_FLAG_CONNECTED;

			if ((env->server_addr = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT : 로그인을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _duo_session_client_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* errp)
{
	// start event handler
	Iso14827TestConnection* c = s->c_peer_server;
	switch (c->present)
	{
	case Iso14827TestConnectionPresent_passive:
		if (_duo_session_client_passive_prepare(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		else
		{
			_set_state_client(env, Iso14827TestDuoSessionClientState_wait_initiate);
			// notify to web
			// client : wait initiate
			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestConnectionPresent_active:
		if (_duo_session_client_active_login(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else
		{
			_set_state_client(env, Iso14827TestDuoSessionClientState_wait_heartbeat);
			Dz1Error_set(errp, 0);
		}
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_client_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_start:
		if (_duo_session_client_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_initial() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait START : Duo Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait INITIATE : Duo Client
static bool_t _duo_session_client_passive_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ClientEventInitiate* msg, Dz1Error* errp)
{
	ItsIso14827SessionKey* skey = msg->key;
	Dz1Asn1Codec codec = msg->initial_codec;

	Iso14827TestAccount* acc = s->c_account;
	Iso14827RejectLogin result = Iso14827RejectLogin_max;

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$$ CLIENT : Login(passive)...\n");

	// notify to web
	// CLIENT login!

	if ((*errp = _ItsIso14827_bindWithServer(arg->t14827, msg->key, msg->myDomain, msg->peerDomain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, NULL, NULL, &result)).code) ERR_OUT(errp);
	else
	{
		env->selected_codec = codec;
		env->flags |= DUO_CLIENT_FLAG_CONNECTED;

		// notify to web
		// client 접속 완료

		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}


static bool_t _duo_session_client_wait_initiate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_initiated:
		if (_duo_session_client_passive_login(arg, env, timer, s, (ItsIso14827ClientEventInitiate*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_wait_initiate() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & DUO_CLIENT_FLAG_CONNECTED))
	{
		// state jump position
		_set_state_client(env, Iso14827TestDuoSessionClientState_wait_heartbeat);
	}

	return ERR_IS_SUCCESS(errp);
}
// wait INITIATE : Duo Client
///////////////////////////////////////////////////////////////////////////////

static bool_t _duo_session_client_echo_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	if ((env->flags & DUO_SERVER_FLAG_HEARTBEAD) == 0)
	{
		env->flags |= DUO_CLIENT_FLAG_HEARTBEAT;

		// notify to web
		// client session connect check!
	}
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : Heartbeat respond...\n");
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("CLIENT : 시험 대상으로부터 HeartBeat응답을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	// notify to web
	// client: hb respond!

	return ERR_IS_SUCCESS(errp);
}


///////////////////////////////////////////////////////////////////////////////
// wait HEARTBEAT : Duo Client
static bool_t _duo_session_client_wait_heartbeat(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_echo:
		if (_duo_session_client_echo_received(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_wait_heartbeat() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & DUO_CLIENT_FLAG_HEARTBEAT))
	{
		// state jump position
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else _set_state_client(env, Iso14827TestDuoSessionClientState_wait_pub_data);
	}
	return ERR_IS_SUCCESS(errp);
}
// wait HEARTBEAT : Duo Client
///////////////////////////////////////////////////////////////////////////////

static bool_t _duo_session_client_subscribe(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, u32_t* ret_sid, Dz1Error* errp)
{
	SubscribeSpecEntry* spec = s->c_sub;
	Dz1Binary* eam = Iso14827TestMsgSet_getNullData(env->selected_codec_duo, errp);
	if (eam == NULL) ERR_OUT(errp);
	else
	{
		Iso14827RejectSubscription result = Iso14827RejectSubscription_max;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);
		if (_client_util_subscribe(arg, env->selected_codec_duo, s->my_domain, s->peer_server_domain, s->c_account, spec, eam, ret_sid, &result, errp) == FALSE) ERR_OUT(errp);
		else if (result != Iso14827RejectSubscription_max) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Asn1UTF8Str* str_u8 = NULL;
			if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("SubscribeSpecEntry"), spec, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				Dz1Binary* data = NULL;
				if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("CLIENT : 시험 대상에게 서브스크립션을 전송하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
				}
				pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
			}
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&eam);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_session_client_pub_data_recv(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{
	Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("CLIENT : 퍼블리케이션을 수신하였습니다."), NULL, NULL, errp);
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : received publication...\n");
	// notify to web
	// client : receive publication

	env->flags |= DUO_CLIENT_FLAG_PUBLICATE;

	Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("퍼블리케이션 데이터 : ."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);

	_publication_log_dump_(arg->msg_api, msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, env->selected_codec);

	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// wait PUBLICATION : Duo Client
static bool_t _duo_session_client_wait_pub_data(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_echo:
		if (_duo_session_client_echo_received(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_trigger:
		if (_duo_session_client_subscribe(arg, env, timer, s, &env->test_subs_id, errp) == FALSE) ERR_OUT(errp);	// always single
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : sent subscribe...\n");
			env->flags |= DUO_CLIENT_FLAG_SUBSCRIBE;
			// notify to web
			// subscription sent!
			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestDuoSessionEvent_data:
		if (_duo_session_client_pub_data_recv(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_wait_pub_data() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & DUO_CLIENT_FLAG_SUBSCRIBE) && (env->flags & DUO_CLIENT_FLAG_PUBLICATE))
	{
		// state jump position
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : session test complete...\n");
		// notify to web
		// client test is complete

		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else _set_state_client(env, Iso14827TestDuoSessionClientState_idle);
	}
	return ERR_IS_SUCCESS(errp);
}
// wait PUBLICATION : Duo Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IDLE
static bool_t _duo_session_client_idle(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_echo:
		if (_duo_session_client_echo_received(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_trigger:
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_idle() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0)
	{
		if (_get_state_server(env) >= Iso14827TestDuoSessionServerState_idle)
		{
			Iso14827TestAccount* acc = s->c_account;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : session terminate : Server Session test complete\n");

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("CLIENT : 시험 대상에게 로그아웃을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if ((*errp = ItsIso14827_disconnectFromServer(arg->t14827, s->my_domain, s->peer_server_domain, acc->userid, Iso14827Logout_clientShutdown)).code) ERR_OUT(errp);
			else _set_state_client(env, Iso14827TestDuoSessionClientState_wait_disconnect);
			// notify to web
			// session terminate, server session test complete
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// IDLE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait DISCONNECT
static bool_t _duo_session_client_wait_disconnect(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoSessionRole* s = (Iso14827TestDuoSessionRole*)_scenario;
	Iso14827TestDuoSessionEvent ev = (Iso14827TestDuoSessionEvent)_ev;

	switch (ev)
	{
	case Iso14827TestDuoSessionEvent_echo:
		if (_duo_session_client_echo_received(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestDuoSessionEvent_disconnected:
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT : 시험 대상으로부터 로그아웃을 하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ CLIENT : session disconnected\n");
		env->flags &= ~DUO_CLIENT_FLAG_CONNECTED;

		// notify to web
		// client session disconnected!

		Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_session_client_wait_disconnect() : EVENT %s(%d) not permited\n", Iso14827TestDuoSessionEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & DUO_CLIENT_FLAG_CONNECTED) == 0)
		_set_state_client(env, Iso14827TestDuoSessionClientState_complete);
	return ERR_IS_SUCCESS(errp);
}
// wait DISCONNECT
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF duo_client_scenario[] =
{
	_duo_session_client_initial,
	_duo_session_client_wait_initiate,
	_duo_session_client_wait_heartbeat,
	_duo_session_client_wait_pub_data,
	_duo_session_client_idle,
	_duo_session_client_wait_disconnect,
	NULL
};


///////////////////////////////////////////////////////////////////////////////
// Chcek : Duo Session
bool_t Iso14827TestDuoSessionScenario_check(Iso14827TestDuoSessionRole* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestAccount* acc = NULL;
	Iso14827TestSubList* list = NULL;

	if (0) {}
	else if (s == NULL || msg_tbl == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Foundation data is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->my_domain == NULL || s->my_domain->data == NULL || s->my_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid my_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->peer_server_domain == NULL || s->peer_server_domain->data == NULL || s->peer_server_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid peer_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->peer_client_domain == NULL || s->peer_client_domain->data == NULL || s->peer_client_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid peer_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->c_peer_server == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ c_peer_server is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((acc = s->c_account) == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ c_account is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (acc->authinfo == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ c_account->authinfo is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (acc->userid == NULL || acc->userid->data == NULL || acc->userid->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ acc->userid is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (acc->passwd == NULL || acc->passwd->data == NULL || acc->passwd->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ ccc->passwd is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->c_sub == NULL || Iso14827TestMsgSet_findAPI(msg_tbl, s->c_sub->oid, NULL) == NULL || SubscribeSpecEntry_isSingle(s->c_sub) == FALSE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ c_sub is invalid\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Chcek : Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prepare : Duo Session
typedef struct ItsIso14827CreateServerCancelArg
{
	void* t14827;
	Dz1Asn1UTF8Str* domain;
} ItsIso14827CreateServerCancelArg;

static void ItsIso14827_createServerCancel(void* ptr)
{
	ItsIso14827CreateServerCancelArg* arg = (ItsIso14827CreateServerCancelArg*)ptr;
	ItsIso14827_deleteServer(arg->t14827, arg->domain);
}
bool_t Iso14827TestDuoSessionScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((env->subs_reg = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		env->flags = 0;
		if ((*errp = ItsIso14827_createServer4Task(my_queue_id, arg->t14827, s->my_domain, 1, NULL, 0)).code) ERR_OUT(errp);
		else
		{
			ItsIso14827CreateServerCancelArg cs_arg = { arg->t14827, s->my_domain };
			pthread_cleanup_push(ItsIso14827_createServerCancel, (void*)&cs_arg);
			env->flags |= DUO_SERVER_FLAG_CREATED;

			if ((*errp = ItsIso14827_createClient4Task(my_queue_id, arg->t14827, s->my_domain)).code) ERR_OUT(errp);
			else
			{
				env->flags |= DUO_CLIENT_FLAG_CREATED;
				_set_state_server(env, Iso14827TestDuoSessionServerState_initial);
				_set_state_client(env, Iso14827TestDuoSessionClientState_initial);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (ItsIso14827_createServerCancel, (void*)&cs_arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Prepare : Duo Session
///////////////////////////////////////////////////////////////////////////////

static void _duo_session_timer_cleanup(void* timer)
{
	Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_DUO_SERVER);
	Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_DUO_CLIENT);
}

static bool_t Iso14827TestDuoSessionServerScenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestDuoSessionEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestDuoSessionServerState state = _get_state_server(env);

	if (state < 0 || state >= Iso14827TestDuoSessionServerState_complete) ERR_SET_OUT(errp, EFAULT);
	else if (duo_server_scenario[state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (_get_state_server(env) == Iso14827TestDuoSessionServerState_complete && _get_state_client(env) == Iso14827TestDuoSessionClientState_complete)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Duo Session Test Complete...\n");
			// notify to web
			// duo session test complete!!

			_duo_session_timer_cleanup(timer);
			*ret_is_complete = TRUE;
			Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t Iso14827TestDuoSessionClientScenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestDuoSessionEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestDuoSessionClientState state = _get_state_client(env);

	if (state < 0 || state >= Iso14827TestDuoSessionClientState_complete) ERR_SET_OUT(errp, EFAULT);
	else if (duo_client_scenario[state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (_get_state_server(env) == Iso14827TestDuoSessionServerState_complete && _get_state_client(env) == Iso14827TestDuoSessionClientState_complete)
		{
			_duo_session_timer_cleanup(timer);
			*ret_is_complete = TRUE;

			Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Start : Duo Session
bool_t Iso14827TestDuoSessionScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	bool_t server_complete = FALSE, client_complete = FALSE;
	env->current_test = test_name_test_duo_session;
	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	ItsIso14827SocketHook_set(_14827_hook_func, env);
	if (0) {}
	else if (Iso14827TestDuoSessionServerScenario_event(arg, env, timer, s, Iso14827TestDuoSessionEvent_start, NULL, &server_complete, errp) == FALSE) ERR_OUT(errp);
	else if (Iso14827TestDuoSessionClientScenario_event(arg, env, timer, s, Iso14827TestDuoSessionEvent_start, NULL, &client_complete, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if (server_complete && client_complete) *ret_is_complete = TRUE;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Start : Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Trigger : Duo Session
bool_t Iso14827TestDuoSessionScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestDuoSessionClientScenario_event(arg, env, timer, s, Iso14827TestDuoSessionEvent_trigger, NULL, ret_is_complete, err);
}
// Trigger : Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message: Duo Session
bool_t Iso14827TestDuoSessionScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestDuoSessionEvent ev, void* t147827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (ev >= Iso14827TestDuoSessionEvent_auth && ev <= Iso14827TestDuoSessionEvent_logout)
	{
		if (Iso14827TestDuoSessionServerScenario_event(arg, env, timer, s, (Iso14827TestDuoSessionEvent)ev, t147827msg, ret_is_complete, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (ev >= Iso14827TestDuoSessionEvent_initiated && ev <= Iso14827TestDuoSessionEvent_disconnected)
	{
		if (Iso14827TestDuoSessionClientScenario_event(arg, env, timer, s, (Iso14827TestDuoSessionEvent)ev, t147827msg, ret_is_complete, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ERR_SET_OUT(errp, EFAULT);
	}
	return ERR_IS_SUCCESS(errp);
}
// ISO-14827 Message: Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout: Duo Session
bool_t Iso14827TestDuoSessionScenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Iso14827TestHelperTimer* tmr, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (tmr->present == Iso14827TestHelperTimerPresent_general)
	{
		u32_t timer_id = tmr->x.general;
		switch (timer_id)
		{
		case ISO14827_TEST_HELPER_TIMER_DUO_SERVER:
			Iso14827TestDuoSessionServerScenario_event(arg, env, timer, s, Iso14827TestDuoSessionEvent_timeout, (void*)&timer_id, ret_is_complete, err);
			break;
		case ISO14827_TEST_HELPER_TIMER_DUO_CLIENT:
			Iso14827TestDuoSessionClientScenario_event(arg, env, timer, s, Iso14827TestDuoSessionEvent_timeout, (void*)&timer_id, ret_is_complete, err);
			break;
		default:
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Timeout: Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Duo Session
bool_t Iso14827TestDuoSessionScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoSessionRole* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_duo_session_timer_cleanup(timer);
	return ERR_IS_SUCCESS(errp);
}
// Stop : Duo Session
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Cleanup : Duo Session
void Iso14827TestDuoSessionScenario_reset(Iso14827TestDuoSessionRole* s, Iso14827TestHelperEnv* env)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Iso14827TestSubList_flush(env->subs_reg);
	if (env->flags & DUO_SERVER_FLAG_CONNECTED)
	{
		if (env->user != NULL)
		{
			if ((*errp = ItsIso14827_terminateClient(env->t14827, s->my_domain, s->peer_client_domain, env->user)).code) ERR_OUT(errp);
			else
			{
				env->flags &= ~DUO_SERVER_FLAG_CONNECTED;
				Dz1Error_set(errp, 0);
			}
		}
	}

	if (env->flags & DUO_CLIENT_FLAG_CONNECTED)
	{
		Iso14827TestAccount* acc = s->c_account;
		if ((*errp = ItsIso14827_disconnectFromServer(env->t14827, s->my_domain, s->peer_server_domain, acc->userid, Iso14827Logout_clientShutdown)).code) ERR_OUT(errp);
		else
		{
			env->flags &= ~DUO_CLIENT_FLAG_CONNECTED;
			Dz1Error_set(errp, 0);
		}
	}

	if (env->flags & DUO_SERVER_FLAG_PORT_OPENED)
	{
		Iso14827TestConnection* sc = s->s_peer_client;
		if (sc->present == Iso14827TestConnectionPresent_passive)
		{
			ItsIso14827_closePort(env->t14827, sc->x.passive);
			env->flags &= ~DUO_SERVER_FLAG_PORT_OPENED;
		}
	}

	if (env->flags & DUO_CLIENT_FLAG_PORT_OPENED)
	{
		Iso14827TestConnection* cc = s->c_peer_server;
		if (cc->present == Iso14827TestConnectionPresent_passive)
		{
			Iso14827TestConnection* sc = s->s_peer_client;
			if (sc->present != Iso14827TestConnectionPresent_passive || sc->x.passive != cc->x.passive) ItsIso14827_closePort(env->t14827, cc->x.passive);

			env->flags &= ~DUO_CLIENT_FLAG_PORT_OPENED;
		}
	}
}
void Iso14827TestDuoSessionScenario_release(Iso14827TestDuoSessionRole* s, Iso14827TestHelperEnv* env)
{
	if (env->flags & DUO_SERVER_FLAG_CREATED)
	{
		ItsIso14827_deleteServer(env->t14827, s->my_domain);
		env->flags &= ~DUO_SERVER_FLAG_CREATED;
	}

	if (env->flags & DUO_CLIENT_FLAG_CREATED)
	{
		ItsIso14827_deleteClient(env->t14827, s->my_domain);
		env->flags &= ~DUO_CLIENT_FLAG_CREATED;
	}
}
// Cleanup : Duo Session
///////////////////////////////////////////////////////////////////////////////

void Iso14827TestDuoSessionRole_status(Iso14827TestDuoSessionRole* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (p != NULL)
	{
		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & DUO_SERVER_FLAG_CREATED) { Dz1STRCPY(dp, Dz1T("svr ")); dp += 4; }
		if (env->flags & DUO_SERVER_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("s_port ")); dp += 7; }
		if (env->flags & DUO_SERVER_FLAG_CONNECTED) { Dz1STRCPY(dp, Dz1T("s_conn ")); dp += 7; }

		if (env->flags & DUO_CLIENT_FLAG_CREATED) { Dz1STRCPY(dp, Dz1T("cli ")); dp += 4; }
		if (env->flags & DUO_CLIENT_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("c_port ")); dp += 7; }
		if (env->flags & DUO_CLIENT_FLAG_CONNECTED) { Dz1STRCPY(dp, Dz1T("c_conn ")); dp += 7; }

		if (env->flags & DUO_SERVER_FLAG_HEARTBEAD) { Dz1STRCPY(dp, Dz1T("s_hb ")); dp += 5; }
		if (env->flags & DUO_SERVER_FLAG_SUBSCRIBE) { Dz1STRCPY(dp, Dz1T("s_sub ")); dp += 6; }
		if (env->flags & DUO_SERVER_FLAG_PUBLICATE) { Dz1STRCPY(dp, Dz1T("s_pub ")); dp += 6; }

		if (env->flags & DUO_CLIENT_FLAG_HEARTBEAT) { Dz1STRCPY(dp, Dz1T("c_hb ")); dp += 5; }
		if (env->flags & DUO_CLIENT_FLAG_SUBSCRIBE) { Dz1STRCPY(dp, Dz1T("c_sub ")); dp += 6; }
		if (env->flags & DUO_CLIENT_FLAG_PUBLICATE) { Dz1STRCPY(dp, Dz1T("c_pub ")); dp += 6; }
		if (env->flags & DUO_CLIENT_FLAG_TERMINATE) { Dz1STRCPY(dp, Dz1T("c_term ")); dp += 7; }

		*dp = 0;
		Dz1Thread_printf(Dz1T("TEST FLAG = [ %s]\n"), status);
	}
}