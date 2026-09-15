#include <dz1_cleanup.h>
#include "../../src/kernel/dz1_console.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Console *c = Dz1ConsoleTTY_new(fileno(stdin), fileno(stdout), &err);
	if (c == NULL) { }
	else
	{
		Dz1Console_tprintf(c, 0, "abcdefghijklmnopqrstuvexyz\n");
		Dz1Console_tprintf(c, 0, "%d\r\n", 10);
		Dz1Console_tprintf(c, 1, "%d\r\n", 20);
		Dz1Console_tprintf(c, 2, "%d\r\n", 30);
		Dz1Console_del(c);
	}
	return err.code;
}
