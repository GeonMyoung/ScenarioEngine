#ifndef DZ1_MDEFC_PARSER_H
#define DZ1_MDEFC_PARSER_H

#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

DZ1_CPPLINK Dz1MdefcModule *Dz1MdefcModule_compile(PublishSpec *spec, IncludeSpec *inc, str_t filename, str_t text, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1MdefcModule_includeTDC(Dz1MdefcModule *p, PublishSpec *spec, IncludeSpec *inc, str_t name);

#endif
