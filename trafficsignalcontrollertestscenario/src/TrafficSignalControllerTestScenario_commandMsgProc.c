#include "TrafficSignalControllerTestScenarioArg.h"
#include "TrafficSignalControllerTestScenarioEnvUtil.h"
#include "TrafficSignalControllerTestScenarioMsg.h"
#include "TrafficSignalControllerTestScenarioTimer.h"
#include "TrafficSignalControllerTestScenarioProc.h"

#include <Dz1SockUtil.h>
#include <TrafficSignalControllerTestMsg.h>


static Dz1TaskProcStatus _scenario_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;
	
	if (TrafficSignalControllerTestScenarioProc_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _scenario_stop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	//if (env->scenario != NULL)
	//{
	//	TrafficSignalControllerScenarioConfig_delAndSetNull((void*)&env->scenario);
	//	u8_t* b_d = "STOP";
	//	Dz1Binary notify_b = { b_d, (u32_t)strlen(b_d) };
	//	TrafficSignalControllerNotifyContext nc = { &notify_b, Dz1T("!!! 시험을 종료하였습니다.") };
	//	if (TrafficSignalControllerTestScenarioEnvUtil_notifyToMain(env, "state", &nc, errp) == FALSE) ERR_OUT(errp);
	//	Dz1Error_set(errp, 0);

	//}
	//else
	//{
	//	u8_t* b_d = "ERROR";
	//	Dz1Binary notify_b = { b_d, (u32_t)strlen(b_d) };
	//	// TrafficSignalControllerNotifyContext nc = { "ERROR", Dz1T("!!! 진행중인 시험이 없습니다.") };
	//	TrafficSignalControllerNotifyContext nc = { &notify_b, Dz1T("!!! Test Scenario is empty.") };
	//	if (TrafficSignalControllerTestScenarioEnvUtil_notifyToMain(env, "error", &nc, errp) == FALSE) ERR_OUT(errp);
	//	Dz1Error_set(errp, 0);
	//}

	if (TrafficSignalControllerTestScenarioProc_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

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

static TrafficSignalControllerScenario* _init_scenario(TrafficSignalControllerTestScenarioEnv* env, Dz1Str testScenario, Dz1Str testConfiguration, Dz1Error* errp)
{
	TrafficSignalControllerScenario* ret = NULL;
	if (testScenario == NULL || testConfiguration == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerScenario_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerScenario_delAndSetNull, (void*)&ret);
		if (0) {}
		
		TrafficSignalControllerTestConfiguration* testConf = NULL;
		if ((testConf = _parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TrafficSignalControllerTestConfiguration"), errp)) == FALSE) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestConfiguration_delAndSetNull, (void*)&testConf);
			if (0) {}
			else if ((ret->req_str = Dz1Str_clone(testConf->req_str, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ret->port = testConf->port;
				ret->cross_id = testConf->cross_id;
				Dz1Error_set(errp, 0);
			}


			if (errp->code == 0)
			{
				if (0) {}
				else if (Dz1STRCMP(testScenario, Dz1T("control")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_control;
				else if (Dz1STRCMP(testScenario, Dz1T("status")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_status;
				else if (Dz1STRCMP(testScenario, Dz1T("detector")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_detector;
				else if (Dz1STRCMP(testScenario, Dz1T("signal_phase_down")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_signal_phase_down;
				else if (Dz1STRCMP(testScenario, Dz1T("signal_phase_up")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_signal_phase_up;
				else if (Dz1STRCMP(testScenario, Dz1T("clock_down")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_clock_down;
				else if (Dz1STRCMP(testScenario, Dz1T("clock_up")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_clock_up;
				else if (Dz1STRCMP(testScenario, Dz1T("special_cmd")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_special_cmd;
				else if (Dz1STRCMP(testScenario, Dz1T("fw_upgrade_cmd")) == 0) ret->eam_type = TrafficSignalControllerRequestPresent_fw_upgrade_cmd;
				else if (Dz1STRCMP(testScenario, Dz1T("signal_phase_down_r29")) == 0) { ret->eam_type = TrafficSignalControllerRequestPresent_signal_phase_down; env->is_r29 = TRUE; }
				else ERR_SET_OUT(errp, EFAULT);
			}

			pthread_cleanup_pop(1); // (TrafficSignalControllerTestConfiguration_delAndSetNull, (void*)&testConf);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerScenario_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Dz1TaskProcStatus _scenario_setup(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	TrafficSignalControllerTestScenarioArg* arg = (TrafficSignalControllerTestScenarioArg*)uArg;
	TrafficSignalControllerTestScenarioEnv* env = (TrafficSignalControllerTestScenarioEnv*)uRsc;

	Dz1Str testConfiguration = (Dz1Str)Dz1TaskSigMsg_getData(*sg);
	if (env->scenario != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if((env->scenario = _init_scenario(env, arg->testScenario, testConfiguration, errp)) == NULL)
		{
			if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험설정을 실패하였습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else
		{
			env->testIdx++;
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Scenario is ready...\n"));

			if (TrafficSignalControllerTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험이 준비되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}


bool_t TrafficSignalControllerTestScenario_commandMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_START), _scenario_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_SETUP), _scenario_setup)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_STOP), _scenario_stop)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}