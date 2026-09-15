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


#define SERVER3_FLAG_CREATED				0x80000000
#define SERVER3_FLAG_PORT_OPENED			0x40000000
#define SERVER3_FLAG_CONNECTED				0x20000000

#define SERVER3_FLAG_TERMINATE_SENT			0x10000000
#define SERVER3_FLAG_HEARTBEAD_RECEIVED		0x08000000
#define SERVER3_FLAG_LOGIN_TRIED			0x04000000
#define SERVER3_FLAG_REQ_RETRIED			0x02000000
#define SERVER3_FLAG_REQ_RETRIED_COMPLETE	0x01000000

#define SERVER3_FLAG_SUBSCRIBE_DONE			0x00800000
#define SERVER3_FLAG_VALIDATE_DONE			0x00400000
#define SERVER3_FLAG_PUB_INVALID_SENT		0x00200000
#define SERVER3_FLAG_PUB_REJECT_RECEIVED	0x00100000



#define SERVER3_FLAG_SUBS_COMPLETE			0x00004000

#define SERVER3_FLAG_SUB_RECEIVED			0x00000020
#define SERVER3_FLAG_NORMAL_PUB_COMPLETE    0x00000010


static struct TestCheckList
{
	Dz1Str testName;
	u32_t psid;
	u32_t payloadType;
	bool_t isSent;
	bool_t isDone;
} TestCheckList;

static struct TestCheckList prj2_ldm_server_check_list[] = {
	{Dz1T("test_map"),82056, 18, FALSE, FALSE},
	{Dz1T("test_spat"), 82055, 19, FALSE, FALSE},
	{Dz1T("test_sdsm"),90000, 41, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList prj2_rsu_server_check_list[] = {
	{Dz1T("test_pvd"), 82051, 26, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList prj4_ldm_server_check_list[] = {
	{Dz1T("test_ig_cooperative_perception"), 90001, 302, FALSE, FALSE},
	{Dz1T("test_ig_response"), 90001, 304, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList prj4_ig_server_check_list[] = {
	{Dz1T("test_ig_join_request"), 90001, 301, FALSE, FALSE},
	{Dz1T("test_ig_assign_id"), 90001, 303, FALSE, FALSE},
	{Dz1T("test_ig_instruct"), 90001, 305, FALSE, FALSE},
	{Dz1T("test_ig_instruct_cancel"), 90001, 306, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList police_prj4_rse_server_check_list[] = {
	{Dz1T("test_bsm"), 82050, 20, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList police_prj4_center_server_check_list[] = {
	{Dz1T("test_rsa"), 82053, 27, FALSE, FALSE},
	{Dz1T("test_tim"), 82054, 31, FALSE, FALSE},
	{Dz1T("test_map"), 82055, 18, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
	{NULL}
};

static struct TestCheckList police_prj4_signal_server_server_check_list[] = {
	{Dz1T("test_spat"),82055, 19, FALSE, FALSE},
	{Dz1T("test_tls"), 1234, 50, FALSE, FALSE},
	{Dz1T("test_invalid"), 9999, 9999, FALSE, FALSE},		// invalid name 확인
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
				i->isSent = TRUE;
				i->isDone = TRUE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

static void _clear_check_list(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p != NULL)
	{
		for (i = p; i->testName != NULL; i++)
		{
			i->isDone = FALSE;
			i->isSent = FALSE;
		}
	}
}

static u32_t _get_psid_from_check_list(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p == NULL) return FALSE;
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (i->isSent == FALSE && i->isDone == FALSE)
			{
				i->isSent = TRUE;
				return i->psid;
			}
		}
	}
	return 0;
}

static u32_t _get_payloadType_from_check_list(struct TestCheckList* p, u32_t psid)
{
	struct TestCheckList* i;
	if (p == NULL) return FALSE;
	{
		for (i = p; i->testName != NULL; i++)
		{
			/*if (i->psid == psid && i->isSent == FALSE)
			{
				return i->payloadType;
			}*/
			if (i->psid == psid && i->isDone == FALSE)
			{
				i->isDone = TRUE;
				return i->payloadType;
			}
		}
	}
	return 0;
}

static struct TestCheckList* _get_check_list_by_test_scenario(Dz1Str testScenario)
{
	if (0) {}
	else if (Dz1STRCMP(testScenario, Dz1T("prj2_rsuServer2ldm")) == 0) return prj2_rsu_server_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("prj2_ldmServer2rsu")) == 0) return prj2_ldm_server_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("prj4_ldmServer2ig")) == 0) return prj4_ldm_server_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("prj4_igServer2ldm")) == 0) return prj4_ig_server_check_list;

	else if (Dz1STRCMP(testScenario, Dz1T("rseServer2center")) == 0) return police_prj4_rse_server_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("centerServer2rse")) == 0) return police_prj4_center_server_check_list;

	else if (Dz1STRCMP(testScenario, Dz1T("signalserverServer2center")) == 0) return police_prj4_signal_server_server_check_list;


	return NULL;
}

static Dz1Str test_name_test_session = Dz1T("test_session");
static Dz1Str test_name_test_login_retry = Dz1T("test_login_retry");
static Dz1Str test_name_test_normal_sub = Dz1T("test_normal_sub");
static Dz1Str test_name_test_map = Dz1T("test_map");
static Dz1Str test_name_test_spat = Dz1T("test_spat");
static Dz1Str test_name_test_bsm = Dz1T("test_bsm");
static Dz1Str test_name_test_pvd = Dz1T("test_pvd");
static Dz1Str test_name_test_sdsm = Dz1T("test_sdsm");

static Dz1Str test_name_test_rsa = Dz1T("test_rsa");
static Dz1Str test_name_test_tim = Dz1T("test_tim");
static Dz1Str test_name_test_tls = Dz1T("test_tls");


static Dz1Str test_name_test_ig_join_request = Dz1T("test_ig_join_request");
static Dz1Str test_name_test_ig_cooperative_perception = Dz1T("test_ig_cooperative_perception");
static Dz1Str test_name_test_ig_assign_id = Dz1T("test_ig_assign_id");
static Dz1Str test_name_test_ig_response = Dz1T("test_ig_response");
static Dz1Str test_name_test_ig_instruct = Dz1T("test_ig_instruct");
static Dz1Str test_name_test_ig_instruct_cancel = Dz1T("test_ig_instruct_cancel");


static Dz1Str test_name_test_sub_retry = Dz1T("test_sub_retry");
static Dz1Str test_name_test_invalid_pub = Dz1T("test_invalid_pub");




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

static bool_t _server3_initial_passive(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, u16_t port, Dz1Error* errp)
{
	if ((*errp = ItsIso14827_openPort(arg->t14827, port, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		char log[128];
		sprintf(log, Dz1T("Port (%d)를 오픈했습니다. 접속 수신을 대기합니다."), port);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Port(%d) opened...\n", port);
		env->flags |= SERVER3_FLAG_PORT_OPENED;

		// notify to web
		// port opened!!! ready to connect

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server3_initial_active(Iso14827TestHelperArg* Arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ConfTestSocketAddress* c, Dz1Error* errp)
{
	// TBD..
	// 현재 서버는 passive 만 고려
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server3_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Error* errp)
{
	Iso14827TestConnection* c = s->connection;
	ItsIso14827SocketHook_set(_14827_hook_func, env);
	switch (c->present)
	{
	case Iso14827TestConnectionPresent_passive:
		if (_server3_initial_passive(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestConnectionPresent_active:
		if (_server3_initial_active(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server3_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp)
{
	Iso14827TestServerRole3* s = (Iso14827TestServerRole3*)_scenario;
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
		
		if (_server3_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login test started...\n");
			env->state = Iso14827TestServer3State_wait_auth;
			// 로그인 대기 타이머 설정
			// Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER3, TIMER_sec_to_us(SERVER3_AUTH_WAIT_TIME_S), NULL);

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
static bool_t _server3_heartbeat_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventEcho* msg, Dz1Error* errp)
{
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("하트비트를 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_echoReply(arg->t14827, s->my_domain, s->peer_domain, msg->user, msg->echoID)).code) ERR_OUT(errp);
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("하트비트 응답을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		if ((env->flags & SERVER3_FLAG_HEARTBEAD_RECEIVED) == 0)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat received\n");
			env->flags |= SERVER3_FLAG_HEARTBEAD_RECEIVED;
		}
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}
// Heartbeat received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait AUTH

static bool_t _server3_authenticate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, ItsIso14827ServerEventAuth* msg, u8_t codec_bits, Dz1Error* errp)
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

static bool_t _server3_wait_auth_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventAuth* msg, bool_t* ret_state_complete, Dz1Error* errp)
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
	
		if (_server3_authenticate(arg, env, msg, arg->codec_bits, errp) == FALSE) ERR_OUT(errp);
		else
		{
			*ret_state_complete = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	else if (msg->is_retried == FALSE && (env->flags &SERVER3_FLAG_LOGIN_TRIED) ==0)
	{
		// 재전송 시험 시작 및 첫번째 요청 수신
		env->current_test = test_name_test_login_retry;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("첫 번째 로그인을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		// 첫 번째 요청
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ First Login received\n");
		env->flags |= SERVER3_FLAG_LOGIN_TRIED;
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
		if (_server3_authenticate(arg, env, msg, arg->codec_bits, errp) == FALSE) ERR_OUT(errp);
		else
		{
			*ret_state_complete = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server3_wait_auth(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole3* s = (Iso14827TestServerRole3*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t go_next_stage = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server3_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_auth:
		if (_server3_wait_auth_received(arg, env, timer, s, (ItsIso14827ServerEventAuth*)_msg, &go_next_stage, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (go_next_stage)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Wait Establish...\n");
				env->state = Iso14827TestServer3State_wait_connected;
				/*if (s->validate_set != NULL)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_normal_sub, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}*/
				env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션 수신 대기 상태로 전환합니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT); // Login 안함 -> 시험 종료
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server3_wait_auth() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait AUTH
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait CONNECTED
static _server3_wait_connected_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventConnected* msg, Dz1Error* errp)
{
	// 접속 성공
	Iso14827TestSubList* temp = NULL;

	// if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("클라이언트와의 세션 연결을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Established\n");
	// notify to web
	// established!!!

	if ((temp = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestSubList_delAndSetNull(&env->subs_reg);
		env->subs_reg = temp;
		temp = NULL;

		env->flags |= SERVER3_FLAG_CONNECTED;
		env->selected_codec = msg->selected;

		if ((env->user = Dz1Asn1OctetStr_clone(msg->user, errp)) == NULL) ERR_OUT(errp); // User 정보 보관
		else Dz1Error_set(errp, 0);
	}
}

static bool_t _server3_wait_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole3* s = (Iso14827TestServerRole3*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_connected:
		if (_server3_wait_connected_received(arg, env, timer, s, (ItsIso14827ServerEventConnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else
		{

			env->state = Iso14827TestServer3State_established;
			// notify to web
			// login success!!


			Dz1Error_set(errp, 0);
		}
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server3_wait_connected() : %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait CONNECTED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request received
static bool_t _server3_request_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, bool_t* ret_msg_accepted, Dz1Error* errp)
{
	int oid_idx = 0;
	Iso14827TestMsgStructAPI* api = NULL;
	Iso14827TestProcessStatusCode code;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription received %s\n", oidStr);

	char log[128];
	sprintf(log, Dz1T("서브스크립션을 수신하였습니다. 요청 OID : %s"), oidStr);
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

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
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		// 아는 OID
		
			// 요청 재전송 시험 안함
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("서브스크립션 수락 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID)).code) ERR_OUT(errp);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription accepted\n");
				*ret_msg_accepted = TRUE;
				Dz1Error_set(errp, 0);
			}
	}
	return ERR_IS_SUCCESS(errp);
}
// Request received
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Request Response
static bool_t _server3_request_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, bool_t * ret_msg_accepted, Dz1Error* errp)
{
	int oid_idx = 0;
	Iso14827TestMsgStructAPI* api = NULL;
	char log[128];
	sprintf(log, Dz1T("서브스크립션을 수신하였습니다. 요청 OID : %s"), oidStr);
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription received = %s\n", oidStr);
	//notify to web
	// subscription received(oid)

	if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, oidStr, &oid_idx)) == NULL)
	{
		// 모르는 OID 수신
		Iso14827TestProcessStatusCode code;
		code = Iso14827TestProcessStatusCode_INVALID_OID;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Unknown OID = %s\n", oidStr);
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("요청 OID가 유효하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("요청 OID가 유효하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, Iso14827RejectSubscription_unknownSubscriptionMsgId)).code) ERR_OUT(errp);
		else
		{
			// notify to web
			// subscription reject - unknown oid!
			char log[128];
			sprintf(log, Dz1T("서브스크립션 거절 패킷을 전송합니다. 거절 사유 : %s"), Iso14827TestProcessStatusCodeStrA(code));
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			ERR_SET_OUT(errp, EPERM);
		}
	}
	// 아는 OID
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("서브스크립션 수락 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription accepted\n");
			// notify to web
			// subscription accepted!!!
			*ret_msg_accepted = TRUE;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Request Response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Data provide

static bool_t __server3_data_provide_normal(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole3* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* err)
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

static Dz1Binary* _get_publication_validate_eam()
{

}

static bool_t __server3_data_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Iso14827TestSubType subs_type, Dz1Error* errp)
{
	Dz1Binary* eam = NULL;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);

	if (subs_type == Iso14827TestSubType_single)
	{
		// single이면 무조건 회신
		if ((eam = Iso14827TestMsgSet_getPublicationSampleData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if (s->validate_set == NULL)
		{
		
		}
		else
		{
			switch (s->validate_set->present)
			{
			case Iso14827TestValidateSetPresent_rseServer2center:
			{
				PolicePrj4ValidateSet_rseServer2center* vs = NULL;
				u32_t psid;
				if ((vs = s->validate_set->x.rseServer2center) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((psid = _get_psid_from_check_list(test_check_list)) == 0)
				{
					// 다보냄 모든 퍼블리케이션을 보냈으니, 퍼블리케이션 중단
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시나리오의 모든 퍼블리케이션을 완료하였습니다. 퍼블리케이션 전송을 종료합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					if ((eam = Iso14827TestMsgSet_getPublicationSampleDataByPsid(arg->msg_api, oidStr, psid, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
					else
					{
						if (psid == 9999) // invalid
						{
							if (s->test_invalid_pub && (env->flags & SERVER3_FLAG_PUB_INVALID_SENT) == 0)
							{

								env->current_test = test_name_test_invalid_pub;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_invalid_pub, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else
							{
								env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
							}
							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 퍼블리케이션 패킷을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("10초간 퍼블리케이션 거절 패킷을 기다립니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, NULL);
								Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1, TIMER_sec_to_us(10), NULL);

								env->flags |= SERVER3_FLAG_PUB_INVALID_SENT;
								Dz1Error_set(errp, 0);

							}
						}
						else
						{
							if (s->validate_set->x.rseServer2center->test_bsm && psid == 82050)
							{
								env->current_test = test_name_test_bsm;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_bsm, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}

							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Dz1Error_set(errp, 0);
							}
						}
					}
				}
			}
				break;
			case Iso14827TestValidateSetPresent_centerServer2rse:
			{
				PolicePrj4ValidateSet_centerServer2rse* vs = NULL;
				u32_t psid;
				if ((vs = s->validate_set->x.centerServer2rse) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((psid = _get_psid_from_check_list(test_check_list)) == 0)
				{
					// 다보냄 모든 퍼블리케이션을 보냈으니, 퍼블리케이션 중단
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시나리오의 모든 퍼블리케이션을 완료하였습니다. 퍼블리케이션 전송을 종료합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					if ((eam = Iso14827TestMsgSet_getPublicationSampleDataByPsid(arg->msg_api, oidStr, psid, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
					else
					{
						if (psid == 9999) // invalid
						{
							if (s->test_invalid_pub && (env->flags & SERVER3_FLAG_PUB_INVALID_SENT) == 0)
							{

								env->current_test = test_name_test_invalid_pub;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_invalid_pub, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else
							{
								env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
							}
							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 퍼블리케이션 패킷을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("10초간 퍼블리케이션 거절 패킷을 기다립니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, NULL);
								Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1, TIMER_sec_to_us(10), NULL);

								env->flags |= SERVER3_FLAG_PUB_INVALID_SENT;
								Dz1Error_set(errp, 0);

							}
						}
						else
						{
							if (s->validate_set->x.centerServer2rse->test_rsa && psid == 82053)
							{
								env->current_test = test_name_test_rsa;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_rsa, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else if (s->validate_set->x.centerServer2rse->test_tim && psid == 82054)
							{
								env->current_test = test_name_test_tim;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_tim, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else if (s->validate_set->x.centerServer2rse->test_map && psid == 82055)
							{
								env->current_test = test_name_test_map;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_map, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}

							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Dz1Error_set(errp, 0);
							}
						}
					}
				}
			}
			break;
			case Iso14827TestValidateSetPresent_signalserverServer2center:
			{
				PolicePrj4ValidateSet_signalserverServer2center* vs = NULL;
				u32_t psid;
				if ((vs = s->validate_set->x.signalserverServer2center) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if ((psid = _get_psid_from_check_list(test_check_list)) == 0)
				{
					// 다보냄 모든 퍼블리케이션을 보냈으니, 퍼블리케이션 중단
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시나리오의 모든 퍼블리케이션을 완료하였습니다. 퍼블리케이션 전송을 종료합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				else
				{
					if ((eam = Iso14827TestMsgSet_getPublicationSampleDataByPsid(arg->msg_api, oidStr, psid, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
					else
					{
						if (psid == 9999) // invalid
						{
							if (s->test_invalid_pub && (env->flags & SERVER3_FLAG_PUB_INVALID_SENT) == 0)
							{

								env->current_test = test_name_test_invalid_pub;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_invalid_pub, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else
							{
								env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
							}
							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 퍼블리케이션 패킷을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("10초간 퍼블리케이션 거절 패킷을 기다립니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, NULL);
								Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1, TIMER_sec_to_us(10), NULL);

								env->flags |= SERVER3_FLAG_PUB_INVALID_SENT;
								Dz1Error_set(errp, 0);

							}
						}
						else
						{
							if (s->validate_set->x.signalserverServer2center->test_spat && psid == 82055)
							{
								env->current_test = test_name_test_spat;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_spat, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							else if (s->validate_set->x.signalserverServer2center->test_tls && psid == 1234)
							{
								env->current_test = test_name_test_tls;
								if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_tls, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}

							if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
							else
							{
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								Dz1Error_set(errp, 0);
							}
						}
					}
				}
			}
				break;
			default:
				ERR_SET_OUT(errp, EPERM);
				break;
			}
		}
	}
	pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&eam);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server3_registered_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventPubStart* msg, Dz1Error* errp)
{

	Iso14827TestSubEntry* node = NULL;
	if ((node = Iso14827TestSubList_findByID(env->subs_reg, s->peer_domain, msg->subID)) == NULL)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
		
		// Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), )
		if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, msg->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		if (__server3_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_max, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
		return ERR_IS_SUCCESS(errp);
}
// Data provide
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single Request received
static bool_t _server3_single_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventSubSignle* msg, bool_t* ret_msg_accepted, Dz1Error* errp)
{

	// if (_server3_request_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
	if (_server3_request_response(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server3_provide_data_single(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	// 단일 요청에 대한 응답
	if (__server3_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_single, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

// Single Request received
///////////////////////////////////////////////////////////////////////////////


static bool_t _is_all_subscribed(Iso14827TestSubList* subs_reg, Iso14827TestMsgStructAPI* msg_api)
{
	u32_t idx = 0;
	Iso14827TestMsgStructAPI* api = 0;
	while ((api = Iso14827TestMsgSet_findByIDX(msg_api, idx)) != NULL)
	{
		if (Iso14827TestSubList_findByOID(subs_reg, api->oid) == NULL) return FALSE;
		idx++;
	}
	return TRUE;
}

static bool_t _server3_set_ed_timer(Iso14827TestHelperEnv* env, void* timer, Dz1Asn1OctetStr* user, Dz1Str oidStr, u32_t subID, Dz1Error* errp);

static Dz1TaskProcStatus _server3_pub_ed(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestHelperTimer *tmr = (Iso14827TestHelperTimer*)(*tData);
	Iso14827TestHelperTimerED* edTmr = tmr->x.ed;

	Iso14827TestServerRole3* s = env->scenario->x.server3;
	if (s == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestSubEntry* node = NULL;
		if ((node = Iso14827TestSubList_findByID(env->subs_reg, s->peer_domain, edTmr->subID)) == NULL)
		{
			Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;

			// Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), )
			if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, edTmr->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			if (__server3_data_provide(arg, env, timer, s, edTmr->user, edTmr->subID, edTmr->oidStr, Iso14827TestSubType_max, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}

	// 타이머를 다시 등록하여 주기적으로 호출되도록 함
	if (!(env->flags & SERVER3_FLAG_PUB_INVALID_SENT && errp->code == 0))
	{
		if (_server3_set_ed_timer(env, timer, edTmr->user, edTmr->oidStr, edTmr->subID, errp) == FALSE) {
			ERR_OUT(errp);
		}
	}
	else
	{
		//ed finish
	}
	return ret;
}

static bool_t _server3_set_ed_timer(Iso14827TestHelperEnv* env, void* timer, Dz1Asn1OctetStr *user, Dz1Str oidStr, u32_t subID, Dz1Error* errp)
{
	Iso14827TestHelperTimer* tmr = Iso14827TestHelperTimer_new(Iso14827TestHelperTimerPresent_ed, NULL, errp);
	if (tmr == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestHelperTimerED* edTmr = NULL;
		pthread_cleanup_push(Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
		if ((edTmr = tmr->x.ed = Iso14827TestHelperTimerED_new(NULL, NULL, subID, ISO14827_TEST_HELPER_TIMER_PUB_ED, errp)) == NULL) ERR_OUT(errp);
		else if ((edTmr->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((edTmr->oidStr = Dz1Str_clone(oidStr, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Iso14827TestHelperTimer_update(timer, &tmr, 10000000, _server3_pub_ed)).code) ERR_OUT(errp);
		else
		{
			tmr = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _server3_registered_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Iso14827TestSubType subs_type, bool_t *ret_msg_accepted, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;

	if ((node = Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg add_cancel_arg = { env->subs_reg, (void**)&node };
		pthread_cleanup_push(Iso14827TestSubList_addCancel, (void*)&add_cancel_arg);
		if (_server3_request_response(arg, env, timer, s, user, subID, oidStr, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else
		{

			if (subs_type == Iso14827TestSubType_event_driven)
			{
				if (_server3_set_ed_timer(env, timer, user, oidStr, subID, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

			}

			node = NULL;
			if (_is_all_subscribed(env->subs_reg, arg->msg_api))
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ All Subscriptions are received!\n");
				// notify to web
				// all subscriptions are received!
				env->flags |= SERVER3_FLAG_SUBSCRIBE_DONE;
				u64_t duration_us = (u64_t)s->subs_timeout_s * 1000000;
				if (Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER2, duration_us, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Timer Start!\n");
				}
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestSubList_addCancel, (void*)&add_cancel_adrg);
	}
	return ERR_IS_SUCCESS(errp);

}


///////////////////////////////////////////////////////////////////////////////
// Event-Driven Request


static bool_t _server3_ed_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventSubPrepareED* msg, bool_t* ret_msg_accepted, Dz1Error* errp)
{

		if (s->test_request_retry)
		{
			// 재전송 시험 선택 됨
			if ((env->flags & SERVER3_FLAG_REQ_RETRIED) == 0)
			{
				// 재전송 시험 수행 했음?
				env->current_test = test_name_test_sub_retry;
				if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("첫 번째 서브스크립션을 무시합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				// 첫번째 요청 무시
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Initial subscription ignored\n");
				env->flags |= SERVER3_FLAG_REQ_RETRIED;
			}
			else
			{
				if ((env->flags & SERVER3_FLAG_REQ_RETRIED_COMPLETE) == 0)
				{
					// 아직 재전송 시험을 끝내지 못했으면
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("두 번째 서브스크립션을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Second subscription received\n");
					env->flags |= SERVER3_FLAG_REQ_RETRIED_COMPLETE;
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
					if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_event_driven, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					// notify to web
					// second subscription received!!
				}
				else
				{
					// 이미 재전송 시험을 했을 경우?
					if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_event_driven, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
		}
		else
		{
			// 재전송 시험 안함
			if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_event_driven, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	return ERR_IS_SUCCESS(errp);
}

// Event-Driven Request
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Periodic Request received
static bool_t _server3_periodic_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventSubPrepareP* msg, bool_t* ret_msg_accepted, Dz1Error* errp)
{
		if (s->test_request_retry)
		{
			// 재전송 시험 선택 됨
			if ((env->flags & SERVER3_FLAG_REQ_RETRIED) == 0)
			{
				// 재전송 시험 수행 했음?
				env->current_test = test_name_test_sub_retry;
				if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("첫 번째 서브스크립션을 무시합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				// 첫번째 요청 무시
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Initial subscription ignored\n");
				env->flags |= SERVER3_FLAG_REQ_RETRIED;
			}
			else
			{
				if ((env->flags & SERVER3_FLAG_REQ_RETRIED_COMPLETE) == 0)
				{
					// 아직 재전송 시험을 끝내지 못했으면
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("두 번째 서브스크립션을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Second subscription received\n");
					env->flags |= SERVER3_FLAG_REQ_RETRIED_COMPLETE;
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
					if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_periodic, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					// notify to web
					// second subscription received!!
				}
				else
				{
					// 이미 재전송 시험을 했을 경우?
					if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_periodic, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
		}
		else
		{
			// 재전송 시험 안함
			if (_server3_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_periodic, ret_msg_accepted, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	return ERR_IS_SUCCESS(errp);
}
// Periodic Request received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PubData Reject received
static bool_t _server3_pubdata_reject_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventPubInform* msg, Dz1Error* errp)
{
	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
	Iso14827TestSubEntry* inv_pub = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);
	if (inv_pub != NULL && inv_pub->sid == msg->subID && (env->flags & SERVER3_FLAG_PUB_INVALID_SENT))
	{
		// 비정상 정보가 제공되고, Reject를 수신하지 않은 상태

		if (s->test_invalid_pub) env->current_test = test_name_test_invalid_pub;

		char log[128];
		sprintf(log, Dz1T("시험 대상으로부터 퍼블리케이션 거부 패킷을 수신하였습니다. 서브스크립션 id: %d"), msg->subID);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Publicatoin handling OK(%u)", msg->subID);
		env->flags |= SERVER3_FLAG_PUB_REJECT_RECEIVED;

		// notify to web
		// invalid publication handling OK!
		Dz1Error_set(errp, 0);
		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
		Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1);
		env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
	}
	
	// 비정상 정보를 제공한적이 없거나, 비정상 정보제공 시험을 완료한 상태
	else
	{
		char log[128];
		sprintf(log, Dz1T("시험 대상으로부터 퍼블리케이션 거부 패킷을 수신하였습니다. 서브스크립션 id: %d"), msg->subID);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		// else if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션이 거절되었습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyInfo(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, NULL, Dz1T("퍼블리케이션이 거절되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
	}
	return ERR_IS_SUCCESS(errp);
}
// PubData Reject received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request test checker
static bool_t _server3_check_requests(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s)
{
	// 로그인 재전송 시험 여부
	//if (s->test_login_retry && (env->flags & SERVER3_FLAG_LOGIN_TRIED) == 0) return FALSE;

	//// 정보요청 시험 여부
	//if (s->test_subs != NULL && (env->flags & SERVER3_FLAG_SUBS_COMPLETE) == 0)
	//{
	//	// 각 요청 확인
	//	DZ1_ERROR_SAFE_VAR(errp, err);

	//	u32_t cnt = 0;
	//	Iso14827TestServerRoleSubsList* list = s->test_subs;
	//	Iso14827TestServerRoleSubsEntry** arr = list->get_array(list, &cnt, NULL);

	//	if (arr != NULL)
	//	{
	//		u32_t i, idx;
	//		bool_t missing = FALSE;
	//		Iso14827TestMsgStructAPI* api = NULL;
	//		Iso14827TestServerRoleSubsEntry* node = NULL;
	//		pthread_cleanup_push(Dz1Memory_cancel, (void*)arr);
	//		for (i = 0; i < cnt; i++)
	//		{
	//			if ((node = arr[i]) == NULL) ERR_SET_OUT(errp, EFAULT);
	//			else if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, node->oid, &idx)) == NULL) {}
	//			else if ((env->flags & (0x01 << idx)) == 0)
	//			{
	//				missing = TRUE;
	//				break;
	//			}
	//		}
	//		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void*)arr);

	//		if (missing) return FALSE;
	//		else
	//		{
	//			// Normal Subscription test complete
	//			s->test_subs = NULL;
	//			if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_normal_sub, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
	//			else Dz1Error_set(errp, 0);
	//			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Normal subscription test complete...\n");
	//			env->flags |= SERVER3_FLAG_SUBS_COMPLETE;
	//		}
	//	}
	//}
	//// 요청 재전송 시험 여부
	//if (s->test_request_retry && (env->flags & SERVER3_FLAG_REQ_RETRIED) == 0) return FALSE;

	//// 비정상 정보제공 시험 여부
	//if (s->test_invalid_pub && ((env->flags & SERVER3_FLAG_PUB_INVALID_SENT) == 0 || (env->flags & SERVER3_FLAG_PUB_REJECT_RECEIVED) == 0)) return FALSE;

	//// HEARTBEAT 수신 여부
	//if ((env->flags & SERVER3_FLAG_HEARTBEAD_RECEIVED) == 0) return FALSE;

	return TRUE;
}
// Request test checker
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request expired
static bool_t _server3_pub_expire_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827ServerEventPubExpire* msg, Dz1Error* errp)
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
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication expired(%u = %s) = %s\n", msg->subID, reg_entry->oid, str_reason);
		Dz1Error_set(errp, 0);

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
	}
	return ERR_IS_SUCCESS(errp);
}
// Request expired
///////////////////////////////////////////////////////////////////////////////


static bool_t _terminate_test_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole3* s, Dz1Error* err);
///////////////////////////////////////////////////////////////////////////////
// wait REQUEST
static bool_t _server3_wait_established(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole3* s = (Iso14827TestServerRole3*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t msg_accepted = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server3_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_single:
		if (_server3_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, &msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else if (msg_accepted)
		{
			if (_server3_provide_data_single(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_req_event_driven:
		if (_server3_ed_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareED*)_msg, &msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_periodic:
		if (_server3_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, &msg_accepted, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_start:
	case Iso14827TestServerEvent_data_period:
		if (_server3_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_pubdata_rejected:
		if (_server3_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_stop:
		// nothing to do
		break;
	case Iso14827TestServerEvent_req_expired:
		if (_server3_pub_expire_received(arg, env, timer, s, (ItsIso14827ServerEventPubExpire*)_msg, errp) == FALSE) ERR_OUT(errp);
		break;
	case Iso14827TestServerEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server3_wait_establisehd() : %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & SERVER3_FLAG_PUB_REJECT_RECEIVED))
	{

		switch (s->validate_set->present)
		{
			case Iso14827TestValidateSetPresent_rseServer2center:
				if (s->validate_set->x.rseServer2center->test_bsm)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_bsm, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				break;
			case Iso14827TestValidateSetPresent_centerServer2rse:
				if (s->validate_set->x.centerServer2rse->test_map)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_map, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				if (s->validate_set->x.centerServer2rse->test_rsa)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_rsa, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				if (s->validate_set->x.centerServer2rse->test_tim)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_tim, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				break;
			case Iso14827TestValidateSetPresent_signalserverServer2center:
				if (s->validate_set->x.signalserverServer2center->test_spat)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_spat, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				if (s->validate_set->x.signalserverServer2center->test_tls)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_tls, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
				}
				break;
			default:ERR_SET_OUT(errp, EPERM); break;
		}
			

		if (s->test_session)	env->current_test = test_name_test_session;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Terminate test...\n");
		if (_terminate_test_start(arg, env, s, errp) == FALSE) ERR_OUT(errp);
		else {
			env->state = Iso14827TestServer3State_wait_disconnect;
			Dz1Error_set(errp, 0);
		}
	}

	return ERR_IS_SUCCESS(errp);
}
// wait REQUEST
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait DISCONNECT
static bool_t _terminate_test_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestServerRole3* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 종료 요청 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_terminateClient(arg->t14827, s->my_domain, s->peer_domain, env->user)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _server3_disconnect_receive(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{

	if (Dz1Asn1UTF8Str_cmp(s->my_domain, msg->myDomain) == 0 &&
		Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) == 0 &&
		env->user != NULL && Dz1Asn1OctetStr_cmp(env->user, msg->user) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 로그아웃을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (s->test_session) {
			if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_session, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, 0);

		Dz1Asn1OctetStr_delAndSetNull(&env->user);
		env->flags &= ~SERVER3_FLAG_CONNECTED;

		// notify to web
		// client terminated!

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client terminated...\n");
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server3_wait_disconnect(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole3* s = (Iso14827TestServerRole3*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server3_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_logout:
		if (_server3_disconnect_receive(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server3_wait_disconnect() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & SERVER3_FLAG_CONNECTED) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test complete...\n");
		env->state = Iso14827TestServer3State_complete;

		// notify to web
		// logout success
		// test complete!
	}
	return ERR_IS_SUCCESS(errp);
}
// wait DISCONNECT
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF server3scenario[] =
{
	_server3_initial,											// 포트 오픈
	_server3_wait_auth,											// 로그인 재전송, 세션설정 로그인
	_server3_wait_connected,									// 세션설정 로그인 성공
	_server3_wait_established,									//	
	NULL,														// 없음
	_server3_wait_disconnect,									// 세션설정테스트 - 터미네이트
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


bool_t Iso14827TestServer3Scenario_check(Iso14827TestServerRole3* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
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
	/*else if (s->test_subs != NULL && Conformance1ServerRole1SubsList_check(s->test_subs, msg_tbl, errp) == FALSE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid subscription test scenario\n");
		ERR_SET_OUT(errp, EINVAL);
	}*/
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Check Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prepare Scenario : Server 1
bool_t Iso14827TestServer3Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((env->subs_reg = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	if ((*errp = ItsIso14827_createServer4Task(my_queue_id, arg->t14827, s->my_domain, 1, NULL, 0)).code) ERR_OUT(errp);
	else
	{
		// env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
		env->state = Iso14827TestServer3State_initial;
		env->flags |= SERVER3_FLAG_CREATED;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Prepare Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

static void _server3_timer_cleanup(void* timer)
{
	Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER1);
}

static bool_t Iso14827TestServer3Scenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Iso14827TestServerEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= Iso14827TestServer3State_complete) ERR_SET_OUT(errp, EFAULT);
	else if (server3scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		_clear_check_list(test_check_list);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		ERR_OUT(errp);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestServer3State_complete)
		{
			_server3_timer_cleanup(timer);
			*ret_is_complete = TRUE;
			_clear_check_list(test_check_list);

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
bool_t Iso14827TestServer3Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((test_check_list = _get_check_list_by_test_scenario(arg->testScenario)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);


	if (s->validate_set != NULL)
	{

		switch (s->validate_set->present)
		{
		case Iso14827TestValidateSetPresent_rseServer2center:
			if (s->validate_set->x.rseServer2center->test_bsm == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_bsm);
			break;
	
		case Iso14827TestValidateSetPresent_centerServer2rse:
			if (s->validate_set->x.centerServer2rse->test_map == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_map);
			if (s->validate_set->x.centerServer2rse->test_rsa == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_rsa);
			if (s->validate_set->x.centerServer2rse->test_tim == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_tim);
			break;

		case Iso14827TestValidateSetPresent_signalserverServer2center:
			if (s->validate_set->x.signalserverServer2center->test_spat == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_spat);
			if (s->validate_set->x.signalserverServer2center->test_tls == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_tls);
		default:break;
		}
		/*switch (s->validate_set->present)
		{
		case Iso14827TestValidateSetPresent_ldmServer2rsu:
			if (s->validate_set->x.ldmServer2rsu->test_map == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_map);
			if (s->validate_set->x.ldmServer2rsu->test_spat == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_spat);
			if (s->validate_set->x.ldmServer2rsu->test_sdsm == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_sdsm);
			break;

		case Iso14827TestValidateSetPresent_rsuServer2ldm:
			if (s->validate_set->x.rsuServer2ldm->test_pvd == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pvd);
			break;
		case Iso14827TestValidateSetPresent_igServer2ldm:
			if (s->validate_set->x.igServer2ldm->test_ig_join_request == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_join_request);
			if (s->validate_set->x.igServer2ldm->test_ig_assign_id == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_assign_id);
			if (s->validate_set->x.igServer2ldm->test_ig_instruct == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_instruct);
			if (s->validate_set->x.igServer2ldm->test_ig_instruct_cancel == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_instruct_cancel);
			break;
		case Iso14827TestValidateSetPresent_ldmServer2ig:
			if (s->validate_set->x.ldmServer2ig->test_ig_cooperative_perception == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_cooperative_perception);
			if (s->validate_set->x.ldmServer2ig->test_ig_response == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_ig_response);
			break;
		default:
			break;
		}*/
	}

	return Iso14827TestServer3Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_start, NULL, ret_is_complete, err);
}
// Start Scenario : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message : Server 1
bool_t Iso14827TestServer3Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer3Scenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Message : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout : Server 1
bool_t Iso14827TestServer3Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer3Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_timeout, (void*)&timer_id, ret_is_complete, err);
}
// Timeout : Server 1
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Server 1
bool_t Iso14827TestServer3Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole3* s, Dz1Error* err)
{
	// stop testing progress
	DZ1_ERROR_SAFE_PTR(errp, err);
	_server3_timer_cleanup(timer);
	return ERR_IS_SUCCESS(errp);
}
// Stop : Server 1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Cleanup : Server 1
void Iso14827TestServer3Scenario_reset(Iso14827TestServerRole3* s, Iso14827TestHelperEnv* env)
{
	// back to prepared status
	if (env->flags & SERVER3_FLAG_PORT_OPENED)
	{
		Iso14827TestConnection* c = s->connection;
		if (c->present == Iso14827TestConnectionPresent_passive)
			ItsIso14827_closePort(env->t14827, c->x.passive);
	}

	if (env->flags & SERVER3_FLAG_CONNECTED)
	{
		ItsIso14827_terminateClient(env->t14827, s->my_domain, s->peer_domain, env->user);
	}

	env->selected_codec = Dz1Asn1Codec_max;
	Dz1Asn1OctetStr_delAndSetNull(&env->user);
	Iso14827TestSubList_delAndSetNull(&env->subs_reg);

	env->state = Iso14827TestServer3State_initial;
	env->flags = SERVER3_FLAG_CREATED;	// clear all flags expect CREATED
}

void Iso14827TestServer3Scenario_release(Iso14827TestServerRole3* s, Iso14827TestHelperEnv* env)
{
	// called when terminate state
	Iso14827TestServer3Scenario_reset(s, env);
	if (env->flags & SERVER3_FLAG_CREATED)
	{
		ItsIso14827_deleteServer(env->t14827, s->my_domain);
		env->flags &= ~SERVER3_FLAG_CREATED;
	}
}
// Cleanup : Server 1
///////////////////////////////////////////////////////////////////////////////

/*
#define SERVER3_FLAG_CREATED				0x80000000
#define SERVER3_FLAG_PORT_OPENED			0x40000000
#define SERVER3_FLAG_CONNECTED				0x20000000

#define SERVER3_FLAG_TERMINATE_SENT			0x00200000
#define SERVER3_FLAG_HEARTBEAD_RECEIVED		0x00100000
#define SERVER3_FLAG_LOGIN_TRIED			0x00080000
#define SERVER3_FLAG_REQ_RETRIED			0x00040000
#define SERVER3_FLAG_PUB_REJECT_RECEIVED	0x00020000
#define SERVER3_FLAG_PUB_INVALID_SENT		0x00010000
*/

void Iso14827TestServerRole3_status(Iso14827TestServerRole3* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (p != NULL)
	{
		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & SERVER3_FLAG_CREATED) { Dz1STRCPY(dp, Dz1T("cre ")); dp += 4; }
		if (env->flags & SERVER3_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("port ")); dp += 5; }
		if (env->flags & SERVER3_FLAG_CONNECTED) { Dz1STRCPY(dp, Dz1T("conn ")); dp += 5; }
		if (env->flags & SERVER3_FLAG_TERMINATE_SENT) { Dz1STRCPY(dp, Dz1T("term ")); dp += 5; }
		if (env->flags & SERVER3_FLAG_HEARTBEAD_RECEIVED) { Dz1STRCPY(dp, Dz1T("hb ")); dp += 3; }
		if (env->flags & SERVER3_FLAG_LOGIN_TRIED) { Dz1STRCPY(dp, Dz1T("retry_login ")); dp += 12; }
		if (env->flags & SERVER3_FLAG_REQ_RETRIED) { Dz1STRCPY(dp, Dz1T("retry_subs")); dp += 11; }
		if (env->flags & SERVER3_FLAG_PUB_REJECT_RECEIVED) { Dz1STRCPY(dp, Dz1T("rej_pub ")); dp += 8; }
		if (env->flags & SERVER3_FLAG_PUB_INVALID_SENT) { Dz1STRCPY(dp, Dz1T("pub_invlid ")); dp += 11; }
		*dp = 0;
		Dz1Thread_printf("TEST FLAG = [ %s]\n", status);
	}
}

/*
		-- 기본 기능 시험
		bool					 test_session;
		bool					 test_login_retry;				-- 기본 기능 시험 - 로그인패킷의 재전송

		-- 정보 요청 시험
		-- bool					 test_normal_sub;
		bool					 test_map;						-- map 검증
		bool					 test_spat;						-- spat 검증
		bool					 test_sdsm;						-- sdsm 검증

		-- 시나리오별 시험
		bool					 test_sub_retry;				-- 서브크스크립션의 재전송
		bool					 test_invalid_pub;				-- 유효하지 않은 퍼블리케이션 패킷
*/