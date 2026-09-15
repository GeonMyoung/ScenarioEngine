#ifndef _DZ1_TDC_DZ1_MFC_FILE_UTIL_DEF_H_
#define _DZ1_TDC_DZ1_MFC_FILE_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_stdio_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileEntry
typedef struct Dz1MfcFileEntry
{
	Dz1Str		name_ext;
	Dz1Str		name;
	Dz1Str		ext;
} Dz1MfcFileEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileEntry *Dz1MfcFileEntry_new(Dz1Str name_ext, Dz1Error *err);
static __inline__ Dz1MfcFileEntry *Dz1MfcFileEntry_gen(Dz1Error *err) { return Dz1MfcFileEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileEntry_copy(Dz1MfcFileEntry *dst, Dz1MfcFileEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileEntry *Dz1MfcFileEntry_clone(Dz1MfcFileEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileEntry_purge(Dz1MfcFileEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileEntry_del(Dz1MfcFileEntry *p);
static __inline__ void Dz1MfcFileEntry_delAndSetNull(void *ptr)
{
	Dz1MfcFileEntry **p = (Dz1MfcFileEntry **)ptr;
	if (p) { Dz1MfcFileEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileEntry_dump(Dz1MfcFileEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFileEntry_cmp(Dz1MfcFileEntry *a, Dz1MfcFileEntry *b); 
// Dz1MfcFileEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileList
typedef struct Dz1MfcFileList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileList *p);
	Dz1Error (*travel)(struct Dz1MfcFileList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileEntry *entry), void *ptr);
	Dz1MfcFileEntry **(*get_array)(struct Dz1MfcFileList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileList *p, Dz1MfcFileEntry *data);
	bool_t (*remove)(struct Dz1MfcFileList *p, Dz1MfcFileEntry *key);
	Dz1MfcFileEntry *(*extract)(struct Dz1MfcFileList *p, Dz1MfcFileEntry *key);
	Dz1MfcFileEntry *(*find)(struct Dz1MfcFileList *p, Dz1MfcFileEntry *key);
	int (*cmp)(Dz1MfcFileEntry *a, Dz1MfcFileEntry *b);
} Dz1MfcFileList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileList *Dz1MfcFileList_new(Dz1Error *err);
static __inline__ Dz1MfcFileList *Dz1MfcFileList_gen(Dz1Error *err) { return Dz1MfcFileList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileList *Dz1MfcFileList_clone(Dz1MfcFileList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileList_purge(Dz1MfcFileList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileList_del(Dz1MfcFileList *p);
static __inline__ void Dz1MfcFileList_delAndSetNull(void *ptr)
{
	Dz1MfcFileList **p = (Dz1MfcFileList **)ptr;
	if (p != NULL) { Dz1MfcFileList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileList_dump(Dz1MfcFileList *p, int tab);

// Dz1MfcFileList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperState
typedef enum Dz1MfcFileOperState
{
	Dz1MfcFileOperState_initial,
	Dz1MfcFileOperState_prepared,
	Dz1MfcFileOperState_success,
	Dz1MfcFileOperState_fail,
	Dz1MfcFileOperState_max
} Dz1MfcFileOperState;

DZ1_CPPLINK str_t Dz1MfcFileOperStateStrA(Dz1MfcFileOperState v);
DZ1_CPPLINK Dz1MfcFileOperState Dz1MfcFileOperStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MfcFileOperStateStrW(Dz1MfcFileOperState v);
DZ1_CPPLINK Dz1MfcFileOperState Dz1MfcFileOperStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MfcFileOperStateStr Dz1MfcFileOperStateStrW
#define Dz1MfcFileOperStateFromStr Dz1MfcFileOperStateFromStrW
#else // UNICODE
#define Dz1MfcFileOperStateStr Dz1MfcFileOperStateStrA
#define Dz1MfcFileOperStateFromStr Dz1MfcFileOperStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MfcFileOperStateStr Dz1MfcFileOperStateStrA
#define Dz1MfcFileOperStateFromStr Dz1MfcFileOperStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperState *Dz1MfcFileOperState_new(Dz1MfcFileOperState *src, Dz1Error *err);
static __inline__ Dz1MfcFileOperState *Dz1MfcFileOperState_gen(Dz1Error *err) { Dz1MfcFileOperState v = Dz1MfcFileOperState_max; return Dz1MfcFileOperState_new(&v, err); }
static __inline__ void Dz1MfcFileOperState_del(Dz1MfcFileOperState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MfcFileOperState_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperState **p = (Dz1MfcFileOperState **)ptr;
	if (p != NULL) { Dz1MfcFileOperState_del(*p); *p = NULL; }
}
// Dz1MfcFileOperState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteEntry
typedef struct Dz1MfcFileOperDeleteEntry
{
	Dz1Str					 path;
	Dz1MfcFileEntry			*file;
	Dz1MfcFileOperState		 state;
	s32_t					 fail_code;
} Dz1MfcFileOperDeleteEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteEntry_new(Dz1Str path, 
																				 Dz1MfcFileEntry *file, Dz1Error *err);
static __inline__ Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteEntry_gen(Dz1Error *err) { return Dz1MfcFileOperDeleteEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperDeleteEntry_copy(Dz1MfcFileOperDeleteEntry *dst, Dz1MfcFileOperDeleteEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteEntry *Dz1MfcFileOperDeleteEntry_clone(Dz1MfcFileOperDeleteEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteEntry_purge(Dz1MfcFileOperDeleteEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteEntry_del(Dz1MfcFileOperDeleteEntry *p);
static __inline__ void Dz1MfcFileOperDeleteEntry_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperDeleteEntry **p = (Dz1MfcFileOperDeleteEntry **)ptr;
	if (p) { Dz1MfcFileOperDeleteEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteEntry_dump(Dz1MfcFileOperDeleteEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFileOperDeleteEntry_cmp(Dz1MfcFileOperDeleteEntry *a, Dz1MfcFileOperDeleteEntry *b); 
// Dz1MfcFileOperDeleteEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteList
typedef struct Dz1MfcFileOperDeleteList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperDeleteList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperDeleteList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperDeleteList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperDeleteList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1MfcFileOperDeleteEntry **(*get_array)(struct Dz1MfcFileOperDeleteList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key);
	Dz1MfcFileOperDeleteEntry *(*extract)(struct Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key);
	Dz1MfcFileOperDeleteEntry *(*find)(struct Dz1MfcFileOperDeleteList *p, Dz1MfcFileOperDeleteEntry *key);
	int (*cmp)(Dz1MfcFileOperDeleteEntry *a, Dz1MfcFileOperDeleteEntry *b);
} Dz1MfcFileOperDeleteList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteList *Dz1MfcFileOperDeleteList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperDeleteList *Dz1MfcFileOperDeleteList_gen(Dz1Error *err) { return Dz1MfcFileOperDeleteList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteList *Dz1MfcFileOperDeleteList_clone(Dz1MfcFileOperDeleteList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteList_purge(Dz1MfcFileOperDeleteList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteList_del(Dz1MfcFileOperDeleteList *p);
static __inline__ void Dz1MfcFileOperDeleteList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperDeleteList **p = (Dz1MfcFileOperDeleteList **)ptr;
	if (p != NULL) { Dz1MfcFileOperDeleteList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteList_dump(Dz1MfcFileOperDeleteList *p, int tab);

// Dz1MfcFileOperDeleteList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDelRefList
typedef struct Dz1MfcFileOperDelRefList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperDelRefList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperDelRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperDelRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperDelRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperDeleteEntry *entry), void *ptr);
	Dz1MfcFileOperDeleteEntry **(*get_array)(struct Dz1MfcFileOperDelRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key);
	Dz1MfcFileOperDeleteEntry *(*extract)(struct Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key);
	Dz1MfcFileOperDeleteEntry *(*find)(struct Dz1MfcFileOperDelRefList *p, Dz1MfcFileOperDeleteEntry *key);
	int (*cmp)(Dz1MfcFileOperDeleteEntry *a, Dz1MfcFileOperDeleteEntry *b);
} Dz1MfcFileOperDelRefList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDelRefList *Dz1MfcFileOperDelRefList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperDelRefList *Dz1MfcFileOperDelRefList_gen(Dz1Error *err) { return Dz1MfcFileOperDelRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDelRefList *Dz1MfcFileOperDelRefList_clone(Dz1MfcFileOperDelRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDelRefList_purge(Dz1MfcFileOperDelRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDelRefList_del(Dz1MfcFileOperDelRefList *p);
static __inline__ void Dz1MfcFileOperDelRefList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperDelRefList **p = (Dz1MfcFileOperDelRefList **)ptr;
	if (p != NULL) { Dz1MfcFileOperDelRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDelRefList_dump(Dz1MfcFileOperDelRefList *p, int tab);

// Dz1MfcFileOperDelRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperDeleteData
typedef struct Dz1MfcFileOperDeleteData
{
	Dz1MfcFileOperDeleteList	*list;
	Dz1MfcFileOperDelRefList	*failed;
} Dz1MfcFileOperDeleteData;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteData *Dz1MfcFileOperDeleteData_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperDeleteData *Dz1MfcFileOperDeleteData_gen(Dz1Error *err) { return Dz1MfcFileOperDeleteData_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperDeleteData_copy(Dz1MfcFileOperDeleteData *dst, Dz1MfcFileOperDeleteData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperDeleteData *Dz1MfcFileOperDeleteData_clone(Dz1MfcFileOperDeleteData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteData_purge(Dz1MfcFileOperDeleteData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteData_del(Dz1MfcFileOperDeleteData *p);
static __inline__ void Dz1MfcFileOperDeleteData_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperDeleteData **p = (Dz1MfcFileOperDeleteData **)ptr;
	if (p) { Dz1MfcFileOperDeleteData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperDeleteData_dump(Dz1MfcFileOperDeleteData *p, int tab);
// Dz1MfcFileOperDeleteData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameEntry
typedef struct Dz1MfcFileOperRenameEntry
{
	Dz1MfcFileEntry			*src;
	Dz1MfcFileEntry			*dst;
	Dz1MfcFileOperState		 state;
	s32_t					 fail_code;
} Dz1MfcFileOperRenameEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameEntry_new(Dz1MfcFileEntry *src, 
																				 Dz1MfcFileEntry *dst, Dz1Error *err);
static __inline__ Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameEntry_gen(Dz1Error *err) { return Dz1MfcFileOperRenameEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperRenameEntry_copy(Dz1MfcFileOperRenameEntry *dst, Dz1MfcFileOperRenameEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameEntry_clone(Dz1MfcFileOperRenameEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameEntry_purge(Dz1MfcFileOperRenameEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameEntry_del(Dz1MfcFileOperRenameEntry *p);
static __inline__ void Dz1MfcFileOperRenameEntry_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperRenameEntry **p = (Dz1MfcFileOperRenameEntry **)ptr;
	if (p) { Dz1MfcFileOperRenameEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameEntry_dump(Dz1MfcFileOperRenameEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFileOperRenameEntry_cmp(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b); 
// Dz1MfcFileOperRenameEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameList
typedef struct Dz1MfcFileOperRenameList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperRenameList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperRenameList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperRenameList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperRenameList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1MfcFileOperRenameEntry **(*get_array)(struct Dz1MfcFileOperRenameList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*extract)(struct Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*find)(struct Dz1MfcFileOperRenameList *p, Dz1MfcFileOperRenameEntry *key);
	int (*cmp)(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b);
} Dz1MfcFileOperRenameList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameList *Dz1MfcFileOperRenameList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperRenameList *Dz1MfcFileOperRenameList_gen(Dz1Error *err) { return Dz1MfcFileOperRenameList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameList *Dz1MfcFileOperRenameList_clone(Dz1MfcFileOperRenameList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameList_purge(Dz1MfcFileOperRenameList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameList_del(Dz1MfcFileOperRenameList *p);
static __inline__ void Dz1MfcFileOperRenameList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperRenameList **p = (Dz1MfcFileOperRenameList **)ptr;
	if (p != NULL) { Dz1MfcFileOperRenameList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameList_dump(Dz1MfcFileOperRenameList *p, int tab);

// Dz1MfcFileOperRenameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenRefList
typedef struct Dz1MfcFileOperRenRefList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperRenRefList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperRenRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperRenRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperRenRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1MfcFileOperRenameEntry **(*get_array)(struct Dz1MfcFileOperRenRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*extract)(struct Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*find)(struct Dz1MfcFileOperRenRefList *p, Dz1MfcFileOperRenameEntry *key);
	int (*cmp)(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b);
} Dz1MfcFileOperRenRefList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenRefList *Dz1MfcFileOperRenRefList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperRenRefList *Dz1MfcFileOperRenRefList_gen(Dz1Error *err) { return Dz1MfcFileOperRenRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenRefList *Dz1MfcFileOperRenRefList_clone(Dz1MfcFileOperRenRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenRefList_purge(Dz1MfcFileOperRenRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenRefList_del(Dz1MfcFileOperRenRefList *p);
static __inline__ void Dz1MfcFileOperRenRefList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperRenRefList **p = (Dz1MfcFileOperRenRefList **)ptr;
	if (p != NULL) { Dz1MfcFileOperRenRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenRefList_dump(Dz1MfcFileOperRenRefList *p, int tab);

// Dz1MfcFileOperRenRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameDstIndex
typedef struct Dz1MfcFileOperRenameDstIndex
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperRenameDstIndex *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperRenameEntry *entry), void *ptr);
	Dz1MfcFileOperRenameEntry **(*get_array)(struct Dz1MfcFileOperRenameDstIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*extract)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key);
	Dz1MfcFileOperRenameEntry *(*find)(struct Dz1MfcFileOperRenameDstIndex *p, Dz1MfcFileOperRenameEntry *key);
	int (*cmp)(Dz1MfcFileOperRenameEntry *a, Dz1MfcFileOperRenameEntry *b);
} Dz1MfcFileOperRenameDstIndex;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameDstIndex *Dz1MfcFileOperRenameDstIndex_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperRenameDstIndex *Dz1MfcFileOperRenameDstIndex_gen(Dz1Error *err) { return Dz1MfcFileOperRenameDstIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameDstIndex *Dz1MfcFileOperRenameDstIndex_clone(Dz1MfcFileOperRenameDstIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameDstIndex_purge(Dz1MfcFileOperRenameDstIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameDstIndex_del(Dz1MfcFileOperRenameDstIndex *p);
static __inline__ void Dz1MfcFileOperRenameDstIndex_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperRenameDstIndex **p = (Dz1MfcFileOperRenameDstIndex **)ptr;
	if (p != NULL) { Dz1MfcFileOperRenameDstIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameDstIndex_dump(Dz1MfcFileOperRenameDstIndex *p, int tab);

// Dz1MfcFileOperRenameDstIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperRenameData
typedef struct Dz1MfcFileOperRenameData
{
	Dz1Str							 path;
	Dz1MfcFileOperRenameList		*list;
	Dz1MfcFileOperRenameDstIndex	*index;
	Dz1MfcFileOperRenRefList		*failed;
} Dz1MfcFileOperRenameData;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameData *Dz1MfcFileOperRenameData_new(Dz1Str path, Dz1Error *err);
static __inline__ Dz1MfcFileOperRenameData *Dz1MfcFileOperRenameData_gen(Dz1Error *err) { return Dz1MfcFileOperRenameData_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperRenameData_copy(Dz1MfcFileOperRenameData *dst, Dz1MfcFileOperRenameData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperRenameData *Dz1MfcFileOperRenameData_clone(Dz1MfcFileOperRenameData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameData_purge(Dz1MfcFileOperRenameData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameData_del(Dz1MfcFileOperRenameData *p);
static __inline__ void Dz1MfcFileOperRenameData_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperRenameData **p = (Dz1MfcFileOperRenameData **)ptr;
	if (p) { Dz1MfcFileOperRenameData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperRenameData_dump(Dz1MfcFileOperRenameData *p, int tab);
// Dz1MfcFileOperRenameData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyOptPresent
typedef enum Dz1MfcFileOperCopyOptPresent
{
	Dz1MfcFileOperCopyOptPresent_rename,
	Dz1MfcFileOperCopyOptPresent_overwirte,
	Dz1MfcFileOperCopyOptPresent_skip,
	Dz1MfcFileOperCopyOptPresent_max
} Dz1MfcFileOperCopyOptPresent;

DZ1_CPPLINK str_t Dz1MfcFileOperCopyOptPresentStrA(Dz1MfcFileOperCopyOptPresent v);
DZ1_CPPLINK Dz1MfcFileOperCopyOptPresent Dz1MfcFileOperCopyOptPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1MfcFileOperCopyOptPresentStrW(Dz1MfcFileOperCopyOptPresent v);
DZ1_CPPLINK Dz1MfcFileOperCopyOptPresent Dz1MfcFileOperCopyOptPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1MfcFileOperCopyOptPresentStr Dz1MfcFileOperCopyOptPresentStrW
#define Dz1MfcFileOperCopyOptPresentFromStr Dz1MfcFileOperCopyOptPresentFromStrW
#else // UNICODE
#define Dz1MfcFileOperCopyOptPresentStr Dz1MfcFileOperCopyOptPresentStrA
#define Dz1MfcFileOperCopyOptPresentFromStr Dz1MfcFileOperCopyOptPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1MfcFileOperCopyOptPresentStr Dz1MfcFileOperCopyOptPresentStrA
#define Dz1MfcFileOperCopyOptPresentFromStr Dz1MfcFileOperCopyOptPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyOptPresent *Dz1MfcFileOperCopyOptPresent_new(Dz1MfcFileOperCopyOptPresent *src, Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyOptPresent *Dz1MfcFileOperCopyOptPresent_gen(Dz1Error *err) { Dz1MfcFileOperCopyOptPresent v = Dz1MfcFileOperCopyOptPresent_max; return Dz1MfcFileOperCopyOptPresent_new(&v, err); }
#define Dz1MfcFileOperCopyOptPresent_clone             Dz1MfcFileOperCopyOptPresent_new
static __inline__ void Dz1MfcFileOperCopyOptPresent_del(Dz1MfcFileOperCopyOptPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1MfcFileOperCopyOptPresent_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyOptPresent **p = (Dz1MfcFileOperCopyOptPresent **)ptr;
	if (p != NULL) { Dz1MfcFileOperCopyOptPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyOptPresent_dump(Dz1MfcFileOperCopyOptPresent *v, int tab);
// Dz1MfcFileOperCopyOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyOpt
typedef struct Dz1MfcFileOperCopyOpt
{
	Dz1MfcFileOperCopyOptPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Str		 rename;
		u32_t		*overwirte;
		u32_t		*skip;
	} x;
} Dz1MfcFileOperCopyOpt;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyOpt *Dz1MfcFileOperCopyOpt_new(Dz1MfcFileOperCopyOptPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyOpt *Dz1MfcFileOperCopyOpt_gen(Dz1Error *err) { return Dz1MfcFileOperCopyOpt_new(Dz1MfcFileOperCopyOptPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1MfcFileOperCopyOpt_copy(Dz1MfcFileOperCopyOpt *dst, Dz1MfcFileOperCopyOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyOpt *Dz1MfcFileOperCopyOpt_clone(Dz1MfcFileOperCopyOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyOpt_purge(Dz1MfcFileOperCopyOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyOpt_del(Dz1MfcFileOperCopyOpt *p);
static __inline__ void Dz1MfcFileOperCopyOpt_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyOpt **p = (Dz1MfcFileOperCopyOpt **)ptr;
	if (p != NULL) { Dz1MfcFileOperCopyOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyOpt_dump(Dz1MfcFileOperCopyOpt *p, int tab);
// Dz1MfcFileOperCopyOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyCollision
typedef struct Dz1MfcFileOperCopyCollision
{
	u64_t		src_size;
	u64_t		dst_size;
} Dz1MfcFileOperCopyCollision;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_new(u64_t src_size, 
																					 u64_t dst_size, Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_gen(Dz1Error *err) { return Dz1MfcFileOperCopyCollision_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperCopyCollision_copy(Dz1MfcFileOperCopyCollision *dst, Dz1MfcFileOperCopyCollision *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_clone(Dz1MfcFileOperCopyCollision *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyCollision_purge(Dz1MfcFileOperCopyCollision *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyCollision_del(Dz1MfcFileOperCopyCollision *p);
static __inline__ void Dz1MfcFileOperCopyCollision_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyCollision **p = (Dz1MfcFileOperCopyCollision **)ptr;
	if (p) { Dz1MfcFileOperCopyCollision_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyCollision_dump(Dz1MfcFileOperCopyCollision *p, int tab);
// Dz1MfcFileOperCopyCollision
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyEntry
typedef struct Dz1MfcFileOperCopyEntry
{
	Dz1MfcFileEntry					*file;
	Dz1MfcFileOperCopyOpt			*opt;
	Dz1MfcFileOperState				 state;
	s32_t							 fail_code;
	Dz1MfcFileOperCopyCollision		*collision;
	s64_t							 copied;
	s64_t							 total;
} Dz1MfcFileOperCopyEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyEntry_new(Dz1MfcFileEntry *file, Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyEntry_gen(Dz1Error *err) { return Dz1MfcFileOperCopyEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperCopyEntry_copy(Dz1MfcFileOperCopyEntry *dst, Dz1MfcFileOperCopyEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyEntry *Dz1MfcFileOperCopyEntry_clone(Dz1MfcFileOperCopyEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyEntry_purge(Dz1MfcFileOperCopyEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyEntry_del(Dz1MfcFileOperCopyEntry *p);
static __inline__ void Dz1MfcFileOperCopyEntry_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyEntry **p = (Dz1MfcFileOperCopyEntry **)ptr;
	if (p) { Dz1MfcFileOperCopyEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyEntry_dump(Dz1MfcFileOperCopyEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFileOperCopyEntry_cmp(Dz1MfcFileOperCopyEntry *a, Dz1MfcFileOperCopyEntry *b); 
// Dz1MfcFileOperCopyEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyList
typedef struct Dz1MfcFileOperCopyList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperCopyList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperCopyList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperCopyList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperCopyList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1MfcFileOperCopyEntry **(*get_array)(struct Dz1MfcFileOperCopyList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key);
	Dz1MfcFileOperCopyEntry *(*extract)(struct Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key);
	Dz1MfcFileOperCopyEntry *(*find)(struct Dz1MfcFileOperCopyList *p, Dz1MfcFileOperCopyEntry *key);
	int (*cmp)(Dz1MfcFileOperCopyEntry *a, Dz1MfcFileOperCopyEntry *b);
} Dz1MfcFileOperCopyList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyList *Dz1MfcFileOperCopyList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyList *Dz1MfcFileOperCopyList_gen(Dz1Error *err) { return Dz1MfcFileOperCopyList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyList *Dz1MfcFileOperCopyList_clone(Dz1MfcFileOperCopyList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyList_purge(Dz1MfcFileOperCopyList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyList_del(Dz1MfcFileOperCopyList *p);
static __inline__ void Dz1MfcFileOperCopyList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyList **p = (Dz1MfcFileOperCopyList **)ptr;
	if (p != NULL) { Dz1MfcFileOperCopyList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyList_dump(Dz1MfcFileOperCopyList *p, int tab);

// Dz1MfcFileOperCopyList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyRefList
typedef struct Dz1MfcFileOperCopyRefList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFileOperCopyRefList *p);
	Dz1Error (*travel)(struct Dz1MfcFileOperCopyRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFileOperCopyRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFileOperCopyRefList *p, Dz1Error (*func)(void *ptr, Dz1MfcFileOperCopyEntry *entry), void *ptr);
	Dz1MfcFileOperCopyEntry **(*get_array)(struct Dz1MfcFileOperCopyRefList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *data);
	bool_t (*remove)(struct Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key);
	Dz1MfcFileOperCopyEntry *(*extract)(struct Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key);
	Dz1MfcFileOperCopyEntry *(*find)(struct Dz1MfcFileOperCopyRefList *p, Dz1MfcFileOperCopyEntry *key);
	int (*cmp)(Dz1MfcFileOperCopyEntry *a, Dz1MfcFileOperCopyEntry *b);
} Dz1MfcFileOperCopyRefList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyRefList *Dz1MfcFileOperCopyRefList_new(Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyRefList *Dz1MfcFileOperCopyRefList_gen(Dz1Error *err) { return Dz1MfcFileOperCopyRefList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyRefList *Dz1MfcFileOperCopyRefList_clone(Dz1MfcFileOperCopyRefList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyRefList_purge(Dz1MfcFileOperCopyRefList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyRefList_del(Dz1MfcFileOperCopyRefList *p);
static __inline__ void Dz1MfcFileOperCopyRefList_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyRefList **p = (Dz1MfcFileOperCopyRefList **)ptr;
	if (p != NULL) { Dz1MfcFileOperCopyRefList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyRefList_dump(Dz1MfcFileOperCopyRefList *p, int tab);

// Dz1MfcFileOperCopyRefList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyData
typedef struct Dz1MfcFileOperCopyData
{
	Dz1Str							 src_path;
	Dz1Str							 dst_path;
	Dz1MfcFileOperCopyList			*files;
	s64_t							 copied;
	s64_t							 total;
	Dz1MfcFileOperCopyRefList		*failed;
} Dz1MfcFileOperCopyData;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyData *Dz1MfcFileOperCopyData_new(Dz1Str src_path, 
																		   Dz1Str dst_path, Dz1Error *err);
static __inline__ Dz1MfcFileOperCopyData *Dz1MfcFileOperCopyData_gen(Dz1Error *err) { return Dz1MfcFileOperCopyData_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFileOperCopyData_copy(Dz1MfcFileOperCopyData *dst, Dz1MfcFileOperCopyData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFileOperCopyData *Dz1MfcFileOperCopyData_clone(Dz1MfcFileOperCopyData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyData_purge(Dz1MfcFileOperCopyData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyData_del(Dz1MfcFileOperCopyData *p);
static __inline__ void Dz1MfcFileOperCopyData_delAndSetNull(void *ptr)
{
	Dz1MfcFileOperCopyData **p = (Dz1MfcFileOperCopyData **)ptr;
	if (p) { Dz1MfcFileOperCopyData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFileOperCopyData_dump(Dz1MfcFileOperCopyData *p, int tab);
// Dz1MfcFileOperCopyData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileCopyOperCBF
typedef void (*Dz1MfcFileCopyOperCBF)(
					void *user_ptr, 
					s32_t phase, 
					s32_t phase_flag, 
					void *entry);
// Dz1MfcFileCopyOperCBF
////////////////////////////////////////////////////////////////////////////////

#endif
