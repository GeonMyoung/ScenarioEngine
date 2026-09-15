#ifndef DZ1_PARSER_LOCAL_H
#define DZ1_PARSER_LOCAL_H

#include <dz1_parser.h>
#include "dz1_parser_syntax.h"
#include "dz1_parser_emiter.h"
#include "dz1_parser_lexer.h"

#define DZ1_PARSE_STATUS_SUCCESS			1
#define DZ1_PARSE_STATUS_FAIL			0
#define DZ1_PARSE_STATUS_OMIT			-1

typedef struct StackTrace
{
	struct StackTrace	*prev;
	str_t				 current;
} StackTrace;
#define StackTrace_initializer(syntax_name)		{ NULL, syntax_name }

typedef struct Dz1Parser
{
	Dz1ParserLexer *lexer;

	void *syntax;

	StackTrace *trace;

	Dz1Error (*addSyntax)(struct Dz1Parser *, Dz1ParserSyntaxEntry *e);
	Dz1ParserSyntaxEntry *(*findSyntax)(struct Dz1Parser *p, str_t name);

	void *emiter;
	Dz1Error (*emit)(struct Dz1Parser *p, str_t emit_name, Dz1ParserToken *t, void *param);
} Dz1Parser;

#endif
