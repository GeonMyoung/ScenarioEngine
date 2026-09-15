#include <dz1.h>
#include <codeconv.h>
#include <ctype.h>

#include <dz1_malloc.h>

#include <dz1_int.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>

#ifdef __BORLANDC__
#pragma warn -8006
#endif

str_t Dz1STRSTRSA(str_t src, str_t tgts[], str_t *ret_choosen)
{
	str_t ret = NULL;
	if (Dz1Str_isVoid(src) == FALSE)
	{
		str_t *i = NULL, tgt;
		for (i = tgts; *i != NULL; i++)
		{
			tgt = *i;
			if ((ret = strstr(src, tgt)) != NULL)
			{
				if (ret_choosen != NULL) *ret_choosen = tgt;
				break;
			}
		}
	}
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1STRSTRSW(wstr_t src, wstr_t tgts[], wstr_t *ret_choosen)
{
	wstr_t ret = NULL;
	if (Dz1Str_isVoid(src) == FALSE)
	{
		wstr_t *i = NULL, tgt;
		for (i = tgts; *i != NULL; i++)
		{
			tgt = *i;
			if ((ret = wcsstr(src, tgt)) != NULL)
			{
				if (ret_choosen != NULL) *ret_choosen = tgt;
				break;
			}
		}
	}
	return ret;
}
#endif

str_t dz1_built_in_str_clone(str_t p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StrA_dup(p, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void dz1_built_in_str_del(str_t p)
{
	if (p != NULL)
		Dz1Free(p);
}
int dz1_built_in_str_cmp(str_t a, str_t b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else ret = strcmp(a, b);
	return ret;
}

void dz1_built_in_strA_predump(str_t p, int tab)
{	// mbcs str_t
	if (p == NULL) Dz1ThreadA_printf("NULL");
	else if (p[0] == 0) Dz1ThreadA_printf("\"\"");
	else Dz1ThreadA_printf("\"%s\"", p);
}
void dz1_built_in_strA_dump(str_t p, int tab) { dz1_built_in_strA_predump(p, tab); Dz1ThreadA_putc('\n', NULL); }

void dz1_built_in_strA_prefdump(FILE *fp, str_t p, int tab)
{	// mbcs str_t
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL");
	else if (p[0] == 0) Dz1ThreadA_fprintf(fp, "\"\"");
	else Dz1ThreadA_fprintf(fp, "\"%s\"", p);
}
void dz1_built_in_strA_fdump(FILE *fp, str_t p, int tab) { dz1_built_in_strA_prefdump(fp, p, tab); Dz1ThreadA_fputc(fp, '\n', NULL); }

#ifndef UNIX_SYSTEM // 20250618 gm
wstr_t dz1_built_in_wstr_clone(wstr_t p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StrW_dup(p, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
void dz1_built_in_wstr_del(wstr_t p) { if (p != NULL) Dz1Free(p); }
int dz1_built_in_wstr_cmp(wstr_t a, wstr_t b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else ret = wcscmp(a, b);
	return ret;
}

void dz1_built_in_wstrA_predump(wstr_t p, int tab)
{	// mbcs wstr_t
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadW_printf(L"NULL");
	else if (p[0] == 0) Dz1ThreadW_printf(L"\"\"");
	else if ((temp = Dz1String_conv(p, wcslen(p) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_MBCS_CHARSET, NULL)) == NULL) Dz1ThreadW_printf(L"#errorn\n");
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_printf("\"%s\"", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
void dz1_built_in_wstrA_dump(wstr_t p, int tab) { dz1_built_in_wstrA_predump(p, tab); Dz1ThreadA_putc('\n', NULL); }

void dz1_built_in_wstrA_prefdump(FILE *fp, wstr_t p, int tab)
{	// mbcs wstr_t
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL");
	else if (p[0] == 0) Dz1ThreadW_fprintf(fp, L"\"\"");
	else if ((temp = Dz1String_conv(p, wcslen(p) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_MBCS_CHARSET, NULL)) == NULL) Dz1ThreadW_fprintf(fp, L"#errorn");
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_fprintf(fp, "\"%s\"", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
void dz1_built_in_wstrA_fdump(FILE *fp, wstr_t p, int tab) { dz1_built_in_wstrA_prefdump(fp, p, tab); Dz1ThreadA_fputc(fp, '\n', NULL); }

void dz1_built_in_strW_predump(str_t p, int tab)
{	// wide str_t
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_printf(L"NULL");
	else if (p[0] == 0) Dz1ThreadW_printf(L"\"\"");
	else if ((temp = Dz1String_conv(p, strlen(p), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_WIDE_CHARSET, NULL)) == NULL) Dz1ThreadW_printf(L"#errorn");
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_printf(L"\"%s\"", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
void dz1_built_in_strW_dump(str_t p, int tab) { dz1_built_in_strW_predump(p, tab); Dz1ThreadW_putc(L'\n', NULL); }

void dz1_built_in_strW_prefdump(FILE *fp, str_t p, int tab)
{	// wide str_t
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL");
	else if (p[0] == 0) Dz1ThreadW_fprintf(fp, L"\"\"");
	else if ((temp = Dz1String_conv(p, strlen(p), DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_WIDE_CHARSET, NULL)) == NULL) Dz1ThreadW_fprintf(fp, L"#errorn");
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_fprintf(fp, L"\"%s\"", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
void dz1_built_in_strW_fdump(FILE *fp, str_t p, int tab) { dz1_built_in_strW_prefdump(fp, p, tab); Dz1ThreadW_fputc(fp, L'\n', NULL); }

void dz1_built_in_wstrW_predump(wstr_t p, int tab)
{	// wide wstr_t
	if (p == NULL) Dz1ThreadW_printf(L"NULL");
	else if (p[0] == 0) Dz1ThreadW_printf(L"\"\"");
	else Dz1ThreadW_printf(L"\"%s\"", p);
}
void dz1_built_in_wstrW_dump(wstr_t p, int tab) { dz1_built_in_wstrW_predump(p, tab); Dz1ThreadW_putc(L'\n', NULL); }

void dz1_built_in_wstrW_prefdump(FILE *fp, wstr_t p, int tab)
{	// wide wstr_t
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL");
	else if (p[0] == 0) Dz1ThreadW_fprintf(fp, L"\"\"");
	else Dz1ThreadW_fprintf(fp, L"\"%s\"", p);
}
void dz1_built_in_wstrW_fdump(FILE *fp, wstr_t p, int tab) { dz1_built_in_wstrW_prefdump(fp, p, tab); Dz1ThreadW_fputc(fp, L'\n', NULL); }
#endif
///////////////////////////////////////////////////////////////////////////////
// Letter UL Case & Dump
char Dz1LetterA_ucase(char c)
{
	if ( c >= 'a' && c <= 'z') c = c - 'a' + 'A';
	return c;
}
char Dz1LetterA_lcase(char c)
{
	if ( c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
	return c;
}
void Dz1LetterA_dump(char *c, int tab)
{
	if (c == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("\'%c\'(%02X)\n", *c, *c);
}
#ifndef UNIX_SYSTEM
wchar_t Dz1LetterW_ucase(wchar_t c)
{
	if ( c >= L'a' && c <= L'z' ) c = c - L'a' + L'A';
	return c;
}
wchar_t Dz1LetterW_lcase(wchar_t c)
{
	if ( c >= L'A' && c <= L'Z') c = c - L'A' + L'a';
	return c;
}
void Dz1LetterW_dump(wchar_t *c, int tab)
{
	if (c == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"(%04X)\n", *c);
}
#endif
// Letter UL Case & Dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value to Letter
static char _digit2letterA(u32_t v)
{
	char ret = '0';
	if (v < 10) ret += v;
	return ret;
}
#ifndef UNIX_SYSTEM
static wchar_t _digit2letterW(u32_t v)
{
	wchar_t ret = L'0';
	if (v < 10) ret += v;
	return ret;
}
#endif
// Value to Letter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value8 from String : ASCII
ssize_t Dz1StrA_fromU8(char *dst, size_t sz, u8_t v)
{
	char buf[8] = { 0, }, *cp = &buf[6];
	ssize_t cnt = 0;
	u8_t r = 0;
	while(v >= 10)
	{
		r = v % 10;
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrA_fromS8(char *dst, size_t sz, s8_t v)
{
	char buf[8] = { 0, }, *cp = &buf[6];
	ssize_t cnt = 0;
	s8_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = v % 10;
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = '-'; cnt++;
	}

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}
// Value8 from String : ASCII
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value16 from String : ASCII
ssize_t Dz1StrA_fromU16(char *dst, size_t sz, u16_t v)
{
	char buf[8] = { 0, }, *cp = &buf[6];
	ssize_t cnt = 0;
	u16_t r = 0;
	while(v >= 10)
	{
		r = v % 10;
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrA_fromS16(char *dst, size_t sz, s16_t v)
{
	char buf[8] = { 0, }, *cp = &buf[6];
	ssize_t cnt = 0;
	s16_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = v % 10;
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = '-'; cnt++;
	}

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}
// Value16 from String : ASCII
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value32 from String : ASCII
ssize_t Dz1StrA_fromU32(char *dst, size_t sz, u32_t v)
{
	char buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrA_fromS32(char *dst, size_t sz, s32_t v)
{
	char buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = '-'; cnt++;
	}

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}
// Value32 from String : ASCII
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value64 from String : ASCII
ssize_t Dz1StrA_fromU64(char *dst, size_t sz, u64_t v)
{
	char buf[64] = { 0, }, *cp = &buf[62];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA((u32_t)(v & 0xFF));
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrA_fromS64(char *dst, size_t sz, s64_t v)
{
	char buf[64] = { 0, }, *cp = &buf[62];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterA(r); cnt++;
		cp--;
	}
	*cp = _digit2letterA((u32_t)(v & 0xFF)); cnt++;

	if (minux)
	{
		cp--;
		*cp = '-'; cnt++;
	}

	if (sz < (size_t)(cnt + 1)) return -1;
	else memcpy(dst, cp, cnt+1);

	return cnt;
}
// Value64 from String : ASCII
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Value8 from String : Windows UNICODE
ssize_t Dz1StrW_fromU8(wchar_t *dst, size_t sz, u8_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrW_fromS8(wchar_t *dst, size_t sz, s8_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = L'-'; cnt++;
	}

	if ((ssize_t)sz < cnt + 1) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}
// Value8 from String : Windows UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value16 from String : Windows UNICODE
ssize_t Dz1StrW_fromU16(wchar_t *dst, size_t sz, u16_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrW_fromS16(wchar_t *dst, size_t sz, s16_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = L'-'; cnt++;
	}

	if ((ssize_t)sz < cnt + 1) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}
// Value16 from String : Windows UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value32 from String : Windows UNICODE
ssize_t Dz1StrW_fromU32(wchar_t *dst, size_t sz, u32_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v);
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrW_fromS32(wchar_t *dst, size_t sz, s32_t v)
{
	wchar_t buf[16] = { 0, }, *cp = &buf[14];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW(v); cnt++;

	if (minux)
	{
		cp--;
		*cp = L'-'; cnt++;
	}

	if ((ssize_t)sz < cnt + 1) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}
// Value32 from String : Windows UNICODE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Value64 from String : Windows UNICODE
ssize_t Dz1StrW_fromU64(wchar_t *dst, size_t sz, u64_t v)
{
	wchar_t buf[64] = { 0, }, *cp = &buf[62];
	ssize_t cnt = 0;
	u32_t r = 0;
	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW((u32_t)(v & 0xFF));
	cnt++;

	if (sz < (size_t)(cnt + 1)) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}

ssize_t Dz1StrW_fromS64(wchar_t *dst, size_t sz, s64_t v)
{
	wchar_t buf[64] = { 0, }, *cp = &buf[62];
	ssize_t cnt = 0;
	u32_t r = 0;

	bool_t minux = FALSE;
	if (v < 0) { minux = TRUE; v = -v; }

	while(v >= 10)
	{
		r = (u32_t)(v % 10);
		v = v / 10;
		*cp = _digit2letterW(r); cnt++;
		cp--;
	}
	*cp = _digit2letterW((u32_t)(v & 0xFF)); cnt++;

	if (minux)
	{
		cp--;
		*cp = L'-'; cnt++;
	}

	if (sz < (size_t)(cnt + 1)) return -1;
	else wcsncpy(dst, cp, cnt+1);

	return cnt;
}
// Value64 from String : Windows UNICODE
///////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// String UL Case
void Dz1StrA_ucase(str_t p)
{
	if (p == NULL) return;
	while(*p != 0)
	{
		(*p) = Dz1LetterA_ucase(*p);
		p++;
	}
}
void Dz1StrA_lcase(str_t p)
{
	if (p == NULL) return;
	while(*p != 0)
	{
		(*p) = Dz1LetterA_lcase(*p);
		p++;
	}
}
#ifndef UNIX_SYSTEM
void Dz1StrW_ucase(wstr_t p)
{
	if (p == NULL) return;
	while(*p != 0)
	{
		(*p) = Dz1LetterW_ucase(*p);
		p++;
	}
}
void Dz1StrW_lcase(wstr_t p)
{
	if (p == NULL) return;
	while(*p != 0)
	{
		(*p) = Dz1LetterW_lcase(*p);
		p++;
	}
}
#endif
// String UL Case
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Char String
int Dz1StrA_cmp(str_t a, str_t b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else return strcmp(a, b);
}

str_t _Dz1StrA_dup(char const * const src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	str_t ret = NULL;
	if (!src) Dz1Error_set(errp, EINVAL);
	else
	{
		int len = (int)strlen(src);
		if ((ret = _Dz1StrA_ndup(src, len, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

str_t _Dz1StrA_ndup(char const * const src, size_t len, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	str_t ret = NULL;
	if (!src) Dz1Error_set(errp, EINVAL);
	else if ((ret = (str_t)_Dz1Malloc(len + 1, errp, __file__, __line__)) != NULL)
	{
		strncpy(ret, src, len);
		ret[len] = 0;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1StrA_del(str_t p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1StrA_dump(str_t p, int tab)
{
	if (!p) Dz1ThreadA_tprintf(tab, "[NULL]\n");
	else Dz1ThreadA_tprintf(tab, "[%s]\n", p);
}

void Dz1StrA_fdump(FILE *fp, str_t p, int tab)
{
	if (!p) Dz1ThreadA_ftprintf(fp, tab, "[NULL]\n");
	else Dz1ThreadA_ftprintf(fp, tab, "[%s]\n", p);
}

static str_t _str_a_realloc(str_t src, size_t src_len, size_t target_len, size_t alter_len, Dz1Error *errp)
{
	str_t ret = NULL;
	size_t append = alter_len > target_len ? alter_len - target_len : 0;
	if ((ret = (str_t)Dz1Calloc(sizeof(char), src_len + append + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		strcpy(ret, src);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

str_t Dz1StrA_replace(str_t _src, str_t target, str_t alter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL, find_p = NULL, src = NULL;
	size_t src_len, target_len;
	if (_src == NULL || _src[0] == 0 ||
		target == NULL || (target_len = strlen(target)) == 0 || 
		alter == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (strstr(alter, target) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((src = Dz1StrA_dup(_src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&src);
		if ((find_p = strstr(src, target)) == NULL)
		{
			ret = src; src = NULL;
			Dz1Error_set(errp, 0);
		}
		else
		{
			str_t temp = NULL;
			size_t alter_len = strlen(alter);
			do 
			{
				if ((temp = _str_a_realloc(src, (src_len = strlen(src)), target_len, alter_len, errp)) == NULL) ERR_OUT(errp);
				else
				{
					char *dp = temp;
					char *sp = src;
					char *ap = alter;
					char *scan_p = NULL;

					pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
					while(sp < find_p) *dp++ = *sp++;
					while(*ap) *dp++ = *ap++;

					scan_p = dp;

					sp += target_len;
					while(*sp) *dp++ = *sp++;
					*dp++ = 0;

					Dz1Error_set(errp, 0);

					Dz1Str_delAndSetNull(&src);
					src = temp; temp = NULL;

					find_p = strstr(scan_p, target);

					pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
				}
			} while(errp->code == 0 && find_p != NULL);
			if (errp->code == 0) { ret = src; src = NULL; }
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&src);
	}
	return ret;
}

Dz1Error Dz1StrA_replaceChr(str_t dst, char src, char rpl)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || src == 0 || rpl == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *cp = dst;
		while(*cp)
		{
			if (*cp == src) *cp = rpl;
			cp++;
		}
	}
	return err;
}
// Char String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Wide Char String
#ifndef UNIX_SYSTEM	// 20250618 gm
int Dz1StrW_cmp(wstr_t a, wstr_t b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else return wcscmp(a, b);
}

wstr_t _Dz1StrW_dup(wchar_t const * const src, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wstr_t ret = NULL;
	if (!src)
		Dz1Error_set(errp, EINVAL);
	else
	{
		int len = (int)wcslen(src);
		if ((ret = _Dz1StrW_ndup(src, len, errp, __file__, __line__)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

wstr_t _Dz1StrW_ndup(wchar_t const * const src, size_t len, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wstr_t ret = NULL;
	if (!src) Dz1Error_set(errp, EINVAL);
	else if ((ret = (wstr_t)_Dz1Calloc(sizeof(wchar_t), len + 1, errp, __file__, __line__)) != NULL)
	{
		wcsncpy(ret, src, len);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

// print Unicode String on Unicode Compiler
void Dz1StrW_dump(wstr_t p, int tab)
{
	if (p == NULL || p[0] == 0) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"\"%s\"\n", p);
// 	size_t src_len = 0;
// 	if (!p || (src_len = wcslen(p)) == 0) Dz1ThreadW_tprintf(tab, L"[NULL]\n");
// 	else 
// 	{
// 		size_t src_byte_size = src_len << 1;
// 		str_t output_str = (str_t)Dz1String_conv(p, src_byte_size, WINDOWS_UNICODE, "EUC-KR", NULL);
// 		if (output_str == NULL) Dz1ThreadW_printf(L"!!! Processing Fail\n");
// 		else
// 		{
// 			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&output_str);
// 			Dz1ThreadW_printf(L"\"%s\"\n", output_str);
// 			pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&output_str);
// 		}
// 	}
}

// print Unicode String on mbcs Compiler
void Dz1StrW_fdump(FILE *fp, wstr_t p, int tab)
{
	if (!p) Dz1ThreadW_ftprintf(fp, tab, L"[NULL]\n");
	else Dz1ThreadW_ftprintf(fp, tab, L"[%;s]\n", p);
}

static wstr_t _str_w_realloc(wstr_t src, size_t src_len, size_t target_len, size_t alter_len, Dz1Error *errp)
{
	wstr_t ret = NULL;
	size_t append = alter_len > target_len ? alter_len - target_len : 0;
	if ((ret = (wstr_t)Dz1Calloc(sizeof(wchar_t), src_len + append + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wcscpy(ret, src);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

wstr_t Dz1StrW_replace(wstr_t _src, wstr_t target, wstr_t alter, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL, find_p = NULL, src = NULL;
	size_t src_len, target_len;
	if (_src == NULL || _src[0] == 0 ||
		target == NULL || (target_len = wcslen(target)) == 0 || 
		alter == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (wcsstr(alter, target) != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((src = Dz1StrW_dup(_src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&src);
		if ((find_p = wcsstr(src, target)) == NULL)
		{
			ret = src; src = NULL;
			Dz1Error_set(errp, 0);
		}
		else
		{
			wstr_t temp = NULL;
			size_t alter_len = wcslen(alter);
			do
			{
				if ((temp = _str_w_realloc(src, (src_len = wcslen(src)), target_len, alter_len, errp)) == NULL) ERR_OUT(errp);
				else
				{
					wchar_t *dp = temp;
					wchar_t *sp = src;
					wchar_t *ap = alter;
					wchar_t *scan_p = NULL;

					pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
					while(sp < find_p) *dp++ = *sp++;
					while(*ap) *dp++ = *ap++;

					scan_p = dp;

					sp += target_len;
					while(*sp) *dp++ = *sp++;
					*dp++ = 0;

					Dz1Error_set(errp, 0);

					Dz1StrW_delAndSetNull(&src);
					src = temp; temp = NULL;

					find_p = wcsstr(scan_p, target);

					pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&temp);
				}
			} while(errp->code == 0 && find_p != NULL);

			if (errp->code == 0) { ret = src; src = NULL; }
		}
		pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&src);
	}
	return ret;
}

Dz1Error Dz1StrW_replaceChr(wstr_t dst, wchar_t src, wchar_t rpl)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || src == 0 || rpl == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t *cp = dst;
		while(*cp)
		{
			if (*cp == src) *cp = rpl;
			cp++;
		}
	}
	return err;
}
// Wide Char String
///////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// Dz1StrA Encode
static ssize_t _Dz1StrA_enc(u8_t *dst, str_t src, size_t len)
{
	ssize_t ret = 0;
	if (dst != NULL && src != NULL && len > 0) memcpy(dst, src, len);
	ret += (ssize_t)len;
	return ret;
}

ssize_t Dz1StrA_enc(u8_t *dst, str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t temp, ret = 0;
	if (dst) { *dst = src ? 1 : 0; dst++; } ret++;

	if (src)
	{ 
		u32_t len = (u32_t)strlen(src);
		if ((temp = Dz1u32_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1); else { if (dst) dst += temp; ret += temp; }

		ret += _Dz1StrA_enc(dst, src, len);
	}

	return ret;
}

ssize_t Dz1StrA16_enc(u8_t *dst, str_t src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst) { *dst = src ? 1 : 0; dst++; } ret++;

	if (src)
	{ 
		u32_t _len = (u32_t)strlen(src);
		u16_t len = 0;

		if (_len & 0xFFFF0000) ERR_SET_OUT_RET(errp, ENOMEM, -1); else len = (u16_t)(_len & 0xFFFF);

		if ((temp = Dz1u16_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1); else { if (dst) dst += temp; ret += temp; }

		ret += _Dz1StrA_enc(dst, src, len);
	}

	return ret;
}

ssize_t Dz1StrA8_enc(u8_t *dst, str_t src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst) { *dst = src ? 1 : 0; dst++; } ret++;

	if (src)
	{ 
		u32_t _len = (u32_t)strlen(src);
		u8_t len = 0;

		if (_len & 0xFFFFFF00) ERR_SET_OUT_RET(errp, ENOMEM, -1); else len = (u8_t)(_len & 0xFF);

		if ((temp = Dz1u8_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1); else { if (dst) dst += temp; ret += temp; }

		ret += _Dz1StrA_enc(dst, src, len);
	}

	return ret;
}
// Dz1StrA Encode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1StrA Decode
static ssize_t _Dz1StrA_dec(str_t *dst, u8_t *src, size_t len, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (*dst) Dz1StrA_del(*dst);
	if (( (*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		memcpy(*dst, src, len);
		ret += (ssize_t)len;
	}
	return ret;
}

ssize_t Dz1StrA_dec(str_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src; src++; ret++;

	if (flag)
	{
		u32_t len, *_len = &len;
		if ((temp = Dz1u32_dec(&_len, src, errp)) <= 0)	ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }

		if ((temp = _Dz1StrA_dec(dst, src, len, errp)) <= 0) ERR_OUT_RET(errp, -1); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrA_del(*dst);
		*dst = NULL;
	}
	return ret;
}

ssize_t Dz1StrA16_dec(str_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src; src++; ret++;

	if (flag)
	{
		u16_t len, *_len = &len;
		if ((temp = Dz1u16_dec(&_len, src, errp)) <= 0) ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }

		if ((temp = _Dz1StrA_dec(dst, src, len, errp)) <= 0) ERR_OUT_RET(errp, -1); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrA_del(*dst);
		*dst = NULL;
	}
	return ret;
}

ssize_t Dz1StrA8_dec(str_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src; src++; ret++;

	if (flag)
	{
		u8_t len, *_len = &len;
		if ((temp = Dz1u8_dec(&_len, src, errp)) <= 0) ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }

		if ((temp = _Dz1StrA_dec(dst, src, len, errp)) <= 0) ERR_OUT_RET(errp, -1); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrA_del(*dst);
		*dst = NULL;
	}
	return ret;
}
// Dz1StrA Decode
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1StrW Encode
static ssize_t _W_enc(u8_t *dst, wstr_t src, size_t src_len, Dz1Error *errp)
{
	ssize_t ret = 0, temp;
	if (dst)
	{
		u8_t *dp = dst;
		wchar_t *sp = src;
		while(src_len)
		{
			if ((temp = Dz1u16_enc(dp, (u16_t *)sp, errp)) <= 0) ERR_OUT_RET(errp, -1);
			else
			{
				ret += temp;
				dp += temp;
				src_len--;
				sp++;
			}
		}
	}
	else
	{
		u32_t byte_len = (u32_t)(src_len << 1);
		ret = byte_len;
	}
	return ret;
}

ssize_t Dz1StrW_enc(u8_t *dst, wstr_t src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	// flag : NULL or not
	if (dst) { *dst = src != NULL ? 1 : 0; dst++; }
	ret++;

	if (src)
	{ 
		u32_t len = (u32_t)wcslen(src);
		if ((temp = Dz1u32_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else { if (dst) dst += temp; ret += temp; }

		if ((temp = _W_enc(dst, src, len, errp)) == 0) ERR_OUT_RET(errp, -1);
		else ret += temp;
	}

	return ret;
}

ssize_t Dz1StrW16_enc(u8_t *dst, wstr_t src, Dz1Error *err)
{
	size_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst) { *dst = (src != NULL) ? 1 : 0; dst++; }
	ret++;

	if (src)
	{ 
		u32_t _len = (u32_t)wcslen(src);
		u16_t len = 0;

		if (_len & 0xFFFF0000) ERR_SET_OUT_RET(errp, ENOMEM, -1); else len = (u16_t)(_len & 0xFFFF);

		if ((temp = Dz1u16_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else { if (dst) dst += temp; ret += temp; }

		if ((temp = _W_enc(dst, src, len, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else ret += temp;
	}

	return ret;
}

ssize_t Dz1StrW8_enc(u8_t *dst, wstr_t src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst) { *dst = (src != NULL) ? 1 : 0; dst++; }
	ret++;

	if (src)
	{ 
		u32_t _len = (u32_t)wcslen(src);
		u8_t len = 0;

		if (_len & 0xFFFFFF00) ERR_SET_OUT_RET(errp, ENOMEM, -1); else len = (u8_t)(_len & 0xFF);

		if ((temp = Dz1u8_enc(dst, &len, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else { if (dst) dst += temp; ret += temp; }

		if ((temp = _W_enc(dst, src, len, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else ret += temp;
	}

	return ret;
}
// Dz1StrW Encode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1StrW Decode
static ssize_t _W_dec(wstr_t *dst, u8_t *src, size_t dst_len, Dz1Error *errp)
{
	ssize_t ret = 0, temp;


	u8_t *sp = src;
	wchar_t *dp = (*dst), _v, *v = &_v;

	while(dst_len)
	{
		if ((temp = Dz1u16_dec((u16_t **)&v, sp, errp)) <= 0) ERR_OUT_RET(errp, -1);
		else
		{
			*dp++ = _v;			// copy value & move ptr
			dst_len--;

			sp += temp;

			ret += temp;
		}
	}
	return ret;
}

static ssize_t _W_DEC(wstr_t *dst, u8_t *src, size_t dst_len, Dz1Error *err)
{
	ssize_t ret = 0, temp;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst_len > 0)
	{
		//u32_t byte_len = dst_len << 1;

		if (*dst) Dz1StrW_del(*dst);
		if ((*dst = (wstr_t)Dz1Calloc(sizeof(wchar_t), dst_len + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)dst);
			if ((temp = _W_dec(dst, src, dst_len, errp)) <= 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				src += temp;
				ret += temp;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)dst);
		}
	}
	else
	{
		if (*dst) Dz1StrW_del(*dst);
		(*dst) = NULL;
	}
	return ret;
}

ssize_t Dz1StrW_dec(wstr_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src++; 
	ret++;

	if (flag)
	{
		u32_t len, *_len = &len;
		if ((temp = Dz1u32_dec(&_len, src, errp)) <= 0) ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }

		if ((temp = _W_DEC(dst, src, len, errp)) < 0) ERR_SET_OUT(errp, EFAULT); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrW_del(*dst);
		*dst = NULL;
	}
	return ret;
}

ssize_t Dz1StrW16_dec(wstr_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src++; 
	ret++;

	if (flag)
	{
		u16_t len, *_len = &len;
		if ((temp = Dz1u16_dec(&_len, src, errp)) <= 0) ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }
		
		if ((temp = _W_DEC(dst, src, len, errp)) < 0) ERR_SET_OUT_RET(errp, EFAULT, -1); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrW_del(*dst);
		*dst = NULL;
	}
	return ret;
}

ssize_t Dz1StrW8_dec(wstr_t *dst, u8_t *src, Dz1Error *err)
{
	ssize_t temp, ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	unsigned char flag;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);

	flag = *src++; 
	ret++;

	if (flag)
	{
		u8_t len, *_len = &len;
		if ((temp = Dz1u8_dec(&_len, src, errp)) <= 0) ERR_OUT_RET(errp, -1); else { src += temp; ret += temp; }
		
		if ((temp = _W_DEC(dst, src, len, errp)) < 0) ERR_SET_OUT_RET(errp, EFAULT, -1); else ret += temp;
	}
	else
	{
		if (*dst) Dz1StrW_del(*dst);
		*dst = NULL;
	}
	return ret;
}
// Dz1StrW Decode
///////////////////////////////////////////////////////////////////////////////
#endif

typedef enum
{
	Dz1StrType_unknown = -1,
	Dz1StrType_decimal,
	Dz1StrType_hex,
	Dz1StrType_binary,
	Dz1StrType_octal
} Dz1StrType;

static str_t Dz1StrATypeChk(Dz1StrType *dst, int *factor, str_t src)
{
	*dst = Dz1StrType_decimal;
	*factor = 1;
	if (strncmp(src, "0x", 2)==0) { *dst = Dz1StrType_hex; src += 2; }
	else if (strncmp(src, "0b", 2)==0) { *dst = Dz1StrType_binary; src += 2; }
	else if (strncmp(src, "0o", 2)==0) { *dst = Dz1StrType_octal; src += 2; }
	else if (*src == '-') { *factor = -1; src++; }

	return src;
}

struct ConvApi
{
	Dz1StrType type;
	bool_t (*conv)(int *v, char cp);
	int (*mul32)(int v);
	u64_t (*mul64)(u64_t v);
};

static bool_t d2v(int *v, char cp)
{
	bool_t ret = TRUE;
	if (cp >= '0' && cp <= '9') { *v = cp - '0'; }
	else ret = FALSE;
	return ret;
}
static int dMul32(int v) { return v * 10; }
static u64_t dMul64(u64_t v) { return v * 10; }

static bool_t h2v(int *v, char cp)
{
	bool_t ret = TRUE;
	if (d2v(v, cp)) return TRUE;
	else if (cp >= 'a' && cp <= 'f') { *v = cp - 'a' + 10; }
	else if (cp >= 'A' && cp <= 'F') { *v = cp - 'A' + 10; }
	else ret = FALSE;
	return ret;
}
static int hMul32(int v) { return (v << 4); }
static u64_t hMul64(u64_t v) { return (v << 4); }


static bool_t b2v(int *v, char cp)
{
	bool_t ret = TRUE;
	if (cp >= '0' && cp <= '1') { *v = cp - '0'; }
	else ret = FALSE;
	return ret;
}
static int bMul32(int v) { return (v << 1); }
static u64_t bMul64(u64_t v) { return (v << 1); }


static bool_t o2v(int *v, char cp)
{
	bool_t ret = TRUE;
	if (cp >= '0' && cp <= '7') { *v = cp - '0'; }
	else ret = FALSE;
	return ret;
}
static int oMul32(int v) { return (v << 3); }
static u64_t oMul64(u64_t v) { return (v << 3); }


static struct ConvApi ConvApi[] =
{
	{ Dz1StrType_decimal, d2v, dMul32, dMul64 },
	{ Dz1StrType_hex, h2v, hMul32, hMul64 },
	{ Dz1StrType_binary, b2v, bMul32, bMul64 },
	{ Dz1StrType_octal, o2v, oMul32, oMul64 },
	{ Dz1StrType_unknown, NULL, NULL, NULL }
};

static u32_t _to32(Dz1StrType type, int factor, str_t cp)
{
	s32_t ret = 0;
	u32_t v;
	while(*cp)
	{
		if (!ConvApi[type].conv((s32_t *)&v, *cp++)) { ret = 0; break; }
		else ret = ConvApi[type].mul32(ret) + v;
	}
	if (factor < 0) ret = -ret;
	return (u32_t)ret;
}

static u64_t _to64(Dz1StrType type, int factor, str_t cp)
{
	s64_t ret = 0;
	u32_t v;
	while(*cp)
	{
		if (!ConvApi[type].conv((s32_t *)&v, *cp++)) { ret = 0; break; }
		else ret = ConvApi[type].mul64(ret) + v;
	}
	if (factor < 0) ret = -ret;
	return (u64_t)ret;
}

u32_t Dz1Ato32(str_t str)
{
	char *cp  = str;
	size_t len = strlen(str);

	Dz1StrType type = Dz1StrType_decimal;
	int factor = 1;

	if (len >= 2) cp = Dz1StrATypeChk(&type, &factor, str);

	return _to32(type, factor, cp);
}

u64_t Dz1Ato64(str_t str)
{
	char *cp  = str;
	size_t len = strlen(str);

	Dz1StrType type = Dz1StrType_decimal;
	int factor = 1;

	if (len >= 2) cp = Dz1StrATypeChk(&type, &factor, str);
	return _to64(type, factor, cp);
}

u32_t Dz1AHexto32(str_t str) { return _to32(Dz1StrType_hex, 1, str); }
u64_t Dz1AHexto64(str_t str) { return _to64(Dz1StrType_hex, 1, str); }

bool_t Dz1StrA_isDigitStr(str_t cp)
{
	while(*cp)
	{
		if (!isdigit((int)(*cp & 0xFF))) return FALSE;
		else cp++;
	}
	return TRUE;
}

bool_t Dz1StrA_isIntegerStr(str_t cp)
{
	if (*cp == '-') cp++;
	
	if (*cp == 0) return FALSE;

	return Dz1StrA_isDigitStr(cp);
}

str_t Dz1StrA_fromS64Digit(s64_t v, char *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	char buf[64][4], *dp = dst;
	int i = 0, r;
	bool_t is_minus = FALSE;
	size_t len;

	if (v < 0) { is_minus = TRUE; v = -v; }	// save minus flag

	while(v > 1000)
	{
		r = (int)(v % 1000);
		v /= 1000;
		_std_snprintfA(buf[i++], 4, "%03d", r);
	}
	if (v) _std_snprintfA(buf[i++], 4, "%d", (int)(v & 0x7FFFFFFF));

	if (is_minus)
	{	// put minus
		if (sz > 1) { *dp++ = '-'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}

	if (i == 0)
	{
		if (sz > 1) { *dp++ = '0'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}
	else
	{
		i--;
		if ((len = strlen(buf[i])) < sz) { strcpy(dp, buf[i]); dp += len; sz -= len; } else { Dz1Error_set(errp, ENOMEM); return NULL; }	// first digits
		for (i = i - 1; i >= 0; i--)
		{
			if (sz > 1) { *dp++ = ','; sz--; } else { Dz1Error_set(errp, ENOMEM); break; }
			if (sz > 3) { strcpy(dp, buf[i]); dp += 3; sz -= 3; } else { Dz1Error_set(errp, ENOMEM); break; }
		}
	}
	*dp = 0;
	return SELECT_BY_ERR(errp, dst, NULL);
}

str_t Dz1StrA_fromU64Digit(s64_t v, char *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	char buf[64][4], *dp = dst;
	int i = 0, r;
	size_t len;

	while(v > 1000)
	{
		r = (int)(v % 1000);
		v /= 1000;
		_std_snprintfA(buf[i++], 4, "%03d", r);
	}
	if (v) _std_snprintfA(buf[i++], 4, "%d", (int)(v & 0x7FFFFFFF));

	if (i == 0)
	{
		if (sz > 1) { *dp++ = '0'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}
	else
	{
		i--;
		if ((len = strlen(buf[i])) < sz) { strcpy(dp, buf[i]); dp += len; sz -= len; } else { Dz1Error_set(errp, ENOMEM); return NULL; }	// first digits
		for (i = i - 1; i >= 0; i--)
		{
			if (sz > 1) { *dp++ = ','; sz--; } else { Dz1Error_set(errp, ENOMEM); break; }
			if (sz > 3) { strcpy(dp, buf[i]); dp += 3; sz -= 3; } else { Dz1Error_set(errp, ENOMEM); break; }
		}
	}
	*dp = 0;
	return SELECT_BY_ERR(errp, dst, NULL);
}
#ifndef UNIX_SYSTEM
wstr_t Dz1StrW_fromS64Digit(s64_t v, wchar_t *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wchar_t buf[64][4], *dp = dst;
	int i = 0, r;
	bool_t is_minus = FALSE;
	size_t len;

	if (v < 0) { is_minus = TRUE; v = -v; }	// save minus flag

	while(v > 1000)
	{
		r = (int)(v % 1000);
		v /= 1000;
		_std_snprintfW(buf[i++], 4, L"%03d", r);
	}
	if (v) _std_snprintfW(buf[i++], 4, L"%d", (int)(v & 0x7FFFFFFF));

	if (is_minus)
	{	// put minus
		if (sz > 1) { *dp++ = L'-'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}

	if (i == 0)
	{
		if (sz > 1) { *dp++ = L'0'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}
	else
	{
		i--;
		if ((len = wcslen(buf[i])) < sz) { wcscpy(dp, buf[i]); dp += len; sz -= len; } else { Dz1Error_set(errp, ENOMEM); return NULL; }	// first digits
		for (i = i - 1; i >= 0; i--)
		{
			if (sz > 1) { *dp++ = L','; sz--; } else { Dz1Error_set(errp, ENOMEM); break; }
			if (sz > 3) { wcscpy(dp, buf[i]); dp += 3; sz -= 3; } else { Dz1Error_set(errp, ENOMEM); break; }
		}
	}
	*dp = 0;
	return SELECT_BY_ERR(errp, dst, NULL);
}

wstr_t Dz1StrW_fromU64Digit(s64_t v, wchar_t *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wchar_t buf[64][4], *dp = dst;
	int i = 0, r;
	size_t len;

	while(v > 1000)
	{
		r = (int)(v % 1000);
		v /= 1000;
		_std_snprintfW(buf[i++], 4, L"%03d", r);
	}
	if (v) _std_snprintfW(buf[i++], 4, L"%d", (int)(v & 0x7FFFFFFF));

	if (i == 0)
	{
		if (sz > 1) { *dp++ = L'0'; sz--; }
		else { Dz1Error_set(errp, ENOMEM); return NULL; }
	}
	else
	{
		i--;
		if ((len = wcslen(buf[i])) < sz) { wcscpy(dp, buf[i]); dp += len; sz -= len; } else { Dz1Error_set(errp, ENOMEM); return NULL; }	// first digits
		for (i = i - 1; i >= 0; i--)
		{
			if (sz > 1) { *dp++ = L','; sz--; } else { Dz1Error_set(errp, ENOMEM); break; }
			if (sz > 3) { wcscpy(dp, buf[i]); dp += 3; sz -= 3; } else { Dz1Error_set(errp, ENOMEM); break; }
		}
	}
	*dp = 0;
	return SELECT_BY_ERR(errp, dst, NULL);
}
#endif

static str_t	ByteUnitA[] =
{
	(str_t)"B",
	(str_t)"KB",
	(str_t)"MB",
	(str_t)"GB",
	(str_t)"TB"
};
static ssize_t unit_max = sizeof(ByteUnitA) / sizeof(str_t);

str_t Dz1StrA_fromU64Bytes(u64_t v, char *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t i = 0, cnt;

		char temp[64], *dp = temp;
		size_t temp_sz = 64;

		u64_t remain = 0;
		for (i = 0; v > 10000 && i < unit_max - 1; i++)
		{
			remain = v % 1024;
			v /= 1024;
		}
		cnt = Dz1StrA_fromU64(dp, temp_sz, v);
		dp += cnt;
		temp_sz -= cnt;

		if (remain)
		{
			*dp++ = '.';
			temp_sz--;
			cnt = snprintf(dp, temp_sz, "%03u", (u32_t)(remain * 1000 / 1024));

			dp += cnt;
			temp_sz -= cnt;

		}

		*dp++ = ' ';
		temp_sz--;

		if (temp_sz < strlen(ByteUnitA[i])) ERR_SET_OUT(errp, E2BIG);
		else strcpy(dp, ByteUnitA[i]);

		if (sz < strlen(temp)) ERR_SET_OUT(errp, E2BIG);
		else 
		{
			strcpy(dst, temp);
			ret = dst;
		}
	}
	return ret;
}

#ifndef UNIX_SYSTEM
struct ConvWApi
{
	Dz1StrType type;
	bool_t (*conv)(int *v, wchar_t cp);
	int (*mul32)(int v);
	u64_t (*mul64)(u64_t v);
};

static bool_t Wd2v(int *v, wchar_t cp)
{
	bool_t ret = TRUE;
	if (cp >= L'0' && cp <= L'9') { *v = cp - L'0'; }
	else ret = FALSE;
	return ret;
}

static bool_t Wh2v(int *v, wchar_t cp)
{
	bool_t ret = TRUE;
	if (Wd2v(v, cp)) return TRUE;
	else if (cp >= L'a' && cp <= L'f') { *v = cp - L'a' + 10; }
	else if (cp >= L'A' && cp <= L'F') { *v = cp - L'A' + 10; }
	else ret = FALSE;
	return ret;
}

static bool_t Wb2v(int *v, wchar_t cp)
{
	bool_t ret = TRUE;
	if (cp >= L'0' && cp <= L'1') { *v = cp - L'0'; }
	else ret = FALSE;
	return ret;
}

static bool_t Wo2v(int *v, wchar_t cp)
{
	bool_t ret = TRUE;
	if (cp >= L'0' && cp <= L'7') { *v = cp - L'0'; }
	else ret = FALSE;
	return ret;
}

static struct ConvWApi ConvWApi[] =
{
	{ Dz1StrType_decimal,	Wd2v, dMul32, dMul64 },
	{ Dz1StrType_hex,		Wh2v, hMul32, hMul64 },
	{ Dz1StrType_binary,	Wb2v, bMul32, bMul64 },
	{ Dz1StrType_octal,		Wo2v, oMul32, oMul64 },
	{ Dz1StrType_unknown, 	NULL, NULL,	  NULL }
};

static wstr_t Dz1StrWTypeChk(Dz1StrType *dst, int *factor, wstr_t src)
{
	*dst = Dz1StrType_decimal;
	*factor = 1;
	if (wcsncmp(src, L"0x", 2)==0) { *dst = Dz1StrType_hex; src += 2; }
	else if (wcsncmp(src, L"0b", 2)==0) { *dst = Dz1StrType_binary; src += 2; }
	else if (wcsncmp(src, L"0o", 2)==0) { *dst = Dz1StrType_octal; src += 2; }
	else if (*src == L'-') { *factor = -1; src++; }

	return src;
}

static u32_t _to32W(Dz1StrType type, int factor, wstr_t cp)
{
	s32_t ret = 0;
	s32_t v;
	while(*cp)
	{
		if (!ConvWApi[type].conv(&v, *cp++)) { ret = 0; break; }
		else ret = ConvWApi[type].mul32(ret) + v;
	}
	if (factor < 0) ret = -ret;
	return (u32_t)ret;
}

static u64_t _to64W(Dz1StrType type, int factor, wstr_t cp)
{
	s64_t ret = 0;
	s32_t v;
	while(*cp)
	{
		if (!ConvWApi[type].conv(&v, *cp++)) { ret = 0; break; }
		else ret = ConvWApi[type].mul64(ret) + v;
	}
	if (factor < 0) ret = -ret;
	return (u64_t)ret;
}

u32_t Dz1Wto32(wstr_t str)
{
	wchar_t *cp  = str;
	size_t len = wcslen(str);

	Dz1StrType type = Dz1StrType_decimal;
	int factor = 1;

	if (len >= 2) cp = Dz1StrWTypeChk(&type, &factor, str);

	return _to32W(type, factor, cp);
}

u64_t Dz1Wto64(wstr_t str)
{
	wchar_t *cp  = str;
	size_t len = wcslen(str);

	Dz1StrType type = Dz1StrType_decimal;
	int factor = 1;

	if (len >= 2) cp = Dz1StrWTypeChk(&type, &factor, str);

	return _to64W(type, factor, cp);
}

u32_t Dz1WHexto32(wstr_t str) { return _to32W(Dz1StrType_hex, 1, str); }
u64_t Dz1WHexto64(wstr_t str) { return _to64W(Dz1StrType_hex, 1, str); }

bool_t Dz1StrW_isDigitStr(wstr_t cp)
{
	while(*cp)
	{
		if (*cp < L'0' || *cp > L'9') return FALSE;
		else cp++;
	}
	return TRUE;
}

bool_t Dz1StrW_isIntegerStr(wstr_t cp)
{
	if (*cp == L'-') cp++;

	if (*cp == 0) return FALSE;

	return Dz1StrW_isDigitStr(cp);
}

static wstr_t	ByteUnitW[] =
{
	(wstr_t)L"B",
	(wstr_t)L"KB",
	(wstr_t)L"MB",
	(wstr_t)L"GB",
	(wstr_t)L"TB"
};

wstr_t Dz1StrW_fromU64Bytes(u64_t v, wchar_t *dst, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;

	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t i = 0, cnt;

		wchar_t temp[64], *dp = temp;
		size_t temp_sz = 64;

		u64_t remain = 0;
		for (i = 0; v > 10000 && i < unit_max - 1; i++)
		{
			remain = v % 1024;
			v /= 1024;
		}
		cnt = Dz1StrW_fromU64(dp, temp_sz, v);
		dp += cnt;
		temp_sz -= cnt;

		if (remain)
		{
			*dp++ = L'.';
			temp_sz--;
			cnt = _std_snprintfW(dp, temp_sz, L"%03u", (u32_t)(remain * 1000 / 1024));

			dp += cnt;
			temp_sz -= cnt;

		}

		*dp++ = L' ';
		temp_sz--;

		if (temp_sz < wcslen(ByteUnitW[i])) ERR_SET_OUT(errp, E2BIG);
		else wcscpy(dp, ByteUnitW[i]);

		if (sz < wcslen(temp)) ERR_SET_OUT(errp, E2BIG);
		else 
		{
			wcscpy(dst, temp);
			ret = dst;
		}
	}
	return ret;
}
#endif//UNIX_SYSTEM


static char *_get_digit_posA(str_t str)
{
	if (str != NULL)
	{
		char *i = str;
		while(*i)
		{
			if (isdigit((int)*i & 0xFF)) return i;
			else i++;
		}
	}
	return NULL;
}

int Dz1StrCmpLogicalA(str_t a, str_t b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a != NULL) return 1;			// ("xxx" : NULL) > 0
	else if (b != NULL) return -1;			// (NULL : "xxx") < 0
	else
	{
		int len_ret = 0;
		size_t a_len, b_len, shorter, longer;
		char *ap = a, *aip = NULL;
		char *bp = b, *bip = NULL;
		while(1)
		{
			aip = _get_digit_posA(ap);
			bip = _get_digit_posA(bp);
			if  (aip == NULL && bip == NULL)
			{
				len_ret = strcmp(ap, bp);
				return len_ret;
			}
			else if (aip == NULL)
			{
				if ((b_len = (size_t)(bip - bp)) == 0)
				{
					if (ap[0] == 0)				len_ret = -1;
					else if (!isalpha(ap[0]))	len_ret = -1;
					else						len_ret = 1;
				}
				else len_ret = strncmp(ap, bp, b_len);
				return len_ret;
			}
			else if (bip == NULL)
			{
				if ((a_len = (size_t)(aip - ap)) == 0)
				{
					if (bp[0] == 0)				len_ret = 1;
					else if (!isalpha(bp[0]))	len_ret = 1;
					else						len_ret = -1;
				}
				else len_ret = strncmp(ap, bp, a_len);
				return len_ret;
			}
			else
			{
				a_len = (size_t)(aip - ap);
				b_len = (size_t)(bip - bp);

				if (0) { }
				else if (a_len < b_len)	{ shorter = a_len; longer = b_len; len_ret = -1; }
				else if (a_len > b_len) { shorter = b_len; longer = a_len; len_ret = 1; }
				else { shorter = longer = a_len; len_ret = 0; }

				if (len_ret != 0)
				{
					int ret = 0;
					if ((ret = strncmp(ap, bp, shorter)) != 0) return ret;
					else return len_ret;
				}
				else if (a_len > 0 && (len_ret = strncmp(ap, bp, a_len)) != 0) return len_ret;
				else
				{
					int ret = 0;
					u32_t na = 0, nb = 0;
					for (ap = aip; *ap != 0 && isdigit((int)*ap & 0xFF); ap++) na = na * 10 + (*ap - '0');
					for (bp = bip; *bp != 0 && isdigit((int)*bp & 0xFF); bp++) nb = nb * 10 + (*bp - '0');
					if ((ret = (int)(na - nb)) != 0) return ret;
				}
			}
		}
		return strcmp(ap, bp);
	}
}

#ifndef UNIX_SYSTEM
#include <Shlwapi.h>
#ifndef __BORLANDC__
#pragma comment(lib, "Shlwapi.lib")
#endif // __BORLANDC__
int Dz1StrCmpLogicalW(wstr_t a, wstr_t b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;			// (NULL : "xxx") < 0
	else if (b == NULL) ret = 1;			// ("xxx" : NULL) > 0
	else if ((ret = StrCmpLogicalW(a, b)) == 0) ret = wcscmp(a, b);
	return ret;
}
#else
static wchar_t *_get_digit_posW(wstr_t str)
{
	if (str != NULL)
	{
		wchar_t *i = str;
		while(*i)
		{
			if (iswdigit((wint_t)*i & 0xFFFF)) return i;
			else i++;
		}
	}
	return NULL;
}

int Dz1StrCmpLogicalW(wstr_t a, wstr_t b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;			// (NULL : "xxx") < 0
	else if (b == NULL) return 1;			// ("xxx" : NULL) > 0
	else
	{	//different
		int len_ret = 0;
		size_t a_len, b_len, shorter, longer;
		wchar_t *ap = a, *aip = NULL;
		wchar_t *bp = b, *bip = NULL;
		while(1)
		{
			aip = _get_digit_posW(ap);
			bip = _get_digit_posW(bp);
			if  (aip == NULL && bip == NULL)
			{
				len_ret = wcscmp(ap, bp);
				return len_ret;
			}
			else if (aip == NULL)
			{
				if ((b_len = (size_t)(bip - bp)) == 0)
				{
					if (ap[0] == 0)				len_ret = -1;
					else if (!iswalpha(ap[0]))	len_ret = -1;
					else						len_ret = 1;
				}
				else len_ret = wcsncmp(ap, bp, b_len);
				return len_ret;
			}
			else if (bip == NULL)
			{
				if ((a_len = (size_t)(aip - ap)) == 0)
				{
					if (bp[0] == 0)				len_ret = 1;
					else if (!iswalpha(bp[0]))	len_ret = 1;
					else						len_ret = -1;
				}
				else len_ret = wcsncmp(ap, bp, a_len);
				return len_ret;
			}
			else
			{
				a_len = (size_t)(aip - ap);
				b_len = (size_t)(bip - bp);

				if (0) { }
				else if (a_len < b_len)	{ shorter = a_len; longer = b_len; len_ret = -1; }
				else if (a_len > b_len) { shorter = b_len; longer = a_len; len_ret = 1; }
				else { shorter = longer = a_len; len_ret = 0; }

				if (len_ret != 0)
				{
					int ret = 0;
					if ((ret = wcsncmp(ap, bp, shorter)) != 0) return ret;
					else return len_ret;
				}
				else if (a_len > 0 && (len_ret = wcsncmp(ap, bp, a_len)) != 0) return len_ret;
				else
				{
					int ret = 0;
					u32_t na = 0, nb = 0;
					for (ap = aip; *ap != 0 && iswdigit((wint_t)*ap & 0xFFFF); ap++) na = na * 10 + (*ap - L'0');
					for (bp = bip; *bp != 0 && iswdigit((wint_t)*bp & 0xFFFF); bp++) nb = nb * 10 + (*bp - L'0');
					if ((ret = (int)(na - nb)) != 0) return ret;
				}
			}
		}
	}
}
#endif

static bool_t _toURL_putEncodedLetter(Dz1ElasticBuf *elb, char c, Dz1Error *errp)
{
	char buf[8] = { 0, };
	_std_snprintfA(buf, sizeof(buf) - 1, "%%%02X", (u8_t)c);
	if (Dz1ElasticBuf_pushStrA(elb, buf, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

str_t Dz1StrU8_toURI(str_t src_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	Dz1ElasticBuf *elb = NULL;
	if (src_u8 == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(src_u8))
	{
		if ((ret = Dz1StrA_dup("", errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((elb = Dz1ElasticBuf_new(256, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *sp = src_u8;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		while(errp->code == 0 && *sp)
		{
			if (*sp > 0x80)
			{
				if (_toURL_putEncodedLetter(elb, *sp, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else switch(*sp)
			{
			case '\r':
			case '\n': Dz1Error_set(errp, EPERM); break;
			case ' ':	case '(':	case ':':	case '[':	case '`':
			case '!':	case ')':	case ';':	case '\\':	case '{':
			case '\"':	case '*':	case '<':	case ']':	case '|':
			case '#':	case '+':	case '=':	case '^':	case '}':
			case '$':	case ',':	case '>':	case '_':	case '~':
			case '%':	case '-':	case '?':
			case '&':	case '.':	case '@':
			case '\'':	case '/': if (_toURL_putEncodedLetter(elb, *sp, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
			default: if (Dz1ElasticBuf_pushChrA(elb, *sp, errp) == FALSE) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
			}
			sp++;
		}

		if (errp->code == 0)
		{
			if ((ret = Dz1ElasticBuf_flattenStrAndPurgeA(elb, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return ret;
}

static u8_t _get_hex_value(char c)
{
	u8_t ret = 0;
}

static char _mk_char_from_letter(char a, char b)
{
	char ret = 0;
	int vh = 0, vl = 0;
	if (h2v(&vh, a) == FALSE) { }
	else if (h2v(&vl, b) == FALSE) { }
	else ret = (u8_t)((vh << 4 | vl) & 0xFF);
	return (char)ret;
}

str_t Dz1StrU8_fromURI(str_t src_u8, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	size_t len = 0;
	str_t ret = NULL;

	if (src_u8 == NULL || (len = strlen(src_u8)) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		str_t dp = src_u8, sp = src_u8;
		while(errp->code == 0 && *sp != 0 && len > 0)
		{
			switch(*sp)
			{
			case '%':
				if (len < 3) Dz1Error_set(errp, EPIPE);
				else
				{
					sp++; len--; // pass '%'
					*dp++ = _mk_char_from_letter(sp[0], sp[1]);
					sp += 2; len -= 2;
				}
				break;
			default: *dp++ = *sp++; len--; break;
			}
		}
		if (errp->code == 0) { *dp = 0; ret = src_u8; }
	}
	return ret;
}

str_t Dz1StrA_toURI(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	str_t temp = NULL, ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((len = strlen(src)) == 0)
	{
		if ((ret = Dz1StrA_dup("", errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((temp = (str_t)Dz1String_conv(src, len, DZ1_SYSTEM_MBCS_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		if ((ret = Dz1StrU8_toURI(temp, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
str_t Dz1StrW_toURI(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len = 0;
	str_t temp = NULL, ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((len = wcslen(src)) == 0)
	{
		if ((ret = Dz1StrA_dup("", errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((temp = (str_t)Dz1String_conv(src, len * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, DZ1_SYSTEM_UTF8_CHARSET, NULL)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		if ((ret = Dz1StrU8_toURI(temp, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}
#endif
