#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_args.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellArgs *args = NULL;
	
	Dz1Cleanup_init();

	//if ((args = Dz1ShellArgs_new("aaa \"bbb ccc\" 'ddd eee fff' ggg", &err)))
	if ((args = Dz1ShellArgs_new("aaa              bbb  ", &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellArgs_del, (void *)args);
		Dz1Thread_printf("Result...\n");
		Dz1ShellArgs_dump(args, 1);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1ShellArgs_del, (void *)args);
	}
	return err.code;
}
