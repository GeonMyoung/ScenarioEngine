#ifndef DZ1_FIFO_REENTRANT_H
#define DZ1_FIFO_REENTRANT_H

#include <dz1_error.h>

/*
 * Dz1FifoReentrant_new : create Dz1FifoReentrant structure
 *
 * @del : user data delete function
 * @dump : user data dump function
 * @size : fifo size
 * @err : Address of Dz1Error structure
 *
 * return : Address of Dz1Fifo Structure
 *
 * NOTE :
 *   size == 0 -> Dynamic size FIFO
 *   size > 0 -> Static sized FIFO
 *               When fifo is full, Dz1Fifo_push will return ENOMEM
 *   size < 0 -> Static sized FIFO
 *               When fifo is full, Dz1Fifo_push will return SUCCESS and First Entry will deleted
 */
DZ1_CPPLINK DZ1_DLLPORT void *Dz1FifoReentrant_new(Dz1DelFunc del, Dz1DumpFunc dump, int size, Dz1Error *err);

/*
 * Dz1FifoReentrant_del : Delete Dz1FifoReentrant structure
 *
 * @p : Address of Dz1Fifo
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1FifoReentrant_del(void *p);

static __inline__ void Dz1FifoReentrant_delAndSetNull(void *pptr)
{
	void **p = (void **)pptr;
	Dz1FifoReentrant_del(*p); *p = NULL;
}

/*
 * Dz1FifoReentrant_push : Push user data to target FIFO
 *
 * @ptr : target FIFO
 * @data : user data to push
 * @wait_us : wait time in micro second. wait_us == 0 : non-wait,  wait_us < 0 : unlimited wait.
 *
 * return : Dz1Error Structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FifoReentrant_push(void *ptr, void *data, s64_t wait_usec);

/*
 * Dz1FifoReentrant_pop : Pop user data from target FIFO
 *
 * @ptr : target FIFO
 * @wait_us : wait time in micro second. wait_us == 0 : non-wait,  wait_us < 0 : unlimited wait.
 * @err : Address of Dz1Error structure
 *
 * return : user data
 */
DZ1_CPPLINK DZ1_DLLPORT void *Dz1FifoReentrant_pop(void *ptr, s64_t wait_us, Dz1Error *err);

/*
 * Dz1FifoReentrant_dump : Dump Dz1Fifo to target console
 *
 * @ptr : Address of Dz1Fifo
 * @tab : indent level
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1FifoReentrant_dump(void *ptr, int tab);

#endif
