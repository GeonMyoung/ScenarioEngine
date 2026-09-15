#ifndef DZ1_MFC_DEF_UTIL_H
#define DZ1_MFC_DEF_UTIL_H

#include <Dz1MfcDef.h>

DZ1_CPPLINK Dz1Error				 Dz1MfcLanManPathList_add_host(Dz1MfcLanManPathList *dst, Dz1Str name);
DZ1_CPPLINK void					 Dz1MfcLanManPathList_remove_host(Dz1MfcLanManPathList *dst, Dz1Str name);

DZ1_CPPLINK ssize_t					 Dz1MfcLanManPathList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t					 Dz1MfcLanManPathList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1Error				 Dz1MfcLanManPathList_toStream(Dz1MfcLanManPathList *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param);
DZ1_CPPLINK Dz1MfcLanManPathList	*Dz1MfcLanManPathList_fromStream(Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

typedef struct Dz1MfcProgressInfo
{
	Dz1Letter			 text[256];
	bool_t				 text_changed;

	u64_t				 total;
	u64_t				 curr;
} Dz1MfcProgressInfo;
DZ1_CPPLINK void Dz1MfcProgressInfo_dump(Dz1MfcProgressInfo *p, int tab);

DZ1_CPPLINK void Dz1MfcProgressInfo_setText(Dz1MfcProgressInfo *dst, Dz1Str text);
DZ1_CPPLINK void Dz1MfcProgressInfo_setPos(Dz1MfcProgressInfo *dst, u64_t pos);

DZ1_CPPLINK void Dz1MfcProgressInfo_addPos(Dz1MfcProgressInfo *dst, u64_t v);
DZ1_CPPLINK void Dz1MfcProgressInfo_subPos(Dz1MfcProgressInfo *dst, u64_t v);

DZ1_CPPLINK void Dz1MfcProgressInfo_incPos(Dz1MfcProgressInfo *dst);
DZ1_CPPLINK void Dz1MfcProgressInfo_decPos(Dz1MfcProgressInfo *dst);

DZ1_CPPLINK void Dz1MfcProgressInfo_setTotal(Dz1MfcProgressInfo *dst, u64_t total);
DZ1_CPPLINK void Dz1MfcProgressInfo_addTotal(Dz1MfcProgressInfo *dst, u64_t total);
DZ1_CPPLINK void Dz1MfcProgressInfo_subTotal(Dz1MfcProgressInfo *dst, u64_t total);

DZ1_CPPLINK void Dz1MfcProgressInfo_incTotal(Dz1MfcProgressInfo *dst);
DZ1_CPPLINK void Dz1MfcProgressInfo_decTotal(Dz1MfcProgressInfo *dst);


DZ1_CPPLINK Dz1MfcProgInfo	*Dz1MfcProgInfo_generate(Dz1Error *err);
DZ1_CPPLINK Dz1Str			 Dz1MfcProgInfo_getArgv(Dz1MfcProgInfo *info, u32_t idx, Dz1Error *err);

#endif