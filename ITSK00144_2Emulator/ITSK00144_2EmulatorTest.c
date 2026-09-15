#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_usleep.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include <ITSK00144_2Emulator.h>
#include <dz1_socket_callback.h>

#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#endif // UNIX_SYSTEM

////////////////////////////////////////////////////////////////////////////////
// Log-File
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
// Log-File
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Test-Env
typedef struct TestEnv
{
	void					*task;
} TestEnv;
static void TestEnv_cleanup(void *ptr)
{
	TestEnv *env = (TestEnv *)ptr;
	Dz1Task_delAndSetNull(&env->task);
}
// Test-Env
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_open Sub Command
static void cmd_server_open_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s port\n"), n); }
static void cmd_server_open(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_server_open_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("open"));

	if (argc != 2) _print_usage(n);
	else
	{
		u16_t port = (u16_t)(atoi(argv[1]));
		if (ITSK00144_2EmulatorServer_open(env->task, port, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}
// cmd_open Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_send Sub Command
static void cmd_server_send_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s opcode\n"), n); }
static void cmd_server_send(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv* env = (TestEnv*)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_server_send_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("send"));

	if (argc != 2) _print_usage(n);
	else
	{
		Dz1Str opcode = argv[1];
		if (ITSK00144_2EmulatorServer_send(env->task, opcode, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}
// cmd_send Sub Command
////////////////////////////////////////////////////////////////////////////////

static void cmd_server_dsrc_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s id\n"), n); }
static void cmd_server_dsrc(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv* env = (TestEnv*)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_server_dsrc_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("dsrc"));

	if (argc != 2) _print_usage(n);
	else
	{
		u16_t id = (u16_t)(atoi(argv[1]));
		if (ITSK00144_2EmulatorServer_dsrc(env->task, id, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}
// cmd_send Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_clear Sub Command
static void cmd_server_clear_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static void cmd_server_clear(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv* env = (TestEnv*)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_server_clear_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("clear"));

	if (argc != 1) _print_usage(n);
	else
	{
		if (ITSK00144_2EmulatorServer_clear(env->task, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

	}
}
// cmd_clear Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_server Root Command
static void cmd_server_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s [ open | send | clear | .. ]\n"), n); }
static Dz1ShellCmdReturn cmd_server(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_server_usage;
	Dz1Str n = argv[0];
	TestEnv *env = (TestEnv *)ptr;
	if (argc < 2) _print_usage(n);
	else
	{
		// Command Code Here
		if (errp->code) {}
		else if (Dz1STRCMP(argv[1], Dz1Text("open")) == 0 || Dz1STRCMP(argv[1], Dz1Text("o")) == 0) cmd_server_open(ptr, n, argc - 1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("send")) == 0 || Dz1STRCMP(argv[1], Dz1Text("s")) == 0) cmd_server_send(ptr, n, argc - 1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("clear")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_server_clear(ptr, n, argc - 1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("dsrc")) == 0 || Dz1STRCMP(argv[1], Dz1Text("d")) == 0) cmd_server_dsrc(ptr, n, argc-1, &argv[1]);
		else _print_usage(n);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_server Root Command
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// cmd_init Sub Command
static void cmd_client_init_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s port\n"), n); }
static void cmd_client_init(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_client_init_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("init"));

	if (argc != 2) _print_usage(n);
	else
	{
		// Command Code Here
//		if (errp->code) { }
//		else if (Dz1STRCMP(argv[1], Dz1Text("_long_sub_cmd_")) == 0 || Dz1STRCMP(argv[1], Dz1Text("_short_sub_cmd_")) == 0) _sub_cmd_(ptr, n, argc-1, &argv[1]);
//		else _print_usage(n);

		u16_t port = (u16_t)(atoi(argv[1]));

		if (ITSK00144_2EmulatorClient_init(env->task, port, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		
	}
}
// cmd_init Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_clear Sub Command
static void cmd_client_clear_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static void cmd_client_clear(void* ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestEnv *env = (TestEnv *)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_client_clear_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("clear"));

	if (argc != 1) _print_usage(n);
	else
	{
		if (ITSK00144_2EmulatorClient_clear(env->task, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	
	}
}
// cmd_clear Sub Command
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// cmd_client Root Command
static void cmd_client_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s [ init | .. ]\n"), n); }
static Dz1ShellCmdReturn cmd_client(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_client_usage;
	Dz1Str n = argv[0];
	TestEnv *env = (TestEnv *)ptr;
	if (argc < 2) _print_usage(n);
	else
	{
		// Command Code Here
		if (errp->code) {}
		else if (Dz1STRCMP(argv[1], Dz1Text("init")) == 0 || Dz1STRCMP(argv[1], Dz1Text("i")) == 0) cmd_client_init(ptr, n, argc - 1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("clear")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_client_clear(ptr, n, argc-1, &argv[1]);
		else _print_usage(n);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_client Root Command
////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////
// Shell
static void _shell_start(void *task)
{
	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("ITSK001442Emulator"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("ITSK001442Emulator"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("command_name"), command_func, task, Dz1Text("command_description") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("server"), cmd_server, task, Dz1Text("server emulator"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("client"), cmd_client, task, Dz1Text("client emulator") )).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}
// Shell
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Process-Entry
static void _task_exception_handler(void *ptr, Dz1Error *reason)
{
	Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "ITSK001442Emulator : Exception Catch\n");
	ERR_OUT(reason);
}

static bool_t _process_start(bool_t is_daemon, Dz1Error *errp)
{
	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("ITSK00144_2EmulatorTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		fflush(logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, Dz1Text("Win sock Initialize Fail\n")); Dz1Error_set(errp, EFAULT); }
	else
	{
		pthread_cleanup_push(Dz1Socket_initCancel, NULL);
		if ((*errp = Dz1SocketCallback2_init()).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);

			TestEnv env = { NULL };
			pthread_cleanup_push(TestEnv_cleanup, (void*)&env);
			if ((env.task = ITSK001442Emulator_new(_task_exception_handler, NULL, errp)) == NULL) ERR_OUT(errp);	// Edit Task Argument
			else if ((*errp = Dz1Task_start(env.task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Task_startCancel, (void*)env.task);

				if (is_daemon) { while (1) Dz1Thread_usleep(1000000); }
				else _shell_start((void*)&env);

				pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)env.task);
			}
			pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);
			Dz1Socket_cleanup();
			pthread_cleanup_pop(1); // (Dz1SocketCallback2_initCancel, NULL);
		}

		pthread_cleanup_pop(1); // (Dz1Socket_initCancel, NULL);
	}

#ifdef _DEBUG
	if (is_daemon == FALSE)
	{
		Dz1Thread_printf("press any key...\n");
		Dz1Thread_getch(-1, NULL);
	}
#endif // _DEBUG
	return errp->code == 0 ? TRUE : FALSE;
}
// Process-Entry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Main-Entry
#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR *argv[])
#else // UNIX_SYSTEM
int main(int argc, char *argv[])
#endif // UNIC_SYSTEM
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	// parse argv, choice fork or shell
	_process_start(FALSE, errp);

	return errp->code;
}
// Main-Entry
////////////////////////////////////////////////////////////////////////////////
