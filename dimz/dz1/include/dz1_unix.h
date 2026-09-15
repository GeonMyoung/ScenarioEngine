#ifndef DZ1_UNIX_H
#define DZ1_UNIX_H
// UNIX Type OS Common
#ifdef UNIX_SYSTEM

#include <stdint.h>
#include <unistd.h>
#include <wchar.h>
#include <sys/time.h>
#include <sys/types.h>
#include <ctype.h>
#include <wctype.h>

////////////////////////////////////////////////////////////////////////////////
// DLL Port
#define DZ1_DLLPORT
// DLL Port
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Path Seprator
#define DIR_SEPRATOR_A			"/"
#define DIR_SEPRATOR_W			L"/"

#define DIR_SEP_A				'/'
#define DIR_SEP_W				L'/'

#ifdef UNICODE
#define DIR_SEP					DIR_SEP_W
#define DIR_SEPRATOR			DIR_SEPRATOR_W
#else
#define DIR_SEP					DIR_SEP_A
#define DIR_SEPRATOR			DIR_SEPRATOR_A
#endif
// Path Seprator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CHAR Wider
#define DZ1WIDER(x)			L ## x
#define DZ1WIDER2(x)		DZ1WIDER(x)

#ifdef UNICODE
#define Dz1T(x)				DZ1WIDER(x)
#else
#define Dz1T(x)				x
#endif
// CHAR Wider
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// constant integer value post-fix
#define DZ1INT64(v)				v##LL
#define DZ1SINT64(v)			v##LL
#define DZ1UINT64(v)			v##LLU
// constant integer value post-fix
////////////////////////////////////////////////////////////////////////////////

#if (__WORDSIZE==32)
///////////////////////////////////////////////////////////////////////////////
// 64-bit type define in 32-bit system
typedef unsigned long long		u64_t;
typedef			 long long		s64_t;
// 64-bit type define in 32-bit system
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// integer32 <-> pointer casting macro in 32bit system
#define DZ1_PTR2VAL32(p)		((u32_t)(p))
#define DZ1_VAL2PTR32(v)		(v)
// integer32 <-> pointer casting macro in 32bit system
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format in 32bit system
#define DZ1U64FMT				"llu"
#define DZ1S64FMT				"lld"
#define DZ1X64FMT				"llX"

#define DZ1_FMT64_A				"%lld"
#define DZ1_FMT64U_A			"%llu"
#define DZ1_FMT64X_A			"%llX"

#define DZ1_FMT64F_A(dgt)		"%" #dgt "lld"
#define DZ1_FMT64UF_A(dgt)		"%" #dgt "llu"
#define DZ1_FMT64XF_A(dgt)		"%" #dgt "llX"

#define DZ1_FMT64_W				L"%lld"
#define DZ1_FMT64U_W			L"%llu"
#define DZ1_FMT64X_W			L"%llX"

#define DZ1_FMT64F_W(dgt)		L"%" L#dgt L"lld"
#define DZ1_FMT64UF_W(dgt)		L"%" L#dgt L"llu"
#define DZ1_FMT64XF_W(dgt)		L"%" L#dgt L"llX"
// 64-bit integer print format in 32bit system
///////////////////////////////////////////////////////////////////////////////

#elif (__WORDSIZE==64)
///////////////////////////////////////////////////////////////////////////////
// 64-bit type define in 64-bit system
typedef unsigned long			u64_t;
typedef			 long			s64_t;
// 64-bit type define in 64-bit system
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// integer32 <-> pointer casting macro in 64bit system
#define DZ1_PTR2VAL32(ptr)		((u32_t)((u64_t)(ptr) & 0xFFFFFFFF))
#define DZ1_VAL2PTR32(val)		(((u64_t)(val)) & 0xFFFFFFFF)
// integer32 <-> pointer casting macro in 64bit system
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format in 64bit system
#define DZ1U64FMT				"lu"
#define DZ1S64FMT				"ld"
#define DZ1X64FMT				"lX"

#define DZ1_FMT64_A				"%ld"
#define DZ1_FMT64U_A			"%lu"
#define DZ1_FMT64X_A			"%lX"

#define DZ1_FMT64F_A(dgt)		"%" #dgt "ld"
#define DZ1_FMT64UF_A(dgt)		"%" #dgt "lu"
#define DZ1_FMT64XF_A(dgt)		"%" #dgt "lX"

#define DZ1_FMT64_W				L"%ld"
#define DZ1_FMT64U_W			L"%lu"
#define DZ1_FMT64X_W			L"%lX"

#define DZ1_FMT64F_W(dgt)		L"%" L#dgt L"ld"
#define DZ1_FMT64UF_W(dgt)		L"%" L#dgt L"lu"
#define DZ1_FMT64XF_W(dgt)		L"%" L#dgt L"lX"
// 64-bit integer print format in 64bit system
///////////////////////////////////////////////////////////////////////////////

#endif

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format normalizer
#ifdef UNICODE
#define DZ1_FMT64				DZ1_FMT64_W
#define DZ1_FMT64U				DZ1_FMT64U_W
#define DZ1_FMT64X				DZ1_FMT64X_W

#define DZ1_FMT64F(dgt)			DZ1_FMT64F_W(dgt)
#define DZ1_FMT64UF(dgt)		DZ1_FMT64UF_W(dgt)
#define DZ1_FMT64XF(dgt)		DZ1_FMT64XF_W(dgt)
#else // UNICODE
#define DZ1_FMT64				DZ1_FMT64_A
#define DZ1_FMT64U				DZ1_FMT64U_A
#define DZ1_FMT64X				DZ1_FMT64X_A

#define DZ1_FMT64F(dgt)			DZ1_FMT64F_A(dgt)
#define DZ1_FMT64UF(dgt)		DZ1_FMT64UF_A(dgt)
#define DZ1_FMT64XF(dgt)		DZ1_FMT64XF_A(dgt)
#endif // UNICODE
// 64-bit integer print format normalizer
///////////////////////////////////////////////////////////////////////////////

#ifdef UNICODE
typedef wchar_t					 TCHAR;
typedef wchar_t					 Dz1Letter;
typedef wchar_t					*Dz1Str;
#define Dz1Text(astr)			 DZ1WIDER2(astr)
#else // UNICODE
typedef char					 TCHAR;
typedef char					 Dz1Letter;
typedef char					*Dz1Str;
#define Dz1Text(astr)			 astr
#endif // UNICODE

#define TRUE			1
#define FALSE			0

#include <libgen.h>
#define basenameA				basename
#define _std_snprintfA			snprintf
#define Dz1GetEnv				getenv

#endif // UNIX_SYSTEM

#endif
