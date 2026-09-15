#ifndef DZ1_CRYPT_SHA1_H
#define DZ1_CRYPT_SHA1_H

#include <dz1_error.h>

typedef struct Dz1CryptSHA1Ctx
{
    u32_t	 digest[5];			// 160bit Hash Value

    u32_t	 bits_len_low;		// low 32bit of length in bits
    u32_t	 bits_len_high;		// high 32bit of length in bits

    u8_t	 data_block[64];	// 512-bit data blocks
    s32_t	 data_block_idx;	// data block index

    bool_t	 calculated;		// calculated flag
    bool_t	 corrupted;			// corrupted flag
} Dz1CryptSHA1Ctx;

#define							 Dz1CryptSHA1_init	Dz1CryptSHA1_reset
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1CryptSHA1_reset(Dz1CryptSHA1Ctx *context);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1CryptSHA1_input(Dz1CryptSHA1Ctx *ctx, const u8_t *src, size_t size);
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1CryptSHA1_finalize(Dz1CryptSHA1Ctx *ctx, u8_t *ret_buf, size_t ret_buf_sz, Dz1Error *err);

#endif	// DZ1_CRYPT_SHA1_H
