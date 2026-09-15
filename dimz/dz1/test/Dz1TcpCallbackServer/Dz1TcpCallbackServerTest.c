#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket_callback.h>
#ifdef _DZ1_USE_SSL
#include <dz1_socket_callback_ssl.h>
#endif
#include <Dz1TcpCallbackServer.h>

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
	Dz1Thread_printf("Dz1TcpCallbackServer : Exception Catched\n");
	ERR_OUT(reason);
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackServer", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackServer", &err)) == NULL) ERR_OUT(&err);
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
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	void *task = NULL;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("Dz1TcpCallbackServerTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

#ifdef _DZ1_USE_SSL
	Dz1SocketCallback2SSL_init();
	pthread_cleanup_push(Dz1SocketCallback2SSL_initCancel, NULL);
#endif

//	if ((err = Dz1SocketCallbackSkel_init()).code) ERR_OUT(&err);
	if ((err = Dz1SocketCallback2_init()).code) ERR_OUT(&err);
	else
	{
//		pthread_cleanup_push(Dz1SocketCallbackSkel_initCancel, NULL);
		pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);
		// Edit Task Argument
		if ((task = Dz1TcpCallbackServer_new(19999, _task_exception_handler, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);
			//if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
			if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1Task_startCancel, (void *)task);

				_shell_start(task);

				pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)task);
			}
			pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&task);
		}
		pthread_cleanup_pop(1); // (Dz1SocketCallbackSkel_initCancel, NULL);
	}

#ifdef _DZ1_USE_SSL
	pthread_cleanup_pop(1); // (Dz1SocketCallback2SSL_initCancel, NULL);
#endif

#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif

#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return err.code;
}
