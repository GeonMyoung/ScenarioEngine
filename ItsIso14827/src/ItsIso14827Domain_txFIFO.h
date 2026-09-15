#ifndef ITS_ISO_14827_DOMAIN_TX_FIFO_H_LOCAL
#define ITS_ISO_14827_DOMAIN_TX_FIFO_H_LOCAL

#include <dz1_fifo.h>
#include <dz1_aatree.h>

#include "ItsIso14827DomainTxFifoDef.h"

typedef struct ItsIso14827DomainTxFifo
{
	Dz1Fifo						*fifo;
	Dz1AATree					*idx;
} ItsIso14827DomainTxFifo;

DZ1_CPPLINK ItsIso14827DomainTxFifo *ItsIso14827DomainTxFifo_new(Dz1Error *err);
DZ1_CPPLINK void ItsIso14827DomainTxFifo_del(ItsIso14827DomainTxFifo *p);
static __inline__ void ItsIso14827DomainTxFifo_delAndSetNull(void *ptr)
{
	ItsIso14827DomainTxFifo **p = (ItsIso14827DomainTxFifo **)ptr;
	ItsIso14827DomainTxFifo_del(*p); *p = NULL;
}

DZ1_CPPLINK void ItsIso14827DomainTxFifo_dump(ItsIso14827DomainTxFifo *p, int tab);

DZ1_CPPLINK Dz1Error ItsIso14827DomainTxFifo_push(ItsIso14827DomainTxFifo *fifo, ItsIso14827DomainTxEntry *msg);
DZ1_CPPLINK ItsIso14827DomainTxEntry *ItsIso14827DomainTxFifo_pop(ItsIso14827DomainTxFifo *fifo, Dz1Error *err);
DZ1_CPPLINK bool_t ItsIso14827DomainTxFifo_isEmpty(ItsIso14827DomainTxFifo *fifo);
DZ1_CPPLINK ItsIso14827DomainTxEntry *ItsIso14827DomainTxFifo_getTail(ItsIso14827DomainTxFifo *fifo);

#endif