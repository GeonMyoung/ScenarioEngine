#ifndef DZ1_SOCK_ADDR_H
#define DZ1_SOCK_ADDR_H

#include <dz1_error.h>

#define DIMZ_SUPPORT_IPV6

#if !defined(UNIX_SYSTEM)
#ifdef DIMZ_SUPPORT_IPV6
#	include <ws2ipdef.h>
#endif
#define DZ1_IN6_ADDR8(p)			((p)->u.Byte)
#define DZ1_IN6_ADDR16(p)			((p)->u.Word)
#else
#	include <netinet/in.h>
#	ifdef s6_addr
#		define DZ1_IN6_ADDR8(p)			((p)->s6_addr)
#	else
#		define DZ1_IN6_ADDR8(p)			((p)->s6_addr8)
#	endif	// s6_addr
#	ifdef MAC_OS_X
#		define s6_addr16				__u6_addr.__u6_addr16
#	endif
#	define DZ1_IN6_ADDR16(p)			((p)->s6_addr16)
#endif	// !defined(UNIX_SYSTEM)
#include <dz1_int.h>

///////////////////////////////////////////////////////////////////////////////
// IPv4
typedef u32_t Dz1IPv4;
static __inline__ Dz1IPv4		*Dz1IPv4_new(Dz1IPv4 v, Dz1Error *err) { return Dz1u32_new(v, err); }
static __inline__ void			*Dz1IPv4_gen(Dz1Error *err) { return Dz1IPv4_new(0, err); }
static __inline__ Dz1IPv4		*Dz1IPv4_clone(Dz1IPv4 *src, Dz1Error *err) { return Dz1u32_clone(src, err); }
static __inline__ void			 Dz1IPv4_del(Dz1IPv4 *v) { Dz1u32_del(v); }
static __inline__ void			 Dz1IPv4_delAndSetNull(void *ptr) { Dz1u32_delAndSetNull(ptr); }

DZ1_CPPLINK	 DZ1_DLLPORT void	 Dz1IPv4A_dump(Dz1IPv4 *p, int tab);
DZ1_CPPLINK	 DZ1_DLLPORT void	 Dz1IPv4A_fdump(FILE *fp, Dz1IPv4 *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK	 DZ1_DLLPORT void	 Dz1IPv4W_dump(Dz1IPv4 *p, int tab);
DZ1_CPPLINK	 DZ1_DLLPORT void	 Dz1IPv4W_fdump(FILE *fp, Dz1IPv4 *p, int tab);
#ifdef UNICODE
#define							 Dz1IPv4_dump		Dz1IPv4W_dump
#define							 Dz1IPv4_fdump		Dz1IPv4W_fdump
#else // UNICODE
#define							 Dz1IPv4_dump		Dz1IPv4A_dump
#define							 Dz1IPv4_fdump		Dz1IPv4A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1IPv4_dump		Dz1IPv4A_dump
#define							 Dz1IPv4_fdump		Dz1IPv4A_fdump
#endif // UNIX_SYSTEM

static __inline__ int			 Dz1IPv4_cmp(Dz1IPv4 *a, Dz1IPv4 *b) { return Dz1u32_cmp(a, b); }

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1IPv4_enc(u8_t *dst, size_t size, Dz1IPv4 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1IPv4_dec(Dz1IPv4 *dst, u8_t *src, size_t size, Dz1Error *err);

#define Dz1IPv2Val				Dz1IPv4VAL
#define Dz1IPv4VAL(a,b,c,d)		((((u32_t)(a)) << 24) | (((u32_t)(b)) << 16) | (((u32_t)(c)) << 8) | ((u32_t)(d)))

#define Dz1IPv4FMT				"%u.%u.%u.%u"
#define Dz1IPv4ARG(v32)			(((v32) >> 24) & 0xFF), (((v32) >> 16) & 0xFF), (((v32) >> 8)&0xFF), ((v32) & 0xFF)

DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Ipv4A_toStr(char *dst, size_t dst_sz, Dz1IPv4 src);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Ipv4W_toStr(wchar_t *dst, size_t dst_sz, Dz1IPv4 src);
#ifdef UNICODE
#define							 Dz1Ipv4_toStr		Dz1Ipv4W_toStr
#define							 Dz1IPv4_printable	Dz1Ipv4W_toStr
#else	// UNICODE
#define							 Dz1Ipv4_toStr		Dz1Ipv4A_toStr
#define							 Dz1IPv4_printable	Dz1Ipv4A_toStr
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define							 Dz1Ipv4_toStr		Dz1Ipv4A_toStr
#define							 Dz1IPv4_printable	Dz1Ipv4A_toStr
#endif	// UNIX_SYSTEM
// IPv4
///////////////////////////////////////////////////////////////////////////////

#ifdef DIMZ_SUPPORT_IPV6
///////////////////////////////////////////////////////////////////////////////
// IPv6
typedef struct Dz1IPv6
{
	u16_t		addr[8];
} Dz1IPv6;
#define DZ1_IPv6_INITIALIZER	{ 0, }

DZ1_CPPLINK DZ1_DLLPORT Dz1IPv6	*Dz1IPv6_new(u16_t addr[8], Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1IPv6 *Dz1IPv6_newA(u16_t a0, u16_t a1, u16_t a2, u16_t a3, u16_t a4, u16_t a5, u16_t a6, u16_t a7, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1IPv6_gen(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1IPv6 *Dz1IPv6_clone(Dz1IPv6 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1IPv6_del(Dz1IPv6 *p);
static __inline__ void			 Dz1IPv6_delAndSetNull(void *ptr)
{
	Dz1IPv6 **p = (Dz1IPv6 **)ptr;
	Dz1IPv6_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1IPv6A_dump(Dz1IPv6 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1IPv6A_fdump(FILE *fp, Dz1IPv6 *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1IPv6W_dump(Dz1IPv6 *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1IPv6W_fdump(FILE *fp, Dz1IPv6 *p, int tab);
#ifdef UNICODE
#define							 Dz1IPv6_dump		Dz1IPv6W_dump
#define							 Dz1IPv6_fdump		Dz1IPv6W_fdump
#else // UNICODE
#define							 Dz1IPv6_dump		Dz1IPv6A_dump
#define							 Dz1IPv6_fdump		Dz1IPv6A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1IPv6_dump		Dz1IPv6A_dump
#define							 Dz1IPv6_fdump		Dz1IPv6A_fdump
#endif // UNIX_SYSTEM
static __inline__ int			 Dz1IPv6_cmp(Dz1IPv6 *a, Dz1IPv6 *b) { return memcmp(a, b, sizeof(Dz1IPv6)); }

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1IPv6_enc(u8_t *dst, size_t size, Dz1IPv6 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1IPv6_dec(Dz1IPv6 *dst, u8_t *src, size_t size, Dz1Error *err);

// 0000:1111:2222:3333:4444:5555:6666:7777
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1IPv6A_printable(Dz1IPv6 *p, char buf[46], bool_t isFullRange); // modified by gm 20230601 - buf size 40 -> 46
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1IPv6W_printable(Dz1IPv6 *p, wchar_t buf[40], bool_t isFullRange);
#ifdef UNICODE
#define							 Dz1IPv6_printable		Dz1IPv6W_printable
#else	// UNICODE
#define							 Dz1IPv6_printable		Dz1IPv6A_printable
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define							 Dz1IPv6_printable		Dz1IPv6A_printable
#endif	// UNIX_SYSTEM
// IPv6
///////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////
// SockAddr
typedef enum
{
	Dz1SocketVer_inet4,
#ifdef DIMZ_SUPPORT_IPV6
	Dz1SocketVer_inet6,
#endif
	Dz1SocketVer_max = 99
} Dz1SocketVer;
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketVer	*Dz1SocketVer_new(Dz1SocketVer *v, Dz1Error *err);
static __inline__		Dz1SocketVer	*Dz1SocketVer_gen(Dz1Error *err) { Dz1SocketVer v = Dz1SocketVer_max; return Dz1SocketVer_new(&v, err); }
static __inline__ void					 Dz1SocketVer_del(Dz1SocketVer *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void					 Dz1SocketVer_delAndSetNull(void *pptr)
{
	Dz1SocketVer **p = (Dz1SocketVer **)pptr;
	if (p) { Dz1SocketVer_del(*p); *p = NULL; }
}

DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1SocketVer_copy(Dz1SocketVer *dst, Dz1SocketVer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketVer	*Dz1SocketVer_clone(Dz1SocketVer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT int				 Dz1SocketVer_cmp(Dz1SocketVer *a, Dz1SocketVer *b);

DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1SocketVerStrA(Dz1SocketVer v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketVer	 Dz1SocketVerFromStrA(str_t str);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketVerA_dump(Dz1SocketVer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketVerA_fdump(FILE *fp, Dz1SocketVer *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1SocketVerStrW(Dz1SocketVer v);
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketVer	 Dz1SocketVerFromStrW(wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketVerW_dump(Dz1SocketVer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketVerW_fdump(FILE *fp, Dz1SocketVer *p, int tab);
#ifdef UNICODE
#define									 Dz1SocketVerStr				Dz1SocketVerStrW
#define									 Dz1SocketVerFromStr			Dz1SocketVerFromStrW
#define									 Dz1SocketVer_dump				Dz1SocketVerW_dump
#define									 Dz1SocketVer_fdump				Dz1SocketVerW_fdump
#else	// UNICODE
#define									 Dz1SocketVerStr				Dz1SocketVerStrA
#define									 Dz1SocketVerFromStr			Dz1SocketVerFromStrA
#define									 Dz1SocketVer_dump				Dz1SocketVerA_dump
#define									 Dz1SocketVer_fdump				Dz1SocketVerA_fdump
#endif	// UNUCODE
#else	// UNIX_SYSTEM
#define									 Dz1SocketVerStr				Dz1SocketVerStrA
#define									 Dz1SocketVerFromStr			Dz1SocketVerFromStrA
#define									 Dz1SocketVer_dump				Dz1SocketVerA_dump
#define									 Dz1SocketVer_fdump				Dz1SocketVerA_fdump
#endif	// UNIX_SYSTEM
typedef struct
{
	__DZ1ALIGN(Dz1SocketVer, ver);
	union
	{
		struct sockaddr_in addr4;
#ifdef DIMZ_SUPPORT_IPV6
		struct sockaddr_in6 addr6;
#endif
		char ptr[1];
	} x;
} Dz1SockAddr;

#define								 Dz1SockAddr_clone(ptr, errp)		_Dz1SockAddr_clone((ptr), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT Dz1SockAddr *_Dz1SockAddr_clone(Dz1SockAddr *p, Dz1Error *err, const char *__file__, int __line__);
static __inline__ void				 Dz1SockAddr_purge(Dz1SockAddr *p) { }
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1SockAddr_del(Dz1SockAddr *p);
static __inline__ void				 Dz1SockAddr_delAndSetNull(void *ptr)
{
	Dz1SockAddr **p = (Dz1SockAddr **)ptr;
	Dz1SockAddr_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1SockAddrA_dump(Dz1SockAddr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1SockAddrW_dump(Dz1SockAddr *p, int tab);
#ifdef UNICODE
#define								 Dz1SockAddr_dump			Dz1SockAddrW_dump
#else // UNICODE
#define								 Dz1SockAddr_dump			Dz1SockAddrA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1SockAddr_dump			Dz1SockAddrA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int			 Dz1SockAddr_cmp(Dz1SockAddr *a, Dz1SockAddr *b);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1SockAddr_isValid(Dz1SockAddr *p);
// SockAddr
///////////////////////////////////////////////////////////////////////////////

static __inline__ bool_t			 Dz1SocketVerIsValid(Dz1SocketVer v)
{
	switch(v)
	{
		case Dz1SocketVer_inet4: 
#ifdef DIMZ_SUPPORT_IPV6
		case Dz1SocketVer_inet6: 
#endif
			return TRUE;
		default: return FALSE;
	}
}

#define								 Dz1SockAddr_setAddrFqdn		Dz1SockAddr_setAddrS

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Address Part
DZ1_CPPLINK DZ1_DLLPORT bool_t		 _Dz1SockAddr_setAddr4LE(Dz1SockAddr *p, u32_t ip4le, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 _Dz1SockAddr_setAddr4BE(Dz1SockAddr *p, u32_t ip4be, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_setAddr4LE(Dz1SockAddr *p, u32_t ip4le);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_setAddr4BE(Dz1SockAddr *p, u32_t ip4be);
#ifdef DIMZ_SUPPORT_IPV6
DZ1_CPPLINK DZ1_DLLPORT bool_t		 _Dz1SockAddr_setAddr6(Dz1SockAddr *p, u16_t ip6[8], Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_setAddr6(Dz1SockAddr *p, u16_t ip6[8]);
#endif
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_getAddr(Dz1SockAddr *p, u8_t *dst, size_t *size);

#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
#define Dz1SockAddr_setAddr4		 Dz1SockAddr_setAddr4LE
#elif DZ1_ENDIAN == DZ1_ENDIAN_BIG
#define Dz1SockAddr_setAddr4		 Dz1SockAddr_setAddr4BE
#endif
// SockAddr : Address Part
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Set Address by String
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrU_setAddrByName(Dz1SockAddr *dst, str_t fqdn_utf8);		// gethostbyname(core)
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrA_setAddrByName(Dz1SockAddr *dst, str_t fqdn);			// gethostbyname(MBCS)
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrA_setAddrStr(Dz1SockAddr *p, str_t str);				// str = fqdn string or "192.168.0.1"
#define								 Dz1SockAddrA_getByName			Dz1SockAddrA_setAddrByName
#define								 Dz1SockAddrA_resolv			Dz1SockAddrA_setAddrByName

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrW_setAddrByName(Dz1SockAddr *dst, wstr_t fqdn);			// gethostbyname(WIDE)
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrW_setAddrStr(Dz1SockAddr *p, wstr_t str);				// str = fqdn string or "192.168.0.1"
#define								 Dz1SockAddrW_getByName			Dz1SockAddrW_setAddrByName
#define								 Dz1SockAddrW_resolv			Dz1SockAddrW_setAddrByName
#ifdef UNICODE
#define								 Dz1SockAddr_setAddrByName		Dz1SockAddrW_setAddrByName
#define								 Dz1SockAddr_setAddrStr			Dz1SockAddrW_setAddrStr
#define								 Dz1SockAddr_getByName			Dz1SockAddrW_getByName
#define								 Dz1SockAddr_resolv				Dz1SockAddrW_resolv
#define								 Dz1SockAddr_setAddrS			Dz1SockAddrW_setAddrStr
#else	// UNICODE
#define								 Dz1SockAddr_setAddrByName		Dz1SockAddrA_setAddrByName
#define								 Dz1SockAddr_setAddrStr			Dz1SockAddrA_setAddrStr
#define								 Dz1SockAddr_getByName			Dz1SockAddrA_getByName
#define								 Dz1SockAddr_resolv				Dz1SockAddrA_resolv
#define								 Dz1SockAddr_setAddrS			Dz1SockAddrA_setAddrStr
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define								 Dz1SockAddr_setAddrByName		Dz1SockAddrU_setAddrByName
#define								 Dz1SockAddr_setAddrStr			Dz1SockAddrU_setAddrByName
#define								 Dz1SockAddr_getByName			Dz1SockAddrU_getByName
#define								 Dz1SockAddr_resolv				Dz1SockAddrU_resolv
#define								 Dz1SockAddr_setAddrS			Dz1SockAddrU_setAddrByName
#endif	// UNIX_SYSTEM
// SockAddr : Set Address by String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SockAddr : Port Part
DZ1_CPPLINK DZ1_DLLPORT bool_t		_Dz1SockAddr_setPort(Dz1SockAddr *p, u16_t  port, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		_Dz1SockAddr_getPort(Dz1SockAddr *p, u16_t *port, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_setPort(Dz1SockAddr *p, u16_t port);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_getPort(Dz1SockAddr *p, u16_t *port);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrU_setPortByName(Dz1SockAddr *dst, str_t service_utf8);	// getservbyname(code)

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrA_setPortStr(Dz1SockAddr *p, str_t strPort);			// str = service_name or "356"
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrA_setPortByName(Dz1SockAddr *dst, str_t service);		// getservbyname(MBCS)

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrW_setPortStr(Dz1SockAddr *p, wstr_t strPort);			// str = service_name or "356"
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddrW_setPortByName(Dz1SockAddr *dst, wstr_t service);		// getservbyname(WIDE)
#ifdef UNICODE
#define								 Dz1SockAddr_setPortStr			Dz1SockAddrW_setPortStr
#define								 Dz1SockAddr_setPortByName		Dz1SockAddrW_setPortByName
#else	// UNICODE
#define								 Dz1SockAddr_setPortStr			Dz1SockAddrA_setPortStr
#define								 Dz1SockAddr_setPortByName		Dz1SockAddrA_setPortByName
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define								 Dz1SockAddr_setPortStr			Dz1SockAddrU_setPortStr
#define								 Dz1SockAddr_setPortByName		Dz1SockAddrU_setPortByName
#endif	// UNIX_SYSTEM
// SockAddr : Port Part
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1SockAddr_setAddrZero(Dz1SockAddr *dst, Dz1SockAddr *ref_addr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1SockAddr_setZeroAddr(Dz1SockAddr *dst, Dz1SocketVer ver, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_6to4(Dz1SockAddr *p);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1SockAddr_4to6(Dz1SockAddr *p);

DZ1_CPPLINK DZ1_DLLPORT int			 Dz1SockAddr_getAddrLen(Dz1SockAddr *p, Dz1Error *err);		// classic api support
DZ1_CPPLINK DZ1_DLLPORT int			 Dz1SockAddr_getAddrFamily(Dz1SockAddr *p, Dz1Error *err);	// classic api support

DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1SockAddrA_printable(Dz1SockAddr *p, char buf[53], bool_t fullRange, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1SockAddrA_printableNoPort(Dz1SockAddr *p, char buf[53], bool_t fullRange, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1SockAddrW_printable(Dz1SockAddr *p, wchar_t buf[53], bool_t fullRange, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1SockAddrW_printableNoPort(Dz1SockAddr *p, wchar_t buf[53], bool_t fullRange, Dz1Error *err);
#ifdef UNICODE
#define								 Dz1SockAddr_printable				Dz1SockAddrW_printable
#define								 Dz1SockAddr_printableNoPort		Dz1SockAddrW_printableNoPort
#else	// UNICODE
#define								 Dz1SockAddr_printable				Dz1SockAddrA_printable
#define								 Dz1SockAddr_printableNoPort		Dz1SockAddrA_printableNoPort
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define								 Dz1SockAddr_printable				Dz1SockAddrA_printable
#define								 Dz1SockAddr_printableNoPort		Dz1SockAddrA_printableNoPort
#endif	// UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1SockAddr_save(Dz1SockAddr *p, FILE *fp, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1SockAddr_load(Dz1SockAddr *p, FILE *fp, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1SockAddr_enc(u8_t *dst, size_t size, Dz1SockAddr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1SockAddr_dec(Dz1SockAddr *dst, u8_t *src, size_t size, Dz1Error *err);

#endif
