#include <dz1_cleanup.h>
#include <dz1_todec.h>
#ifdef _DEBUG
#include <conio.h>
#endif

static void print_help(str_t n)
{
	int tab = 0;
	char *bn = strrchr(n, DIR_SEP_A);
	if (bn == NULL) bn = n; else bn++;

	Dz1Thread_tprintf(tab++,	"%s [-C|-G|-syntax] <options> <filename>\n", bn);
	Dz1Thread_tprintf(tab++,		"-C : Compile *.todec source\n");
	Dz1Thread_tprintf(tab,				"-pause : pause at end\n");
	Dz1Thread_tprintf(tab,				"*** Path Option\n");
	Dz1Thread_tprintf(tab,				"-I : tdo loading path. ex) -I<path>;<path>...\n");
	Dz1Thread_tprintf(tab,				"-s : source output path. ex) -s<path>\n");
	Dz1Thread_tprintf(tab,				"-h : header output path. ex) -h<path>\n");
	Dz1Thread_tprintf(tab,				"\n");
	Dz1Thread_tprintf(tab,				"*** Output Option\n");
	Dz1Thread_tprintf(tab,				"-S : output source only\n");
	Dz1Thread_tprintf(tab,				"-H : output header only\n");
	Dz1Thread_tprintf(tab--,			"-SH : output both(default)\n");
	Dz1Thread_tprintf(tab,				"-o : output file Suffix. ex) -oStream -> {inputName}Stream.c\n");
	Dz1Thread_tprintf(tab,				"\n");
	Dz1Thread_tprintf(tab++,		"-G : Generate *.todec from *.tdo\n");
	Dz1Thread_tprintf(tab,				"-o : output file Suffix. ex) -oConv -> {inputName}Conv.todec\n");
	Dz1Thread_tprintf(tab,				"-i : include name Suffix. ex) -iStream -> include {ModuleName}Stream\n");
	Dz1Thread_tprintf(tab,				"-O : output path. ex) -O..\\out_path\n");
	Dz1Thread_tprintf(tab--,			"\n");
	Dz1Thread_tprintf(tab++,		"-syntax : show the syntax\n");
	Dz1Thread_tprintf(tab--,			"\n");
	Dz1Thread_tprintf(tab++,		"-help\n");
	Dz1Thread_tprintf(tab,			"\n");
}

static Dz1Error _publish(str_t fn, Dz1TodecPubArg *arg, str_t output_suffix)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char path[1024], name[512], name_ext[512], ext[128];

	if ((*errp = Dz1FileName_splitPathName(path, name_ext, fn)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileName_splitNameExt(name, ext, name_ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Todec_publish(path, name, ext, arg, output_suffix)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static bool_t pause_at_end = FALSE;
static Dz1Error _compile(int argc, char *argv[])
{	// -C path
	DZ1_ERROR_SAFE_VAR(errp, err);

	int i;
	char src_dst_path[512] = { 0 }, hdr_dst_path[512] = { 0 };
	char inc_path_buf[1024] = { 0 }, *inc_dp = inc_path_buf;
	char name_buf[1024] = { 0, }, *name_dp = name_buf;
	char output_suffix[1024] = { 0, };
	char *names[64] = { NULL, };
	int name_cnt = 0;
	char *arg = NULL;

	Dz1TodecPubArg pub_arg = 
	{
		inc_path_buf,			// module include path
		src_dst_path,			// source output path
		hdr_dst_path,			// header output path
		TRUE, TRUE,				// output source & header
		0
	};

	for (i = 2; i < argc; i++)
	{
		arg = argv[i];
		if (arg[0] == '-')
		{
			if (0) { } 
			else if (strncmp("-pause", arg, 6) == 0) pause_at_end = TRUE;
			else if (strncmp("-I", arg, 2) == 0)
			{
				char *cp = arg + 2, last = 0;
				while(*cp)
					*inc_dp++ = last = *cp++;
				if (last == ';') inc_dp--;
				*inc_dp = 0;
			}
			else if (strncmp("-s", arg, 2) == 0) strcpy(src_dst_path, arg + 2);
			else if (strncmp("-h", arg, 2) == 0) strcpy(hdr_dst_path, arg + 2);
			else if (strncmp("-o", arg, 2) == 0) strcpy(output_suffix, arg + 2);

			else if (strncmp("-S", arg, 2) == 0) pub_arg.output_hdr = FALSE;
			else if (strncmp("-H", arg, 2) == 0) pub_arg.output_src = FALSE;
			else if (strncmp("-SH", arg, 3) == 0) pub_arg.output_hdr = pub_arg.output_src = TRUE;
			else if (strncmp("-rstk", arg, 5) == 0)
				pub_arg.flags |= TODEC_FLAGS_USE_STACK;
			else
			{
				Dz1Thread_printf("Unknown Option [%s]\n", arg);
				print_help(argv[0]);
				ERR_SET_OUT_RET(errp, EINVAL, err);
			}
		}
		else
		{
			char *cp = arg;
			names[name_cnt] = name_dp;
			while(*cp) *name_dp++ = *cp++;
			*name_dp++ = 0;
			name_cnt++;
		}
	}

	Dz1Thread_printf("Options = "); Dz1TodecPubArg_dump(&pub_arg, 0);

	for (i = 0; i < name_cnt; i++)
	{
		Dz1Thread_printf("Target File = %s\n", names[i]);
		if ((*errp = _publish(names[i], &pub_arg, output_suffix)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Generate
static Dz1Error _generate(char *src_fn, char *out_path, char *oSuffix, char *iSuffix)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char path[2048], name_ext[256], name[256];
	if ((*errp = Dz1FileName_splitPathName(path, name_ext, src_fn)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileName_splitNameExt(name, NULL, name_ext)).code) ERR_OUT(errp);
	else
	{
		char *_path = Dz1Str_isVoid(out_path) ? path : out_path;
		if ((*errp = Dz1Todec_convert(path, name, Dz1TodecTargetCodecMode_public, _path, oSuffix, iSuffix)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _convert(int argc, char *argv[])
{	// -G path
	DZ1_ERROR_SAFE_VAR(errp, err);

	int i;
	char out_suffix[128] = "", inc_suffix[128] = "", out_path[1024] = "", *dp = NULL;
	char name_buf[1024] = { 0, }, *name_dp = name_buf;
	char *names[64] = { NULL, }, *arg = NULL;
	int name_cnt = 0;
	for (i = 2; i < argc; i++)
	{
		arg = argv[i];
		if (arg[0] == '-')
		{
			if (0) { } 
			else if (strncmp("-o", arg, 2) == 0)
			{
				char *cp = arg + 2;
				if (strlen(cp) >= 128) ERR_SET_OUT_RET(errp, E2BIG, err);
				else
				{
					dp = out_suffix;
					while(*cp) *dp++ = *cp++;
					*dp = 0;
					Dz1Error_set(errp, 0);
				}
			}
			else if (strncmp("-i", arg, 2) == 0)
			{
				char *cp = arg + 2;
				if (strlen(cp) >= 128) ERR_SET_OUT_RET(errp, E2BIG, err);
				else
				{
					dp = inc_suffix;
					while(*cp) *dp++ = *cp++;
					*dp = 0;
					Dz1Error_set(errp, 0);
				}
			}
			else if (strncmp("-O", arg, 2) == 0)
			{
				char *cp = arg + 2;
				dp = out_path;
				while(*cp) *dp++ = *cp++;
				*dp = 0;
				if (Dz1DirA_isExist(out_path) == FALSE) ERR_SET_OUT_RET(errp, ENOENT, err);
				else Dz1Error_set(errp, 0);
			}
			else
			{
				Dz1Thread_printf("Unknown Option [%s]\n", arg);
				print_help(argv[0]);
				ERR_SET_OUT_RET(errp, EINVAL, err);
			}
		}
		else
		{
			char *cp = arg;
			names[name_cnt] = name_dp;
			while(*cp)
			{
				if (*cp == '*' || *cp == '?') ERR_SET_OUT_RET(errp, EPERM, err);
				else *name_dp++ = *cp++;
			}

			*name_dp++ = 0;
			name_cnt++;
		}
	}

	Dz1Thread_printf("Suffix = [%s]\n", out_suffix);
	Dz1Thread_printf("Out Path = [%s]\n", out_path);

	for (i = 0; i < name_cnt; i++)
	{
		Dz1Thread_printf("Target File = %s\n", names[i]);
		if ((*errp = _generate(names[i], out_path, out_suffix, inc_suffix)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return err;
}
// Generate
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Cleanup_init();
	if (argc == 1 || strcmp(argv[1], "-help") == 0) print_help(argv[0]);
	else if (strcmp(argv[1], "-C") == 0)
	{
		Dz1Thread_setFpTab(Dz1T("\t"));
		if ((*errp = _compile(argc, argv)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (strcmp(argv[1], "-G") == 0)
	{
		Dz1Thread_setFpTab(Dz1T("\t"));
		if ((*errp = _convert(argc, argv)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (strcmp(argv[1], "-syntax") == 0)
	{
		Dz1Todec_syntax_dump();
	}
	else print_help(argv[0]);

	if (pause_at_end)
	{
		Dz1Thread_printf(Dz1T("Press Any Key...\n"));
		Dz1Thread_getch(-1, NULL);
	}

	return errp->code;
}
