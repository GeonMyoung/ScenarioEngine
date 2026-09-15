#include <dz1_time.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_aatree.h>
#include "dz1_task_timer.h"

typedef struct Dz1TaskTimerEntry
{
	struct Dz1TaskTimerEntry *prev;
	struct Dz1TaskTimerEntry *next;

	u64_t duration_us;
	void *timer_data;
	Dz1DelFunc timer_data_del;
	Dz1CmpFunc timer_data_cmp;
	Dz1TaskTimeoutProcFunc timeout;
} Dz1TaskTimerEntry;

static Dz1TaskTimerEntry *Dz1TaskTimerEntry_new(u64_t duration_us, void *timer_data,
												Dz1DelFunc timer_data_del, Dz1CmpFunc timer_data_cmp,
												Dz1TaskTimeoutProcFunc timeout, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskTimerEntry *ret = (Dz1TaskTimerEntry *)Dz1Calloc(sizeof(Dz1TaskTimerEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->prev = ret->next = NULL;

		ret->duration_us = duration_us;
		ret->timer_data = timer_data;
		ret->timer_data_del = timer_data_del;
		ret->timer_data_cmp = timer_data_cmp;
		ret->timeout = timeout;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TaskTimerEntry_del(Dz1TaskTimerEntry *p)
{
	if (!p) return;
	if (p->timer_data_del && p->timer_data) p->timer_data_del(p->timer_data);
	Dz1Free(p);
}

static void Dz1TaskTimerEntry_dump(Dz1TaskTimerEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "[%p][Prev:%p][Next:%p][%p][%.3f ms]\n", p, p->prev, p->next, p->timer_data,
							(double)((s64_t)p->duration_us) / 1000);
}

static int Dz1TaskTimerEntry_cmp(Dz1TaskTimerEntry *data, Dz1TaskTimerEntry *user_key)
{ return data->timer_data_cmp(data->timer_data, user_key->timer_data); }

typedef struct Dz1TaskTimerList
{
	Dz1TaskTimerEntry *head;
	Dz1TaskTimerEntry *tail;
} Dz1TaskTimerList;

static Dz1TaskTimerList *Dz1TaskTimerList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskTimerList *ret = (Dz1TaskTimerList *)Dz1Calloc(sizeof(Dz1TaskTimerList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->head = ret->tail = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TaskTimerList_del(Dz1TaskTimerList *list)
{
	if (!list) return;
	if (list->head)
	{
		Dz1TaskTimerEntry *p = list->head, *next = NULL;
		while(p)
		{
			next = p->next;
			Dz1TaskTimerEntry_del(p);
			p = next;
		}
	}
	Dz1Free(list);
}

static void Dz1TaskTimerList_dump(Dz1TaskTimerList *list, int tab)
{
	if (!list) return;
	if (list->head)
	{
		Dz1TaskTimerEntry *i;
		Dz1Thread_tprintf(tab, "Dz1TaskTimerList_dump() : Forward\n");
		for (i = list->head; i; i = i->next)
			Dz1TaskTimerEntry_dump(i, tab + 1);
		Dz1Thread_tprintf(tab, "Dz1TaskTimerList_dump() : Backward\n");
		for (i = list->tail; i; i = i->prev)
			Dz1TaskTimerEntry_dump(i, tab + 1);
	}
	else Dz1Thread_tprintf(tab, "[Empty]\n");
}

static void Dz1TaskTimerList_link(Dz1TaskTimerList *list, Dz1TaskTimerEntry *e)
{
	bool_t inserted = FALSE;
	Dz1TaskTimerEntry *i;
	if (list->head)
	{
		for (i = list->head; i; i = i->next)
		{
			if (i->duration_us >= e->duration_us)
			{	// previous of i
				i->duration_us -= e->duration_us;
				if (i == list->head) list->head = e;
				else
				{
					i->prev->next = e;
					e->prev = i->prev;
				}
				e->next = i;
				i->prev = e;

				inserted = TRUE;
				break;
			}
			else e->duration_us -= i->duration_us;
		}

		if (!inserted)
		{
			list->tail->next = e;
			e->prev = list->tail;

			list->tail = e;
		}
	}
	else list->head = list->tail = e;
}

static void Dz1TaskTimerList_unlink(Dz1TaskTimerList *list, Dz1TaskTimerEntry *e)
{
	if (list->head == e) list->head = e->next;
	if (list->tail == e) list->tail = e->prev;

	if (e->prev) e->prev->next = e->next;

	if (e->next)
	{
		e->next->duration_us += e->duration_us;
		e->next->prev = e->prev;
	}

	e->prev = NULL;
	e->next = NULL;
}

static void Dz1TaskTimerList_fix(Dz1TaskTimerList *list, u32_t diff)
{
	Dz1TaskTimerEntry *i;
	for (i = list->head; i; i = i->next)
	{
		if (i->duration_us >= diff)
		{
			i->duration_us -= diff;
			break;
		}
		else
		{
			diff -= (u32_t)i->duration_us;
			i->duration_us = 0;
		}
	}
}

typedef struct Dz1TaskTimer
{
	u32_t flag;
	u32_t sleep_start;
	u32_t work_start;

	void *id_tree;
	Dz1TaskTimerList *time_order;

	Dz1CmpFunc timerDataCmp;
} Dz1TaskTimer;

void *Dz1TaskTimer_new(Dz1CmpFunc timerDataCmp, Dz1Error *err)
{
	Dz1TaskTimer *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (timerDataCmp == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if ((ret = (Dz1TaskTimer *)Dz1Calloc(sizeof(Dz1TaskTimer), 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TaskTimer_delAndSetNull, (void *)&ret);
			if ((ret->id_tree = Dz1AATree_new((Dz1CmpFunc)Dz1TaskTimerEntry_cmp, NULL,
							(Dz1DumpFunc)Dz1TaskTimerEntry_dump, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->time_order = Dz1TaskTimerList_new(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ret->timerDataCmp = timerDataCmp;

				Dz1Time_calibrateMinTimeDelay();
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1TaskTimer_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

void Dz1TaskTimer_del(void *ptr)
{
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;
	if (!p) return;
	if (p->id_tree) Dz1AATree_del(p->id_tree);
	if (p->time_order) Dz1TaskTimerList_del(p->time_order);
	Dz1Free(p);
}

void Dz1TaskTimer_delAndSetNull(void *ptr)
{
	Dz1TaskTimer **p = (Dz1TaskTimer **)ptr;
	Dz1TaskTimer_del(*p); *p = NULL;
}

void Dz1TaskTimer_dump(void *ptr, int tab)
{
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;
	Dz1Thread_tprintf(tab, "List >>>\n");
	Dz1TaskTimerList_dump(p->time_order, tab+1);
	Dz1Thread_tprintf(tab, "ID Tree >>>\n");
	Dz1AATree_dump(p->id_tree, tab + 1);
}

static Dz1TaskTimerEntry *_Dz1TaskTimer_reg(Dz1TaskTimer *p, u64_t duration_us, void *timer_data,
											Dz1DelFunc timer_data_del, Dz1TaskTimeoutProcFunc timeout,
											bool_t overwrite, Dz1Error *errp)
{
	Dz1TaskTimerEntry key = { NULL, NULL, 0 }, *ret = NULL;
	key.timer_data = (Dz1TaskTimerEntry *)timer_data;
	if (overwrite)
	{
		if ((ret = (Dz1TaskTimerEntry *)Dz1AATree_extract(p->id_tree, &key)))
		{
			Dz1TaskTimerList_unlink(p->time_order, ret);
			Dz1TaskTimerEntry_del(ret);
		}

		if ((ret = Dz1TaskTimerEntry_new(duration_us, timer_data,
						timer_data_del, p->timerDataCmp, timeout, errp)) == NULL) ERR_OUT(errp);
	}
	else if (Dz1AATree_find(p->id_tree, &key)) ERR_SET_OUT(errp, EEXIST);
	else if ((ret = Dz1TaskTimerEntry_new(duration_us, timer_data,
						timer_data_del, p->timerDataCmp, timeout, errp)) == NULL) ERR_OUT(errp);

	return ret;
}

Dz1Error Dz1TaskTimer_reg(void *ptr, u64_t duration_us, void **timer_data, Dz1DelFunc timer_data_del,
									Dz1TaskTimeoutProcFunc timeout, bool_t overwrite)
{
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;

	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (timer_data == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1TaskTimerEntry *e = NULL;
		if ((e = _Dz1TaskTimer_reg(p, duration_us, *timer_data, timer_data_del, timeout, overwrite, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1TaskTimerEntry_del, (void *)e);

//			Dz1Thread_eprintf("Dz1TaskTimer_reg() : ptr = %p\n", *timer_data);
			if (timer_data_del != NULL) *timer_data = NULL;

			if ((err = Dz1AATree_insert(p->id_tree, e)).code) ERR_OUT(&err);
			else Dz1TaskTimerList_link(p->time_order, e);


			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1TaskTimerEntry_del, (void *)e);
		}
	}
//	Dz1Thread_eprintf("Dz1TaskTimer_reg() : After Reg\n");
//	Dz1TaskTimer_dump(p, 0);
	return err;
}

void Dz1TaskTimer_dereg(void *ptr, void *timer_key )
{
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;
	Dz1TaskTimerEntry key = { NULL, NULL, 0 }, *e = NULL;
	key.timer_data = timer_key;
	if ((e = (Dz1TaskTimerEntry *)Dz1AATree_extract(p->id_tree, &key)) != NULL)
	{
		Dz1TaskTimerList_unlink(p->time_order, e);
		Dz1TaskTimerEntry_del(e);
	}
//	Dz1Thread_eprintf("Dz1TaskTimer_dereg() : After Dereg\n");
//	Dz1TaskTimer_dump(p, 0);
}

void *Dz1TaskTimer_extract(void *ptr, void *timer_key)
{
	void *ret = NULL;
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;
	Dz1TaskTimerEntry key = { NULL, NULL, 0 }, *e = NULL;
	key.timer_data = timer_key;
	if ((e = (Dz1TaskTimerEntry *)Dz1AATree_extract(p->id_tree, &key)) != NULL)
	{
		Dz1TaskTimerList_unlink(p->time_order, e);
		ret = e->timer_data; e->timer_data = NULL;
		Dz1TaskTimerEntry_del(e);
	}
	return ret;
}

void *Dz1TaskTimer_find(void *ptr, void *timer_key)
{
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;
	Dz1TaskTimerEntry key = { NULL, NULL, 0 };
	key.timer_data = timer_key;
	return Dz1AATree_find(p->id_tree, &key);
}

u64_t *Dz1TaskTimer_getDuration(void *ptr, u64_t *dst)
{
	u64_t *ret = NULL;
	Dz1TaskTimer *p = (Dz1TaskTimer *)ptr;

	p->flag |= 0x1;
	Dz1Time_getMonotonic(&p->sleep_start);

	if (p->time_order->head)
	{
		if ((p->flag & 0x3) == 0x3)
		{
			u32_t diff = Dz1Time_diff(p->work_start, p->sleep_start);
			Dz1TaskTimerList_fix(p->time_order, diff);
		}

		if (dst) *dst = p->time_order->head->duration_us;
		ret = dst;
	}
	return ret;
}


Dz1TaskProcStatus Dz1TaskTimer_timeout(void *user_arg, void *user_resource, void *timer, Dz1Error *err)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskTimer *p = (Dz1TaskTimer *)timer;
	Dz1TaskTimerEntry *head = NULL;
	u32_t base_time = p->sleep_start, diff;

	p->flag |= 0x2;

	Dz1Time_getMonotonic(&p->work_start);

	while(p->time_order->head)
	{
		head = p->time_order->head;

		Dz1Time_getMonotonic(&p->work_start);
		diff = Dz1Time_diff(base_time, p->work_start);
		Dz1TaskTimerList_fix(p->time_order, diff);

		if ((Dz1Time_getMinTimeDelay() / 1000) >= head->duration_us)
		{	// do timeout
			Dz1AATree_extract(p->id_tree, head);
			Dz1TaskTimerList_unlink(p->time_order, head);
			
			pthread_cleanup_push((Dz1DelFunc)Dz1TaskTimerEntry_del, (void *)head);

			//Dz1Thread_eprintf("Dz1TaskTimer_timeout() : timer\n"); Dz1TaskTimer_dump(p, 0);
			if ((ret = head->timeout(user_arg, user_resource, p, &head->timer_data, errp)) == Dz1TaskProcStatus_error) ERR_OUT(errp);

			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1TaskTimerEntry_del, (void *)head);

			if (ret == Dz1TaskProcStatus_terminate || ret == Dz1TaskProcStatus_error) break;
		}
		else break;
		base_time = p->work_start;
	}
	return ret;
}
