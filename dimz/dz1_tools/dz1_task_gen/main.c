#include <dz1_cleanup.h>
#include <dz1_task_gen.h>

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

#define MY_SDK_PATH				Dz1T("D:") DIR_SEPRATOR Dz1T("Implements") DIR_SEPRATOR Dz1T("_SDK_")
#define CODECONV_PATH_ABS		MY_SDK_PATH DIR_SEPRATOR Dz1T("codeconv")
#define PTHREAD_PATH_ABS		MY_SDK_PATH DIR_SEPRATOR Dz1T("pthreads.2")
#define DIMZ_PATH_ABS			MY_SDK_PATH DIR_SEPRATOR Dz1T("dimz")
#define GEN_PARENT_PATH_ABS		DIMZ_PATH_ABS DIR_SEPRATOR Dz1T("dz1_tools") DIR_SEPRATOR Dz1T("dz1_task_gen") DIR_SEPRATOR Dz1T("TestOut")

static bool_t _gen_test(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
#ifdef TEST_OLD_MODE
	GenArgs *args = GenArgs_new(Dz1GenTarget_Task, Dz1GenTextMode_DOS, 
								Dz1TaskGenWordSize_32, Dz1TaskGenEndian_Little,
								GEN_PARENT_PATH_ABS, "MyTask", "MY_TASK",
								CODECONV_PATH_ABS, PTHREAD_PATH_ABS, DIMZ_PATH_ABS,
								DZ1_GEN_FLAG_TEST_MAIN | DZ1_GEN_FALG_VC90_PROJ | DZ1_GEN_FALG_VC_SLN, errp);
	if (args == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(GenArgs_delAndSetNull, (void *)&args);

		if ((*errp = Dz1Dir_flush(GEN_PARENT_PATH_ABS)).code) ERR_OUT(errp);
		else if ((*errp = Dz1TaskGen(args)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (GenArgs_delAndSetNull, (void *)&args);
	}
#else
	GenArgs2 *args = GenArgs2_new(GEN_PARENT_PATH_ABS, Dz1GenTarget_Task, Dz1T("MyTask"),
								  TRUE,			// gen_test_main
								  TRUE,			// gen_makefile
								  NULL,			// gen_studios
								  Dz1GenTextMode_DOS, Dz1TaskGenEndian_Little, GenArgs2Naming_canonical,
								  CODECONV_PATH_ABS, DIMZ_PATH_ABS, NULL, errp);
	if (args == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&args);

		if ((*errp = Dz1Dir_flush(GEN_PARENT_PATH_ABS)).code) ERR_OUT(errp);
		else if ((args->gen_studios = GenArgs2VisualStudio_new(PTHREAD_PATH_ABS, DZ1_TASK_GEN_SOLUTION | DZ1_TASK_GEN_VC90 | DZ1_TASK_GEN_VS2022, errp)) == NULL) ERR_OUT(errp);
		else if ((args->libraries = GenArgs2LibraryInfo_new(errp)) == NULL) ERR_OUT(errp);
		else if (Dz1TaskGen2(args, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (GenArgs2_delAndSetNull, (void *)&args);
	}
#endif
	return errp->code == 0 ? TRUE : FALSE;
}

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();
	Dz1Str bn = basename(argv[0]);
	if ((logfp = Dz1FileStream_open3(Dz1T("."), bn, Dz1T("log.txt"), Dz1T("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		fflush(logfp);

		Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (_gen_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

#ifdef _DEBUG
	Dz1Thread_printf("press any key...\n");
	Dz1Thread_getch(-1, NULL);
#endif
	return err.code;
}