#ifndef DZ1_REAL_H
#define DZ1_REAL_H

#include <dz1_error.h>

///////////////////////////////////////////////////////////////
// real64_t
#define							 Dz1Real64_clone(sp, ep)	_Dz1Real64_clone(sp, ep, __FILE__, __LINE__)
static __inline__ real64_t		*_Dz1Real64_clone(real64_t *src, Dz1Error *err, const char *__file__, int __line__) { return (real64_t *)_Dz1Memory_clone((void *)src, sizeof(real64_t), err, __file__, __line__); }
static __inline__ void			 Dz1Real64_del(real64_t *p) { if (p) Dz1Free(p); }
static __inline__ void			 Dz1Real64_delAndSetNull(void *ptr)
{
	real64_t **p = (real64_t **)ptr;
	Dz1Real64_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Real64_cmp(real64_t *a, real64_t *b);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real64A_dump(real64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real64A_fdump(FILE *fp, real64_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real64W_dump(real64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real64W_fdump(FILE *fp, real64_t *p, int tab);
#ifdef UNICODE
#define							 Dz1Real64_dump				Dz1Real64W_dump
#define							 Dz1Real64_fdump			Dz1Real64W_fdump
#else // UNICODE
#define							 Dz1Real64_dump				Dz1Real64A_dump
#define							 Dz1Real64_fdump			Dz1Real64A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Real64_dump				Dz1Real64A_dump
#define							 Dz1Real64_fdump			Dz1Real64A_fdump
#endif // UNIX_SYSTEM

// macro for type_t
#define							 real64_t_del				 Dz1Real64_del
#define							 real64_t_delAndSetNull		 Dz1Real64_delAndSetNull
#define							 real64_t_cmp				 Dz1Real64_cmp
#define							 real64_tA_dump				 Dz1Real64A_dump
#define							 real64_tA_fdump			 Dz1Real64A_fdump
#ifndef UNIX_SYSTEM
#define							 real64_tW_dump				 Dz1Real64W_dump
#define							 real64_tW_fdump			 Dz1Real64W_fdump
#ifdef UNICODE
#define							 real64_t_dump				 Dz1Real64W_dump
#define							 real64_t_fdump				 Dz1Real64W_fdump
#else // UNICODE
#define							 real64_t_dump				 Dz1Real64A_dump
#define							 real64_t_fdump				 Dz1Real64A_fdump
#endif
#else // UNIX_SYSTEM
#define							 real64_t_dump				 Dz1Real64A_dump
#define							 real64_t_fdump				 Dz1Real64A_fdump
#endif // UNIX_SYSTEM

// compatible with real_t
#define							 real_t_del					 Dz1Real64_del
#define							 real_t_delAndSetNull		 Dz1Real64_delAndSetNull
#define							 real_t_cmp					 Dz1Real64_cmp
#define							 real_tA_dump				 Dz1Real64A_dump
#define							 real_tA_fdump				 Dz1Real64A_fdump
#ifndef UNIX_SYSTEM
#define							 real_tW_dump				 Dz1Real64W_dump
#define							 real_tW_fdump				 Dz1Real64W_fdump
#ifdef UNICODE
#define							 real_t_dump				 Dz1Real64W_dump
#define							 real_t_fdump				 Dz1Real64W_fdump
#else // UNICODE
#define							 real_t_dump				 Dz1Real64A_dump
#define							 real_t_fdump				 Dz1Real64A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 real_t_dump				 Dz1Real64A_dump
#define							 real_t_fdump				 Dz1Real64A_fdump
#endif // UNIX_SYSTEM
// real64_t
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// real32_t
#define							 Dz1Real32_clone(sp, ep)	_Dz1Real32_clone(sp, ep, __FILE__, __LINE__)
static __inline__ real32_t		*_Dz1Real32_clone(real32_t *src, Dz1Error *err, const char *__file__, int __line__) { return (real32_t *)_Dz1Memory_clone((void *)src, sizeof(real32_t), err, __file__, __line__); }
static __inline__ void			 Dz1Real32_del(real32_t *p) { if (p) Dz1Free(p); }
static __inline__ void			 Dz1Real32_delAndSetNull(void *ptr)
{
	real32_t **p = (float **)ptr;
	Dz1Real32_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Real32_cmp(real32_t *a, real32_t *b);

DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real32A_dump(float *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real32A_fdump(FILE *fp, real32_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real32W_dump(float *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Real32W_fdump(FILE *fp, real32_t *p, int tab);
#ifdef UNICODE
#define							 Dz1Real32_dump				Dz1Real32W_dump
#define							 Dz1Real32_fdump			Dz1Real32W_fdump
#define							 real32_t_dump				Dz1Real32W_dump
#define							 real32_t_fdump				Dz1Real32W_fdump
#else // UNICODE
#define							 Dz1Real32_dump				Dz1Real32A_dump
#define							 Dz1Real32_fdump			Dz1Real32A_fdump
#define							 real32_t_dump				Dz1Real32A_dump
#define							 real32_t_fdump				Dz1Real32A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Real32_dump				Dz1Real32A_dump
#define							 Dz1Real32_fdump			Dz1Real32A_fdump
#define							 real32_t_dump				Dz1Real32A_dump
#define							 real32_t_fdump				Dz1Real32A_fdump
#endif // UNIX_SYSTEM
// macro for type_t
#define real32_t_del			 Dz1Real32_del
#define real32_t_delAndSetNull	 Dz1Real32_delAndSetNull
#define real32_t_cmp			 Dz1Real32_cmp
// real32_t
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// String Convention
DZ1_CPPLINK DZ1_DLLPORT real64_t Dz1Real64FromStrA(str_t src);
DZ1_CPPLINK DZ1_DLLPORT real32_t Dz1Real32FromStrA(str_t src);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT real32_t Dz1Real32FromStrW(wstr_t src);
DZ1_CPPLINK DZ1_DLLPORT real64_t Dz1Real64FromStrW(wstr_t src);
#endif

#ifdef	UNIX_SYSTEM
#define							 Dz1Real64FromStr			Dz1Real64FromStrA
#define							 Dz1Real32FromStr			Dz1Real32FromStrA
#define							 Dz1StrToF					atof
#else	// UNIX_SYSTEM
#ifdef UNICODE
#define							 Dz1Real64FromStr			Dz1Real64FromStrW
#define							 Dz1Real32FromStr			Dz1Real32FromStrW
#define							 Dz1StrToF					_wtof
#else	// UNICODE
#define							 Dz1Real64FromStr			Dz1Real64FromStrA
#define							 Dz1Real32FromStr			Dz1Real32FromStrA
#define							 Dz1StrToF					atof
#endif	// UNICODE
#endif	// UNIX_SYSTEM
// String Convention
///////////////////////////////////////////////////////////////

#endif
