#ifndef DZ1_TDC_INFO_CONSTANT_H
#define DZ1_TDC_INFO_CONSTANT_H

#include "Dz1TdcInfoCommon.h"

typedef struct ConstantInfo
{
	str_t					value;
} ConstantInfo;

DZ1_CPPLINK ConstantInfo *ConstantInfo_new(str_t value, Dz1Error *err);
DZ1_CPPLINK ConstantInfo *ConstantInfo_clone(ConstantInfo *src, Dz1Error *err);
DZ1_CPPLINK void ConstantInfo_del(ConstantInfo *p);
static __inline__ void ConstantInfo_delAndSetNull(void *pptr)
{
	ConstantInfo **p = (ConstantInfo **)pptr;
	ConstantInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK void ConstantInfo_dump(ConstantInfo *p, int tab);

DZ1_CPPLINK ConstantInfo *ConstantInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t ConstantInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t ConstantInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
