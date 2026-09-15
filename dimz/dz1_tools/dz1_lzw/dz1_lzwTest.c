#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_lzw.h>

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
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_lzw", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_lzw", &err)) == NULL) ERR_OUT(&err);
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

#define NATIVE_DATA			

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_lzwTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	u8_t native[] = {
		0x01, 0x01, 0x01, 0x01, 0x02,
		0x01, 0x02, 0x01, 0x02, 0x01,
		0x02, 0x02, 0x02, 0x01, 0x03,
		0x01, 0x03, 0x01, 0x03, 0x01,
		0x01, 0x02, 0x01, 0x02, 0x01,
		0x02, 0x02, 0x02, 0x01, 0x03,
		0x01, 0x02, 0x01, 0x02, 0x01,
		0x02, 0x02, 0x02, 0x01, 0x03
	};
	u32_t native_size = sizeof(native);
	u32_t min_bits = 2;

	u32_t codes[1024];
	u8_t compByte[1024];
	Dz1LzwCompStream comp = { codes, 1024, 0, compByte, 1024, 0, 0, 0 };

	Dz1Thread_printf("Natives\n");
	Dz1Thread_tprintb(1, native, native_size, 16, FALSE);

	if ((*errp = Dz1LzwCompress(&comp, native, native_size, min_bits)).code) ERR_OUT(errp);
	else
	{
		u32_t i;
		u8_t buf[1024];
		Dz1LzwDecompStream decomp = { buf, 1024, 0 };
		Dz1Thread_printf("Codes\n");
		for (i = 0; i < comp.arr_idx; i++)
			Dz1Thread_tprintf(1, "%08X\n", codes[i]);

		Dz1Thread_printf("Stream\n");
		Dz1Thread_tprintb(1, compByte, comp.byte_idx, 16, FALSE);

//		if ((*errp = Dz1LzwDecompress(&decomp, codes, comp.arr_idx, min_bits)).code) ERR_OUT(errp);
		if ((*errp = Dz1LzwDecompress(&decomp, compByte, comp.byte_idx, min_bits)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("Decompressed\n");
			Dz1Thread_tprintb(1, buf, decomp.arr_idx, 16, FALSE);
		}
	}

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
