#include "TrafficSignalControllerTestScenarioProc.h"


#include <Dz1SockUtil.h>
#include <dz1_asn1.h>

#include <TrafficSignalControllerTestMsg.h>
#include <TrafficSignalControllerTestMsgFrame.h>

#define TRAFFIC_SIGNAL_CONTROLLER_FLAG_CREATED			0x80000000
#define TRAFFIC_SIGNAL_CONTROLLER_FLAG_CONNECTED		0x40000000
#define TRAFFIC_SIGNAL_CONTROLLER_FLAG_TEST_DATA		0x20000000

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

static TrafficSignalControllerSession* _gen_server_session(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerScenario* s, Dz1Error* errp)
{
	TrafficSignalControllerSession* ret = NULL;

	if ((ret = TrafficSignalControllerSession_new(-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerSession_delAndSetNull, (void*)&ret);
		Dz1SockAddr local;
		u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
		if (0) {}
		else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, (u16_t)s->port)).code) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->acceptor = Dz1SockUtilAcceptorForTask_start(0, ret->local, my_queue_id, errp)) == (u32_t)-1) ERR_OUT(errp);
		else
		{
			char log[128];
			sprintf(log, "포트(%d)를 열었습니다. 클라이언트의 접속 수신을 대기합니다.", (int)s->port);

			if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			u16_t port;
			Dz1SockAddr_getPort(ret->local, &port);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ SERVER : Port Opened(%d)...\n"), port);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerServerSession_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static bool_t _initial(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	TrafficSignalControllerScenario* s = (TrafficSignalControllerScenario*)_s;
	TrafficSignalControllerScenarioEvent ev = (TrafficSignalControllerScenarioEvent)_ev;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	switch (ev)
	{
	case TrafficSignalControllerScenarioEvent_start:
		if (env->session != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((env->session = _gen_server_session(env, s, errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->flags |= TRAFFIC_SIGNAL_CONTROLLER_FLAG_CREATED;
			Dz1Error_set(errp, 0);
		}
		break;

	case TrafficSignalControllerScenarioEvent_auth:
		env->flags |= TRAFFIC_SIGNAL_CONTROLLER_FLAG_CONNECTED;
		Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & TRAFFIC_SIGNAL_CONTROLLER_FLAG_CREATED) && (env->flags & TRAFFIC_SIGNAL_CONTROLLER_FLAG_CONNECTED))
	{
		if (TrafficSignalControllerTestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = TrafficSignalControllerScenarioState_wait_test;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static TrafficSignalControllerTestMsgFrame* _convert_to_msgFrame(TrafficSignalControllerRequest* msg, Dz1Error* errp)
{
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		switch (msg->present)
		{
		case TrafficSignalControllerRequestPresent_control:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromCrossControlInformation(msg->x.control, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_status:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromCrossIndicator(msg->x.status, Dz1IOStreamEndian_big, TrafficSignalControllerRequestPresent_status, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_detector:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromCrossIndicator(msg->x.detector, Dz1IOStreamEndian_big, TrafficSignalControllerRequestPresent_detector, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_down:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromSignalPhaseInformationDownload(msg->x.signal_phase_down, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_signal_phase_up:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromCrossIndicator(msg->x.signal_phase_up, Dz1IOStreamEndian_big, TrafficSignalControllerRequestPresent_signal_phase_up, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_clock_down:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromClockInformationDownload(msg->x.clock_down, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_clock_up:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromCrossIndicator(msg->x.detector, Dz1IOStreamEndian_big, TrafficSignalControllerRequestPresent_clock_up, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_special_cmd:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromSpecialCommandInformation(msg->x.special_cmd, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerRequestPresent_fw_upgrade_cmd:
			if ((ret = TrafficSignalControllerTestMsgFrame_fromFirmwareUpgradeCommand(msg->x.fw_upgrade_cmd, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return ret;
}

static bool_t _convert_and_send(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerRequest* msg, Dz1Error* errp)
{
	TrafficSignalControllerTestMsgFrame* f = NULL;
	TrafficSignalControllerScenario* scenario = NULL;
	TrafficSignalControllerSession* session = NULL;

	if ((scenario = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	if (msg == NULL) ERR_OUT(errp);
	else if ((f = _convert_to_msgFrame(msg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary* bin = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
		if ((bin = TrafficSignalControllerTestMsgFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&bin);

			// send to peer log
			if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, TRAFFIC_SIGNAL_CONTROLLER_SENDER_AGENT, Dz1T("시험 대상에게 메시지를 전송합니다."), bin, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, bin->data, bin->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&bin);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _fwd_request(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerRequest* msg, Dz1Error* errp)
{
	if (msg == NULL) ERR_OUT(errp);
	else if (_convert_and_send(env, msg, errp) == FALSE)	ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}


static bool_t _test_data(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, TrafficSignalControllerScenario* s, Dz1Error* errp)
{


	if (TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, Dz1T("test_name"), Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);


	int cnt = 0;
	Dz1Json* json = NULL;

	if (s->req_str == NULL || Dz1STRCMP(s->req_str, Dz1T("")) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if ((json = Dz1Json_new("UTF-8", env->spec, "TrafficSignalControllerRequest", errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, s->req_str, Dz1STRLEN(s->req_str), errp)) < 0) ERR_OUT(errp);
			else if (sz != Dz1STRLEN(s->req_str)) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0)
			{
				if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, Dz1T("test_name"), NULL, Dz1T("Reqeust 메시지 JSON 파싱에 실패하였습니다."), NULL, NULL, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
				else ERR_SET_OUT(errp, EFAULT);
			}
			else if (cnt = 0) Dz1Error_set(errp, 0);
			else
			{
				Dz1Asn1UTF8Str* u8 = NULL;
				if ((u8 = Dz1Asn1UTF8Str_newFromStr(s->req_str, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&u8);
					Dz1Binary* b = NULL;
					if ((b = Dz1Binary_new(u8->data, u8->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&b);
						if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, Dz1T("test_name"), NULL, Dz1T("전송할 Request context : "), b, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
						pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&b);
					}

					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&u8);
				}

				TrafficSignalControllerRequest* reqMsg = NULL;
				if ((reqMsg = (TrafficSignalControllerRequest*)Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else if (s->eam_type != reqMsg->present)
				{
					if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, Dz1T("test_name"), NULL, Dz1T("Reqeust 메시지 유형이 잘못되었습니다."), NULL, NULL, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
					else ERR_SET_OUT(errp, EFAULT);
				}
				else
				{
					pthread_cleanup_push(TrafficSignalControllerRequest_delAndSetNull, (void*)&reqMsg);
					if (_fwd_request(env, reqMsg, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					pthread_cleanup_pop(1); // (TrafficSignalControllerRequest_delAndSetNull, (void*)&reqMsg);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}

	return ERR_IS_SUCCESS(errp);
}


static TrafficSignalControllerResponse* TrafficSignalControllerResponse_fromCtx(TrafficSignalControllerTestMsgFrameContext* ctx, u8_t cross_id, Dz1Error* errp)
{
	TrafficSignalControllerResponse* ret = NULL;

	if (ctx == NULL) ERR_OUT(errp);
	else if ((ret = TrafficSignalControllerResponse_new((TrafficSignalControllerResponsePresent)ctx->present, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerResponse_delAndSetNull, (void*)&ret);
		switch (ret->present)
		{
		case TrafficSignalControllerResponsePresent_control:
			if ((ret->x.control = CrossIndicator_new(cross_id, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_status:
			if ((ret->x.status = CrossStatusInformation_new(cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->x.status->lc_status = CrossStatusBasicInfo_clone(ctx->x.status_rsp->lc_status, errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (ctx->x.status_rsp->ex_status)
				{
					if ((ret->x.status->ex_status = CrossStatusExtInfo_r27_clone(ctx->x.status_rsp->ex_status, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				Dz1Error_set(errp, 0);
			}
			break;
		case TrafficSignalControllerResponsePresent_detector:
			if ((ret->x.detector = DetectorInformation_new(cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->x.detector->detector_info = DetectorInfo_clone(ctx->x.detector_rsp, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_down:
			if ((ret->x.signal_phase_down = CrossIndicator_new(cross_id, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_signal_phase_up:
			if ((ret->x.signal_phase_up = SignalPhaseInformationUpload_new(cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->x.signal_phase_up->signal_phase_info_up = SignalPhaseInfoUp_clone(ctx->x.signal_phase_upload_rsp, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_clock_down:
			if ((ret->x.clock_down = CrossIndicator_new(cross_id, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_clock_up:
			if ((ret->x.clock_up = ClockInformationUpload_new(cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->x.clock_up->clock_info_up = ClockInfo_clone(ctx->x.clock_upload_rsp, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_special_cmd:
			if ((ret->x.special_cmd = SpecialCommandInformationResponse_new(cross_id, errp)) == NULL) ERR_OUT(errp);
			else if (ctx->x.special_command_rsp)
			{
				if ((ret->x.special_cmd->ppc_register_num_list = SpecialCommandPPCNumberList_clone(ctx->x.special_command_rsp, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else Dz1Error_set(errp, 0);
			break;
		case TrafficSignalControllerResponsePresent_fw_upgrade_cmd:
			if ((ret->x.fw_upgrade_cmd = FirmwareUpgradeResponse_new(cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->x.fw_upgrade_cmd->error = FirmwareUpgradeError_clone(ctx->x.fw_upgrade_rsp, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}

		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static bool_t _validate_rsp(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, TrafficSignalControllerScenario* s, Dz1Error* errp)
{
	TrafficSignalControllerTestMsgFrame* f = NULL;
	TrafficSignalControllerTestMsgFrame_dump(f, 0);

	if ((s->received) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((f = TrafficSignalControllerTestMsgFrame_clone(s->received, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_decode(f->context, Dz1IOStreamEndian_big, NULL, errp)) == NULL)
		{
			// decode error 시험 fail

		}
		else
		{
			TrafficSignalControllerResponse* rsp = NULL;
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
			if ((rsp = TrafficSignalControllerResponse_fromCtx(ctx, f->cross_id, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Asn1UTF8Str* str_u8 = NULL;
				pthread_cleanup_push(TrafficSignalControllerResponse_delAndSetNull, (void*)&rsp);
				// 정상 
				if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("TrafficSignalControllerResponse"), rsp, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Binary* data = NULL;
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						if (rsp->present - 0x01 == s->eam_type)
						{
							if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, Dz1T("test_name"), NULL, Dz1T("수신 메시지 확인을 성공하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
							else if (TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, Dz1T("test_name"), Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
							else
							{
								env->flags |= TRAFFIC_SIGNAL_CONTROLLER_FLAG_TEST_DATA;
								Dz1Error_set(errp, 0);
							}
						}
						else
						{
							if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, Dz1T("test_name"), NULL, Dz1T("올바르지 않은 응답 메시지 입니다.."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
					}
					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
				pthread_cleanup_pop(1); // (TrafficSignalControllerResponse_delAndSetNull, (void*)&rsp);
			}
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _wait_test(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	TrafficSignalControllerScenario* s = (TrafficSignalControllerScenario*)_s;
	TrafficSignalControllerScenarioEvent ev = (TrafficSignalControllerScenarioEvent)_ev;
	switch (ev)
	{

	case TrafficSignalControllerScenarioEvent_trigger:
		if (_test_data(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	break;case TrafficSignalControllerScenarioEvent_data:
		if (_validate_rsp(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & TRAFFIC_SIGNAL_CONTROLLER_FLAG_TEST_DATA))
	{
		env->state = TrafficSignalControllerScenarioState_complete;
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}


static TrafficSignalControllerF _traffic_signal_controller_scenario[] =
{
	 _initial,
	 _wait_test,
	NULL
};

static bool_t TrafficSignalControllerTestScenarioProc_event(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, void* s, int ev, void* msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env->state >= TrafficSignalControllerScenarioState_complete) ERR_SET_OUT(errp, EPERM);
	else if (_traffic_signal_controller_scenario[env->state](arg, env, timer, s, ev, msg, errp) == FALSE)
	{
		TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
		TrafficSignalControllerTestScenarioProc_release(arg, env, timer, NULL);

	}
	else
	{
		Dz1Error_set(errp, 0);
		if (env->state == TrafficSignalControllerScenarioState_complete)
		{
			*ret_is_complete = TRUE;
			TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("SUCCESS"), NULL);
			TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
			TrafficSignalControllerTestScenarioProc_release(arg, env, timer, NULL);
		}
	}

	return ERR_IS_SUCCESS(errp);
}


bool_t TrafficSignalControllerTestScenarioProc_start(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		bool_t is_complete = FALSE;
		env->is_run = TRUE;

		env->state = TrafficSignalControllerScenarioState_initial;
		if (TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		return TrafficSignalControllerTestScenarioProc_event(arg, env, timer, s, TrafficSignalControllerScenarioEvent_start, NULL, &is_complete, errp);

	}
	return ERR_IS_SUCCESS(errp);

}
bool_t TrafficSignalControllerTestScenarioProc_stop(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("STOP"), errp) == FALSE) ERR_OUT(errp);
	else if (TrafficSignalControllerTestScenarioEnvUtil_notifyState(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	TrafficSignalControllerTestScenarioProc_release(arg, env, timer, errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ TrafficSignalController Test is aborted...\n"));
	
	return ERR_IS_SUCCESS(errp);
}

void TrafficSignalControllerTestScenarioProc_release(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	if (env->session != NULL)
		TrafficSignalControllerSession_delAndSetNull((void*)&env->session);

	if (env->scenario != NULL)
		TrafficSignalControllerScenario_delAndSetNull((void*)&env->scenario);

	env->is_run = FALSE;
	env->flags = 0;
	env->state = TrafficSignalControllerScenarioState_initial;
	Dz1Thread_printf("$$$ TrafficSignalController Test Scenario is released...\n");
}

bool_t TrafficSignalControllerTestScenarioProc_triggerPost(void* tSelf, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(tSelf, Dz1Task_getQueueID(tSelf), TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TRIGGER)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioProc_trigger(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t is_complete = FALSE;

		return TrafficSignalControllerTestScenarioProc_event(arg, env, timer, s, TrafficSignalControllerScenarioEvent_trigger, NULL, &is_complete, errp);
	}
	return ERR_IS_SUCCESS(errp);
}


static Dz1TaskProcStatus _task_scenarioTrigger(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* s = env->scenario;
	if (s == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TrafficSignalControllerTestScenarioProc_trigger(arg, env, timer, NULL);
		Dz1Error_set(errp, 0);
	}
	return ret;
}


bool_t TrafficSignalControllerTestScenarioProc_sockProc(TrafficSignalControllerTestScenarioArg* arg, TrafficSignalControllerTestScenarioEnv* env, void* timer, TrafficSignalControllerScenario* s, int ev, void* msg, Dz1Error* err)
{
	bool_t is_complete = FALSE;
	return TrafficSignalControllerTestScenarioProc_event(arg, env, timer, s, ev, msg, &is_complete, err);
}

static Dz1TaskProcStatus _notify_info(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* s = env->scenario;


	TrafficSignalControllerNotifyInfoArg* msg = (TrafficSignalControllerNotifyInfoArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfoToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_state(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* s = env->scenario;


	TrafficSignalControllerNotifyStateArg* msg = (TrafficSignalControllerNotifyStateArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (TrafficSignalControllerTestScenarioEnvUtil_notifyStateToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_error(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* s = env->scenario;


	TrafficSignalControllerNotifyErrorArg* msg = (TrafficSignalControllerNotifyErrorArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (TrafficSignalControllerTestScenarioEnvUtil_notifyErrorToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _validate_request(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (TrafficSignalControllerTestScenarioProc_sockProc(arg, env, timer, s, TrafficSignalControllerScenarioEvent_data, NULL, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

DZ1_CPPLINK bool_t TrafficSignalControllerTestScenarioProc_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_OUT(errp);
	// else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TrafficSignalController_TEST_SCENARIO_VALIDATE_RESPONSE), _received_validate_response)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_STATE), _notify_state)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_ERROR), _notify_error)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_INFO), _notify_info)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_VALIDATE_REQUEST), _validate_request)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_TRIGGER), _task_scenarioTrigger)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}




Dz1TaskProcStatus _connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* scenario = NULL;
	TrafficSignalControllerSession* session = NULL;

	Dz1SockUtilAcceptorConnected* msg = (Dz1SockUtilAcceptorConnected*)Dz1TaskSigMsg_getData(*sg);

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((scenario = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		if (0);
		else if ((session->peer = Dz1SockAddr_clone(msg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((session->sock = msg->sock) == NULL) ERR_OUT(errp);
		else if ((session->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((session->rx_stream = Dz1Stream_openRefElasticBuf(session->rx_buf, errp)) == NULL) ERR_OUT(errp);
		else if ((session->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_modeCallback(session->sock, session->peer, session->local, 1024, my_queue_id)).code) ERR_OUT(errp);
		else
		{
			char str_addr[64] = { 0, };
			Dz1SockAddrA_printable(msg->peer, str_addr, FALSE, NULL);

			char log[128] = "클라이언트가 접속하였습니다. 클라이언트 주소 : ";
			strcat(log, str_addr);

			if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			msg->peer = msg->local = NULL;
			msg->sock = NULL;
			session = NULL;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "@@@ Session Established!\n");
			TrafficSignalControllerSession_dump(env->session, 0);

			TrafficSignalControllerTestScenarioProc_sockProc(arg, env, timer, scenario, TrafficSignalControllerScenarioEvent_auth, NULL, errp);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

Dz1TaskProcStatus _connected_exception(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;
	Dz1SockUtilAcceptorException* msg = (Dz1SockUtilAcceptorException*)Dz1TaskSigMsg_getData(*sg);

	if (env->session != NULL)
	{
		TrafficSignalControllerSession_delAndSetNull(&env->session);
	}
	return ret;
}

Dz1TaskProcStatus _received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* scenario = NULL;
	TrafficSignalControllerSession* session = NULL;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	Dz1Thread_printf("Received msg from peer ] = \n");
	Dz1SockUtilReceiverReceived_dump(msg, 0);


	if ((scenario = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(session->local, msg->local) != 0 || Dz1SockAddr_cmp(session->peer, msg->peer) != 0) ERR_OUT(errp);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(session->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp);
		else
		{
			bool_t done = FALSE;
			TrafficSignalControllerTestMsgFrame* f = NULL;

			while (done == FALSE && errp->code == 0)
			{
				if ((f = TrafficSignalControllerTestMsgFrame_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					ssize_t sz = 0;
					pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
					if ((sz = TrafficSignalControllerTestMsgFrame_read(f, session->rx_stream, Dz1IOStreamEndian_big, NULL, errp)) < 0)
					{
						if (errp->code == EPIPE || errp->code == EAGAIN) { done = TRUE; Dz1Error_set(errp, 0); }
						else ERR_OUT(errp);
					}
					else
					{
						// received from peer log
						/*Dz1Binary* b = NULL;
						if ((b = Dz1Binary_clone(stream, errp)) == FALSE) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&b);*/
							if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, TRAFFIC_SIGNAL_CONTROLLER_DEFAULT_SCENARIO, TRAFFIC_SIGNAL_CONTROLLER_SENDER_SUT, Dz1T("시험 대상으로부터 메시지를 수신하였습니다."), stream, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						//	pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&b);
						//}

						Dz1Stream_drain(session->rx_stream, sz, NULL, errp);
						if ((scenario->received = TrafficSignalControllerTestMsgFrame_clone(f, errp)) == NULL) ERR_OUT(errp);
						else
						{
						
							if ((scenario->received = TrafficSignalControllerTestMsgFrame_clone(f, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_postSimple(env->tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_VALIDATE_REQUEST)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							//TrafficSignalControllerTestScenarioProc_sockProc(arg, env, timer, scenario, TrafficSignalControllerScenarioEvent_data, NULL, errp);
							//Dz1Error_set(errp, 0);
						}
					}
					pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&f);
				}
			}
		}
	}
	return ret;
}

Dz1TaskProcStatus _disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* scenario = NULL;
	TrafficSignalControllerSession* session = NULL;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	if ((scenario = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(session->local, msg->local) != 0 || Dz1SockAddr_cmp(session->peer, msg->peer) != 0) ERR_OUT(errp);
	else
	{
		char str_addr[53] = { 0, };
		Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "@@@ Session Closed(%s)\n", Dz1SockAddrA_printable(session->peer, str_addr, FALSE, NULL));
	}
	return ret;
}

Dz1TaskProcStatus _sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	TrafficSignalControllerScenario* scenario = NULL;
	TrafficSignalControllerSession* session = NULL;

	Dz1SockUtilTransmiterSent* msg = (Dz1SockUtilTransmiterSent*)Dz1TaskSigMsg_getData(*sg);

	if ((scenario = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(session->local, msg->local) != 0 || Dz1SockAddr_cmp(session->peer, msg->peer) != 0) ERR_OUT(errp);
	else
	{
		Dz1SockUtilTxFifo_sentProc(session->tx_fifo, session->sock, errp);
		Dz1Error_set(errp, 0);
	}
	return ret;
}



bool_t TrafficSignalControllerTestScenario_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _connected_exception)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
