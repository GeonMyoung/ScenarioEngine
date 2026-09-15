#include <errno.h>

#include "hae_output.h"
#include "hae_shell.h"

#include "hae_local_memory_cmd.h"

#ifdef HAE_LOCAL_MEMORY_TRACE
static void haeLocalMemory_cmd_dump_usage(str_t name)
{
	HaeOut->printf(0, "Usage] %s dump [freezNum] [data]\n", name);
}

static void haeLocalMemory_cmd_dump(str_t name, int argc, char *argv[])
{
	int freezNum;
	int data_dump = FALSE;
	if (argc==1) freezNum = -1;
	else if (argc==2)
	{
		if (strcmp(argv[1], "data")==0 || strcmp(argv[1], "d")==0) data_dump = TRUE;
		else freezNum = atoi(argv[1]);
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "data")==0 || strcmp(argv[1], "d")==0)
		{
			data_dump = TRUE;
			freezNum = atoi(argv[2]);
		}
		else if (strcmp(argv[2], "data")==0 || strcmp(argv[2], "d")==0)
		{
			data_dump = TRUE;
			freezNum = atoi(argv[1]);
		}
		else { haeLocalMemory_cmd_dump_usage(name); return; }
	}
	else { haeLocalMemory_cmd_dump_usage(name); return; }
	haeLocalMemory_dump(freezNum, data_dump, 1);
}

static void haeLocalMemory_cmd_inspect_usage(str_t n)
{
	HaeOut->printf(0, "Usage] %s inspect <address> <length>\n");
}

static void haeLocalMemory_cmd_inspect(str_t name, int argc, char *argv[])
{
	if (argc != 3)
		haeLocalMemory_cmd_inspect_usage(name);
	else
	{
		void *addr = (void *)strtol(argv[1], (char **)NULL, 0);
		int len = atoi(argv[2]);
		HaeOut->printb(1, addr, len);
	}
}

static void haeLocalMemory_cmd_usage(str_t name)
{
	HaeOut->printf(0, "Usage] %s {freez|melt|dump|export} {param}\n", name);
	HaeOut->printf(0, "        freez    :    no parameter\n");
	HaeOut->printf(0, "        melt     :    no parameter\n");
	HaeOut->printf(0, "        dump     :    [freez num]\n");
	HaeOut->printf(0, "        export   :    no parameter\n");
	HaeOut->printf(0, "        inspect  :    <address> <length>\n");
}

static int haeLocalMemory_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		haeLocalMemory_cmd_usage(argv[0]);
	else
	{
		if (strcmp(argv[1], "dump")==0 || strcmp(argv[1], "d")==0)
			haeLocalMemory_cmd_dump(argv[0], argc-1, &argv[1]);
		else if (strcmp(argv[1], "export")==0 || strcmp(argv[1], "e")==0)
		{
			FILE *fp = fopen("mem.txt", "wb");
			if (fp) 
			{
				haeLocalMemory_export_table(fp);
				fclose(fp);
			}
			else
				HaeOut->printf(0, "export file open = %s(%d)\n", strerror(errno), errno);
		}
		else if (strcmp(argv[1], "freez")==0 || strcmp(argv[1], "f")==0)
		{
			int old = haeLocalMemory_get_freez();
			int new = haeLocalMemory_freez();
			HaeOut->printf(0, "Freezing %d -> %d\n", old, new);
		}
		else if (strcmp(argv[1], "melt")==0 || strcmp(argv[1], "m")==0)
		{
			int old = haeLocalMemory_get_freez();
			int new = haeLocalMemory_melt();
			HaeOut->printf(0, "Melting %d -> %d\n", old, new);
		}
		else if (strcmp(argv[1], "inspect")==0 || strcmp(argv[1], "i")==0)
			haeLocalMemory_cmd_inspect(argv[0], argc - 1, &argv[1]);
		else
			haeLocalMemory_cmd_usage(argv[0]);
	}
	return 1;
}
#endif

int haeLocalMemory_cmdInit(void *handle, str_t name)
{
#ifdef HAE_LOCAL_MEMORY_TRACE
	str_t np = NULL;
	if (!name || !strlen(name)) np = "mem"; else np = name;
	HaeOut->printf(0, "haeLocalMemory_cmdInit() : Trace is enabled(handle=%p)\n", handle);
	if (!haeShell_regcmd(handle, np, haeLocalMemory_cmd, NULL, NULL))
	{
		HaeOut->printf(0, "haeLocalMemory_cmdInit() : Command registration fail\n");
		return FALSE;
	}
#else
	HaeOut->printf(0, "haeLocalMemory_cmdInit() : Trace is Disabled\n");
#endif
	return TRUE;
}
