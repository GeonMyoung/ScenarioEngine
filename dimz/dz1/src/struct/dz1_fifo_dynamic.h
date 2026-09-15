#ifndef DZ1_FIFO_DYNAMIC_H_LOCAL
#define DZ1_FIFO_DYNAMIC_H_LOCAL

#include <dz1_error.h>
#include <dz1_fifo.h>

typedef struct Dz1FifoDynamicEntry
{
	struct Dz1FifoDynamicEntry *prev;	// is ref
	struct Dz1FifoDynamicEntry *next;	// is ref
	void *data;
} Dz1FifoDynamicEntry;

DZ1_CPPLINK Dz1FifoDynamicEntry *Dz1FifoDynamicEntry_new(void *data, Dz1Error *err);
DZ1_CPPLINK void Dz1FifoDynamicEntry_del(Dz1FifoDynamicEntry *p, Dz1DelFunc del);

typedef struct Dz1FifoDynamic
{
	u32_t count;
	Dz1FifoDynamicEntry *head;
	Dz1FifoDynamicEntry *tail;
} Dz1FifoDynamic;

DZ1_CPPLINK void	 Dz1FifoDynamic_init(Dz1FifoDynamic *p);
DZ1_CPPLINK void	 Dz1FifoDynamic_clean(Dz1FifoDynamic *p, Dz1DelFunc del);
DZ1_CPPLINK Dz1Error Dz1FifoDynamic_pushHead(Dz1FifoDynamic *p, void *data);
DZ1_CPPLINK Dz1Error Dz1FifoDynamic_pushTail(Dz1FifoDynamic *p, void *data);
#define				 Dz1FifoDynamic_push(p, data)		Dz1FifoDynamic_pushTail(p, data)
DZ1_CPPLINK void	*Dz1FifoDynamic_popHead(Dz1FifoDynamic *p, Dz1Error *err);
DZ1_CPPLINK void	*Dz1FifoDynamic_popTail(Dz1FifoDynamic *p, Dz1Error *err);
#define				 Dz1FifoDynamic_pop(p, err)			Dz1FifoDynamic_popHead(p, err);
DZ1_CPPLINK void	 Dz1FifoDynamic_dump(Dz1FifoDynamic *p, int tab, Dz1DumpFunc dump);
DZ1_CPPLINK bool_t	 Dz1FifoDynamic_remove(Dz1FifoDynamic *p, void *removeptr, Dz1DelFunc del);
DZ1_CPPLINK void	*Dz1FifoDynamic_extract(Dz1FifoDynamic *p, void *removeptr, Dz1DelFunc del);

DZ1_CPPLINK bool_t	 Dz1FifoDynamic_isEmpty(Dz1FifoDynamic *p);
DZ1_CPPLINK u32_t	 Dz1FifoDynamic_count(Dz1FifoDynamic *p);
DZ1_CPPLINK void	*Dz1FifoDynamic_getFirst(Dz1FifoDynamic *p);
DZ1_CPPLINK void	*Dz1FifoDynamic_getLast(Dz1FifoDynamic *p);

typedef struct Dz1FifoDynamicCursor
{
	Dz1FifoDynamic *fifo;
	Dz1FifoDynamicEntry *pos;
} Dz1FifoDynamicCursor;

DZ1_CPPLINK Dz1Error Dz1FifoDynamicCursor_init(Dz1FifoDynamicCursor *p, Dz1FifoDynamic *fifo, Dz1FifoCursorPos pos);
DZ1_CPPLINK int		 Dz1FifoDynamicCursor_cond(Dz1FifoDynamicCursor *p);
DZ1_CPPLINK bool_t	 Dz1FifoDynamicCursor_isFirst(Dz1FifoDynamicCursor *p);
DZ1_CPPLINK bool_t	 Dz1FifoDynamicCursor_isLast(Dz1FifoDynamicCursor *p);
DZ1_CPPLINK void	 Dz1FifoDynamicCursor_next(Dz1FifoDynamicCursor *p, bool_t notNull);
DZ1_CPPLINK void	 Dz1FifoDynamicCursor_prev(Dz1FifoDynamicCursor *p, bool_t notNull);
DZ1_CPPLINK void	*Dz1FifoDynamicCursor_data(Dz1FifoDynamicCursor *p);

#endif
