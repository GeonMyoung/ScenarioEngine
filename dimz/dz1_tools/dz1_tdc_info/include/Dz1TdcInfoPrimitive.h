#ifndef PRIMITIVE_INFO_LIST_H
#define PRIMITIVE_INFO_LIST_H

#include "dz1_error.h"
#include "Dz1TdcInfoPublishSpec.h"

typedef struct PrimitiveInfo
{
	str_t			 native;		// original defined type name
	NativeStorage	 storage;
	str_t			 prefix;		// API prefix
} PrimitiveInfo;

DZ1_CPPLINK PrimitiveInfo *PrimitiveInfo_new(str_t native, NativeStorage isPointer, str_t prefix, Dz1Error *err);
DZ1_CPPLINK void PrimitiveInfo_del(PrimitiveInfo *p);
DZ1_CPPLINK void PrimitiveInfo_dump(PrimitiveInfo *p, int tab);
static __inline__ void PrimitiveInfo_delAndSetNull(void *ptr)
{
	PrimitiveInfo **p = (PrimitiveInfo **)ptr;
	PrimitiveInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK PrimitiveInfo *PrimitiveInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t PrimitiveInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t PrimitiveInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
