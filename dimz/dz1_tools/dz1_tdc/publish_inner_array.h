#ifndef PUBLISH_INNER_ARRAY_H_LOCAL
#define PUBLISH_INNER_ARRAY_H_LOCAL

#include <Dz1TdcInfoObject.h>
#include <Dz1TdcInfoPublishSpec.h>

#include "publish_util.h"

typedef struct StructMemberArrayMacroAPI
{
	ObjectInstanceType	 type;
	void				 (*code)(FILE *fp, str_t tn, u32_t api, 
								 ObjectInfo *type, bool_t _is_ptr, str_t memb, u32_t memb_flag, MemberDumpMode memb_dump, 
								 str_t c_tn, bool_t c_tn_is_cond, PublishSpec *s, int tab);
} StructMemberArrayMacroAPI;
#define StructMemberArrayMacroAPI_NULL	{ ObjectInstanceType_max, NULL }

DZ1_CPPLINK StructMemberArrayMacroAPI *StructMemberArrayMacroAPI_find(ObjectInstanceType t);

DZ1_CPPLINK bool_t _array_memb_dump_code(FILE *fp, str_t tn, str_t var, str_t concat, str_t memb, str_t arr_opt, 
										 MemberDumpSpec *ds, bool_t tabbed, int tab, bool_t *_else);

#endif
