#include <dz1_system_info.h>

// implement library functions here
#ifdef UNIX_SYSTEM
bool_t Dz1SystemInfoA_getUserPersonalPath(str_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err)
{
#error implement it
	DZ1_ERROR_SAFE_PTR(errp, err);
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1MyselfInfoA_getProcessFilename(str_t dst, u32_t dst_size, Dz1Error *err)
{
#error implement it
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	return errp->code == 0 ? ret : -1;
}
#else	// Windows System
#include <ShlObj.h>
#pragma comment(lib, "shell32.lib")

bool_t Dz1SystemInfoA_getUserPersonalPath(str_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err)
{	
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst_size < MAX_PATH) ERR_SET_OUT(errp, ENOMEM);
	if (SHGetSpecialFolderPathA(NULL, dst, CSIDL_PERSONAL, create_if_not_exist) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SystemInfoW_getUserPersonalPath(wstr_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst_size < MAX_PATH) ERR_SET_OUT(errp, ENOMEM);
	if (SHGetSpecialFolderPathW(NULL, dst, CSIDL_PERSONAL, create_if_not_exist) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SystemInfoA_getUserAppDataPath(str_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst_size < MAX_PATH) ERR_SET_OUT(errp, ENOMEM);
	if (SHGetSpecialFolderPathA(NULL, dst, CSIDL_APPDATA, create_if_not_exist) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1SystemInfoW_getUserAppDataPath(wstr_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst_size < MAX_PATH) ERR_SET_OUT(errp, ENOMEM);
	if (SHGetSpecialFolderPathW(NULL, dst, CSIDL_APPDATA, create_if_not_exist) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

ssize_t Dz1SystemInfoA_getProcessFilename(str_t dst, u32_t dst_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	DWORD nSize = dst_size - 1, status;
	if (dst == NULL || dst_size == 0 || nSize == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((status = (ssize_t)GetModuleFileNameA(NULL, dst, nSize)) == 0) ERR_SET_OUT(errp, GetLastError());
	else if (status == nSize)
	{
		DWORD err_code = GetLastError();
		if (err_code == 0) ret = (ssize_t)status;
		else ERR_SET_OUT(errp, err_code);
	}
	else if (status == 0) ERR_SET_OUT(errp, EFAULT);
	else ret = (ssize_t)status;
	return errp->code == 0 ? ret : -1;
}

ssize_t Dz1SystemInfoW_getProcessFilename(wstr_t dst, u32_t dst_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	DWORD nSize = dst_size - 1, status;
	if (dst == NULL || dst_size == 0 || nSize == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((status = (ssize_t)GetModuleFileNameW(NULL, dst, nSize)) == 0) ERR_SET_OUT(errp, GetLastError());
	else if (status == nSize)
	{
		DWORD err_code = GetLastError();
		if (err_code == 0) ret = (ssize_t)status;
		else ERR_SET_OUT(errp, err_code);
	}
	else if (status == 0) ERR_SET_OUT(errp, EFAULT);
	else ret = (ssize_t)status;
	return errp->code == 0 ? ret : -1;
}
#endif	// UNIX_SYSTEM

