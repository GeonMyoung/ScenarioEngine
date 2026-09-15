#include <Dz1SockUtil.h>
#include <Dz1TcpSerialMsgCodec.h>

#include "Dz1TcpSerialServerArg.h"
#include "Dz1TcpSerialServerEnvUtil.h"

#include "Dz1TcpSerialServerSocketIO.h"
#include "Dz1TcpSerialServerSerialIO.h"

static Dz1Error _start_emulation_port(Dz1TcpSerialServerSessionList *sessions, Dz1SockUtilAcceptorConnected *msg, u32_t myQueueID)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSession *session = Dz1TcpSerialServerSession_new(msg->peer, msg->local, msg->sock, NULL, NULL, FALSE, errp);
	if (session == NULL) ERR_OUT(errp);
	else
	{
		msg->peer = msg->local = NULL;
		msg->sock = NULL;
		pthread_cleanup_push(Dz1TcpSerialServerSession_delAndSetNull, (void *)&session);
		if ((session->rxBuf = Dz1SocketBuf_new(65535, errp)) == NULL) ERR_OUT(errp);
		else if ((session->txFifo = Dz1SocketFifo2_new((Dz1EncodeFunc)Dz1TcpSerialMsg_enc, NULL,
													   (Dz1DelFunc)Dz1TcpSerialMsg_del,
													   (Dz1DumpFunc)Dz1TcpSerialMsg_dump, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_modeCallback(session->sock, session->peer, session->local, 4096, myQueueID)).code) ERR_OUT(errp);
		else if ((*errp = sessions->add(sessions, session)).code) ERR_OUT(errp);
		else
		{
			session = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerSession_delAndSetNull, (void *)&session);
	}
	return err;
}

static ssize_t _pass_through_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *src = (Dz1Binary *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE(cp, size, src->data, src->size, errp, ret);
	}
	return ret;
}

static Dz1Error _start_preset_port(Dz1TcpSerialServerSessionList *sessions, Dz1SockUtilAcceptorConnected *msg, u32_t myQueueID, Dz1TcpSerialServerPreset *cfg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerSession *session = Dz1TcpSerialServerSession_new(msg->peer, msg->local, msg->sock, NULL, NULL, TRUE, errp);
	if (session == NULL) ERR_OUT(errp);
	else
	{
		msg->peer = msg->local = NULL;
		msg->sock = NULL;
		pthread_cleanup_push(Dz1TcpSerialServerSession_delAndSetNull, (void *)&session);
		if ((session->serial = Dz1TcpSerialServerSerialIO_openNullModem(session->peer, session->local, myQueueID, cfg)) == NULL) ERR_OUT(errp);
		else if ((session->rxBuf = Dz1SocketBuf_new(65535, errp)) == NULL) ERR_OUT(errp);
		else if ((session->txFifo = Dz1SocketFifo2_new((Dz1EncodeFunc)_pass_through_enc, NULL,
													   (Dz1DelFunc)Dz1Binary_del,
													   (Dz1DumpFunc)Dz1Binary_dump, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_modeCallback(session->sock, session->peer, session->local, 4096, myQueueID)).code) ERR_OUT(errp);
		else if ((*errp = sessions->add(sessions, session)).code) ERR_OUT(errp);
		else
		{
			session = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerSession_delAndSetNull, (void *)&session);
	}
	return err;
}

static Dz1TaskProcStatus _m_connected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerArg *arg = (Dz1TcpSerialServerArg *)uArg;
	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1SockUtilAcceptorConnected *msg = (Dz1SockUtilAcceptorConnected *)Dz1TaskSigMsg_getData(*sg);

	if (msg->acceptorID == 0)
	{
		if ((*errp = _start_emulation_port(sessions, msg, myQueueID)).code) ERR_OUT(errp);
	}
	else
	{
		Dz1TcpSerialServerConfig *_cfg = arg->config;
		Dz1TcpSerialServerPreset key = { msg->acceptorID }, *cfg = _cfg->presets->find(_cfg->presets, &key);
		if (cfg == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = _start_preset_port(sessions, msg, myQueueID, cfg)).code) ERR_OUT(errp);
	}

	return ret;
}

Dz1Error _emulate_proc(Dz1TcpSerialServerSession *session, Dz1SockUtilReceiverReceived *msg, u32_t myQueueID,
					   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	ssize_t status = 0;
	Dz1Binary *stream = msg->stream;
	Dz1SocketBuf *buf = session->rxBuf;
	if ((status = Dz1SocketBuf_push(buf, stream->data, stream->size, errp)) < 0) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialMsg *pkt = NULL;
		bool_t done = FALSE;
		if (status != stream->size) Dz1Thread_printf("!!! : Socket Buffer overflowed\n");
		while(done == FALSE)
		{
			if ((pkt = Dz1TcpSerialMsg_gen(errp)) == NULL) { ERR_OUT(errp); done = TRUE; }
			else
			{
				pthread_cleanup_push(Dz1TcpSerialMsg_delAndSetNull, (void *)&pkt);
				if ((status = Dz1TcpSerialMsg_dec(pkt, Dz1SocketBuf_getData(buf, NULL),
													   Dz1SocketBuf_getSize(buf, NULL), NULL, errp)) < 0)
				{
					if (errp->code == E2BIG) Dz1Error_set(errp, 0);// wait more data
					else if (errp->code == EAGAIN)
					{	// stream broken
						Dz1SocketBuf_flush(buf);
						Dz1Error_set(errp, 0);
					}
					else ERR_OUT(errp);
					done = TRUE;
				}
				else
				{
					Dz1SocketBuf_pop(buf, NULL, status, NULL);
					Dz1Thread_printf("<<< Msg = "); Dz1TcpSerialMsg_dump(pkt, 0);
					if ((*errp = Dz1TcpSerialServer_serialIO(session, pkt, myQueueID, uArg, uRsc, timer)).code) ERR_OUT(errp);
				}
				pthread_cleanup_pop(1); // (Dz1TcpSerialMsg_delAndSetNull, (void *)&pkt);
			}
		}
		Dz1SocketBuf_fit(buf);
	}
	return err;
}
static Dz1TaskProcStatus _m_received(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1SockUtilReceiverReceived *msg = (Dz1SockUtilReceiverReceived *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);
	if (session != NULL)
	{
		if (session->isPresetPort)
		{
			Dz1Thread_printf("<<< Received "); Dz1Binary_dump(msg->stream, 0);
			if ((*errp = Dz1TcpSerialServerSerialIO_write(session, msg->stream, uArg, uRsc, timer)).code) ERR_OUT(errp);
		}
		else
		{
			if ((*errp = _emulate_proc(session, msg, myQueueID, uArg, uRsc, timer)).code) ERR_OUT(errp);
		}
	}
	return ret;
}

static Dz1TaskProcStatus _m_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;
	u32_t myQueueID = Dz1Task_getQueueID(env->tSelf);

	Dz1SockUtilReceiverReceived *msg = (Dz1SockUtilReceiverReceived *)Dz1TaskSigMsg_getData(*sg);

	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->extract(sessions, &key);
	if (session != NULL)
	{
		pthread_cleanup_push(Dz1TcpSerialServerSession_cleanupAndSetNull, (void *)&session);
		Dz1Thread_printf("!!! Session Disconnected = "); Dz1TcpSerialServerSession_dump(session, 0);
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerSession_cleanupAndSetNull, (void *)&session);
	}
	return ret;
}

static Dz1TaskProcStatus _m_sent(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TcpSerialServerEnv *env = (Dz1TcpSerialServerEnv *)uRsc;
	Dz1TcpSerialServerSessionList *sessions = env->sessions;

	Dz1SockUtilTransmiterSent *msg = (Dz1SockUtilTransmiterSent *)Dz1TaskSigMsg_getData(*sg);
	Dz1TcpSerialServerSession key = { msg->peer, msg->local }, *session = sessions->find(sessions, &key);

	if (session != NULL)
	{
		Dz1TimeVal to = { 3, 0 };
		Dz1SocketFifo2_continueTCP(session->txFifo, session->sock, &to);
	}

	return ret;
}

Dz1Error Dz1TcpSerialServerSocketIO_init(void *tSelf)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _m_connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _m_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _m_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _m_sent)).code) ERR_OUT(errp);
	return err;
}