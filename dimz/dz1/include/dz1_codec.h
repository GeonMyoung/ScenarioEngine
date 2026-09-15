#ifndef DZ1_CODEC_H
#define DZ1_CODEC_H

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_timeval.h>
#include <dz1_bin.h>
#define DZ1_CODEC_ERR_RET(errp)\
	do {\
		if ((errp)->code != E2BIG) ERR_OUT(errp);\
		return -1;\
	} while(0)

#define DZ1_CODEC_ERR(errp, ret) do { if ((errp)->code != E2BIG) ERR_OUT(errp); (ret) = -1; } while(0)

#define DZ1_CODEC_ERRSET_RET(errp, errcode)\
	do {\
		if ((errcode) == E2BIG) Dz1Error_set(errp, errcode);\
		else ERR_SET_OUT(errp, errcode);\
		return -1;\
	} while(0)

#define DZ1_CODEC_ERRSET(errp, errcode, ret) \
	do {\
		if (errcode == E2BIG) Dz1Error_set(errp, errcode);\
		else ERR_SET_OUT(errp, errcode);\
		(ret) = -1;\
	} while(0)

#define DZ1_CODEC_APPLY(cp, cpSize, copied, result) \
	do {\
		if ((cp)) (cp) += (copied);\
		(cpSize) -= (copied);\
		(result) += copied;\
	} while(0)

#define DZ1_CODEC_FUNC(cp, size, result, enc, errp)	\
	do {\
		ssize_t copied;\
		if ((copied = enc) < 0)	DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, copied, result);\
	} while(0)

#define DZ1_CODEC_FUNC_Q(cp, size, result, enc, errp)	\
	do {\
		ssize_t copied;\
		if ((copied = enc) < 0)	return -1;\
		else DZ1_CODEC_APPLY(cp, size, copied, result);\
	} while(0)

DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get1Byte(u8_t *cp, size_t cpSize, u8_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put1Byte(u8_t *cp, size_t cpSize, u8_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get2Byte(u8_t *cp, size_t cpSize, u16_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __get2Byte(u8_t *cp, size_t cpSize, u16_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put2Byte(u8_t *cp, size_t cpSize, u16_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __put2Byte(u8_t *cp, size_t cpSize, u16_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get4Byte(u8_t *cp, size_t cpSize, u32_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __get4Byte(u8_t *cp, size_t cpSize, u32_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put4Byte(u8_t *cp, size_t cpSize, u32_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __put4Byte(u8_t *cp, size_t cpSize, u32_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get8Byte(u8_t *cp, size_t cpSize, u64_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __get8Byte(u8_t *cp, size_t cpSize, u64_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put8Byte(u8_t *cp, size_t cpSize, u64_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __put8Byte(u8_t *cp, size_t cpSize, u64_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _getByte(u8_t *cp, size_t cpSize, u8_t *dst, size_t dstSize, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _putByte(u8_t *cp, size_t cpSize, u8_t *src, size_t srcSize, Dz1Error *errp);

///////////////////////////////////////////////////////////////////////////////
// this function treat Zero-Length string as NULL
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get8str(u8_t *cp, size_t cpSize, str_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _get16str(u8_t *cp, size_t cpSize, str_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __get16str(u8_t *cp, size_t cpSize, str_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put8str(u8_t *cp, size_t cpSize, str_t  src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _put16str(u8_t *cp, size_t cpSize, str_t  src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t __put16str(u8_t *cp, size_t cpSize, str_t  src, Dz1Error *errp);
// this function treat Zero-Length string as NULL
///////////////////////////////////////////////////////////////////////////////

// DZ1_CPPLINK DZ1_DLLPORT size_t		 Dz1Codec_Base64EncLen(size_t size);	// Binary to Letters
// DZ1_CPPLINK DZ1_DLLPORT size_t		 Dz1Codec_Base64DecLen(size_t size);	// Letters to Binary

//DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Codec_Base64BlockEncA(char    dst[4], /* always 4 */   u8_t *src, size_t size, Dz1Error *errp);	// return consume byte counts
//DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Codec_Base64BlockDecA(u8_t    dst[3], size_t *outsize, char *src, size_t cnt, Dz1Error *errp);	// return consume byte counts

// DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1Codec_Base64EncodeA(u8_t *src, ssize_t src_size, Dz1Error *err);
// DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1Codec_Base64DecodeA(str_t src, ssize_t src_len, Dz1Error *err);

// #ifndef UNIX_SYSTEM // modified by gm
//DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Codec_Base64BlockEncW(wchar_t dst[4], /* always 4 */	  u8_t *src, size_t size, Dz1Error *errp);	// return consume letter counts
//DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Codec_Base64BlockDecW(u8_t    dst[3], size_t *outsize, wchar_t *src, size_t cnt, Dz1Error *errp);	// return consume letter counts

// DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1Codec_Base64EncodeW(u8_t *src, ssize_t src_size, Dz1Error *err);
// DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1Codec_Base64DecodeW(wstr_t src, ssize_t src_len, Dz1Error *err);
// #ifdef UNICODE
// #define Dz1Codec_Base64BlockEnc			Dz1Codec_Base64BlockEncW
// #define Dz1Codec_Base64BlockDec			Dz1Codec_Base64BlockDecW
// #define Dz1Codec_Base64Encode			Dz1Codec_Base64EncodeW
// #define Dz1Codec_Base64Decode			Dz1Codec_Base64DecodeW
// #else // UNICODE
// #define Dz1Codec_Base64BlockEnc			Dz1Codec_Base64BlockEncA
// #define Dz1Codec_Base64BlockDec			Dz1Codec_Base64BlockDecA
// #define Dz1Codec_Base64Encode			Dz1Codec_Base64EncodeA
// #define Dz1Codec_Base64Decode			Dz1Codec_Base64DecodeA
// #endif // UNICODE
// #else // UNIX_SYSTEM
// #define Dz1Codec_Base64BlockEnc			Dz1Codec_Base64BlockEncA
// #define Dz1Codec_Base64BlockDec			Dz1Codec_Base64BlockDecA
// #define Dz1Codec_Base64Encode			Dz1Codec_Base64EncodeA
// #define Dz1Codec_Base64Decode			Dz1Codec_Base64DecodeA
// #endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT ssize_t _getBase64(u8_t *dst, size_t dst_size, u8_t *src, size_t src_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _putBase64(u8_t *dst, size_t dst_size, u8_t *src, size_t src_size, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT ssize_t _putBase64StrA(u8_t *dst, size_t dst_size, str_t src, Dz1Error *err);
#ifdef WIN32
DZ1_CPPLINK DZ1_DLLPORT ssize_t _putBase64StrW(u8_t *dst, size_t dst_size, wstr_t src, Dz1Error *err);
#endif
#ifdef UNICODE
#define _putBase64Str			_putBase64StrW
#else
#define _putBase64Str			_putBase64StrA
#endif

// 7 byte date-time hex encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t _time_hex_enc(u8_t *dst, size_t size, time_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _time_hex_dec(time_t *dst, u8_t *src, size_t size, Dz1Error *err);

// 7 byte date-time(yyyymmddhhmiss) bcd encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t _time_bcd_enc(u8_t *dst, size_t size, time_t *src, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _time_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);

// 4 byte date(yyyymmdd) bcd encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t _date_bcd_enc(u8_t *dst, size_t size, time_t *src, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _date_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);

// 3 byte time(hhmmss) bcd encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t _clock_bcd_enc(u8_t *dst, size_t size, time_t *_src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _clock_bcd_dec(time_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);


///////////////////////////////////////////////////////////////////////////////
// BCD CODEC Helper
///////////////////////////////////////////////////////////////////////////////
// Take n byte Decimal Digit to u32_t
DZ1_CPPLINK DZ1_DLLPORT ssize_t _getDigit(u8_t *cp, size_t size, u32_t *dst, size_t len, Dz1Error *errp);

// Take n byte Binary Coded Digit to u32_t
DZ1_CPPLINK DZ1_DLLPORT ssize_t _getBCD(u8_t *cp, size_t size, u32_t *dst, size_t len, Dz1Error *errp);

///////////////////////////////////////////////////////////////////////////////
// CODEC API Entry Helper
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u8_bcd_enc(u8_t *dst, size_t size, u8_t *src, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u8_bcd_dec(u8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u8_hex_enc(u8_t *dst, size_t size, u8_t *src, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u8_hex_dec(u8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT ssize_t _u16_bcd_enc(u8_t *dst, size_t size, u16_t *src, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u16_bcd_dec(u16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u16_hex_enc(u8_t *dst, size_t size, u16_t *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t _u16_hex_dec(u16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err);


///////////////////////////////////////////////////////////////////////////////
// struct timeval helper
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT Dz1TimeVal *Dz1TimeVal_gen(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1TimeVal_enc(u8_t *dst, size_t size, Dz1TimeVal *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1TimeVal_dec(Dz1TimeVal *dst, u8_t *src, size_t size, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// HEX DIGIT Codec Helper
///////////////////////////////////////////////////////////////////////////////
// Take 2 byte Hex Digit to u8_t value
DZ1_CPPLINK DZ1_DLLPORT ssize_t _getHexDigit(u8_t *cp, size_t size, u8_t *dst, Dz1Error *errp);

///////////////////////////////////////////////////////////////////////////////
// Encode 1 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE1(cp, size, src, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _put1Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)
#define _DZ1_ENCODE1(cp, size, src, errp, ret) DZ1_ENCODE1(cp, size, src, errp, ret)

///////////////////////////////////////////////////////////////////////////////
// Decode 1 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE1(dstp, cp, size, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _get1Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)
#define _DZ1_DECODE1(dstp, cp, size, errp, ret) DZ1_DECODE1(dstp, cp, size, errp, ret) 

///////////////////////////////////////////////////////////////////////////////
// Encode 2 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE2(cp, size, src, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _put2Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_ENCODE2(cp, size, src, errp, ret) \
	do {\
	ssize_t __status__;\
	if ((__status__ = __put2Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Decode 2 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE2(dstp, cp, size, errp, ret) \
	do {\
	ssize_t __status__;\
	if ((__status__ = _get2Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_DECODE2(dstp, cp, size, errp, ret) \
	do {\
	ssize_t __status__;\
	if ((__status__ = __get2Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Encode 4 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE4(cp, size, src, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _put4Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_ENCODE4(cp, size, src, errp, ret) \
	do {\
	ssize_t __status__;\
	if ((__status__ = __put4Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Decode 4 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE4(dstp, cp, size, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _get4Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_DECODE4(dstp, cp, size, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = __get4Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Encode 8 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE8(cp, size, src, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _put8Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_ENCODE8(cp, size, src, errp, ret) \
	do {\
	ssize_t __status__;\
	if ((__status__ = __put8Byte((cp), (size), (src), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Decode 8 Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE8(dstp, cp, size, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _get8Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

#define _DZ1_DECODE8(dstp, cp, size, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = __get8Byte((cp), (size), (dstp), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, size, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Encode Multi Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE(cp, cpSize, src, srcSize, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _putByte((cp), (cpSize), (src), (srcSize), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, cpSize, __status__, ret);\
	} while(0)
#define _DZ1_ENCODE(cp, cpSize, src, srcSize, errp, ret) DZ1_ENCODE(cp, cpSize, src, srcSize, errp, ret)

///////////////////////////////////////////////////////////////////////////////
// Decode Multi Byte
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE(dst, dstSize, cp, cpSize, errp, ret) \
	do {\
		ssize_t __status__;\
		if ((__status__ = _getByte((cp), (cpSize), (dst), (dstSize), (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, cpSize, __status__, ret);\
	} while(0)
#define _DZ1_DECODE(dst, dstSize, cp, cpSize, errp, ret) DZ1_DECODE(dst, dstSize, cp, cpSize, errp, ret)

///////////////////////////////////////////////////////////////////////////////
// Encode PAD
///////////////////////////////////////////////////////////////////////////////
#define DZ1_ENCODE_PAD(cp, cpSize, padSize, errp, ret) \
	do {\
		u8_t __pad__[padSize] = { 0, };\
		ssize_t __status__;\
		if ((__status__ = _putByte((cp), (cpSize), __pad__, padSize, (errp))) < 0) DZ1_CODEC_ERR_RET(errp);\
		else DZ1_CODEC_APPLY(cp, cpSize, __status__, ret);\
	} while(0)

///////////////////////////////////////////////////////////////////////////////
// Decode PAD
///////////////////////////////////////////////////////////////////////////////
#define DZ1_DECODE_PAD(padSize, cp, size, errp, ret) DZ1_CODEC_APPLY(cp, size, padSize, ret)

static __inline__ ssize_t _dz1_s64_enc(u8_t *dst, size_t size, s64_t *src, void *param, Dz1Error *err) { return Dz1s64_enc(dst, src, err); }
static __inline__ ssize_t _dz1_s64_dec(s64_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1s64_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_s32_enc(u8_t *dst, size_t size, s32_t *src, void *param, Dz1Error *err) { return Dz1s32_enc(dst, src, err); }
static __inline__ ssize_t _dz1_s32_dec(s32_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1s32_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_s16_enc(u8_t *dst, size_t size, s16_t *src, void *param, Dz1Error *err) { return Dz1s16_enc(dst, src, err); }
static __inline__ ssize_t _dz1_s16_dec(s16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1s16_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_s8_enc(u8_t *dst, size_t size, s8_t *src, void *param, Dz1Error *err) { return Dz1s8_enc(dst, src, err); }
static __inline__ ssize_t _dz1_s8_dec(s8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1s8_dec(&dst, src, err); }

static __inline__ ssize_t _dz1_u64_enc(u8_t *dst, size_t size, u64_t *src, void *param, Dz1Error *err) { return Dz1u64_enc(dst, src, err); }
static __inline__ ssize_t _dz1_u64_dec(u64_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1u64_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_u32_enc(u8_t *dst, size_t size, u32_t *src, void *param, Dz1Error *err) { return Dz1u32_enc(dst, src, err); }
static __inline__ ssize_t _dz1_u32_dec(u32_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1u32_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_u16_enc(u8_t *dst, size_t size, u16_t *src, void *param, Dz1Error *err) { return Dz1u16_enc(dst, src, err); }
static __inline__ ssize_t _dz1_u16_dec(u16_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1u16_dec(&dst, src, err); }
static __inline__ ssize_t _dz1_u8_enc(u8_t *dst, size_t size, u8_t *src, void *param, Dz1Error *err) { return Dz1u8_enc(dst, src, err); }
static __inline__ ssize_t _dz1_u8_dec(u8_t *dst, u8_t *src, size_t size, void *param, Dz1Error *err) { return Dz1u8_dec(&dst, src, err); }

typedef struct Dz1ListCodecArg
{
	u8_t *cp;
	size_t size;
	ssize_t ret;
	void *option;
} Dz1ListCodecArg;

#define Dz1ListCodecArg_init(ap, cp, size, opt)\
	do {\
		(ap)->cp = (cp);\
		(ap)->size = (size);\
		(ap)->ret = 0;\
		(ap)->option = (opt);\
	} while(0)

typedef Dz1ListCodecArg Dz1ListEncArg;

typedef struct Dz1CodecApiMap
{
	int present;
	u32_t opcode;
	void *(*gen)(Dz1Error *errp);
	ssize_t (*enc)(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
	ssize_t (*dec)(void *_dst, u8_t *dst, size_t size, void *param, Dz1Error *err);
} Dz1CodecApiMap;
#define Dz1CodecApi_STRUCT(stname, opcode, mbType, mbName)	{ stname##Present_##mbName, opcode, (Dz1GenFunc)mbType##_gen, mbType##_enc, mbType##_dec }
#define Dz1CodecApi_VAR(stname, opcode, apiPrefix, mbName)	{ stname##Present_##mbName, opcode, NULL, apiPrefix##_enc, apiPrefix##_dec }
#define Dz1CodecApi_VOID(stname, opcode, mbName)			{ stname##Present_##mbName, opcode, NULL, NULL, NULL }
#define Dz1CodecApiMapEntry_last		{ -1 }

/*
*** Structure Type
///////////////////////////////////////////////////////////////////////////////
// <type> CODEC API
static void *<type>_gen(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	<type> *ret = <type>_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static ssize_t <type>_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	<type> *src = (<type> *)_src;
	if (src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = dst;
	}
	return ret;
}

static ssize_t <type>_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	<type> *dst = (<type> *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
	}
	return ret;
}
// <type> CODEC API
///////////////////////////////////////////////////////////////////////////////

*** Variable Type
///////////////////////////////////////////////////////////////////////////////
// <type> CODEC API
static ssize_t <type>_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (_src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		<type> src = *(<type> *)_src;
		u8_t *cp = dst;
	}
	return ret;
}

static ssize_t <type>_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	<type> *dst = (<type> *)_dst;
	if (dst == NULL || src == NULL) DZ1_CODEC_ERRSET_RET(errp, EINVAL);
	else
	{
		u8_t *cp = src;
	}
	return ret;
}
// <type> CODEC API
///////////////////////////////////////////////////////////////////////////////
*/

DZ1_CPPLINK DZ1_DLLPORT Dz1CodecApiMap *Dz1CodecApiMap_findByPresent(Dz1CodecApiMap *table, int present);
DZ1_CPPLINK DZ1_DLLPORT Dz1CodecApiMap *Dz1CodecApiMap_findByOpCode(Dz1CodecApiMap *table, u32_t opcode);

// src->present까지 포함하여 Encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBitEndian, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec64_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec64_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, size_t codeLen, bool_t codeIsBigEndian, Dz1Error *err);

// src->present를 포함하지 않고 Encoding
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec_encByPresent(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec_decByPresent(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec64_encByPresent(u8_t *dst, size_t size, void *_src, void *param, Dz1CodecApiMap *table, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1UnionCodec64_decByPresent(void *_dst, u8_t *src, size_t size, void *param, Dz1CodecApiMap *table, Dz1Error *err);

typedef ssize_t (*Dz1EncodeFunc)(u8_t *dst, size_t size, void *src, void *param, Dz1Error *err);
typedef ssize_t (*Dz1DecodeFunc)(void *dst, u8_t *src, size_t size, void *param, Dz1Error *err);
#endif

