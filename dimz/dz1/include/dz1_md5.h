#ifndef DZ1_MD5_H
#define DZ1_MD5_H

#include <dz1_error.h>

typedef struct Dz1MD5Ctx
{
	u32_t	 state[4];		// state (ABCD)
	u32_t	 count[2];		// number of bits, modulo 2^64 (LSB first)
	u8_t	 buffer[64];	// input buffer
} Dz1MD5Ctx;

typedef u8_t Dz1MD5Data[16];

// Progressive API
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5_init(Dz1MD5Ctx *context);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5_update(Dz1MD5Ctx *context, u8_t *input, u32_t len);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5_final(Dz1MD5Data digest, Dz1MD5Ctx *context);
// Block API
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5_digest(Dz1MD5Data digest, u8_t *src, u32_t size);

// File API
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5_digestFile0(Dz1MD5Data digest, FILE *fp);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1MD5A_digestFile(Dz1MD5Data digest, str_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1MD5A_digestFile2(Dz1MD5Data digest, str_t path, str_t name);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1MD5W_digestFile(Dz1MD5Data digest, wstr_t fn);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1MD5W_digestFile2(Dz1MD5Data digest, wstr_t path, wstr_t name);
#ifdef	UNICODE
#define									 Dz1MD5_digestFile		Dz1MD5W_digestFile
#define									 Dz1MD5_digestFile2		Dz1MD5W_digestFile2
#else// UNICODE
#define									 Dz1MD5_digestFile		Dz1MD5A_digestFile
#define									 Dz1MD5_digestFile2		Dz1MD5A_digestFile2
#endif//UNICODE
#else// UNIX_SYSTEM
#define									 Dz1MD5_digestFile		Dz1MD5A_digestFile
#define									 Dz1MD5_digestFile2		Dz1MD5A_digestFile2
#endif//UNIX_SYSTEM

typedef struct Dz1MD5Struct
{
	Dz1MD5Data			signature;
} Dz1MD5Struct;

DZ1_CPPLINK DZ1_DLLPORT Dz1MD5Struct	*Dz1MD5Struct_new(Dz1Error *errp);
DZ1_CPPLINK DZ1_DLLPORT Dz1MD5Struct	*Dz1MD5Struct_clone(Dz1MD5Struct *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5Struct_del(Dz1MD5Struct *p);
static __inline__ void					 Dz1MD5Struct_delAndSetNull(void *pptr)
{
	Dz1MD5Struct **p = (Dz1MD5Struct **)pptr;
	Dz1MD5Struct_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT str_t			 Dz1MD5StructA_printable(Dz1MD5Struct *p, char buf[32 + 3 + 1]);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5StructA_dump(Dz1MD5Struct *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5StructA_fdump(FILE *fp, Dz1MD5Struct *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT wstr_t			 Dz1MD5StructW_printable(Dz1MD5Struct *p, wchar_t buf[32 + 3+ 1]);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5StructW_dump(Dz1MD5Struct *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1MD5StructW_fdump(FILE *fp, Dz1MD5Struct *p, int tab);
#ifdef	UNICODE
#define									 Dz1MD5Struct_printable			Dz1MD5StructW_printable
#define									 Dz1MD5Struct_dump				Dz1MD5StructW_dump
#define									 Dz1MD5Struct_fdump				Dz1MD5StructW_fdump
#else// UNICODE
#define									 Dz1MD5Struct_printable			Dz1MD5StructA_printable
#define									 Dz1MD5Struct_dump				Dz1MD5StructA_dump
#define									 Dz1MD5Struct_fdump				Dz1MD5StructA_fdump
#endif//UNICODE
#else// UNIX_SYSTEM
#define									 Dz1MD5Struct_printable			Dz1MD5StructA_printable
#define									 Dz1MD5Struct_dump				Dz1MD5StructA_dump
#define									 Dz1MD5Struct_fdump				Dz1MD5StructA_fdump
#endif//UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int				 Dz1MD5Struct_cmp(Dz1MD5Struct *a, Dz1MD5Struct *p);

#endif