#include "Iso14827TestHelperArg.h"
#include "Iso14827TestHelperEnv.h"
#include "Iso14827TestHelperMsg.h"
#include "Iso14827TestHelperScenario.h"

#include <Iso14827TestHelper.h>

#include <TechnicalRegulation1MsgStructAPI.h>
#include <TechnicalRegulation2MsgStructAPI.h>


///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_INIT_SCENARIO
static Dz1TaskProcStatus _task_initScenario(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;


	if (env->scenario == NULL) ERR_SET_OUT(errp, EEXIST);
	/*else if (Iso14827TestScenario_check(env->config->scenario, arg->msg_api, errp) == FALSE) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestScenarioSetup_delAndSetNull, (void*)&env->config);
		if (Iso14827TestScenario_prepare(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_printf("!!!!!!!!! _task_initSCeanrio !!!! \n");
		pthread_cleanup_pop(errp->code);
	}*/
	return ret;
}

//bool_t Conformance1Test_initScenario(void* task, Conformance1TestScenario* scenario, Conformance1TestCB event_cb, void* event_cb_ptr, Dz1Error* err)
//{
//	DZ1_ERROR_SAFE_PTR(errp, err);
//
//	return errp->code == 0 ? TRUE : FALSE;
//}
// CONFORMANCE1_TEST_INIT_SCENARIO
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_SCENARIO_START
static Dz1TaskProcStatus _task_scenarioStart(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (env->scenario == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EEXIST);
	else if (Iso14827TestScenario_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Task Start!!!!!!!!\n");
		Dz1Error_set(errp, 0);
	}
	return ret;
}

// CONFORMANCE1_TEST_SCENARIO_START
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_SCENARIO_STOP
static Dz1TaskProcStatus _task_scenarioStop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (Iso14827TestScenario_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else
	{
	}

	return ret;
}

bool_t Conformance1Test_scenarioStop(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return errp->code == 0 ? TRUE : FALSE;
}
// CONFORMANCE1_TEST_SCENARIO_STOP
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_SCENARIO_RESET
static Dz1TaskProcStatus _task_scenarioReset(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

bool_t Conformance1Test_scenarioReset(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	return errp->code == 0 ? TRUE : FALSE;
}
// CONFORMANCE1_TEST_SCENARIO_RESET
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_RELEASE_SCENARIO
static Dz1TaskProcStatus _task_releaseScenario(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

bool_t Conformance1Test_releaseScenario(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return errp->code == 0 ? TRUE : FALSE;
}
// CONFORMANCE1_TEST_RELEASE_SCENARIO
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFORMANCE1_TEST_DEBUG_STATUS
static Dz1TaskProcStatus _test_debugStatus(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}

bool_t Conformance1Test_debugStatus(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	return errp->code == 0 ? TRUE : FALSE;
}
// CONFORMANCE1_TEST_DEBUG_STATUS
///////////////////////////////////////////////////////////////////////////////


static Dz1TaskProcStatus _scenario_start(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;

	if (env->scenario == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EEXIST);
	else if (Iso14827TestScenario_start(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _scenario_stop(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;
	if (Iso14827TestScenario_stop(arg, env, timer, errp) == FALSE) ERR_OUT(errp);
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

static bool_t _check_scenario(Iso14827TestHelperEnv* env, Dz1Str testScenario, void* _testConf, Dz1Error* errp)
{
	if (testScenario == NULL || _testConf == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		//if (0) {}
		//else if (Dz1STRCMP(Dz1T("prj2_ldmClient2rsu"), testScenario) == 0)
		//{
		//	Prj2TestConfiguration_ldmClient2rsu* testConf = (Prj2TestConfiguration_ldmClient2rsu*)_testConf;
		//	/*	Dz1Str		my_domain;
		//		Dz1Str		peer_domain;
		//		Dz1Str		peer_ip;
		//		s64_t		peer_port;
		//		Dz1Str		user;
		//		Dz1Str		pass;
		//		bool_t		test_login_invalid;
		//		bool_t		test_session_maintain;
		//		bool_t		test_normal_pub_pvd;
		//		bool_t		test_login_duplicate;
		//		bool_t		test_invalid_sub;
		//		bool_t		test_subs_cancel;
		//		bool_t		test_pub_retry;*/
		//	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;

		//	if (testConf->my_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->my_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'LDM Domain 이름 (sender)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid my_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'대상 RSU Domain 이름 (destination)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_ip == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_ip) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'접속할 RSU IP 주소' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_ip\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_port < 0 || testConf->peer_port > 65535)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("잘못된 '접속할 RSU Port 번호' 입력입니다. (0 ~ 65535)\n 입력된 '접속할 RSU Port 번호' : %lld\n"), testConf->peer_port);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_port = %d (0~65535)\n"), testConf->peer_port);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else
		//	{
		//		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Test Configuration checked..."));
		//		Prj2TestConfiguration_ldmClient2rsu_dump(testConf, 0);
		//		Dz1Error_set(errp, 0);
		//	}
		//}
		//else if (Dz1STRCMP(Dz1T("prj2_rsuClient2ldm"), testScenario) == 0)
		//{
		//	Prj2TestConfiguration_rsuClient2ldm* testConf = (Prj2TestConfiguration_rsuClient2ldm*)_testConf;
		//	/*	Dz1Str		my_domain;
		//		Dz1Str		peer_domain;
		//		Dz1Str		peer_ip;
		//		s64_t		peer_port;
		//		Dz1Str		user;
		//		Dz1Str		pass;
		//		bool_t		test_login_invalid;
		//		bool_t		test_session_maintain;
		//		bool_t		test_normal_pub_map;
		//		bool_t		test_normal_pub_spat;
		//		bool_t		test_normal_pub_sdsm;
		//		bool_t		test_login_duplicate;
		//		bool_t		test_invalid_sub;
		//		bool_t		test_subs_cancel;
		//		bool_t		test_pub_retry;*/
		//	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;

		//	if (testConf->my_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->my_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'RSU Domain 이름 (sender)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid my_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'대상 LDM Domain 이름 (destination)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_ip == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_ip) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'접속할 LDM IP 주소' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_ip\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_port < 0 || testConf->peer_port > 65535)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("잘못된 '접속할 LDM Port 번호' 입력입니다. (0 ~ 65535)\n 입력된 '접속할 RSU Port 번호' : %lld\n"), testConf->peer_port);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_port = %d (0~65535)\n"), testConf->peer_port);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else
		//	{
		//		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Test Configuration checked..."));
		//		Prj2TestConfiguration_rsuClient2ldm_dump(testConf, 0);
		//		Dz1Error_set(errp, 0);
		//	}
		//}
		//else if (Dz1STRCMP(Dz1T("prj2_rsuServer2ldm"), testScenario) == 0)
		//{
		//	Prj2TestConfiguration_rsuServer2ldm* testConf = (Prj2TestConfiguration_rsuServer2ldm*)_testConf;
		//	/*Dz1Str		my_domain;
		//	Dz1Str		peer_domain;
		//	u16_t		local_port;
		//	bool_t		test_login_retry;
		//	bool_t		test_sub_pvd;
		//	bool_t		test_sub_retry;
		//	bool_t		test_invalid_pub;*/

		//	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;
		//	if (testConf->my_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->my_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'RSU Domain 이름 (sender)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid my_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'대상 LDM Domain 이름 (destination)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->local_port < 0 || testConf->local_port > 65535)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("잘못된 '접속 대기 수신 Port 번호' 입력입니다. (0 ~ 65535)\n 입력된 '접속 대기 수신 Port 번호' : %lld\n"), testConf->local_port);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid local_port = %d (0~65535)\n"), testConf->local_port);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	
		//	else if (!(testConf->test_pvd))
		//	{
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("최소 한가지의 메시지 검증 시험을 선택하세요"), NULL, errp) == FALSE) ERR_OUT(errp);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->test_pvd && testConf->subs_timeout_s < 180)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("서브스크립션 만료 시간' 입력입니다. (최소 180초)\n 입력된 '서브스크립션 만료 시간' : %lld\n"), testConf->subs_timeout_s);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid subs_timeout_s = %d (0~65535)\n"), testConf->subs_timeout_s);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else
		//	{
		//		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Test Configuration checked..."));
		//		Prj2TestConfiguration_rsuServer2ldm_dump(testConf, 0);
		//		Dz1Error_set(errp, 0);
		//	}
		//}
		//else if (Dz1STRCMP(Dz1T("prj2_ldmServer2rsu"), testScenario) == 0)
		//{
		//	Prj2TestConfiguration_ldmServer2rsu* testConf = (Prj2TestConfiguration_ldmServer2rsu*)_testConf;
		//	/*Dz1Str		my_domain;
		//	Dz1Str		peer_domain;
		//	u16_t		local_port;
		//	bool_t		test_login_retry;
		//	bool_t		test_sub_map;
		//	bool_t		test_sub_spat;
		//	bool_t		test_sub_sdsm;
		//	bool_t		test_sub_retry;
		//	bool_t		test_invalid_pub;*/

		//	Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;
		//	if (testConf->my_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->my_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'LDM Domain 이름 (sender)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid my_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->peer_domain == NULL || Dz1STRCMP(Dz1T(""), testConf->peer_domain) == 0)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("'대상 RSU Domain 이름 (destination)' 입력을 확인하세요."));
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid peer_domain\n"));
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (testConf->local_port < 0 || testConf->local_port > 65535)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("잘못된 '접속 대기 수신 Port 번호' 입력입니다. (0 ~ 65535)\n 입력된 '접속 대기 수신 Port 번호' : %lld\n"), testConf->local_port);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid local_port = %d (0~65535)\n"), testConf->local_port);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if (!(testConf->test_map || testConf->test_spat || testConf->test_sdsm))
		//	{
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), Dz1T("최소 한가지의 메시지 검증 시험을 선택하세요"), NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else if ((testConf->test_map || testConf->test_spat || testConf->test_sdsm) && testConf->subs_timeout_s < 180)
		//	{
		//		char log[128];
		//		sprintf(log, Dz1T("서브스크립션 만료 시간' 입력입니다. (최소 180초)\n 입력된 '서브스크립션 만료 시간' : %lld\n"), testConf->subs_timeout_s);
		//		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR : Test Configuration error : invalid subs_timeout_s = %d (0~65535)\n"), testConf->subs_timeout_s);
		//		if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestProcessStatusCodeStrA(code), log, NULL, errp) == FALSE) ERR_OUT(errp);
		//		else Dz1Error_set(errp, 0);
		//		ERR_SET_OUT(errp, EFAULT);
		//	}
		//	else
		//	{
		//		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Test Configuration checked..."));
		//		Prj2TestConfiguration_ldmServer2rsu_dump(testConf, 0);
		//		Dz1Error_set(errp, 0);
		//	}
		// }
	}
	return ERR_IS_SUCCESS(errp);
}


static Iso14827TestClientConnection* _init_client_connection(Dz1Str myDomain, Dz1Str ipaddr, u16_t peerport, Dz1Str user, Dz1Str pass, Dz1Error* errp)
{
	Iso14827TestClientConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = Iso14827TestClientActive_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->peer = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	return ret;
}


static Iso14827TestClientConnection* _init_duo_client_connection(Dz1Str myDomain, Dz1Str myDomain2, Dz1Str ipaddr, u16_t peerport, Dz1Str user, Dz1Str pass, Dz1Str user2, Dz1Str pass2, Dz1Error* errp)
{
	Iso14827TestClientConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = Iso14827TestClientActive_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->peer = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain2, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->userid = Dz1Asn1UTF8Str_newFromStr(user2, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->passwd = Dz1Asn1UTF8Str_newFromStr(pass2, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	return ret;
}

static Iso14827TestConnection* _init_active_connection(Dz1Str ipaddr, u16_t peerport, Dz1Error* errp)
{
	Iso14827TestConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestConnection_new(Iso14827TestConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestConnection_delAndSetNull, (void*)&ret);
	return ret;
}

static Dz1Str sample_authinfo = Dz1T(" ");
static Iso14827TestAccount* _init_account(Dz1Str user, Dz1Str pass, Dz1Error* errp)
{
	Iso14827TestAccount* ret = NULL;
	pthread_cleanup_push(Iso14827TestAccount_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestAccount_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->authinfo = Dz1Asn1UTF8Str_newFromStr(sample_authinfo, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestAccount_delAndSetNull, (void*)&ret);
	return ret;
}

static void Iso14827Time_fillNow(Iso14827Time* t)
{
	static s32_t year;
	static s32_t month;
	static s32_t day;
	//static Iso14827TimeZone zone = 9;   // KST (+9), 필요 없으면 제거

	time_t now = time(NULL);
	struct tm lt;

	localtime_s(&lt, &now);

	year = lt.tm_year + 1900;
	month = lt.tm_mon + 1;
	day = lt.tm_mday;

	t->year = &year;
	t->month = &month;
	t->day = &day;

	t->h = lt.tm_hour;
	t->m = lt.tm_min;
	t->s = lt.tm_sec;

	t->frac = NULL;      // fractional second 미사용
	t->zone = NULL;     // 타임존 사용 안 하면 NULL
}
static void Iso14827Time_fillTomorrow(Iso14827Time* t)
{
	static s32_t year;
	static s32_t month;
	static s32_t day;
	//static Iso14827TimeZone zone = 9;   // KST (+9), 필요 없으면 NULL

	time_t now = time(NULL);
	struct tm lt;

	localtime_s(&lt, &now);

	/* 날짜 기준으로 하루 증가 */
	lt.tm_mday += 1;
	mktime(&lt);   // 정규화 (월/년 자동 보정)

	year = lt.tm_year + 1900;
	month = lt.tm_mon + 1;
	day = lt.tm_mday;

	t->year = &year;
	t->month = &month;
	t->day = &day;

	t->h = lt.tm_hour;
	t->m = lt.tm_min;
	t->s = lt.tm_sec;

	t->frac = NULL;
	t->zone = NULL;
}


////////////////////////////////////////////////////////////////////////////////
// Registered Subscription Type
static Iso14827RegisteredContinuousDeclare(sub_data_reg_cont, 15);																		// PERIOD = 15
static SubscribeSpecTypeReg			 sub_data_reg_info = { SubscribeSpecTypeRegPresent_continuous, { &sub_data_reg_cont } };		// CONTINUOUS
static SubscribeSpecTypeRegistered	 sub_data_registered = { TRUE, &sub_data_reg_info, Iso14827SubscriptionCancel_dataNotNeeded };	// PERIODIC
static SubscribeSpecType			 sub_type_reg = { SubscribeSpecTypePresent_registered, { &sub_data_registered } };
// Registered Subscription Type
////////////////////////////////////////////////////////////////////////////////
static SubscribeSpecType sub_type_single = { SubscribeSpecTypePresent_single, { NULL } };
static SubscribeSpecEntry sample_invalid_sub = { Dz1T("1.0.15784.99.99.99"), 5, &sub_type_single };
static SubscribeSpecEntry sample_invalid_sub_14827 = { Dz1T("1.0.14827.99.99.99"), 5, &sub_type_single };

static SubscribeSpecEntry sample_single_sub_comm_tx_pdu = { Dz1T("1.0.15784.1.0.1"), 5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_comm_rx_pdu = { Dz1T("1.0.15784.1.0.2"), 5, &sub_type_single };

static SubscribeSpecEntry sample_reg_sub_comm_tx_pdu = { Dz1T("1.0.15784.1.0.1"), 5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_comm_rx_pdu = { Dz1T("1.0.15784.1.0.2"), 5, &sub_type_reg };

static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_comm_tx_pdu = { Dz1T("1.0.15784.1.0.1") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_comm_rx_pdu = { Dz1T("1.0.15784.1.0.2") };

static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_comm_tx_pdu_tr = { Dz1T("1.0.15784.2.0.1") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_comm_rx_pdu_tr = { Dz1T("1.0.15784.2.0.2") };

static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_incident_detection_info = { Dz1T("1.0.14827.1.1.0") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_incident_termination_info = { Dz1T("1.0.14827.1.1.1") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_incident_detection_video_file_info_provide = { Dz1T("1.0.14827.1.1.2") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_control_state_info = { Dz1T("1.0.14827.1.1.3") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_sensor_state_info= { Dz1T("1.0.14827.1.1.4") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_moving_object= { Dz1T("1.0.14827.1.1.5") };

static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_current_link_state = { Dz1T("1.0.14827.1.0.1") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_event_identity = { Dz1T("1.1.0.14827.1.0.2")};
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_incident_identity = { Dz1T("11.0.14827.1.0.3") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_incident_conditions = { Dz1T("1.0.14827.1.0.4") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_roadway_surface_status = { Dz1T("1.0.14827.1.0.5") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_weather_information = { Dz1T("1.0.14827.1.0.6") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_link_roadway_geometry = { Dz1T("1.0.14827.1.0.7") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_probe_vehicle_detection = { Dz1T("1.0.14827.1.0.8") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_detector_collection = { Dz1T("1.0.14827.1.0.9") };
static Iso14827TestServerRoleSubsEntry sample_server_sub_entry_extention_comm_pdu = { Dz1T("1.0.14827.1.1.0") };


static SubscribeSpecEntry sample_single_sub_entry_incident_detection_info = { Dz1T("1.0.14827.1.1.0"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_incident_termination_info = { Dz1T("1.0.14827.1.1.1"), 5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_incident_detection_video_file_info_provide = { Dz1T("1.0.14827.1.1.2"), 5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_control_state_info = { Dz1T("1.0.14827.1.1.3"), 5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_sensor_state_info = { Dz1T("1.0.14827.1.1.4"), 5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_moving_object = { Dz1T("1.0.14827.1.1.5"), 5, &sub_type_single };

static SubscribeSpecEntry sample_single_sub_entry_current_link_state = { Dz1T("1.0.14827.1.0.1"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_event_identity = { Dz1T("1.0.14827.1.0.2"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_incident_identity = { Dz1T("1.0.14827.1.0.3"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_incident_conditions = { Dz1T("1.0.14827.1.0.4"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_roadway_surface_status = { Dz1T("1.0.14827.1.0.5"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_weather_information = { Dz1T("1.0.14827.1.0.6"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_link_roadway_geometry = { Dz1T("1.0.14827.1.0.7"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_probe_vehicle_detection = { Dz1T("1.0.14827.1.0.8"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_detector_collection = { Dz1T("1.0.14827.1.0.9"),  5, &sub_type_single };
static SubscribeSpecEntry sample_single_sub_entry_extention_comm_pdu = { Dz1T("1.0.14827.1.1.0"),  5, &sub_type_single };

static SubscribeSpecEntry sample_reg_sub_entry_current_link_state = { Dz1T("1.0.14827.1.0.1"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_event_identity = { Dz1T("1.0.14827.1.0.2"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_incident_identity = { Dz1T("1.0.14827.1.0.3"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_incident_conditions = { Dz1T("1.0.14827.1.0.4"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_roadway_surface_status = { Dz1T("1.0.14827.1.0.5"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_weather_information = { Dz1T("1.0.14827.1.0.6"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_link_roadway_geometry = { Dz1T("1.0.14827.1.0.7"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_probe_vehicle_detection = { Dz1T("1.0.14827.1.0.8"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_detector_collection = { Dz1T("1.0.14827.1.0.9"),  5, &sub_type_reg };
static SubscribeSpecEntry sample_reg_sub_entry_extention_comm_pdu = { Dz1T("1.0.14827.1.1.0"),  5, &sub_type_reg };

static SubscribeSpecEntry sample_reg_sub_tr1= { Dz1T("1.0.14827.1.0.1"), 5, &sub_type_reg };


static bool_t _insert_server_sub_entry_to_list(Iso14827TestServerRoleSubsList* dst, Iso14827TestServerRoleSubsEntry* src, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Iso14827TestServerRoleSubsEntry* entry = NULL;
		if ((entry = Iso14827TestServerRoleSubsEntry_clone(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Iso14827TestServerRoleSubsEntry_delAndSetNull, (void*)&entry);
			if ((*errp = dst->add(dst, entry)).code) ERR_OUT(errp);
			else
			{
				entry = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Iso14827TestServerRoleSubsEntry_delAndSetNull, (void*)&entry);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _insert_entry_to_sub_list(SubscribeSpecList* list, SubscribeSpecEntry* entry, Dz1Error* errp)
{
	if (list == NULL || entry == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		SubscribeSpecEntry* e = NULL;
		if ((e = SubscribeSpecEntry_clone(entry, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(SubscribeSpecEntry_delAndSetNull, (void*)&e);
			if ((*errp = list->add(list, e)).code) ERR_OUT(errp);
			else
			{
				e = NULL;
				Dz1Error_set(errp, 0);
			}

			pthread_cleanup_pop(1); // (SubscribeSpecEntry_delAndSetNull, (void*)&e);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Iso14827TestScenario* _init_scenario(Iso14827TestHelperEnv* env, Dz1Str testScenario, Dz1Str testConfiguration, Dz1Error* errp)
{
	Iso14827TestScenario* ret = NULL;
	if (env == NULL || testScenario == NULL || testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Iso14827TestScenario_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Iso14827TestScenario_delAndSetNull, (void*)&ret);

		if (0) {}
		else if (Dz1STRCMP(Dz1T("centerClient2rse"), testScenario) == 0)
		{
			// RSE-통합교통관제시스템 구간 RSE 정보 제공 시험 (BSM)
			PolicePrj4TestConfiguration_centerClient2rse* testConf = NULL;
			Iso14827TestClientRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (PolicePrj4TestConfiguration_centerClient2rse*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("PolicePrj4TestConfiguration_centerClient2rse"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.client1 = scenario = Iso14827TestClientRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (testConf->test_invalid_sub)
					{
						if ((scenario->subs_invalid_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_invalid_list, &sample_invalid_sub, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_normal_pub || testConf->test_bsm)
					{
						if ((scenario->subs_normal_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_comm_rx_pdu, errp) == FALSE) ERR_OUT(errp);
						else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_centerClient2rse, NULL, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set->x.centerClient2rse = PolicePrj4ValidateSet_centerClient2rse_new(testConf->test_bsm, errp)) == NULL) ERR_OUT(errp);
						else
						{
							Dz1Error_set(errp, 0);
						}
					}
					if (testConf->test_subs_cancel)
					{
						if ((scenario->subs_cancel = SubscribeSpecEntry_clone(&sample_reg_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_retry)
					{
						if ((scenario->subs_pub_retry = SubscribeSpecEntry_clone(&sample_reg_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					scenario->test_session = testConf->test_session;
					scenario->test_login_invalid = testConf->test_login_invalid;
					scenario->test_login_duplicate = testConf->test_login_duplicate;
					scenario->test_session_maintain = testConf->test_session_maintain;
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->test_normal_pub = testConf->test_normal_pub;
					ret->present = Iso14827TestScenarioPresent_client1;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (PolicePrj4TestConfiguration_ldmClient2rsu_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("rseServer2center"), testScenario) == 0)
		{

			PolicePrj4TestConfiguration_rseServer2center* testConf = NULL;
			Iso14827TestServerRole3* scenario = NULL;
			if (0) {}
			else if ((testConf = (PolicePrj4TestConfiguration_rseServer2center*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("PolicePrj4TestConfiguration_rseServer2center"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server3 = scenario = Iso14827TestServerRole3_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;
						scenario->subs_cancel_reason = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						if (testConf->test_bsm)
						{
							if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_rseServer2center, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set->x.rseServer2center = PolicePrj4ValidateSet_rseServer2center_new(testConf->test_bsm, errp)) == NULL) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						ret->present = Iso14827TestScenarioPresent_server3;
					}
				}
				pthread_cleanup_pop(1); // (PolicePrj4TestConfiguration_rseServer2center_delAndSetNull, (void*)&testConf);
			}
		}

		else if (Dz1STRCMP(Dz1T("rseClient2center"), testScenario) == 0)
		{
			// RSE-통합교통관제시스템 구간 RSE 정보 제공 시험 (BSM)
			PolicePrj4TestConfiguration_rseClient2center* testConf = NULL;
			Iso14827TestClientRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (PolicePrj4TestConfiguration_rseClient2center*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("PolicePrj4TestConfiguration_rseClient2center"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.client1 = scenario = Iso14827TestClientRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (testConf->test_invalid_sub)
					{
						if ((scenario->subs_invalid_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_invalid_list, &sample_invalid_sub, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_normal_pub || testConf->test_map || testConf->test_rsa || testConf->test_tim)
					{
						if ((scenario->subs_normal_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_comm_tx_pdu, errp) == FALSE) ERR_OUT(errp);
						else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_rseClient2center, NULL, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set->x.rseClient2center = PolicePrj4ValidateSet_rseClient2center_new(testConf->test_map, testConf->test_rsa, testConf->test_tim, errp)) == NULL) ERR_OUT(errp);
						else
						{
							Dz1Error_set(errp, 0);
						}
					}
					if (testConf->test_subs_cancel)
					{
						if ((scenario->subs_cancel = SubscribeSpecEntry_clone(&sample_reg_sub_comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_retry)
					{
						if ((scenario->subs_pub_retry = SubscribeSpecEntry_clone(&sample_reg_sub_comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					scenario->test_session = testConf->test_session;
					scenario->test_login_invalid = testConf->test_login_invalid;
					scenario->test_login_duplicate = testConf->test_login_duplicate;
					scenario->test_session_maintain = testConf->test_session_maintain;
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->test_normal_pub = testConf->test_normal_pub;
					ret->present = Iso14827TestScenarioPresent_client1;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (PolicePrj4TestConfiguration_rseClient2center_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("centerServer2rse"), testScenario) == 0)
		{

			PolicePrj4TestConfiguration_centerServer2rse* testConf = NULL;
			Iso14827TestServerRole3* scenario = NULL;
			if (0) {}
			else if ((testConf = (PolicePrj4TestConfiguration_centerServer2rse*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("PolicePrj4TestConfiguration_centerServer2rse"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server3 = scenario = Iso14827TestServerRole3_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;
						scenario->subs_cancel_reason = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						if (testConf->test_map || testConf->test_rsa || testConf->test_tim)
						{
							if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_centerServer2rse, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set->x.centerServer2rse = PolicePrj4ValidateSet_centerServer2rse_new(testConf->test_map, testConf->test_rsa, testConf->test_tim, errp)) == NULL) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						ret->present = Iso14827TestScenarioPresent_server3;
					}
				}
				pthread_cleanup_pop(1); // (PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("signalserverServer2center"), testScenario) == 0)
		{

			PolicePrj4TestConfiguration_signalserverServer2center* testConf = NULL;
			Iso14827TestServerRole3* scenario = NULL;
			if (0) {}
			else if ((testConf = (PolicePrj4TestConfiguration_signalserverServer2center*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("PolicePrj4TestConfiguration_signalserverServer2center"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server3 = scenario = Iso14827TestServerRole3_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;
						scenario->subs_cancel_reason = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						if (testConf->test_spat || testConf->test_tls)
						{
							if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_signalserverServer2center, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set->x.signalserverServer2center = PolicePrj4ValidateSet_signalserverServer2center_new(testConf->test_spat, testConf->test_tls, errp)) == NULL) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						ret->present = Iso14827TestScenarioPresent_server3;
					}
				}
				pthread_cleanup_pop(1); // (PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull, (void*)&testConf);
			}
		}

		else if (Dz1STRCMP(Dz1T("itsk-00100-3-serverRole"), testScenario) == 0)
		{

			ITSK00100_3TestConfigurationServerRole* testConf = NULL;
			Iso14827TestServerRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (ITSK00100_3TestConfigurationServerRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("ITSK00100_3TestConfigurationServerRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server1 = scenario = Iso14827TestServerRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						// scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;
						if ((scenario->test_subs = Iso14827TestServerRoleSubsList_gen(errp)) == NULL) ERR_OUT(errp);
						else
						{

							if (testConf->test_sub_incident_detection_info)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_incident_detection_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_sub_incident_termination_info)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_incident_termination_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_sub_incident_detection_video_file_info_provide)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_incident_detection_video_file_info_provide, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_sub_control_state_info)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_control_state_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_sub_sensor_state_info)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_sensor_state_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_sub_moving_object)
							{
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_moving_object, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
						}

						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						ret->present = Iso14827TestScenarioPresent_server1;
					}
				}
				pthread_cleanup_pop(1); // (ITSK00100_3TestConfigurationServerRole_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("itsk-00100-3-clientRole"), testScenario) == 0)
		{
			ITSK00100_3TestConfigurationClientRole* testConf = NULL;
			Iso14827TestClientRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (ITSK00100_3TestConfigurationClientRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("ITSK00100_3TestConfigurationClientRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.client1 = scenario = Iso14827TestClientRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (testConf->test_invalid_sub)
					{
						if ((scenario->subs_invalid_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_invalid_list, &sample_invalid_sub, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_incident_detection_info || testConf->test_pub_incident_termination_info || testConf->test_pub_incident_detection_video_file_info_provide || testConf->test_pub_control_state_info || testConf->test_pub_sensor_state_info || testConf->test_pub_moving_object)
					{
						if ((scenario->subs_normal_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_itsk00100_3c2cClient, NULL, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set->x.itsk00100_3c2cClient = ITSK00100_3ValidateSet_c2cClient_gen(errp)) == NULL) ERR_OUT(errp);
						else
						{
							if(testConf->test_pub_incident_detection_info)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_incident_detection_info = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_incident_detection_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_incident_termination_info)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_incident_termination_info = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_incident_termination_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_incident_detection_video_file_info_provide)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_incident_detection_video_file_info_provide = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_incident_detection_video_file_info_provide, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_control_state_info)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_control_state_info = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_control_state_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_sensor_state_info)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_sensor_state_info = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_sensor_state_info, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_moving_object)
							{
								scenario->validate_set->x.itsk00100_3c2cClient->test_pub_moving_object = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_moving_object, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
						}
					}
					if (testConf->test_subs_cancel)
					{
						if ((scenario->subs_cancel = SubscribeSpecEntry_clone(&sample_reg_sub_comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_retry)
					{
						if ((scenario->subs_pub_retry = SubscribeSpecEntry_clone(&sample_reg_sub_comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					scenario->test_session = testConf->test_session;
					scenario->test_login_invalid = testConf->test_login_invalid;
					scenario->test_login_duplicate = testConf->test_login_duplicate;
					scenario->test_session_maintain = testConf->test_session_maintain;
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->test_normal_pub = testConf->test_normal_pub;
					ret->present = Iso14827TestScenarioPresent_client1;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (ITSK00100_3TestConfigurationClientRole_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("TechnicalRegulation1-clientRole1"), testScenario) == 0)
		{
			TechnicalRegulation1TestConfiguration_clientRole1* testConf = NULL;
			Iso14827TestClientRole1TR* scenario = NULL;
			if (0) {}
			else if ((testConf = (TechnicalRegulation1TestConfiguration_clientRole1*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulation1TestConfiguration_clientRole1"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.client1_tr = scenario = Iso14827TestClientRole1TR_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (testConf->test_invalid_sub)
					{
						if ((scenario->subs_invalid_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_invalid_list, &sample_invalid_sub_14827, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_current_link_state || testConf->test_pub_event_identity|| testConf->test_pub_incident_identity|| testConf->test_pub_incident_conditions || testConf->test_pub_roadway_surface_status|| testConf->test_pub_weather_information || testConf->test_pub_link_roadway_geometry || testConf->test_pub_probe_vehicle_detection || testConf->test_pub_detector_collection || testConf->test_pub_extention_comm_pdu)
					{
						if ((scenario->subs_normal_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_technical_regulation1_clientRole1, NULL, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set->x.technical_regulation1_clientRole1 = TechnicalRegulation1ValidateSet_clientRole1_gen(errp)) == NULL) ERR_OUT(errp);
						else
						{
							if (testConf->test_pub_current_link_state)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_current_link_state = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_current_link_state, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_event_identity)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_event_identity = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_event_identity, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_incident_identity)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_incident_identity = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_incident_identity, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_incident_conditions)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_incident_conditions = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_incident_conditions, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_roadway_surface_status)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_roadway_surface_status = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_roadway_surface_status, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_weather_information)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_weather_information = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_weather_information, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_link_roadway_geometry)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_link_roadway_geometry = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_link_roadway_geometry, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_probe_vehicle_detection)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_probe_vehicle_detection = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_probe_vehicle_detection, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_detector_collection)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_detector_collection = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_detector_collection, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_extention_comm_pdu)
							{
								scenario->validate_set->x.technical_regulation1_clientRole1->test_pub_extention_comm_pdu = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_entry_extention_comm_pdu, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
						}
					}
					if (testConf->test_subs_cancel)
					{
						if ((scenario->subs_cancel = SubscribeSpecEntry_clone(&sample_reg_sub_tr1, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_retry)
					{
						if ((scenario->subs_pub_retry = SubscribeSpecEntry_clone(&sample_reg_sub_tr1, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					scenario->test_session = testConf->test_session;
					scenario->test_login_invalid = testConf->test_login_invalid;
					scenario->test_login_duplicate = testConf->test_login_duplicate;
					scenario->test_session_maintain = testConf->test_session_maintain;
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->test_normal_pub = testConf->test_normal_pub;
					ret->present = Iso14827TestScenarioPresent_client1_tr;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("TechnicalRegulation1-serverRole1"), testScenario) == 0)
		{

			TechnicalRegulation1TestConfiguration_serverRole1* testConf = NULL;
			Iso14827TestServerRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (TechnicalRegulation1TestConfiguration_serverRole1*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulation1TestConfiguration_serverRole1"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server1 = scenario = Iso14827TestServerRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						// scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;

						/*if (testConf->test_sub_current_link_state || testConf->test_sub_event_identity || testConf->test_sub_incident_identity || testConf->test_sub_incident_conditions || testConf->test_sub_roadway_surface_status || testConf->test_sub_weather_information || testConf->test_sub_link_roadway_geometry || testConf->test_sub_probe_vehicle_detection || testConf->test_sub_detector_collection || testConf->test_sub_extention_comm_pdu)*/
						if(testConf->test_normal_sub)
						{

							if ((scenario->test_subs = Iso14827TestServerRoleSubsList_gen(errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_technical_regulation1_serverRole1, NULL,errp )) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set->x.technical_regulation1_serverRole1 = TechnicalRegulation1ValidateSet_serverRole1_gen(errp)) == NULL) ERR_OUT(errp);
							else
							{

								// if (testConf->test_sub_current_link_state)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_current_link_state = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_current_link_state, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_event_identity)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_event_identity = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_event_identity, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_incident_identity)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_incident_identity = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_incident_identity, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_incident_conditions)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_incident_conditions = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_incident_conditions, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_roadway_surface_status)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_roadway_surface_status = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_roadway_surface_status, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_weather_information)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_weather_information = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_weather_information, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_link_roadway_geometry)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_link_roadway_geometry = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_link_roadway_geometry, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_probe_vehicle_detection)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_probe_vehicle_detection = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_probe_vehicle_detection, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_detector_collection)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_detector_collection = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_detector_collection, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
								// if (testConf->test_sub_extention_comm_pdu)
								// {
								// 	scenario->validate_set->x.technical_regulation1_serverRole1->test_sub_extention_comm_pdu = TRUE;
								 	if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_extention_comm_pdu, errp) == FALSE) ERR_OUT(errp);
								// 	else Dz1Error_set(errp, 0);
								// }
							}
						}
						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						ret->present = Iso14827TestScenarioPresent_server1;
					}
				}
				pthread_cleanup_pop(1); // (TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(Dz1T("TechnicalRegulation2-clientRole1"), testScenario) == 0)
		{
			TechnicalRegulation2TestConfiguration_clientRole1* testConf = NULL;
			Iso14827TestClientRole1TR* scenario = NULL;
			if (0) {}
			else if ((testConf = (TechnicalRegulation2TestConfiguration_clientRole1*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulation2TestConfiguration_clientRole1"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.client1_tr = scenario = Iso14827TestClientRole1TR_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (testConf->test_invalid_sub)
					{
						if ((scenario->subs_invalid_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_invalid_list, &sample_invalid_sub_14827, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_comm_tx_pdu || testConf->test_pub_comm_rx_pdu)
					{
						if ((scenario->subs_normal_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_technical_regulation1_clientRole1, NULL, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->validate_set->x.technical_regulation1_clientRole1 = TechnicalRegulation1ValidateSet_clientRole1_gen(errp)) == NULL) ERR_OUT(errp);
						else
						{
							if (testConf->test_pub_comm_tx_pdu)
							{
								scenario->validate_set->x.technical_regulation2_clientRole1->test_pub_comm_tx_pdu = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_comm_tx_pdu, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
							if (testConf->test_pub_comm_rx_pdu)
							{
								scenario->validate_set->x.technical_regulation2_clientRole1->test_pub_comm_rx_pdu = TRUE;
								if (_insert_entry_to_sub_list(scenario->subs_normal_list, &sample_single_sub_comm_rx_pdu, errp) == FALSE) ERR_OUT(errp);
								else Dz1Error_set(errp, 0);
							}
						}
					}
					if (testConf->test_subs_cancel)
					{
						if ((scenario->subs_cancel = SubscribeSpecEntry_clone(&sample_reg_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}

					if (testConf->test_pub_retry)
					{
						if ((scenario->subs_pub_retry = SubscribeSpecEntry_clone(&sample_reg_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					scenario->test_session = testConf->test_session;
					scenario->test_login_invalid = testConf->test_login_invalid;
					scenario->test_login_duplicate = testConf->test_login_duplicate;
					scenario->test_session_maintain = testConf->test_session_maintain;
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->test_normal_pub = testConf->test_normal_pub;
					ret->present = Iso14827TestScenarioPresent_client1_tr;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull, (void*)&testConf);
			}
			}
		else if (Dz1STRCMP(Dz1T("TechnicalRegulation2-serverRole1"), testScenario) == 0)
		{

			TechnicalRegulation1TestConfiguration_serverRole1* testConf = NULL;
			Iso14827TestServerRole1* scenario = NULL;
			if (0) {}
			else if ((testConf = (TechnicalRegulation1TestConfiguration_serverRole1*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulation1TestConfiguration_serverRole1"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void*)&testConf);
				if (_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				else if ((ret->x.server1 = scenario = Iso14827TestServerRole1_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else
					{
						// scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;

						/*if (testConf->test_sub_current_link_state || testConf->test_sub_event_identity || testConf->test_sub_incident_identity || testConf->test_sub_incident_conditions || testConf->test_sub_roadway_surface_status || testConf->test_sub_weather_information || testConf->test_sub_link_roadway_geometry || testConf->test_sub_probe_vehicle_detection || testConf->test_sub_detector_collection || testConf->test_sub_extention_comm_pdu)*/
						if (testConf->test_normal_sub)
						{

							if ((scenario->test_subs = Iso14827TestServerRoleSubsList_gen(errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set = Iso14827TestValidateSet_new(Iso14827TestValidateSetPresent_technical_regulation2_serverRole1, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((scenario->validate_set->x.technical_regulation2_serverRole1 = TechnicalRegulation2ValidateSet_serverRole1_gen(errp)) == NULL) ERR_OUT(errp);
							else
							{

								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_comm_tx_pdu_tr, errp) == FALSE) ERR_OUT(errp);
							
								if (_insert_server_sub_entry_to_list(scenario->test_subs, &sample_server_sub_entry_comm_rx_pdu_tr, errp) == FALSE) ERR_OUT(errp);
								
							}
						}
						scenario->test_session = testConf->test_session;
						scenario->test_login_retry = testConf->test_login_retry;
						scenario->test_request_retry = testConf->test_sub_retry;
						scenario->test_invalid_pub = testConf->test_invalid_pub;

						ret->present = Iso14827TestScenarioPresent_server1;
					}
				}
				pthread_cleanup_pop(1); // (TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-serverRole2")) == 0 || Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-serverRole2"))==0)
		{
			TechnicalRegulationTestConfiguration_serverRole2* testConf = NULL;
			Iso14827TestServerRole2* scenario = NULL;

			if ((testConf = (TechnicalRegulationTestConfiguration_serverRole2*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulationTestConfiguration_serverRole2"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestConnection* connection = NULL;
				pthread_cleanup_push(TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void*)&testConf);
				// if((_check_scenario(env, testScenario, testConf, errp) == FALSE) ERR_OUT(errp);
				if ((ret->x.server2 = scenario = Iso14827TestServerRole2_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					connection->x.passive = (u16_t)testConf->local_port;
					if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
					else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
					else if (testConf->test_total == FALSE) ERR_SET_OUT(errp, EFAULT);
					else
					{
						scenario->subs_cancel_reason = Iso14827PublicationMgmt_terminateDataNoLongerAvailable;
						if (testConf->subs_timeout_s == 0) scenario->subs_timeout_s = 180;
						else scenario->subs_timeout_s = (u32_t)testConf->subs_timeout_s;
						ret->present = Iso14827TestScenarioPresent_server2;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-clientRole2")) == 0 || Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-clientRole2")) == 0)
		{
			TechnicalRegulationTestConfiguration_clientRole2* testConf = NULL;
			Iso14827TestClientRole2* scenario = NULL;

			if ((testConf = (TechnicalRegulationTestConfiguration_clientRole2*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulationTestConfiguration_clientRole2"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestClientConnection* connection = NULL;
				pthread_cleanup_push(TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void*)&testConf);
				if ((ret->x.client2 = scenario = Iso14827TestClientRole2_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = _init_client_connection(testConf->my_domain, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->subs_total_list = SubscribeSpecList_gen(errp)) == NULL) ERR_OUT(errp);
				
				else
				{
					if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-clientRole2")) == 0)
					{
						if (0) {}
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_current_link_state, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_event_identity, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_incident_identity, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_incident_conditions, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_roadway_surface_status, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_weather_information, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_link_roadway_geometry, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_probe_vehicle_detection, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_detector_collection, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_entry_extention_comm_pdu, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-clientRole2")) == 0)
					{
						if (0) {}
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_comm_tx_pdu, errp) == FALSE) ERR_OUT(errp);
						else if (_insert_entry_to_sub_list(scenario->subs_total_list, &sample_reg_sub_comm_rx_pdu, errp) == FALSE) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					
					scenario->subs_cancel_reason = Iso14827SubscriptionCancel_dataNotNeeded;
					scenario->expireTime = (u32_t)testConf->expire_time;
					ret->present = Iso14827TestScenarioPresent_client2;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-duoClientRole")) == 0 || Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-duoClientRole")) == 0)
		{
			TechnicalRegulationTestConfiguration_duoClientRole* testConf = NULL;
			Iso14827TestDuoClientRole* scenario = NULL;

			if ((testConf = (TechnicalRegulationTestConfiguration_duoClientRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulationTestConfiguration_duoClientRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				Iso14827TestClientConnection* connection = NULL;
				pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void*)&testConf);
				if ((ret->x.duo_client = scenario = Iso14827TestDuoClientRole_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->connection = connection = _init_duo_client_connection(testConf->my_domain1, testConf->my_domain2, testConf->peer_ip, (u16_t)testConf->peer_port, testConf->user1, testConf->pass1, testConf->user2, testConf->pass2, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_domain, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->subs_duo = SubscribeSpecDuo_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-duoClientRole")) == 0)
					{
						if (0) {}
						else if ((scenario->subs_duo->session1 = SubscribeSpecEntry_clone(&sample_single_sub_entry_current_link_state, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->subs_duo->session2 = SubscribeSpecEntry_clone(&sample_single_sub_entry_event_identity, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-duoClientRole")) == 0)
					{
						if (0) {}
						else if ((scenario->subs_duo->session1 = SubscribeSpecEntry_clone(&sample_single_sub_comm_tx_pdu, errp)) == NULL) ERR_OUT(errp);
						else if ((scenario->subs_duo->session2 = SubscribeSpecEntry_clone(&sample_single_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					ret->present = Iso14827TestScenarioPresent_duo_client;
					Dz1Error_set(errp, 0);

				}
				pthread_cleanup_pop(1); // (TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull, (void*)&testConf);
			}
		}
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-duoSessionRole")) == 0 || Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-duoSessionRole")) == 0)
		{
			TechnicalRegulationTestConfiguration_duoSessionRole* testConf = NULL;
			Iso14827TestDuoSessionRole* scenario = NULL;

			if ((testConf = (TechnicalRegulationTestConfiguration_duoSessionRole*)_parse_from_testConfiguration(env->spec, testConfiguration, Dz1T("TechnicalRegulationTestConfiguration_duoSessionRole"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void*)&testConf);
				if ((ret->x.duo_session = scenario = Iso14827TestDuoSessionRole_gen(errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->my_domain = Dz1Asn1UTF8Str_newFromStr(testConf->my_domain, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_server_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_server_domain, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->c_peer_server = _init_active_connection(testConf->peer_ip, (u16_t)testConf->peer_server_port, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->c_account = _init_account(testConf->user, testConf->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->c_sub = SubscribeSpecEntry_clone(&sample_single_sub_comm_rx_pdu, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->peer_client_domain = Dz1Asn1UTF8Str_newFromStr(testConf->peer_client_domain, errp)) == NULL) ERR_OUT(errp);
				else if ((scenario->s_peer_client = _init_active_connection(testConf->peer_ip, (u16_t)testConf->peer_client_port, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->present = Iso14827TestScenarioPresent_duo_session;
					Dz1Error_set(errp, 0);

				}
				pthread_cleanup_pop(1); // (TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull, (void*)&testConf);
			}
		}

		else
		{
			ERR_SET_OUT(errp, EFAULT);
			// 시나리오가 없음
		}
		pthread_cleanup_pop(errp->code); // (Iso14827TestScenario_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Iso14827TestMsgStructAPI* _get_msg_api(Dz1Str testScenario, Dz1Error* errp)
{
	Iso14827TestMsgStructAPI* ret = NULL;
	if (testScenario == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1STRCMP(testScenario, Dz1T("prj2_ldmClient2rsu")) == 0 || Dz1STRCMP(testScenario, Dz1T("prj2_rsuClient2ldm")) == 0)
			ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("prj2_ldmServer2rsu")) == 0) ret = TechnicalRegulation2MsgTx;
		else if (Dz1STRCMP(testScenario, Dz1T("prj2_rsuServer2ldm")) == 0) ret = TechnicalRegulation2MsgRx;

		else if (Dz1STRCMP(testScenario, Dz1T("prj4_ldmClient2ig")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("prj4_igClient2ldm")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("prj4_igServer2ldm")) == 0) ret = TechnicalRegulation2MsgTx;
		else if (Dz1STRCMP(testScenario, Dz1T("prj4_ldmServer2ig")) == 0) ret = TechnicalRegulation2MsgRx;


		else if (Dz1STRCMP(testScenario, Dz1T("centerClient2rse")) == 0) ret = TechnicalRegulation2MsgRx_itsk;
		else if (Dz1STRCMP(testScenario, Dz1T("rseServer2center")) == 0) ret = TechnicalRegulation2MsgRx_itsk;

		else if (Dz1STRCMP(testScenario, Dz1T("rseClient2center")) == 0) ret = TechnicalRegulation2MsgTx_itsk;
		else if (Dz1STRCMP(testScenario, Dz1T("centerServer2rse")) == 0) ret = TechnicalRegulation2MsgTx_itsk;

		else if (Dz1STRCMP(testScenario, Dz1T("signalserverServer2center")) == 0) ret = TechnicalRegulation1_PolicePrj4C2CMsgSet;

		else if (Dz1STRCMP(testScenario, Dz1T("itsk-00100-3-serverRole")) == 0) ret = ITSK00100_3MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("itsk-00100-3-clientRole")) == 0) ret = ITSK00100_3MsgSet;

		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-clientRole1")) == 0) ret = TechnicalRegulation1MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-serverRole1")) == 0) ret = TechnicalRegulation1MsgSet;

		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-clientRole1")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-serverRole1")) == 0) ret = TechnicalRegulation2MsgSet;

		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-clientRole2")) == 0) ret = TechnicalRegulation1MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-serverRole2")) == 0) ret = TechnicalRegulation1MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-duoClientRole")) == 0) ret = TechnicalRegulation1MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation1-duoSessionRole")) == 0) ret = TechnicalRegulation1MsgSet;

		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-clientRole2")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-serverRole2")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-duoClientRole")) == 0) ret = TechnicalRegulation2MsgSet;
		else if (Dz1STRCMP(testScenario, Dz1T("TechnicalRegulation2-duoSessionRole")) == 0) ret = TechnicalRegulation2MsgSet;

		else ERR_SET_OUT(errp, EFAULT);
	}
	return ret;
}


static Dz1TaskProcStatus _scenario_setup(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Iso14827TestHelperArg* arg = (Iso14827TestHelperArg*)uArg;
	Iso14827TestHelperEnv* env = (Iso14827TestHelperEnv*)uRsc;


	Dz1Str testConfiguration = (Dz1Str)Dz1TaskSigMsg_getData(*sg);

	if (env->scenario != NULL) ERR_SET_OUT(errp, EEXIST); // scenario
	else if (testConfiguration == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		env->testIdx++;
		if ((env->scenario = _init_scenario(env, arg->testScenario, testConfiguration, errp)) == NULL)
		{
			Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR: Scenario initalize fail: %s\n"), Iso14827TestProcessStatusCodeStrA(code));

			if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestNotifyContextPresentStrA(code), Dz1T("시나리오 초기화에 실패하였습니다! 시험 환경 설정을 확인하세요."), NULL, errp) == FALSE) ERR_OUT(errp);
			else  ERR_SET_OUT(errp, EFAULT);
		}
		else if (Iso14827TestScenario_prepare(arg, env, timer, errp) == FALSE)
		{
			Iso14827TestProcessStatusCode code = Iso14827TestProcessStatusCode_TEST_CONFIGURATION_ERROR;
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, Dz1T("!!! ERROR: Scenario initalize fail: %s\n"), Iso14827TestProcessStatusCodeStrA(code));

			if (Iso14827TestHelperEnvUtil_notifyError(env, NULL, code, Iso14827TestNotifyContextPresentStrA(code), Dz1T("시나리오 초기화에 실패하였습니다! 시험 환경 설정을 확인하세요."), NULL, errp) == FALSE) ERR_OUT(errp);
			else  ERR_SET_OUT(errp, EFAULT);
		}
		else if ((arg->msg_api = _get_msg_api(arg->testScenario, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Scenario is ready...\n"));
			if (Iso14827TestHelperEnvUtil_notifyInfo(env, NULL, NULL, Dz1T("시험이 준비되었습니다."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

bool_t Iso14827TestHelper_commandMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_START), _scenario_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_STOP), _scenario_stop)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ISO14827_TEST_HELPER_SETUP), _scenario_setup)).code) ERR_OUT(errp);

	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
