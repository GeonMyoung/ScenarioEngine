#ifndef PUBLISH_ENUM_H
#define PUBLISH_ENUM_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

DZ1_CPPLINK bool_t EnumInfo_header(		  FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, EnumInfo *p, PublishSpec *spec, int tab);
DZ1_CPPLINK bool_t EnumInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, EnumInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t EnumInfo_source(		  FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, EnumInfo *p, PublishSpec *s, int tab);

#endif
