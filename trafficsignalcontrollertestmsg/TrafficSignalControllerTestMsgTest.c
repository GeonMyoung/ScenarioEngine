#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
//#include <TrafficSignalControllerTestMsg.h>

#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#endif // UNIX_SYSTEM

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

static void _shell_start(void *task)
{
	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("TrafficSignalControllerTestMsg"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("TrafficSignalControllerTestMsg"), errp)) == NULL) ERR_OUT(errp);
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

#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR *argv[])
#else // UNIX_SYSTEM
int main(int argc, char *argv[])
#endif // UNIC_SYSTEM
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("TrafficSignalControllerTestMsgTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "Win sock Initialize Fail\n"); return EFAULT; }
	else _shell_start(NULL);

	Dz1Socket_cleanup();

#ifdef _DEBUG
#ifdef UNICODE
	wprintf(L"Press Any Key...\n");
#else
	printf("Press Any Key...\n");
#endif // UNICODE
	Dz1Thread_getch(-1, NULL);
#endif // _DEBUG
	return errp->code;
}
