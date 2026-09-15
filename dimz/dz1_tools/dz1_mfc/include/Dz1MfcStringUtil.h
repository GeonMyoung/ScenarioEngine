#ifndef DZ1_MFC_STRING_UTIL_H
#define DZ1_MFC_STRING_UTIL_H

#include <dz1_mfc.h>

DZ1_CPPLINK void Dz1MfcUtilFormattedNumber(CString &dst, s64_t v);
DZ1_CPPLINK void Dz1MfcUtilUnitNumberStr(CString &dst, u64_t v, u8_t basis, u8_t unit_exp, Dz1Str unit_name_arr[], int unit_name_arr_cnt);
DZ1_CPPLINK void Dz1MfcUtil1KNumberStr(CString &dst, u64_t v);
DZ1_CPPLINK void Dz1MfcUtil1024NumberStr(CString &dst, u64_t v);
DZ1_CPPLINK void Dz1MfcUtilFormattedTime(CString &dst, s64_t sec);
DZ1_CPPLINK void Dz1MfcUtilFormattedTimeUS(CString &dst, s64_t _usec);
#endif