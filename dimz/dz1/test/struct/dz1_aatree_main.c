#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_cleanup.h>
#include <dz1_malloc.h>
#include <dz1_aatree.h>

#include <dz1_shell.h>

typedef struct TestEnv
{
	Dz1AATree *tree;
	Dz1AATreeCursor *c;
} TestEnv;

static int dummyCmp(void *pa, void *pb)
{
	int a = (int)__DZ1PTR(pa), b = (int)__DZ1PTR(pb);
	if (a < b) return -1; else if (a > b) return 1; else return 0;
}

static void dummyDump(void *p, int tab)
{
	int data = (int)__DZ1PTR(p);
	Dz1Thread_tprintf(tab, "[%d]\n", data);
}

static void test_cmd_create_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s create\n", n);
}

static void test_cmd_create(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 1) test_cmd_create_usage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		TestEnv *env = (TestEnv *)param;
		if (env->tree) { Dz1Thread_printf("Already Created\n"); return; }
		if ((env->tree = Dz1AATree_new(dummyCmp, NULL, dummyDump, &err)))
		{
			Dz1AATreeCursor_delAndSetNull(&env->c);
			Dz1Thread_printf("Succedd\n");
		}
		else
			Dz1Error_print(&err, 0);
	}
}

static void test_cmd_add_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s add <value>\n", n);
}

static void test_cmd_add(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 2) test_cmd_add_usage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		int type = atoi(argv[1]);
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		if ((err = Dz1AATree_insert(env->tree, (void *)DZ1_VAL2PTR32(type))).code)
			ERR_OUT(&err);
		else
		{
			Dz1AATreeCursor_delAndSetNull(&env->c);
			Dz1Thread_printf("Done\n");
		}
	}
}

static void test_cmd_remove_usage(str_t n) { Dz1Thread_printf("Usage] %s rm <value>\n", n); }
static void test_cmd_remove(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 2) test_cmd_remove_usage(n);
	else
	{
		int type = atoi(argv[1]);
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		Dz1AATree_remove(env->tree, (void *)__DZ1PTR(type));
		Dz1AATreeCursor_delAndSetNull(&env->c);
		Dz1Thread_printf("Done\n");
	}
}

static bool_t func_yes(void *ptr, void *data) { return TRUE; }
static bool_t func_no(void *ptr, void *data) { return FALSE; }

static void test_cmd_remove_conditional_usage(str_t n) { Dz1Thread_printf("Usage] %s rmc <value> { y | n }\n", n); }
static void test_cmd_remove_conditional(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 3) test_cmd_remove_conditional_usage(n);
	else
	{
		bool_t exist = FALSE, remove;

		Dz1AATreeCheckFunc func = NULL;
		int type = atoi(argv[1]);
		TestEnv *env = (TestEnv *)param;

		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }

		if (strcmp(argv[2], "y") == 0) func = func_yes;
		else if (strcmp(argv[2], "n") == 0) func = func_no;
		else { test_cmd_remove_conditional_usage(n); return; }

		if ((remove = Dz1AATree_removeConditional(env->tree, (void *)DZ1_VAL2PTR32(type), func, NULL, &exist)) == TRUE)
			Dz1AATreeCursor_delAndSetNull(&env->c);

		Dz1Thread_printf("Existence = %d, Remove = %d\n", exist, remove);
	}
}

static void test_cmd_extract_usage(str_t n) { Dz1Thread_printf("Usage] %s ex <value>\n", n); }
static void test_cmd_extract(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 2) test_cmd_extract_usage(n);
	else
	{
		void *data = NULL;
		int type = atoi(argv[1]);
		TestEnv *env = (TestEnv *)param;

		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }

		if ((data = Dz1AATree_extract(env->tree, (void *)DZ1_VAL2PTR32(type))) != NULL)
			Dz1AATreeCursor_delAndSetNull(&env->c);

		Dz1Thread_printf("data = %p\n", data);
	}
}

static void test_cmd_extract_conditional_usage(str_t n) { Dz1Thread_printf("Usage] %s exc <value> { y | n }\n", n); }
static void test_cmd_extract_conditional(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 3) test_cmd_extract_conditional_usage(n);
	else
	{
		TestEnv *env = (TestEnv *)param;

		void *data = NULL;
		bool_t exist = FALSE;
		Dz1AATreeCheckFunc func = NULL;

		int type = atoi(argv[1]);
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }

		if (strcmp(argv[2], "y") == 0) func = func_yes;
		else if (strcmp(argv[2], "n") == 0) func = func_no;
		else { test_cmd_extract_conditional_usage(n); return; }

		if ((data = Dz1AATree_extractConditional(env->tree, (void *)__DZ1PTR(type), func, NULL, &exist)) != NULL)
			Dz1AATreeCursor_delAndSetNull(&env->c);

		Dz1Thread_printf("data = %p, Existence = %d\n", data, exist);
	}
}

static void test_cmd_find_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s find <value>\n", n);
}

static void test_cmd_find(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 2) test_cmd_find_usage(n);
	else
	{
		void *result = NULL;
		int type = atoi(argv[1]);
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		if ((result = Dz1AATree_find(env->tree, (void *)__DZ1PTR(type))))
			Dz1Thread_printf("Exist\n");
		else
			Dz1Thread_printf("Not Found\n");
	}
}

static void test_cmd_dump_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s dump\n", n);
}

static void test_cmd_dump(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 1) test_cmd_dump_usage(n);
	else
	{
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		Dz1AATree_dump(env->tree, 1);
	}
}

static void test_cmd_delete_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s delete\n", n);
}

static void test_cmd_delete(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 1) test_cmd_delete_usage(n);
	else
	{
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		Dz1AATree_delAndSetNull(&env->tree);
		Dz1AATreeCursor_delAndSetNull(&env->c);
		Dz1Thread_printf("Done\n");
	}
}

static void test_cmd_min_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s min\n", n);
}

static void test_cmd_min(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 1) test_cmd_min_usage(n);
	else
	{
		int data = 0;
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		data = (int)__DZ1PTR(Dz1AATree_min(env->tree));
		dummyDump((void *)__DZ1PTR(data), 1);
	}
}

static void test_cmd_max_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s max\n", n);
}

static void test_cmd_max(void *param, str_t n, int argc, char *argv[])
{
	if (argc != 1) test_cmd_max_usage(n);
	else
	{
		int data = 0;
		TestEnv *env = (TestEnv *)param;
		if (!env->tree) { Dz1Thread_printf("Not Created\n"); return; }
		data = (int)__DZ1PTR(Dz1AATree_max(env->tree));
		dummyDump((void *)__DZ1PTR(data), 1);
	}
}

static void test_cmd_usage(str_t n)
{
	Dz1Thread_printf("Usage] %s { create | delete | add | rm | rmc | ex | exc | dump | find | min | max } <parameter>\n", n);
}

static Dz1ShellCmdReturn test_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		test_cmd_usage(argv[0]);
	else
	{
		if (strcmp(argv[1], "create")==0 || strcmp(argv[1], "c")==0) test_cmd_create(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "delete")==0 || strcmp(argv[1], "d")==0) test_cmd_delete(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "add")==0 || strcmp(argv[1], "a")==0) test_cmd_add(param, argv[0], argc - 1, &argv[1]);

		else if (strcmp(argv[1], "rm")==0 || strcmp(argv[1], "r")==0) test_cmd_remove(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "rmc")==0 || strcmp(argv[1], "rc")==0) test_cmd_remove_conditional(param, argv[0], argc - 1, &argv[1]);

		else if (strcmp(argv[1], "ex")==0 || strcmp(argv[1], "e")==0) test_cmd_extract(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "exc")==0 || strcmp(argv[1], "ec")==0) test_cmd_extract_conditional(param, argv[0], argc - 1, &argv[1]);

		else if (strcmp(argv[1], "find")==0 || strcmp(argv[1], "f")==0) test_cmd_find(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "dump")==0 || strcmp(argv[1], "p")==0) test_cmd_dump(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "min")==0 || strcmp(argv[1], "m")==0) test_cmd_min(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "max")==0 || strcmp(argv[1], "M")==0) test_cmd_max(param, argv[0], argc - 1, &argv[1]);
		else test_cmd_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}

static void cursor_cmd_create_usage(str_t n) { Dz1Thread_printf("Usage] %s create\n"); }
static void cursor_cmd_create(void *ptr, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_create_usage(n);
	else if (env->tree == NULL) Dz1Thread_printf("Tree not created\n");
	else if (env->c != NULL) Dz1Thread_printf("Already created\n");
	else if ((env->c = Dz1AATreeCursor_init(env->tree, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("Created\n");
	}
}

static void cursor_cmd_delete_usage(str_t n) { Dz1Thread_printf("Usage] %s delete\n"); }
static void cursor_cmd_delete(void *ptr, str_t n, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_delete_usage(n);
	else if (env->c == NULL) Dz1Thread_printf("Not created\n");
	else
	{
		Dz1AATreeCursor_delAndSetNull(&env->c);
		Dz1Thread_printf("Done\n");
	}
}

static void cursor_cmd_cond_usage(str_t n) { Dz1Thread_printf("Usage] %s cond\n"); }
static void cursor_cmd_cond(void *ptr, str_t n, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_cond_usage(n);
	else if (env->tree == NULL) Dz1Thread_printf("Tree not created\n");
	else if (env->c == NULL) Dz1Thread_printf("Cursor Not created\n");
	else
	{
		bool_t v = Dz1AATreeCursor_cond(env->c);
		Dz1Thread_printf("Result = %s\n", v ? "TRUE" : "FALSE");
	}
}

static void cursor_cmd_next_usage(str_t n) { Dz1Thread_printf("Usage] %s cond\n"); }
static void cursor_cmd_next(void *ptr, str_t n, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_next_usage(n);
	else if (env->tree == NULL) Dz1Thread_printf("Tree not created\n");
	else if (env->c == NULL) Dz1Thread_printf("Cursor Not created\n");
	else
	{
		env->c = Dz1AATreeCursor_next(env->c);
		Dz1Thread_printf("Done\n");
	}
}

static void cursor_cmd_prev_usage(str_t n) { Dz1Thread_printf("Usage] %s cond\n"); }
static void cursor_cmd_prev(void *ptr, str_t n, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_prev_usage(n);
	else if (env->tree == NULL) Dz1Thread_printf("Tree not created\n");
	else if (env->c == NULL) Dz1Thread_printf("Cursor Not created\n");
	else
	{
		env->c = Dz1AATreeCursor_prev(env->c);
		Dz1Thread_printf("Done\n");
	}
}

static void cursor_cmd_view_usage(str_t n) { Dz1Thread_printf("Usage] %s view\n"); }
static void cursor_cmd_view(void *ptr, str_t n, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)ptr;
	if (argc != 1) cursor_cmd_view_usage(n);
	else if (env->tree == NULL) Dz1Thread_printf("Tree not created\n");
	else if (env->c == NULL) Dz1Thread_printf("Cursor Not created\n");
	else if (Dz1AATreeCursor_cond(env->c) == FALSE) Dz1Thread_printf("Cursor is invalid\n");
	else
	{
		void *data = Dz1AATreeCursor_data(env->c);
		Dz1Thread_printf("data = %p\n", data);
	}
}

static void cursor_cmd_usage(str_t n) { Dz1Thread_printf("Usage] %s <create | delete | cond | next | prev | view>\n"); }
static Dz1ShellCmdReturn cursor_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		cursor_cmd_usage(argv[0]);
	else
	{
		if		(strcmp(argv[1], "create")==0 || strcmp(argv[1], "c")==0) cursor_cmd_create(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "delete")==0 || strcmp(argv[1], "d")==0) cursor_cmd_delete(param, argv[0], argc - 1, &argv[1]);

		else if (strcmp(argv[1], "cond")==0 || strcmp(argv[1], "o")==0) cursor_cmd_cond(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "next")==0 || strcmp(argv[1], "n")==0) cursor_cmd_next(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "prev")==0 || strcmp(argv[1], "p")==0) cursor_cmd_prev(param, argv[0], argc - 1, &argv[1]);
		else if (strcmp(argv[1], "view")==0 || strcmp(argv[1], "v")==0) cursor_cmd_view(param, argv[0], argc - 1, &argv[1]);

		else cursor_cmd_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}

static Dz1Error start(void *p, int inputIdleWait_sec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TestEnv env = { NULL, NULL };

	void *h = NULL;
#ifndef UNIX_SYSTEM
	if (!(h = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 0, "root", "localhost", &err))) Dz1Error_print(&err, 0);
#else
	if (!(h = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 0, "root", "localhost", &err))) Dz1Error_print(&err, 0);
#endif
	//hae_thread_cmd_init(h, NULL);
	//haeLocalMemory_cmdInit(h, NULL);
	else if ((err = Dz1Shell_cmdReg(h, "t", test_cmd, (void *)&env, "AATree Test Command")).code) Dz1Error_print(&err, 0);
	else if ((err = Dz1Shell_cmdReg(h, "c", cursor_cmd, (void *)&env, "AATree Test Command")).code) Dz1Error_print(&err, 0);
	else
	{
		Dz1Mem_freez();
		Dz1Shell_start(h, NULL);
		Dz1Shell_del(h);
	}
	return err;
}

int main(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	if ((*errp = start(NULL, -1)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err.code;
}
