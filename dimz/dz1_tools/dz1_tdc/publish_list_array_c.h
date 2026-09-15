#ifndef PUBLISH_ARRAY_C_H
#define PUBLISH_ARRAY_C_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

DZ1_CPPLINK bool_t ArrayInfo_header(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, ArrayInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t ArrayInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t api, ArrayInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t ArrayInfo_source(	   FILE *fp, str_t tn, str_t tn_alt, u32_t api, ArrayInfo *p, PublishSpec *s, int tab);

// DZ1_CPPLINK void ArrayInfo_testHeader(FILE *fp, PublishSpec *spec, u32_t api, str_t name, ArrayInfo *p, int tab);
// DZ1_CPPLINK void ArrayInfo_testSource(FILE *fp, PublishSpec *spec, u32_t api, str_t name, ArrayInfo *p, int tab);

#endif
