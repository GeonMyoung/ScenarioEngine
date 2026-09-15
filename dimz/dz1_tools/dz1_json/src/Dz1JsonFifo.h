#ifndef DZ1_JSON_FIFO_H_LOCAL
#define DZ1_JSON_FIFO_H_LOCAL

#include "Dz1JsonStructDef.h"
#include <Dz1JsonDef.h>

DZ1_CPPLINK Dz1JsonFifo *Dz1JsonFifo_create(str_t ingress_charset, Dz1Error *err);

// > 0 : src를 사용한 바이트 수, < 0 error
DZ1_CPPLINK ssize_t Dz1JsonFifo_ingress(Dz1JsonFifo *dst, u8_t *src, size_t sz, Dz1Error *err);

DZ1_CPPLINK int Dz1JsonFifoA_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err);
DZ1_CPPLINK int Dz1JsonFifoW_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err);
DZ1_CPPLINK int Dz1JsonFifoU8_getC(Dz1JsonFifo *src, SingleChar *ret_c, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1JsonFifo_ungetC(Dz1JsonFifo *dst, u32_t c, Dz1Error *err);

#endif
