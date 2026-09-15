#include <dz1_cleanup.h>
#include <dz1_str.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_tdq.h>
#include "sample_tdq.h"
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

typedef struct TestEnv
{
	TCHAR				 db_name[256];
	Dz1TdqDbConnArg		 db_arg;
	Dz1TdqDbScheme		*scm;
} TestEnv;
static void TestEnv_cleanup(void *ptr)
{
	TestEnv *p = (TestEnv *)ptr;
	if (p->scm) Dz1TdqDbScheme_delAndSetNull(&p->scm);
}

////////////////////////////////////////////////////////////////////////////////
// cmd_init Root Command
static void cmd_conn_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_conn(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_conn_usage;
	Dz1Str n = argv[0];
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) _print_usage(n);
	else if (env->scm != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((env->scm = Dz1TdqDbScheme_new(&env->db_arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqDbScheme_delAndSetNull, (void *)&env->scm);
		if (sample_tdq_init(env->scm, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(Dz1T("DB Connected\n"));
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqDbScheme_delAndSetNull, (void *)&env->scm);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_init Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_clean Root Command
static void cmd_disconn_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_disconn(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_disconn_usage;
	Dz1Str n = argv[0];
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) _print_usage(n);
	else if (env->scm == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TdqDbScheme_del(env->scm);
		env->scm = NULL;
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_clean Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_db Root Command
static void _db_create_rollback(void *ptr)
{
	TestEnv *env = (TestEnv *)ptr;
	Dz1TdqDbScheme_destroyDB(env->scm, env->db_name, TRUE, NULL);
}

static void cmd_db_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <select|create|drop>\n"), n); }
static Dz1ShellCmdReturn cmd_db(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_db_usage;
	Dz1Str n = argv[0];
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 2) _print_usage(n);
	else if (env->scm == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (Dz1STRCMP(argv[1], "select") == 0 || Dz1STRCMP(argv[1], "s") == 0)
	{
		if (Dz1TdqDbScheme_selectDB(env->scm, env->db_name, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(Dz1T("%s DB selected\n"), env->db_name);
			Dz1Error_set(errp, 0);
		}
	}
	else if (Dz1STRCMP(argv[1], "create") == 0 || Dz1STRCMP(argv[1], "c") == 0)
	{
		if (Dz1TdqDbScheme_createDB(env->scm, env->db_name, TRUE, errp) == FALSE) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(_db_create_rollback, (void *)env);
			if (Dz1TdqDbScheme_selectDB(env->scm, env->db_name, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1TdqDbScheme_buildDB(env->scm, TRUE, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf(Dz1T("%s DB generated\n"), env->db_name);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (_db_create_rollback, (void *)env);
		}
	}
	else if (Dz1STRCMP(argv[1], "drop") == 0 || Dz1STRCMP(argv[1], "d") == 0)
	{
		if (Dz1TdqDbScheme_destroyDB(env->scm, env->db_name, TRUE, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(Dz1T("%s DB destroied\n"), env->db_name);
			Dz1Error_set(errp, 0);
		}
	}
	else _print_usage(n);

	return Dz1ShellCmdReturn_ok;
}
// cmd_db Root Command
////////////////////////////////////////////////////////////////////////////////

/*
typedef struct Dz1TdqDbConnArg
{
	Dz1Str					 drv_name;
	Dz1Str					 svr_addr;
	u16_t					 svr_port;
	Dz1Str					 user;
	Dz1Str					 pw;
	Dz1Str					 dbn_opt;		// DB Name
} Dz1TdqDbConnArg;
*/
static void _shell_start(void *ptr)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

	TestEnv env = {
		Dz1T("Dz1TdqTestDB"),
		{
			MARIA_DB_DRIVER_3_1,
			Dz1T("192.168.0.254"), 3307,
			Dz1T("root"), Dz1T("dlshaqhkfk"),
			NULL
		},
		NULL
	};
	pthread_cleanup_push(TestEnv_cleanup, (void *)&env);
#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_code_gen", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_code_gen", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push(Dz1Shell_del, (void *)sh);

		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "o", cmd_conn, (void *)&env, "connect to DB")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "x", cmd_disconn, (void *)&env, "disconnect from DB")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "db", cmd_db, (void *)&env, "DB manipulate")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
	pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_tdq_test.log.txt", "wb")) != NULL)
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
