#include "hae_output.h"

#include "hae_local_memory_cmd.h"

//#include "hae_common_init.h"

#include "hae_shell.h"

static int shell_starter(HaeInput *haeInput, void *ptr)
{
	void *p = haeShell_init(HAE_SHELL_CMD_ALL, 4);
	haeLocalMemory_cmdInit(p, NULL);
	HaeOut->printf(0, "shell initialize\n");
	HaeOut->printf(0, "command registration\n");
	haeShell_do(p, haeInput, "root", "star", "hae_shrc");
	haeShell_clean(p);
	return 0;
}

int main(void)
{
//	haeInputRemote_process(shell_starter, NULL, 3023);
	haeInputLocal_process(shell_starter, NULL, -1);
//	haeInputFD_process(shell_starter, NULL, "/dev/orc_master", -1);
	haeLocalMemory_dump(-1, FALSE, 0);
	return 0;
}
