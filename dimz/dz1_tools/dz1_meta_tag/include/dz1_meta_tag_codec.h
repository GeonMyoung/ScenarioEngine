#ifndef DZ1_META_TAG_CODEC_H
#define DZ1_META_TAG_CODEC_H

#include <dz1_meta_tag_def.h>

DZ1_CPPLINK Dz1MetaTagValue *Dz1MetaTagValue_gen(Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData
DZ1_CPPLINK Dz1MetaTagData		*Dz1MetaTagData_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1MetaTagData_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1MetaTagData_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1Binary			*Dz1MetaTagData_toStream(Dz1MetaTagData *src, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagData		*Dz1MetaTagData_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// Dz1MetaTagData
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaSingleTagList
//DZ1_CPPLINK ssize_t					 Dz1MetaSingleTagList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
//DZ1_CPPLINK	ssize_t					 Dz1MetaSingleTagList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

//DZ1_CPPLINK Dz1Binary				*Dz1MetaSingleTagList_toStream(Dz1MetaSingleTagList *src, void *param, Dz1Error *err);
//DZ1_CPPLINK Dz1MetaSingleTagList	*Dz1MetaSingleTagList_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// Dz1MetaSingleTagList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataList
DZ1_CPPLINK Dz1MetaTagDataList	*Dz1MetaTagDataList_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1MetaTagDataList_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t				 Dz1MetaTagDataList_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);
// Dz1MetaTagDataList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList
DZ1_CPPLINK Dz1Binary			*Dz1MetaTagDescrList_toStream(Dz1MetaTagDescrList *src, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrList *Dz1MetaTagDescrList_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// Dz1MetaTagDescrList
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB
DZ1_CPPLINK Dz1Binary			*Dz1MetaTagDB_toStream(Dz1MetaTagDB *src, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDB		*Dz1MetaTagDB_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// Dz1MetaTagDB
///////////////////////////////////////////////////////////////////////////////

#endif