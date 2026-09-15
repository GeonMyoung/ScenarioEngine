#ifndef DZ1_ELASTIC_BUF_STREAM_H_LOCAL
#define DZ1_ELASTIC_BUF_STREAM_H_LOCAL

#include <dz1_aatree.h>
#include "dz1_io_stream.h"

typedef struct Dz1ElasticBufPos
{
	u32_t				 id;						// key
	Dz1ElasticBufEntry	*entry;						// current entry position
	u32_t				 pos;						// current byte position
} Dz1ElasticBufPos;

DZ1_CPPLINK Dz1ElasticBufPos	*Dz1ElasticBufPos_new(u32_t id, Dz1ElasticBufEntry *entry, u32_t pos, Dz1Error *err);
DZ1_CPPLINK void				 Dz1ElasticBufPos_del(Dz1ElasticBufPos *p);
static __inline__ void						 Dz1ElasticBufPos_delAndSetNull(void *pptr)
{
	Dz1ElasticBufPos **p = (Dz1ElasticBufPos **)pptr;
	Dz1ElasticBufPos_del(*p); *p = NULL;
}

DZ1_CPPLINK int					 Dz1ElasticBufPos_cmp(Dz1ElasticBufPos *a, Dz1ElasticBufPos *b);

DZ1_CPPLINK u32_t				 Dz1ElasticBufStream_getCursor(Dz1ElasticBufStream *p, Dz1Error *err);
DZ1_CPPLINK void				 Dz1ElasticBufStream_putCursor(Dz1ElasticBufStream *p, u32_t stream_id);

DZ1_CPPLINK ssize_t				 Dz1ElasticBufStream_read (Dz1ElasticBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1ElasticBufStream_write(Dz1ElasticBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1ElasticBufStream_seek (Dz1ElasticBufStream *p, u32_t stream_id, s64_t movement, int origin);
DZ1_CPPLINK s64_t				 Dz1ElasticBufStream_tell (Dz1ElasticBufStream *p, u32_t stream_id, Dz1Error *err);
DZ1_CPPLINK bool_t				 Dz1ElasticBufStream_isEOF(Dz1ElasticBufStream *p, u32_t stream_id);
DZ1_CPPLINK ssize_t				 Dz1ElasticBufStream_drain(Dz1ElasticBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err);

#endif