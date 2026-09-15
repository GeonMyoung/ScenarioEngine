#ifndef DZ1_PARSER_TOKEN_LOCAL_H
#define DZ1_PARSER_TOKEN_LOCAL_H

#include <dz1_error.h>
#include <dz1_parser_token.h>

typedef char	Dz1ParserTokenTypeStr[32];
DZ1_CPPLINK str_t Dz1ParserToken_typeStr(Dz1ParserTokenTypeStr str, u32_t type);

#define Dz1ParserToken_new(t, v, err)	_Dz1ParserToken_new(t, v, err, __FILE__, __LINE__)
DZ1_CPPLINK Dz1ParserToken *_Dz1ParserToken_new(u32_t tokenType, str_t tokenValue, Dz1Error *err, const char *__file, int __line__);
DZ1_CPPLINK void Dz1ParserToken_del(Dz1ParserToken *);
DZ1_CPPLINK void Dz1ParserToken_dump(Dz1ParserToken *p, int tab);
static __inline__ void Dz1ParserToken_DelAndSetNull(void *ptr)
{
	Dz1ParserToken **p = (Dz1ParserToken **)ptr;
	Dz1ParserToken_del(*p); *p = NULL;
}

#endif
