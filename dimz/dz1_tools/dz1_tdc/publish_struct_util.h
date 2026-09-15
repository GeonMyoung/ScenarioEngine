#ifndef _PUBLISH_STRUCT_UTIL_H_LOCAL_
#define _PUBLISH_STRUCT_UTIL_H_LOCAL_

#include "publish_util.h"

DZ1_CPPLINK void StructMemberEntry_default_value(FILE *fp, StructMemberEntry *p, bool_t print_comma);

DZ1_CPPLINK ssize_t StructMemberEntry_argPrint(FILE *fp, bool_t print_comma, bool_t print_nl, int front_space, StructMemberEntry *p, bool_t isHeader);

DZ1_CPPLINK bool_t StructureMemberList_args(FILE *fp, StructMemberList *p, u32_t front_space, bool_t isHeader);
DZ1_CPPLINK bool_t StructureMemberList_params(FILE *fp, StructMemberList *p);

DZ1_CPPLINK bool_t	StructMemberEntry_clone_code(	FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
DZ1_CPPLINK bool_t	StructMemberEntry_alloc_code(	FILE *fp, str_t tn, str_t dst,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);
DZ1_CPPLINK bool_t	StructMemberEntry_assign_code(	FILE *fp, str_t tn, str_t dst, str_t src, StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
DZ1_CPPLINK void	StructMemberEntry_del_code(		FILE *fp, str_t tn, str_t dst,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab);
DZ1_CPPLINK bool_t	StructMemberEntry_dump_code(	FILE *fp, str_t tn, str_t var,			  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else);
DZ1_CPPLINK bool_t	StructMemberEntry_cmp_code(		FILE *fp, str_t tn, str_t l, str_t r,	  StructMemberEntry *p, ObjectInfo *o, PublishSpec *s, int tab, bool_t *_else);

#endif
