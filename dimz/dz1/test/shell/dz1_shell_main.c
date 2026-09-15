#ifndef UNIX_SYSTEM
#include <conio.h>
#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif
#endif

#include <dz1_cleanup.h>
#include <dz1_thread.h>
#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include "dz1_shell.h"

int main(int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void *sh = NULL;

	Dz1Cleanup_init();

	Dz1Thread_printf(Dz1Text("12345\n"));

#if 1
#ifdef UNIX_SYSTEM
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 3, "root", "embedded", &err)) == NULL) ERR_OUT(&err);
#else
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 3, Dz1Text("root"), Dz1Text("embedded"), &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

		Dz1Shell_start(sh, NULL);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
#endif

#ifdef _DEBUG
#if (_MSC_VER < 1930)
	printf("Press Any Key...\n");
	while (!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif

	return err.code;
}
