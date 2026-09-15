#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_cmd.h"

static Dz1ShellCmdReturn func(void *ptr, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	int v = (int)__DZ1PTR(ptr);

	Dz1Thread_printf("Val = %d\n", v);

	return ret;
}

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellCmd *cmd = NULL;

	Dz1Cleanup_init();

	if ((cmd = Dz1ShellCmd_new(&err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellCmd_del, (void *)cmd);
		if ((err = cmd->insert(cmd, "t0", func, (void *)__DZ1PTR(0), "test command 0")).code) ERR_OUT(&err);
		else if ((err = cmd->insert(cmd, "tt1", func, (void *)__DZ1PTR(1), "test command 1")).code) ERR_OUT(&err);
		else if ((err = cmd->insert(cmd, "ttt2", func, (void *)__DZ1PTR(2), "test command 2")).code) ERR_OUT(&err);
		else if ((err = cmd->insert(cmd, "uu1", func, (void *)__DZ1PTR(3), "test command 3")).code) ERR_OUT(&err);
		else if ((err = cmd->insert(cmd, "uuuu2", func, (void *)__DZ1PTR(4), "test command 4")).code) ERR_OUT(&err);
		else
		{
			Dz1ShellCmdList *list = NULL;

			Dz1Thread_printf("After Insert\n");
			Dz1ShellCmd_dump(cmd, 1);

			if ((list = cmd->like(cmd, "t", &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)Dz1ShellCmdList_del, (void *)list);

				Dz1Thread_printf("like \"t\"\n");
				Dz1ShellCmdList_dump(list, 1);

				cmd->remove(cmd, "ttt2");
				cmd->remove(cmd, "uuuu2");
				Dz1Thread_printf("After Remove\n");
				Dz1ShellCmd_dump(cmd, 1);

				pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1ShellCmdList_del, (void *)list);

				if ((list = cmd->like(cmd, "t", &err)) == NULL) ERR_OUT(&err);
				else
				{
					Dz1ShellCmdEntry *e = NULL;
					pthread_cleanup_push((Dz1DelFunc)Dz1ShellCmdList_del, (void *)list);

					Dz1Thread_printf("like \"t\"\n");
					Dz1ShellCmdList_dump(list, 1);

					if ((e = cmd->find(cmd, "tt1")))
					{
						Dz1ShellCmdReturn ret;
						Dz1Thread_printf("Execute...\n");
						ret = Dz1ShellCmdEntry_execute(e, 0, NULL);
						Dz1Thread_printf("Result = %d\n", ret);
					}

					pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1ShellCmdList_del, (void *)list);
				}
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1ShellCmd_del, (void *)cmd);
	}

	return err.code;
}
