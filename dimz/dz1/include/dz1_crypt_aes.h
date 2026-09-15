#ifndef DZ1_CRYPT_AES_H
#define DZ1_CRYPT_AES_H

#include <dz1.h>

#define DZ1_CRYPT_AES_BLK_SIZE				16						// AES operates on 16 bytes at a time
#define Dz1CryptAes256KeyBitsSize			256
#define Dz1CryptAes256KeyByteSize			(Dz1CryptAes256KeyBitsSize / 8)

///////////////////////////////////////////////////////////////////////////////
// Key Setup
// Key setup must be done before any AES en/de-cryption functions can be used.
// *** key		: The key, must be 128, 192, or 256 bits(16, 24, or 32 bytes)
// *** w		: Output key schedule to be used later
// *** keysize	: Key size in bit. 128, 192, or 256
DZ1_CPPLINK bool_t Dz1CryptAes_KeySetup(const u8_t key[], u32_t w[60], int keysize);
// Key Setup
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// AES - CBC
// *** input	: Plain text
// *** in_len	: size of input in byte. Must be a multiple of DZ1_CRYPT_AES_BLK_SIZE
// *** output	: Cipher text, same length as plaintext
// *** key		: From the key setup
// *** keysize	: Key size in bit. 128, 192, or 256
// *** iv		: IV, must be DZ1_CRYPT_AES_BLK_SIZE bytes long
DZ1_CPPLINK int Dz1CryptAes_EncryptCBC(const u8_t input[], size_t in_len, u8_t output[], const u32_t key[60], int keysize, const u8_t iv[DZ1_CRYPT_AES_BLK_SIZE]);

// Only output the CBC-MAC of the input.
// *** input	: Plain text
// *** in_len	: size of input in byte. Must be a multiple of DZ1_CRYPT_AES_BLK_SIZE
// *** output	: Output MAC
// *** key		: From the key setup
// *** keysize	: Key size in bit. 128, 192, or 256
// *** iv		: IV, must be DZ1_CRYPT_AES_BLK_SIZE bytes long
DZ1_CPPLINK int Dz1CryptAes_EncryptCBC_MAC(const u8_t input[], size_t in_len, u8_t output[], const u32_t key[60], int keysize, const u8_t iv[DZ1_CRYPT_AES_BLK_SIZE]);

// *** input	: Cipher text
// *** in_len	: size of input in byte. Must be a multiple of DZ1_CRYPT_AES_BLK_SIZE
// *** output	: Plain text, same length as plaintext
// *** key		: From the key setup
// *** keysize	: Key size in bit. 128, 192, or 256
// *** iv		: IV, must be DZ1_CRYPT_AES_BLK_SIZE bytes long
DZ1_CPPLINK int Dz1CryptAes_DecryptCBC(const u8_t input[], size_t in_len, u8_t output[], const u32_t key[60], int keysize, const u8_t iv[DZ1_CRYPT_AES_BLK_SIZE]);
// AES - CBC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// AES - CTR
// *** input	: Plain text
// *** in_len	: size of input in byte.
// *** output	: Cipher text, same length as plaintext
// *** key		: From the key setup
// *** keysize	: Key size in bit. 128, 192, or 256
// *** iv		: IV, must be DZ1_CRYPT_AES_BLK_SIZE bytes long
DZ1_CPPLINK void Dz1CryptAes_EncryptCTR(const u8_t input[], size_t in_len, u8_t output[], const u32_t key[60], int keysize, const u8_t iv[DZ1_CRYPT_AES_BLK_SIZE]);

// *** input	: Cipher text
// *** in_len	: size of input in byte.
// *** output	: Plain text, same length as plaintext
// *** key		: From the key setup
// *** keysize	: Key size in bit. 128, 192, or 256
// *** iv		: IV, must be DZ1_CRYPT_AES_BLK_SIZE bytes long
DZ1_CPPLINK void Dz1CryptAes_DecryptCTR(const u8_t input[], size_t in_len, u8_t output[], const u32_t key[60], int keysize,const u8_t iv[DZ1_CRYPT_AES_BLK_SIZE]);
// AES - CTR
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// AES - CCM
// Returns True if the input parameters do not violate any constraint.

// *** plaintext		: IN  - Plain text.
// *** plaintext_len	: IN  - Plain text length.
// *** assoc			: IN  - Associated Data included in authentication, but not encryption.
// *** assoc_len		: IN  - Associated Data length in bytes.
// *** nonce			: IN  - The Nonce to be used for encryption.
// *** nonce_len		: IN  - Nonce length in bytes.
// *** ciphertext		: OUT - Cipher text, a concatination of the plaintext and the MAC.
// *** ciphertext_len	: OUT - The length of the ciphertext, always plaintext_len + mac_len.
// *** mac_len			: IN  - The desired length of the MAC, must be 4, 6, 8, 10, 12, 14, or 16.
// *** key				: IN  - The AES key for encryption.
// *** keysize			: IN  - The length of the key in bits. Valid values are 128, 192, 256.
DZ1_CPPLINK int Dz1CryptAes_EncryptCCM(const u8_t plaintext[],	u32_t  plaintext_len,
									   const u8_t assoc[],		u16_t  assoc_len,
									   const u8_t nonce[],		u16_t  nonce_len,
											 u8_t ciphertext[],	u32_t *ciphertext_len,	u32_t mac_len,
									   const u8_t key[],		int	   keysize);							

// Returns True if the input parameters do not violate any constraint.
// Use mac_auth to ensure decryption/validation was preformed correctly.
// If authentication does not succeed, the plaintext is zeroed out. To overwride
// this, call with mac_auth = NULL. The proper proceedure is to decrypt with
// authentication enabled (mac_auth != NULL) and make a second call to that
// ignores authentication explicitly if the first call failes.

// *** ciphertext		: IN  - Cipher text, the concatination of encrypted plaintext and MAC.
// *** ciphertext_len	: IN  - Cipher text length in bytes.
// *** assoc			: IN  - The Associated Data, required for authentication.
// *** assoc_len		: IN  - Associated Data length in bytes.
// *** nonce			: IN  - The Nonce to use for decryption, same one as for encryption.
// *** nonce_len		: IN  - Nonce length in bytes.
// *** plaintext		: OUT - The plaintext that was decrypted. Will need to be large enough to hold ciphertext_len - mac_len.
// *** plaintext_len	: OUT - Length in bytes of the output plaintext, always ciphertext_len - mac_len .
// *** mac_len			: IN  - The length of the MAC that was calculated.
// *** mac_auth			: OUT - TRUE if authentication succeeded, FALSE if it did not. NULL pointer will ignore the authentication.
// *** key				: IN  - The AES key for decryption.
// *** keysize			: IN  - The length of the key in BITS. Valid values are 128, 192, 256.
DZ1_CPPLINK int Dz1CryptAes_DecryptCCM(const u8_t ciphertext[],	u32_t  ciphertext_len,
									   const u8_t assoc[],		u16_t  assoc_len,
									   const u8_t nonce[],		u16_t  nonce_len,
											 u8_t plaintext[],	u32_t *plaintext_len, u32_t mac_len, int *mac_auth,
									   const u8_t key[],		int    keysize);
// AES - CCM
///////////////////////////////////////////////////////////////////////////////

#endif
