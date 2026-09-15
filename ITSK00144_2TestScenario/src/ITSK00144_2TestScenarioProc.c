#include "ITSK00144_2TestScenarioProc.h"
#include <ITSK00144_2TestMsg.h>
#include <ITSK00144_2TestScenarioDefJson.h>
#include <dz1_asn1.h>

#include <Dz1SockUtil.h>
#include <ITSK00144_2TestMsgSample.h>

bool_t ITSK00144_2TestScenarioProc_start(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		bool_t is_complete = FALSE;
		env->is_run = TRUE;

		env->state = 0; // state define

		switch (s->present)
		{
		case ITSK00144_2ScenarioPresent_linkUnitRole:
			if (ITSK00144_2TestScenarioProcLinkUnitRole_start(arg, env, timer, s->x.linkUnitRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
			break;
		case ITSK00144_2ScenarioPresent_serverRole:
			if (ITSK00144_2TestScenarioProcServerRole_start(arg, env, timer, s->x.serverRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t ITSK00144_2TestScenarioProc_stop(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("STOP"), errp) == FALSE) ERR_OUT(errp);
	else if (ITSK00144_2TestScenarioEnvUtil_notifyState(env, ITSK_00144_2_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	ITSK00144_2TestScenarioProc_release(arg, env, timer, errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ ITSK-00144-2 Test Scenario is aborted...\n"));

	return ERR_IS_SUCCESS(errp);
}

void ITSK00144_2TestScenarioProc_release(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	env->is_run = FALSE;
	// ITSK00144_2TestMsg_clearSample(NULL);
	if (env->scenario != NULL)
	{
		switch (env->scenario->present)
		{
		case ITSK00144_2ScenarioPresent_serverRole:
			ITSK00144_2TestScenarioProcServerRole_sockMsgClear(env->tSelf);
			env->state = ITSK00144_2ScenarioServerState_initial;
		case ITSK00144_2ScenarioPresent_linkUnitRole:
			ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgClear(env->tSelf);
			env->state = ITSK00144_2ScenarioClientState_initial;
			// sock msg clear
			break;
		default:
			break;
		}
		ITSK00144_2Scenario_delAndSetNull((void*)&env->scenario);
	}
	if (env->session != NULL) ITSK00144_2Session_delAndSetNull((void*)&env->session);

	// timer clear
	ITSK001442TestScenarioTimer key = { ITSK_00144_2_TEST_SCENARIO_KEEPALIVE_TIMER };
	ITSK001442TestScenarioTimer_clr(timer, &key);

	env->flags = 0;
	env->received_seq = 0;
	env->send_seq = 0;
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

bool_t ITSK00144_2TestScenarioProc_sockProc(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer,void *_msg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* msg = (Dz1Binary*)_msg;
	ITSK00144_2Scenario* s = NULL;
	ITSK00144_2ProtocolFrame* f = NULL;

	if (msg == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
 	else if ((f = ITSK00144_2ProtocolFrame_decode(msg, errp)) == NULL)
	{
		bool_t is_complete = FALSE;
		switch (s->present)
		{
		case ITSK00144_2ScenarioPresent_serverRole:
			break;
		case ITSK00144_2ScenarioPresent_linkUnitRole:
			ITSK00144_2TestScenarioProcLinkUnitRole_sockProc(arg, env, timer, s->x.linkUnitRole, ITSK00144_2ScenarioEvent_data2, msg, &is_complete, errp);
			break;
		default:break;
		}
	}
	else
	{
		bool_t is_complete = FALSE;
		ITSK00144_2ProtocolFrameContext* ctx = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
		if ((ctx = ITSK00144_2ProtocolFrameContext_decode(f->context, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1UTF8Str* str_u8 = NULL;

			if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("ITSK00144_2ProtocolFrameContext"), ctx, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Binary* data = NULL;
				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
					if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00144_2_SENDER_SUT, Dz1T("시험 대상으로부터 수신한 메시지 컨텍스트 입니다."), data, Dz1T("JSON"), errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
				}
				pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
			}


			pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);
			
			switch (s->present)
			{
			case ITSK00144_2ScenarioPresent_serverRole:
				if (ctx->opcode == ITSK00144_2DataPresent_hb)
				{
					ITSK00144_2TestScenarioProcServerRole_sockProc(arg, env, timer, s->x.serverRole, ITSK00144_2ScenarioEvent_heartbeat, ctx, &is_complete, errp);
				}
				else
				{
					ITSK00144_2TestScenarioProcServerRole_sockProc(arg, env, timer, s->x.serverRole, ITSK00144_2ScenarioEvent_data, ctx, &is_complete, errp);
				}
				break;
			case ITSK00144_2ScenarioPresent_linkUnitRole:
				if (ctx->opcode == ITSK00144_2DataPresent_ack)
				{
					ITSK00144_2TestScenarioProcLinkUnitRole_sockProc(arg, env, timer, s->x.linkUnitRole, ITSK00144_2ScenarioEvent_heartbeat, ctx, &is_complete, errp);
				}
				else ITSK00144_2TestScenarioProcLinkUnitRole_sockProc(arg, env, timer, s->x.linkUnitRole, ITSK00144_2ScenarioEvent_data, ctx, &is_complete, errp);
				break;
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&f);
	}
	return ERR_IS_SUCCESS(errp);
}



bool_t ITSK00144_2TestScenarioProc_sendToPeer(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ITSK00144_2Session* session = NULL;
	if (src == NULL || (session = env->session) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch (session->present)
		{
		case ITSK00144_2SessionPresent_server:
		{
			ITSK00144_2ServerSession* server = NULL;
			if ((server = session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (Dz1SockUtilTxFifo_send(server->tx_fifo, server->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
			break;
		case ITSK00144_2SessionPresent_client:
		{
			ITSK00144_2ClientSession* client = NULL;
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
		if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, env->current_test, ITSK_00144_2_SENDER_AGENT, Dz1T("시험 대상에게 메시지를 전송합니다."), src, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	// seq ++;
	return ERR_IS_SUCCESS(errp);
}



bool_t ITSK00144_2TestScenarioProc_triggerPost(void* tSelf, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(tSelf, Dz1Task_getQueueID(tSelf), ITSK00144_2_TEST_SCENARIO_TRIGGER)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioProc_trigger(ITSK001442TestScenarioArg* arg, ITSK001442TestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2Scenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t is_complete = FALSE;
		switch (s->present)
		{
		case ITSK00144_2ScenarioPresent_serverRole:
			if (ITSK00144_2TestScenarioProcServerRole_trigger(arg, env, timer, s->x.serverRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
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

	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	ITSK00144_2Scenario* s = env->scenario;
	if (s == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		ITSK00144_2TestScenarioProc_trigger(arg, env, timer, NULL);
		Dz1Error_set(errp, 0);
	}
	return ret;
}


DZ1_CPPLINK bool_t ITSK00144_2TestScenarioProc_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_OUT(errp);
	// else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_VALIDATE_RESPONSE), _received_validate_response)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_TRIGGER), _task_scenarioTrigger)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}