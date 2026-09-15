#ifndef SAMPLE_UTIL_H
#define SAMPLE_UTIL_H

#include <dz1_tdq_util.h>
#include "sample.h"

static __inline__ Dz1TdqSqlBlobToDB	*MyBinaryDBIO_write(Dz1Binary *src, Dz1Error *err) { return Dz1BinaryDB_write(src, err); }
static __inline__ bool_t			 MyBinaryDBIO_read(Dz1Binary **dst, Dz1TdqSqlVar *src, Dz1Error *err) { return Dz1BinaryDB_read(dst, src, err); }

DZ1_CPPLINK Dz1TdqSqlBlobToDB	*MyDataDBIO_write(MyBinData  *src, Dz1Error *err);
DZ1_CPPLINK bool_t				 MyDataDBIO_read(MyBinData **dst, Dz1TdqSqlVar *src, Dz1Error *err);

#endif
