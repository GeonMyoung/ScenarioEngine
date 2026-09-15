#ifndef DZ1_INT_H
#define DZ1_INT_H

#include <dz1_malloc.h>

///////////////////////////////////////////////////////////////////////////////
// u8_t
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT u8_t	*Dz1u8_new(u8_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT u8_t	*Dz1u8_clone(u8_t *p, Dz1Error *err);
static __inline__ void			 Dz1u8_del(u8_t *p) { if (!p) return; Dz1Free(p); }
static __inline__ void			 Dz1u8_delAndSetNull(void *ptr)
{
	u8_t **p = (u8_t **)ptr;
	Dz1u8_del(*p); *p = NULL;
}
#define							 u8_t_delAndSetNull		Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u8A_dump(u8_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u8A_fdump(FILE *fp, u8_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u8W_dump(u8_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u8W_fdump(FILE *fp, u8_t *p, int tab);
#ifdef UNICODE
#define							 Dz1u8_dump			Dz1u8W_dump
#define							 Dz1u8_fdump		Dz1u8W_fdump
#else // UNICODE
#define							 Dz1u8_dump			Dz1u8A_dump
#define							 Dz1u8_fdump		Dz1u8A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1u8_dump			Dz1u8A_dump
#define							 Dz1u8_fdump		Dz1u8A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1u8_cmp(u8_t *a, u8_t *b);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u8_enc(u8_t *dst, u8_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u8_dec(u8_t **dst, u8_t *src, Dz1Error *err);


///////////////////////////////////////////////////////////////////////////////
// u16_t
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT u16_t	*Dz1u16_new(u16_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT u16_t	*Dz1u16_clone(u16_t *p, Dz1Error *err);
static __inline__ void			 Dz1u16_del(u16_t *p) { Dz1u8_del((u8_t *)p); }
#define							 Dz1u16_delAndSetNull	Dz1u8_delAndSetNull
#define							 u16_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u16A_dump(u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u16A_fdump(FILE *fp, u16_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u16W_dump(u16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u16W_fdump(FILE *fp, u16_t *p, int tab);
#ifdef UNICODE
#define							 Dz1u16_dump		Dz1u16W_dump
#define							 Dz1u16_fdump		Dz1u16W_fdump
#else // UNICODE
#define							 Dz1u16_dump		Dz1u16A_dump
#define							 Dz1u16_fdump		Dz1u16A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1u16_dump		Dz1u16A_dump
#define							 Dz1u16_fdump		Dz1u16A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1u16_cmp(u16_t *a, u16_t *b);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u16_enc(u8_t *dst, u16_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u16_dec(u16_t **dst, u8_t *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// u32_t
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT u32_t	*Dz1u32_new(u32_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT u32_t	*Dz1u32_clone(u32_t *p, Dz1Error *err);
static __inline__ void			 Dz1u32_del(u32_t *p) { Dz1u8_del((u8_t *)p); }
#define							 Dz1u32_delAndSetNull	Dz1u8_delAndSetNull
#define							 u32_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u32A_dump(u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u32A_fdump(FILE *fp, u32_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u32W_dump(u32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u32W_fdump(FILE *fp, u32_t *p, int tab);
#ifdef UNICODE
#define							 Dz1u32_dump		Dz1u32W_dump
#define							 Dz1u32_fdump		Dz1u32W_fdump
#else // UNICODE
#define							 Dz1u32_dump		Dz1u32A_dump
#define							 Dz1u32_fdump		Dz1u32A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1u32_dump		Dz1u32A_dump
#define							 Dz1u32_fdump		Dz1u32A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1u32_cmp(u32_t *a, u32_t *b);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u32_enc(u8_t *dst, u32_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u32_dec(u32_t **dst, u8_t *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT u32_t	 Dz1u32_pow(u32_t v, u32_t p);

///////////////////////////////////////////////////////////////////////////////
// u64_t
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT u64_t	*Dz1u64_new(u64_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT u64_t	*Dz1u64_clone(u64_t *p, Dz1Error *err);
static __inline__ void			 Dz1u64_del(u64_t *p) { Dz1u8_del((u8_t *)p); }
#define							 Dz1u64_delAndSetNull	Dz1u8_delAndSetNull
#define							 u64_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u64A_dump(u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u64A_fdump(FILE *fp, u64_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u64W_dump(u64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1u64W_fdump(FILE *fp, u64_t *p, int tab);
#ifdef UNICODE
#define							 Dz1u64_dump		Dz1u64W_dump
#define							 Dz1u64_fdump		Dz1u64W_fdump
#else // UNICODE
#define							 Dz1u64_dump		Dz1u64A_dump
#define							 Dz1u64_fdump		Dz1u64A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1u64_dump		Dz1u64A_dump
#define							 Dz1u64_fdump		Dz1u64A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1u64_cmp(u64_t *a, u64_t *b);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u64_enc(u8_t *dst, u64_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1u64_dec(u64_t **dst, u8_t *src, Dz1Error *err);

DZ1_CPPLINK DZ1_DLLPORT u64_t	 Dz1u64_pow(u64_t v, u64_t p);

///////////////////////////////////////////////////////////////////////////////
// s8_t
///////////////////////////////////////////////////////////////////////////////
static __inline__ s8_t			*Dz1s8_new(s8_t val, Dz1Error *err) { return (s8_t *)Dz1u8_new((u8_t)val, err); }
static __inline__ s8_t			*Dz1s8_clone(s8_t *p, Dz1Error *err) { return (s8_t *)Dz1u8_clone((u8_t *)p, err); }
static __inline__ void			 Dz1s8_del(s8_t *p) { if (!p) return; Dz1Free(p); }
#define							 Dz1s8_delAndSetNull	Dz1u8_delAndSetNull
#define							 s8_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s8A_dump(s8_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s8A_fdump(FILE *fp, s8_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s8W_dump(s8_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s8W_fdump(FILE *fp, s8_t *p, int tab);
#ifdef UNICODE
#define							 Dz1s8_dump			Dz1s8W_dump
#define							 Dz1s8_fdump		Dz1s8W_fdump
#else // UNICODE
#define							 Dz1s8_dump			Dz1s8A_dump
#define							 Dz1s8_fdump		Dz1s8A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1s8_dump			Dz1s8A_dump
#define							 Dz1s8_fdump		Dz1s8A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1s8_cmp(s8_t *a, s8_t *b);
static __inline__ ssize_t		 Dz1s8_enc(u8_t *dst, s8_t *src, Dz1Error *err) { return Dz1u8_enc(dst, (u8_t *)src, err); }
static __inline__ ssize_t		 Dz1s8_dec(s8_t **dst, u8_t *src, Dz1Error *err) { return Dz1u8_dec((u8_t **)dst, src, err); }

///////////////////////////////////////////////////////////////////////////////
// s16_t
///////////////////////////////////////////////////////////////////////////////
static __inline__ s16_t			*Dz1s16_new(s16_t val, Dz1Error *err) { return (s16_t *)Dz1u16_new((u16_t)val, err); }
static __inline__ s16_t			*Dz1s16_clone(s16_t *p, Dz1Error *err) { return (s16_t *)Dz1u16_clone((u16_t *)p, err); }
static __inline__ void			 Dz1s16_del(s16_t *p) { Dz1s8_del((s8_t *)p); }
#define							 Dz1s16_delAndSetNull	Dz1s8_delAndSetNull
#define							 s16_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s16A_dump(s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s16A_fdump(FILE *fp, s16_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s16W_dump(s16_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s16W_fdump(FILE *fp, s16_t *p, int tab);
#ifdef UNICODE
#define							 Dz1s16_dump		Dz1s16W_dump
#define							 Dz1s16_fdump		Dz1s16W_fdump
#else // UNICODE
#define							 Dz1s16_dump		Dz1s16A_dump
#define							 Dz1s16_fdump		Dz1s16A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1s16_dump		Dz1s16A_dump
#define							 Dz1s16_fdump		Dz1s16A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1s16_cmp(s16_t *a, s16_t *b);
static __inline__ ssize_t		 Dz1s16_enc(u8_t *dst, s16_t *src, Dz1Error *err) { return Dz1u16_enc(dst, (u16_t *)src, err); }
static __inline__ ssize_t		 Dz1s16_dec(s16_t **dst, u8_t *src, Dz1Error *err) { return Dz1u16_dec((u16_t **)dst, src, err); }

///////////////////////////////////////////////////////////////////////////////
// s32_t
///////////////////////////////////////////////////////////////////////////////
static __inline__ s32_t			*Dz1s32_new(s32_t val, Dz1Error *err) { return (s32_t *)Dz1u32_new((u32_t)val, err); }
static __inline__ s32_t			*Dz1s32_clone(s32_t *p, Dz1Error *err) { return Dz1s32_new((*p), err); }
static __inline__ void			 Dz1s32_del(s32_t *p) { Dz1u8_del((u8_t *)p); }
#define							 Dz1s32_delAndSetNull	Dz1u8_delAndSetNull
#define							 s32_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s32A_dump(s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s32A_fdump(FILE *fp, s32_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s32W_dump(s32_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s32W_fdump(FILE *fp, s32_t *p, int tab);
#ifdef UNICODE
#define							 Dz1s32_dump		Dz1s32W_dump
#define							 Dz1s32_fdump		Dz1s32W_fdump
#else // UNICODE
#define							 Dz1s32_dump		Dz1s32A_dump
#define							 Dz1s32_fdump		Dz1s32A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1s32_dump		Dz1s32A_dump
#define							 Dz1s32_fdump		Dz1s32A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1s32_cmp(s32_t *a, s32_t *b);
static __inline__ ssize_t		 Dz1s32_enc(u8_t *dst, s32_t *src, Dz1Error *err) { return Dz1u32_enc(dst, (u32_t *)src, err); }
static __inline__ ssize_t		 Dz1s32_dec(s32_t **dst, u8_t *src, Dz1Error *err) { return Dz1u32_dec((u32_t **)dst, src, err); }

///////////////////////////////////////////////////////////////////////////////
// s64_t
///////////////////////////////////////////////////////////////////////////////
static __inline__ s64_t			*Dz1s64_new(s64_t val, Dz1Error *err) { return (s64_t *)Dz1u64_new((u64_t)val, err); }
static __inline__ s64_t			*Dz1s64_clone(s64_t *p, Dz1Error *err) { return (s64_t *)Dz1u64_clone((u64_t *)p, err); }
static __inline__ void			 Dz1s64_del(s64_t *p) { Dz1s8_del((s8_t *)p); }
#define							 Dz1s64_delAndSetNull	Dz1s8_delAndSetNull
#define							 s64_t_delAndSetNull	Dz1u8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s64A_dump(s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s64A_fdump(FILE *fp, s64_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s64W_dump(s64_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1s64W_fdump(FILE *fp, s64_t *p, int tab);
#ifdef UNICODE
#define							 Dz1s64_dump		Dz1s64W_dump
#define							 Dz1s64_fdump		Dz1s64W_fdump
#else // UNICODE
#define							 Dz1s64_dump		Dz1s64A_dump
#define							 Dz1s64_fdump		Dz1s64A_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1s64_dump		Dz1s64A_dump
#define							 Dz1s64_fdump		Dz1s64A_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1s64_cmp(s64_t *a, s64_t *b);
static __inline__ ssize_t		 Dz1s64_enc(u8_t *dst, s64_t *src, Dz1Error *err) { return Dz1u64_enc(dst, (u64_t *)src, err); }
static __inline__ ssize_t		 Dz1s64_dec(s64_t **dst, u8_t *src, Dz1Error *err) { return Dz1u64_dec((u64_t **)dst, src, err); }

///////////////////////////////////////////////////////////////////////////////
// long
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT long	*Dz1Long_new(long val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT long	*Dz1Long_clone(long *src, Dz1Error *err);
#define							 Dz1Long_del(ptr)		Dz1u8_del((u8_t *)ptr)
#define							 Dz1Long_delAndSetNull	Dz1s8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LongA_dump(long *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LongA_fdump(FILE *fp, long *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LongW_dump(long *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LongW_fdump(FILE *fp, long *p, int tab);
#ifdef UNICODE
#define							 Dz1Long_dump		Dz1LongW_dump
#define							 Dz1Long_fdump		Dz1LongW_fdump
#else // UNICODE
#define							 Dz1Long_dump		Dz1LongA_dump
#define							 Dz1Long_fdump		Dz1LongA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Long_dump		Dz1LongA_dump
#define							 Dz1Long_fdump		Dz1LongA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Long_enc(unsigned char *dst, long *src);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Long_dec(long **dst, unsigned char *src);

///////////////////////////////////////////////////////////////////////////////
// Bool Type API
///////////////////////////////////////////////////////////////////////////////
static __inline__ bool_t		*Dz1Bool_new(bool_t val, Dz1Error *err) { return Dz1s32_new((s32_t)val, err); }
static __inline__ bool_t		*Dz1Bool_clone(bool_t *src, Dz1Error *err) { return Dz1s32_new((s32_t)(*src), err); }
static __inline__ void			 Dz1Bool_del(bool_t *p) { Dz1u8_del((u8_t *)p); }
#define							 Dz1Bool_delAndSetNull	Dz1s8_delAndSetNull
#define							 bool_t_delAndSetNull	Dz1s8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1BoolA_dump(bool_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1BoolA_fdump(FILE *fp, bool_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1BoolW_dump(bool_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1BoolW_fdump(FILE *fp, bool_t *p, int tab);
#ifdef UNICODE
#define							 Dz1Bool_dump		Dz1BoolW_dump
#define							 Dz1Bool_fdump		Dz1BoolW_fdump
#else // UNICODE
#define							 Dz1Bool_dump		Dz1BoolA_dump
#define							 Dz1Bool_fdump		Dz1BoolA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Bool_dump		Dz1BoolA_dump
#define							 Dz1Bool_fdump		Dz1BoolA_fdump
#endif // UNIX_SYSTEM
static __inline__ int			 Dz1Bool_cmp(bool_t *a, bool_t *b) { return (*a && *b) || (!*a && !*b) ? 0 : *a ? -1 : 1; }
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Bool_enc(u8_t *dst, bool_t *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1Bool_dec(bool_t **dst, u8_t *src, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// size_t Type API
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT size_t	*size_t_new(size_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT size_t	*size_t_clone(size_t *src, Dz1Error *err);
static __inline__		void	 size_t_del(size_t *p) { Dz1u8_del((u8_t *)p); }
#define							 size_t_delAndSetNull	Dz1s8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 size_tA_dump(size_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 size_tA_fdump(FILE *fp, size_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 size_tW_dump(size_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 size_tW_fdump(FILE *fp, size_t *p, int tab);
#ifdef UNICODE
#define							 size_t_dump		size_tW_dump
#define							 size_t_fdump		size_tW_fdump
#else // UNICODE
#define							 size_t_dump		size_tA_dump
#define							 size_t_fdump		size_tA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 size_t_dump		size_tA_dump
#define							 size_t_fdump		size_tA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 size_t_cmp(size_t *a, size_t *b);

///////////////////////////////////////////////////////////////////////////////
// ssize_t Type API
///////////////////////////////////////////////////////////////////////////////
DZ1_CPPLINK DZ1_DLLPORT ssize_t	*ssize_t_new(ssize_t val, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	*ssize_t_clone(ssize_t *src, Dz1Error *err);
static __inline__		void	 ssize_t_del(ssize_t *p) { Dz1u8_del((u8_t *)p); }
#define							 ssize_t_delAndSetNull	Dz1s8_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void	 ssize_tA_dump(ssize_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 ssize_tA_fdump(FILE *fp, ssize_t *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 ssize_tW_dump(ssize_t *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 ssize_tW_fdump(FILE *fp, ssize_t *p, int tab);
#ifdef UNICODE
#define							 ssize_t_dump		ssize_tW_dump
#define							 ssize_t_fdump		ssize_tW_fdump
#else // UNICODE
#define							 ssize_t_dump		ssize_tA_dump
#define							 ssize_t_fdump		ssize_tA_fdump
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 ssize_t_dump		ssize_tA_dump
#define							 ssize_t_fdump		ssize_tA_fdump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 ssize_t_cmp(ssize_t *a, ssize_t *b);

#endif
