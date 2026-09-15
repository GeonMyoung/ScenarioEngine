#ifndef _DZ1_TDC_DZ1_STORAGE_DEF_H_
#define _DZ1_TDC_DZ1_STORAGE_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageChunkEntry
typedef struct Dz1StorageChunkEntry
{
	u32_t		idx;
} Dz1StorageChunkEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageChunkEntry *Dz1StorageChunkEntry_new(u32_t idx, Dz1Error *err);
static __inline__ Dz1StorageChunkEntry *Dz1StorageChunkEntry_gen(Dz1Error *err) { return Dz1StorageChunkEntry_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkEntry_purge(Dz1StorageChunkEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkEntry_del(Dz1StorageChunkEntry *p);
static __inline__ void Dz1StorageChunkEntry_delAndSetNull(void *ptr)
{
	Dz1StorageChunkEntry **p = (Dz1StorageChunkEntry **)ptr;
	if (p) { Dz1StorageChunkEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkEntry_dump(Dz1StorageChunkEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1StorageChunkEntry_cmp(Dz1StorageChunkEntry *a, Dz1StorageChunkEntry *b); 
// Dz1StorageChunkEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageChunkList
typedef struct Dz1StorageChunkList
{
	void *storage;
	unsigned int (*count)(struct Dz1StorageChunkList *p);
	Dz1Error (*travel)(struct Dz1StorageChunkList *p, Dz1Error (*func)(void *ptr, Dz1StorageChunkEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1StorageChunkList *p, Dz1Error (*func)(void *ptr, Dz1StorageChunkEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1StorageChunkList *p, Dz1Error (*func)(void *ptr, Dz1StorageChunkEntry *entry), void *ptr);
	Dz1StorageChunkEntry **(*get_array)(struct Dz1StorageChunkList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1StorageChunkList *p, Dz1StorageChunkEntry *data);
	bool_t (*remove)(struct Dz1StorageChunkList *p, Dz1StorageChunkEntry *key);
	Dz1StorageChunkEntry *(*extract)(struct Dz1StorageChunkList *p, Dz1StorageChunkEntry *key);
	Dz1StorageChunkEntry *(*find)(struct Dz1StorageChunkList *p, Dz1StorageChunkEntry *key);
	int (*cmp)(Dz1StorageChunkEntry *a, Dz1StorageChunkEntry *b);
} Dz1StorageChunkList;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageChunkList *Dz1StorageChunkList_new(Dz1Error *err);
static __inline__ Dz1StorageChunkList *Dz1StorageChunkList_gen(Dz1Error *err) { return Dz1StorageChunkList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkList_purge(Dz1StorageChunkList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkList_del(Dz1StorageChunkList *p);
static __inline__ void Dz1StorageChunkList_delAndSetNull(void *ptr)
{
	Dz1StorageChunkList **p = (Dz1StorageChunkList **)ptr;
	if (p != NULL) { Dz1StorageChunkList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageChunkList_dump(Dz1StorageChunkList *p, int tab);

// Dz1StorageChunkList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlock
typedef struct Dz1StorageBlock
{
	u32_t		idx;
	u32_t		prev_idx;
	u32_t		next_idx;
	u32_t		flag;
} Dz1StorageBlock;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageBlock *Dz1StorageBlock_new(u32_t idx, 
															 u32_t prev_idx, 
															 u32_t next_idx, 
															 u32_t flag, Dz1Error *err);
static __inline__ Dz1StorageBlock *Dz1StorageBlock_gen(Dz1Error *err) { return Dz1StorageBlock_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlock_purge(Dz1StorageBlock *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlock_del(Dz1StorageBlock *p);
static __inline__ void Dz1StorageBlock_delAndSetNull(void *ptr)
{
	Dz1StorageBlock **p = (Dz1StorageBlock **)ptr;
	if (p) { Dz1StorageBlock_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlock_dump(Dz1StorageBlock *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1StorageBlock_cmp(Dz1StorageBlock *a, Dz1StorageBlock *b); 
// Dz1StorageBlock
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlockList
typedef struct Dz1StorageBlockList
{
	void *storage;
	unsigned int (*count)(struct Dz1StorageBlockList *p);
	Dz1Error (*travel)(struct Dz1StorageBlockList *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1StorageBlockList *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1StorageBlockList *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1StorageBlock **(*get_array)(struct Dz1StorageBlockList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1StorageBlockList *p, Dz1StorageBlock *data);
	bool_t (*remove)(struct Dz1StorageBlockList *p, Dz1StorageBlock *key);
	Dz1StorageBlock *(*extract)(struct Dz1StorageBlockList *p, Dz1StorageBlock *key);
	Dz1StorageBlock *(*find)(struct Dz1StorageBlockList *p, Dz1StorageBlock *key);
	Dz1StorageBlock *(*getHead)(struct Dz1StorageBlockList *p);
	int (*cmp)(Dz1StorageBlock *a, Dz1StorageBlock *b);
} Dz1StorageBlockList;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageBlockList *Dz1StorageBlockList_new(Dz1Error *err);
static __inline__ Dz1StorageBlockList *Dz1StorageBlockList_gen(Dz1Error *err) { return Dz1StorageBlockList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockList_purge(Dz1StorageBlockList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockList_del(Dz1StorageBlockList *p);
static __inline__ void Dz1StorageBlockList_delAndSetNull(void *ptr)
{
	Dz1StorageBlockList **p = (Dz1StorageBlockList **)ptr;
	if (p != NULL) { Dz1StorageBlockList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockList_dump(Dz1StorageBlockList *p, int tab);

// Dz1StorageBlockList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageBlockArray
typedef struct Dz1StorageBlockArray
{
	void *storage;
	unsigned int (*count)(struct Dz1StorageBlockArray *p);
	Dz1Error (*travel)(struct Dz1StorageBlockArray *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1StorageBlockArray *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1StorageBlockArray *p, Dz1Error (*func)(void *ptr, Dz1StorageBlock *entry), void *ptr);
	Dz1StorageBlock **(*get_array)(struct Dz1StorageBlockArray *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1StorageBlockArray *p, Dz1StorageBlock *data);
	int (*cmp)(Dz1StorageBlock *a, Dz1StorageBlock *b);
} Dz1StorageBlockArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageBlockArray *Dz1StorageBlockArray_new(Dz1Error *err);
static __inline__ Dz1StorageBlockArray *Dz1StorageBlockArray_gen(Dz1Error *err) { return Dz1StorageBlockArray_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1StorageBlockArray *Dz1StorageBlockArray_clone(Dz1StorageBlockArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockArray_purge(Dz1StorageBlockArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockArray_del(Dz1StorageBlockArray *p);
static __inline__ void Dz1StorageBlockArray_delAndSetNull(void *ptr)
{
	Dz1StorageBlockArray **p = (Dz1StorageBlockArray **)ptr;
	if (p != NULL) { Dz1StorageBlockArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageBlockArray_dump(Dz1StorageBlockArray *p, int tab);

// Dz1StorageBlockArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageArchive
typedef struct Dz1StorageArchive
{
	u32_t					 entry_idx;
	Dz1StorageBlockArray	*blocks;
} Dz1StorageArchive;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageArchive *Dz1StorageArchive_new(u32_t entry_idx, Dz1Error *err);
static __inline__ Dz1StorageArchive *Dz1StorageArchive_gen(Dz1Error *err) { return Dz1StorageArchive_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchive_purge(Dz1StorageArchive *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchive_del(Dz1StorageArchive *p);
static __inline__ void Dz1StorageArchive_delAndSetNull(void *ptr)
{
	Dz1StorageArchive **p = (Dz1StorageArchive **)ptr;
	if (p) { Dz1StorageArchive_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchive_dump(Dz1StorageArchive *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1StorageArchive_cmp(Dz1StorageArchive *a, Dz1StorageArchive *b); 
// Dz1StorageArchive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageArchiveList
typedef struct Dz1StorageArchiveList
{
	void *storage;
	unsigned int (*count)(struct Dz1StorageArchiveList *p);
	Dz1Error (*travel)(struct Dz1StorageArchiveList *p, Dz1Error (*func)(void *ptr, Dz1StorageArchive *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1StorageArchiveList *p, Dz1Error (*func)(void *ptr, Dz1StorageArchive *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1StorageArchiveList *p, Dz1Error (*func)(void *ptr, Dz1StorageArchive *entry), void *ptr);
	Dz1StorageArchive **(*get_array)(struct Dz1StorageArchiveList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1StorageArchiveList *p, Dz1StorageArchive *data);
	bool_t (*remove)(struct Dz1StorageArchiveList *p, Dz1StorageArchive *key);
	Dz1StorageArchive *(*extract)(struct Dz1StorageArchiveList *p, Dz1StorageArchive *key);
	Dz1StorageArchive *(*find)(struct Dz1StorageArchiveList *p, Dz1StorageArchive *key);
	int (*cmp)(Dz1StorageArchive *a, Dz1StorageArchive *b);
} Dz1StorageArchiveList;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageArchiveList *Dz1StorageArchiveList_new(Dz1Error *err);
static __inline__ Dz1StorageArchiveList *Dz1StorageArchiveList_gen(Dz1Error *err) { return Dz1StorageArchiveList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchiveList_purge(Dz1StorageArchiveList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchiveList_del(Dz1StorageArchiveList *p);
static __inline__ void Dz1StorageArchiveList_delAndSetNull(void *ptr)
{
	Dz1StorageArchiveList **p = (Dz1StorageArchiveList **)ptr;
	if (p != NULL) { Dz1StorageArchiveList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageArchiveList_dump(Dz1StorageArchiveList *p, int tab);

// Dz1StorageArchiveList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageInfo
typedef struct Dz1StorageInfo
{
	Dz1StorageBlockList			*blocks;
	Dz1StorageBlockArray		*spaces;
	Dz1StorageArchiveList		*archives;
	Dz1StorageBlockArray		*missings;
	Dz1StorageBlockArray		*collisions;
} Dz1StorageInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1StorageInfo *Dz1StorageInfo_new(Dz1Error *err);
static __inline__ Dz1StorageInfo *Dz1StorageInfo_gen(Dz1Error *err) { return Dz1StorageInfo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageInfo_purge(Dz1StorageInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageInfo_del(Dz1StorageInfo *p);
static __inline__ void Dz1StorageInfo_delAndSetNull(void *ptr)
{
	Dz1StorageInfo **p = (Dz1StorageInfo **)ptr;
	if (p) { Dz1StorageInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1StorageInfo_dump(Dz1StorageInfo *p, int tab);
// Dz1StorageInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1StorageHandle
typedef void Dz1StorageHandle;

// Dz1StorageHandle
////////////////////////////////////////////////////////////////////////////////

#endif
