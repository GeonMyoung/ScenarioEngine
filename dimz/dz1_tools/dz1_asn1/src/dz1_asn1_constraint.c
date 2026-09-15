//#include "dz1_asn1_codec.h"
#include "dz1_asn1_types.h"
#include "dz1_asn1_typedescr.h"
#include "dz1_asn1_constraint.h"
#include "dz1_asn1_codec_ber.h"

///////////////////////////////////////////////////////////////////////////////
// Construct Child Value Constraint
static bool_t Dz1Asn1ConstructChildValueConstraint_match(Dz1Asn1TypeDescr *descr, void *childPtr, u8_t *value_data, u32_t value_size)
{
	bool_t ret = FALSE;
	if (descr != NULL && childPtr != NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1Asn1BerDecoder *decoder = Dz1Asn1BerDecoder_generate(descr, errp);
		if (descr == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1Stream *st = NULL;
			pthread_cleanup_push(Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
			if ((st = Dz1Asn1Stream_new(value_size, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ssize_t sz = 0;
				void *v_ptr = NULL;
				pthread_cleanup_push(Dz1Asn1Stream_delAndSetNull, (void *)&st);

				if (Dz1Asn1Stream_pushOctets(st, value_data, value_size, errp) == FALSE) ERR_OUT(errp);
				else if ((sz = Dz1Asn1BerDecoder_dec(decoder, st, NULL, errp)) < 0) ERR_OUT(errp);
				else if (sz == 0) ERR_SET_OUT(errp, EFAULT);
				else if ((v_ptr = Dz1Asn1BerDecoder_retrive(decoder, errp)) == NULL) ERR_OUT(errp);
				else if (descr->user_api->cmp(childPtr, v_ptr) == 0) ret = TRUE;

				pthread_cleanup_pop(1); // (Dz1Asn1Stream_delAndSetNull, (void *)&st);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
		}
	}
	return ret;
}

bool_t Dz1Asn1ConstructChildConstraint_match(Dz1Asn1ConstructChildConstraint *p, void *parentPtr)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		Dz1Binary *bin = NULL;
		void *child_ptr = p->getChildPtr(parentPtr, NULL);
		if ((bin = p->preEncoded) != NULL && bin->data != NULL && bin->size > 0 &&
			Dz1Asn1ConstructChildValueConstraint_match(p->childType, child_ptr, bin->data, bin->size) == FALSE) { }
		else
		{
			switch(p->presence)
			{
			case Dz1Asn1ConstructChildPresence_abssent: if (child_ptr == NULL) ret = TRUE; break;
			case Dz1Asn1ConstructChildPresence_present: if (child_ptr != NULL) ret = TRUE; break;
			case Dz1Asn1ConstructChildPresence_optional: ret = TRUE; break;
			}
		}
	}
	return ret;
}
// Construct Child Value Constraint
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraint Entry
Dz1Asn1ConstructConstraintEntry *Dz1Asn1ConstructConstraintEntry_new(Dz1Asn1ConstructChildConstraint *childs, u32_t childs_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1ConstructConstraintEntry *ret = NULL;
	if (childs == NULL || childs_cnt == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1ConstructConstraintEntry *)Dz1Calloc(sizeof(Dz1Asn1ConstructConstraintEntry), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ConstructConstraintEntry_delAndSetNull, (void *)&ret);
		_array_clone(Dz1Asn1ConstructChildConstraint, ret, childs, childs_cnt, childs, childs_cnt, err);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1ConstructConstraintEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1ConstructConstraintEntry_del(Dz1Asn1ConstructConstraintEntry *p)
{
	if (p == NULL) return;
	if (p->childs != NULL)
	{
		Dz1Free(p->childs);
		p->childs = NULL;
		p->childs_cnt = 0;
	}
	Dz1Free(p);
}

void Dz1Asn1ConstructConstraintEntryA_dump(Dz1Asn1ConstructConstraintEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructChildConstraint *c;
		Dz1ThreadA_printf("{\n"); tab++;
		for (i = 0, c = p->childs; i < p->childs_cnt; i++, p++)
		{
			Dz1ThreadA_tprintf(tab, "[%02d] : ", i + 1);
			Dz1Asn1ConstructChildConstraintA_dump(c, tab);
		}
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
void Dz1Asn1ConstructConstraintEntryA_fdump(FILE *fp, Dz1Asn1ConstructConstraintEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructChildConstraint *c;
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		for (i = 0, c = p->childs; i < p->childs_cnt; i++, p++)
		{
			Dz1ThreadA_ftprintf(fp, tab, "[%02d] : ", i + 1);
			Dz1Asn1ConstructChildConstraintA_fdump(fp, c, tab);
		}
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructConstraintEntryW_dump(Dz1Asn1ConstructConstraintEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructChildConstraint *c;
		Dz1ThreadW_printf(L"{\n"); tab++;
		for (i = 0, c = p->childs; i < p->childs_cnt; i++, p++)
		{
			Dz1ThreadW_tprintf(tab, L"[%02d] : ", i + 1);
			Dz1Asn1ConstructChildConstraintW_dump(c, tab);
		}
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}

void Dz1Asn1ConstructConstraintEntryW_fdump(FILE *fp, Dz1Asn1ConstructConstraintEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructChildConstraint *c;
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		for (i = 0, c = p->childs; i < p->childs_cnt; i++, p++)
		{
			Dz1ThreadW_ftprintf(fp, tab, L"[%02d] : ", i + 1);
			Dz1Asn1ConstructChildConstraintW_fdump(fp, c, tab);
		}
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif
bool_t Dz1Asn1ConstructConstraintEntry_match(Dz1Asn1ConstructConstraintEntry *p, void *ptr)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		u32_t i;
		ret = TRUE;
		for (i = 0; ret == TRUE && i < p->childs_cnt; i++)
			ret = Dz1Asn1ConstructChildConstraint_match(&p->childs[i], ptr);
	}
	return ret;
}
// Construct Constraint Entry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraint Group
Dz1Asn1ConstructConstraintGrp *Dz1Asn1ConstructConstraintGrp_new(Dz1Asn1ConstructConstraintTreeNode *arr, u32_t cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1ConstructConstraintGrp *ret = NULL;
	if (arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Asn1ConstructConstraintGrp *)Dz1Calloc(sizeof(Dz1Asn1ConstructConstraintGrp), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ConstructConstraintGrp_delAndSetNull, (void *)&ret);
		_array_clone(Dz1Asn1ConstructConstraintTreeNode, ret, collection_arr, collection_arr_cnt, arr, cnt, err);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1ConstructConstraintGrp_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Asn1ConstructConstraintGrp_del(Dz1Asn1ConstructConstraintGrp *p)
{
	if (p == NULL) return;
	if (p->collection_arr != NULL)
	{
		Dz1Free(p->collection_arr);
		p->collection_arr = NULL;
		p->collection_arr_cnt = 0;
	}
	Dz1Free(p);
}

void Dz1Asn1ConstructConstraintGrpA_dump(Dz1Asn1ConstructConstraintGrp *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructConstraintTreeNode *n;
		Dz1ThreadA_printf("{\n"); tab++;
		for (i = 0, n = p->collection_arr; i < p->collection_arr_cnt; i++, p++)
		{
			Dz1ThreadA_tprintf(tab, "[%02d] : ", i + 1);
			Dz1Asn1ConstructConstraintTreeNodeA_dump(n, tab);
		}
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}

void Dz1Asn1ConstructConstraintGrpA_fdump(FILE *fp, Dz1Asn1ConstructConstraintGrp *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructConstraintTreeNode *n;
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		for (i = 0, n = p->collection_arr; i < p->collection_arr_cnt; i++, p++)
		{
			Dz1ThreadA_ftprintf(fp, tab, "[%02d] : ", i + 1);
			Dz1Asn1ConstructConstraintTreeNodeA_fdump(fp, n, tab);
		}
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1ConstructConstraintGrpW_dump(Dz1Asn1ConstructConstraintGrp *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructConstraintTreeNode *n;
		Dz1ThreadW_printf(L"{\n"); tab++;
		for (i = 0, n = p->collection_arr; i < p->collection_arr_cnt; i++, p++)
		{
			Dz1ThreadW_tprintf(tab, L"[%02d] : ", i + 1);
			Dz1Asn1ConstructConstraintTreeNodeW_dump(n, tab);
		}
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
void Dz1Asn1ConstructConstraintGrpW_fdump(FILE *fp, Dz1Asn1ConstructConstraintGrp *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u32_t i;
		Dz1Asn1ConstructConstraintTreeNode *n;
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		for (i = 0, n = p->collection_arr; i < p->collection_arr_cnt; i++, p++)
		{
			Dz1ThreadW_ftprintf(fp, tab, L"[%02d] : ", i + 1);
			Dz1Asn1ConstructConstraintTreeNodeW_fdump(fp, n, tab);
		}
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif
bool_t Dz1Asn1ConstructConstraintGrp_matchALL(Dz1Asn1ConstructConstraintGrp *p, void *ptr)
{
	if (p != NULL)
	{
		u32_t i;
		for (i = 0; i < p->collection_arr_cnt; i++)
			if (Dz1Asn1ConstructConstraintTreeNode_match(&p->collection_arr[i], ptr) == FALSE) return FALSE;
		return TRUE;
	}
	return FALSE;
}

bool_t Dz1Asn1ConstructConstraintGrp_matchANY(Dz1Asn1ConstructConstraintGrp *p, void *ptr)
{
	if (p != NULL)
	{
		u32_t i;
		for (i = 0; i < p->collection_arr_cnt; i++)
			if (Dz1Asn1ConstructConstraintTreeNode_match(&p->collection_arr[i], ptr) == TRUE) return TRUE;
		return FALSE;
	}
	return FALSE;
}
// Construct Constraint Group
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construct Constraints Tree Node
bool_t Dz1Asn1ConstructConstraintTreeNode_match(Dz1Asn1ConstructConstraintTreeNode *p, void *ptr)
{
	bool_t ret = FALSE;
	if (p != NULL)
	{
		switch(p->present)
		{
		case Dz1Asn1ConstructConstraintTreeNodePresent_constraints:	ret = Dz1Asn1ConstructConstraintEntry_match(p->x.constraints, ptr); break;
		case Dz1Asn1ConstructConstraintTreeNodePresent_AND_grp:		ret = Dz1Asn1ConstructConstraintGrp_matchALL(p->x.AND_grp, ptr);	break;
		case Dz1Asn1ConstructConstraintTreeNodePresent_OR_grp:		ret = Dz1Asn1ConstructConstraintGrp_matchANY(p->x.OR_grp, ptr);		break;
		default: break;
		}
	}
	return ret;
}
// Construct Constraints Tree Node
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Length of Normal ASCII
size_t Dz1Asn1ASCIIStr_strlen(Dz1Asn1OctetStr *p)
{
	size_t ret = 0;
	if (p != NULL)
	{
		ret = p->size;
	}
	return ret;
}
// Length of Normal ASCII
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Fast UCS-4 Converter
u32_t *Dz1Asn1ASCIIStr_toUCS4(Dz1Asn1OctetStr *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (u32_t *)Dz1Calloc(sizeof(u32_t), p->size + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		for (i = 0; i < p->size; i++)
			ret[i] = (u32_t)p->data[i] & 0xFF;
	}
	return ret;
}
// Fast UCS-4 Converter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Known Multiplier Restricted String
static bool_t _asn_string_letter_match(Dz1Asn1MetaDataRangeInfo *permitted_alphabet, u32_t *ucs4, bool_t *ret_is_ext)
{
	bool_t ret = FALSE;
	if (permitted_alphabet != NULL && ucs4 != NULL)
	{
		u32_t *cp = ucs4;
		Dz1Asn1Int v;
		ret = TRUE;
		while(*cp)
		{
			v = (Dz1Asn1Int)*cp & 0xFFFFFFFF;
			if (Dz1Asn1MetaDataRangeInfo_match(permitted_alphabet, v, ret_is_ext) == FALSE) { ret = FALSE; break; }
			cp++;
		}
	}
	return ret;
}

static bool_t _asn_string_pattern_match(Dz1Asn1UTF8Str *pattern, u32_t *ucs4)
{
	// XXX : can't support pattern match yet
	return TRUE;
}

bool_t Dz1Asn1Constraint_KMS_match(Dz1Asn1Constraint *p, Dz1Asn1StringConformanceAPI *api, Dz1Asn1OctetStr *v, bool_t *ret_is_ext)
{	// Known Multiplier String Conformance
	bool_t ret = FALSE;
	if (p != NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);

		if (api == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			u32_t *ucs4 = NULL;
			s32_t sz = (s32_t)api->getLen(v);
			Dz1Asn1KnownMultiplerConstraints *str_conf = NULL;

			ret = TRUE;

			if (0) { }
			else if (p->size != NULL && Dz1Asn1MetaDataRange_match(p->size, (Dz1Asn1Int)sz) == FALSE) ret = FALSE;
			else if ((p->i_ranges != NULL || (str_conf = p->str_conf) != NULL) && (ucs4 = api->toUCS4(v, errp)) == NULL) ret = FALSE;
			else
			{	// Letter range check
				Dz1Asn1UTF8Str *pattern = ((str_conf == NULL) ? NULL : str_conf->pattern);
				pthread_cleanup_push(Dz1Memory_cancel, (VOID *)ucs4);

				if (0) { }
				else if (pattern != NULL	 && _asn_string_pattern_match(str_conf->pattern, ucs4) == FALSE)		ret = FALSE;
				else if (p->i_ranges != NULL && _asn_string_letter_match(p->i_ranges, ucs4, ret_is_ext) == FALSE)	ret = FALSE;
				else Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (VOID *)ucs4);
			}
		}
	}
	return ret;
}
// Known Multiplier Restricted String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Root Conformance Checker
bool_t Dz1Asn1Construct_conformance(Dz1Asn1Constraint *cons, void *ptr, bool_t *ret_is_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;
	if (cons == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ret = Dz1Asn1ConstructConstraintTreeNode_match(cons->components, ptr);
		Dz1Error_set(errp, 0);
	}
	return ret;
}
// Root Conformance Checker
///////////////////////////////////////////////////////////////////////////////

