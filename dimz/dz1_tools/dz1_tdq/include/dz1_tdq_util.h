#ifndef DZ1_TDQ_UTIL_H
#define DZ1_TDQ_UTIL_H

#include <dz1_tdq_def.h>

DZ1_CPPLINK Dz1TdqSqlBlobToDB	*Dz1BinaryDB_write(Dz1Binary *src, Dz1Error *err);
DZ1_CPPLINK bool_t				 Dz1BinaryDB_read(Dz1Binary **dst, Dz1TdqSqlVar *src, Dz1Error *err);

DZ1_CPPLINK time_t				 Dz1Tdq_mktime(struct tm *p, bool_t is_gmt_tm);

#endif
