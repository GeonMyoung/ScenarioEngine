#include "dz1_asn1_types.h"
#include "dz1_asn1_typedescr.h"

Dz1Asn1TypeDescrPresence dz1Asn1TypeDescrChildPresence_optional = { Dz1Asn1TypeDescrPresencePresent_opt, { NULL } };

bool_t Dz1Asn1ApplyUtil_pointer_toss(void **_dst, Dz1Asn1WipValue *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipCst *src_cst = NULL;
	Dz1Asn1Custom *src_sto = NULL;

	if (_dst == NULL || *_dst != NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((src_cst = src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		(*_dst) = src_sto->data;
		src_sto->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Checker
static bool_t _chk_default(Dz1Asn1DefaultInfo *p, void *user_data)
{
	bool_t ret = FALSE;
	if (p != NULL && p->is_same != NULL && p->value != NULL && user_data != NULL)
		ret = p->is_same(p->value, user_data);
	return ret;
}

bool_t Dz1Asn1TypeDescrChild_isDefault(Dz1Asn1TypeDescrChild *p, void *data_ptr)
{
	bool_t ret = FALSE;
	Dz1Asn1TypeDescrPresence *presence = NULL;
	if ((presence = p->presence) != NULL)
	{
		switch(presence->present)
		{
		case Dz1Asn1TypeDescrPresencePresent_dflt: ret = _chk_default(presence->x.dflt, data_ptr); break;
		default: break;
		}
	}
	return ret;
}

bool_t Dz1Asn1TypeDescrChild_isOptional(Dz1Asn1TypeDescrChild *p, void *data_ptr)
{
	bool_t ret = FALSE;
	Dz1Asn1TypeDescrPresence *presence = NULL;
	if ((presence = p->presence) != NULL)
	{
		switch(presence->present)
		{
		case Dz1Asn1TypeDescrPresencePresent_opt: ret = TRUE; break;
		default: break;
		}
	}
	return ret;
}
// Checker
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr_findChild
static Dz1Asn1Tag _tag_explicited = Dz1Asn1TagVOID;
static bool_t Dz1Asn1Tag_isVOID(Dz1Asn1Tag *tag)
{
	bool_t ret = FALSE;
	if (tag == NULL || Dz1Asn1Tag_cmp(tag, &_tag_explicited) == 0) ret = TRUE;
	return ret;
}

typedef struct DescrFindChildStack
{
	struct DescrFindChildStack	*next;
	Dz1Asn1TypeDescr			*descr;
} DescrFindChildStack;

static bool_t _isDetermined(Dz1Asn1TypeDescr *descr, DescrFindChildStack *stk)
{
	bool_t ret = FALSE;
	if (stk != NULL)
	{
		DescrFindChildStack *i = NULL;
		for (i = stk; ret == FALSE && i != NULL; i = i->next)
			if (stk->descr == descr) ret = TRUE;
	}
	return ret;
}

static bool_t Dz1Asn1TypeDescr_hasTag(Dz1Asn1TypeDescr *descr, Dz1Asn1Tag *key, DescrFindChildStack *_stk);
static bool_t Dz1Asn1TypeDescr_childHasTag(Dz1Asn1TypeDescrChild *childs, Dz1Asn1Tag *key, DescrFindChildStack *_stk)
{
	bool_t ret = FALSE;
	Dz1Asn1TypeDescrChild *i;
	Dz1Asn1TypeDescr *descr = NULL;
	for (i = childs; ret == FALSE && i != NULL && i->descr != NULL; i++)
	{
		if (Dz1Asn1Tag_isCompatible(&i->tag, key)) ret = TRUE;
		else if (Dz1Asn1TypeDescr_hasTag(i->descr, key, _stk)) ret = TRUE;
	}
	return ret;
}

static bool_t Dz1Asn1TypeDescr_hasTag(Dz1Asn1TypeDescr *descr, Dz1Asn1Tag *key, DescrFindChildStack *_stk)
{
	bool_t ret = FALSE;
	if (_isDetermined(descr, _stk)) { }
	else if (Dz1Asn1Tag_isCompatible(descr->tag, key)) ret = TRUE;
	else if (descr->childs != NULL)
	{
		DescrFindChildStack stk = { _stk, descr };
		if (Dz1Asn1TypeDescr_childHasTag(descr->childs, key, &stk)) ret = TRUE;
	}
	return ret;
}

Dz1Asn1TypeDescrChild *Dz1Asn1TypeDescr_findChild(Dz1Asn1TypeDescr *descr, Dz1Asn1Tag *key, s32_t *opt_ret_idx)
{
	Dz1Asn1TypeDescrChild *ret = NULL;
	if (descr != NULL && key != NULL && descr->childs != NULL)
	{
		DescrFindChildStack stk = { NULL, descr };

		s32_t idx;
		Dz1Asn1TypeDescrChild *i = NULL;
		for (idx = 0, i = descr->childs; ret == NULL && i != NULL && Dz1Asn1TypeDescrChild_isNULL(i) == FALSE; i++, idx++)
		{
			if (Dz1Asn1Tag_isVOID(&i->tag) == FALSE)
			{	// not VOID Tag
				if (Dz1Asn1Tag_isCompatible(&i->tag, key))
				{
					ret = i;
					if (opt_ret_idx) *opt_ret_idx = idx;
				}
			}
			// i->tag == VOID
			else if (i->descr != NULL && Dz1Asn1TypeDescr_hasTag(i->descr, key, &stk))
			{
				ret = i;
				if (opt_ret_idx) *opt_ret_idx = idx;
			}
		}
	}

	if (ret == NULL)
	{	// error detail
		char str_key[64];
		Dz1Asn1TagA_printable(key, str_key, sizeof(str_key));
		Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "KEY = %s\n", str_key);
		if (descr == NULL) Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "descr = NULL\n");
		else if (descr->childs == NULL) Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "descr->childs = NULL\n");
		else
		{
			Dz1Asn1TypeDescrChild *i = NULL;
			for (i = descr->childs; i != NULL && Dz1Asn1TypeDescrChild_isNULL(i) == FALSE; i++)
			{
				Dz1Asn1TagA_printable(&i->tag, str_key, sizeof(str_key));
				Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "CHILDS = %s\n", str_key);
			}
		}
		ret = ret;
	}
	return ret;
}
// Dz1Asn1TypeDescr_findChild
///////////////////////////////////////////////////////////////////////////////

/*
///////////////////////////////////////////////////////////////////////////////
// Find OpenType
static bool_t Dz1Asn1TypeDescr_hasOpenType(Dz1Asn1TypeDescr *descr, DescrFindChildStack *_stk);
static bool_t Dz1Asn1TypeDescr_childHasOpenType(Dz1Asn1TypeDescrChild *childs, DescrFindChildStack *_stk)
{
	bool_t ret = FALSE;
	Dz1Asn1TypeDescrChild *i = NULL;
	for (i = childs; ret == FALSE && i != NULL && i->descr != NULL; i++)
	{
		if (i->descr != NULL)
		{
			if (i->descr == &dz1Asn1TypeDescrOpenType) ret = TRUE;
			else if (Dz1Asn1Tag_isVOID(&i->tag) && Dz1Asn1TypeDescr_hasOpenType(i->descr, _stk) == TRUE) ret = TRUE;
		}
	}
	return ret;
}

static bool_t Dz1Asn1TypeDescr_hasOpenType(Dz1Asn1TypeDescr *descr, DescrFindChildStack *_stk)
{
	bool_t ret = FALSE;
	if (_isDetermined(descr, _stk)) { }
	else if (descr->childs != NULL)
	{
		DescrFindChildStack stk = { _stk, descr };
		if (Dz1Asn1TypeDescr_childHasOpenType(descr->childs, &stk)) ret = TRUE;
	}
	return ret;
}

Dz1Asn1TypeDescrChild *Dz1Asn1TypeDescr_findChildOpenType(Dz1Asn1TypeDescr *descr, s32_t *opt_ret_idx)
{
	Dz1Asn1TypeDescrChild *ret = NULL;
	if (descr != NULL && descr->childs != NULL)
	{
		DescrFindChildStack stk = { NULL, descr };

		s32_t idx;
		Dz1Asn1TypeDescrChild *i = NULL;
		for (idx = 0, i = descr->childs; ret == NULL && i != NULL && i->descr != NULL; i++, idx++)
		{
			if (i->descr != NULL)
			{
				if (i->descr == &dz1Asn1TypeDescrOpenType)
				{
					ret = i;
					if (opt_ret_idx) *opt_ret_idx = idx;
				}
				else if (Dz1Asn1Tag_isVOID(&i->tag) && Dz1Asn1TypeDescr_hasOpenType(i->descr, &stk) == TRUE)
				{
					ret = i;
					if (opt_ret_idx) *opt_ret_idx = idx;
				}
			}
		}
	}
	return ret;
}
// Find OpenType
///////////////////////////////////////////////////////////////////////////////
*/

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr_chkConformanced
bool_t Dz1Asn1TypeDescr_chkConformance(Dz1Asn1TypeDescr *descr, void *user_data, bool_t *ret_is_ext)
{
	bool_t ret = FALSE;
	Dz1Asn1TypeComformance *c = NULL;
	if ((c = descr->conformance) == NULL) ret = TRUE;
	else if (c->check != NULL) ret = c->check(c->cons, user_data, ret_is_ext);

	return ret;
}
// Dz1Asn1TypeDescr_chkConformanced
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr_genCustom
Dz1Asn1Custom *Dz1Asn1TypeDescr_genWipCustom(Dz1Asn1TypeDescr *descr, Dz1Error *errp)
{
	Dz1Asn1Custom *ret = NULL;
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((api = descr->wip_api) == NULL)
		ERR_SET_OUT(errp, EFAULT);
	else if ((ret = __Dz1Asn1Custom_new(NULL, api->clone, api->del, api->dumpA, api->fdumpA, api->dumpW, api->fdumpW, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Custom_delAndSetNull, (void *)&ret);
		if ((ret->data = api->gen(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1Custom_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1Asn1TypeDescr_genCustom
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Type Descriptor Utility
void *Dz1Asn1TypeDescrData_gen(Dz1Asn1TypeDescr *descr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((api = descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (api->gen == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = api->gen(errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void *Dz1Asn1TypeDescrData_clone(Dz1Asn1TypeDescr *descr, void *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Asn1TypeAPI *api = NULL;
	if (src == NULL || descr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((api = descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (api->clone == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((ret = api->clone(src, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1TypeDescrDataA_dump(Dz1Asn1TypeDescr *descr, void *data, int tab)
{
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL || (api = descr->user_api) == NULL || api->dumpA == NULL) Dz1ThreadA_printf("%p(!)\n", data);
	else api->dumpA(data, tab);
}

void Dz1Asn1TypeDescrDataA_fdump(Dz1Asn1TypeDescr *descr, FILE *fp, void *data, int tab)
{
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL || (api = descr->user_api) == NULL || api->fdumpA == NULL) Dz1ThreadA_fprintf(fp, "%p(!)\n", data);
	else api->fdumpA(fp, data, tab);
}
#ifndef UNIX_SYSTEM
void Dz1Asn1TypeDescrDataW_dump(Dz1Asn1TypeDescr *descr, void *data, int tab)
{
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL || (api = descr->user_api) == NULL || api->dumpW == NULL) Dz1ThreadW_printf(L"%p(!)\n", data);
	else api->dumpW(data, tab);
}

void Dz1Asn1TypeDescrDataW_fdump(Dz1Asn1TypeDescr *descr, FILE *fp, void *data, int tab)
{
	Dz1Asn1TypeAPI *api = NULL;
	if (descr == NULL || (api = descr->user_api) == NULL || api->fdumpW == NULL) Dz1ThreadW_fprintf(fp, L"%p(!)\n", data);
	else api->fdumpW(fp, data, tab);
}
#endif
// Type Descriptor Utility
///////////////////////////////////////////////////////////////////////////////
