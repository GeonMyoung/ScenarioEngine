////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_typedescr_def.h"

#include "dz1_asn1_types.h"
#include "dz1_asn1_typedescr.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1DefaultInfo
Dz1Asn1DefaultInfo *Dz1Asn1DefaultInfo_new(void *value, Dz1CmpFunc is_same, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1DefaultInfo *__internal_ret = (Dz1Asn1DefaultInfo *)Dz1Calloc(sizeof(Dz1Asn1DefaultInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1DefaultInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->value = value;
		__internal_ret->is_same = is_same;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1DefaultInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1DefaultInfo_purge(Dz1Asn1DefaultInfo *p)
{
	if (p == NULL) return;
}

void Dz1Asn1DefaultInfo_del(Dz1Asn1DefaultInfo *p)
{
	if (p == NULL) return;
	Dz1Asn1DefaultInfo_purge(p);
	Dz1Free(p);
}

// Dz1Asn1DefaultInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrPresencePresent
static struct Dz1Asn1TypeDescrPresencePresentMapA
{
	str_t str;
	Dz1Asn1TypeDescrPresencePresent v;
} Dz1Asn1TypeDescrPresencePresentMapA[] =
{
	{ (char *)"opt", Dz1Asn1TypeDescrPresencePresent_opt },
	{ (char *)"dflt", Dz1Asn1TypeDescrPresencePresent_dflt },
	{ NULL, Dz1Asn1TypeDescrPresencePresent_max }
};

str_t Dz1Asn1TypeDescrPresencePresentStrA(Dz1Asn1TypeDescrPresencePresent v)
{
	struct Dz1Asn1TypeDescrPresencePresentMapA *i = NULL;
	for (i = Dz1Asn1TypeDescrPresencePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TypeDescrPresencePresent Dz1Asn1TypeDescrPresencePresentFromStrA(str_t str)
{
	struct Dz1Asn1TypeDescrPresencePresentMapA *i = NULL;
	for (i = Dz1Asn1TypeDescrPresencePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TypeDescrPresencePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1TypeDescrPresencePresentMapW
{
	wstr_t str;
	Dz1Asn1TypeDescrPresencePresent v;
} Dz1Asn1TypeDescrPresencePresentMapW[] =
{
	{ (wchar_t *)L"opt", Dz1Asn1TypeDescrPresencePresent_opt },
	{ (wchar_t *)L"dflt", Dz1Asn1TypeDescrPresencePresent_dflt },
	{ NULL, Dz1Asn1TypeDescrPresencePresent_max }
};

wstr_t Dz1Asn1TypeDescrPresencePresentStrW(Dz1Asn1TypeDescrPresencePresent v)
{
	struct Dz1Asn1TypeDescrPresencePresentMapW *i = NULL;
	for (i = Dz1Asn1TypeDescrPresencePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1TypeDescrPresencePresent Dz1Asn1TypeDescrPresencePresentFromStrW(wstr_t str)
{
	struct Dz1Asn1TypeDescrPresencePresentMapW *i = NULL;
	for (i = Dz1Asn1TypeDescrPresencePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1TypeDescrPresencePresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1TypeDescrPresencePresent *Dz1Asn1TypeDescrPresencePresent_new(Dz1Asn1TypeDescrPresencePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TypeDescrPresencePresent *__internal_ret = (Dz1Asn1TypeDescrPresencePresent *)Dz1Calloc(sizeof(Dz1Asn1TypeDescrPresencePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1Asn1TypeDescrPresencePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescrPresence
Dz1Asn1TypeDescrPresence *Dz1Asn1TypeDescrPresence_new(Dz1Asn1TypeDescrPresencePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TypeDescrPresence *ret = (Dz1Asn1TypeDescrPresence *)Dz1Calloc(sizeof(Dz1Asn1TypeDescrPresence), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1TypeDescrPresence_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1TypeDescrPresencePresent_opt:
			// _U_prim_clone
			if (ptr != NULL) ret->x.opt = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1TypeDescrPresencePresent_dflt:
			// _U_cst_clone
			if (ptr != NULL) ret->x.dflt = (Dz1Asn1DefaultInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1TypeDescrPresencePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1TypeDescrPresence_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1TypeDescrPresence_purge(Dz1Asn1TypeDescrPresence *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1TypeDescrPresencePresent_opt:
		Dz1u32_del(p->x.opt);
		break;
	case Dz1Asn1TypeDescrPresencePresent_dflt:
		Dz1Asn1DefaultInfo_del(p->x.dflt);
		break;
	default:
		break;
	}
}

void Dz1Asn1TypeDescrPresence_del(Dz1Asn1TypeDescrPresence *p)
{
	if (!p) return;
	Dz1Asn1TypeDescrPresence_purge(p);
	Dz1Free(p);
}

// Dz1Asn1TypeDescrPresence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeDescr
Dz1Asn1TypeDescr *Dz1Asn1TypeDescr_new(Dz1Asn1UTF8Str *name, 
									   Dz1Asn1Tag *tag/*_ref*/, 
									   Dz1Asn1TypeDescrChild *childs/*_ref*/, 
									   Dz1Asn1TypeComformance *conformance/*_ref*/, 
									   Dz1Asn1TypeAPI *wip_api/*_ref*/, 
									   Dz1Asn1DataBerEncF ber_enc, 
									   Dz1Asn1DataBerDecF ber_dec, 
									   Dz1Asn1FinalizeF finalize, 
									   Dz1Asn1TypeAPI *user_api/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TypeDescr *__internal_ret = (Dz1Asn1TypeDescr *)Dz1Calloc(sizeof(Dz1Asn1TypeDescr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1TypeDescr_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->name = name;
		__internal_ret->tag = tag;
		__internal_ret->childs = childs;
		__internal_ret->conformance = conformance;
		__internal_ret->wip_api = wip_api;
		__internal_ret->ber_enc = ber_enc;
		__internal_ret->ber_dec = ber_dec;
		__internal_ret->finalize = finalize;
		__internal_ret->user_api = user_api;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1TypeDescr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1TypeDescr_purge(Dz1Asn1TypeDescr *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
}

void Dz1Asn1TypeDescr_del(Dz1Asn1TypeDescr *p)
{
	if (p == NULL) return;
	Dz1Asn1TypeDescr_purge(p);
	Dz1Free(p);
}

void Dz1Asn1TypeDescrA_dump(Dz1Asn1TypeDescr *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "name = "); Dz1Asn1UTF8StrA_dump(p->name, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "tag = "); Dz1Asn1TagA_dump(p->tag, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1TypeDescrA_fdump(FILE *fp, Dz1Asn1TypeDescr *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_ftprintf(fp, tab, "name = "); Dz1Asn1UTF8StrA_fdump(fp, p->name, tab); 
		// Normal member
		Dz1ThreadA_ftprintf(fp, tab, "tag = "); Dz1Asn1TagA_fdump(fp, p->tag, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1TypeDescrW_dump(Dz1Asn1TypeDescr *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"name = "); Dz1Asn1UTF8StrW_dump(p->name, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"tag = "); Dz1Asn1TagW_dump(p->tag, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1TypeDescrW_fdump(FILE *fp, Dz1Asn1TypeDescr *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_ftprintf(fp, tab, L"name = "); Dz1Asn1UTF8StrW_fdump(fp, p->name, tab); 
		// Normal member
		Dz1ThreadW_ftprintf(fp, tab, L"tag = "); Dz1Asn1TagW_fdump(fp, p->tag, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1TypeDescr
////////////////////////////////////////////////////////////////////////////////

