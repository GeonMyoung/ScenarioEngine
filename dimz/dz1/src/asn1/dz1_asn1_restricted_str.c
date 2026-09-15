#include <dz1_str.h>
#include "dz1_asn1.h"

static bool_t _Dz1Asn1OctetText_checkLetter(int code, u16_t *charset, s32_t charset_max)
{
	if (code >= charset_max) return FALSE;
	else
	{
		int idx = code >> 4, shf = code & 0xF;
		u16_t mask = 0x8000 >> shf;
		if ((charset[idx] & mask) == 0) return FALSE;
	}
	return TRUE;
}

static bool_t Dz1Asn1OctetText_checkLetter(int code, u16_t *charset, s32_t charset_max)
{
	if (charset == NULL) return TRUE;
	else if (charset_max == 0) return FALSE;
	else return _Dz1Asn1OctetText_checkLetter(code, charset, charset_max);
}

static bool_t Dz1Asn1OctetText_check(u8_t *data, u32_t size, u16_t *charset, s32_t charset_max)
{
	bool_t ret = TRUE;
	if (charset == NULL) { }
	else if (charset_max == 0) ret = FALSE;
	else
	{
		u32_t i;
		for (i = 0; ret == TRUE && i < size; i++)
			ret = _Dz1Asn1OctetText_checkLetter(((int)data[i] & 0xFF), charset, charset_max);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Simple Octet Text Utility
static Dz1Asn1OctetStr *Dz1Asn1OctetTextA_newFromStr(str_t src, u16_t *charset, s32_t charset_max, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1PrintStr *ret = NULL;
	size_t len = 0;
	if (src == NULL || (len = strlen(src)) == 0)	return Dz1Asn1OctetStr_gen(errp);					// zero length string
	else if (charset == NULL)						return Dz1Asn1OctetStr_new(src, (u32_t)len, errp);	// no need to check
	else if (charset_max == 0)						ERR_SET_OUT(errp, EPERM);							// no permitted letter
	else if ((ret = Dz1Asn1OctetStr_new(DZ1_ASN1_OCTETSTR_DATA_ALLOC, (u32_t)len, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *i = NULL;
		u8_t *dp = ret->data;
		pthread_cleanup_push(Dz1Asn1PrintStr_delAndSetNull, (void *)&ret);

		Dz1Error_set(errp, 0);
		for (i = src; errp->code == 0 && *i != 0; i++)
		{
			if (_Dz1Asn1OctetText_checkLetter(((int)(*i) & 0xFF), charset, charset_max) == FALSE) ERR_SET_OUT(errp, EPERM);
			else *dp++ = *i;
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1PrintStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static str_t Dz1Asn1OctetTextA_toStr(Dz1Asn1OctetStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = (str_t)Dz1Calloc(sizeof(char), src->size + 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		for (i = 0; i < src->size; i++)
			ret[i] = (char)src->data[i];
	}
	return ret;
}

static void Dz1Asn1OctetTextA_dump(Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("(null)\n");
	else if (p->data == NULL || p->size == 0) Dz1ThreadA_printf("\"\"\n");
	else
	{
		u32_t i;
		DZ1_ERROR_SAFE_VAR(errp, err);
		if (Dz1ThreadA_putc('\"', errp) == FALSE) { }
		else
		{
			char c;
			for (i = 0; errp->code == 0 && i < p->size; i++)
			{
				c = (char)p->data[i];
				if (c >= 0x20 && c < 0x7F) Dz1ThreadA_putc(c, errp);
				else Dz1ThreadA_printf("\\x%02X", c);
			}
			if (errp->code == 0 )
				Dz1ThreadA_printf("\"\n");
		}
	}
}

static void Dz1Asn1OctetTextA_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "(null)\n");
	else if (p->data == NULL || p->size == 0) Dz1ThreadA_fprintf(fp, "\"\"\n");
	else
	{
		u32_t i;
		DZ1_ERROR_SAFE_VAR(errp, err);
		if (Dz1ThreadA_fputc(fp, '\"', errp) == FALSE) { }
		else
		{
			char c;
			for (i = 0; errp->code == 0 && i < p->size; i++)
			{
				c = (char)p->data[i];
				if (c >= 0x20 && c < 0x7F) Dz1ThreadA_fputc(fp, c, errp);
				else Dz1ThreadA_fprintf(fp, "\\x%02X", c);
			}
			if (errp->code == 0 )
				Dz1ThreadA_fprintf(fp, "\"\n");
		}
	}
}
#ifndef UNIX_SYSTEM
static Dz1Asn1OctetStr *Dz1Asn1OctetTextW_newFromStr(wstr_t src, u16_t *charset, s32_t charset_max, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1PrintStr *ret = NULL;
	size_t len = 0;
	if (src == NULL || (len = wcslen(src)) == 0) return Dz1Asn1OctetStr_gen(errp);
	else if ((ret = Dz1Asn1OctetStr_new(DZ1_ASN1_OCTETSTR_DATA_ALLOC, (u32_t)len * sizeof(wchar_t), errp)) == NULL) ERR_OUT(errp);
	else
	{
		int code = 0;
		wchar_t *i = NULL;
		u8_t *dp = ret->data;
		pthread_cleanup_push(Dz1Asn1PrintStr_delAndSetNull, (void *)&ret);
		Dz1Error_set(errp, 0);
		for (i = src; errp->code == 0 && *i != 0; i++)
		{
			if ((code = ((int)(*i) & 0xFF)) >= charset_max) ERR_SET_OUT(errp, EPERM);
			else
			{
				int idx = code >> 4, shf = code & 0xF;
				u16_t mask = 0x8000 >> shf;
				if ((charset[idx] & mask) == 0) ERR_SET_OUT(errp, EPERM);
				else *dp++ = (u8_t)(code & 0xFF);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1PrintStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static wstr_t Dz1Asn1OctetTextW_toStr(Dz1Asn1OctetStr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = (wstr_t)Dz1Calloc(sizeof(wchar_t), src->size + 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		for (i = 0; i < src->size; i++)
			ret[i] = (wchar_t)src->data[i] & 0xFF;
	}
	return ret;
}

static void Dz1Asn1OctetTextW_dump(Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("(null)\n");
	else if (p->data == NULL || p->size == 0) Dz1ThreadW_printf(L"\"\"\n");
	else
	{
		u32_t i;
		DZ1_ERROR_SAFE_VAR(errp, err);
		if (Dz1ThreadW_putc(L'\"', errp) == FALSE) { }
		else
		{
			wchar_t c;
			for (i = 0; errp->code == 0 && i < p->size; i++)
			{
				c = (wchar_t)p->data[i] & 0xFF;
				if (c >= 0x20 && c < 0x7F) Dz1ThreadW_putc(c, errp);
				else Dz1ThreadW_printf(L"\\x%02X", c);
			}
			if (errp->code == 0 )
				Dz1ThreadW_printf(L"\"\n");
		}
	}
}

static void Dz1Asn1OctetTextW_fdump(FILE *fp, Dz1Asn1OctetStr *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"(null)\n");
	else if (p->data == NULL || p->size == 0) Dz1ThreadW_fprintf(fp, L"\"\"\n");
	else
	{
		u32_t i;
		DZ1_ERROR_SAFE_VAR(errp, err);
		if (Dz1ThreadW_fputc(fp, L'\"', errp) == FALSE) { }
		else
		{
			wchar_t c;
			for (i = 0; errp->code == 0 && i < p->size; i++)
			{
				c = (wchar_t)p->data[i] & 0xFF;
				if (c >= 0x20 && c < 0x7F) Dz1ThreadW_fputc(fp, c, errp);
				else Dz1ThreadW_fprintf(fp, L"\\x%02X", c);
			}
			if (errp->code == 0 )
				Dz1ThreadW_fprintf(fp, L"\"\n");
		}
	}
}
#endif
// Simple Octet Text Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TIME (14) : ISO-8601 Simple String
static u16_t asn1_time_str_charmap[] =
{			//		8	4	2	1	8	4	2	1		8	4	2	1	8	4	2	1
	0x0000,	// 0x00	NUL SOH STX ETX ETO ENQ ACK BEL		BS	HT	LF	VT	FF	CR	S0	S1	0000 0000  0000 0000	0x0000
	0x0000,	// 0x10	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB		CAN	EM	SUB	ESC	FS	GS	RX	US	0000 0000  0000 0000	0x0000
	0x81DF,	// 0x20	SP	!	"	#	$	%	&	'		(	)	*	+	,	-	.	/	0000 0000  0001 1111	0x0000
	0xFFE5,	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?	1111 1111  1110 0000	0x0000
	0x7FFF,	// 0x40	@	A	B	C	D	E	F	G		H	I	J	K	L	M	N	O	0001 1000  1000 0100	0x0000
	0xFFE0,	// 0x50	P	Q	R	S	T	U	V	W		X	Y	Z	[	\	]	^	_	1011 1001  0110 0000	0x0000
};
static s32_t asn1_time_str_max = sizeof(asn1_time_str_charmap) * 8;
Dz1Asn1Time *Dz1Asn1TimeA_newFromStr(str_t iso8601_formatted_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Time *ret = Dz1Asn1OctetTextA_newFromStr(iso8601_formatted_str, asn1_time_str_charmap, asn1_time_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

str_t Dz1Asn1TimeA_toStr(Dz1Asn1Time *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = Dz1Asn1OctetTextA_toStr(src, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1TimeA_dump(Dz1Asn1Time *p, int tab)
{
	Dz1Asn1OctetTextA_dump(p, tab);
}

void Dz1Asn1TimeA_fdump(FILE *fp, Dz1Asn1Time *p, int tab)
{
	Dz1Asn1OctetTextA_fdump(fp, p, tab);
}
#ifndef UNIX_SYSTEM
Dz1Asn1Time *Dz1Asn1TimeW_newFromStr(wstr_t iso8601_formatted_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Time *ret = Dz1Asn1OctetTextW_newFromStr(iso8601_formatted_str, asn1_time_str_charmap, asn1_time_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

wstr_t Dz1Asn1TimeW_toStr(Dz1Asn1Time *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = Dz1Asn1OctetTextW_toStr(src, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1TimeW_dump(Dz1Asn1Time *p, int tab)
{
	Dz1Asn1OctetTextW_dump(p, tab);
}

void Dz1Asn1TimeW_fdump(FILE *fp, Dz1Asn1Time *p, int tab)
{
	Dz1Asn1OctetTextW_fdump(fp, p, tab);
}
#endif
// ASN.1 TIME (14) : ISO-8601 Simple String
///////////////////////////////////////////////////////////////////////////////

// 15 : Reserved
// 16 : SEQUENCE, SEQUENCE-OF
// 17 : SET, SET-OF

static void _charmapped_dumpA(Dz1Asn1OctetStr *p, int tab, u16_t *charmap, u32_t max_v)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u8_t v;
		u32_t i;
		for(i = 0; i < p->size; i++)
		{
			if ((v = p->data[i]) >= max_v) Dz1ThreadA_printf("\\02X;",v);
			else
			{
				int idx = v / 16, shf = v % 16;
				u16_t mask = 0x8000 >> shf;
				if (charmap[idx] & mask)
					Dz1ThreadA_printf("%c", v);
				else Dz1ThreadA_printf("\\02X;",v);
			}
		}
		Dz1ThreadA_putc('\n', NULL);
	}
}
static void _charmapped_fdumpA(FILE *fp, Dz1Asn1OctetStr *p, int tab, u16_t *charmap, u32_t max_v)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		u8_t v;
		u32_t i;
		for(i = 0; i < p->size; i++)
		{
			if ((v = p->data[i]) >= max_v) Dz1ThreadA_fprintf(fp, "\\02X;",v);
			else
			{
				int idx = v / 16, shf = v % 16;
				u16_t mask = 0x8000 >> shf;
				if (charmap[idx] & mask)
					Dz1ThreadA_fprintf(fp, "%c", v);
				else Dz1ThreadA_fprintf(fp, "\\02X;",v);
			}
		}
		Dz1ThreadA_fputc(fp, '\n', NULL);
	}
}
#ifndef UNIX_SYSTEM
static void _charmapped_dumpW(Dz1Asn1OctetStr *p, int tab, u16_t *charmap, u32_t max_v)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u8_t v;
		u32_t i;
		for(i = 0; i < p->size; i++)
		{
			if ((v = p->data[i]) >= max_v) Dz1ThreadW_printf(L"\\02X;",v);
			else
			{
				int idx = v / 16, shf = v % 16;
				u16_t mask = 0x8000 >> shf;
				if (charmap[idx] & mask)
					Dz1ThreadW_printf(L"%c", (wchar_t)v & 0xFF);
				else Dz1ThreadW_printf(L"\\02X;",v);
			}
		}
		Dz1ThreadW_putc(L'\n', NULL);
	}
}

static void _charmapped_fdumpW(FILE *fp, Dz1Asn1OctetStr *p, int tab, u16_t *charmap, u32_t max_v)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		u8_t v;
		u32_t i;
		for(i = 0; i < p->size; i++)
		{
			if ((v = p->data[i]) >= max_v) Dz1ThreadW_fprintf(fp, L"\\02X;",v);
			else
			{
				int idx = v / 16, shf = v % 16;
				u16_t mask = 0x8000 >> shf;
				if (charmap[idx] & mask)
					Dz1ThreadW_fprintf(fp, L"%c", (wchar_t)v & 0xFF);
				else Dz1ThreadW_fprintf(fp, L"\\02X;",v);
			}
		}
		Dz1ThreadW_fputc(fp, L'\n', NULL);
	}
}
#endif

size_t Dz1Asn1SimpleStr_strlen(Dz1Asn1OctetStr *p)
{
	size_t ret = 0;
	if (p != NULL && p->data != NULL && p->size > 0)
	{
		u32_t i;
		u8_t *c;
		for (i = 0, c = p->data; i < p->size && *c != 0; c++, i++) ret++;
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Numeric String (18)
static u16_t asn1_numeric_str_charmap[] =
{			//		8	4	2	1	8	4	2	1		8	4	2	1	8	4	2	1
	0x0000,	// 0x00	NUL SOH STX ETX ETO ENQ ACK BEL		BS	HT	LF	VT	FF	CR	S0	S1	0000 0000  0000 0000	0x0000
	0x0000,	// 0x10	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB		CAN	EM	SUB	ESC	FS	GS	RX	US	0000 0000  0000 0000	0x0000
	0x81DF,	// 0x20	SP	!	"	#	$	%	&	'		(	)	*	+	,	-	.	/	1000 0000  0000 0000	0x8000
	0xFFE5	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?	1111 1111  1100 0000	0xFFC0
};
static s32_t asn1_numeric_str_max = sizeof(asn1_numeric_str_charmap) * 8;
bool_t Dz1Asn1DigitStr_check(Dz1Asn1DigitStr *p)
{
	return Dz1Asn1OctetText_check(p->data, p->size, asn1_numeric_str_charmap, asn1_numeric_str_max);
}

Dz1Asn1DigitStr *Dz1Asn1DigitStrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1DigitStr *ret = Dz1Asn1OctetTextA_newFromStr(src, asn1_numeric_str_charmap, asn1_numeric_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1DigitStrA_dump(Dz1Asn1DigitStr *p, int tab)
{
	_charmapped_dumpA(p, tab, asn1_numeric_str_charmap, asn1_numeric_str_max);
}

void Dz1Asn1DigitStrA_fdump(FILE *fp, Dz1Asn1DigitStr *p, int tab)
{
	_charmapped_fdumpA(fp, p, tab, asn1_numeric_str_charmap, asn1_numeric_str_max);
}
#ifndef UNIX_SYSTEM
Dz1Asn1DigitStr *Dz1Asn1DigitStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1DigitStr *ret = Dz1Asn1OctetTextW_newFromStr(src, asn1_numeric_str_charmap, asn1_numeric_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1DigitStrW_dump(Dz1Asn1DigitStr *p, int tab)
{
	_charmapped_dumpW(p, tab, asn1_numeric_str_charmap, asn1_numeric_str_max);
}

void Dz1Asn1DigitStrW_fdump(FILE *fp, Dz1Asn1DigitStr *p, int tab)
{
	_charmapped_fdumpW(fp, p, tab, asn1_numeric_str_charmap, asn1_numeric_str_max);
}
#endif
// ASN.1 Numeric String (18)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Printable String (19)
static u16_t asn1_printable_str_charmap[] =
{			//		8	4	2	1	8	4	2	1		8	4	2	1	8	4	2	1
	0x0000,	// 0x00	NUL SOH STX ETX ETO ENQ ACK BEL		BS	HT	LF	VT	FF	CR	S0	S1	0000 0000  0000 0000	0x0000
	0x0000,	// 0x10	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB		CAN	EM	SUB	ESC	FS	GS	RX	US	0000 0000  0000 0000	0x0000
	0x81DF,	// 0x20	SP	!	"	#	$	%	&	'		(	)	*	+	,	-	.	/	1000 0001  1101 1111	0x81DF
	0xFFE5,	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?	1111 1111  1110 0101	0xFFE5
	0x7FFF,	// 0x40	@	A	B	C	D	E	F	G		H	I	J	K	L	M	N	O	0111 1111  1111 1111	0x7FFF
	0xFFE0,	// 0x50	P	Q	R	S	T	U	V	W		X	Y	Z	[	\	]	^	_	1111 1111  1110 0000	0xFFE0
	0x7FFF,	// 0x60	`	a	b	c	d	e	f	g		h	i	j	k	l	m	n	o	0111 1111  1111 1111	0x7FFF
	0xFFE0	// 0x70	p	q	r	s	t	u	v	w		x	y	z	{	|	}	~	DEL 1111 1111  1110 0000	0xFFE0
};
static s32_t asn1_printable_str_max = sizeof(asn1_printable_str_charmap) * 8;

bool_t Dz1Asn1PrintStr_check(Dz1Asn1PrintStr *p)
{
	return Dz1Asn1OctetText_check(p->data, p->size, asn1_printable_str_charmap, asn1_printable_str_max);
}

Dz1Asn1PrintStr *Dz1Asn1PrintStrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1PrintStr *ret = Dz1Asn1OctetTextA_newFromStr(src, asn1_printable_str_charmap, asn1_printable_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1PrintStrA_dump(Dz1Asn1PrintStr *p, int tab)
{
	_charmapped_dumpA(p, tab, asn1_printable_str_charmap, asn1_printable_str_max);
}

void Dz1Asn1PrintStrA_fdump(FILE *fp, Dz1Asn1PrintStr *p, int tab)
{
	_charmapped_fdumpA(fp, p, tab, asn1_printable_str_charmap, asn1_printable_str_max);
}
#ifndef UNIX_SYSTEM
Dz1Asn1PrintStr *Dz1Asn1PrintStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1PrintStr *ret = Dz1Asn1OctetTextW_newFromStr(src, asn1_printable_str_charmap, asn1_printable_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1PrintStrW_dump(Dz1Asn1PrintStr *p, int tab)
{
	_charmapped_dumpW(p, tab, asn1_printable_str_charmap, asn1_printable_str_max);
}

void Dz1Asn1PrintStrW_fdump(FILE *fp, Dz1Asn1PrintStr *p, int tab)
{
	_charmapped_fdumpW(fp, p, tab, asn1_printable_str_charmap, asn1_printable_str_max);
}
#endif
// ASN.1 Printable String (19)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TeleTex String, T64 String (20)										G0			G1			G2			G3		C0		C1		Range
// CP-6		: Basic ASCII(X3.4)													▣)B		▣(B											0x21-0x7F
// CP-87	: Japanese							(JIS C 6226)					▣$B		▣$)B		▣$*B		▣$+B					0x2121~0x7E7E
// CP-102	: TeleTex Primary = CP-6			(T.61) 							▣(u		▣)u		▣*u		▣+u					0x21-0x7C
// CP-103	: TeleTex Supplementary	= CP-156	(T.61)							▣(v		▣)v		▣*v		▣+v					0x21-0x7E
// CP-106	: TeleTex Primary Controls			(T.61)																		▣!E			0x08-0x1D
// CP-107	: TeleTex Supplementary Controls	(T.61)																				▣"H	0x8C-0x9B
// CP-126	: Latin/Greek						(ELOT-128/ECMA-118)							▣-F		▣.F		▣/F					0x20-0x7E
// CP-144	: Cyrillic							(ECMA-113 2nd, ISO 8859-5)					▣-L		▣.L		▣/L					0x20-0x7F
// CP-150	: Greek Primary						(CCITT Administrations)			▣(!@		▣)!@		▣*!@		▣+!@					0x21-0x7E
// CP-153	: Basic Cyrillic					(GOST19768-74, ST SEV358-88)				▣-O		▣.O		▣/O					0x20-0x71
// CP-156	: Supplementary	= CP-103			(ISO/IEC 6937)								▣-Q		▣.Q		▣/Q					0x20-0x7F
// CP-164	: Hebrew Supplementary				(CCITT Administrations)						▣-S		▣.S		▣/S					0x60-0x7A
// CP-165	: Chinese							(GB-2312 + GB-8565.2)			▣$(E		▣$)E		▣$*E		▣$+E					0x2121-0x7E7E
// CP-168	: Japanese							(JIS X 0208-1992)				▣&@▣$B	▣&@▣$)B	▣&@▣$*B	▣&@▣$+B				0x2121-0x7E7E

static u16_t asn1_teletex_str_charmap[] =
{			//		0	1	2	3	4	5	6	7		8	9	A	B	C	D	E	F
	0x00AF,	// 0x00	-	-	-	-	-	-	-	-		BS	-	LF	-	FF	CR	LSO	LSI		0000 0000  1010 1111	0x00AF
	0x0074,	// 0x10	-	-	-	-	-	-	-	-		-	SS2	SUB	ESC	-	SS3	-	-		0000 0000  0111 0100	0x0074
	0xE7FF,	// 0x20	SP	!	"			%	&	'		(	)	*	+	,	-	.	/		1110 0111  1111 1111	0xE7FF
	0xFFFF,	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?		1111 1111  1111 1111	0xFFFF
	0xFFFF,	// 0x40	@	A	B	C	D	E	F	G		H	I	J	K	L	M	N	O		1111 1111  1111 1111	0xFFFF
	0xFFF5,	// 0x50	P	Q	R	S	T	U	V	W		X	Y	Z	[		]		_		1111 1111  1111 0101	0xFFF5
	0x7FFF,	// 0x60		a	b	c	d	e	f	g		h	i	j	k	l	m	n	o		0111 1111  1111 1111	0x7FFF
	0xFFE9,	// 0x70	p	q	r	s	t	u	v	w		x	y	z		|			DEL		1111 1111  1110 1001	0xFFE9
	0x0018,	// 0x80	-	-	-	-	-	-	-	-		-	-	-	PLD	PLU	-	-	-		0000 0000  0001 1000	0x0018
	0x0010,	// 0x90	-	-	-	-	-	-	-	-		-	-	-	CSI	-	-	-	-		0000 0000  0001 0000	0x0010
	0xFF90,	// 0xA0	NBS	&i	&c	&L	&$	&Y	&#	&S		&o	-	-	&<<	-	-	-	-		1111 1111  1001 0000	0xFF90
	0xFF9F,	// 0xB0	^o	&+	^2	^3	&x	%u	&P	&.		%/	-	-	&>>	1/4	1/2	3/4	&?		1111 1111  1001 1111	0xFF9F
	0x7FFF,	// 0xC0	-	$@	$@	$@	$@	$@	$@	$@		$@	$@	$@	$@	$@	$@	$@	$@		0111 1111  1111 1111	0x7FFF
	0x0000,	// 0xD0	-	-	-	-	-	-	-	-		-	-	-	-	-	-	-	-		0000 0000  0000 0000	0x0000
	0xFBFF,	// 0xE0	$@	$@	$@	$@	$@	-	$@	$@		$@	$@	$@	$@	$@	$@	$@	$@		1111 1011  1111 1111	0xFBFF
	0xFFFE	// 0xF0	$@	$@	$@	$@	$@	$@	$@	$@		$@	$@	$@	$@	$@	$@	$@	-		1111 1111  1111 1110	0xFFFE
};
static s32_t asn1_teletex_str_max = sizeof(asn1_teletex_str_charmap) * 8;
bool_t Dz1Asn1TeletexStr_check(Dz1Asn1TeletexStr *p)
{
	return Dz1Asn1OctetText_check(p->data, p->size, asn1_teletex_str_charmap, asn1_teletex_str_max);
}

// ASN.1 TeleTex String, T64 String (20)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 VideoTex String (21)													G0			G1			G2			G3		C0		C1		Range
// CP-1		: Control							(ISO-646)						▣!@														0x00-0x1F, 0x40-0x5F | 0x80-0x9F
// CP-13	: Japanese KataKana					(JIS C 6220-1969)				▣(I		▣)I											0x21-0x5F
// CP-72	: Supplementary						Superseded by CP-173
// CP-73	: Attribute Control 4 VideoTex		(CCITT Administrations)																▣"@	0x40-0x5F | 0x80-0x9F
// CP-87	: Japanese							(JIS C 6226-1983)				▣$B		▣$)B		▣$*B		▣$+B					0x2121-0x7E7E
// CP-89	: Arabic							(Arab Standard 449)				▣(k		▣)k		▣*k		▣+k					0x21-0x72
// CP-102	: Teletex Primary = CP-6			(T.61) 							▣(u		▣)u		▣*u		▣+u					0x21-0x7C
// CP-108	: NAPLPS							ANSI X3.110-1983,CSA T500-1983	▣%@
// CP-126	: Latin/Greek						(ELOT-128/ECMA-118)							▣-F		▣.F		▣/F					0x20-0x7E
// CP-128	: Supplementary						CCITT T.101 Data Syntax III		▣(|		▣)|		▣*|		▣+|					0x21-0x7E
// CP-129	: Supplementary						CCITT T.101 Data Syntax III					▣-}		▣.}		▣.}					0x20-0x3F, 0x5F-0x7F
// CP-144	: Cyrillic							(ECMA-113 2nd, ISO 8859-5)					▣-L		▣.L		▣/L					0x20-0x7F
// CP-150	: Greek Primary						(CCITT Administrations)			▣(!@		▣)!@		▣*!@		▣+!@					0x21-0x7E
// CP-153	: Basic Cyrillic					(GOST19768-74, ST SEV358-88)				▣-O		▣.O		▣/O					0x20-0x71
// CP-164	: Hebrew Supplementary				(CCITT Administrations)						▣-S		▣.S		▣/S					0x60-0x7A
// CP-165	: Chinese							(GB-2312 + GB-8565.2)			▣$(E		▣$)E		▣$*E		▣$+E					0x2121-0x0x7E7E
// CP-168	: Japanese							(JIS X 0208-1992)				▣&@▣$B	▣&@▣$)B	▣&@▣$*B	▣&@▣$+B				0x2121-0x0x7E7E
// CP-173	: Supplementary(Mosaic)				CCITT Administrations			▣(d		▣)d		▣*d		▣+d					0x2q-0x7E
// ASN.1 VideoTex String (21)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 IA5 String (22)														G0			G1			G2			G3		C0		C1		Range
// CP-1		: Control							(ISO-646)						▣!@														0x00-0x1F, 0x40-0x5F | 0x80-0x9F
// CP-6		: Basic ASCII(X3.4)													▣)B		▣(B											0x21-0x7F

static u16_t asn1_ia5_str_charmap[] =
{			//		8	4	2	1	8	4	2	1		8	4	2	1	8	4	2	1
	0x0000,	// 0x00	NUL SOH STX ETX ETO ENQ ACK BEL		BS	HT	LF	VT	FF	CR	S0	S1	1111 1111  1111 1111	0xFFFF
	0x0000,	// 0x10	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB		CAN	EM	SUB	ESC	FS	GS	RS	US	1111 1111  1111 1111	0xFFFF
	0x81DF,	// 0x20	SP	!	"	#	$	%	&	'		(	)	*	+	,	-	.	/	1111 1111  1111 1111	0xFFFF
	0xFFE5,	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?	1111 1111  1111 1111	0xFFFF
	0x7FFF,	// 0x40	@	A	B	C	D	E	F	G		H	I	J	K	L	M	N	O	1111 1111  1111 1111	0xFFFF
	0xFFE0,	// 0x50	P	Q	R	S	T	U	V	W		X	Y	Z	[	\	]	^	_	1111 1111  1111 1111	0xFFFF
	0x7FFF,	// 0x60	`	a	b	c	d	e	f	g		h	i	j	k	l	m	n	o	1111 1111  1111 1111	0xFFFF
	0xFFE0	// 0x70	p	q	r	s	t	u	v	w		x	y	z	{	|	}	~	DEL 1111 1111  1111 1111	0xFFFF
};
static s32_t asn1_ia5_str_max = sizeof(asn1_ia5_str_charmap) * 8;

bool_t Dz1Asn1IA5Str_check(Dz1Asn1IA5Str *p)
{
	return Dz1Asn1OctetText_check(p->data, p->size, asn1_ia5_str_charmap, asn1_ia5_str_max);
}

Dz1Asn1IA5Str *Dz1Asn1IA5StrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1IA5Str *ret = Dz1Asn1OctetTextA_newFromStr(src, NULL, 128, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1IA5StrA_dump(Dz1Asn1IA5Str *p, int tab)
{
	_charmapped_dumpA(p, tab, asn1_ia5_str_charmap, asn1_ia5_str_max);
}

void Dz1Asn1IA5StrA_fdump(FILE *fp, Dz1Asn1IA5Str *p, int tab)
{
	_charmapped_fdumpA(fp, p, tab, asn1_ia5_str_charmap, asn1_ia5_str_max);
}
#ifndef UNIX_SYSTEM
Dz1Asn1IA5Str *Dz1Asn1IA5StrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1IA5Str *ret = Dz1Asn1OctetTextW_newFromStr(src, NULL, 128, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1IA5StrW_dump(Dz1Asn1IA5Str *p, int tab)
{
	_charmapped_dumpW(p, tab, asn1_ia5_str_charmap, asn1_ia5_str_max);
}

void Dz1Asn1IA5StrW_fdump(FILE *fp, Dz1Asn1IA5Str *p, int tab)
{
	_charmapped_fdumpW(fp, p, tab, asn1_ia5_str_charmap, asn1_ia5_str_max);
}
#endif
// ASN.1 IA5 String (22)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 UTC Time (23) : [UNIVERSAL 23] IMPLICIT VisibleString
/*
###############################################################################
### X.680
###############################################################################

47.3	The type is defined, using ASN.1, as follows:

			UTCTime ::= [UNIVERSAL 23] IMPLICIT VisibleString

		with the values of the VisibleString restricted to strings of characters which are the juxtaposition of:
		VisibleString의 문자를 사용하는 UTCTime은 다음의 형식으로 제한됩니다.

		a)	the six digits YYMMDD where YY is the two low-order digits of the Christian year, MM is the month (counting January as 01), and DD is the day of the month (01 to 31); and
			6자리 YYMMDD, 여기서 YY는 연도의 하위 2자리, MM은 월(1월을 01로 계산), DD는 해당 월의 일(01~31)입니다.
		그리고

		b)	either:
			1)	the four digits hhmm where hh is hour (00 to 23) and mm is minutes (00 to 59); or
				네 자리 hhmm (여기서 hh는 시간(00~23)이고 mm은 분(00~59)입니다.) 또는
			2)	the six digits hhmmss where hh and mm are as in 1) above, and ss is seconds (00 to 59); and
				6자리 hhmmss (여기서 hh 및 mm는 위의 1)과 같고 ss는 초(00~59) 입니다.)
		그리고
		c)	either:
			1)	the character Z; or
				문자 Z를 쓰거나,
			2)	one of the characters + or -, followed by hhmm, where hh is hour and mm is minutes.
				+ 또는 - 문자 다음에 hhmm가 옵니다. 여기서 hh는 시간이고 mm는 분입니다.

		The alternatives in b) above allow varying precisions in the specification of the time.
		위 b)의 대안은 시간 지정의 다양한 정밀도를 허용합니다.

		In alternative c) 1), the time is coordinated universal time. In alternative c) 2), the time (t1) specified by a) and b) above is the local time; 
		the time differential (t2) specified by c) 2) above enables the coordinated universal time to be determined as follows:
			Coordinated universal time is t1 - t2
		c)의 1) 형식을 사용하면 시간 값이 협정 세계시임을 의미합니다. c)의 2)형식을 사용하면 시간값이 현지 시간임을 의미합니다. 
		이때 시간값을 t1, 현지 시간차 값을 t2라고 하면 협정 세계시를 계산하는 공식은 t1 - t2 입니다.

		EXAMPLE 1 - If local time is 7am on 2 January 1982 and coordinated universal time is 12 noon on 2 January 1982, the value of UTCTime is either of:
			현지 시간이 1982년 1월 2일 오전 7시이고 협정 세계시가 1982년 1월 2일 정오 12시인 경우 UTCTime의 값은 다음 중 하나입니다.
			-	"8201021200Z"; or
			-	"8201020700-0500".
		EXAMPLE 2 - If local time is 7am on 2 January 2001 and coordinated universal time is 12 noon on 2 January 2001, the value of UTCTime is either of:
			현지 시간이 2001년 1월 2일 오전 7시이고 협정 세계시가 2001년 1월 2일 정오인 경우 UTCTime의 값은 다음 중 하나입니다.
			-	"0101021200Z"; or
			-	"0101020700-0500".

47.4	The tag shall be as defined in 47.3.
		태그는 47.3에 정의된 대로여야 합니다.

47.5	The value notation shall be the value notation for the VisibleString defined in 47.3.
		값 표기법은 47.3에 정의된 VisibleString에 대한 값 표기법이어야 합니다.

###############################################################################
### X.690
###############################################################################

11.8	UTCTime
11.8.1	The encoding shall terminate with "Z", as described in the ITU-T X.680 | ISO/IEC 8824-1 clause on UTCTime.
		인코딩은 X.680의 UTCTime 절에 설명된 대로 "Z"로 종료해야 합니다.

11.8.2	The seconds element shall always be present.
		초 요소는 항상 존재해야 합니다.

11.8.3	Midnight (GMT) shall be represented in the form:
		자정(GMT)은 다음 형식으로 표시됩니다.

			"YYMMDD000000Z"

		where "YYMMDD" represents the day following the midnight in question.
		여기서 "YYMMDD"는 해당 자정 다음 날을 나타냅니다.
		-> "YYMMDD000000Z"는 해당 날의 시작을 의미합니다.

11.8.4	Examples of valid representations
			"920521000000Z"
			"920622123421Z"
			"920722132100Z"
11.8.5	Examples of invalid representations
			"920520240000Z"	(midnight represented incorrectly)
			"9207221321Z"	(seconds of "00" omitted)
*/
Dz1Asn1UTCTime *Dz1Asn1UTCTime_newFromTM(struct tm *t, s32_t gmt_offset_min, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UTCTime *ret = NULL;

	if (t == NULL || gmt_offset_min < -719 || gmt_offset_min > 719) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char temp[64] = { 0, }, *dp = temp;
		size_t dp_sz = sizeof(temp), len;

		len = snprintf(dp, dp_sz, "%02d%02d%02d%02d%02d%02d", (t->tm_year + 1900) % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		dp += len;
		dp_sz -= len;

		if (gmt_offset_min != 0)
		{
			char sign = '+';
			u32_t offset_h, offset_m;

			Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "!!! UTCTime : value is not GMT\n");

			if (gmt_offset_min < 0)
			{
				sign = '-';
				gmt_offset_min = -gmt_offset_min;
			}

			offset_h = gmt_offset_min / 60;
			offset_m = gmt_offset_min % 60;

			len = snprintf(dp, dp_sz, "%c%02u%02u", sign, offset_h, offset_m);

			dp += len;
			dp_sz -= len;
		}
		else
		{
			*dp++ = 'Z';
			dp_sz--;
		}
		*dp = 0;

		if ((ret = Dz1Asn1UTCTime_new((u8_t *)temp, (u32_t)(dp - temp), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Asn1UTCTime *Dz1Asn1UTCTime_newFromT(time_t t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1UTCTime *ret = NULL;

	struct tm *tm_p = gmtime(&t);
	if (tm_p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmT = *tm_p;
		if ((ret = Dz1Asn1UTCTime_newFromTM(&tmT, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static ssize_t _parse_gmt_offset(int *ret_offset_min, char *sp, size_t sp_len, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (ret_offset_min == NULL || sp_len < 2) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char temp_digits[3] = { sp[0] , sp[1], 0 };
		int temp_val = Dz1Ato32(temp_digits);

		*ret_offset_min += temp_val * 60;

		sp += 2;
		sp_len -= 2;
		ret += 2;

		if (sp_len >= 2)
		{
			temp_digits[0] = sp[0];
			temp_digits[1] = sp[1];
			temp_val = Dz1Ato32(temp_digits);
			*ret_offset_min += temp_val;

			sp += 2;
			sp_len -= 2;
			ret += 2;
		}
	}
	return errp->code == 0 ? ret : -1;
}

time_t Dz1Asn1UTCTime_toT(Dz1Asn1UTCTime *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	time_t ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->data == NULL || p->size < 13) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *sp = (char *)p->data;
		u32_t sp_len = p->size;

		char yy[3] = {  sp[0],  sp[1], 0 };
		char mm[3] = {  sp[2],  sp[3], 0 };
		char dd[3] = {  sp[4],  sp[5], 0 };
		char hh[3] = {  sp[6],  sp[7], 0 };
		char mi[3] = {  sp[8],  sp[9], 0 };
		char ss[3] = { sp[10], sp[11], 0 };

		u32_t year		= Dz1Ato32(yy);
		u32_t month		= Dz1Ato32(mm);
		u32_t day		= Dz1Ato32(dd);
		u32_t hour		= Dz1Ato32(hh);
		u32_t minute	= Dz1Ato32(mi); // modified by gm 20230601 - mm -> mi
		u32_t seconds	= Dz1Ato32(ss);

		struct tm tmTarget;

		Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "!!! Dz1Asn1UTCTime : Do not use this type for time");

		tmTarget.tm_mon = month - 1;
		tmTarget.tm_mday = day;
		tmTarget.tm_hour = hour;
		tmTarget.tm_min = minute;
		tmTarget.tm_sec = seconds;

		sp += 12;
		sp_len -= 12;

		if (sp_len == 0) ERR_SET_OUT(errp, EFAULT);	// should 'Z' or +HHMM or -HHMM
		else
		{
			u32_t century = 0;
			time_t tNow = time(NULL);

			if (*sp == 'Z')
			{	// finalize to GMT
				struct tm *tm_p = gmtime(&tNow), tmNow = *tm_p;
				century = (tmNow.tm_year + 1900) / 100;
				tmTarget.tm_year = century * 100 + year;
				if ((ret = mktime(&tmTarget)) < 0) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			else if (*sp == '+' || *sp == '-')
			{	// +HHMM
				ssize_t sz = 0;

				bool_t is_minus = *sp == '-' ? TRUE : FALSE;
				int offset_min = 0;

				sp++;
				sp_len--;

				if ((sz = _parse_gmt_offset(&offset_min, sp, sp_len, errp)) < 0) ERR_OUT(errp);
				else
				{
					struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;

					sp += sz;
					sp_len -= (u32_t)sz;

					if (is_minus) offset_min = -offset_min;

					century = (tmNow.tm_year + 1900) / 100;
					tmTarget.tm_year = century * 100 + year;
					if ((ret = mktime(&tmTarget)) < 0) ERR_SET_OUT(errp, EFAULT);
					else
					{
						ret -= (offset_min * 60);
						Dz1Error_set(errp, 0);
					}
				}
			}
		}
	}
	return ret;
}

void Dz1Asn1UTCTimeA_dump(Dz1Asn1UTCTime *p, int tab)
{
	Dz1Asn1VisibleStrA_dump(p, tab);
}

void Dz1Asn1UTCTimeA_fdump(FILE *fp, Dz1Asn1UTCTime *p, int tab)
{
	Dz1Asn1VisibleStrA_fdump(fp, p, tab);
}
#ifndef UNIX_SYSTEM
void Dz1Asn1UTCTimeW_dump(Dz1Asn1UTCTime *p, int tab)
{
	Dz1Asn1VisibleStrW_dump(p, tab);
}
void Dz1Asn1UTCTimeW_fdump(FILE *fp, Dz1Asn1UTCTime *p, int tab)
{
	Dz1Asn1VisibleStrW_fdump(fp, p, tab);
}
#endif
// ASN.1 UTC Time (23) : [UNIVERSAL 23] IMPLICIT VisibleString
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Generalized Time (24) : [UNIVERSAL 24] IMPLICIT VisibleString
/*
###############################################################################
### X.680
###############################################################################

46		Generalized time
		NOTE 1 - Earlier versions of this Recommendation | International Standard used different text (due to the evolution of the ISO time standards), 
		but the technical content is unchanged from the first version of this Recommendation | International Standard.
		이 권장 표준의 이전 버전은 다른 텍스트를 사용했지만(ISO 시간 표준의 발전으로 인해) 기술적 내용은 이 권장 표준의 첫 번째 버전에서 변경되지 않았습니다.

		NOTE 2 - The time type (see clause 38) gives more flexibility and should be preferred.
		시간 유형(38절 참조)은 더 많은 유연성을 제공하며 선호되어야 합니다.

46.1	This type shall be referenced by the name:
			GeneralizedTime
46.2	The type consists of a calendar date, together with:
		유형은 다음과 함께 달력 날짜로 구성됩니다.

		a)	a local time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to an accuracy of:
			하루 중 현지 시간(하루 시작의 자정 포함, 하루 종료의 자정 제외)의 정확도:

			1)	hours, minutes, and seconds (or seconds and fractions of a second to any number of decimal places); or
				시, 분, 초(또는 소수 자릿수까지의 초 및 분수);
			또는
			2)	hours and minutes (or minutes and fractions of a minute to any number of decimal places); or
				시간 및 분(또는 소수점 이하 자릿수까지의 분 및 분수);
			또는
			3)	hours (or hours and fractions of an hour to any number of decimal places); or
				시간(또는 소수점 이하 자릿수까지의 시간 및 분수);
		또는
		b)	a UTC time of day, including midnight at the start of a day, but excluding midnight at the end of a day, to any of the accuracies listed in a) above; or
			하루 중 UTC 시간(하루 시작의 자정 포함, 하루 종료의 자정 제외), 위의 a)에 나열된 정확도;
		또는
		c)	a local time of day as specified in a) above, together with the difference between local time and UTC.
			현지 시간과 UTC의 차이와 함께 위의 a)에 지정된 현지 시간.

			NOTE - The time difference component is positive if the local time is ahead of UTC.
			현지 시간이 UTC보다 빠르면 시차 성분이 양수입니다.

46.3	The type is defined, using ASN.1, as follows:
		유형은 다음과 같이 ASN.1을 사용하여 정의됩니다.

			GeneralizedTime ::= [UNIVERSAL 24] IMPLICIT VisibleString

		with the values of the VisibleString restricted to strings of characters which are either:
		VisibleString의 값은 다음 중 하나인 문자열로 제한됩니다.

		a)	a specification of a calendar date followed by a local time, consisting of: 
			다음으로 구성된 달력 날짜와 현지 시간 지정:

			1)	a string representing the calendar date, (as specified in ISO 8601, 4.1.2.2 - Basic format); followed by:
				달력 날짜를 나타내는 문자열(ISO 8601, 4.1.2.2 - 기본 형식에 지정됨)  -> YYYYMMDD

				NOTE 1 - This specifies a four-digit representation of the year, a two-digit representation of the month 
				and a two-digit representation of the day, without use of separators.
				구분 기호를 사용하지 않고 연도의 네 자리 표시, 월의 두 자리 표시 및 일의 두 자리 표시를 지정합니다.

			다음에:

			2)	a string representing the time of day to an accuracy of one hour, one minute, one second, or fractions of a second (to any degree of accuracy), 
				using either comma or full stop as the decimal sign (as specified in ISO 8601, 4.2.2.2 and 4.2.2.3 - Basic format); optionally followed by:
				쉼표 또는 마침표를 소수점 기호로 사용하여 1시간, 1분, 1초 또는 1초의 소수부(정확도에 관계없이)의 정확도로 시간을 나타내는 문자열
				(ISO 8601, 4.2.2.2 및 4.2.2.3 - 기본 형식) 
				-> HH[MM[SS]]]
			선택적으로:

			3)	a decimal fraction of a minute if seconds are omitted, or a decimal fraction of an hour if minutes and seconds are omitted (as specified in ISO 8601, 4.2.2.4); or
				초가 생략된 경우 분의 소수점 이하 자릿수, 분과 초가 생략된 경우 시간의 소수점 이하 자릿수(ISO 8601, 4.2.2.4에 명시된 대로)
				-> [.ffffff…]

				NOTE 2 - ISO 8601 specifies the use of either a comma or a full stop as the decimal sign. There are no other separators present. 
				It is recommended that in any given ASN.1 specification, either comma or full stop be consistently used as the decimal sign.
				ISO 8601은 쉼표 또는 마침표를 소수점 기호로 사용하도록 지정합니다. 다른 구분 기호가 없습니다. 
				주어진 ASN.1 사양에서 쉼표 또는 마침표를 소수점 기호로 일관되게 사용하는 것이 좋습니다.
		또는
		b)	a specification of a calendar date and a UTC time consisting of the characters in a) above followed by an upper-case letter Z; or
			위의 a) 문자와 대문자 Z로 구성된 달력 날짜 및 UTC 시간 지정
			-> YYYYMMDDHH[MM[SS]]][.fffff…]Z
		또는
		c)	a specification of a calendar date, the local time, and the exact difference between local time and UTC as specified in ISO 8601, 
			with the minutes component optionally omitted if the difference is an integral number of hours.
			ISO 8601에 명시된 대로 달력 날짜, 현지 시간 및 현지 시간과 UTC 간의 정확한 차이를 지정하고, 차이가 정수 시간인 경우 분 구성요소는 선택적으로 생략됩니다.

			NOTE 3 - Early work on ASN.1 canonical encoding rules assumed that there was no actual concept of accuracy, so that an abstract value 
			that might be represented with a seconds component of 3.000 was regarded as the same abstract value as one that was represented with a seconds component of 3, 
			and forbade the use of trailing zeros in canonical encoding fractional parts, and forbade the omission of seconds or minutes and seconds.
			ASN.1 표준 인코딩 규칙에 대한 초기 작업에서는 정확도에 대한 실제 개념이 없다고 가정했으며, 3.000으로 표현한 초 값과 3으로 표현되는 초 값이 동일한 값으로 간주됩니다. 
			표준 인코딩 분수 부분에서 후행 0의 사용을 금지하고 초 또는 분 및 초 생략을 금지합니다.
			-> YYYYMMDDHHMISS[.ffff...]['Z' | {offset}]

			It also supported only the use of UTC time, not local time or local time with a time difference component. 
			This has not been changed in later editions of the ASN.1 standards, for backwards compatibility. 
			또한 현지 시간 또는 시차 구성 요소가 있는 현지 시간이 아닌 UTC 시간만 사용하도록 지원했습니다.
			이것은 이전 버전과의 호환성을 위해 ASN.1 표준의 이후 버전에서 변경되지 않았습니다.

			The TIME type (introduced into ASN.1 in 2004) recognizes that abstract values can have an associated accuracy, and that (e.g.) 
			the representations of seconds as 3.000 and 3 produces different abstract values, and that local time and UTC specifications represent different abstract values. 
			TIME 유형은 추상 값이 관련 정확도를 가질 수 있다는 것과 (예를 들어) 초를 3.000 및 3으로 표현하는 것이 서로 다른 추상 값을 생성하고
			현지 시간 및 UTC 사양이 서로 다른 추상 값을 나타낸다는 것을 인식합니다.

			The canonical encoding rules for TIME encode the full range of its abstract values, so use of TIME may be preferred in new specifications to the use of GeneralizedTime.
			TIME에 대한 "표준 인코딩 규칙"은 추상 값의 전체 범위를 인코딩하므로 새 사양에서는 GeneralizedTime을 사용하는 것보다 TIME을 사용하는 것이 더 좋습니다.

		In case c), the part of the string formed as in case a) represents the local time (t1), and the (signed) time difference (t2) enables UTC to be determined. 
		If t2 is positive, local time is ahead of UTC. We can thus determine UTC as:
		c)의 경우, a)와 같이 형성된 문자열의 일부는 현지 시간(t1)을 나타내고, (부호가 붙은) 시간 차이(t2)는 UTC가 결정될 수 있도록 합니다. 
		t2가 양수이면 현지 시간이 UTC보다 빠릅니다. 따라서 UTC를 다음과 같이 결정할 수 있습니다.

			UTC is t1 - t2

		EXAMPLES
			Case a)
			"19851106210627.3"
			Local time 6 minutes, 27.3 seconds after 9 pm on 6 November 1985.
			현지 시간 1985년 11월 6일 오후 9시 이후 6분 27.3초.
			-> 1985-11-06 21:06:27.3

			Case b)
			"19851106210627.3Z"
			Coordinated universal time as above.
			위와 같이 협정 세계시. 
			-> 1985-11-06 21:06:27.3

			Case c)
			"19851106210627.3-0500"
			Local time as in example a), with a coordinated universal time of 6 minutes, 27.3 seconds after 2 am on 7 November 1985.
			1985년 11월 7일 오전 2시 이후 6분 27.3초의 협정 세계시를 사용하는 예 a)와 같은 현지 시간.
			-> 1985-11-06 21:06:27.3 Local => t1 - (-05:00) = t1 + 05:00
			-> 1985-11-07 02:06:27.3 UTC

			Case d)
			"198511062106.456"
			Local time 6.456 minutes after 9 pm on 6 November 1985.
			1985년 11월 6일 오후 9시 이후 현지 시간 6.456분.
			-> 1985-11-06 21:6.456

			Case e)
			"1985110621.14159"
			Local time 0.14159 hours after 9 pm on 6 November 1985.
			현지 시간 1985년 11월 6일 오후 9시 이후 0.14159시간.
			-> 1985-11-06 21.14159

46.4	The tag shall be as defined in 46.3.
		태그는 46.3에 정의된 대로여야 합니다.

46.5	The value notation shall be the value notation for the VisibleString defined in 46.3.
		값 표기법은 46.3에 정의된 VisibleString에 대한 값 표기법이어야 합니다.

###############################################################################
### X.690
###############################################################################

11.7	GeneralizedTime

11.7.1	The encoding shall terminate with a "Z", as described in the Rec. ITU-T X.680 | ISO/IEC 8824-1 clause on GeneralizedTime.
		인코딩은 GeneralizedTime의 X.680 절에 설명된 대로 "Z"로 종료되어야 합니다.

11.7.2	The seconds element shall always be present.
		초 요소는 항상 존재해야 합니다.

11.7.3	The fractional-seconds elements, if present, shall omit all trailing zeros; if the elements correspond to 0, they shall be wholly omitted, 
		and the decimal point element also shall be omitted.
		fractional-seconds 요소가 있는 경우 모든 후행 0을 생략해야 합니다. 요소가 0에 해당하면 완전히 생략되고 소수점 요소도 생략됩니다.

	EXAMPLE
		A second element of "26.000" shall be represented as "26"; a seconds element of "26.5200" shall be represented as "26.52".
		"26.000"의 초 요소는 "26"으로 표시됩니다. "26.5200"의 초 요소는 "26.52"로 표시됩니다.

11.7.4	The decimal point element, if present, shall be the point option ".".
		소수점 요소가 있는 경우 소수점 옵션 "."을 사용해야 합니다.

11.7.5	Midnight (GMT) shall be represented in the form:
		자정(GMT)은 다음 형식으로 표시됩니다.

			"YYYYMMDD000000Z"

		where "YYYYMMDD" represents the day following the midnight in question.
		여기서 "YYYYMMDD"는 해당 자정 다음 날을 나타냅니다.
		-> “YYYYMMDD000000Z”는 해당일의 시작시간을 의미합니다.

	EXAMPLE
		Examples of valid representations:
			"19920521000000Z"
			"19920622123421Z"
			"19920722132100.3Z"
		Examples of invalid representations:
			"19920520240000Z"		(midnight represented incorrectly)
			"19920622123421.0Z"		(spurious trailing zeros)
			"19920722132100.30Z"	(spurious trailing zeros)
*/

Dz1Asn1GeneralTime *Dz1Asn1GeneralTime_newFromTM(struct tm *t, u32_t frac, u32_t frac_depth, s32_t gmt_offset_min, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1GeneralTime *ret = NULL;

	if (t == NULL || gmt_offset_min < -719 || gmt_offset_min > 719) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char temp[64] = { 0, }, *dp = temp;
		size_t dp_sz = sizeof(temp), len;

		len = snprintf(dp, dp_sz, "%04d%02d%02d%02d%02d%02d", (t->tm_year + 1900), t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		dp += len;
		dp_sz -= len;

		if (frac > 0 && frac_depth > 0)
		{
			while(frac % 10 == 0 && frac_depth)
			{	// calculate actual frac & depth
				frac_depth--;
				frac /= 10;
			}

			if (frac > 0)
			{
				char str_frac[16] = { 0, }, *sp = str_frac;
				u32_t str_frac_len = 0;

				str_frac_len = snprintf(str_frac, 15, "%u", frac);

				*dp++ = '.';
				dp_sz--;

				if (frac_depth > str_frac_len)
				{	// fill '0'
					u32_t front_zero = frac_depth - str_frac_len;
					while(front_zero) { *dp++ = '0'; dp_sz--; front_zero--; }
				}

				while(*sp) { *dp++ = *sp++; dp_sz--; }	// concatenate digits
				*dp = 0;
			}
		}

		if (gmt_offset_min != 0)
		{
			char sign = '+';
			u32_t offset_h, offset_m;

			Dz1Thread_log(DZ1_THREAD_LOG_MESSAGE, "!!! Dz1Asn1GeneralTime : It's not GMT Time\n");

			if (gmt_offset_min < 0)
			{
				sign = '-';
				gmt_offset_min = -gmt_offset_min;
			}

			offset_h = gmt_offset_min / 60;
			offset_m = gmt_offset_min % 60;

			len = snprintf(dp, dp_sz, "%c%02u%02u", sign, offset_h, offset_m);

			dp += len;
			dp_sz -= len;
		}
		else
		{
			*dp++ = 'Z';
			dp_sz--;
		}
		*dp = 0;

		if ((ret = Dz1Asn1GeneralTime_new((u8_t *)temp, (u32_t)(dp - temp), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Asn1GeneralTime *Dz1Asn1GeneralTime_newFromT(time_t t, u32_t frac, u32_t frac_depth, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1GeneralTime *ret = NULL;

	struct tm *tm_p = gmtime(&t);
	if (tm_p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct tm tmT = *tm_p;
		if ((ret = Dz1Asn1GeneralTime_newFromTM(&tmT, frac, frac_depth, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

time_t Dz1Asn1GeneralTime_toT(Dz1Asn1GeneralTime *p, u32_t *ret_frac, u32_t *ret_frac_depth, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	time_t ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->data == NULL || p->size < 15) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char *sp = (char *)p->data;
		u32_t sp_len = p->size;

		char yy[5] = {  sp[0],  sp[1], sp[2], sp[3], 0 };
		char mm[3] = {  sp[4],  sp[5], 0 };
		char dd[3] = {  sp[6],  sp[7], 0 };
		char hh[3] = {  sp[8],  sp[9], 0 };
		char mi[3] = { sp[10], sp[11], 0 };
		char ss[3] = { sp[12], sp[13], 0 };

		u32_t year		= Dz1Ato32(yy);
		u32_t month		= Dz1Ato32(mm);
		u32_t day		= Dz1Ato32(dd);
		u32_t hour		= Dz1Ato32(hh);
		u32_t minute	= Dz1Ato32(mi); // modified by gm 20230601 - mm->mi
		u32_t seconds	= Dz1Ato32(ss);

		struct tm tmTarget;
		tmTarget.tm_year	= year - 1900;
		tmTarget.tm_mon		= month - 1;
		tmTarget.tm_mday	= day;
		tmTarget.tm_hour	= hour;
		tmTarget.tm_min		= minute;
		tmTarget.tm_sec		= seconds;

		sp		+= 14;
		sp_len	-= 14;

		if (sp_len && *sp == '.')
		{	// fractional digits
			u32_t _ret_frac, *rf = ret_frac == NULL ? &_ret_frac : ret_frac;
			u32_t _ret_frac_depth, *rfd = ret_frac_depth == NULL ? &_ret_frac_depth : ret_frac_depth;

			sp++;					// skip '.'
			sp_len--;

			*rf = 0;

			if (sp_len == 0 || !isdigit(*sp)) ERR_SET_OUT(errp, EFAULT);
			else
			{
				while(*sp && isdigit(*sp))
				{
					*rf = *rf * 10 + ((*sp) - '0');
					(*rfd)++;
				}
			}
		}

		if (errp->code != 0) { }
		else if (sp_len == 0) ERR_SET_OUT(errp, EFAULT);	// should 'Z' or +HHMM or -HHMM
		else
		{
			u32_t century = 0;
			time_t tNow = time(NULL);
			century = century; // modified by gm 20230601 - unused value century, tNow;
			tNow = tNow;
			if (*sp == 'Z')
			{	// finalize to GMT
				if ((ret = mktime(&tmTarget)) < 0) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			else if (*sp == '+' || *sp == '-')
			{	// +HHMM
				ssize_t sz = 0;

				bool_t is_minus = *sp == '-' ? TRUE : FALSE;
				int offset_min = 0;

				sp++;
				sp_len--;

				if (sp_len == 0 || !isdigit(*sp)) ERR_SET_OUT(errp, EFAULT);
				else if ((sz = _parse_gmt_offset(&offset_min, sp, sp_len, errp)) < 0) ERR_OUT(errp);
				else
				{
					sp += sz;
					sp_len -= (u32_t)sz;

					if (is_minus) offset_min = -offset_min;

					if ((ret = mktime(&tmTarget)) < 0) ERR_SET_OUT(errp, EFAULT);
					else
					{
						ret -= (offset_min * 60);
						Dz1Error_set(errp, 0);
					}
				}
			}
		}
	}
	return ret;
}

void Dz1Asn1GeneralTimeA_dump(Dz1Asn1GeneralTime *p, int tab)
{
	Dz1Asn1VisibleStrA_dump(p, tab);
}

void Dz1Asn1GeneralTimeA_fdump(FILE *fp, Dz1Asn1GeneralTime *p, int tab)
{
	Dz1Asn1VisibleStrA_fdump(fp, p, tab);
}
#ifndef UNIX_SYSTEM
void Dz1Asn1GeneralTimeW_dump(Dz1Asn1GeneralTime *p, int tab)
{
	Dz1Asn1VisibleStrW_dump(p, tab);
}

void Dz1Asn1GeneralTimeW_fdump(FILE *fp, Dz1Asn1GeneralTime *p, int tab)
{
	Dz1Asn1VisibleStrW_fdump(fp, p, tab);
}
#endif
// ASN.1 Generalized Time (24) : [UNIVERSAL 24] IMPLICIT VisibleString
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Graphic String (25)
// All G Set + SPACE
size_t Dz1Asn1GraphicStr_len(Dz1Asn1GraphicStr *a)
{
	size_t ret = 0;
	if (a != NULL && a->data != NULL && a->size > 0)
	{
		ret = (size_t)a->size;
	}
	return ret;
}
// ASN.1 Graphic String (25)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Visible String (26)													G0			G1			G2			G3		C0		C1		Range
// CP-6		: Basic ASCII(X3.4)													▣)B		▣(B											0x21-0x7F
static u16_t asn1_visible_str_charmap[] =
{			//		8	4	2	1	8	4	2	1		8	4	2	1	8	4	2	1
	0x0000,	// 0x00	NUL SOH STX ETX ETO ENQ ACK BEL		BS	HT	LF	VT	FF	CR	S0	S1	0000 0000  0000 0000	0x0000
	0x0000,	// 0x10	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB		CAN	EM	SUB	ESC	FS	GS	RX	US	0000 0000  0000 0000	0x0000
	0x81DF,	// 0x20	SP	!	"	#	$	%	&	'		(	)	*	+	,	-	.	/	1111 1111  1111 1111	0xFFFF
	0xFFE5,	// 0x30	0	1	2	3	4	5	6	7		8	9	:	;	<	=	>	?	1111 1111  1111 1111	0xFFFF
	0x7FFF,	// 0x40	@	A	B	C	D	E	F	G		H	I	J	K	L	M	N	O	1111 1111  1111 1111	0xFFFF
	0xFFE0,	// 0x50	P	Q	R	S	T	U	V	W		X	Y	Z	[	\	]	^	_	1111 1111  1111 1111	0xFFFF
	0x7FFF,	// 0x60	`	a	b	c	d	e	f	g		h	i	j	k	l	m	n	o	1111 1111  1111 1111	0xFFFF
	0xFFE0	// 0x70	p	q	r	s	t	u	v	w		x	y	z	{	|	}	~	DEL 1111 1111  1111 1110	0xFFFE
};
static s32_t asn1_visible_str_max = sizeof(asn1_visible_str_charmap) * 8;

bool_t Dz1Asn1VisibleStr_check(Dz1Asn1VisibleStr *p)
{
	return Dz1Asn1OctetText_check(p->data, p->size, asn1_visible_str_charmap, asn1_visible_str_max);
}

Dz1Asn1VisibleStr *Dz1Asn1VisibleStrA_newFromStr(str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1VisibleStr *ret = Dz1Asn1OctetTextA_newFromStr(src, asn1_visible_str_charmap, asn1_visible_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1VisibleStrA_dump(Dz1Asn1VisibleStr *p, int tab)
{	// ISO646 String == ASCII String == MBCS
	_charmapped_dumpA(p, tab, asn1_visible_str_charmap, asn1_visible_str_max);
}

void Dz1Asn1VisibleStrA_fdump(FILE *fp, Dz1Asn1VisibleStr *p, int tab)
{
	_charmapped_fdumpA(fp, p, tab, asn1_visible_str_charmap, asn1_visible_str_max);
}
#ifndef UNIX_SYSTEM
Dz1Asn1VisibleStr *Dz1Asn1VisibleStrW_newFromStr(wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Asn1VisibleStr *ret = Dz1Asn1OctetTextW_newFromStr(src, asn1_visible_str_charmap, asn1_visible_str_max, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1Asn1VisibleStrW_dump(Dz1Asn1VisibleStr *p, int tab)
{	// ISO646 String == ASCII String == Just widen
	_charmapped_dumpW(p, tab, asn1_visible_str_charmap, asn1_visible_str_max);
}

void Dz1Asn1VisibleStrW_fdump(FILE *fp, Dz1Asn1VisibleStr *p, int tab)
{
	_charmapped_fdumpW(fp, p, tab, asn1_visible_str_charmap, asn1_visible_str_max);
}
#endif
// ASN.1 Visible String (26)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 General String (27)
// All G Set + All C Set + SPACE + DELETE
// ASN.1 General String (27)
///////////////////////////////////////////////////////////////////////////////

// ASN.1 Universal String (28)

///////////////////////////////////////////////////////////////////////////////
// ASN.1 Character String (29)
// X.680 44.5
// ASN.1 Character String (29)
///////////////////////////////////////////////////////////////////////////////

// ASN.1 BMPString (30)

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DATE (31)
// ISO-8601 Simple String
// ASN.1 DATE (31)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 TIME OF DAY (32)
// ISO-8601 Simple String
// ASN.1 TIME OF DAY (32)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DATE TIME (33)
// ISO-8601 Simple String
// ASN.1 DATE TIME (33)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN.1 DURATION (34)
// ISO-8601 Simple String
// ASN.1 DURATION (34)
///////////////////////////////////////////////////////////////////////////////
