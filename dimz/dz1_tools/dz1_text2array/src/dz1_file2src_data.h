#ifndef _DZ1_TDC_DZ1_FILE2SRC_DATA_H_
#define _DZ1_TDC_DZ1_FILE2SRC_DATA_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcDataEntry
typedef struct Dz1File2SrcDataEntry
{
	Dz1Binary		*block;
} Dz1File2SrcDataEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1File2SrcDataEntry *Dz1File2SrcDataEntry_new(Dz1Binary *block, Dz1Error *err);
static __inline__ Dz1File2SrcDataEntry *Dz1File2SrcDataEntry_gen(Dz1Error *err) { return Dz1File2SrcDataEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataEntry_purge(Dz1File2SrcDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataEntry_del(Dz1File2SrcDataEntry *p);
static __inline__ void Dz1File2SrcDataEntry_delAndSetNull(void *ptr)
{
	Dz1File2SrcDataEntry **p = (Dz1File2SrcDataEntry **)ptr;
	if (p) { Dz1File2SrcDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataEntry_dump(Dz1File2SrcDataEntry *p, int tab);
// Dz1File2SrcDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcDataList
typedef struct Dz1File2SrcDataList
{
	void *storage;
	unsigned int (*count)(struct Dz1File2SrcDataList *p);
	Dz1Error (*travel)(struct Dz1File2SrcDataList *p, Dz1Error (*func)(void *ptr, Dz1File2SrcDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1File2SrcDataList *p, Dz1Error (*func)(void *ptr, Dz1File2SrcDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1File2SrcDataList *p, Dz1Error (*func)(void *ptr, Dz1File2SrcDataEntry *entry), void *ptr);
	Dz1File2SrcDataEntry **(*get_array)(struct Dz1File2SrcDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1File2SrcDataList *p, Dz1File2SrcDataEntry *data);
	Dz1File2SrcDataEntry *(*getHead)(struct Dz1File2SrcDataList *p);
} Dz1File2SrcDataList;

DZ1_CPPLINK DZ1_DLLPORT Dz1File2SrcDataList *Dz1File2SrcDataList_new(Dz1Error *err);
static __inline__ Dz1File2SrcDataList *Dz1File2SrcDataList_gen(Dz1Error *err) { return Dz1File2SrcDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataList_purge(Dz1File2SrcDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataList_del(Dz1File2SrcDataList *p);
static __inline__ void Dz1File2SrcDataList_delAndSetNull(void *ptr)
{
	Dz1File2SrcDataList **p = (Dz1File2SrcDataList **)ptr;
	if (p != NULL) { Dz1File2SrcDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcDataList_dump(Dz1File2SrcDataList *p, int tab);

// Dz1File2SrcDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1File2SrcData
typedef struct Dz1File2SrcData
{
	Dz1File2SrcDataList		*list;
} Dz1File2SrcData;

DZ1_CPPLINK DZ1_DLLPORT Dz1File2SrcData *Dz1File2SrcData_new(Dz1Error *err);
static __inline__ Dz1File2SrcData *Dz1File2SrcData_gen(Dz1Error *err) { return Dz1File2SrcData_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcData_purge(Dz1File2SrcData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcData_del(Dz1File2SrcData *p);
static __inline__ void Dz1File2SrcData_delAndSetNull(void *ptr)
{
	Dz1File2SrcData **p = (Dz1File2SrcData **)ptr;
	if (p) { Dz1File2SrcData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1File2SrcData_dump(Dz1File2SrcData *p, int tab);
// Dz1File2SrcData
////////////////////////////////////////////////////////////////////////////////

#endif
