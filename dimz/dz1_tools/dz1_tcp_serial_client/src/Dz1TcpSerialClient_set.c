#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"
#include "Dz1TcpSerialClient.h"

///////////////////////////////////////////////////////////////////////////////
// Set RTS
Dz1Error Dz1TcpSerialClient_setRTS(void *task, void *p, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (task == NULL)
	{
		if ((*errp = Dz1Serial_setRTS(p, state)).code) ERR_OUT(errp);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPin *msg = Dz1TcpSerialClientMsgPin_new(port, state, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_SET_RTS, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPin_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

static Dz1Error _setRtsGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *s, Dz1SerialPinState pin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1TcpSerialClientPort_pinGen_encodeAndSend(sock, s, Dz1TcpSerialMsgPresent_setRTSReq, pin)).code) ERR_OUT(errp);
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_setRTS(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPin *msg = (Dz1TcpSerialClientMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = _setRtsGen_encodeAndSend(env->sock, port, msg->pin)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Set RTS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Set DTR
Dz1Error Dz1TcpSerialClient_setDTR(void *task, void *p, Dz1SerialPinState state)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (task == NULL)
	{
		if ((*errp = Dz1Serial_setDTR(p, state)).code) ERR_OUT(errp);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPin *msg = Dz1TcpSerialClientMsgPin_new(port, state, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_SET_DTR, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPin_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

static Dz1Error _setDtrGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *s, Dz1SerialPinState pin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1TcpSerialClientPort_pinGen_encodeAndSend(sock, s, Dz1TcpSerialMsgPresent_setDTRReq, pin)).code) ERR_OUT(errp);
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_setDTR(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPin *msg = (Dz1TcpSerialClientMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = _setDtrGen_encodeAndSend(env->sock, port, msg->pin)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Set DTR
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1TcpSerialClient_setByteConsume(void *task, void *p,
										   Dz1SerialByteConsume byteConsume,
										   void *byteConsumeParam)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (task == NULL)
	{
		Dz1Serial_setByteConsume(p, byteConsume, byteConsumeParam);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgSetByteConsume *msg = Dz1TcpSerialClientMsgSetByteConsume_new(port, byteConsume, byteConsumeParam, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgSetByteConsume_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_SET_BYTE_CONSUME, (void *)msg,
									 (Dz1DumpFunc)Dz1TcpSerialClientMsgSetByteConsume_dump,
									 NULL, NULL)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgSetByteConsume_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_setByteConsume(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgSetByteConsume *msg = (Dz1TcpSerialClientMsgSetByteConsume *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else
	{
		port->byteConsume = msg->byteConsume;
		port->byteConsumeParam = msg->byteConsumeParam;
	}
	return ret;
}
