#include <Dz1SockUtil.h>
#include <dz1_web_socket.h>

#include "ScenarioEngineEnvUtil.h"
#include "ScenarioEngineMsg.h"

static Dz1TaskProcStatus _ws_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;
	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	Dz1WebSockMsgList* msgs = env->ws_msgs;

	if (env->wsock != NULL)
	{
		if (Dz1WebSocket_onReceived(env->wsock, msg, msgs, errp) == FALSE)
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Received Message Process fail. but close anyway\n");
		else
		{
			Dz1WebSockMsg* ws_msg = NULL;
			while ((ws_msg = msgs->extract(msgs, NULL)) != NULL)
			{
				u32_t log_lv = 0;
				pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void*)&ws_msg);
				Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
				switch (ws_msg->op)
				{
				case Dz1WebSockOpCode_text:
					if (log_lv & DZ1_THREAD_LOG_DEBUG)
					{
						_Dz1Thread_log("<<< Text Message Received = ");
						DZ1_DUMP(Dz1Binary, ws_msg->payload, 0);
					}
					if (ScenarioEngineEnv_jsonParseWS(env, timer, ws_msg, errp) == FALSE) ERR_OUT(errp);
					else
					{
						// seq 설정 및 response 메시지 전송

						Dz1Error_set(errp, 0);
					}
					break;
				case Dz1WebSockOpCode_max:
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "<<< 웹소켓서버에 연결하였습니다.\n");
					Dz1Task_postSimple(env->tSelf, DZ1_TASK_QUEUE_NONE, SCENARIO_ENGINE_DO_DEFAULT);
					break;
				default:
					break;
				}
				pthread_cleanup_pop(1); // (Dz1WebSockMsg_delAndSetNull, (void*)&ws_msg);
			}
		}
	}
	return SELECT_BY_ERR(errp, Dz1TaskProcStatus_processed, Dz1TaskProcStatus_error);
}


static Dz1TaskProcStatus _ws_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;
	Dz1SockUtilTransmiterSent* msg = (Dz1SockUtilTransmiterSent*)Dz1TaskSigMsg_getData(*sg);
	if (env->wsock != NULL)
	{
		if (Dz1WebSocket_onSent(env->wsock, msg, errp) == FALSE)
		{
			ERR_OUT(errp);
			Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! 웹소켓 전송이 실패했습니다.\n");
		}
	}
	return SELECT_BY_ERR(errp, Dz1TaskProcStatus_processed, Dz1TaskProcStatus_error);

}
static Dz1TaskProcStatus _ws_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	ScenarioEngineEnv* env = (ScenarioEngineEnv*)uRsc;

	Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! WebSocket 접속이 종료되었습니다.\n");
	return Dz1TaskProcStatus_error;
}


bool_t ScenarioEngine_webSockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _ws_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _ws_sent)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _ws_disconnected)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}