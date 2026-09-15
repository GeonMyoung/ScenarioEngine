#ifndef DZ1_CPP_BUILDER_WIN32_H
#define DZ1_CPP_BUILDER_WIN32_H

#ifdef __BORLANDC__

///////////////////////////////////////////////////////////////////////////////
// CPP BUILDER Part
///////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

///////////////////////////////////////////////////////////////////////////////
// 64-bit integer print format
#define DZ1_FMT64_A				"%lld"
#define DZ1_FMT64U_A			"%llu"
#define DZ1_FMT64X_A			"%llX"

#define DZ1_FMT64F_A(dgt)		"%"#dgt"lld"
#define DZ1_FMT64UF_A(dgt)		"%"#dgt"llu"
#define DZ1_FMT64XF_A(dgt)		"%"#dgt"llX"

#define DZ1_FMT64_W				L"%lld"
#define DZ1_FMT64U_W			L"%llu"
#define DZ1_FMT64X_W			L"%llX"

#define DZ1_FMT64F_W(dgt)		L"%" DZ1WIDER2(#dgt) L"lld"
#define DZ1_FMT64UF_W(dgt)		L"%" DZ1WIDER2(#dgt) L"llu"
#define DZ1_FMT64XF_W(dgt)		L"%" DZ1WIDER2(#dgt) L"llX"
// 64-bit integer print format
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:8066)
#pragma warning(disable:8058)

#define TRUE			1
#define FALSE			0

#define _std_vsnprintfW				vsnwprintf

#endif // __BORLANDC__
#endif
