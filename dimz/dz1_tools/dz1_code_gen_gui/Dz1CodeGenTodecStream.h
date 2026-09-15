#ifndef DZ1_CODE_GEN_TODEC_STREAM_H
#define DZ1_CODE_GEN_TODEC_STREAM_H

#include "Dz1CodeGenTodecUtil.h"

DZ1_CPPLINK ssize_t			 ConstructCodec_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t			 ConstructCodec_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1Error		 ConstructCodec_toStream(ConstructCodec *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param);
//DZ1_CPPLINK Dz1Error		 ConstructCodec_fromStream(ConstructCodec *dst, Dz1Stream *src, void *param);
DZ1_CPPLINK ConstructCodec	*ConstructCodec_fromStream(Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1Error		 ConstructCodec_save(ConstructCodec *src, str_t path, str_t name, Dz1IOStreamEndian ed, void *param);
//DZ1_CPPLINK Dz1Error		 ConstructCodec_load(ConstructCodec *dst, str_t path, str_t name, void *param);
DZ1_CPPLINK ConstructCodec	*ConstructCodec_load(str_t path, str_t name, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#endif