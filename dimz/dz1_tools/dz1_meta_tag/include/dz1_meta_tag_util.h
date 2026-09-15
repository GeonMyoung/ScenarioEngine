#ifndef DZ1_META_TAG_UTIL_H
#define DZ1_META_TAG_UTIL_H

#include <dz1_meta_tag_def.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValueList Helper
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValueList_addData8( Dz1MetaTagValueList *dst, u8_t data);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValueList_addData16(Dz1MetaTagValueList *dst, u16_t data);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValueList_addData32(Dz1MetaTagValueList *dst, u32_t data);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValueList_addData64(Dz1MetaTagValueList *dst, u64_t data);
// Dz1MetaTagValueList Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDataList Helper
// Dz1MetaTagDataList Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData Helper
DZ1_CPPLINK Dz1MetaTagData		*Dz1MetaTagData_generate(u32_t target_type, Dz1MetaTagDB *src, Dz1Error *err);					// TAG DB의 Mandatory Tag를 자동으로 등록

DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTag(	   Dz1MetaTagData *dst, Dz1MetaTagDescrEntry *descr);					// Tag 등록
DZ1_CPPLINK Dz1MetaTagDataEntry	*Dz1MetaTagData_extractTag(Dz1MetaTagData *src, u32_t tag_id);									// Tag 추출
DZ1_CPPLINK Dz1MetaTagDataEntry *Dz1MetaTagData_getTag(	   Dz1MetaTagData *src, u32_t tag_id);									// Tag 얻기

// General Append
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *clone_src);		// 등록(얻은) 후 값 설정 : clone_src를 복사해서 삽입
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_injTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue **inject_src);	// 등록(얻은) 후 값 설정 : 삽입 후 (*inject_src)는 NULL이 됨

// Append Number Data
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValue8(Dz1MetaTagData *dst, u32_t tag_id, u8_t data);						// 등록(얻은) 후 값 설정 : 8비트 데이터
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValue16(Dz1MetaTagData *dst, u32_t tag_id, u16_t data);					// 등록(얻은) 후 값 설정 : 16비트 데이터
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValue32(Dz1MetaTagData *dst, u32_t tag_id, u32_t data);					// 등록(얻은) 후 값 설정 : 32비트 데이터
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValue64(Dz1MetaTagData *dst, u32_t tag_id, u64_t data);					// 등록(얻은) 후 값 설정 : 64비트 데이터

// Append Binary Data
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *clone_src);		// 등록(얻은) 후 값 설정 : clone_src를 복사해서 삽입
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_addTagValueBinB(Dz1MetaTagData *dst, u32_t tag_id, u8_t *buf, size_t size);		// 등록(얻은) 후 값 설정 : Binary 데이터
DZ1_CPPLINK Dz1Error			 Dz1MetaTagData_injTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary **inject_src);		// 등록(얻은) 후 값 설정 : 삽입 후 (*inject_src)는 NULL이 됨

// General Remove
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *key);
DZ1_CPPLINK Dz1MetaTagValue		*Dz1MetaTagData_extractTagValue(Dz1MetaTagData *dst, u32_t tag_id, Dz1MetaTagValue *key);

// Remove Number Data
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValue8(Dz1MetaTagData *dst, u32_t tag_id, u8_t key);
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValue16(Dz1MetaTagData *dst, u32_t tag_id, u16_t key);
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValue32(Dz1MetaTagData *dst, u32_t tag_id, u32_t key);
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValue64(Dz1MetaTagData *dst, u32_t tag_id, u64_t key);

// Remove Binary Data
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *key);
DZ1_CPPLINK void				 Dz1MetaTagData_removeTagValueBinB(Dz1MetaTagData *dst, u32_t tag_id, u8_t *key_buf, size_t key_size);
DZ1_CPPLINK Dz1Binary			*Dz1MetaTagData_extractTagValueBin(Dz1MetaTagData *dst, u32_t tag_id, Dz1Binary *key);

DZ1_CPPLINK Dz1MetaTagDataEntry**Dz1MetaTagData_mkArray(Dz1MetaTagData *data, size_t *ret_cnt, Dz1Error *err);					// Table을 Array로 변환 : 내부 포인터는 전부 Reference

DZ1_CPPLINK bool_t				 Dz1MetaTagData_isExistTag(Dz1MetaTagData *data, u32_t tag_id);
// Dz1MetaTagData Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagValue Helper
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_getAsData32(u32_t *dst, Dz1MetaTagValue *src);

typedef struct Dz1MetaTagDataDate8
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	u8_t				month:4;
	u8_t				hday:4;
#else
	u8_t				hday:4;
	u8_t				month:4;
#endif
} Dz1MetaTagDataDate8;
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_getDataAsDate(struct tm *dst, Dz1MetaTagValue *src);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_getDataAsTime(struct tm *dst, Dz1MetaTagValue *src);

typedef struct Dz1MetaTagDataTime16
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	u16_t				minutes:12;
	u16_t				qsec:4;
#else
	u16_t				qsec:4;
	u16_t				minutes:12;
#endif
} Dz1MetaTagDataTime16;
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_getDataAsDateTime(struct tm *dst, Dz1MetaTagValue *src);

DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setNumber(Dz1MetaTagValue *dst, s64_t v);		// check from data8
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setNumber16(Dz1MetaTagValue *dst, s64_t v);	// check from data16
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setNumber32(Dz1MetaTagValue *dst, s64_t v);	// check from data16

DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setUNumber(Dz1MetaTagValue *dst, u64_t v);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setUNumber16(Dz1MetaTagValue *dst, u64_t v);
DZ1_CPPLINK Dz1Error			 Dz1MetaTagValue_setUNumber32(Dz1MetaTagValue *dst, u64_t v);
// Dz1MetaTagValue Helper
///////////////////////////////////////////////////////////////////////////////


















///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB Helper
DZ1_CPPLINK Dz1MetaTagDB			*Dz1MetaTagDB_create(Dz1Error *err);

DZ1_CPPLINK Dz1MetaTagDB			*Dz1MetaTagDBA_load(str_t path, str_t name, Dz1Error *err);
DZ1_CPPLINK Dz1Error				 Dz1MetaTagDBA_save(Dz1MetaTagDB *src, str_t path, str_t name);
#ifdef WIN32
DZ1_CPPLINK Dz1MetaTagDB			*Dz1MetaTagDBW_load(wstr_t path, wstr_t name, Dz1Error *err);
DZ1_CPPLINK Dz1Error				 Dz1MetaTagDBW_save(Dz1MetaTagDB *src, wstr_t path, wstr_t name);
#endif

#ifdef UNICODE
#define Dz1MetaTagDB_load			 Dz1MetaTagDBW_load
#define Dz1MetaTagDB_save			 Dz1MetaTagDBW_save
#else
#define Dz1MetaTagDB_load			 Dz1MetaTagDBA_load
#define Dz1MetaTagDB_save			 Dz1MetaTagDBA_save
#endif

// Dz1MetaTagDB Helper : Target Type
DZ1_CPPLINK Dz1Error				 Dz1MetaTagDB_addTargetTypeUTF8(Dz1MetaTagDB *dst, u32_t type, Dz1Asn1UTF8Str *name);
DZ1_CPPLINK Dz1Error				 Dz1MetaTagDB_addTargetTypeBuf(Dz1MetaTagDB *dst, u32_t type, void *name, size_t sz, str_t name_charset);

DZ1_CPPLINK Dz1Error				 Dz1MetaTagDB_addTargetTypeW(Dz1MetaTagDB *dst, u32_t type, wstr_t name);
DZ1_CPPLINK Dz1Error				 Dz1MetaTagDB_addTargetTypeA(Dz1MetaTagDB *dst, u32_t type, str_t name);
#ifdef UNICODE
#define Dz1MetaTagDB_addTargetType		Dz1MetaTagDB_addTargetTypeW
#else
#define Dz1MetaTagDB_addTargetType		Dz1MetaTagDB_addTargetTypeA
#endif

DZ1_CPPLINK void					 Dz1MetaTagDB_delTargetType(Dz1MetaTagDB *dst, u32_t type);
DZ1_CPPLINK Dz1MetaTargetTypeEntry	*Dz1MetaTagDB_getTargetType(Dz1MetaTagDB *dst, u32_t type);

// Dz1MetaTagDB Helper : TAG Descriptor
// DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_addTagDescrAnsi(Dz1MetaTagDB *dst, u32_t id,
// 																  str_t name, str_t name_charset,
// 																  bool_t mandatory, Dz1Error *err);

DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_addTagDescrUTF8(Dz1MetaTagDB *dst, u32_t id, Dz1Asn1UTF8Str *descr, bool_t mandatory, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_addTagDescrBuf(Dz1MetaTagDB *dst, u32_t id, u8_t *descr, size_t name_size, str_t name_charset, bool_t mandatory, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_addTagDescrW(Dz1MetaTagDB *dst, u32_t id, wstr_t name, bool_t mandatory, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_addTagDescrA(Dz1MetaTagDB *dst, u32_t id, str_t name, bool_t mandatory, Dz1Error *err);
#ifdef UNICODE
#define								 Dz1MetaTagDB_addTagDescr		Dz1MetaTagDB_addTagDescrW
#else
#define								 Dz1MetaTagDB_addTagDescr		Dz1MetaTagDB_addTagDescrA
#endif
DZ1_CPPLINK void					 Dz1MetaTagDB_delTagDescr(Dz1MetaTagDB *dst, u32_t id);
DZ1_CPPLINK Dz1MetaTagDescrEntry	*Dz1MetaTagDB_getTagDescr(Dz1MetaTagDB *dst, u32_t id);
// Dz1MetaTagDB Helper
///////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrList Helper
// Dz1MetaTagDescrList Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_mkNameW(Dz1MetaTagDescrEntry *p);
// Dz1MetaTagDescrEntry Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry Helper : Restrict
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setRestrict(Dz1MetaTagDescrEntry *dst, Dz1MetaTagRestrictMode mode);	// Restriction 생성
DZ1_CPPLINK void						 Dz1MetaTagDescrEntry_clrRestrict(Dz1MetaTagDescrEntry *dst);								// Restriction 제거

DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_addRestrict(Dz1MetaTagDescrEntry *dst, u32_t target_type);	// Restriction Target Type 추가
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_delRestrict(Dz1MetaTagDescrEntry *dst, u32_t target_type);	// Restriction Target Type 제거

DZ1_CPPLINK bool_t						 Dz1MetaTagDescrEntry_isAcceptable(Dz1MetaTagDescrEntry *p, u32_t type);
// Dz1MetaTagDescrEntry Helper : Restrict
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEntry Helper : Descriptor
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrNumber(Dz1MetaTagDescrEntry *dst, Dz1MetaTagDescrNum type);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrFloat(Dz1MetaTagDescrEntry *dst, u32_t precision);

DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrGrade(Dz1MetaTagDescrEntry *dst,
																			u8_t max_grade,
																			u8_t *display_letter, size_t display_letter_len,
																			str_t display_letter_charset);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrGradeAnsi(Dz1MetaTagDescrEntry *dst, u8_t max_grade,
																				str_t display_letter, str_t display_letter_charset);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrGradeW(Dz1MetaTagDescrEntry *dst, u8_t max_grade, wstr_t display_letter);

DZ1_CPPLINK Dz1MetaTagDescrEnums		*Dz1MetaTagDescrEntry_setDescrEnums(Dz1MetaTagDescrEntry *dst, Dz1Error *err);

DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrString(Dz1MetaTagDescrEntry *dst, str_t charset);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrWebUrl(Dz1MetaTagDescrEntry *dst);

DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrDate(Dz1MetaTagDescrEntry *dst, Dz1MetaTagDescrDate8Mode mode);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrTime(Dz1MetaTagDescrEntry *dst);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrDateTime(Dz1MetaTagDescrEntry *dst);

DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrBinary(Dz1MetaTagDescrEntry *dst);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrUser(Dz1MetaTagDescrEntry *dst, u32_t user_handle_type);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEntry_setDescrAlias(Dz1MetaTagDescrEntry *dst, u32_t origin_descr_id);

DZ1_CPPLINK void						 Dz1MetaTagDescrEntry_clrDescr(Dz1MetaTagDescrEntry *dst);
// Dz1MetaTagDescrEntry Helper : Descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrGrade Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrGrade_mkUnitW(Dz1MetaTagDescrGrade *p);
// Dz1MetaTagDescrGrade Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnums Helper
DZ1_CPPLINK Dz1MetaTagDescrEnums		*Dz1MetaTagDescrEnums_create(Dz1Error *err);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEnums_addEntryBuf(Dz1MetaTagDescrEnums *dst, u32_t v, u8_t *str, size_t str_len, str_t str_charset);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEnums_addEntryW(Dz1MetaTagDescrEnums *dst, u32_t v, wstr_t str);
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEnums_addEntryA(Dz1MetaTagDescrEnums *dst, u32_t v, str_t str);
#ifdef UNICODE
#define Dz1MetaTagDescrEnums_addEntry	Dz1MetaTagDescrEnums_addEntryW
#else
#define Dz1MetaTagDescrEnums_addEntry	Dz1MetaTagDescrEnums_addEntryA
#endif
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEnums_addNode(Dz1MetaTagDescrEnums *dst, Dz1MetaTagDescrEnumEntry *node);	// take pointer
DZ1_CPPLINK void						 Dz1MetaTagDescrEnums_delEntry(Dz1MetaTagDescrEnums *dst, u32_t v);
DZ1_CPPLINK Dz1MetaTagDescrEnumEntry	*Dz1MetaTagDescrEnums_getByValue(Dz1MetaTagDescrEnums *src, u32_t v, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrEnumEntry	*Dz1MetaTagDescrEnums_getByCharset(Dz1MetaTagDescrEnums *src,
																		   u8_t *name, size_t name_len,
																		   str_t name_charset, Dz1Error *err);
DZ1_CPPLINK Dz1MetaTagDescrEnumEntry	*Dz1MetaTagDescrEnums_getByStr(Dz1MetaTagDescrEnums *src, Dz1Asn1UTF8Str *str, Dz1Error *err);

DZ1_CPPLINK Dz1MetaTagDescrEnumEntry	*Dz1MetaTagDescrEnums_extract(Dz1MetaTagDescrEnums *src, u32_t v);
DZ1_CPPLINK Dz1MetaTagDescrEnumEntry	*Dz1MetaTagDescrEnums_getLast(Dz1MetaTagDescrEnums *src);
// Dz1MetaTagDescrEnums Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrEnumEntry Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrEnumEntry_mkNameW(Dz1MetaTagDescrEnumEntry *p);
// Dz1MetaTagDescrEnumEntry Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDescrAlias Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTagDescrAlias_resolv(Dz1MetaTagDescrAlias *src, Dz1MetaTagDB *db);
// Dz1MetaTagDescrAlias Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeList Helper
// Dz1MetaTargetTypeList Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTargetTypeEntry Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTargetTypeEntry_mkNameW(Dz1MetaTargetTypeEntry *p);
DZ1_CPPLINK Dz1Error					 Dz1MetaTargetTypeEntry_setNameW(Dz1MetaTargetTypeEntry *p, wstr_t name_w);
// Dz1MetaTargetTypeEntry Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeList Helper
// Dz1MetaTagUserTypeList Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagUserTypeEntry Helper
DZ1_CPPLINK Dz1Error					 Dz1MetaTagUserTypeEntry_mkNameW(Dz1MetaTagUserTypeEntry *p);
// Dz1MetaTagUserTypeEntry Helper
///////////////////////////////////////////////////////////////////////////////
#endif