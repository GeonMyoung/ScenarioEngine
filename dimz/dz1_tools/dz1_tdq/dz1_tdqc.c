#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_tdq.h>
#include "dz1_tdqc_parser.h"
#include "dz1_tdqc_pub.h"

#ifdef _DEBUG
#include <conio.h>
#endif

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

static bool_t compile(Dz1TdqcArg *arg, Dz1Str fn, Dz1Error *errp)
{
	Dz1Str text = NULL;
	TCHAR path[2048], name_ext[1024];
	TCHAR name[768], ext[256];
	if ((*errp = Dz1FileName_splitPathName(path, name_ext, fn)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileName_splitNameExt(name, ext, name_ext)).code) ERR_OUT(errp);
	else if ((text = Dz1TextFile_load2(path, name_ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str zl_str = Dz1Text("");
		Dz1TdqcTarget *tgt = NULL;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);

		if (Dz1Str_isVoid(arg->mod_inc_path)) arg->mod_inc_path = path;
		if (Dz1Str_isVoid(arg->dst_path_c)) arg->dst_path_c = path;
		if (Dz1Str_isVoid(arg->dst_path_h)) arg->dst_path_h = path;
		if (Dz1Str_isVoid(arg->fn_postfix)) arg->fn_postfix = zl_str;

		if ((tgt = Dz1TdqcTarget_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TdqcTarget_delAndSetNull, (void *)&tgt);
			if ((*errp = Dz1Tdqc_parse(tgt, text, arg)).code) ERR_OUT(errp);
			else
			{
//				Dz1Thread_printf("Parsed = "); Dz1TdqcTarget_dump(tgt, 0);

//				Dz1File_touch2(path, name_ext);

				if (Dz1Tdqc_pub(tgt, arg, path, name, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TdqcTarget_delAndSetNull, (void *)&tgt);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void print_usage(Dz1Str bn)
{
	printf(Dz1Text("%s <options...> <tdqc_src_file>\n"), bn);
	printf(Dz1Text("    -I : module load path(-I<path1>;<path2>;...\n"));
	printf(Dz1Text("    -s : source output path(-s<src_out_path>\n"));
	printf(Dz1Text("    -h : header output path(-h<hdr_out_path>\n"));
	printf(Dz1Text("    -o : output file post suffix(-o<post_suffix>\n"));
	printf(Dz1Text("    -S : output source only\n"));
	printf(Dz1Text("    -H : output header only\n"));
	printf(Dz1Text("         default : output source and header\n"));
	printf(Dz1Text("    -p : pause at end\n"));
}

static bool_t pause_at_end = FALSE;
static bool_t set_arg(Dz1TdqcArg *dst, TCHAR *str, Dz1Error *errp)
{
	TCHAR *cp = str;
	if (*cp != Dz1Text('-'))
	{
		if (dst->target_file == NULL) dst->target_file = str;
		else Dz1Error_set(errp, EINVAL);
	}
	else
	{
		cp++; 
		switch(*cp++)
		{
		case Dz1Text('I'):dst->mod_inc_path = cp; break;
		case Dz1Text('s'):dst->dst_path_c = cp; break;
		case Dz1Text('h'):dst->dst_path_h = cp; break;
		case Dz1Text('o'):dst->fn_postfix = cp; break;
		case Dz1Text('S'):dst->output_src = TRUE; dst->output_hdr = FALSE; break;
		case Dz1Text('H'):dst->output_src = FALSE; dst->output_hdr = TRUE; break;
		case Dz1Text('p'):pause_at_end = TRUE; break;
		default: Dz1Error_set(errp, EINVAL); break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t parse_arg(Dz1TdqcArg *dst, int argc, TCHAR *argv[], Dz1Str bn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int i;
	for (i = 1; errp->code == 0 && i < argc; i++)
	{
		if (set_arg(dst, argv[i], errp) == FALSE)
		{
			printf(Dz1Text("unknown option %s\n"), argv[i]);
			print_usage(bn);
			Dz1Error_set(errp, EINVAL);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

int main(int argc, TCHAR *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Str bn = basename(argv[0]);
	Dz1TdqcArg arg = { NULL, NULL, NULL, NULL, TRUE, TRUE, NULL };
	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("tdqc.log.txt"), Dz1Text("wb"), errp)) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init() == FALSE) { Dz1Thread_printf("Win sock Initialize Fail\n"); return EFAULT; }
#endif
	if (argc == 1)
	{
		print_usage(bn);
	}
	else if (parse_arg(&arg, argc, argv, bn, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1Str_isVoid(arg.target_file)) print_usage(bn);
	else if (compile(&arg, arg.target_file, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

#ifndef UNIX_SYSTEM
	Dz1Socket_cleanup();
#endif

	if (pause_at_end)
	{
		printf(Dz1Text("Press any key...\n"));
		Dz1Thread_getch(-1, NULL);
	}
// #ifdef _DEBUG
// 	printf("Press Any Key...\n");
// 	while(!kbhit()) Sleep(10);
// 	fflush(stdin);
// #endif

	return errp->code;
}
