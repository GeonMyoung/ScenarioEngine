#include "Itsk00126v2TestScenarioProc.h"
#include <Itsk00126v2TestScenarioDefJson.h>
#include <dz1_asn1.h>

#include <Dz1SockUtil.h>
// #include <Itsk00126v2TestMsgSample.h>

bool_t Itsk00126v2TestScenarioProc_start(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		bool_t is_complete = FALSE;
		env->is_run = TRUE;

		env->state = 0; // state define

		switch (s->present)
		{
		case Itsk00126v2ScenarioPresent_clientRole:
			//if (Itsk00126v2TestScenarioProcClientRole_start(arg, env, timer, s->x.clientRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			//else Dz1Error_set(errp, 0);
			break;
			break;
		case Itsk00126v2ScenarioPresent_serverRole:
			if (Itsk00126v2TestScenarioProcServerRole_start(arg, env, timer, s->x.serverRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t Itsk00126v2TestScenarioProc_stop(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("STOP"), errp) == FALSE) ERR_OUT(errp);
	else if (Itsk00126V2TestScenarioEnvUtil_notifyState(env, ITSK_00126_V1_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	Itsk00126v2TestScenarioProc_release(arg, env, timer, errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ ITSK-00144-2 Test Scenario is aborted...\n"));

	return ERR_IS_SUCCESS(errp);
}

void Itsk00126v2TestScenarioProc_release(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	env->is_run = FALSE;
	// Itsk00126v2TestMsg_clearSample(NULL);
	if (env->scenario != NULL)
	{
		switch (env->scenario->present)
		{
		case Itsk00126v2ScenarioPresent_serverRole:
			Itsk00126v2TestScenarioProcServerRole_sockMsgClear(env->tSelf);
			env->state = Itsk00126v2ScenarioServerState_initial;
		case Itsk00126v2ScenarioPresent_clientRole:
			//Itsk00126v2TestScenarioProcClientRole_sockMsgClear(env->tSelf);
			env->state = Itsk00126v2ScenarioClientState_initial;
			// sock msg clear
			break;
		default:
			break;
		}
		Itsk00126v2Scenario_delAndSetNull((void*)&env->scenario);
	}
	if (env->session != NULL) Itsk00126v2Session_delAndSetNull((void*)&env->session);

	// timer clear
	//Itsk00126V2TestScenarioTimer key = { ITSK00126_V2_TEST_SCENARIO_KEEPALIVE_TIMER };
	//Itsk00126V2TestScenarioTimer_clr(timer, &key);

	env->flags = 0;
	Dz1Thread_printf("$$$ ITSK-00144-2 Test Scenario is released...\n");
}

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

bool_t Itsk00126v2TestScenarioProc_sockProc(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer,void *_msg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* msg = NULL;
	Itsk00126v2Scenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((msg = Dz1Binary_clone((Dz1Binary*)_msg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&msg);
		bool_t is_complete = FALSE;
		switch (s->present)
		{
		case Itsk00126v2ScenarioPresent_serverRole:
			Itsk00126v2TestScenarioProcServerRole_sockProc(arg, env, timer, s->x.serverRole, Itsk00126v2ScenarioEvent_data, msg, &is_complete, errp);
			break;
		case Itsk00126v2ScenarioPresent_clientRole:
			break;
		default:break;
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}



bool_t Itsk00126v2TestScenarioProc_sendToPeer(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Itsk00126v2Session* session = NULL;
	if (src == NULL || (session = env->session) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch (session->present)
		{
		case Itsk00126v2SessionPresent_server:
		{
			Itsk00126v2ServerSession* server = NULL;
			if ((server = session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (Dz1SockUtilTxFifo_send(server->tx_fifo, server->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
			break;
		case Itsk00126v2SessionPresent_client:
		{
			Itsk00126v2ClientSession* client = NULL;
			if ((client = session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (Dz1SockUtilTxFifo_send(client->tx_fifo, client->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}
	}
	if (errp->code == 0)
	{
		if (Itsk00126V2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00126_V1_SENDER_AGENT, Dz1T("시험 대상에게 메시지를 전송합니다."), src, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	// seq ++;
	return ERR_IS_SUCCESS(errp);
}



bool_t Itsk00126v2TestScenarioProc_triggerPost(void* tSelf, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(tSelf, Dz1Task_getQueueID(tSelf), ITSK00126_V2_TEST_SCENARIO_TRIGGER)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t Itsk00126v2TestScenarioProc_trigger(Itsk00126V2TestScenarioArg* arg, Itsk00126V2TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t is_complete = FALSE;
		switch (s->present)
		{
		case Itsk00126v2ScenarioPresent_serverRole:
			if (Itsk00126v2TestScenarioProcServerRole_trigger(arg, env, timer, s->x.serverRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _task_scenarioTrigger(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Scenario* s = env->scenario;
	if (s == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Itsk00126v2TestScenarioProc_trigger(arg, env, timer, NULL);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static Dz1TaskProcStatus _notify_info(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;


	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Scenario* s = env->scenario;


	Itsk00126v2NotifyInfoArg* msg = (Itsk00126v2NotifyInfoArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Itsk00126V2TestScenarioEnvUtil_notifyInfoToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_state(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Scenario* s = env->scenario;


	Itsk00126v2NotifyStateArg* msg = (Itsk00126v2NotifyStateArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Itsk00126V2TestScenarioEnvUtil_notifyStateToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_error(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Scenario* s = env->scenario;


	Itsk00126v2NotifyErrorArg* msg = (Itsk00126v2NotifyErrorArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Itsk00126V2TestScenarioEnvUtil_notifyErrorToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _validate_request(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Itsk00126V2TestScenarioArg* arg = (Itsk00126V2TestScenarioArg*)uArg;
	Itsk00126V2TestScenarioEnv* env = (Itsk00126V2TestScenarioEnv*)uRsc;

	Itsk00126v2Scenario* s = env->scenario;


	Itsk00126v2ValidateContextArg* msg = (Itsk00126v2ValidateContextArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Itsk00126V2TestScenarioEnvUtil_validateRequestToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

DZ1_CPPLINK bool_t Itsk00126v2TestScenarioProc_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_OUT(errp);
	// else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(Itsk00126v2_TEST_SCENARIO_VALIDATE_RESPONSE), _received_validate_response)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_TRIGGER), _task_scenarioTrigger)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_NOTIFY_STATE), _notify_state)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_NOTIFY_ERROR), _notify_error)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_NOTIFY_INFO), _notify_info)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V2_TEST_SCENARIO_VALIDATE_REQUEST), _validate_request)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}