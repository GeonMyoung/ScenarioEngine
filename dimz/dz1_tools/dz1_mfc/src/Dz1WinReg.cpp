#include "stdafx.h"
#include "dz1_mfc.h"
#include <codeconv.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>

#include "Dz1WinReg.h"

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open. 없으면 만들어 가면서...
static u32_t node_a_cnt(str_t path)
{
	u32_t ret = 0;
	if (path == NULL || strlen(path) == 0) ret = -1;
	else
	{
		char *cp = path;
		while((cp = strstr(cp, DIR_SEPRATOR_A)) != NULL)
		{	// aaaa\bbbb\cccc
			cp++;
			ret++;
		}
		ret++;
	}
	return ret;
}

static str_t *mk_a_array(str_t temp_path, u32_t *ret_cnt, Dz1Error *err)
{
	str_t *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = node_a_cnt(temp_path);
	if (cnt == 0) Dz1Error_set(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(char), cnt + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i = 0;
		char *cprev = temp_path, *cp = temp_path;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		while ((cp = strstr(cp, DIR_SEPRATOR_A)) != NULL)
		{
			ret[i++] = cprev;
			*cp++ = 0;
			cprev = cp;
		}
		ret[i] = cprev;
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);

		if (ret_cnt) (*ret_cnt) = cnt;
	}
	return ret;
}

static void _arr_a_delete(str_t *arr)
{
	if (arr == NULL) return;
	Dz1Free(arr);
}

static void _mkArrayACancel(void *ptr)
{
	str_t *arr = (str_t *)ptr;
	_arr_a_delete(arr);
}

static HKEY _makeSureKeyOpenA(HKEY root_key, str_t path, Dz1Error *err)
{
	HKEY ret = NULL;
	size_t path_len = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (root_key == NULL || path == NULL || (path_len = strlen(path)) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		DWORD status;
#ifdef _DEBUG
		char temp_path[2048];
		strcpy(temp_path, path);
#endif
		if ((status = RegOpenKeyExA(root_key, path, 0, KEY_QUERY_VALUE | KEY_SET_VALUE , &ret)) != ERROR_SUCCESS)
		{
			DWORD outDispo = 0;
#ifdef _DEBUG
			Dz1Thread_printf(Dz1T("Reg Key Open Fail : %s = %u(%08X)\n"), temp_path, status, status);
#endif
			if ((status = RegCreateKeyExA(root_key, path, 0,
							   NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL,
							   &ret, &outDispo)) != ERROR_SUCCESS)
			{
#ifdef _DEBUG
				Dz1Thread_printf(Dz1T("Reg Key Create Fail : %s = %u(%08X)\n"), temp_path, status, status);
#endif
				ERR_SET_OUT(errp, EFAULT);
			}
		}
	}
	return ret;
}

HKEY Dz1WinRegA_SafeOpen(HKEY root_key, str_t permanant_path, str_t create_sub_path, Dz1Error *err)
{
	HKEY ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t permanant_path_len = permanant_path == NULL ? 0 : strlen(permanant_path);
	size_t create_sub_path_len = create_sub_path == NULL ? 0 : strlen(create_sub_path);

	if (root_key == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (permanant_path_len == 0 && create_sub_path_len == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		pthread_cleanup_push(Dz1WinRegKey_closeAndSetNull, (void *)&ret);

		str_t arr_src = Dz1StrA_dup(create_sub_path, errp);
		if (arr_src == NULL) ERR_OUT(errp);
		else
		{
			u32_t cnt = 0;
			str_t *arr = NULL;

			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&arr_src);

			if ((arr = mk_a_array(arr_src, &cnt, errp)) == NULL) ERR_OUT(errp);
			else
			{
				str_t ref_path = NULL;
				size_t total_len = permanant_path_len + 1 + create_sub_path_len;
				pthread_cleanup_push(_mkArrayACancel, (void *)arr);
				if ((ref_path = (str_t)Dz1Calloc(sizeof(char), total_len + 1, errp)) == NULL) ERR_OUT(errp);
				else
				{
					u32_t i;

					pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&ref_path);

					strcpy(ref_path, permanant_path);
					for (i = 0; errp->code == 0 && i < cnt; i++)
					{
						if (strlen(ref_path) > 0) strcat(ref_path, DIR_SEPRATOR_A);
						strcat(ref_path, arr[i]);

						if (ret != NULL) { RegCloseKey(ret); ret = NULL; }

						if ((ret = _makeSureKeyOpenA(root_key, ref_path, errp)) == NULL) ERR_OUT(errp);
					}

					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&ref_path);
				}
				pthread_cleanup_pop(1); // (_mkArrayACancel, (void *)arr);
			}
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WinRegKey_closeAndSetNull, (void *)&ret);
	}
	return ret;
}

static u32_t node_w_cnt(wstr_t path)
{
	u32_t ret = 0;
	if (path == NULL || wcslen(path) == 0) ret = -1;
	else
	{
		wchar_t *cp = path;
		while((cp = wcswcs(cp, DIR_SEPRATOR_W)) != NULL)
		{	// aaaa\bbbb\cccc
			cp++;
			ret++;
		}
		ret++;
	}
	return ret;
}

static wstr_t *mk_w_array(wstr_t temp_path, u32_t *ret_cnt, Dz1Error *err)
{
	wstr_t *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = node_w_cnt(temp_path);
	if (cnt == 0) Dz1Error_set(errp, EINVAL);
	else if ((ret = (wstr_t *)Dz1Calloc(sizeof(wstr_t), cnt + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u32_t i = 0;
		wchar_t *cprev = temp_path, *cp = temp_path;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		while ((cp = wcswcs(cp, DIR_SEPRATOR_W)) != NULL)
		{
			ret[i++] = cprev;
			*cp++ = 0;
			cprev = cp;
		}
		ret[i] = cprev;
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);

		if (ret_cnt) (*ret_cnt) = cnt;
	}
	return ret;
}

static void _arr_w_delete(wstr_t *arr)
{
	if (arr == NULL) return;
	Dz1Free(arr);
}

static void _mkArrayWCancel(void *ptr)
{
	wstr_t *arr = (wstr_t *)ptr;
	_arr_w_delete(arr);
}

static HKEY _makeSureKeyOpenW(HKEY root_key, wstr_t path, Dz1Error *err)
{
	HKEY ret = NULL;
	size_t path_len = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (root_key == NULL || path == NULL || (path_len = wcslen(path)) == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		DWORD status;
#ifdef _DEBUG
		char temp_path[2048];
		Dz1CodeConv((u8_t *)temp_path, 2048, "EUC-KR", (u8_t *)path, (path_len + 1) << 1, WINDOWS_UNICODE);
#endif
		if ((status = RegOpenKeyExW(root_key, path, 0, KEY_QUERY_VALUE | KEY_SET_VALUE , &ret)) != ERROR_SUCCESS)
		{
			DWORD outDispo = 0;
#ifdef _DEBUG
			Dz1Thread_printf(Dz1T("Reg Key Open Fail : %s = %u(%08X)\n"), temp_path, status, status);
#endif
			if ((status = RegCreateKeyExW(root_key, path, 0,
							   NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL,
							   &ret, &outDispo)) != ERROR_SUCCESS)
			{
#ifdef _DEBUG
				Dz1Thread_printf(Dz1T("Reg Key Create Fail : %s = %u(%08X)\n"), temp_path, status, status);
#endif
				ERR_SET_OUT(errp, EFAULT);
			}
		}
	}
	return ret;
}

HKEY Dz1WinRegW_SafeOpen(HKEY root_key, wstr_t permanant_path, wstr_t create_sub_path, Dz1Error *err)
{
	HKEY ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t permanant_path_len = permanant_path == NULL ? 0 : wcslen(permanant_path);
	size_t create_sub_path_len = create_sub_path == NULL ? 0 : wcslen(create_sub_path);

	if (root_key == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (permanant_path_len == 0 && create_sub_path_len == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		pthread_cleanup_push(Dz1WinRegKey_closeAndSetNull, (void *)&ret);

		wstr_t arr_src = Dz1StrW_dup(create_sub_path, errp);
		if (arr_src == NULL) ERR_OUT(errp);
		else
		{
			u32_t cnt = 0;
			wstr_t *arr = NULL;

			pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&arr_src);

			if ((arr = mk_w_array(arr_src, &cnt, errp)) == NULL) ERR_OUT(errp);
			else
			{
				wstr_t ref_path = NULL;
				size_t total_len = permanant_path_len + 1 + create_sub_path_len;
				pthread_cleanup_push(_mkArrayWCancel, (void *)arr);
				if ((ref_path = (wstr_t)Dz1Calloc(sizeof(wchar_t), total_len + 1, errp)) == NULL) ERR_OUT(errp);
				else
				{
					u32_t i;

					pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&ref_path);

					wcscpy(ref_path, permanant_path);
					for (i = 0; errp->code == 0 && i < cnt; i++)
					{
						if (wcslen(ref_path) > 0) wcscat(ref_path, DIR_SEPRATOR_W);
						wcscat(ref_path, arr[i]);

						if (ret != NULL) { RegCloseKey(ret); ret = NULL; }

						if ((ret = _makeSureKeyOpenW(root_key, ref_path, errp)) == NULL) ERR_OUT(errp);
					}

					pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&ref_path);
				}
				pthread_cleanup_pop(1); // (_mkArrayCancel, (void *)arr);
			}
			pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&temp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WinRegKey_closeAndSetNull, (void *)&ret);
	}
	return ret;
}
// 특정 KEY를 Open. 없으면 만들어 가면서...
///////////////////////////////////////////////////////////////////////////////

void Dz1WinRegKey_close(HKEY hKey)
{
	if (hKey == NULL) return;
	RegCloseKey(hKey);
}

///////////////////////////////////////////////////////////////////////////////
// open한 HKEY에 대하여 member variable에 값 설정(REG_SZ Type)
Dz1Error Dz1WinRegKeyA_setNamedValue(HKEY dst, str_t name, str_t value)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t v_len = (strlen(value) + 1);
#ifdef _DEBUG
	char temp_name[1024];
	if (name == NULL) strcpy(temp_name, "(default)");
	else strcpy(temp_name, name);	
#endif

	if (RegSetKeyValueA(dst, NULL, name, REG_SZ, value, (DWORD)v_len) != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		Dz1Thread_printf(Dz1T("Dz1WinRegKeyW_setNamedValue() :: Reg Value Set Fail : %s = %s\n"), temp_name, value);
#endif
		ERR_SET_OUT(errp, EFAULT);
	}
	else Dz1Error_set(errp, 0);

	return err;
}

Dz1Error Dz1WinRegKeyW_setNamedValue(HKEY dst, wstr_t name, wstr_t value)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t v_len = (wcslen(value) + 1) << 1;
#ifdef _DEBUG
	char temp_name[1024];
	if (name == NULL) strcpy(temp_name, "(default)");
	else Dz1CodeConv((u8_t *)temp_name, 1024, "EUC-KR", (u8_t *)name, (wcslen(name) + 1) << 1, WINDOWS_UNICODE);

	char temp_value[2048];
	Dz1CodeConv((u8_t *)temp_value, 2048, "EUC-KR", (u8_t *)value, (wcslen(value) + 1) << 1, WINDOWS_UNICODE);
#endif

	if (RegSetKeyValueW(dst, NULL, name, REG_SZ, value, (DWORD)v_len) != ERROR_SUCCESS)
	{
#ifdef _DEBUG
		Dz1Thread_printf(Dz1T("Dz1WinRegKeyW_setNamedValue() :: Reg Value Set Fail : %s = %s\n"), temp_name, temp_value);
#endif
		ERR_SET_OUT(errp, EFAULT);
	}
	else Dz1Error_set(errp, 0);

	return err;
}
// open한 HKEY에 대하여 member variable에 값 설정(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member의 값 읽어오기(REG_SZ Type)
Dz1Error Dz1WinRegKeyA_getNamedValueSZ(HKEY root_key, str_t path, str_t name, str_t ret_value, DWORD *ret_value_sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int status;
	DWORD type = REG_SZ;
	if ((status = RegGetValueA(root_key, path, name, RRF_RT_REG_SZ, &type, ret_value, ret_value_sz)) != ERROR_SUCCESS)
		ERR_SET_OUT(errp, status);
	return err;
}

Dz1Error Dz1WinRegKeyW_getNamedValueSZ(HKEY root_key, wstr_t path, wstr_t name, wstr_t ret_value, DWORD *ret_value_sz)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int status;
	DWORD type = REG_SZ;
	if ((status = RegGetValueW(root_key, path, name, RRF_RT_REG_SZ, &type, ret_value, ret_value_sz)) != ERROR_SUCCESS)
		ERR_SET_OUT(errp, status);
	return err;
}

Dz1Error Dz1WinRegKeyA_getDefaultValueSZ(HKEY root_key, str_t path, str_t ret_value, DWORD *ret_value_size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int status;
	DWORD type = REG_SZ;
	if ((status = RegGetValueA(root_key, path, NULL, RRF_RT_REG_SZ, &type, ret_value, ret_value_size)) != ERROR_SUCCESS)
		ERR_SET_OUT(errp, status);
	return err;
}

Dz1Error Dz1WinRegKeyW_getDefaultValueSZ(HKEY root_key, wstr_t path, wstr_t ret_value, DWORD *ret_value_size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int status;
	DWORD type = REG_SZ;
	if ((status = RegGetValueW(root_key, path, NULL, RRF_RT_REG_SZ, &type, ret_value, ret_value_size)) != ERROR_SUCCESS)
		ERR_SET_OUT(errp, status);
	return err;
}
// 특정 KEY를 Open하고 지정 member의 값 읽어오기(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member에 값 쓰기(REG_SZ Type)
Dz1Error Dz1WinRegA_SafeSetNamedSZ(HKEY root_key, str_t permanant_path, str_t create_sub_path, str_t value_id, str_t sz_value, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	size_t permanant_path_len = permanant_path == NULL ? 0 : strlen(permanant_path);
	size_t create_sub_path_len = create_sub_path == NULL ? 0 : strlen(create_sub_path);

	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;

	if (root_key == NULL || (permanant_path_len == 0 && create_sub_path_len == 0)) ERR_SET_OUT(errp, EINVAL);
	else
	{
		str_t full_path;
		size_t full_path_len = permanant_path_len + 1 + create_sub_path_len;

		char curr_value[512];
		DWORD curr_val_len = 512;

		if ((full_path = (str_t)Dz1Calloc(sizeof(char), full_path_len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&full_path);

			sprintf(full_path, "%s\\%s", permanant_path, create_sub_path);

			(*ret) = FALSE;

			if ((*errp = Dz1WinRegKeyA_getNamedValueSZ(root_key, full_path, value_id, (str_t)curr_value, &curr_val_len)).code ||
				strcmp(sz_value, curr_value) != 0)
			{
				HKEY dst = Dz1WinRegA_SafeOpen(root_key, permanant_path, create_sub_path, errp);
				if (dst == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1WinRegKey_closeAndSetNull, (void *)&dst);

					if ((*errp = Dz1WinRegKeyA_setNamedValue(dst, value_id, sz_value)).code) ERR_OUT(errp);
					else
					{
						(*ret) = TRUE;
						Dz1Error_set(errp, 0);
					}

					pthread_cleanup_pop(1); // (Dz1WinRegKey_closeAndSetNull, (void *)&dst);
				}
			}
			pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&full_path);
		}
	}
	return err;
}

Dz1Error Dz1WinRegW_SafeSetNamedSZ(HKEY root_key, wstr_t permanant_path, wstr_t create_sub_path, wstr_t value_id, wstr_t sz_value, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	size_t permanant_path_len = permanant_path == NULL ? 0 : wcslen(permanant_path);
	size_t create_sub_path_len = create_sub_path == NULL ? 0 : wcslen(create_sub_path);

	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;

	if (root_key == NULL || (permanant_path_len == 0 && create_sub_path_len == 0)) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wstr_t full_path;
		size_t full_path_len = permanant_path_len + 1 + create_sub_path_len;

		wchar_t curr_value[512];
		DWORD curr_val_len = 512;

		if ((full_path = (wstr_t)Dz1Calloc(sizeof(wchar_t), full_path_len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&full_path);

			wsprintfW(full_path, L"%s\\%s", permanant_path, create_sub_path);

			(*ret) = FALSE;

			if ((*errp = Dz1WinRegKeyW_getNamedValueSZ(root_key, full_path, value_id, curr_value, &curr_val_len)).code ||
				wcscmp(sz_value, curr_value) != 0)
			{
				HKEY dst = Dz1WinRegW_SafeOpen(root_key, permanant_path, create_sub_path, errp);
				if (dst == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1WinRegKey_closeAndSetNull, (void *)&dst);

					if ((*errp = Dz1WinRegKeyW_setNamedValue(dst, value_id, sz_value)).code) ERR_OUT(errp);
					else
					{
						(*ret) = TRUE;
						Dz1Error_set(errp, 0);
					}

					pthread_cleanup_pop(1); // (Dz1WinRegKey_closeAndSetNull, (void *)&dst);
				}
			}
			pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&full_path);
		}
	}
	return err;
}
// 특정 KEY를 Open하고 지정 member에 값 쓰기(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 특정 KEY를 Open하고 지정 member와 값 비교(REG_SZ Type)
int Dz1WinRegA_isEqualNamedSZ(HKEY root_key, str_t path, str_t value_id, str_t SZ_value)
{
	int ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (root_key == NULL || path == NULL || strlen(path) == 0 || SZ_value == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char curr_value[512];
		DWORD curr_val_len = 512;

		if ((*errp = Dz1WinRegKeyA_getNamedValueSZ(root_key, path, value_id, curr_value, &curr_val_len)).code) ERR_OUT(errp);
		else ret = strcmp(SZ_value, curr_value);
	}
	return ret;
}

int Dz1WinRegW_isEqualNamedSZ(HKEY root_key, wstr_t path, wstr_t value_id, wstr_t SZ_value)
{
	int ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (root_key == NULL || path == NULL || wcslen(path) == 0 || SZ_value == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t curr_value[512];
		DWORD curr_val_len = 512;

		if ((*errp = Dz1WinRegKeyW_getNamedValueSZ(root_key, path, value_id, curr_value, &curr_val_len)).code) ERR_OUT(errp);
		else ret = wcscmp(SZ_value, curr_value);
	}
	return ret;
}
// 특정 KEY를 Open하고 지정 member와 값 비교(REG_SZ Type)
///////////////////////////////////////////////////////////////////////////////

/*
*** 확장자등록

1. 기본정보 등록
HKEY_CURRENT_USER/Software/Classes/.{my_type}	: 사용자 전용
-> (default) REG_SZ {my_app_name}.{my_type}

2. App과 Type을 Mapping
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}
-> (default) REG_SZ "{description of this type}"

3. Icon 설정
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}/DefaultIcon
-> (default) REG_SZ {full path of icon resource file}[,{icon_idx}]

4. 실행 방법 설정
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}/Shell/Open/Command
-> (default) REG_SZ "{full path of application with ext}" "%1"

PS:
HKEY_CLASSES_ROOT/{my_type}						: 하위호환
자동으로 HKEY_CURRENT_USER/Software/Classes로 부터 미러링 된다


5. Explorer에 해당 확장자에 대한 실행 프로그램 지정
HKEY_CURRENT_USER/Software/Microsoft/Windows/CurrentVersion/Explorer/FileExts/.{my_type}/UserChoice : 사용자전용
-> "Progid" : REG_SZ : {my_app_name}.<my_type}
*/

///////////////////////////////////////
// Check Basic Info
static bool_t _regMyTypeIsOwnA_basic(str_t ext, str_t my_app_name_without_ext)
{
	bool_t ret = FALSE;

	char key_path[1024];
	sprintf(key_path, "Software\\Classes\\.%s", ext);

	char chk_value[1024];
	sprintf(chk_value, "%s.%s", my_app_name_without_ext, ext);

	if (Dz1WinRegA_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0) ret = TRUE;

	return ret;
}

static bool_t _regMyTypeIsOwnW_basic(wstr_t ext, wstr_t my_app_name_without_ext)
{
	bool_t ret = FALSE;

	wchar_t key_path[1024];
	wsprintfW(key_path, L"Software\\Classes\\.%s", ext);

	wchar_t chk_value[1024];
	wsprintfW(chk_value, L"%s.%s", my_app_name_without_ext, ext);

	if (Dz1WinRegW_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0) ret = TRUE;

	return ret;
}
// Check Basic Info
///////////////////////////////////////

///////////////////////////////////////
// Set Basic Info
static Dz1Error _regMyTypeA_basic(str_t ext, str_t my_app_name_without_ext, str_t description, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t phase1_changed = FALSE, phase2_changed = FALSE;
	(*ret) = FALSE;

	char const_path[128];
	strcpy(const_path, "Software\\Classes");

	char make_sure_path[512];
	char write_value[512];

	// 1. 기본정보 등록
	// HKEY_CURRENT_USER
	// Software\Classes\
	//					.{my_type}
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ {my_app_name}.{my_type}
	sprintf(make_sure_path, ".%s", ext);
	sprintf(write_value, "%s.%s", my_app_name_without_ext, ext);
	if ((*errp = Dz1WinRegA_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase1_changed)).code) ERR_OUT_RET(errp, err);

	// 2. App과 Type을 Mapping
	// HKEY_CURRENT_USER
	// Software\Classes\
	//					{my_app_name}.{my_type}
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ "{description of this type}"
	sprintf(make_sure_path, "%s.%s", my_app_name_without_ext, ext);
	if ((*errp = Dz1WinRegA_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, description, &phase2_changed)).code) ERR_OUT_RET(errp, err);

	(*ret) = phase1_changed || phase2_changed ? TRUE : FALSE;

	return err;
}

static Dz1Error _regMyTypeW_basic(wstr_t ext, wstr_t my_app_name_without_ext, wstr_t description, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t phase1_changed = FALSE, phase2_changed = FALSE;
	(*ret) = FALSE;

	wchar_t const_path[128];
	wcscpy(const_path, L"Software\\Classes");

	wchar_t make_sure_path[512];
	wchar_t write_value[512];

	// 1. 기본정보 등록
	// HKEY_CURRENT_USER
	// Software\Classes\
	//					.{my_type}
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ {my_app_name}.{my_type}
	wsprintfW(make_sure_path, L".%s", ext);
	wsprintfW(write_value, L"%s.%s", my_app_name_without_ext, ext);
	if ((*errp = Dz1WinRegW_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase1_changed)).code) ERR_OUT_RET(errp, err);

	// 2. App과 Type을 Mapping
	// HKEY_CURRENT_USER
	// Software\Classes\
	//					{my_app_name}.{my_type}
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ "{description of this type}"
	wsprintfW(make_sure_path, L"%s.%s", my_app_name_without_ext, ext);
	if ((*errp = Dz1WinRegW_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, description, &phase2_changed)).code) ERR_OUT_RET(errp, err);

	(*ret) = phase1_changed || phase2_changed ? TRUE : FALSE;

	return err;
}
// Set Basic Info
///////////////////////////////////////

///////////////////////////////////////
// Check ICON and Command
static bool_t _regMyTypeIsOwnA_iconAndCmd(str_t ext, str_t my_app_name_without_ext,
										  str_t full_app_path_name_ext, int icon_idx)
{
	bool_t ret = FALSE;

	char key_path[1024];
	sprintf(key_path, "Software\\Classes\\%s.%s\\DefaultIcon", my_app_name_without_ext, ext);

	char chk_value[1024];
	sprintf(chk_value, "%s,%d", full_app_path_name_ext, icon_idx);

	if (Dz1WinRegA_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0)
	{
		sprintf(key_path, "Software\\Classes\\%s.%s\\Shell\\Open\\Command", my_app_name_without_ext, ext);
		sprintf(chk_value, "\"%s\" \"%%1\"", full_app_path_name_ext);
		if (Dz1WinRegA_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0) ret = TRUE;
	}

	return ret;
}

static bool_t _regMyTypeIsOwnW_iconAndCmd(wstr_t ext, wstr_t my_app_name_without_ext,
										  wstr_t full_app_path_name_ext, int icon_idx)
{
	bool_t ret = FALSE;

	wchar_t key_path[1024];
	wsprintfW(key_path, L"Software\\Classes\\%s.%s\\DefaultIcon", my_app_name_without_ext, ext);

	wchar_t chk_value[1024];
	wsprintfW(chk_value, L"%s,%d", full_app_path_name_ext, icon_idx);

	if (Dz1WinRegW_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0)
	{
		wsprintfW(key_path, L"Software\\Classes\\%s.%s\\Shell\\Open\\Command", my_app_name_without_ext, ext);
		wsprintfW(chk_value, L"\"%s\" \"%%1\"", full_app_path_name_ext);
		if (Dz1WinRegW_isEqualDefaultSZ(HKEY_CURRENT_USER, key_path, chk_value) == 0) ret = TRUE;
	}

	return ret;
}
// Check ICON and Command
///////////////////////////////////////

///////////////////////////////////////
// Set ICON and Command
static Dz1Error _regMyTypeA_IconAndCmd(str_t ext, str_t my_app_name_without_ext,
									   str_t full_app_path_name_ext, int icon_idx,
									   bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t phase1_changed = FALSE, phase2_changed = FALSE;
	(*ret) = FALSE;

	char const_path[128];
	char make_sure_path[512];
	char write_value[512];

	// 3. Icon 설정
	// HKEY_CURRENT_USER
	// Software\Classes\{my_app_name}.{my_type}\
	//											DefaultIcon
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ {full path of icon resource file}[,{icon_idx}]
	sprintf(const_path, "Software\\Classes\\%s.%s", my_app_name_without_ext, ext);
	strcpy(make_sure_path, "DefaultIcon");
	sprintf(write_value, "%s,%d", full_app_path_name_ext, icon_idx);
	if ((*errp = Dz1WinRegA_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase1_changed)).code) ERR_OUT_RET(errp, err);

	// 4. 실행 방법 설정
	// HKEY_CURRENT_USER
	// Software\Classes\{my_app_name}.{my_type}\
	//											Shell\Open\Command
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ "{full path of application with ext}" "%1"
	strcpy(make_sure_path, "Shell\\Open\\Command");
	sprintf(write_value, "\"%s\" \"%%1", full_app_path_name_ext);
	if ((*errp = Dz1WinRegA_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase2_changed)).code) ERR_OUT_RET(errp, err);

	(*ret) = phase1_changed || phase2_changed ? TRUE : FALSE;

	return err;
}

static Dz1Error _regMyTypeW_IconAndCmd(wstr_t ext, wstr_t my_app_name_without_ext,
									   wstr_t full_app_path_name_ext, int icon_idx,
									   bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t phase1_changed = FALSE, phase2_changed = FALSE;
	(*ret) = FALSE;

	wchar_t const_path[128];
	wchar_t make_sure_path[512];
	wchar_t write_value[512];

	// 3. Icon 설정
	// HKEY_CURRENT_USER
	// Software\Classes\{my_app_name}.{my_type}\
	//											DefaultIcon
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ {full path of icon resource file}[,{icon_idx}]
	wsprintfW(const_path, L"Software\\Classes\\%s.%s", my_app_name_without_ext, ext);
	wcscpy(make_sure_path, L"DefaultIcon");
	wsprintfW(write_value, L"%s,%d", full_app_path_name_ext, icon_idx);
	if ((*errp = Dz1WinRegW_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase1_changed)).code) ERR_OUT_RET(errp, err);

	// 4. 실행 방법 설정
	// HKEY_CURRENT_USER
	// Software\Classes\{my_app_name}.{my_type}\
	//											Shell\Open\Command
	//-----------------------------------------------------------------------------------------------
	// -> (default) REG_SZ "{full path of application with ext}" "%1"
	wcscpy(make_sure_path, L"Shell\\Open\\Command");
	wsprintfW(write_value, L"\"%s\" \"%%1", full_app_path_name_ext);
	if ((*errp = Dz1WinRegW_SafeSetDefaultSZ(HKEY_CURRENT_USER, const_path, make_sure_path, write_value, &phase2_changed)).code) ERR_OUT_RET(errp, err);

	(*ret) = phase1_changed || phase2_changed ? TRUE : FALSE;

	return err;
}
// Set ICON and Command
///////////////////////////////////////

///////////////////////////////////////
// Check Explorer FileExt
static bool_t _regMyTypeIsOwnA_ExplorerExt(str_t ext, str_t my_app_name_without_ext)
{
	bool_t ret = FALSE;

	char key_path[1024];
	sprintf(key_path, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%s\\UserChoice", ext);

	char chk_value[1024];
	sprintf(chk_value, "%s.%s", my_app_name_without_ext, ext);

	if (Dz1WinRegA_isEqualNamedSZ(HKEY_CURRENT_USER, key_path, "Progid", chk_value) == 0) ret = TRUE;

	return ret;
}

static bool_t _regMyTypeIsOwnW_ExplorerExt(wstr_t ext, wstr_t my_app_name_without_ext)
{
	bool_t ret = FALSE;

	wchar_t key_path[1024];
	wsprintfW(key_path, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%s\\UserChoice", ext);

	wchar_t chk_value[1024];
	wsprintfW(chk_value, L"%s.%s", my_app_name_without_ext, ext);

	if (Dz1WinRegW_isEqualNamedSZ(HKEY_CURRENT_USER, key_path, L"Progid", chk_value) == 0) ret = TRUE;

	return ret;
}
// Check Explorer FileExt
///////////////////////////////////////

///////////////////////////////////////
// Set Explorer FileExt
static Dz1Error _regMyTypeA_ExplorerExt(str_t ext, str_t my_app_name_without_ext, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	(*ret) = FALSE;

	char const_path[64];
	strcpy(const_path, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts");

	char make_sure_path[512];
	char write_value[512];

	char full_path[1024];
	char curr_user_choice[512];
	DWORD curr_user_choice_size = 512;

	// 5. Explorer에 해당 확장자에 대한 실행 프로그램 지정
	//    이곳의 Key내부 속성 값들은 변경불가, 따라서 삭제후 새로 만들어야 함
	// HKEY_CURRENT_USER
	// Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\
	//                                                             .{my_type}/UserChoice : 사용자전용
	//-----------------------------------------------------------------------------------------------
	// -> "Progid" : REG_SZ : {my_app_name}.<my_type}
	sprintf(make_sure_path, ".%s\\UserChoice", ext);
	sprintf(write_value, "%s.%s", my_app_name_without_ext, ext);
	sprintf(full_path, "%s\\%s", const_path, make_sure_path);
	if ((*errp = Dz1WinRegKeyA_getNamedValueSZ(HKEY_CURRENT_USER, full_path, "Progid", curr_user_choice, &curr_user_choice_size)).code != 0 ||
		strcmp(write_value, curr_user_choice) != 0)
	{
		bool_t deleted = FALSE, written = FALSE;
		int status = RegDeleteKeyA(HKEY_CURRENT_USER, full_path);
		if (status != ERROR_SUCCESS) ERR_SET_OUT(errp, status);
		else
		{
			deleted = TRUE;
			if ((*errp = Dz1WinRegA_SafeSetNamedSZ(HKEY_CURRENT_USER, const_path, make_sure_path, "Progid", write_value, &written)).code) ERR_OUT_RET(errp, err);
			(*ret) = deleted || written ? TRUE : FALSE;
		}
	}
	return err;
}

static Dz1Error _regMyTypeW_ExplorerExt(wstr_t ext, wstr_t my_app_name_without_ext, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	(*ret) = FALSE;

	wchar_t const_path[64];
	wcscpy(const_path, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts");

	wchar_t make_sure_path[512];
	wchar_t write_value[512];

	wchar_t full_path[1024];
	wchar_t curr_user_choice[512];
	DWORD curr_user_choice_size = 512;

	// 5. Explorer에 해당 확장자에 대한 실행 프로그램 지정
	//    이곳의 Key내부 속성 값들은 변경불가, 따라서 삭제후 새로 만들어야 함
	// HKEY_CURRENT_USER
	// Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\
	//                                                             .{my_type}/UserChoice : 사용자전용
	//-----------------------------------------------------------------------------------------------
	// -> "Progid" : REG_SZ : {my_app_name}.<my_type}
	wsprintfW(make_sure_path, L".%s\\UserChoice", ext);
	wsprintfW(write_value, L"%s.%s", my_app_name_without_ext, ext);
	wsprintfW(full_path, L"%s\\%s", const_path, make_sure_path);
	if ((*errp = Dz1WinRegKeyW_getNamedValueSZ(HKEY_CURRENT_USER, full_path, L"Progid", curr_user_choice, &curr_user_choice_size)).code != 0 ||
		wcscmp(write_value, curr_user_choice) != 0)
	{
		bool_t deleted = FALSE, written = FALSE;
		int status = RegDeleteKeyW(HKEY_CURRENT_USER, full_path);
		if (status != ERROR_SUCCESS) ERR_SET_OUT(errp, status);
		else
		{
			deleted = TRUE;
			if ((*errp = Dz1WinRegW_SafeSetNamedSZ(HKEY_CURRENT_USER, const_path, make_sure_path, L"Progid", write_value, &written)).code) ERR_OUT_RET(errp, err);
			(*ret) = deleted || written ? TRUE : FALSE;
		}
	}
	return err;
}
// Set Explorer FileExt
///////////////////////////////////////

///////////////////////////////////////
// Check File Association
bool_t Dz1WinRegA_chkTypeAssociation(str_t my_type, str_t full_path_name_ext, int icon_idx)
{
	bool_t ret = FALSE;

	DZ1_ERROR_SAFE_VAR(errp, err);

	char app_path[2048];
	char app_name_ext[512];
	char app_name[256];
	char app_ext[128];

	if		((*errp = Dz1FileNameA_splitPathName(app_path, app_name_ext, full_path_name_ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileNameA_splitNameExt(app_name, app_ext, app_name_ext)).code) ERR_OUT(errp);
	else if (_regMyTypeIsOwnA_basic(my_type, app_name) == TRUE &&
			 _regMyTypeIsOwnA_iconAndCmd(my_type, app_name, full_path_name_ext, icon_idx) == TRUE &&
			 _regMyTypeIsOwnA_ExplorerExt(my_type, app_name) == TRUE) ret = TRUE;

	return ret;
}

bool_t Dz1WinRegW_chkTypeAssociation(wstr_t my_type, wstr_t full_path_name_ext, int icon_idx)
{
	bool_t ret = FALSE;

	DZ1_ERROR_SAFE_VAR(errp, err);

	wchar_t app_path[2048];
	wchar_t app_name_ext[512];
	wchar_t app_name[256];
	wchar_t app_ext[128];

	if		((*errp = Dz1FileNameW_splitPathName(app_path, app_name_ext, full_path_name_ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileNameW_splitNameExt(app_name, app_ext, app_name_ext)).code) ERR_OUT(errp);
	else if (_regMyTypeIsOwnW_basic(my_type, app_name) == TRUE &&
			 _regMyTypeIsOwnW_iconAndCmd(my_type, app_name, full_path_name_ext, icon_idx) == TRUE &&
			 _regMyTypeIsOwnW_ExplorerExt(my_type, app_name) == TRUE) ret = TRUE;

	return ret;
}
// Check File Association
///////////////////////////////////////

///////////////////////////////////////
// Set File Association

/*
*** 확장자등록

1. 기본정보 등록
HKEY_CURRENT_USER/Software/Classes/.{my_type}	: 사용자 전용
-> (default) REG_SZ {my_app_name}.{my_type}

2. App과 Type을 Mapping
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}
-> (default) REG_SZ "{description of this type}"

3. Icon 설정
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}/DefaultIcon
-> (default) REG_SZ {full path of icon resource file}[,{icon_idx}]

4. 실행 방법 설정
HKEY_CURRENT_USER/Software/Classes/{my_app_name}.{my_type}/Shell/Open/Command
-> (default) REG_SZ "{full path of application with ext}" "%1"

PS:
HKEY_CLASSES_ROOT/{my_type}						: 하위호환
자동으로 HKEY_CURRENT_USER/Software/Classes로 부터 미러링 된다


5. Explorer에 해당 확장자에 대한 실행 프로그램 지정
HKEY_CURRENT_USER/Software/Microsoft/Windows/CurrentVersion/Explorer/FileExts/.{my_type}/UserChoice : 사용자전용
-> "Progid" : REG_SZ : {my_app_name}.<my_type}
*/

Dz1Error Dz1WinRegA_setTypeAssociation(str_t my_type, str_t full_path_name_ext, int icon_idx, str_t description, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t basic_changed = FALSE, icon_changed = FALSE, explorer_changed = FALSE;
	(*ret) = FALSE;

	char app_path[2048];
	char app_name_ext[512];
	char app_name[256];
	char app_ext[128];

	if		((*errp = Dz1FileNameA_splitPathName(app_path, app_name_ext, full_path_name_ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileNameA_splitNameExt(app_name, app_ext, app_name_ext)).code) ERR_OUT(errp);

	else if ((*errp = _regMyTypeA_basic(my_type,			app_name,					  description,	&basic_changed)).code) ERR_OUT(errp);
	else if ((*errp = _regMyTypeA_IconAndCmd(my_type,	app_name, full_path_name_ext, icon_idx,		&icon_changed)).code) ERR_OUT(errp);
	else if ((*errp = _regMyTypeA_ExplorerExt(my_type,	app_name,									&explorer_changed)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	(*ret) = basic_changed || icon_changed || explorer_changed ? TRUE : FALSE;

	return err;
}

Dz1Error Dz1WinRegW_setTypeAssociation(wstr_t my_type, wstr_t full_path_name_ext, int icon_idx, wstr_t description, bool_t *ret_changed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _ret_changed, *ret = ret_changed ? ret_changed : &_ret_changed;
	bool_t basic_changed = FALSE, icon_changed = FALSE, explorer_changed = FALSE;
	(*ret) = FALSE;

	wchar_t app_path[2048];
	wchar_t app_name_ext[512];
	wchar_t app_name[256];
	wchar_t app_ext[128];

	if		((*errp = Dz1FileNameW_splitPathName(app_path, app_name_ext, full_path_name_ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileNameW_splitNameExt(app_name, app_ext, app_name_ext)).code) ERR_OUT(errp);

	else if ((*errp = _regMyTypeW_basic(my_type,		app_name,					  description,	&basic_changed)).code) ERR_OUT(errp);
	else if ((*errp = _regMyTypeW_IconAndCmd(my_type,	app_name, full_path_name_ext, icon_idx,		&icon_changed)).code) ERR_OUT(errp);
	else if ((*errp = _regMyTypeW_ExplorerExt(my_type,	app_name,									&explorer_changed)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	(*ret) = basic_changed || icon_changed || explorer_changed ? TRUE : FALSE;

	return err;
}
// Set File Association
///////////////////////////////////////
