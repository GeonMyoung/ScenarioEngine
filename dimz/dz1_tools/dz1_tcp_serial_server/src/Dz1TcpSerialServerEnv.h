#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_ENV_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_ENV_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"


typedef struct Dz1TcpSerialServerPresetPort
{
	u32_t  presetPortNum;
	u32_t  thid;
} Dz1TcpSerialServerPresetPort;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPresetPort *Dz1TcpSerialServerPresetPort_new(u32_t presetPortNum, u32_t thid, Dz1Error *err);
static __inline__ Dz1TcpSerialServerPresetPort *Dz1TcpSerialServerPresetPort_gen(Dz1Error *err) { return Dz1TcpSerialServerPresetPort_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetPort_del(Dz1TcpSerialServerPresetPort *p);
static __inline__ void Dz1TcpSerialServerPresetPort_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerPresetPort **p = (Dz1TcpSerialServerPresetPort **)ptr;
	Dz1TcpSerialServerPresetPort_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetPort_dump(Dz1TcpSerialServerPresetPort *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialServerPresetPort_cmp(Dz1TcpSerialServerPresetPort *a, Dz1TcpSerialServerPresetPort *b);


typedef struct Dz1TcpSerialServerPresetPortList
{
	void *storage;
	Dz1Error (*add)(struct Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *data);
	void (*remove)(struct Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key);
	Dz1TcpSerialServerPresetPort *(*extract)(struct Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key);
	Dz1TcpSerialServerPresetPort **(*get_array)(struct Dz1TcpSerialServerPresetPortList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*travel)(struct Dz1TcpSerialServerPresetPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPresetPort *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TcpSerialServerPresetPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPresetPort *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TcpSerialServerPresetPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPresetPort *entry), void *ptr);
	Dz1TcpSerialServerPresetPort *(*find)(struct Dz1TcpSerialServerPresetPortList *p, Dz1TcpSerialServerPresetPort *key);
	int (*cmp)(Dz1TcpSerialServerPresetPort *a, Dz1TcpSerialServerPresetPort *b);
	unsigned int (*count)(struct Dz1TcpSerialServerPresetPortList *p);
} Dz1TcpSerialServerPresetPortList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPresetPortList *Dz1TcpSerialServerPresetPortList_new(Dz1Error *err);
static __inline__ Dz1TcpSerialServerPresetPortList *Dz1TcpSerialServerPresetPortList_gen(Dz1Error *err) { return Dz1TcpSerialServerPresetPortList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetPortList_del(Dz1TcpSerialServerPresetPortList *p);
static __inline__ void Dz1TcpSerialServerPresetPortList_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerPresetPortList **p = (Dz1TcpSerialServerPresetPortList **)ptr;
	Dz1TcpSerialServerPresetPortList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetPortList_dump(Dz1TcpSerialServerPresetPortList *p, int tab);


typedef struct Dz1TcpSerialServerSerialArg
{
	u32_t        dstQueueID;
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpSerialServerSerialArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerSerialArg *Dz1TcpSerialServerSerialArg_new(u32_t dstQueueID, 
																					 Dz1SockAddr *peer, 
																					 Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1TcpSerialServerSerialArg *Dz1TcpSerialServerSerialArg_gen(Dz1Error *err) { return Dz1TcpSerialServerSerialArg_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSerialArg_del(Dz1TcpSerialServerSerialArg *p);
static __inline__ void Dz1TcpSerialServerSerialArg_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSerialArg **p = (Dz1TcpSerialServerSerialArg **)ptr;
	Dz1TcpSerialServerSerialArg_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSerialArg_dump(Dz1TcpSerialServerSerialArg *p, int tab);

typedef struct Dz1TcpSerialServerSerial
{
	s32_t                        port;
	void                        *io;
	Dz1TcpSerialServerSerialArg *ioArg;
} Dz1TcpSerialServerSerial;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerSerial *Dz1TcpSerialServerSerial_new(s32_t port, 
																			   void *io, 
																			   Dz1TcpSerialServerSerialArg *ioArg, Dz1Error *err);
static __inline__ Dz1TcpSerialServerSerial *Dz1TcpSerialServerSerial_gen(Dz1Error *err) { return Dz1TcpSerialServerSerial_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSerial_del(Dz1TcpSerialServerSerial *p);
static __inline__ void Dz1TcpSerialServerSerial_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSerial **p = (Dz1TcpSerialServerSerial **)ptr;
	Dz1TcpSerialServerSerial_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSerial_dump(Dz1TcpSerialServerSerial *p, int tab);

typedef struct Dz1TcpSerialServerSession
{
	Dz1SockAddr              *peer;
	Dz1SockAddr              *local;
	Dz1TcpClientSocket       *sock;
	Dz1SocketBuf             *rxBuf;
	Dz1SocketFifo2           *txFifo;
	bool_t                    isPresetPort;
	Dz1TcpSerialServerSerial *serial;
} Dz1TcpSerialServerSession;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerSession *Dz1TcpSerialServerSession_new(Dz1SockAddr *peer, 
																				 Dz1SockAddr *local, 
																				 Dz1TcpClientSocket *sock, 
																				 Dz1SocketBuf *rxBuf, 
																				 Dz1SocketFifo2 *txFifo, 
																				 bool_t isPresetPort, Dz1Error *err);
static __inline__ Dz1TcpSerialServerSession *Dz1TcpSerialServerSession_gen(Dz1Error *err) { return Dz1TcpSerialServerSession_new(NULL, NULL, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSession_del(Dz1TcpSerialServerSession *p);
static __inline__ void Dz1TcpSerialServerSession_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSession **p = (Dz1TcpSerialServerSession **)ptr;
	Dz1TcpSerialServerSession_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSession_dump(Dz1TcpSerialServerSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialServerSession_cmp(Dz1TcpSerialServerSession *a, Dz1TcpSerialServerSession *b);


typedef struct Dz1TcpSerialServerSessionList
{
	void *storage;
	Dz1Error (*add)(struct Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *data);
	void (*remove)(struct Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key);
	Dz1TcpSerialServerSession *(*extract)(struct Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key);
	Dz1TcpSerialServerSession **(*get_array)(struct Dz1TcpSerialServerSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*travel)(struct Dz1TcpSerialServerSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerSession *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TcpSerialServerSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerSession *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TcpSerialServerSessionList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerSession *entry), void *ptr);
	Dz1TcpSerialServerSession *(*find)(struct Dz1TcpSerialServerSessionList *p, Dz1TcpSerialServerSession *key);
	int (*cmp)(Dz1TcpSerialServerSession *a, Dz1TcpSerialServerSession *b);
	unsigned int (*count)(struct Dz1TcpSerialServerSessionList *p);
} Dz1TcpSerialServerSessionList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerSessionList *Dz1TcpSerialServerSessionList_new(Dz1Error *err);
static __inline__ Dz1TcpSerialServerSessionList *Dz1TcpSerialServerSessionList_gen(Dz1Error *err) { return Dz1TcpSerialServerSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSessionList_del(Dz1TcpSerialServerSessionList *p);
static __inline__ void Dz1TcpSerialServerSessionList_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerSessionList **p = (Dz1TcpSerialServerSessionList **)ptr;
	Dz1TcpSerialServerSessionList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerSessionList_dump(Dz1TcpSerialServerSessionList *p, int tab);


typedef struct Dz1TcpSerialServerEnv
{
	void                             *tSelf;
	u32_t                             emulator;
	Dz1TcpSerialServerPresetPortList *presets;
	Dz1TcpSerialServerSessionList    *sessions;
} Dz1TcpSerialServerEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerEnv *Dz1TcpSerialServerEnv_new(void *tSelf, u32_t emulator, Dz1Error *err);
static __inline__ Dz1TcpSerialServerEnv *Dz1TcpSerialServerEnv_gen(Dz1Error *err) { return Dz1TcpSerialServerEnv_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerEnv_del(Dz1TcpSerialServerEnv *p);
static __inline__ void Dz1TcpSerialServerEnv_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerEnv **p = (Dz1TcpSerialServerEnv **)ptr;
	Dz1TcpSerialServerEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerEnv_dump(Dz1TcpSerialServerEnv *p, int tab);

#endif
