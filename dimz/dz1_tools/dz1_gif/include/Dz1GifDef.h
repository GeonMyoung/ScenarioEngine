#ifndef _DZ1_TDC_DZ1_GIF_DEF_H_
#define _DZ1_TDC_DZ1_GIF_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_bmp_def.h"
#include "dz1_sync.h"
#include "Dz1GifTypes.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderCallback
typedef Dz1Error (*Dz1GifRenderCallback)(
					void *ptr, 
					u32_t seq, 
					u32_t dur_ms, 
					Dz1BMP *bmp);
// Dz1GifRenderCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataSubBlock
struct Dz1GifDataSubBlock;

typedef struct Dz1GifDataSubBlock
{
	Dz1Binary						*bin;
	struct Dz1GifDataSubBlock		*next;
} Dz1GifDataSubBlock;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataSubBlock *Dz1GifDataSubBlock_new(Dz1Binary *bin, Dz1Error *err);
static __inline__ Dz1GifDataSubBlock *Dz1GifDataSubBlock_gen(Dz1Error *err) { return Dz1GifDataSubBlock_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataSubBlock_purge(Dz1GifDataSubBlock *p);	// User Customized
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataSubBlock_del(Dz1GifDataSubBlock *p);	// User Customized
static __inline__ void Dz1GifDataSubBlock_delAndSetNull(void *ptr)
{
	Dz1GifDataSubBlock **p = (Dz1GifDataSubBlock **)ptr;
	if (p) { Dz1GifDataSubBlock_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataSubBlock_dump(Dz1GifDataSubBlock *p, int tab);
// Dz1GifDataSubBlock
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColor
typedef struct Dz1GifColor
{
	u16_t		idx;
	u8_t		red;
	u8_t		green;
	u8_t		blue;
} Dz1GifColor;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifColor *Dz1GifColor_new(u16_t idx, 
													 u8_t red, 
													 u8_t green, 
													 u8_t blue, Dz1Error *err);
static __inline__ Dz1GifColor *Dz1GifColor_gen(Dz1Error *err) { return Dz1GifColor_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifColor_copy(Dz1GifColor *dst, Dz1GifColor *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifColor *Dz1GifColor_clone(Dz1GifColor *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColor_purge(Dz1GifColor *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColor_del(Dz1GifColor *p);
static __inline__ void Dz1GifColor_delAndSetNull(void *ptr)
{
	Dz1GifColor **p = (Dz1GifColor **)ptr;
	if (p) { Dz1GifColor_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColor_dump(Dz1GifColor *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1GifColor_cmp(Dz1GifColor *a, Dz1GifColor *b); 
// Dz1GifColor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorList
typedef struct Dz1GifColorList
{
	void *storage;
	unsigned int (*count)(struct Dz1GifColorList *p);
	Dz1Error (*travel)(struct Dz1GifColorList *p, Dz1Error (*func)(void *ptr, Dz1GifColor *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1GifColorList *p, Dz1Error (*func)(void *ptr, Dz1GifColor *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1GifColorList *p, Dz1Error (*func)(void *ptr, Dz1GifColor *entry), void *ptr);
	Dz1GifColor **(*get_array)(struct Dz1GifColorList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1GifColorList *p, Dz1GifColor *data);
	bool_t (*remove)(struct Dz1GifColorList *p, Dz1GifColor *key);
	Dz1GifColor *(*extract)(struct Dz1GifColorList *p, Dz1GifColor *key);
	Dz1GifColor *(*find)(struct Dz1GifColorList *p, Dz1GifColor *key);
	Dz1GifColor *(*getHead)(struct Dz1GifColorList *p);
	int (*cmp)(Dz1GifColor *a, Dz1GifColor *b);
} Dz1GifColorList;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifColorList *Dz1GifColorList_new(Dz1Error *err);
static __inline__ Dz1GifColorList *Dz1GifColorList_gen(Dz1Error *err) { return Dz1GifColorList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1GifColorList *Dz1GifColorList_clone(Dz1GifColorList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorList_purge(Dz1GifColorList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorList_del(Dz1GifColorList *p);
static __inline__ void Dz1GifColorList_delAndSetNull(void *ptr)
{
	Dz1GifColorList **p = (Dz1GifColorList **)ptr;
	if (p != NULL) { Dz1GifColorList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorList_dump(Dz1GifColorList *p, int tab);

// Dz1GifColorList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorArray
typedef struct Dz1GifColorArray
{
	Dz1GifColorList		*list;
	Dz1GifColorIndex	*idx;
} Dz1GifColorArray;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifColorArray *Dz1GifColorArray_new(Dz1Error *err);
static __inline__ Dz1GifColorArray *Dz1GifColorArray_gen(Dz1Error *err) { return Dz1GifColorArray_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifColorArray_copy(Dz1GifColorArray *dst, Dz1GifColorArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifColorArray *Dz1GifColorArray_clone(Dz1GifColorArray *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorArray_purge(Dz1GifColorArray *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorArray_del(Dz1GifColorArray *p);
static __inline__ void Dz1GifColorArray_delAndSetNull(void *ptr)
{
	Dz1GifColorArray **p = (Dz1GifColorArray **)ptr;
	if (p) { Dz1GifColorArray_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifColorArray_dump(Dz1GifColorArray *p, int tab);
// Dz1GifColorArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifHeader
typedef struct Dz1GifHeader
{
	str_t		sig;
	str_t		ver;
} Dz1GifHeader;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifHeader *Dz1GifHeader_new(str_t sig, str_t ver, Dz1Error *err);
static __inline__ Dz1GifHeader *Dz1GifHeader_gen(Dz1Error *err) { return Dz1GifHeader_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifHeader_copy(Dz1GifHeader *dst, Dz1GifHeader *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifHeader *Dz1GifHeader_clone(Dz1GifHeader *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifHeader_purge(Dz1GifHeader *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifHeader_del(Dz1GifHeader *p);
static __inline__ void Dz1GifHeader_delAndSetNull(void *ptr)
{
	Dz1GifHeader **p = (Dz1GifHeader **)ptr;
	if (p) { Dz1GifHeader_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifHeader_dump(Dz1GifHeader *p, int tab);
// Dz1GifHeader
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDescr
typedef struct Dz1GifDescr
{
	u16_t				 width;
	u16_t				 height;
	bool_t				 gctPresent;
	s8_t				 color_res;
	bool_t				 gctIsSorted;
	s8_t				 gctSizeExp;
	u8_t				 bgcIdx;
	u8_t				 aspect;
	Dz1GifColorArray	*palette;
} Dz1GifDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDescr *Dz1GifDescr_new(u16_t width, 
													 u16_t height, 
													 bool_t gctPresent, 
													 s8_t color_res, 
													 bool_t gctIsSorted, 
													 s8_t gctSizeExp, 
													 u8_t bgcIdx, 
													 u8_t aspect, Dz1Error *err);
static __inline__ Dz1GifDescr *Dz1GifDescr_gen(Dz1Error *err) { return Dz1GifDescr_new(0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifDescr_copy(Dz1GifDescr *dst, Dz1GifDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifDescr *Dz1GifDescr_clone(Dz1GifDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDescr_purge(Dz1GifDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDescr_del(Dz1GifDescr *p);
static __inline__ void Dz1GifDescr_delAndSetNull(void *ptr)
{
	Dz1GifDescr **p = (Dz1GifDescr **)ptr;
	if (p) { Dz1GifDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDescr_dump(Dz1GifDescr *p, int tab);
// Dz1GifDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifImgDescr
typedef struct Dz1GifImgDescr
{
	u32_t				 x;
	u32_t				 y;
	u32_t				 width;
	u32_t				 height;
	bool_t				 lctPresent;
	bool_t				 isInterlaced;
	bool_t				 lctIsSorted;
	s8_t				 lctSizeExp;
	Dz1GifColorArray	*palette;
} Dz1GifImgDescr;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifImgDescr *Dz1GifImgDescr_new(u32_t x, 
														   u32_t y, 
														   u32_t width, 
														   u32_t height, 
														   bool_t lctPresent, 
														   bool_t isInterlaced, 
														   bool_t lctIsSorted, 
														   s8_t lctSizeExp, Dz1Error *err);
static __inline__ Dz1GifImgDescr *Dz1GifImgDescr_gen(Dz1Error *err) { return Dz1GifImgDescr_new(0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifImgDescr_copy(Dz1GifImgDescr *dst, Dz1GifImgDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifImgDescr *Dz1GifImgDescr_clone(Dz1GifImgDescr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifImgDescr_purge(Dz1GifImgDescr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifImgDescr_del(Dz1GifImgDescr *p);
static __inline__ void Dz1GifImgDescr_delAndSetNull(void *ptr)
{
	Dz1GifImgDescr **p = (Dz1GifImgDescr **)ptr;
	if (p) { Dz1GifImgDescr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifImgDescr_dump(Dz1GifImgDescr *p, int tab);
// Dz1GifImgDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlCmd
typedef enum Dz1GifGraphicControlCmd
{
	Dz1GifGraphicControlCmd_noMean,
	Dz1GifGraphicControlCmd_doNotDispose,
	Dz1GifGraphicControlCmd_restoreToBgColor,
	Dz1GifGraphicControlCmd_restoreToPrev,
	Dz1GifGraphicControlCmd_max
} Dz1GifGraphicControlCmd;

DZ1_CPPLINK str_t Dz1GifGraphicControlCmdStrA(Dz1GifGraphicControlCmd v);
DZ1_CPPLINK Dz1GifGraphicControlCmd Dz1GifGraphicControlCmdFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GifGraphicControlCmdStrW(Dz1GifGraphicControlCmd v);
DZ1_CPPLINK Dz1GifGraphicControlCmd Dz1GifGraphicControlCmdFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GifGraphicControlCmdStr Dz1GifGraphicControlCmdStrW
#define Dz1GifGraphicControlCmdFromStr Dz1GifGraphicControlCmdFromStrW
#else // UNICODE
#define Dz1GifGraphicControlCmdStr Dz1GifGraphicControlCmdStrA
#define Dz1GifGraphicControlCmdFromStr Dz1GifGraphicControlCmdFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GifGraphicControlCmdStr Dz1GifGraphicControlCmdStrA
#define Dz1GifGraphicControlCmdFromStr Dz1GifGraphicControlCmdFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GifGraphicControlCmd *Dz1GifGraphicControlCmd_new(Dz1GifGraphicControlCmd *src, Dz1Error *err);
static __inline__ Dz1GifGraphicControlCmd *Dz1GifGraphicControlCmd_gen(Dz1Error *err) { Dz1GifGraphicControlCmd v = Dz1GifGraphicControlCmd_max; return Dz1GifGraphicControlCmd_new(&v, err); }
static __inline__ void Dz1GifGraphicControlCmd_del(Dz1GifGraphicControlCmd *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GifGraphicControlCmd_delAndSetNull(void *ptr)
{
	Dz1GifGraphicControlCmd **p = (Dz1GifGraphicControlCmd **)ptr;
	if (p != NULL) { Dz1GifGraphicControlCmd_del(*p); *p = NULL; }
}
// Dz1GifGraphicControlCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlExt
typedef struct Dz1GifGraphicControlExt
{
	Dz1GifGraphicControlCmd		disposal;
	bool_t						userInput;
	bool_t						tpColPresent;
	u16_t						delay;
	u8_t						tpColorIdx;
} Dz1GifGraphicControlExt;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_new(Dz1GifGraphicControlCmd disposal, 
																			 bool_t userInput, 
																			 bool_t tpColPresent, 
																			 u16_t delay, 
																			 u8_t tpColorIdx, Dz1Error *err);
static __inline__ Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_gen(Dz1Error *err) { return Dz1GifGraphicControlExt_new(Dz1GifGraphicControlCmd_max, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifGraphicControlExt_copy(Dz1GifGraphicControlExt *dst, Dz1GifGraphicControlExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_clone(Dz1GifGraphicControlExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphicControlExt_purge(Dz1GifGraphicControlExt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphicControlExt_del(Dz1GifGraphicControlExt *p);
static __inline__ void Dz1GifGraphicControlExt_delAndSetNull(void *ptr)
{
	Dz1GifGraphicControlExt **p = (Dz1GifGraphicControlExt **)ptr;
	if (p) { Dz1GifGraphicControlExt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphicControlExt_dump(Dz1GifGraphicControlExt *p, int tab);
// Dz1GifGraphicControlExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifCommentExt
typedef struct Dz1GifCommentExt
{
	str_t		text;
} Dz1GifCommentExt;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifCommentExt *Dz1GifCommentExt_new(str_t text, Dz1Error *err);
static __inline__ Dz1GifCommentExt *Dz1GifCommentExt_gen(Dz1Error *err) { return Dz1GifCommentExt_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifCommentExt_copy(Dz1GifCommentExt *dst, Dz1GifCommentExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifCommentExt *Dz1GifCommentExt_clone(Dz1GifCommentExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifCommentExt_purge(Dz1GifCommentExt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifCommentExt_del(Dz1GifCommentExt *p);
static __inline__ void Dz1GifCommentExt_delAndSetNull(void *ptr)
{
	Dz1GifCommentExt **p = (Dz1GifCommentExt **)ptr;
	if (p) { Dz1GifCommentExt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifCommentExt_dump(Dz1GifCommentExt *p, int tab);
// Dz1GifCommentExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifAppExt
typedef struct Dz1GifAppExt
{
	str_t			 app;
	Dz1Binary		*app_auth;
	Dz1Binary		*app_data;
} Dz1GifAppExt;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifAppExt *Dz1GifAppExt_new(str_t app, 
													   Dz1Binary *app_auth, 
													   Dz1Binary *app_data, Dz1Error *err);
static __inline__ Dz1GifAppExt *Dz1GifAppExt_gen(Dz1Error *err) { return Dz1GifAppExt_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifAppExt_copy(Dz1GifAppExt *dst, Dz1GifAppExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifAppExt *Dz1GifAppExt_clone(Dz1GifAppExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifAppExt_purge(Dz1GifAppExt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifAppExt_del(Dz1GifAppExt *p);
static __inline__ void Dz1GifAppExt_delAndSetNull(void *ptr)
{
	Dz1GifAppExt **p = (Dz1GifAppExt **)ptr;
	if (p) { Dz1GifAppExt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifAppExt_dump(Dz1GifAppExt *p, int tab);
// Dz1GifAppExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderPlainTextExt
typedef struct Dz1GifRenderPlainTextExt
{
	u16_t		x;
	u16_t		y;
	u16_t		width;
	u16_t		height;
	u8_t		cellWidth;
	u8_t		cellHeight;
	u8_t		fgColorIdx;
	u8_t		bgColorIdx;
	str_t		text;
} Dz1GifRenderPlainTextExt;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_new(u16_t x, 
																			   u16_t y, 
																			   u16_t width, 
																			   u16_t height, 
																			   u8_t cellWidth, 
																			   u8_t cellHeight, 
																			   u8_t fgColorIdx, 
																			   u8_t bgColorIdx, 
																			   str_t text, Dz1Error *err);
static __inline__ Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_gen(Dz1Error *err) { return Dz1GifRenderPlainTextExt_new(0, 0, 0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifRenderPlainTextExt_copy(Dz1GifRenderPlainTextExt *dst, Dz1GifRenderPlainTextExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_clone(Dz1GifRenderPlainTextExt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderPlainTextExt_purge(Dz1GifRenderPlainTextExt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderPlainTextExt_del(Dz1GifRenderPlainTextExt *p);
static __inline__ void Dz1GifRenderPlainTextExt_delAndSetNull(void *ptr)
{
	Dz1GifRenderPlainTextExt **p = (Dz1GifRenderPlainTextExt **)ptr;
	if (p) { Dz1GifRenderPlainTextExt_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderPlainTextExt_dump(Dz1GifRenderPlainTextExt *p, int tab);
// Dz1GifRenderPlainTextExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifTableBasedImgData
typedef struct Dz1GifTableBasedImgData
{
	u8_t			 lzwMinimumCodeSize;
	Dz1Binary		*lzw;
} Dz1GifTableBasedImgData;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_new(u8_t lzwMinimumCodeSize, 
																			 Dz1Binary *lzw, Dz1Error *err);
static __inline__ Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_gen(Dz1Error *err) { return Dz1GifTableBasedImgData_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifTableBasedImgData_copy(Dz1GifTableBasedImgData *dst, Dz1GifTableBasedImgData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_clone(Dz1GifTableBasedImgData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifTableBasedImgData_purge(Dz1GifTableBasedImgData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifTableBasedImgData_del(Dz1GifTableBasedImgData *p);
static __inline__ void Dz1GifTableBasedImgData_delAndSetNull(void *ptr)
{
	Dz1GifTableBasedImgData **p = (Dz1GifTableBasedImgData **)ptr;
	if (p) { Dz1GifTableBasedImgData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifTableBasedImgData_dump(Dz1GifTableBasedImgData *p, int tab);
// Dz1GifTableBasedImgData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderTableBasedImg
typedef struct Dz1GifRenderTableBasedImg
{
	Dz1GifImgDescr				*descr;
	Dz1Binary					*pixels;
	Dz1GifTableBasedImgData		*lzw;
} Dz1GifRenderTableBasedImg;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_new(Dz1GifImgDescr *descr, 
																				 Dz1Binary *pixels, 
																				 Dz1GifTableBasedImgData *lzw, Dz1Error *err);
static __inline__ Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_gen(Dz1Error *err) { return Dz1GifRenderTableBasedImg_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifRenderTableBasedImg_copy(Dz1GifRenderTableBasedImg *dst, Dz1GifRenderTableBasedImg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_clone(Dz1GifRenderTableBasedImg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderTableBasedImg_purge(Dz1GifRenderTableBasedImg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderTableBasedImg_del(Dz1GifRenderTableBasedImg *p);
static __inline__ void Dz1GifRenderTableBasedImg_delAndSetNull(void *ptr)
{
	Dz1GifRenderTableBasedImg **p = (Dz1GifRenderTableBasedImg **)ptr;
	if (p) { Dz1GifRenderTableBasedImg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderTableBasedImg_dump(Dz1GifRenderTableBasedImg *p, int tab);
// Dz1GifRenderTableBasedImg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingDataPresent
typedef enum Dz1GifRenderingDataPresent
{
	Dz1GifRenderingDataPresent_tbi,
	Dz1GifRenderingDataPresent_pte,
	Dz1GifRenderingDataPresent_max
} Dz1GifRenderingDataPresent;

DZ1_CPPLINK str_t Dz1GifRenderingDataPresentStrA(Dz1GifRenderingDataPresent v);
DZ1_CPPLINK Dz1GifRenderingDataPresent Dz1GifRenderingDataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GifRenderingDataPresentStrW(Dz1GifRenderingDataPresent v);
DZ1_CPPLINK Dz1GifRenderingDataPresent Dz1GifRenderingDataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GifRenderingDataPresentStr Dz1GifRenderingDataPresentStrW
#define Dz1GifRenderingDataPresentFromStr Dz1GifRenderingDataPresentFromStrW
#else // UNICODE
#define Dz1GifRenderingDataPresentStr Dz1GifRenderingDataPresentStrA
#define Dz1GifRenderingDataPresentFromStr Dz1GifRenderingDataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GifRenderingDataPresentStr Dz1GifRenderingDataPresentStrA
#define Dz1GifRenderingDataPresentFromStr Dz1GifRenderingDataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderingDataPresent *Dz1GifRenderingDataPresent_new(Dz1GifRenderingDataPresent *src, Dz1Error *err);
static __inline__ Dz1GifRenderingDataPresent *Dz1GifRenderingDataPresent_gen(Dz1Error *err) { Dz1GifRenderingDataPresent v = Dz1GifRenderingDataPresent_max; return Dz1GifRenderingDataPresent_new(&v, err); }
#define Dz1GifRenderingDataPresent_clone             Dz1GifRenderingDataPresent_new
static __inline__ void Dz1GifRenderingDataPresent_del(Dz1GifRenderingDataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GifRenderingDataPresent_delAndSetNull(void *ptr)
{
	Dz1GifRenderingDataPresent **p = (Dz1GifRenderingDataPresent **)ptr;
	if (p != NULL) { Dz1GifRenderingDataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderingDataPresent_dump(Dz1GifRenderingDataPresent *v, int tab);
// Dz1GifRenderingDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingData
typedef struct Dz1GifRenderingData
{
	Dz1GifRenderingDataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1GifRenderTableBasedImg		*tbi;
		Dz1GifRenderPlainTextExt		*pte;
	} x;
} Dz1GifRenderingData;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderingData *Dz1GifRenderingData_new(Dz1GifRenderingDataPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1GifRenderingData *Dz1GifRenderingData_gen(Dz1Error *err) { return Dz1GifRenderingData_new(Dz1GifRenderingDataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1GifRenderingData_copy(Dz1GifRenderingData *dst, Dz1GifRenderingData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifRenderingData *Dz1GifRenderingData_clone(Dz1GifRenderingData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderingData_purge(Dz1GifRenderingData *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderingData_del(Dz1GifRenderingData *p);
static __inline__ void Dz1GifRenderingData_delAndSetNull(void *ptr)
{
	Dz1GifRenderingData **p = (Dz1GifRenderingData **)ptr;
	if (p != NULL) { Dz1GifRenderingData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifRenderingData_dump(Dz1GifRenderingData *p, int tab);
// Dz1GifRenderingData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphic
typedef struct Dz1GifGraphic
{
	Dz1GifGraphicControlExt		*gce;
	Dz1GifRenderingData			*data;
	u32_t						 thid;
	bool_t						 isDone;
} Dz1GifGraphic;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifGraphic *Dz1GifGraphic_new(Dz1GifGraphicControlExt *gce, 
														 Dz1GifRenderingData *data, 
														 u32_t thid, 
														 bool_t isDone, Dz1Error *err);
static __inline__ Dz1GifGraphic *Dz1GifGraphic_gen(Dz1Error *err) { return Dz1GifGraphic_new(NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1GifGraphic_copy(Dz1GifGraphic *dst, Dz1GifGraphic *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifGraphic *Dz1GifGraphic_clone(Dz1GifGraphic *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphic_purge(Dz1GifGraphic *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphic_del(Dz1GifGraphic *p);
static __inline__ void Dz1GifGraphic_delAndSetNull(void *ptr)
{
	Dz1GifGraphic **p = (Dz1GifGraphic **)ptr;
	if (p) { Dz1GifGraphic_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifGraphic_dump(Dz1GifGraphic *p, int tab);
// Dz1GifGraphic
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntryPresent
typedef enum Dz1GifDataEntryPresent
{
	Dz1GifDataEntryPresent_graphic,
	Dz1GifDataEntryPresent_app_ext,
	Dz1GifDataEntryPresent_comment,
	Dz1GifDataEntryPresent_max
} Dz1GifDataEntryPresent;

DZ1_CPPLINK str_t Dz1GifDataEntryPresentStrA(Dz1GifDataEntryPresent v);
DZ1_CPPLINK Dz1GifDataEntryPresent Dz1GifDataEntryPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GifDataEntryPresentStrW(Dz1GifDataEntryPresent v);
DZ1_CPPLINK Dz1GifDataEntryPresent Dz1GifDataEntryPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GifDataEntryPresentStr Dz1GifDataEntryPresentStrW
#define Dz1GifDataEntryPresentFromStr Dz1GifDataEntryPresentFromStrW
#else // UNICODE
#define Dz1GifDataEntryPresentStr Dz1GifDataEntryPresentStrA
#define Dz1GifDataEntryPresentFromStr Dz1GifDataEntryPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GifDataEntryPresentStr Dz1GifDataEntryPresentStrA
#define Dz1GifDataEntryPresentFromStr Dz1GifDataEntryPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataEntryPresent *Dz1GifDataEntryPresent_new(Dz1GifDataEntryPresent *src, Dz1Error *err);
static __inline__ Dz1GifDataEntryPresent *Dz1GifDataEntryPresent_gen(Dz1Error *err) { Dz1GifDataEntryPresent v = Dz1GifDataEntryPresent_max; return Dz1GifDataEntryPresent_new(&v, err); }
#define Dz1GifDataEntryPresent_clone             Dz1GifDataEntryPresent_new
static __inline__ void Dz1GifDataEntryPresent_del(Dz1GifDataEntryPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GifDataEntryPresent_delAndSetNull(void *ptr)
{
	Dz1GifDataEntryPresent **p = (Dz1GifDataEntryPresent **)ptr;
	if (p != NULL) { Dz1GifDataEntryPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataEntryPresent_dump(Dz1GifDataEntryPresent *v, int tab);
// Dz1GifDataEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntry
typedef struct Dz1GifDataEntry
{
	Dz1GifDataEntryPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1GifGraphic		*graphic;
		Dz1GifAppExt		*app_ext;
		Dz1GifCommentExt	*comment;
	} x;
} Dz1GifDataEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataEntry *Dz1GifDataEntry_new(Dz1GifDataEntryPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1GifDataEntry *Dz1GifDataEntry_gen(Dz1Error *err) { return Dz1GifDataEntry_new(Dz1GifDataEntryPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Dz1GifDataEntry_copy(Dz1GifDataEntry *dst, Dz1GifDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataEntry *Dz1GifDataEntry_clone(Dz1GifDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataEntry_purge(Dz1GifDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataEntry_del(Dz1GifDataEntry *p);
static __inline__ void Dz1GifDataEntry_delAndSetNull(void *ptr)
{
	Dz1GifDataEntry **p = (Dz1GifDataEntry **)ptr;
	if (p != NULL) { Dz1GifDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataEntry_dump(Dz1GifDataEntry *p, int tab);
// Dz1GifDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataArr
typedef struct Dz1GifDataArr
{
	void *storage;
	unsigned int (*count)(struct Dz1GifDataArr *p);
	Dz1Error (*travel)(struct Dz1GifDataArr *p, Dz1Error (*func)(void *ptr, Dz1GifDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1GifDataArr *p, Dz1Error (*func)(void *ptr, Dz1GifDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1GifDataArr *p, Dz1Error (*func)(void *ptr, Dz1GifDataEntry *entry), void *ptr);
	Dz1GifDataEntry **(*get_array)(struct Dz1GifDataArr *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1GifDataArr *p, Dz1GifDataEntry *data);
} Dz1GifDataArr;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataArr *Dz1GifDataArr_new(Dz1Error *err);
static __inline__ Dz1GifDataArr *Dz1GifDataArr_gen(Dz1Error *err) { return Dz1GifDataArr_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1GifDataArr *Dz1GifDataArr_clone(Dz1GifDataArr *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataArr_purge(Dz1GifDataArr *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataArr_del(Dz1GifDataArr *p);
static __inline__ void Dz1GifDataArr_delAndSetNull(void *ptr)
{
	Dz1GifDataArr **p = (Dz1GifDataArr **)ptr;
	if (p != NULL) { Dz1GifDataArr_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDataArr_dump(Dz1GifDataArr *p, int tab);

// Dz1GifDataArr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Gif
typedef struct Dz1Gif
{
	Dz1GifHeader		*hdr;
	Dz1GifDescr			*descr;
	Dz1GifDataArr		*datas;
} Dz1Gif;

DZ1_CPPLINK DZ1_DLLPORT Dz1Gif *Dz1Gif_new(Dz1GifHeader *hdr, 
										   Dz1GifDescr *descr, Dz1Error *err);
static __inline__ Dz1Gif *Dz1Gif_gen(Dz1Error *err) { return Dz1Gif_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1Gif_copy(Dz1Gif *dst, Dz1Gif *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Gif *Dz1Gif_clone(Dz1Gif *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Gif_purge(Dz1Gif *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Gif_del(Dz1Gif *p);
static __inline__ void Dz1Gif_delAndSetNull(void *ptr)
{
	Dz1Gif **p = (Dz1Gif **)ptr;
	if (p) { Dz1Gif_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1Gif_dump(Dz1Gif *p, int tab);
// Dz1Gif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptParallel
typedef struct Dz1GifDecodeOptParallel
{
	Dz1Sync		*sync;
	u32_t		 seq;
} Dz1GifDecodeOptParallel;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDecodeOptParallel *Dz1GifDecodeOptParallel_new(Dz1Sync *sync, Dz1Error *err);
static __inline__ Dz1GifDecodeOptParallel *Dz1GifDecodeOptParallel_gen(Dz1Error *err) { return Dz1GifDecodeOptParallel_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOptParallel_purge(Dz1GifDecodeOptParallel *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOptParallel_del(Dz1GifDecodeOptParallel *p);
static __inline__ void Dz1GifDecodeOptParallel_delAndSetNull(void *ptr)
{
	Dz1GifDecodeOptParallel **p = (Dz1GifDecodeOptParallel **)ptr;
	if (p) { Dz1GifDecodeOptParallel_del(*p); *p = NULL; }
}
// Dz1GifDecodeOptParallel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptUserFunc
typedef void (*Dz1GifDecodeOptUserFunc)(
					void *user_ptr, 
					u32_t seq, 
					u32_t dur_ms, 
					Dz1BMP *image);
// Dz1GifDecodeOptUserFunc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptSequential
typedef struct Dz1GifDecodeOptSequential
{
	Dz1BMP						*canvas;
	Dz1BMP						*last;
	Dz1GifGraphicControlCmd		 prev_dispos;
	u32_t						 seq;
	Dz1GifDecodeOptUserFunc		 user_handle;
	void						*user_ptr;
} Dz1GifDecodeOptSequential;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDecodeOptSequential *Dz1GifDecodeOptSequential_new(Dz1GifDecodeOptUserFunc user_handle, 
																				 void *user_ptr, Dz1Error *err);
static __inline__ Dz1GifDecodeOptSequential *Dz1GifDecodeOptSequential_gen(Dz1Error *err) { return Dz1GifDecodeOptSequential_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOptSequential_purge(Dz1GifDecodeOptSequential *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOptSequential_del(Dz1GifDecodeOptSequential *p);
static __inline__ void Dz1GifDecodeOptSequential_delAndSetNull(void *ptr)
{
	Dz1GifDecodeOptSequential **p = (Dz1GifDecodeOptSequential **)ptr;
	if (p) { Dz1GifDecodeOptSequential_del(*p); *p = NULL; }
}
// Dz1GifDecodeOptSequential
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptPresent
typedef enum Dz1GifDecodeOptPresent
{
	Dz1GifDecodeOptPresent_parallel,
	Dz1GifDecodeOptPresent_sequential,
	Dz1GifDecodeOptPresent_max
} Dz1GifDecodeOptPresent;

DZ1_CPPLINK str_t Dz1GifDecodeOptPresentStrA(Dz1GifDecodeOptPresent v);
DZ1_CPPLINK Dz1GifDecodeOptPresent Dz1GifDecodeOptPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1GifDecodeOptPresentStrW(Dz1GifDecodeOptPresent v);
DZ1_CPPLINK Dz1GifDecodeOptPresent Dz1GifDecodeOptPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1GifDecodeOptPresentStr Dz1GifDecodeOptPresentStrW
#define Dz1GifDecodeOptPresentFromStr Dz1GifDecodeOptPresentFromStrW
#else // UNICODE
#define Dz1GifDecodeOptPresentStr Dz1GifDecodeOptPresentStrA
#define Dz1GifDecodeOptPresentFromStr Dz1GifDecodeOptPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1GifDecodeOptPresentStr Dz1GifDecodeOptPresentStrA
#define Dz1GifDecodeOptPresentFromStr Dz1GifDecodeOptPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1GifDecodeOptPresent *Dz1GifDecodeOptPresent_new(Dz1GifDecodeOptPresent *src, Dz1Error *err);
static __inline__ Dz1GifDecodeOptPresent *Dz1GifDecodeOptPresent_gen(Dz1Error *err) { Dz1GifDecodeOptPresent v = Dz1GifDecodeOptPresent_max; return Dz1GifDecodeOptPresent_new(&v, err); }
static __inline__ void Dz1GifDecodeOptPresent_del(Dz1GifDecodeOptPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1GifDecodeOptPresent_delAndSetNull(void *ptr)
{
	Dz1GifDecodeOptPresent **p = (Dz1GifDecodeOptPresent **)ptr;
	if (p != NULL) { Dz1GifDecodeOptPresent_del(*p); *p = NULL; }
}
// Dz1GifDecodeOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOpt
typedef struct Dz1GifDecodeOpt
{
	Dz1GifDecodeOptPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1GifDecodeOptParallel			*parallel;
		Dz1GifDecodeOptSequential		*sequential;
	} x;
} Dz1GifDecodeOpt;

DZ1_CPPLINK DZ1_DLLPORT Dz1GifDecodeOpt *Dz1GifDecodeOpt_new(Dz1GifDecodeOptPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1GifDecodeOpt *Dz1GifDecodeOpt_gen(Dz1Error *err) { return Dz1GifDecodeOpt_new(Dz1GifDecodeOptPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOpt_purge(Dz1GifDecodeOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1GifDecodeOpt_del(Dz1GifDecodeOpt *p);
static __inline__ void Dz1GifDecodeOpt_delAndSetNull(void *ptr)
{
	Dz1GifDecodeOpt **p = (Dz1GifDecodeOpt **)ptr;
	if (p != NULL) { Dz1GifDecodeOpt_del(*p); *p = NULL; }
}
// Dz1GifDecodeOpt
////////////////////////////////////////////////////////////////////////////////

#endif
