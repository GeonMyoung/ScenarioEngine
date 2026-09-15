#ifndef DZ1_ORDERED_FIFO_H_LOCAL
#define DZ1_ORDERED_FIFO_H_LOCAL

#include <dz1_ordered_fifo.h>

typedef struct Dz1ORDFifoEntry
{
	struct Dz1ORDFifoEntry *prev;
	struct Dz1ORDFifoEntry *next;
	void *data;
} Dz1ORDFifoEntry;

typedef struct Dz1ORDFifo
{
	u32_t			 count;
	Dz1ORDFifoEntry *head;
	Dz1ORDFifoEntry *tail;
	Dz1CmpFunc		 cmp;
	Dz1DumpFunc		 dump;
	Dz1DelFunc		 del;
} Dz1ORDFifo;

#endif