#include <dz1_shell.h>
#include <dz1_bin.h>
#include <dz1_lzw.h>

typedef struct TestEnv
{
	Dz1Binary		*src;
	Dz1Binary		*dst;
} TestEnv;

static void TestEnv_cleanup(void *ptr)
{
	TestEnv *p = (TestEnv *)ptr;
	if (p->src) Dz1Binary_delAndSetNull(&p->src);
	if (p->dst) Dz1Binary_delAndSetNull(&p->dst);
}

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	void *sh = NULL;

	TestEnv env = { NULL, NULL };
	pthread_cleanup_push(TestEnv_cleanup, (void *)&env);
#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "embedded", &err)) == NULL) ERR_OUT(&err);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "embedded", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

		if (0) { }
		else Dz1Shell_start(sh, NULL);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
	pthread_cleanup_pop(1); // (TestEnv_cleanup, (void *)&env);

	return err.code;
}
