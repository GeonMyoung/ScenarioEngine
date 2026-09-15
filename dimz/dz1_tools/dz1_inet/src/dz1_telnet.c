#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_str.h>
#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_shell.h>
#include <dz1_malloc.h>

#include <dz1_socket_receiver.h>
#include <dz1_socket_connector.h>
#include <dz1_inet_telnet_pi.h>
#include "dz1_inet_telnet_nvt.h"

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

static Dz1Error _genCmdAndSend(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent cmdPresent, Dz1InetTelnetOptPresent optPresent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetMsg *msg = NULL;
	if ((msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetTelnetCmd *cmd = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		if ((cmd = msg->x.cmd = Dz1InetTelnetCmd_new(cmdPresent, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((cmd->x.doOpt = Dz1InetTelnetOpt_new(optPresent, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(s, msg)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
	}
	return err;
}

typedef struct TestEnv
{
	Dz1TcpClientSocket	*sock;
	u32_t				 rcvr;
} TestEnv;

///////////////////////////////////////////////////////////////////////////////
// Suppress Go Ahead
///////////////////////////////////////////////////////////////////////////////
static bool_t _setPeerGA(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	return TRUE;
}

static void _repliedPeerGA(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
	if (e->peer->value == val)
	{
		Dz1InetTelnetNVT_optSetLocal(env, s, Dz1InetTelnetOptPresent_suppressGoAhead, TRUE);
	}
}

static bool_t _setLocalGA(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	return TRUE;
}

static void _repliedLocalGA(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
}

///////////////////////////////////////////////////////////////////////////////
// Terminal Type
///////////////////////////////////////////////////////////////////////////////
static bool_t _setPeerTType(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	Dz1Thread_printf("_setPeerTType() : PEER Try Set Peer Terminal Type Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
	return TRUE;
}

static void _repliedPeerTType(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
	Dz1Thread_printf("_repliedPeerTType() : PEER Confirm to Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
}

static bool_t _setLocalTType(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	Dz1Thread_printf("_setLocalTType() : PEER Try Set Local Terminal Type Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
	return TRUE;
}

static void _repliedLocalTType(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
	Dz1Thread_printf("_repliedLocalTType() : PEER Confirm to Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
}

static void _subNegoTType(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOpt *subNego)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetOptTerminalType *ttype = subNego->x.terminalType;
	if (ttype->present == Dz1InetTelnetOptTerminalTypePresent_send)
	{	// SEND
		Dz1InetTelnetMsg *msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetTelnetCmd *cmd = NULL;
			Dz1InetTelnetOptTerminalType *reply = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
			if ((cmd = msg->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_subNego, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((subNego = cmd->x.subNego = Dz1InetTelnetOpt_new(Dz1InetTelnetOptPresent_terminalType, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((reply = subNego->x.terminalType = Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_is, "xterm", &err)) == NULL) ERR_OUT(&err);
			else if ((err = _encodeAndSend(s, msg)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		}
	}
	else if (ttype->present == Dz1InetTelnetOptTerminalTypePresent_is)
	{	// IS
	}
}

///////////////////////////////////////////////////////////////////////////////
// Window Size
///////////////////////////////////////////////////////////////////////////////
static bool_t _setPeerWinSize(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	Dz1Thread_printf("_setPeerWinSize() : PEER Try Set Peer Window Size Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
	return TRUE;
}

static void _repliedPeerWinSize(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
	Dz1Thread_printf("_repliedPeerWinSize() : PEER Confirm to Window Size Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
}

static bool_t _setLocalWinSize(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val)
{
	Dz1Thread_printf("_setLocalWinSize() : PEER Try Set Local Window Size Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
	return TRUE;
}

static void _repliedLocalWinSize(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e)
{
	Dz1Thread_printf("_repliedLocalWinSize() : PEER Confirm to Window Size Negotiation %s\n", val == TRUE ? "TRUE" : "FALSE");
	if (val == TRUE)
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1InetTelnetMsg *msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetTelnetCmd *cmd = NULL;
			Dz1InetTelnetOpt *subNego = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
			if ((cmd = msg->x.cmd = Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_subNego, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((subNego = cmd->x.subNego = Dz1InetTelnetOpt_new(Dz1InetTelnetOptPresent_windowSize, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((subNego->x.windowSize = Dz1InetTelnetOptWindowSize_new(80, 25, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _encodeAndSend(s, msg)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// TCP Socket Receiver Callback Functions
///////////////////////////////////////////////////////////////////////////////
static Dz1Error _myTelnetInit(void **ret, void *userParam, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *s)
{
	u16_t port;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetNVT *nvt = (Dz1InetTelnetNVT *)userParam;
	if ((err = Dz1SockAddr_getPort(peer, &port)).code) ERR_OUT(&err);
	else if (port == 23)
	{
		if ((err = Dz1InetTelnetNVT_optSetPeer(nvt, s, Dz1InetTelnetOptPresent_suppressGoAhead, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1InetTelnetNVT_optSetLocal(nvt, s, Dz1InetTelnetOptPresent_suppressGoAhead, TRUE)).code) ERR_OUT(&err);
		else if ((err = Dz1InetTelnetNVT_optSetLocal(nvt, s, Dz1InetTelnetOptPresent_terminalType, TRUE)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1SocketReceierBehavior _myTelnetForward(void *userParam, void *userResource,
												Dz1SockAddr *peer, Dz1SockAddr *local,
												Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
	Dz1InetTelnetNVT *nvt = (Dz1InetTelnetNVT *)userParam;
	Dz1InetTelnetMsg *msg = NULL;
	u8_t *cp = data;
	ssize_t status;
	while(size)
	{
		if ((status = Dz1InetTelnetPI_decode(&msg, cp, size, errp)) < 0) { ERR_OUT(errp); ret = Dz1SocketReceierBehavior_exception; break; }
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
			cp += status;
			size -= status;
			if ((*errp = Dz1InetTelnetNVT_recv(nvt, s, msg)).code) ERR_OUT(errp);
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		}
	}
	return ret;
}

void _myDataConsume(void *uRsc, u8_t *data, size_t size)
{
	while(size--) Dz1Thread_printf("%c", (char)*data++);
}

void _myInputEvent(void *uRsc, Dz1InetTelnetNVTPrinterEvent event)
{
	switch(event)
	{
	case Dz1InetTelnetNVTPrinterEvent_bell:
		break;
	case Dz1InetTelnetNVTPrinterEvent_ec:
		Dz1Thread_printf("\b");
		break;
	case Dz1InetTelnetNVTPrinterEvent_htab:
		Dz1Thread_printf("\t");
		break;
	case Dz1InetTelnetNVTPrinterEvent_lf:
		break;
	case Dz1InetTelnetNVTPrinterEvent_vtab:
		break;
	case Dz1InetTelnetNVTPrinterEvent_ff:
		break;
	case Dz1InetTelnetNVTPrinterEvent_cr:
		Dz1Thread_printf("<CR>\n");
		break;
	case Dz1InetTelnetNVTPrinterEvent_crlf:
		Dz1Thread_printf("\n");
		break;
	case Dz1InetTelnetNVTPrinterEvent_el:
		break;
	}
}

static void _myTelnetException(void *userParam, void *userResource,
						 Dz1SockAddr *peer, Dz1SockAddr *local,
						 Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("_myException() : called\n");
}

///////////////////////////////////////////////////////////////////////////////
// Shell Command : OPEN
///////////////////////////////////////////////////////////////////////////////
static void shell_open_usage(str_t n) { Dz1Thread_printf("Usage] %s <ip> [<port>]\n", n); }
static Dz1ShellCmdReturn shell_open(void *param, int argc, char *argv[])
{

	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	TestEnv *env = (TestEnv *)param;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc != 2 && argc != 3) shell_open_usage(argv[0]);
	else if (env->sock != NULL) Dz1Thread_printf("Already Connected\n");
	else
	{
		struct timeval to = { 1, 0 };
		Dz1SockAddr peer, local;
		u16_t port = 23;
		

		memset(&peer, 0, sizeof(Dz1SockAddr));
		memset(&local, 0, sizeof(Dz1SockAddr));

		if (argc == 3) port = (u16_t)atoi(argv[2]);

		if ((err = Dz1SockAddr_setAddrStr(&peer, argv[1])).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);

		else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(&err);

		else if ((env->sock = Dz1TcpClientSocket_open(&peer, &local, &to, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetTelnetNVTOptValue defValue = { FALSE, FALSE };
			Dz1InetTelnetNVTOptEntry defEntry = { &defValue, &defValue };
			Dz1InetTelnetNVTOpt opts[] =
			{
				{
					Dz1InetTelnetOptPresent_suppressGoAhead,
					&defEntry,
					_setPeerGA,
					_repliedPeerGA,
					_setLocalGA,
					_repliedLocalGA,
					NULL
				},
				{
					Dz1InetTelnetOptPresent_windowSize,
					&defEntry,
					_setPeerWinSize,
					_repliedPeerWinSize,
					_setLocalWinSize,
					_repliedLocalWinSize,
					NULL
				},
				{
					Dz1InetTelnetOptPresent_terminalType,
					&defEntry,
					_setPeerTType,
					_repliedPeerTType,
					_setLocalTType,
					_repliedLocalTType,
					_subNegoTType
				}
			};
			Dz1InetTelnetNVT *nvt = NULL;
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);

			if ((nvt = Dz1InetTelnetNVT_new(80, 25, _myDataConsume, _myInputEvent,
											opts, sizeof(opts) / sizeof(Dz1InetTelnetNVTOpt),
											NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1InetTelnetNVT_delAndSetNull, (void *)&nvt);
				if ((env->rcvr = Dz1TcpSocketReceiver_start(&peer, &local, 4096, 0, &env->sock, FALSE,
														_myTelnetInit, _myTelnetForward, _myTelnetException, NULL, NULL,
														(void *)&nvt, (Dz1DelFunc)Dz1InetTelnetNVT_del, &err)) == -1) ERR_OUT(&err);
				pthread_cleanup_pop(1); // (Dz1InetTelnetNVT_delAndSetNull, (void *)&nvt);
			}
			pthread_cleanup_pop(err.code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);
		}
	}
	return ret;
}

static struct Dz1InetTelnetOptPresentMap
{
	Dz1InetTelnetOptPresent		present;
	str_t						str1;
	str_t						str2;
} Dz1InetTelnetOptPresentMap[] =
{
	{ Dz1InetTelnetOptPresent_suppressGoAhead, "SGA", "sga" },
	{ Dz1InetTelnetOptPresent_max, NULL, NULL }
};

static Dz1InetTelnetOptPresent Dz1InetTelnetOptPresentFromStr(str_t str)
{
	struct Dz1InetTelnetOptPresentMap *i;
	for (i = Dz1InetTelnetOptPresentMap; i->present != Dz1InetTelnetOptPresent_max; i++)
		if (strcmp(i->str1, str) == 0 || strcmp(i->str2, str) == 0) return i->present;
	return Dz1InetTelnetOptPresent_max;
}

static void shell_send_opt_usage(str_t n, str_t cmd)
{
	struct Dz1InetTelnetOptPresentMap *i = NULL;
	Dz1Thread_printf("Usage] %s %s <opt> <args...>\n", n, cmd);
	Dz1Thread_printf("   opt = ");
	for (i = Dz1InetTelnetOptPresentMap; i->present != Dz1InetTelnetOptPresent_max; i++)
		Dz1Thread_printf("% s", i->str1);
	Dz1Thread_printf("\n");
}

static void shell_send_do_usage(str_t n) { shell_send_opt_usage(n, "do"); }
static void shell_send_do(TestEnv *env, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetOptPresent present;
	Dz1InetTelnetMsg *msg = NULL;
	if (argc < 2) shell_send_do_usage(n);
	else if ((present = Dz1InetTelnetOptPresentFromStr(argv[1])) == Dz1InetTelnetOptPresent_max) shell_send_do_usage(n);
	else if ((err = _genCmdAndSend(env->sock, Dz1InetTelnetCmdPresent_doOpt, present)).code) ERR_OUT(&err);
}

static void shell_send_dont_usage(str_t n) { shell_send_opt_usage(n, "dont"); }
static void shell_send_dont(TestEnv *env, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetOptPresent present;
	Dz1InetTelnetMsg *msg = NULL;
	if (argc < 2) shell_send_dont_usage(n);
	else if ((present = Dz1InetTelnetOptPresentFromStr(argv[1])) == Dz1InetTelnetOptPresent_max) shell_send_dont_usage(n);
	else if ((err = _genCmdAndSend(env->sock, Dz1InetTelnetCmdPresent_dontOpt, present)).code) ERR_OUT(&err);
}

static void shell_send_will_usage(str_t n) { shell_send_opt_usage(n, "will"); }
static void shell_send_will(TestEnv *env, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetOptPresent present;
	Dz1InetTelnetMsg *msg = NULL;
	if (argc < 2) shell_send_will_usage(n);
	else if ((present = Dz1InetTelnetOptPresentFromStr(argv[1])) == Dz1InetTelnetOptPresent_max) shell_send_will_usage(n);
	else if ((err = _genCmdAndSend(env->sock, Dz1InetTelnetCmdPresent_willOpt, present)).code) ERR_OUT(&err);
}

static void shell_send_wont_usage(str_t n) { shell_send_opt_usage(n, "wont"); }
static void shell_send_wont(TestEnv *env, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetOptPresent present;
	Dz1InetTelnetMsg *msg = NULL;
	if (argc < 2) shell_send_will_usage(n);
	else if ((present = Dz1InetTelnetOptPresentFromStr(argv[1])) == Dz1InetTelnetOptPresent_max) shell_send_will_usage(n);
	else if ((err = _genCmdAndSend(env->sock, Dz1InetTelnetCmdPresent_wontOpt, present)).code) ERR_OUT(&err);
}

static void shell_send_usage(str_t n) { Dz1Thread_printf("Usage] %s <do|dont|will|wont> <args...>\n", n); }
static Dz1ShellCmdReturn shell_send(void *param, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	TestEnv *env = (TestEnv *)param;

	if (argc < 2) shell_send_usage(argv[0]);
	else if (env->sock == NULL) Dz1Thread_printf("Not Connected\n");
	else if (strcmp(argv[1], "do") == 0) shell_send_do(env, argv[0], argc - 1, &argv[1]);
	else if (strcmp(argv[1], "dont") == 0) shell_send_dont(env, argv[0], argc - 1, &argv[1]);
	else if (strcmp(argv[1], "will") == 0) shell_send_will(env, argv[0], argc - 1, &argv[1]);
	else if (strcmp(argv[1], "wont") == 0) shell_send_wont(env, argv[0], argc - 1, &argv[1]);
	else shell_send_usage(argv[0]);

	return ret;
}

static void shell_close_usage(str_t n) { Dz1Thread_printf("Usage] %s\n", n); }
static Dz1ShellCmdReturn shell_close(void *param, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	TestEnv *env = (TestEnv *)param;

	if (argc != 1) shell_close_usage(argv[0]);
	else if (env->sock == NULL) Dz1Thread_printf("Not Connected\n");
	else
	{
		if (env->rcvr != -1) Dz1TcpSocketReceiver_stop(env->rcvr); env->rcvr = -1;
		Dz1TcpClientSocket_close(env->sock); env->sock = NULL;
	}

	return ret;
}

static Dz1Error user_main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TestEnv env = { NULL, -1 };

	void *shell = NULL;
#ifndef UNIX_SYSTEM
	if ((shell = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#else
	if ((shell = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#endif
	else
	{
		pthread_cleanup_push(Dz1Shell_del, shell);
		if ((err = Dz1Shell_cmdReg(shell, "open", shell_open, (void *)&env, "Open TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "send", shell_send, (void *)&env, "Send Message to TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "close", shell_close, (void *)&env, "Close TCP Session")).code) { ERR_OUT(&err); }
		else Dz1Shell_start(shell, NULL);
		pthread_cleanup_pop(1); // (Dz1Shell_del, shell);
	}
	return err;
}

int main(void)
{
	int th = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_init();

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	if ((th = Dz1Thread_init(DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_MESSAGE, &err)) < 0) { ERR_OUT(&err); }
	else if ((err = user_main()).code) { ERR_OUT(&err); }

#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Winsock Initializer Fail\n");
#endif
	return err.code;
}
