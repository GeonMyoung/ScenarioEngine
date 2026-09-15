#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_usleep.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include <Itsk00126v1TestScenario.h>

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
// Shell
static void _shell_start(void *task)
{
	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("Itsk00126V1TestScenario"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("Itsk00126V1TestScenario"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("command_name"), command_func, task, Dz1Text("command_description") )).code) ERR_OUT(errp);
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
	Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "Itsk00126V1TestScenario : Exception Catch\n");
	ERR_OUT(reason);
}

static bool_t _process_start(bool_t is_daemon, Dz1Error *errp)
{
	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("Itsk00126v1TestScenarioTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		fflush(logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, Dz1Text("Win sock Initialize Fail\n")); Dz1Error_set(errp, EFAULT); }
	else
	{
		TestEnv env = { NULL };
		pthread_cleanup_push(TestEnv_cleanup, (void *)&env);
		if ((env.task = Itsk00126V1TestScenario_new(NULL, NULL, _task_exception_handler, NULL, errp)) == NULL) ERR_OUT(errp);	// Edit Task Argument
		else if ((*errp = Dz1Task_start(env.task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void *)env.task);

			if (is_daemon) { while(1) Dz1Thread_usleep(1000000); }
			else _shell_start((void *)&env);

			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)env.task);
		}
		pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);
		Dz1Socket_cleanup();
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
