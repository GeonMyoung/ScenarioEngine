#include "Dz1SockUtilUri.h"

typedef struct UriInfoParseEnvA
{
	str_t					sp;
} UriInfoParseEnvA;

static bool_t _take_protocolU(Dz1SockUtilUriInfoA *dst, UriInfoParseEnvA *env, Dz1Error *errp)
{
	str_t pt = NULL;
	if (dst == NULL || dst->prot != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((pt = strstr(env->sp, "://")) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->prot = Dz1StrA_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
	else
	{
		env->sp = pt + 3;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_hostU(Dz1SockUtilUriInfoA *dst, UriInfoParseEnvA *env, Dz1Error *errp)
{
	str_t pt = NULL;
	if (dst == NULL || dst->host != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((pt = strchr(env->sp, ':')) != NULL)
	{
		if ((dst->host = Dz1StrA_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->sp = pt;
			Dz1Error_set(errp, 0);
		}
	}
	else if ((pt = strchr(env->sp, '/')) != NULL)
	{
		if ((dst->host = Dz1StrA_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->sp = pt;
			Dz1Error_set(errp, 0);
		}
	}
	else if ((dst->host = Dz1StrA_dup(env->sp, errp)) == NULL) ERR_OUT(errp);
	else
	{
		while(*env->sp) env->sp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_portU(Dz1SockUtilUriInfoA *dst, UriInfoParseEnvA *env, Dz1Error *errp)
{
	if (dst == NULL || dst->port != 0) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (*env->sp == ':')
	{
		u32_t port = 0;
		str_t pt = NULL;
		env->sp++;
		if ((pt = strchr(env->sp, '/')) != NULL)
		{
			char temp[64] = { 0, };
			strncpy(temp, env->sp, (size_t)(pt - env->sp));
			if ((port = Dz1Ato32(temp)) == 0) ERR_SET_OUT(errp, EINVAL);
			else if (port > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
			else
			{
				dst->port = (u16_t)(port & 0xFFFF);
				env->sp = pt;
			}
		}
		else if ((port = Dz1Ato32(env->sp)) == 0) ERR_SET_OUT(errp, EINVAL);
		else if (port > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
		else
		{
			while(*env->sp) env->sp++;
			dst->port = (u16_t)(port & 0xFFFF);
		}
	}
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_pathU(Dz1SockUtilUriInfoA *dst, UriInfoParseEnvA *env, Dz1Error *errp)
{
	if (dst == NULL || dst->path != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (*env->sp == '/')
	{
		size_t len = strlen(env->sp);
		if (env->sp[len - 1] == '/')
		{
			if ((dst->path = Dz1StrA_dup(env->sp, errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->sp += len;
				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			char *dp = NULL;
			if ((dst->path = dp = Dz1Calloc(sizeof(char), len + 1 + 1, errp)) == NULL) ERR_OUT(errp);
			else
			{
				while(*env->sp) *dp++ = *env->sp++;
				*dp++ = '/';
				*dp = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	else if (*env->sp == 0)
	{
		if ((dst->path = Dz1StrA_dup("/", errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _Dz1SockUtilUriInfoU_parse(Dz1SockUtilUriInfoA *dst, str_t cloned_u8, Dz1Error *errp)
{
	UriInfoParseEnvA env = { cloned_u8 };
	if (0) { }
	else if (_take_protocolU(dst, &env, errp) == FALSE) ERR_OUT(errp);
	else if (_take_hostU(dst, &env, errp) == FALSE) ERR_OUT(errp);
	else if (_take_portU(dst, &env, errp) == FALSE) ERR_OUT(errp);
	else if (_take_pathU(dst, &env, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

// ws[s]://foo.bar[:port]/{path}
Dz1SockUtilUriInfoU *Dz1SockUtilUriInfoU_parse(str_t src_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockUtilUriInfoU *ret = NULL;
	if (Dz1Str_isVoid(src_u8)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SockUtilUriInfoA_new(NULL, NULL, 0, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		str_t temp = NULL;
		pthread_cleanup_push(Dz1SockUtilUriInfoA_delAndSetNull, (void *)&ret);
		if ((temp = Dz1StrA_dup(src_u8, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);

			if (_Dz1SockUtilUriInfoU_parse(ret, temp, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SockUtilUriInfoA_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_parse(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockUtilUriInfoA *ret = NULL;
	if (Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SockUtilUriInfoA_new(NULL, NULL, 0, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *src_u8 = NULL;
		pthread_cleanup_push(Dz1SockUtilUriInfoA_delAndSetNull, (void *)&ret);
		if ((src_u8 = Dz1String_conv((u8_t *)src, (u32_t)strlen(src), DZ1_SYSTEM_MBCS_CHARSET, "UTF-8", NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&src_u8);

			if ((ret = Dz1SockUtilUriInfoU_parse(src_u8, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&src_u8);
		}
		pthread_cleanup_pop(1); // (Dz1SockUtilUriInfoA_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
typedef struct UriInfoParseEnvW
{
	wstr_t					sp;
} UriInfoParseEnvW;

static bool_t _take_protocolW(Dz1SockUtilUriInfoW *dst, UriInfoParseEnvW *env, Dz1Error *errp)
{
	wstr_t pt = NULL;
	if (dst == NULL || dst->prot != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((pt = wcsstr(env->sp, L"://")) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((dst->prot = Dz1StrW_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
	else
	{
		env->sp = pt + 3;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_hostW(Dz1SockUtilUriInfoW *dst, UriInfoParseEnvW *env, Dz1Error *errp)
{
	wstr_t pt = NULL;
	if (dst == NULL || dst->host != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((pt = wcschr(env->sp, L':')) != NULL)
	{
		if ((dst->host = Dz1StrW_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->sp = pt;
			Dz1Error_set(errp, 0);
		}
	}
	else if ((pt = wcschr(env->sp, L'/')) != NULL)
	{
		if ((dst->host = Dz1StrW_ndup(env->sp, (size_t)(pt - env->sp), errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->sp = pt;
			Dz1Error_set(errp, 0);
		}
	}
	else if ((dst->host = Dz1StrW_dup(env->sp, errp)) == NULL) ERR_OUT(errp);
	else
	{
		while(*env->sp) env->sp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_portW(Dz1SockUtilUriInfoW *dst, UriInfoParseEnvW *env, Dz1Error *errp)
{
	if (dst == NULL || dst->port != 0) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (*env->sp == L':')
	{
		u32_t port = 0;
		wstr_t pt = NULL;
		env->sp++;
		if ((pt = wcschr(env->sp, L'/')) != NULL)
		{
			wchar_t temp[64] = { 0, };
			wcsncpy(temp, env->sp, (size_t)(pt - env->sp));
			if ((port = Dz1Wto32(temp)) == 0) ERR_SET_OUT(errp, EINVAL);
			else if (port > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
			else
			{
				dst->port = (u16_t)(port & 0xFFFF);
				env->sp = pt;
			}
		}
		else if ((port = Dz1Wto32(env->sp)) == 0) ERR_SET_OUT(errp, EINVAL);
		else if (port > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
		else
		{
			while(*env->sp) env->sp++;
			dst->port = (u16_t)(port & 0xFFFF);
		}
	}
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static bool_t _take_pathW(Dz1SockUtilUriInfoW *dst, UriInfoParseEnvW *env, Dz1Error *errp)
{
	if (dst == NULL || dst->path != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (env == NULL || env->sp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (*env->sp == L'/')
	{
		size_t len = wcslen(env->sp);
		if (env->sp[len - 1] == '/')
		{
			if ((dst->path = Dz1StrW_dup(env->sp, errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->sp += len;
				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			wchar_t *dp = NULL;
			if ((dst->path = dp = Dz1Calloc(sizeof(wchar_t), len + 1 + 1, errp)) == NULL) ERR_OUT(errp);
			else
			{
				while(*env->sp) *dp++ = *env->sp++;
				*dp++ = L'/';
				*dp = 0;
			}
		}
	}
	else if (*env->sp == 0)
	{
		if ((dst->path = Dz1StrW_dup(L"/", errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return ERR_IS_SUCCESS(errp);
}

// ws[s]://foo.bar[:port]/{path}
Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_parse(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SockUtilUriInfoW *ret = NULL;
	if (Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SockUtilUriInfoW_new(NULL, NULL, 0, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wstr_t temp = NULL;
		pthread_cleanup_push(Dz1SockUtilUriInfoW_delAndSetNull, (void *)&ret);
		if ((temp = Dz1StrW_dup(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			UriInfoParseEnvW env = { temp };
			pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
			if (0) { }
			else if (_take_protocolW(ret, &env, errp) == FALSE) ERR_OUT(errp);
			else if (_take_hostW(ret, &env, errp) == FALSE) ERR_OUT(errp);
			else if (_take_portW(ret, &env, errp) == FALSE) ERR_OUT(errp);
			else if (_take_pathW(ret, &env, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&temp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SockUtilUriInfoW_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif