#include "Iso14827TestHelperMsg.h"
#include "Iso14827TestHelperScenario.h"




bool_t Iso14827TestScenario_check(Iso14827TestScenario* s, Iso14827TestMsgStructAPI* msg_tbl, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (s == NULL) ERR_SET_OUT(errp, EINVAL);
	switch (s->present)
	{
	case Iso14827TestScenarioPresent_client1:
		if (Iso14827TestClient1Scenario_check(s->x.client1, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_client2:
		if (Iso14827TestClient2Scenario_check(s->x.client2, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_client1_tr:
		if (Iso14827TestClient1ScenarioTR_check(s->x.client1_tr, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_server1:
		if (Iso14827TestServer1Scenario_check(s->x.server1, msg_tbl, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_server2:
		if (Iso14827TestServer2Scenario_check(s->x.server2, msg_tbl, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_server3:
		if (Iso14827TestServer3Scenario_check(s->x.server3, msg_tbl, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;

	case Iso14827TestScenarioPresent_duo_client:
		if (Iso14827TestDuoClientScenario_check(s->x.duo_client, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Iso14827TestScenarioPresent_duo_session:
		if (Iso14827TestDuoSessionScenario_check(s->x.duo_session, msg_tbl, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct ScenarioResetParam
{
	Iso14827TestHelperArg* arg;
	Iso14827TestHelperEnv* env;
	void* timer;
} ScenarioResetParam;

static void Iso14827TestScenario_pause(void* ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ScenarioResetParam* param = (ScenarioResetParam*)ptr;
	//Iso14827TestScenario_stop(param->arg, param->env, param->timer, errp);
}


///////////////////////////////////////////////////////////////////////////////
// Install Scenario
static void Iso14827TestScenario_prepareCancel(void* ptr)
{
	ScenarioResetParam* param = (ScenarioResetParam*)ptr;
	Iso14827TestHelperEnv* env = param->env;

	Iso14827TestScenario_release(param->arg, param->env, param->timer, NULL);
	Iso14827TestScenario_delAndSetNull(&env->scenario);
	Dz1Str_delAndSetNull((void*)&env->current_test);

}

//bool_t Iso14827TestClientScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestClientRole1* s, Dz1Error* err)
bool_t Iso14827TestScenario_prepare(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)								//	switch error check
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		Iso14827TestScenario* s = NULL;
		if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->current_test = Dz1Str_clone(Dz1T("MainScenario"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ScenarioResetParam param = { arg, env, timer };
			pthread_cleanup_push(Iso14827TestScenario_prepareCancel, (void*)&param);
			switch (s->present)
			{
			case Iso14827TestScenarioPresent_client1:
				if (Iso14827TestClient1Scenario_prepare(arg, env, timer, s->x.client1, errp) == FALSE)
				{
					// 사용자에게 메시지 전달
					// arg->tMain;
				}
				else Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_client2:
				if (Iso14827TestClient2Scenario_prepare(arg, env, timer, s->x.client2, errp) == FALSE)
				{
					// notify to web
					// prepare fail!
				}
				break;
			case Iso14827TestScenarioPresent_client1_tr:
				if (Iso14827TestClient1ScenarioTR_prepare(arg, env, timer, s->x.client1_tr, errp) == FALSE)
				{
					// 사용자에게 메시지 전달
					// arg->tMain;
				}
				else Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server1:
			{
				if (Iso14827TestServer1Scenario_prepare(arg, env, timer, s->x.server1, errp) == FALSE)
				{
					// 사용자에게 메시지 전달
					// arg->tMain;
				}
				else Dz1Error_set(errp, 0);
			}
			break;
			case Iso14827TestScenarioPresent_server2:
				if (Iso14827TestServer2Scenario_prepare(arg, env, timer, s->x.server2, errp) == FALSE)
				{
					// notify to web
					// prepare fail!
				}
				else Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server3:
				if (Iso14827TestServer3Scenario_prepare(arg, env, timer, s->x.server3, errp) == FALSE)
				{
					// notify to web
					// prepare fail!
				}
				else Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_duo_client:
				if (Iso14827TestDuoClientScenario_prepare(arg, env, timer, s->x.duo_client, errp) == FALSE)
				{
					//notify to web
					// prepare fail
				}
				else Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_duo_session:
				if (Iso14827TestDuoSessionScenario_prepare(arg, env, timer, s->x.duo_session, errp) == FALSE)
				{
					// notify to web
					// prepare fail
				}
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
			pthread_cleanup_pop(errp->code);// (Iso14827TestScenario_prepareCancel, (void*)&param);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Install Scenario
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Start Scenario
bool_t Iso14827TestScenario_start(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)								//	switch error check
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		bool_t is_complete = FALSE;
		ScenarioResetParam param = { arg, env, timer };
		pthread_cleanup_push(Iso14827TestScenario_pause, (void*)&param);

		env->is_run = TRUE;
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_start(arg, env, timer, s->x.client1, &is_complete, errp) == FALSE)
			{
				// arg->tMain에게 scenario start fail 메시지 전송.
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_client2:
			if (Iso14827TestClient2Scenario_start(arg, env, timer, s->x.client2, &is_complete, errp) == FALSE)
			{
				// notify to web
				// start fail!
			}
			break;

		case Iso14827TestScenarioPresent_client1_tr:
			if (Iso14827TestClient1ScenarioTR_start(arg, env, timer, s->x.client1_tr, &is_complete, errp) == FALSE)
			{

			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server1:
			if (Iso14827TestServer1Scenario_start(arg, env, timer, s->x.server1, &is_complete, errp) == FALSE)
			{

			}
			Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server2:
			if (Iso14827TestServer2Scenario_start(arg, env, timer, s->x.server2, &is_complete, errp) == FALSE)
			{
				// notify to web
				// start fail!
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server3:
			if (Iso14827TestServer3Scenario_start(arg, env, timer, s->x.server3, &is_complete, errp) == FALSE)
			{
				// notify to web
				// start fail!
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			if (Iso14827TestDuoClientScenario_start(arg, env, timer, s->x.duo_client, &is_complete, errp) == FALSE)
			{
				//notify to web
				// start fail
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_session:
			if (Iso14827TestDuoSessionScenario_start(arg, env, timer, s->x.duo_session, &is_complete, errp) == FALSE)
			{
				// notify to web
				// start fail
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
		pthread_cleanup_pop(errp->code || is_complete); // (Iso14827TestScenario_pause, (void*)&param);
	}

	return ERR_IS_SUCCESS(errp);
}
// Start Scenario
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Test Trigger process of Scenario
bool_t Iso14827TestScenario_trigger(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Iso14827TestScenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == FALSE)
	{
		ERR_SET_OUT(errp, ENOSYS);
	}
	else
	{
		bool_t is_complete = FALSE;
		ScenarioResetParam param = { arg, env, timer };
		pthread_cleanup_push(Iso14827TestScenario_pause, (void*)&param);
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_trigger(arg, env, timer, s->x.client1, &is_complete, errp) == FALSE)
			{

			}
			break;
		case Iso14827TestScenarioPresent_client2:
			if (Iso14827TestClient2Scenario_trigger(arg, env, timer, s->x.client2, &is_complete, errp) == FALSE)
			{

			}
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			if (Iso14827TestClient1ScenarioTR_trigger(arg, env, timer, s->x.client1_tr, &is_complete, errp) == FALSE)
			{

			}
			break;
		case Iso14827TestScenarioPresent_server1:
			ERR_SET_OUT(errp, EFAULT);
			break;
		case Iso14827TestScenarioPresent_server2:
			ERR_SET_OUT(errp, EFAULT);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			if (Iso14827TestDuoClientScenario_trigger(arg, env, timer, s->x.duo_client, &is_complete, errp) == FALSE)
			{

			}
			break;
		case Iso14827TestScenarioPresent_duo_session:
			if (Iso14827TestDuoSessionScenario_trigger(arg, env, timer, s->x.duo_session, &is_complete, errp) == FALSE)
			{

			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
		pthread_cleanup_pop(errp->code || is_complete); // (Iso14827TestScenario_pause, (void*)&param);

	}

	return errp->code == 0 ? TRUE : FALSE;
}

// Test Trigger process of Scenario
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// ISO-14827 Message process of Scenario
bool_t Iso14827TestScenario_proc14827(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, int ev, void* t14827msg, Dz1Error* err)	//	switch error check
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestScenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == FALSE)
	{
		//Iso14827TestDuoSessionEvent* evt = (Iso14827TestDuoSessionEvent*)ev;
		//Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! Iso14827TestScenario_proc14827() : %s(%d) is ignored\n", Iso14827TestDuoSessionEventStrA(evt), ev);
		ERR_SET_OUT(errp, ENOSYS);
	}
	else
	{
		bool_t is_complete = FALSE;
		ScenarioResetParam param = { arg, env, timer };
		pthread_cleanup_push(Iso14827TestScenario_pause, (void*)&param);
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_proc14827(arg, env, timer, s->x.client1, (Iso14827TestClientEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// error proc 14827 ERROR
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_client2:
			if (Iso14827TestClient2Scenario_proc14827(arg, env, timer, s->x.client2, (Iso14827TestClientEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// error proc 14827 ERROR
				ERR_OUT(errp);
			}
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			if (Iso14827TestClient1ScenarioTR_proc14827(arg, env, timer, s->x.client1_tr, (Iso14827TestClientEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// error proc 14827 ERROR
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server1:
			if (Iso14827TestServer1Scenario_proc14827(arg, env, timer, s->x.server1, (Iso14827TestServerEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// error proc 14827 ERROR
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server2:
			if (Iso14827TestServer2Scenario_proc14827(arg, env, timer, s->x.server2, (Iso14827TestServerEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web
				// proc14827 error
			}
			Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server3:
			if (Iso14827TestServer3Scenario_proc14827(arg, env, timer, s->x.server3, (Iso14827TestServerEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web
				// proc14827 error
			}
			Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			if (Iso14827TestDuoClientScenario_proc14827(arg, env, timer, s->x.duo_client, (Iso14827TestClientEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web
				/// proc14827 error
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_session:
			if (Iso14827TestDuoSessionScenario_proc14827(arg, env, timer, s->x.duo_session, (Iso14827TestDuoSessionEvent)ev, t14827msg, &is_complete, errp) == FALSE)
			{
				// notify to web
				// proc 14827 error
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
		pthread_cleanup_pop(errp->code || is_complete);// (Iso14827TestScenario_reset, (void*)&param);
	}
	return ERR_IS_SUCCESS(errp);
}
// ISO-14827 Message process of Scenario
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Timeout process of Scenario
Dz1TaskProcStatus Iso14827TestScenario_timeout(void* uArg, void* uRsc, void* timer, void** tData, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperTimer* tmr = (Iso14827TestHelperTimer*)*tData;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == FALSE) {}
	else
	{
		bool_t is_complete = FALSE;
		ScenarioResetParam param = { arg, env, timer };
		pthread_cleanup_push(Iso14827TestScenario_pause, (void*)&param);
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_timeout(arg, env, timer, s->x.client1, tmr, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_client2:
			if (Iso14827TestClient2Scenario_timeout(arg, env, timer, s->x.client2, tmr->x.general, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
			}
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			if (Iso14827TestClient1ScenarioTR_timeout(arg, env, timer, s->x.client1_tr, tmr, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server1:
			if (Iso14827TestServer1Scenario_timeout(arg, env, timer, s->x.server1, tmr->x.general, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
				ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server2:
			if (Iso14827TestServer2Scenario_timeout(arg, env, timer, s->x.server2, tmr->x.general, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
			}
			else Dz1Error_set(errp, 0);
			break;

		case Iso14827TestScenarioPresent_server3:
			if (Iso14827TestServer3Scenario_timeout(arg, env, timer, s->x.server3, tmr->x.general, &is_complete, errp) == FALSE)
			{
				// notify to web!
				// timeout ERROR!
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			if (Iso14827TestDuoClientScenario_timeout(arg, env, timer, s->x.duo_client, tmr->x.general, &is_complete, errp) == FALSE)
			{
				// notify to web
				// timeout ERROR!
			}
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_session:
			if (Iso14827TestDuoSessionScenario_timeout(arg, env, timer, s->x.duo_session, tmr, &is_complete, errp) == FALSE)
			{
				// notify to web
				// timeout ERROR
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
		pthread_cleanup_pop(errp->code || is_complete); // (Iso14827TestScenario_pause, (void*)&param);
	}
	return ret;
}
// Timeout process of Scenario
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stop Scenario Testing
bool_t Iso14827TestScenario_stop(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)
{
	// stop test processing
	DZ1_ERROR_SAFE_PTR(errp, err);

	Iso14827TestScenario* s = NULL;

	if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("STOP"), errp) == FALSE) ERR_OUT(errp);
	else if (Iso14827TestHelperEnvUtil_notifyState(env, ISO14827_TEST_HELPER_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == FALSE) {}
	else
	{
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_stop(arg, env, timer, s->x.client1, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_client2:
			if (Iso14827TestClient2Scenario_stop(arg, env, timer, s->x.client2, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
			break;
		case Iso14827TestScenarioPresent_client1_tr:
			if (Iso14827TestClient1ScenarioTR_stop(arg, env, timer, s->x.client1_tr, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server1:
			if (Iso14827TestServer1Scenario_stop(arg, env, timer, s->x.server1, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server2:
			if (Iso14827TestServer2Scenario_stop(arg, env, timer, s->x.server2, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_server3:
			if (Iso14827TestServer3Scenario_stop(arg, env, timer, s->x.server3, errp) == FALSE) ERR_OUT(errp);
			break;
		case Iso14827TestScenarioPresent_duo_client:
			if (Iso14827TestDuoClientScenario_stop(arg, env, timer, s->x.duo_client, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_duo_session:
			if (Iso14827TestDuoSessionScenario_stop(arg, env, timer, s->x.duo_session, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}

		if (Iso14827TestScenario_release(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	}

	return errp->code == 0 ? TRUE : FALSE;
}
// Stop Scenario Testing
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Reset Scenario
bool_t Iso14827TestScenario_reset(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestScenario* s = NULL;

	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Iso14827TestScenario_stop(arg, env, timer, errp) == FALSE)ERR_OUT(errp);
		else
		{
			switch (s->present)
			{
			case Iso14827TestScenarioPresent_client1:
				Iso14827TestClient1Scenario_reset(s->x.client1, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_client2:
				Iso14827TestClient2Scenario_reset(s->x.client2, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_client1_tr:
				Iso14827TestClient1ScenarioTR_reset(s->x.client1_tr, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server1:
				Iso14827TestServer1Scenario_reset(s->x.server1, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server2:
				Iso14827TestServer2Scenario_reset(s->x.server2, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server3:
				Iso14827TestServer3Scenario_reset(s->x.server3, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_duo_session:
				Iso14827TestDuoSessionScenario_reset(s->x.duo_session, env);
				Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
	}
	return ERR_IS_SUCCESS(errp);
}
// Reset Scenario
///////////////////////////////////////////////////////////////////////////////

bool_t Iso14827TestScenario_release(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Dz1Error* err)
{
	// back to not initialized state : called when runtime state
	DZ1_ERROR_SAFE_PTR(errp, err);
		Iso14827TestScenario* s = NULL;
		if ((s = env->scenario) == NULL) Dz1Error_set(err, EFAULT);
		else
		{
			switch (s->present)
			{
			case Iso14827TestScenarioPresent_client1:
				Iso14827TestClient1Scenario_release(s->x.client1, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_client2:
				Iso14827TestClient2Scenario_release(s->x.client2, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_client1_tr:
				Iso14827TestClient1ScenarioTR_release(s->x.client1_tr, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server1:
				Iso14827TestServer1Scenario_release(s->x.server1, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server2:
				Iso14827TestServer2Scenario_release(s->x.server2, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_server3:
				Iso14827TestServer3Scenario_release(s->x.server3, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_duo_client:
				Iso14827TestDuoClientScenario_release(s->x.duo_client, env);
				Dz1Error_set(errp, 0);
				break;
			case Iso14827TestScenarioPresent_duo_session:
				Iso14827TestDuoSessionScenario_release(s->x.duo_session, env);
				Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EFAULT); break;
			}
			Iso14827TestScenario_delAndSetNull((void*)&env->scenario);
			env->current_test = NULL;
			env->is_run = FALSE;
		}
	return errp->code == 0 ? TRUE : FALSE;
}

void Iso14827TestScenario_status(Iso14827TestScenario* s, Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env)
{
	if (s != NULL)
	{
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:			Iso14827TestClientRole1_status(s->x.client1, arg, env); break;
		case Iso14827TestScenarioPresent_client2:			Iso14827TestClientRole2_status(s->x.client2, arg, env); break;
		case Iso14827TestScenarioPresent_client1_tr:		Iso14827TestClientRole1TR_status(s->x.client1_tr, arg, env); break;
		case Iso14827TestScenarioPresent_server1:			Iso14827TestServerRole1_status(s->x.server1, arg, env); break;
		case Iso14827TestScenarioPresent_server2:			Iso14827TestServerRole2_status(s->x.server2, arg, env); break;
		case Iso14827TestScenarioPresent_duo_client:		Iso14827TestDuoClientRole_status(s->x.duo_client, arg, env); break;
		case Iso14827TestScenarioPresent_duo_session:		Iso14827TestDuoSessionRole_status(s->x.duo_session, arg, env); break;
		}
	}
}


static Dz1TaskProcStatus _task_scenarioTrigger(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;
	if (env->scenario == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Iso14827TestScenario_trigger(arg, env, timer, NULL);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

bool_t Iso14827TestScenario_triggerPost(void* tSelf, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(tSelf, Dz1Task_getQueueID(tSelf), ISO14827_TEST_HELPER_SCENARIO_TRIGGER)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}


static Dz1TaskProcStatus _received_validate_response(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;

	Iso14827TestValidateContext* msg = (Iso14827TestValidateContext*)Dz1TaskSigMsg_getData(*sg);
	if (s == NULL || msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestScenario_validateReceived(arg, env, timer, s, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

bool_t Iso14827TestScenario_validateReceived(Iso14827TestHelperArg* arg, Iso14827TestHelperEnv* env, void* timer, Iso14827TestScenario* s, void* msg, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (s == NULL || msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t is_complete = FALSE;
		switch (s->present)
		{
		case Iso14827TestScenarioPresent_client1:
			if (Iso14827TestClient1Scenario_validateReceived(arg, env, timer, s->x.client1, msg, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827TestScenarioPresent_client2:
			break;
		case Iso14827TestScenarioPresent_server1:
			break;
		case Iso14827TestScenarioPresent_server2:
			break;
		default:
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
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

static Dz1TaskProcStatus _c2c_hook_proc(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;
	
	Iso14827TestHelperC2CHookArg* hook_arg = (Iso14827TestHelperC2CHookArg*)Dz1TaskSigMsg_getData(*sg);
	Iso14827C2CAuthMsg* msg = NULL;
	if (hook_arg == NULL || (msg = hook_arg->msg) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_Iso14827C2CAuthMsg* Gitsn_msg = NULL;
		if ((Gitsn_msg = Gitsn_Iso14827C2CAuthMsg_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Gitsn_Iso14827C2CAuthMsg_delAndSetNull, (void*)&Gitsn_msg);
			if (Iso14827C2CAuthMsg_To_Gitsn(Gitsn_msg, msg, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Asn1UTF8Str* str_u8 = NULL;
				if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_Iso14827C2CAuthMsg"), Gitsn_msg, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Binary* data = NULL;
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Iso14827TestNotifyInfoArg* arg = NULL;
						pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
						if ((arg = Iso14827TestNotifyInfoArg_new(env->testIdx, NULL,errp )) == NULL) ERR_OUT(errp);
						else
						{
							Iso14827TestNotifyInfoContext* ctx = NULL;
							pthread_cleanup_push(Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&arg);
							if ((arg->context = ctx = Iso14827TestNotifyInfoContext_gen(errp)) == NULL) ERR_OUT(errp);
							else
							{

								if ((ctx->testName = Dz1Str_clone(hook_arg->current_test, errp)) == NULL) ERR_OUT(errp);
								else if ((ctx->data = Dz1Binary_clone(data, errp)) == NULL) ERR_OUT(errp);
								else if ((ctx->dataType = Dz1Str_clone(Dz1T("JSON"), errp)) == NULL) ERR_OUT(errp);
								else
								{
									if (hook_arg->isReceived)
									{
										if ((ctx->log = Dz1Str_clone(Dz1T("수신 메시지 : "), errp)) == NULL) ERR_OUT(errp);
										else if ((ctx->sender = Dz1Str_clone(ISO14827_TEST_HELPER_SENDER_SUT, errp)) == NULL) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
									}
									else
									{
										if ((ctx->log = Dz1Str_clone(Dz1T("송신 메시지 : "), errp)) == NULL) ERR_OUT(errp);
										else if ((ctx->sender = Dz1Str_clone(ISO14827_TEST_HELPER_SENDER_AGENT, errp)) == NULL) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
									}
									ctx->time = time(NULL);
									if (errp->code == 0 && ctx != NULL)
									{
										if (Iso14827TestHelperEnvUtil_notifyInfoToMain(env, arg, errp) == FALSE) ERR_OUT(errp);
										else
										{
											arg = NULL;
											Dz1Error_set(errp, 0);
										}
									}
								}
							}

							pthread_cleanup_pop(1); // (Iso14827TestNotifyInfoArg_delAndSetNull, (void*)&arg);
						}
						
						pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
					}
					pthread_cleanup_pop(1); //(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
			}
			pthread_cleanup_pop(1); // (Gitsn_Iso14827C2CAuthMsg_delAndSetNull, (void*)&Gitsn_msg);
		}
	}
	return ret;
}


static Dz1TaskProcStatus _notify_info(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;


	Iso14827TestNotifyInfoArg* msg = (Iso14827TestNotifyInfoArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_notifyInfoToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_state(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;


	Iso14827TestNotifyStateArg* msg = (Iso14827TestNotifyStateArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_notifyStateToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_error(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;


	Iso14827TestNotifyErrorArg* msg = (Iso14827TestNotifyErrorArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_notifyErrorToMain(env,msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret; 
}

static Dz1TaskProcStatus _validate_request(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	Iso14827TestScenario* s = env->scenario;


	Iso14827TestValidateContextArg* msg = (Iso14827TestValidateContextArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Iso14827TestHelperEnvUtil_validateRequestToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}



bool_t Iso14827TestScenario_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_VALIDATE_RESPONSE), _received_validate_response)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_SCENARIO_TRIGGER), _task_scenarioTrigger)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_C2C_HOOK), _c2c_hook_proc)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_NOTIFY_STATE), _notify_state)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_NOTIFY_ERROR), _notify_error)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_NOTIFY_INFO), _notify_info)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_VALIDATE_REQUEST), _validate_request)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;

}