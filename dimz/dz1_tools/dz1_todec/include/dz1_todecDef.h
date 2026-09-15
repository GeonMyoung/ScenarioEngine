#ifndef _DZ1_TDC_DZ1_TODEC_DEF_H_
#define _DZ1_TDC_DZ1_TODEC_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1TdcInfoModule.h"
#include "dz1_elastic_buf.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecUnitSize
typedef enum Dz1TodecUnitSize
{
	Dz1TodecUnitSize_Byte1 = 1,
	Dz1TodecUnitSize_Byte2 = 2,
	Dz1TodecUnitSize_Byte4 = 4,
	Dz1TodecUnitSize_Byte8 = 8,
	Dz1TodecUnitSize_max
} Dz1TodecUnitSize;

DZ1_CPPLINK str_t Dz1TodecUnitSizeStrA(Dz1TodecUnitSize v);
DZ1_CPPLINK Dz1TodecUnitSize Dz1TodecUnitSizeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecUnitSizeStrW(Dz1TodecUnitSize v);
DZ1_CPPLINK Dz1TodecUnitSize Dz1TodecUnitSizeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecUnitSizeStr Dz1TodecUnitSizeStrW
#define Dz1TodecUnitSizeFromStr Dz1TodecUnitSizeFromStrW
#else // UNICODE
#define Dz1TodecUnitSizeStr Dz1TodecUnitSizeStrA
#define Dz1TodecUnitSizeFromStr Dz1TodecUnitSizeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecUnitSizeStr Dz1TodecUnitSizeStrA
#define Dz1TodecUnitSizeFromStr Dz1TodecUnitSizeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecUnitSize *Dz1TodecUnitSize_new(Dz1TodecUnitSize *src, Dz1Error *err);
static __inline__ Dz1TodecUnitSize *Dz1TodecUnitSize_gen(Dz1Error *err) { Dz1TodecUnitSize v = Dz1TodecUnitSize_max; return Dz1TodecUnitSize_new(&v, err); }
static __inline__ void Dz1TodecUnitSize_del(Dz1TodecUnitSize *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecUnitSize_delAndSetNull(void *ptr)
{
	Dz1TodecUnitSize **p = (Dz1TodecUnitSize **)ptr;
	if (p != NULL) { Dz1TodecUnitSize_del(*p); *p = NULL; }
}
// Dz1TodecUnitSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecOrigin
typedef enum Dz1TodecOrigin
{
	Dz1TodecOrigin_MSB,
	Dz1TodecOrigin_LSB,
	Dz1TodecOrigin_max
} Dz1TodecOrigin;

DZ1_CPPLINK str_t Dz1TodecOriginStrA(Dz1TodecOrigin v);
DZ1_CPPLINK Dz1TodecOrigin Dz1TodecOriginFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecOriginStrW(Dz1TodecOrigin v);
DZ1_CPPLINK Dz1TodecOrigin Dz1TodecOriginFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecOriginStr Dz1TodecOriginStrW
#define Dz1TodecOriginFromStr Dz1TodecOriginFromStrW
#else // UNICODE
#define Dz1TodecOriginStr Dz1TodecOriginStrA
#define Dz1TodecOriginFromStr Dz1TodecOriginFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecOriginStr Dz1TodecOriginStrA
#define Dz1TodecOriginFromStr Dz1TodecOriginFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecOrigin *Dz1TodecOrigin_new(Dz1TodecOrigin *src, Dz1Error *err);
static __inline__ Dz1TodecOrigin *Dz1TodecOrigin_gen(Dz1Error *err) { Dz1TodecOrigin v = Dz1TodecOrigin_max; return Dz1TodecOrigin_new(&v, err); }
static __inline__ void Dz1TodecOrigin_del(Dz1TodecOrigin *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecOrigin_delAndSetNull(void *ptr)
{
	Dz1TodecOrigin **p = (Dz1TodecOrigin **)ptr;
	if (p != NULL) { Dz1TodecOrigin_del(*p); *p = NULL; }
}
// Dz1TodecOrigin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBitDescr
typedef struct Dz1TodecBitDescr
{
	u8_t	bit_trim;
	u8_t	bit_take;
} Dz1TodecBitDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBitDescr *Dz1TodecBitDescr_new(u8_t bit_trim, 
															   u8_t bit_take, Dz1Error *err);
static __inline__ Dz1TodecBitDescr *Dz1TodecBitDescr_gen(Dz1Error *err) { return Dz1TodecBitDescr_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecBitDescr_copy(Dz1TodecBitDescr *dst, Dz1TodecBitDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBitDescr *Dz1TodecBitDescr_clone(Dz1TodecBitDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBitDescr_purge(Dz1TodecBitDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBitDescr_del(Dz1TodecBitDescr *p);
static __inline__ void Dz1TodecBitDescr_delAndSetNull(void *ptr)
{
	Dz1TodecBitDescr **p = (Dz1TodecBitDescr **)ptr;
	if (p) { Dz1TodecBitDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBitDescr_dump(Dz1TodecBitDescr *p, int tab);
// Dz1TodecBitDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecByteDescr
typedef struct Dz1TodecByteDescr
{
	u8_t				byte_trim;
	Dz1TodecUnitSize	byte_take;
} Dz1TodecByteDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecByteDescr *Dz1TodecByteDescr_new(u8_t byte_trim, 
																 Dz1TodecUnitSize byte_take, Dz1Error *err);
static __inline__ Dz1TodecByteDescr *Dz1TodecByteDescr_gen(Dz1Error *err) { return Dz1TodecByteDescr_new(0, Dz1TodecUnitSize_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecByteDescr_copy(Dz1TodecByteDescr *dst, Dz1TodecByteDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecByteDescr *Dz1TodecByteDescr_clone(Dz1TodecByteDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecByteDescr_purge(Dz1TodecByteDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecByteDescr_del(Dz1TodecByteDescr *p);
static __inline__ void Dz1TodecByteDescr_delAndSetNull(void *ptr)
{
	Dz1TodecByteDescr **p = (Dz1TodecByteDescr **)ptr;
	if (p) { Dz1TodecByteDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecByteDescr_dump(Dz1TodecByteDescr *p, int tab);
// Dz1TodecByteDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecRestrictDescrPresent
typedef enum Dz1TodecRestrictDescrPresent
{
	Dz1TodecRestrictDescrPresent_fixed,
	Dz1TodecRestrictDescrPresent_dynamic,
	Dz1TodecRestrictDescrPresent_max
} Dz1TodecRestrictDescrPresent;

DZ1_CPPLINK str_t Dz1TodecRestrictDescrPresentStrA(Dz1TodecRestrictDescrPresent v);
DZ1_CPPLINK Dz1TodecRestrictDescrPresent Dz1TodecRestrictDescrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecRestrictDescrPresentStrW(Dz1TodecRestrictDescrPresent v);
DZ1_CPPLINK Dz1TodecRestrictDescrPresent Dz1TodecRestrictDescrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecRestrictDescrPresentStr Dz1TodecRestrictDescrPresentStrW
#define Dz1TodecRestrictDescrPresentFromStr Dz1TodecRestrictDescrPresentFromStrW
#else // UNICODE
#define Dz1TodecRestrictDescrPresentStr Dz1TodecRestrictDescrPresentStrA
#define Dz1TodecRestrictDescrPresentFromStr Dz1TodecRestrictDescrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecRestrictDescrPresentStr Dz1TodecRestrictDescrPresentStrA
#define Dz1TodecRestrictDescrPresentFromStr Dz1TodecRestrictDescrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecRestrictDescrPresent *Dz1TodecRestrictDescrPresent_new(Dz1TodecRestrictDescrPresent *src, Dz1Error *err);
static __inline__ Dz1TodecRestrictDescrPresent *Dz1TodecRestrictDescrPresent_gen(Dz1Error *err) { Dz1TodecRestrictDescrPresent v = Dz1TodecRestrictDescrPresent_max; return Dz1TodecRestrictDescrPresent_new(&v, err); }
#define Dz1TodecRestrictDescrPresent_clone             Dz1TodecRestrictDescrPresent_new
static __inline__ void Dz1TodecRestrictDescrPresent_del(Dz1TodecRestrictDescrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecRestrictDescrPresent_delAndSetNull(void *ptr)
{
	Dz1TodecRestrictDescrPresent **p = (Dz1TodecRestrictDescrPresent **)ptr;
	if (p != NULL) { Dz1TodecRestrictDescrPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecRestrictDescrPresent_dump(Dz1TodecRestrictDescrPresent *v, int tab);
// Dz1TodecRestrictDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecRestrictDescr
typedef struct Dz1TodecRestrictDescr
{
	Dz1TodecRestrictDescrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t				fixed;
		Dz1TodecUnitSize	dynamic;
	} x;
} Dz1TodecRestrictDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecRestrictDescr *Dz1TodecRestrictDescr_new(Dz1TodecRestrictDescrPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecRestrictDescr *Dz1TodecRestrictDescr_gen(Dz1Error *err) { return Dz1TodecRestrictDescr_new(Dz1TodecRestrictDescrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecRestrictDescr_copy(Dz1TodecRestrictDescr *dst, Dz1TodecRestrictDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecRestrictDescr *Dz1TodecRestrictDescr_clone(Dz1TodecRestrictDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecRestrictDescr_purge(Dz1TodecRestrictDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecRestrictDescr_del(Dz1TodecRestrictDescr *p);
static __inline__ void Dz1TodecRestrictDescr_delAndSetNull(void *ptr)
{
	Dz1TodecRestrictDescr **p = (Dz1TodecRestrictDescr **)ptr;
	if (p != NULL) { Dz1TodecRestrictDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecRestrictDescr_dump(Dz1TodecRestrictDescr *p, int tab);
// Dz1TodecRestrictDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchDataEntry
typedef struct Dz1TodecBunchDataEntry
{
	str_t				 src_name;
	Dz1TodecBitDescr	*src_descr;
} Dz1TodecBunchDataEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchDataEntry *Dz1TodecBunchDataEntry_new(str_t src_name, 
																		   Dz1TodecBitDescr *src_descr, Dz1Error *err);
static __inline__ Dz1TodecBunchDataEntry *Dz1TodecBunchDataEntry_gen(Dz1Error *err) { return Dz1TodecBunchDataEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecBunchDataEntry_copy(Dz1TodecBunchDataEntry *dst, Dz1TodecBunchDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchDataEntry *Dz1TodecBunchDataEntry_clone(Dz1TodecBunchDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchDataEntry_purge(Dz1TodecBunchDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchDataEntry_del(Dz1TodecBunchDataEntry *p);
static __inline__ void Dz1TodecBunchDataEntry_delAndSetNull(void *ptr)
{
	Dz1TodecBunchDataEntry **p = (Dz1TodecBunchDataEntry **)ptr;
	if (p) { Dz1TodecBunchDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchDataEntry_dump(Dz1TodecBunchDataEntry *p, int tab);
// Dz1TodecBunchDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchEntryPresent
typedef enum Dz1TodecBunchEntryPresent
{
	Dz1TodecBunchEntryPresent_data_bits,
	Dz1TodecBunchEntryPresent_pad_bits,
	Dz1TodecBunchEntryPresent_max
} Dz1TodecBunchEntryPresent;

DZ1_CPPLINK str_t Dz1TodecBunchEntryPresentStrA(Dz1TodecBunchEntryPresent v);
DZ1_CPPLINK Dz1TodecBunchEntryPresent Dz1TodecBunchEntryPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecBunchEntryPresentStrW(Dz1TodecBunchEntryPresent v);
DZ1_CPPLINK Dz1TodecBunchEntryPresent Dz1TodecBunchEntryPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecBunchEntryPresentStr Dz1TodecBunchEntryPresentStrW
#define Dz1TodecBunchEntryPresentFromStr Dz1TodecBunchEntryPresentFromStrW
#else // UNICODE
#define Dz1TodecBunchEntryPresentStr Dz1TodecBunchEntryPresentStrA
#define Dz1TodecBunchEntryPresentFromStr Dz1TodecBunchEntryPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecBunchEntryPresentStr Dz1TodecBunchEntryPresentStrA
#define Dz1TodecBunchEntryPresentFromStr Dz1TodecBunchEntryPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchEntryPresent *Dz1TodecBunchEntryPresent_new(Dz1TodecBunchEntryPresent *src, Dz1Error *err);
static __inline__ Dz1TodecBunchEntryPresent *Dz1TodecBunchEntryPresent_gen(Dz1Error *err) { Dz1TodecBunchEntryPresent v = Dz1TodecBunchEntryPresent_max; return Dz1TodecBunchEntryPresent_new(&v, err); }
#define Dz1TodecBunchEntryPresent_clone             Dz1TodecBunchEntryPresent_new
static __inline__ void Dz1TodecBunchEntryPresent_del(Dz1TodecBunchEntryPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecBunchEntryPresent_delAndSetNull(void *ptr)
{
	Dz1TodecBunchEntryPresent **p = (Dz1TodecBunchEntryPresent **)ptr;
	if (p != NULL) { Dz1TodecBunchEntryPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchEntryPresent_dump(Dz1TodecBunchEntryPresent *v, int tab);
// Dz1TodecBunchEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchEntry
typedef struct Dz1TodecBunchEntry
{
	Dz1TodecBunchEntryPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TodecBunchDataEntry		*data_bits;
		u8_t						 pad_bits;
	} x;
} Dz1TodecBunchEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchEntry *Dz1TodecBunchEntry_new(Dz1TodecBunchEntryPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecBunchEntry *Dz1TodecBunchEntry_gen(Dz1Error *err) { return Dz1TodecBunchEntry_new(Dz1TodecBunchEntryPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecBunchEntry_copy(Dz1TodecBunchEntry *dst, Dz1TodecBunchEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchEntry *Dz1TodecBunchEntry_clone(Dz1TodecBunchEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchEntry_purge(Dz1TodecBunchEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchEntry_del(Dz1TodecBunchEntry *p);
static __inline__ void Dz1TodecBunchEntry_delAndSetNull(void *ptr)
{
	Dz1TodecBunchEntry **p = (Dz1TodecBunchEntry **)ptr;
	if (p != NULL) { Dz1TodecBunchEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchEntry_dump(Dz1TodecBunchEntry *p, int tab);
// Dz1TodecBunchEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchSeq
typedef struct Dz1TodecBunchSeq
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecBunchSeq *p);
	Dz1Error (*travel)(struct Dz1TodecBunchSeq *p, Dz1Error (*func)(void *ptr, Dz1TodecBunchEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecBunchSeq *p, Dz1Error (*func)(void *ptr, Dz1TodecBunchEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecBunchSeq *p, Dz1Error (*func)(void *ptr, Dz1TodecBunchEntry *entry), void *ptr);
	Dz1TodecBunchEntry **(*get_array)(struct Dz1TodecBunchSeq *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecBunchSeq *p, Dz1TodecBunchEntry *data);
} Dz1TodecBunchSeq;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchSeq *Dz1TodecBunchSeq_new(Dz1Error *err);
static __inline__ Dz1TodecBunchSeq *Dz1TodecBunchSeq_gen(Dz1Error *err) { return Dz1TodecBunchSeq_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchSeq *Dz1TodecBunchSeq_clone(Dz1TodecBunchSeq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchSeq_purge(Dz1TodecBunchSeq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchSeq_del(Dz1TodecBunchSeq *p);
static __inline__ void Dz1TodecBunchSeq_delAndSetNull(void *ptr)
{
	Dz1TodecBunchSeq **p = (Dz1TodecBunchSeq **)ptr;
	if (p != NULL) { Dz1TodecBunchSeq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchSeq_dump(Dz1TodecBunchSeq *p, int tab);

// Dz1TodecBunchSeq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecBunchOfSource
typedef struct Dz1TodecBunchOfSource
{
	Dz1TodecUnitSize	 target_sz;
	Dz1TodecBunchSeq	*seq;
} Dz1TodecBunchOfSource;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchOfSource *Dz1TodecBunchOfSource_new(Dz1TodecUnitSize target_sz, Dz1Error *err);
static __inline__ Dz1TodecBunchOfSource *Dz1TodecBunchOfSource_gen(Dz1Error *err) { return Dz1TodecBunchOfSource_new(Dz1TodecUnitSize_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecBunchOfSource_copy(Dz1TodecBunchOfSource *dst, Dz1TodecBunchOfSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecBunchOfSource *Dz1TodecBunchOfSource_clone(Dz1TodecBunchOfSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchOfSource_purge(Dz1TodecBunchOfSource *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchOfSource_del(Dz1TodecBunchOfSource *p);
static __inline__ void Dz1TodecBunchOfSource_delAndSetNull(void *ptr)
{
	Dz1TodecBunchOfSource **p = (Dz1TodecBunchOfSource **)ptr;
	if (p) { Dz1TodecBunchOfSource_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecBunchOfSource_dump(Dz1TodecBunchOfSource *p, int tab);
// Dz1TodecBunchOfSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleDescrPresent
typedef enum Dz1TodecSingleDescrPresent
{
	Dz1TodecSingleDescrPresent_partial_byte,
	Dz1TodecSingleDescrPresent_restricted,
	Dz1TodecSingleDescrPresent_alter_codec,
	Dz1TodecSingleDescrPresent_max
} Dz1TodecSingleDescrPresent;

DZ1_CPPLINK str_t Dz1TodecSingleDescrPresentStrA(Dz1TodecSingleDescrPresent v);
DZ1_CPPLINK Dz1TodecSingleDescrPresent Dz1TodecSingleDescrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecSingleDescrPresentStrW(Dz1TodecSingleDescrPresent v);
DZ1_CPPLINK Dz1TodecSingleDescrPresent Dz1TodecSingleDescrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecSingleDescrPresentStr Dz1TodecSingleDescrPresentStrW
#define Dz1TodecSingleDescrPresentFromStr Dz1TodecSingleDescrPresentFromStrW
#else // UNICODE
#define Dz1TodecSingleDescrPresentStr Dz1TodecSingleDescrPresentStrA
#define Dz1TodecSingleDescrPresentFromStr Dz1TodecSingleDescrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecSingleDescrPresentStr Dz1TodecSingleDescrPresentStrA
#define Dz1TodecSingleDescrPresentFromStr Dz1TodecSingleDescrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecSingleDescrPresent *Dz1TodecSingleDescrPresent_new(Dz1TodecSingleDescrPresent *src, Dz1Error *err);
static __inline__ Dz1TodecSingleDescrPresent *Dz1TodecSingleDescrPresent_gen(Dz1Error *err) { Dz1TodecSingleDescrPresent v = Dz1TodecSingleDescrPresent_max; return Dz1TodecSingleDescrPresent_new(&v, err); }
#define Dz1TodecSingleDescrPresent_clone             Dz1TodecSingleDescrPresent_new
static __inline__ void Dz1TodecSingleDescrPresent_del(Dz1TodecSingleDescrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecSingleDescrPresent_delAndSetNull(void *ptr)
{
	Dz1TodecSingleDescrPresent **p = (Dz1TodecSingleDescrPresent **)ptr;
	if (p != NULL) { Dz1TodecSingleDescrPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleDescrPresent_dump(Dz1TodecSingleDescrPresent *v, int tab);
// Dz1TodecSingleDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleDescr
typedef struct Dz1TodecSingleDescr
{
	Dz1TodecSingleDescrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TodecByteDescr			*partial_byte;
		Dz1TodecRestrictDescr		*restricted;
		str_t						 alter_codec;
	} x;
} Dz1TodecSingleDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecSingleDescr *Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecSingleDescr *Dz1TodecSingleDescr_gen(Dz1Error *err) { return Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecSingleDescr_copy(Dz1TodecSingleDescr *dst, Dz1TodecSingleDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecSingleDescr *Dz1TodecSingleDescr_clone(Dz1TodecSingleDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleDescr_purge(Dz1TodecSingleDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleDescr_del(Dz1TodecSingleDescr *p);
static __inline__ void Dz1TodecSingleDescr_delAndSetNull(void *ptr)
{
	Dz1TodecSingleDescr **p = (Dz1TodecSingleDescr **)ptr;
	if (p != NULL) { Dz1TodecSingleDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleDescr_dump(Dz1TodecSingleDescr *p, int tab);
// Dz1TodecSingleDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecSingleSource
typedef struct Dz1TodecSingleSource
{
	str_t					 src_name;
	Dz1TodecSingleDescr		*src_descr;
	Dz1TodecUnitSize		 nul_flag;
	str_t					 postfix;
} Dz1TodecSingleSource;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecSingleSource *Dz1TodecSingleSource_new(str_t src_name, 
																	   Dz1TodecSingleDescr *src_descr, 
																	   Dz1TodecUnitSize nul_flag, Dz1Error *err);
static __inline__ Dz1TodecSingleSource *Dz1TodecSingleSource_gen(Dz1Error *err) { return Dz1TodecSingleSource_new(NULL, NULL, Dz1TodecUnitSize_max, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecSingleSource_copy(Dz1TodecSingleSource *dst, Dz1TodecSingleSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecSingleSource *Dz1TodecSingleSource_clone(Dz1TodecSingleSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleSource_purge(Dz1TodecSingleSource *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleSource_del(Dz1TodecSingleSource *p);
static __inline__ void Dz1TodecSingleSource_delAndSetNull(void *ptr)
{
	Dz1TodecSingleSource **p = (Dz1TodecSingleSource **)ptr;
	if (p) { Dz1TodecSingleSource_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecSingleSource_dump(Dz1TodecSingleSource *p, int tab);
// Dz1TodecSingleSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecConditionalSource
typedef struct Dz1TodecConditionalSource
{
	str_t					 src_name;
	str_t					 decider;
	Dz1TodecSingleDescr		*src_descr;
	str_t					 postfix;
} Dz1TodecConditionalSource;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecConditionalSource *Dz1TodecConditionalSource_new(str_t src_name, 
																				 str_t decider, 
																				 Dz1TodecSingleDescr *src_descr, Dz1Error *err);
static __inline__ Dz1TodecConditionalSource *Dz1TodecConditionalSource_gen(Dz1Error *err) { return Dz1TodecConditionalSource_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecConditionalSource_copy(Dz1TodecConditionalSource *dst, Dz1TodecConditionalSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecConditionalSource *Dz1TodecConditionalSource_clone(Dz1TodecConditionalSource *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecConditionalSource_purge(Dz1TodecConditionalSource *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecConditionalSource_del(Dz1TodecConditionalSource *p);
static __inline__ void Dz1TodecConditionalSource_delAndSetNull(void *ptr)
{
	Dz1TodecConditionalSource **p = (Dz1TodecConditionalSource **)ptr;
	if (p) { Dz1TodecConditionalSource_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecConditionalSource_dump(Dz1TodecConditionalSource *p, int tab);
// Dz1TodecConditionalSource
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrDescrPresent
typedef enum Dz1TodecTargetCodecAttrDescrPresent
{
	Dz1TodecTargetCodecAttrDescrPresent_omit,
	Dz1TodecTargetCodecAttrDescrPresent_def,
	Dz1TodecTargetCodecAttrDescrPresent_partial_byte,
	Dz1TodecTargetCodecAttrDescrPresent_alter_codec,
	Dz1TodecTargetCodecAttrDescrPresent_max
} Dz1TodecTargetCodecAttrDescrPresent;

DZ1_CPPLINK str_t Dz1TodecTargetCodecAttrDescrPresentStrA(Dz1TodecTargetCodecAttrDescrPresent v);
DZ1_CPPLINK Dz1TodecTargetCodecAttrDescrPresent Dz1TodecTargetCodecAttrDescrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecTargetCodecAttrDescrPresentStrW(Dz1TodecTargetCodecAttrDescrPresent v);
DZ1_CPPLINK Dz1TodecTargetCodecAttrDescrPresent Dz1TodecTargetCodecAttrDescrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecTargetCodecAttrDescrPresentStr Dz1TodecTargetCodecAttrDescrPresentStrW
#define Dz1TodecTargetCodecAttrDescrPresentFromStr Dz1TodecTargetCodecAttrDescrPresentFromStrW
#else // UNICODE
#define Dz1TodecTargetCodecAttrDescrPresentStr Dz1TodecTargetCodecAttrDescrPresentStrA
#define Dz1TodecTargetCodecAttrDescrPresentFromStr Dz1TodecTargetCodecAttrDescrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecTargetCodecAttrDescrPresentStr Dz1TodecTargetCodecAttrDescrPresentStrA
#define Dz1TodecTargetCodecAttrDescrPresentFromStr Dz1TodecTargetCodecAttrDescrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrDescrPresent *Dz1TodecTargetCodecAttrDescrPresent_new(Dz1TodecTargetCodecAttrDescrPresent *src, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttrDescrPresent *Dz1TodecTargetCodecAttrDescrPresent_gen(Dz1Error *err) { Dz1TodecTargetCodecAttrDescrPresent v = Dz1TodecTargetCodecAttrDescrPresent_max; return Dz1TodecTargetCodecAttrDescrPresent_new(&v, err); }
#define Dz1TodecTargetCodecAttrDescrPresent_clone             Dz1TodecTargetCodecAttrDescrPresent_new
static __inline__ void Dz1TodecTargetCodecAttrDescrPresent_del(Dz1TodecTargetCodecAttrDescrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecTargetCodecAttrDescrPresent_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttrDescrPresent **p = (Dz1TodecTargetCodecAttrDescrPresent **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecAttrDescrPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrDescrPresent_dump(Dz1TodecTargetCodecAttrDescrPresent *v, int tab);
// Dz1TodecTargetCodecAttrDescrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrDescr
typedef struct Dz1TodecTargetCodecAttrDescr
{
	Dz1TodecTargetCodecAttrDescrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t					*omit;
		u32_t					*def;
		Dz1TodecByteDescr		*partial_byte;
		str_t					 alter_codec;
	} x;
} Dz1TodecTargetCodecAttrDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrDescr *Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttrDescr *Dz1TodecTargetCodecAttrDescr_gen(Dz1Error *err) { return Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecTargetCodecAttrDescr_copy(Dz1TodecTargetCodecAttrDescr *dst, Dz1TodecTargetCodecAttrDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrDescr *Dz1TodecTargetCodecAttrDescr_clone(Dz1TodecTargetCodecAttrDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrDescr_purge(Dz1TodecTargetCodecAttrDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrDescr_del(Dz1TodecTargetCodecAttrDescr *p);
static __inline__ void Dz1TodecTargetCodecAttrDescr_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttrDescr **p = (Dz1TodecTargetCodecAttrDescr **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecAttrDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrDescr_dump(Dz1TodecTargetCodecAttrDescr *p, int tab);
// Dz1TodecTargetCodecAttrDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrUnion
typedef struct Dz1TodecTargetCodecAttrUnion
{
	Dz1TodecTargetCodecAttrDescr	*pr;
} Dz1TodecTargetCodecAttrUnion;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrUnion *Dz1TodecTargetCodecAttrUnion_new(Dz1TodecTargetCodecAttrDescr *pr, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttrUnion *Dz1TodecTargetCodecAttrUnion_gen(Dz1Error *err) { return Dz1TodecTargetCodecAttrUnion_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecTargetCodecAttrUnion_copy(Dz1TodecTargetCodecAttrUnion *dst, Dz1TodecTargetCodecAttrUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrUnion *Dz1TodecTargetCodecAttrUnion_clone(Dz1TodecTargetCodecAttrUnion *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrUnion_purge(Dz1TodecTargetCodecAttrUnion *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrUnion_del(Dz1TodecTargetCodecAttrUnion *p);
static __inline__ void Dz1TodecTargetCodecAttrUnion_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttrUnion **p = (Dz1TodecTargetCodecAttrUnion **)ptr;
	if (p) { Dz1TodecTargetCodecAttrUnion_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrUnion_dump(Dz1TodecTargetCodecAttrUnion *p, int tab);
// Dz1TodecTargetCodecAttrUnion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrArray
typedef struct Dz1TodecTargetCodecAttrArray
{
	Dz1TodecTargetCodecAttrDescr	*cnt;
	Dz1TodecTargetCodecAttrDescr	*body;
	str_t							 postfix;
} Dz1TodecTargetCodecAttrArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrArray *Dz1TodecTargetCodecAttrArray_new(Dz1TodecTargetCodecAttrDescr *cnt, 
																					   Dz1TodecTargetCodecAttrDescr *body, 
																					   str_t postfix, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttrArray *Dz1TodecTargetCodecAttrArray_gen(Dz1Error *err) { return Dz1TodecTargetCodecAttrArray_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecTargetCodecAttrArray_copy(Dz1TodecTargetCodecAttrArray *dst, Dz1TodecTargetCodecAttrArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrArray *Dz1TodecTargetCodecAttrArray_clone(Dz1TodecTargetCodecAttrArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrArray_purge(Dz1TodecTargetCodecAttrArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrArray_del(Dz1TodecTargetCodecAttrArray *p);
static __inline__ void Dz1TodecTargetCodecAttrArray_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttrArray **p = (Dz1TodecTargetCodecAttrArray **)ptr;
	if (p) { Dz1TodecTargetCodecAttrArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrArray_dump(Dz1TodecTargetCodecAttrArray *p, int tab);
// Dz1TodecTargetCodecAttrArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttrPresent
typedef enum Dz1TodecTargetCodecAttrPresent
{
	Dz1TodecTargetCodecAttrPresent_st,
	Dz1TodecTargetCodecAttrPresent_un,
	Dz1TodecTargetCodecAttrPresent_ar,
	Dz1TodecTargetCodecAttrPresent_max
} Dz1TodecTargetCodecAttrPresent;

DZ1_CPPLINK str_t Dz1TodecTargetCodecAttrPresentStrA(Dz1TodecTargetCodecAttrPresent v);
DZ1_CPPLINK Dz1TodecTargetCodecAttrPresent Dz1TodecTargetCodecAttrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecTargetCodecAttrPresentStrW(Dz1TodecTargetCodecAttrPresent v);
DZ1_CPPLINK Dz1TodecTargetCodecAttrPresent Dz1TodecTargetCodecAttrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecTargetCodecAttrPresentStr Dz1TodecTargetCodecAttrPresentStrW
#define Dz1TodecTargetCodecAttrPresentFromStr Dz1TodecTargetCodecAttrPresentFromStrW
#else // UNICODE
#define Dz1TodecTargetCodecAttrPresentStr Dz1TodecTargetCodecAttrPresentStrA
#define Dz1TodecTargetCodecAttrPresentFromStr Dz1TodecTargetCodecAttrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecTargetCodecAttrPresentStr Dz1TodecTargetCodecAttrPresentStrA
#define Dz1TodecTargetCodecAttrPresentFromStr Dz1TodecTargetCodecAttrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttrPresent *Dz1TodecTargetCodecAttrPresent_new(Dz1TodecTargetCodecAttrPresent *src, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttrPresent *Dz1TodecTargetCodecAttrPresent_gen(Dz1Error *err) { Dz1TodecTargetCodecAttrPresent v = Dz1TodecTargetCodecAttrPresent_max; return Dz1TodecTargetCodecAttrPresent_new(&v, err); }
#define Dz1TodecTargetCodecAttrPresent_clone             Dz1TodecTargetCodecAttrPresent_new
static __inline__ void Dz1TodecTargetCodecAttrPresent_del(Dz1TodecTargetCodecAttrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecTargetCodecAttrPresent_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttrPresent **p = (Dz1TodecTargetCodecAttrPresent **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecAttrPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttrPresent_dump(Dz1TodecTargetCodecAttrPresent *v, int tab);
// Dz1TodecTargetCodecAttrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecAttr
typedef struct Dz1TodecTargetCodecAttr
{
	Dz1TodecTargetCodecAttrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t							*st;
		Dz1TodecTargetCodecAttrUnion	*un;
		Dz1TodecTargetCodecAttrArray	*ar;
	} x;
} Dz1TodecTargetCodecAttr;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttr *Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecAttr *Dz1TodecTargetCodecAttr_gen(Dz1Error *err) { return Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecTargetCodecAttr_copy(Dz1TodecTargetCodecAttr *dst, Dz1TodecTargetCodecAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecAttr *Dz1TodecTargetCodecAttr_clone(Dz1TodecTargetCodecAttr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttr_purge(Dz1TodecTargetCodecAttr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttr_del(Dz1TodecTargetCodecAttr *p);
static __inline__ void Dz1TodecTargetCodecAttr_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecAttr **p = (Dz1TodecTargetCodecAttr **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecAttr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecAttr_dump(Dz1TodecTargetCodecAttr *p, int tab);
// Dz1TodecTargetCodecAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamEntryPresent
typedef enum Dz1TodecStreamEntryPresent
{
	Dz1TodecStreamEntryPresent_bunch,
	Dz1TodecStreamEntryPresent_conditional,
	Dz1TodecStreamEntryPresent_omit,
	Dz1TodecStreamEntryPresent_single,
	Dz1TodecStreamEntryPresent_pad,
	Dz1TodecStreamEntryPresent_value,
	Dz1TodecStreamEntryPresent_max
} Dz1TodecStreamEntryPresent;

DZ1_CPPLINK str_t Dz1TodecStreamEntryPresentStrA(Dz1TodecStreamEntryPresent v);
DZ1_CPPLINK Dz1TodecStreamEntryPresent Dz1TodecStreamEntryPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecStreamEntryPresentStrW(Dz1TodecStreamEntryPresent v);
DZ1_CPPLINK Dz1TodecStreamEntryPresent Dz1TodecStreamEntryPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecStreamEntryPresentStr Dz1TodecStreamEntryPresentStrW
#define Dz1TodecStreamEntryPresentFromStr Dz1TodecStreamEntryPresentFromStrW
#else // UNICODE
#define Dz1TodecStreamEntryPresentStr Dz1TodecStreamEntryPresentStrA
#define Dz1TodecStreamEntryPresentFromStr Dz1TodecStreamEntryPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecStreamEntryPresentStr Dz1TodecStreamEntryPresentStrA
#define Dz1TodecStreamEntryPresentFromStr Dz1TodecStreamEntryPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecStreamEntryPresent *Dz1TodecStreamEntryPresent_new(Dz1TodecStreamEntryPresent *src, Dz1Error *err);
static __inline__ Dz1TodecStreamEntryPresent *Dz1TodecStreamEntryPresent_gen(Dz1Error *err) { Dz1TodecStreamEntryPresent v = Dz1TodecStreamEntryPresent_max; return Dz1TodecStreamEntryPresent_new(&v, err); }
#define Dz1TodecStreamEntryPresent_clone             Dz1TodecStreamEntryPresent_new
static __inline__ void Dz1TodecStreamEntryPresent_del(Dz1TodecStreamEntryPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecStreamEntryPresent_delAndSetNull(void *ptr)
{
	Dz1TodecStreamEntryPresent **p = (Dz1TodecStreamEntryPresent **)ptr;
	if (p != NULL) { Dz1TodecStreamEntryPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamEntryPresent_dump(Dz1TodecStreamEntryPresent *v, int tab);
// Dz1TodecStreamEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamEntry
typedef struct Dz1TodecStreamEntry
{
	Dz1TodecStreamEntryPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TodecBunchOfSource			*bunch;
		Dz1TodecConditionalSource		*conditional;
		str_t							 omit;
		Dz1TodecSingleSource			*single;
		u16_t							 pad;
		Dz1ElasticBuf					*value;
	} x;
} Dz1TodecStreamEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecStreamEntry *Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TodecStreamEntry *Dz1TodecStreamEntry_gen(Dz1Error *err) { return Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1TodecStreamEntry_copy(Dz1TodecStreamEntry *dst, Dz1TodecStreamEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecStreamEntry *Dz1TodecStreamEntry_clone(Dz1TodecStreamEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamEntry_purge(Dz1TodecStreamEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamEntry_del(Dz1TodecStreamEntry *p);
static __inline__ void Dz1TodecStreamEntry_delAndSetNull(void *ptr)
{
	Dz1TodecStreamEntry **p = (Dz1TodecStreamEntry **)ptr;
	if (p != NULL) { Dz1TodecStreamEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamEntry_dump(Dz1TodecStreamEntry *p, int tab);
// Dz1TodecStreamEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecStreamList
typedef struct Dz1TodecStreamList
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecStreamList *p);
	Dz1Error (*travel)(struct Dz1TodecStreamList *p, Dz1Error (*func)(void *ptr, Dz1TodecStreamEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecStreamList *p, Dz1Error (*func)(void *ptr, Dz1TodecStreamEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecStreamList *p, Dz1Error (*func)(void *ptr, Dz1TodecStreamEntry *entry), void *ptr);
	Dz1TodecStreamEntry **(*get_array)(struct Dz1TodecStreamList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecStreamList *p, Dz1TodecStreamEntry *data);
} Dz1TodecStreamList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecStreamList *Dz1TodecStreamList_new(Dz1Error *err);
static __inline__ Dz1TodecStreamList *Dz1TodecStreamList_gen(Dz1Error *err) { return Dz1TodecStreamList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecStreamList *Dz1TodecStreamList_clone(Dz1TodecStreamList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamList_purge(Dz1TodecStreamList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamList_del(Dz1TodecStreamList *p);
static __inline__ void Dz1TodecStreamList_delAndSetNull(void *ptr)
{
	Dz1TodecStreamList **p = (Dz1TodecStreamList **)ptr;
	if (p != NULL) { Dz1TodecStreamList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecStreamList_dump(Dz1TodecStreamList *p, int tab);

// Dz1TodecStreamList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecMode
typedef enum Dz1TodecTargetCodecMode
{
	Dz1TodecTargetCodecMode_public,
	Dz1TodecTargetCodecMode_header,
	Dz1TodecTargetCodecMode_private,
	Dz1TodecTargetCodecMode_max
} Dz1TodecTargetCodecMode;

DZ1_CPPLINK str_t Dz1TodecTargetCodecModeStrA(Dz1TodecTargetCodecMode v);
DZ1_CPPLINK Dz1TodecTargetCodecMode Dz1TodecTargetCodecModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1TodecTargetCodecModeStrW(Dz1TodecTargetCodecMode v);
DZ1_CPPLINK Dz1TodecTargetCodecMode Dz1TodecTargetCodecModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1TodecTargetCodecModeStr Dz1TodecTargetCodecModeStrW
#define Dz1TodecTargetCodecModeFromStr Dz1TodecTargetCodecModeFromStrW
#else // UNICODE
#define Dz1TodecTargetCodecModeStr Dz1TodecTargetCodecModeStrA
#define Dz1TodecTargetCodecModeFromStr Dz1TodecTargetCodecModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TodecTargetCodecModeStr Dz1TodecTargetCodecModeStrA
#define Dz1TodecTargetCodecModeFromStr Dz1TodecTargetCodecModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecMode *Dz1TodecTargetCodecMode_new(Dz1TodecTargetCodecMode *src, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecMode *Dz1TodecTargetCodecMode_gen(Dz1Error *err) { Dz1TodecTargetCodecMode v = Dz1TodecTargetCodecMode_max; return Dz1TodecTargetCodecMode_new(&v, err); }
static __inline__ void Dz1TodecTargetCodecMode_del(Dz1TodecTargetCodecMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1TodecTargetCodecMode_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecMode **p = (Dz1TodecTargetCodecMode **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecMode_del(*p); *p = NULL; }
}
// Dz1TodecTargetCodecMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecEntry
typedef struct Dz1TodecTargetCodecEntry
{
	str_t						 alter_codec;
	Dz1TodecTargetCodecMode		 mode;
	Dz1TodecTargetCodecAttr		*attr;
	Dz1TodecStreamList			*seq;
	str_t						 postfix;
} Dz1TodecTargetCodecEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_new(str_t alter_codec, 
																			   Dz1TodecTargetCodecMode mode, 
																			   Dz1TodecTargetCodecAttr *attr, Dz1Error *err);
static __inline__ Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_gen(Dz1Error *err) { return Dz1TodecTargetCodecEntry_new(NULL, Dz1TodecTargetCodecMode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecTargetCodecEntry_copy(Dz1TodecTargetCodecEntry *dst, Dz1TodecTargetCodecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecEntry *Dz1TodecTargetCodecEntry_clone(Dz1TodecTargetCodecEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecEntry_purge(Dz1TodecTargetCodecEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecEntry_del(Dz1TodecTargetCodecEntry *p);
static __inline__ void Dz1TodecTargetCodecEntry_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecEntry **p = (Dz1TodecTargetCodecEntry **)ptr;
	if (p) { Dz1TodecTargetCodecEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecEntry_dump(Dz1TodecTargetCodecEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TodecTargetCodecEntry_cmp(Dz1TodecTargetCodecEntry *a, Dz1TodecTargetCodecEntry *b); 
// Dz1TodecTargetCodecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetCodecList
typedef struct Dz1TodecTargetCodecList
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecTargetCodecList *p);
	Dz1Error (*travel)(struct Dz1TodecTargetCodecList *p, Dz1Error (*func)(void *ptr, Dz1TodecTargetCodecEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecTargetCodecList *p, Dz1Error (*func)(void *ptr, Dz1TodecTargetCodecEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecTargetCodecList *p, Dz1Error (*func)(void *ptr, Dz1TodecTargetCodecEntry *entry), void *ptr);
	Dz1TodecTargetCodecEntry **(*get_array)(struct Dz1TodecTargetCodecList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *data);
	bool_t (*remove)(struct Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key);
	Dz1TodecTargetCodecEntry *(*extract)(struct Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key);
	Dz1TodecTargetCodecEntry *(*find)(struct Dz1TodecTargetCodecList *p, Dz1TodecTargetCodecEntry *key);
	int (*cmp)(Dz1TodecTargetCodecEntry *a, Dz1TodecTargetCodecEntry *b);
} Dz1TodecTargetCodecList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecList *Dz1TodecTargetCodecList_new(Dz1Error *err);
static __inline__ Dz1TodecTargetCodecList *Dz1TodecTargetCodecList_gen(Dz1Error *err) { return Dz1TodecTargetCodecList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetCodecList *Dz1TodecTargetCodecList_clone(Dz1TodecTargetCodecList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecList_purge(Dz1TodecTargetCodecList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecList_del(Dz1TodecTargetCodecList *p);
static __inline__ void Dz1TodecTargetCodecList_delAndSetNull(void *ptr)
{
	Dz1TodecTargetCodecList **p = (Dz1TodecTargetCodecList **)ptr;
	if (p != NULL) { Dz1TodecTargetCodecList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetCodecList_dump(Dz1TodecTargetCodecList *p, int tab);

// Dz1TodecTargetCodecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTarget
typedef struct Dz1TodecTarget
{
	str_t						 src_name;
	Dz1TodecTargetCodecList		*codecs;
} Dz1TodecTarget;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTarget *Dz1TodecTarget_new(str_t src_name, Dz1Error *err);
static __inline__ Dz1TodecTarget *Dz1TodecTarget_gen(Dz1Error *err) { return Dz1TodecTarget_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecTarget_copy(Dz1TodecTarget *dst, Dz1TodecTarget *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTarget *Dz1TodecTarget_clone(Dz1TodecTarget *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTarget_purge(Dz1TodecTarget *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTarget_del(Dz1TodecTarget *p);
static __inline__ void Dz1TodecTarget_delAndSetNull(void *ptr)
{
	Dz1TodecTarget **p = (Dz1TodecTarget **)ptr;
	if (p) { Dz1TodecTarget_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTarget_dump(Dz1TodecTarget *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TodecTarget_cmp(Dz1TodecTarget *a, Dz1TodecTarget *b); 
// Dz1TodecTarget
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetList
typedef struct Dz1TodecTargetList
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecTargetList *p);
	Dz1Error (*travel)(struct Dz1TodecTargetList *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecTargetList *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecTargetList *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1TodecTarget **(*get_array)(struct Dz1TodecTargetList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecTargetList *p, Dz1TodecTarget *data);
	int (*cmp)(Dz1TodecTarget *a, Dz1TodecTarget *b);
} Dz1TodecTargetList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetList *Dz1TodecTargetList_new(Dz1Error *err);
static __inline__ Dz1TodecTargetList *Dz1TodecTargetList_gen(Dz1Error *err) { return Dz1TodecTargetList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetList *Dz1TodecTargetList_clone(Dz1TodecTargetList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetList_purge(Dz1TodecTargetList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetList_del(Dz1TodecTargetList *p);
static __inline__ void Dz1TodecTargetList_delAndSetNull(void *ptr)
{
	Dz1TodecTargetList **p = (Dz1TodecTargetList **)ptr;
	if (p != NULL) { Dz1TodecTargetList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetList_dump(Dz1TodecTargetList *p, int tab);

// Dz1TodecTargetList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecTargetTable
typedef struct Dz1TodecTargetTable
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecTargetTable *p);
	Dz1Error (*travel)(struct Dz1TodecTargetTable *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecTargetTable *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecTargetTable *p, Dz1Error (*func)(void *ptr, Dz1TodecTarget *entry), void *ptr);
	Dz1TodecTarget **(*get_array)(struct Dz1TodecTargetTable *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecTargetTable *p, Dz1TodecTarget *data);
	bool_t (*remove)(struct Dz1TodecTargetTable *p, Dz1TodecTarget *key);
	Dz1TodecTarget *(*extract)(struct Dz1TodecTargetTable *p, Dz1TodecTarget *key);
	Dz1TodecTarget *(*find)(struct Dz1TodecTargetTable *p, Dz1TodecTarget *key);
	int (*cmp)(Dz1TodecTarget *a, Dz1TodecTarget *b);
} Dz1TodecTargetTable;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetTable *Dz1TodecTargetTable_new(Dz1Error *err);
static __inline__ Dz1TodecTargetTable *Dz1TodecTargetTable_gen(Dz1Error *err) { return Dz1TodecTargetTable_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecTargetTable *Dz1TodecTargetTable_clone(Dz1TodecTargetTable *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetTable_purge(Dz1TodecTargetTable *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetTable_del(Dz1TodecTargetTable *p);
static __inline__ void Dz1TodecTargetTable_delAndSetNull(void *ptr)
{
	Dz1TodecTargetTable **p = (Dz1TodecTargetTable **)ptr;
	if (p != NULL) { Dz1TodecTargetTable_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecTargetTable_dump(Dz1TodecTargetTable *p, int tab);

// Dz1TodecTargetTable
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncEntry
typedef struct Dz1TodecIncEntry
{
	str_t		name;
} Dz1TodecIncEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncEntry *Dz1TodecIncEntry_new(str_t name, Dz1Error *err);
static __inline__ Dz1TodecIncEntry *Dz1TodecIncEntry_gen(Dz1Error *err) { return Dz1TodecIncEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecIncEntry_copy(Dz1TodecIncEntry *dst, Dz1TodecIncEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncEntry *Dz1TodecIncEntry_clone(Dz1TodecIncEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncEntry_purge(Dz1TodecIncEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncEntry_del(Dz1TodecIncEntry *p);
static __inline__ void Dz1TodecIncEntry_delAndSetNull(void *ptr)
{
	Dz1TodecIncEntry **p = (Dz1TodecIncEntry **)ptr;
	if (p) { Dz1TodecIncEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncEntry_dump(Dz1TodecIncEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TodecIncEntry_cmp(Dz1TodecIncEntry *a, Dz1TodecIncEntry *b); 
// Dz1TodecIncEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncIndex
typedef struct Dz1TodecIncIndex
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecIncIndex *p);
	Dz1Error (*travel)(struct Dz1TodecIncIndex *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecIncIndex *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecIncIndex *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1TodecIncEntry **(*get_array)(struct Dz1TodecIncIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecIncIndex *p, Dz1TodecIncEntry *data);
	bool_t (*remove)(struct Dz1TodecIncIndex *p, Dz1TodecIncEntry *key);
	Dz1TodecIncEntry *(*extract)(struct Dz1TodecIncIndex *p, Dz1TodecIncEntry *key);
	Dz1TodecIncEntry *(*find)(struct Dz1TodecIncIndex *p, Dz1TodecIncEntry *key);
	int (*cmp)(Dz1TodecIncEntry *a, Dz1TodecIncEntry *b);
} Dz1TodecIncIndex;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncIndex *Dz1TodecIncIndex_new(Dz1Error *err);
static __inline__ Dz1TodecIncIndex *Dz1TodecIncIndex_gen(Dz1Error *err) { return Dz1TodecIncIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncIndex *Dz1TodecIncIndex_clone(Dz1TodecIncIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncIndex_purge(Dz1TodecIncIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncIndex_del(Dz1TodecIncIndex *p);
static __inline__ void Dz1TodecIncIndex_delAndSetNull(void *ptr)
{
	Dz1TodecIncIndex **p = (Dz1TodecIncIndex **)ptr;
	if (p != NULL) { Dz1TodecIncIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncIndex_dump(Dz1TodecIncIndex *p, int tab);

// Dz1TodecIncIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecIncList
typedef struct Dz1TodecIncList
{
	void *storage;
	unsigned int (*count)(struct Dz1TodecIncList *p);
	Dz1Error (*travel)(struct Dz1TodecIncList *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TodecIncList *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TodecIncList *p, Dz1Error (*func)(void *ptr, Dz1TodecIncEntry *entry), void *ptr);
	Dz1TodecIncEntry **(*get_array)(struct Dz1TodecIncList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1TodecIncList *p, Dz1TodecIncEntry *data);
	int (*cmp)(Dz1TodecIncEntry *a, Dz1TodecIncEntry *b);
} Dz1TodecIncList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncList *Dz1TodecIncList_new(Dz1Error *err);
static __inline__ Dz1TodecIncList *Dz1TodecIncList_gen(Dz1Error *err) { return Dz1TodecIncList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecIncList *Dz1TodecIncList_clone(Dz1TodecIncList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncList_purge(Dz1TodecIncList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncList_del(Dz1TodecIncList *p);
static __inline__ void Dz1TodecIncList_delAndSetNull(void *ptr)
{
	Dz1TodecIncList **p = (Dz1TodecIncList **)ptr;
	if (p != NULL) { Dz1TodecIncList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecIncList_dump(Dz1TodecIncList *p, int tab);

// Dz1TodecIncList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecInclude
typedef struct Dz1TodecInclude
{
	Dz1TodecIncIndex	*ref_idx;
	Dz1TodecIncList		*seq;
} Dz1TodecInclude;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecInclude *Dz1TodecInclude_new(Dz1Error *err);
static __inline__ Dz1TodecInclude *Dz1TodecInclude_gen(Dz1Error *err) { return Dz1TodecInclude_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1TodecInclude_copy(Dz1TodecInclude *dst, Dz1TodecInclude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TodecInclude *Dz1TodecInclude_clone(Dz1TodecInclude *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecInclude_purge(Dz1TodecInclude *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecInclude_del(Dz1TodecInclude *p);
static __inline__ void Dz1TodecInclude_delAndSetNull(void *ptr)
{
	Dz1TodecInclude **p = (Dz1TodecInclude **)ptr;
	if (p) { Dz1TodecInclude_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecInclude_dump(Dz1TodecInclude *p, int tab);
// Dz1TodecInclude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Todec
typedef struct Dz1Todec
{
	str_t					 mod_name;
	Dz1TodecInclude			*incl;
	Dz1TodecTargetList		*list;
	Dz1TodecTargetTable		*idx;
} Dz1Todec;

DZ1_CPPLINK DZ1_DLLPORT Dz1Todec *Dz1Todec_new(str_t mod_name, Dz1Error *err);	// User Customized
static __inline__ Dz1Todec *Dz1Todec_gen(Dz1Error *err) { return Dz1Todec_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Todec_copy(Dz1Todec *dst, Dz1Todec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Todec *Dz1Todec_clone(Dz1Todec *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Todec_purge(Dz1Todec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Todec_del(Dz1Todec *p);
static __inline__ void Dz1Todec_delAndSetNull(void *ptr)
{
	Dz1Todec **p = (Dz1Todec **)ptr;
	if (p) { Dz1Todec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Todec_dump(Dz1Todec *p, int tab);
// Dz1Todec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TODEC_FLAGS_USE_STACK
#define TODEC_FLAGS_USE_STACK			1
// TODEC_FLAGS_USE_STACK
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TodecPubArg
typedef struct Dz1TodecPubArg
{
	str_t		mod_inc_path;
	str_t		dst_path_c;
	str_t		dst_path_h;
	bool_t		output_src;
	bool_t		output_hdr;
	u32_t		flags;
} Dz1TodecPubArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TodecPubArg *Dz1TodecPubArg_new(str_t mod_inc_path, 
														   str_t dst_path_c, 
														   str_t dst_path_h, 
														   bool_t output_src, 
														   bool_t output_hdr, 
														   u32_t flags, Dz1Error *err);
static __inline__ Dz1TodecPubArg *Dz1TodecPubArg_gen(Dz1Error *err) { return Dz1TodecPubArg_new(NULL, NULL, NULL, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecPubArg_purge(Dz1TodecPubArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecPubArg_del(Dz1TodecPubArg *p);
static __inline__ void Dz1TodecPubArg_delAndSetNull(void *ptr)
{
	Dz1TodecPubArg **p = (Dz1TodecPubArg **)ptr;
	if (p) { Dz1TodecPubArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TodecPubArg_dump(Dz1TodecPubArg *p, int tab);
// Dz1TodecPubArg
////////////////////////////////////////////////////////////////////////////////

#endif
