#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_meta_tag_util.h>
#include "dz1_meta_tag_test_codec.h"

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


///////////////////////////////////////////////////////////////////////////////
// CODEC TEST : Dz1MetaTagDB
static void _cmd_test_tag_db(void *ptr, str_t pcmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDB *p = (Dz1MetaTagDB *)ptr;
	if ((*errp = Dz1MetaTagDBCodec_test(p, TRUE)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
}
// CODEC TEST : Dz1MetaTagDB
///////////////////////////////////////////////////////////////////////////////

#define MY_TARGET_TYPE		0x0000CAFE
///////////////////////////////////////////////////////////////////////////////
// CODEC TEST : Dz1MetaTagData
static void _cmd_test_tag_data(void *ptr, str_t n, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDB *db = (Dz1MetaTagDB *)ptr;
	Dz1MetaTagData *p = Dz1MetaTagData_new(MY_TARGET_TYPE, errp);
	if (p == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&p);

		if		((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 1))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue16(p, 1, 100)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue16(p, 1, 101)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue16(p, 1, 101)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue16(p, 1, 103)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 2))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue32(p, 2, 200)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue32(p, 2, 201)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue32(p, 2, 202)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 3))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue8(p, 3, 5)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 4))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValueBinB(p, 4, (u8_t *)"ABCDEFG", 7)).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValueBinB(p, 4, (u8_t *)"BCDEFGH", 7)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 5))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValue32(p, 5, 1)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 6))).code) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagData_addTagValueBinB(p, 6, (u8_t *)"BINARY", 6)).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagData_addTag(p, Dz1MetaTagDB_getTagDescr(db, 7))).code) ERR_OUT(errp);

		else if ((*errp = Dz1MetaTagDataCodec_test(p, TRUE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1MetaTagData_delAndSetNull, (void *)&p);
	}
}
// CODEC TEST : Dz1MetaTagData
///////////////////////////////////////////////////////////////////////////////

static void _cmd_test_usage(str_t n) { Dz1Thread_printf("Usgae] %s <db | data>\n", n); }
static Dz1ShellCmdReturn _cmd_test(void *ptr, int argc, char *argv[])
{
	if (argc < 2) _cmd_test_usage(argv[0]);
	else if (strncmp(argv[1], "db", strlen(argv[1])) == 0) _cmd_test_tag_db(ptr, argv[0], argc-1, &argv[1]);
	else if (strncmp(argv[1], "data", strlen(argv[1])) == 0) _cmd_test_tag_data(ptr, argv[0], argc-1, &argv[1]);
	else _cmd_test_usage(argv[0]);

	return Dz1ShellCmdReturn_ok;
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_meta_tag", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_meta_tag", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "t", _cmd_test, task, "{command description}")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

static Dz1Error _init_tags(Dz1MetaTagDB *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDescrEntry *descr = NULL;
//	if		((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 1, "NumberTag", "EUC-KR", Dz1MetaTagValueStoragePresent_array, errp)) == NULL) ERR_OUT(errp);
//	else if ((*errp = Dz1MetaTagDescrEntry_setDescrInt(descr)).code) ERR_OUT(errp);
	if		((descr = Dz1MetaTagDB_addTagDescr(dst, 1, Dz1T("NumberTag"), FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrNumber(descr, Dz1MetaTagDescrNum_signed)).code) ERR_OUT(errp);

// 	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 2, "UnsignedTag", "EUC-KR", Dz1MetaTagValueStoragePresent_table, errp)) == NULL) ERR_OUT(errp);
// 	else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr)).code) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 2, Dz1T("UnsignedTag"), FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrNumber(descr, Dz1MetaTagDescrNum_unsigned)).code) ERR_OUT(errp);

// 	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 3, "GradeTag", "EUC-KR", Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 3, Dz1T("GradeTag"), TRUE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrGradeAnsi(descr, 5, "A", "EUC-KR")).code) ERR_OUT(errp);

//	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 4, "StringTag", "EUC-KR", Dz1MetaTagValueStoragePresent_table, errp)) == NULL) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 4, Dz1T("StringTag"), FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrString(descr, "EUC-KR")).code) ERR_OUT(errp);

//	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 5, "BlobTag", "EUC-KR", Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
//	else if ((*errp = Dz1MetaTagDescrEntry_setDescrUInt(descr)).code) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 5, Dz1T("BlobTag"), FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrBinary(descr)).code) ERR_OUT(errp);

//	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 6, "MyBinary", "EUC-KR", Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
// 	else if ((*errp = Dz1MetaTagDescrEntry_setDescrUser(descr)).code) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 6, Dz1T("MyBinary"), FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1MetaTagDescrEntry_setDescrBinary(descr)).code) ERR_OUT(errp);

//	else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(dst, 7, "MyFavorit", "EUC-KR", Dz1MetaTagValueStoragePresent_none, errp)) == NULL) ERR_OUT(errp);
	else if ((descr = Dz1MetaTagDB_addTagDescr(dst, 7, Dz1T("MyFavorit"), FALSE, errp)) == NULL) ERR_OUT(errp);

	return err;
}

int main(int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MetaTagDB *db = NULL;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_meta_tagTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	if ((db = Dz1MetaTagDB_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&db);
		if ((*errp = _init_tags(db)).code) ERR_OUT(errp);
		else _shell_start(db);
		pthread_cleanup_pop(1); // (Dz1MetaTagDB_delAndSetNull, (void *)&db);
	}


#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
	return err.code;
}
