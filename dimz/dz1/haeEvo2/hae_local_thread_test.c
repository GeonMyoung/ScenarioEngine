#ifndef WIN32
#include <sys/time.h>
#endif
#include "hae_output.h"
#include "hae_local_memory_cmd.h"

#include "hae_shell.h"
#include "hae_tvfunc.h"

#include "hae_local_thread.h"
#include "hae_local_thread_cmd.h"

static void log_print(void)
{
	HaeLocalThreadManager->log_printf(HAE_THREAD_LOG_CRITICAL, 0, "log_print() : CRITICAL\n");
	HaeLocalThreadManager->log_printf(HAE_THREAD_LOG_MESSAGE, 0, "log_print() : MESSAGE\n");
	HaeLocalThreadManager->log_printf(HAE_THREAD_LOG_ERROR, 0, "log_print() : ERROR\n");
	HaeLocalThreadManager->log_printf(HAE_THREAD_LOG_FLOW, 0, "log_print() : FLOW\n");
}

static void *thread_func(void *arg)
{
	int tick = 0;
	int cnt = HAE_PTR_CAST(int, arg);
	log_print();
	if (cnt)
	{
		while(cnt--)
		{
			haeMisc_usleep(100000);
			tick++;
			if (tick == 10)
			{
				log_print();
				tick = 0;
			}
		}
	}
	else
	{
		while(1)
		{
			haeMisc_usleep(100000);
			if (tick++ == 10)
			{
				log_print();
				tick = 0;
			}
		}
	}
	HaeLocalThreadManager->exit(NULL);
	return NULL;
}

/*
static int test_cmd_control(void *param, int argc, char *argv[])
{
	int id = (int)param;
	HaeOut->printf(0, "my id is %d\n", id);
	return HAE_SHELL_KEEP_GOING;
}
*/

static void test_cmd_start_usage(void)
{
	HaeOut->printf(0, "Usage] test start <alive_time|god>\n");
	HaeOut->printf(0, "                   alive_time : 1 = 100ms\n");
}

static void test_cmd_start(void *param, int argc, char *argv[])
{
	if (argc != 2)
		test_cmd_start_usage();
	else
	{
		int value, id, ret;
		if (strcmp(argv[1], "god")==0) value = 0;
		else value = atoi(argv[1]);
		if ((ret = HaeLocalThreadManager->START(&id, thread_func, HAE_PTR_CAST(void *, value), 2)))
			HaeOut->printf(0, "error = %s(%d)\n", strerror(ret), ret);
		else
		{
//			char cmd_name[64];
//			sprintf(cmd_name, "th%d", id);
//			haeShell_regcmd(param, cmd_name, test_cmd_control, (void *)id, NULL);
			HaeOut->printf(0, "success\n");
		}
	}
}

static void test_cmd_stop_usage(void)
{
	HaeOut->printf(0, "Usage] test stop <thid>\n");
}

static void test_cmd_stop(int argc, char *argv[])
{
	if (argc < 2)
		test_cmd_stop_usage();
	else
	{
		int ret;
		int thid = atoi(argv[1]);
		if ((ret = HaeLocalThreadManager->stop(thid, NULL, HAE_THREAD_STOP_BLOCKED)))
			HaeOut->printf(0, "error : stop = %s(%d)\n", strerror(ret), ret);
	}
}

static void test_cmd_usage(void)
{
	HaeOut->printf(0, "test {start|stop} <parameter>\n");
}

static int test_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		test_cmd_usage();
	else
	{
		if (strcmp(argv[1], "start")==0 || strcmp(argv[1], "s")==0) test_cmd_start(param, argc - 1, &argv[1]);
		else if (strcmp(argv[1], "stop")==0 || strcmp(argv[1], "x")==0) test_cmd_stop(argc - 1, &argv[1]);
		else test_cmd_usage();
	}
	return HAE_SHELL_KEEP_GOING;
}

static int shell_starter(HaeInput *haeInput, void *p)
{
	void *h = NULL;
	if (!(h = haeShell_init(HAE_SHELL_CMD_ALL, 0)))
	{
		HaeOut->printf(0, "haeShell_init fail\n");
		return 0;
	}
	hae_thread_cmd_init(h, NULL);
	haeLocalMemory_cmdInit(h, NULL);
	haeShell_regcmd(h, "test", test_cmd, h, NULL);
	haeLocalMemory_freez();
	haeShell_do(h, haeInput, "root", "star", NULL);
	haeShell_clean(h);
	haeLocalMemory_dump(-1, FALSE, 0);
	return 0;
}

int main(void)
{
	haeInputLocal_process(shell_starter, NULL, -1);
	return 0;
}

