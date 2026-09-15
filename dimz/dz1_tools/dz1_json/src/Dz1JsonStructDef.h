#ifndef _DZ1_TDC_DZ1_JSON_STRUCT_DEF_H_
#define _DZ1_TDC_DZ1_JSON_STRUCT_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1JsonDef.h"
#include "Dz1JsonConv.h"

////////////////////////////////////////////////////////////////////////////////
// NewLineMap
typedef struct NewLineMap
{
	Dz1JsonNewLine		mode;
	Dz1Str				str;
	size_t				len;
} NewLineMap;

DZ1_CPPLINK DZ1_DLLPORT NewLineMap *NewLineMap_new(Dz1JsonNewLine mode, 
												   Dz1Str str, 
												   size_t len, Dz1Error *err);
static __inline__ NewLineMap *NewLineMap_gen(Dz1Error *err) { return NewLineMap_new(Dz1JsonNewLine_max, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void NewLineMap_purge(NewLineMap *p);
DZ1_CPPLINK DZ1_DLLPORT void NewLineMap_del(NewLineMap *p);
static __inline__ void NewLineMap_delAndSetNull(void *ptr)
{
	NewLineMap **p = (NewLineMap **)ptr;
	if (p) { NewLineMap_del(*p); *p = NULL; }
}
// NewLineMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecRefList
typedef struct Dz1JsonSpecRefList
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonSpecRefList *p);
	Dz1Error (*travel)(struct Dz1JsonSpecRefList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonSpecRefList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonSpecRefList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecEntry *entry), void *ptr);
	Dz1JsonSpecEntry **(*get_array)(struct Dz1JsonSpecRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *data);
	bool_t (*remove)(struct Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key);
	Dz1JsonSpecEntry *(*extract)(struct Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key);
	Dz1JsonSpecEntry *(*find)(struct Dz1JsonSpecRefList *p, Dz1JsonSpecEntry *key);
	int (*cmp)(Dz1JsonSpecEntry *a, Dz1JsonSpecEntry *b);
} Dz1JsonSpecRefList;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecRefList *Dz1JsonSpecRefList_new(Dz1Error *err);
static __inline__ Dz1JsonSpecRefList *Dz1JsonSpecRefList_gen(Dz1Error *err) { return Dz1JsonSpecRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecRefList *Dz1JsonSpecRefList_clone(Dz1JsonSpecRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecRefList_purge(Dz1JsonSpecRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecRefList_del(Dz1JsonSpecRefList *p);
static __inline__ void Dz1JsonSpecRefList_delAndSetNull(void *ptr)
{
	Dz1JsonSpecRefList **p = (Dz1JsonSpecRefList **)ptr;
	if (p != NULL) { Dz1JsonSpecRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecRefList_dump(Dz1JsonSpecRefList *p, int tab);

// Dz1JsonSpecRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecUndefinedEntry
typedef struct Dz1JsonSpecUndefinedEntry
{
	Dz1Str					 name;
	Dz1JsonSpecRefList		*refs;
} Dz1JsonSpecUndefinedEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecUndefinedEntry *Dz1JsonSpecUndefinedEntry_new(Dz1Str name, Dz1Error *err);
static __inline__ Dz1JsonSpecUndefinedEntry *Dz1JsonSpecUndefinedEntry_gen(Dz1Error *err) { return Dz1JsonSpecUndefinedEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedEntry_purge(Dz1JsonSpecUndefinedEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedEntry_del(Dz1JsonSpecUndefinedEntry *p);
static __inline__ void Dz1JsonSpecUndefinedEntry_delAndSetNull(void *ptr)
{
	Dz1JsonSpecUndefinedEntry **p = (Dz1JsonSpecUndefinedEntry **)ptr;
	if (p) { Dz1JsonSpecUndefinedEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedEntry_dump(Dz1JsonSpecUndefinedEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1JsonSpecUndefinedEntry_cmp(Dz1JsonSpecUndefinedEntry *a, Dz1JsonSpecUndefinedEntry *b); 
// Dz1JsonSpecUndefinedEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecUndefinedList
typedef struct Dz1JsonSpecUndefinedList
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonSpecUndefinedList *p);
	Dz1Error (*travel)(struct Dz1JsonSpecUndefinedList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecUndefinedEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonSpecUndefinedList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecUndefinedEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonSpecUndefinedList *p, Dz1Error (*func)(void *ptr, Dz1JsonSpecUndefinedEntry *entry), void *ptr);
	Dz1JsonSpecUndefinedEntry **(*get_array)(struct Dz1JsonSpecUndefinedList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *data);
	bool_t (*remove)(struct Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key);
	Dz1JsonSpecUndefinedEntry *(*extract)(struct Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key);
	Dz1JsonSpecUndefinedEntry *(*find)(struct Dz1JsonSpecUndefinedList *p, Dz1JsonSpecUndefinedEntry *key);
	int (*cmp)(Dz1JsonSpecUndefinedEntry *a, Dz1JsonSpecUndefinedEntry *b);
} Dz1JsonSpecUndefinedList;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonSpecUndefinedList *Dz1JsonSpecUndefinedList_new(Dz1Error *err);
static __inline__ Dz1JsonSpecUndefinedList *Dz1JsonSpecUndefinedList_gen(Dz1Error *err) { return Dz1JsonSpecUndefinedList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedList_purge(Dz1JsonSpecUndefinedList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedList_del(Dz1JsonSpecUndefinedList *p);
static __inline__ void Dz1JsonSpecUndefinedList_delAndSetNull(void *ptr)
{
	Dz1JsonSpecUndefinedList **p = (Dz1JsonSpecUndefinedList **)ptr;
	if (p != NULL) { Dz1JsonSpecUndefinedList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonSpecUndefinedList_dump(Dz1JsonSpecUndefinedList *p, int tab);

// Dz1JsonSpecUndefinedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonFifoUngetE
struct Dz1JsonFifoUngetE;

typedef struct Dz1JsonFifoUngetE
{
	u32_t						 c32;
	struct Dz1JsonFifoUngetE	*next;
} Dz1JsonFifoUngetE;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonFifoUngetE *Dz1JsonFifoUngetE_new(u32_t c32, 
																 struct Dz1JsonFifoUngetE *next_ref, Dz1Error *err);
static __inline__ Dz1JsonFifoUngetE *Dz1JsonFifoUngetE_gen(Dz1Error *err) { return Dz1JsonFifoUngetE_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonFifoUngetE_purge(Dz1JsonFifoUngetE *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonFifoUngetE_del(Dz1JsonFifoUngetE *p);
static __inline__ void Dz1JsonFifoUngetE_delAndSetNull(void *ptr)
{
	Dz1JsonFifoUngetE **p = (Dz1JsonFifoUngetE **)ptr;
	if (p) { Dz1JsonFifoUngetE_del(*p); *p = NULL; }
}
// Dz1JsonFifoUngetE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonFifo
typedef struct Dz1JsonFifo
{
	str_t					 ingress_charset;
	Dz1JsonConv				*conv;
	Dz1ElasticBuf			*ingress_buf;
	Dz1Stream				*pop_stream;
	Dz1JsonFifoUngetE		*ungetc_head;
} Dz1JsonFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonFifo *Dz1JsonFifo_new(str_t ingress_charset, 
													 Dz1JsonConv *conv, 
													 Dz1ElasticBuf *ingress_buf, 
													 Dz1Stream *pop_stream, Dz1Error *err);
static __inline__ Dz1JsonFifo *Dz1JsonFifo_gen(Dz1Error *err) { return Dz1JsonFifo_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonFifo_purge(Dz1JsonFifo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonFifo_del(Dz1JsonFifo *p);
static __inline__ void Dz1JsonFifo_delAndSetNull(void *ptr)
{
	Dz1JsonFifo **p = (Dz1JsonFifo **)ptr;
	if (p) { Dz1JsonFifo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonFifo_dump(Dz1JsonFifo *p, int tab);
// Dz1JsonFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonNumberParse
typedef enum Dz1JsonNumberParse
{
	Dz1JsonNumberParse_undef,
	Dz1JsonNumberParse_decimal,
	Dz1JsonNumberParse_exponent,
	Dz1JsonNumberParse_exp_digit,
	Dz1JsonNumberParse_hex,
	Dz1JsonNumberParse_oct,
	Dz1JsonNumberParse_binary,
	Dz1JsonNumberParse_max
} Dz1JsonNumberParse;

DZ1_CPPLINK str_t Dz1JsonNumberParseStrA(Dz1JsonNumberParse v);
DZ1_CPPLINK Dz1JsonNumberParse Dz1JsonNumberParseFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonNumberParseStrW(Dz1JsonNumberParse v);
DZ1_CPPLINK Dz1JsonNumberParse Dz1JsonNumberParseFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonNumberParseStr Dz1JsonNumberParseStrW
#define Dz1JsonNumberParseFromStr Dz1JsonNumberParseFromStrW
#else // UNICODE
#define Dz1JsonNumberParseStr Dz1JsonNumberParseStrA
#define Dz1JsonNumberParseFromStr Dz1JsonNumberParseFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonNumberParseStr Dz1JsonNumberParseStrA
#define Dz1JsonNumberParseFromStr Dz1JsonNumberParseFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonNumberParse *Dz1JsonNumberParse_new(Dz1JsonNumberParse *src, Dz1Error *err);
static __inline__ Dz1JsonNumberParse *Dz1JsonNumberParse_gen(Dz1Error *err) { Dz1JsonNumberParse v = Dz1JsonNumberParse_max; return Dz1JsonNumberParse_new(&v, err); }
static __inline__ void Dz1JsonNumberParse_del(Dz1JsonNumberParse *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonNumberParse_delAndSetNull(void *ptr)
{
	Dz1JsonNumberParse **p = (Dz1JsonNumberParse **)ptr;
	if (p != NULL) { Dz1JsonNumberParse_del(*p); *p = NULL; }
}
// Dz1JsonNumberParse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonLexerState
typedef enum Dz1JsonLexerState
{
	Dz1JsonLexerState_no_lexing,
	Dz1JsonLexerState_number_lexing,
	Dz1JsonLexerState_string_lexing,
	Dz1JsonLexerState_symbol_lexing,
	Dz1JsonLexerState_max
} Dz1JsonLexerState;

DZ1_CPPLINK str_t Dz1JsonLexerStateStrA(Dz1JsonLexerState v);
DZ1_CPPLINK Dz1JsonLexerState Dz1JsonLexerStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonLexerStateStrW(Dz1JsonLexerState v);
DZ1_CPPLINK Dz1JsonLexerState Dz1JsonLexerStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonLexerStateStr Dz1JsonLexerStateStrW
#define Dz1JsonLexerStateFromStr Dz1JsonLexerStateFromStrW
#else // UNICODE
#define Dz1JsonLexerStateStr Dz1JsonLexerStateStrA
#define Dz1JsonLexerStateFromStr Dz1JsonLexerStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonLexerStateStr Dz1JsonLexerStateStrA
#define Dz1JsonLexerStateFromStr Dz1JsonLexerStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonLexerState *Dz1JsonLexerState_new(Dz1JsonLexerState *src, Dz1Error *err);
static __inline__ Dz1JsonLexerState *Dz1JsonLexerState_gen(Dz1Error *err) { Dz1JsonLexerState v = Dz1JsonLexerState_max; return Dz1JsonLexerState_new(&v, err); }
static __inline__ void Dz1JsonLexerState_del(Dz1JsonLexerState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonLexerState_delAndSetNull(void *ptr)
{
	Dz1JsonLexerState **p = (Dz1JsonLexerState **)ptr;
	if (p != NULL) { Dz1JsonLexerState_del(*p); *p = NULL; }
}
// Dz1JsonLexerState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonLexer
typedef struct Dz1JsonLexer
{
	Dz1JsonLexerState		 state;
	u32_t					 flags;
	Dz1ElasticBuf			*buf;
	Dz1JsonToken			*token;
	u32_t					 temp;
	u32_t					 t_len;
	u32_t					 dbgs;
} Dz1JsonLexer;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonLexer *Dz1JsonLexer_new(Dz1ElasticBuf *buf, Dz1Error *err);
static __inline__ Dz1JsonLexer *Dz1JsonLexer_gen(Dz1Error *err) { return Dz1JsonLexer_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonLexer_purge(Dz1JsonLexer *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonLexer_del(Dz1JsonLexer *p);
static __inline__ void Dz1JsonLexer_delAndSetNull(void *ptr)
{
	Dz1JsonLexer **p = (Dz1JsonLexer **)ptr;
	if (p) { Dz1JsonLexer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonLexer_dump(Dz1JsonLexer *p, int tab);
// Dz1JsonLexer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPrimitiveState
typedef enum Dz1JsonStackPrimitiveState
{
	Dz1JsonStackPrimitiveState_init,
	Dz1JsonStackPrimitiveState_max
} Dz1JsonStackPrimitiveState;

DZ1_CPPLINK str_t Dz1JsonStackPrimitiveStateStrA(Dz1JsonStackPrimitiveState v);
DZ1_CPPLINK Dz1JsonStackPrimitiveState Dz1JsonStackPrimitiveStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackPrimitiveStateStrW(Dz1JsonStackPrimitiveState v);
DZ1_CPPLINK Dz1JsonStackPrimitiveState Dz1JsonStackPrimitiveStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackPrimitiveStateStr Dz1JsonStackPrimitiveStateStrW
#define Dz1JsonStackPrimitiveStateFromStr Dz1JsonStackPrimitiveStateFromStrW
#else // UNICODE
#define Dz1JsonStackPrimitiveStateStr Dz1JsonStackPrimitiveStateStrA
#define Dz1JsonStackPrimitiveStateFromStr Dz1JsonStackPrimitiveStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackPrimitiveStateStr Dz1JsonStackPrimitiveStateStrA
#define Dz1JsonStackPrimitiveStateFromStr Dz1JsonStackPrimitiveStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPrimitiveState *Dz1JsonStackPrimitiveState_new(Dz1JsonStackPrimitiveState *src, Dz1Error *err);
static __inline__ Dz1JsonStackPrimitiveState *Dz1JsonStackPrimitiveState_gen(Dz1Error *err) { Dz1JsonStackPrimitiveState v = Dz1JsonStackPrimitiveState_max; return Dz1JsonStackPrimitiveState_new(&v, err); }
static __inline__ void Dz1JsonStackPrimitiveState_del(Dz1JsonStackPrimitiveState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackPrimitiveState_delAndSetNull(void *ptr)
{
	Dz1JsonStackPrimitiveState **p = (Dz1JsonStackPrimitiveState **)ptr;
	if (p != NULL) { Dz1JsonStackPrimitiveState_del(*p); *p = NULL; }
}
// Dz1JsonStackPrimitiveState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPrimitive
typedef struct Dz1JsonStackPrimitive
{
	Dz1JsonStackPrimitiveState		state;
} Dz1JsonStackPrimitive;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPrimitive *Dz1JsonStackPrimitive_new(Dz1JsonStackPrimitiveState state, Dz1Error *err);
static __inline__ Dz1JsonStackPrimitive *Dz1JsonStackPrimitive_gen(Dz1Error *err) { return Dz1JsonStackPrimitive_new(Dz1JsonStackPrimitiveState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackPrimitive_copy(Dz1JsonStackPrimitive *dst, Dz1JsonStackPrimitive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPrimitive *Dz1JsonStackPrimitive_clone(Dz1JsonStackPrimitive *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPrimitive_purge(Dz1JsonStackPrimitive *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPrimitive_del(Dz1JsonStackPrimitive *p);
static __inline__ void Dz1JsonStackPrimitive_delAndSetNull(void *ptr)
{
	Dz1JsonStackPrimitive **p = (Dz1JsonStackPrimitive **)ptr;
	if (p) { Dz1JsonStackPrimitive_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPrimitive_dump(Dz1JsonStackPrimitive *p, int tab);
// Dz1JsonStackPrimitive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackStructState
typedef enum Dz1JsonStackStructState
{
	Dz1JsonStackStructState_init,
	Dz1JsonStackStructState_parsing_lstart,
	Dz1JsonStackStructState_parsing_pair,
	Dz1JsonStackStructState_parsing_comma,
	Dz1JsonStackStructState_parsing_lend,
	Dz1JsonStackStructState_max
} Dz1JsonStackStructState;

DZ1_CPPLINK str_t Dz1JsonStackStructStateStrA(Dz1JsonStackStructState v);
DZ1_CPPLINK Dz1JsonStackStructState Dz1JsonStackStructStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackStructStateStrW(Dz1JsonStackStructState v);
DZ1_CPPLINK Dz1JsonStackStructState Dz1JsonStackStructStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackStructStateStr Dz1JsonStackStructStateStrW
#define Dz1JsonStackStructStateFromStr Dz1JsonStackStructStateFromStrW
#else // UNICODE
#define Dz1JsonStackStructStateStr Dz1JsonStackStructStateStrA
#define Dz1JsonStackStructStateFromStr Dz1JsonStackStructStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackStructStateStr Dz1JsonStackStructStateStrA
#define Dz1JsonStackStructStateFromStr Dz1JsonStackStructStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackStructState *Dz1JsonStackStructState_new(Dz1JsonStackStructState *src, Dz1Error *err);
static __inline__ Dz1JsonStackStructState *Dz1JsonStackStructState_gen(Dz1Error *err) { Dz1JsonStackStructState v = Dz1JsonStackStructState_max; return Dz1JsonStackStructState_new(&v, err); }
static __inline__ void Dz1JsonStackStructState_del(Dz1JsonStackStructState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackStructState_delAndSetNull(void *ptr)
{
	Dz1JsonStackStructState **p = (Dz1JsonStackStructState **)ptr;
	if (p != NULL) { Dz1JsonStackStructState_del(*p); *p = NULL; }
}
// Dz1JsonStackStructState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackStruct
typedef struct Dz1JsonStackStruct
{
	Dz1JsonStackStructState		state;
} Dz1JsonStackStruct;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackStruct *Dz1JsonStackStruct_new(Dz1JsonStackStructState state, Dz1Error *err);
static __inline__ Dz1JsonStackStruct *Dz1JsonStackStruct_gen(Dz1Error *err) { return Dz1JsonStackStruct_new(Dz1JsonStackStructState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackStruct_copy(Dz1JsonStackStruct *dst, Dz1JsonStackStruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackStruct *Dz1JsonStackStruct_clone(Dz1JsonStackStruct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackStruct_purge(Dz1JsonStackStruct *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackStruct_del(Dz1JsonStackStruct *p);
static __inline__ void Dz1JsonStackStruct_delAndSetNull(void *ptr)
{
	Dz1JsonStackStruct **p = (Dz1JsonStackStruct **)ptr;
	if (p) { Dz1JsonStackStruct_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackStruct_dump(Dz1JsonStackStruct *p, int tab);
// Dz1JsonStackStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackUnionState
typedef enum Dz1JsonStackUnionState
{
	Dz1JsonStackUnionState_init,
	Dz1JsonStackUnionState_parsing_lstart,
	Dz1JsonStackUnionState_parsing_pair,
	Dz1JsonStackUnionState_parsing_lend,
	Dz1JsonStackUnionState_max
} Dz1JsonStackUnionState;

DZ1_CPPLINK str_t Dz1JsonStackUnionStateStrA(Dz1JsonStackUnionState v);
DZ1_CPPLINK Dz1JsonStackUnionState Dz1JsonStackUnionStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackUnionStateStrW(Dz1JsonStackUnionState v);
DZ1_CPPLINK Dz1JsonStackUnionState Dz1JsonStackUnionStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackUnionStateStr Dz1JsonStackUnionStateStrW
#define Dz1JsonStackUnionStateFromStr Dz1JsonStackUnionStateFromStrW
#else // UNICODE
#define Dz1JsonStackUnionStateStr Dz1JsonStackUnionStateStrA
#define Dz1JsonStackUnionStateFromStr Dz1JsonStackUnionStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackUnionStateStr Dz1JsonStackUnionStateStrA
#define Dz1JsonStackUnionStateFromStr Dz1JsonStackUnionStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackUnionState *Dz1JsonStackUnionState_new(Dz1JsonStackUnionState *src, Dz1Error *err);
static __inline__ Dz1JsonStackUnionState *Dz1JsonStackUnionState_gen(Dz1Error *err) { Dz1JsonStackUnionState v = Dz1JsonStackUnionState_max; return Dz1JsonStackUnionState_new(&v, err); }
static __inline__ void Dz1JsonStackUnionState_del(Dz1JsonStackUnionState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackUnionState_delAndSetNull(void *ptr)
{
	Dz1JsonStackUnionState **p = (Dz1JsonStackUnionState **)ptr;
	if (p != NULL) { Dz1JsonStackUnionState_del(*p); *p = NULL; }
}
// Dz1JsonStackUnionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackUnion
typedef struct Dz1JsonStackUnion
{
	Dz1JsonStackUnionState		state;
} Dz1JsonStackUnion;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackUnion *Dz1JsonStackUnion_new(Dz1JsonStackUnionState state, Dz1Error *err);
static __inline__ Dz1JsonStackUnion *Dz1JsonStackUnion_gen(Dz1Error *err) { return Dz1JsonStackUnion_new(Dz1JsonStackUnionState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackUnion_copy(Dz1JsonStackUnion *dst, Dz1JsonStackUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackUnion *Dz1JsonStackUnion_clone(Dz1JsonStackUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackUnion_purge(Dz1JsonStackUnion *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackUnion_del(Dz1JsonStackUnion *p);
static __inline__ void Dz1JsonStackUnion_delAndSetNull(void *ptr)
{
	Dz1JsonStackUnion **p = (Dz1JsonStackUnion **)ptr;
	if (p) { Dz1JsonStackUnion_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackUnion_dump(Dz1JsonStackUnion *p, int tab);
// Dz1JsonStackUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackArrayState
typedef enum Dz1JsonStackArrayState
{
	Dz1JsonStackArrayState_init,
	Dz1JsonStackArrayState_parsing_bstart,
	Dz1JsonStackArrayState_parsing_object,
	Dz1JsonStackArrayState_parsing_comma,
	Dz1JsonStackArrayState_parsing_bend,
	Dz1JsonStackArrayState_max
} Dz1JsonStackArrayState;

DZ1_CPPLINK str_t Dz1JsonStackArrayStateStrA(Dz1JsonStackArrayState v);
DZ1_CPPLINK Dz1JsonStackArrayState Dz1JsonStackArrayStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackArrayStateStrW(Dz1JsonStackArrayState v);
DZ1_CPPLINK Dz1JsonStackArrayState Dz1JsonStackArrayStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackArrayStateStr Dz1JsonStackArrayStateStrW
#define Dz1JsonStackArrayStateFromStr Dz1JsonStackArrayStateFromStrW
#else // UNICODE
#define Dz1JsonStackArrayStateStr Dz1JsonStackArrayStateStrA
#define Dz1JsonStackArrayStateFromStr Dz1JsonStackArrayStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackArrayStateStr Dz1JsonStackArrayStateStrA
#define Dz1JsonStackArrayStateFromStr Dz1JsonStackArrayStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackArrayState *Dz1JsonStackArrayState_new(Dz1JsonStackArrayState *src, Dz1Error *err);
static __inline__ Dz1JsonStackArrayState *Dz1JsonStackArrayState_gen(Dz1Error *err) { Dz1JsonStackArrayState v = Dz1JsonStackArrayState_max; return Dz1JsonStackArrayState_new(&v, err); }
static __inline__ void Dz1JsonStackArrayState_del(Dz1JsonStackArrayState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackArrayState_delAndSetNull(void *ptr)
{
	Dz1JsonStackArrayState **p = (Dz1JsonStackArrayState **)ptr;
	if (p != NULL) { Dz1JsonStackArrayState_del(*p); *p = NULL; }
}
// Dz1JsonStackArrayState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackArray
typedef struct Dz1JsonStackArray
{
	Dz1JsonStackArrayState		state;
} Dz1JsonStackArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackArray *Dz1JsonStackArray_new(Dz1JsonStackArrayState state, Dz1Error *err);
static __inline__ Dz1JsonStackArray *Dz1JsonStackArray_gen(Dz1Error *err) { return Dz1JsonStackArray_new(Dz1JsonStackArrayState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackArray_copy(Dz1JsonStackArray *dst, Dz1JsonStackArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackArray *Dz1JsonStackArray_clone(Dz1JsonStackArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackArray_purge(Dz1JsonStackArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackArray_del(Dz1JsonStackArray *p);
static __inline__ void Dz1JsonStackArray_delAndSetNull(void *ptr)
{
	Dz1JsonStackArray **p = (Dz1JsonStackArray **)ptr;
	if (p) { Dz1JsonStackArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackArray_dump(Dz1JsonStackArray *p, int tab);
// Dz1JsonStackArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPairState
typedef enum Dz1JsonStackPairState
{
	Dz1JsonStackPairState_init,
	Dz1JsonStackPairState_parsing_name,
	Dz1JsonStackPairState_parsing_colon,
	Dz1JsonStackPairState_parsing_object,
	Dz1JsonStackPairState_max
} Dz1JsonStackPairState;

DZ1_CPPLINK str_t Dz1JsonStackPairStateStrA(Dz1JsonStackPairState v);
DZ1_CPPLINK Dz1JsonStackPairState Dz1JsonStackPairStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackPairStateStrW(Dz1JsonStackPairState v);
DZ1_CPPLINK Dz1JsonStackPairState Dz1JsonStackPairStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackPairStateStr Dz1JsonStackPairStateStrW
#define Dz1JsonStackPairStateFromStr Dz1JsonStackPairStateFromStrW
#else // UNICODE
#define Dz1JsonStackPairStateStr Dz1JsonStackPairStateStrA
#define Dz1JsonStackPairStateFromStr Dz1JsonStackPairStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackPairStateStr Dz1JsonStackPairStateStrA
#define Dz1JsonStackPairStateFromStr Dz1JsonStackPairStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPairState *Dz1JsonStackPairState_new(Dz1JsonStackPairState *src, Dz1Error *err);
static __inline__ Dz1JsonStackPairState *Dz1JsonStackPairState_gen(Dz1Error *err) { Dz1JsonStackPairState v = Dz1JsonStackPairState_max; return Dz1JsonStackPairState_new(&v, err); }
static __inline__ void Dz1JsonStackPairState_del(Dz1JsonStackPairState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackPairState_delAndSetNull(void *ptr)
{
	Dz1JsonStackPairState **p = (Dz1JsonStackPairState **)ptr;
	if (p != NULL) { Dz1JsonStackPairState_del(*p); *p = NULL; }
}
// Dz1JsonStackPairState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackPair
typedef struct Dz1JsonStackPair
{
	Dz1JsonStackPairState		 state;
	Dz1JsonSpecEntry			*par_type;
	void						*par_ptr;
} Dz1JsonStackPair;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPair *Dz1JsonStackPair_new(Dz1JsonStackPairState state, 
															   Dz1JsonSpecEntry *par_type_ref, 
															   void *par_ptr, Dz1Error *err);
static __inline__ Dz1JsonStackPair *Dz1JsonStackPair_gen(Dz1Error *err) { return Dz1JsonStackPair_new(Dz1JsonStackPairState_max, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackPair_copy(Dz1JsonStackPair *dst, Dz1JsonStackPair *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackPair *Dz1JsonStackPair_clone(Dz1JsonStackPair *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPair_purge(Dz1JsonStackPair *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPair_del(Dz1JsonStackPair *p);
static __inline__ void Dz1JsonStackPair_delAndSetNull(void *ptr)
{
	Dz1JsonStackPair **p = (Dz1JsonStackPair **)ptr;
	if (p) { Dz1JsonStackPair_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackPair_dump(Dz1JsonStackPair *p, int tab);
// Dz1JsonStackPair
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackObjState
typedef enum Dz1JsonStackObjState
{
	Dz1JsonStackObjState_init,
	Dz1JsonStackObjState_parsing_lstart,
	Dz1JsonStackObjState_parsing_object,
	Dz1JsonStackObjState_parsing_lend,
	Dz1JsonStackObjState_max
} Dz1JsonStackObjState;

DZ1_CPPLINK str_t Dz1JsonStackObjStateStrA(Dz1JsonStackObjState v);
DZ1_CPPLINK Dz1JsonStackObjState Dz1JsonStackObjStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackObjStateStrW(Dz1JsonStackObjState v);
DZ1_CPPLINK Dz1JsonStackObjState Dz1JsonStackObjStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackObjStateStr Dz1JsonStackObjStateStrW
#define Dz1JsonStackObjStateFromStr Dz1JsonStackObjStateFromStrW
#else // UNICODE
#define Dz1JsonStackObjStateStr Dz1JsonStackObjStateStrA
#define Dz1JsonStackObjStateFromStr Dz1JsonStackObjStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackObjStateStr Dz1JsonStackObjStateStrA
#define Dz1JsonStackObjStateFromStr Dz1JsonStackObjStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackObjState *Dz1JsonStackObjState_new(Dz1JsonStackObjState *src, Dz1Error *err);
static __inline__ Dz1JsonStackObjState *Dz1JsonStackObjState_gen(Dz1Error *err) { Dz1JsonStackObjState v = Dz1JsonStackObjState_max; return Dz1JsonStackObjState_new(&v, err); }
static __inline__ void Dz1JsonStackObjState_del(Dz1JsonStackObjState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackObjState_delAndSetNull(void *ptr)
{
	Dz1JsonStackObjState **p = (Dz1JsonStackObjState **)ptr;
	if (p != NULL) { Dz1JsonStackObjState_del(*p); *p = NULL; }
}
// Dz1JsonStackObjState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackObj
typedef struct Dz1JsonStackObj
{
	Dz1JsonStackObjState	state;
} Dz1JsonStackObj;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackObj *Dz1JsonStackObj_new(Dz1Error *err);
static __inline__ Dz1JsonStackObj *Dz1JsonStackObj_gen(Dz1Error *err) { return Dz1JsonStackObj_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonStackObj_copy(Dz1JsonStackObj *dst, Dz1JsonStackObj *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackObj *Dz1JsonStackObj_clone(Dz1JsonStackObj *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackObj_purge(Dz1JsonStackObj *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackObj_del(Dz1JsonStackObj *p);
static __inline__ void Dz1JsonStackObj_delAndSetNull(void *ptr)
{
	Dz1JsonStackObj **p = (Dz1JsonStackObj **)ptr;
	if (p) { Dz1JsonStackObj_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackObj_dump(Dz1JsonStackObj *p, int tab);
// Dz1JsonStackObj
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackDataPresent
typedef enum Dz1JsonStackDataPresent
{
	Dz1JsonStackDataPresent_pr,
	Dz1JsonStackDataPresent_st,
	Dz1JsonStackDataPresent_un,
	Dz1JsonStackDataPresent_ar,
	Dz1JsonStackDataPresent_pair,
	Dz1JsonStackDataPresent_obj,
	Dz1JsonStackDataPresent_max
} Dz1JsonStackDataPresent;

DZ1_CPPLINK str_t Dz1JsonStackDataPresentStrA(Dz1JsonStackDataPresent v);
DZ1_CPPLINK Dz1JsonStackDataPresent Dz1JsonStackDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1JsonStackDataPresentStrW(Dz1JsonStackDataPresent v);
DZ1_CPPLINK Dz1JsonStackDataPresent Dz1JsonStackDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1JsonStackDataPresentStr Dz1JsonStackDataPresentStrW
#define Dz1JsonStackDataPresentFromStr Dz1JsonStackDataPresentFromStrW
#else // UNICODE
#define Dz1JsonStackDataPresentStr Dz1JsonStackDataPresentStrA
#define Dz1JsonStackDataPresentFromStr Dz1JsonStackDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1JsonStackDataPresentStr Dz1JsonStackDataPresentStrA
#define Dz1JsonStackDataPresentFromStr Dz1JsonStackDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackDataPresent *Dz1JsonStackDataPresent_new(Dz1JsonStackDataPresent *src, Dz1Error *err);
static __inline__ Dz1JsonStackDataPresent *Dz1JsonStackDataPresent_gen(Dz1Error *err) { Dz1JsonStackDataPresent v = Dz1JsonStackDataPresent_max; return Dz1JsonStackDataPresent_new(&v, err); }
#define Dz1JsonStackDataPresent_clone             Dz1JsonStackDataPresent_new
static __inline__ void Dz1JsonStackDataPresent_del(Dz1JsonStackDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1JsonStackDataPresent_delAndSetNull(void *ptr)
{
	Dz1JsonStackDataPresent **p = (Dz1JsonStackDataPresent **)ptr;
	if (p != NULL) { Dz1JsonStackDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackDataPresent_dump(Dz1JsonStackDataPresent *v, int tab);
// Dz1JsonStackDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStackData
typedef struct Dz1JsonStackData
{
	Dz1JsonStackDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1JsonStackPrimitive		*pr;
		Dz1JsonStackStruct			*st;
		Dz1JsonStackUnion			*un;
		Dz1JsonStackArray			*ar;
		Dz1JsonStackPair			*pair;
		Dz1JsonStackObj				*obj;
	} x;
} Dz1JsonStackData;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackData *Dz1JsonStackData_new(Dz1JsonStackDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1JsonStackData *Dz1JsonStackData_gen(Dz1Error *err) { return Dz1JsonStackData_new(Dz1JsonStackDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1JsonStackData_copy(Dz1JsonStackData *dst, Dz1JsonStackData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStackData *Dz1JsonStackData_clone(Dz1JsonStackData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackData_purge(Dz1JsonStackData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackData_del(Dz1JsonStackData *p);
static __inline__ void Dz1JsonStackData_delAndSetNull(void *ptr)
{
	Dz1JsonStackData **p = (Dz1JsonStackData **)ptr;
	if (p != NULL) { Dz1JsonStackData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStackData_dump(Dz1JsonStackData *p, int tab);
// Dz1JsonStackData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonStack
struct Dz1JsonStack;

typedef struct Dz1JsonStack
{
	Dz1JsonStackData		*data;
	Dz1JsonVarBind			*dst_var;
	Dz1JsonVarBind			*ret_var;
	struct Dz1JsonStack		*next;
} Dz1JsonStack;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonStack *Dz1JsonStack_new(Dz1JsonStackData *data, 
													   Dz1JsonVarBind *dst_var, Dz1Error *err);
static __inline__ Dz1JsonStack *Dz1JsonStack_gen(Dz1Error *err) { return Dz1JsonStack_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStack_purge(Dz1JsonStack *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStack_del(Dz1JsonStack *p);
static __inline__ void Dz1JsonStack_delAndSetNull(void *ptr)
{
	Dz1JsonStack **p = (Dz1JsonStack **)ptr;
	if (p) { Dz1JsonStack_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonStack_dump(Dz1JsonStack *p, int tab);
// Dz1JsonStack
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonOutputEntry
struct Dz1JsonOutputEntry;

typedef struct Dz1JsonOutputEntry
{
	struct Dz1JsonOutputEntry		*next;
	void							*result;
	Dz1JsonObjDelF					 result_del;
} Dz1JsonOutputEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonOutputEntry *Dz1JsonOutputEntry_new(struct Dz1JsonOutputEntry *next_ref, 
																   void *result, 
																   Dz1JsonObjDelF result_del, Dz1Error *err);
static __inline__ Dz1JsonOutputEntry *Dz1JsonOutputEntry_gen(Dz1Error *err) { return Dz1JsonOutputEntry_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonOutputEntry_copy(Dz1JsonOutputEntry *dst, Dz1JsonOutputEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonOutputEntry *Dz1JsonOutputEntry_clone(Dz1JsonOutputEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputEntry_purge(Dz1JsonOutputEntry *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputEntry_del(Dz1JsonOutputEntry *p);	// User Customized
static __inline__ void Dz1JsonOutputEntry_delAndSetNull(void *ptr)
{
	Dz1JsonOutputEntry **p = (Dz1JsonOutputEntry **)ptr;
	if (p) { Dz1JsonOutputEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputEntry_dump(Dz1JsonOutputEntry *p, int tab);
// Dz1JsonOutputEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonOutputFifo
typedef struct Dz1JsonOutputFifo
{
	Dz1JsonOutputEntry		*head;
	Dz1JsonOutputEntry		*tail;
} Dz1JsonOutputFifo;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonOutputFifo *Dz1JsonOutputFifo_new(Dz1Error *err);
static __inline__ Dz1JsonOutputFifo *Dz1JsonOutputFifo_gen(Dz1Error *err) { return Dz1JsonOutputFifo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1JsonOutputFifo_copy(Dz1JsonOutputFifo *dst, Dz1JsonOutputFifo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonOutputFifo *Dz1JsonOutputFifo_clone(Dz1JsonOutputFifo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputFifo_purge(Dz1JsonOutputFifo *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputFifo_del(Dz1JsonOutputFifo *p);	// User Customized
static __inline__ void Dz1JsonOutputFifo_delAndSetNull(void *ptr)
{
	Dz1JsonOutputFifo **p = (Dz1JsonOutputFifo **)ptr;
	if (p) { Dz1JsonOutputFifo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonOutputFifo_dump(Dz1JsonOutputFifo *p, int tab);
// Dz1JsonOutputFifo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonEnv
typedef struct Dz1JsonEnv
{
	Dz1JsonLexer			*lexer;
	Dz1JsonSpec				*spec;
	Dz1JsonSpecEntry		*root_spe;
	Dz1JsonFifo				*ingress;
	Dz1JsonOutputFifo		*egress;
	Dz1JsonStack			*stk;
	Dz1JsonConv				*stringify_conv;
	Dz1ElasticBuf			*stringify_buf;
} Dz1JsonEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonEnv *Dz1JsonEnv_new(Dz1JsonLexer *lexer, 
												   Dz1JsonSpec *spec_ref, 
												   Dz1JsonSpecEntry *root_spe_ref, 
												   Dz1JsonFifo *ingress, 
												   Dz1JsonOutputFifo *egress, 
												   Dz1JsonConv *stringify_conv, Dz1Error *err);
static __inline__ Dz1JsonEnv *Dz1JsonEnv_gen(Dz1Error *err) { return Dz1JsonEnv_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonEnv_purge(Dz1JsonEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonEnv_del(Dz1JsonEnv *p);
static __inline__ void Dz1JsonEnv_delAndSetNull(void *ptr)
{
	Dz1JsonEnv **p = (Dz1JsonEnv **)ptr;
	if (p) { Dz1JsonEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonEnv_dump(Dz1JsonEnv *p, int tab);
// Dz1JsonEnv
////////////////////////////////////////////////////////////////////////////////

#endif
