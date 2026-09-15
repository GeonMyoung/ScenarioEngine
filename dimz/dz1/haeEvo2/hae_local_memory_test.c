#include "hae_output.h"

#include "hae_local_memory.h"
#include "hae_local_memory_cmd.h"

#include "hae_shell.h"

#define PTR_MAX		128

static void *ptr[PTR_MAX];
static int	 ptr_size[PTR_MAX];

static int find_free_slot(void)
{
	int i;
	for (i = 0; i < PTR_MAX; i++)
		if (!ptr[i]) return i;
	return -1;
}

static void ptr_init(void)
{
	int i;
	for (i = 0; i < PTR_MAX; i++)
	{
		ptr[i] = NULL;
		ptr_size[i] = 0;
	}
}
static void ptr_dump(int idx, int tab)
{
	HaeOut->printf(tab, "[%03d][%p][%6d]\n", idx, ptr[idx], ptr_size[idx]);
}

static void test_cmd_alloc_usage(void)
{
	HaeOut->printf(0, "Usage] test alloc <size>\n");
}

static void test_cmd_alloc(int argc, char *argv[])
{
	int idx = find_free_slot();
	if (argc < 2)
		test_cmd_alloc_usage();
	else
	{
		if (idx == -1)
			HaeOut->printf(0, "No more pointer space\n");
		else
		{
			int size = atoi(argv[1]);
			ptr[idx] = LOCAL_MALLOC(size);
			if (!size)
				HaeOut->printf(0, "error : size is 0 or invalid\n");
			else
			{
				if (ptr[idx])
				{
					ptr_size[idx] = size;
					memset(ptr[idx], 0, ptr_size[idx]);
					HaeOut->printf(0, "Allocate success at %p, size %d\n", ptr[idx], ptr_size[idx]);
				}
				else
					HaeOut->printf(0, "Allocate fail\n");
			}
		}
	}
}

static void test_cmd_free_usage(void)
{
	HaeOut->printf(0, "Usage] test free <ptr_idx>\n");
}

static void test_cmd_free(int argc, char *argv[])
{
	if (argc < 2)
		test_cmd_free_usage();
	else
	{
		int idx = atoi(argv[1]);
		if (ptr[idx])
		{
			LOCAL_FREE(ptr[idx]);
			ptr[idx] = NULL;
			ptr_size[idx] = 0;
			HaeOut->printf(0, "ptr of idx %d is freed\n", idx);
		}
		else
			HaeOut->printf(0, "error : ptr of idx %d is NULL\n", idx);
	}
}

static void test_cmd_dump_usage(void)
{
	HaeOut->printf(0, "Usage] test dump [<ptr_idx>]\n");
}

static void test_cmd_dump(int argc, char *argv[])
{
	if (argc == 2)
	{
		int idx = atoi(argv[1]);
		ptr_dump(idx, 0);
	}
	else if (argc == 1)
	{
		int i, printed = FALSE;
		for (i = 0; i < PTR_MAX; i++)
		{
			if (ptr[i])
			{
				printed = TRUE;
				ptr_dump(i, 0);
			}
		}
		if (!printed) HaeOut->printf(0, "Empty\n");
	}
	else
		test_cmd_dump_usage();
}

static void test_cmd_usage(void)
{
	HaeOut->printf(0, "Usage] test {alloc|free|dump} <param>\n");
}

static int test_cmd(void *param, int argc, char *argv[])
{
	if (argc < 2)
		test_cmd_usage();
	else
	{
		if (strcmp(argv[1], "alloc")==0 || strcmp(argv[1], "a")==0) test_cmd_alloc(argc - 1, &argv[1]);
		else if (strcmp(argv[1], "free")==0 || strcmp(argv[1], "f")==0) test_cmd_free(argc - 1, &argv[1]);
		else if (strcmp(argv[1], "dump")==0 || strcmp(argv[1], "d")==0) test_cmd_dump(argc - 1, &argv[1]);
		else test_cmd_usage();
	}
	return HAE_SHELL_KEEP_GOING;
}

static int shell_starter(HaeInput *haeInput, void *p)
{
	haeShell_do(p, haeInput, "root", "star", NULL);
	return 0;
}

int main(void)
{
	void *h = haeShell_init(HAE_SHELL_CMD_ALL, 0);
	if (!h)
	{
		HaeOut->fprintf(stdout, 0, "user_main : haeShell_init fail\n");
		return 1;
	}
	if (!haeLocalMemory_cmdInit(h, NULL)) return 1;
	if (!haeShell_regcmd(h, "test", test_cmd, NULL, NULL))
	{
		HaeOut->fprintf(stdout, 0, "user_main : command registration fail\n");
		return 1;
	}
	ptr_init();
	haeInputLocal_process(shell_starter, h, -1);
	return 0;
}
