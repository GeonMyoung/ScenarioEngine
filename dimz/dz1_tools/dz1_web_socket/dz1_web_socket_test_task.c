#include <dz1_web_socket.h>
#include "dz1_web_socket_test_task.h"

///////////////////////////////////////////////////////////////////////////////
// Init
static Dz1Error Dz1WebSocketTask_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
//	Dz1WebSocketTaskArg *arg = (Dz1WebSocketTaskArg *)uArg;
	Dz1WebSocketTaskEnv *env = NULL;

	if (0) { }
	else if (((*uRsc) = env = Dz1WebSocketTaskEnv_new(tSelf, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskEnv_delAndSetNull, (void *)uRsc);
		if (0) { }
		else
		{
			Dz1Task_queuePostSimple(my_queue_id, my_queue_id, DZ1_WEB_SOCK_MSG_DEFAULT);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WebSocketTaskEnv_delAndSetNull, (void *)uRsc);
	}
	return err;
}
// Init
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message : DZ1_WEB_SOCK_MSG_DEFAULT
static Dz1TaskProcStatus _doDefault(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "@@@ %s Task start\n", Dz1Task_getName(env->tSelf));
	return ret;
}
// Message : DZ1_WEB_SOCK_MSG_DEFAULT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message : DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _received(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	Dz1SockUtilReceiverReceived *msg = (Dz1SockUtilReceiverReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1WebSockMsgList *msgs = env->msgs;

	if (env->wsock != NULL)
	{
		if (Dz1WebSocket_onReceived(env->wsock, msg, msgs, errp) == FALSE)
		{
			if (env->pend_sg != NULL)
			{
				if (errp->code == EPIPE)
				{
					Dz1Error *status = Dz1TaskSigMsg_getErrPtr(env->pend_sg);
					Dz1Error_set(status, 0);
					Dz1TaskSigMsg_termDelAndSetNull(&env->pend_sg);
				}
				else
				{
					Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Receive Message Process fail. but close anyway\n");
					Dz1TaskSigMsg_TermDelAndSetNull(&env->pend_sg);
				}
			}
			else
			{
				ERR_OUT(errp);
				Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Receive Message Process fail\n");
			}
			Dz1WebSocket_delAndSetNull(&env->wsock);
		}
		else
		{
			Dz1WebSockMsg *ws_msg = NULL;
			while((ws_msg = msgs->extract(msgs, NULL)) != NULL)
			{
				u32_t log_lv = 0;
				pthread_cleanup_push(Dz1WebSockMsg_delAndSetNull, (void *)&ws_msg);
				Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
				switch(ws_msg->op)
				{
				case Dz1WebSockOpCode_text:
					if (log_lv & DZ1_THREAD_LOG_DEBUG)
					{
						_Dz1Thread_log("<<< Text Message Received = ");
						DZ1_DUMP(Dz1Binary, ws_msg->payload, 0);
					}
					break;
				case Dz1WebSockOpCode_binary:
					Dz1Thread_log(DZ1_THREAD_LOG_DEBUG, "<<< Binary Message Received\n");
					break;
				case Dz1WebSockOpCode_max:
					if (env->pend_sg != NULL)
					{
						Dz1Error *result = Dz1TaskSigMsg_getErrPtr(env->pend_sg);
						Dz1Error_set(result, 0);
						Dz1TaskSigMsg_termDelAndSetNull(&env->pend_sg);
					}
					break;
				}
				pthread_cleanup_pop(1); // (Dz1WebSockMsg_delAndSetNull, (void *)&ws_msg);
			}
		}
	}
	return ret;
}
// Message : DZ1_SOCK_UTIL_RECEIVER_RECEIVED
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message : DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
static Dz1TaskProcStatus _disconnected(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	Dz1SockUtilReceiverReceived *msg = (Dz1SockUtilReceiverReceived *)Dz1TaskSigMsg_getData(*sg);
	if (env->wsock != NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Socket Disconnected\n");
		if (env->pend_sg != NULL) Dz1TaskSigMsg_TermDelAndSetNull(&env->pend_sg);
		Dz1WebSocket_delAndSetNull(&env->wsock);
	}
	return ret;
}
// Message : DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// Message : DZ1_SOCK_UTIL_TRANSMITER_SENT
	static Dz1TaskProcStatus _sent(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
	{
		Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
		Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
		Dz1SockUtilTransmiterSent *msg = (Dz1SockUtilTransmiterSent *)Dz1TaskSigMsg_getData(*sg);
		if (env->wsock != NULL)
		{
			if (Dz1WebSocket_onSent(env->wsock, msg, errp) == FALSE)
			{
				ERR_OUT(errp);
				Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Transmission Process fail\n");
				if (env->pend_sg != NULL) Dz1TaskSigMsg_TermDelAndSetNull(&env->pend_sg);
				Dz1WebSocket_delAndSetNull(&env->wsock);
			}
		}
		return ret;
	}
	// Message : DZ1_SOCK_UTIL_TRANSMITER_SENT
	///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Open WebSocket
static Dz1TaskProcStatus _doOpen(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1WebSocketTaskMsgOpen *msg = (Dz1WebSocketTaskMsgOpen *)Dz1TaskSigMsg_getData(*sg);

	if (env->wsock != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (env->pend_sg != NULL) ERR_SET_OUT(errp, EAGAIN);
	else if ((env->wsock = Dz1WebSocket_createU(msg->uri, my_queue_id, TRUE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		env->pend_sg = *sg;
		*sg = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

bool_t Dz1WebSocketTask_open(Dz1Task *task, Dz1Asn1UTF8Str *uri, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketTaskMsgOpen msg = { uri };
	if (task == NULL || uri == NULL || uri->data == NULL || uri->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_WEB_SOCK_MSG_OPEN, (void *)&msg,
								   (Dz1DumpFunc)Dz1WebSocketTaskMsgSend_dump, NULL, NULL)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Open WebSocket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Send via WebSocket
static Dz1TaskProcStatus _doSend(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1WebSocketTaskMsgSend *msg = (Dz1WebSocketTaskMsgSend *)Dz1TaskSigMsg_getData(*sg);

	if (env->wsock == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->pend_sg != NULL) ERR_SET_OUT(errp, EPERM);
	else
	{
		Dz1Binary *bin = NULL;
		switch(msg->present)
		{
		case Dz1WebSocketTaskMsgSendPresent_text:
			if (Dz1WebSocket_sendText(env->wsock, msg->x.text, errp) == FALSE)
			{
				ERR_OUT(errp);
				Dz1WebSocket_delAndSetNull(&env->wsock);
			}
			break;
		case Dz1WebSocketTaskMsgSendPresent_bin:
			bin = msg->x.bin;
			if (Dz1WebSocket_sendBin(env->wsock, bin->data, bin->size, errp) == FALSE)
			{
				ERR_OUT(errp);
				Dz1WebSocket_delAndSetNull(&env->wsock);
			}
			break;
		case Dz1WebSocketTaskMsgSendPresent_ping:
			bin = msg->x.ping;
			if (Dz1WebSocket_sendPing(env->wsock, bin->data, bin->size, errp) == FALSE)
			{
				ERR_OUT(errp);
				Dz1WebSocket_delAndSetNull(&env->wsock);
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ret;
}

bool_t Dz1WebSocketTask_sendText(Dz1Task *task, Dz1Asn1UTF8Str *text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketTaskMsgSend *msg = NULL;
	if (task == NULL || text == NULL || text->data == NULL || text->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((msg = Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent_text, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
		if ((msg->x.text = Dz1Asn1UTF8Str_clone(text, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE,
									DZ1_WEB_SOCK_MSG_SEND, (void **)&msg,
									(Dz1DelFunc)Dz1WebSocketTaskMsgSend_del,
									(Dz1DumpFunc)Dz1WebSocketTaskMsgSend_dump,
									NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1WebSocketTask_sendBin(Dz1Task *task, Dz1Binary *bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketTaskMsgSend *msg = NULL;
	if (task == NULL || bin == NULL || bin->data == NULL || bin->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((msg = Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent_bin, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
		if ((msg->x.bin = Dz1Binary_clone(bin, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE,
									DZ1_WEB_SOCK_MSG_SEND, (void **)&msg,
									(Dz1DelFunc)Dz1WebSocketTaskMsgSend_del,
									(Dz1DumpFunc)Dz1WebSocketTaskMsgSend_dump,
									NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1WebSocketTask_sendPing(Dz1Task *task, Dz1Binary *bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketTaskMsgSend *msg = NULL;
	if (task == NULL || bin == NULL || bin->data == NULL || bin->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((msg = Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent_ping, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
		if ((msg->x.ping = Dz1Binary_clone(bin, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_post(task, DZ1_TASK_QUEUE_NONE,
									DZ1_WEB_SOCK_MSG_SEND, (void **)&msg,
									(Dz1DelFunc)Dz1WebSocketTaskMsgSend_del,
									(Dz1DumpFunc)Dz1WebSocketTaskMsgSend_dump,
									NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1WebSocketTaskMsgSend_delAndSetNull, (void *)&msg);
	}
	return ERR_IS_SUCCESS(errp);
}
// Send via WebSocket
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Close WebSocket
static Dz1TaskProcStatus _doClose(void *uAeg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	Dz1WebSocketTaskMsgClose *msg = (Dz1WebSocketTaskMsgClose *)Dz1TaskSigMsg_getData(*sg);

	if (env->wsock == NULL) Dz1Error_set(errp, ENOSYS);
	else if (env->pend_sg != NULL) Dz1Error_set(errp, EAGAIN);
	else if (Dz1WebSocket_sendClose(env->wsock, Dz1WebSocketCloseReason_normal_close, msg->opt_text, errp) == FALSE) ERR_OUT(errp);
	else
	{
		env->pend_sg = *sg;
		*sg = NULL;
	}
	return ret;
}

bool_t Dz1WebSocketTask_close(Dz1Task *task, Dz1Asn1UTF8Str *opt_text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1WebSocketTaskMsgClose msg = { opt_text };
	if (task == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_WEB_SOCK_MSG_CLOSE, (void *)&msg,
								  (Dz1DumpFunc)Dz1WebSocketTaskMsgClose_dump, NULL, NULL)).code) { }
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
// Close WebSocket
///////////////////////////////////////////////////////////////////////////////

static void Dz1WebSocketTask_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1WebSocketTaskArg *arg = (Dz1WebSocketTaskArg *)uArg;
	if (arg->cb)
		arg->cb(arg->cb_param, reason);
}

static void Dz1WebSocketTask_cleanup(void *uRsc)
{
	Dz1WebSocketTaskEnv *env = (Dz1WebSocketTaskEnv *)uRsc;
	if (env->pend_sg) Dz1TaskSigMsg_TermDelAndSetNull(&env->pend_sg);
	Dz1WebSocketTaskEnv_delAndSetNull(&env);
}

Dz1Task *Dz1WebSocketTask_create(Dz1WebSocketTaskExceptionCB cb, void *cb_param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Task *ret = NULL;
	Dz1WebSocketTaskArg *arg = NULL;
	if (0) { }
//	else if (Dz1Str_isVoid(uri)) ERR_SET_OUT(errp, EINVAL);
	else if ((arg = Dz1WebSocketTaskArg_new(cb, cb_param, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WebSocketTaskArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Dz1WebSocketTest", 1024,
							(void **)&arg, (Dz1DelFunc)Dz1WebSocketTaskArg_del,
							(Dz1CmpFunc)Dz1WebSocketTaskTimer_cmp,
							Dz1WebSocketTask_init,
							Dz1WebSocketTask_exception,
							Dz1WebSocketTask_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);

			arg = NULL;
			if (0) { }
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_WEB_SOCK_MSG_DEFAULT),				_doDefault)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_WEB_SOCK_MSG_OPEN),				_doOpen)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_WEB_SOCK_MSG_SEND),				_doSend)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_WEB_SOCK_MSG_CLOSE),				_doClose)).code) ERR_OUT(errp);

			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED),		_received)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED),	_disconnected)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT),		_sent)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1WebSocketTaskArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}
