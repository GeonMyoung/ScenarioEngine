#ifndef DZ1_STR_H
#define DZ1_STR_H

#include <dz1_error.h>
#include <dz1_io_stream.h>

DZ1_CPPLINK DZ1_DLLPORT str_t Dz1STRSTRSA(str_t src, str_t tgts[], str_t *ret_choosen);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t Dz1STRSTRSW(wstr_t src, wstr_t tgts[], wstr_t *ret_choosen);
#endif
///////////////////////////////////////////////////////////////////////////////
// Standard String API normalizer
#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////
// Windows System
#ifdef	UNICODE
///////////////////////////////
// UNICODE char-set
#define Dz1STRCAT					wcscat
#define Dz1STRCMP					wcscmp
#define Dz1STRNCMP					wcsncmp
#define Dz1STRLEN					wcslen
#define Dz1STRCPY					wcscpy
#define Dz1STRNCPY					wcsncpy
#define Dz1STRCHR					wcschr
#define Dz1STRRCHR					wcsrchr
#define Dz1STRSTR					wcswcs
#define Dz1SSCANF					swscanf

#define Dz1SPRINTF					_std_sprintfW
#define Dz1SNPRINTF					_std_snprintfW
#define Dz1ISSPACE					iswspace
#define Dz1ISALPHA					iswalpha
#define Dz1ISALNUM					iswalnum
#define Dz1ISDIGIT					iswdigit

#define Dz1STRSTRS					Dz1STRSTRSW
// UNICODE char-set
///////////////////////////////
#else //UNICODE
///////////////////////////////
// MBCS char-set
#define Dz1STRCAT					strcat
#define Dz1STRCMP					strcmp
#define Dz1STRNCMP					strncmp
#define Dz1STRLEN					strlen
#define Dz1STRCPY					strcpy
#define Dz1STRNCPY					strncpy
#define Dz1STRCHR					strchr
#define Dz1STRRCHR					strrchr
#define Dz1STRSTR					strstr
#define Dz1SSCANF					sscanf

#define Dz1SPRINTF					_std_sprintfA
#define Dz1SNPRINTF					_std_snprintfA
#define Dz1ISSPACE					isspace
#define Dz1ISALPHA					isalpha
#define Dz1ISALNUM					isalnum
#define Dz1ISDIGIT					isdigit

#define Dz1STRSTRS					Dz1STRSTRSA
// MBCS char-set
///////////////////////////////
#endif//UNICODE
// Windows System
////////////////////////////////////////////////////
#else //UNIX_SYSTEM
////////////////////////////////////////////////////
// Unix_system
#define Dz1STRCAT					strcat
#define Dz1STRCMP					strcmp
#define Dz1STRNCMP					strncmp
#define Dz1STRLEN					strlen
#define Dz1STRCPY					strcpy
#define Dz1STRNCPY					strncpy
#define Dz1STRCHR					strchr
#define Dz1STRRCHR					strrchr
#define Dz1STRSTR					strstr
#define Dz1SSCANF					sscanf

#define Dz1Text(astr)				astr
#define Dz1SPRINTF					sprintf
#define Dz1SNPRINTF					_std_snprintfA
#define Dz1ISSPACE					isspace
#define Dz1ISALPHA					isalpha
#define Dz1ISALNUM					isalnum
#define Dz1ISDIGIT					isdigit

#define Dz1STRSTRS					Dz1STRSTRSA
// Unix_system
////////////////////////////////////////////////////
#endif//UNIX_SYSTEM
// Standard String API normalizer
///////////////////////////////////////////////////////////////////////////////

#define Dz1Str_isVoid(str)			((str == NULL || str[0] == 0) ? TRUE : FALSE)

DZ1_CPPLINK DZ1_DLLPORT str_t	 dz1_built_in_str_clone(str_t p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_str_del(str_t p);
static __inline__ void			 dz1_built_in_str_delAndSetNull(void *pptr)
{
	str_t *pp = (str_t *)pptr;
	if (pp != NULL)
	{
		dz1_built_in_str_del(*pp);
		*pp = NULL;
	}
}
DZ1_CPPLINK DZ1_DLLPORT int		 dz1_built_in_str_cmp(str_t a, str_t b);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strA_predump(str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strA_dump(str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strA_prefdump(FILE *fp, str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strA_fdump(FILE *fp, str_t p, int tab);

#ifndef UNIX_SYSTEM	// 20250618 gm
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 dz1_built_in_wstr_clone(wstr_t p, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstr_del(wstr_t p);
static __inline__ void			 dz1_built_in_wstr_delAndSetNull(void *pptr)
{
	wstr_t *pp = (wstr_t *)pptr;
	if (pp != NULL)
	{
		dz1_built_in_wstr_del(*pp);
		*pp = NULL;
	}
}
DZ1_CPPLINK DZ1_DLLPORT int		 dz1_built_in_wstr_cmp(wstr_t a, wstr_t b);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrA_predump(wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrA_dump(wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrA_prefdump(FILE *fp, wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrA_fdump(FILE *fp, wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strW_predump(str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strW_dump(str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strW_prefdump(FILE *fp, str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_strW_fdump(FILE *fp, str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrW_predump(wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrW_dump(wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrW_prefdump(FILE *fp, wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void	 dz1_built_in_wstrW_fdump(FILE *fp, wstr_t p, int tab);
#ifdef UNICODE
#define							 dz1_built_in_str_predump		dz1_built_in_strW_predump
#define							 dz1_built_in_str_dump			dz1_built_in_strW_dump
#define							 dz1_built_in_str_prefdump		dz1_built_in_strW_prefdump
#define							 dz1_built_in_str_fdump			dz1_built_in_strW_fdump
#define							 dz1_built_in_wstr_predump		dz1_built_in_wstrW_predump
#define							 dz1_built_in_wstr_dump			dz1_built_in_wstrW_dump
#define							 dz1_built_in_wstr_prefdump		dz1_built_in_wstrW_prefdump
#define							 dz1_built_in_wstr_fdump		dz1_built_in_wstrW_fdump
#define							 str_t_dump						dz1_built_in_strW_dump
#define							 str_t_fdump					dz1_built_in_strW_fdump
#define							 wstr_t_dump					dz1_built_in_wstrW_dump
#define							 wstr_t_fdump					dz1_built_in_wstrW_fdump
#else	// !UNICODE
#define							 dz1_built_in_str_predump		dz1_built_in_strA_predump
#define							 dz1_built_in_str_dump			dz1_built_in_strA_dump
#define							 dz1_built_in_str_prefdump		dz1_built_in_strA_prefdump
#define							 dz1_built_in_str_fdump			dz1_built_in_strA_fdump
#define							 dz1_built_in_wstr_predump		dz1_built_in_wstrA_predump
#define							 dz1_built_in_wstr_dump			dz1_built_in_wstrA_dump
#define							 dz1_built_in_wstr_prefdump		dz1_built_in_wstrA_prefdump
#define							 dz1_built_in_wstr_fdump		dz1_built_in_wstrA_fdump
#define							 str_t_dump						dz1_built_in_strA_dump
#define							 str_t_fdump					dz1_built_in_strA_fdump
#define							 wstr_t_dump					dz1_built_in_wstrA_dump
#define							 wstr_t_fdump					dz1_built_in_wstrA_fdump
#endif	// UNICODE
#else // !UNIS_SYSTEM
#define							 dz1_built_in_str_predump		dz1_built_in_strA_predump
#define							 dz1_built_in_str_dump			dz1_built_in_strA_dump
#define							 dz1_built_in_str_prefdump		dz1_built_in_strA_prefdump
#define							 dz1_built_in_str_fdump			dz1_built_in_strA_fdump
#define							 dz1_built_in_wstr_predump		dz1_built_in_wstrA_predump
#define							 dz1_built_in_wstr_dump			dz1_built_in_wstrA_dump
#define							 dz1_built_in_wstr_prefdump		dz1_built_in_wstrA_prefdump
#define							 dz1_built_in_wstr_fdump		dz1_built_in_wstrA_fdump
#define							 str_t_dump						dz1_built_in_strA_dump
#define							 str_t_fdump					dz1_built_in_strA_fdump
#define							 wstr_t_dump					dz1_built_in_wstrA_dump
#define							 wstr_t_fdump					dz1_built_in_wstrA_fdump
#endif // UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Dz1Letter
DZ1_CPPLINK DZ1_DLLPORT char	 Dz1LetterA_ucase(char c);
DZ1_CPPLINK DZ1_DLLPORT char	 Dz1LetterA_lcase(char c);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LetterA_dump(char *c, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wchar_t	 Dz1LetterW_ucase(wchar_t c);
DZ1_CPPLINK DZ1_DLLPORT wchar_t	 Dz1LetterW_lcase(wchar_t c);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1LetterW_dump(wchar_t *c, int tab);
#ifdef UNICODE
#define							 Dz1Letter_ucase				Dz1LetterW_ucase
#define							 Dz1Letter_lcase				Dz1LetterW_lcase
#else	// !UNICODE
#define							 Dz1Letter_ucase				Dz1LetterA_ucase
#define							 Dz1Letter_lcase				Dz1LetterA_lcase
#endif	// UNICODE
#else	// !UNIX_SYSTEM
#define							 Dz1Letter_ucase				Dz1LetterA_ucase
#define							 Dz1Letter_lcase				Dz1LetterA_lcase
#endif	// UNIX_SYSTEM
// Dz1Letter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str
/*
 * Dz1Str_dup : Duplicate a string(clone)
 *
 * @src : source string
 * @err : Address of Dz1Error structure
 *
 * return : Address of Duplicated String
 */
#define Dz1StrA_clone					 Dz1StrA_dup
#define Dz1StrA_dup(src, errp)			_Dz1StrA_dup((src), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT str_t			_Dz1StrA_dup(char const * const src, Dz1Error *err, const char *__file__, int __line__);
#define Dz1StrA_ndup(src, len, errp)	_Dz1StrA_ndup((src), (len), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT str_t			_Dz1StrA_ndup(char const * const src, size_t len, Dz1Error *err, const char *__file__, int __line__);
#ifndef UNIX_SYSTEM
#define Dz1StrW_clone					 Dz1StrW_dup
#define	Dz1StrW_dup(src, errp)			_Dz1StrW_dup((src), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT wstr_t			_Dz1StrW_dup(wchar_t const * const src, Dz1Error *err, const char *__file__, int __line__);
#define Dz1StrW_ndup(src, len, errp)	_Dz1StrW_ndup((src), (len), (errp), __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT wstr_t			_Dz1StrW_ndup(wchar_t const * const src, size_t len, Dz1Error *err, const char *__file__, int __line__);
#endif

/*
 * Dz1Str_del : Delete String
 *
 * @p : target string
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StrA_del(str_t p);
static __inline__ void					 Dz1StrA_delAndSetNull(void *ptr)
{
	str_t *p = (str_t *)ptr;
	Dz1StrA_del(*p); *p = NULL;
}
#ifndef UNIX_SYSTEM
static __inline__ void					 Dz1StrW_del(wstr_t p) { Dz1StrA_del((str_t)p); }
static __inline__ void					 Dz1StrW_delAndSetNull(void *pp) { Dz1StrA_delAndSetNull(pp); }
#endif

/*
 * Dz1Str_dump/Dz1Str_fdump : Print String
 *
 * @con : target console
 * @p : string
 * @tab : indent level
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StrA_dump(str_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StrA_fdump(FILE *fp, str_t p, int tab);
// #define str_t_dump						 Dz1StrA_dump
// #define	str_t_fdump						 Dz1StrA_fdump

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StrW_dump(wstr_t p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1StrW_fdump(FILE *fp, wstr_t p, int tab);
// #define wstr_t_dump						 Dz1StrW_dump
// #define	wstr_t_fdump					 Dz1StrW_fdump
#endif

DZ1_CPPLINK DZ1_DLLPORT int				 Dz1StrA_cmp(str_t a, str_t b);
DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1StrA_replace(str_t src, str_t target, str_t alter, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1StrA_replaceChr(str_t dst, char src, char rpl);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int				 Dz1StrW_cmp(wstr_t a, wstr_t b);
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1StrW_replace(wstr_t src, wstr_t target, wstr_t alter, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1StrW_replaceChr(wstr_t dst, wchar_t src, wchar_t rpl);
#endif // UNIX_SYSTEM

#ifndef UNIX_SYSTEM
#ifdef UNICODE
#define									 Dz1Str_len						wcslen
#define									 Dz1Str_dup						Dz1StrW_dup
#define									 Dz1Str_ndup					Dz1StrW_ndup
#define									 Dz1Str_clone					Dz1StrW_clone
#define									 Dz1Str_del						Dz1StrW_del
#define									 Dz1Str_delAndSetNull			Dz1StrW_delAndSetNull
#define									 Dz1Str_cmp						Dz1StrW_cmp
#define									 Dz1Str_dump					Dz1StrW_dump
#define									 Dz1Str_fdump					Dz1StrW_fdump
#define									 Dz1Str_replace					Dz1StrW_replace
#define									 Dz1Str_replaceChr				Dz1StrW_replaceChr
#else // UNICODE
#define									 Dz1Str_len						strlen
#define									 Dz1Str_dup						Dz1StrA_dup
#define									 Dz1Str_ndup					Dz1StrA_ndup
#define									 Dz1Str_clone					Dz1StrA_clone
#define									 Dz1Str_del						Dz1StrA_del
#define									 Dz1Str_delAndSetNull			Dz1StrA_delAndSetNull
#define									 Dz1Str_cmp						Dz1StrA_cmp
#define									 Dz1Str_dump					Dz1StrA_dump
#define									 Dz1Str_fdump					Dz1StrA_fdump
#define									 Dz1Str_replace					Dz1StrA_replace
#define									 Dz1Str_replaceChr				Dz1StrA_replaceChr
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1Str_len						strlen
#define									 Dz1Str_dup						Dz1StrA_dup
#define									 Dz1Str_ndup					Dz1StrA_ndup
#define									 Dz1Str_clone					Dz1StrA_clone
#define									 Dz1Str_del						Dz1StrA_del
#define									 Dz1Str_delAndSetNull			Dz1StrA_delAndSetNull
#define									 Dz1Str_cmp						Dz1StrA_cmp
#define									 Dz1Str_dump					Dz1StrA_dump
#define									 Dz1Str_fdump					Dz1StrA_fdump
#define									 Dz1Str_replace					Dz1StrA_replace
#define									 Dz1Str_replaceChr				Dz1StrA_replaceChr
#endif	// UNIX_SYSTEM
// Dz1Str
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str : Case convert
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1StrA_ucase(str_t p);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1StrA_lcase(str_t p);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1StrW_ucase(wstr_t p);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1StrW_lcase(wstr_t p);
#ifdef UNICODE
#define							 Dz1Str_ucase				Dz1StrW_ucase
#define							 Dz1Str_lcase				Dz1StrW_lcase
#else	// UNICODE
#define							 Dz1Str_ucase				Dz1StrA_ucase
#define							 Dz1Str_lcase				Dz1StrA_lcase
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define							 Dz1Str_ucase				Dz1StrA_ucase
#define							 Dz1Str_lcase				Dz1StrA_lcase
#endif	// UNIX_SYSTEM
// Dz1Str : Case convert
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str : Digits convert
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromU8(char *dst, size_t sz, u8_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromS8(char *dst, size_t sz, s8_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromU16(char *dst, size_t sz, u16_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromS16(char *dst, size_t sz, s16_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromU32(char *dst, size_t sz, u32_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromS32(char *dst, size_t sz, s32_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromU64(char *dst, size_t sz, u64_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrA_fromS64(char *dst, size_t sz, s64_t v);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromU8(wchar_t *dst, size_t sz, u8_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromS8(wchar_t *dst, size_t sz, s8_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromU16(wchar_t *dst, size_t sz, u16_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromS16(wchar_t *dst, size_t sz, s16_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromU32(wchar_t *dst, size_t sz, u32_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromS32(wchar_t *dst, size_t sz, s32_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromU64(wchar_t *dst, size_t sz, u64_t v);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1StrW_fromS64(wchar_t *dst, size_t sz, s64_t v);
#ifdef UNICODE
#define							 Dz1Letter_dump				Dz1LetterW_dump
#define							 Dz1Str_fromU8				Dz1StrW_fromU8
#define							 Dz1Str_fromS8				Dz1StrW_fromS8
#define							 Dz1Str_fromU16				Dz1StrW_fromU16
#define							 Dz1Str_fromS16				Dz1StrW_fromS16
#define							 Dz1Str_fromU32				Dz1StrW_fromU32
#define							 Dz1Str_fromS32				Dz1StrW_fromS32
#define							 Dz1Str_fromU64				Dz1StrW_fromU64
#define							 Dz1Str_fromS64				Dz1StrW_fromS64
#else
#define							 Dz1Letter_dump				Dz1LetterA_dump
#define							 Dz1Str_fromU8				Dz1StrA_fromU8
#define							 Dz1Str_fromS8				Dz1StrA_fromS8
#define							 Dz1Str_fromU16				Dz1StrA_fromU16
#define							 Dz1Str_fromS16				Dz1StrA_fromS16
#define							 Dz1Str_fromU32				Dz1StrA_fromU32
#define							 Dz1Str_fromS32				Dz1StrA_fromS32
#define							 Dz1Str_fromU64				Dz1StrA_fromU64
#define							 Dz1Str_fromS64				Dz1StrA_fromS64
#endif
#else
#define							 Dz1Letter_dump				Dz1LetterA_dump
#define							 Dz1Str_fromU8				Dz1StrA_fromU8
#define							 Dz1Str_fromS8				Dz1StrA_fromS8
#define							 Dz1Str_fromU16				Dz1StrA_fromU16
#define							 Dz1Str_fromS16				Dz1StrA_fromS16
#define							 Dz1Str_fromU32				Dz1StrA_fromU32
#define							 Dz1Str_fromS32				Dz1StrA_fromS32
#define							 Dz1Str_fromU64				Dz1StrA_fromU64
#define							 Dz1Str_fromS64				Dz1StrA_fromS64
#endif
// Dz1Str : Digits convert
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str : Digits convert as Byte with Unit(B, KB, GB, TB)
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrA_fromS64Digit(s64_t v, char *dst, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrA_fromU64Digit(s64_t v, char *dst, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrA_fromU64Bytes(u64_t v, char *dst, size_t sz, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1StrW_fromS64Digit(s64_t v, wchar_t *dst, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1StrW_fromU64Digit(s64_t v, wchar_t *dst, size_t sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT wstr_t	 Dz1StrW_fromU64Bytes(u64_t v, wchar_t *dst, size_t sz, Dz1Error *err);
#ifdef UNICODE
#define							 Dz1Str_fromS64Digit				Dz1StrW_fromS64Digit
#define							 Dz1Str_fromU64Digit				Dz1StrW_fromU64Digit
#define							 Dz1Str_fromU64Bytes				Dz1StrW_fromU64Bytes
#else // UNICODE
#define							 Dz1Str_fromS64Digit				Dz1StrA_fromS64Digit
#define							 Dz1Str_fromU64Digit				Dz1StrA_fromU64Digit
#define							 Dz1Str_fromU64Bytes				Dz1StrA_fromU64Bytes
#endif // UNICODE
#else // UNIX_SYSTEM
#define							 Dz1Str_fromS64Digit				Dz1StrA_fromS64Digit
#define							 Dz1Str_fromU64Digit				Dz1StrA_fromU64Digit
#define							 Dz1Str_fromU64Bytes				Dz1StrA_fromU64Bytes
#endif // UNIX_SYSTEM
// Dz1Str : Digits convert as Byte with Unit(B, KB, GB, TB)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str : Numeric Value export
/*
 * Dz1Ato32 : Convert String to 32bit variable
 * Dz1Ato64 : Convert String to 64bit variable
 *
 * @str : source string
 *
 * NOTE : str is start with "0x" then perform hexadecimal conversion
 *        str is start with "0b" then perform binary-decimal conversion
 *        str is start with "0o" then perform octal-decimal conversion
 *        str is start with "-" then perform decimal conversion and set sign to minus
 *        else perform normal decimal conversion
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1StrA_isDigitStr(str_t cp);
DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1StrA_isIntegerStr(str_t cp);

DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1Ato32(str_t str);
DZ1_CPPLINK DZ1_DLLPORT u64_t			 Dz1Ato64(str_t str);

DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1AHexto32(str_t str);
DZ1_CPPLINK DZ1_DLLPORT u64_t			 Dz1AHexto64(str_t str);

#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1StrW_isDigitStr(wstr_t cp);
DZ1_CPPLINK DZ1_DLLPORT bool_t			 Dz1StrW_isIntegerStr(wstr_t cp);

DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1Wto32(wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT u64_t			 Dz1Wto64(wstr_t str);

DZ1_CPPLINK DZ1_DLLPORT u32_t			 Dz1WHexto32(wstr_t str);
DZ1_CPPLINK DZ1_DLLPORT u64_t			 Dz1WHexto64(wstr_t str);
#ifdef	UNICODE
#define Dz1StrTo32						 Dz1Wto32
#define Dz1StrTo64						 Dz1Wto64
#define Dz1HexTo32						 Dz1WHexto32
#define Dz1HexTo64						 Dz1WHexto64
#define Dz1Str_isDigitStr				 Dz1StrW_isDigitStr
#define Dz1Str_isIntegerStr				 Dz1StrW_isIntegerStr
#else //UNICODE
#define Dz1StrTo32						 Dz1Ato32
#define Dz1StrTo64						 Dz1Ato64
#define Dz1HexTo32						 Dz1AHexto32
#define Dz1HexTo64						 Dz1AHexto64
#define Dz1Str_isDigitStr				 Dz1StrA_isDigitStr
#define Dz1str_isIntegerStr				 Dz1StrA_isIntegerStr
#endif//UNICODE
#else //UNIX_SYSTEM
#define Dz1StrTo32						 Dz1Ato32
#define Dz1StrTo64						 Dz1Ato64
#define Dz1HexTo32						 Dz1AHexto32
#define Dz1HexTo64						 Dz1AHexto64
#define Dz1Str_isDigitStr				 Dz1StrA_isDigitStr
#define Dz1str_isIntegerStr				 Dz1StrA_isIntegerStr
#endif//UNIX_SYSTEM
// Dz1Str : Numeric Value export
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Str : Character-set convert
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1CodeConv(u8_t *dst, size_t dst_byte_size, const char *dst_charsetname,
													 u8_t *src, size_t src_byte_size, const char *src_charsetname);

DZ1_CPPLINK DZ1_DLLPORT void			*Dz1String_conv(void *src, size_t src_byte_size,
														const char *src_charsetname,
														const char *dst_charsetname, size_t *ret_byte_size);
// Dz1Str : Character-set convert
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Legacy CODEC Support : No null flag, Zero Length String support
// 0 ~ 255
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA8_enc(u8_t *dst, str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA8_dec(str_t *dst, u8_t *src, Dz1Error *err);
// 0 ~ 65535
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA16_enc(u8_t *dst, str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA16_dec(str_t *dst, u8_t *src, Dz1Error *err);
// 0 ~ 4294967295
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA_enc(u8_t *dst, str_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrA_dec(str_t *dst, u8_t *src, Dz1Error *err);

#ifndef UNIX_SYSTEM
// 0 ~ 255
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW8_enc(u8_t *dst, wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW8_dec(wstr_t *dst, u8_t *src, Dz1Error *err);
// 0 ~ 65535
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW16_enc(u8_t *dst, wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW16_dec(wstr_t *dst, u8_t *src, Dz1Error *err);
// 0 ~ 4294967295
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW_enc(u8_t *dst, wstr_t src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1StrW_dec(wstr_t *dst, u8_t *src, Dz1Error *err);
#ifdef	UNICODE
#define									 Dz1Str_enc						Dz1StrW_enc
#define									 Dz1Str_dec						Dz1StrW_dec
#define									 Dz1Str8_enc					Dz1StrW8_enc
#define									 Dz1Str8_dec					Dz1StrW8_dec
#define									 Dz1Str16_enc					Dz1StrW16_enc
#define									 Dz1Str16_dec					Dz1StrW16_dec
#else	//UNICODE
#define									 Dz1Str_enc						Dz1StrA_enc
#define									 Dz1Str_dec						Dz1StrA_dec
#define									 Dz1Str8_enc					Dz1StrA8_enc
#define									 Dz1Str8_dec					Dz1StrA8_dec
#define									 Dz1Str16_enc					Dz1StrA16_enc
#define									 Dz1Str16_dec					Dz1StrA16_dec
#endif	//UNICODE
#else	// UNIX_SYSTEM
#define									 Dz1Str_enc						Dz1StrA_enc
#define									 Dz1Str_dec						Dz1StrA_dec
#define									 Dz1Str8_enc					Dz1StrA8_enc
#define									 Dz1Str8_dec					Dz1StrA8_dec
#define									 Dz1Str16_enc					Dz1StrA16_enc
#define									 Dz1Str16_dec					Dz1StrA16_dec
#endif	// UNIX_SYSTEM
// Legacy CODEC Support : No null flag, Zero Length String support
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK DZ1_DLLPORT int		 Dz1StrCmpLogicalA(str_t a, str_t b);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrU8_toURI(str_t src_u8, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrU8_fromURI(str_t src_u8, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrA_toURI(str_t src, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1StrCmpLogicalW(wstr_t a, wstr_t b);
DZ1_CPPLINK DZ1_DLLPORT str_t	 Dz1StrW_toURI(wstr_t src, Dz1Error *err);
#ifdef UNICODE
#define							 Dz1StrCmpLogical			Dz1StrCmpLogicalW
#define							 Dz1Str_toURI				Dz1StrW_toURI
#else	// UNICODE
#define							 Dz1StrCmpLogical			Dz1StrCmpLogicalA
#define							 Dz1Str_toURI				Dz1StrA_toURI
#endif	// UNICODE
#else	// UNIX_SYSTEM
#define							 Dz1StrCmpLogical			Dz1StrCmpLogicalA
#define							 Dz1Str_toURI				Dz1StrU8_toURI
#endif	// UNIX_SYSTEM

#endif	// DZ1_STR_H
