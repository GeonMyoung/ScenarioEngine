#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_cleanup.h>

#include "dz1_shell_history.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellHistory *h = NULL;

	Dz1Cleanup_init();

	if ((h = Dz1ShellHistory_new(3, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1ShellHistory_del, (void *)h);

		if ((err = h->push(h, "aaaaaaaaaaaaaaa")).code) ERR_OUT(&err);
		else if ((err = h->push(h, "bbbbbbbbbbb")).code) ERR_OUT(&err);
		else if ((err = h->push(h, "ccccccccccccccccc")).code) ERR_OUT(&err);
		else
		{
			str_t his;
			Dz1Thread_printf("History Dump\n");
			Dz1ShellHistory_dump(h, 1);

			Dz1Thread_printf("History = %d\n", h->count(h));

			Dz1Thread_printf("History Forward Trace\n", h->count(h));
			for (h->cursorInit(h, Dz1FifoCursorPos_head); h->cursorCond(h); h->cursorNext(h, FALSE))
				Dz1Thread_tprintf(1, "[%s]\n", h->cursorData(h));

			Dz1Thread_printf("History Backward Trace\n", h->count(h));
			for (h->cursorInit(h, Dz1FifoCursorPos_tail); h->cursorCond(h); h->cursorPrev(h, FALSE))
				Dz1Thread_tprintf(1, "[%s]\n", h->cursorData(h));

			Dz1Thread_printf("History Pop out\n", h->count(h));
			while((his = h->pop(h, NULL)))
			{
				pthread_cleanup_push((Dz1CancelFunc)Dz1Str_del, (void *)his);
				Dz1Thread_tprintf(1, "POP : %s\n", his);
				pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Str_del, (void *)his);
			}
			Dz1Thread_printf("After Pop\n");
			Dz1ShellHistory_dump(h, 1);
		}
		pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1ShellHistory_del, (void *)h);
	}

	return err.code;
}
