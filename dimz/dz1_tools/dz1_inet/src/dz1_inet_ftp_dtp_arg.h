#ifndef _DZ1_TDC_DZ1_INET_FTP_DTP_ARG_H_
#define _DZ1_TDC_DZ1_INET_FTP_DTP_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_env.h"

////////////////////////////////////////////////////////////////////////////////
// DataFragmentList
typedef struct DataFragmentList
{
	void *storage;
	unsigned int (*count)(struct DataFragmentList *p);
	Dz1Error (*travel)(struct DataFragmentList *p, Dz1Error (*func)(void *ptr, Dz1Binary *entry), void *ptr);
	Dz1Error (*travelForward)(struct DataFragmentList *p, Dz1Error (*func)(void *ptr, Dz1Binary *entry), void *ptr);
	Dz1Error (*travelBackward)(struct DataFragmentList *p, Dz1Error (*func)(void *ptr, Dz1Binary *entry), void *ptr);
	Dz1Binary **(*get_array)(struct DataFragmentList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct DataFragmentList *p, Dz1Binary *data);
	int (*cmp)(Dz1Binary *a, Dz1Binary *b);
} DataFragmentList;

DZ1_CPPLINK DZ1_DLLPORT DataFragmentList *DataFragmentList_new(Dz1Error *err);
static __inline__ DataFragmentList *DataFragmentList_gen(Dz1Error *err) { return DataFragmentList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT DataFragmentList *DataFragmentList_clone(DataFragmentList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentList_purge(DataFragmentList *p);
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentList_del(DataFragmentList *p);
static __inline__ void DataFragmentList_delAndSetNull(void *ptr)
{
	DataFragmentList **p = (DataFragmentList **)ptr;
	if (p != NULL) { DataFragmentList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentListA_dump(DataFragmentList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentListA_fdump(FILE *fp, DataFragmentList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentListW_dump(DataFragmentList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void DataFragmentListW_fdump(FILE *fp, DataFragmentList *p, int tab);
#ifdef UNICODE
#define DataFragmentList_dump DataFragmentListW_dump
#define DataFragmentList_fdump DataFragmentListW_fdump
#else //  UNICODE
#define DataFragmentList_dump DataFragmentListA_dump
#define DataFragmentList_fdump DataFragmentListA_fdump
#endif //  UNICODE
static __inline__ void DataFragmentListX_dump(DataFragmentList *p, int tab) { DZ1_DUMP(DataFragmentList, p, tab); }
static __inline__ void DataFragmentListX_fdump(FILE *fp, DataFragmentList *p, int tab) { DZ1_FDUMP(fp, DataFragmentList, p, tab); }
#else // UNIX_SYSTEM
#define DataFragmentList_dump DataFragmentListA_dump
#define DataFragmentListX_dump DataFragmentListA_dump
#define DataFragmentList_fdump DataFragmentListA_fdump
#define DataFragmentListX_fdump DataFragmentListA_fdump
#endif // UNIX_SYSTEM

// DataFragmentList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPDestPresent
typedef enum Dz1InetFtpRXDTPDestPresent
{
	Dz1InetFtpRXDTPDestPresent_fp,
	Dz1InetFtpRXDTPDestPresent_list,
	Dz1InetFtpRXDTPDestPresent_max
} Dz1InetFtpRXDTPDestPresent;

DZ1_CPPLINK str_t Dz1InetFtpRXDTPDestPresentStrA(Dz1InetFtpRXDTPDestPresent v);
DZ1_CPPLINK Dz1InetFtpRXDTPDestPresent Dz1InetFtpRXDTPDestPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpRXDTPDestPresentStrW(Dz1InetFtpRXDTPDestPresent v);
DZ1_CPPLINK Dz1InetFtpRXDTPDestPresent Dz1InetFtpRXDTPDestPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpRXDTPDestPresentStr Dz1InetFtpRXDTPDestPresentStrW
#define Dz1InetFtpRXDTPDestPresentFromStr Dz1InetFtpRXDTPDestPresentFromStrW
#else // UNICODE
#define Dz1InetFtpRXDTPDestPresentStr Dz1InetFtpRXDTPDestPresentStrA
#define Dz1InetFtpRXDTPDestPresentFromStr Dz1InetFtpRXDTPDestPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpRXDTPDestPresentStr Dz1InetFtpRXDTPDestPresentStrA
#define Dz1InetFtpRXDTPDestPresentFromStr Dz1InetFtpRXDTPDestPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpRXDTPDestPresent *Dz1InetFtpRXDTPDestPresent_new(Dz1InetFtpRXDTPDestPresent *src, Dz1Error *err);
static __inline__ Dz1InetFtpRXDTPDestPresent *Dz1InetFtpRXDTPDestPresent_gen(Dz1Error *err) { Dz1InetFtpRXDTPDestPresent v = Dz1InetFtpRXDTPDestPresent_max; return Dz1InetFtpRXDTPDestPresent_new(&v, err); }
static __inline__ void Dz1InetFtpRXDTPDestPresent_del(Dz1InetFtpRXDTPDestPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpRXDTPDestPresent_delAndSetNull(void *ptr)
{
	Dz1InetFtpRXDTPDestPresent **p = (Dz1InetFtpRXDTPDestPresent **)ptr;
	if (p != NULL) { Dz1InetFtpRXDTPDestPresent_del(*p); *p = NULL; }
}
// Dz1InetFtpRXDTPDestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPDest
typedef struct Dz1InetFtpRXDTPDest
{
	Dz1InetFtpRXDTPDestPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		FILE				*fp;
		DataFragmentList	*list;
	} x;
} Dz1InetFtpRXDTPDest;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpRXDTPDest *Dz1InetFtpRXDTPDest_new(Dz1InetFtpRXDTPDestPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpRXDTPDest *Dz1InetFtpRXDTPDest_gen(Dz1Error *err) { return Dz1InetFtpRXDTPDest_new(Dz1InetFtpRXDTPDestPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRXDTPDest_purge(Dz1InetFtpRXDTPDest *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRXDTPDest_del(Dz1InetFtpRXDTPDest *p);
static __inline__ void Dz1InetFtpRXDTPDest_delAndSetNull(void *ptr)
{
	Dz1InetFtpRXDTPDest **p = (Dz1InetFtpRXDTPDest **)ptr;
	if (p != NULL) { Dz1InetFtpRXDTPDest_del(*p); *p = NULL; }
}
// Dz1InetFtpRXDTPDest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPArg
typedef struct Dz1InetFtpRXDTPArg
{
	void					*tFTP;
	Dz1InetFtpDTPSpec		*spec;
	Dz1InetFtpTransfer		*job;
} Dz1InetFtpRXDTPArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpRXDTPArg *Dz1InetFtpRXDTPArg_new(void *tFTP, 
																   Dz1InetFtpDTPSpec *spec_ref, 
																   Dz1InetFtpTransfer *job_ref, Dz1Error *err);
static __inline__ Dz1InetFtpRXDTPArg *Dz1InetFtpRXDTPArg_gen(Dz1Error *err) { return Dz1InetFtpRXDTPArg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRXDTPArg_purge(Dz1InetFtpRXDTPArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRXDTPArg_del(Dz1InetFtpRXDTPArg *p);
static __inline__ void Dz1InetFtpRXDTPArg_delAndSetNull(void *ptr)
{
	Dz1InetFtpRXDTPArg **p = (Dz1InetFtpRXDTPArg **)ptr;
	if (p) { Dz1InetFtpRXDTPArg_del(*p); *p = NULL; }
}
// Dz1InetFtpRXDTPArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTXDTPArg
typedef struct Dz1InetFtpTXDTPArg
{
	void					*tFTP;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1InetFtpDTPSpec		*spec;
	Dz1InetFtpTransfer		*job;
} Dz1InetFtpTXDTPArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTXDTPArg *Dz1InetFtpTXDTPArg_new(void *tFTP, 
																   Dz1SockAddr *peer, 
																   Dz1SockAddr *local, 
																   Dz1TcpClientSocket *sock_ref, 
																   Dz1InetFtpDTPSpec *spec_ref, 
																   Dz1InetFtpTransfer *job_ref, Dz1Error *err);
static __inline__ Dz1InetFtpTXDTPArg *Dz1InetFtpTXDTPArg_gen(Dz1Error *err) { return Dz1InetFtpTXDTPArg_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTXDTPArg_purge(Dz1InetFtpTXDTPArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTXDTPArg_del(Dz1InetFtpTXDTPArg *p);
static __inline__ void Dz1InetFtpTXDTPArg_delAndSetNull(void *ptr)
{
	Dz1InetFtpTXDTPArg **p = (Dz1InetFtpTXDTPArg **)ptr;
	if (p) { Dz1InetFtpTXDTPArg_del(*p); *p = NULL; }
}
// Dz1InetFtpTXDTPArg
////////////////////////////////////////////////////////////////////////////////

#endif
