#ifndef DEFINED_TYPE_INFO_H
#define DEFINED_TYPE_INFO_H

#include "dz1_error.h"

struct Object;

// typedef <nameof(origin)> [*]<name>;
//
// #define <name><newPostFix>				<prefixof(origin)><newPostFix>
//
//$if isClonable(origin) then
// #define <name><clonePostFix>				<prefixof(origin)><clonePostFix>
//$endif
//
// #define <name><delPostFix>				<prefixof(origin)><delPostFix>
// #define <name><delAndSetNullPostFix>		<prefixof(origin)><delAndSetNullPostFix>
// #define <name><dumpPostFix>				<prefixof(origin)><dumpPostFix>
//
//$if isComparable(origin) then
// #define <name><cmpPostFix>				<prefixof(origin)><cmpPostFix>
//$endif

typedef struct DefinedInfo
{
	int isForwarded;
	struct ObjectInfo *origin;		// Referenced
} DefinedInfo;

DZ1_CPPLINK DefinedInfo	*DefinedInfo_new(int isForwarded, struct ObjectInfo *origin, Dz1Error *err);
DZ1_CPPLINK void		 DefinedInfo_del(DefinedInfo *p);
DZ1_CPPLINK void		 DefinedInfo_dump(DefinedInfo *p, int tab);
static __inline__ void	 DefinedInfo_delAndSetNull(void *ptr)
{
	DefinedInfo **p = (DefinedInfo **)ptr;
	DefinedInfo_del(*p); *p = NULL;
}

DZ1_CPPLINK void		*DefinedInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t		 DefinedInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t		 DefinedInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
