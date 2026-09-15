#ifndef _PUBLISH_ASN_CONV_H_LOCAL
#define _PUBLISH_ASN_CONV_H_LOCAL

#include <Dz1TdcInfoPublishSpec.h>

DZ1_CPPLINK bool_t Publish_asnConvDeclare(FILE *fp, u32_t api, PublishSpec *spec, str_t name, str_t srcName, int tab);
DZ1_CPPLINK bool_t Publish_asnConvImple(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab);

#endif
