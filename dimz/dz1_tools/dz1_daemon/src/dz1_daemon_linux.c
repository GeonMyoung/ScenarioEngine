#include "dz1_daemon.h"
#ifdef UNIX_SYSTEM
#ifdef LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
bool_t Dz1DaemonMain(Dz1Str ServiceName, Dz1Str InitialPath, UserApiF Perform, UserApiF Stop, void *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	int pid;

	if ((pid = fork()) < 0) 
	{
		ERR_SET_OUT(errp, errno);
		exit(0);
	}
	else if (pid > 0)
	{	// parent
		printf("child process : [%d], parent process : [%d]\n", pid, getpid());
		exit(0);
	}
	else // pid == 0
	{	// child
		int std_in, std_out, std_err;

		signal(SIGHUP, SIG_IGN);

		std_in = dup(0);
		std_out = dup(1);
		std_err = dup(2);

		close(0);
		close(1);
		close(2);

		umask(0);

		dup2(std_in, 0);
		dup2(std_out, 1);
		dup2(std_err, 2);

		if ((pid = fork()) < 0)
		{	// error
			ERR_SET_OUT(errp, errno);
		}
		else if (pid > 0)
		{	// parent
			exit(0);
		}
		else
		{	// child
			if (Dz1Str_isVoid(InitialPath) == FALSE) chdir(InitialPath);
			Perform(ptr);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#endif
#else
int _avoid_no_symbol_warning_dz1_daemon_ = 0;
#endif
