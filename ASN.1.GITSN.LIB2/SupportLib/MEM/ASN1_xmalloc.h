

#ifndef INCLUDED_XMALLOC_H
#define INCLUDED_XMALLOC_H


#include "../OS/ASN1_Sys.h"

ASN1_CPPLINK ASNVoid *xmalloc (ASNUINT32 size);
ASN1_CPPLINK ASNVoid *xzmalloc (ASNUINT32 size);
ASN1_CPPLINK ASNVoid *xrealloc (ASNVoid *ptr, ASNUINT32 size);
ASN1_CPPLINK ASNINT8 *xstrdup (const ASNINT8 *str);
ASN1_CPPLINK ASNINT8 *xstrndup (const ASNINT8 *str, ASNUINT32 len);



/* Functions using xmalloc.h must provide a function called fatal() conforming
   to the following: */
ASN1_CPPLINK ASNVoid fatal(const ASNINT8 *fatal_message, int fatal_code);
/*   __attribute__ ((noreturn));*/

#endif /* INCLUDED_XMALLOC_H */


