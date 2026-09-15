#ifndef DZ1_SYSTEM_INFO_H
#define DZ1_SYSTEM_INFO_H

#include <dz1_system_info_def.h>

// Linux	: abs-path of "{user_home_path}/MyDocuments"
// Windows	: "C:\\Documents and Settings\\{username}\\My Documents"
DZ1_CPPLINK bool_t Dz1SystemInfoA_getUserPersonalPath(str_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1SystemInfoA_getUserAppDataPath(str_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err);

// abs path of current process file
DZ1_CPPLINK ssize_t Dz1SystemInfoA_getProcessFilename(str_t dst, u32_t dst_size, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK bool_t Dz1SystemInfoW_getUserPersonalPath(wstr_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1SystemInfoW_getUserAppDataPath(wstr_t dst, u32_t dst_size, bool_t create_if_not_exist, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1SystemInfoW_getProcessFilename(wstr_t dst, u32_t dst_size, Dz1Error *err);
#ifdef UNICODE
#define Dz1SystemInfo_getUserPersonalPath			Dz1SystemInfoW_getUserPersonalPath
#define Dz1SystemInfo_getUserAppDataPath			Dz1SystemInfoW_getUserAppDataPath
#define Dz1SystemInfo_getProcessFilename			Dz1SystemInfoW_getProcessFilename
#else // UNICODE
#define Dz1SystemInfo_getUserPersonalPath			Dz1SystemInfoA_getUserPersonalPath
#define Dz1SystemInfo_getUserAppDataPath			Dz1SystemInfoA_getUserAppDataPath
#define Dz1SystemInfo_getProcessFilename			Dz1SystemInfoA_getProcessFilename
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1SystemInfo_getUserPersonalPath			Dz1SystemInfoA_getUserPersonalPath
#define Dz1SystemInfo_getUserAppDataPath			Dz1SystemInfoA_getUserAppDataPath
#define Dz1SystemInfo_getProcessFilename			Dz1SystemInfoA_getProcessFilename
#endif

#endif // DZ1_SYSTEM_INFO_H
