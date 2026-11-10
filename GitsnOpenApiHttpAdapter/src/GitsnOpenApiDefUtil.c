#include "GitsnOpenApiDef.h"
#include <GitsnOpenApi.h>
#include <ctype.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Misc
static str_t __week_dat_name_u9[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
static str_t __month_name_u8[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
bool_t GitsnOpenApiUtil_initDateStrU(char *dst, size_t dst_size, time_t *t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	struct tm *_tmNow;
	if (dst_size < 30) ERR_SET_OUT(errp, ENOMEM);
	else if ((_tmNow = gmtime(t)) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmNow = *_tmNow;
		_std_snprintfA(dst, dst_size - 1, "%s, %d %s %04d %02d:%02d:%02d GMT",	// max 29 byte letters
						__week_dat_name_u9[tmNow.tm_wday], tmNow.tm_mday, 
						__month_name_u8[tmNow.tm_mon], tmNow.tm_year + 1900,
						tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
// Misc
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataEntry
static bool_t _GitsnOpenApiDataEntry_isSensitiveHeader(str_t key)
{
	str_t names[] = {"authorization", "x-api-key", "apikey", NULL};
	size_t i = 0;

	if (key == NULL) return FALSE;
	for (i = 0; names[i] != NULL; i++)
	{
		const char *lhs = key;
		const char *rhs = names[i];
		while (*lhs != 0 && *rhs != 0 && tolower((unsigned char)*lhs) == tolower((unsigned char)*rhs))
		{
			lhs++;
			rhs++;
		}
		if (*lhs == 0 && *rhs == 0) return TRUE;
	}
	return FALSE;
}

void GitsnOpenApiDataEntry_dump(GitsnOpenApiDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
#ifndef UNIX_SYSTEM
		Dz1Str _key = NULL, _value = NULL;
		Dz1Str key = "#error", value = "#error";
		bool_t sensitive = _GitsnOpenApiDataEntry_isSensitiveHeader(p->key_utf8);
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&_key);
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&_value);
		if ((_key	= Dz1String_conv(p->key_utf8,	strlen(p->key_utf8),	DZ1_SYSTEM_UTF8_CHARSET, DZ1_SYSTEM_CHARSET, NULL)) != NULL) key = _key;
		if (sensitive == TRUE) value = Dz1T("***");
		else if ((_value	= Dz1String_conv(p->value_utf8,	strlen(p->value_utf8),	DZ1_SYSTEM_UTF8_CHARSET, DZ1_SYSTEM_CHARSET, NULL)) != NULL) value = _value;
		Dz1Thread_printf(Dz1T("%s: %s\n"), key, value);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&_value);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&_key);
#else
		Dz1Thread_printf("\"%s\": \"%s\"\n", p->key_utf8,
		                 _GitsnOpenApiDataEntry_isSensitiveHeader(p->key_utf8) ? "***" : p->value_utf8);
#endif
	}
}

static bool_t _decode_query_component(char *text, Dz1Error *errp)
{
    char *read = text, *write = text;
    while (*read) {
        unsigned char value = (unsigned char)*read++;
        if (value == '+') value = ' ';
        else if (value == '%') {
            int high, low;
            if (!read[0] || !read[1] || !isxdigit((unsigned char)read[0]) || !isxdigit((unsigned char)read[1])) { Dz1Error_set(errp, EINVAL); return FALSE; }
            high = isdigit((unsigned char)read[0]) ? read[0]-'0' : tolower((unsigned char)read[0])-'a'+10;
            low = isdigit((unsigned char)read[1]) ? read[1]-'0' : tolower((unsigned char)read[1])-'a'+10;
            value = (unsigned char)(high*16+low); read += 2;
            if (!value) { Dz1Error_set(errp, EINVAL); return FALSE; }
        }
        *write++ = (char)value;
    }
    *write = 0; return TRUE;
}

static GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_genFromStrU(str_t str_u8, Dz1Error *errp)
{
	GitsnOpenApiDataEntry *ret = NULL;
	str_t key_u8 = str_u8, value_u8;
	if (Dz1Str_isVoid(str_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((value_u8 = strchr(key_u8, '=')) == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		*value_u8++ = 0;
		if (!_decode_query_component(key_u8, errp) || !_decode_query_component(value_u8, errp)) ERR_OUT(errp);
		else if ((ret = GitsnOpenApiDataEntry_new(key_u8, value_u8, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// GitsnOpenApiDataEntry
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas_insertNode
static Dz1ListAddCancel_impl(GitsnOpenApiDataIndex, GitsnOpenApiDataEntry)
bool_t GitsnOpenApiDatas_insertNode(GitsnOpenApiDatas *dst, GitsnOpenApiDataEntry **_node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDataEntry *node = NULL;
	if (dst == NULL || _node == NULL || (node = *_node) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->index->add(dst->index, node)).code)
	{
		/* 반복 Query는 첫 항목을 검색 index에 유지하고 전체 항목을 storage에
		 * 보존한다. 상위 시나리오 검증기가 중복 파라미터를 판정해야 한다. */
		if (errp->code != EEXIST) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			if ((*errp = dst->storage->add(dst->storage, node)).code) ERR_OUT(errp);
			else
			{
				*_node = NULL;
				Dz1Error_set(errp, 0);
			}
		}
	}
	else
	{
		Dz1ListAddCancelArg arg = { (void *)dst->index, (void **)_node };
		pthread_cleanup_push(GitsnOpenApiDataIndex_addCancel, (void *)&arg);
		if ((*errp = dst->storage->add(dst->storage, node)).code) ERR_OUT(errp);
		else
		{
			*_node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiDataIndex_addCancel, (void *)&arg);
	}
	return ERR_IS_SUCCESS(errp);
}
// GitsnOpenApiDatas_insertNode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas_genFromArgStrU
GitsnOpenApiDatas *GitsnOpenApiDatas_genFromArgStrU(str_t str_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GitsnOpenApiDatas *ret = NULL;

	if (Dz1Str_isVoid(str_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GitsnOpenApiDatas_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		str_t sp = str_u8, amp;
		pthread_cleanup_push(GitsnOpenApiDatas_delAndSetNull, (void *)&ret);
		while(errp->code == 0 && (amp = strchr(sp, '&')) != NULL)
		{
			*amp++ = 0;
			if (GitsnOpenApiDatas_appendArgStrU(ret, sp, errp) == FALSE) ERR_OUT(errp);
			else { sp = amp; Dz1Error_set(errp, 0); }
		}

		if (errp->code == 0)
		{
			if (GitsnOpenApiDatas_appendArgStrU(ret, sp, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (GitsnOpenApiDatas_delAndSetNull, (void *)&ret);
	}
	return ret;
}

GitsnOpenApiDatas *GitsnOpenApiDatas_genFromArgStrA(str_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDatas *ret = NULL;
	str_t str_u8;
	if (Dz1Str_isVoid(str)) ERR_SET_OUT(errp, EINVAL);
	else if ((str_u8 = Dz1String_conv(str, strlen(str), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&str_u8);
		if ((ret = GitsnOpenApiDatas_genFromArgStrU(str_u8, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&str_u8);
	}
	return ret;
}

GitsnOpenApiDatas *GitsnOpenApiDatas_genFromArgStrW(wstr_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDatas *ret = NULL;
	str_t str_u8;
	if (Dz1Str_isVoid(str)) ERR_SET_OUT(errp, EINVAL);
	else if ((str_u8 = Dz1String_conv(str, wcslen(str) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&str_u8);
		if ((ret = GitsnOpenApiDatas_genFromArgStrU(str_u8, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&str_u8);
	}
	return ret;
}
// GitsnOpenApiDatas_genFromArgStrU
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas_appendArgStrU
bool_t GitsnOpenApiDatas_appendArgStrU(GitsnOpenApiDatas *dst, str_t str_u8, Dz1Error *errp)
{
	GitsnOpenApiDataEntry *node;
	if (Dz1Str_isVoid(str_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((node = GitsnOpenApiDataEntry_genFromStrU(str_u8, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
		if (GitsnOpenApiDatas_insertNode(dst, &node, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
	}
	return ERR_IS_SUCCESS(errp);
}
// GitsnOpenApiDatas_appendArgStrU
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas : String Value
static bool_t _GitsnOpenApiDatas_appendEntryStrU(GitsnOpenApiDatas *dst, str_t key_u8, str_t value_u8, Dz1Error *errp)
{
	GitsnOpenApiDataEntry *node = NULL;
	GitsnOpenApiDataList *storage = NULL;
	GitsnOpenApiDataIndex *index = NULL;
	if ((storage = dst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((index = dst->index) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((node = GitsnOpenApiDataEntry_new(key_u8, value_u8, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
		if ((*errp = index->add(index, node)).code) ERR_OUT(errp);
		else
		{
			Dz1ListAddCancelArg arg = { (void *)index, (void **)&node };
			pthread_cleanup_push(GitsnOpenApiDataIndex_addCancel, (void *)&arg);
			if ((*errp = storage->add(storage, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (GitsnOpenApiDataIndex_addCancel, (void *)&arg);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_appendEntryStrU(GitsnOpenApiDatas *dst, str_t key_u8, str_t value_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(key_u8) || Dz1Str_isVoid(value_u8))
		ERR_SET_OUT(errp, EINVAL);
	else if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, value_u8, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_appendEntryStrA(GitsnOpenApiDatas *dst, str_t key, str_t value, Dz1Error *err)
{
	str_t key_u8, value_u8;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(key) || Dz1Str_isVoid(value)) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, strlen(key), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);
		if ((value_u8 = Dz1String_conv(value, strlen(value), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&value_u8);
			if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, value_u8, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&value_u8);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}

#ifndef UNIX_SYSTEM
bool_t GitsnOpenApiDatas_appendEntryStrW(GitsnOpenApiDatas *dst, wstr_t key, wstr_t value, Dz1Error *err)
{
	str_t key_u8, value_u8;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(key) || Dz1Str_isVoid(value)) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, wcslen(key) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);
		if ((value_u8 = Dz1String_conv(value, wcslen(value) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&value_u8);
			if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, value_u8, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&value_u8);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#endif
// GitsnOpenApiDatas : String Value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas : Integer Value
bool_t GitsnOpenApiDatas_appendEntryNumU(GitsnOpenApiDatas *dst, str_t key_u8, s64_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(key_u8)) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char temp[128];
		_std_snprintfA(temp, sizeof(temp) - 1, DZ1_FMT64_A, value);
		if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, temp, err) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_appendEntryNumA(GitsnOpenApiDatas *dst, str_t key, s64_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t key_u8;
	if (dst == NULL || Dz1Str_isVoid(key)) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, strlen(key), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char temp[128];
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);

		_std_snprintfA(temp, sizeof(temp) - 1, DZ1_FMT64_A, value);
		if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, temp, err) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#ifndef UNIX_SYSTEM
bool_t GitsnOpenApiDatas_appendEntryNumW(GitsnOpenApiDatas *dst, wstr_t key, s64_t value, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t key_u8;
	if (dst == NULL || Dz1Str_isVoid(key)) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, wcslen(key) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char temp[128];
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);

		_std_snprintfA(temp, sizeof(temp) - 1, DZ1_FMT64_A, value);
		if (_GitsnOpenApiDatas_appendEntryStrU(dst, key_u8, temp, err) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#endif
// GitsnOpenApiDatas : Integer Value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas : Time Value
// Wed, 21 Jan 2026 20:15:31 GMT
static bool_t _GitsnOpenApiDatas_appendTimeStampU(GitsnOpenApiDatas *dst, str_t name_u8, time_t *t, Dz1Error *errp)
{
	struct tm *_tmNow = gmtime(t);
	if (_tmNow == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmNow = *_tmNow;
		char buf[256] = { 0, };
		_std_snprintfA(buf, sizeof(buf) - 1, "%s, %d %s %04d %02d:%02d:%02d GMT",
						__week_dat_name_u9[tmNow.tm_wday], tmNow.tm_mday, 
						__month_name_u8[tmNow.tm_mon], tmNow.tm_year + 1900,
						tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);

		if (_GitsnOpenApiDatas_appendEntryStrU(dst, name_u8, buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_appendTimeStampU(GitsnOpenApiDatas *dst, str_t name_u8, time_t *t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(name_u8) || t == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_GitsnOpenApiDatas_appendTimeStampU(dst, name_u8, t, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_appendTimeStampA(GitsnOpenApiDatas *dst, str_t key, time_t *t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t key_u8;
	if (dst == NULL || Dz1Str_isVoid(key) || t == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, strlen(key), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);
		if (_GitsnOpenApiDatas_appendTimeStampU(dst, key_u8, t, err) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#ifndef UNIX_SYSTEM
bool_t GitsnOpenApiDatas_appendTimeStampW(GitsnOpenApiDatas *dst, wstr_t key, time_t *t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t key_u8;
	if (dst == NULL || Dz1Str_isVoid(key) || t == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((key_u8 = Dz1String_conv(key, wcslen(key) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&key_u8);
		if (_GitsnOpenApiDatas_appendTimeStampU(dst, key_u8, t, err) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&key_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#endif
// GitsnOpenApiDatas : Time Value
///////////////////////////////////////////////////////////////////////////////

static bool_t _GitsnOpenApiDatas_removeU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *errp)
{
	GitsnOpenApiDataIndex *index;
	GitsnOpenApiDataList *storage;
	if ((index = dst->index) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((storage = dst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnOpenApiDataEntry key = { name_u8 }, *node = index->extract(index, &key);
		if (index == NULL) Dz1Error_set(errp, ENOENT);
		else
		{
			pthread_cleanup_push(GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
			storage->extract(storage, node);
			pthread_cleanup_pop(1); // (GitsnOpenApiDataEntry_delAndSetNull, (void *)&node);
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_removeU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(name_u8)) ERR_SET_OUT(errp, EINVAL);
	else if (_GitsnOpenApiDatas_removeU(dst, name_u8, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnOpenApiDatas_removeA(GitsnOpenApiDatas *dst, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	str_t name_u8;
	if (dst == NULL || Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if ((name_u8 = Dz1String_conv(name, strlen(name), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&name_u8);
		if (_GitsnOpenApiDatas_removeU(dst, name_u8, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&name_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#ifndef UNIX_SYSTEM
bool_t GitsnOpenApiDatas_removeW(GitsnOpenApiDatas *dst, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	str_t name_u8;
	if (dst == NULL || Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if ((name_u8 = Dz1String_conv(name, wcslen(name) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&name_u8);
		if (_GitsnOpenApiDatas_removeU(dst, name_u8, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&name_u8);
	}
	return ERR_IS_SUCCESS(errp);
}
#endif

static GitsnOpenApiDataEntry *_GitsnOpenApiDataEntry_findU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *errp)
{
	GitsnOpenApiDataEntry *ret = NULL;
	GitsnOpenApiDataIndex *index;
	if ((index = dst->index) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		GitsnOpenApiDataEntry key = { name_u8 };
		if ((ret = index->find(index, &key)) == NULL) Dz1Error_set(errp, ENOENT);
	}
	return ret;
}

GitsnOpenApiDataEntry *GitsnOpenApiDatas_findU(GitsnOpenApiDatas *dst, str_t name_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDataEntry *ret = NULL;
	if (dst != NULL && Dz1Str_isVoid(name_u8) == FALSE)
		ret = _GitsnOpenApiDataEntry_findU(dst, name_u8, errp);
	return ret;
}

GitsnOpenApiDataEntry *GitsnOpenApiDatas_findA(GitsnOpenApiDatas *dst, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDataEntry *ret = NULL;
	if (dst != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		str_t name_u8;
		if ((name_u8 = Dz1String_conv(name, strlen(name), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&name_u8);
			ret = _GitsnOpenApiDataEntry_findU(dst, name_u8, errp);
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&name_u8);
		}
	}
	return ret;
}
#ifndef UNIX_SYSTEM
GitsnOpenApiDataEntry *GitsnOpenApiDatas_findW(GitsnOpenApiDatas *dst, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnOpenApiDataEntry *ret = NULL;
	if (dst != NULL && Dz1Str_isVoid(name) == FALSE)
	{
		str_t name_u8;
		if ((name_u8 = Dz1String_conv(name, wcslen(name) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&name_u8);
			ret = _GitsnOpenApiDataEntry_findU(dst, name_u8, errp);
			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&name_u8);
		}
	}
	return ret;
}
#endif
///////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpRsp
typedef struct GitsnOpenApiHttpStatus
{
	u32_t					 code;
	str_t					 text_u8;
} GitsnOpenApiHttpStatus;
#define GitsnOpenApiHttpStatus_NULL				{ -1, NULL }
#define GitsnOpenApiHttpStatus_isNULL(ptr)		((ptr->code == (u32_t)-1 && ptr->text_u8 == NULL) ? TRUE : FALSE)
static GitsnOpenApiHttpStatus gitsnOpenApiHttpStatus[] = {
	{ 200,	"OK" },
	{ 201,	"Created" },
	{ 400,	"Bad Request" },
	{ 401,	"Unauthorized" },
	{ 404,	"Not Found" },
	{ 413,	"Payload Too Large" },
	{ 422,	"Unprocessable Entity" },
	{ 500,	"Internal Server Error" },
	GitsnOpenApiHttpStatus_NULL
};

bool_t GitsnOpenApiHttpRsp_setStatus(GitsnOpenApiHttpRsp *dst, u32_t code, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	bool_t found = FALSE;
	GitsnOpenApiHttpStatus *i;
	for (i = gitsnOpenApiHttpStatus; GitsnOpenApiHttpStatus_isNULL(i) == FALSE; i++)
	{
		if (i->code == code)
		{
			dst->code = i->code;
			dst->code_txt_utf8 = i->text_u8;
			found = TRUE;
			break;
		}
	}

	if (!found) Dz1Error_set(errp, ENOENT);

	return ERR_IS_SUCCESS(errp);
}
// GitsnOpenApiHttpRsp
///////////////////////////////////////////////////////////////////////////////
