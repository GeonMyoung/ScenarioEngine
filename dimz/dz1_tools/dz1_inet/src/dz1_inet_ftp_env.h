#ifndef _DZ1_TDC_DZ1_INET_FTP_ENV_H_
#define _DZ1_TDC_DZ1_INET_FTP_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_def.h"
#include "dz1_inet_ftp_control_pi_msg.h"
#include "dz1_fsm2.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPSpec
typedef struct Dz1InetFtpDTPSpec
{
	Dz1InetFtpDTPType		*type;
	Dz1InetFtpDTPStruct		 stru;
	Dz1InetFtpDTPMode		 mode;
} Dz1InetFtpDTPSpec;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPSpec *Dz1InetFtpDTPSpec_new(Dz1InetFtpDTPType *type, 
																 Dz1InetFtpDTPStruct stru, 
																 Dz1InetFtpDTPMode mode, Dz1Error *err);
static __inline__ Dz1InetFtpDTPSpec *Dz1InetFtpDTPSpec_gen(Dz1Error *err) { return Dz1InetFtpDTPSpec_new(NULL, Dz1InetFtpDTPStruct_max, Dz1InetFtpDTPMode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPSpec_purge(Dz1InetFtpDTPSpec *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPSpec_del(Dz1InetFtpDTPSpec *p);
static __inline__ void Dz1InetFtpDTPSpec_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPSpec **p = (Dz1InetFtpDTPSpec **)ptr;
	if (p) { Dz1InetFtpDTPSpec_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPSpec_dump(Dz1InetFtpDTPSpec *p, int tab);
// Dz1InetFtpDTPSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathNode
struct Dz1InetFtpPathNode;

typedef struct Dz1InetFtpPathNode
{
	struct Dz1InetFtpPathNode		*next;
	str_t							 path;
} Dz1InetFtpPathNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpPathNode *Dz1InetFtpPathNode_new(str_t path, Dz1Error *err);
static __inline__ Dz1InetFtpPathNode *Dz1InetFtpPathNode_gen(Dz1Error *err) { return Dz1InetFtpPathNode_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathNode_purge(Dz1InetFtpPathNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathNode_del(Dz1InetFtpPathNode *p);
static __inline__ void Dz1InetFtpPathNode_delAndSetNull(void *ptr)
{
	Dz1InetFtpPathNode **p = (Dz1InetFtpPathNode **)ptr;
	if (p) { Dz1InetFtpPathNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathNode_dump(Dz1InetFtpPathNode *p, int tab);
// Dz1InetFtpPathNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathList
typedef struct Dz1InetFtpPathList
{
	Dz1InetFtpPathNode		*head;
	Dz1InetFtpPathNode		*tail;
} Dz1InetFtpPathList;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpPathList *Dz1InetFtpPathList_new(Dz1Error *err);
static __inline__ Dz1InetFtpPathList *Dz1InetFtpPathList_gen(Dz1Error *err) { return Dz1InetFtpPathList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathList_purge(Dz1InetFtpPathList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathList_del(Dz1InetFtpPathList *p);
static __inline__ void Dz1InetFtpPathList_delAndSetNull(void *ptr)
{
	Dz1InetFtpPathList **p = (Dz1InetFtpPathList **)ptr;
	if (p) { Dz1InetFtpPathList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathList_dump(Dz1InetFtpPathList *p, int tab);
// Dz1InetFtpPathList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathInfo
typedef struct Dz1InetFtpPathInfo
{
	Dz1InetFtpPathList		*list;
	Dz1InetFtpPathNode		*current;
} Dz1InetFtpPathInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpPathInfo *Dz1InetFtpPathInfo_new(Dz1Error *err);
static __inline__ Dz1InetFtpPathInfo *Dz1InetFtpPathInfo_gen(Dz1Error *err) { return Dz1InetFtpPathInfo_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathInfo_purge(Dz1InetFtpPathInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathInfo_del(Dz1InetFtpPathInfo *p);
static __inline__ void Dz1InetFtpPathInfo_delAndSetNull(void *ptr)
{
	Dz1InetFtpPathInfo **p = (Dz1InetFtpPathInfo **)ptr;
	if (p) { Dz1InetFtpPathInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpPathInfo_dump(Dz1InetFtpPathInfo *p, int tab);
// Dz1InetFtpPathInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferNode
struct Dz1InetFtpTransferNode;

typedef struct Dz1InetFtpTransferNode
{
	struct Dz1InetFtpTransferNode		*next;
	Dz1InetFtpTransfer					*target;
	Dz1InetFtpPathInfo					*pathInfo;
} Dz1InetFtpTransferNode;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransferNode *Dz1InetFtpTransferNode_new(Dz1InetFtpTransfer *target_ref, Dz1Error *err);
static __inline__ Dz1InetFtpTransferNode *Dz1InetFtpTransferNode_gen(Dz1Error *err) { return Dz1InetFtpTransferNode_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferNode_purge(Dz1InetFtpTransferNode *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferNode_del(Dz1InetFtpTransferNode *p);
static __inline__ void Dz1InetFtpTransferNode_delAndSetNull(void *ptr)
{
	Dz1InetFtpTransferNode **p = (Dz1InetFtpTransferNode **)ptr;
	if (p) { Dz1InetFtpTransferNode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferNode_dump(Dz1InetFtpTransferNode *p, int tab);
// Dz1InetFtpTransferNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferJobs
typedef struct Dz1InetFtpTransferJobs
{
	Dz1InetFtpTransferNode		*head;
	Dz1InetFtpTransferNode		*tail;
} Dz1InetFtpTransferJobs;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransferJobs *Dz1InetFtpTransferJobs_new(Dz1Error *err);
static __inline__ Dz1InetFtpTransferJobs *Dz1InetFtpTransferJobs_gen(Dz1Error *err) { return Dz1InetFtpTransferJobs_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferJobs_purge(Dz1InetFtpTransferJobs *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferJobs_del(Dz1InetFtpTransferJobs *p);
static __inline__ void Dz1InetFtpTransferJobs_delAndSetNull(void *ptr)
{
	Dz1InetFtpTransferJobs **p = (Dz1InetFtpTransferJobs **)ptr;
	if (p) { Dz1InetFtpTransferJobs_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferJobs_dump(Dz1InetFtpTransferJobs *p, int tab);
// Dz1InetFtpTransferJobs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpSession
typedef struct Dz1InetFtpSession
{
	Dz1SockAddr					*peer;
	Dz1SockAddr					*local;
	Dz1TcpClientSocket			*sock;
	u32_t						 rcvr;
	str_t						 user;
	str_t						 password;
	str_t						 account;
	bool_t						 isPassive;
	str_t						 remoteCharSetName;
	Dz1TcpServerSocket			*portSock;
	Dz1TcpClientSocket			*dataSock;
	Dz1InetFtpTransferJobs		*jobs;
	Dz1InetFtpTransferNode		*curJob;
	Dz1InetFtpCmdResult			 curStatus;
	Dz1Fsm2						*fsm;
	Dz1InetFtpDTPSpec			*dtpSpec;
	u32_t						 dtp;
	Dz1InetFtpFileDoneInform	 fileDone;
	void						*fileDoneParam;
	void						*sg;
} Dz1InetFtpSession;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpSession *Dz1InetFtpSession_new(Dz1SockAddr *peer, 
																 Dz1SockAddr *local, 
																 Dz1TcpClientSocket *sock, 
																 u32_t rcvr, 
																 str_t user, 
																 str_t password, 
																 str_t account, 
																 bool_t isPassive, 
																 str_t remoteCharSetName, 
																 Dz1InetFtpDTPSpec *dtpSpec, 
																 u32_t dtp, 
																 Dz1InetFtpFileDoneInform fileDone, 
																 void *fileDoneParam, 
																 void *sg, Dz1Error *err);
static __inline__ Dz1InetFtpSession *Dz1InetFtpSession_gen(Dz1Error *err) { return Dz1InetFtpSession_new(NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, NULL, NULL, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSession_purge(Dz1InetFtpSession *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSession_del(Dz1InetFtpSession *p);
static __inline__ void Dz1InetFtpSession_delAndSetNull(void *ptr)
{
	Dz1InetFtpSession **p = (Dz1InetFtpSession **)ptr;
	if (p) { Dz1InetFtpSession_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSession_dump(Dz1InetFtpSession *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1InetFtpSession_cmp(Dz1InetFtpSession *a, Dz1InetFtpSession *b); 
// Dz1InetFtpSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpSessionList
typedef struct Dz1InetFtpSessionList
{
	void *storage;
	unsigned int (*count)(struct Dz1InetFtpSessionList *p);
	Dz1Error (*travel)(struct Dz1InetFtpSessionList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpSession *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1InetFtpSessionList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpSession *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1InetFtpSessionList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpSession *entry), void *ptr);
	Dz1InetFtpSession **(*get_array)(struct Dz1InetFtpSessionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1InetFtpSessionList *p, Dz1InetFtpSession *data);
	bool_t (*remove)(struct Dz1InetFtpSessionList *p, Dz1InetFtpSession *key);
	Dz1InetFtpSession *(*extract)(struct Dz1InetFtpSessionList *p, Dz1InetFtpSession *key);
	Dz1InetFtpSession *(*find)(struct Dz1InetFtpSessionList *p, Dz1InetFtpSession *key);
	int (*cmp)(Dz1InetFtpSession *a, Dz1InetFtpSession *b);
} Dz1InetFtpSessionList;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpSessionList *Dz1InetFtpSessionList_new(Dz1Error *err);
static __inline__ Dz1InetFtpSessionList *Dz1InetFtpSessionList_gen(Dz1Error *err) { return Dz1InetFtpSessionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSessionList_purge(Dz1InetFtpSessionList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSessionList_del(Dz1InetFtpSessionList *p);
static __inline__ void Dz1InetFtpSessionList_delAndSetNull(void *ptr)
{
	Dz1InetFtpSessionList **p = (Dz1InetFtpSessionList **)ptr;
	if (p != NULL) { Dz1InetFtpSessionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpSessionList_dump(Dz1InetFtpSessionList *p, int tab);

// Dz1InetFtpSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpEnv
typedef struct Dz1InetFtpEnv
{
	void						*tSelf;
	Dz1InetFtpSessionList		*sessionList;
} Dz1InetFtpEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpEnv *Dz1InetFtpEnv_new(void *tSelf, Dz1Error *err);
static __inline__ Dz1InetFtpEnv *Dz1InetFtpEnv_gen(Dz1Error *err) { return Dz1InetFtpEnv_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpEnv_purge(Dz1InetFtpEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpEnv_del(Dz1InetFtpEnv *p);
static __inline__ void Dz1InetFtpEnv_delAndSetNull(void *ptr)
{
	Dz1InetFtpEnv **p = (Dz1InetFtpEnv **)ptr;
	if (p) { Dz1InetFtpEnv_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpEnv_dump(Dz1InetFtpEnv *p, int tab);
// Dz1InetFtpEnv
////////////////////////////////////////////////////////////////////////////////

#endif
