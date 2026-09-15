#include <dz1_int.h>
#include <dz1_thread_stdio.h>

static void *dz1Int_new(void *v, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	void *ret = Dz1Malloc(size, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		if (v) memcpy(ret, v, size);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Int type new
u8_t  *Dz1u8_new (u8_t val, Dz1Error *err) { return (u8_t *)dz1Int_new((void *)&val, sizeof(u8_t), err); }
u16_t *Dz1u16_new(u16_t val, Dz1Error *err) { return (u16_t *)dz1Int_new((void *)&val, sizeof(u16_t), err); }
u32_t *Dz1u32_new(u32_t val, Dz1Error *err) { return (u32_t *)dz1Int_new((void *)&val, sizeof(u32_t), err); }
u64_t *Dz1u64_new(u64_t val, Dz1Error *err) { return (u64_t *)dz1Int_new((void *)&val, sizeof(u64_t), err); }
long  *Dz1Long_new(long val, Dz1Error *err) { return (long *)dz1Int_new((void *)&val, sizeof(long), err); }
size_t *size_t_new(size_t val, Dz1Error *err) { return (size_t *)dz1Int_new((void *)&val, sizeof(size_t), err); }
ssize_t *ssize_t_new(ssize_t val, Dz1Error *err) { return (ssize_t *)dz1Int_new((void *)&val, sizeof(ssize_t), err); }
// Int type new
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Int type clone
u8_t  *Dz1u8_clone (u8_t *p, Dz1Error *err) { return (u8_t *)dz1Int_new((void *)p, sizeof(u8_t), err); }
u16_t *Dz1u16_clone(u16_t *p, Dz1Error *err) { return (u16_t *)dz1Int_new((void *)p, sizeof(u16_t), err); }
u32_t *Dz1u32_clone(u32_t *p, Dz1Error *err) { return (u32_t *)dz1Int_new((void *)p, sizeof(u32_t), err); }
u64_t *Dz1u64_clone(u64_t *p, Dz1Error *err) { return (u64_t *)dz1Int_new((void *)p, sizeof(u64_t), err); }
long  *Dz1Long_clone(long *src, Dz1Error *err) { return (long *)dz1Int_new((void *)src, sizeof(long), err); }
size_t *size_t_clone(size_t *src, Dz1Error *err) { return (size_t *)dz1Int_new((void *)src, sizeof(size_t), err); }
ssize_t *ssize_t_clone(ssize_t *src, Dz1Error *err) { return (ssize_t *)dz1Int_new((void *)src, sizeof(ssize_t), err); }
// Int type clone
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Int type dump
static char _LetterA(int v)
{
	char ret = 0;
	if (isprint(v)) ret = (char)(v & 0xFF);
	else ret = '.';
	return ret;
}

void Dz1u8A_dump (u8_t *p, int tab)		{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("0x%02X(%u)(%c)\n", *p, *p, _LetterA((int)*p & 0xFF)); }
void Dz1u16A_dump(u16_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%04X(%u)\n", *p, *p); }
void Dz1u32A_dump(u32_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%08X(%u)\n", *p, *p); }
void Dz1u64A_dump(u64_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%016llX(%llu)\n", *p, *p); }

void Dz1s8A_dump (s8_t *p, int tab)		{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("0x%02X(%d)(%c)\n", *p, *p, _LetterA((int)*p & 0xFF)); }
void Dz1s16A_dump(s16_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%04X(%d)\n", *p, *p); }
void Dz1s32A_dump(s32_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%08X(%d)\n", *p, *p); }
void Dz1s64A_dump(s64_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%016llX(%lld)\n", *p, *p); }

void Dz1LongA_dump(long *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%d\n", *p); }
void Dz1BoolA_dump(bool_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("%s\n", *p ? "True" : "False"); }

void size_tA_dump(size_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("0x%08X(%u)\n", *p, *p); }
void ssize_tA_dump(ssize_t *p, int tab)	{ if (!p) Dz1ThreadA_printf("NULL\n"); else Dz1ThreadA_printf("0x%08X(%d)\n", *p, *p); }
#ifndef UNIX_SYSTEM
static wchar_t _LetterW(int v)
{
	wchar_t ret = 0;
	if (iswprint(v)) ret = (wchar_t)(v & 0xFFFF);
	else ret = L'.';
	return ret;
}

void Dz1u8W_dump (u8_t *p, int tab)		{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"0x%02X(%u)(%c)\n", *p, *p, _LetterW((int)*p & 0xFFFF)); }
void Dz1u16W_dump(u16_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%04X(%u)\n", *p, *p); }
void Dz1u32W_dump(u32_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%08X(%u)\n", *p, *p); }
void Dz1u64W_dump(u64_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%016llX(%llu)\n", *p, *p); }
void Dz1s8W_dump (s8_t *p, int tab)		{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"0x%02X(%d)(%c)\n", *p, *p, _LetterW((int)*p & 0xFFFF)); }
void Dz1s16W_dump(s16_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%04X(%d)\n", *p, *p); }
void Dz1s32W_dump(s32_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%08X(%d)\n", *p, *p); }
void Dz1s64W_dump(s64_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%016llX(%lld)\n", *p, *p); }
void Dz1LongW_dump(long *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%d\n", *p); }
void Dz1BoolW_dump(bool_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"%s\n", *p ? "True" : "False"); }
void size_tW_dump(size_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"0x%08X(%u)\n", *p, *p); }
void ssize_tW_dump(ssize_t *p, int tab)	{ if (!p) Dz1ThreadW_printf(L"NULL\n"); else Dz1ThreadW_printf(L"0x%08X(%d)\n", *p, *p); }
#endif
// Int type dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Int type file dump
void  Dz1u8A_fdump(FILE *fp, u8_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "0x%02X(%u)(%c)\n", *p, *p, _LetterA((int)*p & 0xFF)); }
void Dz1u16A_fdump(FILE *fp, u16_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%04X(%u)\n", *p, *p); }
void Dz1u32A_fdump(FILE *fp, u32_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%08X(%u)\n", *p, *p); }
void Dz1u64A_fdump(FILE *fp, u64_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%016llX(%llu)\n", *p, *p); }
void  Dz1s8A_fdump(FILE *fp, s8_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "0x%02X(%d)(%c)\n", *p, *p, _LetterA((int)*p & 0xFF)); }
void Dz1s16A_fdump(FILE *fp, s16_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%04X(%d)\n", *p, *p); }
void Dz1s32A_fdump(FILE *fp, s32_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%08X(%d)\n", *p, *p); }
void Dz1s64A_fdump(FILE *fp, s64_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%016llX(%lld)\n", *p, *p); }
void Dz1LongA_fdump(FILE *fp, long *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%d\n", *p); }
void Dz1BoolA_fdump(FILE *fp, bool_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "%s\n", *p ? "True" : "False"); }
void  size_tA_fdump(FILE *fp, size_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "0x%08X(%u)\n", *p, *p); }
void ssize_tA_fdump(FILE *fp, ssize_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "NULL\n"); else Dz1ThreadA_fprintf(fp, "0x%08X(%d)\n", *p, *p); }
#ifndef UNIX_SYSTEM
void  Dz1u8W_fdump(FILE *fp, u8_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"0x%02X(%u)(%c)\n", *p, *p, _LetterW((int)*p & 0xFFFF)); }
void Dz1u16W_fdump(FILE *fp, u16_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%04X(%u)\n", *p, *p); }
void Dz1u32W_fdump(FILE *fp, u32_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%08X(%u)\n", *p, *p); }
void Dz1u64W_fdump(FILE *fp, u64_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%016llX(%llu)\n", *p, *p); }
void  Dz1s8W_fdump(FILE *fp, s8_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"0x%02X(%d)(%c)\n", *p, *p, _LetterW((int)*p & 0xFFFF)); }
void Dz1s16W_fdump(FILE *fp, s16_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%04X(%d)\n", *p, *p); }
void Dz1s32W_fdump(FILE *fp, s32_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%08X(%d)\n", *p, *p); }
void Dz1s64W_fdump(FILE *fp, s64_t *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%016llX(%lld)\n", *p, *p); }
void Dz1LongW_fdump(FILE *fp, long *p, int tab)		{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%d\n", *p); }
void Dz1BoolW_fdump(FILE *fp, bool_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"%s\n", *p ? "True" : "False"); }
void  size_tW_fdump(FILE *fp, size_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"0x%08X(%u)\n", *p, *p); }
void ssize_tW_fdump(FILE *fp, ssize_t *p, int tab)	{ if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n"); else Dz1ThreadW_fprintf(fp, L"0x%08X(%d)\n", *p, *p); }
#endif
// Int type file dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// int Type compare
int Dz1u8_cmp(u8_t *a, u8_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1u16_cmp(u16_t *a, u16_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1u32_cmp(u32_t *a, u32_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1u64_cmp(u64_t *a, u64_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}


int Dz1s8_cmp(s8_t *a, s8_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1s16_cmp(s16_t *a, s16_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1s32_cmp(s32_t *a, s32_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int Dz1s64_cmp(s64_t *a, s64_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int size_t_cmp(size_t *a, size_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

int ssize_t_cmp(ssize_t *a, ssize_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}
// int type compare
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// int type encode
static int Dz1Int_enc(unsigned char *dst, void *ptr, u32_t size, Dz1Error *err)
{
	int ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (!ptr) ERR_SET_OUT_RET(errp, EINVAL, -1);

	switch(size)
	{
		case 1:
			if (dst)
			{
				u8_t v = *(u8_t *)ptr;
				*dst++ = v;
			} ret++;
			break;
		case 2:
			if (dst)
			{
				u16_t v = *(u16_t *)ptr;
				*dst++ = (u8_t)((v & 0xFF00U) >> 8);
				*dst++ = (u8_t)(v & 0xFFU);
			} ret += 2;
			break;
		case 4:
			if (dst)
			{
				u32_t v = *(u32_t *)ptr;
				*dst++ = (u8_t)((v & 0xFF000000U) >> 24);
				*dst++ = (u8_t)((v & 0xFF0000U) >> 16);
				*dst++ = (u8_t)((v & 0xFF00U) >> 8);
				*dst++ = (u8_t)(v & 0xFF);
			}
			ret += 4;
			break;
		case 8:
			if (dst)
			{
				u64_t v = *(u64_t *)ptr;
#ifdef UNIX_SYSTEM
				*dst++ = (u8_t)((v & 0xFF00000000000000LLU) >> 54);
				*dst++ = (u8_t)((v & 0xFF000000000000LLU) >> 48);
				*dst++ = (u8_t)((v & 0xFF0000000000LLU) >> 40);
				*dst++ = (u8_t)((v & 0xFF00000000LLU) >> 32);
				*dst++ = (u8_t)((v & 0xFF000000LLU) >> 24);
				*dst++ = (u8_t)((v & 0xFF0000LLU) >> 16);
				*dst++ = (u8_t)((v & 0xFF00) >> 8);
				*dst++ = (u8_t)(v & 0xFF);
#else
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF00000000000000)) >> 54);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF000000000000)) >> 48);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF0000000000)) >> 40);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF00000000)) >> 32);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF000000)) >> 24);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF0000)) >> 16);
				*dst++ = (u8_t)((v & DZ1UINT64(0xFF00)) >> 8);
				*dst++ = (u8_t)( v & DZ1UINT64(0xFF));
#endif
			}
			ret += 8;
			break;
		default:
			ERR_SET_OUT_RET(errp, EINVAL, -1);
			break;
	}

	return ret;
}

ssize_t Dz1u8_enc  (u8_t *dst, u8_t   *src, Dz1Error *err) { return Dz1Int_enc(dst, (void *)src, 1, err); }
ssize_t Dz1u16_enc (u8_t *dst, u16_t  *src, Dz1Error *err) { return Dz1Int_enc(dst, (void *)src, 2, err); }
ssize_t Dz1u32_enc (u8_t *dst, u32_t  *src, Dz1Error *err) { return Dz1Int_enc(dst, (void *)src, 4, err); }
ssize_t Dz1u64_enc (u8_t *dst, u64_t  *src, Dz1Error *err) { return Dz1Int_enc(dst, (void *)src, 8, err); }
ssize_t Dz1Bool_enc(u8_t *dst, bool_t *src, Dz1Error *err) { return Dz1Int_enc(dst, (void *)src, sizeof(bool_t), err); }
// int type encode
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// int type decode
static int Dz1Int_dec(void *ptr, unsigned char *src, u32_t size)
{
	int ret = 0;
	u8_t *v1;
	u16_t *v2;
	u32_t *v4;
	u64_t *v8, _v8;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!ptr) ERR_SET_OUT_RET(&err, EINVAL, -1);

	switch(size)
	{
		case 1:
			v1 = (u8_t *)ptr;
			*v1 = *src++;
			ret++;
			break;
		case 2:
			v2 = (u16_t *)ptr;
			*v2 = *src++; *v2 <<= 8;
			*v2 |= *src++;
			ret += 2;
			break;
		case 4:
			v4 = (u32_t *)ptr;
			*v4 = *src++; *v4 <<= 8;
			*v4 |= *src++; *v4 <<= 8;
			*v4 |= *src++; *v4 <<= 8;
			*v4 |= *src++;
			ret += 4;
			break;
		case 8:
			v8 = (u64_t *)ptr;
			*v8 = *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++; _v8 = (*v8); *v8 = (_v8 << 8);
			*v8 |= *src++;
			ret += 8;
			break;
		default:
			ERR_SET_OUT_RET(&err, EINVAL, -1);
			break;
	}

	return ret;
}

static ssize_t _Dz1V_dec(void **dst, size_t len, u8_t *src, Dz1Error *errp)
{
	ssize_t ret = 0, temp;
	if (*dst == NULL)
	{
		if ((*dst = (void *)Dz1Calloc(sizeof(u8_t), len, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)dst);
			if ((temp = Dz1Int_dec(*dst, src, (u32_t)len)) <= 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
			else ret += temp;
			pthread_cleanup_pop(errp->code); // (Dz1u8_delAndSetNull, (void *)dst);
		}
	}
	else
	{
		if ((temp = Dz1Int_dec(*dst, src, 1)) == 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
		else ret += temp;
	}
	return ret;
}

ssize_t Dz1u8_dec(u8_t **dst, u8_t *src, Dz1Error *err) { return _Dz1V_dec((void **)dst, 1, src, err); }
ssize_t Dz1u16_dec(u16_t **dst, u8_t *src, Dz1Error *err) { return _Dz1V_dec((void **)dst, 2, src, err); }
ssize_t Dz1u32_dec(u32_t **dst, u8_t *src, Dz1Error *err) { return _Dz1V_dec((void **)dst, 4, src, err); }
ssize_t Dz1u64_dec(u64_t **dst, u8_t *src, Dz1Error *err) { return _Dz1V_dec((void **)dst, 8, src, err); }
ssize_t Dz1Bool_dec(bool_t **dst, u8_t *src, Dz1Error *err) { return _Dz1V_dec((void **)dst, sizeof(bool_t), src, err); }
// int type decode
///////////////////////////////////////////////////////////////////////////////

u64_t Dz1u64_pow(u64_t v, u64_t p)
{
	u64_t ret = 1;
	while(p--) ret *= v;
	return ret;
}

u32_t Dz1u32_pow(u32_t v, u32_t p)
{
	u32_t ret = 1;
	while(p--) ret *= v;
	return ret;
}

