#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include <dz1_str.h>

#include "../kernel/dz1_thread_stdio.h"
#include "dz1_parser.h"
#include "dz1_parser_syntax.h"

//#define SYNTAX_DEBUG
Dz1ParserMatchOpt *Dz1ParserMatchOpt_new(Dz1ParserMatchOptType type, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ParserMatchOpt *ret = (Dz1ParserMatchOpt *)Dz1Calloc(sizeof(Dz1ParserMatchOpt), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		ret->type = type;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1ParserMatchOpt_del(Dz1ParserMatchOpt *p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1ParserMatchOpt_dump(Dz1ParserMatchOpt *p, int tab)
{
	if (!p) return;
}

static Dz1Error Dz1ParserSyntaxEntry_addMatch_pushOpt(Dz1ParserSyntaxEntry *p, Dz1ParserMatchOptType opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ParserMatchOpt *e = NULL;
	if ((e = Dz1ParserMatchOpt_new(opt, &err)) == NULL) { ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ParserMatchOpt_del, (void *)e);
		if ((err = Dz1Fifo_push(p->opt, e)).code) { ERR_OUT(&err); }
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ParserMatchOpt_del, (void *)e);
	}
	return err;
}

static Dz1Error Dz1ParserSyntaxEntry_addMatch(Dz1ParserSyntaxEntry *p, Dz1ParserMatchSequenceEntry *e, Dz1ParserMatchOptType opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!e) Dz1Error_set(&err, EINVAL);
	else if ((err = Dz1Fifo_push(p->seq, e)).code) { ERR_OUT(&err); }
	else if ((err = Dz1ParserSyntaxEntry_addMatch_pushOpt(p, opt)).code) { ERR_OUT(&err); }
	/*
	else
	{
		Dz1Thread_tprintf(NULL, 0, "\nDz1ParserSyntaxEntry_addMatch() : After Call\n");
		Dz1ParserSyntaxEntry_dump(NULL, p, 0);
		Dz1Thread_tprintf(NULL, 0, "\n");
	}
	*/
	return err;
}

// Process '+' tag or '*' tag
static Dz1Error _Dz1ParserSyntaxEntry_process(Dz1Parser *parser, Dz1ParserMatchSequenceEntry *seq, Dz1ParserMatchOptType opt, void *param, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	//Dz1ParserMatchSequenceEntry_dump(seq, tab);
	switch(opt)
	{
		case Dz1ParserMatchOptType_none:
			if ((err = seq->process(parser, seq, param, tab)).code) { /* Dz1Error_print(&err, tab); */ }
			break;
		case Dz1ParserMatchOptType_omit:
			seq->process(parser, seq, param, tab);
			break;
		case Dz1ParserMatchOptType_loop:
			if ((err = seq->process(parser, seq, param, tab)).code) { /*ERR_OUT(&err);*/ }
			else
			{
				do
				{
					if ((err = seq->process(parser, seq, param, tab)).code) { /*ERR_OUT(&err);*/ }
				} while(err.code == 0);
			}
			Dz1Error_set(&err, 0);
			break;
		case Dz1ParserMatchOptType_oneLoop:
			if ((err = seq->process(parser, seq, param, tab)).code) { /* ERR_OUT(&err); */ }
			else
			{
				do
				{
					if ((err = seq->process(parser, seq, param, tab)).code) { /* ERR_OUT(&err); */ }
				} while(err.code == 0);
				Dz1Error_set(&err, 0);
			}
			break;
		default:
			ERR_SET_OUT(&err, EFAULT);
			break;
	}
	return err;
}

typedef struct Dz1ParserSyntaxTraceInfo
{
	Dz1Parser *parser;
	str_t old_syntax;
} Dz1ParserSyntaxTraceInfo;

static void syntax_name_push(Dz1Parser *p, StackTrace *trace)
{
	trace->prev = p->trace;
	p->trace = trace;
// 	trace.prev = parser->trace;
// 	trace.current = s->name;
// 	parser->trace = &trace;
}

static void syntax_name_pop(void *ptr)
{
#if 0
	Dz1ParserSyntaxTraceInfo *p = (Dz1ParserSyntaxTraceInfo *)ptr;
	p->parser->current_syntax = p->old_syntax;
#else
	Dz1Parser *p = (Dz1Parser *)ptr;
	p->trace = p->trace->prev;
#endif
}

static __inline__ void trace_dump(StackTrace *p)
{
	if (p)
	{
		if (p->prev) trace_dump(p->prev);
		Dz1Thread_eprintf(":%s", p->current);
	}
}
// Do Sequence Match
static Dz1Error Dz1ParserSyntaxEntry_process(Dz1Parser *parser, Dz1ParserSyntaxEntry *s, void *param, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	StackTrace trace = StackTrace_initializer(s->name);
	syntax_name_push(parser, &trace);

#ifdef SYNTAX_DEBUG
	Dz1Thread_tprintf(tab, "[Syntax : ");
	trace_dump(parser->trace);
	Dz1Thread_eprintf("] >>>>>>>>>>>>>>>>>>>>\n");
//	Dz1ParserToken_dump(parser->lexer->current, tab);
#endif

	if (!s) { Dz1Error_set(&err, EFAULT); }
	else
	{
		void *cSeq = NULL;
		Dz1ParserMatchSequenceEntry *seq = NULL;

		if ((cSeq = Dz1FifoCursor_new(s->seq, NULL)))
		{
			void *cOpt = NULL;
			Dz1ParserMatchOpt *opt = NULL;

			pthread_cleanup_push(Dz1FifoCursor_del, cSeq);

			if ((cOpt = Dz1FifoCursor_new(s->opt, NULL)))
			{
				pthread_cleanup_push(Dz1FifoCursor_del, cOpt);

				for (Dz1FifoCursor_init(cSeq, NULL, Dz1FifoCursorPos_head), Dz1FifoCursor_init(cOpt, NULL, Dz1FifoCursorPos_head);
										Dz1FifoCursor_cond(cSeq) && Dz1FifoCursor_cond(cOpt);
										Dz1FifoCursor_next(cSeq, FALSE), Dz1FifoCursor_next(cOpt, FALSE))
				{
					seq = (Dz1ParserMatchSequenceEntry *)Dz1FifoCursor_data(cSeq);
					opt = (Dz1ParserMatchOpt *)Dz1FifoCursor_data(cOpt);
					if ((err = _Dz1ParserSyntaxEntry_process(parser, seq, opt->type, param, tab)).code) { break; }
				}
				/*
				if (err.code && !Dz1FifoCursor_isFirst(cSeq))
				{
					Dz1Thread_eprintf("Dz1ParserSyntaxEntry_process() : Cirticial Error while Syntax Matching \"%s\" on line %d\n",
							s->name, parser->lexer->getLineNum(parser->lexer));
				}
				*/
				pthread_cleanup_pop(1); // (Dz1FifoCursor_del, cSeq);
			}
			pthread_cleanup_pop(1); // (Dz1FifoCursor_del, cSeq);
		}
	}

#ifdef SYNTAX_DEBUG
	Dz1Thread_tprintf(tab, "[Syntax : ");
	trace_dump(parser->trace);
	Dz1Thread_eprintf("] <=====================(%s)\n", err.code == 0 ? "Ok" : "Fail");
#endif
	syntax_name_pop(parser);

	return err;
}

Dz1ParserSyntaxEntry *Dz1ParserSyntaxEntry_new(str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	int len = 0;
	Dz1ParserSyntaxEntry *ret = NULL;
	if (!name || !(len = (int)strlen(name))) Dz1Error_set(errp, EINVAL);
	else if ((ret = (Dz1ParserSyntaxEntry *)Dz1Malloc(sizeof(Dz1ParserSyntaxEntry), errp)) == NULL) { }
	else
	{
		memset(ret, 0, sizeof(Dz1ParserSyntaxEntry));
		pthread_cleanup_push(Dz1ParserSyntaxEntry_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) { }
		else if ((ret->seq = Dz1Fifo_new((Dz1DelFunc)Dz1ParserMatchSequenceEntry_del, (Dz1DumpFunc)Dz1ParserMatchSequenceEntry_dump, 0, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->opt = Dz1Fifo_new((Dz1DelFunc)Dz1ParserMatchOpt_del, (Dz1DumpFunc)Dz1ParserMatchOpt_dump, 0, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->addMatch = Dz1ParserSyntaxEntry_addMatch;
			ret->process = Dz1ParserSyntaxEntry_process;
		}

		pthread_cleanup_pop(errp->code); // (Dz1ParserSyntaxEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserSyntaxEntry_del(Dz1ParserSyntaxEntry *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	if (p->seq) Dz1Fifo_del(p->seq);
	if (p->opt) Dz1Fifo_del(p->opt);
	Dz1Free(p);
}

void Dz1ParserSyntaxEntry_dump(Dz1ParserSyntaxEntry *p, int tab)
{
	Dz1ParserMatchSequenceEntry *seq = NULL;
	void *cSeq = NULL;

	if (!p) return;

	Dz1Thread_etprintf(tab, "%s ::= ", p->name);

	if ((cSeq = Dz1FifoCursor_new(p->seq, NULL)))
	{
		Dz1ParserMatchOpt *opt = NULL;
		void *cOpt = NULL;

		pthread_cleanup_push(Dz1FifoCursor_del, cSeq);

		if ((cOpt = Dz1FifoCursor_new(p->opt, NULL)))
		{
			pthread_cleanup_push(Dz1FifoCursor_del, cOpt);

			for (Dz1FifoCursor_init(cSeq, NULL, Dz1FifoCursorPos_head), Dz1FifoCursor_init(cOpt, NULL, Dz1FifoCursorPos_head);
					Dz1FifoCursor_cond(cSeq) && Dz1FifoCursor_cond(cOpt);
					Dz1FifoCursor_next(cSeq, FALSE), Dz1FifoCursor_next(cOpt, FALSE))
			{
				seq = (Dz1ParserMatchSequenceEntry *)Dz1FifoCursor_data(cSeq);
				opt = (Dz1ParserMatchOpt *)Dz1FifoCursor_data(cOpt);

				if (opt->type != Dz1ParserMatchOptType_none) Dz1Thread_eprintf("[ ");

				Dz1ParserMatchSequenceEntry_dump(seq, 0);

				if (opt->type != Dz1ParserMatchOptType_none) Dz1Thread_eprintf(" ]");

				switch(opt->type)
				{
					case Dz1ParserMatchOptType_loop:
						Dz1Thread_eprintf("* ");
						break;
					case Dz1ParserMatchOptType_oneLoop:
						Dz1Thread_eprintf("+ ");
						break;
					default:
						Dz1Thread_eprintf(" ");
						break;
				}
			}
			pthread_cleanup_pop(1); // (Dz1FifoCursor_del, cSeq);
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, cSeq);
	}
	Dz1Thread_tprintf(tab, "\n");
}
