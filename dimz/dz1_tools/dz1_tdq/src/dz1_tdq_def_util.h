#ifndef DZ1_TDQ_DEF_UTIL_H_LOCAL
#define DZ1_TDQ_DEF_UTIL_H_LOCAL

#include "dz1_tdq_util.h"
#include <dz1_tdq.h>

DZ1_CPPLINK Dz1TdqTblInstance	*Dz1TdqDbScheme_findInstance(Dz1TdqDbScheme *p, Dz1Str name);
DZ1_CPPLINK Dz1TdqQuery			*Dz1TdqDbScheme_findQuery(Dz1TdqDbScheme *p, Dz1Str name);

#endif
