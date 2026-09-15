#ifndef DZ1_MDEFC_ENV_H_LOCAL
#define DZ1_MDEFC_ENV_H_LOCAL

#include <dz1_error.h>
#include <Dz1TdcInfoModule.h>
#include "misc.h"

typedef struct Dz1MdefcMacroStack
{
	struct Dz1MdefcMacroStack	*next;
	str_t						 name;
} Dz1MdefcMacroStack;

DZ1_CPPLINK Dz1MdefcMacroStack	*Dz1MdefcMacroStack_new(str_t name, Dz1Error *err);
DZ1_CPPLINK void				 Dz1MdefcMacroStack_del(Dz1MdefcMacroStack *p);
static __inline__ void			 Dz1MdefcMacroStack_delAndSetNull(void *pptr)
{
	Dz1MdefcMacroStack **p = (Dz1MdefcMacroStack **)pptr;
	if (p != NULL && *p != NULL)
	{
		Dz1MdefcMacroStack_del(*p);
		*p = NULL;
	}
}
DZ1_CPPLINK bool_t				 Dz1MdefcMacroStack_push(Dz1MdefcMacroStack **_dst, Dz1MdefcMacroStack *p, Dz1Error *err);
DZ1_CPPLINK Dz1MdefcMacroStack	*Dz1MdefcMacroStack_pop(Dz1MdefcMacroStack **_src, Dz1Error *err);


typedef struct Dz1MdefcParserEnv
{
	str_t				 filename;
	PublishSpec			*spec;
	IncludeSpec			*inc;
	Dz1MdefcModule		*module;
	ObjectInfo			*obj;

	EnumEntry			 enumEntry;
	int					 definedForwarded;

	StructMemberEntry	 structEntry;
	UnionMemberEntry	 unionEntry;
	FunctionArg			 funcArg;

	ArrayType			 arrayType;
	bool_t				 indexUnique;

	str_t				 include;

	bool_t				 boolean;

	Dz1MdefcMacroStack *macro_stk;
} Dz1MdefcParserEnv;

// Dz1MdefcParserEnv_getObject() : search name from known list, register to unknown list is not exist
DZ1_CPPLINK ObjectInfo	*Dz1MdefcParserEnv_getObject(Dz1MdefcParserEnv *p, str_t name, bool_t chkForward, Dz1Error *err);
DZ1_CPPLINK bool_t		 Dz1MdefcParserEnv_addObject(Dz1MdefcParserEnv *p, Dz1Error *err);

#endif
