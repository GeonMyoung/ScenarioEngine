#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>

#include "dz1_shell_var.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellVarEntryA
static void Dz1ShellVarEntryA_del(Dz1ShellVarEntryA *p)
{
	if (!p) return;
	if (p->name) Dz1StrA_del(p->name);
	if (p->value) Dz1StrA_del(p->value);
	Dz1Free(p);
}

static void Dz1ShellVarEntryA_delAndSetNull(void *ptr)
{
	Dz1ShellVarEntryA **p = (Dz1ShellVarEntryA **)ptr;
	Dz1ShellVarEntryA_del(*p); *p = NULL;
}

static Dz1ShellVarEntryA *Dz1ShellVarEntryA_new(str_t name, str_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellVarEntryA *ret = (Dz1ShellVarEntryA *)Dz1Malloc(sizeof(Dz1ShellVarEntryA), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellVarEntryA));
		pthread_cleanup_push(Dz1ShellVarEntryA_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrA_dup(name, errp)) == NULL) { }
		else if ((ret->value = Dz1StrA_dup(value, errp)) == NULL) { }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ShellVarEntryA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1ShellVarEntryA_dump(Dz1ShellVarEntryA *p, int tab)
{
	if (!p) return;
	Dz1ThreadA_tprintf(tab, "%s=%s\n", p->name, p->value);
}

static int Dz1ShellVarEntryA_cmp(Dz1ShellVarEntryA *a, Dz1ShellVarEntryA *b) { return Dz1StrA_cmp(a->name, b->name); }
// Dz1ShellVarEntryA
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellVarEntryW
static void Dz1ShellVarEntryW_del(Dz1ShellVarEntryW *p)
{
	if (!p) return;
	if (p->name) Dz1StrW_del(p->name);
	if (p->value) Dz1StrW_del(p->value);
	Dz1Free(p);
}

static void Dz1ShellVarEntryW_delAndSetNull(void *ptr)
{
	Dz1ShellVarEntryW **p = (Dz1ShellVarEntryW **)ptr;
	Dz1ShellVarEntryW_del(*p); *p = NULL;
}

static Dz1ShellVarEntryW *Dz1ShellVarEntryW_new(wstr_t name, wstr_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellVarEntryW *ret = (Dz1ShellVarEntryW *)Dz1Malloc(sizeof(Dz1ShellVarEntryW), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellVarEntryW));
		pthread_cleanup_push(Dz1ShellVarEntryW_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrW_dup(name, errp)) == NULL) { }
		else if ((ret->value = Dz1StrW_dup(value, errp)) == NULL) { }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ShellVarEntryW_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1ShellVarEntryW_dump(Dz1ShellVarEntryW *p, int tab)
{
	if (!p) return;
	Dz1ThreadW_tprintf(tab, L"%s=%s\n", p->name, p->value);
}

static int Dz1ShellVarEntryW_cmp(Dz1ShellVarEntryW *a, Dz1ShellVarEntryW *b) { return Dz1StrW_cmp(a->name, b->name); }
// Dz1ShellVarEntryW
///////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1ShellVarA
static Dz1Error Dz1ShellVarA_insert(Dz1ShellVarA *p, str_t name, str_t value)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellVarEntryA *e = Dz1ShellVarEntryA_new(name, value, &err);

	if (e)
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellVarEntryA_del, (void *)e);
		err = Dz1AATree_insert(p->tree, e);
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ShellVarEntryA_del, (void *)e);
	}
	return err;
}

static void Dz1ShellVarA_remove(Dz1ShellVarA *p, str_t name)
{
	Dz1ShellVarEntryA key;
	key.name = name;
	Dz1AATree_remove(p->tree, &key);
}

static str_t Dz1ShellVarA_find(Dz1ShellVarA *p, str_t name)
{
	Dz1ShellVarEntryA key, *e = NULL;
	key.name = name;
	if ((e = (Dz1ShellVarEntryA *)Dz1AATree_find(p->tree, &key)) != NULL) return e->value;
	return NULL;
}

Dz1ShellVarA *Dz1ShellVarA_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellVarA *ret = (Dz1ShellVarA *)Dz1Malloc(sizeof(Dz1ShellVarA), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellVarA));
		pthread_cleanup_push(Dz1ShellVarA_delAndSetNull, (void *)&ret);
		if ((ret->tree = Dz1AATree_new((Dz1CmpFunc)Dz1ShellVarEntryA_cmp, (Dz1DelFunc)Dz1ShellVarEntryA_del, (Dz1DumpFunc)Dz1ShellVarEntryA_dump, errp)))
		{
			ret->insert = Dz1ShellVarA_insert;
			ret->remove = Dz1ShellVarA_remove;
			ret->find = Dz1ShellVarA_find;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellVarA_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void Dz1ShellVarA_del(Dz1ShellVarA *p)
{
	if (!p) return;
	if (p->tree) Dz1AATree_del(p->tree);
	Dz1Free(p);
}

void Dz1ShellVarA_dump(Dz1ShellVarA *p, int tab)
{
	if (!p) return;
	Dz1AATree_dump(p->tree, tab);
}
// Dz1ShellVarA
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1ShellVarW
static Dz1Error Dz1ShellVarW_insert(Dz1ShellVarW *p, wstr_t name, wstr_t value)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ShellVarEntryW *e = Dz1ShellVarEntryW_new(name, value, &err);

	if (e)
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1ShellVarEntryW_del, (void *)e);
		err = Dz1AATree_insert(p->tree, e);
		pthread_cleanup_pop(err.code); // ((Dz1DelFunc)Dz1ShellVarEntryW_del, (void *)e);
	}
	return err;
}

static void Dz1ShellVarW_remove(Dz1ShellVarW *p, wstr_t name)
{
	Dz1ShellVarEntryW key;
	key.name = name;
	Dz1AATree_remove(p->tree, &key);
}

static wstr_t Dz1ShellVarW_find(Dz1ShellVarW *p, wstr_t name)
{
	Dz1ShellVarEntryW key, *e = NULL;
	key.name = name;
	if ((e = (Dz1ShellVarEntryW *)Dz1AATree_find(p->tree, &key)) != NULL) return e->value;
	return NULL;
}

Dz1ShellVarW *Dz1ShellVarW_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ShellVarW *ret = (Dz1ShellVarW *)Dz1Malloc(sizeof(Dz1ShellVarW), errp);
	if (ret)
	{
		memset(ret, 0, sizeof(Dz1ShellVarW));
		pthread_cleanup_push(Dz1ShellVarW_delAndSetNull, (void *)&ret);
		if ((ret->tree = Dz1AATree_new((Dz1CmpFunc)Dz1ShellVarEntryW_cmp, (Dz1DelFunc)Dz1ShellVarEntryW_del, (Dz1DumpFunc)Dz1ShellVarEntryW_dump, errp)))
		{
			ret->insert = Dz1ShellVarW_insert;
			ret->remove = Dz1ShellVarW_remove;
			ret->find = Dz1ShellVarW_find;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ShellVarW_delAndSetNull, (void *)&ret);
	}

	return ret;
}

void Dz1ShellVarW_del(Dz1ShellVarW *p)
{
	if (!p) return;
	if (p->tree) Dz1AATree_del(p->tree);
	Dz1Free(p);
}

void Dz1ShellVarW_dump(Dz1ShellVarW *p, int tab)
{
	if (!p) return;
	Dz1AATree_dump(p->tree, tab);
}
// Dz1ShellVarW
///////////////////////////////////////////////////////////////////////////////
#endif