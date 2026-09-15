#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_storage.h>

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

static void _cmd_test_entry(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageChunkList *list = NULL;
	
	if ((list = Dz1Storage_getEntries(h, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageChunkList_delAndSetNull, (void *)&list);
		Dz1Thread_printf("Chunk Entries = "); Dz1StorageChunkList_dump(list, 0);
		pthread_cleanup_pop(1); // (Dz1StorageChunkList_delAndSetNull, (void *)&list);
	}
}

static void _cmd_test_alloc(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t idx = DZ1_STORAGE_FRAG_IDX_ERROR;
	
	if ((idx = Dz1Storage_alloc(h, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
	else Dz1Thread_printf("Allocated Entries IDX = %u\n", idx);
}

static void _cmd_test_free_usage(str_t n) { Dz1Thread_printf("Usage] %s <free_index>\n", n); }
static void _cmd_test_free(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	
	char n[64];
	sprintf(n, "%s free", parentCmd);

	if (argc < 2) _cmd_test_free_usage(n);
	else
	{
		u32_t idx = (u32_t)atoi(argv[1]);
		if (idx == 0) Dz1Thread_printf("Error : Index != 0\n");
		else if ((*errp = Dz1Storage_free(h, idx)).code) ERR_OUT(errp);
		else Dz1Thread_printf("Entries %u is freed\n", idx);
	}
}

static void _cmd_test_chk(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageInfo *info = Dz1Storage_analysis(h, errp);
	if (info == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageInfo_delAndSetNull, (void *)&info);
		Dz1Thread_printf("Status = "); Dz1StorageInfo_dump(info, 0);
		Dz1Thread_printf("Handle = "); Dz1Storage_dump(h, 0);
		pthread_cleanup_pop(1); // (Dz1StorageInfo_delAndSetNull, (void *)&info);
	}
}

static void _cmd_test_save_usage(str_t n) { Dz1Thread_printf("Usage] %s <entry_idx> <size>\n", n); }
static void _cmd_test_save(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	char n[64];
	sprintf(n, "%s save", parentCmd);
	if (argc < 2) _cmd_test_save_usage(n);
	else
	{
		u32_t idx = (u32_t)atoi(argv[1]);
		u32_t size = (u32_t)atoi(argv[2]);
		if (idx == 0) Dz1Thread_printf("Entry Index should not be 0\n");
		else if (size == 0) Dz1Thread_printf("size should not be 0\n");
		else
		{
			DZ1_ERROR_SAFE_VAR(errp, err);
			Dz1Binary *bin = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, size, errp);
			if (bin == NULL) ERR_OUT(errp);
			else
			{
				u32_t i;
				u8_t *cp = bin->data, v = 0;
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				for (i = 0; i < bin->size; i++) *cp++ = v++;
				if ((*errp = Dz1Storage_saveBin(h, idx, bin)).code) ERR_OUT(errp);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
		}
	}
}

static void _cmd_test_load_usage(str_t n) { Dz1Thread_printf("Usage] %s <entry_idx>\n", n); }
static void _cmd_test_load(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	char n[64];
	sprintf(n, "%s save", parentCmd);
	if (argc < 2) _cmd_test_load_usage(n);
	else
	{
		u32_t idx = (u32_t)atoi(argv[1]);
		if (idx == 0) Dz1Thread_printf("Entry Index should not be 0\n");
		else
		{
			DZ1_ERROR_SAFE_VAR(errp, err);
			Dz1Binary *bin = Dz1Storage_loadBin(h, idx, errp);
			if (bin == NULL) ERR_OUT(errp);
			else
			{
				u32_t i;
				u8_t *cp = bin->data, v = 0;
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				Dz1Thread_printf("%u Byte load\n", bin->size);
				for (i = 0; errp->code == 0 && i < bin->size; i++)
				{
					if (*cp != v) ERR_SET_OUT(errp, EFAULT);
					cp++; v++;
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
		}
	}
}

static void _cmd_test_sort(Dz1StorageHandle *h, str_t parentCmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1Sotrage_sort(h)).code) ERR_OUT(errp);
}

static void _cmd_test_usage(str_t n) { Dz1Thread_printf("Usage] %s <entry> <parameters...>\n", n); }
static Dz1ShellCmdReturn _cmd_test(void *h, int argc, char *argv[])
{
	str_t n = argv[0];
	if (argc < 2) _cmd_test_usage(n);
	else if (strncmp(argv[1], "entry", strlen(argv[1]) ) == 0) _cmd_test_entry(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "alloc", strlen(argv[1]) ) == 0) _cmd_test_alloc(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "free", strlen(argv[1]) ) == 0) _cmd_test_free(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "check", strlen(argv[1]) ) == 0) _cmd_test_chk(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "save", strlen(argv[1]) ) == 0) _cmd_test_save(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "load", strlen(argv[1]) ) == 0) _cmd_test_load(h, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "sort", strlen(argv[1]) ) == 0) _cmd_test_sort(h, n, argc-1, &argv[1]);
	return Dz1ShellCmdReturn_ok;
}

static void _shell_start(void *h)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_storage", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_storage", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "t", _cmd_test, h, "storage function test")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

#define _mk_magic(a, b, c, d)			(((u32_t)(a) & 0xFF) << 24 | \
										 ((u32_t)(b) & 0xFF) << 16 | \
										 ((u32_t)(c) & 0xFF) << 8 | \
										 ((u32_t)(d) & 0xFF))
int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1StorageHandle *h = NULL;
	bool_t is_created = FALSE;

	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_storageTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	if ((h = Dz1Storage_new2(".", "sample.jpat", _mk_magic('j', 'T', 'M', 'P'), &is_created, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Storage_delAndSetNull, (void *)&h);
		_shell_start(h);
		pthread_cleanup_pop(1); // (Dz1Storage_delAndSetNull, (void *)&h);
	}

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
