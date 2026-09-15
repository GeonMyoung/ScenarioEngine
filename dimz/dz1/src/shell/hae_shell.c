#include <ctype.h>
#include <errno.h>

#include "hae_output.h"

#include "hae_local_hash.h"

#include "hae_local_name_list.h"
#include "hae_shell_core.h"
#include "hae_shell.h"

///////////////////////////////////////////////////////////////////////////////
// history command
///////////////////////////////////////////////////////////////////////////////
static int haeShell_cmdHistory(void *ptr, int argc, char *argv[])
{
	HaeShellHandle *p = (HaeShellHandle *)ptr;
	p->history->dump(p->history, 0);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// sh command
///////////////////////////////////////////////////////////////////////////////
static void haeShell_cmdSh_usage(str_t n)
{
	HaeOut->printf(0, "Usage] %s <filename>\n", n);
}

static int haeShell_cmdSh(void *ptr, int argc, char *argv[])
{
	HaeShellHandle *p = (HaeShellHandle *)ptr;
	if (argc != 2) haeShell_cmdSh_usage(argv[0]);
	else
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp)
		{
			p->doScript(p, fp);
			fclose(fp);
		}
		else
			HaeOut->printf(0, "%s(%d)\n", strerror(errno), errno);
	}
	return HAE_SHELL_KEEP_GOING;
}
