#ifndef PUBLISH_SPEC_PARSER_H
#define PUBLISH_SPEC_PARSER_H

#include <dz1_parser.h>
#include <Dz1TdcInfoModule.h>
#include <Dz1TdcInfoIncludeSpec.h>

void *PublishSpecParser_new(Dz1Error *err);

PublishSpec *PublishSpecParser_proc(void *parser, str_t text, Dz1Error *err);

#endif
