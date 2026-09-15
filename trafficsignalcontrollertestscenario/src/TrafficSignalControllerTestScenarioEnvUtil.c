#include "TrafficSignalControllerTestScenarioEnvUtil.h"
#include "TrafficSignalControllerTestScenarioMsg.h"

#include <TrafficSignalControllerTestMsg.h>

char* json_str = "{ \"scenarios\": [{ \"title\": \"교차로 제어정보 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 제어정보 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}";

static struct UIConfigToTestScenario
{
	Dz1Str testScenario;
	Dz1Str ui_conf;
} ui2ts[] = {
	{Dz1T("control"), Dz1T("{ \"scenarios\": [{ \"title\": \"교차로 제어정보 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 제어정보 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("status"), Dz1T("{ \"scenarios\": [{ \"title\": \"교차로 상황정보 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 상황정보 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("detector"), Dz1T("{ \"scenarios\": [{ \"title\": \"검지기 정보 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"검지기 정보 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("signal_phase_down"), Dz1T("{ \"scenarios\": [{ \"title\": \"현시정보 다운로드 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"현시정보 다운로드 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("signal_phase_up"), Dz1T("{ \"scenarios\": [{ \"title\": \"현시정보 업로드 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"현시정보 업로드 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("clock_down"), Dz1T("{ \"scenarios\": [{ \"title\": \"CLOCK 다운로드 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"CLOCK 다운로드 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("clock_up"), Dz1T("{ \"scenarios\": [{ \"title\": \"CLOCK 업로드 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"CLOCK 업로드 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("special_command"), Dz1T("{ \"scenarios\": [{ \"title\": \"SPECIAL COMMAND 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"SPECIAL COMMAND 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
	{Dz1T("fw_upgrade"), Dz1T("{ \"scenarios\": [{ \"title\": \"펌웨어 업그레이드 연동시험\", \"key\": \"test_data\"}], \"configuration\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"Div\", \"option\": { \"direction\": \"row\"}, \"components\": [{ \"type\": \"FieldSet\", \"option\": { \"label\": \"\"}, \"components\": [{ \"type\": \"Input\", \"option\": { \"label\": \"접속 수신 대기 Port 번호\", \"type\": \"number\", \"name\": \"port\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"펌웨어 업그레이드 연동시험\", \"type\": \"checkbox\", \"name\": \"test_data\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"교차로 ID\", \"type\": \"number\", \"name\": \"cross_id\"}}, { \"type\": \"Input\", \"option\": { \"label\": \"요청 메시지 (JSON)\", \"type\": \"File\", \"name\": \"req_str\"}}]}]}]}]}")},
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

bool_t TrafficSignalControllerTestScenarioEnvUtil_sendUIConfigure(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err)
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
		else if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_UI_CONFIGURE, (void*)&ui_conf, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyState(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL || testName == NULL || state == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		TrafficSignalControllerNotifyStateArg* arg = NULL;
		if ((arg = TrafficSignalControllerNotifyStateArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TrafficSignalControllerNotifyStateContext* context = NULL;
			pthread_cleanup_push(TrafficSignalControllerNotifyStateArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = TrafficSignalControllerNotifyStateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				if (errp->code == 0)
					if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_STATE, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
			}
			pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyStateArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		TrafficSignalControllerNotifyInfoArg* arg = NULL;
		if ((arg = TrafficSignalControllerNotifyInfoArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TrafficSignalControllerNotifyInfoContext* context = NULL;
			pthread_cleanup_push(TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = TrafficSignalControllerNotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_INFO, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyError(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, TrafficSignalControllerProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		TrafficSignalControllerNotifyErrorArg* arg = NULL;
		if ((arg = TrafficSignalControllerNotifyErrorArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TrafficSignalControllerNotifyErrorContext* context = NULL;
			pthread_cleanup_push(TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void*)&arg);

			if ((context = TrafficSignalControllerNotifyErrorContext_gen(errp)) == NULL) ERR_OUT(errp);
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
					if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_ERROR, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
				}
			}
			pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_validateRequest(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, TrafficSignalControllerProcessStatusCode code, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		TrafficSignalControllerValidateContextArg* arg = NULL;
		if ((arg = TrafficSignalControllerValidateContextArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TrafficSignalControllerValidateContext* context = NULL;
			pthread_cleanup_push(TrafficSignalControllerValidateContextArg_delAndSetNull, (void*)&arg);
			if (testName == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((arg->context = context = TrafficSignalControllerValidateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->desc = Dz1Str_clone(TrafficSignalControllerProcessStatusCodeStrA(code), errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (TrafficSignalControllerValidateContextArg_delAndSetNull, (void*)&arg);
		}

	}
	return ERR_IS_SUCCESS(errp);
}


bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyStateToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyStateArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerNotifyStateArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = TrafficSignalControllerNotifyStateArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyStateArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_STATE, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyStateArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyInfoToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyInfoArg* arg, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerNotifyInfoArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = TrafficSignalControllerNotifyInfoArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_INFO, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyInfoArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t TrafficSignalControllerTestScenarioEnvUtil_notifyErrorToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerNotifyErrorArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerNotifyErrorArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = TrafficSignalControllerNotifyErrorArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_NOTIFY_ERROR, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerNotifyErrorArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t TrafficSignalControllerTestScenarioEnvUtil_validateRequestToMain(TrafficSignalControllerTestScenarioEnv* env, TrafficSignalControllerValidateContextArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerValidateContextArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = TrafficSignalControllerValidateContextArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerValidateContextArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TrafficSignalControllerValidateContextArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
