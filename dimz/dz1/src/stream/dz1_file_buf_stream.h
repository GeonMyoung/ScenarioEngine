#ifndef DZ1_FILE_BUF_STREAM_H_LOCAL
#define DZ1_FILE_BUF_STREAM_H_LOCAL

#include "dz1_stdio.h"
#include "dz1_aatree.h"
#include "dz1_io_stream.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1FileBufPos
typedef struct Dz1FileBufPos
{
	u32_t					 id;
	FILEPOSt				 pos;
} Dz1FileBufPos;

DZ1_CPPLINK Dz1FileBufPos *Dz1FileBufPos_new(u32_t id, s64_t pos, Dz1Error *err);
DZ1_CPPLINK Dz1FileBufPos *Dz1FileBufPos_clone(Dz1FileBufPos *src, Dz1Error *err);
DZ1_CPPLINK void Dz1FileBufPos_del(Dz1FileBufPos *p);
static __inline__ void Dz1FileBufPos_delAndSetNull(void *pptr)
{
	Dz1FileBufPos **p = (Dz1FileBufPos **)pptr;
	Dz1FileBufPos_del(*p); *p = NULL;
}

DZ1_CPPLINK void Dz1FileBufPosA_dump(Dz1FileBufPos *p, int tab);
DZ1_CPPLINK void Dz1FileBufPosA_fdump(FILE *fp, Dz1FileBufPos *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void Dz1FileBufPosW_dump(Dz1FileBufPos *p, int tab);
DZ1_CPPLINK void Dz1FileBufPosW_fdump(FILE *fp, Dz1FileBufPos *p, int tab);
#ifdef UNICODE
#define						 Dz1FileBufPos_dump			Dz1FileBufPosW_dump
#define						 Dz1FileBufPos_fdump		Dz1FileBufPosW_fdump
#else // UNICODE
#define						 Dz1FileBufPos_dump			Dz1FileBufPosA_dump
#define						 Dz1FileBufPos_fdump		Dz1FileBufPosA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1FileBufPos_dump			Dz1FileBufPosA_dump
#define						 Dz1FileBufPos_fdump		Dz1FileBufPosA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK int Dz1FileBufPos_cmp(Dz1FileBufPos *a, Dz1FileBufPos *b);
// Dz1FileBufPos
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1FileBufStream

DZ1_CPPLINK u32_t				 Dz1FileBufStream_getCursor(Dz1FileBufStream *p, Dz1Error *err);
DZ1_CPPLINK void				 Dz1FileBufStream_putCursor(Dz1FileBufStream *p, u32_t stream_id);

DZ1_CPPLINK ssize_t				 Dz1FileBufStream_read(Dz1FileBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1FileBufStream_write(Dz1FileBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1FileBufStream_seek(Dz1FileBufStream *p, u32_t stream_id, s64_t movement, int origin);
DZ1_CPPLINK s64_t				 Dz1FileBufStream_tell(Dz1FileBufStream *p, u32_t stream_id, Dz1Error *err);
DZ1_CPPLINK bool_t				 Dz1FileBufStream_isEOF(Dz1FileBufStream *p, u32_t stream_id);
DZ1_CPPLINK ssize_t				 Dz1FileBufStream_drain(Dz1FileBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err);
// Dz1FileBufStream
///////////////////////////////////////////////////////////////////////////////

#endif