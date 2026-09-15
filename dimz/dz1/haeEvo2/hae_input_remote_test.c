#include <signal.h>

#include "hae_output.h"
#include "hae_input.h"

static int proc(HaeInput *haeInput, void *p)
{
	int c;
	while((c= haeInput->getch(haeInput)) != EOF)
		HaeOut->printf(0, "%c", c);
	return 0;
}

static volatile int termed = FALSE;

static void sig_handle(int signo)
{
	switch(signo)
	{
		case SIGINT:
			HaeOut->fprintf(stdout, 0, "sig_handle() : SIGINT Catched\n");
			break;
		case SIGTERM:
			HaeOut->fprintf(stdout, 0, "sig_handle() : SIGTERM Catched\n");
			break;
		default:
			HaeOut->fprintf(stdout, 0, "sig_handle() : Unknown Signal = %d\n", signo);
			break;
	}
	if (!termed) { termed = TRUE; exit(1); }
}

int main(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGTERM, sig_handle);
	HaeOut->fprintf(stdout, 0, "call haeInputRemote_process(%p)\n", haeInputRemote_process);
	haeInputRemote_process(proc, NULL, 3021);
	return 0;
}
