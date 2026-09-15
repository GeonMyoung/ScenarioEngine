#include <dz1_malloc.h>
#include <dz1_aatree.h>

#include "dz1_task_sigmsg_router.h"
#include "../kernel/dz1_thread_stdio.h"

typedef struct Dz1TaskSigRouterEntry
{
	u32_t type;
	u32_t mask;
	Dz1TaskSigMsgProcFunc func;
} Dz1TaskSigRouterEntry;

static Dz1TaskSigRouterEntry *Dz1TaskSigRouterEntry_new(u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskSigRouterEntry *ret = (Dz1TaskSigRouterEntry *)Dz1Calloc(sizeof(Dz1TaskSigRouterEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->type = type;
		ret->mask = mask;
		ret->func = func;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TaskSigRouterEntry_del(Dz1TaskSigRouterEntry *p)
{
	if (!p) return;
	Dz1Free(p);
}

static void Dz1TaskSigRouterEntry_dump(Dz1TaskSigRouterEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "[%08X/%08X][%p]\n", p->type, p->mask, p->func);
}

static int Dz1TaskSigRouterEntry_cmp(Dz1TaskSigRouterEntry *a, Dz1TaskSigRouterEntry *b)
{
	if (a->type == b->type) return 0;
	else if (a->type < b->type) return -1;
	else return 1;
//	return (int)(a->type - b->type);
}

typedef struct Dz1TaskSigRouterListEntry
{
	struct Dz1TaskSigRouterListEntry *prev;
	struct Dz1TaskSigRouterListEntry *next;
	Dz1TaskSigRouterEntry *entry;
} Dz1TaskSigRouterListEntry;

static Dz1TaskSigRouterListEntry *Dz1TaskSigRouterListEntry_new(Dz1TaskSigRouterEntry *entry, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskSigRouterListEntry *ret = (Dz1TaskSigRouterListEntry *)Dz1Calloc(sizeof(Dz1TaskSigRouterListEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->prev = ret->next = NULL;
		ret->entry = entry;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TaskSigRouterListEntry_del(Dz1TaskSigRouterListEntry *p)
{
	if (!p) return;
	if (p->entry) Dz1TaskSigRouterEntry_del(p->entry);
	Dz1Free(p);
}

static void Dz1TaskSigRouterListEntry_dump(Dz1TaskSigRouterListEntry *p, int tab)
{
	if (!p) return;
	Dz1TaskSigRouterEntry_dump(p->entry, tab);
}

typedef struct Dz1TaskSigRouterList
{
	Dz1TaskSigRouterListEntry *head;
	Dz1TaskSigRouterListEntry *tail;
} Dz1TaskSigRouterList;

static Dz1TaskSigRouterEntry *_Dz1TaskSigRouterList_find(Dz1TaskSigRouterList *list, u32_t key, bool_t exact)
{
	u32_t type;
	Dz1TaskSigRouterEntry *e = NULL;
	Dz1TaskSigRouterListEntry *i = NULL;
	for (i = list->head; i; i = i->next)
	{
		e = i->entry;
		if (exact) type = key; else type = key & e->mask;
		if (type == e->type) return e;
	}
	return NULL;
}

/*
static Dz1TaskSigMsgProcFunc Dz1TaskSigRouterList_find(Dz1TaskSigRouterList *list, u32_t type)
{
	Dz1TaskSigRouterEntry *e = _Dz1TaskSigRouterList_find(list, type, FALSE);
	if (e) return e->func; else return NULL;
}
*/

static Dz1Error Dz1TaskSigRouterList_reg(Dz1TaskSigRouterList *p, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskSigRouterEntry *e = _Dz1TaskSigRouterList_find(p, type, TRUE);
	Dz1TaskSigRouterListEntry *node = NULL;
	if (e) ERR_SET_OUT(&err, EEXIST);
	else if ((node = Dz1TaskSigRouterListEntry_new(NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1TaskSigRouterListEntry_del, (void *)node);

		if ((node->entry = Dz1TaskSigRouterEntry_new(type, mask, func, &err)) == NULL) ERR_OUT(&err);
		else if (p->head == NULL) p->head = p->tail = node;
		else
		{
			bool_t inserted = FALSE;
			Dz1TaskSigRouterListEntry *i = NULL;
			for (i = p->head; i; i = i->next)
			{
				e = i->entry;
				if (mask > e->mask || (mask == e->mask && type > e->type))
				{
					if (i->prev) i->prev->next = node;

					node->prev = i->prev;
					node->next = i;

					i->prev = node;

					if (i == p->head) p->head = node;

					inserted = TRUE;

					break;
				}
			}

			if (!inserted)
			{
				p->tail->next = node;
				node->prev = p->tail;

				p->tail = node;
			}
		}
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1TaskSigRouterListEntry_del, (void *)node);
	}
	return err;
}

static void Dz1TaskSigRouterList_dereg(Dz1TaskSigRouterList *list, u32_t type)
{
	Dz1TaskSigRouterListEntry *p = list->head, **pprev = &list->head, *prev = NULL;
	Dz1TaskSigRouterEntry *e = NULL;
	while(p)
	{
		e = p->entry;
		if (e->type == type)
		{
			if (p == list->tail) list->tail = prev;

			*pprev = p->next;
			p->next = NULL;

			Dz1TaskSigRouterListEntry_del(p);

			break;
		}

		pprev = &p->next;
		prev = p;
		p = p->next;
	}
}

static Dz1TaskSigRouterList *Dz1TaskSigRouterList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskSigRouterList *ret = (Dz1TaskSigRouterList *)Dz1Calloc(sizeof(Dz1TaskSigRouterList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->head = ret->tail = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1TaskSigRouterList_del(Dz1TaskSigRouterList *p)
{
	if (!p) return;
	if (p->head)
	{
		Dz1TaskSigRouterListEntry *i = p->head, *next = NULL;
		while(i)
		{
			next = i->next;
			Dz1TaskSigRouterListEntry_del(i);
			i = next;
		}
	}
	Dz1Free(p);
}

static void Dz1TaskSigRouterList_dump(Dz1TaskSigRouterList *p, int tab)
{
	if (!p) return;
	if (p->head == NULL) Dz1Thread_tprintf(tab, "[Empty]\n");
	else
	{
		Dz1TaskSigRouterListEntry *i;
		for (i = p->head; i; i = i->next)
			Dz1TaskSigRouterListEntry_dump(i, tab);
	}
}

typedef struct Dz1TaskSigRouter
{
	void *tree;
	Dz1TaskSigRouterList *list;
} Dz1TaskSigRouter;

void *Dz1TaskSigRouter_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskSigRouter *ret = (Dz1TaskSigRouter *)Dz1Calloc(sizeof(Dz1TaskSigRouter), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TaskSigRouter_delAndSetNull, (void *)&ret);

		if ((ret->tree = Dz1AATree_new((Dz1CmpFunc)Dz1TaskSigRouterEntry_cmp,
										(Dz1DelFunc)Dz1TaskSigRouterEntry_del,
										(Dz1DumpFunc)Dz1TaskSigRouterEntry_dump, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->list = Dz1TaskSigRouterList_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TaskSigRouter_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TaskSigRouter_del(void *ptr)
{
	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	if (!p) return;
	if (p->tree) Dz1AATree_del(p->tree);
	if (p->list) Dz1TaskSigRouterList_del(p->list);
	Dz1Free(p);
}

/*
void Dz1TaskSigRouter_delAndSetNull(void *ptr)
{
	Dz1TaskSigRouter **p = (Dz1TaskSigRouter **)ptr;
	Dz1TaskSigRouter_del(*p); *p = NULL;
}
*/

void Dz1TaskSigRouter_dump(void *ptr, int tab)
{
	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	if (!p) return;
	if (Dz1AATree_isEmpty(p->tree) && p->list->head == NULL)
		Dz1Thread_tprintf(tab, "[Empty]\n");
	else
	{
		Dz1Thread_tprintf(tab, "Tree Order\n");
		Dz1AATree_dump(p->tree, tab+1);
		Dz1Thread_tprintf(tab, "List Order\n");
		Dz1TaskSigRouterList_dump(p->list, tab+1);
	}
}

Dz1Error Dz1TaskSigRouter_reg(void *ptr, u32_t type, u32_t mask, Dz1TaskSigMsgProcFunc func)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	if (mask == 0xFFFFFFFF)
	{
		Dz1TaskSigRouterEntry key, *e = NULL;
		key.type = type;
		if ((e = (Dz1TaskSigRouterEntry *)Dz1AATree_find(p->tree, &key)) != NULL)
			ERR_SET_OUT(&err, EEXIST);
		else if ((e = Dz1TaskSigRouterEntry_new(type, mask, func, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1TaskSigRouterEntry_del, (void *)e);

			if ((err = Dz1AATree_insert(p->tree, e)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1TaskSigRouterEntry_del, (void *)e);
		}
	}
	else
	{
		if ((err = Dz1TaskSigRouterList_reg(p->list, type, mask, func)).code) ERR_OUT(&err);
	}
	return err;
}

void Dz1TaskSigRouter_dereg(void *ptr, u32_t type, u32_t mask)
{
	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	if (mask == 0xFFFFFFFF)
	{
		Dz1TaskSigRouterEntry key;
		key.type = type;
		Dz1AATree_remove(p->tree, &key);
	}
	else
	{
		type &= mask;
		Dz1TaskSigRouterList_dereg(p->list, type);
	}
}

/*
Dz1TaskSigMsgProcFunc Dz1TaskSigRouter_find(void *ptr, u32_t type)
{
	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	Dz1TaskSigRouterEntry key = { type }, *e = Dz1AATree_find(p->tree, &key);
	if (e) return e->func;
	else return Dz1TaskSigRouterList_find(p->list, type);
}
*/

Dz1TaskProcStatus Dz1TaskSigRouter_proc(void *ptr, void *user_arg, void *user_resource, void *timer, void **sig_msg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1TaskSigRouter *p = (Dz1TaskSigRouter *)ptr;
	Dz1SigMsg **sg = (Dz1SigMsg **)sig_msg;

	Dz1TaskSigRouterEntry key, *e = NULL;
	key.type = (*sg)->type;
	if ((e = (Dz1TaskSigRouterEntry *)Dz1AATree_find(p->tree, &key)) == NULL && (e = _Dz1TaskSigRouterList_find(p->list, (*sg)->type, FALSE)) == NULL)
	{
		ret = Dz1TaskProcStatus_nohandle;
	}
	else if ((ret = e->func(user_arg, user_resource, timer, sig_msg, errp)) == Dz1TaskProcStatus_error) ERR_OUT(errp);
	else if (ret == Dz1TaskProcStatus_nohandle)
	{
		u32_t lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), &lv);
		if (lv & DZ1_THREAD_LOG_CRITICAL)
			Dz1Thread_eprintf("!!! Message Implementation [%08X] has bug !!!\n", key.type);
	}

	return ret;
}
