#include "ITSK00144_2TestScenarioEnvUtil.h"
#include "ITSK00144_2TestScenarioMsg.h"


const char* json =
"{\"scenarios\":[{\"title\":\"I2X 교통안전시설 연계장치 장비 상태 정보 요청 시험\",\"key\":\"test_req_link_unit_status\"},{\"title\":\"IoT 교통안전시설별 상태 정보 요청 시험\",\"key\":\"test_req_status\"},{\"title\":\"IoT 교통안전시설 List 요청 시험\",\"key\":\"test_req_list\"},{\"title\":\"IoT 교통안전시설 List 갱신 요청 시험\",\"key\":\"test_req_update_list\"},{\"title\":\"I2X 교통안전시설 연계장치 RESET 요청 시험\",\"key\":\"test_req_reset\"},{\"title\":\"TIM 제공 시험\",\"key\":\"test_tim\"},{\"title\":\"MAP 제공 시험\",\"key\":\"test_map\"},{\"title\":\"세션 유지 시험 (heartbeat)\",\"key\":\"test_session_maintain\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 Serial No\",\"type\":\"number\",\"name\":\"serial_no\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"상세 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 장비 상태 정보 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_link_unit_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설별 상태 정보 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 갱신 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_update_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 RESET 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_reset\"}},{\"type\":\"Input\",\"option\":{\"label\":\"TIM 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_tim\"}},{\"type\":\"Input\",\"option\":{\"label\":\"MAP 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"세션 유지 시험 (heartbeat)\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"heartbeat 전송 주기\",\"type\":\"number\",\"name\":\"hb_duration\"}}]}]}]}]}";


static struct UIConfigToTestScenario
{
	Dz1Str testScenario;
	Dz1Str ui_conf;
} ui2ts[] = {
	{Dz1T("serverRole"), Dz1T("{\"scenarios\":[{\"title\":\"I2X 교통안전시설 연계장치 장비 상태 정보 응답 시험\",\"key\":\"test_rsp_link_unit_status\"},{\"title\":\"IoT 교통안전시설별 상태 정보 응답 시험\",\"key\":\"test_rsp_status\"},{\"title\":\"IoT 교통안전시설 List 응답 시험\",\"key\":\"test_rsp_list\"},{\"title\":\"IoT 교통안전시설 List 갱신 응답 시험\",\"key\":\"test_rsp_update_list\"},{\"title\":\"I2X 교통안전시설 연계장치 RESET 응답 시험\",\"key\":\"test_rsp_reset\"},{\"title\":\"세션 유지 시험 (heartbeat)\",\"key\":\"test_session_maintain\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 Serial No\",\"type\":\"number\",\"name\":\"serial_no\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"상세 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 장비 상태 정보 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_rsp_link_unit_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설별 상태 정보 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_rsp_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_rsp_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 갱신 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_rsp_update_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 RESET 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_rsp_reset\"}},{\"type\":\"Input\",\"option\":{\"label\":\"세션 유지 시험 (heartbeat)\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"heartbeat 전송 주기\",\"type\":\"number\",\"name\":\"hb_duration\"}}]}]}]}]}")},
	{Dz1T("linkUnitRole"), Dz1T("{\"scenarios\":[{\"title\":\"I2X 교통안전시설 연계장치 장비 상태 정보 요청 시험\",\"key\":\"test_req_link_unit_status\"},{\"title\":\"IoT 교통안전시설별 상태 정보 요청 시험\",\"key\":\"test_req_status\"},{\"title\":\"IoT 교통안전시설 List 요청 시험\",\"key\":\"test_req_list\"},{\"title\":\"IoT 교통안전시설 List 갱신 요청 시험\",\"key\":\"test_req_update_list\"},{\"title\":\"I2X 교통안전시설 연계장치 RESET 요청 시험\",\"key\":\"test_req_reset\"},{\"title\":\"TIM 제공 시험\",\"key\":\"test_tim\"},{\"title\":\"MAP 제공 시험\",\"key\":\"test_map\"},{\"title\":\"세션 유지 시험 (heartbeat)\",\"key\":\"test_session_maintain\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 IP 주소\",\"type\":\"text\",\"name\":\"peer_ip\"}},{\"type\":\"Input\",\"option\":{\"label\":\"접속 대상 Port 번호\",\"type\":\"number\",\"name\":\"peer_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 Serial No\",\"type\":\"number\",\"name\":\"serial_no\"}}]}]},{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"상세 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 장비 상태 정보 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_link_unit_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설별 상태 정보 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_status\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 교통안전시설 List 갱신 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_update_list\"}},{\"type\":\"Input\",\"option\":{\"label\":\"I2X 교통안전시설 연계장치 RESET 요청 시험\",\"type\":\"checkbox\",\"name\":\"test_req_reset\"}},{\"type\":\"Input\",\"option\":{\"label\":\"TIM 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_tim\"}},{\"type\":\"Input\",\"option\":{\"label\":\"MAP 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"세션 유지 시험 (heartbeat)\",\"type\":\"checkbox\",\"name\":\"test_session_maintain\"}},{\"type\":\"Input\",\"option\":{\"label\":\"heartbeat 전송 주기\",\"type\":\"number\",\"name\":\"hb_duration\"}}]}]}]}]}")},
	{NULL, NULL}
};

static Dz1Str _get_ui_config_from_test_sceanrio(Dz1Str testScenario)
{
	struct UIConfigToTestScenario* i;
	for (i = ui2ts; i->testScenario; i++)
	{
		if (Dz1STRCMP(i->testScenario, testScenario) == 0)
			return i->ui_conf;
	}
	return NULL;
}

bool_t ITSK00144_2TestScenarioEnvUtil_sendUIConfigure(ITSK001442TestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);

	if (env == NULL || testScenario == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Str ui_conf = NULL;
		if ((ui_conf = _get_ui_config_from_test_sceanrio(testScenario)) == NULL)
		{
			// notify error
			// unknown testSceanrio
			ERR_SET_OUT(errp, EFAULT);
		}
		else if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_UI_CONFIGURE, (void*)&ui_conf, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioEnvUtil_notifyState(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL || testName == NULL || state == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2NotifyStateArg* arg = NULL;
		if ((arg = ITSK00144_2NotifyStateArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2NotifyStateContext* context = NULL;
			pthread_cleanup_push(ITSK00144_2NotifyStateArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = ITSK00144_2NotifyStateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				if (errp->code == 0)
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_NOTIFY_STATE, (void*)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2NotifyStateArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioEnvUtil_notifyInfo(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2NotifyInfoArg* arg = NULL;
		if ((arg = ITSK00144_2NotifyInfoArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2NotifyInfoContext* context = NULL;
			pthread_cleanup_push(ITSK00144_2NotifyInfoArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = ITSK00144_2NotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (log != NULL)
				{
					if ((context->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (testName != NULL)
				{
					if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (sender != NULL)
				{
					if ((context->sender = Dz1Str_clone(sender, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (data != NULL)
				{
					if (dataType != NULL)
					{
						if ((context->dataType = Dz1Str_clone(dataType, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else  Dz1Error_set(errp, 0);
				}
				context->time = time(NULL);
			}

			if (errp->code == 0)
			{
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_NOTIFY_INFO, (void*)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2NotifyInfoArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioEnvUtil_notifyError(ITSK001442TestScenarioEnv* env, Dz1Str testName, ITSK00144_2ProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2NotifyErrorArg* arg = NULL;
		if ((arg = ITSK00144_2NotifyErrorArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2NotifyErrorContext* context = NULL;
			pthread_cleanup_push(ITSK00144_2NotifyErrorArg_delAndSetNull, (void*)&arg);

			if ((context = ITSK00144_2NotifyErrorContext_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				if (log != NULL)
				{
					if ((context->log = Dz1Str_clone(log, errp)) == NULL) ERR_OUT(errp);
					Dz1Error_set(errp, 0);
				}
				if (testName != NULL)
				{
					if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (desc != NULL)
				{
					if ((context->desc = Dz1Str_clone(desc, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				if (data != NULL)
				{
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else  Dz1Error_set(errp, 0);
				}

				context->time = time(NULL);
				context->code = code;

				if (errp->code == 0)
				{
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_NOTIFY_ERROR, (void*)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
				}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2NotifyErrorArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioEnvUtil_validateRequest(ITSK001442TestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, ITSK00144_2ProcessStatusCode code, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ITSK00144_2ValidateContextArg* arg = NULL;
		if ((arg = ITSK00144_2ValidateContextArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ITSK00144_2ValidateContext* context = NULL;
			pthread_cleanup_push(ITSK00144_2ValidateContextArg_delAndSetNull, (void*)&arg);
			if (testName == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((arg->context = context = ITSK00144_2ValidateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->desc = Dz1Str_clone(ITSK00144_2ProcessStatusCodeStrA(code), errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				context->code = code;
				Dz1Error_set(errp, 0);

				if (data != NULL)
				{
					if ((context->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}

				if (raw != NULL)
				{
					if ((context->raw = Dz1Binary_clone(raw, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			if (errp->code == 0)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Validate request [ %s ] to server!\n"), testName);
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_VALIDATE_REQUEST, (void*)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ValidateContextArg_delAndSetNull, (void*)&arg);
		}

	}
	return ERR_IS_SUCCESS(errp);
}
