#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include "dz1_file_buf_stream.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1FileBufPos API
Dz1FileBufPos *Dz1FileBufPos_new(u32_t id, s64_t pos, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufPos *ret = (Dz1FileBufPos *)Dz1Calloc(sizeof(Dz1FileBufPos), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileBufPos_delAndSetNull, (void *)&ret);

		ret->id = id;
		ret->pos = pos;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1FileBufPos *Dz1FileBufPos_clone(Dz1FileBufPos *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufPos *ret = (Dz1FileBufPos *)Dz1Calloc(sizeof(Dz1FileBufPos), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileBufPos_delAndSetNull, (void *)&ret);

		ret->id = src->id;
		ret->pos = src->pos;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1FileBufPos_del(Dz1FileBufPos *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1Free(p);
}

void Dz1FileBufPosA_dump(Dz1FileBufPos *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// Additional print code here
		Dz1ThreadA_tprintf(tab, "id = %08X\n", p->id);
		Dz1ThreadA_tprintf(tab, "pos = " DZ1_FMT64_A"\n", p->pos);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}

void Dz1FileBufPosA_fdump(FILE *fp, Dz1FileBufPos *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// Additional print code here
		Dz1ThreadA_ftprintf(fp, tab, "id = %08X\n", p->id);
		Dz1ThreadA_ftprintf(fp, tab, "pos = " DZ1_FMT64_A"\n", p->pos);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1FileBufPosW_dump(Dz1FileBufPos *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Additional print code here
		Dz1ThreadW_tprintf(tab, L"id = %08X\n", p->id);
		Dz1ThreadW_tprintf(tab, L"pos = " DZ1_FMT64_W L"\n", p->pos);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}

void Dz1FileBufPosW_fdump(FILE *fp, Dz1FileBufPos *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// Additional print code here
		Dz1ThreadW_ftprintf(fp, tab, L"id = %08X\n", p->id);
		Dz1ThreadW_ftprintf(fp, tab, L"pos = " DZ1_FMT64_W L"\n", p->pos);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif
int Dz1FileBufPos_cmp(Dz1FileBufPos *a, Dz1FileBufPos *b)
{
	int ret = 0;
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		// Additional compare code here
		ret = a->id - b->id;
	}
	return ret;
}
// Dz1FileBufPos API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1FileBufStream API
Dz1FileBufStream *Dz1FileBufStream_new(FILE *fp, Dz1StreamFileMode mode, bool_t fp_isRef, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufStream *ret = NULL;
	if (fp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1FileBufStream *)Dz1Calloc(sizeof(Dz1FileBufStream), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileBufStream_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else if ((ret->user_cursors = Dz1AATree_new((Dz1CmpFunc)Dz1FileBufPos_cmp,
													(Dz1DelFunc)Dz1FileBufPos_del,
													(Dz1DumpFunc)Dz1FileBufPos_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->fp = fp;
			ret->fp_isRef = fp_isRef;
			ret->drain_offset = 0;
			ret->alloc_id = 0;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (WaveRileyDataList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1FileBufStream_del(Dz1FileBufStream *p)
{
	if (!p) return;
	// Additional delete code here
	if (p->fp && p->fp_isRef == FALSE) Dz1FileStream_closeAndSetNull(&p->fp);
	Dz1AATree_delAndSetNull(&p->user_cursors);
	Dz1Free(p);
}

void Dz1FileBufStreamA_dump(Dz1FileBufStream *p, int tab)
{
	if (!p) { Dz1ThreadA_printf("NULL\n"); return; }
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		// Additional print code here
		Dz1ThreadA_tprintf(tab, "FP = %p%s\n", p->fp, p->fp_isRef ? "(ref)" : "");
		Dz1ThreadA_tprintf(tab, "drain_offset = " DZ1_FMT64_A"\n", p->drain_offset);
		Dz1ThreadA_tprintf(tab, "alloc_id = %u\n", p->alloc_id);
		Dz1ThreadA_tprintf(tab, "user_cursors = "); Dz1AATree_dump(p->user_cursors, tab);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}

void Dz1FileBufStreamA_fdump(FILE *fp, Dz1FileBufStream *p, int tab)
{
	if (!p) { Dz1ThreadA_fprintf(fp, "NULL\n"); return; }
	else
	{
		Dz1ThreadA_fprintf(fp, "{\n"); tab++;
		// Additional print code here
		Dz1ThreadA_ftprintf(fp, tab, "FP = %p\n", p->fp);
		Dz1ThreadA_ftprintf(fp, tab, "drain_offset = " DZ1_FMT64_A"\n", p->drain_offset);
		Dz1ThreadA_ftprintf(fp, tab, "alloc_id = %u\n", p->alloc_id);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
void Dz1FileBufStreamW_dump(Dz1FileBufStream *p, int tab)
{
	if (!p) { Dz1ThreadW_printf(L"NULL\n"); return; }
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		// Additional print code here
		Dz1ThreadW_tprintf(tab, L"FP = %p%s\n", p->fp, p->fp_isRef ? L"(ref)" : L"");
		Dz1ThreadW_tprintf(tab, L"drain_offset = " DZ1_FMT64_W L"\n", p->drain_offset);
		Dz1ThreadW_tprintf(tab, L"alloc_id = %u\n", p->alloc_id);
		Dz1ThreadW_tprintf(tab, L"user_cursors = "); Dz1AATree_dump(p->user_cursors, tab);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}

void Dz1FileBufStreamW_fdump(FILE *fp, Dz1FileBufStream *p, int tab)
{
	if (!p) { Dz1ThreadW_fprintf(fp, L"NULL\n"); return; }
	else
	{
		Dz1ThreadW_fprintf(fp, L"{\n"); tab++;
		// Additional print code here
		Dz1ThreadW_ftprintf(fp, tab, L"FP = %p\n", p->fp);
		Dz1ThreadW_ftprintf(fp, tab, L"drain_offset = " DZ1_FMT64_W L"\n", p->drain_offset);
		Dz1ThreadW_ftprintf(fp, tab, L"alloc_id = %u\n", p->alloc_id);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif
// Dz1FileBufStream API
////////////////////////////////////////////////////////////////////////////////


/*
Randon Access는 기본
r, r+은 파일 없으면 Error 있으면 유지		// 읽기(+쓰기)
w, w+는 파일 없으면 만들고 있으면 초기화	// 쓰기(+읽기)
a, a+는 파일 없으면 만들고 있으면 유지		// 쓰기(+읽기)

"r" : Opens for reading. If the file does not exist or cannot be found, the fopen call fails.
"w" : Opens an empty file for writing. If the given file exists, its contents are destroyed.
"a" : Opens for writing at the end of the file (appending) without removing the EOF marker before writing new data to the file;
      creates the file first if it doesn't exist.

"r+": Opens for both reading and writing. (The file must exist.)
"w+": Opens an empty file for both reading and writing. If the given file exists, its contents are destroyed.
"a+": Opens for reading and appending;
      the appending operation includes the removal of the EOF marker before new data is written to the file and
	  the EOF marker is restored after writing is complete;
	  creates the file first if it doesn't exist.

When a file is opened with the "a" or "a+" access type, all write operations occur at the end of the file.
The file pointer can be repositioned using fseek or rewind, but is always moved back to the end of the file
before any write operation is carried out. Thus, existing data cannot be overwritten.

The "a" mode does not remove the EOF marker before appending to the file.
After appending has occurred, the MS-DOS TYPE command only shows data up to the original EOF marker and not any data appended to the file.
The "a+" mode does remove the EOF marker before appending to the file.
After appending, the MS-DOS TYPE command shows all data in the file.
The "a+" mode is required for appending to a stream file that is terminated with the CTRL+Z EOF marker.

When the "r+", "w+", or "a+" access type is specified, both reading and writing are allowed
(the file is said to be open for "update"). However, when you switch between reading and writing,
there must be an intervening fflush, fsetpos, fseek, or rewind operation.
The current position can be specified for the fsetpos or fseek operation, if desired.

In addition to the above values, the following characters can be included in mode to specify the translation mode for newline characters: 

t  : Open in text (translated) mode.
	 In this mode, CTRL+Z is interpreted as an end-of-file character on input.
	 In files opened for reading/writing with "a+", fopen checks for a CTRL+Z at the end of the file and removes it, if possible.
	 This is done because using fseek and ftell to move within a file that ends with a CTRL+Z, may cause fseek to behave improperly
	 near the end of the file. 
	 
	 Also, in text mode, carriage return?linefeed combinations are translated into single line feeds on input,
	 and linefeed characters are translated to carriage return?linefeed combinations on output.
	 When a Unicode stream-I/O function operates in text mode (the default), the source or destination stream is
	 assumed to be a sequence of multi-byte characters.
	 Therefore, the Unicode stream-input functions convert multi-byte characters to wide characters
	 (as if by a call to the mbtowc function).
	 For the same reason, the Unicode stream-output functions convert wide characters to multi-byte characters
	 (as if by a call to the wctomb function). 

b  : Open in binary (untranslated) mode; translations involving carriage-return and linefeed characters are suppressed. 

If t or b is not given in mode, the default translation mode is defined by the global variable _fmode.
If t or b is prefixed to the argument, the function fails and returns NULL. 
*/

// typedef struct Dz1StreamFileModeAttrMap
// {
// 	Dz1StreamFileMode			mode;
// 	str_t						attrA;
// 	wstr_t						attrW;
// } Dz1StreamFileModeAttrMap;
// 
// static Dz1StreamFileModeAttrMap fileModeAttrMap[] =
// {
// 	{ Dz1StreamFileMode_RD,		"rb",  L"rb" },		// 읽기만						"rb"
// 
// 	{ Dz1StreamFileMode_WR,		"wb",  L"wb" },		// 쓰기만	(기존 데이터 삭제)	"wb"
// 	{ Dz1StreamFileMode_WRKD,	"ab",  L"ab" },		// 쓰기만	(기존 데이터 유지)	"ab"
// 
// 	{ Dz1StreamFileMode_RDWR,	"w+b", L"w+b" },	// 읽고 쓰기(기존 데이터 삭제)	"w+b"
// //	{ Dz1StreamFileMode_RWKD,	"r+b", L"r+b" },	// 읽고 쓰기(기존 데이터 유지)	"r+b" -> "w+b"
// 
// 	{ -1, NULL, NULL }
// };
// 
// static Dz1StreamFileModeAttrMap *_find_attr_map(Dz1StreamFileMode mode)
// {
// 	Dz1StreamFileModeAttrMap *i;
// 	for (i = fileModeAttrMap; i->attrA != NULL; i++)
// 		if (i->mode == mode) return i;
// 	return NULL;
// }

#define IO_MODE_READ			0x80000000
#define IO_MODE_WRITE			0x40000000

#define IO_INIT_DATA_IGNORE				0
#define IO_INIT_DATA_CLEAR				1
#define IO_INIT_DATA_KEEP_POS_HEAD		2
#define IO_INIT_DATA_KEEP_POS_TAIL		3

static bool_t _mode_opt_detect(Dz1StreamFileMode mode, u32_t *ret_io_mode, u32_t *ret_init_data)
{
	bool_t ret = TRUE;
	switch(mode)
	{
	case Dz1StreamFileMode_RD:			// 읽기만								"rb"
		(*ret_io_mode) = IO_MODE_READ;
		(*ret_init_data) = IO_INIT_DATA_IGNORE;
		break;
	case Dz1StreamFileMode_WR:			// 쓰기만	(기존 데이터 삭제)			"wb"
		(*ret_io_mode) = IO_MODE_WRITE;
		(*ret_init_data) = IO_INIT_DATA_CLEAR;
		break;
	case Dz1StreamFileMode_WRO:			// 쓰기만	(기존 데이터 유지)			"r+b" -> "w+b"
		(*ret_io_mode) = IO_MODE_WRITE;
		(*ret_init_data) = IO_INIT_DATA_KEEP_POS_HEAD;
		break;
	case Dz1StreamFileMode_WRA:			// 쓰기만	(기존 데이터 유지, 맨끝)	"a+b"
		(*ret_io_mode) = IO_MODE_WRITE;
		(*ret_init_data) = IO_INIT_DATA_KEEP_POS_TAIL;
		break;
	case Dz1StreamFileMode_RW:			// 읽고 쓰기(기존 데이터 삭제)			"w+b"
		(*ret_io_mode) = IO_MODE_WRITE | IO_MODE_READ;
		(*ret_init_data) = IO_INIT_DATA_CLEAR;
		break;
	case Dz1StreamFileMode_RWO:			// 읽고 쓰기(기존 데이터 유지)			"r+b" -> "w+b"
		(*ret_io_mode) = IO_MODE_WRITE | IO_MODE_READ;
		(*ret_init_data) = IO_INIT_DATA_KEEP_POS_HEAD;
		break;
	case Dz1StreamFileMode_RWA:			// 읽고 쓰기(기존 데이터 유지, 맨끝)	"a+b"
		(*ret_io_mode) = IO_MODE_WRITE | IO_MODE_READ;
		(*ret_init_data) = IO_INIT_DATA_KEEP_POS_TAIL;
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

static FILE *_mode_A_open(str_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	u32_t io_mode = 0, init_mode = 0;
	bool_t exist = Dz1FileA_isExist(fn);
	char *io_mode_str = NULL;

	if (_mode_opt_detect(mode, &io_mode, &init_mode) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if (exist)
	{	// 파일이 존재함
		if (io_mode & IO_MODE_READ)
		{
			if (io_mode & IO_MODE_WRITE)
			{	// RW
				if (init_mode == IO_INIT_DATA_CLEAR)
					io_mode_str = (str_t)"w+b";
				else io_mode_str = (str_t)"r+b";
			}
			else
			{	// RD
				if (init_mode == IO_INIT_DATA_CLEAR)
					io_mode_str = (str_t)"w+b";
				else io_mode_str = (str_t)"rb";
			}
		}
		else if (io_mode & IO_MODE_WRITE)
		{	// WR
			if (init_mode == IO_INIT_DATA_CLEAR)
				io_mode_str = (str_t)"wb";
			else io_mode_str = (str_t)"a+b";
		}
	}
	else
	{	// 존재하지 않음
		if (io_mode & IO_MODE_READ) io_mode_str = (str_t)"w+b";
		else if (io_mode & IO_MODE_WRITE) io_mode_str = (str_t)"wb";
	}

	if (io_mode_str == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamA_open(fn, io_mode_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		switch(init_mode)
		{
		case IO_INIT_DATA_KEEP_POS_HEAD:
			fseek(fp, 0, SEEK_SET);
			break;
		case IO_INIT_DATA_KEEP_POS_TAIL:
			fseek(fp, 0, SEEK_END);
			break;
		}
	}
	return fp;
}

#ifndef UNIX_SYSTEM
static FILE *_mode_W_open(wstr_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	u32_t io_mode = 0, init_mode = 0;
	bool_t exist = Dz1FileW_isExist(fn);
	wchar_t *io_mode_str = NULL;
	if (_mode_opt_detect(mode, &io_mode, &init_mode) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else if (exist)
	{	// 파일이 존재함
		if (io_mode & IO_MODE_READ)
		{
			if (io_mode & IO_MODE_WRITE)
			{	// RW
				if (init_mode == IO_INIT_DATA_CLEAR)
					io_mode_str = (wstr_t)L"w+b";
				else io_mode_str = (wstr_t)L"r+b";
			}
			else
			{	// RD
				if (init_mode == IO_INIT_DATA_CLEAR)
					io_mode_str = (wstr_t)L"w+b";
				else io_mode_str = (wstr_t)L"rb";
			}
		}
		else if (io_mode & IO_MODE_WRITE)
		{	// WR
			if (init_mode == IO_INIT_DATA_CLEAR)
				io_mode_str = (wstr_t)L"wb";
			else io_mode_str = (wstr_t)L"a+b";
		}
	}
	else
	{	// 존재하지 않음
		if (io_mode & IO_MODE_READ) io_mode_str = (wstr_t)L"w+b";
		else if (io_mode & IO_MODE_WRITE) io_mode_str = (wstr_t)L"wb";
	}

	if (io_mode_str == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamW_open(fn, io_mode_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		switch(init_mode)
		{
		case IO_INIT_DATA_KEEP_POS_HEAD:
			fseek(fp, 0, SEEK_SET);
			break;
		case IO_INIT_DATA_KEEP_POS_TAIL:
			fseek(fp, 0, SEEK_END);
			break;
		}
	}
	return fp;

// 	FILE *fp = NULL;
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	if (mode == Dz1StreamFileMode_RWKD)
// 	{
// 		if ((fp = Dz1FileStreamW_open(fn, L"r+b", errp)) == NULL)
// 		{
// 			if ((fp = Dz1FileStreamW_open(fn, L"w+b", errp)) == NULL) ERR_OUT(errp);
// 			else Dz1Error_set(errp, 0);
// 		}
// 	}
// 	else
// 	{
// 		Dz1StreamFileModeAttrMap *op = _find_attr_map(mode);
// 		if ((fp = Dz1FileStreamW_open(fn, op->attrW, errp)) == NULL)
// 		{
// 			if (errp->code != ENOENT) ERR_OUT(errp);
// 		}
// 	}
// 	return fp;
}
#endif

Dz1FileBufStream *Dz1FileBufStreamA_open(str_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = _mode_A_open(fn, mode, errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
		if ((ret = Dz1FileBufStream_new(fp,  mode, FALSE, errp)) == NULL) ERR_OUT(errp);
		else { Dz1Error_set(errp, 0); fp = NULL; }
		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1FileBufStream *Dz1FileBufStreamW_open(wstr_t fn, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = _mode_W_open(fn, mode, errp);
	if (fp == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
		if ((ret = Dz1FileBufStream_new(fp, mode, FALSE, errp)) == NULL) ERR_OUT(errp);
		else { Dz1Error_set(errp, 0); fp = NULL; }
		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return ret;
}
#endif

Dz1FileBufStream *Dz1FileBufStreamA_open2(str_t path, str_t name, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;

	char fn[4096];
	//FILE *fp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(Dz1ArrParam(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1FileBufStreamA_open(fn, mode, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1FileBufStream *Dz1FileBufStreamW_open2(wstr_t path, wstr_t name, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;

	wchar_t fn[4096];
	//FILE *fp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(Dz1ArrParam(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1FileBufStreamW_open(fn, mode, errp)) == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else Dz1Error_set(errp, 0);

	return ret;
}
#endif

Dz1FileBufStream *Dz1FileBufStreamA_open3(str_t path, str_t name, str_t ext, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;

	char fn[4096];
	//FILE *fp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathNameExt(Dz1ArrParam(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1FileBufStreamA_open(fn, mode, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1FileBufStream *Dz1FileBufStreamW_open3(wstr_t path, wstr_t name, wstr_t ext, Dz1StreamFileMode mode, Dz1Error *err)
{
	Dz1FileBufStream *ret = NULL;

	wchar_t fn[4096];
	//FILE *fp = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathNameExt(Dz1ArrParam(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1FileBufStreamW_open(fn, mode, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}
#endif

static u32_t alloc_seq = 0;
u32_t Dz1FileBufStream_getCursor(Dz1FileBufStream *p, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t alloc_h = (alloc_seq++ << 16) & 0xFFFF0000;
		u32_t alloc_id = alloc_h | (p->alloc_id & 0xFFFF);
		Dz1FileBufPos *pos = Dz1FileBufPos_new(alloc_id, 0, errp);
		if (pos == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1FileBufPos_delAndSetNull, (void *)&pos);
			if ((*errp = Dz1AATree_insert(p->user_cursors, (void *)pos)).code) ERR_OUT(errp);
			else
			{
				pos = NULL;
				p->alloc_id++;
				Dz1Error_set(errp, 0);
				ret = alloc_id;
			}
			pthread_cleanup_pop(1); // (Dz1FileBufPos_delAndSetNull, (void *)&pos);
		}
	}
	return ret;
}

void Dz1FileBufStream_putCursor(Dz1FileBufStream *p, u32_t stream_id)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1FileBufPos key = { stream_id }, *node = NULL;
		if ((node = (Dz1FileBufPos *)Dz1AATree_extract(p->user_cursors, (void *)&key)) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			pthread_cleanup_push(Dz1FileBufPos_delAndSetNull, (void *)&node);
//			Dz1Thread_eprintf("Dz1FileBufStream_putCursor() : put cursor = %08X\n", node->id);
			pthread_cleanup_pop(1); // (Dz1FileBufPos_delAndSetNull, (void *)&node);
		}
	}
}

ssize_t Dz1FileBufStream_read(Dz1FileBufStream *p, u32_t stream_id, u8_t *dst, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || p->fp == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (size == 0) { }
	else if ((cursor = (Dz1FileBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_OUT_RET(errp, -1);
	else 
	{
		FILEPOSt pos = DZ1_FTELL(p->fp);
		FILEPOSt cursor_pos = p->drain_offset + cursor->pos;
		if (pos != cursor_pos && DZ1_FSEEK(p->fp, cursor_pos, SEEK_SET) != 0) ERR_SET_OUT(errp, errno);
		else if ((ret = (ssize_t)fread(dst, sizeof(u8_t), size, p->fp)) == 0)
		{
			if (feof(p->fp)) ERR_SET_RET(errp, EPIPE, -1);
			else ERR_SET_OUT_RET(errp, ferror(p->fp), -1);
		}
		else
		{
			cursor->pos += ret;
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

ssize_t Dz1FileBufStream_write(Dz1FileBufStream *p, u32_t stream_id, u8_t *src, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || p->fp == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (size == 0) { }
	else if ((cursor = (Dz1FileBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_OUT_RET(errp, -1);
	else 
	{
		FILEPOSt pos = DZ1_FTELL(p->fp);
		FILEPOSt cursor_pos = p->drain_offset + cursor->pos;
		if (pos != cursor_pos && DZ1_FSEEK(p->fp, cursor_pos, SEEK_SET) != 0) ERR_SET_OUT_RET(errp, errno, -1);
		else if ((ret = (ssize_t)fwrite(src, sizeof(u8_t), size, p->fp)) == 0)
		{
			if (feof(p->fp)) ERR_SET_OUT_RET(errp, EPIPE, -1);
			else ERR_SET_OUT_RET(errp, ferror(p->fp), -1);
		}
		else
		{
			cursor->pos += ret;
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

static Dz1Error _set_cursor_pos(Dz1FileBufStream *p, Dz1FileBufPos *cursor)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	FILEPOSt pos;
	if ((pos = DZ1_FTELL(p->fp)) < 0) ERR_SET_OUT(errp, errno);
	else
	{
		cursor->pos = pos - p->drain_offset;
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1FileBufStream_seek(Dz1FileBufStream *p, u32_t stream_id, s64_t movement, int origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1FileBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || p->fp == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (movement == 0) { }
	else if ((cursor = (Dz1FileBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_OUT(errp);
	else
	{
		FILEPOSt pos;
		switch(origin)
		{
		case SEEK_SET:
			pos = p->drain_offset + cursor->pos + movement;
			if (DZ1_FSEEK(p->fp, pos, SEEK_SET) != 0) ERR_SET_OUT(errp, errno);
			else if ((*errp = _set_cursor_pos(p, cursor)).code) ERR_OUT(errp);
			break;
		case SEEK_END:
		case SEEK_CUR:
			if (DZ1_FSEEK(p->fp, movement, origin) != 0) ERR_SET_OUT(errp, errno);
			else if ((*errp = _set_cursor_pos(p, cursor)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
		}
	}
	return err;
}

s64_t Dz1FileBufStream_tell(Dz1FileBufStream *p, u32_t stream_id, Dz1Error *err)
{
	s64_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1FileBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || p->fp == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((cursor = (Dz1FileBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_OUT_RET(errp, -1);
	else { ret = (s64_t)cursor->pos; Dz1Error_set(errp, 0); }
	return ret;
}

bool_t Dz1FileBufStream_isEOF(Dz1FileBufStream *p, u32_t stream_id)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1FileBufPos key = { stream_id }, *cursor = NULL;
	if (p == NULL || p->fp == NULL) ERR_SET_OUT_RET(errp, EINVAL, TRUE);
	else if ((cursor = (Dz1FileBufPos *)Dz1AATree_find(p->user_cursors, (void *)&key)) == NULL) ERR_OUT_RET(errp, TRUE);
	else 
	{
		FILEPOSt file_pos = DZ1_FTELL(p->fp);
		FILEPOSt cursor_pos = p->drain_offset + cursor->pos;
		if (file_pos != cursor_pos && DZ1_FSEEK(p->fp, cursor_pos, SEEK_SET) != 0) ERR_SET_OUT_RET(errp, errno, TRUE);
		else
		{
			u8_t c;
			fread(&c, 1, 1, p->fp);

			if (feof(p->fp)) ret = TRUE;
			else ret = FALSE;

			DZ1_FSEEK(p->fp, file_pos, SEEK_SET);
		}
	}
	return ret;
}

static ssize_t _drain_to_buffer(Dz1FileBufStream *p, u8_t *dst, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (DZ1_FSEEK(p->fp, p->drain_offset, SEEK_SET) != 0) ERR_SET_OUT_RET(errp, errno, -1);	// 처음으로
	else if ((ret = (ssize_t)fread(dst, sizeof(u32_t), size, p->fp)) < 0) ERR_SET_OUT_RET(errp, errno, -1);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Dz1Error _reduce_pos(void *ptr, void *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t drain_size = *(size_t *)ptr;
	Dz1FileBufPos *p = (Dz1FileBufPos *)data;

	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if ((size_t)p->pos >= drain_size) p->pos -= drain_size;
		else p->pos = 0;
	}

	return err;
}

ssize_t Dz1FileBufStream_drain(Dz1FileBufStream *p, size_t drain_size, u8_t *opt_drain_buf, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || p->fp == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (drain_size == 0) { }
	else if (opt_drain_buf != NULL && (ret = _drain_to_buffer(p, opt_drain_buf, drain_size, errp)) < 0) ERR_OUT_RET(errp, -1);
	else
	{
		p->drain_offset += drain_size;
		Dz1AATree_travel(p->user_cursors, _reduce_pos, (void *)&drain_size);
	}
	return ret;
}
