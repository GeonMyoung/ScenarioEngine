#ifndef DZ1_JSON_CONV_H_LOCAL
#define DZ1_JSON_CONV_H_LOCAL

#include <Dz1JsonDef.h>

#ifndef	UNIX_SYSTEM
#ifdef	UNICODE
#define Dz1JsonFifo_getC		Dz1JsonFifoW_getC
#else// UNICODE
#define Dz1JsonFifo_getC		Dz1JsonFifoA_getC
#endif//UNICODE
#else// UNIX_SYSTEM
#define Dz1JsonFifo_getC		Dz1JsonFifoU8_getC
#endif


typedef void Dz1JsonConv;
DZ1_CPPLINK Dz1JsonConv *Dz1JsonConv_new(str_t dst_charset, str_t src_charset, Dz1Error *err);
DZ1_CPPLINK void Dz1JsonConv_del(Dz1JsonConv *p);
__inline__ void Dz1JsonConv_delAndSetNull(void *pptr)
{
	Dz1JsonConv **p = (Dz1JsonConv **)pptr;
	Dz1JsonConv_del(*p); *p = NULL;
}
DZ1_CPPLINK bool_t Dz1JsonConv_do(Dz1JsonConv *h, u8_t **dstp, size_t *dst_sz, u8_t **srcp, size_t *src_sz, Dz1Error *err);

typedef u32_t SingleChar;

#endif

