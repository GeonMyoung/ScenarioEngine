#include "GitsnDSRCMsgTestScenarioArg.h"
#include "GitsnDSRCMsgTestScenarioEnvUtil.h"
#include "GitsnDSRCMsgTestScenarioMsg.h"
#include "GitsnDSRCMsgTestScenarioProc.h"

#include <GitsnDSRCMsgTestScenarioDefJson.h>


static Dz1TaskProcStatus _scenario_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	if (GitsnDSRCMsgTestScenarioProc_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
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

static GitsnDSRCMsgScenario* _init_scenario(GitsnDSRCMsgTestScenarioEnv* env, Dz1Str testScenario, Dz1Str testConfiguration, Dz1Error* errp)
{
	GitsnDSRCMsgScenario* ret = NULL;
	if (testScenario == NULL || testConfiguration == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnDSRCMsgScenario_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnDSRCMsgScenario_delAndSetNull, (void*)&ret);
		if (0) {}
		else if (Dz1STRCMP(testScenario, Dz1T("DSRCMsgTest")) == 0)
		{
			GitsnDSRCMsgTestConfiguration* testConf = NULL;
			if ((testConf = (GitsnDSRCMsgTestConfiguration*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("GitsnDSRCMsgTestConfiguration"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(GitsnDSRCMsgTestConfiguration_delAndSetNull, (void*)&testConf);
				
				ret->local_port = (u16_t)testConf->local_port;
				ret->test_map = testConf->test_map;
				ret->test_spat = testConf->test_spat;
				ret->test_bsm = testConf->test_bsm;
				ret->test_eva = testConf->test_eva;
				ret->test_pvd = testConf->test_pvd;
				ret->test_rsa = testConf->test_rsa;
				ret->test_rtcm = testConf->test_rtcm;	
				ret->test_srm = testConf->test_srm;
				ret->test_ssm = testConf->test_ssm;
				ret->test_tim = testConf->test_tim;
				ret->test_psm = testConf->test_psm;
				ret->test_sdsm = testConf->test_sdsm;
				ret->test_tls = testConf->test_tls;
				Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (GitsnDSRCMsgTestConfiguration_delAndSetNull, (void*)&testConf);
			}
		}
		else
		{
			ERR_SET_OUT(errp, EFAULT);
		}
		pthread_cleanup_pop(errp->code); // (GitsnDSRCMsgScenario_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_setup(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;
	Dz1Str testConfiguration = (Dz1Str)Dz1TaskSigMsg_getData(*sg);
	if (env->scenario != NULL) ERR_SET_OUT(errp, EEXIST); // scenario
	else if (testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((env->scenario = _init_scenario(env, arg->testScenario, testConfiguration, errp)) == NULL)
		{
			if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험설정을 실패하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			env->testIdx++;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Scenario is ready...\n"));

			if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험이 준비되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _scenario_stop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;
	if (GitsnDSRCMsgTestScenarioProc_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Error_set(errp, 0);
	}
	return ret;
}
bool_t GitsnDSRCMsgTestScenario_commandMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_START), _scenario_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_STOP), _scenario_stop)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_SETUP), _scenario_setup)).code) ERR_OUT(errp);

	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
