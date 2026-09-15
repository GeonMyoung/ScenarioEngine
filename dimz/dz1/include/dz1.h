#ifndef DZ1_H
#define DZ1_H

#define USE_CODECONV

#define DZ1_ENDIAN_BIG			1
#define DZ1_ENDIAN_LITTLE		2

///////////////////////////////////////////////////////////////////////////////
// Endian Choice
#if defined(__SYSTEM_ENDIAN_BIG__)
#define DZ1_ENDIAN				DZ1_ENDIAN_BIG
#elif defined(__SYSTEM_ENDIAN_LITTLE__)
#define DZ1_ENDIAN				DZ1_ENDIAN_LITTLE
#else
#error "should define either __SYSTEM_ENDIAN_BIG__ or __SYSTEM_ENDIAN_LITTLE__"
#endif
// Endian Choice
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// WORD Size
#ifndef __WORDSIZE

#error "Unknown Word Size..."

#else	// __WORDSIZE

#	if __WORDSIZE == 32
#		define DZ1_PTR_SIZE						4
#		define DZ1_PTR_SIZED_PRINTF				"%08lX"
#		define DZ1_PTR_SIZED_TYPE				unsigned long
#	elif __WORDSIZE == 64
#		define DZ1_PTR_SIZE						8
#		define DZ1_PTR_SIZED_PRINTF				"%016llX"
#		define DZ1_PTR_SIZED_TYPE				unsigned long long int
#	endif

#endif	// __WORDSIZE
// WORD Size
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// UNIX or NOT?
#if !defined(WIN32) && !defined(__BORLANDC__)
	#define UNIX_SYSTEM
#else
	#undef UNIX_SYSTEM

	#if defined(__BORLANDC__)
	#	ifndef WIN32
	#		define WIN32
	#	endif
	#endif
#endif
// UNIX or NOT?
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// C++ naming convention rule
#ifdef __cplusplus
#define DZ1_CPPLINK				extern "C"
#define DZ1_CPPLINK_VAR			extern "C"
#else
#define DZ1_CPPLINK
#define DZ1_CPPLINK_VAR			extern
#endif

#ifndef DZ1_CPPLINK
#error link!!!
#endif
// C++ naming convention rule
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// WIN32 Part
///////////////////////////////////////////////////////////////////////////////
#if defined(WIN32)

#include <dz1_win32.h>
//#include <dz1_non_unix.h>

///////////////////////////////////////////////////////////////////////////////
// LINUX Part
///////////////////////////////////////////////////////////////////////////////
#elif defined(LINUX)
#include <dz1_unix.h>

///////////////////////////////////////////////////////////////////////////////
// SUN Part
///////////////////////////////////////////////////////////////////////////////
#elif defined(SUN)
#include <dz1_unix.h>

///////////////////////////////////////////////////////////////////////////////
// Apple OSX Part
///////////////////////////////////////////////////////////////////////////////
#elif defined(MAC_OS_X)
#include <dz1_unix.h>
#else
#error "No platform defined $BDS" $BDS RAD
#endif

#include <dz1_conf.h>		// configuration on each platform

///////////////////////////////////////////////////////////////////////////////
// Post-COMMON Part
///////////////////////////////////////////////////////////////////////////////
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

typedef void (*OutputHook)(void *ptr, unsigned char *data, size_t size);
DZ1_CPPLINK void Dz1OutputHook_set(OutputHook func, void *param);

#define DZ1_PATH_FILE_STR_LEAST_SIZE		64
#define DZ1_PATH_FILE_STR_ALIGNER			(sizeof(void *) - (DZ1_PATH_FILE_STR_LEAST_SIZE % sizeof(void *)))
#define DZ1_PATH_FILE_STR_SIZE				(DZ1_PATH_FILE_STR_LEAST_SIZE + DZ1_PATH_FILE_STR_ALIGNER)

#define DZ1_PTR_TYPE						void *

///////////////////////////////////////////////////////////////////////////////
// WORD SIZE Part
///////////////////////////////////////////////////////////////////////////////
//-->ldg::c:
//#define __DZ1PTR(var)						((DZ1_PTR_SIZED_TYPE)var)
//
//#define DZ1_ALIGN_SIZE						sizeof(DZ1_PTR_SIZED_TYPE)
//#define __DZ1ALIGN(type, name)				type name; unsigned char __##name##__[DZ1_ALIGN_SIZE - (sizeof(type) % DZ1_ALIGN_SIZE)]
//#define __DZ1VAL(val)						(val), { 0, }
//#define DZ1_ALIGNED_SIZE(sz)				(sz + (DZ1_ALIGN_SIZE - (sz % DZ1_ALIGN_SIZE)))
//DZ1_ALIGN_SIZE Á¤ÀÇ
#ifndef __DZ1_ALIGN_SIZE__
#define __DZ1_ALIGN_SIZE__
#define __DZ1PTR(var)						((DZ1_PTR_SIZED_TYPE)var)

#define DZ1_ALIGN_SIZE						sizeof(DZ1_PTR_SIZED_TYPE)
#define __DZ1ALIGN(type, name)				type name; unsigned char __##name##__[DZ1_ALIGN_SIZE - (sizeof(type) % DZ1_ALIGN_SIZE)]
#define __DZ1VAL(val)						(val), { 0, }
#define DZ1_ALIGNED_SIZE(sz)				(sz + (DZ1_ALIGN_SIZE - (sz % DZ1_ALIGN_SIZE)))
#endif
//<--ldg::c:

typedef unsigned char	 u8_t;
typedef			 char	 s8_t;
typedef unsigned short	 u16_t;
typedef			 short	 s16_t;
typedef unsigned int	 u32_t;
typedef			 int	 s32_t;
typedef char			*str_t;
typedef wchar_t			*wstr_t;

typedef int				 bool_t;

typedef float			 real32_t;
typedef double			 real64_t;
#define real_t			 real64_t

typedef void (*Dz1CancelFunc)(void *p);
typedef void (*Dz1DelFunc)(void *p);
typedef int  (*Dz1CmpFunc)(void *a, void *b);
typedef void (*Dz1DumpFunc)(void *p, int tab);
typedef void (*Dz1FDumpFunc)(FILE *fp, void *p, int tab);

#define DZ1_TAB_STR_A		"    "

#ifndef UNIX_SYSTEM
#define DZ1_TAB_STR_W		L"    "
#endif // UNIXSYSTEM

#define DZ1_TAB_STR_LEN		4

#define DZ1_SYSTEM_UTF8_CHARSET				"UTF-8"
#define DZ1_SYSTEM_UTF8_CHARSET_BOM			((u8_t *)"\xEF\xBB\xBF")
#define DZ1_SYSTEM_UTF8_CHARSET_BOM_SZ		3

#define DZ1_SYSTEM_EUCKR_CHARSET			"EUC-KR"
#define DZ1_SYSTEM_EUCKR_CHARSET_BOM		((u8_t *)"")
#define DZ1_SYSTEM_EUCKR_CHARSET_BOM_SZ		0

#define DZ1_SYSTEM_UCS16BE_CHARSET			"UCS-2BE"
#define DZ1_SYSTEM_UCS16BE_CHARSET_BOM		((u8_t *)"\xFE\xFF")

#define DZ1_SYSTEM_UCS16LE_CHARSET			"UCS-2LE"
#define DZ1_SYSTEM_UCS16LE_CHARSET_BOM		((u8_t *)"\xFF\xFE")

#define DZ1_SYSTEM_UCS16_CHARSET_BOM_SZ		2

/////////////////////////////////
// Char-set Setting
#ifdef UNIX_SYSTEM

#define DZ1_SYSTEM_MBCS_CHARSET				DZ1_SYSTEM_UTF8_CHARSET
#define DZ1_SYSTEM_MBCS_CHARSET_BOM			DZ1_SYSTEM_UTF8_CHARSET_BOM
#define DZ1_SYSTEM_MBCS_CHARSET_BOM_SZ		DZ1_SYSTEM_UTF8_CHARSET_BOM_SZ

#define DZ1_SYSTEM_CHARSET					DZ1_SYSTEM_MBCS_CHARSET
#define DZ1_SYSTEM_CHARSET_BOM				DZ1_SYSTEM_MBCS_CHARSET_BOM				// modified by gm 20231023 -- for UNIX_SYSTEM
#define DZ1_SYSTEM_CHARSET_BOM_SZ			DZ1_SYSTEM_MBCS_CHARSET_BOM_SZ			// modified by gm 20231023 -- for UNIX_SYSTEM

#else // UNIX_SYSTEM

#define DZ1_SYSTEM_MBCS_CHARSET				DZ1_SYSTEM_EUCKR_CHARSET
#define DZ1_SYSTEM_MBCS_CHARSET_BOM			DZ1_SYSTEM_EUCKR_CHARSET_BOM
#define DZ1_SYSTEM_MBCS_CHARSET_BOM_SZ		DZ1_SYSTEM_EUCKR_CHARSET_BOM_SZ

#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
#define DZ1_SYSTEM_WIDE_CHARSET				DZ1_SYSTEM_UCS16BE_CHARSET
#define DZ1_SYSTEM_WIDE_CHARSET_BOM			DZ1_SYSTEM_UCS16BE_CHARSET_BOM
#elif DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
#define DZ1_SYSTEM_WIDE_CHARSET				DZ1_SYSTEM_UCS16LE_CHARSET
#define DZ1_SYSTEM_WIDE_CHARSET_BOM			DZ1_SYSTEM_UCS16LE_CHARSET_BOM
#else // DZ1_ENDIAN
#error "No Endian"
#endif // DZ1_ENDIAN
#define DZ1_SYSTEM_WIDE_CHARSET_BOM_SZ		DZ1_SYSTEM_UCS16_CHARSET_BOM_SZ

#ifdef UNICODE
#define DZ1_SYSTEM_CHARSET					DZ1_SYSTEM_WIDE_CHARSET
#define DZ1_SYSTEM_CHARSET_BOM				DZ1_SYSTEM_WIDE_CHARSET_BOM
#define DZ1_SYSTEM_CHARSET_BOM_SZ			DZ1_SYSTEM_WIDE_CHARSET_BOM_SZ
#else // UNICODE
#define DZ1_SYSTEM_CHARSET					DZ1_SYSTEM_MBCS_CHARSET
#define DZ1_SYSTEM_CHARSET_BOM				DZ1_SYSTEM_MBCS_CHARSET_BOM
#define DZ1_SYSTEM_CHARSET_BOM_SZ			DZ1_SYSTEM_MBCS_CHARSET_BOM_SZ
#endif // UNICODE
#endif // UNIX_SYSTEM
// Charset Setting
/////////////////////////////////

#endif

