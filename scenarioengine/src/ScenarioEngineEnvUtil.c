#include "ScenarioEngineEnvUtil.h"
#include"ScenarioEngineMsg.h"

#include <dz1_web_socket.h>

// Scenario Project
 #include <TrafficSignalControllerTestScenario.h>
#include <Iso14827TestHelper.h>
#include <ITSK00144_2TestScenario.h>
#include <Itsk00126v1TestScenario.h>
#include <Itsk00126v2TestScenario.h>
#include <GitsnDSRCMsgTestScenario.h>

#define SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(struct_name)\
struct_name *msg = NULL;\
for (int i = 0; i < cnt; i++)\
{\
	if ((msg = (struct_name*)Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);\
	else\
	{\
		u32_t log_lv = 0;\
		pthread_cleanup_push(struct_name##_delAndSetNull, (void*)&msg);\
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);\
		if (log_lv & DZ1_THREAD_LOG_DEBUG)\
		{\
			_Dz1Thread_log("Received Message = ");\
			struct_name##_dump(msg, 0);\
		}\
		if(struct_name##_proc(env, msg, errp) == FALSE) ERR_OUT(errp);\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(1); \
	}\
}\


static void _task_exception_proc(void* ptr, Dz1Error * reason)
{
	Dz1Thread_printf(Dz1Text("exception catch!\n"));
	ERR_OUT(reason);
}

static bool_t ScenarioEngineResponseMessageDefault_proc(ScenarioEngineEnv * env, ScenarioEngineResponseMessageDefault * msg, Dz1Error * errp)
{
	Dz1Thread_printf(Dz1T("Response received = \n"));
	ScenarioEngineResponseMessageDefault_dump(msg, 0);
	if (msg == NULL) ERR_OUT(errp);
	else if (env->test_done_seq == msg->seq)
	{

		/*if (env->tScenario != NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			Dz1Task_startCancel((void*)env->tScenario);
			Dz1Task_delAndSetNull((void*)&env->tScenario);


		}*/
if (ScenarioEngineEnv_sendTeardown(env, errp) == FALSE) ERR_OUT(errp);
else
{
	if (env->tScenario != NULL)
	{
		Dz1Task_delAndSetNull((void*)&env->tScenario);
		if (Dz1WebSocket_sendClose(env->wsock, Dz1WebSocketCloseReason_normal_close, NULL, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1WebSocket_delAndSetNull((void*)&env->wsock);
			Dz1Error_set(errp, 0);
		}
		// if (errp->code == 0) ScenarioEngine_del(env->tSelf);
	}
	else Dz1Error_set(errp, 0);
}
	}
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

static bool_t ScenarioEngineRequestMessageDefault_proc(ScenarioEngineEnv* env, ScenarioEngineRequestMessageDefault* msg, Dz1Error* errp)
{
	return ERR_IS_SUCCESS(errp);
}
static bool_t ScenarioEngineRequestMessageDescribe_proc(ScenarioEngineEnv* env, ScenarioEngineRequestMessageDescribe* msg, Dz1Error* errp)
{
	return ERR_IS_SUCCESS(errp);
}

static void* _parse_from_test_configuration(Dz1JsonSpec* spec, Dz1Str testConfiguration, Dz1Str structName, Dz1Error* errp)
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

static bool_t ScenarioEngineRequestMessageInitialize_proc(ScenarioEngineEnv* env, ScenarioEngineRequestMessageInitialize* msg, Dz1Error* errp)
{
	Dz1Binary* src = NULL;
	if ((src = msg->testScenario) == NULL || src->data == NULL || src->size == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		int cnt = 0;
		Dz1Json* json = NULL;
		ScenarioEngineInitializeContext* init_ctxt = NULL;
		if (env->spec == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((json = Dz1Json_new("UTF-8", env->spec, Dz1T("ScenarioEngineInitializeContext"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			
			ssize_t sz;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if ((sz = Dz1Json_push_stream(json, src->data, src->size, errp)) < 0) ERR_OUT(errp);
			else if (sz != src->size) ERR_SET_OUT(errp, EFAULT);
			else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
			else if (cnt == 0) Dz1Error_set(errp, 0);
			else
			{
				if ((init_ctxt = Dz1Json_read(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Str category = NULL;
					Dz1Str testScenario = NULL;
					pthread_cleanup_push(ScenarioEngineInitializeContext_delAndSetNull, (void*)&init_ctxt);
					if ((category = init_ctxt->category) == NULL) ERR_SET_OUT(errp, EFAULT);
					else if ((testScenario = init_ctxt->testScenario) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						if (0) {}

						else if (Dz1STRCMP(category, Dz1T("TrafficSignalController")) == 0)
						{
							if ((env->tScenario = TrafficSignalControllerTestScenario_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						if (0) {}
						else if (Dz1STRCMP(category, Dz1T("ITSK-00143-3-15784")) == 0 || Dz1STRCMP(category, Dz1T("ITSK-00143-3-14827")) == 0 || Dz1STRCMP(category, Dz1T("ITSK-00100-3")) == 0 || Dz1STRCMP(category, Dz1T("TechnicalRegulation1")) == 0 || Dz1STRCMP(category, Dz1T("TechnicalRegulation2")) == 0)
						{
							if ((env->tScenario = Iso14827TestHelper_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else if (Dz1STRCMP(category, Dz1T("ITSK-00144-2")) == 0)
						{
							if ((env->tScenario = ITSK001442TestScenario_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else if (Dz1STRCMP(category, Dz1T("ITSK-00126-1")) == 0)
						{
							if ((env->tScenario = Itsk00126V1TestScenario_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else if (Dz1STRCMP(category, Dz1T("ITSK-00126-2")) == 0)
						{
							if ((env->tScenario = Itsk00126V2TestScenario_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else if (Dz1STRCMP(category, Dz1T("DSRCMsgTest")) == 0)
						{
							if ((env->tScenario = GitsnDSRCMsgTestScenario_new(env->tSelf, testScenario, _task_exception_proc, NULL, errp)) == NULL) ERR_OUT(errp);
							else if ((*errp = Dz1Task_start(env->tScenario, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG | DZ1_THREAD_LOG_DEBUG)).code) ERR_OUT(errp);
							else Dz1Error_set(errp, 0);
						}
						else
						{
							// 
							ERR_SET_OUT(errp, EPERM);
							//notify error
						}
					}
					pthread_cleanup_pop(1); // (ScenarioEngineInitializeContext_delAndSetNull, (void*)&init_ctxt);
				}
			}
			pthread_cleanup_pop(1); //(Dz1Json_delAndSetNull, (void*)&json);
		}
	}

	if (errp->code == 0)
	{
		if (ScenarioEngineEnv_responseToServer(env, msg->seq, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t ScenarioEngineRequestMessageWithData_proc(ScenarioEngineEnv * env, ScenarioEngineRequestMessageWithData * msg, Dz1Error * errp)	// START || STOP || TEARDOWN ...
{
	int cnt = 0;
	Dz1Json* json = NULL;

	if (msg == NULL) ERR_OUT(errp);
	else
	{
		if (Dz1Str_cmp(msg->method, Dz1T("START")) == 0)
		{
			//if ((*errp = Dz1Task_postSimple(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_COMMAND_START)).code) ERR_OUT(errp);
			if ((*errp = Dz1Task_callSimple(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_COMMAND_START, NULL)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1Str_cmp(msg->method, Dz1T("STOP")) == 0)
		{
			// if ((*errp = Dz1Task_postSimple(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_COMMAND_STOP)).code) ERR_OUT(errp);
			if ((*errp = Dz1Task_callSimple(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_COMMAND_STOP, NULL)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, 0);

		if (errp->code == 0)
		{
			if (ScenarioEngineEnv_responseToServer(env, msg->seq, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t ScenarioEngineRequestMessageSetup_proc(ScenarioEngineEnv * env, ScenarioEngineRequestMessageSetup * msg, Dz1Error * errp)
{
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		ScenarioEngineRequestMessageSetup_dump(msg, 0);
		Dz1Str testConfiguration = NULL;
		if ((testConfiguration = msg->testConfiguration) == NULL) ERR_OUT(errp);
		else
		{
			if ((*errp = Dz1Task_post(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_COMMAND_SETUP, (void*)&testConfiguration, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

		if (errp->code == 0)
		{
			if (ScenarioEngineEnv_responseToServer(env, msg->seq, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t ScenarioEngineRequestMessageNotify_proc(ScenarioEngineEnv * env, ScenarioEngineRequestMessageNotify * msg, Dz1Error * errp)
{
	return ERR_IS_SUCCESS(errp);
}

static bool_t ScenarioEngineResponseMessageValidate_proc(ScenarioEngineEnv * env, ScenarioEngineResponseMessageValidate * msg, Dz1Error * errp)
{
	ScenarioEngineValidateContext* validate = NULL;
	if (msg == NULL) ERR_OUT(errp);
	//else if ((validate = msg->validate) == NULL) ERR_OUT(errp);
	else if ((validate = ScenarioEngineValidateContext_clone(msg->validate, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineValidateContext_delAndSetNull, (void*)&validate);
		if ((*errp = Dz1Task_post(env->tScenario, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_VALIDATE_RESPONSE, (void*)&validate, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			validate = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ScenarioEngineValidateContext_delAndSetNull, (void*)&validate);
	}
	return ERR_IS_SUCCESS(errp);
}


bool_t ScenarioEngineEnv_establishWS(ScenarioEngineEnv * env, Dz1Asn1UTF8Str * ws_server_uri, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if (0) {}
	else if ((env->wsock = Dz1WebSocket_createU(ws_server_uri, my_queue_id, TRUE, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t ScenarioEngineEnv_sendDescribe(ScenarioEngineEnv * env, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UTF8Str* describe_msg = NULL;
	if ((describe_msg = Dz1Asn1UTF8Str_newFromStr(Dz1T("{ \"method\": \"DESCRIBE\", \"seq\": 1, \"type\": \"Agent\" }"), errp)) == NULL) ERR_OUT(errp);
	else if (env == NULL || env->wsock == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&describe_msg);
		if (Dz1WebSocket_sendText(env->wsock, describe_msg, errp) == FALSE) ERR_OUT(errp);
		else
		{
			env->seq = 1;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&describe_msg);
	}

	return ERR_IS_SUCCESS(errp);
}

bool_t ScenarioEngineEnv_sendTeardown(ScenarioEngineEnv * env, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json* json = NULL;
	ScenarioEngineRequestMessageDefault* teardown = NULL;
	env->seq++;
	if ((teardown = ScenarioEngineRequestMessageDefault_new(Dz1T("TEARDOWN"), env->seq, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineRequestMessageDefault_delAndSetNull, (void*)&teardown);
		if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageDefault"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			Dz1Str src = NULL;
			if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageDefault"), (void*)teardown, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
			else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
				Dz1Asn1UTF8Str* str_u8 = NULL;
				if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
					else
					{
						Dz1Thread_printf(Dz1T("send teardown msg = \n"));
						Dz1Str_dump(src, 0);
						str_u8 = NULL;
						src = NULL;
						json = NULL;

						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
		pthread_cleanup_pop(1); // (ScenarioEngineRequestMessageDefault_delAndSetNull, (void*)&teardown);
	}


	return ERR_IS_SUCCESS(errp);
}

static struct WS_MSG_TYPE_TBL
{
	Dz1Str		struct_name;
} _ws_msg_type_tbl[] =
{
	{Dz1T("ScenarioEngineResponseMessageDefault")},
	{Dz1T("ScenarioEngineResponseMessageValidate")},
	{Dz1T("ScenarioEngineRequestMessageDefault")},
	{Dz1T("ScenarioEngineRequestMessageInitialize")},
	{Dz1T("ScenarioEngineRequestMessageDescribe")},
	{Dz1T("ScenarioEngineRequestMessageWithData")},
	{Dz1T("ScenarioEngineRequestMessageSetup")},
	{Dz1T("ScenarioEngineRequestMessageNotify")},
	{NULL}
};

bool_t ScenarioEngineEnv_jsonParseWS(ScenarioEngineEnv * env, void* timer, Dz1WebSockMsg * ws_msg, Dz1Error * errp)
{
	int cnt = 0;
	Dz1Json* json = NULL;
	Dz1Binary* payload = NULL;
	if ((payload = ws_msg->payload) == NULL) ERR_SET_OUT(errp, EFAULT);
	// 메시지 컨텍스트
	else
	{
		struct WS_MSG_TYPE_TBL* s_tbl;

		for (s_tbl = _ws_msg_type_tbl; s_tbl->struct_name != NULL; s_tbl++)
		{
			if ((json = Dz1Json_new("UTF-8", env->spec, s_tbl->struct_name, errp)) == NULL) ERR_OUT(errp);
			else
			{

				Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "!!! trying parsed struct name = %s\n", s_tbl->struct_name);
				ssize_t sz;
				pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
				if ((sz = Dz1Json_push_stream(json, payload->data, payload->size, errp)) < 0) ERR_OUT(errp);
				else if (sz != (ssize_t)payload->size) ERR_SET_OUT(errp, EFAULT);
				else if ((cnt = Dz1Json_parse(json, errp)) < 0) ERR_OUT(errp);
				else if (cnt == 0) Dz1Error_set(errp, 0);
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "!!! successed parsed struct name = %s\n", s_tbl->struct_name);
					if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineResponseMessageDefault")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineResponseMessageDefault);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineResponseMessageValidate")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineResponseMessageValidate);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageDefault")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageDefault);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageDescribe")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageDescribe);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageInitialize")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageInitialize);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageWithData")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageWithData);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageSetup")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageSetup);
					}
					else if (Dz1Str_cmp(s_tbl->struct_name, Dz1T("ScenarioEngineRequestMessageNotify")) == 0)
					{
						SCENARIO_ENGINE_WEBSOCKET_MESSAGE_PROC_MACRO(ScenarioEngineRequestMessageNotify);
					}
					else
					{
						Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "!!! ERROR : Unknown message\n");
						Dz1Error_set(errp, EPERM);
					}

					Dz1Error_set(errp, 0);
				}

				pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);

				if (errp->code == 0 && cnt > 0)
				{
					break;
				}
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}


bool_t ScenarioEngineEnv_responseToServer(ScenarioEngineEnv * env, u32_t seq, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json* json = NULL;

	u32_t log_lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);

	Dz1Thread_printf(Dz1T("Send response Message = "));
	ScenarioEngineResponseMessageDefault* rsp = NULL;
	if ((rsp = ScenarioEngineResponseMessageDefault_new(seq, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ScenarioEngineResponseMessageDefault_delAndSetNull, (void*)&rsp);
		if ((rsp->result = ScenarioEngineWebSocketResponseMessageContext_new(ScenarioEngineWebSocketStatusCode_OK, Dz1T("OK"), NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineResponseMessageDefault"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
				Dz1Str src = NULL;
				if (Dz1Json_stringify(json, Dz1T("ScenarioEngineResponseMessageDefault"), (void*)rsp, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
				else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
						else
						{
							str_u8 = NULL;
							src = NULL;
							json = NULL;
							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
			}
		}
		pthread_cleanup_pop(1); // (ScenarioEngineResponseMessageDefault_delAndSetNull, (void*)&rsp);
	}

	return ERR_IS_SUCCESS(errp);
}

bool_t ScenarioEngineEnvUtil_sendUIConfigureToServer(ScenarioEngineEnv * env, ScenarioEngineRequestMessageUIConfigure * ui_conf, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Json* json = NULL;
	u32_t log_lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
	if (ui_conf == NULL) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf(Dz1T("Send UI Message = "));
		ScenarioEngineRequestMessageUIConfigure_dump(ui_conf, 0);
		if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageUIConfigure"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Str src = NULL;
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageUIConfigure"), (void*)ui_conf, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
			else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Asn1UTF8Str* str_u8 = NULL;
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
				if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
					else
					{
						str_u8 = NULL;
						src = NULL;
						json = NULL;

						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
				pthread_cleanup_pop(1); //(Dz1Str_delAndSetNull, (void*)&src);
			}
			pthread_cleanup_pop(1); //  (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ScenarioEngineEnv_notifyToServer(ScenarioEngineEnv * env, ScenarioEngineRequestMessageNotify * notify, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json* json = NULL;
	u32_t log_lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);

	Dz1Thread_printf(Dz1T("Send notify Message = "));
	ScenarioEngineRequestMessageNotify_dump(notify, 0);

	if (notify == NULL) ERR_OUT(errp);
	else
	{
		switch (notify->present)
		{
		case ScenarioEngineRequestMessageNotifyPresent_state:
			if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageNotifyState"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
				Dz1Str src = NULL;
				if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageNotifyState"), (void*)notify->x.state, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
				else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
						else
						{
							str_u8 = NULL;
							src = NULL;
							json = NULL;

							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
			}
			break;
		case ScenarioEngineRequestMessageNotifyPresent_info:
			if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageNotifyInfo"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
				Dz1Str src = NULL;
				if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageNotifyInfo"), (void*)notify->x.info, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
				else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
						else
						{
							str_u8 = NULL;
							src = NULL;
							json = NULL;

							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
			}
			break;
		case ScenarioEngineRequestMessageNotifyPresent_error:
			if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageNotifyError"), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
				Dz1Str src = NULL;
				if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageNotifyError"), (void*)notify->x.error, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
				else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
					Dz1Asn1UTF8Str* str_u8 = NULL;
					if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
						else
						{
							str_u8 = NULL;
							src = NULL;
							json = NULL;

							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					}
					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
				}
				pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
			}
			break;
		default:
			ERR_SET_OUT(errp, EPERM);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t ScenarioEngineEnv_ValidateRequestToServer(ScenarioEngineEnv * env, ScenarioEngineRequestMessageValidate * validate, Dz1Error * err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json* json = NULL;
	u32_t log_lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);

	if (validate == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Send Validate Request = \n"));
		ScenarioEngineRequestMessageValidate_dump(validate, 4);
		if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, env->spec, Dz1T("ScenarioEngineRequestMessageValidate"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
			Dz1Str src = NULL;
			if (Dz1Json_stringify(json, Dz1T("ScenarioEngineRequestMessageValidate"), (void*)validate, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
			else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
				Dz1Asn1UTF8Str* str_u8 = NULL;
				if ((str_u8 = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
					if (Dz1WebSocket_sendText(env->wsock, str_u8, errp) == FALSE) ERR_OUT(errp);
					else
					{
						str_u8 = NULL;
						src = NULL;
						json = NULL;

						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
				}
				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
			}
			pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
		}
	}
	return ERR_IS_SUCCESS(errp);
}
