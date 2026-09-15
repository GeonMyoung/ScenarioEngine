#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
// #include <ConformanceMsgUtil.h>

#include "Iso14827TestHelperEnv.h"
// #include "Iso14827TestMsg.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperMsgSet.h"
#include "Iso14827TestHelperMsg.h"

#define SERVER2_FLAG_CREATED				0x80000000		// delete need
#define SERVER2_FLAG_PORT_OPENED			0x40000000		// close need
#define SERVER2_FLAG_CONNECTED				0x20000000		// disconnect need

#define SERVER2_FLAG_HEARTBEAD_RECEIVED		0x00010000
#define SERVER2_FLAG_SUBSCRIBE_DONE			0x00020000


static Dz1Str test_name_test_total = Dz1T("test_total");

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


static bool_t _server2_set_ed_timer(Iso14827TestHelperEnv* env, void* timer, Dz1Asn1OctetStr* user, Dz1Str oidStr, u32_t subID, Dz1Error* errp);
static bool_t __server2_data_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* errp);
static Dz1TaskProcStatus _server2_pub_ed(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestHelperTimer* tmr = (Iso14827TestHelperTimer*)(*tData);
	Iso14827TestHelperTimerED* edTmr = tmr->x.ed;

	Iso14827TestServerRole2* s = env->scenario->x.server2;
	if (s == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestSubEntry* node = NULL;
		if ((node = Iso14827TestSubList_findByID(env->subs_reg, s->peer_domain, edTmr->subID)) == NULL)
		{
			//Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_INVALID_PROCESS;
			//// Iso14827TestHelperEnvUtil_notifyError(env, env->current_test, code, Iso14827TestProcessStatusCodeStrA(code), )
			//if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, edTmr->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
			//else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
		else
		{
			if (__server2_data_provide(arg, env, timer, s, edTmr->user, edTmr->subID, edTmr->oidStr, errp) == FALSE) ERR_OUT(errp);
			else if (_server2_set_ed_timer(env, timer, edTmr->user, edTmr->oidStr, edTmr->subID, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}


	//// 타이머를 다시 등록하여 주기적으로 호출되도록 함
	//if (!(env->flags & SERVER3_FLAG_PUB_INVALID_SENT && errp->code == 0))
	//{
	//	if (_server3_set_ed_timer(env, timer, edTmr->user, edTmr->oidStr, edTmr->subID, errp) == FALSE) {
	//		ERR_OUT(errp);
	//	}
	//}
	//else
	//{
	//	//ed finish
	//}
	return ret;
}

static bool_t _server2_set_ed_timer(Iso14827TestHelperEnv* env, void* timer, Dz1Asn1OctetStr* user, Dz1Str oidStr, u32_t subID, Dz1Error* errp)
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
		else if ((*errp = Iso14827TestHelperTimer_update(timer, &tmr, 10000000, _server2_pub_ed)).code) ERR_OUT(errp);
		else
		{
			tmr = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestHelperTimer_delAndSetNull, (void*)&tmr);
	}
	return ERR_IS_SUCCESS(errp);
}



///////////////////////////////////////////////////////////////////////////////
// INITIAL = wait START
static bool_t _server2_initial_active(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ConfTestSocketAddress* c, Dz1Error* errp)
{
	Dz1SockAddr peer;
	if ((*errp = Dz1SockAddr_setAddrByName(&peer, c->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, c->port)).code) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_connectToClient(arg->t14827, &peer, s->my_domain, s->peer_domain, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ INITIATE sent\n");
		// notify to web
		// initiate sent!
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* errp)
{
	Iso14827TestConnection* c = s->connection;

	switch (c->present)
	{
	case Iso14827TestConnectionPresent_passive:
		if ((*errp = ItsIso14827_openPort(arg->t14827, c->x.passive, arg->initial_codec, ItsIso14827CRCCheck_warning)).code) ERR_OUT(errp);
		else
		{
			char log[128];
			sprintf(log, Dz1T("Port (%d)를 오픈했습니다. 접속 수신을 대기합니다."), c->x.passive);
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Port(%d) opened\n", c->x.passive);
			env->flags |= SERVER2_FLAG_PORT_OPENED;
		}
		break;
	case Iso14827TestConnectionPresent_active:
		if (_server2_initial_active(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t _server2_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_start:
		ItsIso14827SocketHook_set(_14827_hook_func, env);
		env->current_test = test_name_test_total;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (_server2_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else
		{
			//Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login test started...\n");
			env->state = Iso14827TestServer2State_wait_auth;

			// notify to web
			// login test start!!

			Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_logout:
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server2_initial() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// INITIAL = wait START
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Heartbeat received
static bool_t _server2_heartbeat_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventEcho* msg, Dz1Error* errp)
{
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("하트비트를 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_echoReply(arg->t14827, s->my_domain, s->peer_domain, msg->user, msg->echoID)).code) ERR_OUT(errp);
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("하트비트를 응답을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if ((env->flags & SERVER2_FLAG_HEARTBEAD_RECEIVED) == 0)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat received\n");
			env->flags |= SERVER2_FLAG_HEARTBEAD_RECEIVED;
		}
		// notify to web
		// heartbeat received!!
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Heartbeat received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait AUTH

static Iso14827TestAuth auth_func(ItsIso14827ServerEventAuth* msg, Dz1Asn1Codec* selected_codec)
{
	// TBD...
	*selected_codec = Dz1Asn1Codec_ber;
	return Iso14827TestAuth_success;
}
static bool_t _server2_wait_auth_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventAuth* msg, bool_t* is_authenticate, Dz1Error* errp)
{
	Iso14827TestConnection* c = s->connection;

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0)
	{
		// 잘못된 상대 도메인 명 -> 오류 -> 시험종료
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Unknown Domain Name\n");
		if ((*errp = ItsIso14827_loginReject(arg->t14827, s->my_domain, msg->peerDomain, msg->user, Iso14827RejectLogin_unknownDomainName)).code) ERR_OUT(errp);
		else
		{
			// notifty to web
			// login reject! - unknown domain name
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("잘못된 상대 도메인 이름입니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			ERR_SET_OUT(errp, EPERM);
		}
	}
	else if (env->user != NULL)
	{
		// 중복 연결 -> 오류 -> 시험 종료
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Session duplicated\n");
		if ((*errp = ItsIso14827_loginReject(arg->t14827, s->my_domain, msg->peerDomain, msg->user, Iso14827RejectLogin_sessionExist)).code) ERR_OUT(errp);
		else
		{
			// notify to web
			// login reject! - session exist
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("중복 로그인 요청입니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			ERR_SET_OUT(errp, EPERM);
		}
	}
	else
	{
		u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
		Iso14827TestAuth auth_result = Iso14827TestAuth_max;
		Dz1Asn1Codec selected_codec = Dz1Asn1Codec_max;

		// notify to web
		// login request received!!!
		if ((auth_result = auth_func(msg, &selected_codec)) == Iso14827TestAuth_success)
		{
			// 인증 성공
			if (selected_codec == Dz1Asn1Codec_max || selected_codec == Dz1Asn1Codec_unknown) ERR_SET_OUT(errp, EFAULT);
			else if ((*errp = _ItsIso14827_loginAccept(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, selected_codec, ItsIso14827CRCCheck_warning, NULL, NULL)).code) ERR_OUT(errp);
			else
			{
				*is_authenticate = TRUE;

				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Authenticate success\n");

				// notify to web
				// authenticate success!



				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			// 인증 실패
			//	notify to web
			// authenticate fail!
			Iso14827RejectLogin reason = Iso14827RejectLogin_accessDenied;
			switch (auth_result)
			{
			case Iso14827TestAuth_not_found:
			case Iso14827TestAuth_invalid_passwd:		reason = Iso14827RejectLogin_invalidPassword; break;
			case Iso14827TestAuth_codec_not_support:	reason = Iso14827RejectLogin_other; break;
			}
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Authenticate failed\n");

			if ((*errp = ItsIso14827_loginReject(arg->t14827, msg->myDomain, msg->peerDomain, msg->user, reason)).code) ERR_OUT(errp);
			else
			{
				// notify to web
				// login reject sent!
				Dz1Error_set(errp, 0);
			}

		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_wait_auth(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t go_next_state = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server2_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_auth:
		if (_server2_wait_auth_received(arg, env, timer, s, (ItsIso14827ServerEventAuth*)_msg, &go_next_state, errp) == FALSE) ERR_OUT(errp);
		else if (go_next_state)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Wait establish...\n");
			// notify to web
			// wait establish!
			env->state = Iso14827TestServer2State_wait_connected;

		}
		else
		{
			if (Iso14827TestConnection_isPassive(s->connection)) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Iso14827TestServerEvent_timeout:
		ERR_SET_OUT(errp, ETIMEDOUT); // Login 안함 -> 시험 종료
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server2_wait_auth() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait AUTH
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait CONNECTED
static bool_t _server2_wait_connected_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventConnected* msg, Dz1Error* errp)
{
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Established\n");

	env->flags |= SERVER2_FLAG_CONNECTED;
	env->selected_codec = msg->selected;
	if ((env->user = Dz1Asn1OctetStr_clone(msg->user, errp)) == FALSE) ERR_OUT(errp); // user 정보 보관
	else Dz1Error_set(errp, 0);

	// notify to web!
	// established!! (client connected!)

	Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("클라이언트와의 세션 연결을 성공하였습니다."), NULL, NULL, errp);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_wait_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	bool_t msg_accepted = FALSE;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server2_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_connected:
		if (_server2_wait_connected_received(arg, env, timer, s, (ItsIso14827ServerEventConnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server2_wait_connected() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & SERVER2_FLAG_CONNECTED))
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션 수신 대기 상태로 전환합니다..."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Ready to subscription test...\n");
		env->state = Iso14827TestServer2State_established;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait CONNECTED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Data Provide
static bool_t __server2_data_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* errp)
{
	Dz1Binary* eam = NULL;
	pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&eam);
	if (0) {}
	// else if ((eam = Iso14827TestMsgSet_getPublicationData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	else if ((eam = Iso14827TestMsgSet_getPublicationSampleData(arg->msg_api, oidStr, env->selected_codec, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_dataProvide(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, oidStr, eam->data, eam->size)).code) ERR_OUT(errp);
	else
	{
		_publication_log_dump_(arg->msg_api, oidStr, eam->data, eam->size, env->selected_codec);

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 퍼블리케이션을 전송합니다."), eam, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&eam);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_registered_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventPubStart* msg, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;
	if ((node = Iso14827TestSubList_findByID(env->subs_reg, s->peer_domain, msg->subID)) == NULL)
	{
		if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, msg->subID, Iso14827PublicationMgmt_terminateDataNoLongerAvailable)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (__server2_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_single_provide(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	// 단일 요청에 대한 응답
	if (__server2_data_provide(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Data Provide
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PubData Reject received
static bool_t _server2_pubdata_reject_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventPubInform* msg, Dz1Error* errp)
{
	// just response cancel request
	Iso14827TestSubEntry* reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->subID);
	if (reg_entry != NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication canceled(%u = %s)\n", msg->subID, reg_entry->oid);
		Dz1Error_set(errp, 0);
		// notify to web
		// publication canceled! (subID, oidStr)

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
	}
	return ERR_IS_SUCCESS(errp);
}
// PubData Reject received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request expired
static bool_t _server2_pub_expire_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventPubExpire* msg, Dz1Error* errp)
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

		char log[128];
		sprintf(log, Dz1T("시험 대상으로부터 퍼블리케이션 거부 패킷을 수신하였습니다. 서브스크립션 id: %s"), str_reason);

		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp);

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->subID);
	}
	return ERR_IS_SUCCESS(errp);
}
// Request expired
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Request Response
static bool_t _server2_request_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Dz1Error* errp)
{
	int oid_idx = 0;
	Iso14827TestMsgStructAPI* api = NULL;

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription received = %s\n", oidStr);
	//notify to web
	// subscription received(oid)

	char log[128];
	sprintf(log, Dz1T("서브스크립션을 수신하였습니다. 요청 OID : %s"), oidStr);
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((api = Iso14827TestMsgSet_findAPI(arg->msg_api, oidStr, &oid_idx)) == NULL)
	{
		// 모르는 OID 수신
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Unknown OID = %s\n", oidStr);

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("요청 OID가 유효하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

		if ((*errp = ItsIso14827_singleReject(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID, Iso14827RejectSubscription_unknownSubscriptionMsgId)).code) ERR_OUT(errp);
		else
		{
			char log[128];
			sprintf(log, Dz1T("서브스크립션 거절 패킷을 전송합니다. 거절 사유 : %s"), Iso14827RejectSubscriptionStrA(Iso14827RejectSubscription_unknownSubscriptionMsgId));
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			ERR_SET_OUT(errp, EPERM);
		}
	}
	// 아는 OID
	else
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("서브스크립션 수락 패킷을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		if ((*errp = ItsIso14827_singleAccept(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, user, subID)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription accepted\n");
			// notify to web
			// subscription accepted!!!
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// Request Response
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single Request
static bool_t _server2_single_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventSubSignle* msg, Dz1Error* errp)
{
	if (_server2_request_response(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Single Request
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

///////////////////////////////////////////////////////////////////////////////
// Registered Request
static bool_t _server2_registered_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Asn1OctetStr* user, u32_t subID, Dz1Str oidStr, Iso14827TestSubType subs_type, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;

	if ((node = Iso14827TestSubList_append(env->subs_reg, s->peer_domain, subID, oidStr, subs_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ListAddCancelArg add_cancel_arg = { env->subs_reg, (void**)&node };
		pthread_cleanup_push(Iso14827TestSubList_addCancel, (void*)&add_cancel_arg);
		if (_server2_request_response(arg, env, timer, s, user, subID, oidStr, errp) == FALSE) ERR_OUT(errp);
		else
		{


			if (subs_type == Iso14827TestSubType_event_driven)
			{
				if (_server2_set_ed_timer(env, timer, user, oidStr, subID, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

			}

			node = NULL;
			if (_is_all_subscribed(env->subs_reg, arg->msg_api))
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ All Subscriptions are received!\n");
				// notify to web
				// all subscriptions are received!

				Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("모든 서브스크립션을 확인하였습니다."), NULL, NULL, errp);

				env->flags |= SERVER2_FLAG_SUBSCRIBE_DONE;
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Iso14827TestSubList_addCancel, (void*)&add_cancel_adrg);
	}
	return ERR_IS_SUCCESS(errp);
}
// Registered Request
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Event-Driven Request
static bool_t _server2_ed_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventSubPrepareED* msg, Dz1Error* errp)
{
	// msg->latency_sec;
	if (_server2_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_event_driven, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Event-Driven Request
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Periodic Request received
static bool_t _server2_periodic_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, ItsIso14827ServerEventSubPrepareP* msg, Dz1Error* errp)
{
	// msg->period_sec;
	if (_server2_registered_received(arg, env, timer, s, msg->user, msg->subID, msg->oidStr, Iso14827TestSubType_periodic, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Periodic Request received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ESTABLISHED
static bool_t _server2_wait_established(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server2_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_single:
		if (_server2_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else if (_server2_single_provide(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_event_driven:
		if (_server2_ed_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareED*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_periodic:
		if (_server2_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_start:
	case Iso14827TestServerEvent_data_period:
		if (_server2_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_pubdata_rejected:
		if (_server2_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_stop:
		break;
	case Iso14827TestServerEvent_req_expired:
		if (_server2_pub_expire_received(arg, env, timer, s, (ItsIso14827ServerEventPubExpire*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server_wait_established() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & SERVER2_FLAG_SUBSCRIBE_DONE))
	{
		u64_t duration_us = (u64_t)s->subs_timeout_s * 1000000;

		if (Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER2, duration_us, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Timer Start!\n");
			// notify to web
			// timer start!

			Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("설정된 정보 요청 만료 시간동안 퍼블리케이션을 전송합니다."), NULL, NULL, errp);

			env->state = Iso14827TestServer2State_wait_timeout;
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// ESTABLISHED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait TIMEOUT
static bool_t _server2_release_subscription(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* errp)
{
	Iso14827TestSubEntry* node = NULL;
	Iso14827TestSubList* list = NULL;
	if ((list = env->subs_reg) == NULL) ERR_SET_OUT(errp, EFAULT);
	while (errp->code == 0 && (node = list->getHead(list)) != NULL)
	{
		list->extract(list, node);
		pthread_cleanup_push(Iso14827TestServerEvent_delAndSetNull, (void*)&node);
		if ((*errp = ItsIso14827_dataControl(arg->t14827, ItsIso14827DomainType_server, s->my_domain, s->peer_domain, env->user, node->sid, s->subs_cancel_reason)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Iso14827TestServerEvent_delAndSetNull, (void*)&node);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _server2_wait_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server2_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_single:
		if (_server2_single_received(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else if (_server2_single_provide(arg, env, timer, s, (ItsIso14827ServerEventSubSignle*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_event_driven:
		if (_server2_ed_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareED*)_msg, errp) == FALSE);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_req_periodic:
		if (_server2_periodic_received(arg, env, timer, s, (ItsIso14827ServerEventSubPrepareP*)_msg, errp) == FALSE);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_start:
	case Iso14827TestServerEvent_data_period:
		if (_server2_registered_provide(arg, env, timer, s, (ItsIso14827ServerEventPubStart*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_pubdata_rejected:
		if (_server2_pubdata_reject_received(arg, env, timer, s, (ItsIso14827ServerEventPubInform*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_data_stop:
	case Iso14827TestServerEvent_req_expired:
		break;
	case Iso14827TestServerEvent_timeout:
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Timeout...\n");
		//notify to web
		// timeout!

		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("설정한 정보 요청 만료 시간이 되어, 등록한 서브스크립션들을 취소합니다."), NULL, NULL, errp);

		if (_server2_release_subscription(arg, env, timer, s, errp) == FALSE)ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server2_wait_timeout() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && env->subs_reg->count(env->subs_reg) == 0 && (env->flags & SERVER2_FLAG_HEARTBEAD_RECEIVED))
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ All subscriptions are released...\n");
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Terminate Client...\n");

		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("모든 서브스크립션을 취소하였습니다."), NULL, NULL, errp);
		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("클라이언트에게 Terminate를 전송합니다."), NULL, NULL, errp);

		if ((*errp = ItsIso14827_terminateClient(arg->t14827, s->my_domain, s->peer_domain, env->user)).code) ERR_OUT(errp);
		else
		{

			env->state = Iso14827TestServer2State_wait_logout;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait TIMEOUT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait LOGOUT
static bool_t _server2_wait_logout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestServerRole2* s = (Iso14827TestServerRole2*)_scenario;
	Iso14827TestServerEvent ev = (Iso14827TestServerEvent)_ev;

	switch (ev)
	{
	case Iso14827TestServerEvent_heartbeat:
		if (_server2_heartbeat_received(arg, env, timer, s, (ItsIso14827ServerEventEcho*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestServerEvent_logout:
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client logout...\n");


		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("클라이언트가 로그아웃 하였습니다."), NULL, NULL, errp);
		env->flags &= ~SERVER2_FLAG_CONNECTED;
		// notify to web
		// client logout!!
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_server2_wait_logout() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & SERVER2_FLAG_CONNECTED) == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test Complete...\n");
		env->state = Iso14827TestServer2State_complete;
		// notify to web
		// test complete!!;
	}
	return ERR_IS_SUCCESS(errp);
}
// wait LOGOUT
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF server2scenario[] =
{
	_server2_initial,
	_server2_wait_auth,
	_server2_wait_connected,
	_server2_wait_established,
	_server2_wait_timeout,
	_server2_wait_logout,
	NULL
};

static void _server2_timer_cleanup(void* timer)
{
	Iso14827TestHelperTimer_clrGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_SERVER2);
}

static bool_t Iso14827TestServer2Scenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Iso14827TestServerEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env->state >= Iso14827TestServer2State_complete) ERR_SET_OUT(errp, EFAULT);
	else if (server2scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		// Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestServer2State_complete)
		{


			Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);



			_server2_timer_cleanup(timer);
			*ret_is_complete = TRUE;
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Check Scenario : Server 2
bool_t Iso14827TestServer2Scenario_check(Iso14827TestServerRole2* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
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
	else if (s->subs_timeout_s < 180)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_timeout_s is too small (%u < 180)\n", s->subs_timeout_s);
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->subs_cancel_reason == Iso14827PublicationMgmt_max)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_cancel_reason is not initialized\n");
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (s->subs_cancel_reason == Iso14827PublicationMgmt_resume ||
		s->subs_cancel_reason == Iso14827PublicationMgmt_temporarilySuspended)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_cancel_reason(%s) is wrong\n", Iso14827PublicationMgmtStrA(s->subs_cancel_reason));
		ERR_SET_OUT(errp, EINVAL);
	}
	else Dz1Error_set(errp, 0);


	return ERR_IS_SUCCESS(errp);
}
// Check Scenario : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Prepare Scenario : Server 2
bool_t Iso14827TestServer2Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((env->subs_reg = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = ItsIso14827_createServer4Task(my_queue_id, arg->t14827, s->my_domain, 1, NULL, 0)).code) ERR_OUT(errp);
	else
	{
		env->state = Iso14827TestServer2State_initial;
		env->flags = SERVER2_FLAG_CREATED;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Prepare Scenario : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Start Scenario : Server 2
bool_t Iso14827TestServer2Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return Iso14827TestServer2Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_start, NULL, ret_is_complete, errp);
}
// Start Scenario : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message : Server 2
bool_t Iso14827TestServer2Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Iso14827TestServerEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer2Scenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Message : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout : Server 2
bool_t Iso14827TestServer2Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestServer2Scenario_event(arg, env, timer, s, Iso14827TestServerEvent_timeout, (void*)&timer_id, ret_is_complete, err);
}
// Timeout : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Server 2
bool_t Iso14827TestServer2Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestServerRole2* s, Dz1Error* err)
{
	// stop testing progress
	DZ1_ERROR_SAFE_PTR(errp, err);
	_server2_timer_cleanup(timer);
	return ERR_IS_SUCCESS(errp);
}
// Stop : Server 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Cleanup : Server 2
void   Iso14827TestServer2Scenario_reset(Iso14827TestServerRole2* s, Iso14827TestHelperEnv* env)
{
	// back to prepared status
	if (env->flags & SERVER2_FLAG_PORT_OPENED)
	{
		Iso14827TestConnection* c = s->connection;
		if (c->present == Iso14827TestConnectionPresent_passive)
		{
			ItsIso14827_closePort(env->t14827, c->x.passive);
		}
	}

	if (env->user != NULL)
	{
		if (env->flags & SERVER2_FLAG_CONNECTED)
		{
			ItsIso14827_terminateClient(env->t14827, s->my_domain, s->peer_domain, env->user);
		}
		Dz1Asn1OctetStr_delAndSetNull(&env->user);
	}

	env->selected_codec = Dz1Asn1Codec_max;
	Iso14827TestSubList_flush(env->subs_reg);

	env->state = Iso14827TestServer2State_initial;
	env->flags = SERVER2_FLAG_CREATED;
}

void   Iso14827TestServer2Scenario_release(Iso14827TestServerRole2* s, Iso14827TestHelperEnv* env)	// release resource
{
	// called when terminate state
	Iso14827TestServer2Scenario_reset(s, env);
	if (env->flags & SERVER2_FLAG_CREATED)
	{
		ItsIso14827_deleteServer(env->t14827, s->my_domain);
		env->flags &= ~SERVER2_FLAG_CREATED;
	}
}
// Cleanup : Server 2
///////////////////////////////////////////////////////////////////////////////

void   Iso14827TestServerRole2_status(Iso14827TestServerRole2* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (p != NULL)
	{
		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & SERVER2_FLAG_CREATED) { Dz1STRCPY(dp, Dz1T("cre ")); dp += 4; }
		if (env->flags & SERVER2_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("port ")); dp += 5; }
		if (env->flags & SERVER2_FLAG_CONNECTED) { Dz1STRCPY(dp, Dz1T("conn ")); dp += 5; }
		if (env->flags & SERVER2_FLAG_HEARTBEAD_RECEIVED) { Dz1STRCPY(dp, Dz1T("hb ")); dp += 3; }
		if (env->flags & SERVER2_FLAG_SUBSCRIBE_DONE) { Dz1STRCPY(dp, Dz1T("subscribe ")); dp += 10; }
		*dp = 0;
		Dz1Thread_printf(Dz1T("TEST FLAG = [ %s]\n"), status);
	}
}

