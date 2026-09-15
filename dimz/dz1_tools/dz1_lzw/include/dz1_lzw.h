#ifndef DZ1_LZW_H
#define DZ1_LZW_H

#include "dz1_lzw_def.h"

typedef struct Dz1LzwCompStream
{
	u32_t *code_arr;
	u32_t arr_size;
	u32_t arr_idx;


	u8_t *byte_arr;
	u32_t byte_size;
	u32_t byte_idx;

	u32_t bb;
	u32_t bb_remain;
} Dz1LzwCompStream;

DZ1_CPPLINK Dz1Error Dz1LzwCompress(Dz1LzwCompStream *dst, u8_t *data, size_t size, u32_t code_size);

typedef struct Dz1LzwDecompStream
{
	u8_t *data_arr;
	u32_t arr_size;
	u32_t arr_idx;
} Dz1LzwDecompStream;
//DZ1_CPPLINK Dz1Error Dz1LzwDecompress(Dz1LzwDecompStream *dst, u32_t *codes, size_t size, u32_t code_size);
DZ1_CPPLINK Dz1Error Dz1LzwDecompress(Dz1LzwDecompStream *dst, u8_t *src, size_t size, u32_t code_size);

#endif