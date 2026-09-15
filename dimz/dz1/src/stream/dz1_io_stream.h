#ifndef DZ1_IO_STREAM_H_LOCAL
#define DZ1_IO_STREAM_H_LOCAL

#include <dz1_io_stream.h>

typedef union Dz1IoStreamInternalVal
{
	u8_t			v1;
	u16_t			v2;
	u32_t			v4;
	u64_t			v8;
} Dz1IoStreamInternalVal;

DZ1_CPPLINK bool_t Dz1IoStream_isPossibleSize(size_t s);

#endif