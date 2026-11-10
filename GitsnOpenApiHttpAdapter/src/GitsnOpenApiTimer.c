////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnOpenApiTimer.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiTimer
GitsnOpenApiTimer *GitsnOpenApiTimer_new(u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GitsnOpenApiTimer *__internal_ret = (GitsnOpenApiTimer *)Dz1Calloc(sizeof(GitsnOpenApiTimer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GitsnOpenApiTimer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GitsnOpenApiTimer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GitsnOpenApiTimer_purge(GitsnOpenApiTimer *p)
{
	if (p == NULL) return;
}

void GitsnOpenApiTimer_del(GitsnOpenApiTimer *p)
{
	if (p == NULL) return;
	GitsnOpenApiTimer_purge(p);
	Dz1Free(p);
}

void GitsnOpenApiTimer_dump(GitsnOpenApiTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
	}
}
int GitsnOpenApiTimer_cmp(GitsnOpenApiTimer *a, GitsnOpenApiTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->id, &b->id)) != 0) { }
	return ret;
}
// GitsnOpenApiTimer
////////////////////////////////////////////////////////////////////////////////

