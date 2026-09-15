#ifndef SAMPLE_UTIL_H_LOCAL
#define SAMPLE_UTIL_H_LOCAL

#include "sample.h"

static __inline__ bool_t u8_t_aaaa(u8_t *p, void *param, Dz1Error *err) { return TRUE; }
static __inline__ bool_t MyData_check(MyData *p, void *param, Dz1Error *err) { return TRUE; }
static __inline__ bool_t StructSample_check(StructSample *p, void *param, Dz1Error *err) { return TRUE; }
static __inline__ bool_t Entry_fix(StructSample *p, void *param, Dz1Error *err) { return TRUE; }
static __inline__ bool_t UnionSample_Indication(UnionSample *p, void *param, Dz1Error *err) { return TRUE; }
static __inline__ bool_t UnionSampleList_fixNode(UnionSample *p, void *param, Dz1Error *err) { return TRUE; }

static __inline__ ssize_t OtherInt_read(u32_t *dst, Dz1Stream *st, Dz1IOStreamEndian ed, Dz1StreamCallStk *_param, Dz1Error *err) { return Dz1Stream_read4(st, dst, ed, err); }
static __inline__ ssize_t OtherInt_write(Dz1Stream *st, u32_t *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *_param, Dz1Error *err) { return Dz1Stream_write4(st, *src, ed, err); }
#endif
