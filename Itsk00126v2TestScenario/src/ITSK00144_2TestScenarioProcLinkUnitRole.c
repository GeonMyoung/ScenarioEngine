#include "ITSK00144_2TestScenarioProc.h"
#include <ITSK00144_2TestMsg.h>
#include <Dz1SockUtil.h>
#include <dz1_asn1.h>
#include <ITSK00144_2TestScenarioDefJson.h>
#include <ITSK00144_2TestMsgSample.h>
#include <GitsnAsnUtil.h>

#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CREATED						0x80000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CONNECTED						0x40000000

#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LINK_UNIT_STATUS		0x20000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_STATUS				0x10000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LIST					0x08000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_UPDATE_LIST			0x04000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_RESET					0x02000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_TIM						0x01000000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_MAP						0x00800000
#define ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_SESSION_MAINTAIN			0x00400000

I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;

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

static bool_t _keepalive_timer_set(ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* errp);


static Dz1TaskProcStatus _send_hb(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	ITSK00144_2ScenarioLinkUnitRole* s = NULL;

	ITSK00144_2ClientSession* session = NULL;
	if ((session = env->session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((s = env->scenario->x.linkUnitRole) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;

		if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, ITSK00144_2DataPresent_hb, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary* src = NULL;
			pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
				if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
				else if (_keepalive_timer_set(env, timer, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Dz1Thread_printf("$$$ Heartbeat send!\n");
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);

		}
	}
	return ret;
}


static bool_t _keepalive_timer_set(ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* errp)
{
	ITSK00144_2ScenarioLinkUnitRole* s = NULL;
	if ((s = env->scenario->x.linkUnitRole) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ITSK001442TestScenarioTimer* tmr = ITSK001442TestScenarioTimer_new(ITSK_00144_2_TEST_SCENARIO_KEEPALIVE_TIMER, errp);
		if (tmr == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK001442TestScenarioTimer_delAndSetNull, (void*)&tmr);
			if ((*errp = ITSK001442TestScenarioTimer_set(timer, &tmr, (s->hb_duration-1) * 1000000, _send_hb)).code)
			{
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (ITSK001442TestScenarioTimer_delAndSetNull, (void*)&tmr);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _connect_to_server(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, Dz1Error* errp)
{
	// create client session;

	ITSK00144_2ClientSession* session = NULL;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	if (env->session != NULL || (env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CONNECTED) != 0) ERR_SET_OUT(errp, EEXIST);
	else if ((env->session = ITSK00144_2Session_new(ITSK00144_2SessionPresent_client, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((session = env->session->x.client = ITSK00144_2ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char str_addr[64] = { 0, };
		struct timeval to = { 3 ,0 };
		char log[128]; ;
		sprintf(log, "서버에 접속을 시도합니다. 서버 호스트 주소 : %s:%u", s->peer_ip, s->peer_port);
		strcat(log, str_addr);
		if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, ITSK_00144_2_SENDER_AGENT, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		Dz1SockAddr peer, local;
		if (0) {}
		else if ((*errp = Dz1SockAddr_setAddrStr(&peer, s->peer_ip)).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&peer, s->peer_port)).code) ERR_OUT(errp);
		else if ((session->peer = Dz1SockAddr_clone(&peer, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((session->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((session->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((session->rx_stream = Dz1Stream_openRefElasticBuf(session->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((session->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((session->sock = Dz1TcpClientSocket_open(session->peer, session->local, &to, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_modeCallback(session->sock, session->peer, session->local, 1024, my_queue_id)).code) ERR_OUT(errp);
		else
		{
			env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CONNECTED;

			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("서버에 접속을 성공하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "서버 접속 완료");
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _initial(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioLinkUnitRole* s = (ITSK00144_2ScenarioLinkUnitRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;

	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_start:
		if (_connect_to_server(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 || (env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CONNECTED))
	{
		if (_keepalive_timer_set(env, timer, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = ITSK00144_2ScenarioClientState_wait_req;
			if (s->test_req_link_unit_status)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_link_unit_status"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LINK_UNIT_STATUS;

			if (s->test_req_status)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_status"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_STATUS;

			if (s->test_req_list)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_list"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LIST;
			if (s->test_req_update_list)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_update_list"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_UPDATE_LIST;
			if (s->test_req_reset)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_reset"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_RESET;
			if (s->test_tim)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_tim"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_TIM;
			if (s->test_map)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_map"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_MAP;
			if (s->test_session_maintain)
				ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_session_maintain"), Dz1T("START"), errp);
			else env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_SESSION_MAINTAIN;

			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



static bool_t _send_data(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2DataPresent opcode, Dz1Error* errp)
{
	ITSK00144_2ScenarioLinkUnitRole* s = NULL;
	ITSK00144_2ClientSession* session = NULL;
	if ((session = env->session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((s = env->scenario->x.linkUnitRole) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;
		ITSK00144_2Data* data = NULL;
		if ((data = ITSK00144_2Data_new(opcode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void*)&data);
			switch (opcode)
			{
			case ITSK00144_2DataPresent_rsp_link_unit_status:
				if ((data->x.rsp_link_unit_status = I2XTrafficSafetyDeviceLinkUnitStatus_clone(sample_i2x_traffic_safety_device_link_unit_status, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(s->id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_status:
				if ((data->x.rsp_status = I2XTrafficSafetyDeviceStatusInfo_clone(sample_i2x_traffic_safety_device_status_info, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(s->id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_list:
				if ((data->x.rsp_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(s->id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_rsp_update_list:
				if ((data->x.rsp_update_list = I2XTrafficSafetyDeviceList_clone(sample_i2x_traffic_safety_device_list, errp)) == NULL) ERR_OUT(errp);
				else if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(s->id, env->send_seq++, data, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case ITSK00144_2DataPresent_ack:
				if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(s->id, env->send_seq++, opcode, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EPERM);
				break;
			}
			if (f == NULL || errp->code != 0) ERR_OUT(errp);
			else
			{
				Dz1Binary* src = NULL;
				pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
				if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);

					Dz1Thread_printf("Send Message = \n");
					Dz1Binary_dump(src, 4);

					if (ITSK00144_2TestScenarioProc_sendToPeer(arg, env, timer, src, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					

					/*if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);*/

					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
			}
			pthread_cleanup_pop(1); // (ITSK00144_2Data_delAndSetNull, (void*)&data);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _check_received_seq(ITSK001442TestScenarioEnv* env, u8_t received_seq, Dz1Error* errp)
{
	// 0 ~ 255 까지

	if (env->received_seq == 0 || env->received_seq == received_seq)
	{
		Dz1Error_set(errp, 0);
	}
	else if (env->received_seq + 1 == received_seq)
	{
		env->received_seq = received_seq;
		if (env->received_seq = 255) env->received_seq = 0;
		Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1Thread_printf("!!! unexpected seq = %u\n", received_seq);
		ERR_SET_OUT(errp, EFAULT);
	}

	return ERR_IS_SUCCESS(errp);
}


static bool_t proc_req(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ProtocolFrameContext* ctx = (ITSK00144_2ProtocolFrameContext*)_msg;
	
	if (ctx == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (_check_received_seq(env, ctx->seq, errp) == FALSE) ERR_OUT(errp);
	else
	{
		switch (ctx->opcode)
		{
		case ITSK00144_2DataPresent_req_link_unit_status:
			if (s->test_req_link_unit_status)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_link_unit_status"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LINK_UNIT_STATUS;
					Dz1Error_set(errp, 0);
				}
			}
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_link_unit_status, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ITSK00144_2DataPresent_req_status:
			if (s->test_req_status)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_status"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_STATUS;
					Dz1Error_set(errp, 0);
				}
			}
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_status, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ITSK00144_2DataPresent_req_list:
			if (s->test_req_list)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_list"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LIST;
					Dz1Error_set(errp, 0);
				}
			}
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_list, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ITSK00144_2DataPresent_req_update_list:
			if (s->test_req_update_list)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_update_list"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_UPDATE_LIST;
					Dz1Error_set(errp, 0);
				}
			}
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_rsp_update_list, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ITSK00144_2DataPresent_reset:
			if (s->test_req_reset)
			{
				if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_req_reset"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
				else
				{
					env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_RESET;
					Dz1Error_set(errp, 0);
				}
			}
			if (_send_data(arg, env, timer, ITSK00144_2DataPresent_ack, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: break;
		}
	}

	return ERR_IS_SUCCESS(errp);
}

static bool_t proc_msg(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, void* _msg, Dz1Error* errp)
{
	Dz1Binary* msg = (Dz1Binary*)_msg;
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Binary* src = NULL;
		int id = 0;
		if ((src = GitsnAsnUtil_getValueFromMessageFrame(msg, &id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&src);
			ASN1WorkSpace ws;
			ASN1_INIT_WS_INFO(&ws);
			pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			switch (id)
			{
			case 18: // map
			{
				MapData asn;
				memset(&asn, 0, sizeof(MapData));
				if (MapData_uper_decode(&ws, src, &asn, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Gitsn_MapData deser;
					if (GitsnAsnUtil_Gitsn_MapDataFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
					else
					{
						Dz1Asn1UTF8Str* str_u8 = NULL;
						if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_MapData"), &deser, errp)) == NULL) ERR_OUT(errp);
						else
						{
							Dz1Binary* data = NULL;
							pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
							if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
							else
							{
								if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, Dz1T("test_map"), NULL, Dz1T("MAP decode 성공하였습니다"), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
								
								if (s->test_map)
								{
									env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_MAP;
									if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_map"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
									else Dz1Error_set(errp, 0);
								}
							}
							pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						}
					}
				}
			}
			break;
			case 31: // tim
			{
				TravelerInformation asn;
				memset(&asn, 0, sizeof(TravelerInformation));
				if (TravelerInformation_uper_decode(&ws, src, &asn, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Gitsn_TravelerInformation deser;
					memset(&deser, 0, sizeof(Gitsn_TravelerInformation));
					if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
					else
					{
						Dz1Asn1UTF8Str* str_u8 = NULL;
						if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_TravelerInformation"), &deser, errp)) == NULL) ERR_OUT(errp);
						else
						{
							Dz1Binary* data = NULL;
							pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
							if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
							else
							{
								if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, Dz1T("test_tim"), NULL, Dz1T("TIM decode 성공하였습니다"), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);

								if (s->test_tim)
								{
									env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_TIM;
									if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_tim"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
									else Dz1Error_set(errp, 0);
								}
							}
							pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						}
					}
				}
			}
				break;

			default: ERR_SET_OUT(errp, EPERM);
				break;
			}

			pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&src);
		}

	}




	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_req(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	ITSK00144_2ScenarioLinkUnitRole* s = (ITSK00144_2ScenarioLinkUnitRole*)_s;
	ITSK00144_2ScenarioEvent ev = (ITSK00144_2ScenarioEvent)_ev;
	switch (ev)
	{
	case ITSK00144_2ScenarioEvent_heartbeat:
	if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00144_2_SENDER_SUT, Dz1T("heartbeat 응답을 수신하였습니다"), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if (s->test_session_maintain && (env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_SESSION_MAINTAIN) == 0)
	{
		if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, Dz1T("test_session_maintain"), Dz1T("SUCCESS"), errp) == FALSE)ERR_OUT(errp);
		else
		{
			env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_SESSION_MAINTAIN;
			Dz1Error_set(errp, 0);
		}
	}
	break;
	case ITSK00144_2ScenarioEvent_data:
		if (proc_req(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case ITSK00144_2ScenarioEvent_data2:
		if (proc_msg(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;

	}
	if (errp->code == 0 && (env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LINK_UNIT_STATUS) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_STATUS) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_LIST) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_UPDATE_LIST) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_REQ_RESET) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_TIM) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_MAP) &&
		(env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_TEST_SESSION_MAINTAIN))
	{
		env->state = ITSK00144_2ScenarioClientState_complete;
		Dz1Error_set(errp, 0);
	}
	

	return ERR_IS_SUCCESS(errp);

}









static ITSK00144_2TestScenarioF _link_unit_scenario[] = {
	_initial,
	_wait_req,
	NULL
};


static bool_t ITSK00144_2TestScenarioProcLinkUnitRole_event(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, ITSK00144_2ScenarioEvent ev, void* _msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env->state >= ITSK00144_2ScenarioClientState_complete) ERR_SET_OUT(errp, EPERM);
	else if (_link_unit_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
		ITSK00144_2TestScenarioProc_release(arg, env, timer, NULL);
		ERR_OUT(errp);
	}
	else
	{
		if (env->state == ITSK00144_2ScenarioClientState_complete)
		{
			*ret_is_copmplete = TRUE;
			ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("SUCCESS"), NULL);
			ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
			ITSK00144_2TestScenarioProc_release(arg, env, timer, NULL);
		}
	}
	return ERR_IS_SUCCESS(errp);
}



bool_t ITSK00144_2TestScenarioProcLinkUnitRole_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->flags & ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CREATED) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->state = ITSK00144_2ScenarioClientState_initial;
		env->received_seq = 0;
		env->send_seq = 0;
		env->flags |= ITSK_00144_2_LINK_UNIT_ROLE_FLAG_CREATED;

		if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else if (ITSK00144_2TestMsg_initSample(errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ITSK00144_2TestScenarioProcLinkUnitRole_event(arg, env, timer, s, ITSK00144_2ScenarioEvent_start, NULL, ret_is_copmplete, err);
}


static Dz1TaskProcStatus _received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	ITSK00144_2ClientSession* session = NULL;
	Dz1SockUtilReceiverReceived* msg = Dz1TaskSigMsg_getData(*sg);

	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(session->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("$$$ Received Message From Server = \n");
			Dz1Binary_dump(stream, 0);

			Dz1Stream_drain(session->rx_stream, (size_t)stream->size, NULL, NULL);

			ITSK00144_2TestScenarioProc_sockProc(arg, env, timer, stream, errp);


			/*if (_proc_payload(arg, env, timer, stream, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);*/
			//}
		}
	}
	return ret;
}

static Dz1TaskProcStatus _sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	ITSK00144_2ClientSession* session = NULL;

	if ((session = env->session->x.client) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, session->peer) != 0 || Dz1SockAddr_cmp(msg->local, session->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (env->send_seq == 256) env->send_seq = 0;	// 0~255
			Dz1Error_set(errp, 0);
		}
	}

	return ret;
}

static Dz1TaskProcStatus _disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;
	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);

	return ret;
}


bool_t ITSK00144_2TestScenarioProcLinkUnitRole_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, ITSK00144_2ScenarioLinkUnitRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	return ITSK00144_2TestScenarioProcLinkUnitRole_event(arg, env, timer, s, ev, msg, ret_is_copmplete, err);
}
bool_t ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
void   ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent);
}
