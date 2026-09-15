#ifndef DZ1_TEXT2ARRAY_H
#define DZ1_TEXT2ARRAY_H

#include <dz1_error.h>

DZ1_CPPLINK Dz1Error dz1_text2array(str_t srcFileName, str_t dstFileName, str_t varName, bool_t isStatic, bool_t isUNIX);

#endif
