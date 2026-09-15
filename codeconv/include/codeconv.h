#ifndef CODECONV_H
#define CODECONV_H

typedef void *codeconv_t;

/* Get size_t declaration. */
#include <stddef.h>
#include <errno.h>

/* Some systems, like SunOS 4, don't have EILSEQ. Some systems, like BSD/OS,
   have EILSEQ in a different header.  On these systems, define EILSEQ
   ourselves. */
#ifndef EILSEQ
#define EILSEQ 
#endif

#define WINDOWS_UNICODE					"UCS-2LE"

#ifdef __cplusplus
#define ASMLINK		extern "C"
#else
#define ASMLINK
#endif

/* Allocates descriptor for code conversion from encoding `fromcode' to encoding `tocode'. */
ASMLINK codeconv_t codeconv_open(const char* tocode, const char* fromcode);

/* Converts, using conversion descriptor `cd', at most `*inbytesleft' bytes
   starting at `*inbuf', writing at most `*outbytesleft' bytes starting at `*outbuf'.
   Decrements `*inbytesleft' and increments `*inbuf' by the same amount.
   Decrements `*outbytesleft' and increments `*outbuf' by the same amount. */
ASMLINK size_t codeconv(codeconv_t cd,  char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft);

/* Frees resources allocated for conversion descriptor `cd'. */
ASMLINK int codeconv_close (codeconv_t cd);

/* Nonstandard extensions. */
/* Control of attributes. */
ASMLINK int codeconv_ctl(codeconv_t cd, int request, void *argument);

/* Requests for iconvctl. */
#define ICONV_TRIVIALP            0  /* int *argument */
#define ICONV_GET_TRANSLITERATE   1  /* int *argument */
#define ICONV_SET_TRANSLITERATE   2  /* const int *argument */
#define ICONV_GET_DISCARD_ILSEQ   3  /* int *argument */
#define ICONV_SET_DISCARD_ILSEQ   4  /* const int *argument */

/* Listing of locale independent encodings. */
ASMLINK void codeconv_list(int (*do_one)(unsigned int namescount, const char * const * names, void* data),
						void* data);
#endif /* CODECONV_H */
