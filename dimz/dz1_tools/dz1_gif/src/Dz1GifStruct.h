#ifndef _DZ1_TDC_DZ1_GIF_STRUCT_H_
#define _DZ1_TDC_DZ1_GIF_STRUCT_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1GifDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GifParallelArg
typedef struct Dz1GifParallelArg
{
	Dz1GifDecodeOptParallel		*opt;
	Dz1GifDescr					*descr;
	Dz1GifGraphic				*graphic;
} Dz1GifParallelArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifParallelArg *Dz1GifParallelArg_new(Dz1GifDecodeOptParallel *opt_ref, 
																 Dz1GifDescr *descr_ref, 
																 Dz1GifGraphic *graphic_ref, Dz1Error *err);
static __inline__ Dz1GifParallelArg *Dz1GifParallelArg_gen(Dz1Error *err) { return Dz1GifParallelArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifParallelArg_purge(Dz1GifParallelArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifParallelArg_del(Dz1GifParallelArg *p);
static __inline__ void Dz1GifParallelArg_delAndSetNull(void *ptr)
{
	Dz1GifParallelArg **p = (Dz1GifParallelArg **)ptr;
	if (p) { Dz1GifParallelArg_del(*p); *p = NULL; }
}
// Dz1GifParallelArg
////////////////////////////////////////////////////////////////////////////////

#endif
