#include "Dz1TcpSerialServerEnvUtil.h"

#include "Dz1TcpSerialServerSerialIO.h"
#include "Dz1TcpSerialServerSerialIOMsg.h"

static void _serialIO_byteConsume(void *ptr, u8_t *data, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSerialArg *arg = (Dz1TcpSerialServerSerialArg *)ptr;
	Dz1TcpSerialServerMsgRecv *msg = Dz1TcpSerialServerMsgRecv_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgRecv_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(arg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(arg->local, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->stream = Dz1Binary_new(data, size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_SERIAL_SERVER_SERIAL_RECEIVED, (void **)&msg,
											(Dz1DelFunc)Dz1TcpSerialServerMsgRecv_del,
											(Dz1DumpFunc)Dz1TcpSerialServerMsgRecv_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerMsgRecv_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _serialIO_m_byteConsume(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1TcpSerialServerMsgRecv *msg = (Dz1TcpSerialServerMsgRecv *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);
	if (session != NULL)
	{
		Dz1TimeVal to = { 1, 0 };
		if (session->isPresetPort)
		{
			if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, &msg->stream, &to)).code) ERR_OUT(errp);
			else msg->stream = NULL;
		}
		else
		{
			Dz1TcpSerialServerSerial *s = session->serial;
			Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_received, NULL, errp);
			if (rpl == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
				if ((rpl->x.received = Dz1TcpSerialMsgStream_new(s->port, msg->stream, errp)) == NULL) ERR_OUT(errp);
				else
				{
					msg->stream = NULL;

					Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
					if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
				}
				pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
			}
		}
	}
	return ret;
}

static void _serialIO_ringInd(void *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSerialArg *arg = (Dz1TcpSerialServerSerialArg *)ptr;
	Dz1TcpSerialServerMsgPin *msg = Dz1TcpSerialServerMsgPin_new(NULL, NULL, state, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(arg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(arg->local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_SERIAL_SERVER_SERIAL_RING_IND, (void **)&msg,
											(Dz1DelFunc)Dz1TcpSerialServerMsgPin_del,
											(Dz1DumpFunc)Dz1TcpSerialServerMsgPin_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _serialIO_m_ringInd(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1TcpSerialServerMsgPin *msg = (Dz1TcpSerialServerMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);
	if (session != NULL)
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_ringIndicated, NULL, errp);
		if (rpl == NULL) ERR_OUT(errp);
		else
		{
			Dz1TimeVal to = { 1, 0 };
			pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);

			if ((rpl->x.ringIndicated = Dz1TcpSerialMsgPin_new(s->port, msg->v, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
				if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
			}

			pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
		}
	}
	return ret;
}

static void _serialIO_ctsChanged(void *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSerialArg *arg = (Dz1TcpSerialServerSerialArg *)ptr;
	Dz1TcpSerialServerMsgPin *msg = Dz1TcpSerialServerMsgPin_new(NULL, NULL, state, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(arg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(arg->local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_SERIAL_SERVER_SERIAL_CTS_CHANGED, (void **)&msg,
											(Dz1DelFunc)Dz1TcpSerialServerMsgPin_del,
											(Dz1DumpFunc)Dz1TcpSerialServerMsgPin_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _serialIO_m_ctsChanged(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1TcpSerialServerMsgPin *msg = (Dz1TcpSerialServerMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);
	if (session != NULL)
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_ctsChanged, NULL, errp);
		if (rpl == NULL) ERR_OUT(errp);
		else
		{
			Dz1TimeVal to = { 1, 0 };
			pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);

			if ((rpl->x.ctsChanged = Dz1TcpSerialMsgPin_new(s->port, msg->v, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
				if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
			}

			pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
		}
	}
	return ret;
}

static void _serialIO_dsrChanged(void *ptr, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSerialArg *arg = (Dz1TcpSerialServerSerialArg *)ptr;
	Dz1TcpSerialServerMsgPin *msg = Dz1TcpSerialServerMsgPin_new(NULL, NULL, state, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(arg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(arg->local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_SERIAL_SERVER_SERIAL_DSR_CHANGED, (void **)&msg,
											(Dz1DelFunc)Dz1TcpSerialServerMsgPin_del,
											(Dz1DumpFunc)Dz1TcpSerialServerMsgPin_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerMsgPin_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _serialIO_m_dsrChanged(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1TcpSerialServerMsgPin *msg = (Dz1TcpSerialServerMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);
	if (session != NULL)
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_dsrChanged, NULL, errp);
		if (rpl == NULL) ERR_OUT(errp);
		else
		{
			Dz1TimeVal to = { 1, 0 };
			pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);

			if ((rpl->x.dsrChanged = Dz1TcpSerialMsgPin_new(s->port, msg->v, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
				if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
			}

			pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
		}
	}
	return ret;
}

static void _serialIO_exception(void *ptr, int port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSerialArg *arg = (Dz1TcpSerialServerSerialArg *)ptr;
	Dz1TcpSerialServerMsgException *msg = Dz1TcpSerialServerMsgException_new(NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerMsgException_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(arg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(arg->local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(arg->dstQueueID, DZ1_TASK_QUEUE_NONE,
											DZ1_TCP_SERIAL_SERVER_SERIAL_EXCEPTION, (void **)&msg,
											(Dz1DelFunc)Dz1TcpSerialServerMsgException_del,
											(Dz1DumpFunc)Dz1TcpSerialServerMsgException_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerMsgException_delAndSetNull, (void *)&msg);
	}
}

static Dz1TaskProcStatus _serialIO_m_exception(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1TcpSerialServerMsgException *msg = (Dz1TcpSerialServerMsgException *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->extract(sessions, &key);
	if (session != NULL)
	{
		pthread_cleanup_push(Dz1TcpSerialServerSession_cleanupAndSetNull, (void *)&session);
		Dz1Thread_printf("!!! Serial Exception = "); Dz1TcpSerialServerSession_dump(session, 0);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerSession_cleanupAndSetNull, (void *)&session);
	}
	return ret;
}

typedef struct SessionReplyArg
{
	Dz1TcpSerialServerSession	*session;
	Dz1TcpSerialMsgPresent		 present;
	s32_t						 port;
	Dz1Error					*errp;
} SessionReplyArg;

static void _serialIO_reply(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg *arg = (SessionReplyArg *)ptr;
	Dz1TcpSerialServerSession *session = arg->session;
	Dz1Error *status = arg->errp;

	Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(arg->present, NULL, errp);
	if (rpl == NULL) ERR_OUT(errp);
	else
	{
		Dz1TimeVal to = { 1, 0 };
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);

		if ((rpl->x.__ptr__ = Dz1TcpSerialMsgReply_new(arg->port, status->code, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
			if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
		}

		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
	}
}

static Dz1Error _serialIO_open(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsgOpen *req, u32_t myQueueID, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_openPortRsp, req->port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (session->serial != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((session->serial = s = Dz1TcpSerialServerSerial_new(req->port, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialServerSerialArg *ioArg = NULL;
		Dz1SerialPinChanged _ring_ind = (req->useRingInd ? _serialIO_ringInd : NULL);
		Dz1SerialPinChanged _cts_changed = ((req->flowRTSCTS == Dz1SerialRTSCTS_manual) && (req->useCtsChanged == TRUE)) ? _serialIO_ctsChanged : NULL;
		Dz1SerialPinChanged _dsr_changed = ((req->flowDSRDTR == Dz1SerialDSRDTR_manual) && (req->useDsrChanged == TRUE)) ? _serialIO_dsrChanged : NULL;

		pthread_cleanup_push(Dz1TcpSerialServerSerial_cleanupAndSetNull, (void *)&session->serial);
		if ((s->ioArg = ioArg = Dz1TcpSerialServerSerialArg_new(myQueueID, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((ioArg->peer = Dz1SockAddr_clone(session->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ioArg->local = Dz1SockAddr_clone(session->local, errp)) == NULL) ERR_OUT(errp);
		else if ((s->io = Dz1Serial_open(s->port, req->baud, 8, req->parity, req->stopBit, TRUE,
										 req->flowRTSCTS, req->flowDSRDTR, req->flowXONXOFF,
										 _serialIO_byteConsume, ioArg,
										 _ring_ind,				ioArg,	
										 _cts_changed,			ioArg,
										 _dsr_changed,			ioArg,
										 _serialIO_exception,	ioArg,
										 errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1TcpSerialServerSerial_delAndSetNull, (void *)&session->serial);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

Dz1TcpSerialServerSerial *Dz1TcpSerialServerSerialIO_openNullModem(Dz1SockAddr *peer, Dz1SockAddr *local,
																   u32_t myQueueID, Dz1TcpSerialServerPreset *cfg)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((s = Dz1TcpSerialServerSerial_new(cfg->serialPort, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialServerSerialArg *ioArg = NULL;
		pthread_cleanup_push(Dz1TcpSerialServerSerial_cleanupAndSetNull, (void *)&s);
		if ((s->ioArg = ioArg = Dz1TcpSerialServerSerialArg_new(myQueueID, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((ioArg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ioArg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((s->io = Dz1Serial_openNullModem(s->port, cfg->serialBaud, cfg->bitPerByte,
												  cfg->serialParity, cfg->serialStopBit, FALSE,
												  cfg->serialFlowCtrlXonXoff,
												 _serialIO_byteConsume, ioArg,
												 _serialIO_exception,	ioArg,
												 errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1TcpSerialServerSerial_cleanupAndSetNull, (void *)&s);
	}
	return s;
}

Dz1Error Dz1TcpSerialServerSerialIO_write(Dz1TcpSerialServerSession *session, Dz1Binary *stream, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if ((*errp = Dz1TcpSerialServerSerial_write(s, stream->data, stream->size)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _serialIO_close(Dz1TcpSerialServerSession *session, s32_t port, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = session->serial;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_closePortRsp, port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (s == NULL) { }
	else if (s->port != port) ERR_SET_OUT(errp, EINVAL);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerSerial_cleanupAndSetNull, (void *)&session->serial);
		Dz1Thread_printf("@@@ Close Serial = "); Dz1TcpSerialServerSession_dump(session, 0);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerSerial_cleanupAndSetNull, (void *)&session->serial);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

static Dz1Error _serialIO_write(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsgStream *req, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_writePortRsp, req->port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		Dz1Binary *stream = req->stream;
		if (s->port != req->port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_write(s, stream->data, stream->size)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

static Dz1Error _serialIO_writeDone(Dz1TcpSerialServerSession *session, s32_t port, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_writeDoneRsp, port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if (s->port != port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_writeDone(s)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

typedef struct SessionGetPinReplyArg
{
	Dz1TcpSerialServerSession	*session;
	Dz1TcpSerialMsgPresent		 present;
	s32_t						 port;
	Dz1SerialPinState			*pin;
	Dz1Error					*errp;
} SessionGetPinReplyArg;

static void _serialIO_getPinReply(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionGetPinReplyArg *arg = (SessionGetPinReplyArg *)ptr;
	Dz1TcpSerialServerSession *session = arg->session;
	Dz1Error *status = arg->errp;

	Dz1TcpSerialMsg *rpl = Dz1TcpSerialMsg_new(arg->present, NULL, errp);
	if (rpl == NULL) ERR_OUT(errp);
	else
	{
		Dz1TimeVal to = { 1, 0 };
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
		if ((rpl->x.__ptr__ = Dz1TcpSerialMsgPinResult_new(arg->port, *arg->pin, status->code, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(rpl, 0);
			if ((*errp = Dz1SocketFifo2_sendTCP(session->txFifo, session->sock, (void **)&rpl, &to)).code) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&rpl);
	}
}

static Dz1Error _serialIO_setRTS(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsgPin *req, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_setRTSRsp, req->port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if (s->port != req->port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_setRTS(s, req->v)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

static Dz1Error _serialIO_getCTS(Dz1TcpSerialServerSession *session, s32_t port, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1SerialPinState pin = -1;
	SessionGetPinReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_getCTSRsp, port, &pin, errp };
	pthread_cleanup_push(_serialIO_getPinReply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if (s->port != port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_getCTS(s, &pin)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_getPinReply, (void *)&rplArg);
	return err;
}

static Dz1Error _serialIO_setDTR(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsgPin *req, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	SessionReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_setDTRRsp, req->port, errp };
	pthread_cleanup_push(_serialIO_reply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if (s->port != req->port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_setDTR(s, req->v)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_reply, (void *)&rplArg);
	return err;
}

static Dz1Error _serialIO_getDSR(Dz1TcpSerialServerSession *session, s32_t port, void *uArg, void *uRsc, void *timer)
{
	Dz1TcpSerialServerSerial *s = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1SerialPinState pin = -1;
	SessionGetPinReplyArg rplArg = { session, Dz1TcpSerialMsgPresent_getDSRRsp, port, &pin, errp };
	pthread_cleanup_push(_serialIO_getPinReply, (void *)&rplArg);
	if (session->serial == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerSerial *s = session->serial;
		if (s->port != port) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1TcpSerialServerSerial_getDSR(s, &pin)).code) ERR_OUT(errp);
	}
	pthread_cleanup_pop(1); // (_serialIO_getPinReply, (void *)&rplArg);
	return err;
}

Dz1Error Dz1TcpSerialServer_serialIO(Dz1TcpSerialServerSession *session, Dz1TcpSerialMsg *pkt,
									 u32_t myQueueID,
									 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	switch(pkt->present)
	{
	case Dz1TcpSerialMsgPresent_openPortReq:
		if ((*errp = _serialIO_open(session, pkt->x.openPortReq, myQueueID, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_closePortReq:
		if ((*errp = _serialIO_close(session, pkt->x.closePortReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_writePortReq:
		if ((*errp = _serialIO_write(session, pkt->x.writePortReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_writeDoneReq:
		if ((*errp = _serialIO_writeDone(session, pkt->x.writeDoneReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_setRTSReq:
		if ((*errp = _serialIO_setRTS(session, pkt->x.setRTSReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_getCTSReq:
		if ((*errp = _serialIO_getCTS(session, pkt->x.getCTSReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_setDTRReq:
		if ((*errp = _serialIO_setDTR(session, pkt->x.setDTRReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	case Dz1TcpSerialMsgPresent_getDSRReq:
		if ((*errp = _serialIO_getDSR(session, pkt->x.getDSRReq, uArg, uRsc, timer)).code) ERR_OUT(errp);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

Dz1Error Dz1TcpSerialServerSerialIO_init(void *tSelf)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_SERIAL_RECEIVED),			_serialIO_m_byteConsume)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_SERIAL_RING_IND),		_serialIO_m_ringInd)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_SERIAL_CTS_CHANGED),	_serialIO_m_ctsChanged)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_SERIAL_DSR_CHANGED),	_serialIO_m_dsrChanged)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_TCP_SERIAL_SERVER_SERIAL_EXCEPTION),		_serialIO_m_exception)).code) ERR_OUT(errp);
	return err;
}
