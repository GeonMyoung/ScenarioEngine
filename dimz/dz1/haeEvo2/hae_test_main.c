#include <pthread.h>
#ifndef WIN32
#include <sys/time.h>
#endif

#include <hae_output.h>
#include <hae_local_memory_cmd.h>
#include <hae_local_thread_cmd.h>

#include <hae_shell.h>

typedef struct TestEnv
{
} TestEnv;

static void test_cmd__usage(str_t n) { HaeOut->printf(0, "Usage] %s \n", n); }
static void test_cmd_(TestEnv *env, str_t n, int argc, char *argv[])
{
	if (argc < 2) test_cmd__usage(n);
	else
	{
	}
}

static void test_cmd_usage(str_t n) { HaeOut->printf(0, "%s <>\n", n); }
static int test_cmd(void *param, int argc, char *argv[])
{
	TestEnv *env = (TestEnv *)param;
	if (argc < 2)
		test_cmd_usage(argv[0]);
	else
	{
		if (strcmp(argv[1], "")==0 || strcmp(argv[1], "")==0) test_cmd_(env, argv[0], argc - 1, &argv[1]);
		//else if (strcmp(argv[1], "")==0 || strcmp(argv[1], "")==0) test_cmd_(env, argv[0], argc - 1, &argv[1]);
		else test_cmd_usage(argv[0]);
	}
	return HAE_SHELL_KEEP_GOING;
}

static int shell_starter(HaeInput *haeInput, void *p)
{
	TestEnv env = { };
	void *h = NULL;
	if (!(h = haeShell_init(HAE_SHELL_CMD_ALL, 0))) { HaeOut->printf(0, "haeShell_init fail\n"); return 0; }
	else
	{
		pthread_cleanup_push((HaeGeneralDelFunc)haeShell_clean, h);

		hae_thread_cmd_init(h, NULL);
		haeLocalMemory_cmdInit(h, NULL);

		haeShell_regcmd(h, "test", test_cmd, &env, NULL);

		haeLocalMemory_freez();

		haeShell_do(h, haeInput, "root", "HaeTestEnv", NULL);

		pthread_cleanup_pop(1); // ((HaeGeneralDelFunc)haeShell_clean, h);
		haeLocalMemory_dump(-1, FALSE, 0);
	}
	return 0;
}

int main(void)
{
	haeInputLocal_process(shell_starter, NULL, -1);
	return 0;
}
