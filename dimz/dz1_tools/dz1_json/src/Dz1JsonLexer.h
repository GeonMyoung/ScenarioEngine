#ifndef DZ1_JSON_LEX_H_LOCAL
#define DZ1_JSON_LEX_H_LOCAL

#include "Dz1JsonStructDef.h"

DZ1_CPPLINK Dz1JsonLexer	*Dz1JsonLexer_create(Dz1Error *err);
DZ1_CPPLINK Dz1JsonToken	*Dz1JsonLexer_get(Dz1JsonLexer *p, Dz1JsonFifo *fifo, Dz1Error *err);
DZ1_CPPLINK void			 Dz1JsonLexer_consume(Dz1JsonLexer *p);
static __inline__ void		_Dz1JsonLexer_consume(void *ptr)
{
	Dz1JsonLexer *p = (Dz1JsonLexer *)ptr;
	Dz1JsonLexer_consume(p);
}


#endif
