#include "Itsk00126v2TestScenarioProc.h"
#include <Itsk00126v2TestMsg.h>
#include <Dz1SockUtil.h>
#include <dz1_asn1.h>
#include <Itsk00126v2TestMsgDef.h>
#include <Itsk00126v2TestScenarioDefJson.h>

#define ITSK_00126_V1_SERVER_ROLE_FLAG_CREATED									0x80000000
#define ITSK_00126_V1_SERVER_ROLE_FLAG_CONNECTED								0x40000000
#define ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_IM_DEVICE_STTUS_INFO			0x20000000
#define ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_LIST_RESPONSE_INFO		0x10000000
#define ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_STTUS_INFO				0x08000000

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


static Itsk00126v2ServerSession* _gen_server_session(Itsk00126V2TestScenarioEnv* env, Itsk00126v2ScenarioServerRole* s, Dz1Error* errp)
{
	Itsk00126v2ServerSession* ret = NULL;

	if ((ret = Itsk00126v2ServerSession_new(-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v2ServerSession_delAndSetNull, (void*)&ret);
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

			if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			u16_t port;
			Dz1SockAddr_getPort(ret->local, &port);
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ SERVER : Port Opened(%d)...\n"), port);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Itsk00126v2ServerSession_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static bool_t _initial(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	Itsk00126v2ScenarioServerRole* s = (Itsk00126v2ScenarioServerRole*)_s;
	Itsk00126v2ScenarioEvent ev = (Itsk00126v2ScenarioEvent)_ev;

	switch (ev)
	{
	case Itsk00126v2ScenarioEvent_start:
		if (env->session != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((env->session = Itsk00126v2Session_new(Itsk00126v2SessionPresent_server, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((env->session->x.server = _gen_server_session(env, s, errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_CREATED;
			Dz1Error_set(errp, 0);
		}
		break;
	case Itsk00126v2ScenarioEvent_auth:
		env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_CONNECTED;
		Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_CREATED) && (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_CONNECTED))
	{
		// trigger, state 변경
		if (Itsk00126v2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->state = Itsk00126v2ScenarioServerState_wait_test_iot_im_device_sttus_info;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _validate_iot_im_device_sttus_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, void* _msg, Dz1Error* errp)
{
	Dz1Binary* msg = (Dz1Binary*)_msg;
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT 통합관리장치 상태정보 JSON 파싱을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("F2CIoTImDeviceSttusInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, msg->data, msg->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != msg->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				F2CIoTImDeviceSttusInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					// json parsing 성공

					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("F2CIoTImDeviceSttusInfo"), deser, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Binary* data = NULL;
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
							if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT 통합관리장치 상태정보 JSON 파싱에 성공하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							F2CIoTImDeviceSttusInfo_dump(deser, 0);
							pthread_cleanup_push(F2CIoTImDeviceSttusInfo_delAndSetNull, (void*)&deser);

							env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_IM_DEVICE_STTUS_INFO;

							if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1);// (F2CIoTImDeviceSttusInfo_delAndSetNull, (void*)&deser);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_iot_im_device_sttus_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	Itsk00126v2ScenarioServerRole* s = (Itsk00126v2ScenarioServerRole*)_s;
	Itsk00126v2ScenarioEvent ev = (Itsk00126v2ScenarioEvent)_ev;

	switch (ev)
	{
	case Itsk00126v2ScenarioEvent_trigger:
		if (s->test_iot_im_device_sttus_info == FALSE)
		{
			env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_IM_DEVICE_STTUS_INFO;
			Dz1Error_set(errp, 0);
		}
		else
		{
			env->current_test = Dz1T("test_iot_im_device_sttus_info");
			if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, Dz1T("test_iot_im_device_sttus_info"), Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Itsk00126v2ScenarioEvent_data:
		if (_validate_iot_im_device_sttus_info(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_IM_DEVICE_STTUS_INFO))
	{
		if (Itsk00126v2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00126_V1_DEFAULT_SCENARIO;
			env->state = Itsk00126v2ScenarioServerState_wait_test_iot_device_list_response_info;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t test_iot_device_list_response_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, Dz1Error* errp)
{
	Itsk00126v2ServerSession* session = NULL;

	env->current_test = Dz1T("test_iot_device_list_response_info");

	if ((session = env->session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Itsk00126v2Request* req = NULL;
		if ((req = Itsk00126v2Request_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Itsk00126v2RequestData* req_data = NULL;
			pthread_cleanup_push(Itsk00126v2Request_delAndSetNull, (void*)&req);
			if ((req->command = Dz1Str_clone(Dz1T("message"), errp)) == NULL) ERR_OUT(errp);
			else if ((req_data = req->data = Itsk00126v2RequestData_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((req_data->iot_im_device_id = Dz1Str_clone(s->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
			else if ((req_data->event_name = Dz1Str_clone(Dz1T("iot_device_list_request_info"), errp)) == NULL) ERR_OUT(errp);
			else if ((req_data->event_type = Dz1Str_clone(Dz1T("request"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Asn1UTF8Str* str_u8 = NULL;
				if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Itsk00126v2Request"), req, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Binary* data = NULL;
					if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
						if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00126_V1_SENDER_AGENT, Dz1T("시험 대상에게 요청 메시지를 전달합니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
						pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
					}
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if (Dz1SockUtilTxFifo_send(session->tx_fifo, session->sock, str_u8->data, str_u8->size, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);

					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
			}
			pthread_cleanup_pop(1); // (Itsk00126v2Request_delAndSetNull, (void*)&req);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_iot_device_list_response_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, void* _msg, Dz1Error* errp)
{
	Dz1Binary* msg = (Dz1Binary*)_msg;
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT 통합관리장치 관리목록정보 응답 메시지 JSON 파싱을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("F2CIoTDeviceListResponseInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, msg->data, msg->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != msg->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				F2CIoTDeviceListResponseInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					// json parsing 성공

					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("F2CIoTDeviceListResponseInfo"), deser, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Binary* data = NULL;
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
							if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT 통합관리장치 관리목록정보 응답 메시지 JSON 파싱에 성공하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							F2CIoTDeviceListResponseInfo_dump(deser, 0);
							pthread_cleanup_push(F2CIoTDeviceListResponseInfo_delAndSetNull, (void*)&deser);

							env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_LIST_RESPONSE_INFO;

							if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1);// (F2CIoTDeviceListResponseInfo_delAndSetNull, (void*)&deser);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_iot_device_list_response_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	Itsk00126v2ScenarioServerRole* s = (Itsk00126v2ScenarioServerRole*)_s;
	Itsk00126v2ScenarioEvent ev = (Itsk00126v2ScenarioEvent)_ev;

	switch (ev)
	{
	case Itsk00126v2ScenarioEvent_trigger:
		if (s->test_iot_device_list_response_info== FALSE)
		{
			env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_LIST_RESPONSE_INFO;
			Dz1Error_set(errp, 0);
		}
		else if (test_iot_device_list_response_info(arg, env, timer, s, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Itsk00126v2ScenarioEvent_data:
		if (_validate_iot_device_list_response_info(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;

	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}

	if (errp->code == 0 && (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_LIST_RESPONSE_INFO))
	{
		if (Itsk00126v2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00126_V1_DEFAULT_SCENARIO;
			env->state = Itsk00126v2ScenarioServerState_wait_test_iot_device_sttus_info;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _validate_iot_device_sttus_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, void* _msg, Dz1Error* errp)
{
	Dz1Binary* msg = (Dz1Binary*)_msg;
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT장치 상태정보 JSON 파싱을 시도합니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		Dz1Json* json = NULL;
		int cnt = 0;
		if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("F2CIoTDeviceSttusInfo"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, msg->data, msg->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != msg->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				F2CIoTDeviceSttusInfo* deser = NULL;
				if ((deser = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					// json parsing 성공

					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("F2CIoTDeviceSttusInfo"), deser, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Binary* data = NULL;
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
							if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, NULL, Dz1T("IoT장치 상태정보 JSON 파싱에 성공하였습니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							F2CIoTDeviceSttusInfo_dump(deser, 0);
							pthread_cleanup_push(F2CIoTDeviceSttusInfo_delAndSetNull, (void*)&deser);

							env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_STTUS_INFO;

							if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, env->current_test, Dz1T("SUCCESS"), errp) == FALSE) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);

							pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1);// (F2CIoTDeviceSttusInfo_delAndSetNull, (void*)&deser);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_test_iot_device_sttus_info(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	Itsk00126v2ScenarioServerRole* s = (Itsk00126v2ScenarioServerRole*)_s;
	Itsk00126v2ScenarioEvent ev = (Itsk00126v2ScenarioEvent)_ev;

	switch (ev)
	{
	case Itsk00126v2ScenarioEvent_trigger:
		if (s->test_iot_device_sttus_info == FALSE)
		{
			env->flags |= ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_STTUS_INFO;
			Dz1Error_set(errp, 0);
		}
		else
		{
			env->current_test = Dz1T("test_iot_device_sttus_info");
			if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, Dz1T("test_iot_device_sttus_info"), Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		break;
	case Itsk00126v2ScenarioEvent_data:
		if (_validate_iot_device_sttus_info(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_TEST_IOT_DEVICE_STTUS_INFO))
	{
		if (Itsk00126v2TestScenarioProc_triggerPost(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->current_test = ITSK_00126_V1_DEFAULT_SCENARIO;
			env->state = Itsk00126v2ScenarioServerState_complete;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Itsk00126v2TestScenarioF _server_scenario[] = {
	_initial,
	_wait_test_iot_im_device_sttus_info,
	_wait_test_iot_device_list_response_info,
	_wait_test_iot_device_sttus_info,
	NULL
};



static bool_t Itsk00126v2TestScenarioProcServerRole_event(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, Itsk00126v2ScenarioEvent ev, void* _msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env->state >= Itsk00126v2ScenarioServerState_complete) ERR_SET_OUT(errp, EPERM);
	else if (_server_scenario[env->state](arg, env, timer, s, ev, _msg, errp) == FALSE)
	{
		Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
		Itsk00126v2TestScenarioProc_release(arg, env, timer, NULL);
		ERR_OUT(errp);
	}
	else
	{
		if (env->state == Itsk00126v2ScenarioServerState_complete)
		{
			*ret_is_copmplete = TRUE;
			Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("SUCCESS"), NULL);
			Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
			Itsk00126v2TestScenarioProc_release(arg, env, timer, NULL);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126v2TestScenarioProcServerRole_start(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->flags & ITSK_00126_V1_SERVER_ROLE_FLAG_CREATED) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->state = Itsk00126v2ScenarioServerState_initial;

		if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("START"), errp) == FALSE) ERR_OUT(errp);
		// else if (Itsk00126v2TestMsg_initSample(errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return Itsk00126v2TestScenarioProcServerRole_event(arg, env, timer, s, Itsk00126v2ScenarioEvent_start, NULL, ret_is_copmplete, err);
}

bool_t Itsk00126v2TestScenarioProcServerRole_trigger(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, bool_t* ret_is_copmplete, Dz1Error* err)
{
	return Itsk00126v2TestScenarioProcServerRole_event(arg, env, timer, s, Itsk00126v2ScenarioEvent_trigger, NULL, ret_is_copmplete, err);
}

bool_t Itsk00126v2TestScenarioProcServerRole_sockProc(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Itsk00126v2ScenarioServerRole* s, int ev, void* msg, bool_t* ret_is_copmplete, Dz1Error* err)
{
	return Itsk00126v2TestScenarioProcServerRole_event(arg, env, timer, s, ev, msg, ret_is_copmplete, err);
}


// SOCK MESSAGE
// DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED
static Dz1TaskProcStatus _server_connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Dz1SockUtilAcceptorConnected* msg = Dz1TaskSigMsg_getData(*sg);
	//Itsk00126V2ScenarioConfig* scenario = NULL;
	Itsk00126v2Session* session = NULL;
	Itsk00126v2ServerSession* server = NULL;
	Itsk00126v2Scenario* s = NULL;

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
			if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		msg->sock = NULL;
		msg->local = msg->peer = NULL;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Session established ] = \n"));
		Itsk00126v2ServerSession_dump(server, 0);

		bool_t is_complete = FALSE;
		Itsk00126v2TestScenarioProcServerRole_sockProc(arg, env, timer, s->x.serverRole, Itsk00126v2ScenarioEvent_auth, NULL, &is_complete, errp);

		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION
static Dz1TaskProcStatus _server_connect_exception(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	if (env->session != NULL) Itsk00126v2Session_delAndSetNull((void*)&env->session);

	Dz1Thread_printf("!!! Server accept error!\n");

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _server_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Session* session = NULL;
	Itsk00126v2ServerSession* server = NULL;
	Itsk00126v2Scenario* s = NULL;

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

			if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00126_V1_SENDER_SUT, Dz1T("시험 대상으로부터 메시지를 수신하였습니다."), stream, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Itsk00126v2TestScenarioProc_sockProc(arg, env, timer, stream, errp);

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
	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Server Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);
	Itsk00126v2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else
	{
		// Itsk00126v2TestScenarioProc_sockProc(arg, env, timer, s, Itsk00126V2ScenarioEvent_disconnected, NULL, errp);
		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_TRANSMITER_SENT
static Dz1TaskProcStatus _server_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	Itsk00126v2Session* session = NULL;
	Itsk00126v2ServerSession* server = NULL;

	Itsk00126v2Scenario* s = NULL;
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

bool_t Itsk00126v2TestScenarioProcServerRole_sockMsgInit(void* task, Dz1Error* err)
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
void   Itsk00126v2TestScenarioProcServerRole_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent);
}