#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>

#include "dz1_shell_var.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellVar *p = NULL;

	Dz1Cleanup_init();

	if ((p = Dz1ShellVar_new(&err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1ShellVar_del, (void *)p);

		if ((err = p->insert(p, "test", "test string 123")).code) { }
		else if ((err = p->insert(p, "abcd", "abcdefghijklmnop")).code) { }
		else if ((err = p->insert(p, "qwert", "qwertyuii")).code) { }
		else
		{
			Dz1Thread_printf("After insert test\n");
			Dz1ShellVar_dump(p, 1);
			p->remove(p, "qwert");
			Dz1Thread_printf("After remove test\n");
			Dz1ShellVar_dump(p, 1);
		}
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1ShellVar_del, (void *)p);
	}
	return err.code;
}
