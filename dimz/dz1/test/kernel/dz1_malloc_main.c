#include <stdlib.h>
#include <signal.h>

//#include <dz1.h>
//#include <dz1_error.h>
#include <dz1_cleanup.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>


static void sighandle(int signo)
{
 	Dz1Cleanup();
	abort();
}

int main(int argc, char *argv)
{
	Dz1OutputHook_set(NULL, NULL);
	void *ptr = NULL;
 	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Cleanup_init();

	signal(SIGSEGV, sighandle);

	ptr = Dz1Malloc(10, errp);
	ptr = Dz1Malloc(11, errp);
	Dz1Free(ptr);
	ptr = Dz1Malloc(12, errp);
	ptr = Dz1Malloc(13, errp);

	Dz1Thread_printf("%p\n", ptr);

// 	memcpy(ptr, (void *)1, 10);

	return 0;
}
