#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>

#include "dz1_shell_input.h"

int main(void)
{
	int len = 0;
	bool_t halt = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellInput inp;
	char def[1024] = { 0, };

	Dz1Cleanup_init();

	Dz1ShellInput_init(&inp, "xterm");
	pthread_cleanup_push((Dz1CancelFunc)Dz1ShellInput_clean, (void *)&inp);

	while(!halt)
	{
		switch(Dz1ShellInput_recv(&inp, def))
		{
			case Dz1ShellInputStatus_ok:
				if ((len = strlen(inp.buf)))
				{
					Dz1Thread_printf("Command : %s\n", inp.buf);
					Dz1Thread_tprintb(1, inp.buf, len + 1, 16);
					if (strcmp(inp.buf, "exit") == 0) halt = TRUE;
				}
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_up:
				Dz1Thread_printf("Up Arrow\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_down:
				Dz1Thread_printf("Down Arrow\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_right:
				Dz1Thread_printf("Right Arrow\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_left:
				Dz1Thread_printf("Left Arrow\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_pageUp:
				Dz1Thread_printf("Page Up\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_pageDown:
				Dz1Thread_printf("Page Down\n");
				def[0] = '\0';
				break;
			case Dz1ShellInputStatus_tab:
				Dz1Thread_printf("Command %s with TAB\n", inp.buf);
				strcpy(def, inp.buf);
				break;
			case Dz1ShellInputStatus_esc:
				Dz1Thread_printf("Esc Pressed\n");
				strcpy(def, inp.buf);
				break;
			case Dz1ShellInputStatus_notSupport:
				Dz1Thread_printf("Not Supported Key\n");
				def[0] = '\0';
				break;
			default:
				Dz1Thread_printf("Unknown Status\n");
				def[0] = '\0';
				break;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1ShellInput_init, (void *)&inp);

	return err.code;
}
