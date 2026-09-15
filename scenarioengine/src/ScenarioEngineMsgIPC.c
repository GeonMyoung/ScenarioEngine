#include "ScenarioEngineArg.h"
#include "ScenarioEngineMsg.h"
#include "ScenarioEngineEnvUtil.h"

#include <dz1_web_socket.h>

static Dz1TaskProcStatus _handle_received_ui_configure(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;
	Dz1Str conf = (Dz1Str)Dz1TaskSigMsg_getData(*sg);
	Dz1Asn1UTF8Str* conf_u8 = NULL;
	Dz1Binary* conf_b = NULL;
	ScenarioEngineRequestMessageUIConfigure* ui_conf = NULL;
	if (conf == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((conf_u8 = Dz1Asn1UTF8Str_newFromStr(conf, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&conf_u8);
		if ((conf_b = Dz1Binary_new(conf_u8->data, conf_u8->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&conf_b);
			if ((ui_conf = ScenarioEngineRequestMessageUIConfigure_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->seq++;
				if (0) {}
				else if ((ui_conf->method = Dz1Str_clone(Dz1T("UI_CONFIGURE"), errp)) == NULL) ERR_OUT(errp);
				else if ((ui_conf->conf = Dz1Binary_clone(conf_b, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ui_conf->seq = env->seq;
					Dz1Error_set(errp, 0);
				}
				if (errp->code == 0)
				{
					if (ScenarioEngineEnvUtil_sendUIConfigureToServer(env, ui_conf, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}

			pthread_cleanup_pop(1); //(Dz1Binary_delAndSetNull, (void*)&conf_b);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&conf_u8);
	}

	return ret;
}

static Dz1TaskProcStatus _handle_received_scenario_notify_state(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;

	ScenarioEngineNotifyStateArg* notify_arg = (ScenarioEngineNotifyStateArg*)Dz1TaskSigMsg_getData(*sg);
	ScenarioEngineNotifyStateContext* context = NULL;
	if (notify_arg == NULL || (context = notify_arg->context) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->seq++;
		ScenarioEngineRequestMessageNotify* notify = NULL;
		if ((notify = ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_state, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ScenarioEngineRequestMessageNotifyState* state = NULL;
			pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
			if ((state = notify->x.state = ScenarioEngineRequestMessageNotifyState_new(Dz1T("NOTIFY"), env->seq, notify_arg->testIdx, Dz1T("state"), NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((state->data = ScenarioEngineNotifyStateContext_clone(context, errp)) == NULL) ERR_OUT(errp);
			else if (ScenarioEngineEnv_notifyToServer(env, notify, errp) == FALSE) ERR_OUT(errp);
			else
			{
				notify = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _handle_received_scenario_notify_info(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;

	ScenarioEngineNotifyInfoArg* notify_arg = (ScenarioEngineNotifyInfoArg*)Dz1TaskSigMsg_getData(*sg);
	ScenarioEngineNotifyInfoContext* context = NULL;
	if (notify_arg == NULL || (context = notify_arg->context) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->seq++;
		ScenarioEngineRequestMessageNotify* notify = NULL;
		if ((notify = ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_info, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ScenarioEngineRequestMessageNotifyInfo* info = NULL;
			pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
			if ((info = notify->x.info = ScenarioEngineRequestMessageNotifyInfo_new(Dz1T("NOTIFY"), env->seq, notify_arg->testIdx, Dz1T("info"), NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((info->data = ScenarioEngineNotifyInfoContext_clone(context, errp)) == NULL) ERR_OUT(errp);
			else if (ScenarioEngineEnv_notifyToServer(env, notify, errp) == FALSE) ERR_OUT(errp);
			else
			{
				notify = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
		}
	}
	return ret;
}



//	ScenarioEngineNotifyInfoContext* context = (ScenarioEngineNotifyInfoContext*)Dz1TaskSigMsg_getData(*sg);
//	ScenarioEngineRequestMessageNotify* notify = NULL;
//
//	env->seq++;
//	if (context == NULL) ERR_OUT(errp);
//	else if ((notify = ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_info, NULL, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		ScenarioEngineRequestMessageNotifyInfo* info = NULL;
//		pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
//		if ((info = notify->x.info = ScenarioEngineRequestMessageNotifyInfo_new(Dz1T("NOTIFY"), env->seq, Dz1T("info"), NULL, errp)) == NULL) ERR_OUT(errp);
//		else if ((info->data = ScenarioEngineNotifyInfoContext_clone(context, errp)) == NULL) ERR_OUT(errp);
//		else if (ScenarioEngineEnv_notifyToServer(env, notify, errp) == FALSE) ERR_OUT(errp);
//		else
//		{
//			Dz1Error_set(errp, 0);
//		}
//		pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
//	}
//	return ret;
//}

static Dz1TaskProcStatus _handle_received_scenario_notify_error(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;


	ScenarioEngineNotifyErrorArg* notify_arg = (ScenarioEngineNotifyErrorArg*)Dz1TaskSigMsg_getData(*sg);
	ScenarioEngineNotifyErrorContext* context = NULL;
	if (notify_arg == NULL || (context = notify_arg->context) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->seq++;
		ScenarioEngineRequestMessageNotify* notify = NULL;
		if ((notify = ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_error, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ScenarioEngineRequestMessageNotifyError* error = NULL;
			pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
			if ((error = notify->x.error = ScenarioEngineRequestMessageNotifyError_new(Dz1T("NOTIFY"), env->seq, notify_arg->testIdx, Dz1T("error"), NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((error->data = ScenarioEngineNotifyErrorContext_clone(context, errp)) == NULL) ERR_OUT(errp);
			else if (ScenarioEngineEnv_notifyToServer(env, notify, errp) == FALSE) ERR_OUT(errp);
			else
			{
				notify = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
		}
	}
	return ret;
}


//	ScenarioEngineNotifyErrorContext* context = (ScenarioEngineNotifyErrorContext*)Dz1TaskSigMsg_getData(*sg);
//	ScenarioEngineRequestMessageNotify* notify = NULL;
//
//	env->seq++;
//	if (context == NULL) ERR_OUT(errp);
//	else if ((notify = ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_error, NULL, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		ScenarioEngineRequestMessageNotifyError* error = NULL;
//		pthread_cleanup_push(ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
//		if ((error = notify->x.error = ScenarioEngineRequestMessageNotifyError_new(Dz1T("NOTIFY"), env->seq, Dz1T("error"), NULL, errp)) == NULL) ERR_OUT(errp);
//		else if ((error->data = ScenarioEngineNotifyErrorContext_clone(context, errp)) == NULL) ERR_OUT(errp);
//		else if (ScenarioEngineEnv_notifyToServer(env, notify, errp) == FALSE) ERR_OUT(errp);
//		else
//		{
//			Dz1Error_set(errp, 0);
//		}
//		pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageNotify_delAndSetNull, (void*)&notify);
//	}
//	return ret;
//}

static Dz1TaskProcStatus _handle_received_validate_request(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;


	ScenarioEngineValidateContextArg* validate_arg = (ScenarioEngineValidateContextArg*)Dz1TaskSigMsg_getData(*sg);
	ScenarioEngineValidateContext* context = NULL;
	if (validate_arg == NULL || (context = validate_arg->context) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->seq++;
		ScenarioEngineRequestMessageValidate* validate = NULL;
		if ((validate = ScenarioEngineRequestMessageValidate_new(NULL, env->seq, validate_arg->testIdx, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ScenarioEngineRequestMessageValidate_delAndSetNull, (void*)&validate);
			if ((validate->method = Dz1Str_clone(Dz1T("VALIDATE"), errp)) == NULL) ERR_OUT(errp);
			else if ((validate->validate = ScenarioEngineValidateContext_clone(context, errp)) == NULL) ERR_OUT(errp);
			else if (ScenarioEngineEnv_ValidateRequestToServer(env, validate, errp) == FALSE) ERR_OUT(errp);
			else
			{
				validate = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageValidate_delAndSetNull, (void*)&validate);
		}
	}
	return ret;
}

//
//	ScenarioEngineValidateContext* context = (ScenarioEngineValidateContext*)Dz1TaskSigMsg_getData(*sg);
//	ScenarioEngineRequestMessageValidate* validate = NULL;
//	if (context == NULL) ERR_OUT(errp);
//	else if ((validate = ScenarioEngineRequestMessageValidate_new(NULL, env->seq, NULL, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		pthread_cleanup_push(ScenarioEngineRequestMessageValidate_delAndSetNull, (void*)&validate);
//		if ((validate->method = Dz1Str_clone(Dz1T("VALIDATE"), errp)) == NULL) ERR_OUT(errp);
//		else if ((validate->validate = ScenarioEngineValidateContext_clone(context, errp)) == NULL) ERR_OUT(errp);
//		else if (ScenarioEngineEnv_ValidateRequestToServer(env, validate, errp) == FALSE) ERR_OUT(errp);
//		else
//		{
//			validate = NULL;
//			Dz1Error_set(errp, 0);
//		}
//
//		pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageValidate_delAndSetNull, (void*)&validate);
//	}
//	return ret;
//}

static Dz1TaskProcStatus _handle_received_scenario_done(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ScenarioEngineArg* arg = (ScenarioEngineArg*)uArg;
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;

	env->test_done_seq = env->seq;
	Dz1Thread_printf(Dz1T("TEST_DONE_SEQ = %u\n"), env->test_done_seq);

	Dz1Str testScenario = (Dz1Str)Dz1TaskSigMsg_getData(*sg);

	ScenarioEngineNotifyStateContext* context = NULL;

	if (testScenario == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((context = ScenarioEngineNotifyStateContext_new(NULL, time(NULL), Dz1T("FINISH"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineNotifyStateContext_delAndSetNull, (void*)&context);
		if ((context->testName = Dz1Str_clone(testScenario, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_post(env->tSelf, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_NOTIFY_STATE, (void*)&context, NULL, NULL, NULL, NULL, errp)).code) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ScenarioEngineNotifyStateContext_delAndSetNull, (void*)&context);
	}
	return ret;
}


bool_t ScenarioEngine_IPCMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_UI_CONFIGURE), _handle_received_ui_configure)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_NOTIFY_STATE), _handle_received_scenario_notify_state)).code)ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_NOTIFY_INFO), _handle_received_scenario_notify_info)).code)ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_VALIDATE_REQUEST), _handle_received_validate_request)).code) ERR_OUT(errp);

	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_NOTIFY_ERROR), _handle_received_scenario_notify_error)).code)ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(SCENARIO_ENGINE_RECEIVED_SCENARIO_DONE), _handle_received_scenario_done)).code)ERR_OUT(errp);
	else Dz1Error_set(errp, 0);


	return ERR_IS_SUCCESS(errp);
}
