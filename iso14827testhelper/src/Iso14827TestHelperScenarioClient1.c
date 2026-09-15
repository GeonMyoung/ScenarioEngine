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

#include <TechnicalRegulation2MsgStructAPI.h>
#include <GitsnAsnUtil.h>

#define CLIENT_FLAG_CREATED1				0x80000000
#define CLIENT_FLAG_CREATED2				0x40000000
#define CLIENT_FLAG_PORT_OPENED				0x20000000
#define CLIENT_FLAG_CONNECTED1				0x10000000
#define CLIENT_FLAG_CONNECTED2				0x08000000

#define CLIENT_FLAG_INVALID_LOGIN			0x04000000
#define CLIENT_FLAG_DUPLICATE_LOGIN			0x02000000
#define CLIENT_FLAG_A_HEARTBEAT				0x01000000
#define CLIENT_FLAG_B_HEARTBEAT				0x00800000
#define CLIENT_FLAG_DISCONNECT_TEST			0x00400000
#define CLIENT_FLAG_DEFFERED_PUB_ACK		0x00200000
#define CLIENT_FLAG_PUB_CANCEL				0x00100000
#define CLIENT_FLAG_SUBSCRIPTION_RCVD		0x00080000
#define CLIENT_FLAG_SUBS_NORMAL_COMPLETE	0x00040000
#define CLIENT_FLAG_TOTAL_TEST				0x00020000


// TEST NAME LIST
//--기본 기능 시험
//bool					 test_session_test;				--기본 기능 시험 - 세션 설정
//bool					 test_login_invalid;			--기본 기능 시험 - 유효하지 않은 로그인정보에 대한 세션설정 거부
//bool					 test_session_maintain;			--기본 기능 시험 - 비정상적 세션 연결 감지
//
//-- 정보 제공 시험
//bool					 test_normal_pub_map;
//bool					 test_normal_pub_spat;
//bool					 test_normal_pub_sdsm;
//
//--시나리오별 시험
//bool					 test_login_duplicate;			--시나리오별 시험 - 중복로그인 정보 처리
//bool					 test_invalid_sub;				--시나리오별 시험 - 서브스크립션 분석
//bool					 test_subs_cancel;				--시나리오별 시험 - 서브스크립션에 의한 퍼블리케이션의 명시적 취소
//bool					 test_pub_retry;				--시나리오별 시험 - 재전송

static struct TestCheckList
{
	Dz1Str testName;
	bool_t isDone;
} TestCheckList;


// prj2
static struct TestCheckList prj2_rsu_client_check_list[] = {
	{Dz1T("test_map"), FALSE},
	{Dz1T("test_spat"), FALSE},
	{Dz1T("test_sdsm"), FALSE},
	{NULL}
};
static struct TestCheckList prj2_ldm_client_check_list[] = {
	{Dz1T("test_pvd"), FALSE},
	{NULL}
};

static struct TestCheckList police_prj4_center_client_check_list[] = {		// rx_pdu
	{Dz1T("test_bsm"), FALSE},
	{NULL}
};

static struct TestCheckList police_prj4_rse_client_check_list[] = {		// rx_pdu
	{Dz1T("test_map"), FALSE},
	{Dz1T("test_rsa"), FALSE},
	{Dz1T("test_tim"), FALSE},
	{NULL}
};

static struct TestCheckList itsk_00100_3_c2c_client_check_list[] = {		// rx_pdu
	{Dz1T("test_pub_incident_detection_info"), FALSE},
	{Dz1T("test_pub_incident_termination_info"), FALSE},
	{Dz1T("test_pub_incident_detection_video_file_info_provide"), FALSE},
	{Dz1T("test_pub_control_state_info"), FALSE},
	{Dz1T("test_pub_sensor_state_info"), FALSE},
	{Dz1T("test_pub_moving_object"), FALSE},
	{NULL}
};



static void _clear_check_list(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p != NULL)
	{
		for (i = p; i->testName != NULL; i++)
		{
			i->isDone = FALSE;
		}
	}
}


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
	if (0) {}
	else if (Dz1STRCMP(testScenario, Dz1T("centerClient2rse")) == 0) return police_prj4_center_client_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("rseClient2center")) == 0) return police_prj4_rse_client_check_list;
	else if (Dz1STRCMP(testScenario, Dz1T("itsk00100_3c2cClient")) == 0) return itsk_00100_3_c2c_client_check_list;

	return NULL;
}

// 
static Dz1Str test_name_test_session = Dz1T("test_session");
static Dz1Str test_name_test_login_invalid = Dz1T("test_login_invalid");
static Dz1Str test_name_test_session_maintain = Dz1T("test_session_maintain");
static Dz1Str test_name_test_normal_pub = Dz1T("test_normal_pub");

// prj2
static Dz1Str test_name_test_map = Dz1T("test_map");
static Dz1Str test_name_test_spat = Dz1T("test_spat");
static Dz1Str test_name_test_pvd = Dz1T("test_pvd");
static Dz1Str test_name_test_sdsm = Dz1T("test_sdsm");

//police_prj4
static Dz1Str test_name_test_bsm = Dz1T("test_bsm");
static Dz1Str test_name_test_rsa = Dz1T("test_rsa");
static Dz1Str test_name_test_tim = Dz1T("test_tim");

// itsk00100_3

static Dz1Str test_name_test_pub_incident_detection_info = Dz1T("test_pub_incident_detection_info");
static Dz1Str test_name_test_pub_incident_termination_info = Dz1T("test_pub_incident_termination_info");
static Dz1Str test_name_test_pub_incident_detection_video_file_info_provide = Dz1T("test_pub_incident_detection_video_file_info_provide");
static Dz1Str test_name_test_pub_control_state_info = Dz1T("test_pub_control_state_info");
static Dz1Str test_name_test_pub_sensor_state_info = Dz1T("test_pub_sensor_state_info");
static Dz1Str test_name_test_pub_moving_object = Dz1T("test_pub_moving_object");


static Dz1Str test_name_test_login_duplicate = Dz1T("test_login_duplicate");
static Dz1Str test_name_test_invalid_sub = Dz1T("test_invalid_sub");
static Dz1Str test_name_test_subs_cancel = Dz1T("test_subs_cancel");
static Dz1Str test_name_test_pub_retry = Dz1T("test_pub_retry");



///////////////////////////////////////////////////////////////////////////////
// 14827 hook 

// 전송 메시지
// 수신 메시지 구분하여 로그 표출 c2c message를 json으로 변경할 수 있는지 확인

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

///////////////////////////////////////////////////////////////////////////////
// connection helper
static bool_t _client_establish_session(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Dz1SockAddr* peer, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, Dz1Error* errp)
{
	Iso14827RejectLogin result = Iso14827RejectLogin_max;
	Dz1Asn1Codec codec = arg->initial_codec;
	Iso14827TestClientRole1* s = env->scenario->x.client1;
	if (s->test_session)
	{
		env->current_test = test_name_test_session;
	}
	else
	{
		env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
	}
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	if ((*errp = _ItsIso14827_connectToServer(arg->t14827, peer, acc->my_domain, peer_domain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code) ERR_OUT(errp); // hb, codec, rsp_time 지정할수있도록 설정 또는 선언
	else
	{
		
		env->selected_codec = codec;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _client1_bind_session(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, ItsIso14827ClientEventInitiate* msg, Iso14827TestClientAccount* acc, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	Iso14827RejectLogin result = Iso14827RejectLogin_max;
	Dz1Asn1Codec codec = msg->initial_codec;
	if ((*errp = _ItsIso14827_bindWithServer(arg->t14827, msg->key, msg->myDomain, msg->peerDomain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, NULL, NULL, &result)).code) ERR_OUT(errp);
	else
	{
		env->selected_codec = codec;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// connection helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// subscribe helper
static Dz1Binary* _prepare_subscribe_eam(Dz1Str oid, Dz1Asn1Codec codec, Dz1Error* errp)
{
	Dz1Binary* eam = NULL;
	// if ((eam = Iso14827TestMsgSet_getNullData(codec, errp)) == NULL) ERR_OUT(errp);
	 if ((eam = Iso14827TestMsgSet_getEmptyList(codec, errp)) == NULL) ERR_OUT(errp); // 빈 리스트 eam
	else Dz1Error_set(errp, 0);
	return eam;
}

static bool_t _client_subscribe(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, SubscribeSpecEntry* entry, bool_t is_invalid_entry, u32_t* ret_sid, Iso14827RejectSubscription* ret_result, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* eam = NULL;
	SubscribeSpecType* type = NULL;

	if ((type = entry->type) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((eam = _prepare_subscribe_eam(entry->oid, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827TestAccount _acc = { acc->authinfo, acc->userid, acc->passwd };
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);

		if (_client_util_subscribe(arg, env->selected_codec, acc->my_domain, peer_domain, &_acc, entry, eam, ret_sid, ret_result, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Asn1UTF8Str* str_u8 = NULL;
			if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("SubscribeSpecEntry"), entry, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				Dz1Binary* data = NULL;
				if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 서브스크립션을 전송하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
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

static bool_t _client_unsubscribe(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, SubscribeSpecEntry* entry, u32_t sid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecTypeReg* r_info = NULL;
	SubscribeSpecTypeRegistered* r = NULL;
	SubscribeSpecType* type = entry->type;

	switch (type->present)
	{
	case SubscribeSpecTypePresent_registered:

	{
		Dz1Asn1UTF8Str* str_u8 = NULL;
		if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("SubscribeSpecEntry"), entry, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
			Dz1Binary* data = NULL;
			if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 서브스크립션 취소를 전송합니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					data = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);

		}
		if (errp->code == 0)
		{
			if ((r = type->x.registered) == NULL || (r_info = r->reg_info) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((*errp = ItsIso14827_requestCancel(arg->t14827, ItsIso14827DomainType_client, acc->my_domain, peer_domain, acc->userid, sid, r->when_cancel)).code) ERR_OUT(errp);
			else
			{
				if ((env->flags & CLIENT_FLAG_PUB_CANCEL) == 0)
				{
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션이 취소됐습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Canceled Test Compelete...\n");
					env->flags |= CLIENT_FLAG_PUB_CANCEL;
				}
				else
				{
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션이 취소됐습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Canceled...\n");
				}
				Dz1Error_set(errp, 0);
				// notify to web : publicatoin cancel!!!!!!;
			}
		}
	}
	break;
	default: break;
	}
	return ERR_IS_SUCCESS(errp);
}
// subscribe helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// setup passive mode
static bool_t _client_passive_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestClientPassive* c, Dz1Error* errp)
{
	// initial_codec = Dz1Asn1Codec_ber 고정 
	if ((*errp = ItsIso14827_openPort(arg->t14827, c->local_port, Dz1Asn1Codec_ber, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		env->flags |= CLIENT_FLAG_PORT_OPENED;
		Dz1Error_set(errp, 0);

		// arg->tmain에 메시지 전송
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// setup passive mode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// setup active mode & login test
static u8_t invalid_pass[] = { 0x30, 0x30 };
static Dz1Asn1OctetStr invalid_passwd = { invalid_pass, sizeof(invalid_pass) };

static bool_t _client_connect_and_test_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestClientActive* c, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1SockAddr peer;
	ConfTestSocketAddress* dst = c->peer;
	if ((*errp = Dz1SockAddr_setAddrByName(&peer, dst->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, dst->port)).code) ERR_OUT(errp);
	else
	{
		Iso14827TestClientAccount* acc = c->account1;

		if (s->test_login_invalid && (env->flags & CLIENT_FLAG_INVALID_LOGIN) == 0)
		{
			// 유효하지 않은 Login 시험 : Active
			env->current_test = test_name_test_login_invalid;
			if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);


			Iso14827RejectLogin result = Iso14827RejectLogin_max;
			Dz1Asn1Codec codec = arg->initial_codec; // ber 고정
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Login Test...\n");

			// arg->tMain에 메시지 전송, invalid login 시험 시작


			// 시험 대상에게 유효하지 않은 로그인 정보로 로그인을 시도합니다.
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 로그인 정보로 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if ((*errp = _ItsIso14827_connectToServer(arg->t14827, &peer, acc->my_domain, s->peer_domain, acc->authinfo, acc->userid, &invalid_passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code)
			{
				env->flags |= CLIENT_FLAG_INVALID_LOGIN;
				Dz1Error_set(errp, 0);

				char log[128];
				sprintf(log, Dz1T("시험 대상이 로그인을 거절하였습니다. 거절 사유: %s"), Iso14827RejectLoginStrA(result));
				//if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상이 로그인을 거절하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Login Test complete...\n");
				
			}
			else
			{
				Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
				//if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("시험 대상이 유효하지 않은 로그인에 대해 로그인을 수락하였습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상이 유효하지 않은 로그인에 대해 로그인을 수락하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				env->flags |= CLIENT_FLAG_CONNECTED1;
				ERR_SET_OUT(errp, EPERM); // 유효하지 않은 로그인이 성공 -> 오류 -> 시험 종료
			}
		}
		// 정상 로그인
		if (errp->code == 0)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login...\n");
			if (_client_establish_session(arg, env, &peer, s->peer_domain, acc, errp) == FALSE) ERR_OUT(errp);
			else
			{
				env->flags |= CLIENT_FLAG_CONNECTED1;
				Dz1Error_set(errp, 0);
				// arg->tMain, 로그인 성공 MSG 전송

				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("로그인을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login Success...\n");
				if ((env->server_addr = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// setup active mode & login test
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// heartbeat response received
static bool_t _client1_echo_responsed(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	// arg->tMain HeartBeat Responsed 하트비트 응답 수신함.

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 HeartBeat응답을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((env->flags & CLIENT_FLAG_A_HEARTBEAT) == 0)
	{
		//Iso14827Test_ScenarioSendMessage* send_msg = NULL;
		////pthread_cleanup_push(Iso14827Test_ScenarioSendMessage_delAndSetNull, (void*)&send_msg);
		//if ((send_msg = Iso14827Test_ScenarioSendMessage_new(Iso14827Test_ScenarioSendMessagePresent_notify, NULL, errp)) == NULL) ERR_OUT(errp);
		//else if ((send_msg->x.notify = Iso14827Test_ScenarioNotifyMessage_new(Iso14827Test_ScenarioNotifyMessagePresent_notify, NULL, errp)) == NULL) ERR_OUT(errp);
		//else if ((send_msg->x.notify->x.notify = Dz1Str_clone(Dz1T("$$$ Heartbeat Respond...\n"), errp)) == NULL) ERR_OUT(errp);
		//else if ((Iso14827TestHelperEnv_sendMsgToMain(env, send_msg, errp)) == FALSE) ERR_OUT(errp);
		//else Dz1Error_set(errp, 0);
		//pthread_cleanup_pop(1);// (Iso14827Test_ScenarioSendMessage_delAndSetNull, (void*)&send_msg);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat Respond...\n");
		env->flags |= CLIENT_FLAG_A_HEARTBEAT;
	}

	if (errp->code == 0 && (env->test_subs == NULL || env->test_subs->count(env->test_subs) == 0) && (env->state == Iso14827TestClient1State_wait_subs_cancel))
	{
		if (env->flags & CLIENT_FLAG_PUB_CANCEL)
		{
			if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Start Publication Deferred ACK Test...\n");
				env->state = Iso14827TestClient1State_wait_deferred_ack;
				Dz1Error_set(errp, 0);
				// notify to web
				// publication deferred test is start!
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// heartbeat response received
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait INITIATE State
static bool_t _client1_wait_initiate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	return errp->code == 0 ? TRUE : FALSE;
}
// wait INITIATE State
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INITIAL State
static bool_t _client1_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	// start event handler
	Iso14827TestClientConnection* c = s->connection;
	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		if (_client_passive_prepare(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		break;
	case Iso14827TestClientConnectionPresent_active:
		if (_client_connect_and_test_login(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			/*if (s->test_session)
			{
				env->current_test = test_name_test_session;
			}
			else
			{
				env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
			}*/
			env->state = Iso14827TestClient1State_wait_login_dup;
			Dz1Error_set(errp, 0);
		}
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _client1_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_start:

		ItsIso14827SocketHook_set(_14827_hook_func, env);

		// 시작은 항상 세션 설정 시험
		if (s->test_session)
		{
			env->current_test = test_name_test_session;
			if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		}
		else Dz1Error_set(errp, 0);



		if (_client1_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: // 다른 메시지 허용 안함
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_initial() : EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, 0);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// INITIAL State
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// wait Duplicate LOGIN test command
static void _task_exception_dumb(void* ptr, Dz1Error* reason) { return; }

typedef struct ItsIso14827CancelArg
{
	void* t14827;
	Dz1Asn1UTF8Str* my_domain;
	Dz1Asn1UTF8Str* peer_domain;
	Dz1Asn1OctetStr* user;
} ItsIso14827CancelArg;

static void _create14827ClientCancel(void* ptr)
{
	ItsIso14827CancelArg* arg = (ItsIso14827CancelArg*)ptr;
	ItsIso14827_deleteClient(arg->t14827, arg->my_domain);
}

static void _connect14827ClientCancel(void* ptr)
{
	ItsIso14827CancelArg* arg = (ItsIso14827CancelArg*)ptr;
	ItsIso14827_disconnectFromServer(arg->t14827, arg->my_domain, arg->peer_domain, arg->user, Iso14827Logout_clientShutdown);
}

static bool_t _client1_login_duplicate_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	// trigger event handler
	env->current_test = test_name_test_login_duplicate;

	if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	void* t14827 = ItsIso14827_new(_task_exception_dumb, NULL, errp);
	if (t14827 == NULL) ERR_OUT(errp);
	else
	{
		u32_t log_lv = 0;
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void*)&t14827);

		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if ((*errp = Dz1Task_start(t14827, log_lv)).code) ERR_OUT(errp);
		else
		{
			Iso14827TestClientAccount* acc = env->primary_acc;
			Dz1Asn1Codec codec = arg->initial_codec;
			Iso14827RejectLogin result = Iso14827RejectLogin_max;

			pthread_cleanup_push(Dz1Task_startCancel, (void*)t14827);
			if ((*errp = ItsIso14827_createClient4Task(Dz1Task_getQueueID(env->tSelf), t14827, acc->my_domain)).code) ERR_OUT(errp);
			else
			{
				u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
				ItsIso14827CancelArg arg14827 = { t14827, acc->my_domain, s->peer_domain, acc->userid };
				pthread_cleanup_push(_create14827ClientCancel, (void*)&arg14827);
				// arg->tMain, 중복로그인 시험 시작 알림

				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 중복 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test Duplicated Login...\n");
				if ((*errp = _ItsIso14827_connectToServer(t14827, env->server_addr, acc->my_domain, s->peer_domain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL,
					&result)).code)
				{
					env->flags |= CLIENT_FLAG_DUPLICATE_LOGIN;
					Dz1Error_set(errp, 0);

					char log[128];
					sprintf(log, Dz1T("시험 대상이 중복 로그인을 거절하였습니다. 거절 사유 : %s"), Iso14827RejectLoginStrA(result));
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상이 중복 로그인을 거절하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					// arg->tMain, 중복로그인 시험 성공 완료 알림, 거절 사유 result,
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test Duplicated Login complete...\n");
				}
				else
				{
					pthread_cleanup_push(_connect14827ClientCancel, (void*)&arg14827);

					Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
					//if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("시험 대상이 중복 로그인을 수락하였습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
					if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상이 중복 로그인을 수락하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
					else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					ERR_SET_OUT(errp, EPERM); // 중복로그인을 했는데 성공 -> 오류 -> 시험종료

					pthread_cleanup_pop(1); // (_connect14827ClientCancel, (void*)&arg14827);
				}
				pthread_cleanup_pop(1); //  (_create14827ClientCancel, (void*)&arg14827);
			}
			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void*)t14827);
		}
		pthread_cleanup_pop(1); //  (Dz1Task_delAndSetNull(void*) & t14827);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static bool_t _client1_wait_login_dup(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->test_login_duplicate == FALSE)
		{
			env->flags |= CLIENT_FLAG_DUPLICATE_LOGIN;
			Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Duplicate LOGIN test is suppressed...\n");
		}
		else if (_client1_login_duplicate_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_log_dup() : EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & CLIENT_FLAG_DUPLICATE_LOGIN))
	{
		// heartbeat 수신, 중복 로그인 시험 완료되면...
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestClient1State_wait_disconnect;
			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// wait Duplicate LOGIN test command
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait DISCONNECT state
static bool_t _client1_expected_disconnected_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상이 세션을 종료하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Session maintain check OK...\n");
	Dz1Thread_printf("$$$ Session maintain check OK...\n");
	Iso14827TestHelperTimer_clrClientTimer(timer, acc->my_domain, s->peer_domain, acc->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
	env->flags &= ~CLIENT_FLAG_CONNECTED1;
	env->flags |= CLIENT_FLAG_DISCONNECT_TEST;

	// arg->tMain, 세션 해제 시험 완료
	env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _client1_wait_disconnect(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_disconnected:
		if (_client1_expected_disconnected_received(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->test_session_maintain == FALSE)
		{
			env->flags |= CLIENT_FLAG_DISCONNECT_TEST;
			Dz1Error_set(errp, 0);
		}
		else
		{
			env->current_test = test_name_test_session_maintain;

			if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("하트비트 패킷을 전송하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Iso14827TestClientAccount* acc = env->primary_acc;

			// arg->tMain, 비정상적 세션연결 감지 시작
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Turn off Heartbeat...\n");

			if ((*errp = _ItsIso14827_controlClient(arg->t14827, acc->my_domain, s->peer_domain, acc->userid, ItsIso14827ClientCtrlFlag_HeartBeatOFF, TRUE)).code) ERR_OUT(errp);
			else if (Iso14827TestHelperTimer_setClientTimer(timer, acc->my_domain, s->peer_domain, acc->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT, TIMER_sec_to_us(arg->hb_dur_s * 2), NULL) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestClientEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_discoonect(): EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & CLIENT_FLAG_DISCONNECT_TEST))
	{
		Iso14827TestClientConnection* c = s->connection;

		Iso14827RejectLogin result = Iso14827RejectLogin_max;
		Dz1Asn1Codec codec = arg->initial_codec;
		Iso14827TestClientAccount* acc = env->primary_acc;

		if (s->test_session_maintain)
		{
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, NULL, Dz1T("다음 시험 진행을 위해 다시 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}

		switch (c->present)
		{
		case Iso14827TestClientConnectionPresent_active:
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Re-establishment(active)...\n");
			if ((env->flags & CLIENT_FLAG_CONNECTED1) == 0 &&
				_client_establish_session(arg, env, env->server_addr, s->peer_domain, env->primary_acc, errp) == FALSE) ERR_OUT(errp);
			else
			{
				env->flags |= CLIENT_FLAG_CONNECTED1;
				if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->state = Iso14827TestClient1State_wait_invalid_subs;
					Dz1Error_set(errp, 0);
				}
			}
			break;
		case Iso14827TestClientConnectionPresent_passive:
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Wait initiate(passive)...\n");
			if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
			else
			{
				env->state = Iso14827TestClient1State_wait_restart;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT);	break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// wait DISCONNECT state
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait RESTART state
static bool_t _client1_wait_restart(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_initiated:
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Re-established(passive)...\n");
		if (_client1_bind_session(arg, env, (ItsIso14827ClientEventInitiate*)_msg, env->primary_acc, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->flags |= CLIENT_FLAG_CONNECTED1;
			Dz1Error_set(errp, 0);
		}
		break;

	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_restart() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStr(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & CLIENT_FLAG_DISCONNECT_TEST) && (env->flags & CLIENT_FLAG_CONNECTED1))
	{
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state |= Iso14827TestClient1State_wait_invalid_subs;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait RESTART state
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// do invalid subscribe
static bool_t _client1_invalid_subc_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	env->current_test = test_name_test_invalid_sub;
	if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	SubscribeSpecList* list = NULL;
	if ((list = env->test_subs) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t done = FALSE;
		SubscribeSpecEntry* entry = NULL;
		Iso14827RejectSubscription result;
		Iso14827TestClientAccount* acc = env->primary_acc;
		while (done == FALSE && (entry = list->getHead(list)) != NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Subscribe...\n");
			result = Iso14827RejectSubscription_max;

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 유효하지 않은 정보 요청 전송합니다"), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			if (_client_subscribe(arg, env, s->peer_domain, acc, entry, TRUE, &env->test_subs_id, &result, errp) == FALSE || result != Iso14827RejectSubscription_max)
			{
				// 곧바로 거부되는 경우
				pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&entry);
				// notify web to invalid subs was rejected;
				// reject reason 
				// invalid subs test is success;
				// 20240504

				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상이 유효하지 않은 정보 요청을 거절하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Subscribe Test Complete...\n");
				Dz1Thread_printf("$$$ Invalid Subscribe Test Complete...\n");// debug log

				list->extract(list, entry); // 거부된 항목 제거
				pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&entry);
				Dz1Error_set(errp, 0);
			}
			else done = TRUE; // 서브스크립션이 수락되었음으므로 data_control을 기다려야 함
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// do invalid subscribe
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// do invalid subscribe response
static bool_t _client1_data_control_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827ClientEventPubControl* msg, Dz1Error* errp)
{
	SubscribeSpecEntry* entry = NULL;
	SubscribeSpecList* list = NULL;

	if (env->test_subs_id != msg->sid) ERR_SET_OUT(errp, EFAULT);
	else if ((list = env->test_subs) == NULL || (entry = list->getHead(list)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&entry);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Subscribe -> Publication Cancel...\n");
		// notify to web, Invalid SUbscribe (REgistered,) Publication Cancel.
		Dz1Thread_printf("$$$ Invalid Subscribe -> Publication Cancel...\n");

		list->extract(list, entry);

		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&entry);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// do invalid subscribe response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait INVALID SUBSCRIPT TEST state
static bool_t _client1_wait_invalid_subs(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->subs_invalid_list == NULL || s->subs_invalid_list->count(s->subs_invalid_list) == 0)
		{
			Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Invalid Subscribe test is suppressed...\n");
		}
		else if (_client_init_test_subs(env, s->subs_invalid_list, errp) == FALSE) ERR_OUT(errp);
		else if (_client1_invalid_subc_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827LoginInitiatorStrA(code), Dz1T("시험 대상이 유효하지 않은 정보 요청에 퍼블리케이션을 전송하였습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상이 유효하지 않은 정보 요청에 퍼블리케이션을 전송하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
		// 비정상 서브스크립션에 정상 퍼블리케이션 수신 -> 오류 -> 시험중단
	}
	break;
	case Iso14827TestClientEvent_data_ctrl:
		if (_client1_data_control_received(arg, env, timer, s, (ItsIso14827ClientEventPubControl*)_msg, errp) == FALSE) ERR_OUT(errp);
		else if (_client1_invalid_subc_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_invalid_subs(): EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->test_subs == NULL || env->test_subs->count(env->test_subs) == 0))
	{
		// 정보제공시험으로 넘어가기, (정상 정보 요청)

		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Start normal subscribe test...\n");
			env->state = Iso14827TestClient1State_wait_normal_subs;
			Dz1Error_set(errp, 0);
		}

	}
	return ERR_IS_SUCCESS(errp);
}

// wait INVALID SUBSCRIPT TEST state
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// do normal subscribe
static bool_t _client1_normal_subc_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	Iso14827RejectSubscription result;
	SubscribeSpecEntry* entry = NULL;
	SubscribeSpecList* list = NULL;

	Iso14827TestClientAccount* acc = env->primary_acc;
	if (env->state == Iso14827TestClient1State_wait_normal_subs && s->test_normal_pub)
	{
		env->current_test = test_name_test_normal_pub;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		// if(test)
	}

	if ((list = env->test_subs) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((entry = list->getHead(list)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (_client_subscribe(arg, env, s->peer_domain, acc, entry, FALSE, &env->test_subs_id, &result, errp) == FALSE) ERR_OUT(errp);
	else if (result != Iso14827RejectSubscription_max) ERR_SET_OUT(errp, EPERM);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// do normal subscribe
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// do normal response

static bool_t _check_psid2dsrcid(int psid, int dsrcid, Dz1Error* errp)
{
	if ((psid == 82050 && dsrcid == 20) ||		// bsm
		(psid == 82051 && dsrcid == 26) ||		// pvd
		(psid == 82053 && dsrcid == 27) ||		// rsa
		(psid == 82054 && dsrcid == 31) ||		// tim
		(psid == 82055 && dsrcid == 19) ||		// spat
		(psid == 82056 && dsrcid == 18) ||		// map



		(psid == 90000 && dsrcid == 41) ||		// sdsm
		(psid == 90001 && (dsrcid == 301 || dsrcid == 302 || dsrcid == 303 || dsrcid == 304 || dsrcid == 305 || dsrcid == 306)))
	{
		Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EFAULT);
	return ERR_IS_SUCCESS(errp);
}




static bool_t _validate_publication_commtxpdu_payload(Iso14827TestHelperEnv* env, Iso14827TestClientRole1* s, Dz1CommTxPDUResponse* p, Dz1Error* errp)
{
	Iso14827TestProcessStatusCode code;
	if (p == NULL || p->count(p) == 0) ERR_SET_OUT(errp, EFAULT); // notify to web empty publication
	else
	{
		int cnt;
		Dz1CommTxPDU** list = NULL;
		if ((list = p->get_array(p, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			for (int i = 0; i < cnt;i++)
			{

				Dz1CommTxPDU* e = list[i];
				if (e == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					Dz1Binary* payload = NULL;
					if ((payload = Dz1Binary_new(e->payload->data, e->payload->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Binary* value = NULL;
						int dsrc_id;
						int psid = e->psid;
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&payload);
						switch (psid)
						{






						case 82053:		// rsa
						case 82054:		// tim
						case 82055:		// spat
						case 82056:		// map
						case 90000:		// sdsm
							if ((value = GitsnAsnUtil_getValueFromMessageFrame(payload, &dsrc_id, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&value);

								if (_check_psid2dsrcid(psid, dsrc_id, errp) == FALSE) ERR_OUT(errp);
								else
								{
									Iso14827TestValidateSet* vs = NULL;
									Dz1Asn1UTF8Str* str_u8 = NULL;
									
									Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("@@@ Try dsrc_decode...\n"));

									switch (dsrc_id)
									{
									case 18:// map
									{
										ASN1WorkSpace ws;
										size_t consume_sz = 0;
										ASN1_INIT_WS_INFO(&ws);
										pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
										switch (s->validate_set->present)
										{
										case Iso14827TestValidateSetPresent_rseClient2center:
											if (s->validate_set->x.rseClient2center->test_map)
											{
												if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_map, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
												else Dz1Error_set(errp, 0);
												MapData map;
												memset(&map, 0, sizeof(MapData));
												if (MapData_uper_decode(&ws, value, &map, errp) == FALSE) Dz1Error_set(errp, EFAULT);
												else
												{
													Gitsn_MapData deser;
													memset(&deser, 0, sizeof(Gitsn_MapData));
													if (GitsnAsnUtil_Gitsn_MapDataFromASN(&map, &deser, errp) == FALSE) ERR_OUT(errp);
													else
													{
														if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_MapData"), &deser, errp)) == NULL) ERR_OUT(errp);
														else
														{
															pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
															Dz1Binary* data = NULL;
															if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
															else
															{
																pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
																code = Iso14827TestProcessStatusCode_OK;
																if (Iso14827TestHelperEnvUtil_validateRequest(env, test_name_test_map, value, data, code, errp) == FALSE) ERR_OUT(errp);
																else
																{
																	data = NULL;
																	Dz1Error_set(errp, 0);
																}
																pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
															}
															pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
														}
													}
												}
											}
											break;
										}
										pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
									}
									break;
									case 27:// rsa
									{
										ASN1WorkSpace ws;
										size_t consume_sz = 0;
										ASN1_INIT_WS_INFO(&ws);
										pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
										switch (s->validate_set->present)
										{
										case Iso14827TestValidateSetPresent_rseClient2center:
											if (s->validate_set->x.rseClient2center->test_rsa)
											{
												if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_rsa, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
												else Dz1Error_set(errp, 0);
												RoadSideAlert rsa;
												memset(&rsa, 0, sizeof(RoadSideAlert));
												if (RoadSideAlert_uper_decode(&ws, value, &rsa, errp) == FALSE) Dz1Error_set(errp, EFAULT);
												else
												{
													Gitsn_RoadSideAlert deser;
													memset(&deser, 0, sizeof(Gitsn_RoadSideAlert));
													if (GitsnAsnUtil_Gitsn_RoadSideAlertFromASN(&rsa, &deser, errp) == FALSE) ERR_OUT(errp);
													else
													{
														if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_RoadSideAlert"), &deser, errp)) == NULL) ERR_OUT(errp);
														else
														{
															pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
															Dz1Binary* data = NULL;
															if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
															else
															{
																pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
																code = Iso14827TestProcessStatusCode_OK;
																if (Iso14827TestHelperEnvUtil_validateRequest(env, test_name_test_rsa, value, data, code, errp) == FALSE) ERR_OUT(errp);
																else
																{
																	data = NULL;
																	Dz1Error_set(errp, 0);
																}
																pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
															}
															pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
														}
													}
												}
											}
											break;
										}
										pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
									}
									break;
									case 31:// tim
									{
										ASN1WorkSpace ws;
										size_t consume_sz = 0;
										ASN1_INIT_WS_INFO(&ws);
										pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
										switch (s->validate_set->present)
										{
										case Iso14827TestValidateSetPresent_rseClient2center:
											if (s->validate_set->x.rseClient2center->test_tim)
											{
												if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_tim, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
												else Dz1Error_set(errp, 0);
												TravelerInformation tim;
												memset(&tim, 0, sizeof(TravelerInformation));
												if (TravelerInformation_uper_decode(&ws, value, &tim, errp) == FALSE) Dz1Error_set(errp, EFAULT);
												else
												{
													ASN1_Print_TravelerInformation(&tim, 0);
													Gitsn_TravelerInformation deser;
													memset(&deser, 0, sizeof(Gitsn_TravelerInformation));
													if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(&tim, &deser, errp) == FALSE) ERR_OUT(errp);
													else
													{
														Gitsn_TravelerInformation_dump(&deser, 0);


														if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_TravelerInformation"), &deser, errp)) == NULL) ERR_OUT(errp);
														else
														{
															Dz1Asn1UTF8Str_dump(str_u8, 0);

															pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
															Dz1Binary* data = NULL;
															if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
															else
															{
																pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
																code = Iso14827TestProcessStatusCode_OK;
																if (Iso14827TestHelperEnvUtil_validateRequest(env, test_name_test_tim, value, data, code, errp) == FALSE) ERR_OUT(errp);
																else
																{
																	data = NULL;
																	Dz1Error_set(errp, 0);
																}
																pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
															}
															pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
														}
													}
												}
											}
											break;
										}
										pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
									}
									break;
										ERR_SET_OUT(errp, EPERM);
										break;
									}
								}
								pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&value);
							}
							break;
						default: ERR_SET_OUT(errp, EPERM); break;
						}
						pthread_cleanup_pop(1); //(Dz1Binary_delAndSetNull, (void*)&payload);
					}
				}
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_publication_commrxpdu_payload(Iso14827TestHelperEnv* env, Iso14827TestClientRole1 *s, Dz1CommRxPDUResponse* p, Dz1Error* errp)
{
	Iso14827TestProcessStatusCode code;
	if (p == NULL || p->count(p) == 0) ERR_SET_OUT(errp, EFAULT); // notify to web empty publication
	else
	{
		int cnt;
		Dz1CommRxPDU** list = NULL;
		if ((list = p->get_array(p, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			for (int i = 0; i < cnt;i++)
			{

				Dz1CommRxPDU* e = list[i];
				if (e == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					Dz1Binary* payload = NULL;
					if ((payload = Dz1Binary_new(e->payload->data, e->payload->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Binary* value = NULL;
						int dsrc_id;
						int psid = e->psid;
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&payload);
						switch (psid)
						{
						case 82050:		// bsm
							if ((value = GitsnAsnUtil_getValueFromMessageFrame(payload, &dsrc_id, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&value);

								if (_check_psid2dsrcid(psid, dsrc_id, errp) == FALSE) ERR_OUT(errp);
								else
								{
									Dz1Asn1UTF8Str* str_u8 = NULL;
									ASN1WorkSpace ws;
									size_t consume_sz = 0;
									ASN1_INIT_WS_INFO(&ws);
									pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);

									if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_bsm, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
									else Dz1Error_set(errp, 0);
									BasicSafetyMessage bsm;
									if (BasicSafetyMessage_uper_decode(&ws, value, &bsm, errp) == FALSE) Dz1Error_set(errp, EFAULT);
									else
									{
										Gitsn_BasicSafetyMessage deser;
										memset(&deser, 0, sizeof(Gitsn_BasicSafetyMessage));
										if (GitsnAsnUtil_Gitsn_BasicSafetyMessageFromASN(&bsm, &deser, errp) == FALSE) ERR_OUT(errp);
										else
										{
											if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_BasicSafetyMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
											else
											{
												pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
												Dz1Binary* data = NULL;
												if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
												else
												{
													pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
													code = Iso14827TestProcessStatusCode_OK;
													if (Iso14827TestHelperEnvUtil_validateRequest(env, test_name_test_bsm, value, data, code, errp) == FALSE) ERR_OUT(errp);
													else
													{
														data = NULL;
														Dz1Error_set(errp, 0);
													}
													pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
												}
												pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
											}
										}
									}
									pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
								}
								pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&value);
							}
						break;
						case 82051:		// pvd
							if ((value = GitsnAsnUtil_getValueFromMessageFrame(payload, &dsrc_id, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&value);

								if (_check_psid2dsrcid(psid, dsrc_id, errp) == FALSE) ERR_OUT(errp);
								else
								{
									Dz1Asn1UTF8Str* str_u8 = NULL;
									ASN1WorkSpace ws;
									size_t consume_sz = 0;
									ASN1_INIT_WS_INFO(&ws);
									pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
									if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_pvd, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
									else Dz1Error_set(errp, 0);
									ProbeVehicleData pvd;
									if (ProbeVehicleData_uper_decode(&ws, value, &pvd, errp) == FALSE) Dz1Error_set(errp, EFAULT);
									else
									{
										Gitsn_ProbeVehicleData deser;
										memset(&deser, 0, sizeof(Gitsn_ProbeVehicleData));
										if (GitsnAsnUtil_Gitsn_ProbeVehicleDataFromASN(&pvd, &deser, errp) == FALSE) ERR_OUT(errp);
										else
										{
											if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_ProbeVehicleData"), &deser, errp)) == NULL) ERR_OUT(errp);
											else
											{
												pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
												Dz1Binary* data = NULL;
												if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
												else
												{
													pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
													code = Iso14827TestProcessStatusCode_OK;
													if (Iso14827TestHelperEnvUtil_validateRequest(env, test_name_test_pvd, value, data, code, errp) == FALSE) ERR_OUT(errp);
													else
													{
														data = NULL;
														Dz1Error_set(errp, 0);
													}
													pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
												}
												pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
											}
										}
									}
									pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
								}
								pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&value);
							}
							break;
						default: ERR_SET_OUT(errp, EPERM); break;
					}
					pthread_cleanup_pop(1); //(Dz1Binary_delAndSetNull, (void*)&payload);
					}
				}
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _received_validate_rsp(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, void* _msg, Dz1Error* errp)
{
	Iso14827TestValidateContext* msg = (Iso14827TestValidateContext*)_msg;

	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch (msg->code)
		{
		case Iso14827TestProcessStatusCode_OK:
			if (Iso14827TestHelperEnvUtil_notifyState(env, msg->testName, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Success [ %s ]...\n$$$ raw data = %s\n$$$ result value = %s\n"), msg->testName, msg->raw, msg->data);
				Dz1Error_set(errp, 0);
			}
			break;
		case Iso14827TestProcessStatusCode_AGENT_SYSTEM_ERROR:
		case Iso14827TestProcessStatusCode_SERVER_DISCONNECTED:
		case Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR:
		case Iso14827TestProcessStatusCode_CONNECTION_FAIL:
		case Iso14827TestProcessStatusCode_DISCONNECTED:
		case Iso14827TestProcessStatusCode_TIMEOUT:
		case Iso14827TestProcessStatusCode_OUT_OF_RANGE:
		case Iso14827TestProcessStatusCode_DECODE_FAIL:
		case Iso14827TestProcessStatusCode_INVALID_ENCODING_RULE:
		case Iso14827TestProcessStatusCode_INVALID_OID:
		case Iso14827TestProcessStatusCode_INVALID_DSRC_MSG_ID:
		case Iso14827TestProcessStatusCode_JSON_PARSE_ERROR:
		case Iso14827TestProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR:
		case Iso14827TestProcessStatusCode_INVALID_TOPIC:
		case Iso14827TestProcessStatusCode_UNKNOWN:
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! FAIL [ %s ]\n!!! %s(%d)\n"), msg->testName, msg->desc, msg->code);
			if (Iso14827TestHelperEnvUtil_notifyState(env, msg->testName, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else
			{
				ERR_SET_OUT(errp, EFAULT);
			}
			break;
			// success
			// notify state test success
			// tbd
			break;
		default: break;
		}



		if (errp->code == 0)
		{
			if (_mark_done_validate_test(test_check_list, msg->testName) == FALSE) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _client1_normal_subs_data_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{

	Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 퍼블리케이션을 수신하였습니다."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Iso14827TestClientAccount* acc = env->primary_acc;

	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecEntry* entry = list->getHead(list);

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;

		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}
	else if (entry == NULL || Dz1STRCMP(entry->oid, msg->oidStr) != 0)
	{
		if (entry != NULL)
		{
			Dz1Thread_printf(Dz1T("Entry = "));
			SubscribeSpecEntry_dump(entry, 0);
		}
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_OID;
		char log[128];
		sprintf(log, Dz1T("퍼블리케이션 패킷의 식별자(OID)가 일치하지 않습니다. 수신 OID = %s"), msg->oidStr);
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료

	}
	else if (env->test_subs_id != msg->sid)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;
		//if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}
	else
	{

		list->extract(list, entry);
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&entry);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication received...\n");

		//_publication_log_dump_()

		u32_t idx;
		Iso14827TestMsgStructAPI* api = Iso14827TestMsgSet_findAPI(arg->msg_api, msg->oidStr, &idx);
		if (api != NULL)
		{
			// if (Dz1STRCMP(Dz1T("1.0.15784.2.0.1"), msg->oidStr) == 0)
			if (Dz1STRCMP(Dz1T("1.0.15784.1.0.1"), msg->oidStr) == 0)
			{
				Dz1CommTxPDUResponse* txpdu = NULL;
				if ((txpdu = (Dz1CommTxPDUResponse*)api->struct_decode(&bin, arg->initial_codec, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1CommTxPDUResponse_delAndSetNull, (void*)&txpdu);
					// Dz1CommTxPDUResponse_dump(txpdu, 0);

					// response를 하나씩 돌면서 검증
					if (_validate_publication_commtxpdu_payload(env, s, txpdu, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1); // (Dz1CommTxPDUResponse_delAndSetNull, (void*)&txpdu);
				}
			}
			//else if (Dz1STRCMP(Dz1T("1.0.15784.2.0.2"), msg->oidStr) == 0)
			else if (Dz1STRCMP(Dz1T("1.0.15784.1.0.2"), msg->oidStr) == 0)
			{
				Dz1CommRxPDUResponse* rxpdu = NULL;
				if ((rxpdu = (Dz1CommRxPDUResponse*)api->struct_decode(&bin, arg->initial_codec, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1CommRxPDUResponse_delAndSetNull, (void*)&rxpdu);
					// Dz1CommRxPDUResponse_dump(txpdu, 0);

					// response를 하나씩 돌면서 검증
					if (_validate_publication_commrxpdu_payload(env, s, rxpdu, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1); // (Dz1CommRxPDUResponse_delAndSetNull, (void*)&rxpdu);
				}
			}
			// 기본교통정보교환 
			else ERR_SET_OUT(errp, EPERM);
			// uper 체크
			if (errp->code == 0)
			{
				if (_client_unsubscribe(arg, env, s->peer_domain, acc, entry, env->test_subs_id, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&entry);
	}
	return ERR_IS_SUCCESS(errp);
}
// do normal response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait NORMAL SUBSCRIPT TEST state
static bool_t _client1_wait_normal_subs(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;


	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->subs_normal_list == NULL || s->subs_normal_list->count(s->subs_normal_list) == 0)
		{
			Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Normal Subscribe Test is suppressed...\n");
			Dz1Thread_printf("$$$ Normal Subscribe Test is suppressed...\n");
			if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
			else
			{
				// start publication cancel test
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Start Publication Cancel Test...\n");
				env->state = Iso14827TestClient1State_wait_subs_cancel;
				Dz1Error_set(errp, 0);
			}
		}
		else if (_client_init_test_subs(env, s->subs_normal_list, errp) == FALSE) ERR_OUT(errp);
		else if (_client1_normal_subc_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
		if (_client1_normal_subs_data_received(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else if (env->test_subs->count(env->test_subs) == 0) Dz1Error_set(errp, 0);
		else if (_client1_normal_subc_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data_ctrl:
		ERR_SET_OUT(errp, EPERM); // 정상 요청에 비정상 퍼블리케이션 수신 -> 오류 -> 시험 중단
		break;
	case Iso14827TestClientEvent_validate:
		if (_received_validate_rsp(arg, env, timer, s, _msg, errp) == FALSE)
		{
			if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			ERR_SET_OUT(errp, EFAULT);
		}
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_normal_subs(): EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev); // servereventstr??? - 20240508 gm
		break;
	}

	if (errp->code == 0 && (env->test_subs == NULL || env->test_subs->count(env->test_subs) == 0))
	{
		if (_check_prj_validate_test(test_check_list) == TRUE)
		{
			// PUB-ACK 지연 시험을 넘아가기 (재전송) + 퍼블리케이션 취소
			if ((env->flags & CLIENT_FLAG_SUBS_NORMAL_COMPLETE))
			{
				if (s->test_normal_pub)
				{
					if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
					env->current_test = NULL;
					env->flags |= CLIENT_FLAG_SUBS_NORMAL_COMPLETE;
					Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Normal Subscribe is comeplete...\n");
				}
			}
			if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
			else
			{
				// start publication cancel test
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Start Publication Cancel Test...\n");

				env->state = Iso14827TestClient1State_wait_subs_cancel;
				Dz1Error_set(errp, 0);
			}
		}
	}

	return ERR_IS_SUCCESS(errp);
}
// wait NORMAL SUBSCRIPT TEST state
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// do canceled subscription
static bool_t _client1_sub_cancel_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	SubscribeSpecEntry* entry = s->subs_cancel;
	SubscribeSpecType* type = entry->type;
	env->current_test = test_name_test_subs_cancel;
	if (type->present != SubscribeSpecTypePresent_registered) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else if (_client1_normal_subc_test(arg, env, timer, s, errp) == FALSE)ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// do canceled subscription
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// canceled pub-data response
static bool_t _client1_canceled_pub_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{


	Iso14827TestClientAccount* acc = env->primary_acc;

	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecEntry* entry = list->getHead(list);

	/*if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->userid, msg->user) != 0) ERR_SET_OUT(errp, EPERM);
	else if (entry == NULL || Dz1STRCMP(entry->oid, msg->oidStr) != 0) ERR_SET_OUT(errp, EPERM);
	else if (env->test_subs_id != msg->sid) ERR_SET_OUT(errp, EPERM);*/


	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;

		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}
	else if (entry == NULL || Dz1STRCMP(entry->oid, msg->oidStr) != 0)
	{
		if (entry != NULL)
		{
			Dz1Thread_printf(Dz1T("Entry = "));
			SubscribeSpecEntry_dump(entry, 0);
		}
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_OID;
		char log[128];
		sprintf(log, Dz1T("퍼블리케이션 패킷의 식별자(OID)가 일치하지 않습니다. 수신 OID = %s"), msg->oidStr);
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료

	}
	else if (env->test_subs_id != msg->sid)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}

	else if ((env->flags & CLIENT_FLAG_PUB_CANCEL) == 0)
	{
		Dz1Binary bin = { msg->encodedEAM ,msg->encodedEAMSize };

		list->extract(list, entry);
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&entry);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ To be canceled publication ...\n");
		//publication_log_dump

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 퍼블리케이션을 수신하였습니다."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		if (_client_unsubscribe(arg, env, s->peer_domain, acc, entry, env->test_subs_id, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&entry);
	}

	return ERR_IS_SUCCESS(errp);
}
// canceled pub-data response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait SUBSCRIPTION CANCEL TEST state			// gm 
static bool_t _client1_wait_subs_cancel(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;


	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->subs_cancel == NULL)
		{
			env->flags |= CLIENT_FLAG_PUB_CANCEL;
			if (_client_reset_test_sub(env, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Cancel Test is suppressed...\n");
		}
		else if (_client_init_test_sub(env, s->subs_cancel, errp) == FALSE) ERR_OUT(errp);
		else if (_client1_sub_cancel_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
		if (_client1_canceled_pub_response(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data_ctrl:
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
		//if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("정보 제공이 거절되었습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("정보 제공이 거절되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM);
		break;
	}
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client1_wait_subs_cancel() : Event %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	return ERR_IS_SUCCESS(errp);
}

// wait SUBSCRIPTION CANCEL TEST state			// gm 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// setup deferred pub-ack mode and do subscribe
static bool_t _client1_deferred_ack_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	SubscribeSpecEntry* entry = s->subs_pub_retry;
	SubscribeSpecType* type = entry->type;
	env->current_test = test_name_test_pub_retry;

	if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if (entry == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((type->present != SubscribeSpecTypePresent_registered) && (type->present != SubscribeSpecTypePresent_single)) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = _ItsIso14827_controlClient(arg->t14827, acc->my_domain, s->peer_domain, acc->userid, ItsIso14827ClientCtrlFlag_PubAckDeferred, TRUE)).code) ERR_OUT(errp);
	else if (_client1_normal_subc_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// setup deferred pub-ack mode and do subscribe
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// do deferred pub-data response
static bool_t _client1_deferred_pub_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{

	Iso14827TestClientAccount* acc = env->primary_acc;

	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecEntry* entry = list->getHead(list);

	//if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
	//	Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
	//	Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0)					ERR_SET_OUT(errp, EPERM);	// identifier 값이 다르면 오류 -> 시험 종료
	//else if (entry == NULL || Dz1STRCMP(entry->oid, msg->oidStr) != 0)		ERR_SET_OUT(errp, EPERM);	// identifier 값이 다르면 오류 -> 시험 종료
	//else if (env->test_subs_id != msg->sid)									ERR_SET_OUT(errp, EPERM);	// identifier 값이 다르면 오류 -> 사험 종료

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;

		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}
	else if (entry == NULL || Dz1STRCMP(entry->oid, msg->oidStr) != 0)
	{
		if (entry != NULL)
		{
			Dz1Thread_printf(Dz1T("Entry = "));
			SubscribeSpecEntry_dump(entry, 0);
		}
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_OID;
		char log[128];
		sprintf(log, Dz1T("퍼블리케이션 패킷의 식별자(OID)가 일치하지 않습니다. 수신 OID = %s"), msg->oidStr);
	//	if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료

	}
	else if (env->test_subs_id != msg->sid)
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_IDENTIFIER;
		// if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // identifier값이 다르면 오류 -> 시험 종료
	}
	else if ((env->flags & CLIENT_FLAG_DEFFERED_PUB_ACK) == 0)
	{
		Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("첫 번째 퍼블리케이션을 수신하였습니다."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("첫 번째 퍼블리케이션를 무시합니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Primary publication...\n");
		env->flags |= CLIENT_FLAG_DEFFERED_PUB_ACK;

		// publication log dump

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Primary publication ignore...\n");
		if ((*errp = _ItsIso14827_controlClient(arg->t14827, acc->my_domain, s->peer_domain, acc->userid, ItsIso14827ClientCtrlFlag_PubAckDeferred, FALSE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

		// 시험 완료 항목 제거
		list->extract(list, entry);

		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&entry);
		if (s->subs_pub_retry != NULL)
		{
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("두 번째 퍼블리케이션을 수신하였습니다."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Secondary publication...\n");
		}
		else Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication...\n");

		if (entry->type->present == SubscribeSpecTypePresent_registered)
		{
			if (_client_unsubscribe(arg, env, s->peer_domain, acc, entry, env->test_subs_id, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&entry);
	}
	return ERR_IS_SUCCESS(errp);
}
// do deferred pub-data response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait DEFERRED PUB-ACK TEST state
static bool_t _client1_wait_deferred_ack(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;


	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->subs_pub_retry == NULL)
		{
			env->flags |= CLIENT_FLAG_DEFFERED_PUB_ACK;
			if (_client_reset_test_sub(env, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Retry Test is suppressed...\n");
		}
		else if (_client_init_test_sub(env, s->subs_pub_retry, errp) == FALSE) ERR_OUT(errp);
		else if (_client1_deferred_ack_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
		if (_client1_deferred_pub_response(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data_ctrl:
	{
		Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
		//if (Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("정보 제공이 거절되었습니다."), NULL, errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("정보 제공이 거절되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		else ERR_SET_OUT(errp, EPERM); // 정상 요청에 비정상 퍼블리케이션 수신 -> 오류 -> 시험 중단
	}
	break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client1_wait_deferred_ack() : Event %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->test_subs == NULL || env->test_subs->count(env->test_subs) == 0))
	{
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestClient1State_wait_terminate;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait DEFERRED PUB-ACK TEST state
///////////////////////////////////////////////////////////////////////////////


static bool_t _client1_do_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	if (s->test_session) env->current_test = test_name_test_session;
	else env->current_test = ISO14827_TEST_HELPER_DEFAULT_SCENARIO;

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 로그아웃을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Send Logout...\n");
	if ((*errp = ItsIso14827_disconnectFromServer(arg->t14827, acc->my_domain, s->peer_domain, acc->userid, Iso14827Logout_clientRequested)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _client1_disconnected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상으로부터 로그아웃을 하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	if (s->test_session)
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, test_name_test_session, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Disconnected...\n");
	env->flags &= ~CLIENT_FLAG_CONNECTED1;
	Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// wait TERMINATE TEST state
static bool_t _client1_wait_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole1* s = (Iso14827TestClientRole1*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;


	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client1_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (_client1_do_terminate(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_disconnected:
		if (_client1_disconnected(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client1_wait_disconnected() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStr(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED1) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test Complete...\n");
		env->state = Iso14827TestClient1State_complete;
		Dz1Error_set(errp, 0);

		// notify to web
		// test complete! (client1)
	}
	return ERR_IS_SUCCESS(errp);
}
// wait TERMINATE TEST state
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Check Scenario : Client
static bool_t _check_sub_type(SubscribeSpecEntry* p, SubscribeSpecTypePresent present)
{
	bool_t ret = FALSE;
	SubscribeSpecType* type = NULL;
	if ((type = p->type) == NULL) Dz1Thread_printf(Dz1T("p->type == NULL\n"));
	else if (type->present != present) Dz1Thread_printf(Dz1T("type->presend(%s) != present(%s)\n"), SubscribeSpecTypePresentStr(type->present), SubscribeSpecTypePresentStr(present));
	else if (type->present == SubscribeSpecTypePresent_registered && type->x.registered == NULL)
		Dz1Thread_printf(Dz1T("type->x.registered == NULL\n"));
	else ret = TRUE;
	return ret;
}

static Dz1Error _check_subs_type(void* ptr, SubscribeSpecEntry* p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SubscribeSpecTypePresent present = (SubscribeSpecTypePresent)DZ1_PTR2VAL32(ptr);
	if (_check_sub_type(p, present) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else Dz1Error_set(errp, 0);
	return err;
}

//static Dz1Error _check_subs_invalid(void* ptr, SubscribeSpecEntry* p)
//{
//	DZ1_ERROR_SAFE_VAR(errp, err);
//	ConformanceMsgStructAPI* tbl = (ConformanceMsgStructAPI*)ptr;
//	if (Conformance1MsgUtil_findAPI(tbl, p->oid, NULL) != NULL) ERR_SET_OUT(errp, EEXIST);
//	else Dz1Error_set(errp, 0);
//
//	return err;
//}

/*
typedef struct Conformance1ClientRole
{
	Conformance1ClientConnection *connection;
	Dz1Asn1UTF8Str               *peer_domain;
	SubscribeSpecList            *subs_invalid_list;
	SubscribeSpecList            *subs_normal_list;
	SubscribeSpecEntry           *subs_retry;
	SubscribeSpecList            *subs_total_list;
	u32_t                         subs_total_collect;
	SubscribeSpecDuo             *subs_duo;
	Iso14827SubscriptionCancel    subs_cancel_reason;
} Conformance1ClientRole;
*/
bool_t Iso14827TestClient1Scenario_check(Iso14827TestClientRole1* s, Dz1Error* err)//ConformanceMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecList* list;
	if (0) {}
	else if (s == NULL) //msg_tbl == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Foundation data is missing\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->connection == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid connection info\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->peer_domain == NULL || s->peer_domain->data == NULL || s->peer_domain->size == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid peer_domain\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	/*else if ((list = s->subs_invalid_list) != NULL && (*errp = list->travel(list, _check_subs_invalid, (void*)msg_tbl)).code)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Invalid subscription spec is invalid\n");
		ERR_SET_OUT(errp, EINVAL);
	}*/
	else if ((list = s->subs_normal_list) != NULL && (*errp = list->travel(list, _check_subs_type, (void*)DZ1_VAL2PTR32(SubscribeSpecTypePresent_single))).code)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Normal subscription spec is invalid\n");
		ERR_OUT(errp);
	}
	else if (s->subs_cancel != NULL && _check_sub_type(s->subs_cancel, SubscribeSpecTypePresent_registered) == FALSE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Registered Subscription Cancel spec is invalid\n");
		ERR_OUT(errp);
	}
	else if (s->subs_pub_retry != NULL && _check_sub_type(s->subs_pub_retry, SubscribeSpecTypePresent_registered) == FALSE && _check_sub_type(s->subs_pub_retry, SubscribeSpecTypePresent_single) == FALSE)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Publication retry test spec is invalid\n\n");
	}
	/*else if ((list = s->subs_total_list) != NULL && (*errp = list->travel(list, _check_subs_type, (void*)DZ1_VAL2PTR32(SubscribeSpecTypePresent_registered))).code)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Normal subscription spec is invalid\n");
		ERR_OUT(errp);
	}
	else if (s->subs_total_list != NULL && s->subs_total_list->count(s->subs_total_list) > 0 && s->subs_total_collect < 180)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_total_collect is missing\n");
		ERR_OUT(errp);
	}
	else if (s->subs_duo != NULL && (s->subs_duo->session1 == NULL || s->subs_duo->session2 == NULL))
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_duo is missing\n");
		ERR_OUT(errp);
	}*/
	else if (s->subs_cancel_reason == Iso14827SubscriptionCancel_max)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_cancel_reason is not initialized\n");
		ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Check Scenario : Client
///////////////////////////////////////////////////////////////////////////////



static Iso14827TestClientAccount* _get_account1(Iso14827TestClientRole1* s)
{
	Iso14827TestClientAccount* ret = NULL;
	Iso14827TestClientConnection* c = s->connection;
	Iso14827TestClientPassive* p = NULL;
	Iso14827TestClientActive* a = NULL;
	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		p = c->x.passive;
		ret = p->account1;
		break;
	case Iso14827TestClientConnectionPresent_active:
		a = c->x.active;
		ret = a->account1;
		break;
	}
	return ret;
}
static void _client1_timer_cleanup(Iso14827TestHelperEnv* env, void* timer)
{

	Iso14827TestScenario* scenario = env->scenario;
	Iso14827TestClientRole1* s = scenario->x.client1;

	Iso14827TestClientAccount* acc1 = _get_account1(s);
	//Iso14827TestClientAccount* acc2 = _get_account2(s);
	if (acc1 != NULL) Iso14827TestHelperTimer_clrClientTimer(timer, acc1->my_domain, s->peer_domain, acc1->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
	//if (acc2 != NULL) Conformance1TestTimer_clrClientTimer(timer, acc2->my_domain, s->peer_domain, acc2->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
}

///////////////////////////////////////////////////////////////////////////////
// Install Scenario : Client
bool_t Iso14827TestClient1Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* errp)
{
	Iso14827TestClientConnection* c = s->connection;
	Iso14827TestClientPassive* p = NULL;
	Iso14827TestClientActive* a = NULL;
	Iso14827TestClientAccount* acc = NULL;

	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		p = c->x.passive;
		env->primary_acc = acc = p->account1;
		break;
	case Iso14827TestClientConnectionPresent_active:
		a = c->x.active;
		env->primary_acc = acc = a->account1;
		break;
	}

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if (acc == NULL || (*errp = ItsIso14827_createClient4Task(my_queue_id, arg->t14827, acc->my_domain)).code) ERR_OUT(errp);
	else
	{
		env->flags = CLIENT_FLAG_CREATED1;

		if (errp->code == 0) env->state = Iso14827TestClient1State_initial;
	}



	return errp->code == 0 ? TRUE : FALSE;
}

// Install Scenario : Client
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF client1_scenario[] =
{
	_client1_initial,
	_client1_wait_initiate,
	_client1_wait_login_dup,
	_client1_wait_disconnect,
	_client1_wait_restart,
	_client1_wait_invalid_subs,
	_client1_wait_normal_subs,
	_client1_wait_subs_cancel,
	_client1_wait_deferred_ack,
	_client1_wait_terminate,
	NULL
};

static bool_t Iso14827TestClient1Scenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s,
	Iso14827TestClientEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= Iso14827TestClient1State_complete) ERR_SET_OUT(errp, EFAULT);
	else if (client1_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		_clear_check_list(test_check_list);
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
		if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		ERR_OUT(errp);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestClient1State_complete)
		{
			_client1_timer_cleanup(env, timer);
			*ret_is_complete = TRUE;
			_clear_check_list(test_check_list);
			if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("@@@ Iso14827 Client Test is Done!\n"));
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}




///////////////////////////////////////////////////////////////////////////////
// Start Scenario : Client1
bool_t Iso14827TestClient1Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((test_check_list = _get_check_list_by_test_scenario(arg->testScenario)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if (s->validate_set != NULL)
	{
		switch (s->validate_set->present)
		{
		case Iso14827TestValidateSetPresent_centerClient2rse:
			if (s->validate_set->x.centerClient2rse->test_bsm == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_bsm);
			break;

		case Iso14827TestValidateSetPresent_rseClient2center:
			if (s->validate_set->x.rseClient2center->test_map == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_map);
			if (s->validate_set->x.rseClient2center->test_rsa == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_rsa);
			if (s->validate_set->x.rseClient2center->test_tim == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_tim);
			break;
		case Iso14827TestValidateSetPresent_itsk00100_3c2cClient:
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_incident_detection_info == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_incident_detection_info);
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_incident_termination_info == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_incident_termination_info);
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_incident_detection_video_file_info_provide == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_incident_detection_video_file_info_provide);
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_control_state_info == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_control_state_info);
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_sensor_state_info == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_sensor_state_info);
			if (s->validate_set->x.itsk00100_3c2cClient->test_pub_moving_object == FALSE)
				_mark_done_validate_test(test_check_list, test_name_test_pub_moving_object);
		default:
			break;
		}
	}
	return Iso14827TestClient1Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_start, NULL, ret_is_complete, err);
}
// Start Scenario : Client1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Trigger Scenario : Client1
bool_t Iso14827TestClient1Scenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient1Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_trigger, NULL, ret_is_complete, err);
}
// Trigger Scenario : Client1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message : Client1
bool_t Iso14827TestClient1Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient1Scenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Message : Client1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout : Client1
bool_t Iso14827TestClient1Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Iso14827TestHelperTimer* tmr, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient1Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_timeout, tmr, ret_is_complete, err);
}
// Timeout : Client1
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Client1
bool_t Iso14827TestClient1Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* err)
{	// stop testing progress
	DZ1_ERROR_SAFE_PTR(errp, err);
	_client1_timer_cleanup(env, timer);

	return errp->code == 0 ? TRUE : FALSE;
}
// Stop : Client1
///////////////////////////////////////////////////////////////////////////////


bool_t Iso14827TestClient1Scenario_validateReceived(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, void* msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient1Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_validate, msg, ret_is_complete, err);
}

void   Iso14827TestClient1Scenario_reset(Iso14827TestClientRole1* s, Iso14827TestHelperEnv* env)	// back to prepared status
{
	// back to prepared state
	Iso14827TestClientAccount* acc = NULL;
	if (env->flags & CLIENT_FLAG_PORT_OPENED)
	{
		Iso14827TestClientActive* a = NULL;
		Iso14827TestClientPassive* p = NULL;
		Iso14827TestClientConnection* c = s->connection;
		switch (c->present)
		{
		case Iso14827TestClientConnectionPresent_passive:
			p = c->x.passive;
			ItsIso14827_closePort(env->t14827, p->local_port);
			break;
		}
	}
	if (env->flags & CLIENT_FLAG_CONNECTED1)
	{
		if ((acc = _get_account1(s)) != NULL)
			ItsIso14827_disconnectFromServer(env->t14827, acc->my_domain, s->peer_domain, acc->userid, Iso14827Logout_clientRequested);
	}

	env->selected_codec = Dz1Asn1Codec_max;
	Dz1SockAddr_delAndSetNull(&env->server_addr);
	SubscribeSpecList_delAndSetNull(&env->test_subs);
	env->test_subs_id = 0;
	Iso14827TestSubList_delAndSetNull(&env->subs_reg);

	env->flags &= (CLIENT_FLAG_CREATED1);
	env->state = Iso14827TestClient1State_initial;
}


void   Iso14827TestClient1Scenario_release(Iso14827TestClientRole1* s, Iso14827TestHelperEnv* env)	// release resource
{
	// called when terminate state
	Iso14827TestClient1Scenario_reset(s, env);
	Iso14827TestClientAccount* acc = NULL;
	if (env->flags & CLIENT_FLAG_CREATED1)
	{
		if ((acc = _get_account1(s)) != NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client A Delete\n");
			ItsIso14827_deleteClient(env->t14827, acc->my_domain);
			env->flags &= ~CLIENT_FLAG_CREATED1;
		}
	}
	env->primary_acc = env->secondary_acc = NULL;
}


void Iso14827TestClientRole1_status(Iso14827TestClientRole1* s, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (s != NULL)
	{
		Iso14827TestClientAccount* acc = _get_account1(s);

		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & CLIENT_FLAG_CREATED1) { Dz1STRCPY(dp, Dz1T("cre ")); dp += 5; };
		if (env->flags & CLIENT_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("port ")); dp += 5; };
		if (env->flags & CLIENT_FLAG_CONNECTED1) { Dz1STRCPY(dp, Dz1T("conn ")); dp += 5; };

		if (env->flags & CLIENT_FLAG_INVALID_LOGIN) { Dz1STRCPY(dp, Dz1T("login_invalid")); dp += 14; };
		if (env->flags & CLIENT_FLAG_DUPLICATE_LOGIN) { Dz1STRCPY(dp, Dz1T("login_dupl")); dp += 11; };
		if (env->flags & CLIENT_FLAG_A_HEARTBEAT) { Dz1STRCPY(dp, Dz1T("hb")); dp += 3; };
		if (env->flags & CLIENT_FLAG_DISCONNECT_TEST) { Dz1STRCPY(dp, Dz1T("session")); dp += 8; };
		if (env->flags & CLIENT_FLAG_DEFFERED_PUB_ACK) { Dz1STRCPY(dp, Dz1T("pub_retry")); dp += 10; };
		if (env->flags & CLIENT_FLAG_PUB_CANCEL) { Dz1STRCPY(dp, Dz1T("pub_cancel ")); dp += 11; };
		*dp = 0;
		Dz1Thread_printf(Dz1T("TEST_FLAG = [ %s]\n"), status);
	}
}
