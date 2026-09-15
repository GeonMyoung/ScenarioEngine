#ifndef DZ1_MSVC_WIN32_H
#define DZ1_MSVC_WIN32_H

///////////////////////////////////////////////////////////////////////////////
// MSVC Part
///////////////////////////////////////////////////////////////////////////////
#if __WORDSIZE == 32
typedef s32_t			ssize_t;
#elif __WORDSIZE == 64
typedef s64_t			ssize_t;
#endif
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

/*
#define DZ1U64FMT_A			"I64u"
#define DZ1S64FMT_A			"I64d"
#define DZ1X64FMT_A			"I64X"

#define DZ1U64FMT_W			DZ1WIDER2(DZ1U64FMT_A)
#define DZ1S64FMT_W			DZ1WIDER2(DZ1S64FMT_A)
#define DZ1X64FMT_W			DZ1WIDER2(DZ1X64FMT_A)

#ifdef UNICODE
#define DZ1U64FMT			DZ1U64FMT_W
#define DZ1S64FMT			DZ1S64FMT_W
#define DZ1X64FMT			DZ1X64FMT_W
#else
#define DZ1U64FMT			DZ1U64FMT_A
#define DZ1S64FMT			DZ1S64FMT_A
#define DZ1X64FMT			DZ1X64FMT_A
#endif
*/

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format
#define DZ1_FMT64_A				"%I64d"
#define DZ1_FMT64U_A			"%I64u"
#define DZ1_FMT64X_A			"%I64X"

#define DZ1_FMT64F_A(dgt)		"%"#dgt"I64d"
#define DZ1_FMT64UF_A(dgt)		"%"#dgt"I64u"
#define DZ1_FMT64XF_A(dgt)		"%"#dgt"I64X"

#define DZ1_FMT64_W				L"%I64d"
#define DZ1_FMT64U_W			L"%I64u"
#define DZ1_FMT64X_W			L"%I64X"

#define DZ1_FMT64F_W(dgt)		L"%" DZ1WIDER2(#dgt) L"I64d"
#define DZ1_FMT64UF_W(dgt)		L"%" DZ1WIDER2(#dgt) L"I64u"
#define DZ1_FMT64XF_W(dgt)		L"%" DZ1WIDER2(#dgt) L"I64X"
// 64-bit integer print format
///////////////////////////////////////////////////////////////////////////////

#if _MSC_VER < 1916
#define snprintf				_snprintf
#endif

#if _MSC_VER >= 1500
#pragma warning(disable:4996)
#endif

#if _MSC_VER <= 1400
#define vsnprintf				_vsnprintf
#else
#endif

#define _std_vsnprintfW			_vsnwprintf

#endif
