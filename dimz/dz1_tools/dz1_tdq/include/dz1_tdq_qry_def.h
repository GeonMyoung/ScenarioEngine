#ifndef _DZ1_TDC_DZ1_TDQ_QRY_DEF_H_
#define _DZ1_TDC_DZ1_TDQ_QRY_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_tbl_def.h"
#include "dz1_tdq_types.h"

////////////////////////////////////////////////////////////////////////////////
// _declare_Dz1TdqQueryTblName
struct Dz1TdqQueryTblName;
// _declare_Dz1TdqQueryTblName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryTblCol
struct Dz1TdqQueryTblName;

typedef struct Dz1TdqQryTblCol
{
	struct Dz1TdqQueryTblName		*tbl;
	Dz1Str							 col_name;
} Dz1TdqQryTblCol;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryTblCol *Dz1TdqQryTblCol_new(struct Dz1TdqQueryTblName *tbl_ref, 
															 Dz1Str col_name, Dz1Error *err);
static __inline__ Dz1TdqQryTblCol *Dz1TdqQryTblCol_gen(Dz1Error *err) { return Dz1TdqQryTblCol_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQryTblCol_copy(Dz1TdqQryTblCol *dst, Dz1TdqQryTblCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryTblCol *Dz1TdqQryTblCol_clone(Dz1TdqQryTblCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryTblCol_purge(Dz1TdqQryTblCol *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryTblCol_del(Dz1TdqQryTblCol *p);
static __inline__ void Dz1TdqQryTblCol_delAndSetNull(void *ptr)
{
	Dz1TdqQryTblCol **p = (Dz1TdqQryTblCol **)ptr;
	if (p) { Dz1TdqQryTblCol_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryTblCol_dump(Dz1TdqQryTblCol *p, int tab);
// Dz1TdqQryTblCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryExprCol
typedef struct Dz1TdqQryExprCol
{
	Dz1TdqSqlTypeSpec		*type;
	Dz1Str					 expression;
} Dz1TdqQryExprCol;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryExprCol *Dz1TdqQryExprCol_new(Dz1TdqSqlTypeSpec *type, 
															   Dz1Str expression, Dz1Error *err);
static __inline__ Dz1TdqQryExprCol *Dz1TdqQryExprCol_gen(Dz1Error *err) { return Dz1TdqQryExprCol_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQryExprCol_copy(Dz1TdqQryExprCol *dst, Dz1TdqQryExprCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryExprCol *Dz1TdqQryExprCol_clone(Dz1TdqQryExprCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryExprCol_purge(Dz1TdqQryExprCol *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryExprCol_del(Dz1TdqQryExprCol *p);
static __inline__ void Dz1TdqQryExprCol_delAndSetNull(void *ptr)
{
	Dz1TdqQryExprCol **p = (Dz1TdqQryExprCol **)ptr;
	if (p) { Dz1TdqQryExprCol_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryExprCol_dump(Dz1TdqQryExprCol *p, int tab);
// Dz1TdqQryExprCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryColPresent
typedef enum Dz1TdqQryColPresent
{
	Dz1TdqQryColPresent_tcol,
	Dz1TdqQryColPresent_ecol,
	Dz1TdqQryColPresent_max
} Dz1TdqQryColPresent;

DZ1_CPPLINK str_t Dz1TdqQryColPresentStrA(Dz1TdqQryColPresent v);
DZ1_CPPLINK Dz1TdqQryColPresent Dz1TdqQryColPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqQryColPresentStrW(Dz1TdqQryColPresent v);
DZ1_CPPLINK Dz1TdqQryColPresent Dz1TdqQryColPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqQryColPresentStr Dz1TdqQryColPresentStrW
#define Dz1TdqQryColPresentFromStr Dz1TdqQryColPresentFromStrW
#else // UNICODE
#define Dz1TdqQryColPresentStr Dz1TdqQryColPresentStrA
#define Dz1TdqQryColPresentFromStr Dz1TdqQryColPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqQryColPresentStr Dz1TdqQryColPresentStrA
#define Dz1TdqQryColPresentFromStr Dz1TdqQryColPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryColPresent *Dz1TdqQryColPresent_new(Dz1TdqQryColPresent *src, Dz1Error *err);
static __inline__ Dz1TdqQryColPresent *Dz1TdqQryColPresent_gen(Dz1Error *err) { Dz1TdqQryColPresent v = Dz1TdqQryColPresent_max; return Dz1TdqQryColPresent_new(&v, err); }
#define Dz1TdqQryColPresent_clone             Dz1TdqQryColPresent_new
static __inline__ void Dz1TdqQryColPresent_del(Dz1TdqQryColPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqQryColPresent_delAndSetNull(void *ptr)
{
	Dz1TdqQryColPresent **p = (Dz1TdqQryColPresent **)ptr;
	if (p != NULL) { Dz1TdqQryColPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryColPresent_dump(Dz1TdqQryColPresent *v, int tab);
// Dz1TdqQryColPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryCol
typedef struct Dz1TdqQryCol
{
	Dz1TdqQryColPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TdqQryTblCol		*tcol;
		Dz1TdqQryExprCol	*ecol;
	} x;
} Dz1TdqQryCol;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryCol *Dz1TdqQryCol_new(Dz1TdqQryColPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TdqQryCol *Dz1TdqQryCol_gen(Dz1Error *err) { return Dz1TdqQryCol_new(Dz1TdqQryColPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TdqQryCol_copy(Dz1TdqQryCol *dst, Dz1TdqQryCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryCol *Dz1TdqQryCol_clone(Dz1TdqQryCol *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryCol_purge(Dz1TdqQryCol *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryCol_del(Dz1TdqQryCol *p);
static __inline__ void Dz1TdqQryCol_delAndSetNull(void *ptr)
{
	Dz1TdqQryCol **p = (Dz1TdqQryCol **)ptr;
	if (p != NULL) { Dz1TdqQryCol_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryCol_dump(Dz1TdqQryCol *p, int tab);
// Dz1TdqQryCol
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryColumn
typedef struct Dz1TdqQryColumn
{
	u32_t			 order;
	Dz1TdqQryCol	*src;
	Dz1Str			 alias;
} Dz1TdqQryColumn;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryColumn *Dz1TdqQryColumn_new(u32_t order, 
															 Dz1TdqQryCol *src, 
															 Dz1Str alias, Dz1Error *err);
static __inline__ Dz1TdqQryColumn *Dz1TdqQryColumn_gen(Dz1Error *err) { return Dz1TdqQryColumn_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQryColumn_copy(Dz1TdqQryColumn *dst, Dz1TdqQryColumn *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryColumn *Dz1TdqQryColumn_clone(Dz1TdqQryColumn *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryColumn_purge(Dz1TdqQryColumn *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryColumn_del(Dz1TdqQryColumn *p);
static __inline__ void Dz1TdqQryColumn_delAndSetNull(void *ptr)
{
	Dz1TdqQryColumn **p = (Dz1TdqQryColumn **)ptr;
	if (p) { Dz1TdqQryColumn_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryColumn_dump(Dz1TdqQryColumn *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqQryColumn_cmp(Dz1TdqQryColumn *a, Dz1TdqQryColumn *b); 
// Dz1TdqQryColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryRow
typedef struct Dz1TdqQryRow
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqQryRow *p);
	Dz1Error (*travel)(struct Dz1TdqQryRow *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqQryRow *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqQryRow *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1TdqQryColumn **(*get_array)(struct Dz1TdqQryRow *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqQryRow *p, Dz1TdqQryColumn *data);
	bool_t (*remove)(struct Dz1TdqQryRow *p, Dz1TdqQryColumn *key);
	Dz1TdqQryColumn *(*extract)(struct Dz1TdqQryRow *p, Dz1TdqQryColumn *key);
	Dz1TdqQryColumn *(*find)(struct Dz1TdqQryRow *p, Dz1TdqQryColumn *key);
	int (*cmp)(Dz1TdqQryColumn *a, Dz1TdqQryColumn *b);
} Dz1TdqQryRow;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryRow *Dz1TdqQryRow_new(Dz1Error *err);
static __inline__ Dz1TdqQryRow *Dz1TdqQryRow_gen(Dz1Error *err) { return Dz1TdqQryRow_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryRow *Dz1TdqQryRow_clone(Dz1TdqQryRow *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRow_purge(Dz1TdqQryRow *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRow_del(Dz1TdqQryRow *p);
static __inline__ void Dz1TdqQryRow_delAndSetNull(void *ptr)
{
	Dz1TdqQryRow **p = (Dz1TdqQryRow **)ptr;
	if (p != NULL) { Dz1TdqQryRow_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRow_dump(Dz1TdqQryRow *p, int tab);

// Dz1TdqQryRow
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQryRefCols
typedef struct Dz1TdqQryRefCols
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqQryRefCols *p);
	Dz1Error (*travel)(struct Dz1TdqQryRefCols *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqQryRefCols *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqQryRefCols *p, Dz1Error (*func)(void *ptr, Dz1TdqQryColumn *entry), void *ptr);
	Dz1TdqQryColumn **(*get_array)(struct Dz1TdqQryRefCols *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqQryRefCols *p, Dz1TdqQryColumn *data);
	int (*cmp)(Dz1TdqQryColumn *a, Dz1TdqQryColumn *b);
} Dz1TdqQryRefCols;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryRefCols *Dz1TdqQryRefCols_new(Dz1Error *err);
static __inline__ Dz1TdqQryRefCols *Dz1TdqQryRefCols_gen(Dz1Error *err) { return Dz1TdqQryRefCols_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQryRefCols *Dz1TdqQryRefCols_clone(Dz1TdqQryRefCols *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRefCols_purge(Dz1TdqQryRefCols *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRefCols_del(Dz1TdqQryRefCols *p);
static __inline__ void Dz1TdqQryRefCols_delAndSetNull(void *ptr)
{
	Dz1TdqQryRefCols **p = (Dz1TdqQryRefCols **)ptr;
	if (p != NULL) { Dz1TdqQryRefCols_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQryRefCols_dump(Dz1TdqQryRefCols *p, int tab);

// Dz1TdqQryRefCols
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblJoin
typedef enum Dz1TdqQueryTblJoin
{
	Dz1TdqQueryTblJoin_inner,
	Dz1TdqQueryTblJoin_left,
	Dz1TdqQueryTblJoin_right,
	Dz1TdqQueryTblJoin_outer,
	Dz1TdqQueryTblJoin_max
} Dz1TdqQueryTblJoin;

DZ1_CPPLINK str_t Dz1TdqQueryTblJoinStrA(Dz1TdqQueryTblJoin v);
DZ1_CPPLINK Dz1TdqQueryTblJoin Dz1TdqQueryTblJoinFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqQueryTblJoinStrW(Dz1TdqQueryTblJoin v);
DZ1_CPPLINK Dz1TdqQueryTblJoin Dz1TdqQueryTblJoinFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqQueryTblJoinStr Dz1TdqQueryTblJoinStrW
#define Dz1TdqQueryTblJoinFromStr Dz1TdqQueryTblJoinFromStrW
#else // UNICODE
#define Dz1TdqQueryTblJoinStr Dz1TdqQueryTblJoinStrA
#define Dz1TdqQueryTblJoinFromStr Dz1TdqQueryTblJoinFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqQueryTblJoinStr Dz1TdqQueryTblJoinStrA
#define Dz1TdqQueryTblJoinFromStr Dz1TdqQueryTblJoinFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblJoin *Dz1TdqQueryTblJoin_new(Dz1TdqQueryTblJoin *src, Dz1Error *err);
static __inline__ Dz1TdqQueryTblJoin *Dz1TdqQueryTblJoin_gen(Dz1Error *err) { Dz1TdqQueryTblJoin v = Dz1TdqQueryTblJoin_max; return Dz1TdqQueryTblJoin_new(&v, err); }
static __inline__ void Dz1TdqQueryTblJoin_del(Dz1TdqQueryTblJoin *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqQueryTblJoin_delAndSetNull(void *ptr)
{
	Dz1TdqQueryTblJoin **p = (Dz1TdqQueryTblJoin **)ptr;
	if (p != NULL) { Dz1TdqQueryTblJoin_del(*p); *p = NULL; }
}
// Dz1TdqQueryTblJoin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblName
typedef struct Dz1TdqQueryTblName
{
	Dz1TdqTblInstance		*instance;
	Dz1Str					 alias;
} Dz1TdqQueryTblName;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblName *Dz1TdqQueryTblName_new(Dz1TdqTblInstance *instance_ref, 
																   Dz1Str alias, Dz1Error *err);
static __inline__ Dz1TdqQueryTblName *Dz1TdqQueryTblName_gen(Dz1Error *err) { return Dz1TdqQueryTblName_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQueryTblName_copy(Dz1TdqQueryTblName *dst, Dz1TdqQueryTblName *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblName *Dz1TdqQueryTblName_clone(Dz1TdqQueryTblName *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblName_purge(Dz1TdqQueryTblName *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblName_del(Dz1TdqQueryTblName *p);
static __inline__ void Dz1TdqQueryTblName_delAndSetNull(void *ptr)
{
	Dz1TdqQueryTblName **p = (Dz1TdqQueryTblName **)ptr;
	if (p) { Dz1TdqQueryTblName_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblName_dump(Dz1TdqQueryTblName *p, int tab);
// Dz1TdqQueryTblName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblEntry
typedef struct Dz1TdqQueryTblEntry
{
	Dz1TdqQueryTblName		*tbl;
	Dz1TdqQueryTblJoin		 mode;
	Dz1Str					 match_on;
} Dz1TdqQueryTblEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblEntry *Dz1TdqQueryTblEntry_new(Dz1TdqQueryTblName *tbl, 
																	 Dz1TdqQueryTblJoin mode, 
																	 Dz1Str match_on, Dz1Error *err);
static __inline__ Dz1TdqQueryTblEntry *Dz1TdqQueryTblEntry_gen(Dz1Error *err) { return Dz1TdqQueryTblEntry_new(NULL, Dz1TdqQueryTblJoin_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQueryTblEntry_copy(Dz1TdqQueryTblEntry *dst, Dz1TdqQueryTblEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblEntry *Dz1TdqQueryTblEntry_clone(Dz1TdqQueryTblEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblEntry_purge(Dz1TdqQueryTblEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblEntry_del(Dz1TdqQueryTblEntry *p);
static __inline__ void Dz1TdqQueryTblEntry_delAndSetNull(void *ptr)
{
	Dz1TdqQueryTblEntry **p = (Dz1TdqQueryTblEntry **)ptr;
	if (p) { Dz1TdqQueryTblEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblEntry_dump(Dz1TdqQueryTblEntry *p, int tab);
// Dz1TdqQueryTblEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblSeq
typedef struct Dz1TdqQueryTblSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqQueryTblSeq *p);
	Dz1Error (*travel)(struct Dz1TdqQueryTblSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqQueryTblEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqQueryTblSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqQueryTblEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqQueryTblSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqQueryTblEntry *entry), void *ptr);
	Dz1TdqQueryTblEntry **(*get_array)(struct Dz1TdqQueryTblSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqQueryTblSeq *p, Dz1TdqQueryTblEntry *data);
} Dz1TdqQueryTblSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblSeq *Dz1TdqQueryTblSeq_new(Dz1Error *err);
static __inline__ Dz1TdqQueryTblSeq *Dz1TdqQueryTblSeq_gen(Dz1Error *err) { return Dz1TdqQueryTblSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblSeq *Dz1TdqQueryTblSeq_clone(Dz1TdqQueryTblSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSeq_purge(Dz1TdqQueryTblSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSeq_del(Dz1TdqQueryTblSeq *p);
static __inline__ void Dz1TdqQueryTblSeq_delAndSetNull(void *ptr)
{
	Dz1TdqQueryTblSeq **p = (Dz1TdqQueryTblSeq **)ptr;
	if (p != NULL) { Dz1TdqQueryTblSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSeq_dump(Dz1TdqQueryTblSeq *p, int tab);

// Dz1TdqQueryTblSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryTblSpec
typedef struct Dz1TdqQueryTblSpec
{
	Dz1TdqQueryTblName		*basis;
	Dz1TdqQueryTblSeq		*join_tbls;
} Dz1TdqQueryTblSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblSpec *Dz1TdqQueryTblSpec_new(Dz1TdqQueryTblName *basis, Dz1Error *err);
static __inline__ Dz1TdqQueryTblSpec *Dz1TdqQueryTblSpec_gen(Dz1Error *err) { return Dz1TdqQueryTblSpec_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQueryTblSpec_copy(Dz1TdqQueryTblSpec *dst, Dz1TdqQueryTblSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryTblSpec *Dz1TdqQueryTblSpec_clone(Dz1TdqQueryTblSpec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSpec_purge(Dz1TdqQueryTblSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSpec_del(Dz1TdqQueryTblSpec *p);
static __inline__ void Dz1TdqQueryTblSpec_delAndSetNull(void *ptr)
{
	Dz1TdqQueryTblSpec **p = (Dz1TdqQueryTblSpec **)ptr;
	if (p) { Dz1TdqQueryTblSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryTblSpec_dump(Dz1TdqQueryTblSpec *p, int tab);
// Dz1TdqQueryTblSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQuery
typedef struct Dz1TdqQuery
{
	Dz1Str					 name;
	Dz1TdqQryRow			*sel;
	Dz1TdqQueryTblSpec		*from;
	Dz1TdqQryRefCols		*groupby;
} Dz1TdqQuery;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQuery *Dz1TdqQuery_new(Dz1Str name, 
													 Dz1TdqQryRow *sel, 
													 Dz1TdqQueryTblSpec *from, Dz1Error *err);
static __inline__ Dz1TdqQuery *Dz1TdqQuery_gen(Dz1Error *err) { return Dz1TdqQuery_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqQuery_copy(Dz1TdqQuery *dst, Dz1TdqQuery *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQuery *Dz1TdqQuery_clone(Dz1TdqQuery *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQuery_purge(Dz1TdqQuery *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQuery_del(Dz1TdqQuery *p);
static __inline__ void Dz1TdqQuery_delAndSetNull(void *ptr)
{
	Dz1TdqQuery **p = (Dz1TdqQuery **)ptr;
	if (p) { Dz1TdqQuery_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQuery_dump(Dz1TdqQuery *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqQuery_cmp(Dz1TdqQuery *a, Dz1TdqQuery *b); 
// Dz1TdqQuery
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqQueryList
typedef struct Dz1TdqQueryList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqQueryList *p);
	Dz1Error (*travel)(struct Dz1TdqQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqQuery *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqQuery *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqQueryList *p, Dz1Error (*func)(void *ptr, Dz1TdqQuery *entry), void *ptr);
	Dz1TdqQuery **(*get_array)(struct Dz1TdqQueryList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqQueryList *p, Dz1TdqQuery *data);
	bool_t (*remove)(struct Dz1TdqQueryList *p, Dz1TdqQuery *key);
	Dz1TdqQuery *(*extract)(struct Dz1TdqQueryList *p, Dz1TdqQuery *key);
	Dz1TdqQuery *(*find)(struct Dz1TdqQueryList *p, Dz1TdqQuery *key);
	int (*cmp)(Dz1TdqQuery *a, Dz1TdqQuery *b);
} Dz1TdqQueryList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryList *Dz1TdqQueryList_new(Dz1Error *err);
static __inline__ Dz1TdqQueryList *Dz1TdqQueryList_gen(Dz1Error *err) { return Dz1TdqQueryList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqQueryList *Dz1TdqQueryList_clone(Dz1TdqQueryList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryList_purge(Dz1TdqQueryList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryList_del(Dz1TdqQueryList *p);
static __inline__ void Dz1TdqQueryList_delAndSetNull(void *ptr)
{
	Dz1TdqQueryList **p = (Dz1TdqQueryList **)ptr;
	if (p != NULL) { Dz1TdqQueryList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqQueryList_dump(Dz1TdqQueryList *p, int tab);

// Dz1TdqQueryList
////////////////////////////////////////////////////////////////////////////////

#endif
