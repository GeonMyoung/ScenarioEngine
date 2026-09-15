#include "Itsk00126v1TestScenarioArg.h"
#include "Itsk00126v1TestScenarioEnvUtil.h"
#include "Itsk00126v1TestScenarioMsg.h"
#include "Itsk00126v1TestScenarioProc.h"

#include <Itsk00126v1TestScenarioDefJson.h>


static Dz1TaskProcStatus _scenario_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1TestScenarioArg* arg = (Itsk00126V1TestScenarioArg*)uArg;
	Itsk00126V1TestScenarioEnv* env = (Itsk00126V1TestScenarioEnv*)uRsc;

	if (Itsk00126v1TestScenarioProc_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}


	return ret;
}


static void* _parse_from_testConfiguration(Dz1Json* spec, Dz1Str testConfiguration, Dz1Str structName, Dz1Error* errp)
{
	void* ret = NULL;
	int cnt = 0;
	Dz1Json* json = NULL;
	if (spec == NULL || testConfiguration == NULL || structName == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((json = Dz1Json_new("UTF-8", spec, structName, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
		if ((sz = Dz1Json_push_stream(json, testConfiguration, Dz1STRLEN(testConfiguration), errp)) < 0) ERR_OUT(errp);
		else if (sz != Dz1STRLEN(testConfiguration)) ERR_SET_OUT(errp, EFAULT);
		else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
		else if (cnt == 0) Dz1Error_set(errp, 0);
		else
		{
			if ((ret = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1);// (Dz1Json_delAndSetNull, (void*)&json);
	}
	return ret;
}

static Itsk00126v1Scenario* _init_scenario(Itsk00126V1TestScenarioEnv* env, Dz1Str testScenario, Dz1Str testConfiguration, Dz1Error* errp)
{
	Itsk00126v1Scenario* ret = NULL;
	if (testScenario == NULL || testConfiguration == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Itsk00126v1Scenario_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Itsk00126v1Scenario_delAndSetNull, (void*)&ret);
		if (0) {}
		else if (Dz1STRCMP(testScenario, Dz1T("serverRole")) == 0)
		{
			Itsk00126v1TestConfiguration_serverRole* testConf = NULL;
			if ((testConf = (Itsk00126v1TestConfiguration_serverRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("Itsk00126v1TestConfiguration_serverRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Itsk00126v1ScenarioServerRole* server = NULL;
				pthread_cleanup_push(Itsk00126v1TestConfiguration_serverRole_delAndSetNull, (void*)&testConf);
				if ((ret->x.serverRole = server = Itsk00126v1ScenarioServerRole_new((u16_t)testConf->local_port, NULL, testConf->test_iot_im_device_sttus_info, testConf->test_iot_device_list_response_info, testConf->test_iot_device_sttus_info, testConf->test_safety_signal_list_response_info, errp)) == NULL) ERR_OUT(errp);
				else if ((server->local_center_id= Dz1Str_clone(testConf->local_center_id, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->present = Itsk00126v1ScenarioPresent_serverRole;
					Dz1Error_set(errp, 0);
				}

				if (errp->code == 0)
				{
					if (Itsk00126v1TestScenarioProcServerRole_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Itsk00126v1TestConfiguration_ServerRole_delAndSetNull, (void*)&testConf);
			}
		}
		//else if (Dz1STRCMP(testScenario, Dz1T("clientRole")) == 0)
		//{
		//	Itsk00126v1TestConfiguration_clientRole* testConf = NULL;
		//	if ((testConf = (Itsk00126v1TestConfiguration_clientRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("Itsk00126v1TestConfiguration_clientRole"), errp)) == NULL) ERR_OUT(errp);
		//	else
		//	{
		//		pthread_cleanup_push(Itsk00126v1TestConfiguration_clientRole_delAndSetNull, (void*)&testConf);
		//		if ((ret->x.clientRole = Itsk00126v1ScenarioclientRole_new(NULL, (u16_t)testConf->peer_port, testConf->test_req_link_unit_status, testConf->test_req_status, testConf->test_req_list, testConf->test_req_update_list, testConf->test_req_reset, testConf->test_session_maintain, testConf->test_tim, testConf->test_map, testConf->hb_duration, NULL, errp)) == NULL) ERR_OUT(errp);
		//		else if ((ret->x.clientRole->peer_ip = Dz1Str_clone(testConf->peer_ip, errp)) == NULL) ERR_OUT(errp);
		//		else if ((ret->x.clientRole->id = I2XTrafficSafetyDeviceSerialNo_new(0x4D, testConf->serial_no, errp)) == NULL) ERR_OUT(errp);
		//		else
		//		{
		//			ret->present = Itsk00126v1TestConfigurationPresent_clientRole;
		//			Dz1Error_set(errp, 0);
		//		}

		//		if (errp->code == 0)
		//		{
		//			if (Itsk00126v1TestScenarioProcclientRole_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
		//			else Dz1Error_set(errp, 0);
		//		}
		//		pthread_cleanup_pop(1); // (Itsk00126v1TestConfiguration_clientRole_delAndSetNull, (void*)&testConf);
		//	}
		//}
		else
		{
			ERR_SET_OUT(errp, EFAULT);
		}
		pthread_cleanup_pop(errp->code); // (Itsk00126v1Scenario_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_setup(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1TestScenarioArg* arg = (Itsk00126V1TestScenarioArg*)uArg;
	Itsk00126V1TestScenarioEnv* env = (Itsk00126V1TestScenarioEnv*)uRsc;
	Dz1Str testConfiguration = (Dz1Str)Dz1TaskSigMsg_getData(*sg);
	if (env->scenario != NULL) ERR_SET_OUT(errp, EEXIST); // scenario
	else if (testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((env->scenario = _init_scenario(env, arg->testScenario, testConfiguration, errp)) == NULL)
		{
			if (Itsk00126V1TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험설정을 실패하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			env->testIdx++;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Scenario is ready...\n"));

			if (Itsk00126V1TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험이 준비되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_stop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Itsk00126V1TestScenarioArg* arg = (Itsk00126V1TestScenarioArg*)uArg;
	Itsk00126V1TestScenarioEnv* env = (Itsk00126V1TestScenarioEnv*)uRsc;
	if (Itsk00126v1TestScenarioProc_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return ret;
}
bool_t Itsk00126v1TestScenario_commandMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_TEST_SCENARIO_START), _scenario_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_TEST_SCENARIO_STOP), _scenario_stop)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00126_V1_TEST_SCENARIO_SETUP), _scenario_setup)).code) ERR_OUT(errp);

	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
