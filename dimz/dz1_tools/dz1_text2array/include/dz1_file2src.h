#ifndef DZ1_TEXT2ARRAY_H
#define DZ1_TEXT2ARRAY_H

#include <dz1_file2src_arg.h>

#define DZ1_FILE2SRC_OUTPUT_HEADER			0x00000001
#define DZ1_FILE2SRC_OUTPUT_SOURCE			0x00000002
#define DZ1_FILE2SRC_OUTPUT_HEADER_STATIC	0x00000004

DZ1_CPPLINK Dz1Error Dz1File2Src_convert(File2SrcConvArg *arg, u32_t output_opt);

#endif
