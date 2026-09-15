#ifndef DZ1_ELASTIC_BUFFER_H
#define DZ1_ELASTIC_BUFFER_H

#include <dz1_bin.h>

typedef struct Dz1ElasticBufEntry
{
	struct Dz1ElasticBufEntry *prev;
	struct Dz1ElasticBufEntry *next;
	Dz1Binary *buf;
	u32_t data_start;
	u32_t data_end;
} Dz1ElasticBufEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBufEntry		*Dz1ElasticBufEntry_new(u32_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1ElasticBufEntry_del(Dz1ElasticBufEntry *p);
static __inline__ void							 Dz1ElasticBufEntry_delAndSetNull(void *ptr)
{
	Dz1ElasticBufEntry **p = (Dz1ElasticBufEntry **)ptr;
	Dz1ElasticBufEntry_del(*p); *p = NULL;
}

typedef struct Dz1ElasticBuf
{
	Dz1ElasticBufEntry *head;
	Dz1ElasticBufEntry *tail;
	u32_t elUnit;
} Dz1ElasticBuf;

DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBuf		   *_Dz1ElasticBuf_new(u32_t elUnit, bool_t create_head, Dz1Error *err, char *__file__, int __line__);
#define											 Dz1ElasticBuf_new(elu, head_flag, ep)		_Dz1ElasticBuf_new(elu, head_flag, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBuf			*Dz1ElasticBuf_clone(Dz1ElasticBuf *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1ElasticBuf_del(Dz1ElasticBuf *p);
static __inline__ void							 Dz1ElasticBuf_delAndSetNull(void *ptr)
{
	Dz1ElasticBuf **p = (Dz1ElasticBuf **)ptr;
	Dz1ElasticBuf_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1ElasticBufA_dump(Dz1ElasticBuf *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1ElasticBufW_dump(Dz1ElasticBuf *p, int tab);
#ifdef UNICODE
#define											 Dz1ElasticBuf_dump		Dz1ElasticBufW_dump
#else // UNICODE
#define											 Dz1ElasticBuf_dump		Dz1ElasticBufA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define											 Dz1ElasticBuf_dump		Dz1ElasticBufA_dump
#endif // UNIX_SYSTEM


DZ1_CPPLINK DZ1_DLLPORT bool_t					_Dz1ElasticBuf_push(Dz1ElasticBuf *dst, u8_t *buf, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error				 Dz1ElasticBuf_push(Dz1ElasticBuf *dst, u8_t *src, size_t src_size);				// src 의 내용을 Buffer 끝에 추가한다.
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1ElasticBuf_pop(Dz1ElasticBuf *src, u8_t *dst, size_t dst_size, Dz1Error *err);	// Buffer 의 처음부터 꺼내 dst 에 복사한다.

DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_move(Dz1ElasticBuf *dst, Dz1ElasticBuf *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					_Dz1ElasticBuf_empty(Dz1ElasticBuf *p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error				 Dz1ElasticBuf_empty(Dz1ElasticBuf *p);									// 내용을 모두 지우고 조각을 하나도 남기지 않는다
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_isEmpty(Dz1ElasticBuf *p);

DZ1_CPPLINK DZ1_DLLPORT Dz1Binary const * const	_Dz1ElasticBuf_flatten(Dz1ElasticBuf *p, Dz1Error *err, const char *__file__, int __line__);	// 조각나 있는 내용을 하나로 뭉친다
#define											 Dz1ElasticBuf_flatten(bp, ep)	_Dz1ElasticBuf_flatten(bp, ep, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary *				_Dz1ElasticBuf_flattenAndPurge(Dz1ElasticBuf *p, Dz1Error *err, const char *__file__, int __line__);	// 조각나 있는 내용을 하나로 뭉친Binary를 돌려주고 내용을 비운다
#define											 Dz1ElasticBuf_flattenAndPurge(bp, ep)	_Dz1ElasticBuf_flattenAndPurge(bp, ep, __FILE__, __LINE__)

DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1ElasticBuf_getTailByte(Dz1ElasticBuf *p, u8_t *buf, size_t sz, Dz1Error *err);	// < 0 : error, # of peek byte
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1ElasticBuf_reduce(Dz1ElasticBuf *p, size_t sz, Dz1Error *err);					// < 0 : error, # of reduce byte

DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushStrNA(Dz1ElasticBuf *dst, str_t str, size_t len, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushStrA(Dz1ElasticBuf *dst, str_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushChrA(Dz1ElasticBuf *dst, char c, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_peekLastChrA(Dz1ElasticBuf *p, char *c, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT str_t					 Dz1ElasticBuf_flattenStrA(Dz1ElasticBuf *dst, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t					 Dz1ElasticBuf_flattenStrAndPurgeA(Dz1ElasticBuf *dst, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushStrNW(Dz1ElasticBuf *dst, wstr_t str, size_t len, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushStrW(Dz1ElasticBuf *dst, wstr_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_pushChrW(Dz1ElasticBuf *dst, wchar_t c, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t					 Dz1ElasticBuf_peekLastChrW(Dz1ElasticBuf *p, wchar_t *c, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT wstr_t					 Dz1ElasticBuf_flattenStrW(Dz1ElasticBuf *dst, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t					 Dz1ElasticBuf_flattenStrAndPurgeW(Dz1ElasticBuf *dst, Dz1Error *err);
#ifdef UNICODE
#define											 Dz1ElasticBuf_pushStrN				Dz1ElasticBuf_pushStrNW
#define											 Dz1ElasticBuf_pushStr				Dz1ElasticBuf_pushStrW
#define											 Dz1ElasticBuf_pushChr				Dz1ElasticBuf_pushChrW
#define											 Dz1ElasticBuf_peekLastChr			Dz1ElasticBuf_peekLastChrW

#define											 Dz1ElasticBuf_flattenStr			Dz1ElasticBuf_flattenStrW
#define											 Dz1ElasticBuf_flattenStrAndPurge	Dz1ElasticBuf_flattenStrAndPurgeW
#else // UNICODE
#define											 Dz1ElasticBuf_pushStrN				Dz1ElasticBuf_pushStrNA
#define											 Dz1ElasticBuf_pushStr				Dz1ElasticBuf_pushStrA
#define											 Dz1ElasticBuf_pushChr				Dz1ElasticBuf_pushChrA
#define											 Dz1ElasticBuf_peekLastChr			Dz1ElasticBuf_peekLastChrA

#define											 Dz1ElasticBuf_flattenStr			Dz1ElasticBuf_flattenStrA
#define											 Dz1ElasticBuf_flattenStrAndPurge	Dz1ElasticBuf_flattenStrAndPurgeA
#endif // UNICODE
#else // UNIX_SYSTEM
#define											 Dz1ElasticBuf_pushStrN				Dz1ElasticBuf_pushStrNA
#define											 Dz1ElasticBuf_pushStr				Dz1ElasticBuf_pushStrA
#define											 Dz1ElasticBuf_pushChr				Dz1ElasticBuf_pushChrA
#define											 Dz1ElasticBuf_peekLastChr			Dz1ElasticBuf_peekLastChrA

#define											 Dz1ElasticBuf_flattenStr			Dz1ElasticBuf_flattenStrA
#define											 Dz1ElasticBuf_flattenStrAndPurge	Dz1ElasticBuf_flattenStrAndPurgeA
#endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1ElasticBuf_write(Dz1ElasticBuf *p, FILE *fp, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error				 Dz1ElasticBuf_load(Dz1ElasticBuf *p, FILE *dst);						// FILE의 내용을 buf에 load한다.
DZ1_CPPLINK DZ1_DLLPORT Dz1Error				 Dz1ElasticBuf_save(Dz1ElasticBuf *p, FILE *dst);						// buf의 내용을 FILE에 save한다.

typedef enum Dz1ElasticBufAppendSide
{
	Dz1ElasticBufAppendSide_toFront,
	Dz1ElasticBufAppendSide_toTail
} Dz1ElasticBufAppendSide;

DZ1_CPPLINK DZ1_DLLPORT Dz1ElasticBufEntry		*Dz1ElasticBuf_alloc(Dz1ElasticBuf *p, Dz1ElasticBufAppendSide side, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1ElasticBuf_getDataSize(Dz1ElasticBuf *p, Dz1Error *errp);

///////////////////////////////////////////////////////////////////////////////
// Liquid String
typedef struct Dz1LiquidString
{
	Dz1ElasticBuf				*buf;
} Dz1LiquidString;
DZ1_CPPLINK DZ1_DLLPORT Dz1LiquidString			*Dz1LiquidSgtring_new(str_t charset, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1LiquidString			*Dz1LiquidString_clone(Dz1LiquidString *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1LiquidString_del(Dz1LiquidString *p);
static __inline__ void							 Dz1LiquidString_delAndSetNull(void *pptr)
{
	Dz1LiquidString **p = (Dz1LiquidString **)pptr;
	Dz1LiquidString_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_A_Format(Dz1LiquidString *dst, str_t fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_A_Assign(Dz1LiquidString *dst, str_t str);
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_A_Append(Dz1LiquidString *dst, str_t str);
DZ1_CPPLINK DZ1_DLLPORT char const * const		 Dz1LiquidString_A_Printable(Dz1LiquidString *dst);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_W_Format(Dz1LiquidString *dst, wstr_t fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_W_Assign(Dz1LiquidString *dst, wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT ssize_t					 Dz1LiquidString_W_Append(Dz1LiquidString *dst, str_t str);
DZ1_CPPLINK DZ1_DLLPORT wchar_t const * const	 Dz1LiquidString_W_Printable(Dz1LiquidString *dst);
#ifdef UNICODE
#define Dz1LiquidString_Format					 Dz1LiquidString_W_Format
#define Dz1LiquidString_Assign					 Dz1LiquidString_W_Assign
#define Dz1LiquidString_Append					 Dz1LiquidString_W_Append
#define Dz1LiquidString_Printable				 Dz1LiquidString_W_Printable
#else // UNICODE
#define Dz1LiquidString_Format					 Dz1LiquidString_A_Format
#define Dz1LiquidString_Assign					 Dz1LiquidString_A_Assign
#define Dz1LiquidString_Append					 Dz1LiquidString_A_Append
#define Dz1LiquidString_Printable				 Dz1LiquidString_A_Printable
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1LiquidString_Format					 Dz1LiquidString_A_Format
#define Dz1LiquidString_Assign					 Dz1LiquidString_A_Assign
#define Dz1LiquidString_Append					 Dz1LiquidString_A_Append
#define Dz1LiquidString_Printable				 Dz1LiquidString_A_Printable
#endif // UNIX_SYSTEM
// Liquid String
///////////////////////////////////////////////////////////////////////////////


#endif
