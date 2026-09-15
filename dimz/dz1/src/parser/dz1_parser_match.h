#ifndef DZ1_PARSER_MATCH_H
#define DZ1_PARSER_MATCH_H

#include "dz1_parser_token.h"

#ifndef DZ1_PARSER_STRUCT
#define DZ1_PARSER_STRUCT
struct Dz1Parser;
#endif

///////////////////////////////////////////////////////////////////////////////
// Matching Element
///////////////////////////////////////////////////////////////////////////////

typedef struct Dz1ParserMatchToken
{
	int				tokenTypeOnly;
	Dz1ParserToken *tok;
} Dz1ParserMatchToken;

DZ1_CPPLINK Dz1ParserMatchToken *Dz1ParserMatchToken_new(int tokenTypeOnly, u32_t t, str_t v, Dz1Error *err);
DZ1_CPPLINK void Dz1ParserMatchToken_del(Dz1ParserMatchToken *p);
DZ1_CPPLINK void Dz1ParserMatchToken_dump(Dz1ParserMatchToken *p, int tab);
static __inline__ void Dz1ParserMatchToken_delAndSetNull(void *ptr)
{
	Dz1ParserMatchToken **p = (Dz1ParserMatchToken **)ptr;
	Dz1ParserMatchToken_del(*p); *p = NULL;
}
///////////////////////////////////////////////////////////////////////////////
// Matching Element
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
	Dz1ParserMatchUnitType_token,
	Dz1ParserMatchUnitType_syntax
} Dz1ParserMatchUnitType;

typedef struct Dz1ParserMatchUnit
{
	Dz1ParserMatchUnitType type;
	union
	{
		Dz1ParserMatchToken *token;
		str_t syntax;
	} x;
	Dz1Error (*process)(struct Dz1Parser *parser, Dz1ParserToken *t, struct Dz1ParserMatchUnit *e, str_t emit_name, void *param, int tab);
} Dz1ParserMatchUnit;

DZ1_CPPLINK Dz1ParserMatchUnit *Dz1ParserMatchUnit_newTokenMatch(int tokenTypeOnly, u32_t tokenType, str_t tokenValue, Dz1Error *err);
DZ1_CPPLINK Dz1ParserMatchUnit *Dz1ParserMatchUnit_newSyntaxIssue(str_t syntaxName, Dz1Error *err);
DZ1_CPPLINK void Dz1ParserMatchUnit_del(Dz1ParserMatchUnit *p);
DZ1_CPPLINK void Dz1ParserMatchUnit_dump(Dz1ParserMatchUnit *p, int tab);
static __inline__ void Dz1ParserMatchUnit_delAndSetNull(void *ptr)
{
	Dz1ParserMatchUnit **p = (Dz1ParserMatchUnit **)ptr;
	Dz1ParserMatchUnit_del(*p); *p = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Matching Entry
///////////////////////////////////////////////////////////////////////////////
typedef struct Dz1ParserMatchSequenceEntry
{
	str_t emit_name;
	void *oneOf; // Dz1ParserMatchUnit
	Dz1Error (*addTokenMatch)(struct Dz1ParserMatchSequenceEntry *, int tokenTypeOnly, u32_t t, str_t v);
	Dz1Error (*addSyntaxIssue)(struct Dz1ParserMatchSequenceEntry *, str_t syntaxName);
	Dz1Error (*add)(struct Dz1ParserMatchSequenceEntry *p, Dz1ParserMatchUnit *unit);
	Dz1Error (*process)(struct Dz1Parser *parse, struct Dz1ParserMatchSequenceEntry *m, void *param, int tab);
} Dz1ParserMatchSequenceEntry;

DZ1_CPPLINK Dz1ParserMatchSequenceEntry *Dz1ParserMatchSequenceEntry_new(str_t emit_name, Dz1Error *err);
DZ1_CPPLINK void Dz1ParserMatchSequenceEntry_del(Dz1ParserMatchSequenceEntry *p);
DZ1_CPPLINK void Dz1ParserMatchSequenceEntry_dump(Dz1ParserMatchSequenceEntry *p, int tab);
static __inline__ void Dz1ParserMatchSequenceEntry_delAndSetNull(void *ptr)
{
	Dz1ParserMatchSequenceEntry **p = (Dz1ParserMatchSequenceEntry **)ptr;
	Dz1ParserMatchSequenceEntry_del(*p); *p = NULL;
}
#endif
