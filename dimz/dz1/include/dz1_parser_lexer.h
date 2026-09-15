#ifndef DZ1_PARSER_LEXER_H
#define DZ1_PARSER_LEXER_H

#include "dz1_parser_token.h"

#define DZ1_PARSER_LEX_MAX_SEGMENT		65535


typedef struct Dz1ParserLexer
{
	str_t			 source;
	u32_t			 lineNumber;
	char			 buf[DZ1_PARSER_LEX_MAX_SEGMENT];
	Dz1ParserToken	*current;
	Dz1Error		 (*lex)(struct Dz1ParserLexer *p, const char *__file__, int __line__);

	Dz1Error		 (*setSrc)(struct Dz1ParserLexer *, str_t text);

	u32_t			 (*getLineNum)(struct Dz1ParserLexer *p);
	void			 (*setLineNum)(struct Dz1ParserLexer *p, u32_t num);
} Dz1ParserLexer;

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserLexer *Dz1ParserLexer_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserLexer_del(Dz1ParserLexer *p);
#define Dz1ParserLexer_lex(lexerp)		(lexerp)->lex((lexerp), __FILE__, __LINE__)
#endif
