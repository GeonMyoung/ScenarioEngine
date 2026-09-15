#include <dz1_thread_stdio.h>
#include "Dz1JsonStructUtil.h"

void _undefined_entry_dump(Dz1JsonSpecEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab);
}

static Dz1Error _undefined_dump_(void *ptr, Dz1JsonSpecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = *(int *)ptr;
	_undefined_entry_dump(p, tab);
	Dz1Error_set(errp, 0);
	return err;
}

static void _undefined_dump(Dz1JsonSpecRefList *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	if (p->storage)
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		p->travel(p, _undefined_dump_, &tab);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}

void Dz1JsonSpecUndefinedEntry_dump(Dz1JsonSpecUndefinedEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab);

	if (p->refs == NULL) Dz1Thread_tprintf(tab, Dz1T("refs = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("refs = ")); _undefined_dump(p->refs, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

static bool_t Dz1JsonSpecUndefinedList_add(Dz1JsonSpecUndefinedList *dst, Dz1Str name, Dz1JsonSpecEntry *ref_node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecUndefinedEntry key = { name }, *node = dst->find(dst, &key);
	if (node != NULL)
	{
		if (node->refs->find(node->refs, ref_node) != NULL) { }
		else if ((*errp = node->refs->add(node->refs, ref_node)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((node = Dz1JsonSpecUndefinedEntry_new(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpecUndefinedEntry_delAndSetNull, (void *)&node);
		if ((*errp = node->refs->add(node->refs, ref_node)).code) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonSpecEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct Dz1JsonCheckArg
{
	Dz1JsonSpecEntry *e;
	Dz1JsonSpec *spec;
	Dz1JsonSpecUndefinedList *undefined;
} Dz1JsonCheckArg;

static Dz1Error _Dz1JsonSpecChild_check(void *ptr, Dz1JsonSpecChild *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonCheckArg *arg = (Dz1JsonCheckArg *)ptr;
	if (Dz1JsonSpec_findType(arg->spec, p->type) == NULL)
	{
		if (Dz1JsonSpecUndefinedList_add(arg->undefined, p->type, arg->e, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static bool_t Dz1JsonSpecConstruct_check(Dz1JsonSpecConstruct *p, Dz1JsonSpecEntry *e, Dz1JsonSpec *spec, Dz1JsonSpecUndefinedList *undefined, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecChilds *ch = p->childs;
	Dz1JsonCheckArg arg = { e, spec, undefined };
	if ((*errp = ch->travel(ch, _Dz1JsonSpecChild_check, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1JsonSpecArray_check(Dz1JsonSpecArray *p, Dz1JsonSpecEntry *e, Dz1JsonSpec *spec, Dz1JsonSpecUndefinedList *undefined, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1JsonSpec_findType(spec, p->elem_type) == NULL)
	{
		if (Dz1JsonSpecUndefinedList_add(undefined, p->elem_type, e, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1JsonSpecEntry_check(Dz1JsonSpecEntry *p, Dz1JsonSpec *spec, Dz1JsonSpecUndefinedList *undefined, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecData *d = p->data;
	switch(d->present)
	{
	case Dz1JsonSpecDataPresent_pr:		Dz1Error_set(errp, 0);																break;
	case Dz1JsonSpecDataPresent_cst:	if (Dz1JsonSpecConstruct_check(d->x.cst, p, spec, undefined, errp) == FALSE) ERR_OUT(errp);	break;
	case Dz1JsonSpecDataPresent_ar:		if (Dz1JsonSpecArray_check(d->x.ar, p, spec, undefined, errp) == FALSE) ERR_OUT(errp);			break;
	default:							Dz1Thread_printf(Dz1T("Unknown Spec Kind %d\n"), d->present); ERR_SET_OUT(errp, EFAULT);	break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonSpec_check(Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	Dz1JsonSpecList *types = spec->types;
	Dz1JsonSpecEntry **arr = types->get_array(types, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonSpecUndefinedList *undefined = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if ((undefined = Dz1JsonSpecUndefinedList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			pthread_cleanup_push(Dz1JsonSpecUndefinedList_delAndSetNull, (void *)&undefined);
			for (i = 0; errp->code == 0 && i < cnt; i++)
				if (Dz1JsonSpecEntry_check(arr[i], spec, undefined, errp) == FALSE) ERR_OUT(errp);

			if (errp->code == 0)
			{
				if (undefined->count(undefined) > 0)
				{
					Dz1Thread_printf(Dz1T("Unknown Type = ")); Dz1JsonSpecUndefinedList_dump(undefined, 0);
					ERR_SET_OUT(errp, ENOENT);
				}
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1JsonSpecUndefinedList_delAndSetNull, (void *)&undefined);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
