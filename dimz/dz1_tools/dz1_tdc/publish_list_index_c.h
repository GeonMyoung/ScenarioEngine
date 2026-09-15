#ifndef PUBLISH_INDEX_C_H
#define PUBLISH_INDEX_C_H

#include <Dz1TdcInfoArray.h>
#include <Dz1TdcInfoPublishSpec.h>

DZ1_CPPLINK bool_t IndexInfo_header(	   FILE *fp, str_t tn, str_t tn_ant, u32_t t_api, IndexInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t IndexInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t api, IndexInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t IndexInfo_source(	   FILE *fp, str_t tn, str_t tn_alt, u32_t api, IndexInfo *p, PublishSpec *s, int tab);

#endif