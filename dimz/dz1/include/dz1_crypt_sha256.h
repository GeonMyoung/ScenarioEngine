#ifndef DZ1_CRYPT_SHA256_H
#define DZ1_CRYPT_SHA256_H

#include <dz1.h>

#define Dz1CryptSha256BlkSize		32

typedef struct Dz1CryptSha256Ctx{
	u8_t				 data[64];
	u32_t				 datalen;
	u64_t				 bitlen;
	u32_t				 state[8];
} Dz1CryptSha256Ctx;

DZ1_CPPLINK void Dz1CryptSha256_init(Dz1CryptSha256Ctx *ctx);
DZ1_CPPLINK void Dz1CryptSha256_update(Dz1CryptSha256Ctx *ctx, const u8_t data[], size_t len);
DZ1_CPPLINK void Dz1CryptSha256_final(Dz1CryptSha256Ctx *ctx, u8_t hash[Dz1CryptSha256BlkSize]);

#endif
