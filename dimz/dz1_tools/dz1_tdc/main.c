#ifdef CPP_BUILDER_WIN32
#include <stdio.h>
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>
#include <dz1_args.h>
#include <dz1_malloc.h>
#include <dz1_str.h>

#include "publish_spec_parser.h"
#include "publish_spec_dz1.h"

#include "dz1_mdefc_parser.h"
#include "dz1_asn_parser.h"

#include "publish_c.h"
#include "publish_tdc.h"

#include "misc.h"

#define TEMP_NAME		".tempname"

static bool_t pause_at_end = FALSE;

static Dz1Error file_fix(str_t tempName, str_t destName, str_t srcFileName, bool_t doTouch)
{
	Dz1Binary *exist;
//	size_t exist_size;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((exist = Dz1BinFile_load(destName, &err)) == NULL)
	{	// 목표 파일 로딩 실패
		if (err.code == ENOENT)
		{	// 기존 파일이 없다 -> 임시 파일을 목표 파일로
			Dz1Error_set(&err, 0);
			if (rename(tempName, destName) < 0) { unlink(tempName); ERR_SET_OUT(&err, errno); }
		}
		else ERR_OUT(&err);
	}
	else
	{	// 목표 파일 로딩 성공
		Dz1Binary *mine = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&exist);
		// 임시 파일 로딩
		if ((mine = Dz1BinFile_load(tempName, &err)) == NULL) { ERR_OUT(&err); }
		else
		{	// 임시 파일 로딩 성공
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&mine);

			if (Dz1Binary_cmp(exist, mine) != 0)
			{	// 다른 내용 -> 목표 파일을 지우고 임시 파일을 목표 파일로 변경
				Dz1Thread_printf("File Fixing... %s\n", destName);
				if (unlink(destName) < 0) ERR_SET_OUT(&err, errno);
				else if (rename(tempName, destName) < 0)
				{
					unlink(tempName);
					ERR_SET_OUT(&err, errno);
				}
			}
			else
			{	// 같은 내용 -> 임시 파일을 지우고, 원본 파일의 시간을 뒤로 바꾼다
				Dz1Thread_printf("Nothing changed... %s\n", destName);
				unlink(tempName);
#ifndef UNIX_SYSTEM
				{
					// 목표 파일의 시간
					FILETIME tModDest, tModSrc;
					HANDLE f = CreateFile(destName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					GetFileTime(f, NULL, NULL, &tModDest);
					CloseHandle(f);

					// 원본(tdc, asn)파일의 시간
					f = CreateFile(srcFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					GetFileTime(f, NULL, NULL, &tModSrc);

					if (CompareFileTime(&tModDest, &tModSrc) < 0)
					{	// 소스보다 빠른 시간인 경우 Update
						Dz1Thread_printf("Set File Time...\n");
						Dz1Thread_printf("%s = %08X.%08X\n", destName, tModDest.dwHighDateTime, tModDest.dwLowDateTime);
						Dz1Thread_printf("%s = %08X.%08X\n", srcFileName, tModSrc.dwHighDateTime, tModSrc.dwLowDateTime);
						if (SetFileTime(f, NULL, &tModDest, &tModDest) == 0) ERR_SET_OUT(&err, GetLastError());
					}

					CloseHandle(f);
				}
#endif
//					Dz1Console_printf(NULL, 0, "file_fix() : File is Same\n");
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)mine);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)exist);
	}
	return err;
}


/*
typedef struct CompileOutSpec
{
	str_t path;
} CompileOutSpec;

static void CompileOutSpec_del(CompileOutSpec *p)
{
	if (!p) return;
	if (p->path) Dz1Str_del(p->path);
	Dz1Free(p);
}
static void CompileOutSpec_delAndSetNull(void *ptr)
{
	CompileOutSpec **p = (CompileOutSpec **)ptr;
	CompileOutSpec_del(*p); *p = NULL;
}

static CompileOutSpec *CompileOutSpec_new(str_t path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	CompileOutSpec *ret = (CompileOutSpec *)Dz1Calloc(sizeof(CompileOutSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CompileOutSpec_delAndSetNull, (void *)&ret);

		if (path && (ret->path = Dz1Str_dup(path, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (CompileOutSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
*/
typedef enum
{
	PublishMode_module,	// compile & link -> source output
	PublishMode_object,	// compile -> binary output
	PublishMode_max
} PublishMode;

typedef struct PublishInfo
{
	PublishMode	mode;
	str_t		headerPath;
	str_t		sourcePath;
} PublishInfo;

typedef struct Dz1TdcSpec
{
	PublishSpec *spec;
	IncludeSpec *inc;
//	CompileOutSpec *out;		// NULL = no dump, Not NULL = dump to out->path
	PublishInfo info;
	int			header;
	int			source;
	int			intermediate;
	bool_t		touch;
} Dz1TdcSpec;

static void Dz1TdcSpec_del(Dz1TdcSpec *p)
{
	if (!p) return;
	if (p->spec) PublishSpec_del(p->spec);
	if (p->inc) IncludeSpec_del(p->inc);
//	if (p->out) CompileOutSpec_del(p->out);
	if (p->info.headerPath) Dz1Str_del(p->info.headerPath);
	if (p->info.sourcePath) Dz1Str_del(p->info.sourcePath);
	Dz1Free(p);
}

static void Dz1TdcSpec_delAndSetNull(void *ptr)
{
	Dz1TdcSpec **p = (Dz1TdcSpec **)ptr;
	Dz1TdcSpec_del(*p); *p = NULL;
}

static Dz1TdcSpec *Dz1TdcSpec_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TdcSpec *ret = (Dz1TdcSpec *)Dz1Calloc(sizeof(Dz1TdcSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdcSpec_delAndSetNull, (void *)&ret);
		if ((ret->inc = IncludeSpec_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->info.mode = PublishMode_max;
			ret->touch = TRUE;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdcSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1TdcSpec_fix(Dz1TdcSpec *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) return;
	if (p->spec == NULL && (p->spec = PublishSpec_dz1(&err)) == NULL) ERR_OUT(&err);
	if (p->info.mode == PublishMode_max) p->info.mode = PublishMode_module;
	if (p->header == 0  && p->source == 0 && p->intermediate == 0)
		p->header = p->source = p->intermediate = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Publish Specification Option
///////////////////////////////////////////////////////////////////////////////
static str_t specDz1Help[] = { "Publish specification for DZ1 Library (default)", NULL };
static Dz1Error specDz1(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if ((p->spec = PublishSpec_dz1(&err)) == NULL) ERR_OUT(&err);

	return err;
}

static FILE *logfp = NULL;
static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }
static str_t setLogDumpHelp[] = { "create log file", NULL };
static Dz1Error setLogDump(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((logfp = Dz1FileStream_open("tdc.log.txt", "wb", &err)) != NULL)
	{
		Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
		Dz1OutputHook_set(_outputHook, NULL);
	}
	return err;
}

static str_t specNativeHelp[] = { "Publish specification for Native C", NULL };
static Dz1Error specNative(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (p->spec) ERR_SET_OUT(&err, EEXIST);
//	else if ((p->spec = PublishSpec_native(&err)) == NULL) ERR_OUT(&err);

	return err;
}

static str_t specAlterHelp[] = { "Alternative Publish specification File", NULL };
static Dz1Error specAlter(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (p->spec) ERR_SET_OUT(&err, EEXIST);
	else
	{
		void *parser = NULL;
		PublishSpec *spec = NULL;
		str_t text = NULL;

		pthread_cleanup_push(PublishSpec_delAndSetNull, (void *)&spec);

		if ((text = file_load(NULL, argv[1], &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)text);

			if ((parser = PublishSpecParser_new(&err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1Parser_del, parser);

				if ((spec = PublishSpecParser_proc(parser, text, &err)) == NULL) ERR_OUT(&err);
				else Dz1Error_set(&err, 0);

				pthread_cleanup_pop(1); // (Dz1Parser_del, parser);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)text);
		}
		pthread_cleanup_pop(err.code); // (PublishSpec_delAndSetNull, (void *)spec);

		p->spec = spec;
	}

	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Include Option
///////////////////////////////////////////////////////////////////////////////
static str_t includeHelp[] = { "Include Path", NULL };
static Dz1Error include(void *param, str_t n, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (strchr(argv[1], ';') != NULL)
	{
		char temp[4096], *cp = temp;
		str_t incs[64] = { NULL, };
		u32_t cnt = 0, i;

		strcpy(temp, argv[1]);

		incs[cnt] = temp;
		while ((cp = strchr(cp, ';')) != NULL)
		{
			*cp++ = '\0';
			if (strlen(incs[cnt]) > 0) cnt++;

			incs[cnt] = cp;
		}
		if (strlen(incs[cnt]) > 0) cnt++;

		for (i = 0; err.code == 0 && i < cnt; i++)
		{
			Dz1Thread_printf("INC = %s\n", incs[i]);
			if (p->inc->add(p->inc, incs[i], errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{
		Dz1Thread_printf("INC = %s\n", argv[1]);
#ifdef CALL_STACK_DEBUG
		if ((err = p->inc->add(p->inc, argv[1])).code) ERR_OUT(&err);
#else
		if (p->inc->add(p->inc, argv[1], errp) == FALSE) ERR_OUT(&err);
#endif
		else Dz1Error_set(errp, 0);
	}

	return err;
}


///////////////////////////////////////////////////////////////////////////////
// Compile/Publish Option
///////////////////////////////////////////////////////////////////////////////
static str_t compileOutHelp[] = { "Generate TDC Source file(asn file only)", NULL };
static Dz1Error compileOut(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Dz1TdcSpec *p = (Dz1TdcSpec *)param;

//	if (p->out) ERR_SET_OUT(&err, EEXIST);
//	else if ((p->out = CompileOutSpec_new(NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static str_t compileOutPathHelp[] = { "TDC Source Output Path (default = current path, asn file only)", NULL };
static Dz1Error compileOutPath(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//Dz1TdcSpec *p = (Dz1TdcSpec *)param;

//	if (p->out == NULL) ERR_SET_OUT(&err, EPERM);
//	else if (p->out->path) ERR_SET_OUT(&err, EEXIST);
//	else if ((p->out->path = Dz1Str_dup(argv[1], &err)) == NULL) ERR_OUT(&err);

	return err;
}

static str_t publishModeHelp[] = { "Publish Mode (default = module)", NULL };
static Dz1Error publishMode(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (p->info.mode != PublishMode_max) ERR_SET_OUT(&err, EEXIST);
	else if (strcmp(argv[1], "module") == 0) p->info.mode = PublishMode_module;
	else if (strcmp(argv[1], "object") == 0) p->info.mode = PublishMode_object;
	else ERR_SET_OUT(&err, EINVAL);

	return err;
}

static str_t publishHeaderPathHelp[] = { "Header Output Path (default = current path)", NULL };
static Dz1Error publishHeaderPath(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (p->info.headerPath) ERR_SET_OUT(&err, EEXIST);
	else if ((p->info.headerPath = Dz1Str_dup(argv[1], &err)) == NULL) ERR_OUT(&err);

	return err;
}

static str_t publishSourcePathHelp[] = { "Source Output Path (default = current path)", NULL };
static Dz1Error publishSourcePath(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	if (p->info.sourcePath) ERR_SET_OUT(&err, EEXIST);
	else if ((p->info.sourcePath = Dz1Str_dup(argv[1], &err)) == NULL) ERR_OUT(&err);

	return err;
}

static str_t publishSourceTouchHelp[] = { "don't modify file time if there are same", NULL };
static Dz1Error publishSourceTouch(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	p->touch = FALSE;

	return err;
}

static str_t setPauseAtEndHelp[] = { "pause at end of compile", NULL };
static Dz1Error setPauseAtEnd(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	// Dz1TdcSpec *p = (Dz1TdcSpec *)param; // modified by gm 20230602 - unused var p

	pause_at_end = TRUE;

	return err;
}

static str_t publishHeaderOnlyHelp[] = { "Publish Header", NULL };
static Dz1Error publishHeaderOnly(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	p->header = 1;

	return err;
}

static str_t publishSourceOnlyHelp[] = { "Publish Source", NULL };
static Dz1Error publishSourceOnly(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	p->source = 1;

	return err;
}

static str_t publishIntermediateOnlyHelp[] = { "Publish Intermediate", NULL };
static Dz1Error publishIntermediateOnly(void *param, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TdcSpec *p = (Dz1TdcSpec *)param;

	p->intermediate = 1;

	return err;
}


static Dz1Args opt[] =
{
	{ "--dz1", 1, { 0, }, specDz1, specDz1Help },
	{ "--log", 1, { 0, }, setLogDump, setLogDumpHelp },
	{ "--native", 1, { 0, }, specNative, specNativeHelp },
	{ "--spec", 2, { 0, }, specAlter, specAlterHelp },

	{ "--include", 2, { 0, }, include, includeHelp },
	{ "--dump", 1, { 0, }, compileOut, compileOutHelp },
	{ "--output", 2, { 0, }, compileOutPath, compileOutPathHelp },
	{ "--mode", 2, { 0, }, publishMode, publishModeHelp },
	{ "--header", 2, { 0, }, publishHeaderPath, publishHeaderPathHelp },
	{ "--source", 2, { 0, }, publishSourcePath, publishSourcePathHelp },

	{ "--notouch", 1, { 0, }, publishSourceTouch, publishSourceTouchHelp },

	{ "--pause", 1, { 0, }, setPauseAtEnd, setPauseAtEndHelp },

	{ "-I", 2, { 0, }, include, includeHelp },
	{ "-d", 1, { 0, }, compileOut, compileOutHelp },
	{ "-o", 2, { 0, }, compileOutPath, compileOutPathHelp },
	{ "-m", 2, { 0, }, publishMode, publishModeHelp },
	{ "-h", 2, { 0, }, publishHeaderPath, publishHeaderPathHelp },
	{ "-s", 2, { 0, }, publishSourcePath, publishSourcePathHelp },

	{ "-H", 1, { 0, }, publishHeaderOnly, publishHeaderOnlyHelp },
	{ "-S", 1, { 0, }, publishSourceOnly, publishSourceOnlyHelp },
	{ "-O", 1, { 0, }, publishIntermediateOnly, publishIntermediateOnlyHelp },
	Dz1ArgsTermEntry
};

static str_t _getBasename(str_t src)
{
	int len = (int)strlen(src);
	char *cp = src + len -1;
	while(cp > src)
	{
		if (*cp == DIR_SEP) break;
		else cp--;
	}
	if (*cp == DIR_SEP) cp++;

	return cp;
}
 
typedef enum FileExtType
{
	FileExtType_tdc,
	FileExtType_asn,
	FileExtType_unknown
} FileExtType;

static Dz1Error publishHeader(Dz1MdefcModule *module, Dz1TdcSpec *tdcSpec, str_t srcFileName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	if ((fp = Dz1FileStream_open(TEMP_NAME, "wb", &err)) == NULL) ERR_OUT(&err);
	else
	{
		char fn[1024];
		pthread_cleanup_push((Dz1DelFunc)fclose, (void *)fp);

		if (tdcSpec->info.headerPath == NULL)
			sprintf(fn, "%s.h", module->name);
		else
		{
			str_t basename = _getBasename(module->name);
			sprintf(fn, "%s" DIR_SEPRATOR "%s.h", tdcSpec->info.headerPath , basename);
		}

		Dz1Thread_printf("header = %s\n", fn);

		Dz1MdefcModule_header(fp, tdcSpec->spec, module);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);

		if ((err = file_fix(TEMP_NAME, fn, srcFileName, tdcSpec->touch)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error publishHeaderAsnConv(Dz1MdefcModule *module, Dz1TdcSpec *tdcSpec, str_t srcFileName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	if ((fp = Dz1FileStream_open(TEMP_NAME, "wb", &err)) == NULL) ERR_OUT(&err);
	else
	{
		char fn[1024];
		pthread_cleanup_push((Dz1DelFunc)fclose, (void *)fp);

		if (tdcSpec->info.sourcePath == NULL)
			sprintf(fn, "%s.h", module->name);
		else
		{
			str_t basename = _getBasename(module->name);
			sprintf(fn, "%s" DIR_SEPRATOR "%s.h", tdcSpec->info.sourcePath , basename);
		}

		Dz1Thread_printf("ASN.1 conv = %s\n", fn);

		Dz1MdefcModule_headerAsnConv(fp, tdcSpec->spec, module);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);

		if ((err = file_fix(TEMP_NAME, fn, srcFileName, tdcSpec->touch)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error publishSource(Dz1MdefcModule *module, Dz1TdcSpec *tdcSpec, str_t srcFileName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	if ((fp = Dz1FileStream_open(TEMP_NAME, "wb", &err)) == NULL) ERR_OUT(&err);
	else
	{
		char fn[1024];
		pthread_cleanup_push((Dz1DelFunc)fclose, (void *)fp);

		if (tdcSpec->info.sourcePath == NULL)
			sprintf(fn, "%s.c", module->name);
		else
		{
			str_t basename = _getBasename(module->name);
			sprintf(fn, "%s" DIR_SEPRATOR "%s.c", tdcSpec->info.sourcePath, basename);
		}

		Dz1Thread_printf("source = %s\n", fn);
		Dz1MdefcModule_source(fp, tdcSpec->spec, module);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)fclose, (void *)fp);

		if ((err = file_fix(TEMP_NAME, fn, srcFileName, tdcSpec->touch)).code) ERR_OUT(&err);
	}
	return err;
}

static Dz1Error publishIntermediate(Dz1MdefcModule *module, Dz1TdcSpec *tdcSpec, str_t src_path_name_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char *cp = NULL;
//	FILE *fp = NULL;

	char dst_path[1024], dst_name_ext[512];
	char src_path[1024], dst_fn[1024] = { 0, };

	if ((*errp = Dz1FileName_splitPathName(src_path, dst_name_ext, src_path_name_ext)).code) ERR_OUT(errp);
	else if ((cp = strrchr(dst_name_ext, '.')) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{	// 이름에 tdc를 tdo로 변경
		strcpy(cp, ".tdo");

		// 경로 설정
		if (tdcSpec->info.headerPath == NULL) strcpy(dst_path, src_path);
		else strcpy(dst_path, tdcSpec->info.headerPath);
		Dz1Thread_printf("path = %s\n", dst_path);

		if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(char, dst_fn), dst_path, dst_name_ext)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MdefcModule_save(module, NULL, TEMP_NAME)).code) ERR_OUT(errp);
		else if ((*errp = file_fix(TEMP_NAME, dst_fn, src_path_name_ext, tdcSpec->touch)).code) ERR_OUT(&err);
		else
		{
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error compileByExt(str_t name, str_t ext, FileExtType type, Dz1TdcSpec *tdcSpec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	char fn[1024], srcFileName[1024];
	str_t text = NULL;

	sprintf(fn, "%s.%s", name, ext); strcpy(srcFileName, fn);

	Dz1Thread_printf("Compile %s\n", fn);

	if ((text = file_load(NULL, fn, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1MdefcModule *module = NULL;

		pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)text);
		
		switch(type)
		{
		case FileExtType_asn:
			module = Dz1MdefcModule_compileASN(tdcSpec->spec, tdcSpec->inc, name, text, &err);
			break;
		case FileExtType_tdc:
			module = Dz1MdefcModule_compile(tdcSpec->spec, tdcSpec->inc, name, text, &err);
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}

		if (module == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);

			// TDC output for ASN Converter
			if (type == FileExtType_asn)
			{
				FILE *fp = NULL;
				char tdcName[4096];

				if (tdcSpec->info.headerPath == NULL)
					sprintf(tdcName, "%s.tdc", module->name);
				else
				{
					str_t basename = _getBasename(module->name);
					sprintf(tdcName, "%s" DIR_SEPRATOR "%s.tdc", tdcSpec->info.headerPath , basename);
				}

				if ((fp = Dz1FileStream_open(tdcName, "wb", &err)) == NULL) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
					Dz1MdefcModule_tdc(fp, module, tdcSpec->spec);
					pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
				}
			}

			if (tdcSpec->info.mode == PublishMode_module)
			{

				Dz1Thread_printf("compile() : Module Publishing...(%d, %d, %d)\n", tdcSpec->header, tdcSpec->source, tdcSpec->intermediate);

				// Header Output
				if (tdcSpec->header)
				{
					if ((err = publishHeader(module, tdcSpec, srcFileName)).code) ERR_OUT(&err);
				}

				// Source Output
				if (tdcSpec->source)
				{
					if ((err = publishSource(module, tdcSpec, srcFileName)).code) ERR_OUT(&err);
				}

				if (strcmp(ext, "asn") == 0 && tdcSpec->header)
				{
					if ((err = publishHeaderAsnConv(module, tdcSpec, srcFileName)).code) ERR_OUT(&err);
				}

				if (tdcSpec->intermediate)
				{
					if ((err = publishIntermediate(module, tdcSpec, srcFileName)).code) ERR_OUT(&err);
				}
			}
			else
			{
				Dz1Thread_printf("compile() : Object Publishing...\n");
			}

			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1MdefcModule_del, (void *)module);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)text);
	}
	return err;
}

static Dz1Error _getNameAndExt(str_t src, char name[1024], char ext[1024], FileExtType *ft)
{
	FileExtType _ft = FileExtType_unknown, *ftp = ft ? ft : &_ft;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	char temp[4096];
	char *cp = NULL; // , *fp = name, *ep = ext;
	strcpy(temp, src);
	name[0] = ext[0] = '\0';
	if ((cp = strrchr(temp, '.')) == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		*cp++ = '\0';
		strcpy(name, temp);
		strcpy(ext, cp);
	}

	if (strlen(ext) == 0) ERR_SET_OUT(&err, EINVAL);
	else if (strcmp(ext, "asn") == 0) *ftp = FileExtType_asn;
	else if (strcmp(ext, "tdc") == 0) *ftp = FileExtType_tdc;
	else ERR_SET_OUT(&err, EINVAL);
	return err;
}

int main(int argc, char *argv[])
{
	Dz1TdcSpec *tdcSpec = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	Dz1Cleanup_init();
	Dz1Thread_setFpTab("\t");

	if (argc == 1) Dz1Args_help(opt, argv[0], "<.tdc files...>", 0);
	else if ((tdcSpec = Dz1TdcSpec_new(&err)) == NULL) ERR_OUT(&err);
	else
	{
		int i;
		Dz1Param *param = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1TdcSpec_del, (void *)tdcSpec);

		Dz1Thread_printf(Dz1T("Arguments -----------------------------------------\n"));
		for (i = 1; i < argc; i++)
			Dz1Thread_printf(Dz1T("arg[%d] = %s\n"), i, argv[i]);
		Dz1Thread_printf(Dz1T("---------------------------------------------------\n"));

		if ((param = Dz1Param_new(argc, argv, &err)) == NULL) { ERR_OUT(&err); }
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Param_del, (void *)param);
			if ((err = Dz1Param_proc(param, opt, argv[0], tdcSpec)).code) { ERR_OUT(&err); }
			else if (param->argc <= 1)
			{
				Dz1Thread_printf("No file input(param->argc = %d)\n", param->argc);
				Dz1Error_set(&err, EINVAL);
			}
			else
			{
				int i;
				char name[1024], ext[1024];

				Dz1TdcSpec_fix(tdcSpec);

				if (tdcSpec->spec == NULL) ERR_SET_OUT(&err, EFAULT);
				else
				{
					FileExtType ft = FileExtType_unknown;
					for (i = 1; err.code == 0 && i < param->argc; i++)
					{
						if ((err = _getNameAndExt(param->argv[i], name, ext, &ft)).code) ERR_OUT(&err);
						else if ((err = compileByExt(name, ext, ft, tdcSpec)).code) ERR_OUT(&err);
					}
				}
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Param_del, (void *)param);
		}
		pthread_cleanup_pop(1); // ((Dz1delFunc)Dz1TdcSpec_del, (void *)tdcSpec);
	}

	Dz1Thread_printf("Complete Compile\n");

	if (pause_at_end)
	{
		Dz1Thread_printf("Press any key...");
		Dz1Thread_getch(-1, NULL);
	}
	return err.code;
}
