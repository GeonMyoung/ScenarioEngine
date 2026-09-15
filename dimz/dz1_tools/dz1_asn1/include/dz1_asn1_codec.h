#ifndef DZ1_ASN1_CODEC_H
#define DZ1_ASN1_CODEC_H

#include <dz1_asn1_codec_stream.h>
#include <dz1_asn1_codec_def.h>
#include <dz1_asn1_types.h>
#include <dz1_asn1_constraint.h>
#include <dz1_asn1_codec_ber.h>
#include <dz1_asn1_codec_per.h>
#include <dz1_asn1_typedescr.h>

#define DZ1_THREAD_LOG_SEQUENCE				DZ1_THREAD_LOG_RESERVED12
#define DZ1_THREAD_LOG_SET					DZ1_THREAD_LOG_RESERVED13
#define DZ1_THREAD_LOG_ARRAY				DZ1_THREAD_LOG_RESERVED20
#define DZ1_THREAD_LOG_CHOICE				DZ1_THREAD_LOG_RESERVED21
#define DZ1_THREAD_LOG_INDIRECT				DZ1_THREAD_LOG_RESERVED22
#define DZ1_THREAD_LOG_OPENTYPE				DZ1_THREAD_LOG_RESERVED23

#define Dz1Asn1Codec_shellSupport \
do\
{\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_SEQUENCE, "sequence",	"seq", NULL);\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_SET,		 "set",			"set", NULL);\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_ARRAY,	 "array",		"arr", NULL);\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_CHOICE,	 "choice",		"cho", NULL);\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_INDIRECT, "indirect",	"ind", NULL);\
	Dz1Shell_thredCmdSetLogFlag(DZ1_THREAD_LOG_OPENTYPE, "opentype",	"open", NULL);\
} while(0)

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ObjectSetInfo
typedef struct Dz1Asn1ObjectSetInfo
{
	void					**tbl;
	size_t					  tbl_sz;
} Dz1Asn1ObjectSetInfo;
#define Dz1Asn1ObjectSetInfo_initializer		{ NULL, 0 }
static __inline__ bool_t Dz1Asn1ObjectSetInfo_isValid(Dz1Asn1ObjectSetInfo *p) { bool_t ret = FALSE; if (p != NULL && p->tbl != NULL && p->tbl_sz > 0) ret = TRUE; return ret; }
// Dz1Asn1ObjectSetInfo
///////////////////////////////////////////////////////////////////////////////

#endif // DZ1_ASN1_CODEC_H
