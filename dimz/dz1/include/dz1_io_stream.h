#ifndef DZ1_IO_STREAM_H
#define DZ1_IO_STREAM_H

#include <dz1_stdio.h>
#include <dz1_aatree.h>
#include <dz1_elastic_buf.h>

typedef enum Dz1IOStreamEndian
{
	Dz1IOStreamEndian_little,
	Dz1IOStreamEndian_big
} Dz1IOStreamEndian;

#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
#define Dz1StreamMyEndian			Dz1IOStreamEndian_little
#elif DZ1_ENDIAN == DZ1_ENDIAN_BIG
#define Dz1StreamMyEndian			Dz1IOStreamEndian_big
#else
#error ENDIAN
#endif
///////////////////////////////////////////////////////////////////////////////
// File Buffer Stream
// 쓰기모드가 있는 경우, KeepData, InitialPosition 옵션이 사용가능
typedef enum Dz1StreamFileMode
{
	Dz1StreamFileMode_RD,			// 읽기만								"rb"

	Dz1StreamFileMode_WR,			// 쓰기만	(기존 데이터 삭제)			"wb"
	Dz1StreamFileMode_WRO,			// 쓰기만	(기존 데이터 유지)			"r+b" -> "w+b"
	Dz1StreamFileMode_WRA,			// 쓰기만	(기존 데이터 유지, 맨끝)	"a+b"

	Dz1StreamFileMode_RW,			// 읽고 쓰기(기존 데이터 삭제)			"w+b"
	Dz1StreamFileMode_RWO,			// 읽고 쓰기(기존 데이터 유지)			"r+b" -> "w+b"
	Dz1StreamFileMode_RWA,			// 읽고 쓰기(기존 데이터 유지, 맨끝)	"a+b"
} Dz1StreamFileMode;

typedef struct Dz1FileBufStream
{
	FILE				*fp;
	bool_t				 fp_isRef;
	FILEPOSt			 drain_offset;

	u32_t				 alloc_id;
	Dz1AATree			*user_cursors;
} Dz1FileBufStream;

DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStream_new(FILE *fp, Dz1StreamFileMode mode, bool_t fp_isRef, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1FileBufStream_del(Dz1FileBufStream *p);
static __inline__ void						 Dz1FileBufStream_delAndSetNull(void *pptr)
{
	Dz1FileBufStream **p = (Dz1FileBufStream **)pptr;
	Dz1FileBufStream_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1FileBufStreamA_dump(Dz1FileBufStream *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1FileBufStreamA_fdump(FILE *fp, Dz1FileBufStream *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamA_open(str_t fn, Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamA_open2(str_t path, str_t name, Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamA_open3(str_t path, str_t name, str_t ext, Dz1StreamFileMode mode, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1FileBufStreamW_dump(Dz1FileBufStream *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1FileBufStreamW_fdump(FILE *fp, Dz1FileBufStream *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamW_open(wstr_t fn, Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamW_open2(wstr_t path, wstr_t name, Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FileBufStream	*Dz1FileBufStreamW_open3(wstr_t path, wstr_t name, wstr_t ext, Dz1StreamFileMode mode, Dz1Error *err);
#ifdef UNICODE
#define										 Dz1FileBufStream_dump		Dz1FileBufStreamW_dump
#define										 Dz1FileBufStream_fdump		Dz1FileBufStreamW_fdump
#define										 Dz1FileBufStream_open		Dz1FileBufStreamW_open
#define										 Dz1FileBufStream_open2		Dz1FileBufStreamW_open2
#define										 Dz1FileBufStream_open3		Dz1FileBufStreamW_open3
#else
#define										 Dz1FileBufStream_dump		Dz1FileBufStreamA_dump
#define										 Dz1FileBufStream_fdump		Dz1FileBufStreamA_fdump
#define										 Dz1FileBufStream_open		Dz1FileBufStreamA_open
#define										 Dz1FileBufStream_open2		Dz1FileBufStreamA_open2
#define										 Dz1FileBufStream_open3		Dz1FileBufStreamA_open3
#endif//UNICODE
#else// UNIX_SYSTEM
#define										 Dz1FileBufStream_dump		Dz1FileBufStreamA_dump
#define										 Dz1FileBufStream_fdump		Dz1FileBufStreamA_fdump
#define										 Dz1FileBufStream_open		Dz1FileBufStreamA_open
#define										 Dz1FileBufStream_open2		Dz1FileBufStreamA_open2
#define										 Dz1FileBufStream_open3		Dz1FileBufStreamA_open3
#endif
// File Buffer Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Static Buffer Stream
typedef struct Dz1StaticBufStream
{
	u8_t				*buf;
	size_t				 buf_size;
	bool_t				 buf_is_ref;

	u32_t				 buf_filled;

	u32_t				 alloc_id;
	Dz1AATree			*user_cursors;
} Dz1StaticBufStream;
DZ1_CPPLINK DZ1_DLLPORT Dz1StaticBufStream	*Dz1StaticBufStream_new(u8_t *buf, size_t size, bool_t buf_is_ref, u32_t buf_filled, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1StaticBufStream_del(Dz1StaticBufStream *p);
static __inline__ void						 Dz1StaticBufStream_delAndSetNull(void *pptr)
{
	Dz1StaticBufStream **p = (Dz1StaticBufStream **)pptr;
	Dz1StaticBufStream_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1StaticBufStreamA_dump(Dz1StaticBufStream *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1StaticBufStreamW_dump(Dz1StaticBufStream *p, int tab);
#ifdef UNICODE
#define										 Dz1StaticBufStream_dump		Dz1StaticBufStreamW_dump
#else // UNICODE
#define										 Dz1StaticBufStream_dump		Dz1StaticBufStreamA_dump
#endif // // UNICODE
#else // UNIX_SYSTEM
#define										 Dz1StaticBufStream_dump		Dz1StaticBufStreamA_dump
#endif // UNIX_SYSTEM
// Static Buffer Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream
typedef struct Dz1ElasticBufStream
{
	Dz1ElasticBuf			*elastic;				// Source Data
	bool_t					 elastic_is_ref;		// Source attribute

	u32_t					 alloc_id;
	Dz1AATree				*user_cursors;			// Read/Write Position
} Dz1ElasticBufStream;

DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBufStream *Dz1ElasticBufStream_new(Dz1ElasticBuf *elastic, bool_t elastic_is_ref, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1ElasticBufStream_del(Dz1ElasticBufStream *p);
static __inline__ void						 Dz1ElasticBufStream_delAndSetNull(void *ptr)
{
	Dz1ElasticBufStream **p = (Dz1ElasticBufStream **)ptr;
	Dz1ElasticBufStream_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void				 Dz1ElasticBufStream_dump(Dz1ElasticBufStream *p, int tab);
// Elastic Buffer Stream
///////////////////////////////////////////////////////////////////////////////


typedef u32_t				 (*Dz1StreamAllocF)	 (void *storage, Dz1Error *err);
typedef void				 (*Dz1StreamReleaseF)(void *storage, u64_t stream_id);
typedef ssize_t				 (*Dz1StreamReadF)	 (void *storage, u64_t stream_id, u8_t *dst_buf, size_t buf_size, Dz1Error *err);
typedef ssize_t				 (*Dz1StreamWriteF)	 (void *storage, u64_t stream_id, u8_t *out_data, size_t size, Dz1Error *err);
typedef Dz1Error			 (*Dz1StreamSeekF)	 (void *storage, u64_t stream_id, s64_t diff, int mode);
typedef s64_t				 (*Dz1StreamTellF)	 (void *storage, u64_t stream_id, Dz1Error *err);
typedef bool_t				 (*Dz1StreamIsEofF)	 (void *storage, u64_t stream_id);
typedef ssize_t				 (*Dz1StreamDrainF)	 (void *storage, size_t drain_byte, u8_t *opt_drain_buf, Dz1Error *err);


///////////////////////////////////////////////////////////////////////////////
// IN-OUT Stream
typedef struct Dz1Stream
{
	void				*storage;
	bool_t				 storage_isRef;
	Dz1DelFunc			 storage_del;
	Dz1DumpFunc			 storage_dump;

	// Cursor
	u64_t				 stream_id;
	Dz1StreamReleaseF	 stream_release;		// mandatory

	Dz1StreamReadF		 read;					// optional	- read나 write중 하나는 설정되어 있어야 함
	Dz1StreamWriteF		 write;					// optional	- read나 write중 하나는 설정되어 있어야 함

	Dz1StreamSeekF		 seek;					// optional - socket stream같은 seek불가능한 stream 때문에...
	Dz1StreamTellF		 tell;					// optional - socket stream같은 seek불가능한 stream 때문에...

	Dz1StreamIsEofF		 is_eof;				// mandatory
	Dz1StreamDrainF		 drain;					// optional
} Dz1Stream;
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Stream_close(Dz1Stream *p);
#define								 Dz1Stream_del				 Dz1Stream_close
static __inline__ void				 Dz1Stream_closeAndSetNull(void *pptr)
{
	Dz1Stream **p = (Dz1Stream **)pptr;
	Dz1Stream_close(*p); *p = NULL;
}
#define								 Dz1Stream_delAndSetNull		 Dz1Stream_closeAndSetNull

DZ1_CPPLINK DZ1_DLLPORT void		 Dz1StreamA_dump(Dz1Stream *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1StreamW_dump(Dz1Stream *p, int tab);
#ifdef UNICODE
#define								 Dz1Stream_dump			Dz1StreamW_dump
#else // UNICODE
#define								 Dz1Stream_dump			Dz1StreamA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Stream_dump			Dz1StreamA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int			 Dz1Stream_cmp(Dz1Stream *a, Dz1Stream *b);

/////////////////////////////////////////////////////////////////////
// File Buffer Stream
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_refFileBufStream(Dz1FileBufStream *file_stream, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Stream_attachFileBufStream(Dz1Stream *dst, Dz1FileBufStream **file_stream);
// File Buffer Stream
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// File Stream Open
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamA_openFile( str_t fn,								Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamA_openFile2(str_t path,  str_t name,				Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamA_openFile3(str_t path,  str_t name,	str_t ext,	Dz1StreamFileMode mode, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamW_openFile( wstr_t fn,						    Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamW_openFile2(wstr_t path, wstr_t name,				Dz1StreamFileMode mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1StreamW_openFile3(wstr_t path, wstr_t name, wstr_t ext,	Dz1StreamFileMode mode, Dz1Error *err);
#ifdef	UNICODE
#define Dz1Stream_openFile			 Dz1StreamW_openFile
#define Dz1Stream_openFile2			 Dz1StreamW_openFile2
#define Dz1Stream_openFile3			 Dz1StreamW_openFile3
#else// UNICODE
#define Dz1Stream_openFile			 Dz1StreamA_openFile
#define Dz1Stream_openFile2			 Dz1StreamA_openFile2
#define Dz1Stream_openFile3			 Dz1StreamA_openFile3
#endif//UNICODE
#else// UNIX_SYSTEM
#define Dz1Stream_openFile			 Dz1StreamA_openFile
#define Dz1Stream_openFile2			 Dz1StreamA_openFile2
#define Dz1Stream_openFile3			 Dz1StreamA_openFile3
#endif//UNIX_SYSTEM
// File Stream Open
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Static Buffer Stream
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_refStaticBuf(Dz1StaticBufStream *storage, Dz1Error *err);		// reference buf ptr
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Stream_attachStaticBuf(Dz1Stream *dst, Dz1StaticBufStream **storage);	// take buf ptr
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_createStaticBuf(size_t size, Dz1Error *err);						// create buf

DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_openStaticBuf(u8_t *buf, size_t size, bool_t buf_isRef, size_t data_filled, Dz1Error *err);
// Static Buffer Stream
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Elastic Buffer Stream
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_refElasticBufStream(Dz1ElasticBufStream *buf, Dz1Error *err);		// reference elastic buf stream
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Stream_attachElasticBufStream(Dz1Stream *dst, Dz1ElasticBufStream **buf);	// take elastic buf stream ptr
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_createElasticBufStream(size_t unit_size, Dz1Error *err);				// create elastic buffer Stream

DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_openAttachedElasticBuf(Dz1ElasticBuf **buf, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Stream	*Dz1Stream_openRefElasticBuf(Dz1ElasticBuf *buf, Dz1Error *err);
// Elastic Buffer Stream
/////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT void		 Dz1Stream_release(Dz1Stream *src);
static __inline__ void				 Dz1Stream_attachCancel(void *ptr)
{
	Dz1Stream *p = (Dz1Stream *)ptr;
	Dz1Stream_release(p);
}

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_read			(Dz1Stream *src, u8_t *buf, size_t size, Dz1Error *err);// copy data from src to buf and move position

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_read1		(Dz1Stream *src, u8_t  *v, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_read2		(Dz1Stream *src, u16_t *v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_read4		(Dz1Stream *src, u32_t *v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_read8		(Dz1Stream *src, u64_t *v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_readPad		(Dz1Stream *src, u32_t padding, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_readConst	(Dz1Stream *src, u32_t size, u8_t *const_data, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_peek			(Dz1Stream *src, u8_t *buf, size_t inspect_size, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_peek1		(Dz1Stream *src, u8_t  *v, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_peek2		(Dz1Stream *src, u16_t *v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_peek4		(Dz1Stream *src, u32_t *v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_peek8		(Dz1Stream *src, u64_t *v, Dz1IOStreamEndian ed, Dz1Error *err);


DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_write		(Dz1Stream *dst, u8_t *buf, size_t size, Dz1Error *err);	// copy data from buf to dst and move position

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_write1		(Dz1Stream *dst, u8_t  v, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_write2		(Dz1Stream *dst, u16_t v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_write4		(Dz1Stream *dst, u32_t v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_write8		(Dz1Stream *dst, u64_t v, Dz1IOStreamEndian ed, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_writePad		(Dz1Stream *dst, u32_t padding, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Stream_seek			(Dz1Stream *src, s64_t diff, int mode);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1Stream_skip			(Dz1Stream *src, size_t skip_len);
DZ1_CPPLINK DZ1_DLLPORT s64_t		 Dz1Stream_tell			(Dz1Stream *src);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1Stream_eof			(Dz1Stream *src);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Stream_drain		(Dz1Stream *dst, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err);
// IN-OUT Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Stream MACRO
#define _DZ1_STREAM_READ(dstp, size, streamp, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read( (streamp), (u8_t *)(dstp), (size), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_READ(dstp, size, streamp, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read( (streamp), (u8_t *)(dstp), (size), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else if (__status__ != (ssize_t)size) ERR_SETOUT_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_READ1(dstp, streamp, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read1( (streamp), (u8_t *)(dstp), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_READ2(dstp, streamp, ed, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read2( (streamp), (u16_t *)(dstp), (ed), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_READ4(dstp, streamp, ed, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read4( (streamp), (u32_t *)(dstp), (ed), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_READ8(dstp, streamp, ed, errp, ret) \
	do {\
		ssize_t __status__ = Dz1Stream_read8( (streamp), (u64_t *)(dstp), (ed), (errp) );\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ == 0) ERR_SET_RET(errp, EPIPE, -1);\
		else (ret) += __status__;\
	} while(0)

#define _DZ1_STREAM_WRITE(dstp, srcp, srcp_size, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write((u8_t *)(dstp), (srcp), (srcp_size), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_WRITE(dstp, srcp, srcp_size, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write((dstp), (srcp), (srcp_size), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else if (__status__ != (ssize_t)srcp_size) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_WRITE1(dstp, srcv, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write1((dstp), (srcv), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_WRITE2(dstp, srcv, ed, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write2((dstp), (srcv), (ed), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_WRITE4(dstp, srcv, ed, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write4((dstp), (srcv), (ed), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_STREAM_WRITE8(dstp, srcv, ed, errp, ret) \
	do \
	{\
		ssize_t __status__ = Dz1Stream_write8((dstp), (srcv), (ed), (errp));\
		if (__status__ < 0) ERR_OUT_RET(errp, -1);\
		else (ret) += __status__;\
	} while(0)

#define DZ1_IO_STREAM_FUNC(ret, enc, errp)	\
	do {\
		ssize_t __written__ = enc;\
		if (__written__ < 0) return -1; /*if (__written__ < 0) ERR_OUT_RET(errp, -1);*/ \
		else (ret) += __written__;\
	} while(0)
#define DZ1_IO_STREAM_FUNC_(ret, enc, errp)	\
	do {\
		ssize_t __written__ = enc;\
		if (__written__ < 0) { ERR_OUT(errp); ret = -1; }\
		else (ret) += __written__;\
	} while(0)
// Stream MACRO
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TDC Assist
DZ1_CPPLINK DZ1_DLLPORT ssize_t u8_read(void *u8_t_dst, Dz1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t u8_write(Dz1Stream *dst, void *u8_t_src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8Bcd_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8Bcd_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8Ascii_read(void *u8_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u8Ascii_write(Dz1Stream *dst, void *u8_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t u16_b_read(void *u16_t_dst, Dz1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t u16_b_write(Dz1Stream *dst, void *u16_t_src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t u16_l_read(void *u16_t_dst, Dz1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t u16_l_write(Dz1Stream *dst, void *u16_t_src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u16_read(void *u16_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u16_write(Dz1Stream *dst, void *u16_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t u32_b_read(void *u32_t_dst, Dz1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t u32_b_write(Dz1Stream *dst, void *u32_t_src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t u32_l_read(void *u32_t_dst, Dz1Stream *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t u32_l_write(Dz1Stream *dst, void *u32_t_src, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u32_write(Dz1Stream *dst, void *u32_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u32_read(void *u32_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u64_write(Dz1Stream *dst, void *u64_t_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1u64_read(void *u64_t_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

typedef struct Dz1ListStreamArg
{
	Dz1Stream			*stream;
	ssize_t				 ret;
	Dz1IOStreamEndian	 ed;
	void				*option;
} Dz1ListStreamArg;
// TDC Assist
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Text Line Helper
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamA_TextLoadLine(Dz1Stream *st, u8_t *buf64K, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamW_TextLoadLine(Dz1Stream *st, u8_t *buf64K, Dz1Error *errp);
#ifdef UNICODE
#define Dz1Stream_TextLoadLine		Dz1StreamW_TextLoadLine
#else
#define Dz1Stream_TextLoadLine		Dz1StreamA_TextLoadLine
#endif
// Text Line Helper
///////////////////////////////////////////////////////////////////////////////

typedef ssize_t  (*Dz1StreamWriteFunc)(Dz1Stream *dst, void *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
typedef ssize_t  (*Dz1StreamReadFunc)(void *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1StreamA_loadHelper(void *dst, str_t path, str_t name, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1StreamA_genLoadHelper(str_t path, str_t name, Dz1GenFunc gen, Dz1CancelFunc del_and_setnull, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1StreamA_saveHelper(str_t path, str_t name, void *src, Dz1StreamWriteFunc st_write, Dz1IOStreamEndian ed, void *wr_param, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1StreamW_loadHelper(void *dst, wstr_t path, wstr_t name, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1StreamW_genLoadHelper(wstr_t path, wstr_t name, Dz1GenFunc gen, Dz1CancelFunc del_and_setnull, Dz1StreamReadFunc st_read, Dz1IOStreamEndian ed, void *read_param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1StreamW_saveHelper(wstr_t path, wstr_t name, void *src, Dz1StreamWriteFunc st_write, Dz1IOStreamEndian ed, void *wr_param, Dz1Error *err);
#ifdef UNICODE
#define Dz1Stream_loadHelper			Dz1StreamW_loadHelper
#define Dz1Stream_genLoadHelper			Dz1StreamW_genLoadHelper
#define Dz1Stream_saveHelper			Dz1StreamW_saveHelper
#else // UNICODE
#define Dz1Stream_loadHelper			Dz1StreamA_loadHelper
#define Dz1Stream_genLoadHelper			Dz1StreamA_genLoadHelper
#define Dz1Stream_saveHelper			Dz1StreamA_saveHelper
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1Stream_loadHelper			Dz1StreamA_loadHelper
#define Dz1Stream_genLoadHelper			Dz1StreamA_genLoadHelper
#define Dz1Stream_saveHelper			Dz1StreamA_saveHelper
#endif // UNIX_SYSTEM

#define DZ1_STREAM_GEN_AND_LOAD(st_name, path, fn, ed, param, errp) (st_name *)	Dz1Stream_genLoadHelper(path, fn, st_name##_gen, st_name##_delAndSetNull, st_name##_read, ed, param, errp)
#define DZ1_STREAM_SIMPLE_SAVE(st_name, path, fn, src, ed, param, errp)			Dz1Stream_saveHelper(path, fn, src, st_name##_write, ed, param, errp)

///////////////////////////////////////////////////////////////////////////////
// UNION IO Helper
typedef struct Dz1StreamIoMap
{
	int present;
	u32_t opcode;
	Dz1GenFunc gen;
	ssize_t (*write)(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
	ssize_t (*read)(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
} Dz1StreamIoMap;
#define Dz1StreamIoMap_STRUCT(stname, opcode, mbType, mbName)	{ stname##Present_##mbName, opcode, (Dz1GenFunc)mbType##_gen, mbType##_write, mbType##_read }
#define Dz1StreamIoMap_VAR(stname, opcode, apiPrefix, mbName)	{ stname##Present_##mbName, opcode, NULL, apiPrefix##_write, apiPrefix##_read }
#define Dz1StreamIoMap_PVAR(stname, opcode, apiPrefix, mbName)	{ stname##Present_##mbName, opcode, (Dz1GenFunc)-1, apiPrefix##_write, apiPrefix##_read }
#define Dz1StreamIoMap_VOID(stname, opcode, mbName)				{ stname##Present_##mbName, opcode, NULL, NULL, NULL }
#define Dz1StreamIoMapEntry_last								{ -1 }

DZ1_CPPLINK DZ1_DLLPORT Dz1StreamIoMap *Dz1StreamIoMap_findByPresent(Dz1StreamIoMap *table, int present);
DZ1_CPPLINK DZ1_DLLPORT Dz1StreamIoMap *Dz1StreamIoMap_findByOpCode(Dz1StreamIoMap *table, u32_t opcode);

// src->present까지 포함하여 Read/Write
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param,
													 Dz1StreamIoMap *table, size_t opLen, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param,
													Dz1StreamIoMap *table, size_t opLen, Dz1Error *err);

// 64bit member가 있는 TdcUnion Structure
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion64_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param,
													   Dz1StreamIoMap *table, size_t opLen, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion64_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param,
													  Dz1StreamIoMap *table, size_t opLen, Dz1Error *err);

// Body 만 Read/Write
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion_writeB(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion_readB (void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err);
// 64bit member 가 있는 TdcUnion Structure
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion64_writeB(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StreamUnion64_readB (void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1StreamIoMap *table, Dz1Error *err);
// UNION IO Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// String IO Helper
////////////////////////////////////////
// MBCS String
// 1 byte null flag + 1 byte length + n byte Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// 1 byte null flag + 2 byte length + n byte Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA16_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA16_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// 1 byte null flag + 4 byte length + n byte Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA32_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA32_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// default StrA write
#define							 Dz1StrA_read			Dz1StrA32_read			// flag32 size32 data
#define							 Dz1StrA_write			Dz1StrA32_write			// flag32 size32 data

// no null flag, 4 byte length + n byte Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrAN32_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrAN32_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// default StrAN write
#define							 Dz1StrAN_read			Dz1StrAN32_read
#define							 Dz1StrAN_write			Dz1StrAN32_write

// fixed length Text(No length encoding)
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrAX_read(str_t *dst, Dz1Stream *src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrAX_write(Dz1Stream *dst, str_t src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
// MBCS String
////////////////////////////////////////

////////////////////////////////////////
// MBCS->UTF8 String
// no null flag, 2 Byte Length + Byte Stream 
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA16UTF8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA16UTF8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// no null flag, 4 Byte Length + Byte Stream 
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA32UTF8_read(str_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA32UTF8_write(Dz1Stream *dst, str_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
#define							 Dz1StrAUTF8_read		Dz1StrA32UTF8_read
#define							 Dz1StrAUTF8_write		Dz1StrA32UTF8_write
// MBCS->UTF8 String
////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////
// WIDE String
// 1 byte null flag + 1 byte length + n letter Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// 1 byte null flag + 2 byte length + n letter Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW16_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW16_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// 1 byte null flag + 4 byte length + n letter Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW32_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW32_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// default StrW write
#define							 Dz1StrW_read			Dz1StrW32_read
#define							 Dz1StrW_write			Dz1StrW32_write

// 4 byte length + n letter Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrWN32_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrWN32_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// default StrN write
#define							 Dz1StrWN_read			Dz1StrWN32_read
#define							 Dz1StrWN_write			Dz1StrWN32_write

// X letter fixed length Text
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrWX_read(wstr_t *dst, Dz1Stream *src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrWX_write(Dz1Stream *dst, wstr_t src, size_t fixed_len, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
// WIDE String
////////////////////////////////////////

////////////////////////////////////////
// WIDE->UTF8 String
// 2 Byte Length + Byte Stream 
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StrW16UTF8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StrW16UTF8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

// 4 Byte Length + Byte Stream 
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StrW32UTF8_read(wstr_t *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1StrW32UTF8_write(Dz1Stream *dst, wstr_t src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#define Dz1StrWUTF8_read	Dz1StrW32UTF8_read
#define Dz1StrWUTF8_write	Dz1StrW32UTF8_write
// WIDE->UTF8 String
////////////////////////////////////////

#ifdef UNICODE
#define Dz1Str8_write			Dz1StrW8_write
#define Dz1Str8_read			Dz1StrW8_read
#define Dz1Str16_write			Dz1StrW16_write
#define Dz1Str16_read			Dz1StrW16_read
#define Dz1Str32_write			Dz1StrW32_write
#define Dz1Str32_read			Dz1StrW32_read
#define Dz1Str_write			Dz1StrW32_write
#define Dz1Str_read				Dz1StrW32_read
#define Dz1StrN_write			Dz1StrWN32_write
#define Dz1StrN_read			Dz1StrWN32_read
#define Dz1StrX_write			Dz1StrWX_write
#define Dz1StrX_read			Dz1StrWX_read
#define Dz1Str16UTF8_read		Dz1StrW16UTF8_read
#define Dz1Str16UTF8_write		Dz1StrW16UTF8_write
#define Dz1Str32UTF8_read		Dz1StrW32UTF8_read
#define Dz1Str32UTF8_write		Dz1StrW32UTF8_write
#define Dz1StrUTF8_read			Dz1StrW32UTF8_read
#define Dz1StrUTF8_write		Dz1StrW32UTF8_write
#else
#define Dz1Str8_write			Dz1StrA8_write
#define Dz1Str8_read			Dz1StrA8_read
#define Dz1Str16_write			Dz1StrA16_write
#define Dz1Str16_read			Dz1StrA16_read
#define Dz1Str32_write			Dz1StrA32_write
#define Dz1Str32_read			Dz1StrA32_read
#define Dz1Str_write			Dz1StrA32_write
#define Dz1Str_read				Dz1StrA32_read
#define Dz1StrN_write			Dz1StrAN32_write
#define Dz1StrN_read			Dz1StrAN32_read
#define Dz1StrX_write			Dz1StrAX_write
#define Dz1StrX_read			Dz1StrAX_read
#define Dz1Str16UTF8_read		Dz1StrA16UTF8_read
#define Dz1Str16UTF8_write		Dz1StrA16UTF8_write
#define Dz1Str32UTF8_read		Dz1StrA32UTF8_read
#define Dz1Str32UTF8_write		Dz1StrA32UTF8_write
#define Dz1StrUTF8_read			Dz1StrA32UTF8_read
#define Dz1StrUTF8_write		Dz1StrA32UTF8_write
#endif
#else	// UNIX_SYSTEM
#define Dz1Str8_write			Dz1StrA8_write
#define Dz1Str8_read			Dz1StrA8_read
#define Dz1Str16_write			Dz1StrA16_write
#define Dz1Str16_read			Dz1StrA16_read
#define Dz1Str32_write			Dz1StrA32_write
#define Dz1Str32_read			Dz1StrA32_read
#define Dz1Str_write			Dz1StrA32_write
#define Dz1Str_read				Dz1StrA32_read
#define Dz1StrN_write			Dz1StrAN32_write
#define Dz1StrN_read			Dz1StrAN32_read
#define Dz1StrX_write			Dz1StrAX_write
#define Dz1StrX_read			Dz1StrAX_read
#define Dz1Str16UTF8_read		Dz1StrA16UTF8_read
#define Dz1Str16UTF8_write		Dz1StrA16UTF8_write
#define Dz1Str32UTF8_read		Dz1StrA32UTF8_read
#define Dz1Str32UTF8_write		Dz1StrA32UTF8_write
#define Dz1StrUTF8_read			Dz1StrA32UTF8_read
#define Dz1StrUTF8_write		Dz1StrA32UTF8_write
#endif	// UNIX_SYSTEM
// String IO Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Time IO Helper
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Time_writeB(Dz1Stream *dst, time_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Time_writeL(Dz1Stream *dst, time_t *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Time_readB(time_t *dst, Dz1Stream *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Time_readL(time_t *dst, Dz1Stream *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1TM_writeB(Dz1Stream *dst, struct tm *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1TM_writeL(Dz1Stream *dst, struct tm *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1TM_readB(struct tm *dst, Dz1Stream *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1TM_readL(struct tm *dst, Dz1Stream *src, Dz1Error *err);
// Time IO Helper
///////////////////////////////////////////////////////////////////////////////

typedef struct Dz1StreamCallStk
{
	struct Dz1StreamCallStk		*parent;
	void						*dst;
	void						*user_ptr;
} Dz1StreamCallStk;
#define Dz1StreamCallStk_init(user_ptr)		{ NULL, NULL, user_ptr }

#endif
