#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket_callback.h>

#include <Dz1TcpSerialServer.h>
#include <Dz1TcpSerialServerCfgUtil.h>

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
	Dz1Thread_printf("dz1_tcp_serial_server : Exception Catched\n");
	ERR_OUT(reason);
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_tcp_serial_server", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_tcp_serial_server", &err)) == NULL) ERR_OUT(&err);
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

static Dz1Error _add_preset(Dz1TcpSerialServerPresetList *dst, str_t strAddr, u16_t port,
							u32_t serialPort, u32_t baud, u32_t bitPerByte,
							Dz1SerialParity parity, Dz1SerialStopBit stopBit, Dz1SerialXONXOFF flowXonXoff)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerPreset *node = Dz1TcpSerialServerPreset_new(serialPort, NULL, baud, bitPerByte, parity, stopBit, flowXonXoff, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr tempAddr;
		pthread_cleanup_push(Dz1TcpSerialServerPreset_delAndSetNull, (void *)&node);
		if ((*errp = Dz1SockAddr_setAddrStr(&tempAddr, strAddr)).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&tempAddr, port)).code) ERR_OUT(errp);
		else if ((node->presetListen = Dz1SockAddr_clone(&tempAddr, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerPreset_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _init_presets(Dz1TcpSerialServerPresetList *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if		((*errp = _add_preset(dst, "0.0.0.0", 10907, 7, 115200, 8, Dz1SerialParity_none, Dz1SerialStopBit_one, Dz1SerialXONXOFF_off)).code) ERR_OUT(errp);
//	else if ((*errp = _add_preset(dst, "0.0.0.0", 10902, 2, 115200, 8, Dz1SerialParity_none, Dz1SerialStopBit_one, Dz1SerialXONXOFF_off)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_create(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1TcpSerialServerConfig *ret = Dz1TcpSerialServerConfig_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr tempAddr;
		pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1SockAddr_setAddrStr(&tempAddr, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&tempAddr, 10980)).code) ERR_OUT(errp);
		else if ((ret->emulater = Dz1SockAddr_clone(&tempAddr, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _init_presets(ret->presets)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
	}
	return ret;
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	void *task = NULL;
	Dz1TcpSerialServerConfig *cfg = NULL;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_tcp_serial_serverTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	if ((*errp = Dz1SocketCallback2_init()).code) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketCallback2_initCancel, NULL);
		// Edit Task Argument
		if ((cfg = Dz1TcpSerialServerConfigFile_load(".", "Dz1TcpServer.cfg", errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&cfg);
			if ((task = Dz1TcpSerialServer_new(cfg, _task_exception_handler, NULL, &err)) == NULL) ERR_OUT(&err);
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
			pthread_cleanup_pop(1); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&cfg);
		}
		pthread_cleanup_pop(1); // (Dz1SocketCallback2_initCancel, NULL);
	}
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
