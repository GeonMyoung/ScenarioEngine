#ifndef _DZ1_TDC_DZ1_INET_FTP_MSGS_H_
#define _DZ1_TDC_DZ1_INET_FTP_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_control_pi_msg.h"
#include "dz1_inet_ftp_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgTransfer
typedef struct Dz1InetFtpMsgTransfer
{
	Dz1SockAddr					*peer;
	str_t						 user;
	str_t						 pass;
	str_t						 account;
	bool_t						 isPassive;
	Dz1InetFtpTransferList		*files;
	Dz1InetFtpFileDoneInform	 fileDone;
	void						*fileDoneParam;
} Dz1InetFtpMsgTransfer;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpMsgTransfer *Dz1InetFtpMsgTransfer_new(Dz1SockAddr *peer, 
																		 str_t user, 
																		 str_t pass, 
																		 str_t account, 
																		 bool_t isPassive, 
																		 Dz1InetFtpTransferList *files, 
																		 Dz1InetFtpFileDoneInform fileDone, 
																		 void *fileDoneParam, Dz1Error *err);
static __inline__ Dz1InetFtpMsgTransfer *Dz1InetFtpMsgTransfer_gen(Dz1Error *err) { return Dz1InetFtpMsgTransfer_new(NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransfer_purge(Dz1InetFtpMsgTransfer *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransfer_del(Dz1InetFtpMsgTransfer *p);
static __inline__ void Dz1InetFtpMsgTransfer_delAndSetNull(void *ptr)
{
	Dz1InetFtpMsgTransfer **p = (Dz1InetFtpMsgTransfer **)ptr;
	if (p) { Dz1InetFtpMsgTransfer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransfer_dump(Dz1InetFtpMsgTransfer *p, int tab);
// Dz1InetFtpMsgTransfer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgTransferArg
typedef struct Dz1InetFtpMsgTransferArg
{
	Dz1InetFtpMsgTransferDoneInform		 cb;
	void								*cbParam;
} Dz1InetFtpMsgTransferArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpMsgTransferArg *Dz1InetFtpMsgTransferArg_new(Dz1InetFtpMsgTransferDoneInform cb, 
																			   void *cbParam, Dz1Error *err);
static __inline__ Dz1InetFtpMsgTransferArg *Dz1InetFtpMsgTransferArg_gen(Dz1Error *err) { return Dz1InetFtpMsgTransferArg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransferArg_purge(Dz1InetFtpMsgTransferArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransferArg_del(Dz1InetFtpMsgTransferArg *p);
static __inline__ void Dz1InetFtpMsgTransferArg_delAndSetNull(void *ptr)
{
	Dz1InetFtpMsgTransferArg **p = (Dz1InetFtpMsgTransferArg **)ptr;
	if (p) { Dz1InetFtpMsgTransferArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgTransferArg_dump(Dz1InetFtpMsgTransferArg *p, int tab);
// Dz1InetFtpMsgTransferArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgFileDone
typedef struct Dz1InetFtpMsgFileDone
{
	Dz1SockAddr		*peer;
	Dz1SockAddr		*local;
} Dz1InetFtpMsgFileDone;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpMsgFileDone *Dz1InetFtpMsgFileDone_new(Dz1SockAddr *peer, 
																		 Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1InetFtpMsgFileDone *Dz1InetFtpMsgFileDone_gen(Dz1Error *err) { return Dz1InetFtpMsgFileDone_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgFileDone_purge(Dz1InetFtpMsgFileDone *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgFileDone_del(Dz1InetFtpMsgFileDone *p);
static __inline__ void Dz1InetFtpMsgFileDone_delAndSetNull(void *ptr)
{
	Dz1InetFtpMsgFileDone **p = (Dz1InetFtpMsgFileDone **)ptr;
	if (p) { Dz1InetFtpMsgFileDone_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpMsgFileDone_dump(Dz1InetFtpMsgFileDone *p, int tab);
// Dz1InetFtpMsgFileDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpBasicMsg
typedef struct Dz1InetFtpBasicMsg
{
	Dz1SockAddr		*peer;
	Dz1SockAddr		*local;
	u32_t			 size;
} Dz1InetFtpBasicMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpBasicMsg *Dz1InetFtpBasicMsg_new(Dz1SockAddr *peer, 
																   Dz1SockAddr *local, 
																   u32_t size, Dz1Error *err);
static __inline__ Dz1InetFtpBasicMsg *Dz1InetFtpBasicMsg_gen(Dz1Error *err) { return Dz1InetFtpBasicMsg_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpBasicMsg_purge(Dz1InetFtpBasicMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpBasicMsg_del(Dz1InetFtpBasicMsg *p);
static __inline__ void Dz1InetFtpBasicMsg_delAndSetNull(void *ptr)
{
	Dz1InetFtpBasicMsg **p = (Dz1InetFtpBasicMsg **)ptr;
	if (p) { Dz1InetFtpBasicMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpBasicMsg_dump(Dz1InetFtpBasicMsg *p, int tab);
// Dz1InetFtpBasicMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRcvrMsgException
typedef Dz1InetFtpBasicMsg Dz1InetFtpRcvrMsgException;

#define Dz1InetFtpRcvrMsgException_new               Dz1InetFtpBasicMsg_new
#define Dz1InetFtpRcvrMsgException_del               Dz1InetFtpBasicMsg_del
#define Dz1InetFtpRcvrMsgException_delAndSetNull     Dz1InetFtpBasicMsg_delAndSetNull
#define Dz1InetFtpRcvrMsgException_dump              Dz1InetFtpBasicMsg_dump

// Dz1InetFtpRcvrMsgException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRcvrMsgReply
typedef struct Dz1InetFtpRcvrMsgReply
{
	Dz1SockAddr					*peer;
	Dz1SockAddr					*local;
	Dz1InetFtpCPIMsgReply		*reply;
	Dz1Binary					*pkt;
} Dz1InetFtpRcvrMsgReply;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpRcvrMsgReply *Dz1InetFtpRcvrMsgReply_new(Dz1SockAddr *peer, 
																		   Dz1SockAddr *local, 
																		   Dz1InetFtpCPIMsgReply *reply, Dz1Error *err);
static __inline__ Dz1InetFtpRcvrMsgReply *Dz1InetFtpRcvrMsgReply_gen(Dz1Error *err) { return Dz1InetFtpRcvrMsgReply_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRcvrMsgReply_purge(Dz1InetFtpRcvrMsgReply *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRcvrMsgReply_del(Dz1InetFtpRcvrMsgReply *p);
static __inline__ void Dz1InetFtpRcvrMsgReply_delAndSetNull(void *ptr)
{
	Dz1InetFtpRcvrMsgReply **p = (Dz1InetFtpRcvrMsgReply **)ptr;
	if (p) { Dz1InetFtpRcvrMsgReply_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpRcvrMsgReply_dump(Dz1InetFtpRcvrMsgReply *p, int tab);
// Dz1InetFtpRcvrMsgReply
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPMsg
typedef Dz1InetFtpRcvrMsgException Dz1InetFtpDTPMsg;

#define Dz1InetFtpDTPMsg_new               Dz1InetFtpRcvrMsgException_new
#define Dz1InetFtpDTPMsg_del               Dz1InetFtpRcvrMsgException_del
#define Dz1InetFtpDTPMsg_delAndSetNull     Dz1InetFtpRcvrMsgException_delAndSetNull
#define Dz1InetFtpDTPMsg_dump              Dz1InetFtpRcvrMsgException_dump

// Dz1InetFtpDTPMsg
////////////////////////////////////////////////////////////////////////////////

#endif
