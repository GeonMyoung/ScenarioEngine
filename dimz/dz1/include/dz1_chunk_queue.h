#ifndef DZ1_CHUNK_QUEUE_H
#define DZ1_CHUNK_QUEUE_H

#include <dz1_error.h>

typedef void Dz1Chunk;
DZ1_CPPLINK DZ1_DLLPORT void Dz1Chunk_del(Dz1Chunk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Chunk_dump(Dz1Chunk *p, int tab);
static __inline__ void Dz1Chunk_delAndSetNull(void *ptr)
{
	Dz1Chunk **p = (Dz1Chunk **)ptr;
	Dz1Chunk_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void *Dz1Chunk_getData(Dz1Chunk *p);
DZ1_CPPLINK DZ1_DLLPORT size_t Dz1Chunk_getSize(Dz1Chunk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Chunk_terminate(Dz1Chunk *p, Dz1Error *result);

typedef void Dz1ChunkQueue;

DZ1_CPPLINK DZ1_DLLPORT Dz1ChunkQueue *Dz1ChunkQueue_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ChunkQueue_del(Dz1ChunkQueue *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ChunkQueue_dump(Dz1ChunkQueue *p, int tab);

typedef void (*Dz1ChunkCallback)(void *cbParam, u8_t *data, size_t size, Dz1Error *result);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1ChunkQueue_push(Dz1ChunkQueue *p, u8_t *data, size_t size, Dz1ChunkCallback cb, void *cbParam);
DZ1_CPPLINK DZ1_DLLPORT Dz1Chunk *Dz1ChunkQueue_pop(Dz1ChunkQueue *p, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Chunk *Dz1ChunkQueue_get(Dz1ChunkQueue *p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ChunkQueue_consume(Dz1ChunkQueue *p);

#endif