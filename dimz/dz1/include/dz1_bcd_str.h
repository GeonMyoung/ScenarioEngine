#ifndef DZ1_BCD_STR_H
#define DZ1_BCD_STR_H

#include <dz1_codec.h>
#include <dz1_bin.h>

typedef struct Dz1BCDStr
{
	u8_t *bcdData;
	size_t size;
	size_t allocSize;
	void *str_buf;
} Dz1BCDStr;

DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrA_new(u8_t *bcdData, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrA_newFromStr(str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrA_newFromNibbleSpread(u8_t *nibbleSpreadBCD, size_t byteLen, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BCDStrA_setData(Dz1BCDStr *dst, u8_t *bcdData, size_t byteSize);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrW_new(u8_t *bcdData, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrW_newFromStr(wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1BCDStr	*Dz1BCDStrW_newFromNibbleSpread(u8_t *nibbleSpreadBCD, size_t byteLen, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error	 Dz1BCDStrW_setData(Dz1BCDStr *dst, u8_t *bcdData, size_t byteSize);
#ifdef UNICODE
#define								 Dz1BCDStr_new					Dz1BCDStrW_new
#define								 Dz1BCDStr_newFromStr			Dz1BCDStrW_newFromStr
#define								 Dz1BCDStr_newFromNibbleSpread	Dz1BCDStrW_newFromNibbleSpread
#define								 Dz1BCDStr_setData				Dz1BCDStrW_setData
#else // UNICODE
#define								 Dz1BCDStr_new					Dz1BCDStrA_new
#define								 Dz1BCDStr_newFromStr			Dz1BCDStrA_newFromStr
#define								 Dz1BCDStr_newFromNibbleSpread	Dz1BCDStrA_newFromNibbleSpread
#define								 Dz1BCDStr_setData				Dz1BCDStrA_setData
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1BCDStr_new					Dz1BCDStrA_new
#define								 Dz1BCDStr_newFromStr			Dz1BCDStrA_newFromStr
#define								 Dz1BCDStr_newFromNibbleSpread	Dz1BCDStrA_newFromNibbleSpread
#define								 Dz1BCDStr_setData				Dz1BCDStrA_setData
#endif // UNIX_SYSTEM
static __inline__ Dz1BCDStr			*Dz1BCDStr_gen(Dz1Error *err) { return Dz1BCDStr_new(NULL, 0, err); }
#define								 Dz1BCDStr_clone(sp, ep)	Dz1BCDStr_new((sp)->bcdData, (sp)->size, ep)
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1BCDStr_getNibbleSpread(Dz1BCDStr *src, u8_t *dst, size_t dstSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BCDStr_del(Dz1BCDStr *p);
static __inline__ void				 Dz1BCDStr_delAndSetNull(void *ptr)
{
	Dz1BCDStr **p = (Dz1BCDStr **)ptr;
	Dz1BCDStr_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1BCDStrA_printable(Dz1BCDStr *p);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BCDStrA_dump(Dz1BCDStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BCDStrA_fdump(FILE *fp, Dz1BCDStr *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1BCDStrW_printable(Dz1BCDStr *p);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BCDStrW_dump(Dz1BCDStr *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void		 Dz1BCDStrW_fdump(FILE *fp, Dz1BCDStr *p, int tab);
#ifdef UNICODE
#define								 Dz1BCDStr_printable	Dz1BCDStrW_printable
#define								 Dz1BCDStr_dump			Dz1BCDStrW_dump
#define								 Dz1BCDStr_fdump		Dz1BCDStrW_fdump
#else // UNICODE
#define								 Dz1BCDStr_printable	Dz1BCDStrA_printable
#define								 Dz1BCDStr_dump			Dz1BCDStrA_dump
#define								 Dz1BCDStr_fdump		Dz1BCDStrA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1BCDStr_printable	Dz1BCDStrA_printable
#define								 Dz1BCDStr_dump			Dz1BCDStrA_dump
#define								 Dz1BCDStr_fdump		Dz1BCDStrA_fdump
#endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT int			 Dz1BCDStr_cmp(Dz1BCDStr *a, Dz1BCDStr *b);

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1BCDStr_enc(u8_t *dst, size_t size, Dz1BCDStr *src, size_t byteNum, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1BCDStr_dec(Dz1BCDStr *dst, size_t byteNum, u8_t *src, size_t size, Dz1Error *err);

#endif
