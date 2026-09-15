#ifndef PUBLISH_H
#define PUBLISH_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

DZ1_CPPLINK void Dz1MdefcModule_header(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module);
DZ1_CPPLINK void Dz1MdefcModule_headerAsnConv(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module);
DZ1_CPPLINK void Dz1MdefcModule_source(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module);
/*
DZ1_CPPLINK void Dz1MdefcModule_testHeader(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module);
DZ1_CPPLINK void Dz1MdefcModule_testSource(FILE *fp, PublishSpec *spec, Dz1MdefcModule *module);
*/
#endif
