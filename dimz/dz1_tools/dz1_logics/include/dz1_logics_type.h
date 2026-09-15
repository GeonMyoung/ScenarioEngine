#ifndef DZ1_LOGICS_TYPE_H
#define DZ1_LOGICS_TYPE_H

#include <dz1_str.h>
#include <dz1_error.h>

///////////////////////////////////////////////////////////////////////////////
// Dz1LogicStringRefArrA
typedef struct Dz1LogicStringRefArrA
{
	str_t			*arr;				// string is references
	size_t			 alloc_cnt;
	size_t			 filled_cnt;
} Dz1LogicStringRefArrA;

DZ1_CPPLINK Dz1LogicStringRefArrA	*Dz1LogicStringRefArrA_new(size_t arr_cnt, Dz1Error *err);
DZ1_CPPLINK Dz1LogicStringRefArrA	*Dz1LogicStringRefArrA_clone(Dz1LogicStringRefArrA *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1LogicStringRefArrA_del(Dz1LogicStringRefArrA *p);
static __inline__ void				 Dz1LogicStringRefArrA_delAndSetNull(void *pptr)
{
	Dz1LogicStringRefArrA **p = (Dz1LogicStringRefArrA **)pptr;
	Dz1LogicStringRefArrA_del(*p); (*p) = NULL;
}
DZ1_CPPLINK void					 Dz1LogicStringRefArrA_dump(Dz1LogicStringRefArrA *p, int tab);
DZ1_CPPLINK void					 Dz1LogicStringRefArrA_fdump(FILE *fp, Dz1LogicStringRefArrA *p, int tab);
DZ1_CPPLINK Dz1LogicStringRefArrA	*Dz1LogicStringRefArrA_build(str_t src[], size_t src_cnt, Dz1Error *err);
// Dz1LogicStringRefArrA
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1LogicStringArrA
typedef Dz1LogicStringRefArrA Dz1LogicStringArrA;
#define								 Dz1LogicStringArrA_new				Dz1LogicStringRefArrA_new
#define								 Dz1LogicStringArrA_clone			Dz1LogicStringRefArrA_clone
#define								 Dz1LogicStringArrA_del				Dz1LogicStringRefArrA_del
#define								 Dz1LogicStringArrA_delAndSetNull	Dz1LogicStringRefArrA_delAndSetNull
#define								 Dz1LogicStringArrA_dump			Dz1LogicStringRefArrA_dump
#define								 Dz1LogicStringArrA_fdump			Dz1LogicStringRefArrA_fdump
#define								 Dz1LogicStringArrA_build			Dz1LogicStringRefArrA_build
// Dz1LogicStringArrA
///////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1LogicStringRefArrW
typedef struct Dz1LogicStringRefArrW
{
	wstr_t			*arr;				// string is references
	size_t			 alloc_cnt;
	size_t			 filled_cnt;
} Dz1LogicStringRefArrW;

DZ1_CPPLINK Dz1LogicStringRefArrW	*Dz1LogicStringRefArrW_new(size_t arr_cnt, Dz1Error *err);
DZ1_CPPLINK Dz1LogicStringRefArrW	*Dz1LogicStringRefArrW_clone(Dz1LogicStringRefArrW *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1LogicStringRefArrW_del(Dz1LogicStringRefArrW *p);
static __inline__ void				 Dz1LogicStringRefArrW_delAndSetNull(void *pptr)
{
	Dz1LogicStringRefArrW **p = (Dz1LogicStringRefArrW **)pptr;
	Dz1LogicStringRefArrW_del(*p); (*p) = NULL;
}
DZ1_CPPLINK void					 Dz1LogicStringRefArrW_dump(Dz1LogicStringRefArrW *p, int tab);
DZ1_CPPLINK void					 Dz1LogicStringRefArrW_fdump(FILE *fp, Dz1LogicStringRefArrW *p, int tab);
DZ1_CPPLINK Dz1LogicStringRefArrW	*Dz1LogicStringRefArrW_build(wstr_t src[], size_t src_cnt, Dz1Error *err);
// Dz1LogicStringRefArrW
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1LogicStringArrW
typedef Dz1LogicStringRefArrW Dz1LogicStringArrW;
#define								 Dz1LogicStringArrW_new				Dz1LogicStringRefArrW_new
#define								 Dz1LogicStringArrW_clone			Dz1LogicStringRefArrW_clone
#define								 Dz1LogicStringArrW_del				Dz1LogicStringRefArrW_del
#define								 Dz1LogicStringArrW_delAndSetNull	Dz1LogicStringRefArrW_delAndSetNull
#define								 Dz1LogicStringArrW_dump			Dz1LogicStringRefArrW_dump
#define								 Dz1LogicStringArrW_fdump			Dz1LogicStringRefArrW_fdump
#define								 Dz1LogicStringArrW_build			Dz1LogicStringRefArrW_build
// Dz1LogicStringArrW
///////////////////////////////////////////////////////////////////////////////

#ifdef UNICODE
#define								 Dz1LogicStringRefArr				Dz1LogicStringRefArrW
#define								 Dz1LogicStringRefArr_new			Dz1LogicStringRefArrW_new
#define								 Dz1LogicStringRefArr_clone			Dz1LogicStringRefArrW_clone
#define								 Dz1LogicStringRefArr_del			Dz1LogicStringRefArrW_del
#define								 Dz1LogicStringRefArr_delAndSetNull	Dz1LogicStringRefArrW_delAndSetNull
#define								 Dz1LogicStringRefArr_dump			Dz1LogicStringRefArrW_dump
#define								 Dz1LogicStringRefArr_fdump			Dz1LogicStringRefArrW_fdump
#define								 Dz1LogicStringRefArr_build			Dz1LogicStringRefArrW_build

#define								 Dz1LogicStringArr					Dz1LogicStringArrW
#define								 Dz1LogicStringArr_new				Dz1LogicStringArrW_new
#define								 Dz1LogicStringArr_clone			Dz1LogicStringArrW_clone
#define								 Dz1LogicStringArr_del				Dz1LogicStringArrW_del
#define								 Dz1LogicStringArr_delAndSetNull	Dz1LogicStringArrW_delAndSetNull
#define								 Dz1LogicStringArr_dump				Dz1LogicStringArrW_dump
#define								 Dz1LogicStringArr_fdump			Dz1LogicStringArrW_fdump
#define								 Dz1LogicStringArr_build			Dz1LogicStringArrW_build
#else // UNICODE
#define								 Dz1LogicStringRefArr				Dz1LogicStringRefArrA
#define								 Dz1LogicStringRefArr_new			Dz1LogicStringRefArrA_new
#define								 Dz1LogicStringRefArr_clone			Dz1LogicStringRefArrA_clone
#define								 Dz1LogicStringRefArr_del			Dz1LogicStringRefArrA_del
#define								 Dz1LogicStringRefArr_delAndSetNull	Dz1LogicStringRefArrA_delAndSetNull
#define								 Dz1LogicStringRefArr_dump			Dz1LogicStringRefArrA_dump
#define								 Dz1LogicStringRefArr_fdump			Dz1LogicStringRefArrA_fdump
#define								 Dz1LogicStringRefArr_build			Dz1LogicStringRefArrA_build

#define								 Dz1LogicStringArr					Dz1LogicStringArrA
#define								 Dz1LogicStringArr_new				Dz1LogicStringArrA_new
#define								 Dz1LogicStringArr_clone			Dz1LogicStringArrA_clone
#define								 Dz1LogicStringArr_del				Dz1LogicStringArrA_del
#define								 Dz1LogicStringArr_delAndSetNull	Dz1LogicStringArrA_delAndSetNull
#define								 Dz1LogicStringArr_dump				Dz1LogicStringArrA_dump
#define								 Dz1LogicStringArr_fdump			Dz1LogicStringArrA_fdump
#define								 Dz1LogicStringArr_build			Dz1LogicStringArrA_build
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1LogicStringRefArr				Dz1LogicStringRefArrA
#define								 Dz1LogicStringRefArr_new			Dz1LogicStringRefArrA_new
#define								 Dz1LogicStringRefArr_clone			Dz1LogicStringRefArrA_clone
#define								 Dz1LogicStringRefArr_del			Dz1LogicStringRefArrA_del
#define								 Dz1LogicStringRefArr_delAndSetNull	Dz1LogicStringRefArrA_delAndSetNull
#define								 Dz1LogicStringRefArr_dump			Dz1LogicStringRefArrA_dump
#define								 Dz1LogicStringRefArr_fdump			Dz1LogicStringRefArrA_fdump
#define								 Dz1LogicStringRefArr_build			Dz1LogicStringRefArrA_build

#define								 Dz1LogicStringArr					Dz1LogicStringArrA
#define								 Dz1LogicStringArr_new				Dz1LogicStringArrA_new
#define								 Dz1LogicStringArr_clone			Dz1LogicStringArrA_clone
#define								 Dz1LogicStringArr_del				Dz1LogicStringArrA_del
#define								 Dz1LogicStringArr_delAndSetNull	Dz1LogicStringArrA_delAndSetNull
#define								 Dz1LogicStringArr_dump				Dz1LogicStringArrA_dump
#define								 Dz1LogicStringArr_fdump			Dz1LogicStringArrA_fdump
#define								 Dz1LogicStringArr_build			Dz1LogicStringArrA_build
#endif // UNIX_SYSTEM
#endif