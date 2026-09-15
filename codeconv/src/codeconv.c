#include <stdlib.h>
#include <string.h>
#include <codeconv.h>

/*
 * Consider those system dependent encodings that are needed for the
 * current system.
 */
#define USE_AIX
#define USE_OSF1
#define USE_DOS
#define USE_EXTRA

/*
 * Data type for general conversion loop.
 */
struct loop_funcs {
	size_t (*loop_convert)( codeconv_t icd,
							const char* * inbuf, size_t *inbytesleft,
							char* * outbuf, size_t *outbytesleft);
	size_t (*loop_reset)(codeconv_t icd, char* * outbuf, size_t *outbytesleft);
};

/*
 * Converters.
 */
#include "converters.h"

/*
 * Transliteration tables.
 */
#include "cjk_variants.h"
#include "translit.h"

/*
 * Table of all supported encodings.
 */
struct encoding {
	struct mbtowc_funcs ifuncs; /* conversion multibyte -> unicode */
	struct wctomb_funcs ofuncs; /* conversion unicode -> multibyte */
	int oflags;                 /* flags for unicode -> multibyte conversion */
};

enum {
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  ei_##xxx ,
#include "encodings.def"
#ifdef USE_AIX
#include "encodings_aix.def"
#endif
#ifdef USE_OSF1
#include "encodings_osf1.def"
#endif
#ifdef USE_DOS
#include "encodings_dos.def"
#endif
#ifdef USE_EXTRA
#include "encodings_extra.def"
#endif
#include "encodings_local.def"
#undef DEFENCODING
ei_for_broken_compilers_that_dont_like_trailing_commas
};

#include "flags.h"

static struct encoding const all_encodings[] = {
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  { xxx_ifuncs1,xxx_ifuncs2, xxx_ofuncs1,xxx_ofuncs2, ei_##xxx##_oflags },
#include "encodings.def"
#ifdef USE_AIX
#include "encodings_aix.def"
#endif
#ifdef USE_OSF1
#include "encodings_osf1.def"
#endif
#ifdef USE_DOS
#include "encodings_dos.def"
#endif
#ifdef USE_EXTRA
#include "encodings_extra.def"
#endif
#undef DEFENCODING

#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  { xxx_ifuncs1,xxx_ifuncs2, xxx_ofuncs1,xxx_ofuncs2, 0 },
#include "encodings_local.def"
#undef DEFENCODING
};

/*
 * Conversion loops.
 */
#include "loops.h"

/*
 * Alias lookup function.
 * Defines
 *   struct alias { int name; unsigned int encoding_index; };
 *   const struct alias * aliases_lookup (const char *str, unsigned int len);
 *   #define MAX_WORD_LENGTH ...
 */
#include "aliases.h"

/*
 * System dependent alias lookup function.
 * Defines
 *   const struct alias *aliases2_lookup(const char *str);
 */
struct stringpool2_t {
#define S(tag,name,encoding_index) char stringpool_##tag[sizeof(name)];
#include "aliases2.h"
#undef S
};

static const struct stringpool2_t stringpool2_contents = {
#define S(tag,name,encoding_index) name,
#include "aliases2.h"
#undef S
};

#define stringpool2 ((const char *) &stringpool2_contents)
static const struct alias sysdep_aliases[] = {
#define S(tag,name,encoding_index) { (int)(long)&((struct stringpool2_t *)0)->stringpool_##tag, encoding_index },
#include "aliases2.h"
#undef S
};

static const struct alias *aliases2_lookup(register const char *str)
{
	const struct alias * ptr;
	unsigned int count;
	for (ptr = sysdep_aliases, count = sizeof(sysdep_aliases)/sizeof(sysdep_aliases[0]); count > 0; ptr++, count--)
		if (!strcmp(str, stringpool2 + ptr->name))
			return ptr;
	return NULL;
}

static char strAscii[] = "ASCII";

codeconv_t codeconv_open (const char* tocode, const char* fromcode)
{
	struct conv_struct * cd;
	char buf[MAX_WORD_LENGTH+10+1];
	const char* cp;
	char* bp;
	const struct alias * ap;
	unsigned int count;
	unsigned int from_index;
	int from_wchar;
	unsigned int to_index;
	int to_wchar;
	int transliterate = 0;
	int discard_ilseq = 0;

	/* Before calling aliases_lookup, convert the input string to upper case,
	* and check whether it's entirely ASCII (we call gperf with option "-7"
	* to achieve a smaller table) and non-empty. If it's not entirely ASCII,
	* or if it's too long, it is not a valid encoding name.
	*/
	for (to_wchar = 0;;)
	{
		/* Search tocode in the table. */
		for (cp = tocode, bp = buf, count = MAX_WORD_LENGTH+10+1; ; cp++, bp++)
		{
			unsigned char c = * (unsigned char *) cp;
			if (c >= 0x80) goto invalid;
			if (c >= 'a' && c <= 'z') c -= 'a'-'A';
			*bp = c;
			if (c == '\0') break;
			if (--count == 0) goto invalid;
		}
		if (bp-buf >= 10 && memcmp(bp-10,"//TRANSLIT",10)==0)
		{
			bp -= 10;
			*bp = '\0';
			transliterate = 1;
		}
		if (bp-buf >= 8 && memcmp(bp-8,"//IGNORE",8)==0)
		{
			bp -= 8;
			*bp = '\0';
			discard_ilseq = 1;
		}
		if (buf[0] == '\0')
		{
			tocode = strAscii;
			continue;
		}
		ap = aliases_lookup(buf,bp-buf);
		if (ap == NULL)
		{
			ap = aliases2_lookup(buf);
			if (ap == NULL) goto invalid;
		}
		if (ap->encoding_index == ei_local_char)
		{
			tocode = strAscii;
			continue;
		}
		if (ap->encoding_index == ei_local_wchar_t)
		{
#if __STDC_ISO_10646__
			if (sizeof(wchar_t) == 4)
			{
				to_index = ei_ucs4internal;
				break;
			}
			if (sizeof(wchar_t) == 2)
			{
				to_index = ei_ucs2internal;
				break;
			}
			if (sizeof(wchar_t) == 1)
			{
				to_index = ei_iso8859_1;
				break;
			}
#endif
			goto invalid;
		}
		to_index = ap->encoding_index;
		break;
	}
	for (from_wchar = 0;;)
	{
		/* Search fromcode in the table. */
		for (cp = fromcode, bp = buf, count = MAX_WORD_LENGTH+10+1; ; cp++, bp++)
		{
			unsigned char c = * (unsigned char *) cp;
			if (c >= 0x80) goto invalid;
			if (c >= 'a' && c <= 'z') c -= 'a'-'A';
			*bp = c;
			if (c == '\0') break;
			if (--count == 0) goto invalid;
		}

		if (bp-buf >= 10 && memcmp(bp-10,"//TRANSLIT",10)==0)
		{
			bp -= 10;
			*bp = '\0';
		}
		if (bp-buf >= 8 && memcmp(bp-8,"//IGNORE",8)==0)
		{
			bp -= 8;
			*bp = '\0';
		}
		if (buf[0] == '\0')
		{
			fromcode = strAscii;
			continue;
		}
		ap = aliases_lookup(buf,bp-buf);
		if (ap == NULL)
		{
			ap = aliases2_lookup(buf);
			if (ap == NULL) goto invalid;
		}
		if (ap->encoding_index == ei_local_char)
		{
			fromcode = strAscii;
			continue;
		}
		if (ap->encoding_index == ei_local_wchar_t)
		{
#if __STDC_ISO_10646__
			if (sizeof(wchar_t) == 4)
			{
				from_index = ei_ucs4internal;
				break;
			}
			if (sizeof(wchar_t) == 2)
			{
				from_index = ei_ucs2internal;
				break;
			}
			if (sizeof(wchar_t) == 1)
			{
				from_index = ei_iso8859_1;
				break;
			}
#endif
			goto invalid;
		}
		from_index = ap->encoding_index;
		break;
	}
	cd = (struct conv_struct *) malloc(from_wchar != to_wchar ? sizeof(struct wchar_conv_struct) : sizeof(struct conv_struct));
	if (cd == NULL)
	{
		errno = ENOMEM;
		return (codeconv_t)(-1);
	}
	cd->iindex = from_index;
	cd->ifuncs = all_encodings[from_index].ifuncs;
	cd->oindex = to_index;
	cd->ofuncs = all_encodings[to_index].ofuncs;
	cd->oflags = all_encodings[to_index].oflags;
	/* Initialize the loop functions. */
	cd->lfuncs.loop_convert = unicode_loop_convert;
	cd->lfuncs.loop_reset = unicode_loop_reset;
	/* Initialize the states. */
	memset(&cd->istate,'\0',sizeof(state_t));
	memset(&cd->ostate,'\0',sizeof(state_t));
	/* Initialize the operation flags. */
	cd->transliterate = transliterate;
	cd->discard_ilseq = discard_ilseq;
	/* Initialize additional fields. */
	if (from_wchar != to_wchar)
	{
		struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) cd;
		memset(&wcd->state,'\0',sizeof(mbstate_t));
	}
	/* Done. */
	return (codeconv_t)cd;

invalid:
	errno = EINVAL;
	return (codeconv_t)(-1);
}

size_t codeconv (codeconv_t icd,
              char **inbuf, size_t *inbytesleft,
              char **outbuf, size_t *outbytesleft)
{
	conv_t cd = (conv_t) icd;
	if (inbuf == NULL || *inbuf == NULL)
		return cd->lfuncs.loop_reset(icd,outbuf,outbytesleft);
	else
	{
		return cd->lfuncs.loop_convert(icd, (const char* *)inbuf,inbytesleft, outbuf,outbytesleft);
	}
}

int codeconv_close (codeconv_t icd)
{
	conv_t cd = (conv_t) icd;
	free(cd);
	return 0;
}

int codeconv_ctl (codeconv_t icd, int request, void* argument)
{
	conv_t cd = (conv_t) icd;
	switch (request)
	{
		case ICONV_TRIVIALP:
			*(int *)argument =
			((cd->lfuncs.loop_convert == unicode_loop_convert && cd->iindex == cd->oindex)
			|| cd->lfuncs.loop_convert == wchar_id_loop_convert ? 1 : 0);
			return 0;
		case ICONV_GET_TRANSLITERATE:
			*(int *)argument = cd->transliterate;
			return 0;
		case ICONV_SET_TRANSLITERATE:
			cd->transliterate = (*(const int *)argument ? 1 : 0);
			return 0;
		case ICONV_GET_DISCARD_ILSEQ:
			*(int *)argument = cd->discard_ilseq;
			return 0;
		case ICONV_SET_DISCARD_ILSEQ:
			cd->discard_ilseq = (*(const int *)argument ? 1 : 0);
			return 0;
		default:
			errno = EINVAL;
			return -1;
	}
}

/* An alias after its name has been converted from 'int' to 'const char*'. */
struct nalias
{
	const char* name;
	unsigned int encoding_index;
};

static int compare_by_index(const void * arg1, const void * arg2)
{
  const struct nalias * alias1 = (const struct nalias *) arg1;
  const struct nalias * alias2 = (const struct nalias *) arg2;
  return (int)alias1->encoding_index - (int)alias2->encoding_index;
}

static int compare_by_name(const void * arg1, const void * arg2)
{
	const char * name1 = *(const char **)arg1;
	const char * name2 = *(const char **)arg2;
	/* Compare alphabetically, but put "CS" names at the end. */
	int sign = strcmp(name1,name2);
	if (sign != 0)
		sign = ((name1[0]=='C' && name1[1]=='S') - (name2[0]=='C' && name2[1]=='S')) * 4 + (sign >= 0 ? 1 : -1);
	return sign;
}

void codeconv_list (int (*do_one) (unsigned int namescount,
                               const char * const * names,
                               void* data),
                void* data)
{
#define aliascount1  sizeof(aliases)/sizeof(aliases[0])
#define aliascount2  sizeof(sysdep_aliases)/sizeof(sysdep_aliases[0])
#define aliascount  (aliascount1+aliascount2)

	struct nalias aliasbuf[aliascount];
	const char *namesbuf[aliascount];
	size_t num_aliases;
	{
		/* Put all existing aliases into a buffer. */
		size_t i;
		size_t j;
		j = 0;
		for (i = 0; i < aliascount1; i++)
		{
			const struct alias * p = &aliases[i];
			if (p->name >= 0 && p->encoding_index != ei_local_char && p->encoding_index != ei_local_wchar_t)
			{
				aliasbuf[j].name = stringpool + p->name;
				aliasbuf[j].encoding_index = p->encoding_index;
				j++;
			}
		}
		for (i = 0; i < aliascount2; i++)
		{
			aliasbuf[j].name = stringpool2 + sysdep_aliases[i].name;
			aliasbuf[j].encoding_index = sysdep_aliases[i].encoding_index;
			j++;
		}
		num_aliases = j;
	}
	/* Sort by encoding_index. */
	if (num_aliases > 1)
		qsort(aliasbuf, num_aliases, sizeof(struct nalias), compare_by_index);
	{
		/* Process all aliases with the same encoding_index together. */
		size_t j;
		j = 0;
		while (j < num_aliases)
		{
			unsigned int ei = aliasbuf[j].encoding_index;
			size_t i = 0;
			do
				namesbuf[i++] = aliasbuf[j++].name;
			while (j < num_aliases && aliasbuf[j].encoding_index == ei);
			if (i > 1)
				qsort((void *)namesbuf, i, sizeof(const char *), compare_by_name);
			/* Call the callback. */
			if (do_one(i, namesbuf, data)) break;
		}
	}
#undef aliascount
#undef aliascount2
#undef aliascount1
}

