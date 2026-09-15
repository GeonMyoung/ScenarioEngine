#include <Dz1TcpCallbackMsgCodec.h>

#include "Dz1TcpCallbackServerEnvUtil.h"
#include "Dz1TcpCallbackServerTimerUtil.h"
#include "Dz1TcpCallbackServerMsg.h"

///////////////////////////////////////////////////////////////////////////////
// TX FIFO Helper
Dz1Error _tx_fifo_fwd(Dz1SocketFifo *fifo, Dz1TcpClientSocket *sock)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary *packet = NULL;
	if ((packet = (Dz1Binary *)Dz1SocketFifo_peek(fifo, errp)) != NULL)
	{
		ssize_t sz = 0;
		if ((sz = sock->send(sock, packet->data, packet->size, DZ1_TCP_SOCK_FLAG_COMPLETE, NULL, errp)) < 0) { /* ERR_OUT(errp); */ }
		else if (sz == 0) ERR_SET_OUT(errp, EPIPE);
		else if (sz != packet->size) ERR_SET_OUT(errp, EFAULT);
//		else Dz1Thread_printf(">>> TX = %u\n", sz);
	}
	else Dz1Error_set(&err, 0);
	return err;
}

static Dz1Error _tx_fifo_send(Dz1SocketFifo *fifo, Dz1TcpClientSocket *sock, Dz1Binary **bin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	bool_t doSend = Dz1SocketFifo_count(fifo) == 0 ? TRUE : FALSE;
	if ((err = Dz1SocketFifo_push(fifo, bin)).code) ERR_OUT(&err);
	else if (doSend)
	{
		if ((err = _tx_fifo_fwd(fifo, sock)).code) ERR_OUT(&err);
	}
	return err;
}
// TX FIFO Helper
///////////////////////////////////////////////////////////////////////////////

static Dz1Binary *_getBinary(Dz1TcpCallbackMsg *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);

		if ((sz = Dz1TcpCallbackMsg_enc(NULL, -1, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1TcpCallbackMsg_enc(ret->data, ret->size, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// TX Helper
static Dz1Error _encode_and_send_msg(Dz1TcpCallbackSession *session, void *timer, Dz1TcpCallbackMsg *m)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Binary *bin = _getBinary(m, &err);
	if (bin == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((err = _tx_fifo_send(session->tx_fifo, session->sock, &bin)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// TX Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Received Message Process
static Dz1Error _msg_process(Dz1TcpCallbackServerArg *arg, Dz1TcpCallbackServerEnv *env, void *timer, Dz1TcpCallbackSession *session, Dz1TcpCallbackMsg *m)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(m->present)
	{
	case Dz1TcpCallbackMsgPresent_echo:
		if ((err = _encode_and_send_msg(session, timer, m)).code) ERR_OUT(&err);
		break;
	default:
		break;
	}
	return err;
}
// Received Message Process
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Decode Process
Dz1Error _decode_and_process(Dz1TcpCallbackServerArg *arg, Dz1TcpCallbackServerEnv *env, void *timer, Dz1TcpCallbackSession *session, Dz1SocketBuf *buf)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	ssize_t sz = 0;
	bool_t done = FALSE;
	Dz1TcpCallbackMsg *m = NULL;

	do 
	{
		if ((m = Dz1TcpCallbackMsg_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&m);
			if ((sz = Dz1TcpCallbackMsg_dec(m, Dz1SocketBuf_getData(buf, NULL), Dz1SocketBuf_getSize(buf, NULL), NULL, errp)) < 0)
			{
				if (errp->code == E2BIG)
				{
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
				else if (errp->code == EAGAIN)
				{
					Dz1SocketBuf_flush(buf);
					Dz1Error_set(errp, 0);
					done = TRUE;
				}
				else ERR_OUT(errp);
			}
			else
			{
				Dz1SocketBuf_pop(buf, NULL, sz, errp);
				if ((*errp = _msg_process(arg, env, timer, session, m)).code) ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&m);
		}
	} while (errp->code == 0 && done == FALSE);
	Dz1SocketBuf_fit(buf);
	return err;
}
// Decode Process
///////////////////////////////////////////////////////////////////////////////

Dz1TaskProcStatus _summary(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1TcpCallbackServerEnv *env = (Dz1TcpCallbackServerEnv *)uRsc;

	Dz1TimeVal tNow = Dz1TimeVal_get();
	if (Dz1TimeVal_isZero(env->tLast))
	{
		Dz1Thread_printf("@@@ Measurement Start\n");
	}
	else
	{
		u32_t cnt = env->sessions->count(env->sessions);
		double sec = ((double)Dz1TimeVal2MicroSec(Dz1TimeVal_sub(tNow, env->tLast))) / 1000000.0;
		double rx_bps = ((double)env->rx_amt) / sec;
		double tx_bps = ((double)env->tx_amt) / sec;
		Dz1Thread_printf("@@@ Session = %5u, RX:%10.3f, TX:%10.3f\n",
						  cnt, rx_bps, tx_bps);
	}

	env->tLast = tNow;
	env->tx_amt = 0;
	env->rx_amt = 0;

	_reg_summary_timer(timer);

	return ret;
}

