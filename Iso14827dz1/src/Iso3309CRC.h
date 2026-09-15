#ifndef _ISO14827CRC_H_
#define _ISO14827CRC_H_

#include <dz1.h>

//DZ1_CPPLINK uint16_t Iso14827Crc(u8_t *data, u32_t size);
DZ1_CPPLINK u16_t Iso3309Crc(u8_t *data, size_t size);

#endif
