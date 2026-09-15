#ifndef _DZ1_TDC_DZ1_TDQ_ROW_DEF_H_
#define _DZ1_TDC_DZ1_TDQ_ROW_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_var_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNullOpt
typedef struct Dz1TdqNullOpt
{
	Dz1Str		dflt_val;
} Dz1TdqNullOpt;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNullOpt *Dz1TdqNullOpt_new(Dz1Str dflt_val, Dz1Error *err);
static __inline__ Dz1TdqNullOpt *Dz1TdqNullOpt_gen(Dz1Error *err) { return Dz1TdqNullOpt_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqNullOpt_copy(Dz1TdqNullOpt *dst, Dz1TdqNullOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNullOpt *Dz1TdqNullOpt_clone(Dz1TdqNullOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNullOpt_purge(Dz1TdqNullOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNullOpt_del(Dz1TdqNullOpt *p);
static __inline__ void Dz1TdqNullOpt_delAndSetNull(void *ptr)
{
	Dz1TdqNullOpt **p = (Dz1TdqNullOpt **)ptr;
	if (p) { Dz1TdqNullOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNullOpt_dump(Dz1TdqNullOpt *p, int tab);
// Dz1TdqNullOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumn
typedef struct Dz1TdqColumn
{
	Dz1Str					 name;
	Dz1TdqSqlTypeSpec		*sql_type;
	Dz1TdqNullOpt			*null_opt;
} Dz1TdqColumn;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumn *Dz1TdqColumn_new(Dz1Str name, 
													   Dz1TdqSqlTypeSpec *sql_type, 
													   Dz1TdqNullOpt *null_opt, Dz1Error *err);
static __inline__ Dz1TdqColumn *Dz1TdqColumn_gen(Dz1Error *err) { return Dz1TdqColumn_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqColumn_copy(Dz1TdqColumn *dst, Dz1TdqColumn *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumn *Dz1TdqColumn_clone(Dz1TdqColumn *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumn_purge(Dz1TdqColumn *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumn_del(Dz1TdqColumn *p);
static __inline__ void Dz1TdqColumn_delAndSetNull(void *ptr)
{
	Dz1TdqColumn **p = (Dz1TdqColumn **)ptr;
	if (p) { Dz1TdqColumn_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumn_dump(Dz1TdqColumn *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqColumn_cmp(Dz1TdqColumn *a, Dz1TdqColumn *b); 
// Dz1TdqColumn
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnList
typedef struct Dz1TdqColumnList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqColumnList *p);
	Dz1Error (*travel)(struct Dz1TdqColumnList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqColumnList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqColumnList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1TdqColumn **(*get_array)(struct Dz1TdqColumnList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqColumnList *p, Dz1TdqColumn *data);
	bool_t (*remove)(struct Dz1TdqColumnList *p, Dz1TdqColumn *key);
	Dz1TdqColumn *(*extract)(struct Dz1TdqColumnList *p, Dz1TdqColumn *key);
	Dz1TdqColumn *(*find)(struct Dz1TdqColumnList *p, Dz1TdqColumn *key);
	int (*cmp)(Dz1TdqColumn *a, Dz1TdqColumn *b);
} Dz1TdqColumnList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnList *Dz1TdqColumnList_new(Dz1Error *err);
static __inline__ Dz1TdqColumnList *Dz1TdqColumnList_gen(Dz1Error *err) { return Dz1TdqColumnList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnList *Dz1TdqColumnList_clone(Dz1TdqColumnList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnList_purge(Dz1TdqColumnList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnList_del(Dz1TdqColumnList *p);
static __inline__ void Dz1TdqColumnList_delAndSetNull(void *ptr)
{
	Dz1TdqColumnList **p = (Dz1TdqColumnList **)ptr;
	if (p != NULL) { Dz1TdqColumnList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnList_dump(Dz1TdqColumnList *p, int tab);

// Dz1TdqColumnList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefList
typedef struct Dz1TdqColumnRefList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqColumnRefList *p);
	Dz1Error (*travel)(struct Dz1TdqColumnRefList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqColumnRefList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqColumnRefList *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1TdqColumn **(*get_array)(struct Dz1TdqColumnRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqColumnRefList *p, Dz1TdqColumn *data);
	bool_t (*remove)(struct Dz1TdqColumnRefList *p, Dz1TdqColumn *key);
	Dz1TdqColumn *(*extract)(struct Dz1TdqColumnRefList *p, Dz1TdqColumn *key);
	Dz1TdqColumn *(*find)(struct Dz1TdqColumnRefList *p, Dz1TdqColumn *key);
	int (*cmp)(Dz1TdqColumn *a, Dz1TdqColumn *b);
} Dz1TdqColumnRefList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnRefList *Dz1TdqColumnRefList_new(Dz1Error *err);
static __inline__ Dz1TdqColumnRefList *Dz1TdqColumnRefList_gen(Dz1Error *err) { return Dz1TdqColumnRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnRefList *Dz1TdqColumnRefList_clone(Dz1TdqColumnRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefList_purge(Dz1TdqColumnRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefList_del(Dz1TdqColumnRefList *p);
static __inline__ void Dz1TdqColumnRefList_delAndSetNull(void *ptr)
{
	Dz1TdqColumnRefList **p = (Dz1TdqColumnRefList **)ptr;
	if (p != NULL) { Dz1TdqColumnRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefList_dump(Dz1TdqColumnRefList *p, int tab);

// Dz1TdqColumnRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnSeq
typedef struct Dz1TdqColumnSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqColumnSeq *p);
	Dz1Error (*travel)(struct Dz1TdqColumnSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqColumnSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqColumnSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1TdqColumn **(*get_array)(struct Dz1TdqColumnSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqColumnSeq *p, Dz1TdqColumn *data);
	int (*cmp)(Dz1TdqColumn *a, Dz1TdqColumn *b);
} Dz1TdqColumnSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnSeq *Dz1TdqColumnSeq_new(Dz1Error *err);
static __inline__ Dz1TdqColumnSeq *Dz1TdqColumnSeq_gen(Dz1Error *err) { return Dz1TdqColumnSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnSeq *Dz1TdqColumnSeq_clone(Dz1TdqColumnSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnSeq_purge(Dz1TdqColumnSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnSeq_del(Dz1TdqColumnSeq *p);
static __inline__ void Dz1TdqColumnSeq_delAndSetNull(void *ptr)
{
	Dz1TdqColumnSeq **p = (Dz1TdqColumnSeq **)ptr;
	if (p != NULL) { Dz1TdqColumnSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnSeq_dump(Dz1TdqColumnSeq *p, int tab);

// Dz1TdqColumnSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqColumnRefSeq
typedef struct Dz1TdqColumnRefSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqColumnRefSeq *p);
	Dz1Error (*travel)(struct Dz1TdqColumnRefSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqColumnRefSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqColumnRefSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqColumn *entry), void *ptr);
	Dz1TdqColumn **(*get_array)(struct Dz1TdqColumnRefSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqColumnRefSeq *p, Dz1TdqColumn *data);
	int (*cmp)(Dz1TdqColumn *a, Dz1TdqColumn *b);
} Dz1TdqColumnRefSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnRefSeq *Dz1TdqColumnRefSeq_new(Dz1Error *err);
static __inline__ Dz1TdqColumnRefSeq *Dz1TdqColumnRefSeq_gen(Dz1Error *err) { return Dz1TdqColumnRefSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqColumnRefSeq *Dz1TdqColumnRefSeq_clone(Dz1TdqColumnRefSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefSeq_purge(Dz1TdqColumnRefSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefSeq_del(Dz1TdqColumnRefSeq *p);
static __inline__ void Dz1TdqColumnRefSeq_delAndSetNull(void *ptr)
{
	Dz1TdqColumnRefSeq **p = (Dz1TdqColumnRefSeq **)ptr;
	if (p != NULL) { Dz1TdqColumnRefSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqColumnRefSeq_dump(Dz1TdqColumnRefSeq *p, int tab);

// Dz1TdqColumnRefSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqRow
typedef struct Dz1TdqRow
{
	Dz1TdqColumnList		*index;
	Dz1TdqColumnRefSeq		*seq;
} Dz1TdqRow;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqRow *Dz1TdqRow_new(Dz1Error *err);
static __inline__ Dz1TdqRow *Dz1TdqRow_gen(Dz1Error *err) { return Dz1TdqRow_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqRow_copy(Dz1TdqRow *dst, Dz1TdqRow *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqRow *Dz1TdqRow_clone(Dz1TdqRow *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRow_purge(Dz1TdqRow *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRow_del(Dz1TdqRow *p);
static __inline__ void Dz1TdqRow_delAndSetNull(void *ptr)
{
	Dz1TdqRow **p = (Dz1TdqRow **)ptr;
	if (p) { Dz1TdqRow_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRow_dump(Dz1TdqRow *p, int tab);
// Dz1TdqRow
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqRowRef
typedef struct Dz1TdqRowRef
{
	Dz1TdqColumnRefList		*index;
	Dz1TdqColumnRefSeq		*seq;
} Dz1TdqRowRef;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqRowRef *Dz1TdqRowRef_new(Dz1Error *err);
static __inline__ Dz1TdqRowRef *Dz1TdqRowRef_gen(Dz1Error *err) { return Dz1TdqRowRef_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqRowRef_copy(Dz1TdqRowRef *dst, Dz1TdqRowRef *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqRowRef *Dz1TdqRowRef_clone(Dz1TdqRowRef *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRowRef_purge(Dz1TdqRowRef *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRowRef_del(Dz1TdqRowRef *p);
static __inline__ void Dz1TdqRowRef_delAndSetNull(void *ptr)
{
	Dz1TdqRowRef **p = (Dz1TdqRowRef **)ptr;
	if (p) { Dz1TdqRowRef_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqRowRef_dump(Dz1TdqRowRef *p, int tab);
// Dz1TdqRowRef
////////////////////////////////////////////////////////////////////////////////

#endif
