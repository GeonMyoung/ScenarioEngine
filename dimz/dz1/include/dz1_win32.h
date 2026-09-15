#ifndef DZ1_WIN32_H
#define DZ1_WIN32_H

#if defined(WIN32)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <sys/types.h>

////////////////////////////////////////////////////////////////////////////////
// DLL Port
#if defined(DIMZ_DZ1_IS_DLL)
#	if defined(DZ1_BUILD)
#		define DZ1_DLLPORT					__declspec(dllexport)
#	else
#		define DZ1_DLLPORT					__declspec(dllimport)
#	endif
#else
#	define DZ1_DLLPORT
#endif
// DLL Port
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Path Seprator
#define DIR_SEPRATOR_A			"\\"
#define DIR_SEPRATOR_W			L"\\"

#define DIR_SEP_A				'\\'
#define DIR_SEP_W				L'\\'

#ifdef UNICODE
#define DIR_SEP					DIR_SEP_W
#define DIR_SEPRATOR			DIR_SEPRATOR_W
#else // UNICODE
#define DIR_SEP					DIR_SEP_A
#define DIR_SEPRATOR			DIR_SEPRATOR_A
#endif // UNICODE
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
#define DZ1INT64(v)				v##i64
#define DZ1SINT64(v)			v##i64
#define DZ1UINT64(v)			v##ui64
// constant integer value post-fix
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 64-bit type define
typedef unsigned __int64 u64_t;
typedef          __int64 s64_t;
// 64-bit type define
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// integer32 <-> pointer casting macro in 32bit system
#define DZ1_PTR2VAL32(ptr)      (DWORD_PTR)(ptr)
#define DZ1_VAL2PTR32(val)      (DWORD_PTR)(val)
// integer32 <-> pointer casting macro in 32bit system
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// inline macro
#define __inline__      __inline
// inline macro
////////////////////////////////////////////////////////////////////////////////

#if defined(__BORLANDC__)
// Borland-C IDE definitions
#include <dz1_win32_cpp_builder.h>

#else	// !defined(__BORLANDC__)
// MS Visual Studio IDE definitions
#include <dz1_win32_msvc.h>
#endif // !defined(__BORLANDC__)

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format normalizer
#ifdef UNICODE
#define DZ1_FMT64               DZ1_FMT64_W
#define DZ1_FMT64U              DZ1_FMT64U_W
#define DZ1_FMT64X              DZ1_FMT64X_W

#define DZ1_FMT64F(dgt)         DZ1_FMT64F_W(dgt)
#define DZ1_FMT64UF(dgt)        DZ1_FMT64UF_W(dgt)
#define DZ1_FMT64XF(dgt)        DZ1_FMT64XF_W(dgt)
#else // UNICODE
#define DZ1_FMT64               DZ1_FMT64_A
#define DZ1_FMT64U              DZ1_FMT64U_A
#define DZ1_FMT64X              DZ1_FMT64X_A

#define DZ1_FMT64F(dgt)         DZ1_FMT64F_A(dgt)
#define DZ1_FMT64UF(dgt)        DZ1_FMT64UF_A(dgt)
#define DZ1_FMT64XF(dgt)        DZ1_FMT64XF_A(dgt)
#endif // UNICODE
// 64-bit integer print format normalizer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// basename macro for Windows
static __inline__ char		*basenameA(char *src) { char *ret = strrchr(src, DIR_SEP_A); return ret ? ++ret : src; }
static __inline__ wchar_t	*basenameW(wchar_t *src) { wchar_t *ret = wcsrchr(src, DIR_SEP_W); return ret ? ++ret : src; }

#ifdef UNICODE
#define		basename				 basenameW
#define		Dz1GetEnv				 _wgetenv
#else  // UNICODE
#define		basename				 basenameA
#define		Dz1GetEnv				 getenv
#endif // UNICODE
// basename macro for Windows
///////////////////////////////////////////////////////////////////////////////

#define _std_sprintfA			sprintf
#define _std_snprintfA			_snprintf

#define _std_sprintfW			_swprintf
#define _std_snprintfW			_snwprintf

#ifdef UNICODE
typedef wchar_t					 Dz1Letter;
typedef wchar_t					*Dz1Str;
#define Dz1Text(astr)			 DZ1WIDER2(astr)
#else	// UNICODE
typedef char					 Dz1Letter;
typedef char					*Dz1Str;
#define Dz1Text(astr)			 astr
#endif	// UNICODE
#endif	// WIN32

#endif // DZ1_WIN32_H
