#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"
#include "Dz1TcpSerialClient.h"

///////////////////////////////////////////////////////////////////////////////
// Write
ssize_t Dz1TcpSerialClient_write(void *task, void *p, const unsigned char *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (task == NULL)
	{
		if ((ret = Dz1Serial_write(p, buf, size, errp)) < 0) ERR_OUT(errp);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgChunk *msg = Dz1TcpSerialClientMsgChunk_new(port, NULL, -1, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgChunk_delAndSetNull, (void *)&msg);
			if ((msg->stream = Dz1Binary_new((u8_t *)buf, size, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_WRITE, (void *)msg,
										   (Dz1DumpFunc)Dz1TcpSerialClientMsgChunk_dump,
										   NULL, NULL)).code) ERR_OUT(errp);
			else ret = msg->ret;
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgChunk_delAndSetNull, (void *)&msg);
		}
	}
	return ret;
}

Dz1Error _writeGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *s, Dz1Binary **stream)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialMsg *msg = NULL;
	
	if ((msg = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_writePortReq, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialMsgStream *p = NULL;
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
		if ((msg->x.writePortReq = p = Dz1TcpSerialMsgStream_new(s->port, (*stream), errp)) == NULL) ERR_OUT(errp);
		else
		{
			(*stream) = NULL;
			if ((*errp = Dz1TcpSerialClientPort_encodeAndSend(sock, msg)).code) ERR_OUT(errp);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}


Dz1TaskProcStatus Dz1TcpSerialClient_m_write(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgChunk *msg = (Dz1TcpSerialClientMsgChunk *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = _writeGen_encodeAndSend(env->sock, port, &msg->stream)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Write
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Write Done
Dz1Error Dz1TcpSerialClient_waitWriteDone(void *task, void *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (task == NULL)
	{
		if ((*errp = Dz1Serial_waitWriteDone(p)).code) ERR_OUT(errp);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPort *msg = Dz1TcpSerialClientMsgPort_new(port, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_WRITE_DONE, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPort_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_writeDone(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPort *msg = (Dz1TcpSerialClientMsgPort *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = Dz1TcpSerialClientPort_portGen_encodeAndSend(env->sock, Dz1TcpSerialMsgPresent_writeDoneReq, port)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
// Write Done
///////////////////////////////////////////////////////////////////////////////
