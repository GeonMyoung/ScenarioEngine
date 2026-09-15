#ifndef DZ1_FIFO_STATIC_H_LOCAL
#define DZ1_FIFO_STATIC_H_LOCAL

#include <dz1_fifo.h>

typedef struct Dz1FifoStatic
{
	void **arr;
	u32_t size;
	u32_t head;
	u32_t tail;
	bool_t status;
	bool_t isAutoPop;
} Dz1FifoStatic;

DZ1_CPPLINK Dz1Error Dz1FifoStatic_init(Dz1FifoStatic *p, u32_t size, bool_t autoPop);
DZ1_CPPLINK void Dz1FifoStatic_clean(Dz1FifoStatic *p, Dz1DelFunc del);
DZ1_CPPLINK void *Dz1FifoStatic_pop(Dz1FifoStatic *p, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1FifoStatic_push(Dz1FifoStatic *p, void *data, Dz1DelFunc del);
DZ1_CPPLINK void Dz1FifoStatic_dump(Dz1FifoStatic *p, int tab, Dz1DumpFunc dump);
DZ1_CPPLINK bool_t Dz1FifoStatic_isFull(Dz1FifoStatic *p);
DZ1_CPPLINK bool_t Dz1FifoStatic_isEmpty(Dz1FifoStatic *p);
DZ1_CPPLINK u32_t Dz1FifoStatic_count(Dz1FifoStatic *p);
DZ1_CPPLINK void *Dz1FifoStatic_getFirst(Dz1FifoStatic *p);
DZ1_CPPLINK void *Dz1FifoStatic_getLast(Dz1FifoStatic *p);

typedef struct Dz1FifoStaticCursor
{
	Dz1FifoStatic *fifo;
	u32_t pos;
} Dz1FifoStaticCursor;

DZ1_CPPLINK Dz1Error Dz1FifoStaticCursor_init(Dz1FifoStaticCursor *p, Dz1FifoStatic *fifo, Dz1FifoCursorPos pos);
DZ1_CPPLINK void Dz1FifoStaticCursor_del(Dz1FifoStaticCursor *p);

static __inline__ void Dz1FifoStaticCursor_delAndSetNull(void *ptr)
{
	Dz1FifoStaticCursor **p = (Dz1FifoStaticCursor **)ptr;
	Dz1FifoStaticCursor_del(*p); *p = NULL;
}

DZ1_CPPLINK bool_t Dz1FifoStaticCursor_cond(Dz1FifoStaticCursor *p);
DZ1_CPPLINK bool_t Dz1FifoStaticCursor_isFirst(Dz1FifoStaticCursor *p);
DZ1_CPPLINK bool_t Dz1FifoStaticCursor_isLast(Dz1FifoStaticCursor *p);
DZ1_CPPLINK void Dz1FifoStaticCursor_next(Dz1FifoStaticCursor *p, bool_t notNull);
DZ1_CPPLINK void Dz1FifoStaticCursor_prev(Dz1FifoStaticCursor *p, bool_t notNull);
DZ1_CPPLINK void *Dz1FifoStaticCursor_data(Dz1FifoStaticCursor *p);

#endif
