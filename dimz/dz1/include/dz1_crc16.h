#ifndef DZ1_CRC16_H
#define DZ1_CRC16_H

#include <dz1_error.h>

DZ1_CPPLINK DZ1_DLLPORT u16_t	 Dz1CRC16_ISO3359_buffer(u8_t *data, size_t size);
DZ1_CPPLINK DZ1_DLLPORT ssize_t	 Dz1CRC16_ISO3359_file(FILE *fp, size_t size, u16_t *ret_crc, Dz1Error *err);

#endif