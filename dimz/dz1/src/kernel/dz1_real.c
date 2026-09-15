#include <dz1.h>

#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_real.h>
#include <dz1_str.h>

///////////////////////////////////////////////////////////////////////////////
// Real (double) New/Del/Dump
int Dz1Real64_cmp(real64_t *a, real64_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

void Dz1Real64A_dump(real64_t *p, int tab) { if (!p) Dz1ThreadA_printf("(null)\n"); else Dz1ThreadA_printf("%.9f\n", *p); }
void Dz1Real64A_fdump(FILE *fp, real64_t *p, int tab) { if (!fp) return; else if (!p) Dz1ThreadA_fprintf(fp, "(null)\n"); else Dz1ThreadA_fprintf(fp, "%.9ff\n", *p); }
#ifndef UNIX_SYSTEM
void Dz1Real64W_dump(real64_t *p, int tab) { if (!p) Dz1ThreadW_printf(L"(null)\n"); else Dz1ThreadW_printf(L"%.9f\n", *p); }
void Dz1Real64W_fdump(FILE *fp, real64_t *p, int tab) { if (!fp) return; else if (!p) Dz1ThreadW_fprintf(fp, L"(null)\n"); else Dz1ThreadW_fprintf(fp, L"%.9ff\n", *p); }
#endif
// Real (double) New/Del/Dump
///////////////////////////////////////////////////////////////////////////////

static real64_t _mk_positive_exp_value64(real64_t v, u32_t exp)
{
	real64_t denominator = 1.0;
	u32_t i;
	for (i = 0; i < exp; i++) denominator *= 10.0;
	return v * denominator;
}

static real64_t _mk_negative_exp_value64(real64_t v, u32_t exp)
{
	real64_t denominator = 1.0;
	u32_t i;
	for (i = 0; i < exp; i++) denominator *= 10.0;
	return v / denominator;
}

static real64_t _parse_float64A(str_t src)
{
	real64_t ret = 0.0;

	char *cp = src;
	bool_t is_negative = FALSE;
	s32_t val = 0;

	if (*cp == '-') { is_negative = TRUE; cp++; }

	while(*cp && *cp != '.')
	{
		if (isdigit(*cp)) 
			val = val * 10 + (*cp - '0');
		cp++;
	}

	ret = (real64_t)val;

	if (*cp == '.')
	{
		u32_t max_depth = 16;
		u64_t frag = 0, v_temp;
		real64_t denominator = 1.0;

		cp++;										// pass '.'
		while(*cp && max_depth)
		{
			v_temp = (u64_t)((*cp) - '0');
			frag = frag * 10 + v_temp;
			denominator *= 10.0;
			cp++;
			max_depth--;
		}
		ret += (real64_t)frag / denominator;
	}

	if (is_negative) ret = -ret;

	return ret;
}

real64_t Dz1Real64FromStrA(str_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	real64_t ret = 0.0;
	str_t temp = NULL;
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1StrA_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *sp = temp, *dotp = NULL, *_dotp = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		Dz1StrA_ucase(temp);
		if ((dotp = strchr(temp, '.')) != NULL)
		{	// float type : 123.4567[E[+|-]1234]
			real64_t value = 0.0;
			u32_t exp = 0;
			char *epop = NULL;
			char buf[64], *dp = NULL;

			while((_dotp = strrchr(temp, '.')) != dotp) *_dotp = 0;		// make single dotted string

			if ((epop = strstr(temp, "E+")) != NULL)
			{	// exponent positive, int = sp~ep, +exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float64A(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Ato32(buf);

				ret = _mk_positive_exp_value64(value, exp);
			}
			else if ((epop = strstr(temp, "E-")) != NULL)
			{	// exponent negative, , int = temp~ep, -exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float64A(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Ato32(buf);

				ret = _mk_negative_exp_value64(value, exp);
			}
			else
			{	// simple real number
				ret = _parse_float64A(temp);
			}
		}
		else
		{	// integer type
			u64_t i64 = Dz1Ato64(src);
			ret = (real64_t)i64;
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static real64_t _parse_float64W(wstr_t src)
{
	real64_t ret = 0.0;

	wchar_t *cp = src;
	bool_t is_negative = FALSE;
	s32_t val = 0;

	if (*cp == L'-') { is_negative = TRUE; cp++; }

	while(*cp && *cp != L'.')
	{
		if (iswdigit(*cp)) 
			val = val * 10 + (*cp - L'0');
		cp++;
	}

	ret = (real64_t)val;

	if (*cp == L'.')
	{
		u32_t max_depth = 16;
		u64_t frag = 0;
		real64_t denominator = 1.0;

		cp++;
		while(*cp && max_depth)
		{
			if (iswdigit(*cp))
			{
				frag = frag * 10 + (*cp - L'0');
				denominator *= 10.0;
			}
			cp++;
			max_depth--;
		}
		ret += (real64_t)frag / denominator;
	}

	if (is_negative) ret = -ret;

	return ret;
}

real64_t Dz1Real64FromStrW(wstr_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	real64_t ret = 0.0;
	wstr_t temp = NULL;
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1StrW_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t *sp = temp, *dotp = NULL, *_dotp = NULL;
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
		Dz1StrW_ucase(temp);
		if ((dotp = wcschr(temp, L'.')) != NULL)
		{	// float type : 123.4567[E[+|-]1234]
			real64_t value = 0.0;
			u32_t exp = 0;
			wchar_t *epop = NULL;
			wchar_t buf[64], *dp = NULL;

			while((_dotp = wcsrchr(temp, L'.')) != dotp) *_dotp = 0;		// make single dotted string

			if ((epop = wcsstr(temp, L"E+")) != NULL)
			{	// exponent positive, int = sp~ep, +exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float64W(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Wto32(buf);

				ret = _mk_positive_exp_value64(value, exp);
			}
			else if ((epop = wcsstr(temp, L"E-")) != NULL)
			{	// exponent negative, , int = temp~ep, -exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float64W(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Wto32(buf);

				ret = _mk_negative_exp_value64(value, exp);
			}
			else
			{	// simple real number
				ret = _parse_float64W(temp);
			}
		}
		else
		{	// integer type
			u64_t i64 = Dz1Wto64(src);
			ret = (real64_t)i64;
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Float New/Del/Dump
int Dz1Real32_cmp(real32_t *a, real32_t *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

void Dz1Real32A_dump(float *p, int tab) { if (!p) Dz1ThreadA_printf("(null)\n"); else Dz1ThreadA_printf("%f\n", *p); }
void Dz1Real32A_fdump(FILE *fp, float *p, int tab) { if (p == NULL) Dz1ThreadA_fprintf(fp, "(null)\n"); else Dz1ThreadA_fprintf(fp, "%f\n", *p); }
#ifndef UNIX_SYSTEM
void Dz1Real32W_dump(float *p, int tab) { if (!p) Dz1ThreadW_printf(L"(null)\n"); else Dz1ThreadW_printf(L"%f\n", *p); }
void Dz1Real32W_fdump(FILE *fp, float *p, int tab) { if (p == NULL) Dz1ThreadW_fprintf(fp, L"(null)\n"); else Dz1ThreadW_fprintf(fp, L"%f\n", *p); }
#endif
// Float New/Del/Dump
///////////////////////////////////////////////////////////////////////////////

static real32_t _mk_positive_exp_value32(real32_t v, u32_t exp)
{
	real32_t denominator = 1.0;
	u32_t i;
	for (i = 0; i < exp; i++) denominator *= 10.0;
	return v * denominator;
}

static real32_t _mk_negative_exp_value32(real32_t v, u32_t exp)
{
	real32_t denominator = 1.0;
	u32_t i;
	for (i = 0; i < exp; i++) denominator *= 10.0;
	return v / denominator;
}

static real32_t _parse_float32A(str_t src)
{
	real32_t ret = 0.0;

	char *cp = src;
	bool_t is_negative = FALSE;
	s32_t val = 0;

	if (*cp == '-') { is_negative = TRUE; cp++; }

	while(*cp && *cp != '.')
	{
		if (isdigit(*cp)) 
			val = val * 10 + (*cp - '0');
		cp++;
	}

	ret = (real32_t)val;

	if (*cp == '.')
	{
		u32_t frag = 0;
		real32_t denominator = 1.0;

		cp++;
		while(*cp)
		{
			if (isdigit(*cp))
			{
				frag = frag * 10 + (*cp - '0');
				denominator *= 10.0;
			}
			cp++;
		}
		ret += (real32_t)frag / denominator;
	}

	if (is_negative) ret = -ret;

	return ret;
}

real32_t Dz1Real32FromStrA(str_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	real32_t ret = 0.0;
	str_t temp = NULL;
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1StrA_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *sp = temp, *dotp = NULL, *_dotp = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		Dz1StrA_ucase(temp);
		if ((dotp = strchr(temp, '.')) != NULL)
		{	// float type : 123.4567[E[+|-]1234]
			real32_t value = 0.0;
			u32_t exp = 0;
			char *epop = NULL;
			char buf[64], *dp = NULL;

			while((_dotp = strrchr(temp, '.')) != dotp) *_dotp = 0;		// make single dotted string

			if ((epop = strstr(temp, "E+")) != NULL)
			{	// exponent positive, int = sp~ep, +exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float32A(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Ato32(buf);

				ret = _mk_positive_exp_value32(value, exp);
			}
			else if ((epop = strstr(temp, "E-")) != NULL)
			{	// exponent negative, , int = temp~ep, -exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float32A(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Ato32(buf);

				ret = _mk_negative_exp_value32(value, exp);
			}
			else
			{	// simple real number
				ret = _parse_float32A(temp);
			}
		}
		else
		{	// integer type
			u64_t i64 = Dz1Ato64(src);
			ret = (real32_t)i64;
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static real32_t _parse_float32W(wstr_t src)
{
	real32_t ret = 0.0;

	wchar_t *cp = src, buf[64], *dp = buf;
	bool_t is_negative = FALSE;
	s32_t val = 0;

	if (*cp == L'-') { is_negative = TRUE; cp++; }

	while(*cp && *cp != L'.')
	{
		if (iswdigit(*cp)) 
			val = val * 10 + (*cp - L'0');
		cp++;
	}

	ret = (real32_t)val;

	if (*cp == L'.')
	{
		u32_t frag = 0;
		real32_t denominator = 1.0;

		cp++;
		while(*cp)
		{
			if (iswdigit(*cp))
			{
				frag = frag * 10 + (*cp - L'0');
				denominator *= 10.0;
			}
			cp++;
		}
		ret += (real32_t)frag / denominator;
	}

	if (is_negative) ret = -ret;

	return ret;
}

real32_t Dz1Real32FromStrW(wstr_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	real32_t ret = 0.0;
	wstr_t temp = NULL;
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1StrW_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t *sp = temp, *dotp = NULL, *_dotp = NULL;
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
		Dz1StrW_ucase(temp);
		if ((dotp = wcschr(temp, L'.')) != NULL)
		{	// float type : 123.4567[E[+|-]1234]
			real32_t value = 0.0;
			u32_t exp = 0;
			wchar_t *epop = NULL;
			wchar_t buf[64], *dp = NULL;

			while((_dotp = wcsrchr(temp, L'.')) != dotp) *_dotp = 0;		// make single dotted string

			if ((epop = wcsstr(temp, L"E+")) != NULL)
			{	// exponent positive, int = sp~ep, +exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float32W(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Wto32(buf);

				ret = _mk_positive_exp_value32(value, exp);
			}
			else if ((epop = wcsstr(temp, L"E-")) != NULL)
			{	// exponent negative, , int = temp~ep, -exp=(ep+2)~end
				dp = buf; while(*sp && sp < epop) *dp++ = *sp++; *dp++ = 0;
				value = _parse_float32W(buf);

				sp = epop + 2; dp = buf; while(*sp) *dp++ = *sp++; *dp++ = 0;
				exp = Dz1Wto32(buf);

				ret = _mk_negative_exp_value32(value, exp);
			}
			else
			{	// simple real number
				ret = _parse_float32W(temp);
			}
		}
		else
		{	// integer type
			u64_t i64 = Dz1Wto64(src);
			ret = (real32_t)i64;
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}
#endif
