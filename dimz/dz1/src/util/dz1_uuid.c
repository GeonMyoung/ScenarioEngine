#include <dz1_time.h>
#include "dz1_uuid.h"

static int uuid_clk_seq_status = 0;
static u16_t uuid_clk_seq = 0;
static u16_t _uuid_clk_seq_get(void)
{
	u16_t ret = 0;
	if (uuid_clk_seq_status == 0)
	{
		time_t tNow = time(NULL);
		uuid_clk_seq = (u16_t)(tNow & 0x1FFF);
		uuid_clk_seq_status = 1;
	}
	ret = uuid_clk_seq++;
	uuid_clk_seq &= 0x1FFF;
	return ret;
}

bool_t Dz1UniversalUniqueID_initV1(Dz1UniversalUniqueID *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	s64_t t_ns = 0;
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Time_getNanoTime(&t_ns, errp) == FALSE) ERR_OUT(errp);
	else
	{
		int i, temp;
		u8_t variant = 0x5;
		u64_t ts100 = t_ns / 100;
		u16_t version = 1, clk_seq = _uuid_clk_seq_get();

		dst->t_low = (u32_t)(ts100 & 0xFFFFFFFF);
		dst->t_mid = (u16_t)((ts100 >> 32) & 0xFFFF);
		dst->t_high_and_ver = (version << 12) | (u16_t)((ts100 >> 48) & 0x0FFF);
		dst->clk_high_and_resvered = (variant << 5) | (u8_t)((clk_seq >> 8) & 0xFF);
		dst->clk_low = (u8_t)(clk_seq & 0xFF);

		dst->node48bit = 0;
		for (i = 0; i < 6; i++)
		{
			dst->node48bit <<= 8;
			temp = rand();
			dst->node48bit |= (temp & 0xFF);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t Dz1UniversalUniqueID_toBin(u8_t *dst, size_t dst_sz, Dz1UniversalUniqueID *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || dst_sz < 16 || src == NULL) ERR_SET_OUT(errp, 0);
	else
	{
		u8_t *dp = dst;
		*dp++ = (u8_t)((src->t_low >> 24) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->t_low >> 16) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->t_low >> 8) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->t_low >> 0) & 0xFF); dst_sz--; ret++;

		*dp++ = (u8_t)((src->t_mid >> 8) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->t_mid >> 0) & 0xFF); dst_sz--; ret++;

		*dp++ = (u8_t)((src->t_high_and_ver >> 8) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->t_high_and_ver >> 0) & 0xFF); dst_sz--; ret++;

		*dp++ = src->clk_high_and_resvered; dst_sz--; ret++;
		*dp++ = src->clk_low; dst_sz--; ret++;

		*dp++ = (u8_t)((src->node48bit >> 40) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->node48bit >> 32) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->node48bit >> 24) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->node48bit >> 16) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->node48bit >> 8) & 0xFF); dst_sz--; ret++;
		*dp++ = (u8_t)((src->node48bit >> 0) & 0xFF); dst_sz--; ret++;
	}
	return  ret;
}

ssize_t Dz1UniversalUniqueID_fromBin(Dz1UniversalUniqueID *dst, u8_t *src, size_t src_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src_sz < 16 || src == NULL) ERR_SET_OUT(errp, 0);
	else
	{
		u8_t *sp = src;
		dst->t_low = 0;
		dst->t_low |= (((u32_t)(*sp++) & 0xFF) << 24); src_sz--; ret++;
		dst->t_low |= (((u32_t)(*sp++) & 0xFF) << 16); src_sz--; ret++;
		dst->t_low |= (((u32_t)(*sp++) & 0xFF) << 8); src_sz--; ret++;
		dst->t_low |= (((u32_t)(*sp++) & 0xFF) << 0); src_sz--; ret++;

		dst->t_mid = 0;
		dst->t_mid |= (((u16_t)(*sp++) & 0xFF) << 8); src_sz--; ret++;
		dst->t_mid |= (((u16_t)(*sp++) & 0xFF) << 0); src_sz--; ret++;

		dst->t_high_and_ver = 0;
		dst->t_high_and_ver |= (((u16_t)(*sp++) & 0xFF) << 8); src_sz--; ret++;
		dst->t_high_and_ver |= (((u16_t)(*sp++) & 0xFF) << 0); src_sz--; ret++;

		dst->clk_high_and_resvered = *sp++; src_sz--; ret++;
		dst->clk_low = *sp++; src_sz--; ret++;

		dst->node48bit = 0;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 40); src_sz--; ret++;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 32); src_sz--; ret++;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 24); src_sz--; ret++;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 16); src_sz--; ret++;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 8); src_sz--; ret++;
		dst->node48bit |= (((u64_t)(*sp++) & 0xFF) << 0); src_sz--; ret++;
	}
	return ret;
}

