#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif
#include <Dz1TcpCallbackClient.h>

#ifdef _DEBUG
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

static void _task_exception_handler(void *ptr, Dz1Error *reason)
{
	Dz1Thread_printf("Dz1TcpCallbackClient : Exception Catched\n");
	ERR_OUT(reason);
}

typedef struct TestEnv
{
	void				*simulator;
	Dz1TcpClientSocket	*sock;
	Dz1SockAddr			*peer;
	Dz1SockAddr			*local;
} TestEnv;

static void TestEnv_clenaup(void *ptr)
{
	TestEnv *p = (TestEnv *)ptr;
	if (p->simulator != NULL)
	{
		Dz1Task_stop(p->simulator, FALSE);
		Dz1Task_wait(p->simulator, NULL);
		p->simulator = NULL;
	}

	Dz1TcpClientSocket_closeAndSetNull(&p->sock);
	Dz1SockAddr_delAndSetNull(&p->peer);
	Dz1SockAddr_delAndSetNull(&p->local);
}

///////////////////////////////////////////////////////////////////////////////
// Simulator Arg Parse
// -ssl -max=nnn -port=nnn [ip]
typedef struct TestParam
{
	bool_t		 useSSL;
	bool_t		 stress_mode;
	u32_t		 numOfConn;
	u16_t		 port;
	char		 strIP[64];
} TestParam;

static Dz1Error _parse_args(TestParam *dst, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int i;
	u32_t v32 = 0;

	dst->useSSL = FALSE;
	dst->stress_mode = FALSE;
	dst->numOfConn = 1;
	dst->port = (u16_t)-1;
	memset(dst->strIP, 0, 64);

	for (i = 1; errp->code == 0 && i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			char *cp = argv[i];
			cp++;	// pass '-'
			if (0) { }
			else if (strcmp(cp, "ssl") == 0) dst->useSSL = TRUE;
			else if (strcmp(cp, "stress") == 0) dst->stress_mode = TRUE;
			else if (strncmp(cp, "max", 3) == 0)
			{
				cp += 3;
				if (*cp != '=') ERR_SET_OUT(errp, EINVAL);
				else
				{
					cp++;	// pass '='
					if ((v32 = Dz1StrTo32(cp)) == 0) ERR_SET_OUT(errp, EINVAL);
					else dst->numOfConn = v32;
				}
			}
			else if (strncmp(cp, "port", 4) == 0)
			{
				cp += 4;
				if (*cp != '=') ERR_SET_OUT(errp, EINVAL);
				else
				{
					cp++;	// pass '='
					if ((v32 = Dz1StrTo32(cp)) == 0) ERR_SET_OUT(errp, EINVAL);
					else if (v32 > 0xFFFF) ERR_SET_OUT(errp, E2BIG);
					else dst->port = (u16_t)(v32 & 0xFFFF);
				}
			}
		}
		else
		{
			if (dst->strIP[0] == 0) strncpy(dst->strIP, argv[i], 63);
			else ERR_SET_OUT(errp, EEXIST);
		}
	}

	if (dst->port == (u16_t)-1)
	{
		dst->port = 19999;
		if (dst->useSSL == TRUE) dst->port++;
	}

	if (dst->strIP[0] == 0) strcpy(dst->strIP, "127.0.0.1");

	return err;
}
// Simulator Arg Parse
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _cmd_start Root Command
static void _cmd_start_usage(str_t n) { Dz1Thread_printf("Usage] %s [ip] [-port=nnn] [-max=nnn] [-ssl] [-stress]\n", n); }
static Dz1ShellCmdReturn _cmd_start(void *ptr, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	void *task = env->simulator;
	if (argc < 1 || argc > 5) _cmd_start_usage(argv[0]);
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		// Command Code Here
		TestParam param;
		Dz1SockAddr addr;
		if ((*errp = _parse_args(&param, argc, argv)).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setAddrStr(&addr, param.strIP)).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&addr, param.port)).code) ERR_OUT(errp);
		else if ((*errp = Dz1TcpCallbackClient_simulate_start(task, &addr, param.numOfConn, param.useSSL, param.stress_mode)).code) ERR_OUT(errp);
		//if (strcmp(argv[1], "_long_sub_cmd_") == 0 || strcmp(argv[1], "_short_sub_cmd_") == 0) _sub_cmd_(ptr, argv[0], argc-1, &argv[1]);
		else Dz1Error_set(errp, 0);
	}
	return Dz1ShellCmdReturn_ok;
}
// _cmd_start Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// _cmd_start Root Command
static void _cmd_stop_usage(str_t n) { Dz1Thread_printf("Usage] %s\n", n); }
static Dz1ShellCmdReturn _cmd_stop(void *ptr, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	void *task = env->simulator;
	if (argc != 1) _cmd_stop_usage(argv[0]);
	else
	{
		// Command Code Here
		DZ1_ERROR_SAFE_VAR(errp, err);
		if ((*errp = Dz1TcpCallbackClient_simulate_stop(task)).code) ERR_OUT(errp);
	}
	return Dz1ShellCmdReturn_ok;
}
// _cmd_start Root Command
////////////////////////////////////////////////////////////////////////////////

// static void _cmd_sock_usage(str_t n) { Dz1Thread_printf("Usage] %s <conn | disconn> ...\n", n); }
// static Dz1ShellCmdReturn _cmd_sock(void *ptr, int argc, char *argv[])
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	if (argc < 2) _cmd_sock_usage(argv[0]);
// 	else if (strcmp(argv[1], "conn") == 0) _cmd_sock_conn(ptr, argv[0], argc-1, &argv[1]);
// 	else if (strcmp(argv[1], "discon") == 0) _cmd_sock_conn(ptr, argv[0], argc-1, &argv[1]);
// 	else
// 	{
// 	}
// 	return Dz1ShellCmdReturn_ok;
// }

static void _shell_start(void *envp)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackClient", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackClient", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "start",_cmd_start,envp, "start socket simulation")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "stop", _cmd_stop, envp, "stop socket simulation")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("Dz1TcpCallbackClientTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

#ifdef _DZ1_USE_SSL
	Dz1SocketCallback2SSL_init();
	pthread_cleanup_push(Dz1SocketCallback2SSL_initCancel, NULL);
#endif

//	if ((*errp = Dz1SocketCallbackSkel_init()).code) ERR_OUT(errp);
	if ((*errp = Dz1SocketCallback2_init()).code) ERR_OUT(errp);
	else
	{
		TestEnv env = { NULL, NULL, NULL, NULL };
		pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);

		pthread_cleanup_push(TestEnv_clenaup, (void *)&env);
		if ((env.simulator = Dz1TcpCallbackClient_new(_task_exception_handler, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&env.simulator);
			//if ((*errp = Dz1Task_start(env->simulator, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);
			if ((*errp = Dz1Task_start(env.simulator, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Task_startCancel, (void *)env.simulator);

				_shell_start(&env);

				pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)env->simulator);
			}
			pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&env->simulator);
		}
		pthread_cleanup_pop(1); // (TestEnv_clenaup, (void *)&env);
		pthread_cleanup_pop(1); // (Dz1SocketCallback2_initInitCancel, NULL);
	}

#ifdef _DZ1_USE_SSL
	pthread_cleanup_pop(1); // (Dz1SocketCallback2SSL_initCancel, NULL);
#endif

#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");

#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif

#endif
	return err.code;
}
