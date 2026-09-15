#ifndef DZ1_LIST_H
#define DZ1_LIST_H

#include <dz1_error.h>

typedef struct Dz1ListNode
{
	struct Dz1ListNode *prev;
	struct Dz1ListNode *next;
	void *data;
} Dz1ListNode;

typedef struct Dz1List
{
	Dz1ListNode *head;
	Dz1ListNode *tail;
	int size;
	void **arr;
	bool_t sync;

	Dz1DelFunc dataDel;
//	Dz1DumpFunc dataDump;
} Dz1List;

DZ1_CPPLINK Dz1Error Dz1List_add(Dz1List *list, void *data);
DZ1_CPPLINK void *Dz1List_extract(Dz1List *list, void *ptr);
DZ1_CPPLINK bool_t Dz1List_remove(Dz1List *list, void *ptr);
DZ1_CPPLINK void **Dz1List_getArray(Dz1List *list, size_t *ret_cnt, Dz1Error *err);
DZ1_CPPLINK void *Dz1List_new(Dz1DelFunc dataDel, Dz1DumpFunc dataDump, Dz1Error *err);
DZ1_CPPLINK void Dz1List_del(Dz1List *list);

typedef struct Dz1ListCmpArg
{
	void **a_arr;
	void **b_arr;
	size_t cnt;
	Dz1CmpFunc e_cmp;
} Dz1ListCmpArg;
DZ1_CPPLINK int Dz1ListCmpArg_cmp(Dz1ListCmpArg *p);

#endif
