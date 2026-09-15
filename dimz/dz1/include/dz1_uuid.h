#ifndef DZ1_UUID_H
#define DZ1_UUID_H

#include <dz1_error.h>

typedef struct Dz1UniversalUniqueID
{
	u32_t			t_low;
	u16_t			t_mid;
	u16_t			t_high_and_ver;
	u8_t			clk_high_and_resvered;
	u8_t			clk_low;
	u64_t			node48bit;
} Dz1UniversalUniqueID;

DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1UniversalUniqueID_initV1(Dz1UniversalUniqueID *dst, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1UniversalUniqueID_toBin(u8_t *dst, size_t dst_sz, Dz1UniversalUniqueID *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1UniversalUniqueID_toBin(u8_t *dst, size_t dst_sz, Dz1UniversalUniqueID *src, Dz1Error *err);

#endif
