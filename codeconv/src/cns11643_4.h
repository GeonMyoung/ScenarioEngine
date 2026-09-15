/* CNS 11643-1992 plane 4 */

/*
 * The table has been split into two parts. Each part's entries fit it 16 bits.
 * But the combined table would need 17 bits per entry.
 */
#include "cns11643_4a.h"
#include "cns11643_4b.h"

static int cns11643_4_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
	unsigned char c1 = s[0];
	if ((c1 >= 0x21 && c1 <= 0x6e))
	{
		if (n >= 2)
		{
			unsigned char c2 = s[1];
			if (c2 >= 0x21 && c2 < 0x7f)
			{
				unsigned int i = 94 * (c1 - 0x21) + (c2 - 0x21);
				ucs4_t wc = 0xfffd;
				unsigned short swc;
				{
					if (i < 2914)
						swc = cns11643_4a_2uni_page21[i],
						wc = cns11643_4a_2uni_upages[swc>>8] | (swc & 0xff);
					else if (i < 7298)
						swc = cns11643_4b_2uni_page40[i-2914],
						wc = cns11643_4b_2uni_upages[swc>>8] | (swc & 0xff);
				}
				if (wc != 0xfffd)
				{
					*pwc = wc;
					return 2;
				}
			}
			return RET_ILSEQ;
		}
		return RET_TOOFEW(0);
	}
	return RET_ILSEQ;
}
