#ifndef _DZ1_TDC_DZ1_TJSONC_DEF_H_
#define _DZ1_TDC_DZ1_TJSONC_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1TdcInfoObject.h"

////////////////////////////////////////////////////////////////////////////////
// ObjectInfoIndex
typedef struct ObjectInfoIndex
{
	void *storage;
	unsigned int (*count)(struct ObjectInfoIndex *p);
	Dz1Error (*travel)(struct ObjectInfoIndex *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct ObjectInfoIndex *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ObjectInfoIndex *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	ObjectInfo **(*get_array)(struct ObjectInfoIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ObjectInfoIndex *p, ObjectInfo *data);
	bool_t (*remove)(struct ObjectInfoIndex *p, ObjectInfo *key);
	ObjectInfo *(*extract)(struct ObjectInfoIndex *p, ObjectInfo *key);
	ObjectInfo *(*find)(struct ObjectInfoIndex *p, ObjectInfo *key);
	int (*cmp)(ObjectInfo *a, ObjectInfo *b);
} ObjectInfoIndex;

DZ1_CPPLINK DZ1_DLLPORT ObjectInfoIndex *ObjectInfoIndex_new(Dz1Error *err);
static __inline__ ObjectInfoIndex *ObjectInfoIndex_gen(Dz1Error *err) { return ObjectInfoIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ObjectInfoIndex *ObjectInfoIndex_clone(ObjectInfoIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoIndex_purge(ObjectInfoIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoIndex_del(ObjectInfoIndex *p);
static __inline__ void ObjectInfoIndex_delAndSetNull(void *ptr)
{
	ObjectInfoIndex **p = (ObjectInfoIndex **)ptr;
	if (p != NULL) { ObjectInfoIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoIndex_dump(ObjectInfoIndex *p, int tab);

// ObjectInfoIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ObjectInfoSeq
typedef struct ObjectInfoSeq
{
	void *storage;
	unsigned int (*count)(struct ObjectInfoSeq *p);
	Dz1Error (*travel)(struct ObjectInfoSeq *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct ObjectInfoSeq *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ObjectInfoSeq *p, Dz1Error (*func)(void *ptr, ObjectInfo *entry), void *ptr);
	ObjectInfo **(*get_array)(struct ObjectInfoSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ObjectInfoSeq *p, ObjectInfo *data);
	int (*cmp)(ObjectInfo *a, ObjectInfo *b);
} ObjectInfoSeq;

DZ1_CPPLINK DZ1_DLLPORT ObjectInfoSeq *ObjectInfoSeq_new(Dz1Error *err);
static __inline__ ObjectInfoSeq *ObjectInfoSeq_gen(Dz1Error *err) { return ObjectInfoSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ObjectInfoSeq *ObjectInfoSeq_clone(ObjectInfoSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoSeq_purge(ObjectInfoSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoSeq_del(ObjectInfoSeq *p);
static __inline__ void ObjectInfoSeq_delAndSetNull(void *ptr)
{
	ObjectInfoSeq **p = (ObjectInfoSeq **)ptr;
	if (p != NULL) { ObjectInfoSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ObjectInfoSeq_dump(ObjectInfoSeq *p, int tab);

// ObjectInfoSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonTargetObjects
typedef struct Dz1JsonTargetObjects
{
	ObjectInfoIndex		*index;
	ObjectInfoSeq		*seq;
} Dz1JsonTargetObjects;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonTargetObjects *Dz1JsonTargetObjects_new(Dz1Error *err);
static __inline__ Dz1JsonTargetObjects *Dz1JsonTargetObjects_gen(Dz1Error *err) { return Dz1JsonTargetObjects_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonTargetObjects_purge(Dz1JsonTargetObjects *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonTargetObjects_del(Dz1JsonTargetObjects *p);
static __inline__ void Dz1JsonTargetObjects_delAndSetNull(void *ptr)
{
	Dz1JsonTargetObjects **p = (Dz1JsonTargetObjects **)ptr;
	if (p) { Dz1JsonTargetObjects_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonTargetObjects_dump(Dz1JsonTargetObjects *p, int tab);
// Dz1JsonTargetObjects
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncIndex
typedef struct Dz1JsonCompileIncIndex
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonCompileIncIndex *p);
	Dz1Error (*travel)(struct Dz1JsonCompileIncIndex *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonCompileIncIndex *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonCompileIncIndex *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Str *(*get_array)(struct Dz1JsonCompileIncIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonCompileIncIndex *p, Dz1Str data);
	bool_t (*remove)(struct Dz1JsonCompileIncIndex *p, Dz1Str key);
	Dz1Str (*extract)(struct Dz1JsonCompileIncIndex *p, Dz1Str key);
	Dz1Str (*find)(struct Dz1JsonCompileIncIndex *p, Dz1Str key);
	int (*cmp)(Dz1Str a, Dz1Str b);
} Dz1JsonCompileIncIndex;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompileIncIndex *Dz1JsonCompileIncIndex_new(Dz1Error *err);
static __inline__ Dz1JsonCompileIncIndex *Dz1JsonCompileIncIndex_gen(Dz1Error *err) { return Dz1JsonCompileIncIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompileIncIndex *Dz1JsonCompileIncIndex_clone(Dz1JsonCompileIncIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncIndex_purge(Dz1JsonCompileIncIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncIndex_del(Dz1JsonCompileIncIndex *p);
static __inline__ void Dz1JsonCompileIncIndex_delAndSetNull(void *ptr)
{
	Dz1JsonCompileIncIndex **p = (Dz1JsonCompileIncIndex **)ptr;
	if (p != NULL) { Dz1JsonCompileIncIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncIndex_dump(Dz1JsonCompileIncIndex *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncIndex_fdump(FILE *fp, Dz1JsonCompileIncIndex *p, int tab);

// Dz1JsonCompileIncIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncSeq
typedef struct Dz1JsonCompileIncSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1JsonCompileIncSeq *p);
	Dz1Error (*travel)(struct Dz1JsonCompileIncSeq *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1JsonCompileIncSeq *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1JsonCompileIncSeq *p, Dz1Error (*func)(void *ptr, Dz1Str entry), void *ptr);
	Dz1Str *(*get_array)(struct Dz1JsonCompileIncSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1JsonCompileIncSeq *p, Dz1Str data);
	int (*cmp)(Dz1Str a, Dz1Str b);
} Dz1JsonCompileIncSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompileIncSeq *Dz1JsonCompileIncSeq_new(Dz1Error *err);
static __inline__ Dz1JsonCompileIncSeq *Dz1JsonCompileIncSeq_gen(Dz1Error *err) { return Dz1JsonCompileIncSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompileIncSeq *Dz1JsonCompileIncSeq_clone(Dz1JsonCompileIncSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncSeq_purge(Dz1JsonCompileIncSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncSeq_del(Dz1JsonCompileIncSeq *p);
static __inline__ void Dz1JsonCompileIncSeq_delAndSetNull(void *ptr)
{
	Dz1JsonCompileIncSeq **p = (Dz1JsonCompileIncSeq **)ptr;
	if (p != NULL) { Dz1JsonCompileIncSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncSeq_dump(Dz1JsonCompileIncSeq *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncSeq_fdump(FILE *fp, Dz1JsonCompileIncSeq *p, int tab);

// Dz1JsonCompileIncSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompileIncs
typedef struct Dz1JsonCompileIncs
{
	Dz1JsonCompileIncIndex		*index;
	Dz1JsonCompileIncSeq		*seq;
} Dz1JsonCompileIncs;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompileIncs *Dz1JsonCompileIncs_new(Dz1Error *err);
static __inline__ Dz1JsonCompileIncs *Dz1JsonCompileIncs_gen(Dz1Error *err) { return Dz1JsonCompileIncs_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncs_purge(Dz1JsonCompileIncs *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncs_del(Dz1JsonCompileIncs *p);
static __inline__ void Dz1JsonCompileIncs_delAndSetNull(void *ptr)
{
	Dz1JsonCompileIncs **p = (Dz1JsonCompileIncs **)ptr;
	if (p) { Dz1JsonCompileIncs_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompileIncs_dump(Dz1JsonCompileIncs *p, int tab);
// Dz1JsonCompileIncs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonCompilerArg
typedef struct Dz1JsonCompilerArg
{
	Dz1JsonCompileIncs		*src_module_inc;
	Dz1Str					 src_out_path;
	Dz1Str					 hdr_out_path;
	bool_t					 src_out;
	bool_t					 hdr_out;
	Dz1Str					 suffix;
	Dz1Str					 tgt_fn;
	Dz1Str					 tgt_path;
	Dz1Str					 tgt_name;
	Dz1Str					 tgt_ext;
	Dz1Str					 output_name;
} Dz1JsonCompilerArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1JsonCompilerArg *Dz1JsonCompilerArg_new(Dz1JsonCompileIncs *src_module_inc, Dz1Error *err);
static __inline__ Dz1JsonCompilerArg *Dz1JsonCompilerArg_gen(Dz1Error *err) { return Dz1JsonCompilerArg_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompilerArg_purge(Dz1JsonCompilerArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompilerArg_del(Dz1JsonCompilerArg *p);
static __inline__ void Dz1JsonCompilerArg_delAndSetNull(void *ptr)
{
	Dz1JsonCompilerArg **p = (Dz1JsonCompilerArg **)ptr;
	if (p) { Dz1JsonCompilerArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1JsonCompilerArg_dump(Dz1JsonCompilerArg *p, int tab);
// Dz1JsonCompilerArg
////////////////////////////////////////////////////////////////////////////////

#endif
