#ifndef DZ1_MDEFC_EMIT_UTIL_H_LOCAL
#define DZ1_MDEFC_EMIT_UTIL_H_LOCAL

#include <Dz1TdcInfoModule.h>

DZ1_CPPLINK ObjectInfo	*_emit_util_resolve_type(FORWARD_TYPE *_fwd, str_t type_name, int _is_ptr, str_t memb, u32_t memb_flags, ObjectInfo *papa, Dz1MdefcModule *module, Dz1Error *err);

#endif
