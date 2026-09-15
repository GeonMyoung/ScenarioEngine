#ifndef _PUBLISH_UNION_UTIL_H_LOCAL_
#define _PUBLISH_UNION_UTIL_H_LOCAL_

#include <Dz1TdcInfoPublishSpec.h>
#include <Dz1TdcInfoObject.h>

DZ1_CPPLINK bool_t UnionMemberEntry_clone_code(FILE *fp, str_t tn, str_t dst, str_t src, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
DZ1_CPPLINK void UnionMemberEntry_del_code(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t UnionMemberEntry_cmp_code(FILE *fp, str_t tn, str_t l, str_t r, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
DZ1_CPPLINK bool_t UnionMemberEntry_dump_code(FILE *fp, str_t tn, str_t var, UnionMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, int tab, bool_t *_else);

#endif
