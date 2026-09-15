#include "dz1_crypt_sha1.h"

#define SHA1_calc(bits,word)  ((((word) << (bits)) & 0xFFFFFFFF) | ((word) >> (32-(bits))))

///////////////////////////////////////////////////////////////////////////////
// Dz1CryptSHA1_block
static void Dz1CryptSHA1_block(Dz1CryptSHA1Ctx *context)
{
	s32_t	t;
	u32_t	temp, W[80], A, B, C, D, E;
	const u32_t K[] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };	// Constants defined in SHA-1

	// Initialize the first 16 words in the array W
	for (t = 0; t < 16; t++)
	{
		W[t] = ((unsigned)context->data_block[t * 4]) << 24;
		W[t] |= ((unsigned)context->data_block[t * 4 + 1]) << 16;
		W[t] |= ((unsigned)context->data_block[t * 4 + 2]) << 8;
		W[t] |= ((unsigned)context->data_block[t * 4 + 3]);
	}

	for (t = 16; t < 80; t++)
		W[t] = SHA1_calc(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);

	A = context->digest[0];
	B = context->digest[1];
	C = context->digest[2];
	D = context->digest[3];
	E = context->digest[4];

	for (t = 0; t < 20; t++)
	{
		temp = SHA1_calc(5, A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = SHA1_calc(30, B);
		B = A;
		A = temp;
	}

	for (t = 20; t < 40; t++)
	{
		temp = SHA1_calc(5, A) + (B ^ C ^ D) + E + W[t] + K[1];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = SHA1_calc(30, B);
		B = A;
		A = temp;
	}

	for (t = 40; t < 60; t++)
	{
		temp = SHA1_calc(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = SHA1_calc(30, B);
		B = A;
		A = temp;
	}

	for (t = 60; t < 80; t++)
	{
		temp = SHA1_calc(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = SHA1_calc(30, B);
		B = A;
		A = temp;
	}

	context->digest[0] = (context->digest[0] + A) & 0xFFFFFFFF;
	context->digest[1] = (context->digest[1] + B) & 0xFFFFFFFF;
	context->digest[2] = (context->digest[2] + C) & 0xFFFFFFFF;
	context->digest[3] = (context->digest[3] + D) & 0xFFFFFFFF;
	context->digest[4] = (context->digest[4] + E) & 0xFFFFFFFF;
	context->data_block_idx = 0;
}
// Dz1CryptSHA1_block
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1CryptSHA1_padding
static void Dz1CryptSHA1_padding(Dz1CryptSHA1Ctx *context)
{
    /*
     *  Check to see if the current message block is too small to hold
     *  the initial padding bits and length.  If so, we will pad the
     *  block, process it, and then continue padding into a second
     *  block.
     */
    if (context->data_block_idx > 55)
    {
        context->data_block[context->data_block_idx++] = 0x80;
        while(context->data_block_idx < 64)
            context->data_block[context->data_block_idx++] = 0;

        Dz1CryptSHA1_block(context);

        while(context->data_block_idx < 56)
            context->data_block[context->data_block_idx++] = 0;
    }
    else
    {
        context->data_block[context->data_block_idx++] = 0x80;
        while(context->data_block_idx < 56)
            context->data_block[context->data_block_idx++] = 0;
    }

    /*
     *  Store the message length as the last 8 octets
     */
    context->data_block[56] = (context->bits_len_high >> 24) & 0xFF;
    context->data_block[57] = (context->bits_len_high >> 16) & 0xFF;
    context->data_block[58] = (context->bits_len_high >> 8) & 0xFF;
    context->data_block[59] = (context->bits_len_high) & 0xFF;
    context->data_block[60] = (context->bits_len_low >> 24) & 0xFF;
    context->data_block[61] = (context->bits_len_low >> 16) & 0xFF;
    context->data_block[62] = (context->bits_len_low >> 8) & 0xFF;
    context->data_block[63] = (context->bits_len_low) & 0xFF;

    Dz1CryptSHA1_block(context);
}
// Dz1CryptSHA1_padding
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1CryptSHA1_reset
void Dz1CryptSHA1_reset(Dz1CryptSHA1Ctx *context)
{
    context->bits_len_low             = 0;
    context->bits_len_high            = 0;
    context->data_block_idx    = 0;

    context->digest[0]      = 0x67452301;
    context->digest[1]      = 0xEFCDAB89;
    context->digest[2]      = 0x98BADCFE;
    context->digest[3]      = 0x10325476;
    context->digest[4]      = 0xC3D2E1F0;

    context->calculated   = FALSE;
    context->corrupted  = FALSE;
}
// Dz1CryptSHA1_reset
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1CryptSHA1_input
void Dz1CryptSHA1_input(Dz1CryptSHA1Ctx *context, const u8_t *message_array, size_t length)
{
    if (length == 0) return;

    if (context->calculated || context->corrupted)
    {
        context->corrupted = TRUE;
        return;
    }

    while(length-- && !context->corrupted)
    {
        context->data_block[context->data_block_idx++] = (*message_array & 0xFF);

        context->bits_len_low += 8;
        /* Force it to 32 bits */
        context->bits_len_low &= 0xFFFFFFFF;
        if (context->bits_len_low == 0)
        {
            context->bits_len_high++;
            /* Force it to 32 bits */
            context->bits_len_high &= 0xFFFFFFFF;
            if (context->bits_len_high == 0) context->corrupted = TRUE;	// Message is too long
        }

        if (context->data_block_idx == 64)
		{
			Dz1CryptSHA1_block(context);
			context->data_block_idx = 0;
		}
        message_array++;
    }
}
// Dz1CryptSHA1_input
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1CryptSHA1_conclued
bool_t Dz1CryptSHA1_finalize(Dz1CryptSHA1Ctx *ctx, u8_t *ret_buf, size_t ret_buf_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (ctx == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (ret_buf != NULL && ret_buf_sz < 20) ERR_SET_OUT(errp, ENOMEM);
    else if (ctx->corrupted) ERR_SET_OUT(errp, E2BIG);
    else
	{
		Dz1Error_set(errp, 0);
		if (!ctx->calculated)
		{
			Dz1CryptSHA1_padding(ctx);
			ctx->calculated = TRUE;
		}
		if (ret_buf != NULL)
		{
			u8_t *dp = ret_buf;
			*dp++ = (u8_t)((ctx->digest[0] >> 24) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[0] >> 16) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[0] >> 8) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[0] >> 0) & 0xFF);

			*dp++ = (u8_t)((ctx->digest[1] >> 24) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[1] >> 16) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[1] >> 8) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[1] >> 0) & 0xFF);

			*dp++ = (u8_t)((ctx->digest[2] >> 24) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[2] >> 16) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[2] >> 8) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[2] >> 0) & 0xFF);

			*dp++ = (u8_t)((ctx->digest[3] >> 24) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[3] >> 16) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[3] >> 8) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[3] >> 0) & 0xFF);

			*dp++ = (u8_t)((ctx->digest[4] >> 24) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[4] >> 16) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[4] >> 8) & 0xFF);
			*dp++ = (u8_t)((ctx->digest[4] >> 0) & 0xFF);
		}
	}
    return ERR_IS_SUCCESS(errp);
}
// Dz1CryptSHA1_conclued
///////////////////////////////////////////////////////////////////////////////

