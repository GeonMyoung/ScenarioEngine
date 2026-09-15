#include <dz1.h>
#include <dz1_str.h>
#include <dz1_codec.h>
#ifdef WIN32
#include <winnls.h>
#endif

#include <dz1_malloc.h>

#include <dz1_thread_stdio.h>
#include <dz1_asn1.h>

#ifdef USE_CODECONV
#include <codeconv.h>
#endif

#ifdef USE_CODECONV
#else
static struct CodeSetMap
{
	u32_t	codePage;
	str_t	codeSetName;
} CodeSetMap[] =
{
	{ 51949, "EUC-KR" },
	{ 51949, "EUCKR" },
	{ 65001, "UTF-8" },
	{ 65001, "UTF8" },
	{ 0, NULL }
};

static u32_t getCodePage(str_t codeSetName)
{
	struct CodeSetMap *i;
	for (i = CodeSetMap; i->codeSetName != NULL; i++)
		if (strcmp(codeSetName, i->codeSetName) == 0) break;
	return i->codePage;
}
#endif

#ifndef UNIX_SYSTEM // modified by gm 20230601 - defined but not used function, need to check
#ifdef USE_CODECONV
static void codeconv_openCancel(void *ptr)
{
	codeconv_t h = (codeconv_t)ptr;
	codeconv_close(h);
}
#endif // USE_CODECONV
#endif // UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// Unicode String
static Dz1Asn1OctetStr *Dz1Asn1UnicodeStr_newFromBuf(const char *dst_charset, u8_t dst_unit_max, u8_t *src, size_t src_byte_size, const char *src_charset, u8_t src_unit_min, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OctetStr *ret = NULL;
	u8_t *temp = NULL;
	size_t dst_byte_size = ((src_byte_size / src_unit_min) + ((src_byte_size % src_unit_min) ? 1 : 0)) * dst_unit_max + dst_unit_max;
	if (src == NULL || src_byte_size == 0 || Dz1Str_isVoid(src_charset)) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1Malloc(dst_byte_size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		if ((sz = Dz1CodeConv(temp, dst_byte_size, dst_charset, src, src_byte_size, src_charset)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = Dz1Asn1OctetStr_new(temp, (u32_t)sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}

static str_t Dz1Asn1UnicodeStrA_printable(Dz1Asn1OctetStr *src, const char *src_charset, char *buf, size_t buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	ssize_t sz = 0;
	memset(buf, 0, buf_sz);
	if ((sz = Dz1CodeConv((u8_t *)buf, buf_sz, DZ1_SYSTEM_MBCS_CHARSET, src->data, src->size, src_charset)) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		buf[buf_sz - 1] = 0;
		ret = buf;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static str_t Dz1Asn1UnicodeStrA_toStr(Dz1Asn1OctetStr *src, const char *src_charset, u32_t convert_factor, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	u8_t *temp = NULL;
	size_t dst_byte_size = 0;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->data == NULL || src->size == 0)
	{	// zero length string
		if ((ret = (str_t)Dz1Calloc(sizeof(char), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((temp = (u8_t *)Dz1Malloc((dst_byte_size = ((src->size * sizeof(char)) << convert_factor)) + sizeof(char), errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		memset(temp, 0, dst_byte_size + sizeof(char));
		if ((sz = Dz1CodeConv((u8_t *)temp, dst_byte_size, DZ1_SYSTEM_MBCS_CHARSET, src->data, src->size, src_charset)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = Dz1StrA_dup((str_t)temp, errp)) == NULL) ERR_OUT(errp); // modified by gm 20230602 - type casting u8_t * -> str_t
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
static wstr_t Dz1Asn1UnicodeStrW_printable(Dz1Asn1OctetStr *src, const char *src_charset, wchar_t *buf, size_t buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	ssize_t sz = 0;
	size_t byte_sz = buf_sz * sizeof(wchar_t);
	memset(buf, 0, byte_sz);
	if ((sz = Dz1CodeConv((u8_t *)buf, byte_sz, DZ1_SYSTEM_MBCS_CHARSET, src->data, src->size, src_charset)) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		buf[buf_sz - 1] = 0;
		ret = buf;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static wstr_t Dz1Asn1UnicodeStrW_toStr(Dz1Asn1OctetStr *src, const char *src_charset, u32_t convert_factor, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	u8_t *temp = NULL;
	size_t dst_byte_size = 0;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src->data == NULL || src->size == 0)
	{	// zero length string
		if ((ret = (wstr_t)Dz1Calloc(sizeof(wchar_t), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((temp = (u8_t *)Dz1Malloc((dst_byte_size = ((src->size * sizeof(wchar_t)) << convert_factor)) + sizeof(wchar_t), errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);

		memset(temp, 0, dst_byte_size + sizeof(wchar_t));
		if ((sz = Dz1CodeConv((u8_t *)temp, dst_byte_size, DZ1_SYSTEM_WIDE_CHARSET, src->data, src->size, src_charset)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = Dz1StrW_dup((wchar_t *)temp, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
	return ret;
}
#endif
// Unicode String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 UTF8String (12)
void Dz1Asn1UTF8StrA_dump(Dz1Asn1UTF8Str *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if ((temp = Dz1Asn1UTF8StrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_printf("\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1UTF8StrA_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else if ((temp = Dz1Asn1UTF8StrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_fprintf(fp, "\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1UTF8StrW_dump(Dz1Asn1UTF8Str *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if ((temp = Dz1Asn1UTF8StrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_printf(L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1UTF8StrW_fdump(FILE *fp, Dz1Asn1UTF8Str *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else if ((temp = Dz1Asn1UTF8StrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_fprintf(fp, L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#endif

int Dz1Asn1UTF8Str_cmp(Dz1Asn1UTF8Str *a, Dz1Asn1UTF8Str *b)
{
//	return Dz1Asn1OctetStr_cmp(a, b);
	if		(a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		u8_t *p;
		size_t aSz, bSz;

		p = &a->data[a->size - 1];
		while(p > a->data && *p == '\0') p--;
		aSz = (size_t)(p - a->data) + 1;

		p = &b->data[b->size - 1];
		while(p > b->data && *p == '\0') p--;
		bSz = (size_t)(p - b->data) + 1;

		if (aSz < bSz) return 1;
		else if (aSz > bSz) return -1;
		else return memcmp(a->data, b->data, aSz);
	}
}

size_t Dz1Asn1UTF8Str_strlen(Dz1Asn1UTF8Str *p)
{
	size_t ret = 0;
	if (p != NULL)
	{
		u8_t *cp = p->data;
		u32_t size = p->size;
		while(size > 0 && *cp != 0)
		{
			if ((*cp & 0xB0) == 0xB0)
			{	// duo octet letter
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				ret++;
			}
			else if ((*cp & 0xE0) == 0xE0)
			{	// triple octet letter
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				ret++;
			}
			else if ((*cp & 0xF0) == 0xF0)
			{	// quadruple octet letter
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				if (size) { cp++; size--; }
				ret++;
			}
			else // if ((*cp & 0x80) == 0x00)
			{	// single octet letter
				ret++;
				size--;
				cp++;
			}
		}
	}
	return ret;
}

Dz1Asn1UniversalStr *Dz1Asn1UTF8Str_toUCS4(Dz1Asn1UTF8Str *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Asn1OctetStr *ret = Dz1Asn1UnicodeStr_newFromBuf("UCS-4BE", 4, src->data, src->size, "UTF-8", 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

///////////////////////////////////////
// New From
Dz1Asn1UTF8Str *Dz1Asn1UTF8Str_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UTF8Str *ret = Dz1Asn1UnicodeStr_newFromBuf("UTF-8", 3, src, src_byte_size, src_charset, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
Dz1Asn1UTF8Str *Dz1Asn1UTF8StrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1UTF8Str *ret = NULL;
	if ((ret = Dz1Asn1UTF8Str_newFromBuf((u8_t *)src, strlen(src), DZ1_SYSTEM_MBCS_CHARSET, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
Dz1Asn1UTF8Str *Dz1Asn1UTF8StrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1UTF8Str *ret = NULL;
	if ((ret = Dz1Asn1UTF8Str_newFromBuf((u8_t *)src, wcslen(src) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// New From
///////////////////////////////////////

///////////////////////////////////////
// Convert to
ssize_t Dz1Asn1UTF8Str_conv(Dz1Asn1UTF8Str *src, str_t dst_charset, void *dst, size_t dst_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL || dst_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (src->data == NULL || src->size == 0) { memset(dst, 0, dst_size); Dz1Error_set(errp, 0); }
	else if ((ret = Dz1CodeConv((u8_t *)dst, dst_size, dst_charset, src->data, src->size, "UTF-8")) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? ret : -1;
}

str_t Dz1Asn1UTF8StrA_printable(Dz1Asn1UTF8Str *src, char *buf, size_t buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	if ((ret = Dz1Asn1UnicodeStrA_printable(src, "UTF-8", buf, buf_sz, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

str_t Dz1Asn1UTF8StrA_toStr(Dz1Asn1UTF8Str *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = Dz1Asn1UnicodeStrA_toStr(src, "UTF-8", 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1Asn1UTF8StrW_printable(Dz1Asn1UTF8Str *src, wchar_t *buf, size_t buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	if ((ret = Dz1Asn1UnicodeStrW_printable(src, "UTF-8", buf, buf_sz, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

wstr_t Dz1Asn1UTF8StrW_toStr(Dz1Asn1UTF8Str *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = Dz1Asn1UnicodeStrW_toStr(src, "UTF-8", 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// Convert to
///////////////////////////////////////

///////////////////////////////////////
// CODEC
ssize_t Dz1Asn1UTF8Str_enc(u8_t *dst, size_t size, Dz1Asn1UTF8Str *src, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t status = Dz1Asn1OctetStr_enc(dst, size, src, param, errp);
	if (status < 0) DZ1_CODEC_ERR_RET(errp);
	return status;
}

ssize_t Dz1Asn1UTF8Str_dec(Dz1Asn1UTF8Str *dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t status = Dz1Asn1OctetStr_dec(dst, src, size, param, errp);
	if (status < 0) DZ1_CODEC_ERR_RET(errp);
	return status;
}
// CODEC
///////////////////////////////////////

///////////////////////////////////////
// Stream
ssize_t Dz1Asn1UTF8Str_write(Dz1Stream *dst, Dz1Asn1UTF8Str *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->size & 0xFFFF), ed, errp, ret);
		DZ1_STREAM_WRITE(dst, src->data, src->size, errp, ret);
	}
	return ret;
}

ssize_t Dz1Asn1UTF8Str_read(Dz1Asn1UTF8Str *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u16_t size = 0;
		DZ1_STREAM_READ2(&size, src, ed, errp, ret);
		
		if (dst->data != NULL) Dz1Free(dst->data);
		if ((dst->data = (u8_t *)Dz1Calloc(sizeof(u8_t), (dst->size = (u32_t)size) + 1, errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_STREAM_READ(dst->data, dst->size, src, errp, ret);
	}
	return ret;
}
// Stream
///////////////////////////////////////
// ASN.1 UTF8String (12)
///////////////////////////////////////////////////////////////////////////////

// ASN.1 RELATIVE OBJECT IDENTIFIER (13)
// ASN.1 TIME (14)
// ASN.1 Reserved (15)
// ASN.1 SEQUENCE, SEQUENCE OF (16)
// ASN.1 SET, SET OF (17)
// ASN.1 Numeric String (18)
// ASN.1 Printable String (19)
// ASN.1 TeleTex String, T64 String (20)
// ASN.1 VideoTex String (21)
// ASN.1 IA5 String (22)
// ASN.1 UTC Time (23)
// ASN.1 Generalized Time (24)
// ASN.1 Graphic String (25)
// ASN.1 Visible String, ISO646 String (26)
// ASN.1 General String (27)

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Universal String (28)
int Dz1Asn1UniversalStr_cmp(Dz1Asn1UniversalStr *a, Dz1Asn1UniversalStr *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		size_t a_len = Dz1Asn1UniversalStr_strlen(a);
		size_t b_len = Dz1Asn1UniversalStr_strlen(b);
		if (a_len < b_len) return -1;
		else if (a_len < b_len) return 1;
		else
		{
			u32_t i, sz = a->size / sizeof(u32_t);
			u32_t *a_data = (u32_t *)a->data, a_value;
			u32_t *b_data = (u32_t *)b->data, b_value;
			for (i = 0; i < sz; i++)
			{
				a_value = Dz1Endian4_big2host(a_data[i]);
				b_value = Dz1Endian4_big2host(b_data[i]);
				if (a_value < b_value) return -1;
				else if (a_value > b_value) return 1;
			}
			return 0;
		}
	}
}

size_t Dz1Asn1UniversalStr_strlen(Dz1Asn1UniversalStr *p)
{
	size_t ret = 0;
	if (p != NULL)
	{
		u32_t *cp = (u32_t *)p->data;
		u32_t size = p->size;
		while(size)
		{
			if (*cp != 0)
			{
				size -= (size > 4) ? 4 : size; cp++;
				ret++;
			}
		}
	}
	return ret;
}
/*
u32_t *Dz1Asn1UniversalStr_toUCS4(Dz1Asn1UniversalStr *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((p->size & 0x3)!= 0) ERR_SET_OUT(errp, EFAULT);
	else if (p->data == NULL || p->size == 0)
	{	// zero length
		if ((ret = (u32_t *)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t cnt = (p->size >> 2);
		if ((ret = Dz1Calloc(sizeof(u32_t), cnt + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			size_t i;
			u32_t *src = (u32_t *)p->data;
			for (i = 0; i < cnt; i++)
				ret[i] = Dz1Endian4_big2host(src[i]);
		}
	}
	return ret;
}
*/
void Dz1Asn1UniversalStrA_dump(Dz1Asn1UniversalStr *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if ((temp = Dz1Asn1UniversalStrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_printf("\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1UniversalStrA_fdump(FILE *fp, Dz1Asn1UniversalStr *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else if ((temp = Dz1Asn1UniversalStrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_fprintf(fp, "\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1UniversalStrW_dump(Dz1Asn1UniversalStr *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if ((temp = Dz1Asn1UniversalStrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_printf(L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1UniversalStrW_fdump(FILE *fp, Dz1Asn1UniversalStr *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else if ((temp = Dz1Asn1UniversalStrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_fprintf(fp, L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#endif

// #if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
// #define Dz1Asn1UniversalStr_CHARSET			"UCS-4LE"
// #elif DZ1_ENDIAN == DZ1_ENDIAN_BIG
// #define Dz1Asn1UniversalStr_CHARSET			"UCS-4BE"
// #else
// #error Endian not defined
// #endif
#define Dz1Asn1UniversalStr_CHARSET			"UCS-4BE"

///////////////////////////////////////
// New From
Dz1Asn1UniversalStr *Dz1Asn1UniversalStr_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr *ret = Dz1Asn1UnicodeStr_newFromBuf(Dz1Asn1UniversalStr_CHARSET, 4, src, src_byte_size, src_charset, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1Asn1UniversalStr	*Dz1Asn1UniversalStrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr	*ret = Dz1Asn1UniversalStr_newFromBuf((u8_t *)src, strlen(src), DZ1_SYSTEM_MBCS_CHARSET, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
Dz1Asn1UniversalStr *Dz1Asn1UniversalStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr	*ret = Dz1Asn1UniversalStr_newFromBuf((u8_t *)src, wcslen(src) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// New From
///////////////////////////////////////

///////////////////////////////////////
// Convert to
ssize_t Dz1Asn1UniversalStr_conv(Dz1Asn1UniversalStr *src, str_t dst_charset, void *dst, size_t dst_byte_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL || dst_byte_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (src->data == NULL || src->size == 0) { memset(dst, 0, dst_byte_size); Dz1Error_set(errp, 0); }
	else if ((ret = Dz1CodeConv(dst, dst_byte_size, dst_charset, src->data, (size_t)src->size, Dz1Asn1UniversalStr_CHARSET)) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ret;
}

str_t Dz1Asn1UniversalStrA_toStr(Dz1Asn1UniversalStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = Dz1Asn1UnicodeStrA_toStr(src, Dz1Asn1UniversalStr_CHARSET, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1Asn1UniversalStrW_toStr(Dz1Asn1UniversalStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = Dz1Asn1UnicodeStrW_toStr(src, Dz1Asn1UniversalStr_CHARSET, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// Convert to
///////////////////////////////////////
// ASN.1 Universal String (28)
///////////////////////////////////////////////////////////////////////////////

// ASN.1 Character String (29)

///////////////////////////////////////////////////////////////////////////////
// ASN.1 BMPString (30)
static size_t _Dz1Asn1BMPStr_strlen(Dz1Asn1BMPStr *p)
{
	ssize_t ret = 0;
	if (p != NULL && p->data != NULL)
	{
		u16_t *cp = (u16_t *)p->data;
		u32_t sz = p->size / sizeof(u16_t);
		while(*cp && sz)
		{
			cp++;
			sz--;
			ret++;
		}
	}
	return ret;
}

int Dz1Asn1BMPStr_cmp(Dz1Asn1BMPStr *a, Dz1Asn1BMPStr *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else
	{
		size_t a_len = _Dz1Asn1BMPStr_strlen(a);
		size_t b_len = _Dz1Asn1BMPStr_strlen(b);
		if (a_len < b_len) return -1;
		else if (a_len > b_len) return 1;
		else
		{
			size_t i;
			u16_t *a_data = (u16_t *)a->data, a_value;
			u16_t *b_data = (u16_t *)b->data, b_value;
			for (i = 0; i < a_len; i++)
			{
				a_value = Dz1Endian2_big2host(a_data[i]);
				b_value = Dz1Endian2_big2host(b_data[i]);
				if (a_value < b_value) return -1;
				else if (a_value > b_value) return 1;
			}
			return 0;
		}
	}
}

size_t Dz1Asn1BMPStr_strlen(Dz1Asn1BMPStr *p)
{
	size_t ret = 0;
	if (p != NULL)
	{
		u16_t *cp = (u16_t *)p->data;
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
		u16_t mask = 0x00D8;
#elif DZ1_ENDIAN == DZ1_ENDIAN_BIG
		u16_t mask = 0xD800;
#else
#error No Endian
#endif
		u32_t size = p->size;
		while(size > 0 && *cp != 0)
		{
			if ((*cp & mask) == mask)
			{	// duo BMP letter
				size -= (size > 2) ? 2 : size; cp++;
				size -= (size > 2) ? 2 : size; cp++;
				ret++;
			}
			else // if ((*cp & mask) == 0x0000)
			{	// single BMP letter
				size -= (size > 2) ? 2 : size; cp++;
				ret++;
			}
		}
	}
	return ret;
}

Dz1Asn1UniversalStr *Dz1Asn1BMPStr_toUCS4(Dz1Asn1BMPStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Asn1OctetStr *ret = Dz1Asn1UnicodeStr_newFromBuf("UCS-4BE", 4, src->data, src->size, "UCS-2BE", 2, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}


void Dz1Asn1BMPStrA_dump(Dz1Asn1BMPStr *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if ((temp = Dz1Asn1BMPStrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_printf("\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1BMPStrA_fdump(FILE *fp, Dz1Asn1BMPStr *p, int tab)
{
	str_t temp = NULL;
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else if ((temp = Dz1Asn1BMPStrA_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		Dz1ThreadA_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadA_fprintf(fp, "\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#ifndef UNIX_SYSTEM
void Dz1Asn1BMPStrW_dump(Dz1Asn1BMPStr *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if ((temp = Dz1Asn1BMPStrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintb(tab, p->data, p->size, 16, TRUE);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_printf(L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}

void Dz1Asn1BMPStrW_fdump(FILE *fp, Dz1Asn1BMPStr *p, int tab)
{
	wstr_t temp = NULL;
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else if ((temp = Dz1Asn1BMPStrW_toStr(p, NULL)) == NULL)
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		Dz1ThreadW_ftprintb(fp, tab, p->data, p->size, 16);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)temp);
		Dz1ThreadW_fprintf(fp, L"\"%s\"\n", temp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)temp);
	}
}
#endif

#define Dz1Asn1BMPStr_CHARSET			"UCS-2BE"

///////////////////////////////////////
// New From
Dz1Asn1BMPStr *Dz1Asn1BMPStr_newFromBuf(u8_t *src, size_t src_byte_size, const char *src_charset, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr *ret = Dz1Asn1UnicodeStr_newFromBuf(Dz1Asn1BMPStr_CHARSET, 2, src, src_byte_size, src_charset, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

Dz1Asn1BMPStr *Dz1Asn1BMPStrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr	*ret = Dz1Asn1BMPStr_newFromBuf((u8_t *)src, strlen(src) * sizeof(char), DZ1_SYSTEM_MBCS_CHARSET, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
Dz1Asn1BMPStr *Dz1Asn1BMPStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UniversalStr	*ret = Dz1Asn1BMPStr_newFromBuf((u8_t *)src, wcslen(src) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// New From
///////////////////////////////////////

///////////////////////////////////////
// Convert to
ssize_t Dz1Asn1BMPStr_conv(Dz1Asn1BMPStr *src, str_t dst_charset, void *dst, size_t dst_byte_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (src == NULL || dst == NULL || dst_byte_size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (src->data == NULL || src->size == 0) { memset(dst, 0, dst_byte_size); Dz1Error_set(errp, 0); }
	else if ((ret = Dz1CodeConv(dst, dst_byte_size, dst_charset, src->data, (size_t)src->size, Dz1Asn1BMPStr_CHARSET)) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ret;
}

str_t Dz1Asn1BMPStrA_toStr(Dz1Asn1BMPStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = Dz1Asn1UnicodeStrA_toStr(src, Dz1Asn1BMPStr_CHARSET, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1Asn1BMPStrW_toStr(Dz1Asn1BMPStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = Dz1Asn1UnicodeStrW_toStr(src, Dz1Asn1BMPStr_CHARSET, 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif
// Convert to
///////////////////////////////////////
// ASN.1 BMPString (30)
///////////////////////////////////////////////////////////////////////////////
