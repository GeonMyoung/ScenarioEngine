#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_parse.h"

#define PARSE_TEST

#ifdef PARSE_TEST
static Dz1Error func(void *p, Dz1ShellParseToken type, str_t token)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(type)
	{
		case Dz1ShellParseToken_doubleCotatedString:
			Dz1Thread_printf("Dz1ShellParseToken_doubleCotatedString\n");
			break;
		case Dz1ShellParseToken_singleCotatedString:
			Dz1Thread_printf("Dz1ShellParseToken_singleCotatedString\n");
			break;
		case Dz1ShellParseToken_word:
			Dz1Thread_printf("Dz1ShellParseToken_word\n");
			break;
		case Dz1ShellParseToken_literal:
			Dz1Thread_printf("Dz1ShellParseToken_literal\n");
			break;
		default:
			Dz1Thread_printf("Unknown Token\n");
			break;
	}
	Dz1Thread_tprintf(1, "[%s]\n", token);
	return err;
}
#endif

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	str_t text = "aaa \"bbb ccc\" 'ddd eee fff ggg' $hhh !99";

#ifdef PARSE_TEST
	ssize_t size = 0;
#else
	char buf[1024];
	str_t temp = NULL;
#endif

	Dz1Cleanup_init();

#ifdef PARSE_TEST
	size = Dz1ShellParse(text, FALSE, TRUE, func, NULL, &err);

	Dz1Thread_printf("%d byte consume\n", size);
#else
	if ((temp = Dz1ShellParse_word(buf, text, &err)))
	{
		Dz1Thread_printf("[temp:%s][buf:%s]\n", temp, buf);
	}
#endif
	return err.code;
}
