
#include "ASN1_xmalloc.h"


ASNVoid* xmalloc(ASNUINT32 size)
{
    ASNVoid *ret;

    ret = malloc(size);
    if (ret != NULL) return ret;


    return 0; /*NOTREACHED*/
}

ASNVoid* xzmalloc(ASNUINT32 size)
{
    ASNVoid *ret;

    ret = malloc(size);
    if (ret != NULL) {
	memset(ret, 0, size);
	return ret;
    }


    return 0; /*NOTREACHED*/
}

ASNVoid *xrealloc (ASNVoid* ptr, ASNUINT32 size)
{
    ASNVoid *ret;

    /* xrealloc (NULL, size) behaves like xmalloc (size), as in ANSI C */
    ret = (!ptr ? malloc (size) : realloc (ptr, size));
    if (ret != NULL) return ret;


    return 0; /*NOTREACHED*/
}

ASNINT8 *xstrdup(const ASNINT8* str)
{
    ASNINT8 *p = xmalloc((ASNUINT32)strlen(str)+1);
    strcpy(p, str);
    return p;
}

ASNINT8 *xstrndup(const ASNINT8* str, ASNUINT32 len)
{
    ASNINT8 *p = xmalloc(len+1);
    strncpy(p, str, len);
    p[len] = '\0';
    return p;
}




