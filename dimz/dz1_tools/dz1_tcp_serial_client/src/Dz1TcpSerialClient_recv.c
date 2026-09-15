#include <dz1_socket_receiver.h>
#include <Dz1TcpSerialMsgCodec.h>

#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"

#include "Dz1TcpSerialClient.h"

///////////////////////////////////////////////////////////////////////////////
// Exception
static void _cb_exception(void *uArg, void *uRsc,
						  Dz1SockAddr *peer, Dz1SockAddr *local,
						  Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(uArg);
	Dz1TcpSerialClientMsgReceived *msg = Dz1TcpSerialClientMsgReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_DISCONNECTED, (void **)&msg,
										    (Dz1DelFunc)Dz1TcpSerialClientMsgReceived_del,
											(Dz1DumpFunc)Dz1TcpSerialClientMsgReceived_dump,
											reason, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&msg);
	}
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *err)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientMsgReceived *msg = (Dz1TcpSerialClientMsgReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1Error *reason = Dz1TaskSigMsg_getErrPtr(*sg);

	Dz1Thread_printf("@@@ TCP Serial Sub-system Disconnected\n");
	ret = Dz1TaskProcStatus_error;

	return ret;
}
// Exception
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Received
static Dz1SocketReceierBehavior _cb_fwd(void *uArg, void *uRsc,
										Dz1SockAddr *peer, Dz1SockAddr *local,
										Dz1TcpClientSocket *s, u8_t *data, size_t size,
										Dz1Error *errp)
{
	u32_t dstQueueID = (u32_t)DZ1_PTR2VAL32(uArg);
	Dz1TcpSerialClientMsgReceived *msg = Dz1TcpSerialClientMsgReceived_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->stream = Dz1Binary_new(data, size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_RECEIVED, (void **)&msg,
										    (Dz1DelFunc)Dz1TcpSerialClientMsgReceived_del,
											(Dz1DumpFunc)Dz1TcpSerialClientMsgReceived_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgReceived_delAndSetNull, (void *)&msg);
	}
	return Dz1SocketReceierBehavior_continue;
}

static Dz1Error _response_simpleReply(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl, u32_t reqSgType)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { rpl->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (s->req_sg == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
		if (Dz1TaskSigMsg_getType(s->req_sg) != reqSgType) ERR_SET_OUT(errp, EINVAL);
		else
		{
			Dz1Error *status = Dz1TaskSigMsg_getErrPtr(s->req_sg);
			Dz1Error_set(status, rpl->status);
			Dz1TaskSigMsg_termDelAndSetNull(&s->req_sg);
		}
		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
	}
	return err;
}

static Dz1Error _response_openPortReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { rpl->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (s->req_sg == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
		if (Dz1TaskSigMsg_getType(s->req_sg) != DZ1_TCP_SERIAL_CLIENT_OPEN) ERR_SET_OUT(errp, EINVAL);
		else
		{
			Dz1TcpSerialClientMsgOpen *msg = (Dz1TcpSerialClientMsgOpen *)Dz1TaskSigMsg_getData(s->req_sg);
			Dz1Error *status = Dz1TaskSigMsg_getErrPtr(s->req_sg);
			Dz1Error_set(status, rpl->status);
			msg->ret = (void *)DZ1_VAL2PTR32(s->port);
			Dz1TaskSigMsg_termDelAndSetNull(&s->req_sg);
		}
		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
	}
	return err;
}

static Dz1Error _response_closePortReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_simpleReply(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_CLOSE)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_writePortReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_simpleReply(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_WRITE)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_writeDoneReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_simpleReply(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_WRITE_DONE)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_setRTSReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_simpleReply(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_SET_RTS)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_setDTRReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgReply *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_simpleReply(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_SET_DTR)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_pinResult(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPinResult *rpl, u32_t reqSgType)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { rpl->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (s->req_sg == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
		if (Dz1TaskSigMsg_getType(s->req_sg) != reqSgType) ERR_SET_OUT(errp, EINVAL);
		else
		{
			Dz1Error *status = Dz1TaskSigMsg_getErrPtr(s->req_sg);
			Dz1TcpSerialClientMsgPin *msg = (Dz1TcpSerialClientMsgPin *)Dz1TaskSigMsg_getData(s->req_sg);

			msg->pin = rpl->v;
			Dz1Error_set(status, rpl->status);
			Dz1TaskSigMsg_termDelAndSetNull(&s->req_sg);
		}
		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1TaskSigMsg_terminateAbnormal, (void *)&s->req_sg);
	}
	return err;
}


static Dz1Error _response_getCTSReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPinResult *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_pinResult(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_GET_CTS)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_getDSRReq(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
									  Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPinResult *rpl)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _response_pinResult(arg, env, timer, ports, rpl, DZ1_TCP_SERIAL_CLIENT_GET_DSR)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _response_received(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer, Dz1TcpSerialMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	switch(msg->present)
	{
	case Dz1TcpSerialMsgPresent_openPortRsp:
		if ((*errp = _response_openPortReq(arg, env, timer, env->ports, msg->x.openPortRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_closePortRsp:
		if ((*errp = _response_closePortReq(arg, env, timer, env->ports, msg->x.closePortRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_writePortRsp:
		if ((*errp = _response_writePortReq(arg, env, timer, env->ports, msg->x.writePortRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_writeDoneRsp:
		if ((*errp = _response_writeDoneReq(arg, env, timer, env->ports, msg->x.writeDoneRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_setRTSRsp:
		if ((*errp = _response_setRTSReq(arg, env, timer, env->ports, msg->x.setRTSRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_getCTSRsp:
		if ((*errp = _response_getCTSReq(arg, env, timer, env->ports, msg->x.getCTSRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_setDTRRsp:
		if ((*errp = _response_setDTRReq(arg, env, timer, env->ports, msg->x.setDTRRsp)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_getDSRRsp:
		if ((*errp = _response_getDSRReq(arg, env, timer, env->ports, msg->x.getDSRRsp)).code) ERR_OUT(errp);
		break;
	default:
		break;
	}

	return err;
}

static Dz1Error _callback_received(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
								   Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgStream *ev)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { ev->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1Binary *stream = ev->stream;
		if (s->byteConsume != NULL)
			s->byteConsume(s->byteConsumeParam, stream->data, stream->size);
	}
	return err;
}

static Dz1Error _callback_ringInd(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
								   Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPin *ev)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { ev->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		if (s->ringInd != NULL)
			s->ringInd(s->ringIndParam, ev->v);
	}
	return err;
}

static Dz1Error _callback_ctsChange(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
								   Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPin *ev)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { ev->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		if (s->ctsChanged != NULL)
			s->ctsChanged(s->ctsChangedParam, ev->v);
	}
	return err;
}

static Dz1Error _callback_dsrChange(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer,
								   Dz1TcpSerialClientPortList *ports, Dz1TcpSerialMsgPin *ev)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialClientPort key = { ev->port }, *s = ports->find(ports, &key);
	if (s == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		if (s->dsrChanged != NULL)
			s->dsrChanged(s->dsrChangedParam, ev->v);
	}
	return err;
}

static Dz1Error _event_received(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer, Dz1TcpSerialMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	switch(msg->present)
	{
	case Dz1TcpSerialMsgPresent_received:
		if ((*errp = _callback_received(arg, env, timer, env->ports, msg->x.received)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_ringIndicated:
		if ((*errp = _callback_ringInd(arg, env, timer, env->ports, msg->x.ringIndicated)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_ctsChanged:
		if ((*errp = _callback_ctsChange(arg, env, timer, env->ports, msg->x.ctsChanged)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_dsrChanged:
		if ((*errp = _callback_dsrChange(arg, env, timer, env->ports, msg->x.dsrChanged)).code) ERR_OUT(errp);
		break;
	default:
		break;
	}
	return err;
}

static Dz1Error _reply_proc(Dz1TcpSerialClientArg *arg, Dz1TcpSerialClientEnv *env, void *timer, Dz1TcpSerialMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	switch(msg->present)
	{
	case Dz1TcpSerialMsgPresent_openPortRsp:
	case Dz1TcpSerialMsgPresent_closePortRsp:
	case Dz1TcpSerialMsgPresent_writePortRsp:
	case Dz1TcpSerialMsgPresent_writeDoneRsp:
	case Dz1TcpSerialMsgPresent_setRTSRsp:
	case Dz1TcpSerialMsgPresent_getCTSRsp:
	case Dz1TcpSerialMsgPresent_setDTRRsp:
	case Dz1TcpSerialMsgPresent_getDSRRsp:
		if ((*errp = _response_received(arg, env, timer, msg)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_received:
	case Dz1TcpSerialMsgPresent_ringIndicated:
	case Dz1TcpSerialMsgPresent_ctsChanged:
	case Dz1TcpSerialMsgPresent_dsrChanged:
		if ((*errp = _event_received(arg, env, timer, msg)).code) ERR_OUT(errp);
		break;
	default:
		break;
	}

	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_recv(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1SocketBuf *buf = env->rxBuf;
	Dz1TcpSerialClientMsgReceived *msg = (Dz1TcpSerialClientMsgReceived *)Dz1TaskSigMsg_getData(*sg);
	Dz1Binary *stream = msg->stream;

	ssize_t status = 0;
	if ((status = Dz1SocketBuf_push(buf, stream->data, stream->size, errp)) < 0) ERR_OUT(errp);
	else
	{
		bool_t done = FALSE;
		Dz1TcpSerialMsg *pkt = NULL;
		if (status != stream->size) { Dz1Thread_printf("!!! Buffer overrun\n"); }

		while(done == FALSE)
		{
			if ((pkt = Dz1TcpSerialMsg_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&pkt);
				if ((status = Dz1TcpSerialMsg_dec(pkt, Dz1SocketBuf_getData(buf, NULL), Dz1SocketBuf_getSize(buf, NULL), NULL, errp)) < 0)
				{
					if (errp->code == E2BIG) Dz1Error_set(errp, 0);
					else if (errp->code == EAGAIN) { Dz1Error_set(errp, 0); Dz1SocketBuf_flush(buf); }
					else ERR_OUT(errp);
					done = TRUE;
				}
				else
				{
					Dz1SocketBuf_pop(buf, NULL, status, errp);
					Dz1Thread_printf("<<< Msg = "); Dz1TcpSerialMsg_dump(pkt, 0);
					if ((*errp = _reply_proc(uArg, uRsc, timer, pkt)).code) ERR_OUT(errp);
				}
				pthread_cleanup_pop(1) ; // (Dz1TcpSerialMsg_delAndSetNull, (void *)&pkt);
			}
		}
		Dz1SocketBuf_fit(buf);
	}

	return ret;
}
// Received
///////////////////////////////////////////////////////////////////////////////

u32_t Dz1TcpSerialClientReceiver_start(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, u32_t dstQueueID, Dz1Error *err)
{
	u32_t ret = -1;
	void *_arg = (void *)DZ1_VAL2PTR32(dstQueueID);
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((ret = Dz1TcpSocketReceiver_start(peer, local, 1024, 0, &sock, FALSE,
										NULL,
										_cb_fwd,
										_cb_exception,
										NULL,
										NULL,
										(void **)&_arg, NULL, errp)) == -1) ERR_OUT(errp);
	return ret;
}

