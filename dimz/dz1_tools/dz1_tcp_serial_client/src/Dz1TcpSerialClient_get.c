#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"
#include "Dz1TcpSerialClient.h"

///////////////////////////////////////////////////////////////////////////////
// Get DSR
Dz1SerialPinState Dz1TcpSerialClient_getDSR(void *task, void *p, Dz1Error *err)
{
	Dz1SerialPinState ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (task == NULL)
	{
		if ((ret = Dz1Serial_getDSR(p)) == -1) ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPin *msg = Dz1TcpSerialClientMsgPin_new(port, Dz1SerialPinState_low, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_GET_DSR, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPin_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			else ret = msg->pin;
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
		}
	}
	return ret;
}


Dz1TaskProcStatus Dz1TcpSerialClient_m_getDSR(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPin *msg = (Dz1TcpSerialClientMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = Dz1TcpSerialClientPort_portGen_encodeAndSend(env->sock, Dz1TcpSerialMsgPresent_getDSRReq, port)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Get DSR
///////////////////////////////////////////////////////////////////////////////










///////////////////////////////////////////////////////////////////////////////
// Get CTS
Dz1SerialPinState Dz1TcpSerialClient_getCTS(void *task, void *p, Dz1Error *err)
{
	Dz1SerialPinState ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (task == NULL)
	{
		if ((ret = Dz1Serial_getCTS(p)) == -1) ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPin *msg = Dz1TcpSerialClientMsgPin_new(port, Dz1SerialPinState_low, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_GET_CTS, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPin_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			else ret = msg->pin;
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPin_delAndSetNull, (void *)&msg);
		}
	}
	return ret;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_getCTS(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPin *msg = (Dz1TcpSerialClientMsgPin *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = Dz1TcpSerialClientPort_portGen_encodeAndSend(env->sock, Dz1TcpSerialMsgPresent_getCTSReq, port)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Get CTS
///////////////////////////////////////////////////////////////////////////////


