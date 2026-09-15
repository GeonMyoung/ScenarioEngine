#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
// #include <ConformanceMsgUtil.h>

#include "Iso14827TestHelperEnv.h"
//#include "Iso14827TestMsg.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperMsgSet.h"
#include "Iso14827TestHelperMsg.h"


#define SERVER1_FLAG_CREATED				0x80000000
#define SERVER1_FLAG_PORT_OPENED			0x40000000
#define SERVER1_FLAG_CONNECTED				0x20000000

#define SERVER1_FLAG_TERMINATE_SENT			0x00200000
#define SERVER1_FLAG_HEARTBEAD_RECEIVED		0x00100000
#define SERVER1_FLAG_LOGIN_TRIED			0x00080000
#define SERVER1_FLAG_REQ_RETRIED			0x00040000
#define SERVER1_FLAG_PUB_REJECT_RECEIVED	0x00020000
#define SERVER1_FLAG_PUB_INVALID_SENT		0x00010000
#define SERVER1_FLAG_VIOLATED_PUB			0x00008000
#define SERVER1_FLAG_SUBS_COMPLETE			0x00004000
#define SERVER1_FLAG_REQ_RETRIED_COMPLETE	0x00000200
#define SERVER1_FLAG_NORMAL_PUB_COMPLETE    0x00000010

#define SERVER1_AUTH_WAIT_TIME_S			30


static struct TestCheckList
{
	Dz1Str testName;
	bool_t isDone;
} TestCheckList;

static struct TestCheckList prj2_rsu_client_check_list[] = {
	{Dz1T("test_normal_pub_map"), FALSE},
	{Dz1T("test_normal_pub_spat"), FALSE},
	{Dz1T("test_normal_pub_sdsm"), FALSE},
	{NULL}
};

static struct TestCheckList prj2_ldm_client_check_list[] = {
	{Dz1T("test_normal_pub_pvd"), FALSE},
	{NULL}
};


static struct TestCheckList* test_check_list;

static bool_t _check_prj_validate_test(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p == NULL) return FALSE;
	else
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (i->isDone == FALSE) return FALSE;
		}
	}
	return TRUE;
}

static bool_t _mark_done_validate_test(struct TestCheckList* p, Dz1Str testName)
{
	struct TestCheckList* i;
	if (p == NULL || testName == NULL) return FALSE;
	else
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (Dz1STRCMP(i->testName, testName) == 0)
			{
				i->isDone = TRUE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

static struct TestCheckList* _get_check_list_by_test_scenario(Dz1Str testScenario)
{
	if (Dz1STRCMP(testScenario, Dz1T("prj2_rsuClient2ldm")) == 0) return prj2_rsu_client_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("prj2_ldmClient2rsu")) == 0) return prj2_ldm_client_check_list;
	return NULL;
}

static Dz1Str test_name_test_session = Dz1T("test_session");
static Dz1Str test_name_test_login_retry = Dz1T("test_login_retry");
static Dz1Str test_name_test_sub_map = Dz1T("test_sub_map");
static Dz1Str test_name_test_sub_spat = Dz1T("test_sub_spat");
static Dz1Str test_name_test_sub_pvd = Dz1T("test_sub_pvd");
static Dz1Str test_name_test_sub_sdsm = Dz1T("test_sub_sdsm");
static Dz1Str test_name_test_sub_retry = Dz1T("test_sub_retry");
static Dz1Str test_name_test_invalid_pub = Dz1T("test_invalid_pub");

static Dz1Str test_name_test_normal_sub = Dz1T("test_normal_sub");

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
///////////////////////////////////////////////////////////////////////////////
// Initial State

static bool_t _server1_initial_passive(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, u16_t port, Dz1Error* errp)
{
	if ((*errp = ItsIso14827_openPort(arg->t14827, port, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		char log[128];
		sprintf(log, Dz1T("Port (%d)를 오픈했습니다. 접속 수신을 대기합니다."), port);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Port(%d) opened...\n", port);
		env->flags |= SERVER1_FLAG_PORT_OPENED;

		// notify to web
		// port opened!!! ready to connect

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_initial_active(Iso14827TestHelperArg* Arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ConfTestSocketAddress* c, Dz1Error* errp)
{
	// TBD..
	// 현재 서버는 passive 만 고려
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server1_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Error* errp)
{
	Iso14827TestConnection* c = s->connection;
	ItsIso14827SocketHook_set(_14827_hook_func, env);
	switch (c->present)
	{
	case Iso14827TestConnectionPresent_passive:
		if (_server1_initial_passive(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestConnectionPresent_active:
		if (_server1_initial_active(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server1_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp)
{
	Iso14827TestServerRole1* s = (Iso14827TestServerRole1*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_start:
		if (s->test_session)
		{
			env->current_test = test_name_test_session;
			if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		if (_server1_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login test started...\n");
			env->state = Iso14827TestServer1State_wait_auth;
			// 로그인 대기 타이머 설정
			// Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1, TIMER_sec_to_us(SERVER1_AUTH_WAIT_TIME_S), NULL);

			// notify to web
			// start login test
			Dz1Error_set(errp, 0);
		}
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// Initial State
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Heartbeat received
static bool_t _server1_heartbeat_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventEcho* msg, Dz1Error* errp)
{
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("하트비트를 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_echoReply(arg->t14827, s->my_domain, s->peer_domain, msg->user, msg->echoID)).code) ERR_OUT(errp);
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("하트비트를 응답을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		if ((env->flags & SERVER1_FLAG_HEARTBEAD_RECEIVED) == 0)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat received\n");
			env->flags |= SERVER1_FLAG_HEARTBEAD_RECEIVED;
		}
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}
// Heartbeat received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait AUTH

static bool_t _server1_authenticate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, ItsIso14827ServerEventAuth* msg, u8_t codec_bits, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1Asn1Codec selected_codec = Dz1Asn1Codec_max;
	// need user check routine 
	// success
	if ((*errp = _ItsIso14827_loginAccept(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Dz1Asn1Codec_ber, ItsIso14827CRCCheck_warning, NULL, NULL)).code) ERR_OUT(errp);
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("인증 정보를 확인하여 로그인을 수락합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Authenticate success\n");
		// notify to web
		// authenticate success
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_wait_auth_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventAuth* msg, bool_t* ret_state_complete, Dz1Error* errp)
{
	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0)
	{
		// 잘못된 상대 도메인 명 -> 오류 -> 시험종료
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("잘못된 상대 도메인 이름입니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("잘못된 상대 도메인 이름입니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Unknown Domain Name\n");
		if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827RejectLogin_unknownDomainName)).code) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
	}
	else if (env->user != NULL)
	{
		// 중복 연결시 시험 종료
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_SESSION_DUPLICATE;
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("중복 로그인 요청입니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("중복 로그인 요청입니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Session Duplicated\n");
		if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, Iso14827RejectLogin_sessionExist)).code) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
	}
	else if (s->test_login_retry == FALSE)
	{
		// 로그인 재전송 시험 안함
		if (s->test_session) env->current_test = test_name_test_session;

		if (_server1_authenticate(arg, env, msg, arg->codec_bits, errp) == FALSE) ERR_OUT(errp);
		else
		{
			*ret_state_complete = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else if (msg->is_retried == FALSE && (env->flags & SERVER1_FLAG_LOGIN_TRIED) == 0)
	{
		// 재전송 시험 시작 및 첫번째 요청 수신
		env->current_test = test_name_test_login_retry;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("첫 번째 로그인을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		// 첫 번째 요청
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ First Login received\n");
		env->flags |= SERVER1_FLAG_LOGIN_TRIED;
		Dz1Error_set(errp, 0);
	}
	else
	{
		// 두 번째 요청
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Second Login received\n");
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("두 번째 로그인을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (s->test_session) env->current_test = test_name_test_session;
		if (_server1_authenticate(arg, env, msg, arg->codec_bits, errp) == FALSE) ERR_OUT(errp);
		else
		{
			*ret_state_complete = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_wait_auth(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole1* s = (Iso14827TestServerRole1*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t go_next_stage = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server1_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_auth:
		if (_server1_wait_auth_received(arg, env, timer, s, (ItsIso14827ServerEventAuth*)_msg, &go_next_stage, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (go_next_stage)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Wait Establish...\n");
				env->state = Iso14827TestServer1State_wait_connected;

				env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
			}
			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT); // Login 안함 -> 시험 종료
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server1_wait_auth() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait AUTH
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait CONNECTED
static _server1_wait_connected_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventConnected* msg, Dz1Error* errp)
{
	// 접속 성공
	Iso14827TestSubList* temp = NULL;

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("클라이언트와의 세션 연결을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Established\n");
	// notify to web
	// established!!!

	if ((temp = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestSubList_delAndSetNull(&env->subs_reg);
		env->subs_reg = temp;
		temp = NULL;

		env->flags |= SERVER1_FLAG_CONNECTED;
		env->selected_codec = msg->selected;

		if ((env->user = Dz1Asn1OctetStr_clone(msg->user, errp)) == NULL) ERR_OUT(errp); // User 정보 보관
		else Dz1Error_set(errp, 0);
	}
}

static bool_t _server1_wait_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole1* s = (Iso14827TestServerRole1*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_connected:
		if (_server1_wait_connected_received(arg, env, timer, s, (ItsIso14827ServerEventConnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestServer1State_established;
			// notify to web
			// login success!!

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션 수신 대기 상태로 전환합니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

			if (s->validate_set != NULL)
			{
				Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_normal_sub, Dz1T("START"), errp);
			}

			Dz1Error_set(errp, 0);
		}
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server1_wait_connected() : %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait CONNECTED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request received
static bool_t _server1_request_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, bool_t* ret_msg_accepted, Dz1Error* errp)
{
	int oid_idx = 0;
	Iso14827TestMsgStructAPI* api = NULL;
	Iso14827TestProcessStatusCode code;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription received %s\n", oidStr);

	char log[128];
	sprintf(log, Dz1T("서브스크립션을 수신하였습니다. 요청 OID : %s"), oidStr);
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	//notify to web
	// Subscription received (oid)!

	if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, oidStr, &oid_idx)) == NULL)
	{
		// 모르는 OID 수신
		code = Iso14827TestProcessStatusCode_INVALID_OID;

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Unknown OID = %s\n", oidStr);
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("요청 OID가 유효하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("요청 OID가 유효하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, Iso14827RejectSubscription_unknownSubscriptionMsgId)).code) ERR_OUT(errp);
		else
		{
			char log[128];
			sprintf(log, Dz1T("서브스크립션 거절 패킷을 전송합니다. 거절 사유 : %s"), Iso14827TestProcessStatusCodeStrA(code));
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			//notify to web
			// unknonw oid received
			// reject subscription
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		// 아는 OID
		if (s->test_subs != NULL)
		{
			// 정보 요청 시험 사용
			Iso14827TestServerRoleSubsEntry key = { oidStr };
			if (s->test_subs->find(s->test_subs, &key) != NULL)
			{
				u32_t msg_flag = 0x1 << oid_idx;
				env->flags |= msg_flag;
			}
		}
		if (s->test_request_retry)
		{
			// 요청 재전송 시험
			if ((env->flags & SERVER1_FLAG_REQ_RETRIED) == 0)
			{
				env->current_test = test_name_test_sub_retry;
				if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("첫 번째 서브스크립션을 무시합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0 );
				// 첫번째 요청 무시
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Initial subscription ignored\n");
				env->flags |= SERVER1_FLAG_REQ_RETRIED;

				// notify to web
				// first subscription ignore!!!
			}
			else
			{
				// 이미 재전송 시험을 함
				// 두번째 정보제공 요청됨
				if ((env->flags & SERVER1_FLAG_REQ_RETRIED_COMPLETE) == 0)
				{
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("두 번째 서브스크립션을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Second subscription received\n");
					env->flags |= SERVER1_FLAG_REQ_RETRIED_COMPLETE;
					// notify to web
					// second subscription received!!
					if ((env->flags & SERVER1_FLAG_SUBS_COMPLETE) == 0 && s->validate_set != NULL)
					{
						env->current_test = test_name_test_normal_sub;
					}
				}

				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("서브스크립션 수락 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

				if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID)).code) ERR_OUT(errp);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription accepted\n");
					*ret_msg_accepted = TRUE;
					// notify to web
					// single subscription accept!
					Dz1Error_set(errp, 0);
				}
			}
		}
		else
		{
			// 요청 재전송 시험 안함
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("서브스크립션 수락 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID)).code) ERR_OUT(errp);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription accepted\n");
				*ret_msg_accepted = TRUE;
				// notify to web
				// single subscription accept!
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Request received
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Data provide

static bool_t __server1_data_provide_normal(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole1* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* eam = NULL;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);
	//if ((eam = Iso14827TestMsgSet_getPublicationData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	if ((eam = Iso14827TestMsgSet_getPublicationSampleData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
	else
	{
	
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);

		_publication_log_dump_(arg->msg_api, oidStr, eam->data, eam->size, env->selected_codec);

		Dz1Error_set(errp, 0);
	}

	pthread_cleanup_pop(1);// (Dz1Binary_delAndSetNull, (void*)&eam);

	return ERR_IS_SUCCESS(errp);
}
static bool_t __server1_data_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Iso14827TestSubType subs_type, Dz1Error* errp)
{
	Dz1Binary* eam = NULL;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);
	if (s->test_invalid_pub)
	{
		// 비정상 publication 시험
		if (subs_type != Iso14827TestSubType_single)
		{
			//registered subscription에 한하여
			if (env->flags & SERVER1_FLAG_PUB_INVALID_SENT)
			{
				// 이미 수행 함 -> 정상 Publication
				// publication event 생성
				// if ((eam = Iso14827TestMsgSet_getPublicationData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
				if ((eam = Iso14827TestMsgSet_getPublicationSampleData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			// 비정상 publication
			else
			{
				// notify to web
				// invalid publication test start!!

				if ((eam = Iso14827TestMsgSet_getNullData(env->selected_codec, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
				else
				{
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 퍼블리케이션 패킷을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("10초간 퍼블리케이션 거절 패킷을 기다립니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, NULL);
					Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1, TIMER_sec_to_us(10), NULL);
					// 10초 이내에 취소되지 않으면 오류

					//Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Publicatoin sent(%s)\n", oidStr);

					env->flags |= SERVER1_FLAG_PUB_INVALID_SENT;
					Dz1Error_set(errp, 0);

					// notify to web
					// invalid publication sent!!!
				}
			}
		}
		// single -> 무조건 정상
		else if (__server1_data_provide_normal(arg, env, s, user, subID, oidStr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	// 비정상 publication 시험 안함 -> 정상 publication
	else if (__server1_data_provide_normal(arg, env, s, user, subID, oidStr, errp) == FALSE) ERR_OUT(errp);
	else {
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1);// (Dz1Bianry_delAndSetNull, (void*)&eam);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_registered_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventPubStart* msg, Dz1Error* errp)
{
	if (s->test_invalid_pub)
	{
		env->current_test = test_name_test_invalid_pub;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	if (__server1_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_max, errp) == FALSE) ERR_OUT(errp);
	return ERR_IS_SUCCESS(errp);
}
// Data provide
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single Request received
static bool_t _server1_single_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventSubSignle* msg, bool_t* ret_msg_accepted, Dz1Error* errp)
{
	
	if (_server1_request_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_provide_data_single(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	// 단일 요청에 대한 응답
	if (__server1_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_single, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

// Single Request received
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Periodic Request received
static bool_t _server1_periodic_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventSubPrepareP* msg, bool_t* ret_msg_accepted, Dz1Error* errp)
{
	// msg->priod_sec
	if (_server1_request_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Periodic Request received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PubData Reject received
static bool_t _server1_pubdata_reject_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827ServerEventPubInform* msg, Dz1Error* errp)
{
	Dz1Str temp = env->current_test;
	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
	Iso14827TestSubEntry* inv_pub = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);



	if (inv_pub != NULL && inv_pub->sid == msg->subID)
	{
		// 비정상 정보가 제공되고, Reject를 수신하지 않은 상태

		env->current_test = test_name_test_invalid_pub;
	
		char log[128];
		sprintf(log, Dz1T("시험 대상으로부터 퍼블리케이션 거부 패킷을 수신하였습니다. 서브스크립션 id: %d"), msg->subID);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Publicatoin handling OK(%u)", msg->subID);
		env->flags |= SERVER1_FLAG_PUB_REJECT_RECEIVED;

		// notify to web
		// invalid publication handling OK!
		Dz1Error_set(errp, 0);

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
		Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1);

	}
	// 비정상 정보를 제공한적이 없거나, 비정상 정보제공 시험을 완료한 상태
	else
	{
		char log[128];
		sprintf(log, Dz1T("시험 대상으로부터 퍼블리케이션 거부 패킷을 수신하였습니다. 서브스크립션 id: %d"), msg->subID);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		///else if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션이 거절되었습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyInfo(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, NULL, Dz1T("퍼블리케이션이 거절되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
	}
	env->current_test = temp;
	return ERR_IS_SUCCESS(errp);
}
// PubData Reject received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request test checker
static bool_t _server1_check_requests(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s)
{
	// 로그인 재전송 시험 여부
	if (s->test_login_retry && (env->flags & SERVER1_FLAG_LOGIN_TRIED) == 0) return FALSE;

	// 정보요청 시험 여부
	if (s->test_subs != NULL && (env->flags & SERVER1_FLAG_SUBS_COMPLETE) == 0)
	{
		// 각 요청 확인
		DZ1_ERROR_SAFE_VAR(errp, err);

		u32_t cnt = 0;
		Iso14827TestServerRoleSubsList* list = s->test_subs;
		Iso14827TestServerRoleSubsEntry** arr = list->get_array(list, &cnt, NULL);

		if (arr != NULL)
		{
			u32_t i, idx;
			bool_t missing = FALSE;
			Iso14827TestMsgStructAPI* api = NULL;
			Iso14827TestServerRoleSubsEntry* node = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void*)arr);
			for (i = 0; i < cnt; i++)
			{
				if ((node = arr[i]) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, node->oid, &idx)) == NULL) {}
				else if ((env->flags & (0x01 << idx)) == 0)
				{
					missing = TRUE;
					break;
				}
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void*)arr);
			
			if (missing) return FALSE;
			else
			{
				// Normal Subscription test complete
				s->test_subs = NULL;
				if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_normal_sub, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Normal subscription test complete...\n");
				env->flags |= SERVER1_FLAG_SUBS_COMPLETE;
			}
		}
	}
	// 요청 재전송 시험 여부
	if (s->test_request_retry && (env->flags & SERVER1_FLAG_REQ_RETRIED) == 0) return FALSE;

	// 비정상 정보제공 시험 여부
	if (s->test_invalid_pub && ((env->flags & SERVER1_FLAG_PUB_INVALID_SENT) == 0 || (env->flags & SERVER1_FLAG_PUB_REJECT_RECEIVED) == 0)) return FALSE;

	// HEARTBEAT 수신 여부
	if ((env->flags & SERVER1_FLAG_HEARTBEAD_RECEIVED) == 0) return FALSE;

	return TRUE;
}
// Request test checker
///////////////////////////////////////////////////////////////////////////////

static bool_t _terminate_test_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole1* s, Dz1Error* err);
///////////////////////////////////////////////////////////////////////////////
// wait REQUEST
static bool_t _server1_wait_established(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole1* s = (Iso14827TestServerRole1*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t msg_accepted = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server1_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_single:
		if (_server1_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, &msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else if (msg_accepted)
		{
			if (_server1_provide_data_single(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_req_event_driven:
		break;
	case Iso14827TestServerEvent_req_periodic:
		if (_server1_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, &msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_start:
	case Iso14827TestServerEvent_data_period:
		if (_server1_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_pubdata_rejected:
		if (_server1_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_stop:
		// nothing to do
		break;
	case Iso14827TestServerEvent_req_expired:
		break;
	case Iso14827TestServerEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server1_wait_establisehd() : %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && _server1_check_requests(arg, env, timer, s))
	{
		// 세션 종료 시험
		env->current_test = test_name_test_session;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Terminate test...\n");
		// notify to web
		// terminate test start!
		if (_terminate_test_start(arg, env, s, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestServer1State_wait_disconnect;
			Dz1Error_set(errp, 0);

		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait REQUEST
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait DISCONNECT
static bool_t _terminate_test_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole1* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 종료 요청 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_terminateClient(arg->t14827, s->my_domain, s->peer_domain, env->user)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _server1_disconnect_receive(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{

	if (Dz1Asn1UTF8Str_cmp(s->my_domain, msg->myDomain) == 0 &&
		Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) == 0 &&
		env->user != NULL && Dz1Asn1OctetStr_cmp(env->user, msg->user) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 로그아웃을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		
		Dz1Asn1OctetStr_delAndSetNull(&env->user);
		env->flags &= ~SERVER1_FLAG_CONNECTED;

		// notify to web
		// client terminated!

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client terminated...\n");
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server1_wait_disconnect(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole1* s = (Iso14827TestServerRole1*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server1_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_logout:
		if (_server1_disconnect_receive(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server1_wait_disconnect() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & SERVER1_FLAG_CONNECTED) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test complete...\n");
		env->state = Iso14827TestServer1State_complete;

		// notify to web
		// logout success
		// test complete!
	}
	return ERR_IS_SUCCESS(errp);
}
// wait DISCONNECT
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF server1scenario[] =
{
	_server1_initial,
	_server1_wait_auth,
	_server1_wait_connected,
	_server1_wait_established,
	NULL,
	_server1_wait_disconnect,
	NULL
};


static bool_t Conformance1ServerRole1SubsList_check(Iso14827TestServerRoleSubsList* list, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Iso14827TestMsgStructAPI* api = NULL;
	if (list->count(list) == 0) ERR_SET_OUT(errp, ENOENT);			// 비어있으면 안됨
	else
	{	// check all OIDs are exist in msg_tbl
		u32_t cnt = 0;
		Iso14827TestServerRoleSubsEntry** arr = list->get_array(list, &cnt, errp);
		if (arr == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			Iso14827TestServerRoleSubsEntry* node = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void*)arr);
			for (i = 0; errp->code == 0 && i < cnt; i++)
			{
				if ((node = arr[i]) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((api = Iso14827TestMsgSet_findAPI(msg_tbl, node->oid, NULL)) == NULL) ERR_SET_OUT(errp, ENOENT);	// 모르는 OID 안됨
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}


bool_t Iso14827TestServer1Scenario_check(Iso14827TestServerRole1* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	//else if (s == NULL || msg_tbl == NULL)
	else if (s == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Foundation data is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->my_domain == NULL || s->my_domain->data == NULL || s->my_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid my_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->peer_domain == NULL || s->peer_domain->data == NULL || s->peer_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid peer_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->connection == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid connection info\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->test_subs != NULL && Conformance1ServerRole1SubsList_check(s->test_subs, msg_tbl, errp) == FALSE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid subscription test scenario\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Check Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prepare Scenario : Server 1
bool_t Iso14827TestServer1Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((*errp = ItsIso14827_createServer4Task(my_queue_id, arg->t14827, s->my_domain, 1, NULL, 0)).code) ERR_OUT(errp);
	else
	{
		env->state = Iso14827TestServer1State_initial;
		env->flags |= SERVER1_FLAG_CREATED;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Prepare Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

static void _server1_timer_cleanup(void* timer)
{
	Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1);
}

static bool_t Iso14827TestServer1Scenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Iso14827TestServerEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= Iso14827TestServer1State_complete) ERR_SET_OUT(errp, EFAULT);
	else if (server1scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		// 에러를 해야 할 지 말 지?
		ERR_OUT(errp);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestServer1State_complete)
		{
			_server1_timer_cleanup(timer);
			*ret_is_complete = TRUE;

			if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("@@@ Iso14827 Server Test is Done!\n"));
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Start Scenario : Server 1
bool_t Iso14827TestServer1Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return Iso14827TestServer1Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_start, NULL, ret_is_complete, err);
}
// Start Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message : Server 1
bool_t Iso14827TestServer1Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer1Scenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Message : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout : Server 1
bool_t Iso14827TestServer1Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer1Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_timeout, (void*)&timer_id, ret_is_complete, err);
}
// Timeout : Server 1
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Server 1
bool_t Iso14827TestServer1Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole1* s, Dz1Error* err)
{
	// stop testing progress
	DZ1_ERROR_SAFE_PTR(errp, err);
	_server1_timer_cleanup(timer);
	return ERR_IS_SUCCESS(errp);
}
// Stop : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Cleanup : Server 1
void Iso14827TestServer1Scenario_reset(Iso14827TestServerRole1* s, Iso14827TestHelperEnv* env)
{
	// back to prepared status
	if (env->flags & SERVER1_FLAG_PORT_OPENED)
	{
		Iso14827TestConnection* c = s->connection;
		if (c->present == Iso14827TestConnectionPresent_passive)
			ItsIso14827_closePort(env->t14827, c->x.passive);
	}

	if (env->flags & SERVER1_FLAG_CONNECTED)
	{
		ItsIso14827_terminateClient(env->t14827, s->my_domain, s->peer_domain, env->user);
	}

	env->selected_codec = Dz1Asn1Codec_max;
	Dz1Asn1OctetStr_delAndSetNull(&env->user);
	Iso14827TestSubList_delAndSetNull(&env->subs_reg);

	env->state = Iso14827TestServer1State_initial;
	env->flags = SERVER1_FLAG_CREATED;	// clear all flags expect CREATED
}

void Iso14827TestServer1Scenario_release(Iso14827TestServerRole1* s, Iso14827TestHelperEnv* env)
{
	// called when terminate state
	Iso14827TestServer1Scenario_reset(s, env);
	if (env->flags & SERVER1_FLAG_CREATED)
	{
		ItsIso14827_deleteServer(env->t14827, s->my_domain);
		env->flags &= ~SERVER1_FLAG_CREATED;
	}
}
// Cleanup : Server 1
///////////////////////////////////////////////////////////////////////////////

/*
#define SERVER1_FLAG_CREATED				0x80000000
#define SERVER1_FLAG_PORT_OPENED			0x40000000
#define SERVER1_FLAG_CONNECTED				0x20000000

#define SERVER1_FLAG_TERMINATE_SENT			0x00200000
#define SERVER1_FLAG_HEARTBEAD_RECEIVED		0x00100000
#define SERVER1_FLAG_LOGIN_TRIED			0x00080000
#define SERVER1_FLAG_REQ_RETRIED			0x00040000
#define SERVER1_FLAG_PUB_REJECT_RECEIVED	0x00020000
#define SERVER1_FLAG_PUB_INVALID_SENT		0x00010000
*/

void Iso14827TestServerRole1_status(Iso14827TestServerRole1* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (p != NULL)
	{
		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & SERVER1_FLAG_CREATED) { Dz1STRCPY(dp, Dz1T("cre ")); dp += 4; }
		if (env->flags & SERVER1_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("port ")); dp += 5; }
		if (env->flags & SERVER1_FLAG_CONNECTED) { Dz1STRCPY(dp, Dz1T("conn ")); dp += 5; }
		if (env->flags & SERVER1_FLAG_TERMINATE_SENT) { Dz1STRCPY(dp, Dz1T("term ")); dp += 5; }
		if (env->flags & SERVER1_FLAG_HEARTBEAD_RECEIVED) { Dz1STRCPY(dp, Dz1T("hb ")); dp += 3; }
		if (env->flags & SERVER1_FLAG_LOGIN_TRIED) { Dz1STRCPY(dp, Dz1T("retry_login ")); dp += 12; }
		if (env->flags & SERVER1_FLAG_REQ_RETRIED) { Dz1STRCPY(dp, Dz1T("retry_subs")); dp += 11; }
		if (env->flags & SERVER1_FLAG_PUB_REJECT_RECEIVED) { Dz1STRCPY(dp, Dz1T("rej_pub ")); dp += 8; }
		if (env->flags & SERVER1_FLAG_PUB_INVALID_SENT) { Dz1STRCPY(dp, Dz1T("pub_invlid ")); dp += 11; }
		*dp = 0;
		Dz1Thread_printf("TEST FLAG = [ %s]\n", status);
	}
}
