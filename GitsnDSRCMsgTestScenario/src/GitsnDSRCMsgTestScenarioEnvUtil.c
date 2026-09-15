#include "GitsnDSRCMsgTestScenarioEnvUtil.h"
#include "GitsnDSRCMsgTestScenarioMsg.h"
#include <GitsnTestDataProtocol.h>
static struct UIConfigToTestScenario
{
	Dz1Str testScenario;
	Dz1Str ui_conf;
} ui2ts[] = {

	{Dz1T("DSRCMsgTest"), Dz1T("{\"scenarios\":[{\"title\":\"MAP 규격 검증 시험\",\"key\":\"test_map\"},{\"title\":\"SPaT 규격 검증 시험\",\"key\":\"test_spat\"},{\"title\":\"BSM 규격 검증 시험\",\"key\":\"test_bsm\"},{\"title\":\"EVA 규격 검증 시험\",\"key\":\"test_eva\"},{\"title\":\"PVD 규격 검증 시험\",\"key\":\"test_pvd\"},{\"title\":\"RTCM 규격 검증 시험\",\"key\":\"test_rtcm\"},{\"title\":\"SRM 규격 검증 시험\",\"key\":\"test_srm\"},{\"title\":\"SSM 규격 검증 시험\",\"key\":\"test_ssm\"},{\"title\":\"TIM 규격 검증 시험\",\"key\":\"test_tim\"},{\"title\":\"PSM 규격 검증 시험\",\"key\":\"test_psm\"},{\"title\":\"SDSM 규격 검증 시험\",\"key\":\"test_sdsm\"},{\"title\":\"TLS 규격 검증 시험\",\"key\":\"test_tls\"}],\"configuration\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"Div\",\"option\":{\"direction\":\"row\"},\"components\":[{\"type\":\"FieldSet\",\"option\":{\"label\":\"세션 설정\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"접속 수신 대기 Port 번호\",\"type\":\"number\",\"name\":\"local_port\"}}]},{\"type\":\"FieldSet\",\"option\":{\"label\":\"상세 시험\"},\"components\":[{\"type\":\"Input\",\"option\":{\"label\":\"MAP 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_map\"}},{\"type\":\"Input\",\"option\":{\"label\":\"SPaT 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_spat\"}},{\"type\":\"Input\",\"option\":{\"label\":\"BSM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_bsm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"EVA 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_eva\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PVD 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_pvd\"}},{\"type\":\"Input\",\"option\":{\"label\":\"rsa 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_rsa\"}},{\"type\":\"Input\",\"option\":{\"label\":\"RTCM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_rtcm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"SRM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_srm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"SSM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_ssm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"TIM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_tim\"}},{\"type\":\"Input\",\"option\":{\"label\":\"PSM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_psm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"SDSM 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_sdsm\"}},{\"type\":\"Input\",\"option\":{\"label\":\"TLS 규격 검증 시험\",\"type\":\"checkbox\",\"name\":\"test_tls\"}}]}]}]}]}")},
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

bool_t GitsnDSRCMsgTestScenarioEnvUtil_sendUIConfigure(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testScenario, Dz1Error* err)
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
		else if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_UI_CONFIGURE, (void**)&ui_conf, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyState(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL || testName == NULL || state == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnDSRCMsgNotifyStateArg* arg = NULL;
		if ((arg = GitsnDSRCMsgNotifyStateArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			GitsnDSRCMsgNotifyStateContext* context = NULL;
			pthread_cleanup_push(GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = GitsnDSRCMsgNotifyStateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->state = Dz1Str_clone(state, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->time = time(NULL);
				if (errp->code == 0)
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_STATE, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
			}
			pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnDSRCMsgNotifyInfoArg* arg = NULL;
		if ((arg = GitsnDSRCMsgNotifyInfoArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			GitsnDSRCMsgNotifyInfoContext* context = NULL;
			pthread_cleanup_push(GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void*)&arg);
			if ((arg->context = context = GitsnDSRCMsgNotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_INFO, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyError(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, GitsnDSRCMsgProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnDSRCMsgNotifyErrorArg* arg = NULL;
		if ((arg = GitsnDSRCMsgNotifyErrorArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			GitsnDSRCMsgNotifyErrorContext* context = NULL;
			pthread_cleanup_push(GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void*)&arg);

			if ((context = GitsnDSRCMsgNotifyErrorContext_gen(errp)) == NULL) ERR_OUT(errp);
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
					if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_ERROR, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
					else
					{
						arg = NULL;
						Dz1Error_set(errp, 0);
					}
				}
			}
			pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void*)&arg);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, GitsnDSRCMsgProcessStatusCode code, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnDSRCMsgValidateContextArg* arg = NULL;
		if ((arg = GitsnDSRCMsgValidateContextArg_new(env->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			GitsnDSRCMsgValidateContext* context = NULL;
			pthread_cleanup_push(GitsnDSRCMsgValidateContextArg_delAndSetNull, (void*)&arg);
			if (testName == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((arg->context = context = GitsnDSRCMsgValidateContext_gen(errp)) == NULL) ERR_OUT(errp);
			else if ((context->testName = Dz1Str_clone(testName, errp)) == NULL) ERR_OUT(errp);
			else if ((context->desc = Dz1Str_clone(GitsnDSRCMsgProcessStatusCodeStrA(code), errp)) == NULL) ERR_OUT(errp);
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
				if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&arg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
				else
				{
					arg = NULL;
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (GitsnDSRCMsgValidateContextArg_delAndSetNull, (void*)&arg);
		}

	}
	return ERR_IS_SUCCESS(errp);
}


bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyStateToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyStateArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgNotifyStateArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = GitsnDSRCMsgNotifyStateArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_STATE, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyStateArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyInfoToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyInfoArg* arg, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgNotifyInfoArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = GitsnDSRCMsgNotifyInfoArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_INFO, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyInfoArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t GitsnDSRCMsgTestScenarioEnvUtil_notifyErrorToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgNotifyErrorArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgNotifyErrorArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = GitsnDSRCMsgNotifyErrorArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_ERROR, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnDSRCMsgNotifyErrorArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioEnvUtil_validateRequestToMain(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgValidateContextArg* arg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgValidateContextArg* msg = NULL;
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((msg = GitsnDSRCMsgValidateContextArg_clone(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgValidateContextArg_delAndSetNull, (void*)&msg);
		if ((*errp = Dz1Task_post(env->tMain, DZ1_TASK_QUEUE_NONE, GITSN_DSRCMSG_TEST_SCENARIO_VALIDATE_REQUEST, (void**)&msg, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnDSRCMsgValidateContextArg_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}


bool_t GitsnDSRCMsgTestScenarioEnvUtil_insertDataFrame(GitsnDSRCMsgTestScenarioEnv* env, Dz1Binary* src, bool_t* ret_is_complete_df, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnTestDataFrames* dfs = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dfs = env->dfs) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnTestDataFrame* df = NULL;
		if ((df = GitsnTestDataFrame_decode(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(GitsnTestDataFrame_delAndSetNull, (void*)&df);
			GitsnTestDataFrame_dump(df, 0);

			if ((*errp = dfs->add(dfs, df)).code) ERR_OUT(errp);
			else
			{
				if (df->frameType == 0b00 || df->frameType == 0b10) *ret_is_complete_df = TRUE;
				else *ret_is_complete_df = FALSE;

				df = NULL;
			}
			pthread_cleanup_pop(1); // (GitsnTestDataFrame_delAndSetNull, (void*)&df);
		}
	}
	return ERR_IS_SUCCESS(errp);
}