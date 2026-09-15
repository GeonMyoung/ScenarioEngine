#ifndef DZ1_MDEFC_MODULE_H
#define DZ1_MDEFC_MODULE_H

#include <dz1_error.h>

#include <dz1_fifo.h>
#include <dz1_aatree.h>
#include <Dz1TdcInfoIncludeSpec.h>

#include "Dz1TdcInfoPublishSpec.h"
#include "Dz1TdcInfoObject.h"

typedef enum ModuleIncludeStatus
{
	ModuleIncludeStatus_included,
	ModuleIncludeStatus_referenced,
	ModuleIncludeStatus_natived
} ModuleIncludeStatus;

typedef struct Dz1MdefcModule
{
	str_t					 name;
	str_t					 ext;
	ModuleIncludeStatus		 includeStatus;
	// bool_t					 is_loaded;

	Dz1AATree				*moduleTree;						// included module

	Dz1Fifo					*objFifo;							// objects in sequence
	Dz1AATree				*objTree;							// objects in name indexed

	Dz1AATree				*objUnknown;

	EnumEntry				*(*findEnum)(struct Dz1MdefcModule *p, str_t name);

	Dz1Error				 (*addModule)(struct Dz1MdefcModule *p, struct Dz1MdefcModule *m);
	struct Dz1MdefcModule	*(*findModule)(struct Dz1MdefcModule *p, str_t name);

	Dz1Error				 (*addObject)(struct Dz1MdefcModule *p, ObjectInfo *o);
	ObjectInfo				*(*findObject)(struct Dz1MdefcModule *p, str_t name);

	ObjectInfo				*(*regUnknownObject)(struct Dz1MdefcModule *p, str_t name, Dz1Error *err);
	ObjectInfo				*(*findUnknownObject)(struct Dz1MdefcModule *p, str_t name, Dz1Error *err);
	ObjectInfo				*(*extractUnknownObject)(struct Dz1MdefcModule *p, str_t name, Dz1Error *err);
} Dz1MdefcModule;

DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_new(str_t name, str_t ext, PublishSpec *spec, Dz1Error *err);
DZ1_CPPLINK void			 Dz1MdefcModule_del(Dz1MdefcModule *p);
DZ1_CPPLINK void			 Dz1MdefcModule_dump(Dz1MdefcModule *p, int tab);
static __inline__ void		 Dz1MdefcModule_delAndSetNull(void *ptr)
{
	Dz1MdefcModule **p = (Dz1MdefcModule **)ptr;
	Dz1MdefcModule_del(*p); *p = NULL;
}
DZ1_CPPLINK int				 Dz1MdefcModule_cmp(Dz1MdefcModule *a, Dz1MdefcModule *b);

DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t			 Dz1MdefcModule_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t			 Dz1MdefcModule_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_load1(str_t fn, Dz1Error *err);
DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_load2(str_t path, str_t name_ext, Dz1Error *err);
DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_load3(str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK Dz1MdefcModule	*Dz1MdefcModule_iload(str_t path[], u32_t cnt, str_t name, Dz1Error *err);
DZ1_CPPLINK Dz1Error		 Dz1MdefcModule_save(Dz1MdefcModule *p, str_t path, str_t name);

DZ1_CPPLINK bool_t			 Dz1MdefcModule_isUnknownExist(Dz1MdefcModule *p);
DZ1_CPPLINK Dz1Error		 Dz1MdefcModule_fixupDefinedEnums(Dz1MdefcModule *p);

//DZ1_CPPLINK Dz1Error		 Dz1MdefcModule_import(Dz1MdefcModule *p, IncludeSpec *inc);

DZ1_CPPLINK void			 Dz1MdefcModule_tdc(FILE *fp, Dz1MdefcModule *module, PublishSpec *sp);

#endif
