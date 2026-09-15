#include <dz1_asn1.h>

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes
Dz1Asn1EmbPdvSyntaxes *Dz1Asn1EmbPdvSyntaxes_new(Dz1Asn1OID *abstract, Dz1Asn1OID *transfer, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1EmbPdvSyntaxes *__internal_ret = (Dz1Asn1EmbPdvSyntaxes *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvSyntaxes), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvSyntaxes_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->abstract = abstract;
		__internal_ret->transfer = transfer;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvSyntaxes_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1EmbPdvSyntaxes *Dz1Asn1EmbPdvSyntaxes_clone(Dz1Asn1EmbPdvSyntaxes *src, Dz1Error *err)
{
	Dz1Asn1EmbPdvSyntaxes *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1EmbPdvSyntaxes *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvSyntaxes), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvSyntaxes_delAndSetNull, (void *)&ret);

		if (src->abstract && (ret->abstract = Dz1Asn1OID_clone(src->abstract, errp)) == NULL) ERR_OUT(errp);
		else if (src->transfer && (ret->transfer = Dz1Asn1OID_clone(src->transfer, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvSyntaxes_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1EmbPdvSyntaxes_del(Dz1Asn1EmbPdvSyntaxes *p)
{
	if (p == NULL) return;
	if (p->abstract) Dz1Asn1OID_del(p->abstract);
	if (p->transfer) Dz1Asn1OID_del(p->transfer);
	Dz1Free(p);
}

int Dz1Asn1EmbPdvSyntaxes_cmp(Dz1Asn1EmbPdvSyntaxes *a, Dz1Asn1EmbPdvSyntaxes *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		int ret = 0;
		if ((ret = Dz1Asn1OID_cmp(a->abstract, b->abstract)) != 0) { }
		else if ((ret = Dz1Asn1OID_cmp(a->transfer, b->transfer)) != 0) { }
		return ret;
	}
}

void Dz1Asn1EmbPdvSyntaxesA_dump(Dz1Asn1EmbPdvSyntaxes *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->abstract == NULL) Dz1ThreadA_tprintf(tab, "abstract = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "abstract = "); Dz1Asn1OIDA_dump(p->abstract, tab); /* using dump func */ }

	if (p->transfer == NULL) Dz1ThreadA_tprintf(tab, "transfer = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "transfer = "); Dz1Asn1OIDA_dump(p->transfer, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1EmbPdvSyntaxesA_fdump(FILE *fp, Dz1Asn1EmbPdvSyntaxes *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	if (p->abstract == NULL) Dz1ThreadA_ftprintf(fp, tab, "abstract = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "abstract = "); Dz1Asn1OIDA_fdump(fp, p->abstract, tab); }

	if (p->transfer == NULL) Dz1ThreadA_ftprintf(fp, tab, "transfer = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "transfer = "); Dz1Asn1OIDA_fdump(fp, p->transfer, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1EmbPdvSyntaxesW_dump(Dz1Asn1EmbPdvSyntaxes *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->abstract == NULL) Dz1ThreadW_tprintf(tab, L"abstract = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"abstract = "); Dz1Asn1OIDW_dump(p->abstract, tab); /* using dump func */ }

	if (p->transfer == NULL) Dz1ThreadW_tprintf(tab, L"transfer = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"transfer = "); Dz1Asn1OIDW_dump(p->transfer, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1EmbPdvSyntaxesW_fdump(FILE *fp, Dz1Asn1EmbPdvSyntaxes *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	if (p->abstract == NULL) Dz1ThreadW_ftprintf(fp, tab, L"abstract = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"abstract = "); Dz1Asn1OIDW_fdump(fp, p->abstract, tab); }

	if (p->transfer == NULL) Dz1ThreadW_ftprintf(fp, tab, L"transfer = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"transfer = "); Dz1Asn1OIDW_fdump(fp, p->transfer, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvSyntaxes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego
Dz1Asn1EmbPdvCtxNego *Dz1Asn1EmbPdvCtxNego_new(Dz1Asn1Int presentation_context_id, Dz1Asn1OID *transfer_syntax, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1EmbPdvCtxNego *__internal_ret = (Dz1Asn1EmbPdvCtxNego *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvCtxNego), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvCtxNego_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->presentation_context_id = presentation_context_id;
		__internal_ret->transfer_syntax = transfer_syntax;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvCtxNego_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1EmbPdvCtxNego *Dz1Asn1EmbPdvCtxNego_clone(Dz1Asn1EmbPdvCtxNego *src, Dz1Error *err)
{
	Dz1Asn1EmbPdvCtxNego *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1EmbPdvCtxNego *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvCtxNego), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvCtxNego_delAndSetNull, (void *)&ret);

		if (src->transfer_syntax && (ret->transfer_syntax = Dz1Asn1OID_clone(src->transfer_syntax, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->presentation_context_id = src->presentation_context_id;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvCtxNego_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1EmbPdvCtxNego_del(Dz1Asn1EmbPdvCtxNego *p)
{
	if (p == NULL) return;
	if (p->transfer_syntax) Dz1Asn1OID_del(p->transfer_syntax);
	Dz1Free(p);
}

int Dz1Asn1EmbPdvCtxNego_cmp(Dz1Asn1EmbPdvCtxNego *a, Dz1Asn1EmbPdvCtxNego *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		int ret = 0;
		if ((ret = Dz1Asn1Int_cmp(&a->presentation_context_id, &b->presentation_context_id)) != 0) { }
		else if ((ret = Dz1Asn1OID_cmp(a->transfer_syntax, b->transfer_syntax)) != 0) { }
		return ret;
	}
}
void Dz1Asn1EmbPdvCtxNegoA_dump(Dz1Asn1EmbPdvCtxNego *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	Dz1ThreadA_tprintf(tab, "presentation_context_id = "); Dz1Asn1IntA_dump(&p->presentation_context_id, tab);

	if (p->transfer_syntax == NULL) Dz1ThreadA_tprintf(tab, "transfer_syntax = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "transfer_syntax = "); Dz1Asn1OIDA_dump(p->transfer_syntax, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1EmbPdvCtxNegoA_fdump(FILE *fp, Dz1Asn1EmbPdvCtxNego *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	Dz1ThreadA_ftprintf(fp, tab, "presentation_context_id = "); Dz1Asn1IntA_fdump(fp, &p->presentation_context_id, tab);

	if (p->transfer_syntax == NULL) Dz1ThreadA_ftprintf(fp, tab, "transfer_syntax = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "transfer_syntax = "); Dz1Asn1OIDA_fdump(fp, p->transfer_syntax, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1EmbPdvCtxNegoW_dump(Dz1Asn1EmbPdvCtxNego *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	Dz1ThreadW_tprintf(tab, L"presentation_context_id = "); Dz1Asn1IntW_dump(&p->presentation_context_id, tab);

	if (p->transfer_syntax == NULL) Dz1ThreadW_tprintf(tab, L"transfer_syntax = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"transfer_syntax = "); Dz1Asn1OIDW_dump(p->transfer_syntax, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1EmbPdvCtxNegoW_fdump(FILE *fp, Dz1Asn1EmbPdvCtxNego *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	Dz1ThreadW_ftprintf(fp, tab, L"presentation_context_id = "); Dz1Asn1IntW_fdump(fp, &p->presentation_context_id, tab);

	if (p->transfer_syntax == NULL) Dz1ThreadW_ftprintf(fp, tab, L"transfer_syntax = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"transfer_syntax = "); Dz1Asn1OIDW_fdump(fp, p->transfer_syntax, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvCtxNego
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvIDPresent
static struct Dz1Asn1EmbPdvIDPresentMapA
{
	str_t str;
	Dz1Asn1EmbPdvIDPresent v;
} Dz1Asn1EmbPdvIDPresentMapA[] =
{
	{ (char *)"syntaxes", Dz1Asn1EmbPdvIDPresent_syntaxes },
	{ (char *)"syntax", Dz1Asn1EmbPdvIDPresent_syntax },
	{ (char *)"presentation_context_id", Dz1Asn1EmbPdvIDPresent_presentation_context_id },
	{ (char *)"context_negotiation", Dz1Asn1EmbPdvIDPresent_context_negotiation },
	{ (char *)"transfer_syntax", Dz1Asn1EmbPdvIDPresent_transfer_syntax },
	{ (char *)"fixed", Dz1Asn1EmbPdvIDPresent_fixed },
	{ NULL, Dz1Asn1EmbPdvIDPresent_max }
};

str_t Dz1Asn1EmbPdvIDPresentStrA(Dz1Asn1EmbPdvIDPresent v)
{
	struct Dz1Asn1EmbPdvIDPresentMapA *i = NULL;
	for (i = Dz1Asn1EmbPdvIDPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1EmbPdvIDPresent Dz1Asn1EmbPdvIDPresentFromStrA(str_t str)
{
	struct Dz1Asn1EmbPdvIDPresentMapA *i = NULL;
	for (i = Dz1Asn1EmbPdvIDPresentMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1Asn1EmbPdvIDPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1EmbPdvIDPresentMapW
{
	wstr_t str;
	Dz1Asn1EmbPdvIDPresent v;
} Dz1Asn1EmbPdvIDPresentMapW[] =
{
	{ (wchar_t *)L"syntaxes", Dz1Asn1EmbPdvIDPresent_syntaxes },
	{ (wchar_t *)L"syntax", Dz1Asn1EmbPdvIDPresent_syntax },
	{ (wchar_t *)L"presentation_context_id", Dz1Asn1EmbPdvIDPresent_presentation_context_id },
	{ (wchar_t *)L"context_negotiation", Dz1Asn1EmbPdvIDPresent_context_negotiation },
	{ (wchar_t *)L"transfer_syntax", Dz1Asn1EmbPdvIDPresent_transfer_syntax },
	{ (wchar_t *)L"fixed", Dz1Asn1EmbPdvIDPresent_fixed },
	{ NULL, Dz1Asn1EmbPdvIDPresent_max }
};

wstr_t Dz1Asn1EmbPdvIDPresentStrW(Dz1Asn1EmbPdvIDPresent v)
{
	struct Dz1Asn1EmbPdvIDPresentMapW *i = NULL;
	for (i = Dz1Asn1EmbPdvIDPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1EmbPdvIDPresent Dz1Asn1EmbPdvIDPresentFromStrW(wstr_t str)
{
	struct Dz1Asn1EmbPdvIDPresentMapW *i = NULL;
	for (i = Dz1Asn1EmbPdvIDPresentMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1Asn1EmbPdvIDPresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1EmbPdvIDPresent *Dz1Asn1EmbPdvIDPresent_new(Dz1Asn1EmbPdvIDPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1EmbPdvIDPresent *__internal_ret = (Dz1Asn1EmbPdvIDPresent *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvIDPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1Asn1EmbPdvIDPresentA_dump(Dz1Asn1EmbPdvIDPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1EmbPdvIDPresentStrA(*v));
}
void Dz1Asn1EmbPdvIDPresentA_fdump(FILE *fp, Dz1Asn1EmbPdvIDPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1EmbPdvIDPresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1EmbPdvIDPresentW_dump(Dz1Asn1EmbPdvIDPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1EmbPdvIDPresentStrW(*v));
}
void Dz1Asn1EmbPdvIDPresentW_fdump(FILE *fp, Dz1Asn1EmbPdvIDPresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1EmbPdvIDPresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdvIDPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID
Dz1Asn1EmbPdvID *Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1EmbPdvID *ret = (Dz1Asn1EmbPdvID *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvID), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1Asn1EmbPdvIDPresent_syntaxes:
				ret->x.syntaxes = (Dz1Asn1EmbPdvSyntaxes *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_syntax:
				ret->x.syntax = (Dz1Asn1OID *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
				if (ptr) ret->x.presentation_context_id = *(Dz1Asn1Int *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_context_negotiation:
				ret->x.context_negotiation = (Dz1Asn1EmbPdvCtxNego *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
				ret->x.transfer_syntax = (Dz1Asn1OID *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_fixed:
				if (ptr) ret->x.fixed = *(Dz1Asn1Null *)ptr; // Value Primitive Scalar Assign
				ERR_CLEAR(errp);
				break;
			case Dz1Asn1EmbPdvIDPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1EmbPdvID *Dz1Asn1EmbPdvID_clone(Dz1Asn1EmbPdvID *src, Dz1Error *err)
{
	Dz1Asn1EmbPdvID *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1Asn1EmbPdvID *)Dz1Calloc(sizeof(Dz1Asn1EmbPdvID), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&ret);

		ret->present = src->present;
		switch(ret->present)
		{
			case Dz1Asn1EmbPdvIDPresent_syntaxes:
				if (src->x.syntaxes && (ret->x.syntaxes = Dz1Asn1EmbPdvSyntaxes_clone(src->x.syntaxes, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1EmbPdvIDPresent_syntax:
				if (src->x.syntax && (ret->x.syntax = Dz1Asn1OID_clone(src->x.syntax, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
				ret->x.presentation_context_id = src->x.presentation_context_id;
				break;
			case Dz1Asn1EmbPdvIDPresent_context_negotiation:
				if (src->x.context_negotiation && (ret->x.context_negotiation = Dz1Asn1EmbPdvCtxNego_clone(src->x.context_negotiation, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
				if (src->x.transfer_syntax && (ret->x.transfer_syntax = Dz1Asn1OID_clone(src->x.transfer_syntax, errp)) == NULL) { ERR_OUT(errp); }
				break;
			case Dz1Asn1EmbPdvIDPresent_fixed:
				ret->x.fixed = src->x.fixed;
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1EmbPdvID_del(Dz1Asn1EmbPdvID *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			if (p->x.syntaxes) Dz1Asn1EmbPdvSyntaxes_del(p->x.syntaxes);
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			if (p->x.syntax) Dz1Asn1OID_del(p->x.syntax);
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			if (p->x.context_negotiation) Dz1Asn1EmbPdvCtxNego_del(p->x.context_negotiation);
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			if (p->x.transfer_syntax) Dz1Asn1OID_del(p->x.transfer_syntax);
			break;
		case Dz1Asn1EmbPdvIDPresent_fixed:
			break;
		default:
			break;
	}
	Dz1Free(p);
}

int Dz1Asn1EmbPdvID_cmp(Dz1Asn1EmbPdvID *a, Dz1Asn1EmbPdvID *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else if (a->present < b->present) return -1;
	else if (a->present > b->present) return 1;
	else
	{
		int ret = 0;
		switch(a->present)
		{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			ret = Dz1Asn1EmbPdvSyntaxes_cmp(a->x.syntaxes, b->x.syntaxes);
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			ret = Dz1Asn1OID_cmp(a->x.syntax, b->x.syntax);
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			ret = Dz1Asn1Int_cmp(&a->x.presentation_context_id, &b->x.presentation_context_id);
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			ret = Dz1Asn1EmbPdvCtxNego_cmp(a->x.context_negotiation, b->x.context_negotiation);
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			ret = Dz1Asn1OID_cmp(a->x.transfer_syntax, b->x.transfer_syntax);
			break;
		default:
		case Dz1Asn1EmbPdvIDPresent_fixed:
			// ret = Dz1Asn1Null_cmp(&a->x.fixed, &b->x.fixed);
			break;
		}
		return ret;
	}
}

void Dz1Asn1EmbPdvIDA_dump(Dz1Asn1EmbPdvID *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			if (p->x.syntaxes == NULL) Dz1ThreadA_tprintf(tab, "syntaxes = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "syntaxes = "); Dz1Asn1EmbPdvSyntaxesA_dump(p->x.syntaxes, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			if (p->x.syntax == NULL) Dz1ThreadA_tprintf(tab, "syntax = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "syntax = "); Dz1Asn1OIDA_dump(p->x.syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			Dz1ThreadA_tprintf(tab, "presentation_context_id = "); Dz1Asn1IntA_dump(&p->x.presentation_context_id, tab); // Value Primitive Scalar Type
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			if (p->x.context_negotiation == NULL) Dz1ThreadA_tprintf(tab, "context_negotiation = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "context_negotiation = "); Dz1Asn1EmbPdvCtxNegoA_dump(p->x.context_negotiation, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			if (p->x.transfer_syntax == NULL) Dz1ThreadA_tprintf(tab, "transfer_syntax = NULL\n");
			else { Dz1ThreadA_tprintf(tab, "transfer_syntax = "); Dz1Asn1OIDA_dump(p->x.transfer_syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_fixed:
			Dz1ThreadA_tprintf(tab, "fixed = "); Dz1Asn1NullA_dump(&p->x.fixed, tab); // Value Primitive Scalar Type
			break;
		default:
			Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
			break;
	}
}
void Dz1Asn1EmbPdvIDA_fdump(FILE *fp, Dz1Asn1EmbPdvID *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			if (p->x.syntaxes == NULL) Dz1ThreadA_fprintf(fp, "syntaxes = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "syntaxes = "); Dz1Asn1EmbPdvSyntaxesA_fdump(fp, p->x.syntaxes, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			if (p->x.syntax == NULL) Dz1ThreadA_fprintf(fp, "syntax = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "syntax = "); Dz1Asn1OIDA_fdump(fp, p->x.syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			Dz1ThreadA_fprintf(fp, "presentation_context_id = "); Dz1Asn1IntA_fdump(fp, &p->x.presentation_context_id, tab); // Value Primitive Scalar Type
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			if (p->x.context_negotiation == NULL) Dz1ThreadA_fprintf(fp, "context_negotiation = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "context_negotiation = "); Dz1Asn1EmbPdvCtxNegoA_fdump(fp, p->x.context_negotiation, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			if (p->x.transfer_syntax == NULL) Dz1ThreadA_fprintf(fp, "transfer_syntax = NULL\n");
			else { Dz1ThreadA_fprintf(fp, "transfer_syntax = "); Dz1Asn1OIDA_fdump(fp, p->x.transfer_syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_fixed:
			Dz1ThreadA_fprintf(fp, "fixed = "); Dz1Asn1NullA_fdump(fp, &p->x.fixed, tab); // Value Primitive Scalar Type
			break;
		default:
			Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
			break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1EmbPdvIDW_dump(Dz1Asn1EmbPdvID *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			if (p->x.syntaxes == NULL) Dz1ThreadW_tprintf(tab, L"syntaxes = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"syntaxes = "); Dz1Asn1EmbPdvSyntaxesW_dump(p->x.syntaxes, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			if (p->x.syntax == NULL) Dz1ThreadW_tprintf(tab, L"syntax = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"syntax = "); Dz1Asn1OIDW_dump(p->x.syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			Dz1ThreadW_tprintf(tab, L"presentation_context_id = "); Dz1Asn1IntW_dump(&p->x.presentation_context_id, tab); // Value Primitive Scalar Type
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			if (p->x.context_negotiation == NULL) Dz1ThreadW_tprintf(tab, L"context_negotiation = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"context_negotiation = "); Dz1Asn1EmbPdvCtxNegoW_dump(p->x.context_negotiation, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			if (p->x.transfer_syntax == NULL) Dz1ThreadW_tprintf(tab, L"transfer_syntax = NULL\n");
			else { Dz1ThreadW_tprintf(tab, L"transfer_syntax = "); Dz1Asn1OIDW_dump(p->x.transfer_syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_fixed:
			Dz1ThreadW_tprintf(tab, L"fixed = "); Dz1Asn1NullW_dump(&p->x.fixed, tab); // Value Primitive Scalar Type
			break;
		default:
			Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
			break;
	}
}
void Dz1Asn1EmbPdvIDW_fdump(FILE *fp, Dz1Asn1EmbPdvID *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	switch(p->present)
	{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:
			if (p->x.syntaxes == NULL) Dz1ThreadW_fprintf(fp, L"syntaxes = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"syntaxes = "); Dz1Asn1EmbPdvSyntaxesW_fdump(fp, p->x.syntaxes, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_syntax:
			if (p->x.syntax == NULL) Dz1ThreadW_fprintf(fp, L"syntax = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"syntax = "); Dz1Asn1OIDW_fdump(fp, p->x.syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:
			Dz1ThreadW_fprintf(fp, L"presentation_context_id = "); Dz1Asn1IntW_fdump(fp, &p->x.presentation_context_id, tab); // Value Primitive Scalar Type
			break;
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:
			if (p->x.context_negotiation == NULL) Dz1ThreadW_fprintf(fp, L"context_negotiation = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"context_negotiation = "); Dz1Asn1EmbPdvCtxNegoW_fdump(fp, p->x.context_negotiation, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:
			if (p->x.transfer_syntax == NULL) Dz1ThreadW_fprintf(fp, L"transfer_syntax = NULL\n");
			else { Dz1ThreadW_fprintf(fp, L"transfer_syntax = "); Dz1Asn1OIDW_fdump(fp, p->x.transfer_syntax, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1Asn1EmbPdvIDPresent_fixed:
			Dz1ThreadW_fprintf(fp, L"fixed = "); Dz1Asn1NullW_fdump(fp, &p->x.fixed, tab); // Value Primitive Scalar Type
			break;
		default:
			Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
			break;
	}
}
#endif // UNIX_SYSTEM

// Dz1Asn1EmbPdvID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv
Dz1Asn1EmbPdv *_Dz1Asn1EmbPdv_new(Dz1Asn1EmbPdvID *identifier, Dz1Asn1OctetStr *data_value, Dz1Error *err, const char *__file, int __line)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1EmbPdv *__internal_ret = (Dz1Asn1EmbPdv *)_Dz1Calloc(sizeof(Dz1Asn1EmbPdv), 1, errp, __file, __line);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdv_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->identifier = identifier;
		__internal_ret->data_value = data_value;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1EmbPdv *_Dz1Asn1EmbPdv_clone(Dz1Asn1EmbPdv *src, Dz1Error *err, const char *__file, int __line)
{
	Dz1Asn1EmbPdv *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1EmbPdv *)_Dz1Calloc(sizeof(Dz1Asn1EmbPdv), 1, errp, __file, __line)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdv_delAndSetNull, (void *)&ret);

		if (src->identifier && (ret->identifier = Dz1Asn1EmbPdvID_clone(src->identifier, errp)) == NULL) ERR_OUT(errp);
		else if (src->data_value_descriptor && (src->data_value_descriptor = _Dz1Asn1ObjDescr_clone(src->data_value_descriptor, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else if (src->data_value && (ret->data_value = _Dz1Asn1OctetStr_clone(src->data_value, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1EmbPdv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1EmbPdv_del(Dz1Asn1EmbPdv *p)
{
	if (p == NULL) return;
	if (p->identifier) Dz1Asn1EmbPdvID_del(p->identifier);
	if (p->data_value_descriptor) Dz1Asn1ObjDescr_del(p->data_value_descriptor);
	if (p->data_value) Dz1Asn1OctetStr_del(p->data_value);
	Dz1Free(p);
}

int Dz1Asn1EmbPdv_cmp(Dz1Asn1EmbPdv *a, Dz1Asn1EmbPdv *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		int ret = 0;
		if ((ret = Dz1Asn1EmbPdvID_cmp(a->identifier, b->identifier)) != 0) { }
		else if ((ret = Dz1Asn1ObjDescr_cmp(a->data_value_descriptor, b->data_value_descriptor)) != 0) { }
		else if ((ret = Dz1Asn1OctetStr_cmp(a->data_value, b->data_value)) != 0) { }
		return ret;
	}
}

void Dz1Asn1EmbPdvA_dump(Dz1Asn1EmbPdv *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->identifier == NULL) Dz1ThreadA_tprintf(tab, "identifier = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "identifier."); Dz1Asn1EmbPdvIDA_dump(p->identifier, tab); /* using dump func */ }

	if (p->data_value_descriptor == NULL) Dz1ThreadA_tprintf(tab, "data_value_descriptor = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "data_value_descriptor."); Dz1Asn1ObjDescrA_dump(p->data_value_descriptor, tab); /* using dump func */ }

	if (p->data_value == NULL) Dz1ThreadA_tprintf(tab, "data_value = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "data_value = "); Dz1Asn1OctetStrA_dump(p->data_value, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1EmbPdvA_fdump(FILE *fp, Dz1Asn1EmbPdv *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	if (p->identifier == NULL) Dz1ThreadA_ftprintf(fp, tab, "identifier = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "identifier."); Dz1Asn1EmbPdvIDA_fdump(fp, p->identifier, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadA_ftprintf(fp, tab, "data_value_descriptor = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "data_value_descriptor."); Dz1Asn1ObjDescrA_fdump(fp, p->data_value_descriptor, tab); /* using dump func */ }

	if (p->data_value == NULL) Dz1ThreadA_ftprintf(fp, tab, "data_value = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "data_value = "); Dz1Asn1OctetStrA_fdump(fp, p->data_value, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1EmbPdvW_dump(Dz1Asn1EmbPdv *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->identifier == NULL) Dz1ThreadW_tprintf(tab, L"identifier = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"identifier."); Dz1Asn1EmbPdvIDW_dump(p->identifier, tab); /* using dump func */ }

	if (p->data_value_descriptor == NULL) Dz1ThreadW_tprintf(tab, L"data_value_descriptor = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"data_value_descriptor."); Dz1Asn1ObjDescrW_dump(p->data_value_descriptor, tab); /* using dump func */ }

	if (p->data_value == NULL) Dz1ThreadW_tprintf(tab, L"data_value = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"data_value = "); Dz1Asn1OctetStrW_dump(p->data_value, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1EmbPdvW_fdump(FILE *fp, Dz1Asn1EmbPdv *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	if (p->identifier == NULL) Dz1ThreadW_ftprintf(fp, tab, L"identifier = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"identifier."); Dz1Asn1EmbPdvIDW_fdump(fp, p->identifier, tab); }

	if (p->data_value_descriptor == NULL) Dz1ThreadW_ftprintf(fp, tab, L"data_value_descriptor = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"data_value_descriptor."); Dz1Asn1ObjDescrW_fdump(fp, p->data_value_descriptor, tab); /* using dump func */ }

	if (p->data_value == NULL) Dz1ThreadW_ftprintf(fp, tab, L"data_value = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"data_value = "); Dz1Asn1OctetStrW_fdump(fp, p->data_value, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1EmbPdv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr
Dz1Asn1CharStr *_Dz1Asn1CharStr_new(Dz1Asn1EmbPdvID *identifier, Dz1Asn1OctetStr *str_value, Dz1Error *err, const char *__file, int __line)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1CharStr *__internal_ret = (Dz1Asn1CharStr *)_Dz1Calloc(sizeof(Dz1Asn1CharStr), 1, errp, __file, __line);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1CharStr_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->identifier = identifier;
		__internal_ret->str_value = str_value;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1CharStr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1Asn1CharStr *_Dz1Asn1CharStr_clone(Dz1Asn1CharStr *src, Dz1Error *err, const char *__file, int __line)
{
	Dz1Asn1CharStr *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1Asn1CharStr *)_Dz1Calloc(sizeof(Dz1Asn1CharStr), 1, errp, __file, __line)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Asn1CharStr_delAndSetNull, (void *)&ret);

		if (src->identifier && (ret->identifier = Dz1Asn1EmbPdvID_clone(src->identifier, errp)) == NULL) ERR_OUT(errp);
		else if (src->str_value_descriptor && (ret->str_value_descriptor = _Dz1Asn1ObjDescr_clone(src->str_value_descriptor, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else if (src->str_value && (ret->str_value = Dz1Asn1OctetStr_clone(src->str_value, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1CharStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1CharStr_del(Dz1Asn1CharStr *p)
{
	if (p == NULL) return;
	if (p->identifier) Dz1Asn1EmbPdvID_del(p->identifier);
	if (p->str_value_descriptor) Dz1Asn1ObjDescr_del(p->str_value_descriptor);
	if (p->str_value) Dz1Asn1OctetStr_del(p->str_value);
	Dz1Free(p);
}

int Dz1Asn1CharStr_cmp(Dz1Asn1CharStr *a, Dz1Asn1CharStr *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		int ret = 0;
		if ((ret = Dz1Asn1EmbPdvID_cmp(a->identifier, b->identifier)) != 0) { }
		else if ((ret = Dz1Asn1ObjDescr_cmp(a->str_value_descriptor, b->str_value_descriptor)) != 0) { }
		else if ((ret = Dz1Asn1OctetStr_cmp(a->str_value, b->str_value)) != 0) { }
		return ret;
	}
}

void Dz1Asn1CharStrA_dump(Dz1Asn1CharStr *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	Dz1ThreadA_printf("{\n"); tab++;

	if (p->identifier == NULL) Dz1ThreadA_tprintf(tab, "identifier = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "identifier."); Dz1Asn1EmbPdvIDA_dump(p->identifier, tab); /* using dump func */ }

	if (p->str_value_descriptor != NULL) { Dz1ThreadA_tprintf(tab, "str_value_descr = "); Dz1Asn1ObjDescrA_dump(p->str_value_descriptor, tab); /* using dump func */ }

	if (p->str_value == NULL) Dz1ThreadA_tprintf(tab, "str_value = NULL\n");
	else { Dz1ThreadA_tprintf(tab, "str_value = "); Dz1Asn1OctetStrA_dump(p->str_value, tab); /* using dump func */ }

	Dz1ThreadA_tprintf(--tab, "}\n");
}
void Dz1Asn1CharStrA_fdump(FILE *fp, Dz1Asn1CharStr *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	Dz1ThreadA_fprintf(fp, "{\n");tab++;

	if (p->identifier == NULL) Dz1ThreadA_ftprintf(fp, tab, "identifier = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "identifier."); Dz1Asn1EmbPdvIDA_fdump(fp, p->identifier, tab); }

	if (p->str_value_descriptor != NULL) { Dz1ThreadA_ftprintf(fp, tab, "str_value_descr = "); Dz1Asn1ObjDescrA_fdump(fp, p->str_value_descriptor, tab); /* using dump func */ }

	if (p->str_value == NULL) Dz1ThreadA_ftprintf(fp, tab, "str_value = NULL\n");
	else { Dz1ThreadA_ftprintf(fp, tab, "str_value = "); Dz1Asn1OctetStrA_fdump(fp, p->str_value, tab); }

	Dz1ThreadA_ftprintf(fp, --tab, "}\n");
}
#ifndef UNIX_SYSTEM
void Dz1Asn1CharStrW_dump(Dz1Asn1CharStr *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	Dz1ThreadW_printf(L"{\n"); tab++;

	if (p->identifier == NULL) Dz1ThreadW_tprintf(tab, L"identifier = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"identifier."); Dz1Asn1EmbPdvIDW_dump(p->identifier, tab); /* using dump func */ }

	if (p->str_value_descriptor != NULL) { Dz1ThreadW_tprintf(tab, L"str_value_descr = "); Dz1Asn1ObjDescrW_dump(p->str_value_descriptor, tab); /* using dump func */ }

	if (p->str_value == NULL) Dz1ThreadW_tprintf(tab, L"str_value = NULL\n");
	else { Dz1ThreadW_tprintf(tab, L"str_value = "); Dz1Asn1OctetStrW_dump(p->str_value, tab); /* using dump func */ }

	Dz1ThreadW_tprintf(--tab, L"}\n");
}
void Dz1Asn1CharStrW_fdump(FILE *fp, Dz1Asn1CharStr *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	Dz1ThreadW_fprintf(fp, L"{\n");tab++;

	if (p->identifier == NULL) Dz1ThreadW_ftprintf(fp, tab, L"identifier = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"identifier."); Dz1Asn1EmbPdvIDW_fdump(fp, p->identifier, tab); }

	if (p->str_value_descriptor != NULL) { Dz1ThreadW_ftprintf(fp, tab, L"str_value_descr = "); Dz1Asn1ObjDescrW_fdump(fp, p->str_value_descriptor, tab); /* using dump func */ }

	if (p->str_value == NULL) Dz1ThreadW_ftprintf(fp, tab, L"str_value = NULL\n");
	else { Dz1ThreadW_ftprintf(fp, tab, L"str_value = "); Dz1Asn1OctetStrW_fdump(fp, p->str_value, tab); }

	Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
}
#endif // UNIX_SYSTEM
// Dz1Asn1CharStr
////////////////////////////////////////////////////////////////////////////////

