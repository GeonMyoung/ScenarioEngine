#ifndef _DZ1_TDC_DZ1_SERIAL_SOCK_SPEC_H_
#define _DZ1_TDC_DZ1_SERIAL_SOCK_SPEC_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_sync.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SerialSocketSpecific
typedef struct Dz1SerialSocketSpecific
{
	Dz1Sync			*sync;
	Dz1SocketBuf	*buf;
	bool_t			 eof;
	void			*io;
} Dz1SerialSocketSpecific;

DZ1_CPPLINK DZ1_DLLPORT Dz1SerialSocketSpecific *Dz1SerialSocketSpecific_new(Dz1Sync *sync, 
																			 Dz1SocketBuf *buf, 
																			 bool_t eof, 
																			 void *io, Dz1Error *err);
static __inline__ Dz1SerialSocketSpecific *Dz1SerialSocketSpecific_gen(Dz1Error *err) { return Dz1SerialSocketSpecific_new(NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1SerialSocketSpecific_purge(Dz1SerialSocketSpecific *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SerialSocketSpecific_del(Dz1SerialSocketSpecific *p);
static __inline__ void Dz1SerialSocketSpecific_delAndSetNull(void *ptr)
{
	Dz1SerialSocketSpecific **p = (Dz1SerialSocketSpecific **)ptr;
	if (p) { Dz1SerialSocketSpecific_del(*p); *p = NULL; }
}
// Dz1SerialSocketSpecific
////////////////////////////////////////////////////////////////////////////////

#endif
