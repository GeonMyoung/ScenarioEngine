#ifndef _DZ1_TDC_DZ1_TDQ_DEF_H_
#define _DZ1_TDC_DZ1_TDQ_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_tbl_def.h"
#include "dz1_tdq_qry_def.h"
#include "dz1_tdq_types.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqDbScheme
typedef struct Dz1TdqDbScheme
{
	Dz1TdqDbConnArg				*arg;
	Dz1TdqDbIface				*dbh;
	Dz1TdqTblShapeList			*shapes;
	Dz1TdqTblInstanceList		*tables;
	Dz1TdqTblInstanceSeq		*tblseq;
	Dz1TdqQueryList				*queries;
} Dz1TdqDbScheme;

DZ1_CPPLINK DZ1_DLLPORT Dz1TdqDbScheme *Dz1TdqDbScheme_new(Dz1TdqDbConnArg *arg, Dz1Error *err);	// User Customized
static __inline__ Dz1TdqDbScheme *Dz1TdqDbScheme_gen(Dz1Error *err) { return Dz1TdqDbScheme_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqDbScheme_purge(Dz1TdqDbScheme *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqDbScheme_del(Dz1TdqDbScheme *p);
static __inline__ void Dz1TdqDbScheme_delAndSetNull(void *ptr)
{
	Dz1TdqDbScheme **p = (Dz1TdqDbScheme **)ptr;
	if (p) { Dz1TdqDbScheme_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TdqDbScheme_dump(Dz1TdqDbScheme *p, int tab);
// Dz1TdqDbScheme
////////////////////////////////////////////////////////////////////////////////

#endif
