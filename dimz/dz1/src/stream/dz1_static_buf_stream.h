#ifndef DZ1_STATIC_BUF_STREAM_H_LOCAL
#define DZ1_STATIC_BUF_STREAM_H_LOCAL

#include "dz1_aatree.h"
#include "dz1_io_stream.h"

///////////////////////////////////////////////////////////////////////////////
// Static Buffer Cursor
typedef struct Dz1StaticBufPos
{
	u32_t				 id;				// cursor ID
	u32_t				 pos;				// IO Position
} Dz1StaticBufPos;

DZ1_CPPLINK Dz1StaticBufPos *Dz1StaticBufPos_new(u32_t id, u32_t pos, Dz1Error *err);
DZ1_CPPLINK Dz1StaticBufPos *Dz1StaticBufPos_clone(Dz1StaticBufPos *src, Dz1Error *err);
DZ1_CPPLINK void Dz1StaticBufPos_del(Dz1StaticBufPos *p);
static __inline__ void Dz1StaticBufPos_delAndSetNull(void *pptr)
{
	Dz1StaticBufPos **p = (Dz1StaticBufPos **)pptr;
	Dz1StaticBufPos_del(*p); *p = NULL;
}

DZ1_CPPLINK void Dz1StaticBufPosA_dump(Dz1StaticBufPos *p, int tab);
DZ1_CPPLINK void Dz1StaticBufPosA_fdump(FILE *fp, Dz1StaticBufPos *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void Dz1StaticBufPosW_dump(Dz1StaticBufPos *p, int tab);
DZ1_CPPLINK void Dz1StaticBufPosW_fdump(FILE *fp, Dz1StaticBufPos *p, int tab);
#ifdef UNICODE
#define						 Dz1StaticBufPos_dump		Dz1StaticBufPosW_dump
#define						 Dz1StaticBufPos_fdump		Dz1StaticBufPosW_fdump
#else // UNICODE
#define						 Dz1StaticBufPos_dump		Dz1StaticBufPosA_dump
#define						 Dz1StaticBufPos_fdump		Dz1StaticBufPosA_fdump
#endif // // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1StaticBufPos_dump		Dz1StaticBufPosA_dump
#define						 Dz1StaticBufPos_fdump		Dz1StaticBufPosA_fdump
#endif // UNIX_SYSTEM
// Static Buffer Cursor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Static Buffer Stream

DZ1_CPPLINK u32_t				 Dz1StaticBufStream_getCursor(Dz1StaticBufStream *p, Dz1Error *err);
DZ1_CPPLINK void				 Dz1StaticBufStream_putCursor(Dz1StaticBufStream *p, u32_t stream_id);

DZ1_CPPLINK ssize_t				 Dz1StaticBufStream_read(Dz1StaticBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1StaticBufStream_write(Dz1StaticBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1StaticBufStream_seek(Dz1StaticBufStream *p, u32_t stream_id, s64_t movement, int origin);
DZ1_CPPLINK s64_t				 Dz1StaticBufStream_tell(Dz1StaticBufStream *p, u32_t stream_id, Dz1Error *err);
DZ1_CPPLINK bool_t				 Dz1StaticBufStream_isEOF(Dz1StaticBufStream *p, u32_t stream_id);
DZ1_CPPLINK ssize_t				 Dz1StaticBufStream_drain(Dz1StaticBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err);

// Static Buffer Stream
///////////////////////////////////////////////////////////////////////////////

#endif
