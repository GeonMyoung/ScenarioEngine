#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_vfs.h>

#ifdef _DEBUG
#include <conio.h>
#endif

#include "dz1_vfs_test_codec.h"

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

typedef struct Dz1VfsTestEnv
{
	Dz1MetaTagDB		*tagDB;
	Dz1Vfs				*fs;
} Dz1VfsTestEnv;
static void Dz1VfsTestEnv_cleanup(void *ptr)
{
	Dz1VfsTestEnv *p = (Dz1VfsTestEnv *)ptr;
	Dz1MetaTagDB_delAndSetNull(&p->tagDB);
	Dz1Vfs_closeAndsetNull(&p->fs);
}

///////////////////////////////////////////////////////////////////////////////
// CODEC TEST : DIR
static u32_t child_idx = 1000;
static Dz1Error _add_child(Dz1VfsChildList *dst, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsChildNode *node = Dz1VfsChildNode_new(NULL, child_idx++, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsChildNode_delAndSetNull, (void *)&node);
		if ((node->name = Dz1Asn1UTF8Str_newFromStr(name, "EUC-KR", errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1VfsChildNode_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _init_dirs(Dz1VfsChildList *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if		((*errp = _add_child(dst, "dir1")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "dir2")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "dir3")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "dir4")).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error _init_files(Dz1VfsChildList *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if		((*errp = _add_child(dst, "file1")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "file2")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "file3")).code) ERR_OUT(errp);
	else if ((*errp = _add_child(dst, "file4")).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static void _cmd_test_codec_dir(void *ptr, str_t pcmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsDir *p = Dz1VfsDir_gen(errp);
	if (p == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&p);
		if ((p->tags = Dz1MetaTagData_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _init_dirs(p->dirs)).code) ERR_OUT(errp);
		else if ((*errp = _init_files(p->files)).code) ERR_OUT(errp);
		else
		{
			p->idx = 100;
			p->parent_idx = 10;
			if ((*errp = Dz1VfsDirCodec_test(p, TRUE)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1VfsDir_delAndSetNull, (void *)&p);
	}
}
// CODEC TEST : DIR
///////////////////////////////////////////////////////////////////////////////

static void _cmd_test_codec_file(void *ptr, str_t pcmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsFile *p = Dz1VfsFile_new(100, Dz1MetaTagTargetType_audio, 101, NULL, errp);
	if (p == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagData *tags = NULL;
		pthread_cleanup_push(Dz1VfsFile_delAndSetNull, (void *)&p);
		if ((p->tags = tags = Dz1MetaTagData_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1VfsFileCodec_test(p, TRUE)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1VfsFile_delAndSetNull, (void *)&p);
	}
}

///////////////////////////////////////////////////////////////////////////////
// CODEC TEST
static void _cmd_codec_usage(str_t n) { Dz1Thread_printf("Usage] %s <dir | file>\n", n); }
static Dz1ShellCmdReturn _cmd_codec(void *ptr, int argc, char *argv[])
{
	str_t n = argv[0];
	if (argc < 2) _cmd_codec_usage(argv[0]);
	else if (strncmp(argv[1], "dir", strlen(argv[1])) == 0) _cmd_test_codec_dir(ptr, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "file", strlen(argv[1])) == 0) _cmd_test_codec_file(ptr, n, argc-1, &argv[1]);
	else _cmd_codec_usage(argv[0]);
	return Dz1ShellCmdReturn_ok;
}
// CODEC TEST
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// VFS TEST : Open
static void _cmd_vfs_open(void *ptr, str_t pcmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsTestEnv *env = (Dz1VfsTestEnv *)ptr;
	if (env->fs != NULL) Dz1Thread_printf("@@@ Already opened\n");
	else if ((env->fs = Dz1Vfs_open("sample.jvfs", errp)) == NULL) ERR_OUT(errp);
	else Dz1Thread_printf("@@@ Open Success\n");
}
// VFS TEST : Open
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// VFS TEST : Close
static void _cmd_vfs_close(void *ptr, str_t pcmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsTestEnv *env = (Dz1VfsTestEnv *)ptr;
	if (env->fs == NULL) Dz1Thread_printf("@@@ Not opened\n");
	else
	{
		Dz1Vfs_closeAndsetNull(&env->fs);
		Dz1Thread_printf("@@@ Closed\n");
	}
}
// VFS TEST : Close
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// VFS TEST
static void _cmd_vfs_usage(str_t n) { Dz1Thread_printf("Usage] %s <open | close>\n", n); }
static Dz1ShellCmdReturn _cmd_vfs(void *ptr, int argc, char *argv[])
{
	str_t n = argv[0];
	if (argc < 2) _cmd_vfs_usage(argv[0]);
	else if (strncmp(argv[1], "open", strlen(argv[1])) == 0) _cmd_vfs_open(ptr, n, argc-1, &argv[1]);
	else if (strncmp(argv[1], "close", strlen(argv[1])) == 0) _cmd_vfs_close(ptr, n, argc-1, &argv[1]);
//	else if (strncmp(argv[1], "file", strlen(argv[1])) == 0) _cmd_test_codec_file(ptr, n, argc-1, &argv[1]);
	else _cmd_vfs_usage(argv[0]);
	return Dz1ShellCmdReturn_ok;
}
// VFS TEST
///////////////////////////////////////////////////////////////////////////////

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_vfs", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_vfs", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "t", _cmd_codec, task, "CODEC Test Command")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "v", _cmd_vfs, task, "VFS Test Command")).code) ERR_OUT(&err);
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

	Dz1VfsTestEnv env = { NULL, NULL };
	pthread_cleanup_push(Dz1VfsTestEnv_cleanup, (void *)&env);

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_vfs_test.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	_shell_start((void *)&env);

#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif

	pthread_cleanup_pop(1); // (Dz1VfsTestEnv_cleanup, (void *)&env);

	return err.code;
}
