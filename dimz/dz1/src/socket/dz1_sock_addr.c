#include <ctype.h>
#include <codeconv.h>
#include <dz1_stdio.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_sock_addr.h>
#include <dz1_codec.h>
#ifdef UNIX_SYSTEM
#include <netdb.h>
#include <arpa/inet.h>
#else
#ifdef DIMZ_SUPPORT_IPV6
#include <Shlwapi.h>
#include <WS2tcpip.h>
#ifndef __BORLANDC__
#pragma comment(lib, "Shlwapi.lib")
#endif // __BORLANDC__
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// IPv4
void Dz1IPv4A_dump(Dz1IPv4 *p, int tab)
{
	if (!p) return;
	Dz1ThreadA_printf("%d.%d.%d.%d\n", ((*p) & 0xFF000000) >> 24, ((*p) & 0xFF0000) >> 16, ((*p) & 0xFF00) >> 8, ((*p) & 0xFF));
}

void Dz1IPv4A_fdump(FILE *fp, Dz1IPv4 *p, int tab)
{
	if (!p) return;
	Dz1ThreadA_fprintf(fp, "%d.%d.%d.%d\n", ((*p) & 0xFF000000) >> 24, ((*p) & 0xFF0000) >> 16, ((*p) & 0xFF00) >> 8, ((*p) & 0xFF));
}
#ifndef UNIX_SYSTEM
void Dz1IPv4W_dump(Dz1IPv4 *p, int tab)
{
	if (!p) return;
	Dz1ThreadW_printf(L"%d.%d.%d.%d\n", ((*p) & 0xFF000000) >> 24, ((*p) & 0xFF0000) >> 16, ((*p) & 0xFF00) >> 8, ((*p) & 0xFF));
}

void Dz1IPv4W_fdump(FILE *fp, Dz1IPv4 *p, int tab)
{
	if (!p) return;
	Dz1ThreadW_fprintf(fp, L"%d.%d.%d.%d\n", ((*p) & 0xFF000000) >> 24, ((*p) & 0xFF0000) >> 16, ((*p) & 0xFF00) >> 8, ((*p) & 0xFF));
}
#endif
ssize_t Dz1IPv4_enc(u8_t *dst, size_t size, Dz1IPv4 *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
		DZ1_ENCODE4(cp, size, (*src), errp, ret);
	}
	return ret;
}

ssize_t Dz1IPv4_dec(Dz1IPv4 *dst, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!dst || !src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
		DZ1_DECODE4(dst, cp, size, errp, ret);
	}
	return ret;
}

bool_t Dz1Ipv4A_toStr(char *dst, size_t dst_sz, Dz1IPv4 src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char temp[4], *cp = dst;
	ssize_t len;
	u8_t a = ((src >> 24) & 0xFF), b = ((src >> 16) & 0xFF);
	u8_t c = ((src >>  8) & 0xFF), d = ((src >>  0) & 0xFF);

	if ((len = Dz1StrA_fromU8(temp, 4, a)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { strcpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = '.'; dst_sz--; }

	if ((len = Dz1StrA_fromU8(temp, 4, b)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { strcpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = '.'; dst_sz--; }

	if ((len = Dz1StrA_fromU8(temp, 4, c)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { strcpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = '.'; dst_sz--; }

	if ((len = Dz1StrA_fromU8(temp, 4, d)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { strcpy(cp, temp); cp += len; dst_sz -= len; }

	return TRUE;
}
#ifndef UNIX_SYSTEM
bool_t Dz1Ipv4W_toStr(wchar_t *dst, size_t dst_sz, Dz1IPv4 src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	wchar_t temp[4], *cp = dst;
	ssize_t len;
	u8_t a = ((src >> 24) & 0xFF), b = ((src >> 16) & 0xFF);
	u8_t c = ((src >>  8) & 0xFF), d = ((src >>  0) & 0xFF);

	if ((len = Dz1StrW_fromU8(temp, 4, a)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { wcscpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = L'.'; dst_sz--; }

	if ((len = Dz1StrW_fromU8(temp, 4, b)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { wcscpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = L'.'; dst_sz--; }

	if ((len = Dz1StrW_fromU8(temp, 4, c)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { wcscpy(cp, temp); cp += len; dst_sz -= len; }

	if (dst_sz == 0) ERR_SET_OUT_RET(errp, E2BIG, FALSE); else { *cp++ = L'.'; dst_sz--; }

	if ((len = Dz1StrW_fromU8(temp, 4, d)) < 0) ERR_OUT_RET(errp, FALSE);
	else if (dst_sz <= (size_t)len) ERR_SET_OUT_RET(errp, E2BIG, FALSE);
	else { wcscpy(cp, temp); cp += len; dst_sz -= len; }

	return TRUE;
}
#endif
// IPv4
///////////////////////////////////////////////////////////////////////////////

#ifdef DIMZ_SUPPORT_IPV6
///////////////////////////////////////////////////////////////////////////////
// IPv6
Dz1IPv6 *Dz1IPv6_new(u16_t addr[8], Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1IPv6 *ret = (Dz1IPv6 *)Dz1Calloc(sizeof(Dz1IPv6), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else memcpy(ret->addr, addr, (sizeof(u16_t) << 3));
	return ret;
}

Dz1IPv6 *Dz1IPv6_newA(u16_t a0, u16_t a1, u16_t a2, u16_t a3, u16_t a4, u16_t a5, u16_t a6, u16_t a7, Dz1Error *err)
{
	Dz1IPv6 *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u16_t addr[8] = { a0, a1, a2, a3, a4, a5, a6, a7 };
	if ((ret = Dz1IPv6_new(addr, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

void *Dz1IPv6_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1IPv6 *ret = Dz1IPv6_newA(0, 0, 0, 0, 0, 0, 0, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

Dz1IPv6 *Dz1IPv6_clone(Dz1IPv6 *src, Dz1Error *err)
{
	Dz1IPv6 *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IPv6_new(src->addr, errp)) == NULL) ERR_OUT(errp);
	return ret;
}

void Dz1IPv6_del(Dz1IPv6 *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1IPv6A_dump(Dz1IPv6 *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		char buf[46] = { 0, };	// modified by gm 20230601 - buf size 40 -> 46
		if (Dz1IPv6A_printable(p, buf, FALSE) == NULL) Dz1ThreadA_printf("#Address Error#\n");
		else Dz1ThreadA_printf("%s\n", buf);

// 		int i;
// 		str_t txt = NULL;
// 		char buf[40] = { 0, };
// 		struct sockaddr_in6 addr;
// 		Dz1Error err = DZ1_ERROR_INITIALIZER;
// 
// 		addr.sin6_family = AF_INET6;
// 		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);
// 		if ((txt = Dz1SockAddr6A_printable(&addr, buf, FALSE, &err)) == NULL) Dz1ThreadA_printf("#Address Error#\n");
// 		else Dz1ThreadA_printf("%s\n", txt);
	}
}

void Dz1IPv6A_fdump(FILE *fp, Dz1IPv6 *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		char buf[46] = { 0, }; // modified by gm 20230601 - buf size 40 -> 46
		if (Dz1IPv6A_printable(p, buf, FALSE) == NULL) Dz1ThreadA_fprintf(fp, "#Address Error#\n");
		else Dz1ThreadA_fprintf(fp, "%s\n", buf);

// 		int i;
// 		str_t txt = NULL;
// 		char buf[40] = { 0, };
// 		struct sockaddr_in6 addr;
// 		Dz1Error err = DZ1_ERROR_INITIALIZER;
// 
// 		addr.sin6_family = AF_INET6;
// 		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);
// 		if ((txt = Dz1SockAddr6A_printable(&addr, buf, FALSE, &err)) == NULL) Dz1ThreadA_fprintf(fp, "#Address Error#\n");
// 		else Dz1ThreadA_fprintf(fp, "%s\n", txt);
	}
}
#ifndef UNIX_SYSTEM
void Dz1IPv6W_dump(Dz1IPv6 *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		wchar_t buf[40] = { 0, };
		if (Dz1IPv6W_printable(p, buf, FALSE) == NULL) Dz1ThreadW_printf(L"#Address Error#\n");
		else Dz1ThreadW_printf(L"%s\n", buf);

// 		int i;
// 		wstr_t txt = NULL;
// 		wchar_t buf[40] = { 0, };
// 		struct sockaddr_in6 addr;
// 		Dz1Error err = DZ1_ERROR_INITIALIZER;
// 
// 		addr.sin6_family = AF_INET6;
// 		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);
// 		if ((txt = Dz1SockAddr6W_printable(&addr, buf, FALSE, &err)) == NULL) Dz1ThreadW_printf(L"#Address Error#\n");
// 		else Dz1ThreadW_printf(L"%s\n", txt);
	}
}

void Dz1IPv6W_fdump(FILE *fp, Dz1IPv6 *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		wchar_t buf[40] = { 0, };
		if (Dz1IPv6W_printable(p, buf, FALSE) == NULL) Dz1ThreadW_fprintf(fp, L"#Address Error#\n");
		else Dz1ThreadW_fprintf(fp, L"%s\n", buf);

// 		int i;
// 		wstr_t txt = NULL;
// 		wchar_t buf[40] = { 0, };
// 		struct sockaddr_in6 addr;
// 		Dz1Error err = DZ1_ERROR_INITIALIZER;
// 
// 		addr.sin6_family = AF_INET6;
// 		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);
// 		if ((txt = Dz1SockAddr6W_printable(&addr, buf, FALSE, &err)) == NULL) Dz1ThreadW_fprintf(fp, L"#Address Error#\n");
// 		else Dz1ThreadW_fprintf(fp, L"%s\n", txt);
	}
}
#endif

static str_t Dz1SockAddr6A_printable(struct sockaddr_in6 *p, char buf[46], bool_t fullRange, Dz1Error *errp); // modified by gm 20230601 - buf size 40 -> 46
str_t Dz1IPv6A_printable(Dz1IPv6 *p, char buf[46], bool_t isFullRange)
{
	str_t ret = NULL;
	if (p != NULL)
	{
		int i;
		struct sockaddr_in6 addr;

		addr.sin6_family = AF_INET6;
		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);

		ret = Dz1SockAddr6A_printable(&addr, buf, FALSE, NULL);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static wstr_t Dz1SockAddr6W_printable(struct sockaddr_in6 *p, wchar_t buf[40], bool_t fullRange, Dz1Error *errp);
wstr_t Dz1IPv6W_printable(Dz1IPv6 *p, wchar_t buf[40], bool_t isFullRange)
{
	wstr_t ret = NULL;
	if (p != NULL)
	{
		int i;
		struct sockaddr_in6 addr;

		addr.sin6_family = AF_INET6;
		for (i = 0; i < 8; i++) DZ1_IN6_ADDR16(&addr.sin6_addr)[i] = Dz1Endian2_host2big(p->addr[i]);

		ret = Dz1SockAddr6W_printable(&addr, buf, FALSE, NULL);
	}
	return ret;
}
#endif

ssize_t Dz1IPv6_enc(u8_t *dst, size_t size, Dz1IPv6 *src, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		int i;
		u8_t *cp = dst;
		for (i = 0; errp->code == 0 && i < 8; i++) DZ1_ENCODE2(cp, size, src->addr[i], errp, ret);
	}
	return ret;
}

ssize_t Dz1IPv6_dec(Dz1IPv6 *dst, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!dst && !src) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		int i;
		u8_t *cp = src;
		for (i = 0; errp->code == 0 && i < 8; i++) DZ1_DECODE2(&dst->addr[i], cp, size, errp, ret);
	}
	return ret;
}
// IPv6
///////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// Socket Address
///////////////////////////////////////////////////////////////////////////////

#if 0
            |       |       |       |       |
------------+-------+-------+-------+-------+-------+
            | Done  | HDgt  | Dot   | Cln   | DCln  |
------------+-------+-------+-------+-------+-------+
Initial  00 |       | L01   |       | Pu05  | Pu08  |
------------+-------+-------+-------+-------+-------+
Branch   01 |       |       | C03   | H05   |       |
------------+-------+-------+-------+-------+-------+
IPv4-Dot 02 | CXX.  |       | C03   |       |       |
------------+-------+-------+-------+-------+-------+
IPv4-Num 03 |       | L02   |       |       |       |
------------+-------+-------+-------+-------+-------+
IPv6-Col 04 | HXX.  |       | C11   | H05   | HPu05 |
------------+-------+-------+-------+-------+-------+
IPv6-Hex 05 |       | L04   |       |       |       |
------------+-------+-------+-------+-------+-------+
IPv6-ELB 08 | XX.   | L09   |       |       |       | <- Unsigned
------------+-------+-------+-------+-------+-------+
IPv6-Lcl 09 | HXX.  |       | C11   | H05   |       | <- Local Loopback
------------+-------+-------+-------+-------+-------+
IPv6-Dot 10 | CXX.  |       | C11   |       |       | <- IPv4 Mapped or IPv4 Compatible IPv6 Address
------------+-------+-------+-------+-------+-------+
IPv6-Num 11 |       | L10   |       |       |       |
------------+-------+-------+-------+-------+-------+
#endif

/*
typedef enum
{
	STATE_Initial,
	STATE_Branch,
	STATE_IPv4_Dot,
	STATE_IPv4_Num,
	STATE_IPv6_Colon,
	STATE_IPv6_Hex,
	STATE_IPv6_ELB,
	STATE_IPv6_Local,
	STATE_IPv6_Dot,
	STATE_IPv6_Num,
	STATE_max
} STATE;

typedef enum
{
	EVENT_Done,
	EVENT_HexDigit,
	EVENT_Dot,
	EVENT_Colon,
	EVENT_DoubleColon,
	EVENT_max
} EVENT;

typedef enum
{
	FillType_none,
	FillType_char,
	FillType_short,
	FillType_shortPad,
	FillType_longPad
} FillType;

typedef struct
{
	int state;

	str_t str;

	u8_t buf[16];
	u8_t *cp;
	int remain;

	FillType fill[16];
	FillType *fp;

	bool_t longPadPresent;

	Dz1SockAddr *dst;
} Dz1SockAddrFsmEnv;

typedef enum
{
	FsmRet_term = -1,
	FsmRet_ok,
	FsmRet_err
} FsmRet;

static Dz1Error L(Dz1SockAddrFsmEnv *e, str_t str)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (e->str) { ERR_SET_OUT(&err, EINVAL); }
	else if ((e->str = Dz1StrA_dup(str, &err)) == NULL) { ERR_OUT(&err); }
	return err;
}

static int h2i(char c)
{
	int ret = 0;
	if (c >= '0' && c <= '9') ret = c - '0';
	else if (c >= 'a' && c <= 'f') ret = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F') ret = c - 'A' + 10;
	return ret;
}

static int hex2i(str_t str)
{
	int ret = 0;
	char *cp = str;
	while(*cp)
	{
		if (isxdigit(*cp)) ret = (ret << 4) + h2i(*cp);
		cp++;
	}
//	Dz1Console_printf(NULL, 0, "hex2i() : %X\n", ret);
	return ret;
}

static Dz1Error C(Dz1SockAddrFsmEnv *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (e->remain == 0) { ERR_SET_OUT(&err, ENOMEM); }
	else
	{
		*e->fp++ = FillType_char;
		*e->cp++ = (u8_t)atoi(e->str); Dz1StrA_del(e->str); e->str = NULL;
		e->remain--;
	}
	return err;
}

static Dz1Error H(Dz1SockAddrFsmEnv *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (e->remain < 2) { ERR_SET_OUT(&err, ENOMEM); }
	else
	{
		*e->fp++ = FillType_short;
		*(u16_t *)e->cp = htons((u16_t)hex2i(e->str)); Dz1StrA_del(e->str); e->str = NULL;
		e->cp += sizeof(short);
		e->remain -= sizeof(short);
	}
	return err;
}

static Dz1Error P(Dz1SockAddrFsmEnv *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	*e->fp++ = FillType_longPad;
	return err;
}

static Dz1Error p(Dz1SockAddrFsmEnv *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	*e->fp++ = FillType_shortPad;
	return err;
}

static Dz1Error u(Dz1SockAddrFsmEnv *e)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (e->longPadPresent) { ERR_SET_OUT(&err, EEXIST); }
	else e->longPadPresent = TRUE;
	return err;
}
static ssize_t AddrBuild(u8_t dst[16], FillType *fp, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0, len;
	u8_t *cp = src, *dp = dst;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u8_t temp[16] = { 0, };

	memset(dst, 0, 16);

	for (; *fp != FillType_none && errp->code == 0; fp++)
	{
		switch(*fp)
		{
			case FillType_char:
				if (size) { *dp++ = *cp++; ret++; size--; }
				else { ERR_SET_OUT(errp, ENOMEM); ret = -1; }
				break;
			case FillType_short:
				if (size >= 2)
				{
					*(u16_t *)dp = *(u16_t *)cp;
					cp += sizeof(u16_t);
					dp += sizeof(u16_t);
					ret+= sizeof(u16_t);
					size -= sizeof(u16_t);
				}
				else { ERR_SET_OUT(errp, ENOMEM); ret = -1; }
				break;
			case FillType_shortPad:
				if (size) { *dp++ = '\0'; ret++; size--; }
				else { ERR_SET_OUT(errp, ENOMEM); ret = -1; }
				break;
			case FillType_longPad:
				fp++;
				if ((len = AddrBuild(temp, fp, cp, size, errp)) == -1) { ERR_OUT(errp); ret = -1; }
				else
				{
					dp = dst + 16 - len;
					memcpy(dp, temp, len);
					return 16;
				}
			default:
				ERR_SET_OUT(errp, EFAULT);
				break;
		}
	}
	return ret;
}

static Dz1Error XX(Dz1SockAddrFsmEnv *e)
{
	ssize_t len;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t temp[16] = { 0, };

	if ((len = AddrBuild(temp, e->fill, e->buf, 16, &err)) == -1) { ERR_OUT(&err); }
	else if (len == 4)
	{
		e->dst->ver = Dz1SocketVer_inet4;
		e->dst->x.addr4.sin_family = AF_INET;
		e->dst->x.addr4.sin_addr.s_addr = *(u32_t *)temp;
	}
	else if (len == 16)
	{
		e->dst->ver = Dz1SocketVer_inet6;
		e->dst->x.addr6.sin6_family = AF_INET6;
		memcpy(e->dst->x.addr6.sin6_addr.s6_addr, temp, 16);
	}
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static FsmRet L001(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = L(env, t)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_Branch;

	return ret;
}

static FsmRet L002(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = L(env, t)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv4_Dot;

	return ret;
}

static FsmRet L004(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = L(env, t)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Colon;

	return ret;
}

static FsmRet L009(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = L(env, t)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Local;

	return ret;
}

static FsmRet L010(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = L(env, t)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Dot;

	return ret;
}

static FsmRet C003(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = C(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv4_Num;

	return ret;
}

static __inline__ FsmRet H011(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = H(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Num;

	return ret;
}

static FsmRet C011(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = C(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Num;

	return ret;
}

static FsmRet Pu05(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = P(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = u(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Hex;

	return ret;
}

static __inline__ FsmRet p005(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = p(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Hex;

	return ret;
}

static FsmRet H005(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = H(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Hex;

	return ret;
}

static FsmRet Pu08(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = P(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = u(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_ELB;

	return ret;
}

static FsmRet HPu5(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = H(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = P(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = u(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else env->state = STATE_IPv6_Hex;

	return ret;
}

static FsmRet CXXt(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = C(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = XX(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else ret = FsmRet_term;

	return ret;
}

static FsmRet HXXt(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = H(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else if ((*errp = XX(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else ret = FsmRet_term;

	return ret;
}

static FsmRet XXtt(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err)
{
	FsmRet ret = FsmRet_ok;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((*errp = XX(env)).code) { ERR_OUT(errp); ret = FsmRet_err; }
	else ret = FsmRet_term;

	return ret;
}

typedef FsmRet (*FsmFunc)(Dz1SockAddrFsmEnv *env, str_t t, Dz1Error *err);

static FsmFunc fsm[STATE_max][EVENT_max] =
{
	{ NULL, L001, NULL, Pu05, Pu08 },
	{ NULL, NULL, C003, H005, NULL },
	{ CXXt, NULL, C003, NULL, NULL },
	{ NULL, L002, NULL, NULL, NULL },
	{ HXXt, NULL, C011, H005, HPu5 },
	{ NULL, L004, NULL, NULL, NULL },
	{ XXtt, L009, NULL, NULL, NULL },
	{ HXXt, NULL, C011, H005, NULL },
	{ CXXt, NULL, C011, NULL, NULL },
	{ NULL, L010, NULL, NULL, NULL },
};

typedef struct Dz1SockAddrToken
{
	EVENT e;
	str_t v;
} Dz1SockAddrToken;

static void Dz1SockAddrToken_del(Dz1SockAddrToken *p)
{
	if (!p) return;
	if (p->v) Dz1StrA_del(p->v);
	Dz1Free(p);
}

static void Dz1SockAddrToken_delAndSetNull(void *ptr)
{
	Dz1SockAddrToken **p = (Dz1SockAddrToken **)ptr;
	Dz1SockAddrToken_del(*p); *p = NULL;
}

static Dz1SockAddrToken *Dz1SockAddrToken_new(EVENT e, str_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockAddrToken *ret = (Dz1SockAddrToken *)Dz1Calloc(sizeof(Dz1SockAddrToken), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SockAddrToken_delAndSetNull, (void *)&ret);

		if (v && (ret->v = Dz1StrA_dup(v, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->e = e;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1SockAddrToken_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static str_t Dz1SockAddr_lex(str_t src, Dz1SockAddrToken **t, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char buf[1024], *dp = buf;
	char *cp = src;
	if (*cp)
	{
		while(*cp)
		{
			if (isxdigit(*cp))
			{
				while(*cp && isxdigit(*cp)) *dp++ = *cp++;
				*dp = '\0';

				if ((*t = Dz1SockAddrToken_new(EVENT_HexDigit, buf, errp)) == NULL) { ERR_OUT(errp); cp = NULL; }

				break;
			}
			else if (*cp == '.')
			{
				cp++;

				if ((*t = Dz1SockAddrToken_new(EVENT_Dot, NULL, errp)) == NULL) { ERR_OUT(errp); cp = NULL; }

				break;
			}
			else if (*cp == ':')
			{
				cp++;
				if (*cp == ':')
				{
					cp++;
					if ((*t = Dz1SockAddrToken_new(EVENT_DoubleColon, NULL, errp)) == NULL) { ERR_OUT(errp); cp = NULL; }
				}
				else
				{
					if ((*t = Dz1SockAddrToken_new(EVENT_Colon, NULL, errp)) == NULL) { ERR_OUT(errp); cp = NULL; }
				}

				break;
			}
			else
			{
				Dz1Error_set(errp, EINVAL);
				cp = NULL;
				break;
			}
		}
	}
	else
	{
		if ((*t = Dz1SockAddrToken_new(EVENT_Done, NULL, errp)) == NULL) { ERR_OUT(errp); }
	}

	return cp;
}

Dz1Error Dz1SockAddr_setAddrStr(Dz1SockAddr *p, str_t strIP)
{
	char *cp = strIP;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p == NULL || strIP == NULL || strIP[0] == 0) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		Dz1SockAddrFsmEnv env =
		{
			STATE_Initial,
			NULL,
			{ 0, },
			NULL,
			16,
			{ FillType_none, },
			NULL,
			FALSE,
			NULL
		};

		Dz1SockAddrToken *t = NULL;
		FsmRet status;
		FsmFunc func;

		env.cp = env.buf;
		env.fp = env.fill;
		env.dst = p;

		//Dz1Console_printf(NULL, 0, "Dz1SockAddr_setAddrStr() : str = %s\n", strIP);
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&env.str);
		do
		{
			cp = Dz1SockAddr_lex(cp, &t, errp);

			pthread_cleanup_push((Dz1CancelFunc)Dz1SockAddrToken_delAndSetNull, (void *)&t);

			if (t != NULL)
			{
				//Dz1Console_printf(NULL, 0, "Dz1SockAddr_setAddrStr() : S=%d, E=%d\n", env.state, t->e);

				if ((func = fsm[env.state][t->e]) == NULL) { ERR_SET_OUT(errp, EINVAL); status = FsmRet_err; }
				else if ((status = fsm[env.state][t->e](&env, t->v, errp)) == FsmRet_err) { ERR_OUT(errp); }
				// else if (status == FsmRet_term) { Dz1Console_printf(NULL, 0, "Done\n"); }
				func = func;
			}
			else
			{
//				ERR_OUT(errp);
				status = FsmRet_err;
			}

			pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1SockAddrToken_delAndSetNull, (void *)&t);
		}
		while(status == FsmRet_ok);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&env.str);
	}
	return err;
}
*/

///////////////////////////////////////////////////////////////////////////////
// SockAddr : IPv4 : Printable
static str_t _Dz1SockAddr4A_printable(u32_t ip, char buf[46], bool_t fullRange)
{
	if (fullRange)
		sprintf(buf, "%03d.%03d.%03d.%03d", (ip & 0xFF000000) >> 24, (ip & 0xFF0000) >> 16, (ip & 0xFF00) >> 8, ip & 0xFF);
	else
		sprintf(buf, "%d.%d.%d.%d", (ip & 0xFF000000) >> 24, (ip & 0xFF0000) >> 16, (ip & 0xFF00) >> 8, ip & 0xFF);
	return buf;
}

static str_t Dz1SockAddr4A_printable(struct sockaddr_in *p, char buf[46], bool_t fullRange, Dz1Error *errp)
{
	if (p->sin_family != AF_INET) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		u32_t ip = ntohl(p->sin_addr.s_addr);
		Dz1Error_set(errp, 0);
		return _Dz1SockAddr4A_printable(ip, buf, fullRange);
	}
	return NULL;
}

#ifndef UNIX_SYSTEM
static wstr_t _Dz1SockAddr4W_printable(u32_t ip, wchar_t buf[46], bool_t fullRange)
{
	if (fullRange)
		_std_snprintfW(buf, 46, L"%03d.%03d.%03d.%03d", (ip & 0xFF000000) >> 24, (ip & 0xFF0000) >> 16, (ip & 0xFF00) >> 8, ip & 0xFF);
	else
		_std_snprintfW(buf, 46, L"%d.%d.%d.%d", (ip & 0xFF000000) >> 24, (ip & 0xFF0000) >> 16, (ip & 0xFF00) >> 8, ip & 0xFF);
	return buf;
}

static wstr_t Dz1SockAddr4W_printable(struct sockaddr_in *p, wchar_t buf[46], bool_t fullRange, Dz1Error *errp)
{
	if (p->sin_family != AF_INET) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		u32_t ip = ntohl(p->sin_addr.s_addr);
		Dz1Error_set(errp, 0);
		return _Dz1SockAddr4W_printable(ip, buf, fullRange);
	}
	return NULL;
}
#endif
// SockAddr : IPv4 : Printable
///////////////////////////////////////////////////////////////////////////////
#ifdef DIMZ_SUPPORT_IPV6
///////////////////////////////////////////////////////////////////////////////
// SockAddr : IPv6 : Printable
static str_t Dz1SockAddr6A_printable(struct sockaddr_in6 *p, char buf[46], bool_t fullRange, Dz1Error *err) // modified by gm 20230601 - buf size 40 -> 46
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct in6_addr *in6 = &p->sin6_addr;
	if (p->sin6_family != AF_INET6) { ERR_SET_OUT(errp, EINVAL); }
	else if (IN6_IS_ADDR_V4MAPPED(in6))
	{
		//u32_t ip = ntohl(in6->s6_addr32[3]);
		u32_t ip = ntohl(*(u32_t *)(&(DZ1_IN6_ADDR8(in6)[12])));
		char *cp = buf;
		int len = sprintf(cp, ":FFFF:"); cp += len;
		_Dz1SockAddr4A_printable(ip, cp, fullRange);
		return buf;
	}
	else if (IN6_IS_ADDR_V4COMPAT(in6))
	{
		u32_t ip = ntohl(*(u32_t *)(&(DZ1_IN6_ADDR8(in6)[12])));
		//u32_t ip = ntohl(in6->s6_addr32[3]);
		return _Dz1SockAddr4A_printable(ip, buf, fullRange);
	}
	else
	{
		int i, len;
		char *cp = buf;
		bool_t printed = FALSE;
		for (i = 0; i <8; i++)
		{
			if (printed) { *cp++ = ':'; }
			if (fullRange)
				len = sprintf(cp, "%04X", ntohs(DZ1_IN6_ADDR16(in6)[i]));
			else
				len = sprintf(cp, "%X", ntohs(DZ1_IN6_ADDR16(in6)[i]));
			cp += len; 
			printed = TRUE;
		}
		return buf;
	}
	return NULL;
}
#ifndef UNIX_SYSTEM
static wstr_t Dz1SockAddr6W_printable(struct sockaddr_in6 *p, wchar_t buf[40], bool_t fullRange, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t sz = 40;
	struct in6_addr *in6 = &p->sin6_addr;
	if (p->sin6_family != AF_INET6) { ERR_SET_OUT(errp, EINVAL); }
	else if (IN6_IS_ADDR_V4MAPPED(in6))
	{
		//u32_t ip = ntohl(in6->s6_addr32[3]);
		u32_t ip = ntohl(*(u32_t *)(&(DZ1_IN6_ADDR8(in6)[12])));
		wchar_t *cp = buf;
		int len = _std_snprintfW(cp, sz, L":FFFF:");
		cp += len;
		sz -= len;
		_Dz1SockAddr4W_printable(ip, cp, fullRange);
		return buf;
	}
	else if (IN6_IS_ADDR_V4COMPAT(in6))
	{
		u32_t ip = ntohl(*(u32_t *)(&(DZ1_IN6_ADDR8(in6)[12])));
		//u32_t ip = ntohl(in6->s6_addr32[3]);
		return _Dz1SockAddr4W_printable(ip, buf, fullRange);
	}
	else
	{
		int i, len;
		wchar_t *cp = buf;
		bool_t printed = FALSE;
		for (i = 0; i <8; i++)
		{
			if (printed) 
			{
				*cp++ = L':';
				sz--;
			}

			if (fullRange)
				len = _std_snprintfW(cp, sz, L"%04X", ntohs(DZ1_IN6_ADDR16(in6)[i]));
			else
				len = _std_snprintfW(cp, sz, L"%X", ntohs(DZ1_IN6_ADDR16(in6)[i]));
			cp += len; 
			sz -= len;
			printed = TRUE;
		}
		return buf;
	}
	return NULL;
}
#endif
// SockAddr : IPv6 : Printable
///////////////////////////////////////////////////////////////////////////////
#endif

Dz1SocketVer *Dz1SocketVer_new(Dz1SocketVer *v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketVer *ret = NULL;
	
	if (v == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SocketVer *)Dz1Calloc(sizeof(Dz1SocketVer), 1, errp)) == NULL) ERR_OUT(errp);
	else { *ret = *v; Dz1Error_set(errp, 0); }
	return ret;
}

bool_t Dz1SocketVer_copy(Dz1SocketVer *dst, Dz1SocketVer *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		*dst = *src;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

Dz1SocketVer *Dz1SocketVer_clone(Dz1SocketVer *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SocketVer *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1SocketVer_new(src, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

int Dz1SocketVer_cmp(Dz1SocketVer *a, Dz1SocketVer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if (*a < *b) ret = -1;
	else if (*a > *b) ret = 1;
	return ret;
}

typedef struct Dz1SocketVerAMap
{
	Dz1SocketVer	v;
	str_t			name;
} Dz1SocketVerAMap;
static Dz1SocketVerAMap dz1SocketVerAMap[] =
{
	{ Dz1SocketVer_inet4, "ipV4" },
#ifdef DIMZ_SUPPORT_IPV6
	{ Dz1SocketVer_inet6, "ipV6" },
#endif
	{ Dz1SocketVer_max, NULL }
};
str_t Dz1SocketVerStrA(Dz1SocketVer v)
{
	Dz1SocketVerAMap *i;
	for (i = dz1SocketVerAMap; i->v != Dz1SocketVer_max; i++)
		if (i->v == v) break;
	return i->name;
}
Dz1SocketVer Dz1SocketVerFromStrA(str_t str)
{
	Dz1SocketVerAMap *i;
	for (i = dz1SocketVerAMap; i->v != Dz1SocketVer_max; i++)
		if (strcmp(i->name, str) == 0) break;
	return i->v;
}
void Dz1SocketVerA_dump(Dz1SocketVer *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%s(%d)\n", Dz1SocketVerStrA(*p), *p);
}
void Dz1SocketVerA_fdump(FILE *fp, Dz1SocketVer *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%s(%d)\n", Dz1SocketVerStrA(*p), *p);
}
#ifndef UNIX_SYSTEM
typedef struct Dz1SocketVerWMap
{
	Dz1SocketVer	v;
	wstr_t			name;
} Dz1SocketVerWMap;
static Dz1SocketVerWMap dz1SocketVerWMap[] =
{
	{ Dz1SocketVer_inet4, L"ipV4" },
#ifdef DIMZ_SUPPORT_IPV6
	{ Dz1SocketVer_inet6, L"ipV6" },
#endif
	{ Dz1SocketVer_max, NULL }
};
wstr_t Dz1SocketVerStrW(Dz1SocketVer v)
{
	Dz1SocketVerWMap *i;
	for (i = dz1SocketVerWMap; i->v != Dz1SocketVer_max; i++)
		if (i->v == v) break;
	return i->name;
}
Dz1SocketVer Dz1SocketVerFromStrW(wstr_t str)
{
	Dz1SocketVerWMap *i;
	for (i = dz1SocketVerWMap; i->v != Dz1SocketVer_max; i++)
		if (wcscmp(i->name, str) == 0) break;
	return i->v;
}
void Dz1SocketVerW_dump(Dz1SocketVer *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%s(%d)\n", Dz1SocketVerStrW(*p), *p);
}
void Dz1SocketVerW_fdump(FILE *fp, Dz1SocketVer *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%s(%d)\n", Dz1SocketVerStrW(*p), *p);
}
#endif
///////////////////////////////////////////////////////////////////////////////
// SockAddr : Basic
Dz1SockAddr *_Dz1SockAddr_clone(Dz1SockAddr *p, Dz1Error *err, const char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SockAddr *ret = (Dz1SockAddr *)_Dz1Malloc(sizeof(Dz1SockAddr), errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret, p, sizeof(Dz1SockAddr));
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1SockAddr_del(Dz1SockAddr *p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1SockAddrA_dump(Dz1SockAddr *p, int tab)
{
	char buf[53];
	if (!p) return;
	Dz1ThreadA_printf("%s\n", Dz1SockAddrA_printable(p, buf, FALSE, NULL));
}
#ifndef UNIX_SYSTEM
void Dz1SockAddrW_dump(Dz1SockAddr *p, int tab)
{
	wchar_t buf[53];
	if (!p) return;
	Dz1ThreadW_printf(L"%s\n", Dz1SockAddrW_printable(p, buf, FALSE, NULL));
}
#endif
int Dz1SockAddr_cmp(Dz1SockAddr *a, Dz1SockAddr *b)
{
	char A[53], B[53];
	Dz1SockAddr_printable(a, A, TRUE, NULL);
	Dz1SockAddr_printable(b, B, TRUE, NULL);
	return strcmp(A, B);
}

static bool_t Dz1SockAddr_isValid4(struct sockaddr_in *p)
{
	bool_t ret = FALSE;
	u8_t temp[sizeof(p->sin_addr)] = { 0, };
	if (memcpy(&p->sin_addr, temp, sizeof(struct in_addr)) != 0 && p->sin_port != 0) ret = TRUE;
	return ret;
}
#ifdef DIMZ_SUPPORT_IPV6
static bool_t Dz1SockAddr_isValid6(struct sockaddr_in6 *p)
{
	bool_t ret = FALSE;
	u8_t temp[sizeof(p->sin6_addr)] = { 0, };
	if (memcpy(&p->sin6_addr, temp, sizeof(p->sin6_addr)) != 0 && p->sin6_port != 0) ret = FALSE;
	return ret;
}
#endif
bool_t Dz1SockAddr_isValid(Dz1SockAddr *p)
{
	bool_t ret = FALSE;
	switch(p->ver)
	{
	case Dz1SocketVer_inet4: ret = Dz1SockAddr_isValid4(&p->x.addr4); break;
#ifdef DIMZ_SUPPORT_IPV6
	case Dz1SocketVer_inet6: ret = Dz1SockAddr_isValid6(&p->x.addr6); break;
#endif
	default: break;
	}
	return ret;
}
// SockAddr : Basic
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Printable
//           1         2         3         4         5
// 012345678901234567890123456789012345678901234567890123
// XXXX:XXXX:XXXX:XXXX:XXXX:XXXX:ddd.ddd.ddd.ddd(65535)
str_t Dz1SockAddrA_printable(Dz1SockAddr *p, char buf[53], bool_t fullRange, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char temp[46];
	memset(temp, 0, 46);
	if (!Dz1SocketVerIsValid(p->ver)) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		switch (p->ver)
		{
			case Dz1SocketVer_inet4:
				if (Dz1SockAddr4A_printable(&p->x.addr4, temp, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { sprintf(buf, "%s^%u", temp, ntohs(p->x.addr4.sin_port)); return buf; }
				break;
#ifdef DIMZ_SUPPORT_IPV6
			case Dz1SocketVer_inet6:
				if (Dz1SockAddr6A_printable(&p->x.addr6, temp, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { sprintf(buf, "%s^%u", temp, ntohs(p->x.addr6.sin6_port)); return buf; }
				break;
#endif
			default:
				break;
		}
	}
	return NULL;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1SockAddrW_printable(Dz1SockAddr *p, wchar_t buf[53], bool_t fullRange, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wchar_t temp[46];
	memset(temp, 0, sizeof(temp));
	if (!Dz1SocketVerIsValid(p->ver)) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		switch (p->ver)
		{
			case Dz1SocketVer_inet4:
				if (Dz1SockAddr4W_printable(&p->x.addr4, temp, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { _std_snprintfW(buf, 52, L"%s^%u", temp, ntohs(p->x.addr4.sin_port)); return buf; }
				break;
#ifdef DIMZ_SUPPORT_IPV6
			case Dz1SocketVer_inet6:
				if (Dz1SockAddr6W_printable(&p->x.addr6, temp, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { _std_snprintfW(buf, 52, L"%s^%u", temp, ntohs(p->x.addr6.sin6_port)); return buf; }
				break;
#endif
			default:
				break;
		}
	}
	return NULL;
}
#endif

str_t Dz1SockAddrA_printableNoPort(Dz1SockAddr *p, char buf[53], bool_t fullRange, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	char temp[46];
	memset(temp, 0, 46);
	if (!Dz1SocketVerIsValid(p->ver)) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		switch (p->ver)
		{
			case Dz1SocketVer_inet4:
				if (Dz1SockAddr4A_printable(&p->x.addr4, buf, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { return buf; }
				break;
#ifdef DIMZ_SUPPORT_IPV6
			case Dz1SocketVer_inet6:
				if (Dz1SockAddr6A_printable(&p->x.addr6, buf, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { return buf; }
				break;
#endif
			default:
				break;
		}
	}
	return NULL;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1SockAddrW_printableNoPort(Dz1SockAddr *p, wchar_t buf[53], bool_t fullRange, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	wchar_t temp[46];
	memset(temp, 0, sizeof(wchar_t) * 46);
	if (!Dz1SocketVerIsValid(p->ver)) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		switch (p->ver)
		{
			case Dz1SocketVer_inet4:
				if (Dz1SockAddr4W_printable(&p->x.addr4, buf, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { return buf; }
				break;
#ifdef DIMZ_SUPPORT_IPV6
			case Dz1SocketVer_inet6:
				if (Dz1SockAddr6W_printable(&p->x.addr6, buf, fullRange, errp) == NULL) { ERR_OUT(errp); }
				else { return buf; }
				break;
#endif
			default:
				break;
		}
	}
	return NULL;
}
#endif
// SockAddr : Printable
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SockAddr : IPv4 : Address Set
bool_t _Dz1SockAddr_setAddr4LE(Dz1SockAddr *p, u32_t ip4le, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t ip4host = Dz1Endian4_little2host(ip4le);
	u32_t ip4be = Dz1Endian4_host2big(ip4host);
	if (_Dz1SockAddr_setAddr4BE(p, ip4be, errp) == FALSE) ERR_OUT(errp);

	return errp->code == 0 ? TRUE : FALSE;
}

bool_t _Dz1SockAddr_setAddr4BE(Dz1SockAddr *p, u32_t ip4be, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	p->ver = Dz1SocketVer_inet4;

	memset(&p->x.addr4, 0, sizeof(struct sockaddr_in));

	p->x.addr4.sin_family = AF_INET;
	p->x.addr4.sin_addr.s_addr = ip4be;

	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1SockAddr_setAddr4LE(Dz1SockAddr *p, u32_t ip4le)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1SockAddr_setAddr4LE(p, ip4le, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1SockAddr_setAddr4BE(Dz1SockAddr *p, u32_t ip4be)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1SockAddr_setAddr4BE(p, ip4be, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// Dz1SockAddr : IPv4 : Address Set
///////////////////////////////////////////////////////////////////////////////
#ifdef DIMZ_SUPPORT_IPV6
///////////////////////////////////////////////////////////////////////////////
// Dz1SockAddr : IPv6 : Address Set
bool_t _Dz1SockAddr_setAddr6(Dz1SockAddr *p, u16_t ip6[8], Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
#ifdef DIMZ_SUPPORT_IPV6
	p->ver = Dz1SocketVer_inet6;

	memset(&p->x.addr6, 0, sizeof(struct sockaddr_in6));

	p->x.addr6.sin6_family = AF_INET6;
	memcpy(p->x.addr6.sin6_addr.s6_addr, ip6, 16);
	Dz1Error_set(errp, 0);
#else
	Dz1Error_set(errp, ENOSYS);
#endif
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1SockAddr_setAddr6(Dz1SockAddr *p, u16_t ip6[8])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1SockAddr_setAddr6(p, ip6, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Dz1SockAddr : IPv6 : Address Set
///////////////////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////////////////////
// Dz1SockAddr : Get Address
Dz1Error Dz1SockAddr_getAddr(Dz1SockAddr *p, u8_t *dst, size_t *size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p || !dst || !size) { ERR_SET_OUT(&err, EINVAL); }
	else
	{
		switch(p->ver)
		{
		case Dz1SocketVer_inet4:
			if (*size < 4) ERR_SET_OUT(&err, E2BIG);
			else
			{
				u32_t temp = ntohl(p->x.addr4.sin_addr.s_addr);
				memcpy(dst,&temp, 4);
				*size = 4;
			}
			break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6:
			if (*size < 16) ERR_SET_OUT(&err, E2BIG);
			else
			{
				memcpy(dst, &p->x.addr6.sin6_addr, 16);
				*size = 16;
			}
			break;
#endif
		default:
			break;
		}
	}
	return err;
}
// Dz1SockAddr : Get Address
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Set Address by FQDN
Dz1Error Dz1SockAddrU_setAddrByName(Dz1SockAddr *dst, str_t fqdn)
{	// UTF-8 version
	DZ1_ERROR_SAFE_VAR(errp, err);
	struct hostent *he = NULL;
	
	if (dst == NULL || fqdn == NULL || fqdn[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((he = gethostbyname(fqdn)) == NULL)
	{
#ifdef UNIX_SYSTEM
		ERR_SET_OUT(&err, errno);
#else
		int status = WSAGetLastError();
		ERR_SET_OUT(&err, status);
#endif
	}
	else
	{
		char temp[16] = { 0, };
		memcpy(temp, he->h_addr_list[0], he->h_length);
		if (he->h_addrtype == AF_INET)
		{
			u32_t ipv4 = *(u32_t *)temp;
			Dz1SockAddr_setAddr4(dst, Dz1Endian4_big2host(ipv4));
		}
#ifdef DIMZ_SUPPORT_IPV6
		else if (he->h_addrtype == AF_INET6)
		{
			Dz1SockAddr_setAddr6(dst, (u16_t *)temp);
		}
#else
		else Dz1Error_set(errp, ENOSYS);
#endif
		Dz1SockAddr_setPort(dst, 0);
	}
	return err;
}

Dz1Error Dz1SockAddrA_setAddrByName(Dz1SockAddr *dst, str_t fqdn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char *utf8 = (char *)Dz1String_conv(fqdn, strlen(fqdn) * sizeof(char), DZ1_SYSTEM_MBCS_CHARSET, "UTF-8", NULL);
	if (utf8 == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((*errp = Dz1SockAddrU_setAddrByName(dst, utf8)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1SockAddrW_setAddrByName(Dz1SockAddr *dst, wstr_t fqdn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char *utf8 = (char *)Dz1String_conv(fqdn, wcslen(fqdn) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, "UTF-8", NULL);
	if (utf8 == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((*errp = Dz1SockAddrU_setAddrByName(dst, utf8)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return err;
}
#endif
// SockAddr : Set Address by FQDN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Set Address Unified
#ifndef DIMZ_SUPPORT_IPV6
static bool_t _parse_ip_strA(Dz1SockAddr *dst, const char *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t dot = 0;
	const char *sp = src;
	while(*sp)
	{
		if (*sp == '.') dot++;
		sp++;
	}
	if (dot == 0)
	{	// ipv6
		Dz1Error_set(errp, ENOSYS);
	}
	else if (dot != 3) Dz1Error_set(errp, EINVAL);
	else
	{
		Dz1IPv4 ip = 0;
		u32_t v = 0;
		char dig[16], *dp = dig;
		sp = src;
		while(errp->code == 0 && dot > 0 && *sp)
		{
			if (isdigit(*sp)) *dp++ = *sp;
			else if (*sp == '.')
			{
				dot--;
				*dp = 0;
				if ((v = Dz1Ato32(dig)) > 255) Dz1Error_set(errp, EINVAL);
				else
				{
					ip = (ip << 8) | v;
					dp = dig;
				}
			}
			sp++;
		}

		if (errp->code == 0)
		{
			if ((v = Dz1Ato32((char *)sp)) > 255) Dz1Error_set(errp, EINVAL);
			else
			{
				ip = (ip << 8) | v;
				Dz1SockAddr_setAddr4(dst, ip);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
static bool_t _parse_ip_strW(Dz1SockAddr *dst, const wchar_t *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u32_t dot = 0;
	const wchar_t *sp = src;
	while(*sp)
	{
		if (*sp == L'.') dot++;
		sp++;
	}
	if (dot == 0)
	{	// ipv6
		Dz1Error_set(errp, ENOSYS);
	}
	else if (dot != 3) Dz1Error_set(errp, EINVAL);
	else
	{
		Dz1IPv4 ip = 0;
		u32_t v = 0;
		wchar_t dig[16], *dp = dig;
		sp = src;
		while(errp->code == 0 && dot > 0 && *sp)
		{
			if (iswdigit(*sp)) *dp++ = *sp;
			else if (*sp == L'.')
			{
				dot--;
				*dp = 0;
				if ((v = Dz1Wto32(dig)) > 255) Dz1Error_set(errp, EINVAL);
				else
				{
					ip = (ip << 8) | v;
					dp = dig;
				}
			}
			sp++;
		}

		if (errp->code == 0)
		{
			if ((v = Dz1Wto32((wchar_t *)sp)) > 255) Dz1Error_set(errp, EINVAL);
			else
			{
				ip = (ip << 8) | v;
				Dz1SockAddr_setAddr4(dst, ip);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
#endif

Dz1Error Dz1SockAddrA_setAddrStr(Dz1SockAddr *p, str_t str)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef DIMZ_SUPPORT_IPV6
	u8_t temp[32] = { 0, };
	if (inet_pton(AF_INET, str, (void *)&temp))
	{	// IPv4 convention
		u32_t ipv4_be = *(u32_t *)temp;
		if (_Dz1SockAddr_setAddr4BE(p, ipv4_be, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (inet_pton(AF_INET6, str, &temp))
	{	// IPv6 convention
		u16_t *ipv6_be = (u16_t *)temp;
		if (_Dz1SockAddr_setAddr6(p, ipv6_be, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
#else
	if (_parse_ip_strA(p, str, NULL) == TRUE) { }
#endif
	// FQDN convention
	else if ((*errp = Dz1SockAddrA_setAddrByName(p, str)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1SockAddrW_setAddrStr(Dz1SockAddr *p, wstr_t str)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifdef DIMZ_SUPPORT_IPV6
	u8_t temp[32] = { 0, };
	if (InetPtonW(AF_INET, str, &temp))
	{	// IPv4 convention
		u32_t ipv4_be = *(u32_t *)temp;
		if (_Dz1SockAddr_setAddr4BE(p, ipv4_be, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
		else if (InetPtonW(AF_INET6, str, &temp))
	{	// IPv6 convention
		u16_t *ipv6_be = (u16_t *)temp;
		if (_Dz1SockAddr_setAddr6(p, ipv6_be, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
#else
	if (_parse_ip_strW(p, str, NULL) == TRUE) { }
#endif
	// FQDN convention
	else if ((*errp = Dz1SockAddrW_setAddrByName(p, str)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
#endif
// SockAddr : Set Address Unified
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Port
bool_t _Dz1SockAddr_setPort(Dz1SockAddr *p, u16_t  port, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	switch(p->ver)
	{
		case Dz1SocketVer_inet4:
			p->x.addr4.sin_port = htons(port);
			Dz1Error_set(errp, 0);
			break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6:
			p->x.addr6.sin6_port = htons(port);
			Dz1Error_set(errp, 0);
			break;
#endif
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t _Dz1SockAddr_getPort(Dz1SockAddr *p, u16_t *port, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (!p || !port) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		switch(p->ver)
		{
			case Dz1SocketVer_inet4:
				*port = ntohs(p->x.addr4.sin_port);
				Dz1Error_set(errp, 0);
				break;
#ifdef DIMZ_SUPPORT_IPV6
			case Dz1SocketVer_inet6:
				*port = ntohs(p->x.addr6.sin6_port);
				Dz1Error_set(errp, 0);
				break;
#endif
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Error Dz1SockAddr_setPort(Dz1SockAddr *p, u16_t port)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1SockAddr_setPort(p, port, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1SockAddr_getPort(Dz1SockAddr *p, u16_t *port)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1SockAddr_getPort(p, port, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1SockAddrA_setPortStr(Dz1SockAddr *p, str_t strPort)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	u32_t port = (u32_t)Dz1Ato32(strPort);

	if (port == 0 && strcmp(strPort, "0") != 0)
	{
		if ((*errp = Dz1SockAddrA_setPortByName(p, strPort)).code)
			ERR_SET_OUT(errp, EINVAL);
	}
	else if ((*errp = Dz1SockAddr_setPort(p, port)).code) ERR_OUT(errp);

	return err;
}

Dz1Error Dz1SockAddrW_setPortStr(Dz1SockAddr *p, wstr_t strPort)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t port = (u32_t)Dz1Wto32(strPort);

	if (port == 0 && wcscmp(strPort, L"0") != 0)
	{
		if ((*errp = Dz1SockAddrW_setPortByName(p, strPort)).code)
			ERR_SET_OUT(errp, EINVAL);
	}
	else if ((*errp = Dz1SockAddr_setPort(p, port)).code) ERR_OUT(errp);

	return err;
}
#endif

Dz1Error Dz1SockAddrU_setPortByName(Dz1SockAddr *dst, str_t service)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	struct servent *se = getservbyname(service, NULL);
	if (se == NULL)
	{
#ifdef UNIX_SYSTEM
		ERR_SET_OUT(&err, errno);
#else
		int status = WSAGetLastError();
		ERR_SET_OUT(&err, status);
#endif
	}
	else if ((err = Dz1SockAddr_setPort(dst, se->s_port)).code) ERR_OUT(&err);
	return err;
}
#ifndef UNIX_SYSTEM
Dz1Error Dz1SockAddrA_setPortByName(Dz1SockAddr *dst, str_t service)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char *utf8 = (char *)Dz1String_conv(service, strlen(service), DZ1_SYSTEM_MBCS_CHARSET, "UTF-8", NULL);
	if (utf8 == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((*errp = Dz1SockAddrU_setPortByName(dst, utf8)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return err;
}

Dz1Error Dz1SockAddrW_setPortByName(Dz1SockAddr *dst, wstr_t service)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char *utf8 = (char *)Dz1String_conv(service, wcslen(service) * sizeof(wchar_t), DZ1_SYSTEM_WIDE_CHARSET, "UTF-8", NULL);
	if (utf8 == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)utf8);
		if ((*errp = Dz1SockAddrU_setPortByName(dst, utf8)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)utf8);
	}
	return err;
}
#endif
// SockAddr : Port
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1SockAddr_setAddrZero(Dz1SockAddr *dst, Dz1SockAddr *ref_addr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u16_t ip6[8] = { 0, };
		Dz1SocketVer ver = Dz1SocketVer_inet4;
		if (ref_addr != NULL) ver = ref_addr->ver;
		switch(ver)
		{
		default:
		case Dz1SocketVer_inet4:
			if ((*errp = Dz1SockAddr_setAddr4(dst, 0)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SockAddr_setPort(dst, 0)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1SocketVer_inet6:
			if ((*errp = Dz1SockAddr_setAddr6(dst, ip6)).code) ERR_OUT(errp);
			else if ((*errp = Dz1SockAddr_setPort(dst, 0)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SockAddr_setZeroAddr(Dz1SockAddr *dst, Dz1SocketVer ver, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		memset(dst, 0, sizeof(Dz1SockAddr));
		dst->ver = ver;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

///////////////////////////////////////////////////////////////////////////////
// Dz1SockAddr : Version Convert
Dz1Error Dz1SockAddr_6to4(Dz1SockAddr *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}

Dz1Error Dz1SockAddr_4to6(Dz1SockAddr *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}
// Dz1SockAddr : Version Convert
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classic API support
int Dz1SockAddr_getAddrLen(Dz1SockAddr *p, Dz1Error *err)
{
	int ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(p->ver)
		{
		case Dz1SocketVer_inet4: ret = sizeof(p->x.addr4); break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6: ret = sizeof(p->x.addr6); break;
#endif
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return ret;
}

int Dz1SockAddr_getAddrFamily(Dz1SockAddr *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(p->ver)
		{
		case Dz1SocketVer_inet4: ret = AF_INET; break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6: ret = AF_INET6; break;
#endif
		default: ERR_SET_OUT(errp, EFAULT);
		}
	}
	return ret;
}

// Classic API support
///////////////////////////////////////////////////////////////////////////////

// Dz1Error Dz1SockAddr_resolv(Dz1SockAddr *dst, str_t fqdn)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	if ((*errp = Dz1SockAddr_setAddrByName(dst, fqdn)).code)
// 	{
// 		if ((*errp = Dz1SockAddr_setAddrStr(dst, fqdn)).code) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 	}
// 	return err;
// }

///////////////////////////////////////////////////////////////////////////////
// SockAddr : CODEC
ssize_t Dz1SockAddr_save(Dz1SockAddr *p, FILE *fp, Dz1Error *err)
{
	u16_t port;
	ssize_t ret = 0;
	u8_t buf[16] = { 0, };
	size_t size = 16;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!p || !fp) DZ1_STDIO_ERRSET_RET(errp, EINVAL);
	else if ((*errp = Dz1SockAddr_getPort(p, &port)).code) DZ1_STDIO_ERR_RET(errp);
	else if ((*errp = Dz1SockAddr_getAddr(p, buf, &size)).code) DZ1_STDIO_ERR_RET(errp);
	else
	{
		ssize_t status;

		if (p->ver == Dz1SocketVer_inet4)
		{
			Dz1IPv4 *ip = (Dz1IPv4 *)buf;
			Dz1Endian4_host2big((*ip));
		}
#ifdef DIMZ_SUPPORT_IPV6
		else if (p->ver == Dz1SocketVer_inet6)
		{
			u16_t *ip6 = (u16_t *)buf, i;
			for (i = 0; i < 8; i++) ip6[i] = Dz1Endian2_host2big(ip6[i]);
		}
#endif
		else DZ1_STDIO_ERRSET_RET(errp, ENOSYS);

		DZ1_WRITE2(fp, port, status, ret, errp);
		DZ1_WRITE1(fp, (u8_t)p->ver, status, ret, errp);
		DZ1_WRITE(fp, buf, 16, status, ret, errp);
	}
	return ret;
}

ssize_t Dz1SockAddr_load(Dz1SockAddr *p, FILE *fp, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t buf[16] = { 0, };
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!p || !fp) DZ1_STDIO_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t temp;
		u16_t port;
		Dz1IPv4 *ip = NULL;
#ifdef DIMZ_SUPPORT_IPV6
		u16_t *ip6, i;
#endif
		ssize_t status;
		DZ1_READ2(fp, &port, status, ret, errp);
		DZ1_READ1(fp, &temp, status, ret, errp);
		p->ver = (Dz1SocketVer)temp;
		if ((*errp = Dz1SockAddr_setPort(p, port)).code) DZ1_STDIO_ERR_RET(errp);

		DZ1_READ(fp, buf, 16, status, ret, errp);

		switch(p->ver)
		{
		case Dz1SocketVer_inet4:
			ip = (Dz1IPv4 *)buf;
			Dz1Endian4_big2host((*ip));
			Dz1SockAddr_setAddr4(p, (*ip));
			break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6:
			ip6 = (u16_t *)buf;
			for (i = 0; i < 8; i++) ip6[i] = Dz1Endian2_big2host(ip6[i]);
			Dz1SockAddr_setAddr6(p, ip6);
			break;
#endif
		default:
			DZ1_STDIO_ERRSET_RET(errp, EFAULT);
			break;
		}
	}
	return ret;
}

ssize_t Dz1SockAddr_enc(u8_t *dst, size_t size, Dz1SockAddr *src, Dz1Error *err)
{
	u16_t port;
	ssize_t ret = 0;
	u8_t buf[16] = { 0, };
	size_t _size = 16;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!src) DZ1_STDIO_ERRSET_RET(errp, EINVAL);
	else if ((*errp = Dz1SockAddr_getPort(src, &port)).code) DZ1_STDIO_ERR_RET(errp);
	else if ((*errp = Dz1SockAddr_getAddr(src, buf, &_size)).code) DZ1_STDIO_ERR_RET(errp);
	else
	{
		u8_t *cp = dst;
		if (src->ver == Dz1SocketVer_inet4)
		{
			Dz1IPv4 *ip = (Dz1IPv4 *)buf;
			Dz1Endian4_host2big((*ip));
		}
#ifdef DIMZ_SUPPORT_IPV6
		else if (src->ver == Dz1SocketVer_inet6)
		{
			u16_t *ip6 = (u16_t *)buf, i;
			for (i = 0; i < 8; i++) ip6[i] = Dz1Endian2_host2big(ip6[i]);
		}
#endif
		else DZ1_STDIO_ERRSET_RET(errp, ENOSYS);

		DZ1_ENCODE2(cp, size, port, errp, ret);
		DZ1_ENCODE1(cp, size, (u8_t)src->ver, errp, ret);
		DZ1_ENCODE(cp, size, buf, 16, errp, ret);
	}
	return ret;
}

ssize_t Dz1SockAddr_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	u8_t buf[16] = { 0, };
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!dst || !src) DZ1_STDIO_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t temp, *cp = src;
		u16_t port;
		Dz1IPv4 *ip = NULL;
#ifdef DIMZ_SUPPORT_IPV6
		u16_t *ip6, i;
#endif
		DZ1_DECODE2(&port, cp, size, errp, ret);

		DZ1_DECODE1(&temp, cp, size, errp, ret);
		dst->ver = (Dz1SocketVer)temp;
		if ((*errp = Dz1SockAddr_setPort(dst, port)).code) DZ1_STDIO_ERR_RET(errp);

		DZ1_DECODE(buf, 16, cp, size, errp, ret);

		switch(dst->ver)
		{
		case Dz1SocketVer_inet4:
			ip = (Dz1IPv4 *)buf;
			Dz1Endian4_big2host((*ip));
			Dz1SockAddr_setAddr4(dst, (*ip));
			break;
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6:
			ip6 = (u16_t *)buf;
			for (i = 0; i < 8; i++) ip6[i] = Dz1Endian2_big2host(ip6[i]);
			Dz1SockAddr_setAddr6(dst, ip6);
			break;
#endif
		default:
			DZ1_STDIO_ERRSET_RET(errp, EFAULT);
			break;
		}
	}
	return ret;
}
// SockAddr : CODEC
///////////////////////////////////////////////////////////////////////////////

