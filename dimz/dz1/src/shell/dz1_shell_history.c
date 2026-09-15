#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_history.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellHistoryA
static Dz1Error Dz1ShellHistoryA_push(Dz1ShellHistoryA *p, str_t cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((cmd = Dz1StrA_dup(cmd, &err)) == NULL) { }
	else if ((err = Dz1Fifo_push(p->fifo, (void *)cmd)).code) { }
	else p->num++;

	return err;
}

static str_t Dz1ShellHistoryA_pop(Dz1ShellHistoryA *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	return (str_t)Dz1Fifo_pop(p->fifo, errp);
}

static u32_t Dz1ShellHistoryA_count(Dz1ShellHistoryA *p) { return Dz1Fifo_count(p->fifo); }

static bool_t Dz1ShellHistoryA_isFull(Dz1ShellHistoryA *p) { return Dz1Fifo_isFull(p->fifo); }

static void Dz1ShellHistoryA_cursorInit(Dz1ShellHistoryA *p, Dz1FifoCursorPos pos) { Dz1FifoCursor_init(p->fifoc, p->fifo, pos); }

static bool_t Dz1ShellHistoryA_cursorCond(Dz1ShellHistoryA *p) { return Dz1FifoCursor_cond(p->fifoc); }

static void Dz1ShellHistoryA_cursorNext(Dz1ShellHistoryA *p, bool_t notNull) { Dz1FifoCursor_next(p->fifoc, notNull); }

static void Dz1ShellHistoryA_cursorPrev(Dz1ShellHistoryA *p, bool_t notNull) { Dz1FifoCursor_prev(p->fifoc, notNull); }

static str_t Dz1ShellHistoryA_cursorData(Dz1ShellHistoryA *p) { return (str_t)Dz1FifoCursor_data(p->fifoc); }

Dz1ShellHistoryA *Dz1ShellHistoryA_new(u32_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellHistoryA *ret = (Dz1ShellHistoryA *)Dz1Malloc(sizeof(Dz1ShellHistoryA), errp);
	if (ret)
	{
		int _size = (int)size;
		_size = -_size;

		memset(ret, 0, sizeof(Dz1ShellHistoryA));
		pthread_cleanup_push(Dz1ShellHistoryA_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)Dz1StrA_del, (Dz1DumpFunc)Dz1StrA_dump, _size, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->fifoc = Dz1FifoCursor_new(ret->fifo, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->num = 0;
			ret->push = Dz1ShellHistoryA_push;
			ret->pop = Dz1ShellHistoryA_pop;

			ret->count = Dz1ShellHistoryA_count;
			ret->isFull = Dz1ShellHistoryA_isFull;

			ret->cursorInit = Dz1ShellHistoryA_cursorInit;
			ret->cursorCond = Dz1ShellHistoryA_cursorCond;
			ret->cursorNext = Dz1ShellHistoryA_cursorNext;
			ret->cursorPrev = Dz1ShellHistoryA_cursorPrev;
			ret->cursorData = Dz1ShellHistoryA_cursorData;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ShellHistoryA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellHistoryA_del(Dz1ShellHistoryA *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	if (p->fifoc) Dz1FifoCursor_del(p->fifoc);
	Dz1Free(p);
}

void Dz1ShellHistoryA_dump(Dz1ShellHistoryA *p, int tab)
{
	u32_t idx, cnt;
	if (!p) return;
	if ((cnt = p->count(p)) > 0)
	{
		for (idx = p->num - p->count(p), p->cursorInit(p, Dz1FifoCursorPos_head); p->cursorCond(p) && cnt; idx++, p->cursorNext(p, FALSE), cnt--)
			Dz1ThreadA_tprintf(tab, "%d %s\n", idx, p->cursorData(p));
	}
	else Dz1ThreadA_tprintf(tab, "Empty\n");
}
// Dz1ShellHistoryA
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellHistoryW
static Dz1Error Dz1ShellHistoryW_push(Dz1ShellHistoryW *p, wstr_t cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((cmd = Dz1StrW_dup(cmd, &err)) == NULL) { }
	else if ((err = Dz1Fifo_push(p->fifo, (void *)cmd)).code) { }
	else p->num++;

	return err;
}

static wstr_t Dz1ShellHistoryW_pop(Dz1ShellHistoryW *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	return (wstr_t)Dz1Fifo_pop(p->fifo, errp);
}

static u32_t Dz1ShellHistoryW_count(Dz1ShellHistoryW *p) { return Dz1Fifo_count(p->fifo); }

static bool_t Dz1ShellHistoryW_isFull(Dz1ShellHistoryW *p) { return Dz1Fifo_isFull(p->fifo); }

static void Dz1ShellHistoryW_cursorInit(Dz1ShellHistoryW *p, Dz1FifoCursorPos pos) { Dz1FifoCursor_init(p->fifoc, p->fifo, pos); }

static bool_t Dz1ShellHistoryW_cursorCond(Dz1ShellHistoryW *p) { return Dz1FifoCursor_cond(p->fifoc); }

static void Dz1ShellHistoryW_cursorNext(Dz1ShellHistoryW *p, bool_t notNull) { Dz1FifoCursor_next(p->fifoc, notNull); }

static void Dz1ShellHistoryW_cursorPrev(Dz1ShellHistoryW *p, bool_t notNull) { Dz1FifoCursor_prev(p->fifoc, notNull); }

static wstr_t Dz1ShellHistoryW_cursorData(Dz1ShellHistoryW *p) { return (wstr_t)Dz1FifoCursor_data(p->fifoc); }

Dz1ShellHistoryW *Dz1ShellHistoryW_new(u32_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellHistoryW *ret = (Dz1ShellHistoryW *)Dz1Malloc(sizeof(Dz1ShellHistoryW), errp);
	if (ret)
	{
		int _size = (int)size;
		_size = -_size;

		memset(ret, 0, sizeof(Dz1ShellHistoryW));
		pthread_cleanup_push(Dz1ShellHistoryW_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new((Dz1DelFunc)Dz1StrA_del, (Dz1DumpFunc)Dz1StrA_dump, _size, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->fifoc = Dz1FifoCursor_new(ret->fifo, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->num = 0;
			ret->push = Dz1ShellHistoryW_push;
			ret->pop = Dz1ShellHistoryW_pop;

			ret->count = Dz1ShellHistoryW_count;
			ret->isFull = Dz1ShellHistoryW_isFull;

			ret->cursorInit = Dz1ShellHistoryW_cursorInit;
			ret->cursorCond = Dz1ShellHistoryW_cursorCond;
			ret->cursorNext = Dz1ShellHistoryW_cursorNext;
			ret->cursorPrev = Dz1ShellHistoryW_cursorPrev;
			ret->cursorData = Dz1ShellHistoryW_cursorData;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ShellHistoryW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellHistoryW_del(Dz1ShellHistoryW *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	if (p->fifoc) Dz1FifoCursor_del(p->fifoc);
	Dz1Free(p);
}

void Dz1ShellHistoryW_dump(Dz1ShellHistoryW *p, int tab)
{
	u32_t idx, cnt;
	if (!p) return;
	if ((cnt = p->count(p)) > 0)
	{
		for (idx = p->num - p->count(p), p->cursorInit(p, Dz1FifoCursorPos_head); p->cursorCond(p) && cnt; idx++, p->cursorNext(p, FALSE), cnt--)
			Dz1ThreadW_tprintf(tab, L"%d %s\n", idx, p->cursorData(p));
	}
	else Dz1ThreadW_tprintf(tab, L"Empty\n");
}
// Dz1ShellHistoryW
///////////////////////////////////////////////////////////////////////////////
#endif