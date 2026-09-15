#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include <dz1_str.h>

#include "../kernel/dz1_thread_stdio.h"
#include "dz1_parser.h"
#include "dz1_parser_match.h"

//#define MATCH_TRACE

Dz1ParserMatchToken *Dz1ParserMatchToken_new(int tokenTypeOnly, u32_t t, str_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserMatchToken *ret = (Dz1ParserMatchToken *)Dz1Calloc(sizeof(Dz1ParserMatchToken), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ParserMatchToken_delAndSetNull, (void *)&ret);
		if ((ret->tok = Dz1ParserToken_new(t, v, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->tokenTypeOnly = tokenTypeOnly;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserMatchToken_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserMatchToken_del(Dz1ParserMatchToken *p)
{
	if (!p) return;
	if (p->tok) Dz1ParserToken_del(p->tok);
	p->tok = NULL;
	Dz1Free(p);
}

void Dz1ParserMatchToken_dump(Dz1ParserMatchToken *p, int tab)
{
	Dz1ParserTokenTypeStr typeStr;
	if (!p) return;
	Dz1Thread_etprintf(tab, "<%s>", Dz1ParserToken_typeStr(typeStr, p->tok->t));
	if (!p->tokenTypeOnly)
		Dz1Thread_eprintf("(%s)", p->tok->v ? p->tok->v : "null");
}



///////////////////////////////////////////////////////////////////////////////
//// Matching Element
/////////////////////////////////////////////////////////////////////////////////
static int tokenType_isEqual(u32_t a, u32_t b)
{
	if ((a & DZ1_PARSER_TOKEN_NUMBER_MASK) == DZ1_PARSER_TOKEN_NUMBER)
	{	// 'a' is number type token
		if ((b & DZ1_PARSER_TOKEN_NUMBER_MASK) == DZ1_PARSER_TOKEN_NUMBER)
		{	// 'b' is number type token
			if ((a & NUMBER_SIGN_SPECIFIED) && ((b & NUMBER_SIGN_SPECIFIED) == 0)) return 0;
			if ((a & NUMBER_TYPE_MASK) && ((a & NUMBER_TYPE_MASK) != (b & NUMBER_TYPE_MASK))) return 0;

			return 1;
		}
		else return 0;
	}
	else return (a == b);
}

static Dz1Error Dz1ParserMatchUnit_process(Dz1Parser *parser, Dz1ParserToken *t, Dz1ParserMatchUnit *e, str_t emit_name, void *param, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef MATCH_ERROR_PRINT 
	char want[64], income[64];
#endif

#ifdef MATCH_TRACE
	Dz1Thread_tprintf(tab, "Dz1ParserMatchUnit_process(%s) ---------\n", emit_name);
	Dz1ParserToken_dump(t, tab);
	if (e->type == Dz1ParserMatchUnitType_syntax)
		Dz1Thread_tprintf(tab, "Syntax:%s\n", e->x.syntax);
	else
		Dz1ParserToken_dump(e->x.token->tok, tab);
	Dz1Thread_tprintf(tab, "-----------------------------------------\n");
#endif

	switch(e->type)
	{
		case Dz1ParserMatchUnitType_token:
			{
				if (!tokenType_isEqual(e->x.token->tok->t, t->t))
				{
// 					char want[64], income[64];
// 					Dz1Error_setWithComment(&err, EINVAL, (DZ1_ERROR_ARG, "Matching Fail line %d, [!]%s <- %s", Dz1Parser_getLineNum(parser), Dz1ParserToken_typeStr(want, e->x.token->tok->t), Dz1ParserToken_typeStr(income, t->t) ) );
					Dz1Error_set(&err, EINVAL);
#ifdef MATCH_ERROR_PRINT 
					Dz1Thread_tprintf(tab, "Type Mismatch = [!]%s <- %s\n", Dz1ParserToken_typeStr(want, e->match.token.tokenType),
																	Dz1ParserToken_typeStr(income, t->t));
#endif
				}
				else if (!e->x.token->tokenTypeOnly && strcmp(e->x.token->tok->v, t->v) != 0)
				{
					Dz1Error_set(&err, EINVAL);
#ifdef MATCH_ERROR_PRINT
					Dz1Thread_tprintf(tab, "Value Mismatch = [!]%s <- %s\n",	e->x.token->tok->v, t->v);
#endif
				}
				else
				{
#ifdef MATCH_TRACE
					Dz1Thread_tprintf(tab, "Emiting : [%s]\n", emit_name);
#endif
					if ((err = parser->emit(parser, emit_name, t, param)).code) { }
					else if ((err = parser->lexer->lex(parser->lexer, __FILE__, __LINE__)).code) { ERR_OUT(&err); }
				}
			}
			break;
		case Dz1ParserMatchUnitType_syntax:
			if ((err = Dz1Parser_process(parser, e->x.syntax, param, tab + 1)).code == 0)
			{
#ifdef MATCH_TRACE
				Dz1Thread_tprintf(tab, "Emiting : [%s]\n", emit_name);
#endif
				if ((err = parser->emit(parser, emit_name, NULL, param)).code) { }
			}
#ifdef SYNTAX_DEBUG
			else { Dz1Thread_tprintf(tab, "Syntax Matching Fail\n"); }
#endif
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
			//tabprintf( tab, "Dz1ParserMatchUnit_process() : Unknown Match Mode %d\n", e->matchMode);
	}
	return err;
}

Dz1ParserMatchUnit *Dz1ParserMatchUnit_newTokenMatch(int tokenTypeOnly, u32_t tokenType, str_t tokenValue, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserMatchUnit *ret = (Dz1ParserMatchUnit *)Dz1Calloc(sizeof(Dz1ParserMatchUnit), 1, errp);
	if (ret)
	{
		pthread_cleanup_push(Dz1ParserMatchUnit_delAndSetNull, (void *)&ret);

		if ((ret->x.token = Dz1ParserMatchToken_new(tokenTypeOnly, tokenType, tokenValue, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->type = Dz1ParserMatchUnitType_token;
			ret->process = Dz1ParserMatchUnit_process;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserMatchUnit_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1ParserMatchUnit *Dz1ParserMatchUnit_newSyntaxIssue(str_t syntaxName, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1ParserMatchUnit *ret = (Dz1ParserMatchUnit *)Dz1Calloc(sizeof(Dz1ParserMatchUnit), 1, errp);
	if (ret)
	{
		pthread_cleanup_push(Dz1ParserMatchUnit_delAndSetNull, (void *)&ret);

		if ((ret->x.syntax = Dz1StrA_dup(syntaxName, errp)))
		{
			ret->type = Dz1ParserMatchUnitType_syntax;
			ret->process = Dz1ParserMatchUnit_process;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserMatchUnit_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserMatchUnit_del(Dz1ParserMatchUnit *p)
{
	if (!p) return;
	switch(p->type)
	{
		case Dz1ParserMatchUnitType_token:
			Dz1ParserMatchToken_del(p->x.token);
			break;
		case Dz1ParserMatchUnitType_syntax:
			Dz1StrA_del(p->x.syntax);
			break;
	}
	Dz1Free(p);
}

void Dz1ParserMatchUnit_dump(Dz1ParserMatchUnit *p, int tab)
{
	if (!p) return;
	switch(p->type)
	{
		case Dz1ParserMatchUnitType_token:
			Dz1ParserMatchToken_dump(p->x.token, tab);
			break;
		case Dz1ParserMatchUnitType_syntax:
			Dz1Thread_tprintf(tab, "<SYNTAX:%s>", p->x.syntax);
			break;
		default:
			Dz1Thread_tprintf(tab, "Unknown(%d)\n", p->type);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Matching Entry
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Dz1ParserMatchSequenceEntry_addTokenMatch(Dz1ParserMatchSequenceEntry *p, int tokenTypeOnly, u32_t t, str_t v)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserMatchUnit *e = Dz1ParserMatchUnit_newTokenMatch(tokenTypeOnly, t, v, &err);
	if (e == NULL) { ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ParserMatchUnit_del, (void *)e);

		if ((err = p->add(p, e)).code) { ERR_OUT(&err); }

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ParserMatchUnit_del, (void *)e);
	}
	return err;
}

static Dz1Error Dz1ParserMatchSequenceEntry_addSyntaxIssue(Dz1ParserMatchSequenceEntry *p, str_t syntaxName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserMatchUnit *e = Dz1ParserMatchUnit_newSyntaxIssue(syntaxName, &err);
	if (e == NULL) { ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ParserMatchUnit_del, (void *)e);

		if ((err = p->add(p, e)).code) { ERR_OUT(&err); }

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ParserMatchUnit_del, (void *)e);
	}
	return err;
}

static Dz1Error Dz1ParserMatchSequenceEntry_add(Dz1ParserMatchSequenceEntry *p, Dz1ParserMatchUnit *unit)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (!unit) { ERR_SET_OUT(&err, EINVAL); }
	else if ((err = Dz1Fifo_push(p->oneOf, unit)).code) { ERR_OUT(&err); }

	return err;
}

// OR Match
static Dz1Error Dz1ParserMatchSequenceEntry_process(Dz1Parser *parser, Dz1ParserMatchSequenceEntry *m, void *param, int tab)
{	// matching one of list
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1ParserToken *token_backup = NULL;
	Dz1ParserLexer *lexer = parser->lexer;
	str_t source = lexer->source;
	u32_t line_num = lexer->getLineNum(lexer);

//	printf("\n%s\n\n", lexer->source);

	if ((token_backup = Dz1ParserToken_new(lexer->current->t, lexer->current->v, &err)) == NULL) ERR_OUT(errp);
	else
	{
		void *c = NULL;
		pthread_cleanup_push(Dz1ParserToken_DelAndSetNull, (void *)&token_backup);
		if ((c = Dz1FifoCursor_new(m->oneOf, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1ParserMatchUnit *e = NULL;
			pthread_cleanup_push(Dz1FifoCursor_del, c);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ParserMatchUnit *)Dz1FifoCursor_data(c)))
				{
					if ((*errp = e->process(parser, lexer->current, e, m->emit_name, param, tab)).code == 0) break;
					else
					{
						Dz1Error tErr = DZ1_ERROR_INITIALIZER;

						lexer->source = source;				// Restore source position
						lexer->setLineNum(lexer, line_num); // restore line number

						Dz1ParserToken_DelAndSetNull(&lexer->current);
						if ((lexer->current = Dz1ParserToken_new(token_backup->t, token_backup->v, &tErr)) == NULL) { *errp = tErr; ERR_OUT(&tErr); break; }
					}
				}
			}
			// if all matches are fail, err has some code
			pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);

			if (err.code)
			{
#ifdef MATCH_ERROR_PRINT
				Dz1ParserTokenTypeStr buf;
				Dz1Thread_tprintf(tab, "Dz1ParserMatchSequenceEntry_process() : No match for %s(%s) while Syntax [%s] - line %d\n",
						Dz1ParserToken_typeStr(buf, token_backup->tokenType),
						token_backup->tokenValue ? token_backup->tokenValue : "NULL", parser->current_syntax, line_num);
#endif
			}
			else
			{
#ifdef MATCH_TRACE
				Dz1ParserTokenTypeStr buf;
				Dz1Thread_tprintf(tab, "Take Token [%s][%s : %s]\n",
						parser->trace ? parser->trace->current : "(null)",
						Dz1ParserToken_typeStr(buf, token_backup->t),
						token_backup->v ? token_backup->v : "NULL");
#endif
			}
		}
		pthread_cleanup_pop(1); // (Dz1ParserToken_DelAndSetNull, (void *)&token_backup);
	}
	return err;
}


Dz1ParserMatchSequenceEntry *Dz1ParserMatchSequenceEntry_new(str_t emit_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserMatchSequenceEntry *ret = (Dz1ParserMatchSequenceEntry *)Dz1Calloc(sizeof(Dz1ParserMatchSequenceEntry), 1, errp);
	if (ret)
	{
		pthread_cleanup_push(Dz1ParserMatchSequenceEntry_delAndSetNull, (void *)&ret);

		if (emit_name && (ret->emit_name = Dz1StrA_dup(emit_name, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->oneOf = Dz1Fifo_new((Dz1DelFunc)Dz1ParserMatchUnit_del, (Dz1DumpFunc)Dz1ParserMatchUnit_dump, 0, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->addTokenMatch = Dz1ParserMatchSequenceEntry_addTokenMatch;
			ret->addSyntaxIssue = Dz1ParserMatchSequenceEntry_addSyntaxIssue;
			ret->add = Dz1ParserMatchSequenceEntry_add;
			ret->process = Dz1ParserMatchSequenceEntry_process;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserMatchSequenceEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserMatchSequenceEntry_del(Dz1ParserMatchSequenceEntry *p)
{
	if (!p) return;
	if (p->emit_name) Dz1StrA_del(p->emit_name);
	if (p->oneOf) Dz1Fifo_del(p->oneOf);
	Dz1Free(p);
}

void Dz1ParserMatchSequenceEntry_dump(Dz1ParserMatchSequenceEntry *p, int tab)
{
	if (!p) return;
	else
	{
		void *c = NULL;
		int printed = 0;
		Dz1ParserMatchUnit *e = NULL;

		Dz1Thread_tprintf(tab, "");
		if ((c = Dz1FifoCursor_new(p->oneOf, NULL)) != NULL)
		{
			pthread_cleanup_push(Dz1FifoCursor_del, c);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ParserMatchUnit *)Dz1FifoCursor_data(c)))
				{
					if (printed) Dz1Thread_eprintf("|");
					Dz1ParserMatchUnit_dump(e, 0);
					printed = 1;
				}
			}
			pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
		}

		if (p->emit_name) Dz1Thread_eprintf("=%s", p->emit_name);
	}
}
