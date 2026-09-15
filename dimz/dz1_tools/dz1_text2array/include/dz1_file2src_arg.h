#ifndef _DZ1_TDC_DZ1_FILE2SRC_ARG_H_
#define _DZ1_TDC_DZ1_FILE2SRC_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// File2SrcConvTextPublish
typedef enum File2SrcConvTextPublish
{
	File2SrcConvTextPublish_String,
	File2SrcConvTextPublish_Binary,
	File2SrcConvTextPublish_max
} File2SrcConvTextPublish;

DZ1_CPPLINK str_t File2SrcConvTextPublishStrA(File2SrcConvTextPublish v);
DZ1_CPPLINK File2SrcConvTextPublish File2SrcConvTextPublishFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t File2SrcConvTextPublishStrW(File2SrcConvTextPublish v);
DZ1_CPPLINK File2SrcConvTextPublish File2SrcConvTextPublishFromStrW(wstr_t str);
#ifdef UNICODE
#define File2SrcConvTextPublishStr File2SrcConvTextPublishStrW
#define File2SrcConvTextPublishFromStr File2SrcConvTextPublishFromStrW
#else // UNICODE
#define File2SrcConvTextPublishStr File2SrcConvTextPublishStrA
#define File2SrcConvTextPublishFromStr File2SrcConvTextPublishFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define File2SrcConvTextPublishStr File2SrcConvTextPublishStrA
#define File2SrcConvTextPublishFromStr File2SrcConvTextPublishFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT File2SrcConvTextPublish *File2SrcConvTextPublish_new(File2SrcConvTextPublish *src, Dz1Error *err);
static __inline__ File2SrcConvTextPublish *File2SrcConvTextPublish_gen(Dz1Error *err) { File2SrcConvTextPublish v = File2SrcConvTextPublish_max; return File2SrcConvTextPublish_new(&v, err); }
static __inline__ void File2SrcConvTextPublish_del(File2SrcConvTextPublish *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void File2SrcConvTextPublish_delAndSetNull(void *ptr)
{
	File2SrcConvTextPublish **p = (File2SrcConvTextPublish **)ptr;
	if (p != NULL) { File2SrcConvTextPublish_del(*p); *p = NULL; }
}
// File2SrcConvTextPublish
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvTextAttrPresent
typedef enum File2SrcConvTextAttrPresent
{
	File2SrcConvTextAttrPresent_PlaneText,
	File2SrcConvTextAttrPresent_HexDump,
	File2SrcConvTextAttrPresent_max
} File2SrcConvTextAttrPresent;

DZ1_CPPLINK str_t File2SrcConvTextAttrPresentStrA(File2SrcConvTextAttrPresent v);
DZ1_CPPLINK File2SrcConvTextAttrPresent File2SrcConvTextAttrPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t File2SrcConvTextAttrPresentStrW(File2SrcConvTextAttrPresent v);
DZ1_CPPLINK File2SrcConvTextAttrPresent File2SrcConvTextAttrPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define File2SrcConvTextAttrPresentStr File2SrcConvTextAttrPresentStrW
#define File2SrcConvTextAttrPresentFromStr File2SrcConvTextAttrPresentFromStrW
#else // UNICODE
#define File2SrcConvTextAttrPresentStr File2SrcConvTextAttrPresentStrA
#define File2SrcConvTextAttrPresentFromStr File2SrcConvTextAttrPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define File2SrcConvTextAttrPresentStr File2SrcConvTextAttrPresentStrA
#define File2SrcConvTextAttrPresentFromStr File2SrcConvTextAttrPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT File2SrcConvTextAttrPresent *File2SrcConvTextAttrPresent_new(File2SrcConvTextAttrPresent *src, Dz1Error *err);
static __inline__ File2SrcConvTextAttrPresent *File2SrcConvTextAttrPresent_gen(Dz1Error *err) { File2SrcConvTextAttrPresent v = File2SrcConvTextAttrPresent_max; return File2SrcConvTextAttrPresent_new(&v, err); }
static __inline__ void File2SrcConvTextAttrPresent_del(File2SrcConvTextAttrPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void File2SrcConvTextAttrPresent_delAndSetNull(void *ptr)
{
	File2SrcConvTextAttrPresent **p = (File2SrcConvTextAttrPresent **)ptr;
	if (p != NULL) { File2SrcConvTextAttrPresent_del(*p); *p = NULL; }
}
// File2SrcConvTextAttrPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvTextAttr
typedef struct File2SrcConvTextAttr
{
	File2SrcConvTextAttrPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		File2SrcConvTextPublish		 PlaneText;
		u32_t						*HexDump;
	} x;
} File2SrcConvTextAttr;

DZ1_CPPLINK DZ1_DLLPORT File2SrcConvTextAttr *File2SrcConvTextAttr_new(File2SrcConvTextAttrPresent present, void *ptr, Dz1Error *err);
static __inline__ File2SrcConvTextAttr *File2SrcConvTextAttr_gen(Dz1Error *err) { return File2SrcConvTextAttr_new(File2SrcConvTextAttrPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvTextAttr_purge(File2SrcConvTextAttr *p);
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvTextAttr_del(File2SrcConvTextAttr *p);
static __inline__ void File2SrcConvTextAttr_delAndSetNull(void *ptr)
{
	File2SrcConvTextAttr **p = (File2SrcConvTextAttr **)ptr;
	if (p != NULL) { File2SrcConvTextAttr_del(*p); *p = NULL; }
}
// File2SrcConvTextAttr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcVariableForm
typedef enum File2SrcVariableForm
{
	File2SrcVariableForm_SingleVariable,
	File2SrcVariableForm_ArrayByLine,
	File2SrcVariableForm_ArrayByBlock,
	File2SrcVariableForm_max
} File2SrcVariableForm;

DZ1_CPPLINK str_t File2SrcVariableFormStrA(File2SrcVariableForm v);
DZ1_CPPLINK File2SrcVariableForm File2SrcVariableFormFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t File2SrcVariableFormStrW(File2SrcVariableForm v);
DZ1_CPPLINK File2SrcVariableForm File2SrcVariableFormFromStrW(wstr_t str);
#ifdef UNICODE
#define File2SrcVariableFormStr File2SrcVariableFormStrW
#define File2SrcVariableFormFromStr File2SrcVariableFormFromStrW
#else // UNICODE
#define File2SrcVariableFormStr File2SrcVariableFormStrA
#define File2SrcVariableFormFromStr File2SrcVariableFormFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define File2SrcVariableFormStr File2SrcVariableFormStrA
#define File2SrcVariableFormFromStr File2SrcVariableFormFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT File2SrcVariableForm *File2SrcVariableForm_new(File2SrcVariableForm *src, Dz1Error *err);
static __inline__ File2SrcVariableForm *File2SrcVariableForm_gen(Dz1Error *err) { File2SrcVariableForm v = File2SrcVariableForm_max; return File2SrcVariableForm_new(&v, err); }
static __inline__ void File2SrcVariableForm_del(File2SrcVariableForm *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void File2SrcVariableForm_delAndSetNull(void *ptr)
{
	File2SrcVariableForm **p = (File2SrcVariableForm **)ptr;
	if (p != NULL) { File2SrcVariableForm_del(*p); *p = NULL; }
}
// File2SrcVariableForm
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvTextOpt
typedef struct File2SrcConvTextOpt
{
	File2SrcConvTextAttr	*attr;
	File2SrcVariableForm	 form;
} File2SrcConvTextOpt;

DZ1_CPPLINK DZ1_DLLPORT File2SrcConvTextOpt *File2SrcConvTextOpt_new(File2SrcConvTextAttr *attr, 
																	 File2SrcVariableForm form, Dz1Error *err);
static __inline__ File2SrcConvTextOpt *File2SrcConvTextOpt_gen(Dz1Error *err) { return File2SrcConvTextOpt_new(NULL, File2SrcVariableForm_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvTextOpt_purge(File2SrcConvTextOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvTextOpt_del(File2SrcConvTextOpt *p);
static __inline__ void File2SrcConvTextOpt_delAndSetNull(void *ptr)
{
	File2SrcConvTextOpt **p = (File2SrcConvTextOpt **)ptr;
	if (p) { File2SrcConvTextOpt_del(*p); *p = NULL; }
}
// File2SrcConvTextOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvOptPresent
typedef enum File2SrcConvOptPresent
{
	File2SrcConvOptPresent_textMode,
	File2SrcConvOptPresent_binMode,
	File2SrcConvOptPresent_max
} File2SrcConvOptPresent;

DZ1_CPPLINK str_t File2SrcConvOptPresentStrA(File2SrcConvOptPresent v);
DZ1_CPPLINK File2SrcConvOptPresent File2SrcConvOptPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t File2SrcConvOptPresentStrW(File2SrcConvOptPresent v);
DZ1_CPPLINK File2SrcConvOptPresent File2SrcConvOptPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define File2SrcConvOptPresentStr File2SrcConvOptPresentStrW
#define File2SrcConvOptPresentFromStr File2SrcConvOptPresentFromStrW
#else // UNICODE
#define File2SrcConvOptPresentStr File2SrcConvOptPresentStrA
#define File2SrcConvOptPresentFromStr File2SrcConvOptPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define File2SrcConvOptPresentStr File2SrcConvOptPresentStrA
#define File2SrcConvOptPresentFromStr File2SrcConvOptPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT File2SrcConvOptPresent *File2SrcConvOptPresent_new(File2SrcConvOptPresent *src, Dz1Error *err);
static __inline__ File2SrcConvOptPresent *File2SrcConvOptPresent_gen(Dz1Error *err) { File2SrcConvOptPresent v = File2SrcConvOptPresent_max; return File2SrcConvOptPresent_new(&v, err); }
static __inline__ void File2SrcConvOptPresent_del(File2SrcConvOptPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void File2SrcConvOptPresent_delAndSetNull(void *ptr)
{
	File2SrcConvOptPresent **p = (File2SrcConvOptPresent **)ptr;
	if (p != NULL) { File2SrcConvOptPresent_del(*p); *p = NULL; }
}
// File2SrcConvOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvOpt
typedef struct File2SrcConvOpt
{
	File2SrcConvOptPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		File2SrcConvTextOpt		*textMode;
		u32_t					*binMode;
	} x;
} File2SrcConvOpt;

DZ1_CPPLINK DZ1_DLLPORT File2SrcConvOpt *File2SrcConvOpt_new(File2SrcConvOptPresent present, void *ptr, Dz1Error *err);
static __inline__ File2SrcConvOpt *File2SrcConvOpt_gen(Dz1Error *err) { return File2SrcConvOpt_new(File2SrcConvOptPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvOpt_purge(File2SrcConvOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvOpt_del(File2SrcConvOpt *p);
static __inline__ void File2SrcConvOpt_delAndSetNull(void *ptr)
{
	File2SrcConvOpt **p = (File2SrcConvOpt **)ptr;
	if (p != NULL) { File2SrcConvOpt_del(*p); *p = NULL; }
}
// File2SrcConvOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcOutputMode
typedef enum File2SrcOutputMode
{
	File2SrcOutputMode_DOS,
	File2SrcOutputMode_UNIX,
	File2SrcOutputMode_max
} File2SrcOutputMode;

DZ1_CPPLINK str_t File2SrcOutputModeStrA(File2SrcOutputMode v);
DZ1_CPPLINK File2SrcOutputMode File2SrcOutputModeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t File2SrcOutputModeStrW(File2SrcOutputMode v);
DZ1_CPPLINK File2SrcOutputMode File2SrcOutputModeFromStrW(wstr_t str);
#ifdef UNICODE
#define File2SrcOutputModeStr File2SrcOutputModeStrW
#define File2SrcOutputModeFromStr File2SrcOutputModeFromStrW
#else // UNICODE
#define File2SrcOutputModeStr File2SrcOutputModeStrA
#define File2SrcOutputModeFromStr File2SrcOutputModeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define File2SrcOutputModeStr File2SrcOutputModeStrA
#define File2SrcOutputModeFromStr File2SrcOutputModeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT File2SrcOutputMode *File2SrcOutputMode_new(File2SrcOutputMode *src, Dz1Error *err);
static __inline__ File2SrcOutputMode *File2SrcOutputMode_gen(Dz1Error *err) { File2SrcOutputMode v = File2SrcOutputMode_max; return File2SrcOutputMode_new(&v, err); }
static __inline__ void File2SrcOutputMode_del(File2SrcOutputMode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void File2SrcOutputMode_delAndSetNull(void *ptr)
{
	File2SrcOutputMode **p = (File2SrcOutputMode **)ptr;
	if (p != NULL) { File2SrcOutputMode_del(*p); *p = NULL; }
}
// File2SrcOutputMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// File2SrcConvArg
typedef struct File2SrcConvArg
{
	str_t					 srcPath;
	str_t					 srcName;
	File2SrcConvOpt			*opt;
	str_t					 var_name;
	str_t					 dstPath;
	str_t					 dstName;
	File2SrcOutputMode		 mode;
} File2SrcConvArg;

DZ1_CPPLINK DZ1_DLLPORT File2SrcConvArg *File2SrcConvArg_new(str_t srcPath, 
															 str_t srcName, 
															 File2SrcConvOpt *opt, 
															 str_t var_name, 
															 str_t dstPath, 
															 str_t dstName, 
															 File2SrcOutputMode mode, Dz1Error *err);
static __inline__ File2SrcConvArg *File2SrcConvArg_gen(Dz1Error *err) { return File2SrcConvArg_new(NULL, NULL, NULL, NULL, NULL, NULL, File2SrcOutputMode_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvArg_purge(File2SrcConvArg *p);
DZ1_CPPLINK DZ1_DLLPORT void File2SrcConvArg_del(File2SrcConvArg *p);
static __inline__ void File2SrcConvArg_delAndSetNull(void *ptr)
{
	File2SrcConvArg **p = (File2SrcConvArg **)ptr;
	if (p) { File2SrcConvArg_del(*p); *p = NULL; }
}
// File2SrcConvArg
////////////////////////////////////////////////////////////////////////////////

#endif
