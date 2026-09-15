#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"
#include "Dz1TcpSerialClient.h"

Dz1Error Dz1TcpSerialClient_close(void *task, void *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (task == NULL)
	{
		Dz1Serial_close(p);
	}
	else
	{
		s32_t port = (s32_t)DZ1_PTR2VAL32(p);
		Dz1TcpSerialClientMsgPort *msg = Dz1TcpSerialClientMsgPort_new(port, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_CLOSE, (void *)msg,
									  (Dz1DumpFunc)Dz1TcpSerialClientMsgPort_dump,
									  NULL, NULL)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgPort_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_close(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgPort *msg = (Dz1TcpSerialClientMsgPort *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (port->req_sg != NULL) ERR_SET_OUT(errp, EBUSY);
	else if ((*errp = Dz1TcpSerialClientPort_portGen_encodeAndSend(env->sock, Dz1TcpSerialMsgPresent_closePortReq, port)).code) ERR_OUT(errp);
	else
	{
		port->req_sg = (*sg);
		(*sg) = NULL;
	}
	return ret;
}
