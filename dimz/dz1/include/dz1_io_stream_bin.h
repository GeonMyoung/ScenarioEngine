#ifndef DZ1_IO_STREAM_BIN_H
#define DZ1_IO_STREAM_BIN_H

#include <dz1_bin.h>
#include <dz1_io_stream.h>

#define Dz1Binary_b_gen					Dz1Binary_gen
#define Dz1Binary_l_gen					Dz1Binary_gen

DZ1_CPPLINK ssize_t Dz1Binary8_write(Dz1Stream *st, void *Dz1BinaryPtr, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Binary8_read(void *Dz1BinaryPtr, Dz1Stream *st, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1Binary16_write(Dz1Stream *st, void *Dz1BinaryPtr, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Binary16_read(void *Dz1BinaryPtr, Dz1Stream *st, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t Dz1Binary32_write(Dz1Stream *st, void *Dz1BinaryPtr, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1Binary32_read(void *Dz1BinaryPtr, Dz1Stream *st, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#define Dz1Binary_write			Dz1Binary32_write
#define Dz1Binary_read			Dz1Binary32_read

#define Dz1Binary2_write		Dz1Binary32_write
#define Dz1Binary2_read			Dz1Binary32_read

static __inline__ ssize_t Dz1Binary_b_write(Dz1Stream *st, void *Dz1BinaryPtr, void *param, Dz1Error *err)
	{ return Dz1Binary_write(st, Dz1BinaryPtr, Dz1IOStreamEndian_big, param, err); }

static __inline__ ssize_t Dz1Binary_l_write(Dz1Stream *st, void *Dz1BinaryPtr, void *param, Dz1Error *err)
	{ return Dz1Binary_write(st, Dz1BinaryPtr, Dz1IOStreamEndian_little, param, err); }

static __inline__ ssize_t Dz1Binary_b_read(void *Dz1BinaryPtr, Dz1Stream *st, void *param, Dz1Error *err)
	{ return Dz1Binary_read(Dz1BinaryPtr, st, Dz1IOStreamEndian_big, param, err); }

static __inline__ ssize_t Dz1Binary_l_read(void *Dz1BinaryPtr, Dz1Stream *st, void *param, Dz1Error *err)
	{ return Dz1Binary_read(Dz1BinaryPtr, st, Dz1IOStreamEndian_little, param, err); }

#endif
