#include <dz1_sync.h>
#include <dz1_shell.h>
#include <dz1_task.h>
#include <dz1_socket.h>
#include <dz1_thread_stdio.h>
#include <dz1_usleep.h>

#include "dz1_inet_ftp.h"
#include "dz1_inet_ftp_control_pi_msg_test.h"

static void fileCB(void *ptr, Dz1SockAddr *peer, Dz1InetFtpTransfer *transfer)
{
	Dz1Thread_printf("fileCB() : PEER = "); Dz1SockAddr_dump(peer, 0);
	Dz1Thread_printf("fileCB() : Transfer = "); Dz1InetFtpTransfer_dump(transfer, 0);
}

#define UPLOAD			TRUE
#define DOWNLOAD		FALSE

#define ioBUFFER		TRUE
#define ioFILE			FALSE
static struct Transfers
{
	str_t	name;
	str_t	remotePath;
	bool_t	isUpload;
	bool_t	localIsBuffer;
	str_t	localPath;
} Transfers[] =
{
//	{ "임진강수영대회배너2.jpg",		"/BIS/DOWN/FILE",		DOWNLOAD,	ioFILE,		NULL },
	{ "20111205.zip",				"MASTER/20111205",		DOWNLOAD,	ioFILE,		NULL },
//	{ "BitCore2Test.zip",			NULL,					DOWNLOAD,	ioFILE,		NULL },
//	{ "hae_inet_telnet.c",			"/test/sample/001",		UPLOAD,		ioFILE,		NULL },
//	{ "hae_inet_rdate.c",			"/test/sample/002",		UPLOAD,		ioFILE,		NULL },
//	{ "my_msg.txt",					"/test/sample1/194",	UPLOAD,		ioBUFFER,	"This is My Message" },
//	{ "hae_inet_telnet.c",			"/test/sample/001",		DOWNLOAD,	ioFILE,		NULL },
//	{ "hae_inet_rdate.c",			"/test/sample/002",		DOWNLOAD,	ioBUFFER,	NULL },
//	{ "my_msg.txt",					"/test/sample/003",		DOWNLOAD,	ioBUFFER,	NULL },
	
//	{ "mv.avi",						NULL,					UPLOAD,		ioFILE,		NULL },
//	{ "MAINAPP_20100314170625.ZIP",	"/BIS/DOWN/MAINAPP",	DOWNLOAD,	ioFILE,		NULL },
	{ NULL, NULL }
};

static Dz1Error _Dz1InetFtpTransferList_init(Dz1InetFtpFileInfo *local, str_t name, str_t path)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	switch(local->present)
	{
	case Dz1InetFtpFileInfoPresent_buffer:
		if (path != NULL && (local->x.buffer = Dz1Binary_new((u8_t *)path, (u32_t)strlen(path), &err)) == NULL) ERR_OUT(&err);
		break;
	case Dz1InetFtpFileInfoPresent_file:
		if ((local->x.file = Dz1InetFtpFileName_new(path, name, (u32_t)strlen(name), &err)) == NULL) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}
static Dz1Error Dz1InetFtpTransferList_init(Dz1InetFtpTransferList *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetFtpTransfer *node = NULL;
	struct Transfers *i;
	for (i = Transfers; i->name != NULL; i++)
	{
		if ((node = Dz1InetFtpTransfer_new(i->isUpload ? Dz1InetFtpDirection_upload : Dz1InetFtpDirection_download,
											NULL, NULL, TRUE, 0, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetFtpFileInfo *local = NULL;
			pthread_cleanup_push(Dz1InetFtpTransfer_delAndSetNull, (void *)&node);

			if ((node->remote = Dz1InetFtpFileName_new(i->remotePath, i->name, (u32_t)strlen(i->name), &err)) == NULL) ERR_OUT(&err);
			else if ((local = node->local = Dz1InetFtpFileInfo_new(i->localIsBuffer ? Dz1InetFtpFileInfoPresent_buffer :
																					  Dz1InetFtpFileInfoPresent_file, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _Dz1InetFtpTransferList_init(local, i->name, i->localPath)).code) ERR_OUT(&err);
			else if ((err = dst->add(dst, node)).code) ERR_OUT(&err);
			else node = NULL;

			pthread_cleanup_pop(1); // (Dz1InetFtpTransfer_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

//#define LOCAL_FTP_SERVER
#define IC_FTP_SERVER
static void cmd_upload_usage(str_t n) { Dz1Thread_printf("Usage] %s [<ip> [<port>]]\n", n); }
static Dz1ShellCmdReturn cmd_upload(void *tFTP, int argc, char *argv[])
{
	if (argc != 3 && argc != 2 && argc != 1) cmd_upload_usage(argv[0]);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1InetFtpTransferList *files =  NULL;
		Dz1SockAddr peer;
#if defined(LOCAL_FTP_SERVER)
		str_t ipStr = "127.0.0.1";
		u16_t port = 21;
		str_t user = "BIT_CLIENT";
		str_t pass = "BIT_CLIENT";
		bool_t passive = TRUE;
#elif defined(GM_FTP_SERVER)
		str_t ipStr = "192.168.180.241";
		u16_t port = 21;
		str_t user = "bit";
		str_t pass = "!@#123qwe";
		bool_t passive = TRUE;
#elif defined(GM_FTP_SERVER2)
		str_t ipStr = "192.168.180.241";
		u16_t port = 9000;
		str_t user = "bit";
		str_t pass = "!@#123qwe";
		bool_t passive = TRUE;
#elif defined(BC_FTP_SERVER)
		str_t ipStr = "192.168.75.12";
		u16_t port = 21;
		str_t user = "bit";
		str_t pass = "!@#123qwe";
		bool_t passive = TRUE;
#elif defined(IC_FTP_SERVER)
		str_t ipStr = "10.1.11.60";
		u16_t port = 21;
		str_t user = "BIT";
		str_t pass = "BIT1234";
		bool_t passive = TRUE;
#else
#error "Server Not Defined
#endif
		if (argc >= 2) ipStr = argv[1];
		if (argc >= 3) port = (u16_t)atoi(argv[2]);

		if (port == 0) cmd_upload_usage(argv[0]);
		else if ((err = Dz1SockAddr_setAddrStr(&peer, ipStr)).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);
		else if ((files = Dz1InetFtpTransferList_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetFtpTransferList *result =  NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)files);

			if ((err = Dz1InetFtpTransferList_init(files)).code) ERR_OUT(&err);
			//else if ((err = Dz1InetFtpCall_transfer(tFTP, &peer, "test", "test", NULL,
			else if ((err = Dz1InetFtpCall_transfer(tFTP, &peer, user, pass, NULL,
													passive,
													files, fileCB, NULL, &result)).code) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)result);
				//Dz1Thread_usleep(1000000);
				//Dz1Thread_printf("Result = "); Dz1InetFtpTransferList_dump(result, 0);
				Dz1Thread_printf("Done\n");
				pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)result);
			}

			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)files);
		}
	}
	return Dz1ShellCmdReturn_ok;
}

static str_t _getPathAndName(str_t src, str_t path, str_t name)
{
	char *cp = NULL, *ret = NULL;
	strcpy(path, src);
	if ((cp = strrchr(path, DIR_SEP)) != NULL || (cp = strrchr(path, '/')) != NULL)
	{
		*cp++ = '\0';
		strcpy(name, cp);
		ret = path;
	}
	else strcpy(name, path);
	return ret;
}

static void cmd_loop_usage(str_t n) { Dz1Thread_printf("Usage] %s <id> <pass> <filename> <count> [<ip> [<port>]]\n", n); }
static Dz1ShellCmdReturn cmd_loop(void *tFTP, int argc, char *argv[])
{
	if (argc != 7 && argc != 6 && argc != 5) cmd_loop_usage(argv[0]);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1InetFtpTransferList *files =  NULL;
		Dz1SockAddr peer;
		str_t ipStr = "10.1.11.60";
		u16_t port = 21;

		char name[4096] = { 0, };
		char _path[4096] = { 0, }, *path = _getPathAndName(argv[3], _path, name);
		u32_t count = (u32_t)atoi(argv[4]), i;


		if (argc >= 6) ipStr = argv[5];
		if (argc >= 7) port = (u16_t)atoi(argv[6]);

		if (port == 0 || count == 0) cmd_loop_usage(argv[0]);
		else if ((err = Dz1SockAddr_setAddrStr(&peer, ipStr)).code) ERR_OUT(&err);
		else if ((err = Dz1SockAddr_setPort(&peer, port)).code) ERR_OUT(&err);
		else
		{
			for (i = 0; i < count; i++)
			{
				Dz1Thread_printf("=====================================\n");
				Dz1Thread_printf("Test Loop : %u\n", i);
				Dz1Thread_printf("=====================================\n");
				if ((files = Dz1InetFtpTransferList_new(&err)) == NULL) ERR_OUT(&err);
				else
				{
					Dz1InetFtpTransfer *node = NULL;
					pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)files);

					if ((node = Dz1InetFtpTransfer_new(Dz1InetFtpDirection_download, NULL, NULL, TRUE, 0, &err)) == NULL) ERR_OUT(&err);
					else
					{
						Dz1InetFtpFileInfo *local = NULL;
						pthread_cleanup_push(Dz1InetFtpTransfer_delAndSetNull, (void *)&node);


						if ((node->remote = Dz1InetFtpFileName_new(path, name, (u32_t)strlen(name), &err)) == NULL) ERR_OUT(&err);
						else if ((local = node->local = Dz1InetFtpFileInfo_new(Dz1InetFtpFileInfoPresent_file, NULL, &err)) == NULL) ERR_OUT(&err);
						else if ((local->x.file = Dz1InetFtpFileName_new(".", name, (u32_t)strlen(name), &err)) == NULL) ERR_OUT(&err);
						else if ((err = files->add(files, node)).code) ERR_OUT(&err);
						else
						{
							Dz1InetFtpTransferList *result =  NULL;
							node = NULL;
							if ((err = Dz1InetFtpCall_transfer(tFTP, &peer, argv[1], argv[2], NULL, TRUE,
																files, fileCB, NULL, &result)).code) ERR_OUT(&err);
							else
							{
								pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)result);
								Dz1Thread_printf("Done\n");
								pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)result);
							}
						}
						pthread_cleanup_pop(1); // (Dz1InetFtpTransfer_delAndSetNull, (void *)&node);
					}
					pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpTransferList_del, (void *)files);
				}
			}
		}
	}
	return Dz1ShellCmdReturn_ok;
}

static Dz1Error user_main(void *task)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	void *shell = NULL;
#ifndef UNIX_SYSTEM
	if ((shell = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#else
	if ((shell = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 255, "root", "Dz1SockClient", &err)) == NULL) { ERR_OUT(&err); }
#endif
	else
	{
		pthread_cleanup_push(Dz1Shell_del, shell);

		if ((err = Dz1Shell_cmdReg(shell, "upload", cmd_upload, (void *)task, "FTP Upload Test")).code) { ERR_OUT(&err); }
		if ((err = Dz1Shell_cmdReg(shell, "loop", cmd_loop, (void *)task, "FTP Download Stress Test")).code) { ERR_OUT(&err); }
		else Dz1Shell_start(shell, NULL);

		pthread_cleanup_pop(1); // (Dz1Shell_del, shell);
	}
	return err;
}

static __inline__ void sync_test(Dz1Sync *s)
{
	pthread_testcancel();
	pthread_testcancel();
}

int main(void)
{
	void *task = NULL;

	Dz1Error err = DZ1_ERROR_INITIALIZER;

	//Dz1Sync sync;
	//sync_test(&sync);
	if (Dz1Socket_init())
	{
		pthread_cleanup_push(Dz1Socket_initCancel, NULL);
		if ((err = Dz1InetFtpCPIMsg_test()).code) ERR_OUT(&err);

		if ((task = Dz1InetFtp_new("EUC-KR", NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);

			//if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
			if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(&err);
			else if ((err = user_main(task)).code) { ERR_OUT(&err); }
			pthread_cleanup_pop(1); //(Dz1Task_delAndSetNull, (void *)task);
		}
		pthread_cleanup_pop(1); // (Dz1Socket_initCancel, NULL);
	}
	else Dz1Thread_printf("WinSock Initializer Fail\n");

	return err.code;
}
