#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include <ITSK00144_2TestMsg.h>
#include <ITSK00144_2TestMsgSample.h>

#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#endif // UNIX_SYSTEM

static I2XTrafficSafetyDeviceSerialNo sample_id = { 0x4D, 9 };

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

////////////////////////////////////////////////////////////////////////////////
// cmd_init Root Command
static void cmd_init_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_init(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_init_usage;
	Dz1Str n = argv[0];
	//. *env = (. *)ptr;
	if (argc != 1) _print_usage(n);
	else
	{
		// Command Code Here
		if (ITSK00144_2TestMsg_initSample(errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_init Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_test Root Command
static void cmd_test_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_test(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_test_usage;
	Dz1Str n = argv[0];
	//. *env = (. *)ptr;
	if (argc != 1) _print_usage(n);
	else
	{
		ITSK00144_2ProtocolFrame* f = NULL;
		if ((f = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(&sample_id, 0, ITSK00144_2DataPresent_hb, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary* src = NULL;
			if ((src = ITSK00144_2ProtocolFrame_encode(f, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ITSK00144_2ProtocolFrame* f2 = NULL;
				if ((f2 = ITSK00144_2ProtocolFrame_decode(src, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ITSK00144_2ProtocolFrameContext* ctx = NULL;
					if ((ctx = ITSK00144_2ProtocolFrameContext_decode(f2->context, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
					else
					{
						ITSK00144_2ProtocolFrameContext_dump(ctx, 0);
					}
				}

			}
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_test Root Command
////////////////////////////////////////////////////////////////////////////////




static void _shell_start(void *task)
{
	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("ITSK001442TestMsg"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("ITSK001442TestMsg"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("command_name"), command_func, task, Dz1Text("command_description") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("init"), cmd_init, task, Dz1Text("init sample"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("test"), cmd_test, task, Dz1Text("test") )).code) ERR_OUT(errp);
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
	if ((logfp = Dz1FileStream_open(Dz1Text("ITSK00144_2TestMsgTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
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
