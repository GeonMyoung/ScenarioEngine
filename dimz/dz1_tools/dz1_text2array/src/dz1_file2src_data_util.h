#ifndef DZ1_FILE2SRC_DATA_UTIL_H_LOCAL
#define DZ1_FILE2SRC_DATA_UTIL_H_LOCAL

#include "dz1_file2src_data.h"
#include <dz1_file2src_arg.h>

DZ1_CPPLINK Dz1Error Dz1File2SrcData_read(Dz1File2SrcData *dst, File2SrcConvArg *arg);

DZ1_CPPLINK Dz1Error Dz1File2Src_publishHdr(Dz1File2SrcData *src, File2SrcConvArg *arg);
DZ1_CPPLINK Dz1Error Dz1File2Src_publishSrc(Dz1File2SrcData *src, File2SrcConvArg *arg);
DZ1_CPPLINK Dz1Error Dz1File2Src_publishHdrStatic(Dz1File2SrcData *src, File2SrcConvArg *arg);

#endif