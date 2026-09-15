#ifndef _DZ1_TDC_DZ1_RIFF_H_
#define _DZ1_TDC_DZ1_RIFF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_riff_wave.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffDataPresent
typedef enum Dz1RiffDataPresent
{
	Dz1RiffDataPresent_wave,
	Dz1RiffDataPresent_max
} Dz1RiffDataPresent;

DZ1_CPPLINK str_t Dz1RiffDataPresentStrA(Dz1RiffDataPresent v);
DZ1_CPPLINK Dz1RiffDataPresent Dz1RiffDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1RiffDataPresentStrW(Dz1RiffDataPresent v);
DZ1_CPPLINK Dz1RiffDataPresent Dz1RiffDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1RiffDataPresentStr Dz1RiffDataPresentStrW
#define Dz1RiffDataPresentFromStr Dz1RiffDataPresentFromStrW
#else // UNICODE
#define Dz1RiffDataPresentStr Dz1RiffDataPresentStrA
#define Dz1RiffDataPresentFromStr Dz1RiffDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1RiffDataPresentStr Dz1RiffDataPresentStrA
#define Dz1RiffDataPresentFromStr Dz1RiffDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffDataPresent *Dz1RiffDataPresent_new(Dz1RiffDataPresent *src, Dz1Error *err);
static __inline__ Dz1RiffDataPresent *Dz1RiffDataPresent_gen(Dz1Error *err) { Dz1RiffDataPresent v = Dz1RiffDataPresent_max; return Dz1RiffDataPresent_new(&v, err); }
#define Dz1RiffDataPresent_clone             Dz1RiffDataPresent_new
static __inline__ void Dz1RiffDataPresent_del(Dz1RiffDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1RiffDataPresent_delAndSetNull(void *ptr)
{
	Dz1RiffDataPresent **p = (Dz1RiffDataPresent **)ptr;
	if (p != NULL) { Dz1RiffDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffDataPresent_dump(Dz1RiffDataPresent *v, int tab);
// Dz1RiffDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffData
typedef struct Dz1RiffData
{
	Dz1RiffDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1RiffWave		*wave;
	} x;
} Dz1RiffData;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffData *Dz1RiffData_new(Dz1RiffDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1RiffData *Dz1RiffData_gen(Dz1Error *err) { return Dz1RiffData_new(Dz1RiffDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1RiffData_copy(Dz1RiffData *dst, Dz1RiffData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffData *Dz1RiffData_clone(Dz1RiffData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffData_purge(Dz1RiffData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffData_del(Dz1RiffData *p);
static __inline__ void Dz1RiffData_delAndSetNull(void *ptr)
{
	Dz1RiffData **p = (Dz1RiffData **)ptr;
	if (p != NULL) { Dz1RiffData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffData_dump(Dz1RiffData *p, int tab);
// Dz1RiffData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Riff
typedef struct Dz1Riff
{
	Dz1RiffData		*data;
} Dz1Riff;

DZ1_CPPLINK DZ1_DLLPORT Dz1Riff *Dz1Riff_new(Dz1RiffData *data, Dz1Error *err);
static __inline__ Dz1Riff *Dz1Riff_gen(Dz1Error *err) { return Dz1Riff_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Riff_copy(Dz1Riff *dst, Dz1Riff *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Riff *Dz1Riff_clone(Dz1Riff *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Riff_purge(Dz1Riff *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Riff_del(Dz1Riff *p);
static __inline__ void Dz1Riff_delAndSetNull(void *ptr)
{
	Dz1Riff **p = (Dz1Riff **)ptr;
	if (p) { Dz1Riff_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Riff_dump(Dz1Riff *p, int tab);
// Dz1Riff
////////////////////////////////////////////////////////////////////////////////

#endif
