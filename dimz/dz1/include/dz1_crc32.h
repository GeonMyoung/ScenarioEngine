#ifndef DZ1_CRC32_H
#define DZ1_CRC32_H

#include <dz1_error.h>

DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1CRC32_IEEE802Dot3_file(FILE *fp, size_t size, u32_t crc);
DZ1_CPPLINK DZ1_DLLPORT u32_t Dz1CRC32_IEEE802Dot3_buffer(u8_t *data, size_t size, u32_t crc);

#endif