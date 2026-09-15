#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include <dz1_aatree.h>
#include "../kernel/dz1_thread_stdio.h"
#include "dz1_parser.h"

static bool_t isExistEmiter(Dz1Parser *p, Dz1ParserSyntaxEntry *syntax)
{
	int ret = TRUE;
	Dz1ParserMatchSequenceEntry *match = NULL;
	void *c = Dz1FifoCursor_new(syntax->seq, NULL);
	if (c)
	{
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((match = (Dz1ParserMatchSequenceEntry *)Dz1FifoCursor_data(c)))
			{
				if (match->emit_name == NULL) continue; // No Emitter is Skip
				else
				{
					Dz1ParserEmitEntry key;
					key.name = match->emit_name;
					if (Dz1AATree_find(p->emiter, &key) == NULL)
					{
						Dz1Thread_eprintf("isExistEmiter() : Emitter '%s' is not found\n", key.name);
						ret = FALSE;
						break;
					}
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
	return ret;
}

static Dz1Error Dz1Parser_addSyntax(Dz1Parser *p, Dz1ParserSyntaxEntry *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserSyntaxEntry key;
	key.name = e->name;

	if (Dz1AATree_find(p->syntax, &key)) Dz1Error_set(&err, EEXIST);
	else if (!(isExistEmiter(p, e)))
	{
		Dz1Thread_eprintf("Dz1Parser_addSyntax() : syntax '%s' has missing emitter\n", e->name);
		Dz1Error_set(&err, EINVAL);
	}
	else err = Dz1AATree_insert(p->syntax, e);
	return err;
}

static Dz1ParserSyntaxEntry *Dz1Parser_findSyntax(Dz1Parser *p, str_t name)
{
	Dz1ParserSyntaxEntry key;
	key.name = name;
	return (Dz1ParserSyntaxEntry *)Dz1AATree_find(p->syntax, &key);
}

Dz1Error Dz1Parser_addEmiter(Dz1ParserHandle *ptr, str_t name, Dz1ParserEmitFunc func)
{
	Dz1Parser *p = (Dz1Parser *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserEmitEntry key, *e = NULL;
	key.name = name;
	if (Dz1AATree_find(p->emiter, &key)) Dz1Error_set(&err, EEXIST);
	else if ((e = Dz1ParserEmitEntry_new(name, func, &err)) == NULL) { }
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ParserEmitEntry_del, (void *)e);

		err = Dz1AATree_insert(p->emiter, e);

		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ParserEmitEntry_del, (void *)e);
	}
	return err;
}

u32_t Dz1Parser_getLineNum(Dz1ParserHandle *ptr)
{
	u32_t ret = 0;
	Dz1Parser *p = (Dz1Parser *)ptr;
	if (p && p->lexer) ret = p->lexer->getLineNum(p->lexer);
	return ret;
}

Dz1Error Dz1Parser_prepare(Dz1ParserHandle *ptr, str_t text)
{
	Dz1Parser *p = (Dz1Parser *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (strlen(text) <= 0) ERR_SET_OUT(&err, EINVAL);
	else if ((err = p->lexer->setSrc(p->lexer, text)).code) { }
	else if ((err = p->lexer->lex(p->lexer, __FILE__, __LINE__)).code) { }
	return err;
}

Dz1Error Dz1Parser_process(Dz1ParserHandle *ptr, str_t syntaxName, void *param, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Parser *parser = (Dz1Parser *)ptr;
	Dz1ParserSyntaxEntry key, *s = NULL;
	key.name = syntaxName;
	if ((s = (Dz1ParserSyntaxEntry *)Dz1AATree_find(parser->syntax, (void *)&key)) == NULL)
	{
		Dz1Thread_tprintf(tab, "Dz1Parser_process() : No such Syntax \"%s\" at line %d\n", syntaxName, parser->lexer->getLineNum(parser->lexer) + 1);
		Dz1Error_set(&err, ESRCH);
		return err;
	}

#ifdef SYNTAX_DEBUG
	Dz1Thread_tprintf(tab, "Dz1Parser_process() : Syntax Procesing [%s] Enter\n", s->name);
	Dz1ParserSyntaxEntry_dump(s, tab);
#endif

	if ((err = s->process(parser, s, param, tab)).code)
	{
#ifdef SYNTAX_DEBUG
		Dz1Thread_tprintf(tab, "Syntax Process Fail : %s\n", syntaxName);
#endif
	}

#ifdef SYNTAX_DEBUG
	Dz1Thread_tprintf(tab, "Dz1Parser_process() : Syntax Procesing [%s] Return(%d)\n", s->name, err.code);
#endif

	/*
	if (err.code != 0)
	{
		Dz1Thread_eprintf("Dz1Parser_process() : Token = "); Dz1ParserTokenA_dump(parser->lexer->current, 0);
	}
	*/
	return err;
}

static Dz1Error Dz1Parser_emit(Dz1Parser *parser, str_t emit_name, Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (emit_name == NULL || strcmp(emit_name, "none")==0) { Dz1Error_set(&err, 0); }
	else
	{
		Dz1ParserEmitEntry key, *e = NULL;
		key.name = emit_name;

		//Dz1Thread_tprintf(0, "Dz1Parser_emit() : Emitting %s\n", emit_name);
		if ((e = (Dz1ParserEmitEntry *)Dz1AATree_find(parser->emiter, (void *)&key)) != NULL)
			err = e->func(t, param);
		else
			Dz1Error_set(&err, ESRCH);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Symbol Hash Helper Functions
///////////////////////////////////////////////////////////////////////////////
static int emiterHashCmp(void *a, void *b)
{
	Dz1ParserEmitEntry *pa = (Dz1ParserEmitEntry *)a, *pb = (Dz1ParserEmitEntry *)b;
	if (!pa && pb) return -1;
	else if (pa && !pb) return 1;
	else return strcmp(pa->name, pb->name);
}

static void emiterHashDel(void *ptr) { Dz1ParserEmitEntry_del((Dz1ParserEmitEntry*)ptr); }
static void emiterHashDump(void *ptr, int tab) { Dz1ParserEmitEntry_dump((Dz1ParserEmitEntry *)ptr, tab); }

///////////////////////////////////////////////////////////////////////////////
// Syntax Hash Helper Functions
///////////////////////////////////////////////////////////////////////////////
static int syntaxHashCmp(void *a, void *b)
{
	Dz1ParserSyntaxEntry *pa = (Dz1ParserSyntaxEntry *)a,
						 *pb = (Dz1ParserSyntaxEntry *)b;
	if (!pa && pb) return -1;
	else if (pa && !pb) return 1;
	else return strcmp(pa->name, pb->name);
}

static void syntaxHashDel(void *ptr) { Dz1ParserSyntaxEntry_del((Dz1ParserSyntaxEntry *)ptr); }
static void syntaxHashDump(void *ptr, int tab) { Dz1ParserSyntaxEntry_dump((Dz1ParserSyntaxEntry *)ptr, tab); }

void *Dz1Parser_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Parser *ret = (Dz1Parser *)Dz1Malloc(sizeof(Dz1Parser), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1Parser));
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&ret);

		if ((ret->syntax = Dz1AATree_new(syntaxHashCmp, syntaxHashDel, syntaxHashDump, errp)) == NULL) { }
		else if ((ret->emiter = Dz1AATree_new(emiterHashCmp, emiterHashDel, emiterHashDump, errp)) == NULL) {  }
		else if ((ret->lexer = Dz1ParserLexer_new(errp)) == NULL) { }
		else
		{
			ret->addSyntax = Dz1Parser_addSyntax;
			ret->findSyntax = Dz1Parser_findSyntax;
			ret->emit = Dz1Parser_emit;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&ret);
	}
	return (void *)ret;
}

void Dz1Parser_del(Dz1ParserHandle *ptr)
{
	Dz1Parser *p = (Dz1Parser *)ptr;
	if (!p) return;
	if (p->syntax) Dz1AATree_del(p->syntax);
	if (p->emiter) Dz1AATree_del(p->emiter);
	if (p->lexer) Dz1ParserLexer_del(p->lexer);
	Dz1Free(p);
}

void Dz1Parser_delAndSetNull(void *ptr)
{
	Dz1Parser **p = (Dz1Parser **)ptr;
	Dz1Parser_del(*p); *p = NULL;
}

void Dz1Parser_dump(Dz1ParserHandle *ptr, int tab)
{
	Dz1Parser *p = (Dz1Parser *)ptr;
	if (!p) return;
	Dz1Thread_tprintf(tab, "[Syntaxies]------------------------------------------\n");
	Dz1AATree_dump(p->syntax, tab + 1);
	Dz1Thread_tprintf(tab, "[emiters]--------------------------------------------\n");
	Dz1AATree_dump(p->emiter, tab + 1);
	Dz1Thread_tprintf(tab, "[Lexer]----------------------------------------------\n");
	Dz1ParserToken_dump(p->lexer->current, tab + 1);
}

