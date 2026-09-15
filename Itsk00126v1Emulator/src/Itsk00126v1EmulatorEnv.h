#ifndef _DZ1_TDC_ITSK00126V1_EMULATOR_ENV_H_
#define _DZ1_TDC_ITSK00126V1_EMULATOR_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorDef.h"
#include "Dz1SockUtilDef.h"
#include "Dz1JsonDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ClientSession
typedef struct Itsk00126v1ClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v1ClientSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ClientSession *Itsk00126v1ClientSession_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v1ClientSession *Itsk00126v1ClientSession_gen(Dz1Error *err) { return Itsk00126v1ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_purge(Itsk00126v1ClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_del(Itsk00126v1ClientSession *p);
static __inline__ void Itsk00126v1ClientSession_delAndSetNull(void *ptr)
{
	Itsk00126v1ClientSession **p = (Itsk00126v1ClientSession **)ptr;
	if (p) { Itsk00126v1ClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ClientSession_dump(Itsk00126v1ClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v1ClientSession_cmp(Itsk00126v1ClientSession *a, Itsk00126v1ClientSession *b); 
// Itsk00126v1ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ServerSession
typedef struct Itsk00126v1ServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} Itsk00126v1ServerSession;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ServerSession *Itsk00126v1ServerSession_new(u32_t acceptor, 
																			   Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ Itsk00126v1ServerSession *Itsk00126v1ServerSession_gen(Dz1Error *err) { return Itsk00126v1ServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_purge(Itsk00126v1ServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_del(Itsk00126v1ServerSession *p);
static __inline__ void Itsk00126v1ServerSession_delAndSetNull(void *ptr)
{
	Itsk00126v1ServerSession **p = (Itsk00126v1ServerSession **)ptr;
	if (p) { Itsk00126v1ServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ServerSession_dump(Itsk00126v1ServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Itsk00126v1ServerSession_cmp(Itsk00126v1ServerSession *a, Itsk00126v1ServerSession *b); 
// Itsk00126v1ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1SessionPresent
typedef enum Itsk00126v1SessionPresent
{
	Itsk00126v1SessionPresent_client,
	Itsk00126v1SessionPresent_server,
	Itsk00126v1SessionPresent_max
} Itsk00126v1SessionPresent;

DZ1_CPPLINK str_t Itsk00126v1SessionPresentStrA(Itsk00126v1SessionPresent v);
DZ1_CPPLINK Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1SessionPresentStrW(Itsk00126v1SessionPresent v);
DZ1_CPPLINK Itsk00126v1SessionPresent Itsk00126v1SessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrW
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrW
#else // UNICODE
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrA
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1SessionPresentStr Itsk00126v1SessionPresentStrA
#define Itsk00126v1SessionPresentFromStr Itsk00126v1SessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1SessionPresent *Itsk00126v1SessionPresent_new(Itsk00126v1SessionPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1SessionPresent *Itsk00126v1SessionPresent_gen(Dz1Error *err) { Itsk00126v1SessionPresent v = Itsk00126v1SessionPresent_max; return Itsk00126v1SessionPresent_new(&v, err); }
static __inline__ void Itsk00126v1SessionPresent_del(Itsk00126v1SessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1SessionPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1SessionPresent **p = (Itsk00126v1SessionPresent **)ptr;
	if (p != NULL) { Itsk00126v1SessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1SessionPresent_dump(Itsk00126v1SessionPresent *v, int tab);
// Itsk00126v1SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Session
typedef struct Itsk00126v1Session
{
	Itsk00126v1SessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v1ClientSession	*client;
		Itsk00126v1ServerSession	*server;
	} x;
} Itsk00126v1Session;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Session *Itsk00126v1Session_new(Itsk00126v1SessionPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1Session *Itsk00126v1Session_gen(Dz1Error *err) { return Itsk00126v1Session_new(Itsk00126v1SessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_purge(Itsk00126v1Session *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_del(Itsk00126v1Session *p);
static __inline__ void Itsk00126v1Session_delAndSetNull(void *ptr)
{
	Itsk00126v1Session **p = (Itsk00126v1Session **)ptr;
	if (p != NULL) { Itsk00126v1Session_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Session_dump(Itsk00126v1Session *p, int tab);
// Itsk00126v1Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorEnv
typedef struct Itsk00126V1EmulatorEnv
{
	void					*tSelf;
	Dz1JsonSpec				*spec;
	Itsk00126v1Session		*session;
	Dz1Str					 local_center_id;
} Itsk00126V1EmulatorEnv;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1EmulatorEnv *Itsk00126V1EmulatorEnv_new(void *tSelf, 
																		   Dz1JsonSpec *spec, Dz1Error *err);
static __inline__ Itsk00126V1EmulatorEnv *Itsk00126V1EmulatorEnv_gen(Dz1Error *err) { return Itsk00126V1EmulatorEnv_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorEnv_purge(Itsk00126V1EmulatorEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorEnv_del(Itsk00126V1EmulatorEnv *p);
static __inline__ void Itsk00126V1EmulatorEnv_delAndSetNull(void *ptr)
{
	Itsk00126V1EmulatorEnv **p = (Itsk00126V1EmulatorEnv **)ptr;
	if (p) { Itsk00126V1EmulatorEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorEnv_dump(Itsk00126V1EmulatorEnv *p, int tab);
// Itsk00126V1EmulatorEnv
////////////////////////////////////////////////////////////////////////////////

#endif
