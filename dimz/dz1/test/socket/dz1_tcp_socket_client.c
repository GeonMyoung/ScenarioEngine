#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_shell.h>
#include <dz1_malloc.h>

#include <dz1_socket_receiver.h>
#include <dz1_socket_connector.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif

#ifdef WIN32
#include <conio.h>
#endif

static FILE *logfp = NULL;
static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }

typedef struct TestEnv
{
	Dz1TcpClientSocket	*sock;
	u32_t				 rcvr;
} TestEnv;

static void TestEnv_clean(void *ptr)
{
	TestEnv *env = (TestEnv *)ptr;
	if (env->sock != NULL) Dz1TcpClientSocket_closeAndSetNull(&env->sock);
	if (env->rcvr != (u32_t)-1) Dz1TcpSocketReceiver_stop(env->rcvr); env->rcvr = -1;
}

#define SOCKET_NATIVE		1
#define SOCKET_CALLBACK		2
#define SOCKET_CALLBACK_SSL	3

//#define SOCKET_MODE			SOCKET_NATIVE
#define SOCKET_MODE			SOCKET_CALLBACK
//#define SOCKET_MODE			SOCKET_CALLBACK_SSL

#if (SOCKET_MODE == SOCKET_NATIVE)
static void _myException(void *uArg, void *userResource,
						 Dz1SockAddr *peer, Dz1SockAddr *local,
						 Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("_myException() : called\n");
}

static Dz1SocketReceierBehavior _myForward(void *uArg, void *userResource,
										   Dz1SockAddr *peer, Dz1SockAddr *local,
										   Dz1TcpClientSocket *s, u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1Thread_printf("_myForward() Called\n");
	Dz1Thread_tprintb(1, data, size, 16);
	return Dz1SocketReceierBehavior_continue;
}
#elif ((SOCKET_MODE == SOCKET_CALLBACK) || (SOCKET_MODE == SOCKET_CALLBACK_SSL))
static void _rx_inform(void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local,
					   u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1Thread_printf("_rx_inform() Called\n");
	if (data == NULL || size == 0)
		ERR_OUT(errp);
	else
		Dz1Thread_tprintb(1, data, size, 16, TRUE);
}

static void _tx_done(void *arg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *errp)
{
	Dz1Thread_printf("_tx_done() last send command complete\n");
}
#endif

static void shell_open_usage(str_t n) { Dz1Thread_printf("Usage] %s <ip> <port>\n", n); }
static Dz1ShellCmdReturn shell_open(void *param, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	if (argc >= 2 && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0)) shell_open_usage(argv[0]);
	else
	{
		TestEnv *env = (TestEnv *)param;
		Dz1Error err = DZ1_ERROR_INITIALIZER;

		if (env->sock != NULL) Dz1Thread_printf("Already Connected\n");
		else
		{
			struct timeval to = { 1, 0 };
			str_t strIP = "127.0.0.1";
			u16_t port = 9999;
			
			Dz1SockAddr peer, local;

			memset(&peer, 0, sizeof(Dz1SockAddr));
			memset(&local, 0, sizeof(Dz1SockAddr));
			if (argc >= 2) strIP = argv[1];
			if (argc >= 3) port = (u16_t)atoi(argv[2]);

			if ((err = Dz1SockAddr_setAddrStr(&peer, strIP)).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);

			else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(&err);
			else if ((env->sock = Dz1TcpClientSocket_open(&peer, &local, &to, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);
#if SOCKET_MODE == SOCKET_NATIVE
				if ((env->rcvr = Dz1TcpSocketReceiver_start(&peer, &local, 4096, 0, &env->sock, FALSE,
														NULL, _myForward, _myException, NULL, NULL,
														NULL, NULL, &err)) == -1) ERR_OUT(&err);
#elif SOCKET_MODE == SOCKET_CALLBACK
				//if ((err = Dz1TcpClientSocket_modeCallback(env->sock, &peer, &local, 4096, _rx_inform, NULL, NULL, _tx_done, NULL, NULL)).code) ERR_OUT(&err);
				if ((err = Dz1SocketCallback2_associate(env->sock, &peer, &local, 4096,
														_rx_inform, _tx_done, NULL, NULL)).code) ERR_OUT(&err);
#elif SOCKET_MODE == SOCKET_CALLBACK_SSL
#ifdef _DZ1_USE_SSL
				if ((err = Dz1TcpClientSocket_modeSSLClient(env->sock, &peer, &local, 4096,
															_rx_inform, NULL, NULL,
															_tx_done, NULL, NULL,
															Dz1TcpClientSocketSSLClientMode_auto, "SEED-SHA:AES256-SHA")).code) ERR_OUT(&err);
#else
#error "Select SSL Build Mode or Change SOCKET_MODE to non SSL Mode"
#endif
#endif
				pthread_cleanup_pop(err.code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);
			}
		}
	}
	return ret;
}

static Dz1ShellCmdReturn shell_open2(void *param, int argc, char *argv[])
{

	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	TestEnv *env = (TestEnv *)param;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

//	if (argc != 3) shell_open_usage(argv[0]);
	if (env->sock != NULL) Dz1Thread_printf("Already Connected\n");
	else
	{
		str_t strIP = "127.0.0.1";
		u16_t port = 9999;
		struct timeval to = { 1, 0 };
		Dz1SockAddr peer, local;

		memset(&peer, 0, sizeof(Dz1SockAddr));
		memset(&local, 0, sizeof(Dz1SockAddr));

		if (argc >= 2) strIP = argv[1];
		if (argc >= 3) port = (u16_t)atoi(argv[2]);

		if ((err = Dz1SockAddr_setAddrStr(&peer, strIP)).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);

		else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(&err);
		else if ((env->sock = Dz1TcpClientSocket_open(&peer, &local, &to, &err)) == NULL) ERR_OUT(&err);
		else Dz1TcpClientSocket_closeAndSetNull((void *)&env->sock);
	}
	return ret;
}

static Dz1ShellCmdReturn shell_open3(void *param, int argc, char *argv[])
{

	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	TestEnv *env = (TestEnv *)param;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

//	if (argc != 3) shell_open_usage(argv[0]);
	if (env->sock != NULL) Dz1Thread_printf("Already Connected\n");
	else
	{
		str_t strIP = "127.0.0.1";
		u16_t port = 9999;
		struct timeval to = { 1, 0 };
		Dz1SockAddr peer, local;

		memset(&peer, 0, sizeof(Dz1SockAddr));
		memset(&local, 0, sizeof(Dz1SockAddr));

		if (argc >= 2) strIP = argv[1];
		if (argc >= 3) port = (u16_t)atoi(argv[2]);

		if ((err = Dz1SockAddr_setAddrStr(&peer, strIP)).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);

		else if ((err = Dz1SockAddr_setAddrStr(&local, "0.0.0.0")).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(&err);
		else if ((env->sock = Dz1TcpClientSocket_open(&peer, &local, &to, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);
			if (0) { }
#if (SOCKET_MODE == SOCKET_CALLBACK)
			//else if ((err = Dz1TcpClientSocket_modeCallback(env->sock, &peer, &local, 4096, _rx_inform, NULL, NULL, _tx_done, NULL, NULL)).code) ERR_OUT(&err);
			else if ((err = Dz1SocketCallback2_associate(env->sock, &peer, &local, 4096,
														 _rx_inform, _tx_done, NULL, NULL)).code) ERR_OUT(&err);
#elif (SOCKET_MODE == SOCKET_CALLBACK_SSL)
#ifdef _DZ1_USE_SSL
			else if ((err = Dz1TcpClientSocket_modeSSLClient(env->sock, &peer, &local, 4096,
															 _rx_inform, NULL, NULL,
															 _tx_done, NULL, NULL,
															 Dz1TcpClientSocketSSLClientMode_v3,
															 "SEED-SHA:AES256-SHA")).code) ERR_OUT(&err);
#else
#error "Select SSL Build Mode or chabge SOCKET_MODE to non SSL mode"
#endif
			else if ((env->sock->send(env->sock, (u8_t *)"12345", 5, DZ1_TCP_SOCK_FLAG_COMPLETE, &to, &err)) <= 0) ERR_OUT(&err);
#endif
			else Dz1TcpClientSocket_closeAndSetNull(&env->sock);
			pthread_cleanup_pop(err.code); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&env->sock);
		}
	}
	return ret;
}

static void shell_send_usage(str_t n) { Dz1Thread_printf("Usage] %s <args>\n", n); }
static Dz1ShellCmdReturn shell_send(void *param, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	TestEnv *env = (TestEnv *)param;

	if (argc == 1) shell_send_usage(argv[0]);
	else if (env->sock == NULL) Dz1Thread_printf("Not Connected\n");
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		int i;
		size_t size = 0;
		u8_t *buf = NULL;
		//Dz1TcpClientSocket *s = (Dz1TcpClientSocket *)param;

		for (i = 1; i < argc; i++) if (i == 1) size += strlen(argv[i]); else size += (1 + strlen(argv[i]));

		if ((buf = (u8_t *)Dz1Malloc(size + 1, &err)) == NULL) { ERR_OUT(&err); }
		else
		{
			char *cp = (char *)buf;
			size_t len = 0;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

			for (i = 1; i < argc; i++)
			{
				if (i == 1) len = sprintf(cp, "%s", argv[i]); else len = sprintf(cp, " %s", argv[i]);
				cp += len;
			}

			if (env->sock->send(env->sock, buf, size, TRUE, NULL, &err) <= 0) { ERR_OUT(&err); }

			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
	}

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
		if (env->rcvr != (u32_t)-1) Dz1TcpSocketReceiver_stop(env->rcvr); env->rcvr = -1;
		Dz1TcpClientSocket_close(env->sock); env->sock = NULL;
	}

	return ret;
}

static Dz1Error user_main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TestEnv env = { NULL, -1 };

	void *shell = NULL;
	pthread_cleanup_push(TestEnv_clean, (void *)&env);
#ifndef UNIX_SYSTEM
	if ((shell = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#else
	if ((shell = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#endif
	else
	{
		pthread_cleanup_push(Dz1Shell_del, shell);
		if ((err = Dz1Shell_cmdReg(shell, "o", shell_open, (void *)&env, "Open TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "o2", shell_open2, (void *)&env, "Open TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "o3", shell_open3, (void *)&env, "Open TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "s", shell_send, (void *)&env, "Send Message to TCP Session")).code) { ERR_OUT(&err); }
		else if ((err = Dz1Shell_cmdReg(shell, "c", shell_close, (void *)&env, "Close TCP Session")).code) { ERR_OUT(&err); }
		else Dz1Shell_start(shell, NULL);
		pthread_cleanup_pop(1); // (Dz1Shell_del, shell);
	}
	pthread_cleanup_pop(1); // (TestEnv_clean, (void *)&env);
	return err;
}

int main(void)
{
	int th = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_tcp_socket_client.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

	Dz1Cleanup_init();

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	if ((th = Dz1Thread_init(DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_MESSAGE, &err)) < 0) { ERR_OUT(&err); }

#ifdef _DZ1_USE_SSL
#if 0
	Dz1SocketCallback_sslInit();
	pthread_cleanup_push(Dz1SocketCallback_sslInitCancel, NULL);
#endif
#endif
//	if ((err = Dz1SocketCallbackSkel_init()).code) ERR_OUT(&err);
	if ((err = Dz1SocketCallback2_init()).code) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);

		if ((err = user_main()).code) { ERR_OUT(&err); }

		pthread_cleanup_pop(1); // (Dz1SocketCallback2_initCancel, NULL);
	}
#ifdef _DZ1_USE_SSL
#if 0
	pthread_cleanup_pop(1); // (Dz1SocketCallback_sslInitCancel, NULL);
#endif
#endif

#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("WinSock Initializer Fail\n");
#ifdef _DEBUG
#if (_MSC_VER < 1930)
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
#endif
	return err.code;
}
