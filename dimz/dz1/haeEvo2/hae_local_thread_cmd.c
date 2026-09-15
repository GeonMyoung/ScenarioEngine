#include "hae_output.h"
#include "hae_shell.h"

#include "hae_local_thread.h"
#include "hae_local_thread_cmd.h"

static void hae_thread_cmd_debug_usage(str_t name)
{
	HaeOut->printf(0, "Usage] %s setdebug <thread_id> <level>\n", name);
	HaeOut->printf(0, "          level : none(0)\n");
	HaeOut->printf(0, "                  error(1)\n");
	HaeOut->printf(0, "                  message(2)\n");
	HaeOut->printf(0, "                  debug(3)\n");
	HaeOut->printf(0, "                  flow(4)\n");
}

static void hae_thread_cmd_debug(str_t name, int argc, char *argv[])
{
	if (argc != 3)
		hae_thread_cmd_debug_usage(name);
	else
	{
		int ret = 0;
		u32_t thid = (u32_t)atoi(argv[1]);
		int level = 1;
		if (strcmp(argv[2], "none")==0 || strcmp(argv[2], "0")==0) level = 0;
		else if (strcmp(argv[2], "error")==0 || strcmp(argv[2], "1")==0) level = 1;
		else if (strcmp(argv[2], "message")==0 || strcmp(argv[2], "2")==0) level = 2;
		else if (strcmp(argv[2], "debug")==0 || strcmp(argv[2], "3")==0) level = 3;
		else if (strcmp(argv[2], "flow")==0 || strcmp(argv[2], "4")==0) level = 4;
		else
		{
			hae_thread_cmd_debug_usage(name);
			return;
		}
		if ((ret = HaeLocalThreadManager->set_debug_level(thid, level)))
			HaeOut->printf(0, "error = %s(%d)\n", strerror(ret), ret);
		else
			HaeOut->printf(0, "Success\n");
	}
}

static void hae_thread_cmd_dump(str_t name, int argc, char *argv[])
{
	HaeLocalThreadManager->dump(1);
}

static void hae_thread_cmd_usage(str_t name)
{
	HaeOut->printf(0, "Usage] %s {dump|setdebug} <parameter>\n", name);
}

static int hae_thread_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		hae_thread_cmd_usage(argv[0]);
	else
	{
		if (strcmp(argv[1], "dump")==0 || strcmp(argv[1], "d")==0) hae_thread_cmd_dump(argv[0], argc-1, &argv[1]);
		else if (strcmp(argv[1], "setdebug")==0 || strcmp(argv[1], "s")==0) hae_thread_cmd_debug(argv[0], argc-1, &argv[1]);
		else hae_thread_cmd_usage(argv[0]);
	}
	return HAE_SHELL_KEEP_GOING;
}

int hae_thread_cmd_init(void *handle, str_t name)
{
	str_t np = NULL;
	if (!name || !strlen(name)) np = "th"; else np = name;
	return haeShell_regcmd(handle, np, hae_thread_cmd, NULL, NULL);
}
