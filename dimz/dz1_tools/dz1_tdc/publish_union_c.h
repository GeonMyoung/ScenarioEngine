#ifndef PUBLISH_UNION_C_H
#define PUBLISH_UNION_C_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

bool_t UnionInfo_header(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, UnionInfo *p, PublishSpec *s, int tab);
bool_t UnionInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, UnionInfo *p, PublishSpec *s, int tab);
bool_t UnionInfo_source(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, UnionInfo *p, PublishSpec *s, int tab);

//void UnionInfo_testHeader(FILE *fp, struct PublishSpec *spec, u32_t api, str_t name, UnionInfo *p, int tab);
//void UnionInfo_testSource(FILE *fp, struct PublishSpec *spec, u32_t api, str_t name, UnionInfo *p, int tab);

#endif
