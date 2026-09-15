#ifndef DZ1_STDIO_H
#define DZ1_STDIO_H

#include <dz1_bin.h>
//#include <dz1_io_stream.h>

#ifndef UNIX_SYSTEM
#if		_MSC_VER >= 1400
#define FILEPOSt			s64_t
#define DZ1_FSEEK			_fseeki64
#define DZ1_FTELL			_ftelli64
#else //_MSC_VER >= 1400
#define FILEPOSt			long
#define DZ1_FSEEK			fseek
#define DZ1_FTELL			ftell
#endif//_MSC_VER >= 1400
#else //UNIX_SYSTEM
#define FILEPOSt			long
#define DZ1_FSEEK			fseek
#define DZ1_FTELL			ftell
#endif//UNIX_SYSTEM

typedef void *(*Dz1CloneFunc)(void *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// primitive type dump
///////////////////////////////////////
// Unsigned MBCS Dump
DZ1_CPPLINK DZ1_DLLPORT void u64_t_dumpA(u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u32_t_dumpA(u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u16_t_dumpA(u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u8_t_dumpA(u8_t *p, int tab);

DZ1_CPPLINK DZ1_DLLPORT void u64_t_fdumpA(FILE *fp, u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u32_t_fdumpA(FILE *fp, u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u16_t_fdumpA(FILE *fp, u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u8_t_fdumpA(FILE *fp, u8_t *p, int tab);
// Unsigned MBCS Dump
///////////////////////////////////////

///////////////////////////////////////
// Signed MBCS Dump
DZ1_CPPLINK DZ1_DLLPORT void s64_t_dumpA(s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s32_t_dumpA(s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s16_t_dumpA(s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s8_t_dumpA(s8_t *p, int tab);

DZ1_CPPLINK DZ1_DLLPORT void s64_t_fdumpA(FILE *fp, s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s32_t_fdumpA(FILE *fp, s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s16_t_fdumpA(FILE *fp, s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s8_t_fdumpA(FILE *fp, s8_t *p, int tab);
// Signed MBCS Dump
///////////////////////////////////////
#ifndef UNIX_SYSTEM
///////////////////////////////////////
// Unsigned WIDE Dump
DZ1_CPPLINK DZ1_DLLPORT void u64_t_dumpW(u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u32_t_dumpW(u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u16_t_dumpW(u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u8_t_dumpW(u8_t *p, int tab);

DZ1_CPPLINK DZ1_DLLPORT void u64_t_fdumpW(FILE *fp, u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u32_t_fdumpW(FILE *fp, u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u16_t_fdumpW(FILE *fp, u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void u8_t_fdumpW(FILE *fp, u8_t *p, int tab);
// Unsigned WIDE Dump
///////////////////////////////////////

///////////////////////////////////////
// Signed WIDE Dump
DZ1_CPPLINK DZ1_DLLPORT void s64_t_dumpW(s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s32_t_dumpW(s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s16_t_dumpW(s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s8_t_dumpW(s8_t *p, int tab);

DZ1_CPPLINK DZ1_DLLPORT void s64_t_fdumpW(FILE *fp, s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s32_t_fdumpW(FILE *fp, s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s16_t_fdumpW(FILE *fp, s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void s8_t_fdumpA(FILE *fp, s8_t *p, int tab);
// Signed WIDE Dump
///////////////////////////////////////
#ifdef UNICODE
///////////////////////////////////////
// Unsigned Dump in UNICODE
#define						 u64_t_dump			u64_t_dumpW
#define						 u32_t_dump			u32_t_dumpW
#define						 u16_t_dump			u16_t_dumpW
#define						 u8_t_dump			u8_t_dumpW

#define						 u64_t_fdump		u64_t_fdumpW
#define						 u32_t_fdump		u32_t_fdumpW
#define						 u16_t_fdump		u16_t_fdumpW
#define						 u8_t_fdump			u8_t_fdumpW
// Unsigned Dump in UNICODE
///////////////////////////////////////
///////////////////////////////////////
// Signed Dump in UNICODE
#define						 s64_t_dump			s64_t_dumpW
#define						 s32_t_dump			s32_t_dumpW
#define						 s16_t_dump			s16_t_dumpW
#define						 s8_t_dump			s8_t_dumpW

#define						 s64_t_fdump		s64_t_fdumpW
#define						 s32_t_fdump		s32_t_fdumpW
#define						 s16_t_fdump		s16_t_fdumpW
#define						 s8_t_fdump			s8_t_fdumpW
// Signed Dump in UNICODE
///////////////////////////////////////
#else // UNICODE
///////////////////////////////////////
// Unsigned Dump in MBCS
#define						 u64_t_dump			u64_t_dumpA
#define						 u32_t_dump			u32_t_dumpA
#define						 u16_t_dump			u16_t_dumpA
#define						 u8_t_dump			u8_t_dumpA

#define						 u64_t_fdump		u64_t_fdumpA
#define						 u32_t_fdump		u32_t_fdumpA
#define						 u16_t_fdump		u16_t_fdumpA
#define						 u8_t_fdump			u8_t_fdumpA
// Unsigned Dump in MBCS
///////////////////////////////////////
///////////////////////////////////////
// Signed Dump in MBCS
#define						 s64_t_dump			s64_t_dumpA
#define						 s32_t_dump			s32_t_dumpA
#define						 s16_t_dump			s16_t_dumpA
#define						 s8_t_dump			s8_t_dumpA

#define						 s64_t_fdump		s64_t_fdumpA
#define						 s32_t_fdump		s32_t_fdumpA
#define						 s16_t_fdump		s16_t_fdumpA
#define						 s8_t_fdump			s8_t_fdumpA
// Signed Dump in MBCS
///////////////////////////////////////
#endif // UNICODE
#else // UNIX_SYSTEM
///////////////////////////////////////
// Unsigned Dump in UTF8
#define						 u64_t_dump			u64_t_dumpA
#define						 u32_t_dump			u32_t_dumpA
#define						 u16_t_dump			u16_t_dumpA
#define						 u8_t_dump			u8_t_dumpA

#define						 u64_t_fdump		u64_t_fdumpA
#define						 u32_t_fdump		u32_t_fdumpA
#define						 u16_t_fdump		u16_t_fdumpA
#define						 u8_t_fdump			u8_t_fdumpA
// Unsigned Dump in UTF8
///////////////////////////////////////
///////////////////////////////////////
// Signed Dump in UTF8
#define						 s64_t_dump			s64_t_dumpA
#define						 s32_t_dump			s32_t_dumpA
#define						 s16_t_dump			s16_t_dumpA
#define						 s8_t_dump			s8_t_dumpA

#define						 s64_t_fdump		s64_t_fdumpA
#define						 s32_t_fdump		s32_t_fdumpA
#define						 s16_t_fdump		s16_t_fdumpA
#define						 s8_t_fdump			s8_t_fdumpA
// Signed Dump in UTF8
///////////////////////////////////////
#endif // UNIX_SYSTEM

// primitive type dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO ENDIAN Convert Helper Function
DZ1_CPPLINK DZ1_DLLPORT u16_t Dz1Endian2_host2little(u16_t host);
DZ1_CPPLINK DZ1_DLLPORT u16_t Dz1Endian2_little2host(u16_t little);
DZ1_CPPLINK DZ1_DLLPORT u16_t Dz1Endian2_host2big(u16_t host);
DZ1_CPPLINK DZ1_DLLPORT u16_t Dz1Endian2_big2host(u16_t little);

DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Endian4_host2little(u32_t host);
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Endian4_little2host(u32_t little);
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Endian4_host2big(u32_t host);
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1Endian4_big2host(u32_t big);

DZ1_CPPLINK DZ1_DLLPORT u64_t Dz1Endian8_host2little(u64_t host);
DZ1_CPPLINK DZ1_DLLPORT u64_t Dz1Endian8_little2host(u64_t little);
DZ1_CPPLINK DZ1_DLLPORT u64_t Dz1Endian8_host2big(u64_t host);
DZ1_CPPLINK DZ1_DLLPORT u64_t Dz1Endian8_big2host(u64_t big);
// STDIO ENDIAN Convert Helper Function
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT size_t Dz1Kernel_getPhyFreeMem(void);

///////////////////////////////////////////////////////////////////////////////
// Partition Info
typedef struct Dz1KernelPartitionEntry
{
	str_t name;
	u64_t totalByte;
	u64_t freeByte;
} Dz1KernelPartitionEntry;
DZ1_CPPLINK DZ1_DLLPORT void Dz1KernelPartitionEntryA_dump(Dz1KernelPartitionEntry *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1KernelPartitionEntryW_dump(Dz1KernelPartitionEntry *p, int tab);
#ifdef UNICODE
#define						 Dz1KernelPartitionEntry_dump		Dz1KernelPartitionEntryW_dump
#else // UNICODE
#define						 Dz1KernelPartitionEntry_dump		Dz1KernelPartitionEntryA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define						 Dz1KernelPartitionEntry_dump		Dz1KernelPartitionEntryA_dump
#endif // UNIX_SYSTEM
typedef struct Dz1KernelPartitionInfo
{
	Dz1KernelPartitionEntry *entries;
	size_t numOfEntries;
} Dz1KernelPartitionInfo;
DZ1_CPPLINK DZ1_DLLPORT Dz1KernelPartitionInfo	*Dz1Kernel_getPartitionInfo(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1Kernel_putPartitionInfo(Dz1KernelPartitionInfo *p);
static __inline__ void							 Dz1Kernel_getPartitionInfo_cancel(void *ptr)
{
	Dz1KernelPartitionInfo *p = (Dz1KernelPartitionInfo *)ptr;
	Dz1Kernel_putPartitionInfo(p);
}
static __inline__ void							 Dz1Kernel_getPartitionInfo_cancelAndSetNull(void *ptr)
{
	Dz1KernelPartitionInfo **p = (Dz1KernelPartitionInfo **)ptr;
	Dz1Kernel_putPartitionInfo(*p); *p = NULL;
}

#define Dz1KernelPartitionInfo_del				 Dz1Kernel_putPartitionInfo
#define Dz1KernelPartitionInfo_delAndSetNull	 Dz1Kernel_getPartitionInfo_cancelAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1KernelPartitionInfoA_dump(Dz1KernelPartitionInfo *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void					 Dz1KernelPartitionInfoW_dump(Dz1KernelPartitionInfo *p, int tab);
#ifdef UNICODE
#define											 Dz1KernelPartitionInfo_dump		Dz1KernelPartitionInfoW_dump
#else // UNICODE
#define											 Dz1KernelPartitionInfo_dump		Dz1KernelPartitionInfoA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define											 Dz1KernelPartitionInfo_dump		Dz1KernelPartitionInfoA_dump
#endif // UNIX_SYSTEM
// Partition Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Print Functions
#define							 Dz1A_fprintf	fprintf
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1A_vfprintf( FILE *fp,		   const str_t fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1A_ftprintf( FILE *fp, int tab, const str_t fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1A_vftprintf(FILE *fp, int tab, const str_t fmt, va_list ap);

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1A_fprintb (FILE *fp,		  void *ptr, size_t size, size_t align);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1A_ftprintb(FILE *fp, int tab, void *ptr, size_t size, size_t align);
#ifndef UNIX_SYSTEM
#define							 Dz1W_fprintf	fwprintf
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1W_vfprintf(	FILE *fp,		   const wstr_t fmt, va_list ap);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1W_ftprintf( FILE *fp, int tab, const wstr_t fmt, ...);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1W_vftprintf(FILE *fp, int tab, const wstr_t fmt, va_list ap);

DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1W_fprintb (FILE *fp,		  void *ptr, size_t size, size_t align);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1W_ftprintb(FILE *fp, int tab, void *ptr, size_t size, size_t align);
#ifdef UNICODE
#define							 Dz1_fprintf				Dz1W_fprintf
#define							 Dz1_vfprintf				Dz1W_vfprintf
#define							 Dz1_ftprintf				Dz1W_ftprintf
#define							 Dz1_vftprintf				Dz1W_vftprintf

#define							 Dz1_fprintb				Dz1W_fprintb
#define							 Dz1_ftprintb				Dz1W_ftprintb
#else // UNICODE
#define							 Dz1_fprintf				Dz1A_fprintf
#define							 Dz1_vfprintf				Dz1A_vfprintf
#define							 Dz1_ftprintf				Dz1A_ftprintf
#define							 Dz1_vftprintf				Dz1A_vftprintf

#define							 Dz1_fprintb				Dz1A_fprintb
#define							 Dz1_ftprintb				Dz1A_ftprintb
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1_fprintf				Dz1A_fprintf
#define							 Dz1_vfprintf				Dz1A_vfprintf
#define							 Dz1_ftprintf				Dz1A_ftprintf
#define							 Dz1_vftprintf				Dz1A_vftprintf

#define							 Dz1_fprintb				Dz1A_fprintb
#define							 Dz1_ftprintb				Dz1A_ftprintb
#endif // UNIX_SYSTEM
// STDIO Print Functions
///////////////////////////////////////////////////////////////////////////////

// Encode/Decode Support
///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC ERROR Macro
#define DZ1_STDIO_ERR_RET(errp)							ERR_OUT_RET( errp, -1 )
#define DZ1_STDIO_ERRSET_RET(errp, code)				ERR_SETOUT_RET( errp, code, -1 )

#define DZ1_STDIO_LOOP_ERR_RET(errp, ret)				do { ERR_OUT(errp); (ret) = -1; } while(0)
#define DZ1_STDIO_LOOP_ERRSET_RET(errp, ret, code)		do { ERR_SET_OUT(errp, code); (ret) = -1; } while(0)
// STDIO File CODEC ERROR Macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Basic READ/WRITE functions
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read1Byte(FILE *fp, u8_t *c, Dz1Error *errp);
//DZ1_CPPLINK DZ1_DLLPORT ssize_t __read2Byte(FILE *fp, u8_t c[2], Dz1Error *errp);		// host endian write
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read2Byte(FILE *fp, u16_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read4Byte(FILE *fp, u32_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read8Byte(FILE *fp, u64_t *c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readByte (FILE *fp, u8_t *buf, size_t readSize, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write1Byte(FILE *fp, u8_t c, Dz1Error *errp);
//DZ1_CPPLINK DZ1_DLLPORT ssize_t __write2Byte(FILE *fp, u8_t c[2], Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write2Byte(FILE *fp, u16_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write4Byte(FILE *fp, u32_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write8Byte(FILE *fp, u32_t c, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeByte (FILE *fp, u8_t *buf, size_t writeSize, Dz1Error *errp);
// STDIO File CODEC Basic READ/WRITE functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Extended READ/WRITE functions
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readDigitA(FILE *fp, u32_t *dst, size_t len, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read8strA (FILE *fp, str_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read16strA(FILE *fp, str_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readLineA(FILE *fp, u8_t *dst, size_t size, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeDigitA(FILE *fp, u32_t src, size_t len, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write8strA (FILE *fp, str_t src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write16strA(FILE *fp, str_t src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeLineA(FILE *fp, u8_t *src, size_t size, Dz1Error *errp);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readDigitW(FILE *fp, u32_t *dst, size_t len, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read8strW (FILE *fp, wstr_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read16strW(FILE *fp, wstr_t *dst, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readLineW(FILE *fp, u8_t *dst, size_t size, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeDigitW(FILE *fp, u32_t src, size_t len, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write8strW (FILE *fp, wstr_t src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write16strW(FILE *fp, wstr_t src, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeLineW(FILE *fp, u8_t *src, size_t size, Dz1Error *errp);

#ifdef	UNICODE
#define _readDigit				 _readDigitW
#define _read8str				 _read8strW
#define _read16str				 _read16strW
#define _readLine				 _readLineW

#define _writeDigit				 _writeDigitW
#define _write8str				 _write8strW
#define _write16str				 _write16strW
#define _writeLine				 _writeLineW
#else	// UNICODE
#define _readDigit				 _readDigitA
#define _read8str				 _read8strA
#define _read16str				 _read16strA
#define _readLine				 _readLineA

#define _writeDigit				 _writeDigitA
#define _write8str				 _write8strA
#define _write16str				 _write16strA
#define _writeLine				 _writeLineA
#endif	// UNICODE
#else	// !UNIX_SYSTEM
#define _readDigit				 _readDigitA
#define _read8str				 _read8strA
#define _read16str				 _read16strA
#define _readLine				 _readLineA

#define _writeDigit				 _writeDigitA
#define _write8str				 _write8strA
#define _write16str				 _write16strA
#define _writeLine				 _writeLineA
#endif
// STDIO File CODEC Extended READ/WRITE functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Basic READ/WRITE Macros
#define DZ1_READ8(fp, dstp, status, ret, errp)			do { if ((status = _read8Byte((fp), (u32_t *)(dstp), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_READ4(fp, dstp, status, ret, errp)			do { if ((status = _read4Byte((fp), (u32_t *)(dstp), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_READ2(fp, dstp, status, ret, errp)			do { if ((status = _read2Byte((fp), (u16_t *)(dstp), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_READ1(fp, dstp, status, ret, errp)			do { if ((status = _read1Byte((fp), (u8_t *)(dstp), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_READ( fp, dstp, size, status, ret, errp)	do { if ((status = _readByte((fp), (u8_t *)(dstp), (size_t)(size), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)

#define DZ1_WRITE8(fp, src, status, ret, errp)			do { if ((status = _write8Byte((fp), (src), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_WRITE4(fp, src, status, ret, errp)			do { if ((status = _write4Byte((fp), (src), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_WRITE2(fp, src, status, ret, errp)			do { if ((status = _write2Byte((fp), (src), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_WRITE1(fp, src, status, ret, errp)			do { if ((status = _write1Byte((fp), (src), (errp))) < 0) DZ1_STDIO_ERR_RET(errp); else (ret) += (status); } while(0)
#define DZ1_WRITE( fp, src, size, status, ret, errp)	do { if ((status = _writeByte((fp), (u8_t *)src, (size_t)(size), (errp))) < 0) ERR_OUT_RET(errp, -1); else (ret) += (status); } while(0)
// STDIO File CODEC Basic READ/WRITE Macros
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Tree/FIFO/List Support Structure
typedef struct Dz1ListIOArg
{
	FILE	*fp;
	ssize_t	 ret;
	void	*ptr;
} Dz1ListIOArg;
// STDIO File CODEC Tree/FIFO/List Support Structure
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PATH Helper
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1PathA_isAbsPath(str_t str);
DZ1_CPPLINK DZ1_DLLPORT	str_t	 Dz1Path_getLastPathA(str_t src);
DZ1_CPPLINK DZ1_DLLPORT	void	 Dz1Path_trimLastPathA(str_t dst);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Path_cmpA(str_t a, str_t b);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrA_appendSepStr(char dst[4096], str_t str);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrA_appendDotStr(char dst[4096], str_t str);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrA_concat(char *dst, size_t dst_sz, ...);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1PathW_isAbsPath(wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1Path_getLastPathW(wstr_t src);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Path_trimLastPathW(wstr_t dst);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Path_cmpW(wstr_t a, wstr_t b);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrW_appendSepStr(wchar_t dst[4096], wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrW_appendDotStr(wchar_t dst[4096], wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1PathStrW_concat(wchar_t *dst, size_t dst_sz, ...);

#ifdef	UNICODE
#define Dz1Path_isAbsPath		 Dz1PathW_isAbsPath
#define Dz1Path_getLastPath		 Dz1Path_getLastPathW
#define Dz1Path_trimLastPath	 Dz1Path_trimLastPathW
#define Dz1Path_cmp				 Dz1Path_cmpW
#define Dz1PathStr_appendSepStr	 Dz1PathStrW_appendSepStr
#define Dz1PathStr_appendDotStr	 Dz1PathStrW_appendDotStr
#define Dz1PathStr_concat		 Dz1PathStrW_concat
#else //UNICODE
#define Dz1Path_isAbsPath		 Dz1PathA_isAbsPath
#define Dz1Path_getLastPath		 Dz1Path_getLastPathA
#define Dz1Path_trimLastPath	 Dz1Path_trimLastPathA
#define Dz1Path_cmp				 Dz1Path_cmpA
#define Dz1PathStr_appendSepStr	 Dz1PathStrA_appendSepStr
#define Dz1PathStr_appendDotStr	 Dz1PathStrA_appendDotStr
#define Dz1PathStr_concat		 Dz1PathStrA_concat
#endif//UNICODE
#else //UNIX_SYSTEM
#define Dz1Path_isAbsPath		 Dz1PathA_isAbsPath
#define Dz1Path_getLastPath		 Dz1Path_getLastPathA
#define Dz1Path_trimLastPath	 Dz1Path_trimLastPathA
#define Dz1Path_cmp				 Dz1Path_cmpA
#define Dz1PathStr_appendSepStr	 Dz1PathStrA_appendSepStr
#define Dz1PathStr_appendDotStr	 Dz1PathStrA_appendDotStr
#define Dz1PathStr_concat		 Dz1PathStrA_concat
#endif
// Path Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Name Helper
// path : name
#define							 Dz1FileNameA_mkFullName(dstb, dstsz, pathp, namep) Dz1FileNameA_concatPathName((dstb), dstsz, (pathp), (namep))

DZ1_CPPLINK DZ1_DLLPORT bool_t	_Dz1FileNameA_concatPathName(str_t dst, size_t dst_sz, str_t path, str_t name, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_concatPathName(char *dst, size_t dst_sz, str_t path, str_t name);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1FileNameA_genConcatPathName(str_t path, str_t name, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameA_concatPathNameExt(char *dst, size_t dst_sz, str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_concatPathNameExt(char *dst, size_t dst_sz, str_t path, str_t name, str_t ext);

DZ1_CPPLINK DZ1_DLLPORT bool_t	_Dz1FileNameA_splitPathName(char *dstPath, char *dstName, str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_splitPathName(char *dstPath, char *dstName, str_t src);
// name : ext
DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameA_concatNameExt(char *dst, size_t dst_sz, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_concatNameExt(char *dst, size_t dst_sz, str_t name, str_t ext);

DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameA_splitNameExt(char *dstName, char *dstExt, str_t name, Dz1Error *err);	// faster then Dz1FileNameW_splitNameExt
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_splitNameExt(char *dstName, char *dstExt, str_t name);
// ext
DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameA_getExt(char *dstExt, str_t name, Dz1Error *err); // faster then Dz1FileNameW_getExt
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameA_getExt(char *dstExt, str_t name);
#ifndef UNIX_SYSTEM
// path : name
#define							 Dz1FileNameW_mkFullName(dstb, dstsz, pathp, namep) Dz1FileNameW_concatPathName((dstb), dstsz, (pathp), (namep))

DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameW_concatPathName(wstr_t dst, size_t dst_sz, wstr_t path, wstr_t name, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_concatPathName(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name);
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1FileNameW_genConcatPathName(wstr_t path, wstr_t name, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT bool_t	_Dz1FileNameW_concatPathNameExt(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_concatPathNameExt(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name, wstr_t ext);

DZ1_CPPLINK DZ1_DLLPORT bool_t	_Dz1FileNameW_splitPathName(wchar_t *dstPath, wchar_t *dstName, wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_splitPathName(wchar_t *dstPath, wchar_t *dstName, wstr_t src);
// name : ext
DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameW_concatNameExt(wchar_t *dst, size_t dst_sz, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_concatNameExt(wchar_t *dst, size_t dst_sz, wstr_t name, wstr_t ext);
DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameW_splitNameExt(wchar_t *dstName, wchar_t *dstExt, wstr_t name, Dz1Error *err);	// faster then Dz1FileNameW_splitNameExt
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_splitNameExt(wchar_t *dstName, wchar_t *dstExt, wstr_t name);
// ext
DZ1_CPPLINK DZ1_DLLPORT bool_t  _Dz1FileNameW_getExt(wchar_t *dstExt, wstr_t name, Dz1Error *err); // faster then Dz1FileNameW_getExt
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FileNameW_getExt(wchar_t *dstExt, wstr_t name);
#ifdef UNICODE
#define							 Dz1FileName_mkFullName				 Dz1FileNameW_mkFullName
#define 						_Dz1FileName_concatPathName			_Dz1FileNameW_concatPathName
#define							 Dz1FileName_concatPathName			 Dz1FileNameW_concatPathName
#define							 Dz1FileName_genConcatPathName		 Dz1FileNameW_genConcatPathName
#define							_Dz1FileName_concatPathNameExt		_Dz1FileNameW_concatPathNameExt
#define 						 Dz1FileName_concatPathNameExt		 Dz1FileNameW_concatPathNameExt
#define							_Dz1FileName_concatNameExt			_Dz1FileNameW_concatNameExt
#define 						 Dz1FileName_concatNameExt			 Dz1FileNameW_concatNameExt
#define							_Dz1FileName_splitPathName			_Dz1FileNameW_splitPathName
#define 						 Dz1FileName_splitPathName			 Dz1FileNameW_splitPathName
#define							_Dz1FileName_splitNameExt			_Dz1FileNameW_splitNameExt
#define 						 Dz1FileName_splitNameExt			 Dz1FileNameW_splitNameExt
#define							_Dz1FileName_getExt					_Dz1FileNameW_getExt
#define							 Dz1FileName_getExt					 Dz1FileNameW_getExt
#else// UNICODE
#define 						 Dz1FileName_mkFullName				 Dz1FileNameA_mkFullName
#define							_Dz1FileName_concatPathName			_Dz1FileNameA_concatPathName
#define 						 Dz1FileName_concatPathName			 Dz1FileNameA_concatPathName
#define							 Dz1FileName_genConcatPathName		 Dz1FileNameA_genConcatPathName
#define							_Dz1FileName_concatPathNameExt		_Dz1FileNameA_concatPathNameExt
#define 						 Dz1FileName_concatPathNameExt		 Dz1FileNameA_concatPathNameExt
#define							_Dz1FileName_concatNameExt			_Dz1FileNameA_concatNameExt
#define							 Dz1FileName_concatNameExt			 Dz1FileNameA_concatNameExt
#define							_Dz1FileName_splitPathName			_Dz1FileNameA_splitPathName
#define							 Dz1FileName_splitPathName			 Dz1FileNameA_splitPathName
#define							_Dz1FileName_splitNameExt			_Dz1FileNameA_splitNameExt
#define							 Dz1FileName_splitNameExt			 Dz1FileNameA_splitNameExt
#define							_Dz1FileName_getExt					_Dz1FileNameA_getExt
#define							 Dz1FileName_getExt					 Dz1FileNameA_getExt
#endif//UNICODE
#else// UNIX_SYSTEM
#define 						 Dz1FileName_mkFullName				 Dz1FileNameA_mkFullName
#define							_Dz1FileName_concatPathName			_Dz1FileNameA_concatPathName
#define 						 Dz1FileName_concatPathName			 Dz1FileNameA_concatPathName
#define							 Dz1FileName_genConcatPathName		 Dz1FileNameA_genConcatPathName
#define							_Dz1FileName_concatPathNameExt		_Dz1FileNameA_concatPathNameExt
#define 						 Dz1FileName_concatPathNameExt		 Dz1FileNameA_concatPathNameExt
#define							_Dz1FileName_concatNameExt			_Dz1FileNameA_concatNameExt
#define							 Dz1FileName_concatNameExt			 Dz1FileNameA_concatNameExt
#define							_Dz1FileName_splitPathName			_Dz1FileNameA_splitPathName
#define							 Dz1FileName_splitPathName			 Dz1FileNameA_splitPathName
#define							_Dz1FileName_splitNameExt			_Dz1FileNameA_splitNameExt
#define							 Dz1FileName_splitNameExt			 Dz1FileNameA_splitNameExt
#define							_Dz1FileName_getExt					_Dz1FileNameA_getExt
#define							 Dz1FileName_getExt					 Dz1FileNameA_getExt
#endif//UNIX_SYSTEM
// File Name Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Operation Helper Functions
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StdioA_isFile(str_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_isExist(str_t fn);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_isExist2(str_t path, str_t name);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_isExist3(str_t path, str_t name, str_t ext);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_delete(str_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_delete2(str_t path, str_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_delete3(str_t path, str_t name, str_t ext);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_rename(str_t dstPathName, str_t srcPathName);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_rename2(str_t dstPath, str_t dstNameExt, str_t srcPath, str_t srcNameExt);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_rename3(str_t dstPath, str_t dstName, str_t dstExt, str_t srcPath, str_t srcName, str_t srcExt);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_copy(str_t dstPathName, str_t srcPathName);
DZ1_CPPLINK DZ1_DLLPORT s64_t		 Dz1FileA_getSize(str_t fn);
DZ1_CPPLINK DZ1_DLLPORT s64_t		 Dz1FileA_getSize2(str_t path, str_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_time(str_t fn, time_t *ret);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_getTime(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_getTime2(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t path, str_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileA_getTime3(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_touch(str_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileA_touch2(str_t path, str_t name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StdioW_isFile(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_isExist(wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_isExist2(wstr_t path, wstr_t name);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_isExist3(wstr_t path, wstr_t name, wstr_t ext);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_delete(wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_delete2(wstr_t path, wstr_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_delete3(wstr_t path, wstr_t name, wstr_t ext);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_rename(wstr_t dstPathName, wstr_t srcPathName);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_rename2(wstr_t dstPath, wstr_t dstNameExt, wstr_t srcPath, wstr_t srcNameExt);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_rename3(wstr_t dstPath, wstr_t dstName, wstr_t dstExt, wstr_t srcPath, wstr_t srcName, wstr_t srcExt);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_copy(wstr_t dstPathName, wstr_t srcPathName);
DZ1_CPPLINK DZ1_DLLPORT s64_t		 Dz1FileW_getSize(wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT s64_t		 Dz1FileW_getSize2(wstr_t path, wstr_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_time(wstr_t fn, time_t *ret);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_getTime(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_getTime2(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t path, wstr_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileW_getTime3(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_touch(wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1FileW_touch2(wstr_t path, wstr_t name);

#ifdef	UNICODE
#define Dz1Stdio_isFile				 Dz1StdioW_isFile
#define Dz1File_isExist				 Dz1FileW_isExist
#define Dz1File_isExist2			 Dz1FileW_isExist2
#define Dz1File_isExist3			 Dz1FileW_isExist3
#define Dz1File_delete				 Dz1FileW_delete
#define Dz1File_delete2				 Dz1FileW_delete2
#define Dz1File_delete3				 Dz1FileW_delete3
#define Dz1File_rename				 Dz1FileW_rename
#define Dz1File_rename2				 Dz1FileW_rename2
#define Dz1File_rename3				 Dz1FileW_rename3
#define Dz1File_copy				 Dz1FileW_copy
#define Dz1File_getSize				 Dz1FileW_getSize
#define Dz1File_getSize2			 Dz1FileW_getSize2
#define Dz1File_time				 Dz1FileW_time
#define Dz1File_getTime				 Dz1FileW_getTime
#define Dz1File_getTime2			 Dz1FileW_getTime2
#define Dz1File_getTime3			 Dz1FileW_getTime3
#define Dz1File_touch				 Dz1FileW_touch
#define Dz1File_touch2				 Dz1FileW_touch2
#else	// UNICODE
#define Dz1Stdio_isFile				 Dz1StdioA_isFile
#define Dz1File_isExist				 Dz1FileA_isExist
#define Dz1File_isExist2			 Dz1FileA_isExist2
#define Dz1File_isExist3			 Dz1FileA_isExist3
#define Dz1File_delete				 Dz1FileA_delete
#define Dz1File_delete2				 Dz1FileA_delete2
#define Dz1File_delete3				 Dz1FileA_delete3
#define Dz1File_rename				 Dz1FileA_rename
#define Dz1File_rename2				 Dz1FileA_rename2
#define Dz1File_rename3				 Dz1FileA_rename3
#define Dz1File_copy				 Dz1FileA_copy
#define Dz1File_getSize				 Dz1FileA_getSize
#define Dz1File_getSize2			 Dz1FileA_getSize2
#define Dz1File_time				 Dz1FileA_time
#define Dz1File_getTime				 Dz1FileA_getTime
#define Dz1File_getTime2			 Dz1FileA_getTime2
#define Dz1File_getTime3			 Dz1FileA_getTime3
#define Dz1File_touch				 Dz1FileA_touch
#define Dz1File_touch2				 Dz1FileA_touch2
#endif	// UNICODE
#else	// !UNIX_SYSTEM
#define Dz1Stdio_isFile				 Dz1StdioA_isFile
#define Dz1File_isExist				 Dz1FileA_isExist
#define Dz1File_isExist2			 Dz1FileA_isExist2
#define Dz1File_isExist3			 Dz1FileA_isExist3
#define Dz1File_delete				 Dz1FileA_delete
#define Dz1File_delete2				 Dz1FileA_delete2
#define Dz1File_delete3				 Dz1FileA_delete3
#define Dz1File_rename				 Dz1FileA_rename
#define Dz1File_rename2				 Dz1FileA_rename2
#define Dz1File_rename3				 Dz1FileA_rename3
#define Dz1File_copy				 Dz1FileA_copy
#define Dz1File_getSize				 Dz1FileA_getSize
#define Dz1File_getSize2			 Dz1FileA_getSize2
#define Dz1File_time				 Dz1FileA_time
#define Dz1File_getTime				 Dz1FileA_getTime
#define Dz1File_getTime2			 Dz1FileA_getTime2
#define Dz1File_getTime3			 Dz1FileA_getTime3
#define Dz1File_touch				 Dz1FileA_touch
#define Dz1File_touch2				 Dz1FileA_touch2
#endif
// File Operation Helper Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Text File Helper Function
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_load0(char *fn, u32_t *retSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_load(char *fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_load2(str_t path, str_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_load3(str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_ixload(str_t path[], u32_t cnt, str_t name_ext, str_t *selected_path, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1TextFileA_ixload2(str_t path[], u32_t cnt, str_t name, str_t ext, str_t *selected_path, Dz1Error *errp);

#ifndef	UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_load0(wstr_t fn, u32_t *retSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_load(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_load2(wstr_t path, wstr_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_load3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_ixload(wstr_t path[], u32_t cnt, wstr_t name_ext, wstr_t *selected_path, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1TextFileW_ixload2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, wstr_t *selected_path, Dz1Error *errp);

#ifdef	UNICODE
#define Dz1TextFile_load0			 Dz1TextFileW_load0
#define Dz1TextFile_load			 Dz1TextFileW_load
#define Dz1TextFile_load2			 Dz1TextFileW_load2
#define Dz1TextFile_load3			 Dz1TextFileW_load3
#define Dz1TextFile_ixload			 Dz1TextFileW_ixload
#define Dz1TextFile_ixload2			 Dz1TextFileW_ixload2
#else	// UNICODE
#define Dz1TextFile_load0			 Dz1TextFileA_load0
#define Dz1TextFile_load			 Dz1TextFileA_load
#define Dz1TextFile_load2			 Dz1TextFileA_load2
#define Dz1TextFile_load3			 Dz1TextFileA_load3
#define Dz1TextFile_ixload			 Dz1TextFileA_ixload
#define Dz1TextFile_ixload2			 Dz1TextFileA_ixload2
#endif	// UNICODE
#else	// !UNIX_SYSTEM
#define Dz1TextFile_load0			 Dz1TextFileA_load0
#define Dz1TextFile_load			 Dz1TextFileA_load
#define Dz1TextFile_load2			 Dz1TextFileA_load2
#define Dz1TextFile_load3			 Dz1TextFileA_load3
#define Dz1TextFile_ixload			 Dz1TextFileA_ixload
#define Dz1TextFile_ixload2			 Dz1TextFileA_ixload2
#endif	// UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1StrA_loadFromFile(str_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1StrA_loadFromFile2(str_t path, str_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1StrA_loadFromFile3(str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrA_saveToFile(str_t fn, str_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrA_saveToFile2(str_t path, str_t name_ext, str_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrA_saveToFile3(Dz1Str path, str_t name, str_t ext, str_t str, Dz1Error *err);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1StrW_loadFromFile(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1StrW_loadFromFile2(wstr_t path, wstr_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1StrW_loadFromFile3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrW_saveToFile(wstr_t fn, wstr_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrW_saveToFile2(wstr_t path, wstr_t name_ext, wstr_t str, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1StrW_saveToFile3(wstr_t path, wstr_t name, wstr_t ext, wstr_t str, Dz1Error *err);
#ifdef UNICODE
#define								 Dz1Str_loadFromFile	Dz1StrW_loadFromFile
#define								 Dz1Str_loadFromFile2	Dz1StrW_loadFromFile2
#define								 Dz1Str_loadFromFile3	Dz1StrW_loadFromFile3
#define								 Dz1Str_saveToFile		Dz1StrW_saveToFile
#define								 Dz1Str_saveToFile2		Dz1StrW_saveToFile2
#define								 Dz1Str_saveToFile3		Dz1StrW_saveToFile3
#else // UNICODE
#define								 Dz1Str_loadFromFile	Dz1StrA_loadFromFile
#define								 Dz1Str_loadFromFile2	Dz1StrA_loadFromFile2
#define								 Dz1Str_loadFromFile3	Dz1StrA_loadFromFile3
#define								 Dz1Str_saveToFile		Dz1StrA_saveToFile
#define								 Dz1Str_saveToFile2		Dz1StrA_saveToFile2
#define								 Dz1Str_saveToFile3		Dz1StrA_saveToFile3
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Str_loadFromFile	Dz1StrA_loadFromFile
#define								 Dz1Str_loadFromFile2	Dz1StrA_loadFromFile2
#define								 Dz1Str_loadFromFile3	Dz1StrA_loadFromFile3
#define								 Dz1Str_saveToFile		Dz1StrA_saveToFile
#define								 Dz1Str_saveToFile2		Dz1StrA_saveToFile2
#define								 Dz1Str_saveToFile3		Dz1StrA_saveToFile3
#endif // UNIX_SYSTEM
// STDIO Text File Helper Function
///////////////////////////////////////////////////////////////////////////////

#define DZ1_UNICODE_BOM_UCS2LE			(u8_t *)"\xFF\xFE"
#define DZ1_UNICODE_BOM_UCS2BE			(u8_t *)"\xFE\xFF"
#define DZ1_UNICODE_BOM_UCS2_LEN		2

#define DZ1_UNICODE_BOM_UTF8			(u8_t *)"\xEF\xBB\xBF"
#define DZ1_UNICODE_BOM_UTF8_LEN		3

///////////////////////////////////////////////////////////////////////////////
// STDIO Binary File Helper Function
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFile_loadf(FILE *fp, u64_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFile_savef(Dz1Binary *bin, FILE *fp);

DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_load(str_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_load2(str_t path, str_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_load3(str_t path, str_t name, str_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_iload(str_t path[], u32_t cnt, str_t name_ext, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_iload2(str_t path[], u32_t cnt, str_t name, str_t ext, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_read(str_t fn, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileA_read2(str_t path, str_t name, size_t sz, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileA_save(char *fn, Dz1Binary *src);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileA_save2(char *path, char *name, Dz1Binary *src);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileA_save3(char *path, char *name, char *ext, Dz1Binary *src);

#ifndef	UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_load(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_load2(wstr_t path, wstr_t name_ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_load3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_iload(wstr_t path[], u32_t cnt, wstr_t name_ext, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_iload2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_read(wstr_t fn, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1BinFileW_read2(wstr_t path, wstr_t name, size_t sz, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileW_save(wstr_t fn, Dz1Binary *src);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileW_save2(wstr_t path, wstr_t name, Dz1Binary *src);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BinFileW_save3(wstr_t path, wstr_t name, wstr_t ext, Dz1Binary *src);

#ifdef	UNICODE
#define Dz1BinFile_load				 Dz1BinFileW_load
#define Dz1BinFile_load2			 Dz1BinFileW_load2
#define Dz1BinFile_load3			 Dz1BinFileW_load3
#define Dz1BinFile_iload			 Dz1BinFileW_iload
#define Dz1BinFile_iload2			 Dz1BinFileW_iload2
#define Dz1BinFile_read				 Dz1BinFileW_read
#define Dz1BinFile_read2			 Dz1BinFileW_read2

#define Dz1BinFile_save				 Dz1BinFileW_save
#define Dz1BinFile_save2			 Dz1BinFileW_save2
#define Dz1BinFile_save3			 Dz1BinFileW_save3
#else	// UNICODE
#define Dz1BinFile_load				 Dz1BinFileA_load
#define Dz1BinFile_load2			 Dz1BinFileA_load2
#define Dz1BinFile_load3			 Dz1BinFileA_load3
#define Dz1BinFile_iload			 Dz1BinFileA_iload
#define Dz1BinFile_iload2			 Dz1BinFileA_iload2
#define Dz1BinFile_read				 Dz1BinFileA_read
#define Dz1BinFile_read2			 Dz1BinFileA_read2

#define Dz1BinFile_save				 Dz1BinFileA_save
#define Dz1BinFile_save2			 Dz1BinFileA_save2
#define Dz1BinFile_save3			 Dz1BinFileA_save3
#endif	// UNICODE

#else	// !UNIX_SYSTEM
#define Dz1BinFile_load				 Dz1BinFileA_load
#define Dz1BinFile_load2			 Dz1BinFileA_load2
#define Dz1BinFile_load3			 Dz1BinFileA_load3
#define Dz1BinFile_iload			 Dz1BinFileA_iload
#define Dz1BinFile_iload2			 Dz1BinFileA_iload2
#define Dz1BinFile_read				 Dz1BinFileA_read
#define Dz1BinFile_read2			 Dz1BinFileA_read2

#define Dz1BinFile_save				 Dz1BinFileA_save
#define Dz1BinFile_save2			 Dz1BinFileA_save2
#define Dz1BinFile_save3			 Dz1BinFileA_save3
#endif
// STDIO Binary File Helper Function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File Descriptor
typedef int Dz1FileDescr;
DZ1_CPPLINK DZ1_DLLPORT Dz1FileDescr Dz1FileDescr_open();
#define								 Dz1FileDescr_close(fd)			close(fd)
#define								 Dz1FileDescr_get(fd)			fileno(fd)
// STDIO File Descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Stream
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1FileStream_getSize(FILE *fp, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1FileStream_textBOM(FILE *fp, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamA_open(str_t fn, const char *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamA_open2(str_t path, str_t name, const char *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamA_open3(str_t path, str_t name, str_t ext, const char *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamA_iopen(str_t path[], u32_t cnt, str_t name_ext, const char *attr, str_t *selected, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamA_iopen2(str_t path[], u32_t cnt, str_t name, str_t ext, const char *attr, str_t *selected, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamW_open(wstr_t fn, const wchar_t *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamW_open2(wstr_t path, wstr_t name, const wchar_t *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamW_open3(wstr_t path, wstr_t name, wstr_t ext, const wchar_t *attr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamW_iopen(wstr_t path[], u32_t cnt, wstr_t name_ext, const wchar_t *attr, wstr_t *selected, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT FILE		*Dz1FileStreamW_iopen2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, const wchar_t *attr, wstr_t *selected, Dz1Error *err);
#endif

static __inline__ void				 Dz1FileStream_close(FILE *fp) { if (fp) fclose(fp); }
static __inline__ void				 Dz1FileStream_cancel(void *ptr)
{
	FILE *p = (FILE *)ptr;
	Dz1FileStream_close(p);
}

static __inline__ void				 Dz1FileStream_closeAndSetNull(void *pptr)
{
	FILE **fpp = (FILE **)pptr;
	Dz1FileStream_close(*fpp); *fpp = NULL;
}
#define								 Dz1FileStream_cancelAndSetNull	Dz1FileStream_closeAndSetNull

// TDC Support : FILE
static __inline__ void FILE_del(FILE *fp)				{ Dz1FileStream_close(fp); }
static __inline__ void FILE_delAndSetNull(void *pptr)	{ Dz1FileStream_closeAndSetNull(pptr); }

#ifndef UNIX_SYSTEM
#ifdef	UNICODE
#define Dz1FileStream_open								Dz1FileStreamW_open
#define Dz1FileStream_open2								Dz1FileStreamW_open2
#define Dz1FileStream_open3								Dz1FileStreamW_open3
#define Dz1FileStream_iopen(ar, cn, nmext, att, ep)		Dz1FileStreamW_iopen(ar, cn, nmext, arr, NULL, ep)
#define Dz1FileStream_iopen2(ar, cn, nm,ext, att, ep)	Dz1FileStreamW_iopen2(ar, cn, nm, ext, arr, NULL, ep)
#define Dz1FileStream_ixopen							Dz1FileStreamW_iopen
#define Dz1FileStream_ixopen2							Dz1FileStreamW_iopen2
#else// UNICODE
#define Dz1FileStream_open								Dz1FileStreamA_open
#define Dz1FileStream_open2								Dz1FileStreamA_open2
#define Dz1FileStream_open3								Dz1FileStreamA_open3
#define Dz1FileStream_iopen(ar, cn, nmext, att, ep)		Dz1FileStreamA_iopen(ar, cn, nmext, arr, NULL, ep)
#define Dz1FileStream_iopen2(ar, cn, nm, ext, att, ep)	Dz1FileStreamA_iopen2(ar, cn, nm, ext, arr, NULL, ep)
#define Dz1FileStream_ixopen							Dz1FileStreamA_iopen
#define Dz1FileStream_ixopen2							Dz1FileStreamA_iopen2
#endif//UNICODE
#else// UNIX_SYSTEM
#define Dz1FileStream_open								Dz1FileStreamA_open
#define Dz1FileStream_open2								Dz1FileStreamA_open2
#define Dz1FileStream_open3								Dz1FileStreamA_open3
#define Dz1FileStream_iopen(ar, cn, nmext, att, ep)		Dz1FileStreamA_iopen(ar, cn, nmext, arr, NULL, ep)
#define Dz1FileStream_iopen2(ar, cn, nm, ext, att, ep)	Dz1FileStreamA_iopen2(ar, cn, nm, ext, arr, NULL, ep)
#define Dz1FileStream_ixopen							Dz1FileStreamA_iopen
#define Dz1FileStream_ixopen2							Dz1FileStreamA_iopen2
#endif//UNIX_SYSTEM
// File Stream
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Directory Operation Helper Functions
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_delete(str_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_delete2(str_t path, str_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_flush(str_t path);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_flush2(str_t basePath, str_t dirName);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_mkDir(str_t targetPath);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_mkDirNested(str_t targetPath);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1DirA_pwd(char *buf, size_t buf_cnt, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirA_chdir(str_t path);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1DirA_isExist(str_t path);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1DirA_isExist2(str_t base_path, str_t dir_name);
DZ1_CPPLINK DZ1_DLLPORT time_t		 Dz1DirA_time(str_t path, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_delete(wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_delete2(wstr_t path, wstr_t name);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_flush(wstr_t path);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_flush2(wstr_t basePath, wstr_t dirName);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_mkDir(wstr_t targetPath);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_mkDirNested(wstr_t targetPath);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1DirW_pwd(wchar_t *buf, size_t buf_cnt, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1DirW_chdir(wstr_t path);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1DirW_isExist(wstr_t path);
DZ1_CPPLINK DZ1_DLLPORT bool_t		 Dz1DirW_isExist2(wstr_t base_path, wstr_t dir_name);
DZ1_CPPLINK DZ1_DLLPORT time_t		 Dz1DirW_time(wstr_t path, Dz1Error *err);
#ifdef	UNICODE
#define								 Dz1Dir_delete				Dz1DirW_delete
#define								 Dz1Dir_delete2				Dz1DirW_delete2
#define								 Dz1Dir_flush				Dz1DirW_flush
#define								 Dz1Dir_flush2				Dz1DirW_flush2
#define								 Dz1Dir_mkDir				Dz1DirW_mkDir
#define								 Dz1Dir_mkDirNested			Dz1DirW_mkDirNested
#define								 Dz1Dir_pwd					Dz1DirW_pwd
#define								 Dz1Dir_chdir				Dz1DirW_chdir
#define								 Dz1Dir_isExist				Dz1DirW_isExist
#define								 Dz1Dir_isExist2			Dz1DirW_isExist2
#define								 Dz1Dir_time				Dz1DirW_time
#else// UNICODE
#define								 Dz1Dir_delete				Dz1DirA_delete
#define								 Dz1Dir_delete2				Dz1DirA_delete2
#define								 Dz1Dir_flush				Dz1DirA_flush
#define								 Dz1Dir_flush2				Dz1DirA_flush2
#define								 Dz1Dir_mkDir				Dz1DirA_mkDir
#define								 Dz1Dir_mkDirNested			Dz1DirA_mkDirNested
#define								 Dz1Dir_pwd					Dz1DirA_pwd
#define								 Dz1Dir_chdir				Dz1DirA_chdir
#define								 Dz1Dir_isExist				Dz1DirA_isExist
#define								 Dz1Dir_isExist2			Dz1DirA_isExist2
#define								 Dz1Dir_time				Dz1DirA_time
#endif//UNICODE
#else
#define								 Dz1Dir_delete				Dz1DirA_delete
#define								 Dz1Dir_delete2				Dz1DirA_delete2
#define								 Dz1Dir_flush				Dz1DirA_flush
#define								 Dz1Dir_flush2				Dz1DirA_flush2
#define								 Dz1Dir_mkDir				Dz1DirA_mkDir
#define								 Dz1Dir_mkDirNested			Dz1DirA_mkDirNested
#define								 Dz1Dir_pwd					Dz1DirA_pwd
#define								 Dz1Dir_chdir				Dz1DirA_chdir
#define								 Dz1Dir_isExist				Dz1DirA_isExist
#define								 Dz1Dir_isExist2			Dz1DirA_isExist2
#define								 Dz1Dir_time				Dz1DirA_time
#endif//UNIX_SYSTEM
// STDIO Directory Operation Helper Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Directory Catalog API
typedef struct Dz1DirEntryA
{
	char			 name[260];
	u64_t			 size;
	time_t			 date;
	time_t			 cdate;
} Dz1DirEntryA;

typedef struct Dz1DirCatalogA
{
	str_t			 path;
	time_t			 path_stamp;
	str_t			 spec;
	Dz1DirEntryA	*entries;
	size_t			 size;
	size_t			 valid;
} Dz1DirCatalogA;

typedef enum Dz1DirCatalogSortBy
{
	Dz1DirCatalogSortBy_name,
	Dz1DirCatalogSortBy_size,
	Dz1DirCatalogSortBy_date
} Dz1DirCatalogSortBy;

#define									 Dz1DirCatalogA_new				 Dz1DirCatalogA_newFiles
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogA	*Dz1DirCatalogA_newFiles(str_t path, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogA	*Dz1DirCatalogA_newFiles2(str_t path, str_t spec, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogA	*Dz1DirCatalogA_newSubDir(str_t path, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogA	*Dz1DirCatalogA_newSubDir2(str_t path, str_t spec, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogA_updateFiles(Dz1DirCatalogA *ret);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogA_updateSubDir(Dz1DirCatalogA *ret);

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1DirCatalogA_del(Dz1DirCatalogA *p);
static __inline__		void			 Dz1DirCatalogA_delAndSetNull(void *ptr)
{
	Dz1DirCatalogA **p = (Dz1DirCatalogA **)ptr;
	Dz1DirCatalogA_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1DirCatalogA_dump(Dz1DirCatalogA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int				 Dz1DirCatalogA_cmp(Dz1DirCatalogA *a, Dz1DirCatalogA *b);
DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1DirCatalogA_find(Dz1DirCatalogA *p, str_t name);

// Custom Sort
typedef int (*Dz1DirEntryACmpFunc)(Dz1DirEntryA *a, Dz1DirEntryA *b);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		_Dz1DirCatalogA_sort(Dz1DirCatalogA *p, Dz1DirEntryACmpFunc cmp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogA_sort(Dz1DirCatalogA *p, Dz1DirCatalogSortBy sort);

#ifndef UNIX_SYSTEM
typedef struct Dz1DirEntryW
{
	wchar_t			 name[260];
	u64_t			 size;
	time_t			 date;
	time_t			 cdate;
} Dz1DirEntryW;

typedef struct Dz1DirCatalogW
{
	wstr_t			 path;
	time_t			 path_stamp;
	wstr_t			 spec;
	Dz1DirEntryW	*entries;
	size_t			 size;
	size_t			 valid;
} Dz1DirCatalogW;

#define									 Dz1DirCatalogW_new				 Dz1DirCatalogW_newFiles
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogW	*Dz1DirCatalogW_newFiles(wstr_t path, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogW	*Dz1DirCatalogW_newFiles2(wstr_t path, wstr_t spec, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogW	*Dz1DirCatalogW_newSubDir(wstr_t path, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1DirCatalogW	*Dz1DirCatalogW_newSubDir2(wstr_t path, wstr_t spec, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogW_updateFiles(Dz1DirCatalogW *ret);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogW_updateSubDir(Dz1DirCatalogW *ret);

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1DirCatalogW_del(Dz1DirCatalogW *p);
static __inline__		void			 Dz1DirCatalogW_delAndSetNull(void *ptr)
{
	Dz1DirCatalogW **p = (Dz1DirCatalogW **)ptr;
	Dz1DirCatalogW_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void			 Dz1DirCatalogW_dump(Dz1DirCatalogW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int				 Dz1DirCatalogW_cmp(Dz1DirCatalogW *a, Dz1DirCatalogW *b);
DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1DirCatalogW_find(Dz1DirCatalogW *p, wstr_t name);

// Custom Sort
typedef int							   (*Dz1DirEntryWCmpFunc)(Dz1DirEntryW *a, Dz1DirEntryW *b);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		_Dz1DirCatalogW_sort(Dz1DirCatalogW *p, Dz1DirEntryWCmpFunc cmp);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1DirCatalogW_sort(Dz1DirCatalogW *p, Dz1DirCatalogSortBy sort);

#ifdef UNICODE
#define									 Dz1DirEntry						 Dz1DirEntryW
#define									 Dz1DirCatalog					 Dz1DirCatalogW
#define									 Dz1DirCatalog_new				 Dz1DirCatalogW_new
#define									 Dz1DirCatalog_newFiles			 Dz1DirCatalogW_newFiles
#define									 Dz1DirCatalog_newFiles2		 Dz1DirCatalogW_newFiles2
#define									 Dz1DirCatalog_newSubDir		 Dz1DirCatalogW_newSubDir
#define									 Dz1DirCatalog_newSubDir2		 Dz1DirCatalogW_newSubDir2

#define									 Dz1DirCatalog_updateFiles		 Dz1DirCatalogW_updateFiles
#define									 Dz1DirCatalog_updateSubDir		 Dz1DirCatalogW_updateSubDir

#define									 Dz1DirCatalog_del				 Dz1DirCatalogW_del
#define									 Dz1DirCatalog_delAndSetNull	 Dz1DirCatalogW_delAndSetNull
#define									 Dz1DirCatalog_dump				 Dz1DirCatalogW_dump
#define									 Dz1DirCatalog_cmp				 Dz1DirCatalogW_cmp

#define									 Dz1DirCatalog_find				 Dz1DirCatalogW_find
#define									_Dz1DirCatalog_sort				_Dz1DirCatalogW_sort
#define									 Dz1DirCatalog_sort				 Dz1DirCatalogW_sort

#else
#define									 Dz1DirEntry					 Dz1DirEntryA
#define									 Dz1DirCatalog					 Dz1DirCatalogA
#define									 Dz1DirCatalog_new				 Dz1DirCatalogA_new
#define									 Dz1DirCatalog_newFiles			 Dz1DirCatalogA_newFiles
#define									 Dz1DirCatalog_newFiles2		 Dz1DirCatalogA_newFiles2
#define									 Dz1DirCatalog_newSubDir		 Dz1DirCatalogA_newSubDir
#define									 Dz1DirCatalog_newSubDir2		 Dz1DirCatalogA_newSubDir2

#define									 Dz1DirCatalog_updateFiles		 Dz1DirCatalogA_updateFiles
#define									 Dz1DirCatalog_updateSubDir		 Dz1DirCatalogA_updateSubDir

#define									 Dz1DirCatalog_del				 Dz1DirCatalogA_del
#define									 Dz1DirCatalog_delAndSetNull	 Dz1DirCatalogA_delAndSetNull
#define									 Dz1DirCatalog_dump				 Dz1DirCatalogA_dump
#define									 Dz1DirCatalog_cmp				 Dz1DirCatalogA_cmp

#define									 Dz1DirCatalog_find				 Dz1DirCatalogA_find
#define									_Dz1DirCatalog_sort				_Dz1DirCatalogA_sort
#define									 Dz1DirCatalog_sort				 Dz1DirCatalogA_sort
#endif//UNICODE
#else// UNIX_SYSTEM
#define									 Dz1DirEntry					 Dz1DirEntryA
#define									 Dz1DirCatalog					 Dz1DirCatalogA
#define									 Dz1DirCatalog_new				 Dz1DirCatalogA_new
#define									 Dz1DirCatalog_newFiles			 Dz1DirCatalogA_newFiles
#define									 Dz1DirCatalog_newFiles2		 Dz1DirCatalogA_newFiles2
#define									 Dz1DirCatalog_newSubDir		 Dz1DirCatalogA_newSubDir
#define									 Dz1DirCatalog_newSubDir2		 Dz1DirCatalogA_newSubDir2

#define									 Dz1DirCatalog_updateFiles		 Dz1DirCatalogA_updateFiles
#define									 Dz1DirCatalog_updateSubDir		 Dz1DirCatalogA_updateSubDir

#define									 Dz1DirCatalog_del				 Dz1DirCatalogA_del
#define									 Dz1DirCatalog_delAndSetNull	 Dz1DirCatalogA_delAndSetNull
#define									 Dz1DirCatalog_dump				 Dz1DirCatalogA_dump
#define									 Dz1DirCatalog_cmp				 Dz1DirCatalogA_cmp

#define									 Dz1DirCatalog_find				 Dz1DirCatalogA_find
#define									_Dz1DirCatalog_sort				_Dz1DirCatalogA_sort
#define									 Dz1DirCatalog_sort				 Dz1DirCatalogA_sort
#endif//UNIX_SYSTEM
// STDIO Directory Catalog API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Temp File
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1GetTempFileNameA(char *dst, size_t dst_sz, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1GetTempFileNameW(wchar_t *dst, size_t dst_sz, Dz1Error *err);
#ifdef	UNICODE
#define Dz1GetTempFileName		 Dz1GetTempFileNameW
#else// UNICODE
#define Dz1GetTempFileName		 Dz1GetTempFileNameA
#endif//UNICODE
#else// UNIX_SYSTEM
#define Dz1GetTempFileName		 Dz1GetTempFileNameA
#endif//UNIX_SYSTEM
// STDIO Temp File
///////////////////////////////////////////////////////////////////////////////
#endif
