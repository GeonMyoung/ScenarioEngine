/* CP858 */

static int cp858_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
	unsigned char c = *s;
	if (c < 0x80)
		*pwc = (ucs4_t) c;
	else if (c == 0xd5)
		*pwc = 0x20ac;
	else
		*pwc = (ucs4_t) cp850_2uni[c-0x80];
	return 1;
}

static int cp858_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
	unsigned char c = 0;
	if (wc < 0x0080)
	{
		*r = wc;
		return 1;
	}
	else if (wc >= 0x00a0 && wc < 0x0100)
		c = cp850_page00[wc-0x00a0];
	else if (wc == 0x0192)
		c = 0x9f;
	else if (wc == 0x2017)
		c = 0xf2;
	else if (wc == 0x20ac)
		c = 0xd5;
	else if (wc >= 0x2500 && wc < 0x25a8)
		c = cp850_page25[wc-0x2500];
	if (c != 0)
	{
		*r = c;
		return 1;
	}
	return RET_ILUNI;
}
