#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>

#include "dz1_parser_token.h"
#include "stack.h"

static StackNode *StackNode_new(char oper, Dz1Error *err)
{
	Dz1Error local_err, *errp = err ? err : &local_err;
	StackNode *ret = (StackNode *)Dz1Malloc(sizeof(StackNode), errp);
	if (ret)
	{
		ret->next = NULL;
		ret->oper = oper;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void StackNode_del(StackNode *p)
{
	if (!p) return;
	Dz1Free(p);
}

static void StackNode_dump(StackNode *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%c\n", p->oper);
}

static Dz1Error Stack_push(Stack *p, char oper)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	StackNode *node = NULL;
	if ((node = StackNode_new(oper, &err)) != NULL)
	{
		node->next = p->head;
		p->head = node;
	}
	return err;
}

static char Stack_pop(Stack *p, Dz1Error *err)
{
	Dz1Error local_err, *errp = err ? err : &local_err;
	StackNode *node = p->head;
	char ret = '\0';
	if (node == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		ret = node->oper;
		p->head = node->next;
		node->next = NULL;
		StackNode_del(node);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Stack_dump(Stack *p, int tab)
{
	if (!p) return;
	else
	{
		if (p->head)
		{
			StackNode *e = NULL;
			for (e = p->head; e; e = e->next)
				StackNode_dump(e, tab);
		}
		else
			Dz1Thread_printf("[Empty]\n");
	}
}

Stack *Stack_new(Dz1Error *err)
{
	Dz1Error local_err, *errp = err ? err : &local_err;
	Stack *ret = (Stack *)Dz1Malloc(sizeof(Stack), errp);
	if (ret)
	{
		ret->head = NULL;
		ret->push = Stack_push;
		ret->pop = Stack_pop;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Stack_del(Stack *p)
{
	if (!p) return;
	if (p->head)
	{
		StackNode *e = p->head, *next = NULL;
		while(e)
		{
			next = e->next;
			StackNode_del(e);
			e = next;
		}
	}
	Dz1Free(p);
}

