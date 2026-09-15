#include <dz1_task.h>

#include <dz1_serial.h>

#include "dz1_serial_sock_spec.h"
#include <dz1_serial_sock.h>

static void Dz1SerialSock_byteConsume(void *ptr, u8_t *data, size_t size)
{
	ssize_t status;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)ptr;

//	Dz1Thread_printf("<<< Serial\n");
//	Dz1Thread_tprintb(1, data, size, 16);
	Dz1Sync_lock(spec->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)spec->sync);
	if ((status = Dz1SocketBuf_push(spec->buf, data, size, &err)) < 0) ERR_OUT(&err);
	else
	{
		if ((size_t)status != size) Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "!!! WARNING : Received data is truncated\n");
		Dz1Sync_signal(spec->sync);
	}
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)spec->sync);
}

static void Dz1SerialSock_exception(void *ptr, int port)
{
	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)ptr;
	Dz1Sync_lock(spec->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)spec->sync);
	spec->eof = TRUE;
	Dz1Sync_signal(spec->sync);
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)spec->sync);
}

static void Dz1SerialSocketSpecific_cleanup(void *ptr)
{
	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)ptr;
	if (spec->io != NULL) Dz1Serial_closeAndSetNull(&spec->io);
	Dz1SerialSocketSpecific_del(spec);
}

static Dz1Error Dz1SerialSock_waitCond(void *ptr, bool_t *wakeup)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)ptr;
	*wakeup = FALSE;
	if (Dz1SocketBuf_getSize(spec->buf, &err) > 0 || spec->eof) *wakeup = TRUE;
	return err;
}

static int Dz1SerialSock_waitNoLock(Dz1SerialSocketSpecific *spec, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *errp)
{
	int ret = 0;
	if (flag & Dz1SocketWaitFlag_out)
	{
		ret |= Dz1SocketWaitFlag_out;
		if (flag & Dz1SocketWaitFlag_in)
		{
			if (Dz1SocketBuf_getSize(spec->buf, errp) > 0 || spec->eof)
				ret |= Dz1SocketWaitFlag_in;
		}
	}
	else if (flag & Dz1SocketWaitFlag_in)
	{
		if (Dz1SocketBuf_getSize(spec->buf, errp) > 0 || spec->eof) ret |= Dz1SocketWaitFlag_in;
		else
		{
			if (to != NULL)
			{
				u64_t duration_us = Dz1TimeVal2US(*to);
				if ((*errp = Dz1Sync_wait(spec->sync, &duration_us, Dz1SerialSock_waitCond, (void *)spec)).code) ERR_OUT(errp);
				else if (Dz1SocketBuf_getSize(spec->buf, errp) > 0 || spec->eof) ret |= Dz1SocketWaitFlag_in;
				(*to) = Dz1TimeValFromUS(duration_us);
			}
			else
			{
				if ((*errp = Dz1Sync_wait(spec->sync, NULL, Dz1SerialSock_waitCond, (void *)spec)).code) ERR_OUT(errp);
			}
		}
	}
	return ret;
}
 
static int Dz1SerialSock_wait(Dz1TcpClientSocket *p, Dz1SocketWaitFlag flag, struct timeval *to, Dz1Error *err)
{
	int ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SerialSocketSpecific *spec = p->specific;
	Dz1Sync_lock(spec->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)spec->sync);
	if ((ret = Dz1SerialSock_waitNoLock(spec, flag, to, errp)) < 0) ERR_OUT(errp);
	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)spec->sync);
	return ret;
}

static ssize_t Dz1SerialSock_send(Dz1TcpClientSocket *p, u8_t *data, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)p->specific;

	u32_t lv = 0;
	Dz1Thread_getLogLevel(Dz1Thread_self(), &lv);
	if (lv & DZ1_THREAD_LOG_MESSAGE)
	{
		Dz1Binary bin = { data, (u32_t)size };
		Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, ">>> Serial = "); DZ1_DUMP(Dz1Binary, &bin, 0);
	}

	return Dz1Serial_write(spec->io, data, size, errp);
}

static ssize_t Dz1SerialSock_read(Dz1TcpClientSocket *p, u8_t *buf, size_t size, u32_t flag, struct timeval *to, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SerialSocketSpecific *spec = (Dz1SerialSocketSpecific *)p->specific;
	Dz1Sync_lock(spec->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)spec->sync);

	if ((ret = (ssize_t)Dz1SerialSock_waitNoLock(spec, Dz1SocketWaitFlag_in, to, errp)) < 0) ERR_OUT(errp);
	else if (ret == 0) { Dz1Error_set(errp, ETIMEDOUT); ret = -1; }
	else if ((ret = Dz1SocketBuf_getSize(spec->buf, errp)) < 0) ERR_OUT(errp);
	else if (ret > 0)
	{
		if ((ret = Dz1SocketBuf_pop(spec->buf, buf, size, errp)) < 0) ERR_OUT(errp);
		else if (ret == 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
	}
	else if (spec->eof) // ret == 0
		Dz1Error_set(errp, EPIPE);
	else Dz1Error_set(errp, EAGAIN);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)spec->sync);
	return ret;
}

SOCKET Dz1SerialSock_getOsHandle(Dz1TcpClientSocket *p) { return INVALID_SOCKET; }

Dz1TcpClientSocket *Dz1SerialSock_new(int port, u32_t baud, Dz1Error *err)
{
	Dz1TcpClientSocket *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SerialSocketSpecific *spec = Dz1SerialSocketSpecific_new(NULL, NULL, FALSE, NULL, errp);
	if (spec == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SerialSocketSpecific_delAndSetNull, (void *)&spec);
		if ((spec->sync = Dz1Sync_new(errp)) == NULL) ERR_OUT(errp);
		else if ((spec->buf = Dz1SocketBuf_new(16384, errp)) == NULL) ERR_OUT(errp);
		else if ((spec->io = Dz1Serial_open(port, baud, 8, Dz1SerialParity_none, Dz1SerialStopBit_one, TRUE,
											Dz1SerialRTSCTS_off, Dz1SerialDSRDTR_off, Dz1SerialXONXOFF_off,
											Dz1SerialSock_byteConsume, (void *)spec,
											NULL, NULL,
											NULL, NULL,
											NULL, NULL,
											Dz1SerialSock_exception, (void *)spec,
											errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1TcpClientSocket_encapsulation((void **)&spec,
														 (Dz1DelFunc)Dz1SerialSocketSpecific_cleanup,
														 Dz1SerialSock_wait,
														 Dz1SerialSock_send,
														 Dz1SerialSock_read,
														 Dz1SerialSock_getOsHandle, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1SerialSocketSpecific_delAndSetNull, (void *)&spec);
	}
	return ret;
}
