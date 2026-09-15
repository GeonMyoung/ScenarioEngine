#include "ITSK00144_2TestScenarioProc.h"
#include <ITSK00144_2TestMsg.h>
#include <Dz1SockUtil.h>
#include <dz1_asn1.h>
#include <ITSK00144_2TestScenarioDefJson.h>
#include <ITSK00144_2TestMsgSample.h>

I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;


#define ITSK_00144_2_SERVER_ROLE_FLAG_CREATED						0x80000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_CONNECTED						0x40000000

#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LINK_UNIT_STATUS		0x20000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_STATUS				0x10000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LIST					0x08000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_UPDATE_LIST			0x04000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_RESET				0x02000000
#define ITSK_00144_2_SERVER_ROLE_FLAG_TEST_SESSION_MAITAIN			0x01000000

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

static bool_t _proc_hb(ITSK001442TestScenarioArg *arg, ITSK001442TestScenarioEnv* env, void *timer, ITSK00144_2ScenarioServerRole* s, void* msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;

		if (ctx->opcode == ITSK00144_2DataPresent_hb)
		{
			if (s->test_session_maintain && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_SESSION_MAITAIN) == 0)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_session_maintain"), Dz1T("SUCCESS"), errp) == FALSE)ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_SESSION_MAITAIN;
					Dz1Error_set(errp, 0);
				}
			}

			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00144_2_SENDER_SUT, Dz1T("하트비트를 수신하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_ack, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Binary* src = NULL;
				pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
				if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);

					if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			}
		}
		else
		{
			if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_nack, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Binary* src = NULL;
				pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
				if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
					if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			}
			ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static ITSK00144_2ServerSession* _gen_server_session(ITSK001442TestScenarioEnv* env, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	ITSK00144_2ServerSession* ret = NULL;

	if ((ret = ITSK00144_2ServerSession_new(-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK00144_2ServerSession_delAndSetNull, (void*)&ret);
		Dz1SockAddr local;
		u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
		if (0) {}
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, (u16_t)s->local_port)).code) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->acceptor = Dz1SockUtilAcceptorForTask_start(0, ret->local, my_queue_id, errp)) == (u32_t)-1) ERR_OUT(errp);
		else
		{
			char log[128];
			sprintf(log, "포트(%d)를 열었습니다. 클라이언트의 접속 수신을 대기합니다.", (int)s->local_port);

			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			u16_t port;
			Dz1SockAddr_getPort(ret->local, &port);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ SERVER : Port Opened(%d)...\n"), port);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (ITSK00144_2ServerSession_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static bool_t _initial(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_start:
		if (env->session != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((env->session = ITSK00144_2Session_new(ITSK00144_2SessionPresent_server, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((env->session->x.server = _gen_server_session(env, s, errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_CREATED;
			Dz1Error_set(errp, 0);
		}
		break;
	case ITSK00144_2ScenarioEvent_auth:
		if (s->test_session_maintain)
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_session_maintain"), Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_CONNECTED;
		Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_CREATED) && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_CONNECTED))
	{
		// trigger, state 변경
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = ITSK00144_2ScenarioServerState_wait_test_rsp_link_status;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _test_rsp_link_unit_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	env->current_test = Dz1T("test_rsp_link_unit_status");
	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	ITSK00144_2ProtocolFrame* f = NULL;
	Dz1Binary* src = NULL;
	if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_req_link_unit_status, Dz1IOStreamEndian_big, NULL, errp)) == NULL) {
		env->send_seq--;
		ERR_OUT(errp);
	}
	else
	{
		Dz1Binary* src = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
			if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1);  // (Dz1Binary_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_rsp_link_unit_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* _s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ITSK00144_2ProtocolFrameContext_dump(ctx, 4);
		if (ctx->opcode == ITSK00144_2DataPresent_rsp_link_unit_status)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LINK_UNIT_STATUS;

			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
		else
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



static bool_t _wait_test_rsp_link_unit_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
		if (_proc_hb(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_trigger:
		if (s->test_rsp_link_unit_status == FALSE)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LINK_UNIT_STATUS;
			Dz1Error_set(errp, 0);
		}
		else if (_test_rsp_link_unit_status(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data:
		if (_validate_rsp_link_unit_status(arg, env, timer,s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LINK_UNIT_STATUS))
	{
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00144_2_DEFAULT_SCENARIO;
			env->state = ITSK00144_2ScenarioServerState_wait_test_rsp_status;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _test_rsp_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	env->current_test = Dz1T("test_rsp_status");
	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	ITSK00144_2ProtocolFrame* f = NULL;
	Dz1Binary* src = NULL;
	if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_req_status, Dz1IOStreamEndian_big, NULL, errp)) == NULL) {
		env->send_seq--;
		ERR_OUT(errp);
	}
	else
	{
		Dz1Binary* src = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
			if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1);  // (Dz1Binary_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_rsp_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* _s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ITSK00144_2ProtocolFrameContext_dump(ctx, 4);
		if (ctx->opcode == ITSK00144_2DataPresent_rsp_status)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_STATUS;

			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
		else
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_rsp_status(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
		if (_proc_hb(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_trigger:
		if (s->test_rsp_status == FALSE)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_STATUS;
			Dz1Error_set(errp, 0);
		}
		else if (_test_rsp_status(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data:
		if (_validate_rsp_status(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_STATUS))
	{
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00144_2_DEFAULT_SCENARIO;
			env->state = ITSK00144_2ScenarioServerState_wait_test_rsp_list;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _test_rsp_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	env->current_test = Dz1T("test_rsp_list");
	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	ITSK00144_2ProtocolFrame* f = NULL;
	Dz1Binary* src = NULL;
	if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_req_list, Dz1IOStreamEndian_big, NULL, errp)) == NULL) {
		env->send_seq--;
		ERR_OUT(errp);
	}
	else
	{
		Dz1Binary* src = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
			if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1);  // (Dz1Binary_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_rsp_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* _s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ITSK00144_2ProtocolFrameContext_dump(ctx, 4);
		if (ctx->opcode == ITSK00144_2DataPresent_rsp_list)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LIST;

			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
		else
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_rsp_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
		if (_proc_hb(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_trigger:
		if (s->test_rsp_list == FALSE)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LIST;
			Dz1Error_set(errp, 0);
		}
		else if (_test_rsp_list(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data:
		if (_validate_rsp_list(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_LIST))
	{
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00144_2_DEFAULT_SCENARIO;
			env->state = ITSK00144_2ScenarioServerState_wait_test_rsp_update_list;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



static bool_t _test_rsp_update_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	env->current_test = Dz1T("test_rsp_update_list");
	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);


	ITSK00144_2Data* data = NULL;
	if ((data = ITSK00144_2Data_new(ITSK00144_2DataPresent_req_update_list, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void*)&data);
		if ((data->x.req_update_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2ProtocolFrame* f = NULL;
			Dz1Binary* src = NULL;
			if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(s->id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL)
			{
				env->send_seq--;
				ERR_SET_OUT(errp, EFAULT);
			}
			else
			{
				Dz1Binary* src = NULL;
				pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
				if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
					if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1);  // (Dz1Binary_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			}

		}
		pthread_cleanup_pop(1); // (ITSK00144_2Data_delAndSetNull, (void*)&data);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_rsp_update_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* _s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ITSK00144_2ProtocolFrameContext_dump(ctx, 4);
		if (ctx->opcode == ITSK00144_2DataPresent_rsp_update_list)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_UPDATE_LIST;

			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
		else
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_rsp_update_list(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
		if (_proc_hb(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_trigger:
		if (s->test_rsp_update_list == FALSE)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_UPDATE_LIST;
			Dz1Error_set(errp, 0);
		}
		else if (_test_rsp_update_list(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data:
		if (_validate_rsp_update_list(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_UPDATE_LIST))
	{
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00144_2_DEFAULT_SCENARIO;
			env->state = ITSK00144_2ScenarioServerState_wait_test_rsp_reset;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _test_rsp_reset(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, Dz1Error* errp)
{
	env->current_test = Dz1T("test_rsp_reset");
	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	ITSK00144_2ProtocolFrame* f = NULL;
	Dz1Binary* src = NULL;
	if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_reset, Dz1IOStreamEndian_big, NULL, errp)) == NULL) {
		env->send_seq--;
		ERR_OUT(errp);
	}
	else
	{
		Dz1Binary* src = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
			if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1);  // (Dz1Binary_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_rsp_reset(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* _s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;

	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ITSK00144_2ProtocolFrameContext_dump(ctx, 4);
		if (ctx->opcode == ITSK00144_2DataPresent_ack)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_RESET;

			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

		}
		else
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("FAIL"), errp) == FALSE) ERR_OUT(errp);
			else ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_rsp_reset(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioServerRole* s = (ITSK00144_2ScenarioServerRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
		if (_proc_hb(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_trigger:
		if (s->test_rsp_reset == FALSE)
		{
			env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_RESET;
			Dz1Error_set(errp, 0);
		}
		else if (_test_rsp_reset(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data:
		if (_validate_rsp_reset(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_RSP_RESET) && (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_TEST_SESSION_MAITAIN))
	{
		if (ITSK00144_2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00144_2_DEFAULT_SCENARIO;
			env->state = ITSK00144_2ScenarioServerState_complete;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static ITSK00144_2TestScenarioF _server_scenario[] = {
	_initial,
	_wait_test_rsp_link_unit_status,
	_wait_test_rsp_status,
	_wait_test_rsp_list,
	_wait_test_rsp_update_list,
	_wait_test_rsp_reset,
	NULL
};

static bool_t ITSK00144_2TestScenarioProcServerRole_event(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, ITSK00144_2ScenarioEvent ev, void* _msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env->state >= ITSK00144_2ScenarioServerState_complete) ERR_SET_OUT(errp, EPERM);
	else if (_server_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
		ITSK00144_2TestScenarioProc_release(arg, env, timer, NULL);
		ERR_OUT(errp);
	}
	else
	{
		if (env->state == ITSK00144_2ScenarioServerState_complete)
		{
			*ret_is_copmplete = TRUE;
			ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("SUCCESS"), NULL);
			ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
			ITSK00144_2TestScenarioProc_release(arg, env, timer, NULL);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioProcServerRole_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->flags & ITSK_00144_2_SERVER_ROLE_FLAG_CREATED) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->state = ITSK00144_2ScenarioServerState_initial;
		env->received_seq = 0;
		env->send_seq = 0;

		if (s->test_session_maintain == FALSE) env->flags |= ITSK_00144_2_SERVER_ROLE_FLAG_TEST_SESSION_MAITAIN;

		if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else if (ITSK00144_2TestMsg_initSample(errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ITSK00144_2TestScenarioProcServerRole_event(arg, env, timer, s, ITSK00144_2ScenarioEvent_start, NULL, ret_is_copmplete, err);
}

bool_t ITSK00144_2TestScenarioProcServerRole_trigger(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err)
{
	return ITSK00144_2TestScenarioProcServerRole_event(arg, env, timer, s, ITSK00144_2ScenarioEvent_trigger, NULL, ret_is_copmplete, err);
}

bool_t ITSK00144_2TestScenarioProcServerRole_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioServerRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	return ITSK00144_2TestScenarioProcServerRole_event(arg, env, timer, s, ev, msg, ret_is_copmplete, err);
}


// SOCK MESSAGE
// DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED
static Dz1TaskProcStatus _server_connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	Dz1SockUtilAcceptorConnected* msg = Dz1TaskSigMsg_getData(*sg);
	//ITSK001442ScenarioConfig* scenario = NULL;
	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;
	ITSK00144_2Scenario* s = NULL;

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if ((server->peer = Dz1SockAddr_clone(msg->peer, errp)) == NULL) ERR_OUT(errp);
	else if ((server->sock = msg->sock) == NULL) ERR_OUT(errp);
	else if ((server->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((server->rx_stream = Dz1Stream_openRefElasticBuf(server->rx_buf, errp)) == NULL) ERR_OUT(errp);
	else if ((server->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1SockUtilTcpClient_modeCallback(server->sock, server->peer, server->local, 1024, my_queue_id)).code) ERR_OUT(errp);
	else
	{
		char str_addr[64] = { 0, };
		Dz1SockAddrA_printable(msg->peer, str_addr, FALSE, NULL);

		if (0) {}
		else
		{
			char log[128] = "클라이언트가 접속하였습니다. 클라이언트 주소 : ";
			strcat(log, str_addr);
			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		msg->sock = NULL;
		msg->local = msg->peer = NULL;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Session established ] = \n"));
		ITSK00144_2ServerSession_dump(server, 0);

		bool_t is_complete = FALSE;
		ITSK00144_2TestScenarioProcServerRole_sockProc(arg, env, timer, s->x.serverRole, ITSK00144_2ScenarioEvent_auth, NULL, &is_complete, errp);

		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION
static Dz1TaskProcStatus _server_connect_exception(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	if (env->session != NULL) ITSK00144_2Session_delAndSetNull((void*)&env->session);

	Dz1Thread_printf("!!! Server accept error!\n");

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _server_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;
	ITSK00144_2Scenario* s = NULL;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("Received msg from SUT = \n"));
	Dz1SockUtilReceiverReceived_dump(msg, 0);
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("\n"));

	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(server->peer, msg->peer) != 0 || Dz1SockAddr_cmp(server->local, msg->local) != 0) ERR_OUT(errp);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(server->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp); // 소켓 버퍼에서 로컬 변수로 데이터 옮김
		else
		{
			Dz1Stream_drain(server->rx_stream, (size_t)stream->size, NULL, errp);

			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00144_2_SENDER_SUT, Dz1T("시험 대상으로부터 메시지를 수신하였습니다."), stream, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			ITSK00144_2TestScenarioProc_sockProc(arg, env, timer, stream, errp);

			stream = NULL;
			Dz1Error_set(errp, 0);
		}
	}

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
static Dz1TaskProcStatus _server_client_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Server Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);
	ITSK00144_2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else
	{
		// ITSK00144_2TestScenarioProc_sockProc(arg, env, timer, s, ITSK001442ScenarioEvent_disconnected, NULL, errp);
		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_TRANSMITER_SENT
static Dz1TaskProcStatus _server_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	ITSK00144_2Session* session = NULL;
	ITSK00144_2ServerSession* server = NULL;

	ITSK00144_2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, server->peer) != 0 || Dz1SockAddr_cmp(msg->local, server->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(server->tx_fifo, server->sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

bool_t ITSK00144_2TestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
void   ITSK00144_2TestScenarioProcServerRole_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent);
}