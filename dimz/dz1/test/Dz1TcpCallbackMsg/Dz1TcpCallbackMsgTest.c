#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <Dz1TcpCallbackMsgCodec.h>

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

static Dz1Binary *_getBinary(Dz1TcpCallbackMsg *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);

		if ((sz = Dz1TcpCallbackMsg_enc(NULL, -1, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1TcpCallbackMsg_enc(ret->data, ret->size, src, NULL, errp)) < 0) ERR_OUT(errp);
		else if (sz != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1TcpCallbackMsg *_getStruct(Dz1Binary *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpCallbackMsg *ret = Dz1TcpCallbackMsg_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);

		if ((sz = Dz1TcpCallbackMsg_dec(ret, src->data, src->size, NULL, errp)) < 0) ERR_OUT(errp);
		else if (sz != src->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _codecTest(Dz1TcpCallbackMsg *src, str_t subject, bool_t verbose)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Binary *bin = NULL;
	if (verbose)
	{
		Dz1Thread_printf("=================================================\n");
		Dz1Thread_printf("%s\n", subject);
		Dz1Thread_printf("=================================================\n");
		Dz1Thread_printf("Source = "); Dz1TcpCallbackMsg_dump(src, 0);
	}

	if ((bin = _getBinary(src, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1TcpCallbackMsg *dst = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("Encoded\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16, TRUE);
		}

		if ((dst = _getStruct(bin, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&dst);
			if (verbose)
			{
				Dz1Thread_printf("Decoded = ");
				Dz1TcpCallbackMsg_dump(dst, 0);
			}

			if ((chk = _getBinary(dst, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chk);
				if (Dz1Binary_cmp(chk, bin) != 0)
				{
					Dz1Thread_printf("CODEC Fault\n");
					ERR_SET_OUT(&err, EFAULT);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chk);
			}
			pthread_cleanup_pop(1); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&dst);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

static Dz1Error _codecTestEcho(bool_t verbose)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpCallbackMsg *msg =Dz1TcpCallbackMsg_new(Dz1TcpCallbackMsgPresent_echo, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		Dz1TimeVal stamp = Dz1TimeVal_get();
		Dz1TcpCallbackEcho *e = NULL;
		pthread_cleanup_push(Dz1TcpCallbackMsg_delAndSetNull, (void *)&msg);
		if ((msg->x.echo = e = Dz1TcpCallbackEcho_new(0x12345678, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((e->stamp = Dz1TimeVal_clone(&stamp, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _codecTest(msg, "Echo", verbose)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1TcpCallbackMsg_delAndSetNull, (void *)&msg);
	}
	return err;
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackMsg", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "Dz1TcpCallbackMsg", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = _codecTestEcho(TRUE)).code) ERR_OUT(&err);
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

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("Dz1TcpCallbackMsgTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	_shell_start(NULL);

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
