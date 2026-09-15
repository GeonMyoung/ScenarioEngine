#ifndef DZ1_PARSER_EMITER_H
#define DZ1_PARSER_EMITER_H

#include <dz1_parser.h>
#include "dz1_parser_token.h"

typedef struct Dz1ParserEmitEntry
{
	str_t name;
	Dz1ParserEmitFunc func;
} Dz1ParserEmitEntry;

DZ1_CPPLINK Dz1ParserEmitEntry *Dz1ParserEmitEntry_new(str_t name, Dz1ParserEmitFunc func, Dz1Error *err);
DZ1_CPPLINK void Dz1ParserEmitEntry_del(Dz1ParserEmitEntry *p);
DZ1_CPPLINK void Dz1ParserEmitEntry_dump(Dz1ParserEmitEntry *p, int tab);

static __inline__ void Dz1ParserEmitEntry_delAndSetNull(void *ptr)
{
	Dz1ParserEmitEntry **p = (Dz1ParserEmitEntry **)ptr;
	Dz1ParserEmitEntry_del(*p); *p = NULL;
}

#endif
