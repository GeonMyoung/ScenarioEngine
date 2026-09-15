#ifndef GITSN_LICENSE_CHK_H
#define GITSN_LICENSE_CHK_H

#include <dz1_error.h>

#define GitsnLicensePatternChunkSize			2048
typedef struct GitsnLicensePattern
{
	u64_t			 preamble1;
	u64_t			 preamble2;
	u8_t			 chunk[GitsnLicensePatternChunkSize];	// cast as GitsnLicenseCertChunk
} GitsnLicensePattern;

DZ1_CPPLINK bool_t				 GitsnLicenseChk_execute(u64_t preamble1, u64_t preamble2, GitsnLicensePattern *pattern, Dz1Error *err);
// License Information
///////////////////////////////////////////////////////////////////////////////
#endif
