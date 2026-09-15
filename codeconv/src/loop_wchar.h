/* This file defines three conversion loops:
     - from wchar_t to anything else,
     - from anything else to wchar_t,
     - from wchar_t to wchar_t.
 */

/*
#if HAVE_WCRTOMB || HAVE_MBRTOWC
# include <wchar.h>
# define BUF_SIZE 64  // assume MB_LEN_MAX <= 64
  // Some systems, like BeOS, have multibyte encodings but lack mbstate_t.
  extern size_t mbrtowc ();
# ifdef mbstate_t
#  define mbrtowc(pwc, s, n, ps) (mbrtowc)(pwc, s, n, 0)
#  define mbsinit(ps) 1
# endif
# ifndef mbsinit
#  if !HAVE_MBSINIT
#   define mbsinit(ps) 1
#  endif
# endif
#else
*/
# if !defined(mbstate_t) && !defined(MBSTATE_T_DEF)
   typedef int mbstate_t;
# endif
//#endif

/*
 * The first two conversion loops have an extended conversion descriptor.
 */
struct wchar_conv_struct {
  struct conv_struct parent;
  mbstate_t state;
};


/*
#if HAVE_WCRTOMB

// From wchar_t to anything else.

static size_t wchar_from_loop_convert (codeconv_t icd,
                                       const char* * inbuf, size_t *inbytesleft,
                                       char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t result = 0;
  while (*inbytesleft >= sizeof(wchar_t)) {
    const wchar_t * inptr = (const wchar_t *) *inbuf;
    size_t inleft = *inbytesleft;
    char buf[BUF_SIZE];
    mbstate_t state = wcd->state;
    size_t bufcount = 0;
    while (inleft >= sizeof(wchar_t)) {
      // Convert one wchar_t to multibyte representation.
      size_t count = wcrtomb(buf+bufcount,*inptr,&state);
      if (count == (size_t)(-1)) {
        // Invalid input.
        if (!wcd->parent.discard_ilseq) {
          errno = EILSEQ;
          return -1;
        }
        count = 0;
      }
      inptr++;
      inleft -= sizeof(wchar_t);
      bufcount += count;
      if (count == 0) {
        // Continue, append next wchar_t.
      } else {
        // Attempt to convert the accumulated multibyte representations
           to the target encoding.
        const char* bufptr = buf;
        size_t bufleft = bufcount;
        char* outptr = *outbuf;
        size_t outleft = *outbytesleft;
        size_t res = unicode_loop_convert(&wcd->parent,
                                          &bufptr,&bufleft,
                                          &outptr,&outleft);
        if (res == (size_t)(-1)) {
          if (errno == EILSEQ)
            // Invalid input.
            return -1;
          else if (errno == E2BIG)
            // Output buffer too small.
            return -1;
          else if (errno == EINVAL) {
            // Continue, append next wchar_t, but avoid buffer overrun.
            if (bufcount + MB_CUR_MAX > BUF_SIZE)
              abort();
          } else
            abort();
        } else {
          // Successful conversion.
          wcd->state = state;
          *inbuf = (const char *) inptr;
          *inbytesleft = inleft;
          *outbuf = outptr;
          *outbytesleft = outleft;
          result += res;
          break;
        }
      }
    }
  }
  return result;
}

static size_t wchar_from_loop_reset (codeconv_t icd,
                                     char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  if (outbuf == NULL || *outbuf == NULL) {
    // Reset the states.
    memset(&wcd->state,'\0',sizeof(mbstate_t));
    return unicode_loop_reset(&wcd->parent,NULL,NULL);
  } else {
    if (!mbsinit(&wcd->state)) {
      mbstate_t state = wcd->state;
      char buf[BUF_SIZE];
      size_t bufcount = wcrtomb(buf,(wchar_t)0,&state);
      if (bufcount == (size_t)(-1) || bufcount == 0 || buf[bufcount-1] != '\0')
        abort();
      else {
        const char* bufptr = buf;
        size_t bufleft = bufcount-1;
        char* outptr = *outbuf;
        size_t outleft = *outbytesleft;
        size_t res = unicode_loop_convert(&wcd->parent,
                                          &bufptr,&bufleft,
                                          &outptr,&outleft);
        if (res == (size_t)(-1)) {
          if (errno == E2BIG)
            return -1;
          else
            abort();
        } else {
          res = unicode_loop_reset(&wcd->parent,&outptr,&outleft);
          if (res == (size_t)(-1))
            return res;
          else {
            // Successful.
            wcd->state = state;
            *outbuf = outptr;
            *outbytesleft = outleft;
            return 0;
          }
        }
      }
    } else
      return unicode_loop_reset(&wcd->parent,outbuf,outbytesleft);
  }
}

#endif

#if HAVE_MBRTOWC

// From anything else to wchar_t. 

static size_t wchar_to_loop_convert (codeconv_t icd,
                                     const char* * inbuf, size_t *inbytesleft,
                                     char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t result = 0;
  while (*inbytesleft > 0) {
    size_t incount;
    for (incount = 1; incount <= *inbytesleft; incount++) {
      char buf[BUF_SIZE];
      const char* inptr = *inbuf;
      size_t inleft = incount;
      char* bufptr = buf;
      size_t bufleft = BUF_SIZE;
      size_t res = unicode_loop_convert(&wcd->parent,
                                        &inptr,&inleft,
                                        &bufptr,&bufleft);
      if (res == (size_t)(-1)) {
        if (errno == EILSEQ)
          // Invalid input.
          return -1;
        else if (errno == EINVAL) {
          // Incomplete input. Next try with one more input byte.
        } else
          // E2BIG shouldn't occur.
          abort();
      } else {
        // Successful conversion.
        size_t bufcount = bufptr-buf; // = BUF_SIZE-bufleft
        mbstate_t state = wcd->state;
        wchar_t wc;
        res = mbrtowc(&wc,buf,bufcount,&state);
        if (res == (size_t)(-2)) {
          // Next try with one more input byte.
        } else {
          if (res == (size_t)(-1)) {
            // Invalid input.
            if (!wcd->parent.discard_ilseq)
              return -1;
          } else {
            if (*outbytesleft < sizeof(wchar_t)) {
              errno = E2BIG;
              return -1;
            }
            *(wchar_t*) *outbuf = wc;
            // Restoring the state is not needed because it is the initial
            // state anyway: For all known locale encodings, the multibyte
            // to wchar_t conversion doesn't have shift state, and we have
            // excluded partial accumulated characters.
            // wcd->state = state;
            *outbuf += sizeof(wchar_t);
            *outbytesleft -= sizeof(wchar_t);
          }
          *inbuf += incount;
          *inbytesleft -= incount;
          result += res;
          break;
        }
      }
    }
  }
  return result;
}

static size_t wchar_to_loop_reset (codeconv_t icd,
                                   char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t res = unicode_loop_reset(&wcd->parent,outbuf,outbytesleft);
  if (res == (size_t)(-1))
    return res;
  memset(&wcd->state,0,sizeof(mbstate_t));
  return 0;
}

#endif
*/

/* From wchar_t to wchar_t. */

static size_t wchar_id_loop_convert (codeconv_t icd,
                                     const char* * inbuf, size_t *inbytesleft,
                                     char* * outbuf, size_t *outbytesleft)
{
  const wchar_t* inptr = (const wchar_t*) *inbuf;
  size_t inleft = *inbytesleft / sizeof(wchar_t);
  wchar_t* outptr = (wchar_t*) *outbuf;
  size_t outleft = *outbytesleft / sizeof(wchar_t);
  size_t count = (inleft <= outleft ? inleft : outleft);
  if (count > 0) {
    *inbytesleft -= count * sizeof(wchar_t);
    *outbytesleft -= count * sizeof(wchar_t);
    do
      *outptr++ = *inptr++;
    while (--count > 0);
    *inbuf = (const char*) inptr;
    *outbuf = (char*) outptr;
  }
  return 0;
}

#if 0
static size_t wchar_id_loop_reset (codeconv_t icd,
                                   char* * outbuf, size_t *outbytesleft)
{
	return 0;
}
#endif
