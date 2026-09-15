#include "ITSK00144_2TestScenarioArg.h"
#include "ITSK00144_2TestScenarioEnvUtil.h"
#include "ITSK00144_2TestScenarioMsg.h"
#include "ITSK00144_2TestScenarioProc.h"

#include <ITSK00144_2TestScenarioDefJson.h>


static Dz1TaskProcStatus _scenario_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	if (ITSK00144_2TestScenarioProc_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
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

static ITSK00144_2Scenario* _init_scenario(ITSK001442TestScenarioEnv* env, Dz1Str testScenario, Dz1Str testConfiguration, Dz1Error* errp)
{
	ITSK00144_2Scenario* ret = NULL;
	if (testScenario == NULL || testConfiguration == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ITSK00144_2Scenario_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK00144_2Scenario_delAndSetNull, (void*)&ret);
		if (0) {}
		else if (Dz1STRCMP(testScenario, Dz1T("serverRole")) == 0)
		{
			ITSK00144_2TestConfiguration_ServerRole* testConf = NULL;
			if ((testConf = (ITSK00144_2TestConfiguration_ServerRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("ITSK00144_2TestConfiguration_ServerRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				ITSK00144_2ScenarioServerRole* server = NULL;
				pthread_cleanup_push(ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void*)&testConf);
				if ((ret->x.serverRole = server = ITSK00144_2ScenarioServerRole_new((u16_t)testConf->local_port, testConf->test_rsp_link_unit_status, testConf->test_rsp_status, testConf->test_rsp_list, testConf->test_rsp_update_list, testConf->test_rsp_reset, testConf->test_session_maintain, testConf->hb_duration, errp)) == NULL) ERR_OUT(errp);
				else if ((server->id = I2XTrafficSafetyDeviceSerialNo_new(0x4D, testConf->serial_no, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->present = ITSK00144_2TestConfigurationPresent_serverRole;
					Dz1Error_set(errp, 0);
				}

				if (errp->code == 0)
				{
					if (ITSK00144_2TestScenarioProcServerRole_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2TestConfiguration_ServerRole_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(testScenario, Dz1T("linkUnitRole")) == 0)
		{
			ITSK00144_2TestConfiguration_LinkUnitRole* testConf = NULL;
			if ((testConf = (ITSK00144_2TestConfiguration_LinkUnitRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("ITSK00144_2TestConfiguration_LinkUnitRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void*)&testConf);
				if ((ret->x.linkUnitRole = ITSK00144_2ScenarioLinkUnitRole_new(NULL, (u16_t)testConf->peer_port, testConf->test_req_link_unit_status, testConf->test_req_status, testConf->test_req_list, testConf->test_req_update_list, testConf->test_req_reset, testConf->test_session_maintain, testConf->test_tim, testConf->test_map, testConf->hb_duration, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((ret->x.linkUnitRole->peer_ip = Dz1Str_clone(testConf->peer_ip, errp)) == NULL) ERR_OUT(errp);
				else if ((ret->x.linkUnitRole->id = I2XTrafficSafetyDeviceSerialNo_new(0x4D, testConf->serial_no, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->present = ITSK00144_2TestConfigurationPresent_linkUnitRole;
					Dz1Error_set(errp, 0);
				}

				if (errp->code == 0)
				{
					if (ITSK00144_2TestScenarioProcLinkUnitRole_sockMsgInit(env->tSelf, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull, (void*)&testConf);
			}
		}
		else
		{
			ERR_SET_OUT(errp, EFAULT);
		}
		pthread_cleanup_pop(errp->code); // (ITSK00144_2Scenario_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_setup(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;
	Dz1Str testConfiguration = (Dz1Str)Dz1TaskSigMsg_getData(*sg);
	if (env->scenario != NULL) ERR_SET_OUT(errp, EEXIST); // scenario
	else if (testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((env->scenario = _init_scenario(env, arg->testScenario, testConfiguration, errp)) == NULL)
		{
			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험설정을 실패하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			env->testIdx++;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Scenario is ready...\n"));

			if (ITSK00144_2TestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험이 준비되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_stop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;
	if (ITSK00144_2TestScenarioProc_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return ret;
}
bool_t ITSK00144_2TestScenario_commandMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_START), _scenario_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_STOP), _scenario_stop)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_SETUP), _scenario_setup)).code) ERR_OUT(errp);

	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
