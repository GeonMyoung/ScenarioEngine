#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>
#include "dz1_shell_cmd.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdEntryA
static void Dz1ShellCmdEntryA_del(Dz1ShellCmdEntryA *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	if (p->help) Dz1StrA_del(p->help);
	Dz1Free(p);
}

static void Dz1ShellCmdEntryA_delAndSetNull(void *ptr)
{
	Dz1ShellCmdEntryA **p = (Dz1ShellCmdEntryA **)ptr;
	Dz1ShellCmdEntryA_del(*p); *p = NULL;
}

static Dz1ShellCmdEntryA *Dz1ShellCmdEntryA_new(str_t name, Dz1ShellCmdFuncA func, void *funcParam, str_t help, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdEntryA *ret = (Dz1ShellCmdEntryA *)Dz1Malloc(sizeof(Dz1ShellCmdEntryA), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdEntryA));
		pthread_cleanup_push(Dz1ShellCmdEntryA_delAndSetNull, (void *)&ret);
		if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->help = Dz1StrA_dup(help, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->func = func;
			ret->funcParam = funcParam;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdEntryA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1ShellCmdEntryA_dump(Dz1ShellCmdEntryA *p, int tab)
{
	if (!p) return;
	Dz1ThreadA_tprintf(tab, "%s=%p(%p)\n", p->name, p->func, p->funcParam);
}

static int Dz1ShellCmdEntryA_cmp(Dz1ShellCmdEntryA *a, Dz1ShellCmdEntryA *b) { return Dz1StrA_cmp(a->name, b->name); }

Dz1ShellCmdReturn Dz1ShellCmdEntryA_execute(Dz1ShellCmdEntryA *p, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	if (p && p->func)
	{
		Dz1ThreadA_printf("Invoke (%s)\n", p->name);
 		ret = p->func(p->funcParam, argc, argv);
	}
	return ret;
}
// Dz1ShellCmdEntry
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdEntryW
static void Dz1ShellCmdEntryW_del(Dz1ShellCmdEntryW *p)
{
	if (!p) return;
	if (p->name) Dz1StrW_del(p->name);
	if (p->help) Dz1StrW_del(p->help);
	Dz1Free(p);
}

static void Dz1ShellCmdEntryW_delAndSetNull(void *ptr)
{
	Dz1ShellCmdEntryW **p = (Dz1ShellCmdEntryW **)ptr;
	Dz1ShellCmdEntryW_del(*p); *p = NULL;
}

static Dz1ShellCmdEntryW *Dz1ShellCmdEntryW_new(wstr_t name, Dz1ShellCmdFuncW func, void *funcParam, wstr_t help, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdEntryW *ret = (Dz1ShellCmdEntryW *)Dz1Malloc(sizeof(Dz1ShellCmdEntryW), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdEntryW));
		pthread_cleanup_push(Dz1ShellCmdEntryW_delAndSetNull, (void *)&ret);
		if ((ret->name = Dz1StrW_dup(name, errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->help = Dz1StrW_dup(help, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->func = func;
			ret->funcParam = funcParam;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdEntryW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1ShellCmdEntryW_dump(Dz1ShellCmdEntryW *p, int tab)
{
	if (!p) return;
	Dz1ThreadW_tprintf(tab, L"%s=%p(%p)\n", p->name, p->func, p->funcParam);
}

static int Dz1ShellCmdEntryW_cmp(Dz1ShellCmdEntryW *a, Dz1ShellCmdEntryW *b) { return Dz1StrW_cmp(a->name, b->name); }

Dz1ShellCmdReturn Dz1ShellCmdEntryW_execute(Dz1ShellCmdEntryW *p, int argc, wchar_t *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;
	if (p && p->func)
	{
		Dz1ThreadW_printf(L"Invoke (%s)\n", p->name);
 		ret = p->func(p->funcParam, argc, argv);
	}
	return ret;
}
// Dz1ShellCmdEntry
///////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdListA
static Dz1Error Dz1ShellCmdListA_push(Dz1ShellCmdListA *p, Dz1ShellCmdEntryA *e) { return Dz1Fifo_push(p->fifo, e); }
static Dz1ShellCmdEntryA *Dz1ShellCmdListA_pop(Dz1ShellCmdListA *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	return (Dz1ShellCmdEntryA *)Dz1Fifo_pop(p->fifo, errp);
}

static Dz1ShellCmdListA *Dz1ShellCmdListA_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdListA *ret = (Dz1ShellCmdListA *)Dz1Malloc(sizeof(Dz1ShellCmdListA), errp);

	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdListA));
		pthread_cleanup_push(Dz1ShellCmdListA_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new(NULL, (Dz1DumpFunc)Dz1ShellCmdEntryA_dump, 0, errp)))
		{
			ret->push = Dz1ShellCmdListA_push;
			ret->pop = Dz1ShellCmdListA_pop;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdListA_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void Dz1ShellCmdListA_del(Dz1ShellCmdListA *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void Dz1ShellCmdListA_dump(Dz1ShellCmdListA *p, int tab)
{
	if (!p) return;
	else
	{
		char fmt[1024];
		int len = 0, _len = 0;
		Dz1ShellCmdEntryA *e = NULL;
		void *c = Dz1FifoCursor_new(p->fifo, NULL);
		if (c)
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1FifoCursor_del, c);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ShellCmdEntryA *)Dz1FifoCursor_data(c)))
				{
					if (len < (_len = (int)strlen(e->name))) len = _len;
				}
			}

			sprintf(fmt, "%%%ds : %%s\n", len);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ShellCmdEntryA *)Dz1FifoCursor_data(c)))
					Dz1ThreadA_tprintf(tab, fmt, e->name, e->help);
			}
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1FifoCursor_del, c);
		}
	}
}
// Dz1ShellCmdListA
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdListW
static Dz1Error Dz1ShellCmdListW_push(Dz1ShellCmdListW *p, Dz1ShellCmdEntryW *e) { return Dz1Fifo_push(p->fifo, e); }
static Dz1ShellCmdEntryW *Dz1ShellCmdListW_pop(Dz1ShellCmdListW *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	return (Dz1ShellCmdEntryW *)Dz1Fifo_pop(p->fifo, errp);
}

static Dz1ShellCmdListW *Dz1ShellCmdListW_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdListW *ret = (Dz1ShellCmdListW *)Dz1Malloc(sizeof(Dz1ShellCmdListW), errp);

	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdListW));
		pthread_cleanup_push(Dz1ShellCmdListW_delAndSetNull, (void *)&ret);

		if ((ret->fifo = Dz1Fifo_new(NULL, (Dz1DumpFunc)Dz1ShellCmdEntryW_dump, 0, errp)))
		{
			ret->push = Dz1ShellCmdListW_push;
			ret->pop = Dz1ShellCmdListW_pop;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdListW_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void Dz1ShellCmdListW_del(Dz1ShellCmdListW *p)
{
	if (!p) return;
	if (p->fifo) Dz1Fifo_del(p->fifo);
	Dz1Free(p);
}

void Dz1ShellCmdListW_dump(Dz1ShellCmdListW *p, int tab)
{
	if (!p) return;
	else
	{
		wchar_t fmt[1024];
		int len = 0, _len = 0;
		Dz1ShellCmdEntryW *e = NULL;
		void *c = Dz1FifoCursor_new(p->fifo, NULL);
		if (c)
		{
			pthread_cleanup_push((Dz1CancelFunc)Dz1FifoCursor_del, c);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ShellCmdEntryW *)Dz1FifoCursor_data(c)))
				{
					if (len < (_len = (int)wcslen(e->name))) len = _len;
				}
			}

			swprintf(fmt, 1023, L"%%%ds : %%s\n", len);

			for (Dz1FifoCursorForward(c))
			{
				if ((e = (Dz1ShellCmdEntryW *)Dz1FifoCursor_data(c)))
					Dz1ThreadW_tprintf(tab, fmt, e->name, e->help);
			}
			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1FifoCursor_del, c);
		}
	}
}
// Dz1ShellCmdListW
///////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdA
static Dz1Error Dz1ShellCmdA_insert(Dz1ShellCmdA *p, str_t name, Dz1ShellCmdFuncA func, void *funcParam, str_t help)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellCmdEntryA *e = p->find(p, name);
	
	if (e) Dz1Error_set(&err, EEXIST);
	else if ((e = Dz1ShellCmdEntryA_new(name, func, funcParam, help, &err)) == NULL) { } 
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellCmdEntryA_del, (void *)&e);
		err = Dz1AATree_insert(p->tree, e);
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ShellCmdEntryA_del, (void *)&e);
	}
	return err;
}

static void Dz1ShellCmdA_remove(Dz1ShellCmdA *p, str_t name)
{
	Dz1ShellCmdEntryA key;
	key.name = name;
	Dz1AATree_remove(p->tree, &key);
}

static Dz1ShellCmdEntryA *Dz1ShellCmdA_find(Dz1ShellCmdA *p, str_t name)
{
	Dz1ShellCmdEntryA key;
	key.name = name;
	return (Dz1ShellCmdEntryA *)Dz1AATree_find(p->tree, &key);
}

typedef struct Dz1ShellCmdLikeArgA
{
	Dz1ShellCmdListA	*list;
	str_t				 name;
} Dz1ShellCmdLikeArgA;

static Dz1Error _Dz1ShellCmdA_like(Dz1ShellCmdLikeArgA *arg, Dz1ShellCmdEntryA *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (strncmp(e->name, arg->name, strlen(arg->name)) == 0)
		err = arg->list->push(arg->list, e);
	return err;
}

static Dz1ShellCmdListA *Dz1ShellCmdA_like(Dz1ShellCmdA *p, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdListA *ret = Dz1ShellCmdListA_new(errp);
	if (ret)
	{
		Dz1ShellCmdLikeArgA arg;
		arg.list = ret;
		arg.name = name;

		pthread_cleanup_push(Dz1ShellCmdListA_delAndSetNull, (void *)&ret);
		*errp = Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)_Dz1ShellCmdA_like, (void *)&arg);
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdListA_delAndSetNull, (void *)&ret);
	}

	return ret;
}

Dz1ShellCmdA *Dz1ShellCmdA_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdA *ret = (Dz1ShellCmdA *)Dz1Malloc(sizeof(Dz1ShellCmdA), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdA));
		pthread_cleanup_push(Dz1ShellCmdA_delAndSetNull, (void *)&ret);
		if ((ret->tree = Dz1AATree_new((Dz1CmpFunc)Dz1ShellCmdEntryA_cmp, (Dz1DelFunc)Dz1ShellCmdEntryA_del, (Dz1DumpFunc)Dz1ShellCmdEntryA_dump, errp)))
		{
			ret->insert = Dz1ShellCmdA_insert;
			ret->remove = Dz1ShellCmdA_remove;
			ret->find = Dz1ShellCmdA_find;
			ret->like = Dz1ShellCmdA_like;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellCmdA_del(Dz1ShellCmdA *p)
{
	if (!p) return;
	if (p->tree) Dz1AATree_del(p->tree);
	Dz1Free(p);
}

static Dz1Error _Dz1ShellCmdA_dump(int *len, Dz1ShellCmdEntryA *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int _len = (int)strlen(e->name);
	if (*len < _len) *len = _len;
	return err;
}

typedef struct Dz1ShellCmdDumpArgA
{
	int		 tab;
	str_t	 fmt;
} Dz1ShellCmdDumpArgA;

static Dz1Error __Dz1ShellCmdA_dump(Dz1ShellCmdDumpArgA *p, Dz1ShellCmdEntryA *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ThreadA_tprintf(p->tab, p->fmt, e->name, e->help);
	return err;
}

void Dz1ShellCmdA_dump(Dz1ShellCmdA *p, int tab)
{
	if (p)
	{
		int len = 0;
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if ((err = Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)_Dz1ShellCmdA_dump, (void *)&len)).code == 0)
		{
			char fmt[1024];
			Dz1ShellCmdDumpArgA arg;
			arg.tab = tab;
			arg.fmt = fmt;

			sprintf(fmt, "%%%ds : %%s\n", len);
			Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)__Dz1ShellCmdA_dump, (void *)&arg);
		}
	}
}
// Dz1ShellCmdA
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellCmdW
static Dz1Error Dz1ShellCmdW_insert(Dz1ShellCmdW *p, wstr_t name, Dz1ShellCmdFuncW func, void *funcParam, wstr_t help)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellCmdEntryW *e = p->find(p, name);
	
	if (e) Dz1Error_set(&err, EEXIST);
	else if ((e = Dz1ShellCmdEntryW_new(name, func, funcParam, help, &err)) == NULL) { } 
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellCmdEntryW_del, (void *)&e);
		err = Dz1AATree_insert(p->tree, e);
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ShellCmdEntryW_del, (void *)&e);
	}
	return err;
}

static void Dz1ShellCmdW_remove(Dz1ShellCmdW *p, wstr_t name)
{
	Dz1ShellCmdEntryW key;
	key.name = name;
	Dz1AATree_remove(p->tree, &key);
}

static Dz1ShellCmdEntryW *Dz1ShellCmdW_find(Dz1ShellCmdW *p, wstr_t name)
{
	Dz1ShellCmdEntryW key;
	key.name = name;
	return (Dz1ShellCmdEntryW *)Dz1AATree_find(p->tree, &key);
}

typedef struct Dz1ShellCmdLikeArgW
{
	Dz1ShellCmdListW	*list;
	wstr_t				 name;
} Dz1ShellCmdLikeArgW;

static Dz1Error _Dz1ShellCmdW_like(Dz1ShellCmdLikeArgW *arg, Dz1ShellCmdEntryW *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (wcsncmp(e->name, arg->name, wcslen(arg->name)) == 0)
		err = arg->list->push(arg->list, e);
	return err;
}

static Dz1ShellCmdListW *Dz1ShellCmdW_like(Dz1ShellCmdW *p, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdListW *ret = Dz1ShellCmdListW_new(errp);
	if (ret)
	{
		Dz1ShellCmdLikeArgW arg;
		arg.list = ret;
		arg.name = name;

		pthread_cleanup_push(Dz1ShellCmdListW_delAndSetNull, (void *)&ret);
		*errp = Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)_Dz1ShellCmdW_like, (void *)&arg);
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdListW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1ShellCmdW *Dz1ShellCmdW_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellCmdW *ret = (Dz1ShellCmdW *)Dz1Malloc(sizeof(Dz1ShellCmdW), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellCmdW));
		pthread_cleanup_push(Dz1ShellCmdW_delAndSetNull, (void *)&ret);
		if ((ret->tree = Dz1AATree_new((Dz1CmpFunc)Dz1ShellCmdEntryW_cmp, (Dz1DelFunc)Dz1ShellCmdEntryW_del, (Dz1DumpFunc)Dz1ShellCmdEntryW_dump, errp)))
		{
			ret->insert = Dz1ShellCmdW_insert;
			ret->remove = Dz1ShellCmdW_remove;
			ret->find = Dz1ShellCmdW_find;
			ret->like = Dz1ShellCmdW_like;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellCmdW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ShellCmdW_del(Dz1ShellCmdW *p)
{
	if (!p) return;
	if (p->tree) Dz1AATree_del(p->tree);
	Dz1Free(p);
}

static Dz1Error _Dz1ShellCmdW_dump(int *len, Dz1ShellCmdEntryW *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int _len = (int)wcslen(e->name);
	if (*len < _len) *len = _len;
	return err;
}

typedef struct Dz1ShellCmdDumpArgW
{
	int		 tab;
	wstr_t	 fmt;
} Dz1ShellCmdDumpArgW;

static Dz1Error __Dz1ShellCmdW_dump(Dz1ShellCmdDumpArgW *p, Dz1ShellCmdEntryW *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ThreadW_tprintf(p->tab, p->fmt, e->name, e->help);
	return err;
}

void Dz1ShellCmdW_dump(Dz1ShellCmdW *p, int tab)
{
	if (p)
	{
		int len = 0;
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		if ((err = Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)_Dz1ShellCmdW_dump, (void *)&len)).code == 0)
		{
			wchar_t fmt[1024];
			Dz1ShellCmdDumpArgW arg;
			arg.tab = tab;
			arg.fmt = fmt;

			swprintf(fmt, 1023, L"%%%ds : %%s\n", len);
			Dz1AATree_travel(p->tree, (Dz1AATreeTravelFunc)__Dz1ShellCmdW_dump, (void *)&arg);
		}
	}
}
// Dz1ShellCmdW
///////////////////////////////////////////////////////////////////////////////
#endif