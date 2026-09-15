#ifndef DZ1_CODE_GEN_TODEC_UTIL_H
#define DZ1_CODE_GEN_TODEC_UTIL_H

#include <Dz1TdcInfoModule.h>
#include "Dz1CodeGenTodecDef.h"

#define INSTANCE_NAME_PRESENT			"@present"		// union
#define INSTANCE_NAME_COUNT				"@count"		// array
#define INSTANCE_NAME_ELEMENT			"@element"		// array
#define INSTANCE_NAME_PAD				"@pad"			// structure

///////////////////////////////////////////////////////////////////////////////
// ConstructCodec
DZ1_CPPLINK Dz1Error					 ConstructCodec_initSrc(ConstructCodec *dst);

DZ1_CPPLINK Dz1Error					 ConstructCodec_addTodecByName(ConstructCodec *p, Dz1Str name, str_t opt_suffix, bool_t is_public);
DZ1_CPPLINK Dz1Error					 ConstructCodec_addTodecByObj(ConstructCodec *p, ObjectInfo *src, str_t opt_suffix, bool_t is_public);

DZ1_CPPLINK void						 ConstructCodec_removeTodecByName(ConstructCodec *p, Dz1Str name, str_t opt_suffix);
DZ1_CPPLINK void						 ConstructCodec_removeTodecByObj(ConstructCodec *p, ObjectInfo *obj, str_t opt_suffix);

DZ1_CPPLINK Dz1Error					 ConstructCodec_resolve(ConstructCodec *dst);
// ConstructCodec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Object
DZ1_CPPLINK Dz1Error					 ConstructObjectEntry_resolve(ConstructObjectEntry *p, Dz1MdefcModule *module);
// Object
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Entry
DZ1_CPPLINK Dz1Error					 ConstructCodecEntry_resolve(ConstructCodecEntry *p, Dz1MdefcModule *module);
// CODEC Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Member List
DZ1_CPPLINK ConstructMemberCodecEntry	*ConstructMemberCodecList_findByName(ConstructMemberCodecList *list, str_t name);
// CODEC Member List
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Member Entry
DZ1_CPPLINK Dz1Error					 ConstructMemberCodecEntry_setInfo(ConstructMemberCodecEntry *dst, ConstructMemberCodecInfo *info);
DZ1_CPPLINK Dz1Error					 ConstructMemberCodecEntry_getDescript(ConstructMemberCodecEntry *p, Dz1Str endian, Dz1Str buf, size_t sz);
DZ1_CPPLINK Dz1Error					 ConstructMemberCodecEntry_resolve(ConstructMemberCodecEntry *p, Dz1MdefcModule *module);
// CODEC Member Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Individual CODEC Info
DZ1_CPPLINK Dz1Error					 ConstructMemberCodecInfo_setParent(ConstructMemberCodecInfo *p, ConstructMemberCodecEntry *entry);
// Individual CODEC Info
///////////////////////////////////////////////////////////////////////////////


#endif
