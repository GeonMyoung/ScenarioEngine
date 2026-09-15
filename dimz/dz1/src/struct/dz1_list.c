#include <dz1_error.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_list.h"

static Dz1ListNode *Dz1ListNode_new(void *data, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ListNode *ret = (Dz1ListNode *)Dz1Calloc(sizeof(Dz1ListNode), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->data = data;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1ListNode_del(Dz1ListNode *p, Dz1DelFunc dataDel)
{
	if (!p) return;
	if (p->data && dataDel) dataDel(p->data);
	Dz1Free(p);
}

static void Dz1ListNode_dump(Dz1ListNode *p, Dz1DumpFunc dataDump, int tab)
{
	if (!p) return;
	if (p->data && dataDump) dataDump(p->data, tab);
}

Dz1Error Dz1List_add(Dz1List *list, void *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListNode *n = Dz1ListNode_new(data, &err);
	if (n == NULL) ERR_OUT(&err);
	else
	{
		if (list->head)
		{
			list->tail->next = n;
			n->prev = list->tail;
			list->tail = n;

			list->size++;
			list->sync = FALSE;
		}
		else list->head = list->tail = n;
	}
	return err;
}

void *Dz1List_extract(Dz1List *list, void *ptr)
{
	void *ret = NULL;
	Dz1ListNode **pprev = &list->head, *p = list->head;
	while(p)
	{
		if (p->data == ptr)
		{
			int old_state;
			pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);

			if (p == list->head) list->head = p->next;
			if (p == list->tail) list->tail = p->prev;

			if (p->next) p->next->prev = p->prev;
			if (p->prev) p->prev->next = p->next;
			p->next = p->prev = NULL;

			ret = p->data;
			p->data = NULL;

			list->size--;
			list->sync = FALSE;

			pthread_setcancelstate(old_state, NULL);
			break;
		}
		pprev = &p->next;
		p = p->next;
	}
	pprev = pprev;// no mean, avoid warning
	return ret;
}

bool_t Dz1List_remove(Dz1List *list, void *ptr)
{
	bool_t ret = FALSE;
	void *node = Dz1List_extract(list, ptr);
	if (node && list->dataDel)
	{
		list->dataDel(node);
		ret = TRUE;
	}
	return ret;
}

void **Dz1List_getArray(Dz1List *list, size_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	void **ret = NULL;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (list->size == 0) ERR_SET_OUT(errp, ENOENT);
	else if (list->sync == FALSE)
	{
		if (list->arr) Dz1Free(list->arr);
		list->arr = NULL;

		if ((list->arr = (void **)Dz1Calloc(sizeof(void **), list->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			int idx = 0;
			Dz1ListNode *i;
			for (idx = 0, i = list->head; i; idx++, i = i->next) list->arr[idx] = i->data;

			ret = list->arr;
			if (ret_cnt) *ret_cnt = (size_t)list->size;
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		ret = list->arr;
		if (ret_cnt) *ret_cnt = (size_t)list->size;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void *Dz1List_new(Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1List *ret = (Dz1List *)Dz1Calloc(sizeof(Dz1List), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->head = ret->tail = NULL;
		ret->size = 0;
		ret->arr = NULL;
		ret->sync = FALSE;

		ret->dataDel = dataDel;
//		ret->dataDump = dataDump;

		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1List_del(Dz1List *list)
{
	if (!list) return;
	if (list->head)
	{
		Dz1ListNode *p = list->head, *next = NULL;
		while(p)
		{
			next = p->next;
			Dz1ListNode_del(p, list->dataDel);
			p = next;
		}
	}
	if (list->arr) Dz1Free(list->arr);
	Dz1Free(list);
}

/*
void Dz1List_dump(Dz1List *list, int tab)
{
	if (!list) return;
	if (list->head == NULL) Dz1Thread_tprintf(tab, "Empty\n");
	else
	{
		Dz1ListNode *i;
		for (i = list->head; i; i = i->next)
			Dz1ListNode_dump(i, list->dataDump, tab);
	}
}
*/

int Dz1ListCmpArg_cmp(Dz1ListCmpArg *p)
{
	int ret = 0;
	if (p != NULL)
	{
		if (p->a_arr == NULL && p->b_arr == NULL) { }
		else if (p->a_arr == NULL) ret = -1;
		else if (p->b_arr == NULL) ret = 1;
		else
		{
			size_t i;
			void *a, *b;
			for (i = 0; i < p->cnt; i++)
			{
				a = p->a_arr[i];
				b = p->b_arr[i];
				if ((ret = p->e_cmp(a, b)) != 0) break;
			}
		}
	}
	return ret;
}