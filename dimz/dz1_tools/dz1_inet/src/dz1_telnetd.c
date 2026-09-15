#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_usleep.h>

#include <dz1_socket_acceptor.h>
#include <dz1_socket_receiver.h>
#include <dz1_inet_telnet_pi.h>

static Dz1Error _encodeAndSend(Dz1TcpClientSocket *s, Dz1InetTelnetMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t *data = NULL;
	ssize_t size = 0;

	Dz1Thread_tprintf(1, "_encodeAndSend() : msg = "); Dz1InetTelnetMsg_dump(msg, 2);
	if ((size = Dz1InetTelnetPI_encode(&data, msg, &err)) < 0) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)data);

		if (s->send(s, data, size, TRUE, NULL, &err) < 0) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)data);
	}
	return err;
}

static void telnetdNego(Dz1TcpClientSocket *s, Dz1InetTelnetCmd *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetMsg *reply = NULL;
	if ((reply = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetTelnetCmd *cmd = NULL;
		Dz1InetTelnetOpt *opt = (Dz1InetTelnetOpt *)msg->x.__ptr__;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)reply);
		switch(msg->present)
		{
		case Dz1InetTelnetCmdPresent_doOpt:
			if (opt->present == Dz1InetTelnetOptPresent_suppressGoAhead)
			{
				if ((cmd = reply->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_willOpt, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt->present, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((err = _encodeAndSend(s, reply)).code) ERR_OUT(&err);

				else if ((cmd = reply->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_doOpt, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt->present, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((err = _encodeAndSend(s, reply)).code) ERR_OUT(&err);
			}
			else
			{
				if ((cmd = reply->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_wontOpt, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt->present, NULL, &err)) == NULL) ERR_OUT(&err);
				else if ((err = _encodeAndSend(s, reply)).code) ERR_OUT(&err);
			}
			break;
		case Dz1InetTelnetCmdPresent_dontOpt:
			if ((cmd = reply->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_wontOpt, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt->present, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _encodeAndSend(s, reply)).code) ERR_OUT(&err);
			break;
		case Dz1InetTelnetCmdPresent_willOpt:
		case Dz1InetTelnetCmdPresent_wontOpt:
			if ((cmd = reply->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_dontOpt, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt->present, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _encodeAndSend(s, reply)).code) ERR_OUT(&err);
			break;
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)reply);
	}
}

static void telnetdControl(void *ptr, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s, Dz1InetTelnetMsg *msg)
{
	if (msg->present == Dz1InetTelnetMsgPresent_cmd)
	{
		Dz1InetTelnetCmd *cmd = msg->x.cmd;
		switch(cmd->present)
		{
		case Dz1InetTelnetCmdPresent_doOpt:
		case Dz1InetTelnetCmdPresent_dontOpt:
		case Dz1InetTelnetCmdPresent_willOpt:
		case Dz1InetTelnetCmdPresent_wontOpt:
			telnetdNego(s, cmd);
			break;
		default:
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Socket Receiver Callback
///////////////////////////////////////////////////////////////////////////////
static Dz1SocketReceierBehavior receiverForward(void *ptr, void *resource, Dz1SockAddr *peer, Dz1SockAddr *local,
											Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	Dz1InetTelnetMsg *msg = NULL;
	u8_t *cp = data;
	ssize_t status;

	Dz1Thread_printf("receiverForward() : Data Received\n");

	while(size)
	{
		if ((status = Dz1InetTelnetPI_decode(&msg, cp, size, errp)) < 0) { ERR_OUT(errp); ret = Dz1SocketReceierBehavior_exception; break; }
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
			cp += status;
			size -= status;
			Dz1Thread_printf("receiverForward() : Telnet PI Msg = "); Dz1InetTelnetMsg_dump(msg, 1);
			telnetdControl(NULL, peer, local, s, msg);
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		}
	}

	return ret;
}

static void receiverException(void *userParam, void *userResource, Dz1SockAddr *peer, Dz1SockAddr *local,
																	Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("Receiver Exception : PEER Closed\n");
}

static void receiverCleanup(void *ptr) { Dz1Thread_printf("Receiver Terminated\n"); }

///////////////////////////////////////////////////////////////////////////////
// Socket Acceptor Callback
///////////////////////////////////////////////////////////////////////////////
typedef struct AcceptorEnv
{
	u32_t rcvr;
} AcceptorEnv;

static AcceptorEnv *AcceptorEnv_new(Dz1Error *errp)
{
	AcceptorEnv *ret = (AcceptorEnv *)Dz1Calloc(sizeof(AcceptorEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else ret->rcvr = -1;
	return ret;
}

static void AcceptorEnv_del(AcceptorEnv *p)
{
	if (!p) return;
	if (p->rcvr != -1) Dz1TcpSocketReceiver_stop(p->rcvr);
	Dz1Free(p);
}
// typedef Dz1Error (*Dz1TcpSocketAcceptorInitFunc)(void **uRsc, void *uArg, Dz1TcpServerSocket *s);
static Dz1Error acceptorInit(void **ret, void *uParam, Dz1TcpServerSocket *s)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	AcceptorEnv *env = NULL;
	if ((env = (*ret) = AcceptorEnv_new(&err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1TcpSocketAcceptorBehavior acceptorForward(void *uArg, void *uRsc, Dz1TcpClientSocket **s, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *errp)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;
	AcceptorEnv *env = (AcceptorEnv *)uRsc;

	if (env->rcvr != (u32_t)-1) { Dz1TcpSocketReceiver_stop(env->rcvr); env->rcvr = -1; }

	if ((env->rcvr = Dz1TcpSocketReceiver_start(peer, local, 0x4000, 0, s, TRUE,
												NULL, receiverForward, receiverException, NULL, receiverCleanup,
												NULL, NULL, errp)) == (u32_t)-1) { ERR_OUT(errp); }
	return ret;
}

typedef struct TestEnv
{
	Dz1TcpServerSocket *s;
	u32_t acceptor;
	bool_t acceptorDown;
} TestEnv;

static void accceptorException(void *uArg, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason)
{
	TestEnv *p = (TestEnv *)uArg;
	p->acceptorDown = TRUE;
}

static void acceptorCleanup(void *ptr)
{
	AcceptorEnv *env = (AcceptorEnv *)ptr;
	AcceptorEnv_del(env);
}

static Dz1Error user_main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	TestEnv env = { NULL, -1 };

	char addrStr[53];
	Dz1SockAddr addr;

	u16_t port = 0;

	memset(&addr, 0, sizeof(Dz1SockAddr));

	if ((err = Dz1SockAddr_setAddrStr(&addr, "0.0.0.0")).code) { ERR_OUT(&err); }
#ifdef UNIX_SYSTEM
	else if ((err = Dz1SockAddr_setPort(&addr, 2023)).code) { ERR_OUT(&err); }
#else
	else if ((err = Dz1SockAddr_setPort(&addr, 23)).code) { ERR_OUT(&err); }
#endif
	else if ((env.s = Dz1TcpServerSocket_open(&addr, &port, 5, &err)) == NULL) { ERR_OUT(&err); }
	else
	{
		if (Dz1SockAddr_printable(&addr, addrStr, FALSE, &err) == NULL) { ERR_OUT(&err); }
		else
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1TcpServerSocket_close, (void *)env.s);

			Dz1Thread_printf("ADDR : %s\n", addrStr);

			if ((env.acceptor = Dz1TcpSocketAcceptor_start(env.s, FALSE, 0, 0,
							acceptorInit, acceptorForward,
							accceptorException, NULL, acceptorCleanup,
							(void *)&env, NULL, &err)) == (u32_t)-1) ERR_OUT(&err);
			else
			{
				int ch;
				while(1)
				{
					if (env.acceptorDown == TRUE) break;
//					else if (Dz1Thread_read(&ch, 1, 0, &err) == 1)
					else if ((ch = Dz1Thread_getch(1000000, NULL)) > 0)
					{
						Dz1TcpSocketAcceptor_stop(env.acceptor);
						break;
					}
//					else Dz1Thread_usleep(100000);
				}
			}
			pthread_cleanup_pop(err.code); // ((Dz1CancelFunc)Dz1TcpServerSocket_close, (void *)s);
		}
		Dz1TcpServerSocket_close(env.s);
	}

	return err;
}

int main(void)
{
	int th = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_init();
#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win Sock Init Fail\n"); return EFAULT; }
#endif

	if ((th = Dz1Thread_init(DZ1_THREAD_LOG_BASIS, &err)) < 0) { ERR_OUT(&err); }
	else if ((err = user_main()).code) { ERR_OUT(&err); }

	return err.code;
}
