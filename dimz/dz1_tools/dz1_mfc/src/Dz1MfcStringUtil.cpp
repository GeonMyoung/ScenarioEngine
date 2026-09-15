#include "stdafx.h"
#include "dz1_mfc.h"
#include "Dz1MfcStringUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Comma presented numeric string
void Dz1MfcUtilFormattedNumber(CString &dst, s64_t v)
{
	bool_t minus = FALSE;
	u16_t arr[6] = { 0, };
	int cnt = 0;

	if (v < 0)
	{
		minus = TRUE;
		v = -v;
	}

	if (v > 0)
	{
		while(v > 999)
		{
			arr[cnt++] = v % 1000;
			v = v / 1000;
		}

		if (v) arr[cnt] = (u16_t)(v & 0xFFFF); else cnt--;

		CString temp;
		dst.Format(Dz1Text("%s%u"), minus ? Dz1Text("-") : Dz1Text(""), arr[cnt--]);
		while(cnt >= 0)
		{
			temp.Format(Dz1Text(",%03u"), arr[cnt--]);
			dst += temp;
		}
	}
	else
	{
		dst = Dz1Text("0");
	}
}
// Comma presented numeric string
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Unit Scaled Numeric String : Unit = bias ^ unit_exp
void Dz1MfcUtilUnitNumberStr(CString &dst, u64_t v, u8_t basis, u8_t unit_exp, Dz1Str unit_name_arr[], int unit_name_arr_cnt)
{	// 정수부가 최소 1이상이어야 한다.
	u64_t unit = 1, u_exp = unit_exp;
	u64_t decimal = v, fraction = 0;
	int idx = 0;

	while(u_exp--) unit *= basis;

	while(idx < (unit_name_arr_cnt - 1) && decimal >= unit)
	{
		fraction = decimal % unit;
		decimal = decimal / unit;
		idx++;
	}

	CString strDecimal;
	strDecimal.Format(_T("%u"), decimal);

	CString strFraction, strFractionFmt;
	strFractionFmt.Format(_T("%%0%uu"), unit_exp);
	strFraction.Format(strFractionFmt.GetBuffer(), fraction);

	dst = strDecimal;
	dst += _T(".");
	dst += strFraction;
	dst += unit_name_arr[idx];
}
// Unit Scaled Numeric String
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Decimal K unit numeric string (10 ^ 3)
void Dz1MfcUtil1KNumberStr(CString &dst, u64_t v)
{
	Dz1Str arr[] = {
		_T(""),
		_T("K"),
		_T("M"),
		_T("G"),
		_T("T")
	};
	int arr_cnt = 5;
	Dz1MfcUtilUnitNumberStr(dst, v, 10, 3, arr, arr_cnt);
}
// Decimal K unit numeric string (10 ^ 3)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Binary K unit numeric string (2 ^ 10)
void Dz1MfcUtil1024NumberStr(CString &dst, u64_t v)
{
	Dz1Str arr[] = {
		_T(""),
		_T("K"),
		_T("M"),
		_T("G"),
		_T("T")
	};
	int arr_cnt = 5;
	Dz1MfcUtilUnitNumberStr(dst, v, 2, 10, arr, arr_cnt);
}
// Binary K unit numeric string (2 ^ 10)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Formatted time of amount (HH:MM:SS)
void Dz1MfcUtilFormattedTime(CString &dst, s64_t _sec)
{
	u8_t sec = 0;
	u8_t min = 0;
	u32_t hour = 0;

	sec = (u8_t)(_sec % 60); _sec /= 60;
	min = (u8_t)(_sec % 60); _sec /= 60;
	hour = (u32_t)_sec;

	dst.Format(_T("%u:%02u:%02u"), hour, min, sec);
}
// Formatted time of amount (HH:MM:SS)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Formatted time of amount (HH:MM:SS.fff) for micro seconds
void Dz1MfcUtilFormattedTimeUS(CString &dst, s64_t _usec)
{
	u32_t us = 0;
	u8_t sec = 0;
	u8_t min = 0;
	u32_t hour = 0;

	us = (u32_t)(_usec % 1000000);	_usec /= 1000000;
	sec = (u8_t)(_usec % 60);		_usec /= 60;
	min = (u8_t)(_usec % 60);		_usec /= 60;
	hour = (u32_t)_usec;

	dst.Format(_T("%u:%02u:%02u.%03u"), hour, min, sec, us / 1000);
}
// Formatted time of amount (HH:MM:SS.fff) for micro seconds
///////////////////////////////////////////////////////////////////////////////

