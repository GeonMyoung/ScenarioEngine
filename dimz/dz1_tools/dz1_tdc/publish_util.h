#ifndef _PUBLISH_UTIL_H_LOCAL_
#define _PUBLISH_UTIL_H_LOCAL_

#include <Dz1TdcInfoObject.h>

#define TAB_SIZE 4

DZ1_CPPLINK bool_t			 ObjectInfo_isAddress(ObjectInfo *p);
DZ1_CPPLINK NativeStorage	 ObjectInfo_getPrimStorage(ObjectInfo *p);
DZ1_CPPLINK bool_t			 ObjectInfo_getDumpApiSticky(ObjectInfo *p, PublishSpec *sp);

DZ1_CPPLINK bool_t			 Type_header_delAndSetNull(FILE *fp, str_t tn, bool_t t_is_primptr, PublishSpec *s, int tab);

///////////////////////////////////////////////////////////////////////////////
// Member Publish API version 2
DZ1_CPPLINK void	 _memb_del_with_api(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, str_t instance, PublishSpec *s);
DZ1_CPPLINK void	 _memb_purge_with_api(FILE *fp, bool_t parent_struct, str_t var, ObjectInfo *memb, str_t instance, PublishSpec *s);
DZ1_CPPLINK bool_t	 _memb_cmp_with_api(FILE *fp, bool_t parent_struct, str_t l, str_t r, str_t _amp, ObjectInfo *memb, str_t instance, PublishSpec *s, bool_t _else);
// Member Publish API version 2
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Dump Spec
typedef struct MemberDumpSpec
{
	u32_t support_flag;
	str_t _dump;
	str_t _fprintf;
	str_t _ftprintf;
	str_t _fparg;
	str_t _AW;
	str_t _AW_origin;
	str_t _TLb;
	str_t _TLe;
} MemberDumpSpec;
DZ1_CPPLINK void MemberDumpSpec_init(MemberDumpSpec *dst, bool_t is_file_mode, int dump_mode, PublishSpec *s);
// Member Dump Spec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member Dump code publish
DZ1_CPPLINK bool_t _dump_if_ptr_null(	  FILE *fp, bool_t parent_struct,				str_t var, ObjectInfo *memb,				  str_t instance,								MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else);
DZ1_CPPLINK bool_t _dump_address(		  FILE *fp, bool_t parent_struct, str_t prefix, str_t var,									  str_t instance,								MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else);
DZ1_CPPLINK bool_t _dump_enum(			  FILE *fp, bool_t parent_struct,				str_t var, ObjectInfo *memb, bool_t memb_ptr, str_t instance,				PublishSpec *s,	MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else);
DZ1_CPPLINK bool_t _dump_using_api(		  FILE *fp, bool_t parent_struct, str_t prefix, str_t var, ObjectInfo *memb,				  str_t instance, str_t bridge, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else);
DZ1_CPPLINK void   _dump_using_linked_api(FILE *fp, bool_t parent_struct, str_t prefix, str_t var, ObjectInfo *memb,				  str_t instance, str_t bridge, PublishSpec *s, MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t _else);
// Member Dump code publish
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// for CONSTRUCT dump api
DZ1_CPPLINK void _dump_api_declare(FILE *fp, str_t tn, str_t _AW, str_t var, bool_t file_mode, PublishSpec *s, bool_t is_header, int tab);
DZ1_CPPLINK void _dump_api_header_publish(FILE *fp, str_t tn, u32_t t_api, str_t var, bool_t is_construct, PublishSpec *s, int tab);
// for CONSTRUCT dump api
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member print spec
typedef struct MemberEntryNames
{
	char					 type[512];

	char					 ptrs_memb[4];
	char					 ptrs_args[4];

	char					 name_postfix[64];
} MemberEntryNames;

DZ1_CPPLINK bool_t MemberEntryNames_get(MemberEntryNames *dst, int FORWARD_TYPE, ObjectInfo *type, bool_t _is_ptr, u32_t memb_flag, bool_t isHeader);
// Member print spec
///////////////////////////////////////////////////////////////////////////////
#endif
