#ifndef PUBLISH_SPEC_DZ1_H
#define PUBLISH_SPEC_DZ1_H

#include <dz1_error.h>
#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

PublishSpec *PublishSpec_dz1(Dz1Error *err);
void PublishSpec_dz1Write(FILE *fp);

#endif
