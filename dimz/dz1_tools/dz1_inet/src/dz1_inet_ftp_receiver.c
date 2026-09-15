#include <dz1_socket_receiver.h>
#include <dz1_inet_telnet_pi.h>
#include "dz1_inet_ftp_control_pi.h"
#include "dz1_inet_ftp_msg.h"
#include "dz1_inet_ftp_receiver_arg.h"
#include "dz1_inet_ftp_receiver.h"

typedef struct Dz1InetFtpReceiverEnv
{
	u8_t *buf;
	size_t size;
	u8_t *appendPtr;
	Dz1Error (*concat)(struct Dz1InetFtpReceiverEnv *env, Dz1Binary *bin);
	void (*consume)(struct Dz1InetFtpReceiverEnv *env, size_t size);

//	Dz1InetFtpCPIMsg *msg;
} Dz1InetFtpReceiverEnv;

static Dz1Error Dz1InetFtpReceiverEnv_concat(Dz1InetFtpReceiverEnv *env, Dz1Binary *bin)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	size_t sz = env->size - (size_t)(env->appendPtr - env->buf);
	if (sz < bin->size) ERR_SET_OUT(&err, E2BIG);
	else
	{
		memcpy(env->appendPtr, bin->data, bin->size);
		env->appendPtr += bin->size;
	}
	return err;
}

static void Dz1InetFtpReceiverEnv_consume(Dz1InetFtpReceiverEnv *env, size_t size)
{
	size_t dataSize = (size_t)(env->appendPtr - env->buf);
	if (dataSize == size) env->appendPtr = env->buf;
	else
	{
		u8_t *copyPtr = env->buf + size;
		size_t copySize = dataSize - size;
		memcpy(env->buf, copyPtr, copySize);
		env->appendPtr = env->buf + copySize;
	}
}

static void Dz1InetFtpReceiverEnv_del(Dz1InetFtpReceiverEnv *p)
{
	if (!p) return;
	if (p->buf) Dz1Free(p->buf);
	//if (p->msg) Dz1InetFtpCPIMsg_del(p->msg);
	Dz1Free(p);
}

static void Dz1InetFtpReceiverEnv_delAndSetNull(void *ptr)
{
	Dz1InetFtpReceiverEnv **p = (Dz1InetFtpReceiverEnv **)ptr;
	Dz1InetFtpReceiverEnv_del(*p); *p = NULL;
}

static Dz1InetFtpReceiverEnv *Dz1InetFtpReceiverEnv_new(size_t size, Dz1Error *errp)
{
	Dz1InetFtpReceiverEnv *ret = NULL;
	if (size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1InetFtpReceiverEnv *)Dz1Calloc(sizeof(Dz1InetFtpReceiverEnv), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpReceiverEnv_delAndSetNull, (void *)&ret);
		if ((ret->buf = (u8_t *)Dz1Malloc((ret->size = size), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->appendPtr = ret->buf;
			ret->concat = Dz1InetFtpReceiverEnv_concat;
			ret->consume = Dz1InetFtpReceiverEnv_consume;
//			ret->msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1InetFtpReceiverEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1InetFtpReceiver_init(void **ret, void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpReceiverEnv *env = NULL;

	if ((env = (*ret) = Dz1InetFtpReceiverEnv_new(8192, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error _postReply(void *tControl, Dz1InetFtpCPIMsg *msg, Dz1SockAddr *peer, Dz1SockAddr *local,
						   u8_t *data, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER	;
	Dz1InetFtpRcvrMsgReply *reply = NULL;
	if ((reply = Dz1InetFtpRcvrMsgReply_new(NULL, NULL, msg->x.reply, &err)) == NULL) ERR_OUT(&err);
	else
	{
		msg->x.reply = NULL;
		pthread_cleanup_push(Dz1InetFtpRcvrMsgReply_delAndSetNull, (void *)&reply);

		if ((reply->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((reply->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((reply->pkt = Dz1Binary_new(data, (u32_t)size, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(tControl, DZ1_TASK_QUEUE_NONE, DZ1_INET_FTP_RCVE_REPLY, (void **)&reply,
									(Dz1DelFunc)Dz1InetFtpRcvrMsgReply_del,
									(Dz1DumpFunc)Dz1InetFtpRcvrMsgReply_dump, NULL, NULL, NULL)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1InetFtpRcvrMsgReply_delAndSetNull, (void *)&reply);
	}
	return err;
}

static Dz1Error _ftpRecv(Dz1InetFtpReceiverArg *arg, Dz1InetFtpReceiverEnv *env, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1InetTelnetMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(msg->present)
	{
	case Dz1InetTelnetMsgPresent_bytes:
		if ((err = env->concat(env, msg->x.bytes)).code) ERR_OUT(&err);
		else
		{
			ssize_t status;
			size_t size = 0;
			bool_t isComplete;
			u8_t *cp = NULL;
			Dz1InetFtpCPIMsg *ftpMsg = NULL;
			while(err.code == 0 && (size = (size_t)(env->appendPtr - env->buf)))
			{
				isComplete = FALSE;
				cp = env->buf;
				if ((status = Dz1InetFtpCPIMsg_decode(&ftpMsg, cp, size, &isComplete, &err)) < 0)
				{
					if (err.code == E2BIG)
					{
						Dz1Error_set(&err, 0);
						break;
					}
				}
				else
				{
					pthread_cleanup_push(Dz1InetFtpCPIMsg_delAndSetNull, (void *)&ftpMsg);
					if (isComplete)
					{
						cp += status;
						if ((err = _postReply(arg->tControl, ftpMsg, peer, local, env->buf, (size_t)(cp - env->buf))).code) ERR_OUT(&err);
						env->consume(env, (size_t)(cp - env->buf));
					}
					pthread_cleanup_pop(1); // (Dz1InetFtpCPIMsg_delAndSetNull, (void *)&msg);
				}
			}
		}
		break;
	case Dz1InetTelnetMsgPresent_cmd:	// ignore cmd on client
		break;
	default:
		ERR_SET_OUT(&err, EFAULT);
		break;
	}
	return err;
}

static Dz1SocketReceierBehavior Dz1InetFtpReceiver_forward(void *uArg, void *uRsc,  Dz1SockAddr *peer, Dz1SockAddr *local,
															Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
	Dz1InetFtpReceiverArg *arg = (Dz1InetFtpReceiverArg *)uArg;
	Dz1InetFtpReceiverEnv *env = (Dz1InetFtpReceiverEnv *)uRsc;
	Dz1InetTelnetMsg *msg = NULL;
	u8_t *cp = data;
	ssize_t status;

	//Dz1Thread_printf("Dz1InetFtpReceiver_forward() : Packet Dump\n");
	//Dz1Thread_tprintb(1, data, size, 16);

	while(errp->code == 0 && size)
	{
		if ((status = Dz1InetTelnetPI_decode(&msg, cp, size, errp)) < 0) { ERR_OUT(errp); ret = Dz1SocketReceierBehavior_exception; break; }
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
			cp += status;
			size -= status;
			if ((*errp = _ftpRecv(arg, env, peer, local, msg)).code)
			{
				ret = Dz1SocketReceierBehavior_exception;
				ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		}
	}
	return ret;
}

/*
static Dz1SocketReceierBehavior Dz1InetFtpReceiver_timeout(void *userParam, void *userResource, Dz1SockAddr *peer, Dz1SockAddr *local,
															Dz1TcpClientSocket *s, Dz1Error *errp)
{
	return Dz1SocketReceierBehavior_exception;
}
*/

static void Dz1InetFtpReceiver_exception(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpReceiverArg *arg = (Dz1InetFtpReceiverArg *)uArg;
	Dz1InetFtpRcvrMsgException *msg = Dz1InetFtpRcvrMsgException_new(NULL, NULL, 0, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1InetFtpRcvrMsgException_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(arg->tControl, DZ1_TASK_QUEUE_NONE, DZ1_INET_FTP_RCVE_EXCEPTION, (void **)&msg,
									(Dz1DelFunc)Dz1InetFtpRcvrMsgException_del,
									(Dz1DumpFunc)Dz1InetFtpRcvrMsgException_dump, reason, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1InetFtpRcvrMsgException_delAndSetNull, (void *)&msg);
	}
}

static void Dz1InetFtpReceiver_cleanup(void *ptr)
{
	Dz1InetFtpReceiverEnv *env = (Dz1InetFtpReceiverEnv *)ptr;
	Dz1InetFtpReceiverEnv_del(env);
}


u32_t Dz1InetFtpReceiver_start(void *tControl, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	u32_t ret = -1;
	Dz1InetFtpReceiverArg *arg = Dz1InetFtpReceiverArg_new(tControl, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpReceiverArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1TcpSocketReceiver_start(peer, local, 4096, 300000, &sock, FALSE,
											Dz1InetFtpReceiver_init,
											Dz1InetFtpReceiver_forward,
											Dz1InetFtpReceiver_exception,
											NULL,
											Dz1InetFtpReceiver_cleanup,
											(void *)&arg, (Dz1DelFunc)Dz1InetFtpReceiverArg_del, errp)) == -1) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1InetFtpReceiverArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void Dz1InetFtpReceiver_stop(u32_t id)
{
	if (id != -1) Dz1TcpSocketReceiver_stop(id);
}
