#ifndef DZ1_TERMCAP_H
#define DZ1_TERMCAP_H

#include <dz1_error.h>

typedef enum
{
	Dz1TermKey_esc,
	Dz1TermKey_up,
	Dz1TermKey_down,
	Dz1TermKey_right,
	Dz1TermKey_left,
	Dz1TermKey_end,
	Dz1TermKey_home,
	Dz1TermKey_insert,
	Dz1TermKey_delete,
	Dz1TermKey_pageUp,
	Dz1TermKey_pageDown,
	Dz1TermKey_f1,
	Dz1TermKey_f2,
	Dz1TermKey_f3,
	Dz1TermKey_f4,
	Dz1TermKey_f5,
	Dz1TermKey_f6,
	Dz1TermKey_f7,
	Dz1TermKey_f8,
	Dz1TermKey_f9,
	Dz1TermKey_f10,
	Dz1TermKey_f11,
	Dz1TermKey_f12,
	Dz1TermKey_max
} Dz1TermKey;


typedef enum
{
	Dz1TermMetaKey_none,
	Dz1TermMetaKey_shift,
	Dz1TermMetaKey_alt,
	Dz1TermMetaKey_control,
	Dz1TermMetaKey_shiftAlt,
	Dz1TermMetaKey_shiftControl,
	Dz1TermMetaKey_controlAlt,
	Dz1TermMetaKey_shiftControlAlt,
	Dz1TermMetaKey_max
} Dz1TermMetaKey;

DZ1_CPPLINK DZ1_DLLPORT str_t Dz1TermKeyStrA(Dz1TermKey key);
DZ1_CPPLINK DZ1_DLLPORT str_t Dz1TermMetaKeyStrA(Dz1TermMetaKey key);

DZ1_CPPLINK DZ1_DLLPORT void *Dz1TermIoA_new(str_t termName, size_t fifoSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void  Dz1TermIoA_del(void *p);
DZ1_CPPLINK DZ1_DLLPORT void  Dz1TermIoA_delAndSetNull(void *ptr);

// -1 = error, 0 = Special Key, 0 < Char
DZ1_CPPLINK DZ1_DLLPORT int	  Dz1TermIoA_getc(void *ptr, Dz1TermMetaKey *meta, Dz1TermKey *key, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t Dz1TermKeyStrW(Dz1TermKey key);
DZ1_CPPLINK DZ1_DLLPORT wstr_t Dz1TermMetaKeyStrW(Dz1TermMetaKey key);

DZ1_CPPLINK DZ1_DLLPORT void *Dz1TermIoW_new(wstr_t termName, size_t fifoSize, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void  Dz1TermIoW_del(void *p);
DZ1_CPPLINK DZ1_DLLPORT void  Dz1TermIoW_delAndSetNull(void *ptr);

// -1 = error, 0 = Special Key, 0 < Char
DZ1_CPPLINK DZ1_DLLPORT int	  Dz1TermIoW_getc(void *ptr, Dz1TermMetaKey *meta, Dz1TermKey *key, Dz1Error *err);
#ifdef UNICODE
#define						  Dz1TermIo_new				Dz1TermIoW_new
#define						  Dz1TermIo_del				Dz1TermIoW_del
#define						  Dz1TermIo_delAndSetNull	Dz1TermIoW_delAndSetNull
#define						  Dz1TermIo_getc			Dz1TermIoW_getc
#else // UNICODE
#define						  Dz1TermIo_new				Dz1TermIoA_new
#define						  Dz1TermIo_del				Dz1TermIoA_del
#define						  Dz1TermIo_delAndSetNull	Dz1TermIoA_delAndSetNull
#define						  Dz1TermIo_getc			Dz1TermIoA_getc
#endif // UNICODE
#else // UNIX_SYSTEM
#define						  Dz1TermIo_new				Dz1TermIoA_new
#define						  Dz1TermIo_del				Dz1TermIoA_del
#define						  Dz1TermIo_delAndSetNull	Dz1TermIoA_delAndSetNull
#define						  Dz1TermIo_getc			Dz1TermIoA_getc
#endif // UNIX_SYSTEM

#endif
