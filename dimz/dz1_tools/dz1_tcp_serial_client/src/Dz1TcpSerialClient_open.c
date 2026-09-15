#include "Dz1TcpSerialClientArg.h"
#include "Dz1TcpSerialClientEnvUtil.h"
#include "Dz1TcpSerialClientMsg.h"
#include "Dz1TcpSerialClient.h"

///////////////////////////////////////////////////////////////////////////////
// Open
void *Dz1TcpSerialClient_open(void *task,
							  int					portNum,
							  u32_t					baud,
							  int					bitPerByte,	
							  Dz1SerialParity		parity,
							  Dz1SerialStopBit		stopBit,
							  bool_t				fullDuplex,
							  
							  Dz1SerialRTSCTS		flowRTSCTS,
							  Dz1SerialDSRDTR		flowDSRDTR,
							  Dz1SerialXONXOFF		flowXONXOFF,
							  
							  Dz1SerialByteConsume	byteConsume,	void *byteConsumeParam,
							  Dz1SerialPinChanged	ringInd,		void *ringIndParam,
							  Dz1SerialPinChanged	ctsChanged,		void *ctsChangedParam,
							  Dz1SerialPinChanged	dsrChanged,		void *dsrChangedParam,
							  Dz1SerialException	exception,		void *exceptionParam,
							  
							  Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (task == NULL)
	{
		if ((ret = Dz1Serial_open(portNum, baud, bitPerByte, parity, stopBit,
								   fullDuplex, flowRTSCTS, flowDSRDTR, flowXONXOFF,
								   byteConsume, byteConsumeParam,
								   ringInd, ringIndParam,
								   ctsChanged, ctsChangedParam,
								   dsrChanged, dsrChangedParam,
								   exception, exceptionParam, errp)) == NULL) ERR_OUT(errp);
	}
	else
	{
		Dz1TcpSerialClientMsgOpen *msg = Dz1TcpSerialClientMsgOpen_new(portNum, baud, bitPerByte, parity, stopBit,
																	   fullDuplex, flowRTSCTS, flowDSRDTR, flowXONXOFF,
																	   byteConsume, byteConsumeParam,
																	   ringInd, ringIndParam,
																	   ctsChanged, ctsChangedParam,
																	   dsrChanged, dsrChangedParam,
																	   exception, exceptionParam,
																	   NULL, errp);
		if (msg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientMsgOpen_delAndSetNull, (void *)&msg);
			if ((*errp = Dz1Task_call(task, DZ1_TASK_QUEUE_NONE, DZ1_TCP_SERIAL_CLIENT_OPEN, (void *)msg,
									 (Dz1DumpFunc)Dz1TcpSerialClientMsgOpen_dump, NULL, NULL)).code) ERR_OUT(errp);
			else
			{
				ret = msg->ret;
				msg->ret = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientMsgOpen_delAndSetNull, (void *)&msg);
		}
	}
	return ret;
}

void *Dz1TcpSerialClient_openNullModem(void *task,
									   int portNum, u32_t baud,
									   int bitPerByte, Dz1SerialParity pairty, Dz1SerialStopBit stopBit,
									   bool_t duplex,
									   Dz1SerialXONXOFF xonoffFlowControl,
									   Dz1SerialByteConsume byteConsume, void *byteConsumeParam,
									   Dz1SerialException exception, void *exceptionParam,
									   Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (task == NULL)
	{
		if ((ret = Dz1Serial_openNullModem(portNum, baud, bitPerByte, pairty, stopBit, duplex,
										xonoffFlowControl,
										byteConsume, byteConsumeParam,
										exception, exceptionParam, err)) == NULL) ERR_OUT(errp);
	}
	else
	{
		if ((ret = Dz1TcpSerialClient_open(task, portNum, baud, bitPerByte, pairty, stopBit, duplex,
										Dz1SerialRTSCTS_off,
										Dz1SerialDSRDTR_off,
										xonoffFlowControl,
										byteConsume, byteConsumeParam,
										NULL, NULL,
										NULL, NULL,
										NULL, NULL,
										exception, exceptionParam, errp)) == NULL) ERR_OUT(errp);
	}
	return ret;
}

static Dz1Error _openGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *port)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialMsg *msg = Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_openPortReq, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialMsgOpen *p = NULL;
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
		if ((msg->x.openPortReq = p = Dz1TcpSerialMsgOpen_new(port->port, port->baud, port->parity, port->stopBit, port->fullDuplex,
															  port->flowRTSCTS, port->flowDSRDTR, port->flowXONXOFF,
															  port->ringInd == NULL ? FALSE : TRUE,
															  port->ctsChanged == NULL ? FALSE : TRUE,
															  port->dsrChanged == NULL ? FALSE : TRUE,
															  errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialClientPort_encodeAndSend(sock, msg)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

Dz1TaskProcStatus Dz1TcpSerialClient_m_open(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialClientArg *arg = (Dz1TcpSerialClientArg *)uArg;
	Dz1TcpSerialClientEnv *env = (Dz1TcpSerialClientEnv *)uRsc;
	Dz1TcpSerialClientMsgOpen *msg = (Dz1TcpSerialClientMsgOpen *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialClientPort key = { msg->portNum }, *port = env->ports->find(env->ports, &key);

	if (port != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		if ((port = Dz1TcpSerialClientPort_new(msg->portNum, msg->baud, msg->bitPerByte, msg->parity, msg->stopBit,
											   msg->fullDuplex, msg->flowRTSCTS, msg->flowDSRDTR, msg->flowXONXOFF,
											   msg->byteConsume, msg->byteConsumeParam,
											   msg->ringInd, msg->ringIndParam,
											   msg->ctsChanged, msg->ctsChangedParam,
											   msg->dsrChanged, msg->dsrChangedParam,
											   msg->exception, msg->exceptionParam, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialClientPort_delAndSetNull, (void *)&port);
			if ((*errp = _openGen_encodeAndSend(env->sock, port)).code) ERR_OUT(errp);
			else if ((*errp = env->ports->add(env->ports, port)).code) ERR_OUT(errp);
			else
			{
				port->req_sg = (*sg); (*sg) = NULL;
				port = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TcpSerialClientPort_delAndSetNull, (void *)&port);
		}
	}

	return ret;
}
// Open
///////////////////////////////////////////////////////////////////////////////

