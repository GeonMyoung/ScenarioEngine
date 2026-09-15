#include "Itsk00126v2TestScenarioEnvUtil.h"
#include "Itsk00126v2TestScenarioMsg.h"

static struct UIConfigToTestScenario
{
	Dz1Str testScenario;
	Dz1Str ui_conf;
} ui2ts[] = {
	{Dz1T("serverRole"), Dz1T("{\"scenarios\":[{\"title\":\"IoT 통합관리장치 상태정보 제공 시험\",\"key\":\"test_iot_im_device_sttus_info\"},{\"title\":\"IoT 통합관리장치 관리목록정보 메시지 응답 시험\",\"key\":\"test_iot_device_list_response_info\"},{\"title\":\"IoT장치 상태정보 제공 시험\",\"key\":\"test_iot_device_sttus_info\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 통합관리장치 ID\",\"type\":\"text\",\"name\":\"iot_im_device_id\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"상세 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"IoT 통합관리장치 상태정보 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_iot_im_device_sttus_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT 통합관리장치 관리목록정보 메시지 응답 시험\",\"type\":\"checkbox\",\"name\":\"test_iot_device_list_response_info\"}},{\"type\":\"Input\",\"option\":{\"label\":\"IoT장치 상태정보 제공 시험\",\"type\":\"checkbox\",\"name\":\"test_iot_device_sttus_info\"}}]}]}]}]}")},
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

bool_t Itsk00126V2TestScenarioEnvUtil_sendUIConfigure(Itsk00126V2TestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err)
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
		else if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_UI_CONFIGURE, (void**)&ui_conf, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_notifyState(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL || testName == NULL || state == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Itsk00126v2NotifyStateArg* arg = NULL;
		if ((arg = Itsk00126v2NotifyStateArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Itsk00126v2NotifyStateContext* context = NULL;
			pthread_cleanup_push(Itsk00126v2NotifyStateArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = Itsk00126v2NotifyStateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				if (errp->code == 0)
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_STATE, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
			}
			pthread_cleanup_pop(1); // (Itsk00126v2NotifyStateArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_notifyInfo(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Itsk00126v2NotifyInfoArg* arg = NULL;
		if ((arg = Itsk00126v2NotifyInfoArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Itsk00126v2NotifyInfoContext* context = NULL;
			pthread_cleanup_push(Itsk00126v2NotifyInfoArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = Itsk00126v2NotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_INFO, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Itsk00126v2NotifyInfoArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_notifyError(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Itsk00126v2ProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Itsk00126v2NotifyErrorArg* arg = NULL;
		if ((arg = Itsk00126v2NotifyErrorArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Itsk00126v2NotifyErrorContext* context = NULL;
			pthread_cleanup_push(Itsk00126v2NotifyErrorArg_delAndSetNull, (void*)&arg);

			if ((context = Itsk00126v2NotifyErrorContext_gen(errp)) == NULL) ERR_OUT(errp);
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
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_ERROR, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
				}
			}
			pthread_cleanup_pop(1); // (Itsk00126v2NotifyErrorArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_validateRequest(Itsk00126V2TestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, Itsk00126v2ProcessStatusCode code, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Itsk00126v2ValidateContextArg* arg = NULL;
		if ((arg = Itsk00126v2ValidateContextArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Itsk00126v2ValidateContext* context = NULL;
			pthread_cleanup_push(Itsk00126v2ValidateContextArg_delAndSetNull, (void*)&arg);
			if (testName == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((arg->context = context = Itsk00126v2ValidateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->desc = Dz1Str_clone(Itsk00126v2ProcessStatusCodeStrA(code), errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Itsk00126v2ValidateContextArg_delAndSetNull, (void*)&arg);
		}

	}
	return ERR_IS_SUCCESS(errp);
}


bool_t Itsk00126V2TestScenarioEnvUtil_notifyStateToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyStateArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2NotifyStateArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Itsk00126v2NotifyStateArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyStateArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_STATE, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Itsk00126v2NotifyStateArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_notifyInfoToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyInfoArg* arg, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2NotifyInfoArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Itsk00126v2NotifyInfoArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyInfoArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_INFO, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Itsk00126v2NotifyInfoArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t Itsk00126V2TestScenarioEnvUtil_notifyErrorToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2NotifyErrorArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2NotifyErrorArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Itsk00126v2NotifyErrorArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v2NotifyErrorArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_NOTIFY_ERROR, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Itsk00126v2NotifyErrorArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126V2TestScenarioEnvUtil_validateRequestToMain(Itsk00126V2TestScenarioEnv* env, Itsk00126v2ValidateContextArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2ValidateContextArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = Itsk00126v2ValidateContextArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v2ValidateContextArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, ITSK00126_V2_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Itsk00126v2ValidateContextArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
