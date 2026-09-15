#include "dz1_tdq_row_def_util.h"
#include "dz1_tdq_var_def_util.h"

int Dz1TdqSqlBlobRef_cmp(Dz1TdqSqlBlobRef *a, Dz1TdqSqlBlobRef *b)
{
    int ret = 0;
    if (a == NULL && b == NULL) { }
    else if (a == NULL /* && b != NULL*/) ret = -1;
    else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->sz < b->sz) ret = -1;
	else if (a->sz > b->sz) ret = 1;
	else if (a->ptr == NULL && b->ptr == NULL) ret = 0;
	else if (a->ptr == NULL /*&& b->ptr != NULL*/) ret = -1;
	else if (/*a->ptr != NULL &&*/ b->ptr == NULL) ret = 1;
	else ret = memcmp(a->ptr, b->ptr, a->sz);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStr
Dz1TdqSqlStr *Dz1TdqSqlStr_new(Dz1Str text, u32_t alloc_byte, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlStr *ret = NULL;
	
	if (text != NULL && alloc_byte == 0) ERR_SET_OUT(errp, 0); // { NULL, 0 }, { NULL, n }, "{ ptr, 0 }", { ptr, n }
	else if ((ret = (Dz1TdqSqlStr *)Dz1Calloc(sizeof(Dz1TdqSqlStr), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlStr_delAndSetNull, (void *)&ret);

		ret->alloc_byte = alloc_byte;

		if (text == NULL)
		{	// { NULL, 0 }, { NULL, n }
			if (alloc_byte > 0)
			{
				if ((ret->text = Dz1Calloc(alloc_byte, 1, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else Dz1Error_set(errp, 0);
		}
		// { ptr, n }
		else if ((ret->text = Dz1Calloc(alloc_byte, 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t src_byte = (u32_t)(Dz1STRLEN(text) * sizeof(TCHAR));
			u32_t dst_byte = alloc_byte - sizeof(TCHAR);
			u32_t copy_byte = src_byte < dst_byte ? src_byte : dst_byte;
			memcpy(ret->text, text, copy_byte);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TdqSqlStr *Dz1TdqSqlStr_newFromStr(Dz1Str str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlStr *ret = NULL;
	if (Dz1Str_isVoid(str)) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t len = (u32_t)((Dz1STRLEN(str) + 1) * sizeof(TCHAR));
		if ((ret = Dz1TdqSqlStr_new(NULL, len, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1STRCPY(ret->text, str);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

Dz1TdqSqlStr *Dz1TdqSqlStr_newFromBin(Dz1Binary *bin, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlStr *ret = NULL;
	if (bin == NULL || bin->data == NULL || bin->size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if ((ret = Dz1TdqSqlStr_new(NULL, bin->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			memcpy(ret->text, bin->data, bin->size);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}
// Dz1TdqSqlStr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlDate
Dz1TdqSqlDate *Dz1TdqSqlDate_genFromTM(struct tm *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlDate *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlDate_new((u16_t)(p->tm_year + 1900), p->tm_mon + 1, p->tm_mday, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1TdqSqlDate_setFromT(Dz1TdqSqlDate *dst, time_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct tm *tm_p = NULL;
	if (dst == NULL || (tm_p = gmtime(&src)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmV = *tm_p;
		dst->year = tmV.tm_year + 1900;
		dst->month = tmV.tm_mon + 1;
		dst->day = tmV.tm_mday;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void Dz1TdqSqlDate_dump(Dz1TdqSqlDate *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("%04d-%02u-%02u\n"), p->year, p->month, p->day);
}
// Dz1TdqSqlDate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlTime
Dz1TdqSqlTime *Dz1TdqSqlTime_genFromTM(struct tm *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlTime *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlTime_new(p->tm_hour, p->tm_min, p->tm_sec, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1TdqSqlTime_setFromT(Dz1TdqSqlTime *dst, time_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct tm *tm_p = NULL;
	if (dst == NULL || (tm_p = gmtime(&src)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmV = *tm_p;
		dst->hour = tmV.tm_hour;
		dst->minute = tmV.tm_min;
		dst->second = tmV.tm_sec;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void Dz1TdqSqlTime_dump(Dz1TdqSqlTime *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("%02u:%02u:%02u\n"), p->hour, p->minute, p->second);
}
// Dz1TdqSqlTime
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlStamp
Dz1TdqSqlStamp *Dz1TdqSqlStamp_genFromTM(struct tm *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlStamp *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlStamp_new((u16_t)(p->tm_year + 1900), p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, 0, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1TdqSqlStamp_setFromT(Dz1TdqSqlStamp *dst, time_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct tm *tm_p = NULL;
	if (dst == NULL || (tm_p = gmtime(&src)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmV = *tm_p;
		dst->year = tmV.tm_year + 1900;
		dst->month = tmV.tm_mon + 1;
		dst->day = tmV.tm_mday;
		dst->hour = tmV.tm_hour;
		dst->minute = tmV.tm_min;
		dst->second = tmV.tm_sec;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void Dz1TdqSqlStamp_dump(Dz1TdqSqlStamp *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("%04d-%02u-%02u %02u:%02u:%02u(%u)\n"), p->year, p->month, p->day, p->hour, p->minute, p->second, p->frac);
}
// Dz1TdqSqlStamp
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlBlob
void Dz1TdqSqlBlob_dump(Dz1TdqSqlBlob *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		Dz1Binary2 *bin = NULL;
		Dz1TdqSqlBlobRef *rbuf = NULL;
		Dz1TdqSqlBlobFromDB *r = NULL;
		Dz1TdqSqlBlobToDB *w = NULL;

		Dz1Thread_printf(Dz1T("RD:"));
		if ((r = p->readFromDB) == NULL) Dz1Thread_printf(Dz1T("NULL"));
		else 
		{ 
			Dz1Thread_printf(Dz1T("%s:"), Dz1TdqSqlBlobFromDBPresentStrA(r->present));
			switch(r->present)
			{
			case Dz1TdqSqlBlobFromDBPresent_embedded:
				if ((bin = r->x.embedded) == NULL || bin->data == NULL) Dz1Thread_printf(Dz1T("NULL"));
				else if (bin->size == 0) Dz1Thread_tprintf(tab, Dz1T("Empty"));
				else Dz1Thread_printf(Dz1T("%u Byte"), bin->size);
				break;
			case Dz1TdqSqlBlobFromDBPresent_saved_file:
				Dz1Thread_printf(Dz1T("%s"), r->x.saved_file);
				break;
			default:
				break;
			}
		}

		Dz1Thread_printf(Dz1T(", WR:"));
		if ((w = p->writeToDB) == NULL) Dz1Thread_printf(Dz1T("NULL"));
		else 
		{
			Dz1Thread_printf(Dz1T("%s:"), Dz1TdqSqlBlobToDBPresentStrA(w->present));
			switch(w->present)
			{
			case Dz1TdqSqlBlobToDBPresent_embedded:
				if ((bin = w->x.embedded) == NULL || bin->data == NULL) Dz1Thread_printf(Dz1T("NULL"));
				else if (bin->size == 0) Dz1Thread_tprintf(tab, Dz1T("Empty"));
				else Dz1Thread_printf(Dz1T("%u Byte"), bin->size);
				break;
			case Dz1TdqSqlBlobToDBPresent_ref_buf:
				if ((rbuf = w->x.ref_buf) == NULL || rbuf->ptr == NULL) Dz1Thread_printf(Dz1T("NULL"));
				else if (rbuf->sz == 0) Dz1Thread_tprintf(tab, Dz1T("Empty"));
				else Dz1Thread_printf(Dz1T("%u Byte"), rbuf->sz);
				break;
			case Dz1TdqSqlBlobToDBPresent_saved_file:
				Dz1Thread_printf(Dz1T("%s"), w->x.saved_file);
				break;
			default:
				break;
			}
		}
		Dz1Thread_tprintf(tab, Dz1T(", iosz = ") DZ1_FMT64 Dz1T("\n"), p->iosz);
	}
}
// Dz1TdqSqlBlob
///////////////////////////////////////////////////////////////////////////////

void Dz1TdqSqlVar_setNullValue(Dz1TdqSqlVar *p)
{
	if (p != NULL)
	{
		Dz1TdqSqlVarPresent present = p->present;
		u32_t cat = _category_of(present);
		switch(cat)
		{
		case 0:	// num
		case 1:	// real
			break;
		case 2:	// str&bin
			switch(present)
			{
			case Dz1TdqSqlVarPresent_binary:
			case Dz1TdqSqlVarPresent_vbinary:
				Dz1Binary2_delAndSetNull(&p->x.__ptr__);
				break;
			default:
				Dz1TdqSqlStr_delAndSetNull(&p->x.__ptr__);
				break;
			}
			break;
		case 3:	// date&time
			switch(present)
			{
			case Dz1TdqSqlVarPresent_ymd: Dz1TdqSqlDate_delAndSetNull(&p->x.__ptr__); break;
			case Dz1TdqSqlVarPresent_hms: Dz1TdqSqlTime_delAndSetNull(&p->x.__ptr__); break;
			case Dz1TdqSqlVarPresent_stamp: Dz1TdqSqlStamp_delAndSetNull(&p->x.__ptr__); break;
			default: break;
			}
			break;
		case 4:	// blob
			Dz1TdqSqlBlob_delAndSetNull(&p->x.__ptr__); 
			break;
		case 15: // null
		default:
			break;
		}
		p->present = Dz1TdqSqlVarPresent_nul;
		p->x.nul = present;
	}
}

bool_t Dz1TdqSqlVarGetStr(Dz1Str *dst, Dz1TdqSqlVar *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present == Dz1TdqSqlVarPresent_nul)
		Dz1Str_delAndSetNull(dst);
	else if (_category_of(src->present) != 0x02 || src->present == Dz1TdqSqlVarPresent_binary || src->present == Dz1TdqSqlVarPresent_vbinary) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1TdqSqlStr *spec = (Dz1TdqSqlStr *)src->x.__ptr__;
		if (spec->text[0] == 0) Dz1Str_delAndSetNull(dst);
		else if (( (*dst) = Dz1Str_dup(spec->text, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqSqlVarGetBin(Dz1Binary **dst, Dz1TdqSqlVar *src, long len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present == Dz1TdqSqlVarPresent_nul)
		Dz1Binary_delAndSetNull(dst);
	else if (src->present != Dz1TdqSqlVarPresent_binary && src->present != Dz1TdqSqlVarPresent_vbinary) ERR_SET_OUT(errp, EINVAL);
	else
	{
//		Dz1TdqSqlStr *spec = (Dz1TdqSqlStr *)src->x.__ptr__;
// 		if (spec->text[0] == 0) Dz1Str_delAndSetNull(dst);
// 		else if (( (*dst) = Dz1Str_dup(spec->text, errp)) == NULL) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
		Dz1Binary2 *bin = src->x.binary;
		if (bin == NULL || bin->data == NULL || bin->size == 0) Dz1Binary_delAndSetNull(dst);
		else if (( (*dst) = Dz1Binary_new(bin->data, (u32_t)len, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarArray Generation from ColRefSeq
static Dz1TdqSqlBlob *Dz1TdqSqlBlob_genFromSpec(Dz1TdqSqlBlobSpec spec, Dz1Error *errp)
{
	Dz1TdqSqlBlob *ret = Dz1TdqSqlBlob_new(NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlBlobToDB *w = NULL;
		Dz1TdqSqlBlobFromDB *r = NULL;
		pthread_cleanup_push(Dz1TdqSqlBlob_delAndSetNull, (void *)&ret);
		switch(spec)
		{
		case Dz1TdqSqlBlobSpec_embedded:
			if ((ret->readFromDB = r = Dz1TdqSqlBlobFromDB_new(Dz1TdqSqlBlobFromDBPresent_embedded, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlBlobSpec_saved_file:
			if ((ret->readFromDB = r = Dz1TdqSqlBlobFromDB_new(Dz1TdqSqlBlobFromDBPresent_saved_file, NULL, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlBlob_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1TdqSqlVar *Dz1TdqSqlVar_genFromSpec(Dz1TdqSqlTypeSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = Dz1TdqSqlVar_new(spec->present, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
		switch(ret->present)
		{
		case Dz1TdqSqlVarPresent_string:
		case Dz1TdqSqlVarPresent_vstring:
		case Dz1TdqSqlVarPresent_tstring:
		case Dz1TdqSqlVarPresent_vtstring:
			if ((ret->x.__ptr__ = Dz1TdqSqlStr_new(NULL, (u32_t)((spec->x.string->size + 1) * sizeof(TCHAR)), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlVarPresent_binary:
		case Dz1TdqSqlVarPresent_vbinary:
			if ((ret->x.__ptr__ = Dz1Binary2_new(DZ1_BIN_DATA_ALLOC, (u32_t)(spec->x.binary->size), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlVarPresent_ymd:
			if ((ret->x.ymd = Dz1TdqSqlDate_gen(errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlVarPresent_hms:
			if ((ret->x.hms = Dz1TdqSqlTime_gen(errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlVarPresent_stamp:
			if ((ret->x.stamp = Dz1TdqSqlStamp_gen(errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlVarPresent_blob:
		case Dz1TdqSqlVarPresent_blobL:
			if ((ret->x.blob = Dz1TdqSqlBlob_genFromSpec(spec->x.blob, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			break;
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error VarArray_genFromSpec(void *ptr, Dz1TdqColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlVarArray *dst = (Dz1TdqSqlVarArray *)ptr;
	Dz1TdqSqlTypeSpec *spec = p->sql_type;
	Dz1TdqSqlVar *node = Dz1TdqSqlVar_genFromSpec(spec, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_genFromSpec(Dz1TdqColumnRefSeq *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVarArray *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlVarArray_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
		if ((*errp = src->travel(src, VarArray_genFromSpec, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1TdqSqlVarArray Generation from ColRefSeq
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarArray Generation from Select Row
static Dz1TdqSqlVar *Dz1TdqSqlVar_genFromQryTblCol(Dz1TdqQryTblCol *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = NULL;

	Dz1TdqQueryTblName *tInd = src->tbl;
	Dz1TdqTblInstance *instance = tInd->instance;
	Dz1TdqTblShape *shp = instance->shape;
	Dz1TdqColumn *col = Dz1TdqRow_findByName(shp->row, src->col_name);
	if (col == NULL)
	{
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Column not found : %s\n", src->col_name);
		Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "!!! Shape = "); Dz1TdqRow_dump(shp->row, 0);
		ERR_SET_OUT(errp, ENOENT);
	}
	else if ((ret = Dz1TdqSqlVar_genFromSpec(col->sql_type, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Dz1TdqSqlVar *Dz1TdqSqlVar_genFromQryExprCol(Dz1TdqQryExprCol *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = NULL;

	if ((ret = Dz1TdqSqlVar_genFromSpec(src->type, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TdqSqlVar *Dz1TdqSqlVar_genFromQryCol(Dz1TdqQryCol *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = NULL;
	switch(src->present)
	{
	case Dz1TdqQryColPresent_tcol:
		if ((ret = Dz1TdqSqlVar_genFromQryTblCol(src->x.tcol, errp)) == NULL) ERR_SET_OUT(errp, EINVAL);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TdqQryColPresent_ecol:
		if ((ret = Dz1TdqSqlVar_genFromQryExprCol(src->x.ecol, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	}
	return ret;
}

static Dz1Error VarArray_genFromSelSpec(void *ptr, Dz1TdqQryColumn *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqSqlVarArray *dst = (Dz1TdqSqlVarArray *)ptr;
	Dz1TdqQryCol *src = p->src;

	Dz1TdqSqlVar *node = Dz1TdqSqlVar_genFromQryCol(p->src, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1TdqSqlVarArray *Dz1TdqSqlVarArray_genFromSelSpec(Dz1TdqQryRow *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVarArray *ret = NULL;
	if (src == NULL) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((ret = Dz1TdqSqlVarArray_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
		if ((*errp = src->travel(src, VarArray_genFromSelSpec, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1TdqSqlVarArray Generation from Select Row
///////////////////////////////////////////////////////////////////////////////

static bool_t Dz1TdqSqlDate_isNull(Dz1TdqSqlDate *p)
{
	bool_t ret = FALSE;

	if (p == NULL) ret = TRUE;
	else if (p->year == 0 && p->month == 0 && p->day == 0) ret = TRUE;

	return ret;
}

bool_t Dz1TdqSqlVarGetDate(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err)
{	// Dz1Tdq Library는 DB에 GMT시간을 입력하도록 한다.
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present == Dz1TdqSqlVarPresent_nul || Dz1TdqSqlDate_isNull(src->x.ymd)) (*dst) = 0;
	else if (src->present != Dz1TdqSqlVarPresent_ymd) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tm_v;
		Dz1TdqSqlDate *p = src->x.ymd;
		tm_v.tm_year = p->year - 1900;
		tm_v.tm_mon = p->month - 1;
		tm_v.tm_mday = p->day;
		tm_v.tm_hour = 0;
		tm_v.tm_min = 0;
		tm_v.tm_sec = 0;
		(*dst) = Dz1Tdq_mktime(&tm_v, TRUE);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t	Dz1TdqSqlVarGetTime(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present == Dz1TdqSqlVarPresent_nul) (*dst) = 0;
	else if (src->present != Dz1TdqSqlVarPresent_hms) ERR_SET_OUT(errp, EINVAL);
	else
	{
		time_t tNow = time(NULL);
		struct tm tm_v, *tm_p = gmtime(&tNow), tmNow = *tm_p;
		Dz1TdqSqlTime *p = src->x.hms;
		tm_v.tm_year = tmNow.tm_year;
		tm_v.tm_mon = tmNow.tm_mon;
		tm_v.tm_mday = tmNow.tm_mday;
		tm_v.tm_hour = p->hour;
		tm_v.tm_min = p->minute;
		tm_v.tm_sec = p->second;
		(*dst) = Dz1Tdq_mktime(&tm_v, TRUE);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1TdqSqlStamp_isNull(Dz1TdqSqlStamp *p)
{
	bool_t ret = FALSE;

	if (p == NULL) ret = TRUE;
	else if (p->year == 0 && p->month == 0 && p->day == 0 && p->hour == 0 && p->minute == 0 && p->second == 0) ret = TRUE;

	return ret;
}

bool_t	Dz1TdqSqlVarGetStamp(time_t *dst, Dz1TdqSqlVar *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->present == Dz1TdqSqlVarPresent_nul || Dz1TdqSqlStamp_isNull(src->x.stamp)) (*dst) = 0;
	else if (src->present != Dz1TdqSqlVarPresent_stamp) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tm_v;
		Dz1TdqSqlStamp *p = src->x.stamp;
		tm_v.tm_year = p->year - 1900;
		tm_v.tm_mon = p->month - 1;
		tm_v.tm_mday = p->day;
		tm_v.tm_hour = p->hour;
		tm_v.tm_min = p->minute;
		tm_v.tm_sec = p->second;
		(*dst) = Dz1Tdq_mktime(&tm_v, TRUE);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlVarArray
static Dz1TdqSqlVar *Dz1TdqSqlVar_newNum(Dz1TdqSqlVarPresent type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = NULL;
	
	if (val_ptr == NULL)
	{
		if ((ret = Dz1TdqSqlVar_new( Dz1TdqSqlVarPresent_nul, &type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1TdqSqlVar_new(type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

bool_t Dz1TdqSqlVarArray_addNum(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent num_type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *node = NULL;
	u32_t cat = _category_of(num_type);
	if (cat != 0x00 && cat != 0x01) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((node = Dz1TdqSqlVar_newNum(num_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqSqlVarArray_addReal(Dz1TdqSqlVarArray *dst, void *val_ptr, Dz1Error *err)
{ return Dz1TdqSqlVarArray_addNum(dst, Dz1TdqSqlVarPresent_r64, val_ptr, err); }

static Dz1TdqSqlVar *Dz1TdqSqlVar_newStr(Dz1TdqSqlVarPresent type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *ret = NULL;
	if (val_ptr == NULL)
	{
		if ((ret = Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_nul, &type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1TdqSqlVar_new(type, NULL, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
		if ((type & 0x0F) < 4)
		{	// String
			 if ((ret->x.__ptr__ = Dz1TdqSqlStr_newFromStr((Dz1Str)val_ptr, errp)) == NULL) ERR_OUT(errp);
			 else Dz1Error_set(errp, 0);
		}
		else
		{	// Binary
			 if ((ret->x.__ptr__ = Dz1TdqSqlStr_newFromBin((Dz1Binary *)val_ptr, errp)) == NULL) ERR_OUT(errp);
			 else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlVarArray_addStr(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent str_type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *node = NULL;
	u32_t cat = _category_of(str_type);
	if (cat != 0x02) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlVar_newStr(str_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqSqlVar *Dz1TdqSqlVar_createTime(Dz1TdqSqlVarPresent type, time_t *val_ptr, Dz1Error *errp)
{
	struct tm *tm_p = NULL;
	Dz1TdqSqlVar *ret = NULL;
	if (val_ptr == NULL)
	{
		if ((ret = Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_nul, &type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((tm_p = gmtime(val_ptr)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		struct tm tm_v = *tm_p;
		if ((ret = Dz1TdqSqlVar_new(type, NULL, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
			
			switch (type & 0x0F)
			{
			case 0: // date
				if ((ret->x.__ptr__ = Dz1TdqSqlDate_genFromTM(&tm_v, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case 1: // time
				if ((ret->x.__ptr__ = Dz1TdqSqlTime_genFromTM(&tm_v, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case 2:	// stamp
				if ((ret->x.__ptr__ = Dz1TdqSqlStamp_genFromTM(&tm_v, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default: ERR_SET_OUT(errp, EINVAL); break;
			}
			pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
		}
	}
	return ret;
}

bool_t Dz1TdqSqlVarArray_addTime(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent time_type, time_t *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *node = NULL;
	u32_t cat = _category_of(time_type);
	if (cat != 0x03) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlVar_newStr(time_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqSqlVar *Dz1TdqSqlVar_newBlobW(Dz1TdqSqlVarPresent type, Dz1Binary *bin, Dz1Error *errp)
{
	Dz1TdqSqlVar *ret = NULL;
	
	if (bin == NULL)
	{
		if ((ret = Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_nul, &type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1TdqSqlVar_new(type, NULL, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		Dz1TdqSqlBlob *b = NULL;
		Dz1TdqSqlBlobToDB *w = NULL;
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&ret);

		if ((ret->x.__ptr__ = b = Dz1TdqSqlBlob_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((b->writeToDB = w = Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent_ref_buf, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((w->x.ref_buf = Dz1TdqSqlBlobRef_new(bin->data, bin->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlVarArray_addBlob(Dz1TdqSqlVarArray *dst, Dz1TdqSqlVarPresent blob_type, Dz1Binary *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlVar *node = NULL;
	u32_t cat = _category_of(blob_type);
	if (cat != 0x04) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlVar_newBlobW(blob_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1TdqSqlVarArray
///////////////////////////////////////////////////////////////////////////////

Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVarList_findByName(Dz1TdqSqlNamedVarList *list, Dz1Str name)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqSqlNamedVar key = { name };
		ret = list->find(list, &key);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqSqlNamedVarList 
static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_createNum(Dz1Str name, Dz1TdqSqlVarPresent num_type, void *val_ptr, Dz1Error *errp)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	
	if ((ret = Dz1TdqSqlNamedVar_new(name, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
		if ((ret->val = Dz1TdqSqlVar_newNum(num_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlNamedVarList_addNum(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent num_type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlNamedVar *node = NULL;
	u32_t cat = _category_of(num_type);
	if (dst == NULL || Dz1Str_isVoid(name) == TRUE || (cat != 0x00 && cat != 0x01)) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlNamedVar_createNum(name, num_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqSqlNamedVarList_addReal(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent real_type, void *val_ptr, Dz1Error *err)
{ return Dz1TdqSqlNamedVarList_addNum(dst, name, real_type, val_ptr, err); }

static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_createStr(Dz1Str name, Dz1TdqSqlVarPresent present, void *val_ptr, Dz1Error *errp)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	
	if ((ret = Dz1TdqSqlNamedVar_new(name, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlVar *val = NULL;
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
		if ((ret->val = Dz1TdqSqlVar_newStr(present, val_ptr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlNamedVarList_addStr(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent str_type, void *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlNamedVar *node = NULL;
	u32_t cat = _category_of(str_type);
	if (dst == NULL || Dz1Str_isVoid(name) == TRUE || cat != 0x02) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlNamedVar_createStr(name, str_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_createTime(Dz1Str name, Dz1TdqSqlVarPresent present, time_t *val_ptr, Dz1Error *errp)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	
	if ((ret = Dz1TdqSqlNamedVar_new(name, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		struct tm *tm_p = NULL;
		Dz1TdqSqlVar *val = NULL;
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
		if ((ret->val = Dz1TdqSqlVar_createTime(present, val_ptr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlNamedVarList_addTime(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent time_type, time_t *val_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlNamedVar *node = NULL;
	u32_t cat = _category_of(time_type);
	if (dst == NULL || Dz1Str_isVoid(name) == TRUE || cat != 0x03) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlNamedVar_createTime(name, time_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_createBlobW(Dz1Str name, Dz1TdqSqlVarPresent present, Dz1TdqUserBlobWrite bw, void *bw_ptr, Dz1Error *errp)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	
	if ((ret = Dz1TdqSqlNamedVar_new(name, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlVar *val = NULL;
		Dz1TdqSqlBlob *b = NULL;
		Dz1TdqSqlBlobToDB *w = NULL;
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
		if (bw_ptr == NULL)
		{
			if ((ret->val = val = Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_nul, NULL, errp)) == NULL) ERR_OUT(errp);
			else 
			{
				val->x.nul = Dz1TdqType_blob;
				Dz1Error_set(errp, 0);
			}
		}
		else if ((ret->val = val = Dz1TdqSqlVar_new(present, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((val->x.__ptr__ = b = Dz1TdqSqlBlob_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((b->writeToDB = bw(bw_ptr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlNamedVarList_addBlob(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent blob_type, Dz1TdqUserBlobWrite bw, void *bw_ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlNamedVar *node = NULL;
	u32_t cat = _category_of(blob_type);
	if (dst == NULL || Dz1Str_isVoid(name) == TRUE || cat != 0x04) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1TdqSqlNamedVar_createBlobW(name, blob_type, bw, bw_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// static Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVar_createBlobR(Dz1Str name, Dz1TdqSqlVarPresent present, Dz1TdqSqlBlobFromDB *val_ptr, Dz1Error *errp)
// {
// 	Dz1TdqSqlNamedVar *ret = NULL;
// 	
// 	if ((ret = Dz1TdqSqlNamedVar_new(name, NULL, errp)) == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		Dz1TdqSqlVar *val = NULL;
// 		Dz1TdqSqlBlob *b = NULL;
// 		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
// 		if (val_ptr == NULL)
// 		{
// 			if ((ret->val = Dz1TdqSqlVar_new(Dz1TdqSqlVarPresent_nul, &present, errp)) == NULL) ERR_OUT(errp);
// 			else Dz1Error_set(errp, 0);
// 		}
// 		else if ((ret->val = val = Dz1TdqSqlVar_new(present, NULL, errp)) == NULL) ERR_OUT(errp);
// 		else if ((val->x.__ptr__ = Dz1TdqSqlBlob_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
// 		else if ((b->readFromDB = Dz1TdqSqlBlobFromDB_clone(val_ptr, errp)) == NULL) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }
// 
// bool_t Dz1TdqSqlNamedVarList_addBlobR(Dz1TdqSqlNamedVarList *dst, Dz1Str name, Dz1TdqSqlVarPresent blob_type, Dz1TdqSqlBlobFromDB *val_ptr, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1TdqSqlNamedVar *node = NULL;
// 	u32_t cat = _category_of(blob_type);
// 	if (dst == NULL || Dz1Str_isVoid(name) == TRUE || cat != 0x04) ERR_SET_OUT(errp, EINVAL);
// 	else if ((node = Dz1TdqSqlNamedVar_createBlobR(name, blob_type, val_ptr, errp)) == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
// 		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
// 		else
// 		{
// 			node = NULL;
// 			Dz1Error_set(errp, 0);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
// 	}
// 	return errp->code == 0 ? TRUE : FALSE;
// }
// Dz1TdqSqlNamedVarList 
///////////////////////////////////////////////////////////////////////////////

Dz1TdqSqlNamedVar *Dz1TdqSqlNamedVarList_extractByName(Dz1TdqSqlNamedVarList *list, Dz1Str name)
{
	Dz1TdqSqlNamedVar *ret = NULL;
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqSqlNamedVar key = { name };
		ret = list->extract(list, &key);
	}
	return ret;
}

void Dz1TdqSqlNamedVarList_removeByName(Dz1TdqSqlNamedVarList *list, Dz1Str name)
{
	if (list != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		Dz1TdqSqlNamedVar key = { name };
		list->remove(list, &key);
	}
}

static bool_t _is_symbol_seprator(TCHAR c)
{
	if (Dz1ISSPACE(c)) return TRUE;
	else
	{
		switch(c)
		{
		case Dz1Text(','): return TRUE;
		default: return FALSE;
		}
	}
}

// static bool_t _is_symbol_letter(TCHAR c)
// {
// 	if (Dz1ISALNUM(c)) return TRUE;
// 	else
// 	{
// 		switch(c)
// 		{
// 		case Dz1Text('_'): return TRUE;
// 		default: return FALSE;
// 		}
// 	}
// }

static TCHAR *_take_name(TCHAR dst[1024], TCHAR *src)
{
	TCHAR *dp = dst;

	if (src == NULL || *src == 0) return NULL;

	while(*src && _is_symbol_seprator(*src)) src++;

	if (*src)
	{
		while(*src && !_is_symbol_seprator(*src)) 
			*dp++ = *src++;
	}
	else return NULL;

	*dp = 0;
	return src;
}

Dz1TdqSqlNamedVarList *Dz1TdqSqlNamedVarList_collect(Dz1TdqSqlNamedVarList *src, Dz1Str comma_seprated_names, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlNamedVarList *ret = NULL;
	if (src == NULL || Dz1Str_isVoid(comma_seprated_names)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TdqSqlNamedVar *node = NULL;
		TCHAR buf[1024], *cp = comma_seprated_names;
		pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
		while(errp->code == 0 && (cp = _take_name(buf, cp)) != NULL)
		{
			if ((node = Dz1TdqSqlNamedVarList_extractByName(src, buf)) == NULL) ERR_SET_OUT(errp, ENOENT);
			else 
			{
				pthread_cleanup_push(Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
				if ((*errp = ret->add(ret, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVar_delAndSetNull, (void *)&node);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1TdqSqlNumSpec_isComapt(Dz1TdqSqlNumSpec *basis, Dz1TdqSqlNumSpec *compat)
{
	bool_t ret = FALSE;
	if (basis == NULL && compat == NULL) ret = TRUE;
	else if (basis == NULL || compat == NULL) { }
	else if (basis->size != compat->size) { }
	else ret = TRUE;
	return ret;
}

bool_t Dz1TdqSqlRealSpec_isComapt(Dz1TdqSqlRealSpec *basis, Dz1TdqSqlRealSpec *compat)
{
	bool_t ret = FALSE;
	// don't care different percision
	return ret;
}

bool_t Dz1TdqSqlStrSpec_isComapt(Dz1TdqSqlStrSpec *basis, Dz1TdqSqlStrSpec *compat)
{
	bool_t ret = FALSE;
	// don't care different size
	return ret;
}

/*
typedef struct Dz1TdqSqlTypeSpec
{
	Dz1TdqSqlTypeSpecPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TdqSqlNumSpec *num_s8;
		Dz1TdqSqlNumSpec *num_u8;
		Dz1TdqSqlNumSpec *num_s16;
		Dz1TdqSqlNumSpec *num_u16;
		Dz1TdqSqlNumSpec *num_s32;
		Dz1TdqSqlNumSpec *num_u32;
		Dz1TdqSqlNumSpec *num_s64;
		Dz1TdqSqlNumSpec *num_u64;
		Dz1TdqSqlRealSpec *num_r32;
		Dz1TdqSqlRealSpec *num_r64;
		Dz1TdqSqlStrSpec *string;
		Dz1TdqSqlStrSpec *vstring;
		Dz1TdqSqlStrSpec *tstring;
		Dz1TdqSqlStrSpec *vtstring;
		Dz1TdqSqlStrSpec *binary;
		Dz1TdqSqlStrSpec *vbinary;
		u32_t *ymd;
		u32_t *hms;
		u32_t *stamp;
		Dz1TdqSqlBlobSpec blob;
		Dz1TdqSqlBlobSpec blobL;
	} x;
} Dz1TdqSqlTypeSpec;
*/
Dz1Error Dz1TdqSqlTypeSpec_isCompat(Dz1TdqSqlTypeSpec *basis, Dz1TdqSqlTypeSpec *compat, bool_t *ret_compat)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	*ret_compat = FALSE;

	if (basis == NULL || compat == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (basis->present != compat->present) { }
	else
	{
		u32_t cat = _category_of(basis->present);
		switch(cat)
		{
		case 0:	// num
			*ret_compat = Dz1TdqSqlNumSpec_isComapt((Dz1TdqSqlNumSpec *)basis->x.__ptr__, (Dz1TdqSqlNumSpec *)compat->x.__ptr__);
			break;
		case 1:	// real
			*ret_compat = Dz1TdqSqlRealSpec_isComapt((Dz1TdqSqlRealSpec *)basis->x.__ptr__, (Dz1TdqSqlRealSpec *)compat->x.__ptr__);
			break;
		case 2:	// str&bin
			*ret_compat = Dz1TdqSqlStrSpec_isComapt((Dz1TdqSqlStrSpec *)basis->x.__ptr__, (Dz1TdqSqlStrSpec *)compat->x.__ptr__);
			break;
		case 3:	// date&time
		case 4:	// blob
		case 15: // null
			*ret_compat = TRUE;
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return err;
}
