#include <codeconv.h>
#include <dz1_str.h>
#include "dz1_meta_tag_codec.h"
#include "dz1_meta_tag_util.h"

static wstr_t _mk_unicode_str(Dz1Asn1UTF8Str *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	if (src == NULL || src->data == NULL || src->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (wstr_t)Dz1Calloc(sizeof(wchar_t), src->size + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&ret);

		Dz1Asn1UTF8Str_conv(src, WINDOWS_UNICODE, (char *)ret, sizeof(wchar_t) * src->size, errp); // modified by gm 20230605 
// 		if (Dz1Asn1UTF8Str_printable(src, WINDOWS_UNICODE, (u8_t *)ret, sizeof(wchar_t) * src->size) == NULL) ERR_SET_OUT(errp, EFAULT);
// 		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1WStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1MetaTagValueList_addData8(Dz1MetaTagValueList *dst, u8_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagValue *node = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data8, &data, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1MetaTagValueList_addData16(Dz1MetaTagValueList *dst, u16_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagValue *node = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data16, &data, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1MetaTagValueList_addData32(Dz1MetaTagValueList *dst, u32_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagValue *node = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data32, &data, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1MetaTagValueList_addData64(Dz1MetaTagValueList *dst, u64_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagValue *node = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data64, &data, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
	}
	return err;
}


static Dz1Error _Dz1MetaTagData_create(void *ptr, Dz1MetaTagDescrEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagData *dst = (Dz1MetaTagData *)ptr;
	Dz1Thread_printf("Default TAGs(%08X) : mandatory = %s\n", p->id, p->mandatory ? "TRUE" : "FALSE");
	if (p->mandatory && Dz1MetaTagDescrEntry_isAcceptable(p, dst->target_type))
	{
		Dz1Thread_printf("Add TAGs(%08X) : mandatory = %s\n", p->id, p->mandatory ? "TRUE" : "FALSE");
		if ((*errp = Dz1MetaTagData_addTag(dst, p)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1MetaTagData *Dz1MetaTagData_generate(u32_t target_type, Dz1MetaTagDB *src, Dz1Error *err)
{	// TAG DB의 Mandatory Tag를 자동으로 등록
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagData *ret = Dz1MetaTagData_new(target_type, errp);

	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&ret);

		if ((*errp = src->table->travel(src->table, _Dz1MetaTagData_create, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1MetaTagData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData Helper
Dz1MetaTagDataEntry *Dz1MetaTagData_getTag(Dz1MetaTagData *src, u32_t tag_id)
{
	Dz1MetaTagDataEntry key = { tag_id };
	return src->tags->find(src->tags, &key);
}

Dz1MetaTagDataEntry *Dz1MetaTagData_extractTag(Dz1MetaTagData *src, u32_t tag_id)
{
	Dz1MetaTagDataEntry key = { tag_id };
	return src->tags->extract(src->tags, &key);
}

Dz1Error Dz1MetaTagData_addTag(Dz1MetaTagData *dst, Dz1MetaTagDescrEntry *descr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagDataList *table = dst->tags;
	Dz1MetaTagDataEntry key = { descr->id }, *node = table->find(table, &key);
	if (node == NULL)
	{
		if ((node = Dz1MetaTagDataEntry_new(descr->id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTagDataEntry_delAndSetNull, (void *)&node);
			if ((*errp = table->add(table, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDataEntry_delAndSetNull, (void *)&node);
		}
	}
	else
	{
	}
	return err;
}

static Dz1Error Dz1MetaTagValueList_addValue(Dz1MetaTagValueList *dst, Dz1MetaTagValue *clone_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1MetaTagValue *node = dst->find(dst, clone_src);
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((node = Dz1MetaTagValue_clone(clone_src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1MetaTagData_addTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *clone_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || clone_src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MetaTagDataList *table = dst->tags;
		Dz1MetaTagDataEntry key = { tag_id }, *node = table->find(table, &key);
		if (node == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = node->values->add(node->values, clone_src)).code) ERR_OUT(errp);
	}

	return err;
}

Dz1Error Dz1MetaTagData_injTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue **inject_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL || inject_src == NULL || (*inject_src) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDataList *table = dst->tags;
		Dz1MetaTagDataEntry key = { tag_id }, *node = table->find(table, &key);
		if (node == NULL) ERR_SET_OUT(errp, ENOENT);
		else if ((*errp = node->values->add(node->values, (*inject_src) )).code) ERR_OUT(errp);
		else
		{
			(*inject_src) = NULL;
			Dz1Error_set(errp, 0);
		}
	}

	return err;
}

Dz1Error Dz1MetaTagData_addTagValue8(Dz1MetaTagData *dst, u32_t tag_id, u8_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data8, &data, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
		if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
	}
	return err;
}

Dz1Error Dz1MetaTagData_addTagValue16(Dz1MetaTagData *dst, u32_t tag_id, u16_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data16, &data, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
		if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
	}
	return err;
}

Dz1Error Dz1MetaTagData_addTagValue32(Dz1MetaTagData *dst, u32_t tag_id, u32_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data32, &data, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
		if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
	}
	return err;
}

Dz1Error Dz1MetaTagData_addTagValue64(Dz1MetaTagData *dst, u32_t tag_id, u64_t data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_data64, &data, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
		if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
	}
	return err;
}


Dz1Error Dz1MetaTagData_addTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *clone_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || clone_src == NULL || clone_src->data == NULL || clone_src->size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_binary, NULL, errp);
		if (v == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
			if ((v->x.binary = Dz1Binary_clone(clone_src, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
		}
	}
	return err;
}

static void _unbind_inject_src(void *ptr)
{
	Dz1MetaTagValue *v = (Dz1MetaTagValue *)ptr;
	v->x.__ptr__ = NULL;
}

Dz1Error Dz1MetaTagData_injTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary **inject_src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *bin = NULL;
	if (dst == NULL || inject_src == NULL || (bin = (*inject_src)) == NULL || bin->data == NULL || bin->size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MetaTagValue *v = Dz1MetaTagValue_new(Dz1MetaTagValuePresent_binary, (*inject_src), errp);
		if (v == NULL) ERR_OUT(errp);
		else
		{
			(*inject_src) = NULL;
			pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);

			if ((*errp = Dz1MetaTagData_injTagValue(dst, tag_id, &v)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagData_addTagValueBinB(Dz1MetaTagData *dst, u32_t tag_id, u8_t *buf, size_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || buf == NULL || size == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1Binary *bin = Dz1Binary_new(buf, (u32_t)size, errp);
		if (bin == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			if ((*errp = Dz1MetaTagData_injTagValueBin(dst, tag_id, &bin)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
	}
	return err;
}

void Dz1MetaTagData_removeTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *key)
{
	Dz1MetaTagDataEntry tag_key = { tag_id }, *node = dst->tags->find(dst->tags, &tag_key);
	if (node != NULL)
		node->values->remove(node->values, key);
}

Dz1MetaTagValue *Dz1MetaTagData_extractTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *key)
{
	Dz1MetaTagValue *ret = NULL;
	Dz1MetaTagDataEntry tag_key = { tag_id }, *node = dst->tags->find(dst->tags, &tag_key);
	if (node != NULL)
		ret = node->values->extract(node->values, key);
	return ret;
}

void Dz1MetaTagData_removeTagValue8(Dz1MetaTagData *dst, u32_t tag_id, u8_t key)
{
	Dz1MetaTagValue v_key = { Dz1MetaTagValuePresent_data8 };
	v_key.x.data8 = key;
	Dz1MetaTagData_removeTagValue(dst, tag_id, &v_key);
}

void Dz1MetaTagData_removeTagValue16(Dz1MetaTagData *dst, u32_t tag_id, u16_t key)
{
	Dz1MetaTagValue v_key = { Dz1MetaTagValuePresent_data16 };
	v_key.x.data16 = key;
	Dz1MetaTagData_removeTagValue(dst, tag_id, &v_key);
}

void Dz1MetaTagData_removeTagValue32(Dz1MetaTagData *dst, u32_t tag_id, u32_t key)
{
	Dz1MetaTagValue v_key = { Dz1MetaTagValuePresent_data32 };
	v_key.x.data32 = key;
	Dz1MetaTagData_removeTagValue(dst, tag_id, &v_key);
}

void Dz1MetaTagData_removeTagValue64(Dz1MetaTagData *dst, u32_t tag_id, u64_t key)
{
	Dz1MetaTagValue v_key = { Dz1MetaTagValuePresent_data64 };
	v_key.x.data64 = key;
	Dz1MetaTagData_removeTagValue(dst, tag_id, &v_key);
}

void Dz1MetaTagData_removeTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *key)
{
	Dz1MetaTagValue b_key = { Dz1MetaTagValuePresent_binary, { key } };
	Dz1MetaTagData_removeTagValue(dst, tag_id, &b_key);
}

void Dz1MetaTagData_removeTagValueBinB(Dz1MetaTagData *dst, u32_t tag_id, u8_t *key_buf, size_t key_size)
{
	Dz1Binary b_key = { key_buf, (u32_t)key_size };
	Dz1MetaTagData_removeTagValueBin(dst, tag_id, &b_key);
}

Dz1Binary *Dz1MetaTagData_extractTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *key)
{
	Dz1Binary *ret = NULL;
	Dz1MetaTagValue b_key = { Dz1MetaTagValuePresent_binary, { key } };
	Dz1MetaTagValue *v = Dz1MetaTagData_extractTagValue(dst, tag_id, &b_key);
	if (v != NULL)
	{
		pthread_cleanup_push(Dz1MetaTagValue_delAndSetNull, (void *)&v);
		ret = v->x.binary;
		v->x.binary = NULL;
		pthread_cleanup_pop(1); // (Dz1MetaTagValue_delAndSetNull, (void *)&v);
	}
	return ret;
}

static Dz1Error _getAsData32_representFromBinary(u32_t *dst, Dz1Binary *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t v = 0;
		if		(src->size >= 4) v = (u32_t)(*(u32_t *)src->data);
		else if (src->size >= 2) v = (u32_t)(*(u16_t *)src->data);
		else if (src->size >= 1) v = (u32_t)(*(u8_t *)src->data);
		memcpy(dst, &v, sizeof(u32_t));
	}
	return err;
}

Dz1Error Dz1MetaTagValue_getAsData32(u32_t *dst, Dz1MetaTagValue *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t v = 0;
	if (src != NULL)
	{
		Dz1Binary *bin = src->x.binary;
		switch(src->present)
		{
		case Dz1MetaTagValuePresent_data8:
			v = (u32_t)(src->x.data8);
			memcpy(dst, &v, sizeof(u32_t));
			break;
		case Dz1MetaTagValuePresent_data16:
			v = (u32_t)(src->x.data16);
			memcpy(dst, &v, sizeof(u32_t));
			break;
		case Dz1MetaTagValuePresent_data32:
			v = (u32_t)(src->x.data32);
			memcpy(dst, &v, sizeof(u32_t));
			break;
		case Dz1MetaTagValuePresent_data64:
			v = (u32_t)(src->x.data64 & 0xFFFFFFFF);
			memcpy(dst, &v, sizeof(u32_t));
			break;
		case Dz1MetaTagValuePresent_binary:
			if ((*errp = _getAsData32_representFromBinary(dst, src->x.binary)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1Error _calc_date(struct tm *dst, s64_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	struct tm *tm_p, tm2000, tmTarget;
	time_t t2000, tTarget;

	tm2000.tm_year = 100;
	tm2000.tm_mon = 0;
	tm2000.tm_mday = 1;
	tm2000.tm_hour = 0;
	tm2000.tm_min = 0;
	tm2000.tm_sec = 0;
	t2000 = mktime(&tm2000);

	tTarget = t2000 + diff;
	if ((tm_p = localtime(&tTarget)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		tmTarget = (*tm_p);
		dst->tm_year = tmTarget.tm_year;
		dst->tm_mon = tmTarget.tm_mon;
		dst->tm_mday = tmTarget.tm_mday;
	}
	return err;
}

static Dz1Error _calc_date8(struct tm *dst, u8_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MetaTagDataDate8 *date8 = NULL;

		time_t tNow = time(NULL);
		struct tm *tm_p = localtime(&tNow);

		(*dst) = (*tm_p);

		date8 = (Dz1MetaTagDataDate8 *)&v;
		dst->tm_mon = date8->month;
		dst->tm_mday = 1 + (date8->hday * 2);

		dst->tm_hour = 0;
		dst->tm_min	= 0;
		dst->tm_sec = 0;
	}
	return err;
}

static Dz1Error _getAsDate_representFromBinary(struct tm *dst, Dz1Binary *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t v = 0;
		if		(src->size >= 8)
		{
			v = (s64_t)(*(u64_t *)src->data);
			if ((*errp = _calc_date(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 4)
		{
			v = (s64_t)(*(u32_t *)src->data);
			if ((*errp = _calc_date(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 2)
		{
			v = (s64_t)(*(u16_t *)src->data);
			if ((*errp = _calc_date(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 1)
		{
			u8_t v8 = (*(u8_t *)src->data);
			if ((*errp = _calc_date8(dst, v8)).code) ERR_OUT(errp);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagValue_getDataAsDate(struct tm *dst, Dz1MetaTagValue *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t diff;

		switch(src->present)
		{
		case Dz1MetaTagValuePresent_data8:
			if ((*errp = _calc_date8(dst, src->x.data8)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data16:
			diff = (s64_t)src->x.data16 * (24 * 60 * 60);
			if ((*errp = _calc_date(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data32:
			diff = (s64_t)src->x.data32 * (24 * 60 * 60);
			if ((*errp = _calc_date(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data64:
			diff = (s64_t)src->x.data64 * (24 * 60 * 60);
			if ((*errp = _calc_date(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_binary:
			if ((*errp = _getAsDate_representFromBinary(dst, src->x.binary)).code) ERR_OUT(errp);
			break;
		}
	}
	return err;
}

static Dz1Error _calc_time(struct tm *dst, u32_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	time_t tNow = time(NULL), tTarget;
	struct tm *tm_p = localtime(&tNow), tmNow = (*tm_p);

	diff = diff % 86400;

	tmNow.tm_hour = 0;
	tmNow.tm_min = 0;
	tmNow.tm_sec = 0;
	tTarget = mktime(&tmNow) + diff;
	
	if ((tm_p = localtime(&tTarget)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else (*dst) = (*tm_p);

	return err;
}

static Dz1Error _getAsTime_representFromBinary(struct tm *dst, Dz1Binary *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t v = 0;
		if		(src->size >= 8)
		{
			u64_t v64;
			v64 = (u64_t)(*(u64_t *)src->data);
			v = (u32_t)(v64 & 0xFFFFFFFF);
			if ((*errp = _calc_time(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 4)
		{
			v = (u32_t)(*(u32_t *)src->data);
			if ((*errp = _calc_time(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 2)
		{
			u16_t v16 = (u16_t)(*(u16_t *)src->data);
			Dz1MetaTagDataTime16 *time16 = (Dz1MetaTagDataTime16 *)&v16;
			v = (u32_t)time16->minutes * 60 + (time16->qsec * 4);
			if ((*errp = _calc_time(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 1)
		{
			u8_t v8 = (*(u8_t *)src->data);
			v = (v8 % 144) * 10 * 60;
			if ((*errp = _calc_time(dst, v)).code) ERR_OUT(errp);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagValue_getDataAsTime(struct tm *dst, Dz1MetaTagValue *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t diff;
		Dz1MetaTagDataTime16 *time16;
		switch(src->present)
		{
		case Dz1MetaTagValuePresent_data8:
			diff = (src->x.data8 % 144) * 10 * 60;
			if ((*errp = _calc_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data16:
			time16 = (Dz1MetaTagDataTime16 *)&src->x.data16;
			diff = (u32_t)time16->minutes * 60 + (time16->qsec * 4);
			if ((*errp = _calc_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data32:
			diff = src->x.data32;
			if ((*errp = _calc_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data64:
			diff = (u32_t)(src->x.data64 & 0xFFFFFFFF);
			if ((*errp = _calc_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_binary:
			if ((*errp = _getAsTime_representFromBinary(dst, src->x.binary)).code) ERR_OUT(errp);
			break;
		}
	}
	return err;
}

static Dz1Error _calc_date_time(struct tm *dst, s64_t diff)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	struct tm *tm_p = localtime((time_t *)&diff);

	if (tm_p == NULL) ERR_SET_OUT(errp, EINVAL);
	else (*dst) = (*tm_p);

	return err;
}

static Dz1Error _getAsDateTime_representFromBinary(struct tm *dst, Dz1Binary *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t v = 0;
		if		(src->size >= 8)
		{
			v = (s64_t)(*(s64_t *)src->data);
			if ((*errp = _calc_date_time(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 4)
		{
			v = (s64_t)(*(u32_t *)src->data);
			if ((*errp = _calc_date_time(dst, v)).code) ERR_OUT(errp);
		}
		else if (src->size >= 2)
		{
			u16_t v16 = (u16_t)(*(u16_t *)src->data);
			Dz1MetaTagDataTime16 *time16 = (Dz1MetaTagDataTime16 *)&v16;
			u32_t v32 = ((u32_t)time16->minutes * 60 + (time16->qsec * 4));
			if ((*errp = _calc_time(dst, v32)).code) ERR_OUT(errp);
		}
		else if (src->size >= 1)
		{
			u8_t v8 = (*(u8_t *)src->data);
			u32_t v32 = (u32_t)((v8 % 144) * 10 * 60);
			if ((*errp = _calc_time(dst, v32)).code) ERR_OUT(errp);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagValue_getDataAsDateTime(struct tm *dst, Dz1MetaTagValue *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t diff;
		Dz1MetaTagDataTime16 *time16;
		switch(src->present)
		{
		case Dz1MetaTagValuePresent_data8:
			diff = (src->x.data8 % 144) * 10 * 60;
			if ((*errp = _calc_time(dst, (u32_t)(diff & 0xFFFFFFFF))).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data16:
			time16 = (Dz1MetaTagDataTime16 *)&src->x.data16;
			diff = ((s64_t)((u32_t)time16->minutes * 60 + (time16->qsec * 4)) & 0xFFFFFFFF);
			if ((*errp = _calc_time(dst, (u32_t)diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data32:
			diff = ((s64_t)src->x.data32 & 0xFFFFFFFF);
			if ((*errp = _calc_date_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_data64:
			diff = (s32_t)src->x.data64;
			if ((*errp = _calc_date_time(dst, diff)).code) ERR_OUT(errp);
			break;
		case Dz1MetaTagValuePresent_binary:
			if ((*errp = _getAsDateTime_representFromBinary(dst, src->x.binary)).code) ERR_OUT(errp);
			break;
		}
	}
	return err;
}

Dz1MetaTagDataEntry **Dz1MetaTagData_mkArray(Dz1MetaTagData *data, size_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDataEntry **ret = NULL;
	Dz1MetaTagDataList *table = NULL;
	if (data == NULL || (table = data->tags) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t _ret_cnt = 0;
		if ((ret = table->get_array(table, &_ret_cnt, errp)) == NULL) ERR_OUT(errp);
		else (*ret_cnt) = (size_t)_ret_cnt;
	}
	return ret;
}

bool_t Dz1MetaTagData_isExistTag(Dz1MetaTagData *data, u32_t tag_id)
{
	bool_t ret = FALSE;
	if (data != NULL)
	{
		Dz1MetaTagDataList *table = data->tags;
		Dz1MetaTagDataEntry key = { tag_id };
		ret = table->find(table, &key) == NULL ? FALSE : TRUE;
	}
	return ret;
}

// Dz1MetaTagData Helper
///////////////////////////////////////////////////////////////////////////////

static void _setNumber32(Dz1MetaTagValue *dst, s64_t v)
{
	if (v <= 2147483647 && v >= DZ1INT64(-2147483648))
	{	// data32
		dst->present = Dz1MetaTagValuePresent_data32;
		dst->x.data32 = (u32_t)(v & 0xFFFFFFFF);
	}
	else
	{
		dst->present = Dz1MetaTagValuePresent_data64;
		dst->x.data64 = (u64_t)v;
	}
}

static void _setNumber16(Dz1MetaTagValue *dst, s64_t v)
{
	if (v <= 32767 && v >= -32768)
	{	// data16
		dst->present = Dz1MetaTagValuePresent_data16;
		dst->x.data16 = (u16_t)(v & 0xFFFF);
	}
	else _setNumber32(dst, v);
}

static void _setNumber(Dz1MetaTagValue *dst, s64_t v)
{
	if (v <= 127 && v >= -128)
	{	// data8
		dst->present = Dz1MetaTagValuePresent_data8;
		dst->x.data8 = (u8_t)(v & 0xFF);
	}
	else _setNumber16(dst, v);
}

Dz1Error Dz1MetaTagValue_setNumber(Dz1MetaTagValue *dst, s64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);

		_setNumber(dst, v);

	}
	return err;
}
Dz1Error Dz1MetaTagValue_setNumber16(Dz1MetaTagValue *dst, s64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);

		_setNumber16(dst, v);

	}
	return err;
}
Dz1Error Dz1MetaTagValue_setNumber32(Dz1MetaTagValue *dst, s64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);

		_setNumber32(dst, v);

	}
	return err;
}

static void _setUNumber32(Dz1MetaTagValue *dst, u64_t v)
{
	if (v <= DZ1UINT64(0xFFFFFFFF))
	{	// data32
		dst->present = Dz1MetaTagValuePresent_data32;
		dst->x.data32 = (v & 0xFFFFFFFF);
	}
	else
	{
		dst->present = Dz1MetaTagValuePresent_data64;
		dst->x.data64 = v;
	}
}

static void _setUNumber16(Dz1MetaTagValue *dst, u64_t v)
{
	if (v <= 0xFFFF)
	{	// data16
		dst->present = Dz1MetaTagValuePresent_data16;
		dst->x.data16 = (v & 0xFFFF);
	}
	else _setUNumber32(dst, v);
}

static void _setUNumber(Dz1MetaTagValue *dst, u64_t v)
{
	if (v <= 0xFF)
	{	// data8
		dst->present = Dz1MetaTagValuePresent_data8;
		dst->x.data8 = (v & 0xFF);
	}
	else _setUNumber16(dst, v);
}

Dz1Error Dz1MetaTagValue_setUNumber(Dz1MetaTagValue *dst, u64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);
		_setUNumber(dst, v);
	}
	return err;
}

Dz1Error Dz1MetaTagValue_setUNumber16(Dz1MetaTagValue *dst, u64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);
		_setUNumber16(dst, v);
	}
	return err;
}

Dz1Error Dz1MetaTagValue_setUNumber32(Dz1MetaTagValue *dst, u64_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (dst->present == Dz1MetaTagValuePresent_binary && dst->x.binary != NULL) Dz1Binary_delAndSetNull(&dst->x.binary);
		_setUNumber32(dst, v);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB Helper
static Dz1Error _add_target_type(Dz1MetaTargetTypeList *types, u32_t type, Dz1Asn1UTF8Str **name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTargetTypeEntry key = { type }, *node = types->find(types, &key);
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((node = Dz1MetaTargetTypeEntry_new(type, (*name), errp)) == NULL) ERR_OUT(errp);
	else
	{
		(*name) = NULL;
		pthread_cleanup_push(Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
		if ((*errp = types->add(types, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _add_target_type_buf(Dz1MetaTagDB *dst, u32_t type, u8_t *name, size_t sz, str_t name_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1UTF8Str *utf8name = NULL;
	if (dst == NULL || name == NULL || sz == 0 || name_charset == NULL || name_charset[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((utf8name = Dz1Asn1UTF8Str_newFromBuf((u8_t *)name, sz, name_charset, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8name);
		if ((*errp = _add_target_type(dst->types, type, &utf8name)).code) ERR_OUT(errp);
		else
		{
			utf8name = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8name);
	}
	return err;
}

#if 0		
Dz1MetaTagDB *Dz1MetaTagDB_create(Dz1Error *errp)
{
	Dz1MetaTagDB *ret = Dz1MetaTagDB_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrEntry *descr = NULL;
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&ret);
		if (0) { }
		///////////////////////////////////////////////////////
		// Video Descriptor
		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_TITLE,
													   "Video Title", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_array, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrString(descr, "UTF-8")).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_POSTER,
													   "Video Poster", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr, Dz1MetaTagDescrNum_data32)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_POSTER_FRONT,
													   "Video Poster Front", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr, Dz1MetaTagDescrNum_data32)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_POSTER_REAR,
													   "Video Poster Rear", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr, Dz1MetaTagDescrNum_data32)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_SCREEN_SHOT,
													   "Video Screen Shot", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_array, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr, Dz1MetaTagDescrNum_data32)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_CASTING,
													   "Video Castings", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_array, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrAlias(descr, DZ1_META_TAG_DESCR_PEOPLE_NAMES)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, DZ1_META_TAG_DESCR_VIDEO_WEB_LINKS,
													   "Video Description Web", "EUC-KR",
													   Dz1MetaTagValueStoragePresent_array, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrString(descr, "UTF-8")).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setRestrict(descr, Dz1MetaTagRestrictMode_accept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_addRestrict(descr, DZ1_META_TAG_TARGET_TYPE_VIDEO)).code) ERR_OUT(errp);
		// Video Descriptor
		///////////////////////////////////////////////////////
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

Dz1MetaTagDB *Dz1MetaTagDB_create(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDB *ret = Dz1MetaTagDB_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&ret);

		if ((*errp = Dz1MetaTagDB_addTargetTypeBuf(ret, 0, (u8_t *)"Unknown", 8, "EUC-KR")).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MetaTagDB *Dz1MetaTagDBA_load(str_t path, str_t name, Dz1Error *err)
{
	Dz1MetaTagDB *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = Dz1BinFile_load2(path, name, errp);
	if (bin == NULL)
	{
		if ((ret = Dz1MetaTagDB_create(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MetaTagDB_save(ret, path, name);
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = Dz1MetaTagDB_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1Error Dz1MetaTagDBA_save(Dz1MetaTagDB *src, str_t path, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *bin = Dz1MetaTagDB_toStream(src, NULL, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((*errp = Dz1BinFile_save2(path, name, bin)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

#ifdef WIN32
Dz1MetaTagDB *Dz1MetaTagDBW_load(wstr_t path, wstr_t name, Dz1Error *err)
{
	Dz1MetaTagDB *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = Dz1BinFileW_load2(path, name, errp);
	if (bin == NULL)
	{
		if ((ret = Dz1MetaTagDB_create(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1MetaTagDBW_save(ret, path, name);
			Dz1Error_set(errp, 0);
		}
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = Dz1MetaTagDB_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

Dz1Error Dz1MetaTagDBW_save(Dz1MetaTagDB *src, wstr_t path, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *bin = Dz1MetaTagDB_toStream(src, NULL, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((*errp = Dz1BinFileW_save2(path, name, bin)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
#endif

Dz1Error Dz1MetaTagDB_addTargetTypeUTF8(Dz1MetaTagDB *dst, u32_t type, Dz1Asn1UTF8Str *name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || name == NULL || name->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((name = Dz1Asn1UTF8Str_clone(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		if ((*errp = _add_target_type(dst->types, type, &name)).code) ERR_OUT(errp);
		else
		{
			name = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
	}
	return err;
}

Dz1Error Dz1MetaTagDB_addTargetTypeBuf(Dz1MetaTagDB *dst, u32_t type, u8_t *name, size_t sz, str_t name_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = _add_target_type_buf(dst, type, name, sz, name_charset)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDB_addTargetTypeW(Dz1MetaTagDB *dst, u32_t type, wstr_t name_w)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1UTF8Str *utf8 = NULL;
	size_t len = 0;
	if (dst == NULL || name_w == NULL || (len = wcslen(name_w)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((utf8 = Dz1Asn1UTF8Str_newFromBuf((u8_t *)name_w, sizeof(wchar_t) * len, WINDOWS_UNICODE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((*errp = _add_target_type(dst->types, type, &utf8)).code) ERR_OUT(errp);
		else
		{
			utf8 = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
	}
	return err;
}

Dz1Error Dz1MetaTagDB_addTargetTypeA(Dz1MetaTagDB *dst, u32_t type, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1UTF8Str *utf8 = NULL;
	size_t len = 0;
	if (dst == NULL || name == NULL || (len = strlen(name)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((utf8 = Dz1Asn1UTF8Str_newFromBuf((u8_t *)name, len, WINDOWS_UNICODE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((*errp = _add_target_type(dst->types, type, &utf8)).code) ERR_OUT(errp);
		else
		{
			utf8 = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
	}
	return err;
}

void Dz1MetaTagDB_delTargetType(Dz1MetaTagDB *dst, u32_t type)
{
	Dz1MetaTargetTypeEntry key = { type };
	dst->types->remove(dst->types, &key);
}

Dz1MetaTargetTypeEntry *Dz1MetaTagDB_getTargetType(Dz1MetaTagDB *dst, u32_t type)
{
	Dz1MetaTargetTypeEntry *ret = NULL;
	if (dst == NULL) { }
	else if (dst->types == NULL) { }
	else
	{
		Dz1MetaTargetTypeList *types = dst->types;
		Dz1MetaTargetTypeEntry key = { type };
		ret = types->find(types, &key);
	}
	return ret;
}

Dz1MetaTagDescrEntry *Dz1MetaTagDB_addTagDescrUTF8(Dz1MetaTagDB *dst, u32_t id, Dz1Asn1UTF8Str *name, bool_t mandatory, Dz1Error *err)
{
	Dz1MetaTagDescrEntry *ret = NULL, *node = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Dz1MetaTagDB_getTagDescr(dst, id) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (dst == NULL || name == NULL || name->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1MetaTagDescrEntry_new(id, NULL, NULL, mandatory, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
		if ((node->name = Dz1Asn1UTF8Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if ((node->name_w = _mk_unicode_str(node->name, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->table->add(dst->table, node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1MetaTagDescrEntry *Dz1MetaTagDB_addTagDescrBuf(Dz1MetaTagDB *dst, u32_t id, u8_t *name, size_t name_size, str_t name_charset, bool_t mandatory, Dz1Error *err)
{
	Dz1MetaTagDescrEntry *ret = NULL, *node = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Dz1MetaTagDB_getTagDescr(dst, id) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (dst == NULL || name == NULL || name_size == 0 || name_charset == NULL || strlen(name_charset) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (name_size == -1 && (name_size = strlen(name)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1MetaTagDescrEntry_new(id, NULL, NULL, mandatory, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
		if ((node->name = Dz1Asn1UTF8Str_newFromBuf(name, name_size, name_charset, errp)) == NULL) ERR_OUT(errp);
		else if ((node->name_w = _mk_unicode_str(node->name, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->table->add(dst->table, node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagDescrEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

// Dz1MetaTagDescrEntry *Dz1MetaTagDB_addTagDescrAnsi(Dz1MetaTagDB *dst,
// 												   u32_t id, str_t name, str_t name_charset,
// 												   bool_t mandatory, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1MetaTagDescrEntry *ret = Dz1MetaTagDB_addTagDescrBuf(dst, id, (u8_t *)name, -1, name_charset, mandatory, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

Dz1MetaTagDescrEntry *Dz1MetaTagDB_addTagDescrW(Dz1MetaTagDB *dst, u32_t id, wstr_t name, bool_t mandatory, Dz1Error *err)
{
	size_t len = 0;
	Dz1MetaTagDescrEntry *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (name == NULL || (len = wcslen(name)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDB_addTagDescrBuf(dst, id, (u8_t *)name, sizeof(wchar_t) * len, WINDOWS_UNICODE, mandatory, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1MetaTagDescrEntry *Dz1MetaTagDB_addTagDescrA(Dz1MetaTagDB *dst, u32_t id, str_t name, bool_t mandatory, Dz1Error *err)
{
	size_t len = 0;
	Dz1MetaTagDescrEntry *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (name == NULL || (len = strlen(name)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDB_addTagDescrBuf(dst, id, (u8_t *)name, len, "EUC-KR", mandatory, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1MetaTagDB_delTagDescr(Dz1MetaTagDB *dst, u32_t id)
{
	Dz1MetaTagDescrEntry key = { id };
	dst->table->remove(dst->table, &key);
}

Dz1MetaTagDescrEntry *Dz1MetaTagDB_getTagDescr(Dz1MetaTagDB *dst, u32_t id)
{
	Dz1MetaTagDescrEntry key = { id };
	return dst->table->find(dst->table, &key);
}

// Dz1MetaTagDB Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry Helper : Restrict
Dz1Error Dz1MetaTagDescrEntry_setRestrict(Dz1MetaTagDescrEntry *dst, Dz1MetaTagRestrictMode mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->status != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((dst->status = Dz1MetaTagRestrict_new(mode, errp)) == NULL) ERR_OUT(errp);

	return err;
}

void Dz1MetaTagDescrEntry_clrRestrict(Dz1MetaTagDescrEntry *dst)
{
	if (dst != NULL)
	{
		if (dst->status)
			Dz1MetaTagRestrict_delAndSetNull(&dst->status);
	}
}

Dz1Error Dz1MetaTagDescrEntry_addRestrict(Dz1MetaTagDescrEntry *dst, u32_t target_type)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->status == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1MetaTagRestrict *p = dst->status;
		Dz1MetaTargetTypeEntry key = { target_type }, *node = p->list->find(p->list, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MetaTargetTypeEntry_new(target_type, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
			if ((*errp = p->list->add(p->list, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTargetTypeEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_delRestrict(Dz1MetaTagDescrEntry *dst, u32_t target_type)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->status == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1MetaTargetTypeEntry key = { target_type };
		Dz1MetaTagRestrict *p = dst->status;
		p->list->remove(p->list, &key);
	}
	return err;
}
bool_t Dz1MetaTagDescrEntry_isAcceptable(Dz1MetaTagDescrEntry *p, u32_t type)
{
	bool_t ret = FALSE;
	if (p->status == NULL) ret = TRUE;
	else
	{
		Dz1MetaTagRestrict *status = p->status;
		Dz1MetaTargetTypeList *list = status->list;
		Dz1MetaTargetTypeEntry key = { type }, *node = list->find(list, &key);
		if (node == NULL)
		{	// 없음
			ret = status->mode == Dz1MetaTagRestrictMode_reject ? TRUE : FALSE;
		}
		else
		{	// 있음
			ret = status->mode == Dz1MetaTagRestrictMode_accept ? TRUE : FALSE;
		}
	}
	return ret;
}

// Dz1MetaTagDescrEntry Helper : Restrict
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry Helper : Descriptor
static Dz1MetaTagDescriptor *_setDescr(Dz1MetaTagDescrEntry *dst,
									   Dz1MetaTagDescriptorPresent type,
									   Dz1Error *err)
{
	Dz1MetaTagDescriptor *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || dst->descr != NULL || type < 0 || type >= Dz1MetaTagDescriptorPresent_max) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->descr = ret = Dz1MetaTagDescriptor_new(type, NULL, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1Error _setSimpleDescr(Dz1MetaTagDescrEntry *dst, Dz1MetaTagDescriptorPresent present)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_setDescr(dst, present, errp) == NULL) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrNumber(Dz1MetaTagDescrEntry *dst, Dz1MetaTagDescrNum type)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_number, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.number = Dz1MetaTagDescrNumber_new(type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrFloat(Dz1MetaTagDescrEntry *dst, u32_t precision)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_floating, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.floating = Dz1MetaTagDescrFloat_new(precision, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrGrade(Dz1MetaTagDescrEntry *dst,
											u8_t max_grade,
											u8_t *display_letter, size_t display_letter_len,
											str_t display_letter_charset)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || display_letter == NULL || display_letter_len == 0 || display_letter_charset == NULL || strlen(display_letter_charset) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (display_letter_len == -1 && (display_letter_len = strlen(display_letter)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_grade, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrGrade *g = NULL;
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.grade = g = Dz1MetaTagDescrGrade_new(max_grade, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((g->grade_unit = Dz1Asn1UTF8Str_newFromBuf(display_letter, display_letter_len, display_letter_charset, errp)) == NULL) ERR_OUT(errp);
		else if ((g->grade_unit_w = _mk_unicode_str(g->grade_unit, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrGradeAnsi(Dz1MetaTagDescrEntry *dst, u8_t max_grade,
												str_t display_letter, str_t display_letter_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1MetaTagDescrEntry_setDescrGrade(dst, max_grade, (u8_t *)display_letter, -1, display_letter_charset)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrString(Dz1MetaTagDescrEntry *dst, str_t charset)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || charset == NULL || strlen(charset) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_string, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrString *g = NULL;
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.string = g = Dz1MetaTagDescrString_new(charset, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrWebUrl(Dz1MetaTagDescrEntry *dst)
{
	return _setSimpleDescr(dst, Dz1MetaTagDescriptorPresent_web_url);
}

Dz1MetaTagDescrEnums *Dz1MetaTagDescrEntry_setDescrEnums(Dz1MetaTagDescrEntry *dst, Dz1Error *err)
{
	Dz1MetaTagDescrEnums *ret = NULL;
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_enumerate, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.enumerate = ret = Dz1MetaTagDescrEnums_create(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return ret;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrDate(Dz1MetaTagDescrEntry *dst, Dz1MetaTagDescrDate8Mode mode)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_date, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.date = Dz1MetaTagDescrDate_new(mode, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrAlias(Dz1MetaTagDescrEntry *dst, u32_t origin_descr_id)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_alias, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrAlias *g = NULL;
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.alias = g = Dz1MetaTagDescrAlias_new(origin_descr_id, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEntry_setDescrBinary(Dz1MetaTagDescrEntry *dst)
{
	return _setSimpleDescr(dst, Dz1MetaTagDescriptorPresent_binary);
}

Dz1Error Dz1MetaTagDescrEntry_setDescrUser(Dz1MetaTagDescrEntry *dst, u32_t user_handling_Type)
{
	Dz1MetaTagDescriptor *p = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p = _setDescr(dst, Dz1MetaTagDescriptorPresent_user, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
		if ((p->x.user = Dz1MetaTagDescriptorUser_new(user_handling_Type, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDescriptor_delAndSetNull, (void *)&dst->descr);
	}
	return err;
}

void Dz1MetaTagDescrEntry_clrDescr(Dz1MetaTagDescrEntry *dst)
{
	if (dst != NULL) Dz1MetaTagDescriptor_delAndSetNull(&dst->descr);
}

// Dz1MetaTagDescrEntry Helper : Descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Enums Helper
static Dz1MetaTagDescrEnumIndex *Dz1MetaTagDescrEnumTable_search(Dz1MetaTagDescrEnumTable *table, Dz1Asn1UTF8Str *str)
{
	Dz1MetaTagDescrEnumIndex key = { 0, str };
	return table->find(table, &key);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_searchValue(Dz1MetaTagDescrEnums *enums, u32_t v)
{
	Dz1MetaTagDescrEnumEntry key = { v };
	return enums->values->find(enums->values, &key);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_searchString(Dz1MetaTagDescrEnums *enums, Dz1Asn1UTF8Str *str)
{
	Dz1MetaTagDescrEnumIndex key = { 0, str };
	return (Dz1MetaTagDescrEnumEntry *)enums->strings->find(enums->strings, &key);
}

static Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_searchByKeyV(Dz1MetaTagDescrEnums *enums, Dz1MetaTagDescrEnumEntry *key)
{
	return enums->values->find(enums->values, key);
}

static Dz1MetaTagDescrEnumEntry *_Dz1MetaTagDescrEnums_extractKeyV(Dz1MetaTagDescrEnums *src, Dz1MetaTagDescrEnumEntry *key)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEnumEntry *ret = NULL, *node = src->values->extract(src->values, key);
	if (node == NULL) Dz1Error_set(errp, ENOENT);
	else
	{
		src->strings->extract(src->strings, (Dz1MetaTagDescrEnumIndex *)node);
		ret = node;
	}
	return ret;
}

static Dz1MetaTagDescrEnumEntry **Dz1MetaTagDescrEnums_mkArray(Dz1MetaTagDescrEnums *src, u32_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDescrEnumEntry **ret = NULL;
	Dz1MetaTagDescrEnumList *table = src->values;
	if ((ret = table->get_array(table, ret_cnt, errp)) == NULL) ERR_OUT(errp);

	return ret;
}

Dz1MetaTagDescrEnums *Dz1MetaTagDescrEnums_create(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDescrEnums *ret =Dz1MetaTagDescrEnums_new(Dz1MetaTagDescrEnums_addNode,
														Dz1MetaTagDescrEnums_searchByKeyV,
														_Dz1MetaTagDescrEnums_extractKeyV,
														Dz1MetaTagDescrEnums_mkArray,
														Dz1MetaTagDescrEnums_getLast, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

Dz1Error Dz1MetaTagDescrEnums_addEntryBuf(Dz1MetaTagDescrEnums *dst, u32_t v, u8_t *str, size_t str_len, str_t str_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || str == NULL || str_len == 0 || str_charset == NULL || str_charset[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1MetaTagDescrEnumEntry key = { v }, *node = dst->values->find(dst->values, &key);
		if (node != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MetaTagDescrEnumEntry_new(v, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
			if ((node->string = Dz1Asn1UTF8Str_newFromBuf(str, str_len, str_charset, errp)) == NULL) ERR_OUT(errp);
			else if (Dz1MetaTagDescrEnums_searchString(dst, node->string) != NULL) ERR_SET_OUT(errp, EEXIST);
			else if ((node->str_w = _mk_unicode_str(node->string, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = dst->values->add(dst->values, node)).code) ERR_OUT(errp);
			else if ((*errp = dst->strings->add(dst->strings, (Dz1MetaTagDescrEnumIndex *)node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEnums_addEntryW(Dz1MetaTagDescrEnums *dst, u32_t v, wstr_t str)
{
	size_t len = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (str == NULL || (len = wcslen(str)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1MetaTagDescrEnums_addEntryBuf(dst, v, (u8_t *)str, len << 1, WINDOWS_UNICODE)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDescrEnums_addEntryA(Dz1MetaTagDescrEnums *dst, u32_t v, str_t str)
{
	size_t len = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (str == NULL || (len = strlen(str)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1MetaTagDescrEnums_addEntryBuf(dst, v, (u8_t *)str, len, "EUC-KR")).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDescrEnums_addNode(Dz1MetaTagDescrEnums *dst, Dz1MetaTagDescrEnumEntry *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || node == NULL || node->string == NULL || node->string->data == NULL || node->string->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1MetaTagDescrEnums_searchString(dst, node->string) != NULL)
	{	// exist string
		ERR_SET_OUT(errp, EEXIST);
	}
	else if (Dz1MetaTagDescrEnums_searchValue(dst, node->value) != NULL)
	{	// exist value
		ERR_SET_OUT(errp, EEXIST);
	}
	else if (node->str_w == NULL && (node->str_w = _mk_unicode_str(node->string, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = dst->values->add(dst->values, node)).code) ERR_OUT(errp);
	else if ((*errp = dst->strings->add(dst->strings, (Dz1MetaTagDescrEnumIndex *)node)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

void Dz1MetaTagDescrEnums_delEntry(Dz1MetaTagDescrEnums *dst, u32_t v)
{
	if (dst != NULL)
	{
		Dz1MetaTagDescrEnumEntry key = { v }, *node = dst->values->extract(dst->values, &key);
		if (node != NULL)
		{
			pthread_cleanup_push(Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
			dst->strings->extract(dst->strings, (Dz1MetaTagDescrEnumIndex *)node);
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrEnumEntry_delAndSetNull, (void *)&node);
		}
	}
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_getByValue(Dz1MetaTagDescrEnums *src, u32_t v, Dz1Error *err)
{
	Dz1MetaTagDescrEnumEntry *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDescrEnums_searchValue(src, v)) == NULL) Dz1Error_set(errp, ENOENT);
	else Dz1Error_set(errp, 0);

	return ret;
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_getByCharset(Dz1MetaTagDescrEnums *src,
															u8_t *name, size_t name_len,
															str_t name_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDescrEnumEntry *ret = NULL;
	Dz1Asn1UTF8Str *str = NULL;
	if (src == NULL || name == NULL || name_len == 0 || name_charset == NULL || strlen(name_charset) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (name_len == -1 && (name_len = strlen(name)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((str =  Dz1Asn1UTF8Str_newFromBuf(name, name_len, name_charset, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&str);
		if ((ret = Dz1MetaTagDescrEnums_getByStr(src, str, errp)) == NULL) { }
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&str);
	}
	return ret;
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_getByStr(Dz1MetaTagDescrEnums *src, Dz1Asn1UTF8Str *str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDescrEnumEntry *ret = NULL;
	if (src == NULL || str == NULL || str->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MetaTagDescrEnums_searchString(src, str)) == NULL) Dz1Error_set(errp, ENOENT);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_extract(Dz1MetaTagDescrEnums *src, u32_t v)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEnumEntry *ret = NULL, key = { v };
	return _Dz1MetaTagDescrEnums_extractKeyV(src, &key);
}

Dz1MetaTagDescrEnumEntry *Dz1MetaTagDescrEnums_getLast(Dz1MetaTagDescrEnums *src)
{
	Dz1MetaTagDescrEnumEntry *ret = NULL;
	if (src != NULL && src->values != NULL)
		ret = src->values->getTail(src->values);
	return ret;
}

typedef struct Dz1MetaTagDescrEnumsMkArrayArg
{
	Dz1MetaTagDescrEnumEntry **arr;
	u32_t idx;
} Dz1MetaTagDescrEnumsMkArrayArg;

static Dz1Error _Dz1MetaTagDescrEnums_mkArray(void *ptr, Dz1MetaTagDescrEnumEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEnumsMkArrayArg *arg = (Dz1MetaTagDescrEnumsMkArrayArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

// Enums Helper
///////////////////////////////////////////////////////////////////////////////

#if 0
///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrStrSets Helper
static Dz1Error Dz1MetaTagDescrStrSet_addString(Dz1MetaTagDescrStrSet *dst, Dz1Asn1UTF8Str *name, bool_t isCurrent)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrEntry2 key = { 0, name }, *node = dst->history2->find(dst->history2, &key);
	if (node != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((node = Dz1MetaTagDescrStrEntry2_new(dst->history->count(dst->history), NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDescrStrEntry2_delAndSetNull, (void *)&node);
		if ((*errp = dst->history->add(dst->history, (Dz1MetaTagDescrStrEntry *)node)).code) ERR_OUT(errp);
		else if ((*errp = dst->history2->add(dst->history2, node)).code) ERR_OUT(errp);
		else
		{
			if (isCurrent) dst->curr = (Dz1MetaTagDescrStrEntry *)node;
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrEntry2_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error Dz1MetaTagDescrStrSet_addStringAnsi(Dz1MetaTagDescrStrSet *dst, str_t name, str_t name_charset, bool_t isCurrent)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Asn1UTF8Str *utf8 = Dz1Asn1UTF8Str_newFromStr(name, name_charset, errp);
	if (utf8 == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrStrEntry2 key = { 0, utf8 }, *node = NULL;
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((node = dst->history2->find(dst->history2, &key)) != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((node = Dz1MetaTagDescrStrEntry2_new(dst->history->count(dst->history), utf8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			utf8 = NULL;
			pthread_cleanup_push(Dz1MetaTagDescrStrEntry2_delAndSetNull, (void *)&node);
			if ((*errp = dst->history->add(dst->history, (Dz1MetaTagDescrStrEntry *)node)).code) ERR_OUT(errp);
			else if ((*errp = dst->history2->add(dst->history2, node)).code) ERR_OUT(errp);
			else
			{
				if (isCurrent) dst->curr = (Dz1MetaTagDescrStrEntry *)node;
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrEntry2_delAndSetNull, (void *)&node);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
	}
	return err;
}

static Dz1MetaTagDescrStrEntry *Dz1MetaTagDescrStrSet_findName(Dz1MetaTagDescrStrSet *dst, Dz1Asn1UTF8Str *name)
{
	Dz1MetaTagDescrStrEntry2 key = { 0, name };
	return (Dz1MetaTagDescrStrEntry *)dst->history2->extract(dst->history2, &key);
}

static Dz1MetaTagDescrStrEntry *Dz1MetaTagDescrStrSet_extractString(Dz1MetaTagDescrStrSet *dst, Dz1Asn1UTF8Str *name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrEntry2 key = { 0, name }, *node = dst->history2->extract(dst->history2, &key);
	if (node != NULL)
		dst->history->extract(dst->history, (Dz1MetaTagDescrStrEntry *)node);
	return (Dz1MetaTagDescrStrEntry *)node;
}

static Dz1MetaTagDescrStrEntry *Dz1MetaTagDescrStrSet_extractStringAnsi(Dz1MetaTagDescrStrSet *dst, str_t name, str_t name_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrEntry *ret = NULL;
	Dz1Asn1UTF8Str *utf8 = Dz1Asn1UTF8Str_newFromStr(name, name_charset, errp);
	if (utf8 == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrStrEntry2 key = { 0, utf8 }, *node = NULL;
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((node = dst->history2->extract(dst->history2, &key)) != NULL)
		{
			dst->history->extract(dst->history, (Dz1MetaTagDescrStrEntry *)node);
			ret = (Dz1MetaTagDescrStrEntry *)node;
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
	}
	return ret;
}

Dz1Error Dz1MetaTagDescrStrSets_addString(Dz1MetaTagDescrStrSets *dst, u32_t id, Dz1Asn1UTF8Str *name, bool_t isCurrent)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL)
	{
		if ((node = Dz1MetaTagDescrStrSet_new(id, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTagDescrStrSet_delAndSetNull, (void *)&node);
			if ((*errp = Dz1MetaTagDescrStrSet_addString(node, name, isCurrent)).code) ERR_OUT(errp);
			else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrSet_delAndSetNull, (void *)&node);
		}
	}
	else if ((*errp = Dz1MetaTagDescrStrSet_addString(node, name, isCurrent)).code) ERR_OUT(errp);
	return err;
}
Dz1Error Dz1MetaTagDescrStrSets_addStringAnsi(Dz1MetaTagDescrStrSets *dst, u32_t id, str_t name, str_t name_charset, bool_t isCurrent)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL)
	{
		if ((node = Dz1MetaTagDescrStrSet_new(id, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MetaTagDescrStrSet_delAndSetNull, (void *)&node);
			if ((*errp = Dz1MetaTagDescrStrSet_addStringAnsi(node, name, name_charset, isCurrent)).code) ERR_OUT(errp);
			else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrSet_delAndSetNull, (void *)&node);
		}
	}
	else if ((*errp = Dz1MetaTagDescrStrSet_addStringAnsi(node, name, name_charset, isCurrent)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1MetaTagDescrStrSets_delString(Dz1MetaTagDescrStrSets *dst, u32_t id, Dz1Asn1UTF8Str *name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MetaTagDescrStrEntry *entry = Dz1MetaTagDescrStrSet_extractString(node, name);
		if (entry != NULL)
		{
			pthread_cleanup_push(Dz1MetaTagDescrStrEntry_delAndSetNull, (void *)&entry);
			if (node->curr == entry) node->curr = NULL;
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrEntry_delAndSetNull, (void *)&entry);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrStrSets_delStringAnsi(Dz1MetaTagDescrStrSets *dst, u32_t id, str_t name, str_t name_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MetaTagDescrStrEntry *entry = Dz1MetaTagDescrStrSet_extractStringAnsi(node, name, name_charset);
		if (entry != NULL)
		{
			pthread_cleanup_push(Dz1MetaTagDescrStrEntry_delAndSetNull, (void *)&entry);
			if (node->curr == entry) node->curr = NULL;
			pthread_cleanup_pop(1); // (Dz1MetaTagDescrStrEntry_delAndSetNull, (void *)&entry);
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrStrSets_setCurrent(Dz1MetaTagDescrStrSets *dst, u32_t id, Dz1Asn1UTF8Str *name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1MetaTagDescrStrEntry *entry = Dz1MetaTagDescrStrSet_findName(node, name);
		if (entry == NULL) ERR_SET_OUT(errp, ENOENT);
		else node->curr = entry;
	}
	return err;
}

Dz1Error Dz1MetaTagDescrStrSets_setCurrentAnsi(Dz1MetaTagDescrStrSets *dst, u32_t id, str_t name, str_t name_charset)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrStrSet key = { id }, *node = dst->find(dst, &key);
	if (node == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		Dz1Asn1UTF8Str *utf8 = Dz1Asn1UTF8Str_newFromStr(name, name_charset, errp);
		if (utf8 == NULL) ERR_OUT(errp);
		else
		{
			Dz1MetaTagDescrStrEntry *entry = NULL;
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
			if ((entry = Dz1MetaTagDescrStrSet_findName(node, utf8)) == NULL) ERR_SET_OUT(errp, ENOENT);
			else node->curr = entry;
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		}
	}
	return err;
}

void Dz1MetaTagDescrStrSets_delStrings(Dz1MetaTagDescrStrSets *dst, u32_t id)
{
	Dz1MetaTagDescrStrSet key = { id };
	dst->remove(dst, &key);
}

Dz1MetaTagDescrStrEntry *Dz1MetaTagDescrStrSets_getCurrent(Dz1MetaTagDescrStrSets *src, u32_t id)
{
	Dz1MetaTagDescrStrEntry *ret = NULL;
	Dz1MetaTagDescrStrSet key = { id };
	Dz1MetaTagDescrStrSet *str_set = src->find(src, &key);
	if (str_set != NULL)
	{
		ret = str_set->curr;
		if (ret == NULL)
			ret = str_set->history->getTail(str_set->history);
	}
	return ret;
}

// Dz1MetaTagDescrStrSets Helper
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1MetaTagDescrStrEntry_mkNameW(Dz1MetaTagDescrStrEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->name_w == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->name) == NULL || utf8->size == 0) { }
		else
		{
			if ((p->name_w = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
			else Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->name_w, sizeof(wchar_t) * utf8->size);
		}
	}
	return err;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrAlias Helper
Dz1Error Dz1MetaTagDescrAlias_resolv(Dz1MetaTagDescrAlias *src, Dz1MetaTagDB *db)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (src->origin_descr == NULL)
	{
		Dz1MetaTagDescrEntry *p = NULL;
		if ((p = Dz1MetaTagDB_getTagDescr(db, src->origin_descr_id)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			Dz1MetaTagDescriptor *i = p->descr;
			if (i->present == Dz1MetaTagDescriptorPresent_alias)
			{
				Dz1MetaTagDescrAlias *i_alias = i->x.alias;
				if ((*errp = Dz1MetaTagDescrAlias_resolv(i_alias, db)).code) ERR_OUT(errp);
				else src->origin_descr = i_alias->origin_descr;
			}
			else src->origin_descr = i;
		}
	}

	return err;
}
// Dz1MetaTagDescrAlias Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeList Helper
// Dz1MetaTargetTypeList Helper
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1MetaTargetTypeEntry_mkNameW(Dz1MetaTargetTypeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->name_w == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->name) == NULL || utf8->size == 0) { }
		else
		{
			if ((p->name_w = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
			else
			{
//				Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->name_w, sizeof(wchar_t) * utf8->size);
				Dz1Asn1UTF8Str_conv(utf8, WINDOWS_UNICODE, (char *)p->name_w, sizeof(wchar_t) * utf8->size, errp); // modified by gm 20230605
			}
		}
	}
	return err;
}

Dz1Error Dz1MetaTargetTypeEntry_setNameW(Dz1MetaTargetTypeEntry *p, wstr_t name_w)
{
	size_t name_w_len;
	Dz1Asn1UTF8Str *utf8 = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL || name_w == NULL || (name_w_len = wcslen(name_w)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((utf8 = Dz1Asn1UTF8Str_newFromBuf((u8_t *)name_w, (name_w_len + 1) << 2, WINDOWS_UNICODE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wstr_t _name_w = NULL;
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
		if ((_name_w = Dz1StrW_dup(name_w, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1StrW_delAndSetNull(&p->name_w);
			p->name_w = _name_w; _name_w = NULL;
			Dz1Asn1UTF8Str_delAndSetNull(&p->name);
			p->name = utf8; utf8 = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&utf8);
	}
	return err;
}


Dz1Error Dz1MetaTagDescrEntry_mkNameW(Dz1MetaTagDescrEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->name_w == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->name) == NULL || utf8->size == 0) { }
		else
		{
			if ((p->name_w = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
			else
			{
//				Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->name_w, sizeof(wchar_t) * utf8->size);
				Dz1Asn1UTF8Str_conv(utf8, WINDOWS_UNICODE, (char *)p->name_w, sizeof(wchar_t) * utf8->size, errp); // modified by gm 20230605
			}
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrGrade_mkUnitW(Dz1MetaTagDescrGrade *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->grade_unit_w == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->grade_unit) == NULL || utf8->size == 0) { }
		else
		{
//			wchar_t temp[16] = { 0, };
//			size_t temp_size = mbstowcs(temp, utf8->data, utf8->size);
			if ((p->grade_unit_w = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
			else
			{
//				Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->grade_unit_w, sizeof(wchar_t) * utf8->size);
				Dz1Asn1UTF8Str_conv(utf8, WINDOWS_UNICODE, (char *)p->grade_unit_w, sizeof(wchar_t) * utf8->size, errp); // modified by gm 20230605
			}
		}
	}
	return err;
}

Dz1Error Dz1MetaTagDescrEnumEntry_mkNameW(Dz1MetaTagDescrEnumEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->str_w == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->string) == NULL || utf8->size == 0) { }
		else if ((p->str_w = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
//			Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->str_w, sizeof(wchar_t) * utf8->size);
			Dz1Asn1UTF8Str_conv(utf8, WINDOWS_UNICODE, (char *)p->str_w, sizeof(wchar_t) * utf8->size, errp); // modified by gm 20230605
		}
	}
	return err;
}

Dz1Error Dz1MetaTagUserTypeEntry_mkNameW(Dz1MetaTagUserTypeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->userTypeNameW == NULL)
	{
		Dz1Asn1UTF8Str *utf8 = NULL;
		if ((utf8 = p->userTypeName) == NULL || utf8->size == 0) { }
		else if ((p->userTypeNameW = (wstr_t)Dz1Calloc(sizeof(wchar_t), utf8->size + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
//			Dz1Asn1UTF8Str_printable(utf8, WINDOWS_UNICODE, (u8_t *)p->userTypeNameW, sizeof(wchar_t) * utf8->size);
			Dz1Asn1UTF8Str_conv(utf8, WINDOWS_UNICODE, (char *)p->userTypeNameW, sizeof(wchar_t) * utf8->size, errp); // modified by gm 20230605
		}
	}
	return err;
}
