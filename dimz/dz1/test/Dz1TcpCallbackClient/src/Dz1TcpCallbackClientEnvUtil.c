#include <Dz1TcpCallbackMsgCodec.h>

#include "Dz1TcpCallbackClientEnvUtil.h"
#include "Dz1TcpCallbackClientTimerUtil.h"
#include "Dz1TcpCallbackClientSocket.h"

void _session_runtime_terminate(void *timer, Dz1TcpCallbackSession *session)
{
	_dereg_retry_timer(timer, session);
	_dereg_term_timer(timer, session);
	Dz1TcpCallbackSession_del(session);
}

///////////////////////////////////////////////////////////////////////////////
// Received Message Process
static Dz1Error _msg_process(Dz1TcpCallbackClientArg *arg, Dz1TcpCallbackClientEnv *env, void *timer,
							 Dz1TcpCallbackSession *session, Dz1TcpCallbackMsg *m)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(m->present)
	{
	case Dz1TcpCallbackMsgPresent_echo:
		m->x.echo->echoID = session->echoID++;
		if ((err = _encode_and_send_msg(session, m)).code) ERR_OUT(&err);
		else _reg_retry_timer(timer, session);
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
Dz1Error _decode_proc(Dz1TcpCallbackClientArg *arg, Dz1TcpCallbackClientEnv *env, void *timer, Dz1TcpCallbackSession *session, Dz1SocketBuf *buf)
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
				// XXX : Message Procedure
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

