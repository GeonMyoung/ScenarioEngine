#include <dz1_str.h>
#include "dz1_meta_tag_def.h"

void Dz1MetaTargetTypeEntry_dump(Dz1MetaTargetTypeEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("%08X:", p->type);
	if (p->name == NULL) Dz1Thread_tprintf(tab, "NULL\n");
	else Dz1Asn1UTF8Str_dump(p->name, tab);
}

typedef struct RestrictDumpArg
{
	bool_t isFirst;
} RestrictDumpArg;

static Dz1Error _restrict_dump(void *ptr, Dz1MetaTargetTypeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	RestrictDumpArg *arg = (RestrictDumpArg *)ptr;
	if (arg->isFirst)
	{
		Dz1Thread_printf("%u", p->type);
		arg->isFirst = FALSE;
	}
	else Dz1Thread_printf(", %u", p->type);

	return err;
}

void Dz1MetaTagRestrict_dump(Dz1MetaTagRestrict *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else
	{
		RestrictDumpArg arg = { TRUE };
		Dz1Thread_printf("[%s:", p->mode == Dz1MetaTagRestrictMode_accept ? "Accept" : "Reject");
		p->list->travel(p->list, _restrict_dump, (void *)&arg);
		Dz1Thread_printf("]\n");
	}
	/*
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "mode = %s(%d)\n", Dz1MetaTagRestrictModeStr(p->mode), p->mode);

	if (p->list == NULL) Dz1Thread_tprintf(tab, "list = NULL\n");
	else { Dz1Thread_tprintf(tab, "list = "); Dz1MetaTargetTypeList_dump(p->list, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
	*/
}


void Dz1MetaTagDescrEntry_dump(Dz1MetaTagDescrEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		size_t m_len = p->name ? p->name->size : 16;
		char *str = NULL;
		
		if (p->name != NULL)
		{
			if ((str = Dz1Asn1UTF8Str_toStr(p->name, NULL)) == NULL)
			{
				if ((str = Dz1Str_dup(Dz1T("#name_error"), NULL)) == NULL)
				{
					Dz1Thread_printf(Dz1T("#dump error\n"));
					return;
				}
			}
		}
		else if ((str = Dz1Str_dup(Dz1T("#name_error"), NULL)) == NULL)
		{
			Dz1Thread_printf(Dz1T("#dump error\n"));
			return;
		}

		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);

		Dz1Thread_printf("{\n"); tab++;
		Dz1Thread_tprintf(tab, "(%u)[%s]", p->id, str);
		if (p->status)
				Dz1MetaTagRestrict_dump(p->status, tab);
		else Dz1Thread_tprintf(0, "[No Restriction]\n");

		if (p->descr == NULL)
		{
			Dz1Thread_tprintf(tab, "storage = (null)\n");
		}
		else
		{
			Dz1Thread_tprintf(tab, "storage = "); Dz1MetaTagDescriptor_dump(p->descr, tab);
		}
		Dz1Thread_tprintf(--tab, "}\n");
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
	}
}

static Dz1Error _enum_fix_strings(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEnumTable *dst = (Dz1MetaTagDescrEnumTable *)ptr;
	if ((*errp = dst->add(dst, (Dz1MetaTagDescrEnumIndex *)p)).code) ERR_OUT(errp);
	return err;
}

Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_clone(Dz1MetaTagDescrEnums *src, Dz1Error *err)
{
	Dz1MetaTagDescrEnums *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1MetaTagDescrEnums *)Dz1Calloc(sizeof(Dz1MetaTagDescrEnums), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEnums_delAndSetNull, (void *)&ret);

		if (src->values && (ret->values = Dz1MetaTagDescrEnumList_clone(src->values, errp)) == NULL) ERR_OUT(errp);
		else if (src->strings && (ret->strings = Dz1MetaTagDescrEnumTable_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (ret->strings != NULL)
			{
				ret->values->travel(ret->values, _enum_fix_strings, (void *)ret->strings);
			}
			ret->add = src->add;
			ret->find = src->find;
			ret->extract = src->extract;
			ret->get_array = src->get_array;
			ret->getTail = src->getTail;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MetaTagDescrEnums_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MetaTagDescrAlias_dump(Dz1MetaTagDescrAlias *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else Dz1Thread_printf("%u\n", p->origin_descr_id);
	/*
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "origin_descr_id = "); Dz1u32_dump(&p->origin_descr_id, tab);

	if (p->origin_descr == NULL) Dz1Thread_tprintf(tab, "origin_descr = NULL\n");
	else { Dz1Thread_tprintf(tab, "origin_descr."); Dz1MetaTagDescriptor_dump(p->origin_descr, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
	*/
}

#if 0
void Dz1MetaTagDescrStrSet_dump(Dz1MetaTagDescrStrSet *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else if (p->history->count(p->history) == 0) Dz1Thread_printf("Empty\n");
	else
	{
		Dz1MetaTagDescrStrEntry *entry = p->curr;
		if (entry == NULL) entry = p->history->getTail(p->history);

		if (entry->name)
		{
			DZ1_ERROR_SAFE_VAR(errp, err);
			size_t m_len = entry->name->size;
			char *str = (char *)Dz1Calloc(sizeof(char), m_len + 1, errp);
			if (str == NULL) Dz1Thread_printf("ERRRO\n");
			else
			{
				pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);

				Dz1Asn1UTF8Str_printable(entry->name, "EUC-KR", str, m_len);
				Dz1Thread_printf("%u : %s\n", p->id, str);

				pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
			}
		}
		else Dz1Thread_printf("%u : (null)\n", p->id);
	}
	/*
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "id = "); Dz1u32_dump(&p->id, tab);

	if (p->history == NULL) Dz1Thread_tprintf(tab, "history = NULL\n");
	else { Dz1Thread_tprintf(tab, "history = "); Dz1MetaTagDescrStrList_dump(p->history, tab); }

	if (p->curr == NULL) Dz1Thread_tprintf(tab, "curr = NULL\n");
	else { Dz1Thread_tprintf(tab, "curr = "); Dz1MetaTagDescrStrEntry_dump(p->curr, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
	*/
}

#endif

// void Dz1MetaTagUserTypeEntry_dump(Dz1MetaTagUserTypeEntry *p, int tab)
// {
// 	if (!p) { Dz1Thread_printf("NULL\n"); return; }
// 	Dz1Thread_printf("{\n"); tab++;
// 
// 	Dz1Thread_tprintf(tab, "userType = "); Dz1u32_dump(&p->userType, tab);
// 	
// 	if (p->userData == NULL) Dz1Thread_tprintf(tab, "userData = NULL\n");
// 	else if (p->userDataDump == NULL) Dz1Thread_tprintf(tab, "userData = %p\n", p->userData);
// 	else { Dz1Thread_tprintf(tab, "userData = "); p->userDataDump(p->userData, tab); }
// 
// 	Dz1Thread_tprintf(--tab, "}\n");
// }

void Dz1MetaTagUserTypeEntry_del(Dz1MetaTagUserTypeEntry *p)
{
	if (p == NULL) return;
	if (p->userTypeName) Dz1Asn1UTF8Str_del(p->userTypeName);
	if (p->userTypeNameW) Dz1StrW_del(p->userTypeNameW);
	if (p->resource != NULL && p->resource_del != NULL) { p->resource_del(p->resource); p->resource = NULL; }
	if (p->userData != NULL && p->userDataDel != NULL) { p->userDataDel(p->userData); p->userData = NULL; }
	Dz1Free(p);
}

