#ifndef TXT_UTIL_H_LOCAL
#define TXT_UTIL_H_LOCAL

#include "dz1_task_gen_args.h"

static __inline__ void _lf(FILE *fp, Dz1GenTextMode mode)
{
	str_t lf = mode == Dz1GenTextMode_DOS ? "\r\n" : "\n";
	fputs(lf, fp);
}

static __inline__ void _lfn(FILE *fp, Dz1GenTextMode mode, int cnt)
{
	str_t lf = mode == Dz1GenTextMode_DOS ? "\r\n" : "\n";
	while(cnt--)
		fputs(lf, fp);
}

static __inline__ void _crlf(FILE *fp)
{
	str_t lf = "\r\n";
	fputs(lf, fp);
}

#ifdef UNIX_SYSTEM
#include <dz1_thread_stdio.h>
static __inline__ char *MkGUIDStr(char buf[40])
{
	Dz1Thread_printf("Do Not use this program in *NIX OS\n");
	strcpy(buf, "{00000000-0000-0000-0000-000000000000}");
	return buf;
}

#else
#include <Guiddef.h>
#include <ObjBase.h>
#pragma comment(lib, "Ole32.lib")
static __inline__ Dz1Str MkGUIDStr(TCHAR buf[40])
{
	GUID TestGUID;
	CoCreateGuid(&TestGUID); 
	Dz1SNPRINTF(buf, 40, Dz1T("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"), 
			TestGUID.Data1,    TestGUID.Data2,    TestGUID.Data3,  TestGUID.Data4[0],
			TestGUID.Data4[1], TestGUID.Data4[2], TestGUID.Data4[3], TestGUID.Data4[4],
			TestGUID.Data4[5], TestGUID.Data4[6], TestGUID.Data4[7]);
	return buf;
}
#endif
DZ1_CPPLINK Dz1Str			 GetGUIDStr(Dz1Error *err);

DZ1_CPPLINK Dz1Str			 _getDefineName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Error *err);

typedef struct TextEmitArg
{
	void					*dst;
	Dz1Str					 bias_path_abs;
	int						 tab;
} TextEmitArg;

#endif
