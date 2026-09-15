#ifndef _DZ1_TDC_DZ1_TDQ_TBL_DEF_H_
#define _DZ1_TDC_DZ1_TDQ_TBL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_row_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexEntry
typedef struct Dz1TdqIndexEntry
{
	Dz1Str			 suffix_name;
	Dz1TdqRowRef	*own_cols;
	bool_t			 unique;
} Dz1TdqIndexEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqIndexEntry *Dz1TdqIndexEntry_new(Dz1Str suffix_name, 
															   bool_t unique, Dz1Error *err);
static __inline__ Dz1TdqIndexEntry *Dz1TdqIndexEntry_gen(Dz1Error *err) { return Dz1TdqIndexEntry_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqIndexEntry_copy(Dz1TdqIndexEntry *dst, Dz1TdqIndexEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqIndexEntry *Dz1TdqIndexEntry_clone(Dz1TdqIndexEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexEntry_purge(Dz1TdqIndexEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexEntry_del(Dz1TdqIndexEntry *p);
static __inline__ void Dz1TdqIndexEntry_delAndSetNull(void *ptr)
{
	Dz1TdqIndexEntry **p = (Dz1TdqIndexEntry **)ptr;
	if (p) { Dz1TdqIndexEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexEntry_dump(Dz1TdqIndexEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqIndexEntry_cmp(Dz1TdqIndexEntry *a, Dz1TdqIndexEntry *b); 
// Dz1TdqIndexEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqIndexList
typedef struct Dz1TdqIndexList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqIndexList *p);
	Dz1Error (*travel)(struct Dz1TdqIndexList *p, Dz1Error (*func)(void *ptr, Dz1TdqIndexEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqIndexList *p, Dz1Error (*func)(void *ptr, Dz1TdqIndexEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqIndexList *p, Dz1Error (*func)(void *ptr, Dz1TdqIndexEntry *entry), void *ptr);
	Dz1TdqIndexEntry **(*get_array)(struct Dz1TdqIndexList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqIndexList *p, Dz1TdqIndexEntry *data);
	bool_t (*remove)(struct Dz1TdqIndexList *p, Dz1TdqIndexEntry *key);
	Dz1TdqIndexEntry *(*extract)(struct Dz1TdqIndexList *p, Dz1TdqIndexEntry *key);
	Dz1TdqIndexEntry *(*find)(struct Dz1TdqIndexList *p, Dz1TdqIndexEntry *key);
	int (*cmp)(Dz1TdqIndexEntry *a, Dz1TdqIndexEntry *b);
} Dz1TdqIndexList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqIndexList *Dz1TdqIndexList_new(Dz1Error *err);
static __inline__ Dz1TdqIndexList *Dz1TdqIndexList_gen(Dz1Error *err) { return Dz1TdqIndexList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqIndexList *Dz1TdqIndexList_clone(Dz1TdqIndexList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexList_purge(Dz1TdqIndexList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexList_del(Dz1TdqIndexList *p);
static __inline__ void Dz1TdqIndexList_delAndSetNull(void *ptr)
{
	Dz1TdqIndexList **p = (Dz1TdqIndexList **)ptr;
	if (p != NULL) { Dz1TdqIndexList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqIndexList_dump(Dz1TdqIndexList *p, int tab);

// Dz1TdqIndexList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShape
typedef struct Dz1TdqTblShape
{
	Dz1Str				 name;
	Dz1TdqRow			*row;
	Dz1TdqRowRef		*pk;
	Dz1TdqIndexList		*indexes;
} Dz1TdqTblShape;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblShape *Dz1TdqTblShape_new(Dz1Str name, 
														   Dz1TdqRow *row, 
														   Dz1TdqRowRef *pk, Dz1Error *err);
static __inline__ Dz1TdqTblShape *Dz1TdqTblShape_gen(Dz1Error *err) { return Dz1TdqTblShape_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqTblShape_copy(Dz1TdqTblShape *dst, Dz1TdqTblShape *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblShape *Dz1TdqTblShape_clone(Dz1TdqTblShape *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShape_purge(Dz1TdqTblShape *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShape_del(Dz1TdqTblShape *p);
static __inline__ void Dz1TdqTblShape_delAndSetNull(void *ptr)
{
	Dz1TdqTblShape **p = (Dz1TdqTblShape **)ptr;
	if (p) { Dz1TdqTblShape_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShape_dump(Dz1TdqTblShape *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqTblShape_cmp(Dz1TdqTblShape *a, Dz1TdqTblShape *b); 
// Dz1TdqTblShape
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblShapeList
typedef struct Dz1TdqTblShapeList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqTblShapeList *p);
	Dz1Error (*travel)(struct Dz1TdqTblShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblShape *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqTblShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblShape *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqTblShapeList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblShape *entry), void *ptr);
	Dz1TdqTblShape **(*get_array)(struct Dz1TdqTblShapeList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqTblShapeList *p, Dz1TdqTblShape *data);
	bool_t (*remove)(struct Dz1TdqTblShapeList *p, Dz1TdqTblShape *key);
	Dz1TdqTblShape *(*extract)(struct Dz1TdqTblShapeList *p, Dz1TdqTblShape *key);
	Dz1TdqTblShape *(*find)(struct Dz1TdqTblShapeList *p, Dz1TdqTblShape *key);
	int (*cmp)(Dz1TdqTblShape *a, Dz1TdqTblShape *b);
} Dz1TdqTblShapeList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblShapeList *Dz1TdqTblShapeList_new(Dz1Error *err);
static __inline__ Dz1TdqTblShapeList *Dz1TdqTblShapeList_gen(Dz1Error *err) { return Dz1TdqTblShapeList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblShapeList *Dz1TdqTblShapeList_clone(Dz1TdqTblShapeList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShapeList_purge(Dz1TdqTblShapeList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShapeList_del(Dz1TdqTblShapeList *p);
static __inline__ void Dz1TdqTblShapeList_delAndSetNull(void *ptr)
{
	Dz1TdqTblShapeList **p = (Dz1TdqTblShapeList **)ptr;
	if (p != NULL) { Dz1TdqTblShapeList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblShapeList_dump(Dz1TdqTblShapeList *p, int tab);

// Dz1TdqTblShapeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameEntry
typedef struct Dz1TdqNameEntry
{
	u32_t		order;
	Dz1Str		name;
} Dz1TdqNameEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNameEntry *Dz1TdqNameEntry_new(u32_t order, 
															 Dz1Str name, Dz1Error *err);
static __inline__ Dz1TdqNameEntry *Dz1TdqNameEntry_gen(Dz1Error *err) { return Dz1TdqNameEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqNameEntry_copy(Dz1TdqNameEntry *dst, Dz1TdqNameEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNameEntry *Dz1TdqNameEntry_clone(Dz1TdqNameEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameEntry_purge(Dz1TdqNameEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameEntry_del(Dz1TdqNameEntry *p);
static __inline__ void Dz1TdqNameEntry_delAndSetNull(void *ptr)
{
	Dz1TdqNameEntry **p = (Dz1TdqNameEntry **)ptr;
	if (p) { Dz1TdqNameEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameEntry_dump(Dz1TdqNameEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqNameEntry_cmp(Dz1TdqNameEntry *a, Dz1TdqNameEntry *b); 
// Dz1TdqNameEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqNameList
typedef struct Dz1TdqNameList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqNameList *p);
	Dz1Error (*travel)(struct Dz1TdqNameList *p, Dz1Error (*func)(void *ptr, Dz1TdqNameEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqNameList *p, Dz1Error (*func)(void *ptr, Dz1TdqNameEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqNameList *p, Dz1Error (*func)(void *ptr, Dz1TdqNameEntry *entry), void *ptr);
	Dz1TdqNameEntry **(*get_array)(struct Dz1TdqNameList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqNameList *p, Dz1TdqNameEntry *data);
	bool_t (*remove)(struct Dz1TdqNameList *p, Dz1TdqNameEntry *key);
	Dz1TdqNameEntry *(*extract)(struct Dz1TdqNameList *p, Dz1TdqNameEntry *key);
	Dz1TdqNameEntry *(*find)(struct Dz1TdqNameList *p, Dz1TdqNameEntry *key);
	Dz1TdqNameEntry *(*getHead)(struct Dz1TdqNameList *p);
	Dz1TdqNameEntry *(*getTail)(struct Dz1TdqNameList *p);
	int (*cmp)(Dz1TdqNameEntry *a, Dz1TdqNameEntry *b);
} Dz1TdqNameList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNameList *Dz1TdqNameList_new(Dz1Error *err);
static __inline__ Dz1TdqNameList *Dz1TdqNameList_gen(Dz1Error *err) { return Dz1TdqNameList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqNameList *Dz1TdqNameList_clone(Dz1TdqNameList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameList_purge(Dz1TdqNameList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameList_del(Dz1TdqNameList *p);
static __inline__ void Dz1TdqNameList_delAndSetNull(void *ptr)
{
	Dz1TdqNameList **p = (Dz1TdqNameList **)ptr;
	if (p != NULL) { Dz1TdqNameList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqNameList_dump(Dz1TdqNameList *p, int tab);

// Dz1TdqNameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqForeignKeyMode
typedef enum Dz1TdqForeignKeyMode
{
	Dz1TdqForeignKeyMode_no_action,
	Dz1TdqForeignKeyMode_cascade,
	Dz1TdqForeignKeyMode_set_null,
	Dz1TdqForeignKeyMode_set_default,
	Dz1TdqForeignKeyMode_restrict,
	Dz1TdqForeignKeyMode_max
} Dz1TdqForeignKeyMode;

DZ1_CPPLINK str_t Dz1TdqForeignKeyModeStrA(Dz1TdqForeignKeyMode v);
DZ1_CPPLINK Dz1TdqForeignKeyMode Dz1TdqForeignKeyModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TdqForeignKeyModeStrW(Dz1TdqForeignKeyMode v);
DZ1_CPPLINK Dz1TdqForeignKeyMode Dz1TdqForeignKeyModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TdqForeignKeyModeStr Dz1TdqForeignKeyModeStrW
#define Dz1TdqForeignKeyModeFromStr Dz1TdqForeignKeyModeFromStrW
#else // UNICODE
#define Dz1TdqForeignKeyModeStr Dz1TdqForeignKeyModeStrA
#define Dz1TdqForeignKeyModeFromStr Dz1TdqForeignKeyModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TdqForeignKeyModeStr Dz1TdqForeignKeyModeStrA
#define Dz1TdqForeignKeyModeFromStr Dz1TdqForeignKeyModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqForeignKeyMode *Dz1TdqForeignKeyMode_new(Dz1TdqForeignKeyMode *src, Dz1Error *err);
static __inline__ Dz1TdqForeignKeyMode *Dz1TdqForeignKeyMode_gen(Dz1Error *err) { Dz1TdqForeignKeyMode v = Dz1TdqForeignKeyMode_max; return Dz1TdqForeignKeyMode_new(&v, err); }
static __inline__ void Dz1TdqForeignKeyMode_del(Dz1TdqForeignKeyMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TdqForeignKeyMode_delAndSetNull(void *ptr)
{
	Dz1TdqForeignKeyMode **p = (Dz1TdqForeignKeyMode **)ptr;
	if (p != NULL) { Dz1TdqForeignKeyMode_del(*p); *p = NULL; }
}
// Dz1TdqForeignKeyMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqFKEntry
struct Dz1TdqTblInstance;

typedef struct Dz1TdqFKEntry
{
	Dz1Str						 suffix_name;
	Dz1TdqRowRef				*own_cols;
	struct Dz1TdqTblInstance	*peer_tbl;
	Dz1Str						 peer_idx_suffix_opt;
	Dz1TdqForeignKeyMode		 on_update;
	Dz1TdqForeignKeyMode		 on_delete;
} Dz1TdqFKEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqFKEntry *Dz1TdqFKEntry_new(Dz1Str suffix_name, 
														 struct Dz1TdqTblInstance *peer_tbl_ref, 
														 Dz1Str peer_idx_suffix_opt, 
														 Dz1TdqForeignKeyMode on_update, 
														 Dz1TdqForeignKeyMode on_delete, Dz1Error *err);
static __inline__ Dz1TdqFKEntry *Dz1TdqFKEntry_gen(Dz1Error *err) { return Dz1TdqFKEntry_new(NULL, NULL, NULL, Dz1TdqForeignKeyMode_max, Dz1TdqForeignKeyMode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqFKEntry_copy(Dz1TdqFKEntry *dst, Dz1TdqFKEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqFKEntry *Dz1TdqFKEntry_clone(Dz1TdqFKEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKEntry_purge(Dz1TdqFKEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKEntry_del(Dz1TdqFKEntry *p);
static __inline__ void Dz1TdqFKEntry_delAndSetNull(void *ptr)
{
	Dz1TdqFKEntry **p = (Dz1TdqFKEntry **)ptr;
	if (p) { Dz1TdqFKEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKEntry_dump(Dz1TdqFKEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqFKEntry_cmp(Dz1TdqFKEntry *a, Dz1TdqFKEntry *b); 
// Dz1TdqFKEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqFKList
typedef struct Dz1TdqFKList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqFKList *p);
	Dz1Error (*travel)(struct Dz1TdqFKList *p, Dz1Error (*func)(void *ptr, Dz1TdqFKEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqFKList *p, Dz1Error (*func)(void *ptr, Dz1TdqFKEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqFKList *p, Dz1Error (*func)(void *ptr, Dz1TdqFKEntry *entry), void *ptr);
	Dz1TdqFKEntry **(*get_array)(struct Dz1TdqFKList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqFKList *p, Dz1TdqFKEntry *data);
	bool_t (*remove)(struct Dz1TdqFKList *p, Dz1TdqFKEntry *key);
	Dz1TdqFKEntry *(*extract)(struct Dz1TdqFKList *p, Dz1TdqFKEntry *key);
	Dz1TdqFKEntry *(*find)(struct Dz1TdqFKList *p, Dz1TdqFKEntry *key);
	int (*cmp)(Dz1TdqFKEntry *a, Dz1TdqFKEntry *b);
} Dz1TdqFKList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqFKList *Dz1TdqFKList_new(Dz1Error *err);
static __inline__ Dz1TdqFKList *Dz1TdqFKList_gen(Dz1Error *err) { return Dz1TdqFKList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqFKList *Dz1TdqFKList_clone(Dz1TdqFKList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKList_purge(Dz1TdqFKList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKList_del(Dz1TdqFKList *p);
static __inline__ void Dz1TdqFKList_delAndSetNull(void *ptr)
{
	Dz1TdqFKList **p = (Dz1TdqFKList **)ptr;
	if (p != NULL) { Dz1TdqFKList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqFKList_dump(Dz1TdqFKList *p, int tab);

// Dz1TdqFKList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstance
typedef struct Dz1TdqTblInstance
{
	Dz1Str				 name;
	Dz1TdqTblShape		*shape;
	Dz1TdqFKList		*fks;
} Dz1TdqTblInstance;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstance *Dz1TdqTblInstance_new(Dz1Str name, 
																 Dz1TdqTblShape *shape_ref, Dz1Error *err);
static __inline__ Dz1TdqTblInstance *Dz1TdqTblInstance_gen(Dz1Error *err) { return Dz1TdqTblInstance_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TdqTblInstance_copy(Dz1TdqTblInstance *dst, Dz1TdqTblInstance *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstance *Dz1TdqTblInstance_clone(Dz1TdqTblInstance *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstance_purge(Dz1TdqTblInstance *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstance_del(Dz1TdqTblInstance *p);
static __inline__ void Dz1TdqTblInstance_delAndSetNull(void *ptr)
{
	Dz1TdqTblInstance **p = (Dz1TdqTblInstance **)ptr;
	if (p) { Dz1TdqTblInstance_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstance_dump(Dz1TdqTblInstance *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TdqTblInstance_cmp(Dz1TdqTblInstance *a, Dz1TdqTblInstance *b); 
// Dz1TdqTblInstance
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstanceList
typedef struct Dz1TdqTblInstanceList
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqTblInstanceList *p);
	Dz1Error (*travel)(struct Dz1TdqTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqTblInstanceList *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1TdqTblInstance **(*get_array)(struct Dz1TdqTblInstanceList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *data);
	bool_t (*remove)(struct Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key);
	Dz1TdqTblInstance *(*extract)(struct Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key);
	Dz1TdqTblInstance *(*find)(struct Dz1TdqTblInstanceList *p, Dz1TdqTblInstance *key);
	int (*cmp)(Dz1TdqTblInstance *a, Dz1TdqTblInstance *b);
} Dz1TdqTblInstanceList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstanceList *Dz1TdqTblInstanceList_new(Dz1Error *err);
static __inline__ Dz1TdqTblInstanceList *Dz1TdqTblInstanceList_gen(Dz1Error *err) { return Dz1TdqTblInstanceList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstanceList *Dz1TdqTblInstanceList_clone(Dz1TdqTblInstanceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceList_purge(Dz1TdqTblInstanceList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceList_del(Dz1TdqTblInstanceList *p);
static __inline__ void Dz1TdqTblInstanceList_delAndSetNull(void *ptr)
{
	Dz1TdqTblInstanceList **p = (Dz1TdqTblInstanceList **)ptr;
	if (p != NULL) { Dz1TdqTblInstanceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceList_dump(Dz1TdqTblInstanceList *p, int tab);

// Dz1TdqTblInstanceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqTblInstanceSeq
typedef struct Dz1TdqTblInstanceSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1TdqTblInstanceSeq *p);
	Dz1Error (*travel)(struct Dz1TdqTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TdqTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TdqTblInstanceSeq *p, Dz1Error (*func)(void *ptr, Dz1TdqTblInstance *entry), void *ptr);
	Dz1TdqTblInstance **(*get_array)(struct Dz1TdqTblInstanceSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TdqTblInstanceSeq *p, Dz1TdqTblInstance *data);
	int (*cmp)(Dz1TdqTblInstance *a, Dz1TdqTblInstance *b);
} Dz1TdqTblInstanceSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstanceSeq *Dz1TdqTblInstanceSeq_new(Dz1Error *err);
static __inline__ Dz1TdqTblInstanceSeq *Dz1TdqTblInstanceSeq_gen(Dz1Error *err) { return Dz1TdqTblInstanceSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TdqTblInstanceSeq *Dz1TdqTblInstanceSeq_clone(Dz1TdqTblInstanceSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceSeq_purge(Dz1TdqTblInstanceSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceSeq_del(Dz1TdqTblInstanceSeq *p);
static __inline__ void Dz1TdqTblInstanceSeq_delAndSetNull(void *ptr)
{
	Dz1TdqTblInstanceSeq **p = (Dz1TdqTblInstanceSeq **)ptr;
	if (p != NULL) { Dz1TdqTblInstanceSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqTblInstanceSeq_dump(Dz1TdqTblInstanceSeq *p, int tab);

// Dz1TdqTblInstanceSeq
////////////////////////////////////////////////////////////////////////////////

#endif
