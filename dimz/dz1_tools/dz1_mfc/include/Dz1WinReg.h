#ifndef DZ1_WIN_REG_H
#define DZ1_WIN_REG_H

//////////////////
// Charset Free //
//////////////////

#include <dz1_error.h>

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open. 없으면 만들어 가면서...
DZ1_CPPLINK HKEY Dz1WinRegA_SafeOpen(HKEY root_key, str_t permanant_path,  str_t create_sub_path,  Dz1Error *err);
DZ1_CPPLINK HKEY Dz1WinRegW_SafeOpen(HKEY root_key, wstr_t permanant_path, wstr_t create_sub_path, Dz1Error *err);
// 특정 KEY를 Open. 없으면 만들어 가면서...
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK void Dz1WinRegKey_close(HKEY hKey);
static __inline__ void Dz1WinRegKey_closeAndSetNull(void *ptr)
{
	HKEY *hKey = (HKEY *)ptr;
	Dz1WinRegKey_close(*hKey); (*hKey) = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// open한 HKEY에 대하여 member variable에 값 설정(REG_SZ Type)
DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyA_setNamedValueSZ(HKEY dst, str_t name,  str_t value);
static __inline__ Dz1Error	 Dz1WinRegKeyA_setDefaultValueSZ(HKEY dst, str_t value)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1WinRegKeyA_setNamedValueSZ(dst, NULL, value)).code) ERR_OUT(errp);
	return err;
}

DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyW_setNamedValueSZ(HKEY dst, wstr_t name, wstr_t value);
static __inline__ Dz1Error	 Dz1WinRegKeyW_setDefaultValueSZ(HKEY dst, wstr_t value)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1WinRegKeyW_setNamedValueSZ(dst, NULL, value)).code) ERR_OUT(errp);
	return err;
}
// open한 HKEY에 대하여 member variable에 값 설정(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member의 값 읽어오기(REG_SZ Type)
DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyA_getNamedValueSZ  (HKEY root_key, str_t path,  str_t name,  str_t ret_value,  DWORD *ret_value_sz);
DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyW_getNamedValueSZ  (HKEY root_key, wstr_t path, wstr_t name, wstr_t ret_value, DWORD *ret_value_sz);

DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyA_getDefaultValueSZ(HKEY root_key, str_t path,				  str_t ret_value,  DWORD *ret_value_size);
DZ1_CPPLINK Dz1Error		 Dz1WinRegKeyW_getDefaultValueSZ(HKEY root_key, wstr_t path,			  wstr_t ret_value, DWORD *ret_value_size);
// 특정 KEY를 Open하고 지정 member의 값 읽어오기(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member에 값 쓰기(REG_SZ Type)
DZ1_CPPLINK Dz1Error		 Dz1WinRegA_SafeSetNamedSZ	(HKEY root_key, str_t permanant_path, str_t create_sub_path, str_t value_id, str_t sz_value, bool_t *ret_changed);
static __inline__ Dz1Error	 Dz1WinRegA_SafeSetDefaultSZ(HKEY root_key, str_t permanant_path, str_t create_sub_path,				 str_t sz_value, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1WinRegA_SafeSetNamedSZ(root_key, permanant_path, create_sub_path, NULL, sz_value, ret_changed)).code) ERR_OUT(errp);
	return err;
}

DZ1_CPPLINK Dz1Error		 Dz1WinRegW_SafeSetNamedSZ	(HKEY root_key, wstr_t permanant_path, wstr_t create_sub_path, wstr_t value_id, wstr_t sz_value, bool_t *ret_changed);
static __inline__ Dz1Error	 Dz1WinRegW_SafeSetDefaultSZ(HKEY root_key, wstr_t permanant_path, wstr_t create_sub_path,					wstr_t sz_value, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1WinRegW_SafeSetNamedSZ(root_key, permanant_path, create_sub_path, NULL, sz_value, ret_changed)).code) ERR_OUT(errp);
	return err;
}
// 특정 KEY를 Open하고 지정 member에 값 쓰기(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member와 값 비교(REG_SZ Type)
DZ1_CPPLINK		  int		 Dz1WinRegA_isEqualNamedSZ		(HKEY root_key, str_t path,  str_t value_id,  str_t SZ_value);
static __inline__ int		 Dz1WinRegA_isEqualDefaultSZ	(HKEY root_key, str_t path,					  str_t SZ_value)
{
	return Dz1WinRegA_isEqualNamedSZ(root_key, path, NULL, SZ_value);
}

DZ1_CPPLINK		  int		 Dz1WinRegW_isEqualNamedSZ		(HKEY root_key, wstr_t path, wstr_t value_id, wstr_t SZ_value);
static __inline__ int		 Dz1WinRegW_isEqualDefaultSZ	(HKEY root_key, wstr_t path,				  wstr_t SZ_value)
{
	return Dz1WinRegW_isEqualNamedSZ(root_key, path, NULL, SZ_value);
}
// 특정 KEY를 Open하고 지정 member와 값 비교(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK bool_t			 Dz1WinRegA_chkTypeAssociation(str_t my_type, str_t full_path_name_ext, int icon_idx);
DZ1_CPPLINK bool_t			 Dz1WinRegW_chkTypeAssociation(wstr_t my_type, wstr_t full_path_name_ext, int icon_idx);

DZ1_CPPLINK Dz1Error		 Dz1WinRegA_setTypeAssociation(str_t my_type, str_t full_path_name_ext, int icon_idx, str_t description, bool_t *ret_changed);
DZ1_CPPLINK Dz1Error		 Dz1WinRegW_setTypeAssociation(wstr_t my_type, wstr_t full_path_name_ext, int icon_idx, wstr_t description, bool_t *ret_changed);

#ifdef UNICODE
#define						 Dz1WinRegKey_setNamedValueSZ		Dz1WinRegKeyW_setNamedValueSZ
#define						 Dz1WinRegKey_setDefaultValueSZ		Dz1WinRegKeyW_setDefaultValueSZ

#define						 Dz1WinRegKey_getNamedValueSZ		Dz1WinRegKeyW_getNamedValueSZ
#define						 Dz1WinRegKey_getDefaultValueSZ		Dz1WinRegKeyW_getDefaultValueSZ

#define						 Dz1WinReg_SafeOpen					Dz1WinRegW_SafeOpen

#define						 Dz1WinReg_SafeSetNamedSZ			Dz1WinRegW_SafeSetNamedSZ
#define						 Dz1WinReg_SafeSetDefaultSZ			Dz1WinRegW_SafeSetDefaultSZ

#define						 Dz1WinReg_isEqualNamedSZ			Dz1WinRegW_isEqualNamedSZ

#define						 Dz1WinReg_chkTypeAssociation		Dz1WinRegW_chkTypeAssociation
#define						 Dz1WinReg_setTypeAssociation		Dz1WinRegW_setTypeAssociation
#else
#define						 Dz1WinRegKey_setNamedValueSZ		Dz1WinRegKeyA_setNamedValueSZ
#define						 Dz1WinRegKey_setDefaultValueSZ		Dz1WinRegKeyA_setDefaultValueSZ

#define						 Dz1WinRegKey_getNamedValueSZ		Dz1WinRegKeyA_getNamedValueSZ
#define						 Dz1WinRegKey_getDefaultValueSZ		Dz1WinRegKeyA_getDefaultValueSZ

#define						 Dz1WinReg_SafeOpen					Dz1WinRegA_SafeOpen
#define						 Dz1WinReg_SafeSetNamedSZ			Dz1WinRegA_SafeSetNamedSZ
#define						 Dz1WinReg_SafeSetDefaultSZ			Dz1WinRegA_SafeSetDefaultSZ
#define						 Dz1WinReg_isEqualNamedSZ			Dz1WinRegA_isEqualNamedSZ

#define						 Dz1WinReg_chkTypeAssociation		Dz1WinRegA_chkTypeAssociation
#define						 Dz1WinReg_setTypeAssociation		Dz1WinRegA_setTypeAssociation
#endif

#endif