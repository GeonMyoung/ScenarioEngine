#ifndef DZ1_STREAM_FIFO_H
#define DZ1_STREAM_FIFO_H

#include <dz1_error.h>

typedef void Dz1StreamFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1StreamFifo	*Dz1StreamFifo_new(size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StreamFifo_del(Dz1StreamFifo *ptr);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StreamFifo_delAndSetNull(void *ptr);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StreamFifoA_dump(Dz1StreamFifo *ptr, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StreamFifoW_dump(Dz1StreamFifo *ptr, int tab);
#ifdef UNICODE
#define									 Dz1StreamFifo_dump			Dz1StreamFifoW_dump
#else // UNICODE
#define									 Dz1StreamFifo_dump			Dz1StreamFifoA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1StreamFifo_dump			Dz1StreamFifoA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK bool_t						 Dz1StreamFifo_isFull(Dz1StreamFifo *fifop);
DZ1_CPPLINK bool_t						 Dz1StreamFifo_isEmpty(Dz1StreamFifo *fifop);
DZ1_CPPLINK ssize_t						 Dz1StreamFifo_getDataSize(Dz1StreamFifo *p, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StreamFifo_push(Dz1StreamFifo *fifop, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StreamFifo_pop(Dz1StreamFifo *fifop, u8_t *buf, size_t size, Dz1Error *err);

#endif

