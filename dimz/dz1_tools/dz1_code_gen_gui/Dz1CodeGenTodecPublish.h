#ifndef DZ1_CODE_GEN_TODEC_PUBLISH_H
#define DZ1_CODE_GEN_TODEC_PUBLISH_H

#include "Dz1CodeGenTodecUtil.h"

#ifdef UNIX_SYSTEM
#define NEW_LINE			"\n"
#else
#define NEW_LINE			"\r\n"
#endif
typedef struct ConstructPublishEnv
{
	str_t				 construct_name;
	str_t				 suffix;
	str_t				 endian;
} ConstructPublishEnv;

DZ1_CPPLINK s32_t _resolve_primitive_type_size(PrimitiveInfo *info);

DZ1_CPPLINK Dz1Error ConstructObjectEntry_publish_src(FILE *fp, ConstructObjectEntry *p, str_t endian, bool_t *has_public_api);
DZ1_CPPLINK Dz1Error ConstructObjectEntry_publish_hdr(FILE *fp, ConstructObjectEntry *p, str_t endian, bool_t *printed);

DZ1_CPPLINK Dz1Error ConstructCodec_publish_src(ConstructCodec *p, str_t path, str_t filename);
DZ1_CPPLINK Dz1Error ConstructCodec_publish_hdr(ConstructCodec *p, str_t path, str_t filename);

#endif