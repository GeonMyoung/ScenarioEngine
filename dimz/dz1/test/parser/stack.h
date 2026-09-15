#ifndef STACK_H
#define STACK_H

#include <dz1_error.h>

typedef struct StackNode
{
	struct StackNode *next;
	char oper;
} StackNode;

typedef struct Stack
{
	StackNode *head;
	Dz1Error (*push)(struct Stack *p, char oper);
	char (*pop)(struct Stack *p, Dz1Error *err);
} Stack;

DZ1_CPPLINK Stack *Stack_new(Dz1Error *err);
DZ1_CPPLINK void Stack_del(Stack *p);
DZ1_CPPLINK void Stack_dump(Stack *p, int tab);
#endif

