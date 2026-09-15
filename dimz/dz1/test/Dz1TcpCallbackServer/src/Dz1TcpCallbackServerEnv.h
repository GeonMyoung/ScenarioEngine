#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_ENV_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_ENV_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackServerDef.h"


typedef enum Dz1TcpCallbackSessionLife
{
	Dz1TcpCallbackSessionLife_immediateDie,
	Dz1TcpCallbackSessionLife_negotiateAndDie,
	Dz1TcpCallbackSessionLife_tenSeconds,
	Dz1TcpCallbackSessionLife_halfHour,
	Dz1TcpCallbackSessionLife_immotal0,
	Dz1TcpCallbackSessionLife_immotal1,
	Dz1TcpCallbackSessionLife_immotal2,
	Dz1TcpCallbackSessionLife_immotal3,
	Dz1TcpCallbackSessionLife_immotal4,
	Dz1TcpCallbackSessionLife_max
} Dz1TcpCallbackSessionLife;

DZ1_CPPLINK str_t Dz1TcpCallbackSessionLifeStrA(Dz1TcpCallbackSessionLife v);
DZ1_CPPLINK Dz1TcpCallbackSessionLife Dz1TcpCallbackSessionLifeFromStrA(str_t str);

DZ1_CPPLINK wstr_t Dz1TcpCallbackSessionLifeStrW(Dz1TcpCallbackSessionLife v);
DZ1_CPPLINK Dz1TcpCallbackSessionLife Dz1TcpCallbackSessionLifeFromStrW(wstr_t str);

#ifdef UNICODE
#define Dz1TcpCallbackSessionLifeStr Dz1TcpCallbackSessionLifeStrW
#define Dz1TcpCallbackSessionLifeFromStr Dz1TcpCallbackSessionLifeFromStrW
#else // UNICODE
#define Dz1TcpCallbackSessionLifeStr Dz1TcpCallbackSessionLifeStrA
#define Dz1TcpCallbackSessionLifeFromStr Dz1TcpCallbackSessionLifeFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackSessionLife *Dz1TcpCallbackSessionLife_new(Dz1TcpCallbackSessionLife *src, Dz1Error *err);
static __inline__ Dz1TcpCallbackSessionLife *Dz1TcpCallbackSessionLife_gen(Dz1Error *err) { Dz1TcpCallbackSessionLife v = Dz1TcpCallbackSessionLife_max; return Dz1TcpCallbackSessionLife_new(&v, err); }
#define Dz1TcpCallbackSessionLife_del               Dz1u32_del
#define Dz1TcpCallbackSessionLife_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSessionLife_dump(Dz1TcpCallbackSessionLife *v, int tab);


typedef struct Dz1TcpCallbackSession
{
	Dz1SockAddr        *peer;
	Dz1SockAddr        *local;
	Dz1TcpClientSocket *sock;
	Dz1SocketBuf       *rx_buf;
	Dz1SocketFifo      *tx_fifo;
} Dz1TcpCallbackSession;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackSession *Dz1TcpCallbackSession_new(Dz1SockAddr *peer, 
																		 Dz1SockAddr *local, 
																		 Dz1TcpClientSocket *sock, 
																		 Dz1SocketBuf *rx_buf, 
																		 Dz1SocketFifo *tx_fifo, Dz1Error *err);
static __inline__ Dz1TcpCallbackSession *Dz1TcpCallbackSession_gen(Dz1Error *err) { return Dz1TcpCallbackSession_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSession_del(Dz1TcpCallbackSession *p);
static __inline__ void Dz1TcpCallbackSession_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackSession **p = (Dz1TcpCallbackSession **)ptr;
	Dz1TcpCallbackSession_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSession_dump(Dz1TcpCallbackSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpCallbackSession_cmp(Dz1TcpCallbackSession *a, Dz1TcpCallbackSession *b);


typedef struct Dz1TcpCallbackSessionList
{
	void *storage;
	Dz1Error (*add)(struct Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *data);
	void (*remove)(struct Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key);
	Dz1TcpCallbackSession *(*extract)(struct Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key);
	Dz1TcpCallbackSession **(*get_array)(struct Dz1TcpCallbackSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*travel)(struct Dz1TcpCallbackSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpCallbackSession *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TcpCallbackSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpCallbackSession *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TcpCallbackSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpCallbackSession *entry), void *ptr);
	Dz1TcpCallbackSession *(*find)(struct Dz1TcpCallbackSessionList *p, Dz1TcpCallbackSession *key);
	int (*cmp)(Dz1TcpCallbackSession *a, Dz1TcpCallbackSession *b);
	unsigned int (*count)(struct Dz1TcpCallbackSessionList *p);
} Dz1TcpCallbackSessionList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackSessionList *Dz1TcpCallbackSessionList_new(Dz1Error *err);
static __inline__ Dz1TcpCallbackSessionList *Dz1TcpCallbackSessionList_gen(Dz1Error *err) { return Dz1TcpCallbackSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSessionList_del(Dz1TcpCallbackSessionList *p);
static __inline__ void Dz1TcpCallbackSessionList_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackSessionList **p = (Dz1TcpCallbackSessionList **)ptr;
	Dz1TcpCallbackSessionList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSessionList_dump(Dz1TcpCallbackSessionList *p, int tab);


typedef struct Dz1TcpCallbackServerEnv
{
	void                      *tSelf;
	u32_t                      acceptor;
	u32_t                      acceptor_ssl;
	Dz1TcpCallbackSessionList *sessions;
	Dz1TimeVal                 tLast;
	u64_t                      tx_amt;
	u64_t                      rx_amt;
} Dz1TcpCallbackServerEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerEnv *Dz1TcpCallbackServerEnv_new(void *tSelf, 
																			 u32_t acceptor, 
																			 u32_t acceptor_ssl, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerEnv *Dz1TcpCallbackServerEnv_gen(Dz1Error *err) { return Dz1TcpCallbackServerEnv_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerEnv_del(Dz1TcpCallbackServerEnv *p);
static __inline__ void Dz1TcpCallbackServerEnv_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerEnv **p = (Dz1TcpCallbackServerEnv **)ptr;
	Dz1TcpCallbackServerEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerEnv_dump(Dz1TcpCallbackServerEnv *p, int tab);

#endif
