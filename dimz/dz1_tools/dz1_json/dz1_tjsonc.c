#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#ifdef _DEBUG
#include <conio.h>
#endif
#include "dz1_tjsonc_parser.h"
#include "dz1_tjsonc_publish.h"
#include "dz1_tjsonc_util.h"
#include "dz1_tjsonc.h"

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

#define TEMPORARY_FILE_NAME		Dz1Text("__temporary_output__")
#ifdef WIN32
Dz1Error _get_file_time(FILETIME *dst, Dz1Str path, Dz1Str name, Dz1Str ext)
{
	TCHAR fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	// 목표 파일의 시간
	HANDLE f = NULL;
	if ((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(TCHAR, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((f = CreateFile(fn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == 0) 
	{
		int code = GetLastError();
		ERR_SET_OUT(errp, code);
	}
	else 
	{
		GetFileTime(f, NULL, NULL, dst);
		CloseHandle(f);
	}
	return err;
}

static Dz1Error _set_file_time_to_past(Dz1Str fn, FILETIME *basis)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	HANDLE f = INVALID_HANDLE_VALUE;
	if ((f = CreateFile(fn, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == 0) ERR_SET_OUT(errp, GetLastError());
	else
	{
		FILETIME tModSrc;
		GetFileTime(f, NULL, NULL, &tModSrc);

		if (CompareFileTime(basis, &tModSrc) < 0)
		{	// 소스보다 빠른 시간인 경우 Update
			if (SetFileTime(f, NULL, basis, basis) == 0) ERR_SET_OUT(errp, GetLastError());
			else Dz1Error_set(errp, 0);
		}

		CloseHandle(f);
	}
	return err;
}
#endif

static Dz1Error file_fix(Dz1Str tgt_path, Dz1Str out_name, Dz1Str tgt_name, Dz1Str ext, Dz1Str src_fn)
{
	Dz1Binary *exist;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (Dz1Str_isVoid(tgt_path)) tgt_path = Dz1T(".");

	if ((exist = Dz1BinFile_load3(tgt_path, tgt_name, ext, &err)) == NULL)
	{	// 목표 파일 로딩 실패
		if (err.code == ENOENT)
		{	// 기존 파일이 없다 -> 임시 파일을 목표 파일로
			Dz1Error_set(errp, 0);
			if ((*errp = Dz1File_rename3(tgt_path, tgt_name, ext, tgt_path, out_name, ext)).code)
			{
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Path = "); Dz1Str_dump(tgt_path, 0);
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Src Name = "); Dz1Str_dump(out_name, 0);
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, "Dst Name = "); Dz1Str_dump(tgt_name, 0);
				Dz1File_delete3(tgt_path, out_name, ext); 
				ERR_OUT(errp); 
			}
		}
		else ERR_OUT(&err);
	}
	else
	{	// 목표 파일 로딩 성공
		Dz1Binary *mine = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&exist);
		// 임시 파일 로딩
		if ((mine = Dz1BinFile_load3(tgt_path, out_name, ext, errp)) == NULL) ERR_OUT(errp);
		else
		{	// 임시 파일 로딩 성공
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&mine);

			if (Dz1Binary_cmp(exist, mine) != 0)
			{	// 다른 내용 -> 목표 파일을 지우고 임시 파일을 목표 파일로 변경
				Dz1Thread_printf("File Fixing... %s.%s\n", tgt_name, ext);
				if ((*errp = Dz1File_delete3(tgt_path, tgt_name, ext)).code) ERR_OUT(errp);
				else if ((*errp = Dz1File_rename3(tgt_path, tgt_name, ext, tgt_path, out_name, ext)).code)
				{
					Dz1File_delete3(tgt_path, out_name, ext);
					ERR_OUT(errp);
				}
			}
			else
			{	// 같은 내용 -> 임시 파일을 지우고, 원본 파일의 시간을 뒤로 바꾼다
				Dz1Thread_printf("Nothing changed... %s.%s\n", tgt_name, ext);
				Dz1File_delete3(tgt_path, out_name, ext);
#ifndef UNIX_SYSTEM
				{
					// 목표 파일의 시간
					FILETIME tModDest;
					if ((*errp = _get_file_time(&tModDest, tgt_path, tgt_name, ext)).code) ERR_OUT(errp);
					else if ((*errp = _set_file_time_to_past(src_fn, &tModDest)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
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

static void _print_help(Dz1Str argv0)
{
	printf(Dz1Text("%s <opt> <filename>\n"), argv0);
	printf(Dz1Text("	*** Option\n"));
	printf(Dz1Text("	-I<includes>    : <path>;<path>;...\n"));
	printf(Dz1Text("	-S<path>        : Source Output Path\n"));
	printf(Dz1Text("	-H<path>        : Header Output Path\n"));
	printf(Dz1Text("	-s              : Source Output Only\n"));
	printf(Dz1Text("	-h              : Header Output Only\n"));
	printf(Dz1Text("	-o<suffix>      : Output Suffix\n"));
	printf(Dz1Text("	-p              : pause at end\n"));
}

static bool_t pause_at_end = FALSE;

static Dz1Error _arg_parse(Dz1JsonCompilerArg *dst, int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int i;
	TCHAR *str = NULL;
	for (i = 1; errp->code == 0 && i < argc; i++)
	{
		str = argv[i];
		if (str[0] == Dz1Text('-'))
		{
			switch(str[1])
			{
			case Dz1Text('I'):
				if (Dz1JsonCompileIncs_appendPath(dst->src_module_inc, &str[2], errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Text('S'):
				if (dst->src_out_path != NULL) ERR_SET_OUT(errp, EEXIST);
				else if ((dst->src_out_path = Dz1Str_dup(&str[2], errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Text('H'):
				if (dst->hdr_out_path != NULL) ERR_SET_OUT(errp, EEXIST);
				else if ((dst->hdr_out_path = Dz1Str_dup(&str[2], errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Text('s'):
				if (dst->src_out) ERR_SET_OUT(errp, EEXIST);
				else { dst->src_out = TRUE; Dz1Error_set(errp, 0); }
				break;
			case Dz1Text('h'):
				if(dst->hdr_out) ERR_SET_OUT(errp, EEXIST);
				else { dst->hdr_out = TRUE; Dz1Error_set(errp, 0); }
				break;
			case Dz1Text('o'):
				if (dst->suffix != NULL) ERR_SET_OUT(errp, EEXIST);
				else if ((dst->suffix = Dz1Str_dup(&str[2], errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1Text('p'):
				pause_at_end = TRUE;
			}
		}
		else
		{
			if (dst->tgt_fn != NULL) ERR_SET_OUT(errp, EEXIST);
			else if ((dst->tgt_fn = Dz1Str_dup(str, errp)) == NULL) ERR_OUT(errp);
			else
			{
				TCHAR path[2048], name_ext[1024], name[1024 - 64], ext[64];
				if ((*errp = Dz1FileName_splitPathName(path, name_ext, dst->tgt_fn)).code) ERR_OUT(errp);
				else if ((*errp = Dz1FileName_splitNameExt(name, ext, name_ext)).code) ERR_OUT(errp);
				else if ((dst->tgt_path = Dz1Str_dup(path, errp)) == NULL) ERR_OUT(errp);
				else if ((dst->tgt_name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
				else if ((dst->tgt_ext = Dz1Str_dup(ext, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

static bool_t file_fix_header(Dz1JsonCompilerArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (arg->hdr_out)
	{
		if ((*errp = file_fix(arg->hdr_out_path, TEMPORARY_FILE_NAME , arg->output_name, Dz1Text("h"), arg->tgt_fn)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t file_fix_source(Dz1JsonCompilerArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (arg->src_out)
	{
		if ((*errp = file_fix(arg->src_out_path, TEMPORARY_FILE_NAME , arg->output_name, Dz1Text("c"), arg->tgt_fn)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _mk_output_name(Dz1JsonCompilerArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR name[2048];
	Dz1STRCPY(name, arg->tgt_name);
	if (arg->suffix != NULL) Dz1STRCAT(name, arg->suffix);

	if ((arg->output_name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

int main(int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1JsonCompilerArg *arg = NULL;

	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_json_compiler.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

	if (argc == 1) _print_help(argv[0]);
	else if ((arg = Dz1JsonCompilerArg_new(NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str text = NULL;
		pthread_cleanup_push(Dz1JsonCompilerArg_delAndSetNull, (void *)&arg);
		if ((arg->src_module_inc = Dz1JsonCompileIncs_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _arg_parse(arg, argc, argv)).code || arg->tgt_fn == NULL) _print_help(argv[0]);
		else
		{
// 			Dz1Thread_printf("Compile Argument[0] = "); Dz1JsonCompilerArg_dump(arg, 0);
			if		(arg->src_out_path == NULL && (arg->src_out_path = Dz1Str_dup(arg->tgt_path, errp)) == NULL) ERR_OUT(errp);
			else if (arg->hdr_out_path == NULL && (arg->hdr_out_path = Dz1Str_dup(arg->tgt_path, errp)) == NULL) ERR_OUT(errp);
			else if (_mk_output_name(arg, errp) == FALSE) ERR_OUT(errp);
			else if ((text = Dz1TextFile_load(arg->tgt_fn, errp)) == NULL) ERR_OUT(errp);
			else 
			{
				Dz1JsonCompilerEnv *c_env = NULL;
				Dz1Primitive_delAndSetNull_push(Dz1Str, text);
				Dz1Thread_printf("Compile Argument = "); Dz1JsonCompilerArg_dump(arg, 0);
				if (arg->src_out == FALSE && arg->hdr_out == FALSE) arg->src_out = arg->hdr_out = TRUE;
				
				if ((c_env = Dz1Tjsonc_parse(text, arg, errp)) == NULL) ERR_OUT(errp);
				else
				{
//					Dz1Str temp_name = TEMPORARY_FILE_NAME;
					Dz1Struct_delAndSetNull_push(Dz1JsonCompilerEnv, c_env);

					if (Dz1JsonTargetObjects_publish(c_env, arg, arg->output_name, errp) == FALSE) ERR_OUT(errp);
// 					else if (file_fix_header(arg, errp) == FALSE) ERR_OUT(errp);
// 					else if (file_fix_source(arg, errp) == FALSE) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
					Dz1Struct_delAndSetNull_pop(1); //  (Dz1JsonCompilerEnv, &c_env);
				}
				Dz1Primitive_delAndSetNull_pop(1); //  (Dz1Str, text);
			}
		}
		pthread_cleanup_pop(1); // (Dz1JsonCompilerArg_delAndSetNull, (void *)&arg);
	}

	if (pause_at_end)
	{
		printf(Dz1T("press any key..."));
		Dz1Thread_getch(-1, NULL);
	}
	return errp->code ? -errp->code : 0;
}
