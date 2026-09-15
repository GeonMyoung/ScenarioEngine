#ifndef DZ1_ELASTIC_BUFFER_H_LOCAL
#define DZ1_ELASTIC_BUFFER_H_LOCAL

#include <dz1_elastic_buf.h>

DZ1_CPPLINK size_t Dz1ElasticBufEntry_getDataSize(Dz1ElasticBufEntry *p);
DZ1_CPPLINK s64_t Dz1ElasticBuf_getDistance(Dz1ElasticBuf *eb, Dz1ElasticBufEntry *entry, u32_t pos, Dz1Error *err);

#endif