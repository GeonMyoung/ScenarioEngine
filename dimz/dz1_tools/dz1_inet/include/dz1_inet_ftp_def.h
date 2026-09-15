#ifndef _DZ1_TDC_DZ1_INET_FTP_DEF_H_
#define _DZ1_TDC_DZ1_INET_FTP_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpException
typedef void (*Dz1InetFtpException)(void *ptr, Dz1Error *reason);
// Dz1InetFtpException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCmdResult
typedef enum Dz1InetFtpCmdResult
{
	Dz1InetFtpCmdResult_success,
	Dz1InetFtpCmdResult_omitted,
	Dz1InetFtpCmdResult_serviceNotReady,
	Dz1InetFtpCmdResult_serverBusy,
	Dz1InetFtpCmdResult_serverFail,
	Dz1InetFtpCmdResult_authFail,
	Dz1InetFtpCmdResult_fileNotFound,
	Dz1InetFtpCmdResult_pathNotFound,
	Dz1InetFtpCmdResult_transferFail,
	Dz1InetFtpCmdResult_unknown,
	Dz1InetFtpCmdResult_noPermission,
	Dz1InetFtpCmdResult_max
} Dz1InetFtpCmdResult;

DZ1_CPPLINK str_t Dz1InetFtpCmdResultStrA(Dz1InetFtpCmdResult v);
DZ1_CPPLINK Dz1InetFtpCmdResult Dz1InetFtpCmdResultFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpCmdResultStrW(Dz1InetFtpCmdResult v);
DZ1_CPPLINK Dz1InetFtpCmdResult Dz1InetFtpCmdResultFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpCmdResultStr Dz1InetFtpCmdResultStrW
#define Dz1InetFtpCmdResultFromStr Dz1InetFtpCmdResultFromStrW
#else // UNICODE
#define Dz1InetFtpCmdResultStr Dz1InetFtpCmdResultStrA
#define Dz1InetFtpCmdResultFromStr Dz1InetFtpCmdResultFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpCmdResultStr Dz1InetFtpCmdResultStrA
#define Dz1InetFtpCmdResultFromStr Dz1InetFtpCmdResultFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCmdResult *Dz1InetFtpCmdResult_new(Dz1InetFtpCmdResult *src, Dz1Error *err);
static __inline__ Dz1InetFtpCmdResult *Dz1InetFtpCmdResult_gen(Dz1Error *err) { Dz1InetFtpCmdResult v = Dz1InetFtpCmdResult_max; return Dz1InetFtpCmdResult_new(&v, err); }
static __inline__ void Dz1InetFtpCmdResult_del(Dz1InetFtpCmdResult *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpCmdResult_delAndSetNull(void *ptr)
{
	Dz1InetFtpCmdResult **p = (Dz1InetFtpCmdResult **)ptr;
	if (p != NULL) { Dz1InetFtpCmdResult_del(*p); *p = NULL; }
}
// Dz1InetFtpCmdResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileName
typedef struct Dz1InetFtpFileName
{
	str_t		path;
	str_t		name;
	u32_t		size;
} Dz1InetFtpFileName;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpFileName *Dz1InetFtpFileName_new(str_t path, 
																   str_t name, 
																   u32_t size, Dz1Error *err);
static __inline__ Dz1InetFtpFileName *Dz1InetFtpFileName_gen(Dz1Error *err) { return Dz1InetFtpFileName_new(NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1InetFtpFileName_copy(Dz1InetFtpFileName *dst, Dz1InetFtpFileName *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpFileName *Dz1InetFtpFileName_clone(Dz1InetFtpFileName *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileName_purge(Dz1InetFtpFileName *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileName_del(Dz1InetFtpFileName *p);
static __inline__ void Dz1InetFtpFileName_delAndSetNull(void *ptr)
{
	Dz1InetFtpFileName **p = (Dz1InetFtpFileName **)ptr;
	if (p) { Dz1InetFtpFileName_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileName_dump(Dz1InetFtpFileName *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1InetFtpFileName_cmp(Dz1InetFtpFileName *a, Dz1InetFtpFileName *b); 
// Dz1InetFtpFileName
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileInfoPresent
typedef enum Dz1InetFtpFileInfoPresent
{
	Dz1InetFtpFileInfoPresent_file,
	Dz1InetFtpFileInfoPresent_buffer,
	Dz1InetFtpFileInfoPresent_max
} Dz1InetFtpFileInfoPresent;

DZ1_CPPLINK str_t Dz1InetFtpFileInfoPresentStrA(Dz1InetFtpFileInfoPresent v);
DZ1_CPPLINK Dz1InetFtpFileInfoPresent Dz1InetFtpFileInfoPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpFileInfoPresentStrW(Dz1InetFtpFileInfoPresent v);
DZ1_CPPLINK Dz1InetFtpFileInfoPresent Dz1InetFtpFileInfoPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpFileInfoPresentStr Dz1InetFtpFileInfoPresentStrW
#define Dz1InetFtpFileInfoPresentFromStr Dz1InetFtpFileInfoPresentFromStrW
#else // UNICODE
#define Dz1InetFtpFileInfoPresentStr Dz1InetFtpFileInfoPresentStrA
#define Dz1InetFtpFileInfoPresentFromStr Dz1InetFtpFileInfoPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpFileInfoPresentStr Dz1InetFtpFileInfoPresentStrA
#define Dz1InetFtpFileInfoPresentFromStr Dz1InetFtpFileInfoPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpFileInfoPresent *Dz1InetFtpFileInfoPresent_new(Dz1InetFtpFileInfoPresent *src, Dz1Error *err);
static __inline__ Dz1InetFtpFileInfoPresent *Dz1InetFtpFileInfoPresent_gen(Dz1Error *err) { Dz1InetFtpFileInfoPresent v = Dz1InetFtpFileInfoPresent_max; return Dz1InetFtpFileInfoPresent_new(&v, err); }
#define Dz1InetFtpFileInfoPresent_clone             Dz1InetFtpFileInfoPresent_new
static __inline__ void Dz1InetFtpFileInfoPresent_del(Dz1InetFtpFileInfoPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpFileInfoPresent_delAndSetNull(void *ptr)
{
	Dz1InetFtpFileInfoPresent **p = (Dz1InetFtpFileInfoPresent **)ptr;
	if (p != NULL) { Dz1InetFtpFileInfoPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileInfoPresent_dump(Dz1InetFtpFileInfoPresent *v, int tab);
// Dz1InetFtpFileInfoPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileInfo
typedef struct Dz1InetFtpFileInfo
{
	Dz1InetFtpFileInfoPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1InetFtpFileName		*file;
		Dz1Binary				*buffer;
	} x;
} Dz1InetFtpFileInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpFileInfo *Dz1InetFtpFileInfo_new(Dz1InetFtpFileInfoPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpFileInfo *Dz1InetFtpFileInfo_gen(Dz1Error *err) { return Dz1InetFtpFileInfo_new(Dz1InetFtpFileInfoPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1InetFtpFileInfo_copy(Dz1InetFtpFileInfo *dst, Dz1InetFtpFileInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpFileInfo *Dz1InetFtpFileInfo_clone(Dz1InetFtpFileInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileInfo_purge(Dz1InetFtpFileInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileInfo_del(Dz1InetFtpFileInfo *p);
static __inline__ void Dz1InetFtpFileInfo_delAndSetNull(void *ptr)
{
	Dz1InetFtpFileInfo **p = (Dz1InetFtpFileInfo **)ptr;
	if (p != NULL) { Dz1InetFtpFileInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpFileInfo_dump(Dz1InetFtpFileInfo *p, int tab);
// Dz1InetFtpFileInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDirection
typedef enum Dz1InetFtpDirection
{
	Dz1InetFtpDirection_upload,
	Dz1InetFtpDirection_download,
	Dz1InetFtpDirection_max
} Dz1InetFtpDirection;

DZ1_CPPLINK str_t Dz1InetFtpDirectionStrA(Dz1InetFtpDirection v);
DZ1_CPPLINK Dz1InetFtpDirection Dz1InetFtpDirectionFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpDirectionStrW(Dz1InetFtpDirection v);
DZ1_CPPLINK Dz1InetFtpDirection Dz1InetFtpDirectionFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpDirectionStr Dz1InetFtpDirectionStrW
#define Dz1InetFtpDirectionFromStr Dz1InetFtpDirectionFromStrW
#else // UNICODE
#define Dz1InetFtpDirectionStr Dz1InetFtpDirectionStrA
#define Dz1InetFtpDirectionFromStr Dz1InetFtpDirectionFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpDirectionStr Dz1InetFtpDirectionStrA
#define Dz1InetFtpDirectionFromStr Dz1InetFtpDirectionFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDirection *Dz1InetFtpDirection_new(Dz1InetFtpDirection *src, Dz1Error *err);
static __inline__ Dz1InetFtpDirection *Dz1InetFtpDirection_gen(Dz1Error *err) { Dz1InetFtpDirection v = Dz1InetFtpDirection_max; return Dz1InetFtpDirection_new(&v, err); }
static __inline__ void Dz1InetFtpDirection_del(Dz1InetFtpDirection *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpDirection_delAndSetNull(void *ptr)
{
	Dz1InetFtpDirection **p = (Dz1InetFtpDirection **)ptr;
	if (p != NULL) { Dz1InetFtpDirection_del(*p); *p = NULL; }
}
// Dz1InetFtpDirection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransfer
typedef struct Dz1InetFtpTransfer
{
	Dz1InetFtpDirection		 direction;
	Dz1InetFtpFileName		*remote;
	Dz1InetFtpFileInfo		*local;
	bool_t					 overwrite;
	Dz1InetFtpCmdResult		 result;
	void					*userKey;
} Dz1InetFtpTransfer;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransfer *Dz1InetFtpTransfer_new(Dz1InetFtpDirection direction, 
																   Dz1InetFtpFileName *remote, 
																   Dz1InetFtpFileInfo *local, 
																   bool_t overwrite, 
																   void *userKey, Dz1Error *err);
static __inline__ Dz1InetFtpTransfer *Dz1InetFtpTransfer_gen(Dz1Error *err) { return Dz1InetFtpTransfer_new(Dz1InetFtpDirection_max, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1InetFtpTransfer_copy(Dz1InetFtpTransfer *dst, Dz1InetFtpTransfer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransfer *Dz1InetFtpTransfer_clone(Dz1InetFtpTransfer *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransfer_purge(Dz1InetFtpTransfer *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransfer_del(Dz1InetFtpTransfer *p);
static __inline__ void Dz1InetFtpTransfer_delAndSetNull(void *ptr)
{
	Dz1InetFtpTransfer **p = (Dz1InetFtpTransfer **)ptr;
	if (p) { Dz1InetFtpTransfer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransfer_dump(Dz1InetFtpTransfer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1InetFtpTransfer_cmp(Dz1InetFtpTransfer *a, Dz1InetFtpTransfer *b); 
// Dz1InetFtpTransfer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferList
typedef struct Dz1InetFtpTransferList
{
	void *storage;
	unsigned int (*count)(struct Dz1InetFtpTransferList *p);
	Dz1Error (*travel)(struct Dz1InetFtpTransferList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpTransfer *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1InetFtpTransferList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpTransfer *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1InetFtpTransferList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpTransfer *entry), void *ptr);
	Dz1InetFtpTransfer **(*get_array)(struct Dz1InetFtpTransferList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1InetFtpTransferList *p, Dz1InetFtpTransfer *data);
	int (*cmp)(Dz1InetFtpTransfer *a, Dz1InetFtpTransfer *b);
} Dz1InetFtpTransferList;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransferList *Dz1InetFtpTransferList_new(Dz1Error *err);
static __inline__ Dz1InetFtpTransferList *Dz1InetFtpTransferList_gen(Dz1Error *err) { return Dz1InetFtpTransferList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpTransferList *Dz1InetFtpTransferList_clone(Dz1InetFtpTransferList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferList_purge(Dz1InetFtpTransferList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferList_del(Dz1InetFtpTransferList *p);
static __inline__ void Dz1InetFtpTransferList_delAndSetNull(void *ptr)
{
	Dz1InetFtpTransferList **p = (Dz1InetFtpTransferList **)ptr;
	if (p != NULL) { Dz1InetFtpTransferList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpTransferList_dump(Dz1InetFtpTransferList *p, int tab);

// Dz1InetFtpTransferList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpFileDoneInform
typedef void (*Dz1InetFtpFileDoneInform)(void *ptr, Dz1SockAddr *peer, Dz1InetFtpTransfer *transfer);
// Dz1InetFtpFileDoneInform
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgTransferDoneInform
typedef void (*Dz1InetFtpMsgTransferDoneInform)(void *ptr, Dz1SockAddr *peer, Dz1InetFtpTransferList **files);
// Dz1InetFtpMsgTransferDoneInform
////////////////////////////////////////////////////////////////////////////////

#endif
