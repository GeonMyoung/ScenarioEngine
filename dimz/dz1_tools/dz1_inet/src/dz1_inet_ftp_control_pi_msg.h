#ifndef _DZ1_TDC_DZ1_INET_FTP_CONTROL_PI_MSG_H_
#define _DZ1_TDC_DZ1_INET_FTP_CONTROL_PI_MSG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPTextForm
typedef enum Dz1InetFtpDTPTextForm
{
	Dz1InetFtpDTPTextForm_nonPrint,
	Dz1InetFtpDTPTextForm_telnet,
	Dz1InetFtpDTPTextForm_asa,
	Dz1InetFtpDTPTextForm_max
} Dz1InetFtpDTPTextForm;

DZ1_CPPLINK str_t Dz1InetFtpDTPTextFormStrA(Dz1InetFtpDTPTextForm v);
DZ1_CPPLINK Dz1InetFtpDTPTextForm Dz1InetFtpDTPTextFormFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpDTPTextFormStrW(Dz1InetFtpDTPTextForm v);
DZ1_CPPLINK Dz1InetFtpDTPTextForm Dz1InetFtpDTPTextFormFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpDTPTextFormStr Dz1InetFtpDTPTextFormStrW
#define Dz1InetFtpDTPTextFormFromStr Dz1InetFtpDTPTextFormFromStrW
#else // UNICODE
#define Dz1InetFtpDTPTextFormStr Dz1InetFtpDTPTextFormStrA
#define Dz1InetFtpDTPTextFormFromStr Dz1InetFtpDTPTextFormFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpDTPTextFormStr Dz1InetFtpDTPTextFormStrA
#define Dz1InetFtpDTPTextFormFromStr Dz1InetFtpDTPTextFormFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPTextForm *Dz1InetFtpDTPTextForm_new(Dz1InetFtpDTPTextForm *src, Dz1Error *err);
static __inline__ Dz1InetFtpDTPTextForm *Dz1InetFtpDTPTextForm_gen(Dz1Error *err) { Dz1InetFtpDTPTextForm v = Dz1InetFtpDTPTextForm_max; return Dz1InetFtpDTPTextForm_new(&v, err); }
static __inline__ void Dz1InetFtpDTPTextForm_del(Dz1InetFtpDTPTextForm *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpDTPTextForm_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPTextForm **p = (Dz1InetFtpDTPTextForm **)ptr;
	if (p != NULL) { Dz1InetFtpDTPTextForm_del(*p); *p = NULL; }
}
// Dz1InetFtpDTPTextForm
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPTypePresent
typedef enum Dz1InetFtpDTPTypePresent
{
	Dz1InetFtpDTPTypePresent_ascii,
	Dz1InetFtpDTPTypePresent_ebcdic,
	Dz1InetFtpDTPTypePresent_image,
	Dz1InetFtpDTPTypePresent_local,
	Dz1InetFtpDTPTypePresent_max
} Dz1InetFtpDTPTypePresent;

DZ1_CPPLINK str_t Dz1InetFtpDTPTypePresentStrA(Dz1InetFtpDTPTypePresent v);
DZ1_CPPLINK Dz1InetFtpDTPTypePresent Dz1InetFtpDTPTypePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpDTPTypePresentStrW(Dz1InetFtpDTPTypePresent v);
DZ1_CPPLINK Dz1InetFtpDTPTypePresent Dz1InetFtpDTPTypePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpDTPTypePresentStr Dz1InetFtpDTPTypePresentStrW
#define Dz1InetFtpDTPTypePresentFromStr Dz1InetFtpDTPTypePresentFromStrW
#else // UNICODE
#define Dz1InetFtpDTPTypePresentStr Dz1InetFtpDTPTypePresentStrA
#define Dz1InetFtpDTPTypePresentFromStr Dz1InetFtpDTPTypePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpDTPTypePresentStr Dz1InetFtpDTPTypePresentStrA
#define Dz1InetFtpDTPTypePresentFromStr Dz1InetFtpDTPTypePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPTypePresent *Dz1InetFtpDTPTypePresent_new(Dz1InetFtpDTPTypePresent *src, Dz1Error *err);
static __inline__ Dz1InetFtpDTPTypePresent *Dz1InetFtpDTPTypePresent_gen(Dz1Error *err) { Dz1InetFtpDTPTypePresent v = Dz1InetFtpDTPTypePresent_max; return Dz1InetFtpDTPTypePresent_new(&v, err); }
static __inline__ void Dz1InetFtpDTPTypePresent_del(Dz1InetFtpDTPTypePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpDTPTypePresent_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPTypePresent **p = (Dz1InetFtpDTPTypePresent **)ptr;
	if (p != NULL) { Dz1InetFtpDTPTypePresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPTypePresent_dump(Dz1InetFtpDTPTypePresent *v, int tab);
// Dz1InetFtpDTPTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPType
typedef struct Dz1InetFtpDTPType
{
	Dz1InetFtpDTPTypePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1InetFtpDTPTextForm		*ascii;
		Dz1InetFtpDTPTextForm		*ebcdic;
		u32_t						*image;
		u32_t						 local;
	} x;
} Dz1InetFtpDTPType;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPType *Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpDTPType *Dz1InetFtpDTPType_gen(Dz1Error *err) { return Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPType_purge(Dz1InetFtpDTPType *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPType_del(Dz1InetFtpDTPType *p);
static __inline__ void Dz1InetFtpDTPType_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPType **p = (Dz1InetFtpDTPType **)ptr;
	if (p != NULL) { Dz1InetFtpDTPType_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpDTPType_dump(Dz1InetFtpDTPType *p, int tab);
// Dz1InetFtpDTPType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPStruct
typedef enum Dz1InetFtpDTPStruct
{
	Dz1InetFtpDTPStruct_file,
	Dz1InetFtpDTPStruct_record,
	Dz1InetFtpDTPStruct_page,
	Dz1InetFtpDTPStruct_max
} Dz1InetFtpDTPStruct;

DZ1_CPPLINK str_t Dz1InetFtpDTPStructStrA(Dz1InetFtpDTPStruct v);
DZ1_CPPLINK Dz1InetFtpDTPStruct Dz1InetFtpDTPStructFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpDTPStructStrW(Dz1InetFtpDTPStruct v);
DZ1_CPPLINK Dz1InetFtpDTPStruct Dz1InetFtpDTPStructFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpDTPStructStr Dz1InetFtpDTPStructStrW
#define Dz1InetFtpDTPStructFromStr Dz1InetFtpDTPStructFromStrW
#else // UNICODE
#define Dz1InetFtpDTPStructStr Dz1InetFtpDTPStructStrA
#define Dz1InetFtpDTPStructFromStr Dz1InetFtpDTPStructFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpDTPStructStr Dz1InetFtpDTPStructStrA
#define Dz1InetFtpDTPStructFromStr Dz1InetFtpDTPStructFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPStruct *Dz1InetFtpDTPStruct_new(Dz1InetFtpDTPStruct *src, Dz1Error *err);
static __inline__ Dz1InetFtpDTPStruct *Dz1InetFtpDTPStruct_gen(Dz1Error *err) { Dz1InetFtpDTPStruct v = Dz1InetFtpDTPStruct_max; return Dz1InetFtpDTPStruct_new(&v, err); }
static __inline__ void Dz1InetFtpDTPStruct_del(Dz1InetFtpDTPStruct *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpDTPStruct_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPStruct **p = (Dz1InetFtpDTPStruct **)ptr;
	if (p != NULL) { Dz1InetFtpDTPStruct_del(*p); *p = NULL; }
}
// Dz1InetFtpDTPStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPMode
typedef enum Dz1InetFtpDTPMode
{
	Dz1InetFtpDTPMode_stream,
	Dz1InetFtpDTPMode_block,
	Dz1InetFtpDTPMode_compressed,
	Dz1InetFtpDTPMode_max
} Dz1InetFtpDTPMode;

DZ1_CPPLINK str_t Dz1InetFtpDTPModeStrA(Dz1InetFtpDTPMode v);
DZ1_CPPLINK Dz1InetFtpDTPMode Dz1InetFtpDTPModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpDTPModeStrW(Dz1InetFtpDTPMode v);
DZ1_CPPLINK Dz1InetFtpDTPMode Dz1InetFtpDTPModeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpDTPModeStr Dz1InetFtpDTPModeStrW
#define Dz1InetFtpDTPModeFromStr Dz1InetFtpDTPModeFromStrW
#else // UNICODE
#define Dz1InetFtpDTPModeStr Dz1InetFtpDTPModeStrA
#define Dz1InetFtpDTPModeFromStr Dz1InetFtpDTPModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpDTPModeStr Dz1InetFtpDTPModeStrA
#define Dz1InetFtpDTPModeFromStr Dz1InetFtpDTPModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpDTPMode *Dz1InetFtpDTPMode_new(Dz1InetFtpDTPMode *src, Dz1Error *err);
static __inline__ Dz1InetFtpDTPMode *Dz1InetFtpDTPMode_gen(Dz1Error *err) { Dz1InetFtpDTPMode v = Dz1InetFtpDTPMode_max; return Dz1InetFtpDTPMode_new(&v, err); }
static __inline__ void Dz1InetFtpDTPMode_del(Dz1InetFtpDTPMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpDTPMode_delAndSetNull(void *ptr)
{
	Dz1InetFtpDTPMode **p = (Dz1InetFtpDTPMode **)ptr;
	if (p != NULL) { Dz1InetFtpDTPMode_del(*p); *p = NULL; }
}
// Dz1InetFtpDTPMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpAlloc
typedef struct Dz1InetFtpAlloc
{
	u32_t		 numOfOctet;
	u32_t		*numOfRecord;
} Dz1InetFtpAlloc;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpAlloc *Dz1InetFtpAlloc_new(u32_t numOfOctet, 
															 u32_t *numOfRecord, Dz1Error *err);
static __inline__ Dz1InetFtpAlloc *Dz1InetFtpAlloc_gen(Dz1Error *err) { return Dz1InetFtpAlloc_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpAlloc_purge(Dz1InetFtpAlloc *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpAlloc_del(Dz1InetFtpAlloc *p);
static __inline__ void Dz1InetFtpAlloc_delAndSetNull(void *ptr)
{
	Dz1InetFtpAlloc **p = (Dz1InetFtpAlloc **)ptr;
	if (p) { Dz1InetFtpAlloc_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpAlloc_dump(Dz1InetFtpAlloc *p, int tab);
// Dz1InetFtpAlloc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReqPresent
typedef enum Dz1InetFtpCPIMsgReqPresent
{
	Dz1InetFtpCPIMsgReqPresent_user,
	Dz1InetFtpCPIMsgReqPresent_pass,
	Dz1InetFtpCPIMsgReqPresent_acct,
	Dz1InetFtpCPIMsgReqPresent_cwd,
	Dz1InetFtpCPIMsgReqPresent_cdup,
	Dz1InetFtpCPIMsgReqPresent_smnt,
	Dz1InetFtpCPIMsgReqPresent_quit,
	Dz1InetFtpCPIMsgReqPresent_rein,
	Dz1InetFtpCPIMsgReqPresent_port,
	Dz1InetFtpCPIMsgReqPresent_pasv,
	Dz1InetFtpCPIMsgReqPresent_type,
	Dz1InetFtpCPIMsgReqPresent_stru,
	Dz1InetFtpCPIMsgReqPresent_mode,
	Dz1InetFtpCPIMsgReqPresent_retr,
	Dz1InetFtpCPIMsgReqPresent_stor,
	Dz1InetFtpCPIMsgReqPresent_stou,
	Dz1InetFtpCPIMsgReqPresent_appe,
	Dz1InetFtpCPIMsgReqPresent_allo,
	Dz1InetFtpCPIMsgReqPresent_rest,
	Dz1InetFtpCPIMsgReqPresent_rnfr,
	Dz1InetFtpCPIMsgReqPresent_rnto,
	Dz1InetFtpCPIMsgReqPresent_abor,
	Dz1InetFtpCPIMsgReqPresent_dele,
	Dz1InetFtpCPIMsgReqPresent_rmd,
	Dz1InetFtpCPIMsgReqPresent_mkd,
	Dz1InetFtpCPIMsgReqPresent_pwd,
	Dz1InetFtpCPIMsgReqPresent_list,
	Dz1InetFtpCPIMsgReqPresent_nlst,
	Dz1InetFtpCPIMsgReqPresent_site,
	Dz1InetFtpCPIMsgReqPresent_syst,
	Dz1InetFtpCPIMsgReqPresent_stat,
	Dz1InetFtpCPIMsgReqPresent_help,
	Dz1InetFtpCPIMsgReqPresent_size,
	Dz1InetFtpCPIMsgReqPresent_feat,
	Dz1InetFtpCPIMsgReqPresent_max
} Dz1InetFtpCPIMsgReqPresent;

DZ1_CPPLINK str_t Dz1InetFtpCPIMsgReqPresentStrA(Dz1InetFtpCPIMsgReqPresent v);
DZ1_CPPLINK Dz1InetFtpCPIMsgReqPresent Dz1InetFtpCPIMsgReqPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpCPIMsgReqPresentStrW(Dz1InetFtpCPIMsgReqPresent v);
DZ1_CPPLINK Dz1InetFtpCPIMsgReqPresent Dz1InetFtpCPIMsgReqPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpCPIMsgReqPresentStr Dz1InetFtpCPIMsgReqPresentStrW
#define Dz1InetFtpCPIMsgReqPresentFromStr Dz1InetFtpCPIMsgReqPresentFromStrW
#else // UNICODE
#define Dz1InetFtpCPIMsgReqPresentStr Dz1InetFtpCPIMsgReqPresentStrA
#define Dz1InetFtpCPIMsgReqPresentFromStr Dz1InetFtpCPIMsgReqPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpCPIMsgReqPresentStr Dz1InetFtpCPIMsgReqPresentStrA
#define Dz1InetFtpCPIMsgReqPresentFromStr Dz1InetFtpCPIMsgReqPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgReqPresent *Dz1InetFtpCPIMsgReqPresent_new(Dz1InetFtpCPIMsgReqPresent *src, Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsgReqPresent *Dz1InetFtpCPIMsgReqPresent_gen(Dz1Error *err) { Dz1InetFtpCPIMsgReqPresent v = Dz1InetFtpCPIMsgReqPresent_max; return Dz1InetFtpCPIMsgReqPresent_new(&v, err); }
static __inline__ void Dz1InetFtpCPIMsgReqPresent_del(Dz1InetFtpCPIMsgReqPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpCPIMsgReqPresent_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsgReqPresent **p = (Dz1InetFtpCPIMsgReqPresent **)ptr;
	if (p != NULL) { Dz1InetFtpCPIMsgReqPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReqPresent_dump(Dz1InetFtpCPIMsgReqPresent *v, int tab);
// Dz1InetFtpCPIMsgReqPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReq
typedef struct Dz1InetFtpCPIMsgReq
{
	Dz1InetFtpCPIMsgReqPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		str_t					 user;
		str_t					 pass;
		str_t					 acct;
		str_t					 cwd;
		u32_t					*cdup;
		str_t					 smnt;
		u32_t					*quit;
		u32_t					*rein;
		Dz1SockAddr				*port;
		u32_t					*pasv;
		Dz1InetFtpDTPType		*type;
		Dz1InetFtpDTPStruct		 stru;
		Dz1InetFtpDTPMode		 mode;
		str_t					 retr;
		str_t					 stor;
		u32_t					*stou;
		str_t					 appe;
		Dz1InetFtpAlloc			*allo;
		str_t					 rest;
		str_t					 rnfr;
		str_t					 rnto;
		u32_t					*abor;
		str_t					 dele;
		str_t					 rmd;
		str_t					 mkd;
		u32_t					*pwd;
		str_t					 list;
		str_t					 nlst;
		str_t					 site;
		u32_t					*syst;
		str_t					 stat;
		str_t					 help;
		str_t					 size;
		u32_t					*feat;
	} x;
} Dz1InetFtpCPIMsgReq;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgReq *Dz1InetFtpCPIMsgReq_new(Dz1InetFtpCPIMsgReqPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsgReq *Dz1InetFtpCPIMsgReq_gen(Dz1Error *err) { return Dz1InetFtpCPIMsgReq_new(Dz1InetFtpCPIMsgReqPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReq_purge(Dz1InetFtpCPIMsgReq *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReq_del(Dz1InetFtpCPIMsgReq *p);
static __inline__ void Dz1InetFtpCPIMsgReq_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsgReq **p = (Dz1InetFtpCPIMsgReq **)ptr;
	if (p != NULL) { Dz1InetFtpCPIMsgReq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReq_dump(Dz1InetFtpCPIMsgReq *p, int tab);
// Dz1InetFtpCPIMsgReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReplyTextList
typedef struct Dz1InetFtpCPIMsgReplyTextList
{
	void *storage;
	unsigned int (*count)(struct Dz1InetFtpCPIMsgReplyTextList *p);
	Dz1Error (*travel)(struct Dz1InetFtpCPIMsgReplyTextList *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1InetFtpCPIMsgReplyTextList *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1InetFtpCPIMsgReplyTextList *p, Dz1Error (*func)(void *ptr, str_t entry), void *ptr);
	str_t *(*get_array)(struct Dz1InetFtpCPIMsgReplyTextList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1InetFtpCPIMsgReplyTextList *p, str_t data);
	str_t (*getTail)(struct Dz1InetFtpCPIMsgReplyTextList *p);
	int (*cmp)(str_t a, str_t b);
} Dz1InetFtpCPIMsgReplyTextList;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgReplyTextList *Dz1InetFtpCPIMsgReplyTextList_new(Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsgReplyTextList *Dz1InetFtpCPIMsgReplyTextList_gen(Dz1Error *err) { return Dz1InetFtpCPIMsgReplyTextList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgReplyTextList *Dz1InetFtpCPIMsgReplyTextList_clone(Dz1InetFtpCPIMsgReplyTextList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReplyTextList_purge(Dz1InetFtpCPIMsgReplyTextList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReplyTextList_del(Dz1InetFtpCPIMsgReplyTextList *p);
static __inline__ void Dz1InetFtpCPIMsgReplyTextList_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsgReplyTextList **p = (Dz1InetFtpCPIMsgReplyTextList **)ptr;
	if (p != NULL) { Dz1InetFtpCPIMsgReplyTextList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReplyTextList_dump(Dz1InetFtpCPIMsgReplyTextList *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReplyTextList_fdump(FILE *fp, Dz1InetFtpCPIMsgReplyTextList *p, int tab);

// Dz1InetFtpCPIMsgReplyTextList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReply
typedef struct Dz1InetFtpCPIMsgReply
{
	u32_t								 code;
	str_t								 title;
	Dz1InetFtpCPIMsgReplyTextList		*list;
} Dz1InetFtpCPIMsgReply;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgReply *Dz1InetFtpCPIMsgReply_new(u32_t code, 
																		 str_t title, Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsgReply *Dz1InetFtpCPIMsgReply_gen(Dz1Error *err) { return Dz1InetFtpCPIMsgReply_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReply_purge(Dz1InetFtpCPIMsgReply *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReply_del(Dz1InetFtpCPIMsgReply *p);
static __inline__ void Dz1InetFtpCPIMsgReply_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsgReply **p = (Dz1InetFtpCPIMsgReply **)ptr;
	if (p) { Dz1InetFtpCPIMsgReply_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgReply_dump(Dz1InetFtpCPIMsgReply *p, int tab);
// Dz1InetFtpCPIMsgReply
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgPresent
typedef enum Dz1InetFtpCPIMsgPresent
{
	Dz1InetFtpCPIMsgPresent_req,
	Dz1InetFtpCPIMsgPresent_reply,
	Dz1InetFtpCPIMsgPresent_max
} Dz1InetFtpCPIMsgPresent;

DZ1_CPPLINK str_t Dz1InetFtpCPIMsgPresentStrA(Dz1InetFtpCPIMsgPresent v);
DZ1_CPPLINK Dz1InetFtpCPIMsgPresent Dz1InetFtpCPIMsgPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpCPIMsgPresentStrW(Dz1InetFtpCPIMsgPresent v);
DZ1_CPPLINK Dz1InetFtpCPIMsgPresent Dz1InetFtpCPIMsgPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpCPIMsgPresentStr Dz1InetFtpCPIMsgPresentStrW
#define Dz1InetFtpCPIMsgPresentFromStr Dz1InetFtpCPIMsgPresentFromStrW
#else // UNICODE
#define Dz1InetFtpCPIMsgPresentStr Dz1InetFtpCPIMsgPresentStrA
#define Dz1InetFtpCPIMsgPresentFromStr Dz1InetFtpCPIMsgPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpCPIMsgPresentStr Dz1InetFtpCPIMsgPresentStrA
#define Dz1InetFtpCPIMsgPresentFromStr Dz1InetFtpCPIMsgPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsgPresent *Dz1InetFtpCPIMsgPresent_new(Dz1InetFtpCPIMsgPresent *src, Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsgPresent *Dz1InetFtpCPIMsgPresent_gen(Dz1Error *err) { Dz1InetFtpCPIMsgPresent v = Dz1InetFtpCPIMsgPresent_max; return Dz1InetFtpCPIMsgPresent_new(&v, err); }
static __inline__ void Dz1InetFtpCPIMsgPresent_del(Dz1InetFtpCPIMsgPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpCPIMsgPresent_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsgPresent **p = (Dz1InetFtpCPIMsgPresent **)ptr;
	if (p != NULL) { Dz1InetFtpCPIMsgPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsgPresent_dump(Dz1InetFtpCPIMsgPresent *v, int tab);
// Dz1InetFtpCPIMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsg
typedef struct Dz1InetFtpCPIMsg
{
	Dz1InetFtpCPIMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1InetFtpCPIMsgReq			*req;
		Dz1InetFtpCPIMsgReply		*reply;
	} x;
} Dz1InetFtpCPIMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpCPIMsg *Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1InetFtpCPIMsg *Dz1InetFtpCPIMsg_gen(Dz1Error *err) { return Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsg_purge(Dz1InetFtpCPIMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsg_del(Dz1InetFtpCPIMsg *p);
static __inline__ void Dz1InetFtpCPIMsg_delAndSetNull(void *ptr)
{
	Dz1InetFtpCPIMsg **p = (Dz1InetFtpCPIMsg **)ptr;
	if (p != NULL) { Dz1InetFtpCPIMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetFtpCPIMsg_dump(Dz1InetFtpCPIMsg *p, int tab);
// Dz1InetFtpCPIMsg
////////////////////////////////////////////////////////////////////////////////

#endif
