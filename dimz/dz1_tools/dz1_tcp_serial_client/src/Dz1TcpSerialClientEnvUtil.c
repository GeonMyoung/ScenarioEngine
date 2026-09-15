#include <Dz1TcpSerialMsgCodec.h>
#include "Dz1TcpSerialClientEnvUtil.h"

Dz1Error Dz1TcpSerialClientPort_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary *bin = NULL;
	
	Dz1Thread_printf(">>> Msg = "); Dz1TcpSerialMsg_dump(msg, 0);

	if ((bin = Dz1Binary_new(NULL, 0, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TimeVal to = { 1, 0 };
		ssize_t status;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((status = Dz1TcpSerialMsg_enc(NULL, -1, msg, NULL, errp)) < 0) ERR_OUT(errp);
		else if ((bin->data = (u8_t *)Dz1Malloc((bin->size = status), errp)) == NULL) ERR_OUT(errp);
		else if ((status = Dz1TcpSerialMsg_enc(bin->data, bin->size, msg, NULL, errp)) < 0) ERR_OUT(errp);
		else if (status != (ssize_t)bin->size) ERR_SET_OUT(errp, EFAULT);
		else if ((status = sock->send(sock, bin->data, bin->size, DZ1_TCP_SOCK_FLAG_COMPLETE, &to, errp)) < 0) ERR_OUT(errp);
		else if (status == 0) ERR_SET_OUT(errp, EPIPE);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

Dz1Error Dz1TcpSerialClientPort_pinGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialClientPort *s, Dz1TcpSerialMsgPresent present, Dz1SerialPinState pin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialMsg *msg = NULL;
	
	switch(present)
	{
	case Dz1TcpSerialMsgPresent_setRTSReq:
	case Dz1TcpSerialMsgPresent_setDTRReq:
	case Dz1TcpSerialMsgPresent_ringIndicated:
	case Dz1TcpSerialMsgPresent_ctsChanged:
	case Dz1TcpSerialMsgPresent_dsrChanged:
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		return err;
	}

	if ((msg = Dz1TcpSerialMsg_new(present, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialMsgPin *p = NULL;
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
		if ((msg->x.__ptr__ = p = Dz1TcpSerialMsgPin_new(s->port, pin, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialClientPort_encodeAndSend(sock, msg)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
	}

	return err;
}

Dz1Error Dz1TcpSerialClientPort_portGen_encodeAndSend(Dz1TcpClientSocket *sock, Dz1TcpSerialMsgPresent present, Dz1TcpSerialClientPort *s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialMsg *msg = NULL;
	
	switch(present)
	{
	case Dz1TcpSerialMsgPresent_closePortReq:
	case Dz1TcpSerialMsgPresent_getCTSReq:
	case Dz1TcpSerialMsgPresent_getDSRReq:
	case Dz1TcpSerialMsgPresent_writeDoneReq:
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		return err;
	}
	if ((msg = Dz1TcpSerialMsg_new(present, &s->port, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
		if ((*errp = Dz1TcpSerialClientPort_encodeAndSend(sock, msg)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}
