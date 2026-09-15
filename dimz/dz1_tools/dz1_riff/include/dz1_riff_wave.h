#ifndef _DZ1_TDC_DZ1_RIFF_WAVE_H_
#define _DZ1_TDC_DZ1_RIFF_WAVE_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveUnknown
typedef struct Dz1RiffWaveUnknown
{
	str_t			 id;
	Dz1Binary		*chunk;
} Dz1RiffWaveUnknown;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveUnknown *Dz1RiffWaveUnknown_new(str_t id, 
																   Dz1Binary *chunk, Dz1Error *err);
static __inline__ Dz1RiffWaveUnknown *Dz1RiffWaveUnknown_gen(Dz1Error *err) { return Dz1RiffWaveUnknown_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1RiffWaveUnknown_copy(Dz1RiffWaveUnknown *dst, Dz1RiffWaveUnknown *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveUnknown *Dz1RiffWaveUnknown_clone(Dz1RiffWaveUnknown *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveUnknown_purge(Dz1RiffWaveUnknown *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveUnknown_del(Dz1RiffWaveUnknown *p);
static __inline__ void Dz1RiffWaveUnknown_delAndSetNull(void *ptr)
{
	Dz1RiffWaveUnknown **p = (Dz1RiffWaveUnknown **)ptr;
	if (p) { Dz1RiffWaveUnknown_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveUnknown_dump(Dz1RiffWaveUnknown *p, int tab);
// Dz1RiffWaveUnknown
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveFmt
typedef struct Dz1RiffWaveFmt
{
	u16_t			 audioFormat;
	u16_t			 numOfChannel;
	u32_t			 sampleRate;
	u32_t			 byteRate;
	u16_t			 blockAlign;
	u16_t			 bitPerSample;
	Dz1Binary		*extra;
} Dz1RiffWaveFmt;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveFmt *Dz1RiffWaveFmt_new(u16_t audioFormat, 
														   u16_t numOfChannel, 
														   u32_t sampleRate, 
														   u32_t byteRate, 
														   u16_t blockAlign, 
														   u16_t bitPerSample, 
														   Dz1Binary *extra, Dz1Error *err);
static __inline__ Dz1RiffWaveFmt *Dz1RiffWaveFmt_gen(Dz1Error *err) { return Dz1RiffWaveFmt_new(0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1RiffWaveFmt_copy(Dz1RiffWaveFmt *dst, Dz1RiffWaveFmt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveFmt *Dz1RiffWaveFmt_clone(Dz1RiffWaveFmt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveFmt_purge(Dz1RiffWaveFmt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveFmt_del(Dz1RiffWaveFmt *p);
static __inline__ void Dz1RiffWaveFmt_delAndSetNull(void *ptr)
{
	Dz1RiffWaveFmt **p = (Dz1RiffWaveFmt **)ptr;
	if (p) { Dz1RiffWaveFmt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveFmt_dump(Dz1RiffWaveFmt *p, int tab);
// Dz1RiffWaveFmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveData
typedef struct Dz1RiffWaveData
{
	Dz1Binary		*data;
} Dz1RiffWaveData;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveData *Dz1RiffWaveData_new(Dz1Binary *data, Dz1Error *err);
static __inline__ Dz1RiffWaveData *Dz1RiffWaveData_gen(Dz1Error *err) { return Dz1RiffWaveData_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1RiffWaveData_copy(Dz1RiffWaveData *dst, Dz1RiffWaveData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveData *Dz1RiffWaveData_clone(Dz1RiffWaveData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveData_purge(Dz1RiffWaveData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveData_del(Dz1RiffWaveData *p);
static __inline__ void Dz1RiffWaveData_delAndSetNull(void *ptr)
{
	Dz1RiffWaveData **p = (Dz1RiffWaveData **)ptr;
	if (p) { Dz1RiffWaveData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveData_dump(Dz1RiffWaveData *p, int tab);
// Dz1RiffWaveData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveChunkPresent
typedef enum Dz1RiffWaveChunkPresent
{
	Dz1RiffWaveChunkPresent_fmt,
	Dz1RiffWaveChunkPresent_data,
	Dz1RiffWaveChunkPresent_unknown,
	Dz1RiffWaveChunkPresent_max
} Dz1RiffWaveChunkPresent;

DZ1_CPPLINK str_t Dz1RiffWaveChunkPresentStrA(Dz1RiffWaveChunkPresent v);
DZ1_CPPLINK Dz1RiffWaveChunkPresent Dz1RiffWaveChunkPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1RiffWaveChunkPresentStrW(Dz1RiffWaveChunkPresent v);
DZ1_CPPLINK Dz1RiffWaveChunkPresent Dz1RiffWaveChunkPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1RiffWaveChunkPresentStr Dz1RiffWaveChunkPresentStrW
#define Dz1RiffWaveChunkPresentFromStr Dz1RiffWaveChunkPresentFromStrW
#else // UNICODE
#define Dz1RiffWaveChunkPresentStr Dz1RiffWaveChunkPresentStrA
#define Dz1RiffWaveChunkPresentFromStr Dz1RiffWaveChunkPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1RiffWaveChunkPresentStr Dz1RiffWaveChunkPresentStrA
#define Dz1RiffWaveChunkPresentFromStr Dz1RiffWaveChunkPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveChunkPresent *Dz1RiffWaveChunkPresent_new(Dz1RiffWaveChunkPresent *src, Dz1Error *err);
static __inline__ Dz1RiffWaveChunkPresent *Dz1RiffWaveChunkPresent_gen(Dz1Error *err) { Dz1RiffWaveChunkPresent v = Dz1RiffWaveChunkPresent_max; return Dz1RiffWaveChunkPresent_new(&v, err); }
#define Dz1RiffWaveChunkPresent_clone             Dz1RiffWaveChunkPresent_new
static __inline__ void Dz1RiffWaveChunkPresent_del(Dz1RiffWaveChunkPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1RiffWaveChunkPresent_delAndSetNull(void *ptr)
{
	Dz1RiffWaveChunkPresent **p = (Dz1RiffWaveChunkPresent **)ptr;
	if (p != NULL) { Dz1RiffWaveChunkPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveChunkPresent_dump(Dz1RiffWaveChunkPresent *v, int tab);
// Dz1RiffWaveChunkPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWaveChunk
typedef struct Dz1RiffWaveChunk
{
	Dz1RiffWaveChunkPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1RiffWaveFmt			*fmt;
		Dz1RiffWaveData			*data;
		Dz1RiffWaveUnknown		*unknown;
	} x;
} Dz1RiffWaveChunk;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveChunk *Dz1RiffWaveChunk_new(Dz1RiffWaveChunkPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1RiffWaveChunk *Dz1RiffWaveChunk_gen(Dz1Error *err) { return Dz1RiffWaveChunk_new(Dz1RiffWaveChunkPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1RiffWaveChunk_copy(Dz1RiffWaveChunk *dst, Dz1RiffWaveChunk *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWaveChunk *Dz1RiffWaveChunk_clone(Dz1RiffWaveChunk *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveChunk_purge(Dz1RiffWaveChunk *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveChunk_del(Dz1RiffWaveChunk *p);
static __inline__ void Dz1RiffWaveChunk_delAndSetNull(void *ptr)
{
	Dz1RiffWaveChunk **p = (Dz1RiffWaveChunk **)ptr;
	if (p != NULL) { Dz1RiffWaveChunk_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWaveChunk_dump(Dz1RiffWaveChunk *p, int tab);
// Dz1RiffWaveChunk
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffWave
typedef struct Dz1RiffWave
{
	void *storage;
	unsigned int (*count)(struct Dz1RiffWave *p);
	Dz1Error (*travel)(struct Dz1RiffWave *p, Dz1Error (*func)(void *ptr, Dz1RiffWaveChunk *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1RiffWave *p, Dz1Error (*func)(void *ptr, Dz1RiffWaveChunk *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1RiffWave *p, Dz1Error (*func)(void *ptr, Dz1RiffWaveChunk *entry), void *ptr);
	Dz1RiffWaveChunk **(*get_array)(struct Dz1RiffWave *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1RiffWave *p, Dz1RiffWaveChunk *data);
} Dz1RiffWave;

DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWave *Dz1RiffWave_new(Dz1Error *err);
static __inline__ Dz1RiffWave *Dz1RiffWave_gen(Dz1Error *err) { return Dz1RiffWave_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1RiffWave *Dz1RiffWave_clone(Dz1RiffWave *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWave_purge(Dz1RiffWave *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWave_del(Dz1RiffWave *p);
static __inline__ void Dz1RiffWave_delAndSetNull(void *ptr)
{
	Dz1RiffWave **p = (Dz1RiffWave **)ptr;
	if (p != NULL) { Dz1RiffWave_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1RiffWave_dump(Dz1RiffWave *p, int tab);

// Dz1RiffWave
////////////////////////////////////////////////////////////////////////////////

#endif
