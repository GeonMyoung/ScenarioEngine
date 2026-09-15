#ifndef _DZ1_TDC_I_T_S_K00144_2_EMULATOR_ENV_H_
#define _DZ1_TDC_I_T_S_K00144_2_EMULATOR_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorDef.h"
#include "Dz1SockUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ClientSession
typedef struct ITSK00144_2ClientSession
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} ITSK00144_2ClientSession;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ClientSession *ITSK00144_2ClientSession_new(Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ ITSK00144_2ClientSession *ITSK00144_2ClientSession_gen(Dz1Error *err) { return ITSK00144_2ClientSession_new(NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_purge(ITSK00144_2ClientSession *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_del(ITSK00144_2ClientSession *p);
static __inline__ void ITSK00144_2ClientSession_delAndSetNull(void *ptr)
{
	ITSK00144_2ClientSession **p = (ITSK00144_2ClientSession **)ptr;
	if (p) { ITSK00144_2ClientSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ClientSession_dump(ITSK00144_2ClientSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK00144_2ClientSession_cmp(ITSK00144_2ClientSession *a, ITSK00144_2ClientSession *b); 
// ITSK00144_2ClientSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ServerSession
typedef struct ITSK00144_2ServerSession
{
	u32_t					 acceptor;
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1ElasticBuf			*rx_buf;
	Dz1Stream				*rx_stream;
	Dz1SockUtilTxFifo		*tx_fifo;
} ITSK00144_2ServerSession;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ServerSession *ITSK00144_2ServerSession_new(u32_t acceptor, 
																			   Dz1SockAddr *peer, 
																			   Dz1SockAddr *local, 
																			   Dz1TcpClientSocket *sock, 
																			   Dz1ElasticBuf *rx_buf, 
																			   Dz1Stream *rx_stream, 
																			   Dz1SockUtilTxFifo *tx_fifo, Dz1Error *err);
static __inline__ ITSK00144_2ServerSession *ITSK00144_2ServerSession_gen(Dz1Error *err) { return ITSK00144_2ServerSession_new(0, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_purge(ITSK00144_2ServerSession *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_del(ITSK00144_2ServerSession *p);
static __inline__ void ITSK00144_2ServerSession_delAndSetNull(void *ptr)
{
	ITSK00144_2ServerSession **p = (ITSK00144_2ServerSession **)ptr;
	if (p) { ITSK00144_2ServerSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ServerSession_dump(ITSK00144_2ServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ITSK00144_2ServerSession_cmp(ITSK00144_2ServerSession *a, ITSK00144_2ServerSession *b); 
// ITSK00144_2ServerSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2SessionPresent
typedef enum ITSK00144_2SessionPresent
{
	ITSK00144_2SessionPresent_client,
	ITSK00144_2SessionPresent_server,
	ITSK00144_2SessionPresent_max
} ITSK00144_2SessionPresent;

DZ1_CPPLINK str_t ITSK00144_2SessionPresentStrA(ITSK00144_2SessionPresent v);
DZ1_CPPLINK ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2SessionPresentStrW(ITSK00144_2SessionPresent v);
DZ1_CPPLINK ITSK00144_2SessionPresent ITSK00144_2SessionPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrW
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrW
#else // UNICODE
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrA
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2SessionPresentStr ITSK00144_2SessionPresentStrA
#define ITSK00144_2SessionPresentFromStr ITSK00144_2SessionPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2SessionPresent *ITSK00144_2SessionPresent_new(ITSK00144_2SessionPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2SessionPresent *ITSK00144_2SessionPresent_gen(Dz1Error *err) { ITSK00144_2SessionPresent v = ITSK00144_2SessionPresent_max; return ITSK00144_2SessionPresent_new(&v, err); }
static __inline__ void ITSK00144_2SessionPresent_del(ITSK00144_2SessionPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2SessionPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2SessionPresent **p = (ITSK00144_2SessionPresent **)ptr;
	if (p != NULL) { ITSK00144_2SessionPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2SessionPresent_dump(ITSK00144_2SessionPresent *v, int tab);
// ITSK00144_2SessionPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Session
typedef struct ITSK00144_2Session
{
	ITSK00144_2SessionPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2ClientSession	*client;
		ITSK00144_2ServerSession	*server;
	} x;
} ITSK00144_2Session;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Session *ITSK00144_2Session_new(ITSK00144_2SessionPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2Session *ITSK00144_2Session_gen(Dz1Error *err) { return ITSK00144_2Session_new(ITSK00144_2SessionPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_purge(ITSK00144_2Session *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_del(ITSK00144_2Session *p);
static __inline__ void ITSK00144_2Session_delAndSetNull(void *ptr)
{
	ITSK00144_2Session **p = (ITSK00144_2Session **)ptr;
	if (p != NULL) { ITSK00144_2Session_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Session_dump(ITSK00144_2Session *p, int tab);
// ITSK00144_2Session
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorEnv
typedef struct ITSK001442EmulatorEnv
{
	void					*tSelf;
	ITSK00144_2Session		*session;
	u8_t					 received_seq;
	u8_t					 send_seq;
} ITSK001442EmulatorEnv;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442EmulatorEnv *ITSK001442EmulatorEnv_new(void *tSelf, Dz1Error *err);
static __inline__ ITSK001442EmulatorEnv *ITSK001442EmulatorEnv_gen(Dz1Error *err) { return ITSK001442EmulatorEnv_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorEnv_purge(ITSK001442EmulatorEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorEnv_del(ITSK001442EmulatorEnv *p);
static __inline__ void ITSK001442EmulatorEnv_delAndSetNull(void *ptr)
{
	ITSK001442EmulatorEnv **p = (ITSK001442EmulatorEnv **)ptr;
	if (p) { ITSK001442EmulatorEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorEnv_dump(ITSK001442EmulatorEnv *p, int tab);
// ITSK001442EmulatorEnv
////////////////////////////////////////////////////////////////////////////////

#endif
