#ifndef INCLUDE_SPEC_H
#define INCLUDE_SPEC_H

#include <dz1_error.h>

typedef struct IncludeSpec
{
	void *pathFifo;
	bool_t	 (*add)(struct IncludeSpec *p, str_t path, Dz1Error *err);
	str_t	 (*load)(struct IncludeSpec *p, str_t name, Dz1Error *err);
} IncludeSpec;

DZ1_CPPLINK IncludeSpec *IncludeSpec_new(Dz1Error *err);
DZ1_CPPLINK void IncludeSpec_del(IncludeSpec *p);
DZ1_CPPLINK void IncludeSpec_dump(IncludeSpec *p, int tab);
static __inline__ void IncludeSpec_delAndSetNull(void *ptr)
{
	IncludeSpec **p = (IncludeSpec **)ptr;
	IncludeSpec_del(*p); *p = NULL;
}

DZ1_CPPLINK u32_t IncludeSpec_count(IncludeSpec *p);
DZ1_CPPLINK str_t IncludeSpec_getPathOfFile(IncludeSpec *p, str_t fn);

#endif
