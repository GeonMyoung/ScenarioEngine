#include "Dz1TcpSerialServerEnvUtil.h"

void Dz1TcpSerialServerSession_cleanup(Dz1TcpSerialServerSession *p)
{
	if (p->serial != NULL) Dz1TcpSerialServerSerial_cleanupAndSetNull(&p->serial);
	Dz1TcpSerialServerSession_del(p);
}

void Dz1TcpSerialServerSerial_cleanup(Dz1TcpSerialServerSerial *p)
{
	if (p->io != NULL) Dz1Serial_closeAndSetNull(&p->io);
	Dz1TcpSerialServerSerial_del(p);
}

Dz1Error Dz1TcpSerialServerSerial_write(Dz1TcpSerialServerSerial *p, u8_t *data, size_t size)
{
	ssize_t status;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (p == NULL || p->io == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((status = Dz1Serial_write(p->io, data, size, errp)) < 0) ERR_OUT(errp);
	else if (status != size) ERR_SET_OUT(errp, EPIPE);
	return err;
}

Dz1Error Dz1TcpSerialServerSerial_writeDone(Dz1TcpSerialServerSerial *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1Serial_waitWriteDone(p->io)).code) ERR_OUT(errp);
	return err;
}


Dz1Error Dz1TcpSerialServerSerial_setRTS(Dz1TcpSerialServerSerial *p, Dz1SerialPinState v)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (p == NULL || p->io == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1Serial_setRTS(p->io, v)).code) ERR_OUT(errp);

	return err;
}

Dz1Error Dz1TcpSerialServerSerial_getCTS(Dz1TcpSerialServerSerial *p, Dz1SerialPinState *v)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (p == NULL || p->io == NULL || v == NULL) ERR_SET_OUT(errp, EINVAL);
	else (*v) = Dz1Serial_getCTS(p->io);

	return err;
}

Dz1Error Dz1TcpSerialServerSerial_setDTR(Dz1TcpSerialServerSerial *p, Dz1SerialPinState v)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (p == NULL || p->io == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1Serial_setDTR(p->io, v)).code) ERR_OUT(errp);

	return err;
}

Dz1Error Dz1TcpSerialServerSerial_getDSR(Dz1TcpSerialServerSerial *p, Dz1SerialPinState *v)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if (p == NULL || p->io == NULL || v == NULL) ERR_SET_OUT(errp, EINVAL);
	else (*v) = Dz1Serial_getDSR(p->io);

	return err;
}


