////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_asn1_constraint_def.h"

#include "dz1_asn1_typedescr.h"
#include "dz1_asn1_constraint.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructChildPresence
static struct Dz1Asn1ConstructChildPresenceMapA
{
	str_t str;
	Dz1Asn1ConstructChildPresence v;
} Dz1Asn1ConstructChildPresenceMapA[] =
{
	{ (char *)"abssent", Dz1Asn1ConstructChildPresence_abssent },
	{ (char *)"present", Dz1Asn1ConstructChildPresence_present },
	{ (char *)"optional", Dz1Asn1ConstructChildPresence_optional },
	{ NULL, Dz1Asn1ConstructChildPresence_max }
};

str_t Dz1Asn1ConstructChildPresenceStrA(Dz1Asn1ConstructChildPresence v)
{
	struct Dz1Asn1ConstructChildPresenceMapA *i = NULL;
	for (i = Dz1Asn1ConstructChildPresenceMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ConstructChildPresence Dz1Asn1ConstructChildPresenceFromStrA(str_t str)
{
	struct Dz1Asn1ConstructChildPresenceMapA *i = NULL;
	for (i = Dz1Asn1ConstructChildPresenceMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ConstructChildPresence_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1ConstructChildPresenceMapW
{
	wstr_t str;
	Dz1Asn1ConstructChildPresence v;
} Dz1Asn1ConstructChildPresenceMapW[] =
{
	{ (wchar_t *)L"abssent", Dz1Asn1ConstructChildPresence_abssent },
	{ (wchar_t *)L"present", Dz1Asn1ConstructChildPresence_present },
	{ (wchar_t *)L"optional", Dz1Asn1ConstructChildPresence_optional },
	{ NULL, Dz1Asn1ConstructChildPresence_max }
};

wstr_t Dz1Asn1ConstructChildPresenceStrW(Dz1Asn1ConstructChildPresence v)
{
	struct Dz1Asn1ConstructChildPresenceMapW *i = NULL;
	for (i = Dz1Asn1ConstructChildPresenceMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ConstructChildPresence Dz1Asn1ConstructChildPresenceFromStrW(wstr_t str)
{
	struct Dz1Asn1ConstructChildPresenceMapW *i = NULL;
	for (i = Dz1Asn1ConstructChildPresenceMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ConstructChildPresence_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1ConstructChildPresence *Dz1Asn1ConstructChildPresence_new(Dz1Asn1ConstructChildPresence *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ConstructChildPresence *__internal_ret = (Dz1Asn1ConstructChildPresence *)Dz1Calloc(sizeof(Dz1Asn1ConstructChildPresence), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1ConstructChildPresenceA_dump(Dz1Asn1ConstructChildPresence *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1ConstructChildPresenceStrA(*v));
}
void Dz1Asn1ConstructChildPresenceA_fdump(FILE *fp, Dz1Asn1ConstructChildPresence *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1ConstructChildPresenceStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructChildPresenceW_dump(Dz1Asn1ConstructChildPresence *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1ConstructChildPresenceStrW(*v));
}
void Dz1Asn1ConstructChildPresenceW_fdump(FILE *fp, Dz1Asn1ConstructChildPresence *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1ConstructChildPresenceStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructChildPresence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructChildConstraint
Dz1Asn1ConstructChildConstraint *Dz1Asn1ConstructChildConstraint_new(Dz1Asn1TypeDescr *childType/*_ref*/, 
																	 Dz1Asn1GetChildF getChildPtr, 
																	 Dz1Binary *preEncoded, 
																	 Dz1Asn1ConstructChildPresence presence, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ConstructChildConstraint *__internal_ret = (Dz1Asn1ConstructChildConstraint *)Dz1Calloc(sizeof(Dz1Asn1ConstructChildConstraint), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1ConstructChildConstraint_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->childType = childType;
		__internal_ret->getChildPtr = getChildPtr;
		__internal_ret->preEncoded = preEncoded;
		__internal_ret->presence = presence;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1ConstructChildConstraint_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1ConstructChildConstraint_purge(Dz1Asn1ConstructChildConstraint *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->preEncoded);
}

void Dz1Asn1ConstructChildConstraint_del(Dz1Asn1ConstructChildConstraint *p)
{
	if (p == NULL) return;
	Dz1Asn1ConstructChildConstraint_purge(p);
	Dz1Free(p);
}

void Dz1Asn1ConstructChildConstraintA_dump(Dz1Asn1ConstructChildConstraint *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "childType = %p\n", p->childType);
		Dz1ThreadA_tprintf(tab, "getChildPtr = %p\n", p->getChildPtr);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "preEncoded = "); Dz1BinaryA_dump(p->preEncoded, tab); 
		Dz1ThreadA_tprintf(tab, "presence = %s(%d)\n", Dz1Asn1ConstructChildPresenceStrA(p->presence), p->presence);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1ConstructChildConstraintA_fdump(FILE *fp, Dz1Asn1ConstructChildConstraint *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_ftprintf(fp, tab, "childType = %p\n", p->childType);
		Dz1ThreadA_ftprintf(fp, tab, "getChildPtr = %p\n", p->getChildPtr);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_ftprintf(fp, tab, "preEncoded = "); Dz1BinaryA_fdump(fp, p->preEncoded, tab); 
		Dz1ThreadA_ftprintf(fp, tab, "presence = %s(%d)\n", Dz1Asn1ConstructChildPresenceStrA(p->presence), p->presence);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructChildConstraintW_dump(Dz1Asn1ConstructChildConstraint *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"childType = %p\n", p->childType);
		Dz1ThreadW_tprintf(tab, L"getChildPtr = %p\n", p->getChildPtr);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"preEncoded = "); Dz1BinaryW_dump(p->preEncoded, tab); 
		Dz1ThreadW_tprintf(tab, L"presence = %s(%d)\n", Dz1Asn1ConstructChildPresenceStrW(p->presence), p->presence);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1ConstructChildConstraintW_fdump(FILE *fp, Dz1Asn1ConstructChildConstraint *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_ftprintf(fp, tab, L"childType = %p\n", p->childType);
		Dz1ThreadW_ftprintf(fp, tab, L"getChildPtr = %p\n", p->getChildPtr);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_ftprintf(fp, tab, L"preEncoded = "); Dz1BinaryW_fdump(fp, p->preEncoded, tab); 
		Dz1ThreadW_ftprintf(fp, tab, L"presence = %s(%d)\n", Dz1Asn1ConstructChildPresenceStrW(p->presence), p->presence);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructChildConstraint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintTreeNodePresent
static struct Dz1Asn1ConstructConstraintTreeNodePresentMapA
{
	str_t str;
	Dz1Asn1ConstructConstraintTreeNodePresent v;
} Dz1Asn1ConstructConstraintTreeNodePresentMapA[] =
{
	{ (char *)"constraints", Dz1Asn1ConstructConstraintTreeNodePresent_constraints },
	{ (char *)"AND_grp", Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp },
	{ (char *)"OR_grp", Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp },
	{ NULL, Dz1Asn1ConstructConstraintTreeNodePresent_max }
};

str_t Dz1Asn1ConstructConstraintTreeNodePresentStrA(Dz1Asn1ConstructConstraintTreeNodePresent v)
{
	struct Dz1Asn1ConstructConstraintTreeNodePresentMapA *i = NULL;
	for (i = Dz1Asn1ConstructConstraintTreeNodePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ConstructConstraintTreeNodePresent Dz1Asn1ConstructConstraintTreeNodePresentFromStrA(str_t str)
{
	struct Dz1Asn1ConstructConstraintTreeNodePresentMapA *i = NULL;
	for (i = Dz1Asn1ConstructConstraintTreeNodePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ConstructConstraintTreeNodePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1Asn1ConstructConstraintTreeNodePresentMapW
{
	wstr_t str;
	Dz1Asn1ConstructConstraintTreeNodePresent v;
} Dz1Asn1ConstructConstraintTreeNodePresentMapW[] =
{
	{ (wchar_t *)L"constraints", Dz1Asn1ConstructConstraintTreeNodePresent_constraints },
	{ (wchar_t *)L"AND_grp", Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp },
	{ (wchar_t *)L"OR_grp", Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp },
	{ NULL, Dz1Asn1ConstructConstraintTreeNodePresent_max }
};

wstr_t Dz1Asn1ConstructConstraintTreeNodePresentStrW(Dz1Asn1ConstructConstraintTreeNodePresent v)
{
	struct Dz1Asn1ConstructConstraintTreeNodePresentMapW *i = NULL;
	for (i = Dz1Asn1ConstructConstraintTreeNodePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1Asn1ConstructConstraintTreeNodePresent Dz1Asn1ConstructConstraintTreeNodePresentFromStrW(wstr_t str)
{
	struct Dz1Asn1ConstructConstraintTreeNodePresentMapW *i = NULL;
	for (i = Dz1Asn1ConstructConstraintTreeNodePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1Asn1ConstructConstraintTreeNodePresent_max;
}
#endif // UNIX_SYSTEM

Dz1Asn1ConstructConstraintTreeNodePresent *Dz1Asn1ConstructConstraintTreeNodePresent_new(Dz1Asn1ConstructConstraintTreeNodePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ConstructConstraintTreeNodePresent *__internal_ret = (Dz1Asn1ConstructConstraintTreeNodePresent *)Dz1Calloc(sizeof(Dz1Asn1ConstructConstraintTreeNodePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1Asn1ConstructConstraintTreeNodePresentA_dump(Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s\n", Dz1Asn1ConstructConstraintTreeNodePresentStrA(*v));
}
void Dz1Asn1ConstructConstraintTreeNodePresentA_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab)
{
	if (v == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s\n", Dz1Asn1ConstructConstraintTreeNodePresentStrA(*v));
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructConstraintTreeNodePresentW_dump(Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s\n", Dz1Asn1ConstructConstraintTreeNodePresentStrW(*v));
}
void Dz1Asn1ConstructConstraintTreeNodePresentW_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNodePresent *v, int tab)
{
	if (v == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s\n", Dz1Asn1ConstructConstraintTreeNodePresentStrW(*v));
}
#endif // UNIX_SYSTEM
// Dz1Asn1ConstructConstraintTreeNodePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ConstructConstraintTreeNode
Dz1Asn1ConstructConstraintTreeNode *Dz1Asn1ConstructConstraintTreeNode_new(Dz1Asn1ConstructConstraintTreeNodePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1ConstructConstraintTreeNode *ret = (Dz1Asn1ConstructConstraintTreeNode *)Dz1Calloc(sizeof(Dz1Asn1ConstructConstraintTreeNode), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1ConstructConstraintTreeNode_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
			// _U_imp_clone
			if (ptr != NULL) ret->x.constraints = (Dz1Asn1ConstructConstraintEntry *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
			// _U_imp_clone
			if (ptr != NULL) ret->x.AND_grp = (Dz1Asn1ConstructConstraintGrp *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
			// _U_imp_clone
			if (ptr != NULL) ret->x.OR_grp = (Dz1Asn1ConstructConstraintGrp *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1Asn1ConstructConstraintTreeNodePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1ConstructConstraintTreeNode_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1ConstructConstraintTreeNode_purge(Dz1Asn1ConstructConstraintTreeNode *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
		Dz1Asn1ConstructConstraintEntry_del(p->x.constraints);
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
		Dz1Asn1ConstructConstraintGrp_del(p->x.AND_grp);
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
		Dz1Asn1ConstructConstraintGrp_del(p->x.OR_grp);
		break;
	default:
		break;
	}
}

void Dz1Asn1ConstructConstraintTreeNode_del(Dz1Asn1ConstructConstraintTreeNode *p)
{
	if (!p) return;
	Dz1Asn1ConstructConstraintTreeNode_purge(p);
	Dz1Free(p);
}

void Dz1Asn1ConstructConstraintTreeNodeA_dump(Dz1Asn1ConstructConstraintTreeNode *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
		Dz1ThreadA_printf("constraints = "); Dz1Asn1ConstructConstraintEntryA_dump(p->x.constraints, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
		Dz1ThreadA_printf("AND_grp = "); Dz1Asn1ConstructConstraintGrpA_dump(p->x.AND_grp, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
		Dz1ThreadA_printf("OR_grp = "); Dz1Asn1ConstructConstraintGrpA_dump(p->x.OR_grp, tab); 
		break;
	default:
		Dz1ThreadA_tprintf(tab, "??? = %d\n", p->present);
		break;
	}
}
void Dz1Asn1ConstructConstraintTreeNodeA_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNode *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
		Dz1ThreadA_fprintf(fp, "constraints = "); Dz1Asn1ConstructConstraintEntryA_fdump(fp, p->x.constraints, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
		Dz1ThreadA_fprintf(fp, "AND_grp = "); Dz1Asn1ConstructConstraintGrpA_fdump(fp, p->x.AND_grp, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
		Dz1ThreadA_fprintf(fp, "OR_grp = "); Dz1Asn1ConstructConstraintGrpA_fdump(fp, p->x.OR_grp, tab); 
		break;
	default:
		Dz1ThreadA_ftprintf(fp, tab, "??? = %d\n", p->present);
		break;
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructConstraintTreeNodeW_dump(Dz1Asn1ConstructConstraintTreeNode *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
		Dz1ThreadW_printf(L"constraints = "); Dz1Asn1ConstructConstraintEntryW_dump(p->x.constraints, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
		Dz1ThreadW_printf(L"AND_grp = "); Dz1Asn1ConstructConstraintGrpW_dump(p->x.AND_grp, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
		Dz1ThreadW_printf(L"OR_grp = "); Dz1Asn1ConstructConstraintGrpW_dump(p->x.OR_grp, tab); 
		break;
	default:
		Dz1ThreadW_tprintf(tab, L"??? = %d\n", p->present);
		break;
	}
}
void Dz1Asn1ConstructConstraintTreeNodeW_fdump(FILE *fp, Dz1Asn1ConstructConstraintTreeNode *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else switch(p->present)
	{
	case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:
		Dz1ThreadW_fprintf(fp, L"constraints = "); Dz1Asn1ConstructConstraintEntryW_fdump(fp, p->x.constraints, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:
		Dz1ThreadW_fprintf(fp, L"AND_grp = "); Dz1Asn1ConstructConstraintGrpW_fdump(fp, p->x.AND_grp, tab); 
		break;
	case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:
		Dz1ThreadW_fprintf(fp, L"OR_grp = "); Dz1Asn1ConstructConstraintGrpW_fdump(fp, p->x.OR_grp, tab); 
		break;
	default:
		Dz1ThreadW_ftprintf(fp, tab, L"??? = %d\n", p->present);
		break;
	}
}
#endif // UNIX_SYSTEM

// Dz1Asn1ConstructConstraintTreeNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1KnownMultiplerConstraints
Dz1Asn1KnownMultiplerConstraints *Dz1Asn1KnownMultiplerConstraints_new(Dz1Asn1UTF8Str *pattern, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1KnownMultiplerConstraints *__internal_ret = (Dz1Asn1KnownMultiplerConstraints *)Dz1Calloc(sizeof(Dz1Asn1KnownMultiplerConstraints), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1KnownMultiplerConstraints_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->pattern = pattern;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1KnownMultiplerConstraints_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1KnownMultiplerConstraints_purge(Dz1Asn1KnownMultiplerConstraints *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->pattern);
}

void Dz1Asn1KnownMultiplerConstraints_del(Dz1Asn1KnownMultiplerConstraints *p)
{
	if (p == NULL) return;
	Dz1Asn1KnownMultiplerConstraints_purge(p);
	Dz1Free(p);
}

void Dz1Asn1KnownMultiplerConstraintsA_dump(Dz1Asn1KnownMultiplerConstraints *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_printf("pattern = "); Dz1Asn1UTF8StrA_dump(p->pattern, tab); 
	}
}
void Dz1Asn1KnownMultiplerConstraintsA_fdump(FILE *fp, Dz1Asn1KnownMultiplerConstraints *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_fprintf(fp, "pattern = "); Dz1Asn1UTF8StrA_fdump(fp, p->pattern, tab); 
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1KnownMultiplerConstraintsW_dump(Dz1Asn1KnownMultiplerConstraints *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_printf(L"pattern = "); Dz1Asn1UTF8StrW_dump(p->pattern, tab); 
	}
}
void Dz1Asn1KnownMultiplerConstraintsW_fdump(FILE *fp, Dz1Asn1KnownMultiplerConstraints *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_fprintf(fp, L"pattern = "); Dz1Asn1UTF8StrW_fdump(fp, p->pattern, tab); 
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1KnownMultiplerConstraints
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Constraint
Dz1Asn1Constraint *Dz1Asn1Constraint_new(void *value, 
										 Dz1Asn1MetaDataRangeInfo *i_ranges, 
										 Dz1Asn1MetaDataRealRangeInfo *f_ranges, 
										 Dz1Asn1MetaDataRange *size, 
										 Dz1Asn1TypeDescr *type_of_any, 
										 Dz1Asn1Constraint *component/*_ref*/, 
										 Dz1Asn1ConstructConstraintTreeNode *components, 
										 Dz1Asn1KnownMultiplerConstraints *str_conf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1Constraint *__internal_ret = (Dz1Asn1Constraint *)Dz1Calloc(sizeof(Dz1Asn1Constraint), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1Constraint_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->value = value;
		__internal_ret->i_ranges = i_ranges;
		__internal_ret->f_ranges = f_ranges;
		__internal_ret->size = size;
		__internal_ret->type_of_any = type_of_any;
		__internal_ret->component = component;
		__internal_ret->components = components;
		__internal_ret->str_conf = str_conf;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1Constraint_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1Constraint_purge(Dz1Asn1Constraint *p)
{
	if (p == NULL) return;
	Dz1Asn1MetaDataRangeInfo_del(p->i_ranges);
	Dz1Asn1MetaDataRealRangeInfo_del(p->f_ranges);
	Dz1Asn1MetaDataRange_del(p->size);
	Dz1Asn1TypeDescr_del(p->type_of_any);
	Dz1Asn1ConstructConstraintTreeNode_del(p->components);
	Dz1Asn1KnownMultiplerConstraints_del(p->str_conf);
}

void Dz1Asn1Constraint_del(Dz1Asn1Constraint *p)
{
	if (p == NULL) return;
	Dz1Asn1Constraint_purge(p);
	Dz1Free(p);
}

void Dz1Asn1ConstraintA_dump(Dz1Asn1Constraint *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "value = %p\n", p->value);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "i_ranges = "); Dz1Asn1MetaDataRangeInfoA_dump(p->i_ranges, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_tprintf(tab, "f_ranges = "); Dz1Asn1MetaDataRealRangeInfoA_dump(p->f_ranges, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "size = "); Dz1Asn1MetaDataRangeA_dump(p->size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_tprintf(tab, "type_of_any = %p\n", p->type_of_any);
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_tprintf(tab, "component = %p\n", p->component);
		Dz1ThreadA_tprintf(tab, "components."); Dz1Asn1ConstructConstraintTreeNodeA_dump(p->components, tab); 
		// Normal member
		Dz1ThreadA_tprintf(tab, "str_conf = "); Dz1Asn1KnownMultiplerConstraintsA_dump(p->str_conf, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1ConstraintA_fdump(FILE *fp, Dz1Asn1Constraint *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintf(fp, tab, "value = %p\n", p->value);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_ftprintf(fp, tab, "i_ranges = "); Dz1Asn1MetaDataRangeInfoA_fdump(fp, p->i_ranges, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadA_ftprintf(fp, tab, "f_ranges = "); Dz1Asn1MetaDataRealRangeInfoA_fdump(fp, p->f_ranges, tab); 
		// Normal member
		Dz1ThreadA_ftprintf(fp, tab, "size = "); Dz1Asn1MetaDataRangeA_fdump(fp, p->size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadA_ftprintf(fp, tab, "type_of_any = %p\n", p->type_of_any);
		// Recursive member
		// Recursive but address dump
		Dz1ThreadA_ftprintf(fp, tab, "component = %p\n", p->component);
		Dz1ThreadA_ftprintf(fp, tab, "components."); Dz1Asn1ConstructConstraintTreeNodeA_fdump(fp, p->components, tab); 
		// Normal member
		Dz1ThreadA_ftprintf(fp, tab, "str_conf = "); Dz1Asn1KnownMultiplerConstraintsA_fdump(fp, p->str_conf, tab); 
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstraintW_dump(Dz1Asn1Constraint *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"value = %p\n", p->value);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"i_ranges = "); Dz1Asn1MetaDataRangeInfoW_dump(p->i_ranges, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_tprintf(tab, L"f_ranges = "); Dz1Asn1MetaDataRealRangeInfoW_dump(p->f_ranges, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"size = "); Dz1Asn1MetaDataRangeW_dump(p->size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_tprintf(tab, L"type_of_any = %p\n", p->type_of_any);
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_tprintf(tab, L"component = %p\n", p->component);
		Dz1ThreadW_tprintf(tab, L"components."); Dz1Asn1ConstructConstraintTreeNodeW_dump(p->components, tab); 
		// Normal member
		Dz1ThreadW_tprintf(tab, L"str_conf = "); Dz1Asn1KnownMultiplerConstraintsW_dump(p->str_conf, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1ConstraintW_fdump(FILE *fp, Dz1Asn1Constraint *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintf(fp, tab, L"value = %p\n", p->value);
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_ftprintf(fp, tab, L"i_ranges = "); Dz1Asn1MetaDataRangeInfoW_fdump(fp, p->i_ranges, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1ThreadW_ftprintf(fp, tab, L"f_ranges = "); Dz1Asn1MetaDataRealRangeInfoW_fdump(fp, p->f_ranges, tab); 
		// Normal member
		Dz1ThreadW_ftprintf(fp, tab, L"size = "); Dz1Asn1MetaDataRangeW_fdump(fp, p->size, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1ThreadW_ftprintf(fp, tab, L"type_of_any = %p\n", p->type_of_any);
		// Recursive member
		// Recursive but address dump
		Dz1ThreadW_ftprintf(fp, tab, L"component = %p\n", p->component);
		Dz1ThreadW_ftprintf(fp, tab, L"components."); Dz1Asn1ConstructConstraintTreeNodeW_fdump(fp, p->components, tab); 
		// Normal member
		Dz1ThreadW_ftprintf(fp, tab, L"str_conf = "); Dz1Asn1KnownMultiplerConstraintsW_fdump(fp, p->str_conf, tab); 
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// Dz1Asn1Constraint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Asn1TypeComformance
Dz1Asn1TypeComformance *Dz1Asn1TypeComformance_new(Dz1Asn1Constraint *cons, 
												   Dz1Asn1TypeComformanceF check, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Asn1TypeComformance *__internal_ret = (Dz1Asn1TypeComformance *)Dz1Calloc(sizeof(Dz1Asn1TypeComformance), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Asn1TypeComformance_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cons = cons;
		__internal_ret->check = check;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Asn1TypeComformance_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Asn1TypeComformance_purge(Dz1Asn1TypeComformance *p)
{
	if (p == NULL) return;
	Dz1Asn1Constraint_del(p->cons);
}

void Dz1Asn1TypeComformance_del(Dz1Asn1TypeComformance *p)
{
	if (p == NULL) return;
	Dz1Asn1TypeComformance_purge(p);
	Dz1Free(p);
}

// Dz1Asn1TypeComformance
////////////////////////////////////////////////////////////////////////////////

