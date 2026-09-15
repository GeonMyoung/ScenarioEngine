#ifndef PUBLISH_STRUCTURE_C_H
#define PUBLISH_STRUCTURE_C_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

// DZ1_CPPLINK int StructureInfo_vars(FILE *fp, StructureInfo *p, str_t instance, int comma);
//DZ1_CPPLINK int StructureInfo_args(FILE *fp, StructureInfo *p, str_t type, str_t instance, int comma);

DZ1_CPPLINK bool_t StructureInfo_header(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t StructureInfo_source(	   FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t StructureInfo_headerAsnConv(FILE *fp, str_t tn, str_t tn_alt, u32_t t_api, StructureInfo *p, PublishSpec *s, int tab);

// DZ1_CPPLINK void StructureInfo_testHeader(FILE *fp, struct PublishSpec *spec, u32_t api, str_t name, StructureInfo *p, int tab);
// DZ1_CPPLINK void StructureInfo_testSource(FILE *fp, struct PublishSpec *spec, u32_t api, str_t name, StructureInfo *p, int tab);

// DZ1_CPPLINK int StructureMemberEntry_sourceMemberCmp(FILE *fp, PublishSpec *spec, /*str_t name,*/ StructMemberEntry *p, int tab, int needElse);

#endif
