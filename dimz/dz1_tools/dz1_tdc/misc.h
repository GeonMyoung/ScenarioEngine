#ifndef GLOBAL_MISC_DEF_H
#define GLOBAL_MISC_DEF_H

#include <dz1_error.h>
#include <Dz1TdcInfoModule.h>

static __inline__ char lower(char c)
{
	if (c >= 'A' && c <= 'Z') c = (c - 'A') + 'a';
	return c;
}

static __inline__ char upper(char c)
{
	if (c >= 'a' && c <= 'z') c = (c - 'a') + 'A';
	return c;
}

static __inline__ int isUpper(char c)
{
	if (c >= 'A' && c <= 'Z') return TRUE;
	return FALSE;
}

DZ1_CPPLINK str_t		 file_load(str_t include, str_t name, Dz1Error *err);
DZ1_CPPLINK str_t		 mkBaseName(char dst[1024], char *src);
DZ1_CPPLINK Dz1Error	 ParserHelp_addPresentObj(Dz1MdefcModule *module, ObjectInfo *obj);

DZ1_CPPLINK Dz1AATree	*Dz1TdcStringList_new(Dz1Error *err);
DZ1_CPPLINK bool_t		 Dz1TdcStringList_add(Dz1AATree *dst, Dz1Str str, Dz1Error *err);

#endif
