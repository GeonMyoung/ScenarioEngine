#include <dz1_parser_init.h>

#include "../kernel/dz1_thread_stdio.h"
#include "dz1_parser.h"

// name['+']'('syntax_emiter')' = 	[[<token>[|<token>]]*=<emiter_name>]*';'
// special emiter_name "void" is mean no emiter

typedef Dz1Error (*EmitFunc)(Dz1ParserToken *t, void *user_param);

///////////////////////////////////////////////////////////////////////////////
// Match
///////////////////////////////////////////////////////////////////////////////
static Dz1ParserToken *match_skip(Dz1ParserLexer *lp, Dz1ParserToken *t, EmitFunc func, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (func && (err = func(t, param)).code != 0)
	{
		Dz1Thread_eprintf("match_skip() : Emiter Return Error\n");
		Dz1Error_print(&err, 1);
		return NULL;
	}

	if ((err = lp->lex(lp, NULL, 0)).code) { t = NULL; } else { t = lp->current; }

	return t;
}

static Dz1ParserToken *match_emit(Dz1ParserLexer *lp, Dz1ParserToken *t, u32_t type, str_t value, EmitFunc func, void *param)
{
	char want[64], income[64];
	if (t->t != type)
	{
		Dz1Thread_eprintf("match_emit() : Type Mismatch = expect(%s) : income(%s)\n", Dz1ParserToken_typeStr(want, type), Dz1ParserToken_typeStr(income, t->t));
		return NULL;
	}
	if (value && strlen(value))
	{
		if (t->v && strlen(t->v))
		{
			if (strcmp(value, t->v) != 0)
			{
				Dz1Thread_eprintf("match_emit() : Value Mismatch = %s : %s\n", value, t->v);
				return NULL;
			}
		}
		else
		{
			Dz1Thread_eprintf("match_emit() : Value Not Assigned = %s\n", value);
			return NULL;
		}
	}
	return match_skip(lp, t, func, param);
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
typedef struct MyParam
{
	Dz1Parser *parser;
	Dz1ParserMatchUnit *match_unit;
	Dz1ParserMatchSequenceEntry *sequence_entry;
	Dz1ParserMatchOptType opt;
	Dz1ParserSyntaxEntry *syntax;
} MyParam;

static void MyParam_cancel(void *ptr)
{
	MyParam *p = (MyParam *)ptr;
	if (p->match_unit) Dz1ParserMatchUnit_del(p->match_unit);
	if (p->sequence_entry) Dz1ParserMatchSequenceEntry_del(p->sequence_entry);
	if (p->syntax) Dz1ParserSyntaxEntry_del(p->syntax);
}

///////////////////////////////////////////////////////////////////////////////
// Emitter
///////////////////////////////////////////////////////////////////////////////
static u32_t get_token_type(str_t name)
{
	if (0) { }
	else if (strcmp(name, "lbracket")==0)	return DZ1_PARSER_TOKEN_LBRACKET;
	else if (strcmp(name, "rbracket")==0)	return DZ1_PARSER_TOKEN_RBRACKET;
	else if (strcmp(name, "liststart")==0)	return DZ1_PARSER_TOKEN_LISTSTART;
	else if (strcmp(name, "listend")==0)	return DZ1_PARSER_TOKEN_LISTEND;
	else if (strcmp(name, "blockstart")==0) return DZ1_PARSER_TOKEN_BLOCKSTART;
	else if (strcmp(name, "blockend")==0)	return DZ1_PARSER_TOKEN_BLOCKEND;

	else if (strcmp(name, "colon")==0)		return DZ1_PARSER_TOKEN_COLON;
	else if (strcmp(name, "assign")==0)		return DZ1_PARSER_TOKEN_ASSIGN;

	else if (strcmp(name, "equal")==0)		return DZ1_PARSER_TOKEN_EQUAL;

	else if (strcmp(name, "dot")==0)		return DZ1_PARSER_TOKEN_DOT;
	else if (strcmp(name, "dotdot")==0)		return DZ1_PARSER_TOKEN_DOTDOT;
	else if (strcmp(name, "dotdotdot")==0)	return DZ1_PARSER_TOKEN_DOTDOTDOT;

	else if (strcmp(name, "alt")==0)		return DZ1_PARSER_TOKEN_ALTERNATE;
	else if (strcmp(name, "comma")==0)		return DZ1_PARSER_TOKEN_COMMA;

	else if (strcmp(name, "less")==0)		return DZ1_PARSER_TOKEN_LESS;
	else if (strcmp(name, "greater")==0)	return DZ1_PARSER_TOKEN_GT;		// !!! previous token name is "gt"

	else if (strcmp(name, "plus")==0)		return DZ1_PARSER_TOKEN_PLUS;
	else if (strcmp(name, "minus")==0)		return DZ1_PARSER_TOKEN_MINUS;
	else if (strcmp(name, "mul")==0)		return DZ1_PARSER_TOKEN_MUL;
	else if (strcmp(name, "div")==0)		return DZ1_PARSER_TOKEN_DIV;
	else if (strcmp(name, "pow")==0)		return DZ1_PARSER_TOKEN_POW;
	else if (strcmp(name, "mod")==0)		return DZ1_PARSER_TOKEN_MOD;

	else if (strcmp(name, "bool_not")==0)	return DZ1_PARSER_TOKEN_BOOL_NOT;

	else if (strcmp(name, "bool_eq")==0)	return DZ1_PARSER_TOKEN_BOOL_EQUAL;
	else if (strcmp(name, "bool_noteq")==0)	return DZ1_PARSER_TOKEN_BOOL_NOTEQ;
	else if (strcmp(name, "bool_lt")==0)	return DZ1_PARSER_TOKEN_LESS;
	else if (strcmp(name, "bool_gt")==0)	return DZ1_PARSER_TOKEN_GT;

	else if (strcmp(name, "bool_and")==0)	return DZ1_PARSER_TOKEN_BOOL_AND;
	else if (strcmp(name, "bool_or")==0)	return DZ1_PARSER_TOKEN_BOOL_OR;

	else if (strcmp(name, "semicolon")==0)	return DZ1_PARSER_TOKEN_SEMICOLON;
	else if (strcmp(name, "and")==0)		return DZ1_PARSER_TOKEN_AND;
	else if (strcmp(name, "at")==0)			return DZ1_PARSER_TOKEN_AT;
	else if (strcmp(name, "hash")==0)		return DZ1_PARSER_TOKEN_HASH;
	else if (strcmp(name, "symbol")==0)		return DZ1_PARSER_TOKEN_SYMBOL;
	else if (strcmp(name, "literal")==0)	return DZ1_PARSER_TOKEN_LITERAL;

	// any type of number
	else if (strcmp(name, "number")==0) return DZ1_PARSER_TOKEN_NUMBER;

	// signed number
	else if (strcmp(name, "number_s")==0) return DZ1_PARSER_TOKEN_NUMBER_S(1);
	else if (strcmp(name, "number_u")==0) return DZ1_PARSER_TOKEN_NUMBER_S(0);

	// typed number
	else if (strcmp(name, "number_deci")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_DECIMAL);
	else if (strcmp(name, "number_hex")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_HEXA);
	else if (strcmp(name, "number_oct")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_OCT);
	else if (strcmp(name, "number_bin")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_BIN);
	else if (strcmp(name, "number_real")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_FLOAT);
	else if (strcmp(name, "number_exp")==0) return DZ1_PARSER_TOKEN_NUMBER_T(NUMBER_EXPONENT);

	// '+' signed typed number
	else if (strcmp(name, "number_s_deci")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_DECIMAL);
	else if (strcmp(name, "number_s_hex")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_HEXA);
	else if (strcmp(name, "number_s_oct")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_OCT);
	else if (strcmp(name, "number_s_bin")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_BIN);
	else if (strcmp(name, "number_s_real")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_FLOAT);
	else if (strcmp(name, "number_s_exp")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(1, NUMBER_EXPONENT);

	// '-' signed typed number
	else if (strcmp(name, "number_u_deci")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_DECIMAL);
	else if (strcmp(name, "number_u_hex")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_HEXA);
	else if (strcmp(name, "number_u_oct")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_OCT);
	else if (strcmp(name, "number_u_bin")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_BIN);
	else if (strcmp(name, "number_u_real")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_FLOAT);
	else if (strcmp(name, "number_u_exp")==0) return DZ1_PARSER_TOKEN_NUMBER_ST(0, NUMBER_EXPONENT);

	else if (strcmp(name, "string")==0) return DZ1_PARSER_TOKEN_STRING;
	else if (strcmp(name, "letter")==0) return DZ1_PARSER_TOKEN_LETTER;
	else if (strcmp(name, "done")==0) return DZ1_PARSER_TOKEN_DONE;

	return DZ1_PARSER_TOKEN_NONE;
}

static Dz1Error create_match(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;

	u32_t type = get_token_type(t->v);

	if (type == DZ1_PARSER_TOKEN_NONE)
	{	// Syntax Match
		p->match_unit = Dz1ParserMatchUnit_newSyntaxIssue(t->v, &err);
	}
	else
	{	// Token Match
		p->match_unit = Dz1ParserMatchUnit_newTokenMatch(TRUE, type, NULL, &err);
	}
//	Dz1Thread_eprintf("Match Created : "); Dz1ParserMatchUnit_dump(NULL, p->match_unit, 0); Dz1Thread_eprintf("\n");
	return err;
}

static Dz1Error create_symbol_match(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	p->match_unit = Dz1ParserMatchUnit_newTokenMatch(FALSE, DZ1_PARSER_TOKEN_SYMBOL, t->v, &err);
	return err;
}

static Dz1Error create_seq(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;

	if ((p->sequence_entry = Dz1ParserMatchSequenceEntry_new(NULL, &err)) == NULL) { }

	return err;
}

static Dz1Error add_match2orList(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	if ((err = p->sequence_entry->add(p->sequence_entry, p->match_unit)).code) { }
	else p->match_unit = NULL;
	return err;
}

static Dz1Error set_sequence_entry_emiter(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;

	if ((p->sequence_entry->emit_name = t->v) == NULL) { Dz1Error_set(&err, EINVAL); }
	else t->v = NULL;
	return err;
}

static Dz1Error set_omitable(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	p->opt = Dz1ParserMatchOptType_omit;
	return err;
}

static Dz1Error set_loop_one_more(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	p->opt = Dz1ParserMatchOptType_oneLoop;
	return err;
}

static Dz1Error set_loop(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	p->opt = Dz1ParserMatchOptType_loop;
	return err;
}

static Dz1Error create_syntax(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;
	if ((p->syntax = Dz1ParserSyntaxEntry_new(t->v, &err)) == NULL) { }
	return err;
}

static Dz1Error add_sequence_to_syntax(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;

//	Dz1Thread_eprintf("add_sequence_to_syntax() : Add Sequence to Syntax : ");
//	Dz1ParserMatchSequenceEntry_dump(NULL, p->sequence_entry, 0);
//	Dz1Thread_eprintf("\n");

	if ((err = p->syntax->addMatch(p->syntax, p->sequence_entry, p->opt)).code) { }
	else
	{
		p->sequence_entry = NULL;
		p->opt = Dz1ParserMatchOptType_none;
	}
	return err;
}

static Dz1Error add_syntax_to_parser(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	MyParam *p = (MyParam *)ptr;

//	Dz1Thread_eprintf("add_syntax_to_parser() : Add Syntax : ");
//	Dz1ParserSyntaxEntry_dump(NULL, p->syntax, 0);
//	Dz1Thread_eprintf("\n");

	if ((err = p->parser->addSyntax(p->parser, p->syntax)).code)
	{
		Dz1Thread_eprintf("add_syntax_to_parser() : addSyntax fail = %s\n", p->syntax->name);
		ERR_OUT(&err);
	}
	else p->syntax = NULL;
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Parsing Rule
///////////////////////////////////////////////////////////////////////////////
// token = '<' <symbol>=create_match '>'
// 			or
// 		   <symbol>=create_symbol_match
static Dz1ParserToken *Dz1Parser_parse_token(Dz1ParserLexer *lp, Dz1ParserToken *t, void *param)
{
	if (t->t == DZ1_PARSER_TOKEN_LESS)
	{
		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_LESS, NULL, NULL, param))) return NULL;
		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_SYMBOL, NULL, create_match, param))) return NULL;
		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_GT, NULL, NULL, param))) return NULL;
	}
	else if (t->t == DZ1_PARSER_TOKEN_SYMBOL)
		t = match_skip(lp, t, create_symbol_match, param);
	else
		return NULL;
	return t;
}

// tokens = <token>=add_match2orList [| <token>=add_match2orList]*
static Dz1ParserToken *Dz1Parser_parse_tokens(Dz1ParserLexer *lp, Dz1ParserToken *t, void *param)
{
	if (!(t = Dz1Parser_parse_token(lp, t, param))) return NULL;
	add_match2orList(NULL, param);

	while(t->t == DZ1_PARSER_TOKEN_ALTERNATE)
	{
		if (!(t = match_skip(lp, t, NULL, param))) return NULL;
		if (!(t = Dz1Parser_parse_token(lp, t, param))) return NULL;
		add_match2orList(NULL, param);
	}

	return t;
}

// match = <tokens> [=  <symbol>=set_emiter]
static Dz1ParserToken *Dz1Parser_parse_match(Dz1ParserLexer *lp, Dz1ParserToken *t, void *param)
{
	create_seq(NULL, param);

	if (!(t = Dz1Parser_parse_tokens(lp, t, param))) return NULL;

	if (t->t == DZ1_PARSER_TOKEN_EQUAL)
	{
		t = match_emit(lp, t, DZ1_PARSER_TOKEN_EQUAL, NULL, NULL, param);
		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_SYMBOL, NULL, set_sequence_entry_emiter, param))) return NULL;
	}

	return t;
}
// matches = '[' <matche> ']'=set_omit ['+'=set_oneloop|'*'=set_loop]
// 			 or
// 			 <match>
static Dz1ParserToken *Dz1Parser_parse_matches(Dz1ParserLexer *lp, Dz1ParserToken *t, void *param)
{
	if (t->t == DZ1_PARSER_TOKEN_BLOCKSTART)
	{
		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_BLOCKSTART, NULL, NULL, param))) return NULL;

		if (!(t = Dz1Parser_parse_match(lp, t, param))) return NULL;

		if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_BLOCKEND, NULL, set_omitable, param))) return NULL;

		if (t->t == DZ1_PARSER_TOKEN_PLUS && (t = match_emit(lp, t, DZ1_PARSER_TOKEN_PLUS, NULL, set_loop_one_more, param)) == NULL) return NULL;
		else if (t->t == DZ1_PARSER_TOKEN_MUL && (t = match_emit(lp, t, DZ1_PARSER_TOKEN_MUL, NULL, set_loop, param)) == NULL) return NULL;
	}
	else if (!(t = Dz1Parser_parse_match(lp, t, param))) return NULL;

	add_sequence_to_syntax(NULL, param);

	return t;
}

// syntax = <symbol>=create_symtax <equal> [<matches>=add_sequence_to_syntax]+ <semicolon>
static Dz1ParserToken *Dz1Parser_parse_syntax(Dz1ParserLexer *lp, Dz1ParserToken *t, void *param)
{
	if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_SYMBOL, NULL, create_syntax, param))) return NULL;
	if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_EQUAL, NULL, NULL, param))) return NULL;
	do
	{
		if (!(t = Dz1Parser_parse_matches(lp, t, param))) return NULL;
	}
	while(t->t != DZ1_PARSER_TOKEN_SEMICOLON);

	if (!(t = match_emit(lp, t, DZ1_PARSER_TOKEN_SEMICOLON, NULL, add_syntax_to_parser, param))) return NULL;
	return t;
}

// main = [<syntax>]+ <done>
static Dz1Error _Dz1ParserInit_parse(Dz1ParserLexer *lp, MyParam *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserToken *t = lp->current;

	while(t->t != DZ1_PARSER_TOKEN_DONE)
	{
		if ((t = Dz1Parser_parse_syntax(lp, t, param)) == NULL)
		{
			Dz1Error_setWithComment(&err, EFAULT, (DZ1_ERROR_ARG, "Error Occur at line %d\n", lp->getLineNum(lp) + 1));
			break;
		}
	}

	if (err.code == 0 && t != NULL && t->t != DZ1_PARSER_TOKEN_DONE) { Dz1Error_set(&err, EINVAL); }

	return err;
}

// main = [<syntax>=add_symtax]+ <done>
// syntax = <symbol>=create_symtax <equal> [<matches>=add_sequence_to_syntax]+ <semicolon>
// matches = '[' <matche> ']'=set_omit ['+'=set_oneloop|'*'=set_loop]
// 			 or
// 			 <match>
// match = <tokens> [=  <symbol>=set_emiter]
// token = '<' <symbol>=create_match '>'
// 			or
// 		   <symbol>=create_symbol_match
Dz1Error Dz1ParserInit_parse(void *parser, str_t text)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	MyParam param = { NULL, NULL, NULL, Dz1ParserMatchOptType_none, NULL };
	Dz1ParserLexer *lp = NULL;

	param.parser = (Dz1Parser *)parser;

	pthread_cleanup_push(MyParam_cancel, (void *)&param);

	if ((lp = Dz1ParserLexer_new(&err)))
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ParserLexer_del, (void *)lp);

		if ((err = lp->setSrc(lp, text)).code) { }
		else if ((err = lp->lex(lp, NULL, 0)).code) { }
		else if ((err = _Dz1ParserInit_parse(lp, &param)).code) { }

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1ParserLexer_del, (void *)lp);
	}

	pthread_cleanup_pop(1); // (MyParam_cancel, (void *)&param);
	return err;
}
