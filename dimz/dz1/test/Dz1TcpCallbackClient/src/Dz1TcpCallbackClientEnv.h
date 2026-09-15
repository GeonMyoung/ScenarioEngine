#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_ENV_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_CLIENT_ENV_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackClientDef.h"

typedef enum Dz1TcpCallbackSessionLife
{
	Dz1TcpCallbackSessionLife_immediateDie,
	Dz1TcpCallbackSessionLife_negotiationAndDie,
	Dz1TcpCallbackSessionLife_sendAndDie,
	Dz1TcpCallbackSessionLife_tenSecond,
	Dz1TcpCallbackSessionLife_halfHour,
	Dz1TcpCallbackSessionLife_immotal0,
	Dz1TcpCallbackSessionLife_immotal1,
	Dz1TcpCallbackSessionLife_immotal2,
	Dz1TcpCallbackSessionLife_immotal3,
	Dz1TcpCallbackSessionLife_immotal4,
	Dz1TcpCallbackSessionLife_immotal5,
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
	u32_t               echoID;
} Dz1TcpCallbackSession;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackSession *Dz1TcpCallbackSession_new(Dz1SockAddr *peer, 
																		 Dz1SockAddr *local, 
																		 Dz1TcpClientSocket *sock, 
																		 Dz1SocketBuf *rx_buf, 
																		 Dz1SocketFifo *tx_fifo, Dz1Error *err);
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
	Dz1TcpCallbackSession *(*getHead)(struct Dz1TcpCallbackSessionList *p);
	unsigned int (*count)(struct Dz1TcpCallbackSessionList *p);
} Dz1TcpCallbackSessionList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackSessionList *Dz1TcpCallbackSessionList_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSessionList_del(Dz1TcpCallbackSessionList *p);
static __inline__ void Dz1TcpCallbackSessionList_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackSessionList **p = (Dz1TcpCallbackSessionList **)ptr;
	Dz1TcpCallbackSessionList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackSessionList_dump(Dz1TcpCallbackSessionList *p, int tab);

typedef struct Dz1TcpCallbackClientCmd
{
	Dz1SockAddr *server_addr;
	u32_t        max_conn;
	bool_t       use_ssl;
	bool_t       stress_mode;
} Dz1TcpCallbackClientCmd;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientCmd *Dz1TcpCallbackClientCmd_new(Dz1SockAddr *server_addr, 
																			 u32_t max_conn, 
																			 bool_t use_ssl, 
																			 bool_t stress_mode, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientCmd *Dz1TcpCallbackClientCmd_clone(Dz1TcpCallbackClientCmd *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientCmd_del(Dz1TcpCallbackClientCmd *p);
static __inline__ void Dz1TcpCallbackClientCmd_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientCmd **p = (Dz1TcpCallbackClientCmd **)ptr;
	Dz1TcpCallbackClientCmd_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientCmd_dump(Dz1TcpCallbackClientCmd *p, int tab);

typedef struct Dz1TcpCallbackClientEnv
{
	void                      *tSelf;
	Dz1TcpCallbackSessionList *sessions;
	Dz1TcpCallbackClientCmd   *cmd;
} Dz1TcpCallbackClientEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackClientEnv *Dz1TcpCallbackClientEnv_new(void *tSelf, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientEnv_del(Dz1TcpCallbackClientEnv *p);
static __inline__ void Dz1TcpCallbackClientEnv_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackClientEnv **p = (Dz1TcpCallbackClientEnv **)ptr;
	Dz1TcpCallbackClientEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackClientEnv_dump(Dz1TcpCallbackClientEnv *p, int tab);

#endif
