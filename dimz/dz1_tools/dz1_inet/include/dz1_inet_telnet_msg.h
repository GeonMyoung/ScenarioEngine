#ifndef _DZ1_TDC_DZ1_INET_TELNET_MSG_H_
#define _DZ1_TDC_DZ1_INET_TELNET_MSG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptTerminalTypePresent
typedef enum Dz1InetTelnetOptTerminalTypePresent
{
	Dz1InetTelnetOptTerminalTypePresent_is,
	Dz1InetTelnetOptTerminalTypePresent_send,
	Dz1InetTelnetOptTerminalTypePresent_max
} Dz1InetTelnetOptTerminalTypePresent;

DZ1_CPPLINK str_t Dz1InetTelnetOptTerminalTypePresentStrA(Dz1InetTelnetOptTerminalTypePresent v);
DZ1_CPPLINK Dz1InetTelnetOptTerminalTypePresent Dz1InetTelnetOptTerminalTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetOptTerminalTypePresentStrW(Dz1InetTelnetOptTerminalTypePresent v);
DZ1_CPPLINK Dz1InetTelnetOptTerminalTypePresent Dz1InetTelnetOptTerminalTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetOptTerminalTypePresentStr Dz1InetTelnetOptTerminalTypePresentStrW
#define Dz1InetTelnetOptTerminalTypePresentFromStr Dz1InetTelnetOptTerminalTypePresentFromStrW
#else // UNICODE
#define Dz1InetTelnetOptTerminalTypePresentStr Dz1InetTelnetOptTerminalTypePresentStrA
#define Dz1InetTelnetOptTerminalTypePresentFromStr Dz1InetTelnetOptTerminalTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetOptTerminalTypePresentStr Dz1InetTelnetOptTerminalTypePresentStrA
#define Dz1InetTelnetOptTerminalTypePresentFromStr Dz1InetTelnetOptTerminalTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOptTerminalTypePresent *Dz1InetTelnetOptTerminalTypePresent_new(Dz1InetTelnetOptTerminalTypePresent *src, Dz1Error *err);
static __inline__ Dz1InetTelnetOptTerminalTypePresent *Dz1InetTelnetOptTerminalTypePresent_gen(Dz1Error *err) { Dz1InetTelnetOptTerminalTypePresent v = Dz1InetTelnetOptTerminalTypePresent_max; return Dz1InetTelnetOptTerminalTypePresent_new(&v, err); }
static __inline__ void Dz1InetTelnetOptTerminalTypePresent_del(Dz1InetTelnetOptTerminalTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetOptTerminalTypePresent_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOptTerminalTypePresent **p = (Dz1InetTelnetOptTerminalTypePresent **)ptr;
	if (p != NULL) { Dz1InetTelnetOptTerminalTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptTerminalTypePresent_dump(Dz1InetTelnetOptTerminalTypePresent *v, int tab);
// Dz1InetTelnetOptTerminalTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptTerminalType
typedef struct Dz1InetTelnetOptTerminalType
{
	Dz1InetTelnetOptTerminalTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		str_t		 is;
		u32_t		*send;
	} x;
} Dz1InetTelnetOptTerminalType;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOptTerminalType *Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetTelnetOptTerminalType *Dz1InetTelnetOptTerminalType_gen(Dz1Error *err) { return Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptTerminalType_purge(Dz1InetTelnetOptTerminalType *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptTerminalType_del(Dz1InetTelnetOptTerminalType *p);
static __inline__ void Dz1InetTelnetOptTerminalType_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOptTerminalType **p = (Dz1InetTelnetOptTerminalType **)ptr;
	if (p != NULL) { Dz1InetTelnetOptTerminalType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptTerminalType_dump(Dz1InetTelnetOptTerminalType *p, int tab);
// Dz1InetTelnetOptTerminalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptWindowSize
typedef struct Dz1InetTelnetOptWindowSize
{
	u16_t		width;
	u16_t		height;
} Dz1InetTelnetOptWindowSize;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOptWindowSize *Dz1InetTelnetOptWindowSize_new(u16_t width, 
																				   u16_t height, Dz1Error *err);
static __inline__ Dz1InetTelnetOptWindowSize *Dz1InetTelnetOptWindowSize_gen(Dz1Error *err) { return Dz1InetTelnetOptWindowSize_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptWindowSize_purge(Dz1InetTelnetOptWindowSize *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptWindowSize_del(Dz1InetTelnetOptWindowSize *p);
static __inline__ void Dz1InetTelnetOptWindowSize_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOptWindowSize **p = (Dz1InetTelnetOptWindowSize **)ptr;
	if (p) { Dz1InetTelnetOptWindowSize_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptWindowSize_dump(Dz1InetTelnetOptWindowSize *p, int tab);
// Dz1InetTelnetOptWindowSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptPresent
typedef enum Dz1InetTelnetOptPresent
{
	Dz1InetTelnetOptPresent_binary,
	Dz1InetTelnetOptPresent_echo,
	Dz1InetTelnetOptPresent_prepareReconnect,
	Dz1InetTelnetOptPresent_suppressGoAhead,
	Dz1InetTelnetOptPresent_approximateMsgSize,
	Dz1InetTelnetOptPresent_status,
	Dz1InetTelnetOptPresent_timingMark,
	Dz1InetTelnetOptPresent_rcTxAndEcho,
	Dz1InetTelnetOptPresent_lineWidth,
	Dz1InetTelnetOptPresent_pageSize,
	Dz1InetTelnetOptPresent_crDisposition,
	Dz1InetTelnetOptPresent_hTabStop,
	Dz1InetTelnetOptPresent_hTabDisposition,
	Dz1InetTelnetOptPresent_formFeedDisposition,
	Dz1InetTelnetOptPresent_vTabStop,
	Dz1InetTelnetOptPresent_vTabDisposition,
	Dz1InetTelnetOptPresent_lfDisposition,
	Dz1InetTelnetOptPresent_xAscii,
	Dz1InetTelnetOptPresent_forceLogout,
	Dz1InetTelnetOptPresent_byteMacro,
	Dz1InetTelnetOptPresent_dataEntryTerminal,
	Dz1InetTelnetOptPresent_supdupProtocol,
	Dz1InetTelnetOptPresent_supdupOutput,
	Dz1InetTelnetOptPresent_sendLocation,
	Dz1InetTelnetOptPresent_terminalType,
	Dz1InetTelnetOptPresent_endOfRecord,
	Dz1InetTelnetOptPresent_tacacsUserID,
	Dz1InetTelnetOptPresent_OutputMarking,
	Dz1InetTelnetOptPresent_ttyNumber,
	Dz1InetTelnetOptPresent_regime3270,
	Dz1InetTelnetOptPresent_xDot3Pad,
	Dz1InetTelnetOptPresent_windowSize,
	Dz1InetTelnetOptPresent_terminalSpeed,
	Dz1InetTelnetOptPresent_remoteFlowControl,
	Dz1InetTelnetOptPresent_lineMode,
	Dz1InetTelnetOptPresent_xDispLoc,
	Dz1InetTelnetOptPresent_oldEnvs,
	Dz1InetTelnetOptPresent_auth,
	Dz1InetTelnetOptPresent_encryption,
	Dz1InetTelnetOptPresent_newEnvs,
	Dz1InetTelnetOptPresent_extOptList,
	Dz1InetTelnetOptPresent_max
} Dz1InetTelnetOptPresent;

DZ1_CPPLINK str_t Dz1InetTelnetOptPresentStrA(Dz1InetTelnetOptPresent v);
DZ1_CPPLINK Dz1InetTelnetOptPresent Dz1InetTelnetOptPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetOptPresentStrW(Dz1InetTelnetOptPresent v);
DZ1_CPPLINK Dz1InetTelnetOptPresent Dz1InetTelnetOptPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetOptPresentStr Dz1InetTelnetOptPresentStrW
#define Dz1InetTelnetOptPresentFromStr Dz1InetTelnetOptPresentFromStrW
#else // UNICODE
#define Dz1InetTelnetOptPresentStr Dz1InetTelnetOptPresentStrA
#define Dz1InetTelnetOptPresentFromStr Dz1InetTelnetOptPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetOptPresentStr Dz1InetTelnetOptPresentStrA
#define Dz1InetTelnetOptPresentFromStr Dz1InetTelnetOptPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOptPresent *Dz1InetTelnetOptPresent_new(Dz1InetTelnetOptPresent *src, Dz1Error *err);
static __inline__ Dz1InetTelnetOptPresent *Dz1InetTelnetOptPresent_gen(Dz1Error *err) { Dz1InetTelnetOptPresent v = Dz1InetTelnetOptPresent_max; return Dz1InetTelnetOptPresent_new(&v, err); }
static __inline__ void Dz1InetTelnetOptPresent_del(Dz1InetTelnetOptPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetOptPresent_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOptPresent **p = (Dz1InetTelnetOptPresent **)ptr;
	if (p != NULL) { Dz1InetTelnetOptPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOptPresent_dump(Dz1InetTelnetOptPresent *v, int tab);
// Dz1InetTelnetOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOpt
typedef struct Dz1InetTelnetOpt
{
	Dz1InetTelnetOptPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t							*binary;
		u32_t							*echo;
		u32_t							*prepareReconnect;
		u32_t							*suppressGoAhead;
		u32_t							*approximateMsgSize;
		u32_t							*status;
		u32_t							*timingMark;
		u32_t							*rcTxAndEcho;
		u32_t							*lineWidth;
		u32_t							*pageSize;
		u32_t							*crDisposition;
		u32_t							*hTabStop;
		u32_t							*hTabDisposition;
		u32_t							*formFeedDisposition;
		u32_t							*vTabStop;
		u32_t							*vTabDisposition;
		u32_t							*lfDisposition;
		u32_t							*xAscii;
		u32_t							*forceLogout;
		u32_t							*byteMacro;
		u32_t							*dataEntryTerminal;
		u32_t							*supdupProtocol;
		u32_t							*supdupOutput;
		u32_t							*sendLocation;
		Dz1InetTelnetOptTerminalType	*terminalType;
		u32_t							*endOfRecord;
		u32_t							*tacacsUserID;
		u32_t							*OutputMarking;
		u32_t							*ttyNumber;
		u32_t							*regime3270;
		u32_t							*xDot3Pad;
		Dz1InetTelnetOptWindowSize		*windowSize;
		u32_t							*terminalSpeed;
		u32_t							*remoteFlowControl;
		u32_t							*lineMode;
		u32_t							*xDispLoc;
		u32_t							*oldEnvs;
		u32_t							*auth;
		u32_t							*encryption;
		u32_t							*newEnvs;
		u32_t							*extOptList;
	} x;
} Dz1InetTelnetOpt;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOpt *Dz1InetTelnetOpt_new(Dz1InetTelnetOptPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetTelnetOpt *Dz1InetTelnetOpt_gen(Dz1Error *err) { return Dz1InetTelnetOpt_new(Dz1InetTelnetOptPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOpt_purge(Dz1InetTelnetOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOpt_del(Dz1InetTelnetOpt *p);
static __inline__ void Dz1InetTelnetOpt_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOpt **p = (Dz1InetTelnetOpt **)ptr;
	if (p != NULL) { Dz1InetTelnetOpt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetOpt_dump(Dz1InetTelnetOpt *p, int tab);
// Dz1InetTelnetOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetOptCode
typedef enum Dz1InetTelnetOptCode
{
	Dz1InetTelnetOptCode_binary,
	Dz1InetTelnetOptCode_echo,
	Dz1InetTelnetOptCode_prepareReconnect,
	Dz1InetTelnetOptCode_suppressGoAhead,
	Dz1InetTelnetOptCode_approximateMsgSize,
	Dz1InetTelnetOptCode_status,
	Dz1InetTelnetOptCode_timingMark,
	Dz1InetTelnetOptCode_rcTxAndEcho,
	Dz1InetTelnetOptCode_lineWidth,
	Dz1InetTelnetOptCode_pageSize,
	Dz1InetTelnetOptCode_crDisposition,
	Dz1InetTelnetOptCode_hTabStop,
	Dz1InetTelnetOptCode_hTabDisposition,
	Dz1InetTelnetOptCode_formFeedDisposition,
	Dz1InetTelnetOptCode_vTabStop,
	Dz1InetTelnetOptCode_vTabDisposition,
	Dz1InetTelnetOptCode_lfDisposition,
	Dz1InetTelnetOptCode_xAscii,
	Dz1InetTelnetOptCode_forceLogout,
	Dz1InetTelnetOptCode_byteMacro,
	Dz1InetTelnetOptCode_dataEntryTerminal,
	Dz1InetTelnetOptCode_supdupProtocol,
	Dz1InetTelnetOptCode_supdupOutput,
	Dz1InetTelnetOptCode_sendLocation,
	Dz1InetTelnetOptCode_terminalType,
	Dz1InetTelnetOptCode_endOfRecord,
	Dz1InetTelnetOptCode_tacacsUserID,
	Dz1InetTelnetOptCode_OutputMarking,
	Dz1InetTelnetOptCode_ttyNumber,
	Dz1InetTelnetOptCode_regime3270,
	Dz1InetTelnetOptCode_xDot3Pad,
	Dz1InetTelnetOptCode_windowSize,
	Dz1InetTelnetOptCode_terminalSpeed,
	Dz1InetTelnetOptCode_remoteFlowControl,
	Dz1InetTelnetOptCode_lineMode,
	Dz1InetTelnetOptCode_xDispLoc,
	Dz1InetTelnetOptCode_oldEnvs,
	Dz1InetTelnetOptCode_auth,
	Dz1InetTelnetOptCode_encryption,
	Dz1InetTelnetOptCode_newEnvs,
	Dz1InetTelnetOptCode_extOptList = 255,
	Dz1InetTelnetOptCode_max
} Dz1InetTelnetOptCode;

DZ1_CPPLINK str_t Dz1InetTelnetOptCodeStrA(Dz1InetTelnetOptCode v);
DZ1_CPPLINK Dz1InetTelnetOptCode Dz1InetTelnetOptCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetOptCodeStrW(Dz1InetTelnetOptCode v);
DZ1_CPPLINK Dz1InetTelnetOptCode Dz1InetTelnetOptCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetOptCodeStr Dz1InetTelnetOptCodeStrW
#define Dz1InetTelnetOptCodeFromStr Dz1InetTelnetOptCodeFromStrW
#else // UNICODE
#define Dz1InetTelnetOptCodeStr Dz1InetTelnetOptCodeStrA
#define Dz1InetTelnetOptCodeFromStr Dz1InetTelnetOptCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetOptCodeStr Dz1InetTelnetOptCodeStrA
#define Dz1InetTelnetOptCodeFromStr Dz1InetTelnetOptCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetOptCode *Dz1InetTelnetOptCode_new(Dz1InetTelnetOptCode *src, Dz1Error *err);
static __inline__ Dz1InetTelnetOptCode *Dz1InetTelnetOptCode_gen(Dz1Error *err) { Dz1InetTelnetOptCode v = Dz1InetTelnetOptCode_max; return Dz1InetTelnetOptCode_new(&v, err); }
static __inline__ void Dz1InetTelnetOptCode_del(Dz1InetTelnetOptCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetOptCode_delAndSetNull(void *ptr)
{
	Dz1InetTelnetOptCode **p = (Dz1InetTelnetOptCode **)ptr;
	if (p != NULL) { Dz1InetTelnetOptCode_del(*p); *p = NULL; }
}
// Dz1InetTelnetOptCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmdPresent
typedef enum Dz1InetTelnetCmdPresent
{
	Dz1InetTelnetCmdPresent_endOfSubNego,
	Dz1InetTelnetCmdPresent_noOper,
	Dz1InetTelnetCmdPresent_dataMark,
	Dz1InetTelnetCmdPresent_brk,
	Dz1InetTelnetCmdPresent_interruptProcess,
	Dz1InetTelnetCmdPresent_abortOutput,
	Dz1InetTelnetCmdPresent_areYouThere,
	Dz1InetTelnetCmdPresent_eraseChar,
	Dz1InetTelnetCmdPresent_eraseLine,
	Dz1InetTelnetCmdPresent_goAhead,
	Dz1InetTelnetCmdPresent_subNego,
	Dz1InetTelnetCmdPresent_willOpt,
	Dz1InetTelnetCmdPresent_wontOpt,
	Dz1InetTelnetCmdPresent_doOpt,
	Dz1InetTelnetCmdPresent_dontOpt,
	Dz1InetTelnetCmdPresent_max
} Dz1InetTelnetCmdPresent;

DZ1_CPPLINK str_t Dz1InetTelnetCmdPresentStrA(Dz1InetTelnetCmdPresent v);
DZ1_CPPLINK Dz1InetTelnetCmdPresent Dz1InetTelnetCmdPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetCmdPresentStrW(Dz1InetTelnetCmdPresent v);
DZ1_CPPLINK Dz1InetTelnetCmdPresent Dz1InetTelnetCmdPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetCmdPresentStr Dz1InetTelnetCmdPresentStrW
#define Dz1InetTelnetCmdPresentFromStr Dz1InetTelnetCmdPresentFromStrW
#else // UNICODE
#define Dz1InetTelnetCmdPresentStr Dz1InetTelnetCmdPresentStrA
#define Dz1InetTelnetCmdPresentFromStr Dz1InetTelnetCmdPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetCmdPresentStr Dz1InetTelnetCmdPresentStrA
#define Dz1InetTelnetCmdPresentFromStr Dz1InetTelnetCmdPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetCmdPresent *Dz1InetTelnetCmdPresent_new(Dz1InetTelnetCmdPresent *src, Dz1Error *err);
static __inline__ Dz1InetTelnetCmdPresent *Dz1InetTelnetCmdPresent_gen(Dz1Error *err) { Dz1InetTelnetCmdPresent v = Dz1InetTelnetCmdPresent_max; return Dz1InetTelnetCmdPresent_new(&v, err); }
static __inline__ void Dz1InetTelnetCmdPresent_del(Dz1InetTelnetCmdPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetCmdPresent_delAndSetNull(void *ptr)
{
	Dz1InetTelnetCmdPresent **p = (Dz1InetTelnetCmdPresent **)ptr;
	if (p != NULL) { Dz1InetTelnetCmdPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetCmdPresent_dump(Dz1InetTelnetCmdPresent *v, int tab);
// Dz1InetTelnetCmdPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmd
typedef struct Dz1InetTelnetCmd
{
	Dz1InetTelnetCmdPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t				*endOfSubNego;
		u32_t				*noOper;
		u32_t				*dataMark;
		u32_t				*brk;
		u32_t				*interruptProcess;
		u32_t				*abortOutput;
		u32_t				*areYouThere;
		u32_t				*eraseChar;
		u32_t				*eraseLine;
		u32_t				*goAhead;
		Dz1InetTelnetOpt	*subNego;
		Dz1InetTelnetOpt	*willOpt;
		Dz1InetTelnetOpt	*wontOpt;
		Dz1InetTelnetOpt	*doOpt;
		Dz1InetTelnetOpt	*dontOpt;
	} x;
} Dz1InetTelnetCmd;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetCmd *Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetTelnetCmd *Dz1InetTelnetCmd_gen(Dz1Error *err) { return Dz1InetTelnetCmd_new(Dz1InetTelnetCmdPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetCmd_purge(Dz1InetTelnetCmd *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetCmd_del(Dz1InetTelnetCmd *p);
static __inline__ void Dz1InetTelnetCmd_delAndSetNull(void *ptr)
{
	Dz1InetTelnetCmd **p = (Dz1InetTelnetCmd **)ptr;
	if (p != NULL) { Dz1InetTelnetCmd_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetCmd_dump(Dz1InetTelnetCmd *p, int tab);
// Dz1InetTelnetCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetCmdCode
typedef enum Dz1InetTelnetCmdCode
{
	Dz1InetTelnetCmdCode_endOfSubNego = 240,
	Dz1InetTelnetCmdCode_noOper,
	Dz1InetTelnetCmdCode_dataMark,
	Dz1InetTelnetCmdCode_brk,
	Dz1InetTelnetCmdCode_interruptProcess,
	Dz1InetTelnetCmdCode_abortOutput,
	Dz1InetTelnetCmdCode_areYouThere,
	Dz1InetTelnetCmdCode_eraseChar,
	Dz1InetTelnetCmdCode_eraseLine,
	Dz1InetTelnetCmdCode_goAhead,
	Dz1InetTelnetCmdCode_subNego,
	Dz1InetTelnetCmdCode_willOpt,
	Dz1InetTelnetCmdCode_wontOpt,
	Dz1InetTelnetCmdCode_doOpt,
	Dz1InetTelnetCmdCode_dontOpt,
	Dz1InetTelnetCmdCode_max
} Dz1InetTelnetCmdCode;

DZ1_CPPLINK str_t Dz1InetTelnetCmdCodeStrA(Dz1InetTelnetCmdCode v);
DZ1_CPPLINK Dz1InetTelnetCmdCode Dz1InetTelnetCmdCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetCmdCodeStrW(Dz1InetTelnetCmdCode v);
DZ1_CPPLINK Dz1InetTelnetCmdCode Dz1InetTelnetCmdCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetCmdCodeStr Dz1InetTelnetCmdCodeStrW
#define Dz1InetTelnetCmdCodeFromStr Dz1InetTelnetCmdCodeFromStrW
#else // UNICODE
#define Dz1InetTelnetCmdCodeStr Dz1InetTelnetCmdCodeStrA
#define Dz1InetTelnetCmdCodeFromStr Dz1InetTelnetCmdCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetCmdCodeStr Dz1InetTelnetCmdCodeStrA
#define Dz1InetTelnetCmdCodeFromStr Dz1InetTelnetCmdCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetCmdCode *Dz1InetTelnetCmdCode_new(Dz1InetTelnetCmdCode *src, Dz1Error *err);
static __inline__ Dz1InetTelnetCmdCode *Dz1InetTelnetCmdCode_gen(Dz1Error *err) { Dz1InetTelnetCmdCode v = Dz1InetTelnetCmdCode_max; return Dz1InetTelnetCmdCode_new(&v, err); }
static __inline__ void Dz1InetTelnetCmdCode_del(Dz1InetTelnetCmdCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetCmdCode_delAndSetNull(void *ptr)
{
	Dz1InetTelnetCmdCode **p = (Dz1InetTelnetCmdCode **)ptr;
	if (p != NULL) { Dz1InetTelnetCmdCode_del(*p); *p = NULL; }
}
// Dz1InetTelnetCmdCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetEsc
typedef enum Dz1InetTelnetEsc
{
	Dz1InetTelnetEsc_IAC = 255,
	Dz1InetTelnetEsc_max
} Dz1InetTelnetEsc;

DZ1_CPPLINK str_t Dz1InetTelnetEscStrA(Dz1InetTelnetEsc v);
DZ1_CPPLINK Dz1InetTelnetEsc Dz1InetTelnetEscFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetEscStrW(Dz1InetTelnetEsc v);
DZ1_CPPLINK Dz1InetTelnetEsc Dz1InetTelnetEscFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetEscStr Dz1InetTelnetEscStrW
#define Dz1InetTelnetEscFromStr Dz1InetTelnetEscFromStrW
#else // UNICODE
#define Dz1InetTelnetEscStr Dz1InetTelnetEscStrA
#define Dz1InetTelnetEscFromStr Dz1InetTelnetEscFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetEscStr Dz1InetTelnetEscStrA
#define Dz1InetTelnetEscFromStr Dz1InetTelnetEscFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetEsc *Dz1InetTelnetEsc_new(Dz1InetTelnetEsc *src, Dz1Error *err);
static __inline__ Dz1InetTelnetEsc *Dz1InetTelnetEsc_gen(Dz1Error *err) { Dz1InetTelnetEsc v = Dz1InetTelnetEsc_max; return Dz1InetTelnetEsc_new(&v, err); }
static __inline__ void Dz1InetTelnetEsc_del(Dz1InetTelnetEsc *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetEsc_delAndSetNull(void *ptr)
{
	Dz1InetTelnetEsc **p = (Dz1InetTelnetEsc **)ptr;
	if (p != NULL) { Dz1InetTelnetEsc_del(*p); *p = NULL; }
}
// Dz1InetTelnetEsc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetMsgPresent
typedef enum Dz1InetTelnetMsgPresent
{
	Dz1InetTelnetMsgPresent_cmd,
	Dz1InetTelnetMsgPresent_bytes,
	Dz1InetTelnetMsgPresent_max
} Dz1InetTelnetMsgPresent;

DZ1_CPPLINK str_t Dz1InetTelnetMsgPresentStrA(Dz1InetTelnetMsgPresent v);
DZ1_CPPLINK Dz1InetTelnetMsgPresent Dz1InetTelnetMsgPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetTelnetMsgPresentStrW(Dz1InetTelnetMsgPresent v);
DZ1_CPPLINK Dz1InetTelnetMsgPresent Dz1InetTelnetMsgPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetTelnetMsgPresentStr Dz1InetTelnetMsgPresentStrW
#define Dz1InetTelnetMsgPresentFromStr Dz1InetTelnetMsgPresentFromStrW
#else // UNICODE
#define Dz1InetTelnetMsgPresentStr Dz1InetTelnetMsgPresentStrA
#define Dz1InetTelnetMsgPresentFromStr Dz1InetTelnetMsgPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetTelnetMsgPresentStr Dz1InetTelnetMsgPresentStrA
#define Dz1InetTelnetMsgPresentFromStr Dz1InetTelnetMsgPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetMsgPresent *Dz1InetTelnetMsgPresent_new(Dz1InetTelnetMsgPresent *src, Dz1Error *err);
static __inline__ Dz1InetTelnetMsgPresent *Dz1InetTelnetMsgPresent_gen(Dz1Error *err) { Dz1InetTelnetMsgPresent v = Dz1InetTelnetMsgPresent_max; return Dz1InetTelnetMsgPresent_new(&v, err); }
static __inline__ void Dz1InetTelnetMsgPresent_del(Dz1InetTelnetMsgPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetTelnetMsgPresent_delAndSetNull(void *ptr)
{
	Dz1InetTelnetMsgPresent **p = (Dz1InetTelnetMsgPresent **)ptr;
	if (p != NULL) { Dz1InetTelnetMsgPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetMsgPresent_dump(Dz1InetTelnetMsgPresent *v, int tab);
// Dz1InetTelnetMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetTelnetMsg
typedef struct Dz1InetTelnetMsg
{
	Dz1InetTelnetMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1InetTelnetCmd	*cmd;
		Dz1Binary			*bytes;
	} x;
} Dz1InetTelnetMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetMsg *Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetTelnetMsg *Dz1InetTelnetMsg_gen(Dz1Error *err) { return Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetMsg_purge(Dz1InetTelnetMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetMsg_del(Dz1InetTelnetMsg *p);
static __inline__ void Dz1InetTelnetMsg_delAndSetNull(void *ptr)
{
	Dz1InetTelnetMsg **p = (Dz1InetTelnetMsg **)ptr;
	if (p != NULL) { Dz1InetTelnetMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetMsg_dump(Dz1InetTelnetMsg *p, int tab);
// Dz1InetTelnetMsg
////////////////////////////////////////////////////////////////////////////////

#endif
