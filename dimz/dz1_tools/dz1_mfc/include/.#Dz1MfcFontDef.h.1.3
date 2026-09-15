#ifndef _DZ1_TDC_DZ1_MFC_FONT_DEF_H_
#define _DZ1_TDC_DZ1_MFC_FONT_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFontEntry
typedef struct Dz1MfcFontEntry
{
	Dz1Str		 name;
	Dz1Str		 font_name;
	u16_t		 font_size;
	void		*font;
} Dz1MfcFontEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFontEntry *Dz1MfcFontEntry_new(Dz1Str name, 
															 Dz1Str font_name, 
															 u16_t font_size, Dz1Error *err);	// User Customized
static __inline__ Dz1MfcFontEntry *Dz1MfcFontEntry_gen(Dz1Error *err) { return Dz1MfcFontEntry_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1MfcFontEntry_copy(Dz1MfcFontEntry *dst, Dz1MfcFontEntry *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFontEntry *Dz1MfcFontEntry_clone(Dz1MfcFontEntry *src, Dz1Error *err);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontEntry_purge(Dz1MfcFontEntry *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontEntry_del(Dz1MfcFontEntry *p);	// User Customized
static __inline__ void Dz1MfcFontEntry_delAndSetNull(void *ptr)
{
	Dz1MfcFontEntry **p = (Dz1MfcFontEntry **)ptr;
	if (p) { Dz1MfcFontEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontEntry_dump(Dz1MfcFontEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1MfcFontEntry_cmp(Dz1MfcFontEntry *a, Dz1MfcFontEntry *b); 
// Dz1MfcFontEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFontList
typedef struct Dz1MfcFontList
{
	void *storage;
	unsigned int (*count)(struct Dz1MfcFontList *p);
	Dz1Error (*travel)(struct Dz1MfcFontList *p, Dz1Error (*func)(void *ptr, Dz1MfcFontEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1MfcFontList *p, Dz1Error (*func)(void *ptr, Dz1MfcFontEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1MfcFontList *p, Dz1Error (*func)(void *ptr, Dz1MfcFontEntry *entry), void *ptr);
	Dz1MfcFontEntry **(*get_array)(struct Dz1MfcFontList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1MfcFontList *p, Dz1MfcFontEntry *data);
	bool_t (*remove)(struct Dz1MfcFontList *p, Dz1MfcFontEntry *key);
	Dz1MfcFontEntry *(*extract)(struct Dz1MfcFontList *p, Dz1MfcFontEntry *key);
	Dz1MfcFontEntry *(*find)(struct Dz1MfcFontList *p, Dz1MfcFontEntry *key);
	int (*cmp)(Dz1MfcFontEntry *a, Dz1MfcFontEntry *b);
} Dz1MfcFontList;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFontList *Dz1MfcFontList_new(Dz1Error *err);
static __inline__ Dz1MfcFontList *Dz1MfcFontList_gen(Dz1Error *err) { return Dz1MfcFontList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFontList *Dz1MfcFontList_clone(Dz1MfcFontList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontList_purge(Dz1MfcFontList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontList_del(Dz1MfcFontList *p);
static __inline__ void Dz1MfcFontList_delAndSetNull(void *ptr)
{
	Dz1MfcFontList **p = (Dz1MfcFontList **)ptr;
	if (p != NULL) { Dz1MfcFontList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFontList_dump(Dz1MfcFontList *p, int tab);

// Dz1MfcFontList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcFonts
typedef struct Dz1MfcFonts
{
	Dz1MfcFontList		*Dz1MfcFontList;
	real64_t			 factor;
} Dz1MfcFonts;

DZ1_CPPLINK DZ1_DLLPORT Dz1MfcFonts *Dz1MfcFonts_new(real64_t factor, Dz1Error *err);
static __inline__ Dz1MfcFonts *Dz1MfcFonts_gen(Dz1Error *err) { return Dz1MfcFonts_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFonts_purge(Dz1MfcFonts *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFonts_del(Dz1MfcFonts *p);
static __inline__ void Dz1MfcFonts_delAndSetNull(void *ptr)
{
	Dz1MfcFonts **p = (Dz1MfcFonts **)ptr;
	if (p) { Dz1MfcFonts_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1MfcFonts_dump(Dz1MfcFonts *p, int tab);
// Dz1MfcFonts
////////////////////////////////////////////////////////////////////////////////

#endif
