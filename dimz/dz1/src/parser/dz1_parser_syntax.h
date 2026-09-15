#ifndef DZ1_PARSER_SYNTAX_H
#define DZ1_PARSER_SYNTAX_H

#include "dz1_parser_match.h"

#ifndef DZ1_PARSER_STRUCT
#define DZ1_PARSER_STRUCT
struct Dz1Parser;
#endif

///////////////////////////////////////////////////////////////////////////////
// Syntax Processing Structure
///////////////////////////////////////////////////////////////////////////////
#define SYNTAX_MATCH_NONE				0
#define SYNTAX_MATCH_LOOP				1
#define SYNTAX_MATCH_OMITABLE			2

typedef enum
{
	Dz1ParserMatchOptType_none,			// Exactly Once Match

	Dz1ParserMatchOptType_omit,			// match or not, retuen Success

	Dz1ParserMatchOptType_loop,			// first match is not success then return Success
										// first match is success then return Success
										// After First Match, match is not success, then return Success

	Dz1ParserMatchOptType_oneLoop		// first match is Not Success then return Fail
										// first match is Success then Matching Repeat
										// After First Match, match is not success, then return Success
} Dz1ParserMatchOptType;

typedef struct Dz1ParserMatchOpt
{
	Dz1ParserMatchOptType type;
} Dz1ParserMatchOpt;

Dz1ParserMatchOpt *Dz1ParserMatchOpt_new(Dz1ParserMatchOptType type, Dz1Error *err);
void Dz1ParserMatchOpt_del(Dz1ParserMatchOpt *p);
void Dz1ParserMatchOpt_dump(Dz1ParserMatchOpt *p, int tab);
static __inline__ void Dz1ParserMatchOpt_delAndSetNull(void *ptr)
{
	Dz1ParserMatchOpt **p = (Dz1ParserMatchOpt **)ptr;
	Dz1ParserMatchOpt_del(*p); *p = NULL;
}

typedef struct Dz1ParserSyntaxEntry
{
	str_t name;

	void *seq;	// Dz1ParserMatchSequenceEntry

	void *opt;	// Dz1ParserMatchOpt

	Dz1Error (*addMatch)(struct Dz1ParserSyntaxEntry *p, Dz1ParserMatchSequenceEntry *e, Dz1ParserMatchOptType opt);

	Dz1Error (*process)(struct Dz1Parser *parser, struct Dz1ParserSyntaxEntry *s, void *param, int tab);
} Dz1ParserSyntaxEntry;

DZ1_CPPLINK Dz1ParserSyntaxEntry *Dz1ParserSyntaxEntry_new(str_t name, Dz1Error *err);
DZ1_CPPLINK void Dz1ParserSyntaxEntry_del(Dz1ParserSyntaxEntry *p);
DZ1_CPPLINK void Dz1ParserSyntaxEntry_dump(Dz1ParserSyntaxEntry *p, int tab);
static __inline__ void Dz1ParserSyntaxEntry_delAndSetNull(void *ptr)
{
	Dz1ParserSyntaxEntry **p = (Dz1ParserSyntaxEntry **)ptr;
	Dz1ParserSyntaxEntry_del(*p); *p = NULL;
}
#endif
