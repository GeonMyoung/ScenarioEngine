#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_usleep.h>

#include <dz1_daemon.h>

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

static void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_daemon", errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_daemon", errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, "{command}", {command_func}, task, "{command description}")).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int debug_main(int argc, TCHAR *argv[])
{

	DZ1_ERROR_SAFE_VAR(errp, err);
#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win sock Initialize Fail\n"); return EFAULT; }
#endif

	_shell_start(NULL);


#ifndef UNIX_SYSTEM
	Dz1Socket_cleanup();
#endif
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return errp->code;
}

static bool_t is_done = FALSE;
static void perform(void *ptr)
{
	u32_t cnt = 0;
	while(is_done == FALSE)
	{
		Dz1Thread_printf("Count = %u\n", cnt++);
		Dz1Thread_usleep(1000 * 100);
		//Sleep(100);
	}
}

static void stop_perform(void *ptr)
{
	is_done = TRUE;
}


int main(int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	TCHAR path[4096], name[1024];
	if (Dz1Daemon_getMyPath(path, 4096, name, 1024, argv[0], errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
		if ((logfp = Dz1FileStream_open2(path, Dz1Text("dz1_daemon_text.log.txt"), Dz1Text("wb"), NULL)) != NULL)
			Dz1OutputHook_set(_outputHook, NULL);

		Dz1Thread_printf("path = %s\n", path);
		Dz1Thread_printf("name = %s\n", name);

		if (argc == 1) 
		{
			TCHAR *cp = Dz1STRRCHR(argv[0], DIR_SEP);
			if (cp == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				is_done = FALSE;
				if (Dz1DaemonMain(name, path, perform, stop_perform, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
#ifndef UNIX_SYSTEM
		else if (Dz1STRCMP(argv[1], Dz1Text("/I")) == 0 || Dz1STRCMP(argv[1], Dz1Text("/i")) == 0)
		{
			if (Dz1DaemonServiceCreate(name, Dz1Text("DZ1 Daemon Library Test Service"), argv[0], Dz1Text("dz1_daemon_test is dz1_daemon library test process"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("/U")) == 0 || Dz1STRCMP(argv[1], Dz1Text("/u")) == 0)
		{
			if (Dz1DaemonServiceDelete(name, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
#endif
		else if (Dz1STRCMP(argv[1], Dz1Text("/D")) == 0 || Dz1STRCMP(argv[1], Dz1Text("/d")) == 0)
		{
			int code = debug_main(argc-1, &argv[1]);
			if (code != 0) ERR_SET_OUT(errp, code);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("/H")) == 0 || Dz1STRCMP(argv[1], Dz1Text("/h")) == 0)
		{
			printf("Usage] %s {option}\n", name);
			printf("\toption:\t/I = Install Service\n");
			printf("\t\t\t\t/U = Uninstall Service\n");
			printf("\t\t\t\t/S = Service Mode\n");
			Dz1Error_set(errp, 0);
		}
		else
		{
			printf("Unknown Command... use \"/h\" option to see help\n");
			ERR_SET_OUT(errp, EINVAL);
		}
	}
	return errp->code;
}
