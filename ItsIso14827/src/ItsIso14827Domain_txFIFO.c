#include "ItsIso14827Domain_txFIFO.h"

ItsIso14827DomainTxFifo *ItsIso14827DomainTxFifo_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827DomainTxFifo *ret = (ItsIso14827DomainTxFifo *)Dz1Calloc(sizeof(ItsIso14827DomainTxFifo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainTxFifo_delAndSetNull, (void *)&ret);
		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)ItsIso14827DomainTxEntry_del,
									 (Dz1DumpFunc)ItsIso14827DomainTxEntry_dump, 0, errp)) == NULL) ERR_OUT(errp);

		else if ((ret->idx = Dz1AATree_new((Dz1CmpFunc)ItsIso14827DomainTxEntry_cmp,
											NULL,
											(Dz1DumpFunc)ItsIso14827DomainTxEntry_dump,
											errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ItsIso14827DomainTxFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827DomainTxFifo_del(ItsIso14827DomainTxFifo *p)
{
	if (p == NULL) return;
	if (p->idx) Dz1AATree_del(p->idx);
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void ItsIso14827DomainTxFifo_dump(ItsIso14827DomainTxFifo *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else if (Dz1Fifo_count(p->fifo) == 0) Dz1Thread_printf("Empty\n");
	else Dz1Fifo_dump(p->fifo, tab);
}

typedef struct _AddCancelArg
{
	Dz1AATree *idx;
	ItsIso14827DomainTxEntry *msg;
} _AddCancelArg;

static void _addCancel(void *ptr)
{
	_AddCancelArg *arg = (_AddCancelArg *)ptr;
	Dz1AATree_extract(arg->idx, arg->msg);
}

Dz1Error ItsIso14827DomainTxFifo_push(ItsIso14827DomainTxFifo *p, ItsIso14827DomainTxEntry *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p == NULL || msg == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Dz1AATree_insert(p->idx, (void *)msg)).code) ERR_OUT(&err);
	else
	{
		_AddCancelArg arg = { p->idx, msg };
		pthread_cleanup_push(_addCancel, (void *)&arg);

		if ((err = Dz1Fifo_push(p->fifo, (void *)msg)).code) ERR_OUT(&err);

		pthread_cleanup_pop(err.code); // (_addCancel, (void *)&arg);
	}
	return err;
}

ItsIso14827DomainTxEntry *ItsIso14827DomainTxFifo_pop(ItsIso14827DomainTxFifo *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827DomainTxEntry *ret = (ItsIso14827DomainTxEntry *)Dz1Fifo_pop(p->fifo, errp);
	if (ret) Dz1AATree_extract(p->idx, ret);
	return ret;
}

bool_t ItsIso14827DomainTxFifo_isEmpty(ItsIso14827DomainTxFifo *p)
{
	return Dz1Fifo_isEmpty(p->fifo);	
}

ItsIso14827DomainTxEntry *ItsIso14827DomainTxFifo_getTail(ItsIso14827DomainTxFifo *p)
{
	return (ItsIso14827DomainTxEntry *)Dz1Fifo_getFirst(p->fifo);
}
