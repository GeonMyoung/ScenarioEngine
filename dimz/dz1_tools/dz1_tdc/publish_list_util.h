#ifndef _PUBLISH_LIST_UTIL_H_LOCAL_
#define _PUBLISH_LIST_UTIL_H_LOCAL_

#include <Dz1TdcInfoPublishSpec.h>
#include <Dz1TdcInfoObject.h>

DZ1_CPPLINK bool_t ListType_header_typedef(FILE *fp, str_t tn, ArrayType at, u32_t a_api, bool_t elem_fwd, ObjectInfo *elem, bool_t e_cmp, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t ListType_header(FILE *fp, str_t tn, ArrayType a_type, u32_t t_api, u32_t l_api, ObjectInfo *elem, bool_t elem_is_fwd, bool_t elem_has_cmp, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_add(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_remove(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_extract(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_array(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_travel(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_find(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_getHead(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_getTail(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_count(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, PublishSpec *s, int tab);

DZ1_CPPLINK void ListType_source_newApi(FILE *fp, str_t tn, ArrayType a_type, u32_t a_api, str_t e_cmp_fn, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_clone(FILE *fp, str_t tn, ArrayType a_type, ObjectInfo *elem, bool_t elem_is_ref, PublishSpec *s, int tab);
DZ1_CPPLINK void ListType_source_del(FILE *fp, str_t tn, ArrayType a_type, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t ListType_source_dump(FILE *fp, str_t tn, ArrayType a_type, u32_t a_api, str_t dumpPrefix, ObjectInfo *elem, PublishSpec *s, int tab);

#endif
