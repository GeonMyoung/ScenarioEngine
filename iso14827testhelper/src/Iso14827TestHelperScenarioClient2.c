#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>

#include "Iso14827TestHelperEnv.h"
//#include "Iso14827TestMsg.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperMsgSet.h"
#include "Iso14827TestHelperMsg.h"
#include <TechnicalRegulation2MsgStructAPI.h>

#define CLIENT_FLAG_CREATED1				0x80000000
#define CLIENT_FLAG_PORT_OPENED				0x20000000
#define CLIENT_FLAG_CONNECTED1				0x10000000

#define CLIENT_FLAG_A_HEARTBEAT				0x01000000
#define CLIENT_FLAG_TOTAL_TEST				0x00020000

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


///////////////////////////////////////////////////////////////////////////////
// connection helper
static bool_t _client_establish_session(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Dz1SockAddr* peer, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, Dz1Error* errp)
{


	Iso14827RejectLogin result = Iso14827RejectLogin_max;
	Dz1Asn1Codec codec = arg->initial_codec;

	// arg->tMain에게 로그인 시도 MSG 전송 (peerDomain, Accountinfo)
	//Iso14827Test_ScenarioSendMessage* send_msg = NULL;
	//if ((send_msg = Iso14827Test_ScenarioSendMessage_new(Iso14827Test_ScenarioSendMessagePresent_notify, NULL, errp)) == NULL) ERR_OUT(errp);
	//else if ((send_msg->x.notify = Iso14827Test_ScenarioNotifyMessage_new(Iso14827Test_ScenarioNotifyMessagePresent_notify, NULL, errp)) == NULL) ERR_OUT(errp);
	//else if ((send_msg->x.notify->x.notify = Dz1Str_clone(Dz1T("[Test System] client: trying connect to server!!"), errp)) == NULL) ERR_OUT(errp);
	//else if ((Iso14827TestHelperEnv_sendMsgToMain(env, send_msg, errp)) == FALSE) ERR_OUT(errp);
	//else Dz1Error_set(errp, 0);
	// arg->tMain에게 로그인 시도 MSG 전송 (peerDomain, Accountinfo)
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

	if ((*errp = _ItsIso14827_connectToServer(arg->t14827, peer, acc->my_domain, peer_domain, acc->authinfo, acc->userid, acc->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code) ERR_OUT(errp); // hb, codec, rsp_time 지정할수있도록 설정 또는 선언
	else
	{
		env->selected_codec = codec;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _client_bind_session(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, ItsIso14827ClientEventInitiate* msg, Iso14827TestClientAccount* acc, Dz1Error* errp)
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
	if ((eam = Iso14827TestMsgSet_getNullData(codec, errp)) == NULL) ERR_OUT(errp);
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
			// subscribe notify!!!!! 20240503
			// subsid, oid
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
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("서브스크립션이 취소됐습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Canceled...\n");
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
// heartbeat response received
static bool_t _client_echo_responsed(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	env->hb_cnt++;
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 HeartBeat응답을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	// arg->tMain HeartBeat Responsed 하트비트 응답 수신함.

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat Respond...\n");

	if ((env->flags & CLIENT_FLAG_A_HEARTBEAT) == 0 && env->hb_cnt == 2)
	{
		env->flags |= CLIENT_FLAG_A_HEARTBEAT;
	}

	return errp->code == 0 ? TRUE : FALSE;
}
// heartbeat response received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// setup active mode & login test
static bool_t _client_connect_and_test_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Iso14827TestClientActive* c, Dz1Error* errp)
{
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1SockAddr peer;
	ConfTestSocketAddress* dst = c->peer;
	if ((*errp = Dz1SockAddr_setAddrByName(&peer, dst->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, dst->port)).code) ERR_OUT(errp);
	else
	{
		Iso14827TestClientAccount* acc = c->account1;

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login...\n");
		if (_client_establish_session(arg, env, &peer, s->peer_domain, acc, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->flags |= CLIENT_FLAG_CONNECTED1;
			Dz1Error_set(errp, 0);

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("로그인을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Login Success...\n");
			if ((env->server_addr = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// setup active mode & login test
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INITIAL State
static bool_t _client2_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
{
	// start event handler
	Iso14827TestClientConnection* c = s->connection;
	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		//if (_client_passive_prepare(arg, env, timer, s, c->x.passive, errp) == FALSE) ERR_OUT(errp);
		break;
	case Iso14827TestClientConnectionPresent_active:
		if (_client_connect_and_test_login(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		// else if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestClient2State_connected;
			Dz1Error_set(errp, 0);
		}
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _client2_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole2* s = (Iso14827TestClientRole2*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_start:
		ItsIso14827SocketHook_set(_14827_hook_func, env);
		env->current_test = test_name_test_total;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (_client2_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
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

static bool_t _client2_connected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole2* s = (Iso14827TestClientRole2*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: // 다른 메시지 허용 안함
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_initial() : EVENT %s(%d) not permitted\n", Iso14827TestClientEventStrA(ev), ev);
		ERR_SET_OUT(errp, 0);
		break;
	}

	if (errp->code == 0 && (env->flags & CLIENT_FLAG_A_HEARTBEAT))
	{
		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("정보 연계 시험 전 세션유지 기능을 확인하였습니다."), NULL, NULL, errp);
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestClient2State_wait_total_test;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _client_subscribe_and_register(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestSubList* dst_reg, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, SubscribeSpecEntry* node, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestSubEntry* entry = NULL;

	SubscribeSpecType* type = NULL;
	Iso14827TestSubType subs_type = Iso14827TestSubType_max;

	if ((type = node->type) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (type->present != SubscribeSpecTypePresent_registered) ERR_SET_OUT(errp, EINVAL);
	else if ((subs_type = Iso14827TestSubType_getFromSubscribe(node, errp)) == Iso14827TestSubType_max) ERR_SET_OUT(errp, EFAULT);
	else if ((entry = Iso14827TestSubEntry_new(NULL, -1, node->oid, subs_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827RejectSubscription result = Iso14827RejectSubscription_max;
		pthread_cleanup_push(Iso14827TestSubEntry_delAndSetNull, (void*)&entry);
		if ((entry->peer = Dz1Asn1UTF8Str_clone(peer_domain, errp)) == NULL) ERR_OUT(errp);
		else if (_client_subscribe(arg, env, peer_domain, acc, node, FALSE, &entry->sid, &result, errp) == FALSE) ERR_OUT(errp);
		else if (result != Iso14827RejectSubscription_max) ERR_SET_OUT(errp, EPERM);
		else if (Iso14827TestSubList_insert(dst_reg, &entry, errp) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Iso14827TestSubEntry_delAndSetNull, (void*)&entry);
	}

	return ERR_IS_SUCCESS(errp);
}


///////////////////////////////////////////////////////////////////////////////
// WAIT TOTAL TEST State
static bool_t _client_total_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
{
	// trigger event handler
	if ((env->subs_reg = Iso14827TestSubList_new(errp)) == FALSE) ERR_OUT(errp);
	else
	{
		u32_t cnt = 0;
		SubscribeSpecList* list = NULL;
		SubscribeSpecEntry** arr = NULL;
		pthread_cleanup_push(Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg);
		if ((list = env->test_subs) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((arr = list->get_array(list, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827TestClientAccount* acc = env->primary_acc;

			u32_t i;
			SubscribeSpecEntry* node = NULL;
			SubscribeSpecType* type = NULL;

			Iso14827TestSubEntry* entry = NULL;

			pthread_cleanup_push(Dz1Memory_cancel, (void*)arr);
			for (i = 0; errp->code == 0 && i < cnt; i++)
			{
				if ((node = arr[i]) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (_client_subscribe_and_register(arg, env, env->subs_reg, s->peer_domain, acc, node, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); //  (Dz1Memory_cancel, (void*)arr);

			if (errp->code == 0)
			{
				Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("모든 서브스크립션을 전송하였습니다."), NULL, NULL, errp);
				Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("설정된 정보 요청 만료 시간동안 퍼블리케이션을 수신합니다."), NULL, NULL, errp);
			}
		}
		pthread_cleanup_pop(errp->code); // (Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t _client_total_pub_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{
	Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상으로부터 퍼블리케이션을 수신하였습니다."), &bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);



	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecEntry* spec_entry = NULL;

	Iso14827TestSubEntry* reg_entry = NULL;
	Iso14827TestClientAccount* acc = env->primary_acc;

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(my_domain, peer_domain, user)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EPERM); // identifier 값이 다르면 오류 -> 시험 종료
	}
	else if ((reg_entry = Iso14827TestSubList_findByID(env->subs_reg, s->peer_domain, msg->sid)) == NULL)
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("퍼블리케이션 패킷의 식별자(sid)가 일치하지 않습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT); // 요청한적 없는 Subscription ID -> 시험 종료
	}
	else if (Dz1STRCMP(reg_entry->oid, msg->oidStr) != 0)
	{
		char log[128];
		sprintf(log, Dz1T("퍼블리케이션 패킷의 식별자(OID)가 일치하지 않습니다. 수신 OID = %s"), msg->oidStr);
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EPERM); // identifier 값이 다르면 오류 -> 시험 종료
	}
	else if ((spec_entry = SubscribeSpecList_findByOID(list, reg_entry->oid)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u32_t idx;
		Iso14827TestMsgStructAPI* api = Iso14827TestMsgSet_findAPI(arg->msg_api, msg->oidStr, &idx);
		if (api != NULL)
		{
			if (Dz1STRCMP(Dz1T("1.0.15784.2.0.1"), msg->oidStr) == 0)
			{
				Dz1CommTxPDUResponse* txpdu = NULL;
				if ((txpdu = (Dz1CommTxPDUResponse*)api->struct_decode(&bin, arg->initial_codec, errp)) == NULL) ERR_OUT(errp);
				else
				{
					CommTxPDUList* deser = NULL;
					pthread_cleanup_push(Dz1CommTxPDUResponse_delAndSetNull, (void*)&txpdu);
					// Dz1CommTxPDUResponse_dump(txpdu, 0);
					if ((deser = CommTxPDUList_fromDimz(txpdu, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(CommTxPDUList_delAndSetNull, (void*)&deser);
						Dz1Asn1UTF8Str* str_u8 = NULL;
						if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("CommTxPDUList"), deser, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
							Dz1Binary* data = NULL;
							if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("퍼블리케이션 데이터 : ."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
								else
								{
									data = NULL;
									Dz1Error_set(errp, 0);
								}
								pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
							}
							pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						}
						pthread_cleanup_pop(1); // (CommTxPDUList_delAndSetNull, (void*)&deser);
					}
					pthread_cleanup_pop(1); // (Dz1CommTxPDUResponse_delAndSetNull, (void*)&txpdu);
				}
			}
			//else if (Dz1STRCMP(Dz1T("1.0.15784.2.0.2"), msg->oidStr) == 0)
			else if (Dz1STRCMP(Dz1T("1.0.15784.2.0.2"), msg->oidStr) == 0)
			{
				Dz1CommRxPDUResponse* rxpdu = NULL;
				if ((rxpdu = (Dz1CommRxPDUResponse*)api->struct_decode(&bin, arg->initial_codec, errp)) == NULL) ERR_OUT(errp);
				else
				{
					CommRxPDUList* deser = NULL;
					pthread_cleanup_push(Dz1CommRxPDUResponse_delAndSetNull, (void*)&rxpdu);
					if ((deser = CommRxPDUList_fromDimz(rxpdu, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(CommRxPDUList_delAndSetNull, (void*)&deser);
						Dz1Asn1UTF8Str* str_u8 = NULL;
						if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("CommRxPDUList"), deser, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
							Dz1Binary* data = NULL;
							if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
							else
							{
								pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
								if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("퍼블리케이션 데이터 : ."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
								else
								{
									data = NULL;
									Dz1Error_set(errp, 0);
								}
								pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
							}
							pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						}
						pthread_cleanup_pop(1); // (CommRxPDUList_delAndSetNull, (void*)&deser);
					}
					pthread_cleanup_pop(1); // (Dz1CommRxPDUResponse_delAndSetNull, (void*)&rxpdu);
				}
			}
			// 기본교통정보교환 
			else ERR_SET_OUT(errp, EPERM);
		}
		reg_entry->cnt++;
		_publication_log_dump_(arg->msg_api, msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, env->selected_codec);
	}
	return ERR_IS_SUCCESS(errp);
}

static _client_total_pubctrl_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, ItsIso14827ClientEventPubControl* msg, Dz1Error* errp)
{
	// data ctrl event handler
	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecEntry* spec_entry = NULL;

	Iso14827TestSubEntry* reg_entry = NULL;
	Iso14827TestClientAccount* acc = env->primary_acc;

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0 ||
		Dz1Asn1UTF8Str_cmp(acc->my_domain, msg->myDomain) != 0 ||
		Dz1Asn1OctetStr_cmp(acc->userid, msg->user) != 0) ERR_SET_OUT(errp, EPERM); // identifier 값이 다르면 오류 -> 시험 종료
	else if ((reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->sid)) == NULL) ERR_SET_OUT(errp, EFAULT); // 요청한적 없는 Subscription ID->시험 종료
	else if ((spec_entry = SubscribeSpecList_findByOID(list, reg_entry->oid)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscription canceled while total subscription test...\n");
		list->extract(list, spec_entry);
		// notify to web
		// while total subscription test, subscription canceled!!
		pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);

		Iso14827TestSubList_removeByID(env->subs_reg, msg->peerDomain, msg->sid);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _client_total_cancel_all_subs(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	Iso14827TestSubList* reg_list = env->subs_reg;
	Iso14827TestSubEntry* reg_entry = NULL;

	SubscribeSpecList* spec_list = env->test_subs;
	SubscribeSpecEntry* spec_entry = NULL;

	Iso14827TestHelperEnv* envenv = (Iso14827TestHelperEnv*)env;

	while (errp->code == 0 && (spec_entry = spec_list->getHead(spec_list)) != NULL)
	{
		spec_list->extract(spec_list, spec_entry);
		pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
		while (errp->code == 0 && (reg_entry = Iso14827TestSubList_findByOID(reg_list, spec_entry->oid)) != NULL)
		{
			reg_list->extract(reg_list, reg_entry);
			pthread_cleanup_push(Iso14827TestSubEntry_delAndSetNull, (void*)&reg_entry);
			if (_client_unsubscribe(arg, env, s->peer_domain, acc, spec_entry, reg_entry->sid, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Iso14827TestSubEntry_delAndSetNull, (void*)&reg_entry);
		}
		pthread_cleanup_pop(1);// (SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
	}
	if (errp->code == 0)
	{
		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("모든 서브스크립션이 취소되었습니다."), NULL, NULL, errp);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ All Total Publications are canceled...\n");
	}
	// notify to web
	// all total publication canceled!!

	return ERR_IS_SUCCESS(errp);
}

static _client2_wait_total_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole2* s = (Iso14827TestClientRole2*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;
	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (s->subs_total_list == NULL || s->subs_total_list->count(s->subs_total_list) == 0) ERR_SET_OUT(errp, EFAULT);
		else if (_client_init_test_subs(env, s->subs_total_list, errp) == FALSE) ERR_OUT(errp);
		else if (_client_total_test(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else if (Iso14827TestHelperTimer_setGeneralTimer(timer, ISO14827_TEST_HELPER_TIMER_DUO_CLIENT, TIMER_sec_to_us(s->expireTime), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
		if (_client_total_pub_response(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data_ctrl:
		if (_client_total_pubctrl_response(arg, env, timer, s, (ItsIso14827ClientEventPubControl*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_timeout:
		if (_client_total_cancel_all_subs(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: // 다른 메시지 허용 안함
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_total_test() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->test_subs == NULL || env->test_subs->count(env->test_subs) == 0))
	{
		Iso14827TestSubList_delAndSetNull(&env->subs_reg);
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestClient2State_wait_terminate;
			Dz1Error_set(errp, 0);
		}
	}

	return ERR_IS_SUCCESS(errp);
}

// WAIT TOTAL TEST State
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// wait Terminate State
static bool_t _client_do_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Logout send...\n");


	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("시험 대상에게 로그아웃을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_disconnectFromServer(arg->t14827, acc->my_domain, s->peer_domain, acc->userid, Iso14827Logout_clientRequested)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
static bool_t _client_disconnected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc = env->primary_acc;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Disconnect...\n");
	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("시험 대상으로부터 로그아웃을 하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	env->flags &= ~CLIENT_FLAG_CONNECTED1;
	Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t _client2_wait_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestClientRole2* s = (Iso14827TestClientRole2*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_client_echo_responsed(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (_client_do_terminate(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_disconnected:
		if (_client_disconnected(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_client_wait_terminate() : EVENT %s(%d) not permitted\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED1) == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Total Test Complete...\n");
		env->flags |= CLIENT_FLAG_TOTAL_TEST;
		env->state = Iso14827TestClient2State_complete;
		Dz1Error_set(errp, 0);
		// notify to web
		// total test complete!!
	}
	return ERR_IS_SUCCESS(errp);
}
// wait Terminate State
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestClientAccount* _get_account1(Iso14827TestClientRole2* s)
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

static void _client2_timer_cleanup(Iso14827TestHelperEnv* env, void* timer)
{

	Iso14827TestScenario* scenario = env->scenario;
	Iso14827TestClientRole2* s = scenario->x.client2;

	Iso14827TestClientAccount* acc1 = _get_account1(s);
	if (acc1 != NULL) Iso14827TestHelperTimer_clrClientTimer(timer, acc1->my_domain, s->peer_domain, acc1->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
}

static Iso14827TestHelperScenarioF client2_scenario[] =
{
	_client2_initial,
	_client2_connected,
	_client2_wait_total_test,
	_client2_wait_terminate,
	NULL
};

static bool_t Iso14827TestClient2Scenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s,
	Iso14827TestClientEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= Iso14827TestClient2State_complete) ERR_SET_OUT(errp, EFAULT);
	else if (client2_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), errp);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestClient2State_complete)
		{
			Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);

			_client2_timer_cleanup(env, timer);
			*ret_is_complete = TRUE;
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}



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

static void _client1_timer_cleanup(Iso14827TestHelperEnv* env, void* timer)
{

	Iso14827TestScenario* scenario = env->scenario;
	Iso14827TestClientRole2* s = scenario->x.client2;

	Iso14827TestClientAccount* acc1 = _get_account1(s);
	if (acc1 != NULL) Iso14827TestHelperTimer_clrClientTimer(timer, acc1->my_domain, s->peer_domain, acc1->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
}

///////////////////////////////////////////////////////////////////////////////
// Check Scenario : Client2
bool_t Iso14827TestClient2Scenario_check(Iso14827TestClientRole2* s, Dz1Error* err)//ConformanceMsgStructAPI* msg_tbl, Dz1Error* err)
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
	else if ((list = s->subs_total_list) != NULL && (*errp = list->travel(list, _check_subs_type, (void*)DZ1_VAL2PTR32(SubscribeSpecTypePresent_registered))).code)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ Total subscription spec is invalid\n");
		ERR_OUT(errp);
	}
	else if (s->subs_total_list != NULL && s->subs_total_list->count(s->subs_total_list) > 0 && s->expireTime < 10)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ expire time is missing\n");
		ERR_OUT(errp);
	}
	else if (s->subs_cancel_reason == Iso14827SubscriptionCancel_max)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_cancel_reason is not initialized\n");
		ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Check Scenario : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Install Scenario : Client2
bool_t Iso14827TestClient2Scenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* errp)
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

		if (errp->code == 0) env->state = Iso14827TestClient2State_initial;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// Install Scenario : Client2
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Start Scenario : Client2
bool_t Iso14827TestClient2Scenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return Iso14827TestClient2Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_start, NULL, ret_is_complete, err);
}
// Start Scenario : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Trigger Scenario : Client2
bool_t Iso14827TestClient2Scenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient2Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_trigger, NULL, ret_is_complete, err);
}
// Trigger Scenario : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message : Client2
bool_t Iso14827TestClient2Scenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient2Scenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Message : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timeout : Client2
bool_t Iso14827TestClient2Scenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestClient2Scenario_event(arg, env, timer, s, Iso14827TestClientEvent_timeout, (void*)&timer_id, ret_is_complete, err);
}
// Timeout : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop : Client2
bool_t Iso14827TestClient2Scenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole2* s, Dz1Error* err)
{	// stop testing progress
	DZ1_ERROR_SAFE_PTR(errp, err);
	_client1_timer_cleanup(env, timer);

	return errp->code == 0 ? TRUE : FALSE;
}
// Stop : Client2
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Reset : Client2
void   Iso14827TestClient2Scenario_reset(Iso14827TestClientRole2* s, Iso14827TestHelperEnv* env)	// back to prepared status
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
	env->state = Iso14827TestClient2State_initial;
}
// Reset : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Release : Client2
void   Iso14827TestClient2Scenario_release(Iso14827TestClientRole2* s, Iso14827TestHelperEnv* env)	// release resource
{
	// called when terminate state
	Iso14827TestClient2Scenario_reset(s, env);
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
// Release : Client2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Status : Client2
void Iso14827TestClientRole2_status(Iso14827TestClientRole2* s, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (s != NULL)
	{
		Iso14827TestClientAccount* acc = _get_account1(s);

		TCHAR status[1024] = { 0, }, * dp = status;
		if (env->flags & CLIENT_FLAG_CREATED1) { Dz1STRCPY(dp, Dz1T("cre ")); dp += 5; };
		if (env->flags & CLIENT_FLAG_PORT_OPENED) { Dz1STRCPY(dp, Dz1T("port ")); dp += 5; };
		if (env->flags & CLIENT_FLAG_CONNECTED1) { Dz1STRCPY(dp, Dz1T("conn ")); dp += 5; };

		if (env->flags & CLIENT_FLAG_A_HEARTBEAT) { Dz1STRCPY(dp, Dz1T("hb")); dp += 3; };

		*dp = 0;
		Dz1Thread_printf(Dz1T("TEST_FLAG = [ %s]\n"), status);
	}
}
// Status : Client2
///////////////////////////////////////////////////////////////////////////////