#ifndef _DZ1_TDC_DZ1_ASN1_STRUCT_H_
#define _DZ1_TDC_DZ1_ASN1_STRUCT_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// DummyStruct
typedef struct DummyStruct
{
	u32_t		dumb;
} DummyStruct;

DZ1_CPPLINK DZ1_DLLPORT DummyStruct *DummyStruct_new(u32_t dumb, Dz1Error *err);
static __inline__ DummyStruct *DummyStruct_gen(Dz1Error *err) { return DummyStruct_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void DummyStruct_purge(DummyStruct *p);
DZ1_CPPLINK DZ1_DLLPORT void DummyStruct_del(DummyStruct *p);
static __inline__ void DummyStruct_delAndSetNull(void *ptr)
{
	DummyStruct **p = (DummyStruct **)ptr;
	if (p) { DummyStruct_del(*p); *p = NULL; }
}
// DummyStruct
////////////////////////////////////////////////////////////////////////////////

#endif
