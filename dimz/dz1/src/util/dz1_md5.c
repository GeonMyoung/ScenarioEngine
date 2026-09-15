#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_md5.h>
#include <dz1_stdio.h>

typedef u8_t *byte_ptr_t;

static u8_t PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (u32_t)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (u32_t)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (u32_t)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (u32_t)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* MD5 initialization. Begins an MD5 operation, writing a new context. */
void Dz1MD5_init(Dz1MD5Ctx *context)
{
  context->count[0] = context->count[1] = 0;
  /* Load magic initialization constants.*/
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

static void _memset(byte_ptr_t output, int value, u32_t len)
{
	u32_t i;

	for (i = 0; i < len; i++)
		((char *)output)[i] = (char)value;
}

static void _memcpy(byte_ptr_t output, byte_ptr_t input, u32_t len)
{
	u32_t i;

	for (i = 0; i < len; i++)
		output[i] = input[i];
}

static void _enc(u8_t *output, u32_t *input, u32_t len)
{
	u32_t i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		pthread_testcancel();
		output[j] = (u8_t)(input[i] & 0xff);
		output[j+1] = (u8_t)((input[i] >> 8) & 0xff);
		output[j+2] = (u8_t)((input[i] >> 16) & 0xff);
		output[j+3] = (u8_t)((input[i] >> 24) & 0xff);
	}
}

static void _dec (u32_t *output, u8_t *input, u32_t len)
{
	u32_t i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
	{
		pthread_testcancel();
		output[i] = ((u32_t)input[j]) |
					(((u32_t)input[j+1]) << 8) |
					(((u32_t)input[j+2]) << 16) |
					(((u32_t)input[j+3]) << 24);
	}
}

static void _transform(u32_t state[4], u8_t block[64])
{
  u32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  _dec(x, block, 64);

  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

 /* Round 2 */
  GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  _memset((byte_ptr_t)x, 0, sizeof(x));
}

void Dz1MD5_update(Dz1MD5Ctx *context, u8_t *input, u32_t inputLen)
{
	u32_t i, index, partLen;

	/* Compute number of bytes mod 64 */
	index = (u32_t)((context->count[0] >> 3) & 0x3F);

	/* Update number of bits */
	if ((context->count[0] += ((u32_t)inputLen << 3)) < ((u32_t)inputLen << 3)) context->count[1]++;
	context->count[1] += ((u32_t)inputLen >> 29);

	partLen = 64 - index;

	/* Transform as many times as possible. */
	if (inputLen >= partLen)
	{
		_memcpy((byte_ptr_t)&context->buffer[index], (byte_ptr_t)input, partLen);
		_transform(context->state, context->buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
		{
			pthread_testcancel();
			_transform(context->state, &input[i]);
		}
		index = 0;
	}
	else i = 0;

	/* Buffer remaining input */
	_memcpy((byte_ptr_t)&context->buffer[index], (byte_ptr_t)&input[i], inputLen-i);
}

void Dz1MD5_final(Dz1MD5Data digest, Dz1MD5Ctx *context)
{
	u8_t bits[8];
	u32_t index, padLen;

	/* Save number of bits */
	_enc(bits, context->count, 8);

	/* Pad out to 56 mod 64. */
	index = (u32_t)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	Dz1MD5_update(context, PADDING, padLen);

	/* Append length (before padding) */
	Dz1MD5_update(context, bits, 8);

	/* Store state in digest */
	_enc(digest, context->state, 16);

	/* Zeroize sensitive information. */
	_memset((byte_ptr_t)context, 0, sizeof (*context));
}

void Dz1MD5_digest(Dz1MD5Data digest, u8_t *src, u32_t size)
{
	Dz1MD5Ctx ctx;
	Dz1MD5_init(&ctx);
	Dz1MD5_update(&ctx, src, size);
	Dz1MD5_final(digest, &ctx);
}

void Dz1MD5_digestFile0(Dz1MD5Data digest, FILE *fp)
{
	u8_t buf[4096];
	size_t sz = 0;
	Dz1MD5Ctx ctx;
	Dz1MD5_init(&ctx);

	while((sz = fread(buf, sizeof(u8_t), 4096, fp)) > 0)
		Dz1MD5_update(&ctx, buf, (u32_t)sz);
	
	Dz1MD5_final(digest, &ctx);
}

Dz1Error Dz1MD5A_digestFile(Dz1MD5Data digest, str_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = Dz1FileStreamA_open(fn, "r", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		Dz1MD5_digestFile0(digest, fp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1MD5W_digestFile(Dz1MD5Data digest, wstr_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = Dz1FileStreamW_open(fn, L"r", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		Dz1MD5_digestFile0(digest, fp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}
#endif

Dz1Error Dz1MD5A_digestFile2(Dz1MD5Data digest, str_t path, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = Dz1FileStreamA_open2(path, name, "r", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		Dz1MD5_digestFile0(digest, fp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1MD5W_digestFile2(Dz1MD5Data digest, wstr_t path, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = Dz1FileStreamW_open2(path, name, L"r", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		Dz1MD5_digestFile0(digest, fp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}
#endif
////////////////////////////////////////////////////////////////////////////////
// Dz1MD5Struct API
Dz1MD5Struct *Dz1MD5Struct_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MD5Struct *ret = (Dz1MD5Struct *)Dz1Calloc(sizeof(Dz1MD5Struct), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MD5Struct_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MD5Struct *Dz1MD5Struct_clone(Dz1MD5Struct *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MD5Struct *ret = (Dz1MD5Struct *)Dz1Calloc(sizeof(Dz1MD5Struct), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret->signature, src->signature, sizeof(Dz1MD5Data));
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1MD5Struct_del(Dz1MD5Struct *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1Free(p);
}

str_t Dz1MD5StructA_printable(Dz1MD5Struct *p, char buf[32 + 3 + 1])
{
	str_t ret = NULL;
	if (p != NULL)
	{
		u32_t i;
		char *cp = buf;
		for (i = 0; i < 16; i++)
		{
			sprintf(cp, "%02X", p->signature[i]);
			cp += 2;
			if (i != 15 && ((i + 1) & 3) == 0) *cp++ = ' ';
		}
		ret = buf;
	}
	return ret;
}

void Dz1MD5StructA_dump(Dz1MD5Struct *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		char buf[32+3+1];
		Dz1ThreadA_printf("%s\n", Dz1MD5StructA_printable(p, buf));
	}
}

void Dz1MD5StructA_fdump(FILE *fp, Dz1MD5Struct *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		char buf[32+3+1];
		Dz1ThreadA_fprintf(fp, "%s\n", Dz1MD5StructA_printable(p, buf));
	}
}
#ifndef UNIX_SYSTEM
wstr_t Dz1MD5StructW_printable(Dz1MD5Struct *p, wchar_t buf[32 + 3+ 1])
{
	wstr_t ret = NULL;
	if (p != NULL)
	{
		u32_t i;
		size_t sz = 36;
		wchar_t *cp = buf;
		for (i = 0; i < 16; i++)
		{
			swprintf(cp, sz, L"%02X", p->signature[i]);
			cp += 2; sz -= 2;
			if (i != 15 && ((i + 1) & 3) == 0) { *cp++ = L' '; sz--; }
		}
		ret = buf;
	}
	return ret;
}

void Dz1MD5StructW_dump(Dz1MD5Struct *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		wchar_t buf[32+3+1];
		Dz1ThreadW_printf(L"%s\n", Dz1MD5StructW_printable(p, buf));
	}
}

void Dz1MD5StructW_fdump(FILE *fp, Dz1MD5Struct *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		wchar_t buf[32+3+1];
		Dz1ThreadW_fprintf(fp, L"%s\n", Dz1MD5StructW_printable(p, buf));
	}
}
#endif

int Dz1MD5Struct_cmp(Dz1MD5Struct *a, Dz1MD5Struct *b)
{
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		return memcmp(a->signature, b->signature, 16);
	}
}

// Dz1MD5Struct API
////////////////////////////////////////////////////////////////////////////////

