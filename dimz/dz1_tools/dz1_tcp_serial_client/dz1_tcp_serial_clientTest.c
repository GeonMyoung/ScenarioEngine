#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <Dz1TcpSerialClient.h>

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
	Dz1Thread_printf("dz1_tcp_serial_client : Exception Catched\n");
	ERR_OUT(reason);
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_tcp_serial_client", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_tcp_serial_client", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((err = Dz1Shell_cmdReg(sh, "{command}", {command_func}, task, "{command description}")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	void *task = NULL;
	Dz1SockAddr serverAddr;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_tcp_serial_clientTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	// Edit Task Argument
	if ((*errp = Dz1SockAddr_setAddrStr(&serverAddr, "127.0.0.1")).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&serverAddr, 10986)).code) ERR_OUT(errp);
	else if ((task = Dz1TcpSerialClient_new(&serverAddr, _task_exception_handler, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);
		if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void *)task);

			_shell_start(task);

			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)task);
		}
		pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&task);
	}
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");

#ifdef _DEBUG
	printf("Press Any Key...\n");
	Dz1Thread_getch(-1, NULL);
	fflush(stdin);
#endif

#endif
	return err.code;
}
