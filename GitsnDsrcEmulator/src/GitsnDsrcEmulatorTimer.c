////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDsrcEmulatorTimer.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDsrcEmulatorTimer
GitsnDsrcEmulatorTimer *GitsnDsrcEmulatorTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnDsrcEmulatorTimer *__internal_ret = (GitsnDsrcEmulatorTimer *)Dz1Calloc(sizeof(GitsnDsrcEmulatorTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnDsrcEmulatorTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnDsrcEmulatorTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnDsrcEmulatorTimer_purge(GitsnDsrcEmulatorTimer *p)
{
	if (p == NULL) return;
}

void GitsnDsrcEmulatorTimer_del(GitsnDsrcEmulatorTimer *p)
{
	if (p == NULL) return;
	GitsnDsrcEmulatorTimer_purge(p);
	Dz1Free(p);
}

void GitsnDsrcEmulatorTimer_dump(GitsnDsrcEmulatorTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int GitsnDsrcEmulatorTimer_cmp(GitsnDsrcEmulatorTimer *a, GitsnDsrcEmulatorTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// GitsnDsrcEmulatorTimer
////////////////////////////////////////////////////////////////////////////////

