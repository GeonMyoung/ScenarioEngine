#ifndef EXTERN_INFO_H_LOCAL
#define EXTERN_INFO_H_LOCAL

#include <dz1_error.h>

typedef enum ExternInfoStatic
{
	ExternInfoStatic_primitive = 1,
	ExternInfoStatic_primitive_ptr = 3,
	ExternInfoStatic_typical_union,
	ExternInfoStatic_construct
} ExternInfoStatic;

typedef struct ExternInfo
{
	int			isStatic;
	str_t		prefix;
	str_t		publish_name;
	str_t		module_name;
} ExternInfo;

DZ1_CPPLINK ExternInfo *ExternInfo_new(ExternInfoStatic isStatic, str_t prefix, str_t publish_name, str_t module_name, Dz1Error *err);
DZ1_CPPLINK void ExternInfo_del(ExternInfo *p);
DZ1_CPPLINK void ExternInfo_dump(ExternInfo *p, int tab);
static __inline__ void ExternInfo_delAndSetNull(void *ptr)
{
	ExternInfo **p = (ExternInfo **)ptr;
	ExternInfo_del(*p); (*p) = NULL;
}

DZ1_CPPLINK ExternInfo *ExternInfo_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t ExternInfo_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t ExternInfo_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif

