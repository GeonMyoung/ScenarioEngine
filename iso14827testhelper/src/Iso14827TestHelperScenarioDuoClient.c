#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
// #include <ConformanceMsgUtil.h>

#include "Iso14827TestHelperEnv.h"
#include "Iso14827TestHelperTimerUtil.h"
#include "Iso14827TestHelperScenario.h"
#include "Iso14827TestHelperScenarioUtil.h"
#include "Iso14827TestHelperMsgSet.h"
#include "Iso14827TestHelperMsg.h"
#include <TechnicalRegulation2MsgStructAPI.h>

#define CLIENT_FLAG_CREATED1				0x80000000
#define CLIENT_FLAG_CREATED2				0x40000000
#define CLIENT_FLAG_PORT_OPENED				0x20000000
#define CLIENT_FLAG_CONNECTED1				0x10000000
#define CLIENT_FLAG_CONNECTED2				0x08000000

#define CLIENT_FLAG_A_HEARTBEAT				0x01000000
#define CLIENT_FLAG_B_HEARTBEAT				0x00800000
#define CLIENT_FLAG_DEFFERED_PUB_ACK		0x00200000
#define CLIENT_FLAG_SUBSCRIPTION_RCVD		0x00080000
#define CLIENT_FLAG_SUBS_NORMAL_COMPLETE	0x00040000
#define CLIENT_FLAG_TOTAL_TEST				0x00020000

static Dz1Str test_name_test_duo_client = Dz1T("test_duo_client");

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

///////////////////////////////////////////////////////////////////////////////
// heartbeat response received
static bool_t _duo_client_echo_response(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, ItsIso14827EventDisconnected* msg, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc1 = env->primary_acc, * acc2 = env->secondary_acc;
	if (Dz1Asn1UTF8Str_cmp(msg->myDomain, acc1->my_domain) == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat A...\n");
		env->flags |= CLIENT_FLAG_A_HEARTBEAT;
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("CLIENT 1 : 시험 대상으로부터 HeartBeat응답을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		// notify to web
		// client1 Heartbeat
	}
	else if (Dz1Asn1UTF8Str_cmp(msg->myDomain, acc2->my_domain) == 0)
	{
		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("Client 2 : 시험 대상으로부터 HeartBeat응답을 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Heartbeat B...\n");
		env->flags |= CLIENT_FLAG_B_HEARTBEAT;
		// notify to web
		// client2 Heartbeat
	}
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// heartbeat response received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INITIAL State
static bool_t _duo_client1_connect_and_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Iso14827TestClientActive* c, Dz1Error* errp)
{
	Dz1SockAddr peer;
	ConfTestSocketAddress* dst = c->peer;

	if ((*errp = Dz1SockAddr_setAddrByName(&peer, dst->addr)).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&peer, dst->port)).code) ERR_OUT(errp);
	else
	{
		// client1 login
		Iso14827TestClientAccount* acc1 = c->account1;
		Iso14827RejectLogin result = Iso14827RejectLogin_max;
		Dz1Asn1Codec codec = arg->initial_codec;


		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client1 Login...\n");

		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("CLIENT 1 : 시험 대상에게 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);


		if ((*errp = _ItsIso14827_connectToServer(arg->t14827, &peer, acc1->my_domain, s->peer_domain, acc1->authinfo, acc1->userid, acc1->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code) ERR_OUT(errp);
		else
		{
			env->selected_codec = codec;
			env->flags |= CLIENT_FLAG_CONNECTED1;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client1 Login Success...\n");

			if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT 1 : 로그인을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

			// notify to web
			// client1 login success;

			if ((env->server_addr = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



static bool_t _duo_client_initial_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	Iso14827TestClientConnection* c = s->connection;
	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		break;
	case Iso14827TestClientConnectionPresent_active:
		if (_duo_client1_connect_and_login(arg, env, timer, s, c->x.active, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}

	return ERR_IS_SUCCESS(errp);
}
static bool_t _duo_client_initial(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoClientRole* s = (Iso14827TestDuoClientRole*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_duo_client_echo_response(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_start:
		ItsIso14827SocketHook_set(_14827_hook_func, env);
		env->current_test = test_name_test_duo_client;
		if (Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (_duo_client_initial_start(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_client_initial() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED1) && (env->flags & CLIENT_FLAG_A_HEARTBEAT))
	{
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestDuoClientState_wait_duo_client1_established;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// INITIAL State
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait DUO CLIENT1 ESTABLISHED State
static bool_t _duo_client2_connect_and_login(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{

	// client2 login
	Iso14827TestClientAccount* acc2 = s->connection->x.active->account2;
	Iso14827RejectLogin result = Iso14827RejectLogin_max;
	Dz1Asn1Codec codec = arg->initial_codec;

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client2 Login...\n");

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("Client 2 : 시험 대상에게 로그인을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);



	if ((*errp = _ItsIso14827_connectToServer(arg->t14827, env->server_addr, acc2->my_domain, s->peer_domain, acc2->authinfo, acc2->userid, acc2->passwd, arg->codec_bits, arg->hb_dur_s, arg->rsp_time_s, 0, &codec, ItsIso14827CRCCheck_warning, NULL, NULL, &result)).code) ERR_OUT(errp);
	else
	{
		env->selected_codec_duo = codec;
		env->flags |= CLIENT_FLAG_CONNECTED2;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client2 Login Success...\n");


		if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("Client 2 : 로그인을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);

		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_wait_client1_established(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoClientRole* s = (Iso14827TestDuoClientRole*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_duo_client_echo_response(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (_duo_client2_connect_and_login(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_client1_established() : EVENT %s(%d) not permited", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED2) && (env->flags & CLIENT_FLAG_B_HEARTBEAT) && (env->flags & CLIENT_FLAG_A_HEARTBEAT))
	{
		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Duo subscription test is ready...\n");
			// notify to web
			// duo subscription test is ready
			env->state = Iso14827TestDuoClientState_wait_duo_subs_test;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait DUO CLIENT1 ESTABLISHED State
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
		if ((r = type->x.registered) == NULL || (r_info = r->reg_info) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = ItsIso14827_requestCancel(arg->t14827, ItsIso14827DomainType_client, acc->my_domain, peer_domain, acc->userid, sid, r->when_cancel)).code) ERR_OUT(errp);
		else
		{


			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication Canceled...\n");
			Dz1Error_set(errp, 0);
			// notify to web : publicatoin cancel!!!!!!;
		}
		break;
	default: break;
	}
	return ERR_IS_SUCCESS(errp);
}
// subscribe helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait DUO SUBS TEST State
static bool_t _duo_client_subscribe_and_register(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, Iso14827TestSubList* dst_reg, Dz1Asn1UTF8Str* peer_domain, Iso14827TestClientAccount* acc, SubscribeSpecEntry* node, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestSubEntry* entry = NULL;

	SubscribeSpecType* type = NULL;
	Iso14827TestSubType subs_type = Iso14827TestSubType_max;

	if ((type = node->type) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((type->present != SubscribeSpecTypePresent_registered) && (type->present != SubscribeSpecTypePresent_single)) ERR_SET_OUT(errp, EINVAL);
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

static bool_t _duo_client_duo_subscribe(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	if ((env->subs_reg = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg);

		if ((env->subs_reg2 = Iso14827TestSubList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			SubscribeSpecDuo* duo = s->subs_duo;
			Iso14827TestClientAccount* acc1 = env->primary_acc;
			Iso14827TestClientAccount* acc2 = env->secondary_acc;

			pthread_cleanup_push(Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg2);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Subscribe A and B...\n");
			// notify yo web
			// try Subscribe A and B

			if (0) {}
			else
			{
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT 1 : 서브스크립션을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (_duo_client_subscribe_and_register(arg, env, env->subs_reg, s->peer_domain, acc1, duo->session1, errp) == FALSE) ERR_OUT(errp);
				if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT 2 : 서브스크립션을 전송합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (_duo_client_subscribe_and_register(arg, env, env->subs_reg2, s->peer_domain, acc2, duo->session2, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg2);
		}
		pthread_cleanup_pop(errp->code); // (Iso14827TestSubList_delAndSetNull, (void*)&env->subs_reg);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_data_received(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, ItsIso14827ClientEventPublication* msg, Dz1Error* errp)
{
	SubscribeSpecList* list = env->test_subs;
	SubscribeSpecList* list2 = env->test_subs2;
	SubscribeSpecEntry* spec_entry = NULL;
	Iso14827TestSubEntry* reg_entry = NULL;

	Iso14827TestClientAccount* acc1 = env->primary_acc;
	Iso14827TestClientAccount* acc2 = env->secondary_acc;

	Dz1Binary bin = { msg->encodedEAM, msg->encodedEAMSize };

	if (Dz1Asn1UTF8Str_cmp(s->peer_domain, msg->peerDomain) != 0) ERR_SET_OUT(errp, EPERM); // identifier 값이 다르면 오류 -> 시험 종료
	else if (Dz1Asn1UTF8Str_cmp(acc1->my_domain, msg->myDomain) == 0 && Dz1Asn1OctetStr_cmp(acc1->userid, msg->user) == 0)
	{
		// 1번 세션 데이터
		if ((reg_entry = Iso14827TestSubList_findByID(env->subs_reg, msg->peerDomain, msg->sid)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((spec_entry = SubscribeSpecList_findByOID(list, reg_entry->oid)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			list->extract(list, spec_entry);
			pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication A...\n");
			// notify to web
			// Publication A
			Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("CLIENT 1 : 퍼블리케이션을 수신하였습니다."), NULL, NULL, errp);

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


			_publication_log_dump_(arg->msg_api, msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, env->selected_codec);

			if (_client_unsubscribe(arg, env, s->peer_domain, acc1, spec_entry, reg_entry->sid, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
		}
	}
	else if (Dz1Asn1UTF8Str_cmp(acc2->my_domain, msg->myDomain) == 0 && Dz1Asn1OctetStr_cmp(acc2->userid, msg->user) == 0)
	{
		// 2번 세션 데이터
		if ((reg_entry = Iso14827TestSubList_findByID(env->subs_reg2, msg->peerDomain, msg->sid)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((spec_entry = SubscribeSpecList_findByOID(list2, reg_entry->oid)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			list2->extract(list2, spec_entry);
			pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Publication B...\n");
			// notify to web
			// Publication B

			Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("Client 2 : 퍼블리케이션을 수신하였습니다."), NULL, NULL, errp);

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

			_publication_log_dump_(arg->msg_api, msg->oidStr, msg->encodedEAM, msg->encodedEAMSize, env->selected_codec);

			if (_client_unsubscribe(arg, env, s->peer_domain, acc2, spec_entry, reg_entry->sid, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&spec_entry);
		}
	}
	else ERR_SET_OUT(errp, EPERM); // identifier 값이 다르면 오류 -> 시험 종료

	return ERR_IS_SUCCESS(errp);
}
static bool_t _duo_client_wait_duo_subs_test(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoClientRole* s = (Iso14827TestDuoClientRole*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_duo_client_echo_response(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_trigger:
		if (_client_init_duo_subs1(env, s->subs_duo, errp) == FALSE) ERR_OUT(errp);
		else if (_client_init_duo_subs2(env, s->subs_duo, errp) == FALSE) ERR_OUT(errp);
		else if (_duo_client_duo_subscribe(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data:
		if (_duo_client_data_received(arg, env, timer, s, (ItsIso14827ClientEventPublication*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_data_ctrl:		// 정보 제공 거절 -> 오류 -> 시험 종료
		Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_SUT, Dz1T("시험 대상이 서브스크립션을 거절하였습니다."), NULL, NULL, errp);
		ERR_SET_OUT(errp, EPERM);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_client_wait_duo_subs_test() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->test_subs->count(env->test_subs) == 0) && (env->test_subs2->count(env->test_subs2) == 0))
	{
		Iso14827TestSubList_delAndSetNull((void*)&env->subs_reg);
		Iso14827TestSubList_delAndSetNull((void*)&env->subs_reg2);

		if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Iso14827TestDuoClientState_wait_duo_terminate;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
// wait DUO SUBS TEST State
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wait DUO TERMINATE State
static bool_t _duo_client_client2_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc2 = env->secondary_acc;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Logout B...\n");
	// notify to web
	// logout sent B

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("Client 2 : 시험 대상에게 로그아웃을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((*errp = ItsIso14827_disconnectFromServer(arg->t14827, acc2->my_domain, s->peer_domain, acc2->userid, Iso14827Logout_clientRequested)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_client2_disconnected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Disconnect B ...\n");
	env->flags &= ~CLIENT_FLAG_CONNECTED2;

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("Client 2 : 시험 대상으로부터 로그아웃을 하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	// notify to web
	// discoonected B!

	Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_wait_duo_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoClientRole* s = (Iso14827TestDuoClientRole*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_duo_client_echo_response(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED2) == 0 && (env->flags & CLIENT_FLAG_A_HEARTBEAT))
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Duo Client Test Complete...\n");
			// notify to web
			// duo client test is success;

			if (Iso14827TestScenario_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
			else
			{
				env->state = Iso14827TestDuoClientState_wait_terminate;
				Dz1Error_set(errp, 0);
			}
		}

		break;
	case Iso14827TestClientEvent_trigger:
		if (_duo_client_client2_terminate(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_disconnected:
		if (_duo_client_client2_disconnected(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_client_wait_duo_terminate() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	return ERR_IS_SUCCESS(errp);
}
// wait DUO TERMINATE State
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wait TERMINATE State
static bool_t _duo_client_client1_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	Iso14827TestClientAccount* acc1 = env->primary_acc;

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, ISO14827_TEST_HELPER_SENDER_AGENT, Dz1T("CLIENT 1 : 시험 대상에게 로그아웃을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Logout A...\n");
	// notify to web
	// logout sent A
	if ((*errp = ItsIso14827_disconnectFromServer(arg->t14827, acc1->my_domain, s->peer_domain, acc1->userid, Iso14827Logout_clientRequested)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_client1_disconnected(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* errp)
{
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Disconnect A ...\n");
	env->flags &= ~CLIENT_FLAG_CONNECTED1;

	// notify to web
	// discoonected A!

	if (Iso14827TestHelperEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("CLIENT 1 : 시험 대상으로부터 로그아웃을 하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _duo_client_wait_terminate(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, void* _scenario, int _ev, void* _msg, Dz1Error* errp)
{
	Iso14827TestDuoClientRole* s = (Iso14827TestDuoClientRole*)_scenario;
	Iso14827TestClientEvent ev = (Iso14827TestClientEvent)_ev;

	switch (ev)
	{
	case Iso14827TestClientEvent_echo:
		if (_duo_client_echo_response(arg, env, timer, s, (ItsIso14827EventDisconnected*)_msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;

	case Iso14827TestClientEvent_trigger:
		if (_duo_client_client1_terminate(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestClientEvent_disconnected:
		if (_duo_client_client1_disconnected(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		break;
	default:
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "_duo_client_wait_terminate() : EVENT %s(%d) not permited\n", Iso14827TestServerEventStrA(ev), ev);
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & CLIENT_FLAG_CONNECTED1) == 0)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Test complete...\n");
		env->state = Iso14827TestDuoClientState_complete;
		Dz1Error_set(errp, 0);
		// notify to web
		// test complete!!
	}
	return ERR_IS_SUCCESS(errp);
}
// wait TERMINATE State
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Check Scenario : Duo Client
bool_t Iso14827TestDuoClientScenario_check(Iso14827TestDuoClientRole* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if (s == NULL)
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
	else if (s->subs_duo != NULL && (s->subs_duo->session1 == NULL || s->subs_duo->session2 == NULL))
	{
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "$$$ subs_duo is missing\n");
		ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// Check Scenario : Duo Client
///////////////////////////////////////////////////////////////////////////////


static Iso14827TestClientAccount* _get_account1(Iso14827TestDuoClientRole* s)
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


static Iso14827TestClientAccount* _get_account2(Iso14827TestDuoClientRole* s)
{
	Iso14827TestClientAccount* ret = NULL;
	Iso14827TestClientConnection* c = s->connection;
	Iso14827TestClientPassive* p = NULL;
	Iso14827TestClientActive* a = NULL;
	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		p = c->x.passive;
		ret = p->account2;
		break;
	case Iso14827TestClientConnectionPresent_active:
		a = c->x.active;
		ret = a->account2;
		break;
	}
	return ret;
}

static void _duo_client_timer_cleanup(Iso14827TestHelperEnv* env, void* timer)
{

	Iso14827TestScenario* scenario = env->scenario;
	Iso14827TestDuoClientRole* s = scenario->x.duo_client;

	Iso14827TestClientAccount* acc1 = _get_account1(s);
	Iso14827TestClientAccount* acc2 = _get_account2(s);
	if (acc1 != NULL) Iso14827TestHelperTimer_clrClientTimer(timer, acc1->my_domain, s->peer_domain, acc1->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
	if (acc2 != NULL) Iso14827TestHelperTimer_clrClientTimer(timer, acc2->my_domain, s->peer_domain, acc2->userid, CLIENT_TIMER_ID_DISCONNECT_WAIT);
}

///////////////////////////////////////////////////////////////////////////////
// Install Scenario : Duo Client
bool_t Iso14827TestDuoClientScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestClientConnection* c = s->connection;
	Iso14827TestClientPassive* p = NULL;
	Iso14827TestClientActive* a = NULL;
	Iso14827TestClientAccount* acc1 = NULL, * acc2 = NULL;

	switch (c->present)
	{
	case Iso14827TestClientConnectionPresent_passive:
		p = c->x.passive;
		env->primary_acc = acc1 = p->account1;
		env->secondary_acc = acc2 = p->account2;
		break;
	case Iso14827TestClientConnectionPresent_active:
		a = c->x.active;
		env->primary_acc = acc1 = a->account1;
		env->secondary_acc = acc2 = a->account2;
		break;
	}

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if (acc1 == NULL || (*errp = ItsIso14827_createClient4Task(my_queue_id, arg->t14827, acc1->my_domain)).code) ERR_OUT(errp);
	else if (acc2 == NULL || (*errp = ItsIso14827_createClient4Task(my_queue_id, arg->t14827, acc2->my_domain)).code) ERR_OUT(errp);
	else
	{
		env->flags |= CLIENT_FLAG_CREATED1;
		env->flags |= CLIENT_FLAG_CREATED2;

		if (errp->code == 0) env->state = Iso14827TestDuoClientState_initial;
	}
	return ERR_IS_SUCCESS(errp);
}
// Install Scenario : Duo Client
///////////////////////////////////////////////////////////////////////////////

static Iso14827TestHelperScenarioF duo_client_scenario[] =
{
	_duo_client_initial,
	_duo_client_wait_client1_established,
	_duo_client_wait_duo_subs_test,
	_duo_client_wait_duo_terminate,
	_duo_client_wait_terminate,
	NULL
};

static bool_t Iso14827TestDuoClientScenario_event(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Iso14827TestClientEvent ev, void* _msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= Iso14827TestDuoClientState_complete) ERR_SET_OUT(errp, EFAULT);
	else if (duo_client_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == Iso14827TestDuoClientState_complete)
		{

			_duo_client_timer_cleanup(env, timer);
			*ret_is_complete = TRUE;
			Iso14827TestHelperEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), errp);
			Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp);
			if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Start Scenario : Duo Client
bool_t					Iso14827TestDuoClientScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return Iso14827TestDuoClientScenario_event(arg, env, timer, s, Iso14827TestClientEvent_start, NULL, ret_is_complete, errp);
}
// Start Scenario : Duo Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Trigger Scenario : Duo Client
bool_t					Iso14827TestDuoClientScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, bool_t* ret_is_complete, Dz1Error* err)
{

	return Iso14827TestDuoClientScenario_event(arg, env, timer, s, Iso14827TestClientEvent_trigger, NULL, ret_is_complete, err);
}
// Trigger Scenario : Duo Client
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Messgage : Duo Client
bool_t					Iso14827TestDuoClientScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Iso14827TestClientEvent ev, void* t14827msg, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestDuoClientScenario_event(arg, env, timer, s, ev, t14827msg, ret_is_complete, err);
}
// ISO-14827 Messgage : Duo Client
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// TIMEOUT : Duo Client
bool_t					Iso14827TestDuoClientScenario_timeout(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, u32_t timer_id, bool_t* ret_is_complete, Dz1Error* err)
{
	return Iso14827TestDuoClientScenario_event(arg, env, timer, s, Iso14827TestClientEvent_timeout, (void*)&timer_id, ret_is_complete, err);
}
// TIMEOUT : Duo Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STOP : Duo Client
bool_t					Iso14827TestDuoClientScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestDuoClientRole* s, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_duo_client_timer_cleanup(env, timer);
	return ERR_IS_SUCCESS(errp);
}
// STOP : Duo Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Release : Duo Client
void Iso14827TestDuoClientScenario_reset(Iso14827TestDuoClientRole* s, Iso14827TestHelperEnv* env)
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
		default:
			break;
		}
	}

	if (env->flags & CLIENT_FLAG_CONNECTED1)
	{
		if ((acc = _get_account1(s)) != NULL)
			ItsIso14827_disconnectFromServer(env->t14827, acc->my_domain, s->peer_domain, acc->userid, Iso14827Logout_clientRequested);
	}

	if (env->flags & CLIENT_FLAG_CONNECTED2)
	{
		if ((acc = _get_account2(s)) != NULL)
			ItsIso14827_disconnectFromServer(env->t14827, acc->my_domain, s->peer_domain, acc->userid, Iso14827Logout_clientRequested);
	}

	env->selected_codec = Dz1Asn1Codec_max;
	Dz1SockAddr_delAndSetNull(&env->server_addr);
	SubscribeSpecList_delAndSetNull(&env->test_subs);
	SubscribeSpecList_delAndSetNull(&env->test_subs2);
	env->test_subs_id = 0;
	Iso14827TestSubList_delAndSetNull(&env->subs_reg);

	env->flags &= (CLIENT_FLAG_CREATED1 | CLIENT_FLAG_CREATED2);
	env->state = Iso14827TestDuoClientState_initial;
}

void Iso14827TestDuoClientScenario_release(Iso14827TestDuoClientRole* s, Iso14827TestHelperEnv* env)
{
	// called when terminate state
	Iso14827TestDuoClientScenario_reset(s, env);
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

	if (env->flags & CLIENT_FLAG_CREATED2)
	{
		if ((acc = _get_account2(s)) != NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "$$$ Client B Delete\n");
			ItsIso14827_deleteClient(env->t14827, acc->my_domain);
			env->flags &= ~CLIENT_FLAG_CREATED2;
		}
	}
	env->primary_acc = env->secondary_acc = NULL;
}
// Release : Duo Client
///////////////////////////////////////////////////////////////////////////////

void Iso14827TestDuoClientRole_status(Iso14827TestDuoClientRole* p, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	// tbd
}
