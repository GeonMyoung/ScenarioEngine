#ifndef DZ1_BASE64_H
#define DZ1_BASE64_H

#include <dz1_bin.h>
DZ1_CPPLINK DZ1_DLLPORT size_t		 Dz1Base64_getEncSize(size_t raw_size);

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_encBlockA(char *dst, size_t dst_sz, u8_t *src, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_decBlockA(u8_t *dst, size_t dst_sz, size_t *outsize, char *src, size_t src_size, Dz1Error *errp);

DZ1_CPPLINK DZ1_DLLPORT str_t		 Dz1Base64_encA(u8_t *src, ssize_t src_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1Base64_decA(str_t src, ssize_t src_len, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_encBlockW(wchar_t *dst, size_t dst_sz, u8_t *src, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_decBlockW(u8_t *dst, size_t dst_sz, size_t *outsize, wchar_t *src, size_t src_size, Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT wstr_t		 Dz1Base64_encW(u8_t *src, ssize_t src_size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Binary	*Dz1Base64_decW(wstr_t src, ssize_t src_len, Dz1Error *err);
#ifdef UNICODE
#define								 Dz1Base64_encBlock	Dz1Base64_encBlockW
#define								 Dz1Base64_decBlock	Dz1Base64_decBlockW
#define								 Dz1Base64_enc		Dz1Base64_encW
#define								 Dz1Base64_dec		Dz1Base64_decW
#else // UNICODE
#define								 Dz1Base64_encBlock	Dz1Base64_encBlockA
#define								 Dz1Base64_decBlock	Dz1Base64_decBlockA
#define								 Dz1Base64_enc		Dz1Base64_encA
#define								 Dz1Base64_dec		Dz1Base64_decA
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Base64_encBlock	Dz1Base64_encBlockA
#define								 Dz1Base64_decBlock	Dz1Base64_decBlockA
#define								 Dz1Base64_enc		Dz1Base64_encA
#define								 Dz1Base64_dec		Dz1Base64_decA
#endif // UNIX_SYSTEM

DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_RawToB64(char *b64, size_t b64_sz, u8_t *raw, size_t raw_sz, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t		 Dz1Base64_B64ToRaw(u8_t *raw, size_t raw_sz, char *b64, size_t b64_sz, Dz1Error *err);

#endif	// DZ1_BASE64_H
