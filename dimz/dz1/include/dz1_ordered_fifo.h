#ifndef DZ1_ORDERED_FIFO_H
#define DZ1_ORDERED_FIFO_H

#include <dz1_error.h>

typedef void Dz1OrderedFifo;

#define								 Dz1OrderedFifo_new(cmp, del, dump, errp)	_Dz1OrderedFifo_new((cmp), (del), (dump), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void	   *_Dz1OrderedFifo_new(Dz1CmpFunc cmp, Dz1DelFunc del, Dz1DumpFunc dump, Dz1Error *err, const char *__file__, int __line__);

DZ1_CPPLINK DZ1_DLLPORT void		 Dz1OrderedFifo_empty(Dz1OrderedFifo *p);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1OrderedFifo_del(Dz1OrderedFifo *p);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1OrderedFifo_dump(Dz1OrderedFifo *p, int tab);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1OrderedFifo_push(Dz1OrderedFifo *p, void *data);
DZ1_CPPLINK DZ1_DLLPORT void		*Dz1OrderedFifo_pop(Dz1OrderedFifo *p, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT void		*Dz1OrderedFifo_find(Dz1OrderedFifo *p, void *key);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1OrderedFifo_remove(Dz1OrderedFifo *p, void *key);
DZ1_CPPLINK DZ1_DLLPORT void		*Dz1OrderedFifo_extract(Dz1OrderedFifo *p, void *key);

typedef Dz1Error (*Dz1OrderedFifoTravelFunc)(void *param, void *data);
#define								 Dz1OrderedFifo_travel		Dz1OrderedFifo_travelForward
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1OrderedFifo_travelForward(Dz1OrderedFifo *ptr, Dz1OrderedFifoTravelFunc func, void *param);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1OrderedFifo_travelBackward(Dz1OrderedFifo *ptr, Dz1OrderedFifoTravelFunc func, void *param);

DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1OrderedFifo_isEmpty(Dz1OrderedFifo *p);
static __inline__ bool_t			 Dz1OrderedFifo_isFull(Dz1OrderedFifo *p) { return FALSE; }

DZ1_CPPLINK DZ1_DLLPORT u32_t		 Dz1OrderedFifo_count(Dz1OrderedFifo *p);

DZ1_CPPLINK DZ1_DLLPORT void		*Dz1OrderedFifo_getFirst(Dz1OrderedFifo *p);
#define								 Dz1OrderedFifo_getHead		Dz1OrderedFifo_getFirst

DZ1_CPPLINK DZ1_DLLPORT void		*Dz1OrderedFifo_getLast(Dz1OrderedFifo *p);
#define								 Dz1OrderedFifo_getTail		Dz1OrderedFifo_getLast

static __inline__ void				 Dz1OrderedFifo_delAndSetNull(void *ptr)
{
	void **p = (void **)ptr;
	Dz1OrderedFifo_del(*p); *p = NULL;
}


#endif