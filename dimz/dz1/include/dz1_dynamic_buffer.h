#ifndef DZ1_DYNAMIC_BUFFER_H
#define DZ1_DYNAMIC_BUFFER_H

#include <dz1_error.h>

typedef void Dz1DynamicBuffer;

#define DZ1_DYNAMIC_BUFFER_FRAG_SIZE		4096

DZ1_CPPLINK DZ1_DLLPORT Dz1DynamicBuffer	*Dz1DynamicBuffer_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1DynamicBuffer_del(Dz1DynamicBuffer *pDB);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1DynamicBuffer_delAndSetNull(void *ptr);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1DynamicBuffer_push(Dz1DynamicBuffer *pDB, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1DynamicBuffer_pop(Dz1DynamicBuffer *pDB, u8_t *buf, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1DynamicBuffer_getDataSize(Dz1DynamicBuffer *pDB, Dz1Error *err);

typedef void Dz1ElasticBufferfer;

DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBufferfer	*Dz1ElasticBufferfer_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1ElasticBufferfer_del(Dz1ElasticBufferfer *p);
static __inline__ void						 Dz1ElasticBufferfer_delAndSetNull(void *pptr)
{
	Dz1ElasticBufferfer **p = (Dz1ElasticBufferfer **)pptr;
	Dz1ElasticBufferfer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1ElasticBufferferA_dump(Dz1ElasticBufferfer *_p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1ElasticBufferferW_dump(Dz1ElasticBufferfer *_p, int tab);
#ifdef UNICODE
#define										 Dz1ElasticBufferfer_dump		Dz1ElasticBufferferW_dump
#else // UNICODE
#define										 Dz1ElasticBufferfer_dump		Dz1ElasticBufferferA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1ElasticBufferfer_dump		Dz1ElasticBufferferA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1ElasticBufferfer_read(Dz1ElasticBufferfer *_p, u8_t *dst_buf, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1ElasticBufferfer_write(Dz1ElasticBufferfer *_p, u8_t *data_buf, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1ElasticBufferfer_tell(Dz1ElasticBufferfer *_p, Dz1Error *err);

typedef enum Dz1ElasticBufferferSeek
{
	Dz1ElasticBufferferSeek_atFirst,
	Dz1ElasticBufferferSeek_atLast,
	Dz1ElasticBufferferSeek_atCurr
} Dz1ElasticBufferferSeek;

DZ1_CPPLINK DZ1_DLLPORT Dz1Error			 Dz1ElasticBufferfer_seek(Dz1ElasticBufferfer *_p, Dz1ElasticBufferferSeek seek, ssize_t pos);
DZ1_CPPLINK DZ1_DLLPORT ssize_t				 Dz1ElasticBufferfer_push(Dz1ElasticBufferfer *_p, u8_t *data_buf, size_t size, Dz1Error *err);

#endif

