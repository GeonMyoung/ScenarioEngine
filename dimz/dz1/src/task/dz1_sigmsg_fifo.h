#ifndef DZ1_SIG_MSG_FIFO_H_LOCAL
#define DZ1_SIG_MSG_FIFO_H_LOCAL

#include <dz1_error.h>
#include "dz1_sigmsg.h"

typedef struct Dz1SigMsgFifo
{
	Dz1Sync sync;
	void *fifo;
	bool_t halted;
} Dz1SigMsgFifo;

DZ1_CPPLINK Dz1SigMsgFifo *Dz1SigMsgFifo_new(size_t size, Dz1Error *err);
DZ1_CPPLINK void Dz1SigMsgFifo_del(Dz1SigMsgFifo *p);
static __inline__ void Dz1SigMsgFifo_delAndSetNull(void *ptr)
{
	Dz1SigMsgFifo **p = (Dz1SigMsgFifo **)ptr;
	Dz1SigMsgFifo_del(*p); *p = NULL;
}

DZ1_CPPLINK Dz1Error Dz1SigMsgFifo_push(Dz1SigMsgFifo *p, Dz1SigMsg **msg, u64_t *wait_us);
DZ1_CPPLINK Dz1SigMsg *Dz1SigMsgFifo_pop(Dz1SigMsgFifo *p, u64_t *wait_us, Dz1Error *err);

DZ1_CPPLINK void Dz1SigMsgFifo_halt(Dz1SigMsgFifo *p);

#endif
