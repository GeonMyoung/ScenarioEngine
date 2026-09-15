#include <time.h>

#include "hae_local_memory.h"

#include "hae_des.h"
#include "hae_local_crypt.h"
#include "hae_local_crypt_vectors.c"

static int rand_init = FALSE;

static void enshuffel(u8_t *dst, u8_t *src, int srcLen, u16_t iv_idx, u16_t pad)
{
	u32_t factor = (((u32_t)iv_idx << 16) & 0xffff0000) | (((u32_t)pad) & 0x0000ffff);
	u8_t *p = (u8_t *)&factor;
	int seg = srcLen / 4, frag = srcLen % 4;

	*dst++ = *p++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*dst++ = *p++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*dst++ = *p++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*dst++ = *p++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	if (frag) memcpy(dst, src, frag);
}

static u32_t deshuffel(u8_t *dst, u8_t *src, int srcLen)
{
	u32_t ret = 0;
	u8_t *p = (u8_t *)&ret;

	int seg = srcLen / 4, frag = srcLen % 4;

	*p++ = *src++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*p++ = *src++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*p++ = *src++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	*p++ = *src++;
	memcpy(dst, src, seg); dst += seg; src += seg;
	if (frag)
		memcpy(dst, src, frag);
	return ret;
}

int _hae_local_encrypt(void *data, int len, char key[8], void **secured, int *secLen HAE_LOCAL_MEMORY_TRC_ARG)
{
	u16_t iv_idx = -1, result;
	u8_t *cheater = NULL;
	DES_CBC_CTX ctx;
	u16_t pad = 8 - (len % 8);

	if (!rand_init) srand(time(NULL));

	iv_idx = (u16_t)(rand() % NUMBER_OF_VECTORS);
	DES_CBC.init(&ctx, (u8_t *)key, (u8_t *)vectors[iv_idx], 1);
	
	*secLen = len + pad;
	*secured = (void *)LOCAL_MALLOC_TRC(*secLen + 4);
	cheater = (u8_t *)LOCAL_MALLOC_TRC(*secLen);

	memset(*secured, 0, *secLen);
	memcpy(*secured, data, len);

	if ((result = DES_CBC.update(&ctx, cheater, *secured, *secLen)))
	{
		LOCAL_FREE(*secured); *secured = NULL;
		LOCAL_FREE(cheater);
		*secLen = 0;
		return FALSE;
	}


	enshuffel(*secured, cheater, *secLen, iv_idx, pad);
	*secLen += 4;

	LOCAL_FREE(cheater);
	return TRUE;
}

int _hae_local_decrypt(void *data, int len, char key[8],  void **opened, int *openedLen HAE_LOCAL_MEMORY_TRC_ARG)
{
	u32_t factor = 0;
	u16_t iv_idx = -1, pad = 0;
	int result = 0;
	u8_t *cheater = NULL;
	DES_CBC_CTX ctx;

	*openedLen = len - 4;

	cheater = (u8_t *)LOCAL_MALLOC_TRC(*openedLen);
	*opened = (void *)LOCAL_MALLOC_TRC(*openedLen);

	factor = deshuffel(cheater, data, *openedLen);
	iv_idx = (u16_t)((factor & 0xffff0000) >> 16);
	pad = (u16_t)(factor & 0x0000ffff);
	if (iv_idx > NUMBER_OF_VECTORS)
	{
		LOCAL_FREE(*opened); *opened = NULL;
		LOCAL_FREE(cheater);
		*openedLen = 0;
		printf("_hae_local_decrypt() : Invalid IV Idx\n");
		return FALSE;
	}

	DES_CBC.init(&ctx, (u8_t *)key, (u8_t *)vectors[iv_idx], 0);

	if ((result = DES_CBC.update(&ctx, *opened, cheater, *openedLen)))
	{
		LOCAL_FREE(*opened); *opened = NULL;
		LOCAL_FREE(cheater);
		*openedLen = 0;
		printf("_hae_local_decrypt() : Invalid IV Idx\n");
		return FALSE;
	}
	*openedLen -= pad;
	LOCAL_FREE(cheater);
	return TRUE;
}


