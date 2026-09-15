#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_gasn_support.h>
#ifdef _DEBUG
#include <conio.h>
#endif

#include "ItsIso14827Test.h"
#include "ItsIso14827TestEam.h"

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

static void _task_exception_handler(void *ptr, Dz1Error *reason)
{
	Dz1Thread_printf("ItsIso14827 : Exception Catch\n");
	ERR_OUT(reason);
}

void *t14827 = NULL;
static void *tServer = NULL;
static void *tClient = NULL;

static void _test_cleanup(void *ptr)
{
	Dz1Task_delAndSetNull(&tServer);
	Dz1Task_delAndSetNull(&tClient);
}

///////////////////////////////////////////////////////////////////////////////
// Domain : Server
static TestServerUserEntry users[] =
{
	{ DEFAULT_USER_NAME, DEFAULT_USER_PASS }
};
size_t users_cnt = sizeof(users) / sizeof(TestServerUserEntry);

static void _cmdDomain_server_createUsage(str_t n) { Dz1Thread_printf("Usage] %s <maxClient>\n", n); }
static void _cmdDomain_server_create(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);
	if (argc != 2) _cmdDomain_server_createUsage(n);
	else if (tServer != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		u32_t maxClient = (u32_t)atoi(argv[1]);
		if (maxClient == 0) ERR_SET_OUT(errp, EINVAL);
		else if ((tServer = TestServerTask_new(SERVER_DOMAIN_DEFAULT, maxClient, users, (u32_t)users_cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&tServer);

			if ((*errp = Dz1Task_start(tServer, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&tServer);
		}
	}
}

static void _cmdDomain_server_deleteUsage(str_t n) { Dz1Thread_printf("Usage] %s\n", n); }
static void _cmdDomain_server_delete(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);
	if (argc != 1) _cmdDomain_server_deleteUsage(n);
	else if (tServer == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&tServer);

		if ((*errp = Dz1Task_stop(tServer, TRUE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&svr_domain);
	}
}

static void _cmdDomain_server_initiateUsage(str_t n) { Dz1Thread_printf("Usage] %s [-a=<ip>] [-p=<port>] [-c=<codec>] [-crc=<crc_mode>] [<peer_domain>]\n", n); }
static void _cmdDomain_server_initiate(void *task, str_t parent_cmd, int argc, char *argv[])
{
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);
	if (argc > 6) _cmdDomain_server_initiateUsage(n);
	else
	{
		DZ1_ERROR_SAFE_VAR(errp, err);

		Dz1Str str_addr = NULL; // Dz1T("127.0.0.1");
		u32_t port = 0; // DEFAULT_TEST_PORT_NUMBER;
		Dz1Asn1Codec codec = Dz1Asn1Codec_unknown; // Dz1Asn1Codec_ber;
		ItsIso14827CRCCheck crc = ItsIso14827CRCCheck_max; // ItsIso14827CRCCheck_warning;
		Dz1Str str_peer_domain = NULL;

		Dz1SockAddr dst_addr;
		Dz1Asn1UTF8Str *peer_domain = NULL;

		int i;
		for (i = 1; i < argc; i++)
		{
			if (Dz1STRNCMP(argv[i], Dz1T("-a="), 3) == 0)
			{
				if (str_addr != NULL) { _cmdDomain_server_initiateUsage(n); return; }
				else str_addr = &argv[i][3];
			}
			else if (Dz1STRNCMP(argv[i], Dz1T("-p="), 3) == 0)
			{
				if (port != 0) { _cmdDomain_server_initiateUsage(n); return; }
				else
				{
					Dz1Str portp = &argv[i][3];
					if ((port = Dz1StrTo32(portp)) == 0 || port > 0xFFFF) { Dz1Thread_printf(Dz1T("port = 1 ~ 65535\n")); return; }
				}
			}
			else if (Dz1STRNCMP(argv[i], Dz1T("-c="), 3) == 0)
			{
				if (codec != Dz1Asn1Codec_unknown) { _cmdDomain_server_initiateUsage(n); return; }
				else
				{
					Dz1Str strp = &argv[i][3];
					if ((codec = Dz1Asn1CodecFromStr(strp)) == Dz1Asn1Codec_unknown) { _cmdDomain_server_initiateUsage(n); return; }
				}
			}
			else if (Dz1STRNCMP(argv[i], Dz1T("-crc="), 5) == 0)
			{
				if (crc != ItsIso14827CRCCheck_max) { _cmdDomain_server_initiateUsage(n); return; }
				else
				{
					Dz1Str strp = &argv[i][5];
					if ((crc = ItsIso14827CRCCheckFromStr(strp)) == ItsIso14827CRCCheck_max) { _cmdDomain_server_initiateUsage(n); return; }
				}
			}
			else
			{
				if (str_peer_domain != NULL) { _cmdDomain_server_initiateUsage(n); return; }
				else str_peer_domain = argv[i];
			}
		}

		if (str_addr == NULL) str_addr = Dz1T("127.0.0.1");
		if (port == 0) port = DEFAULT_TEST_PORT_NUMBER;
		if (codec == Dz1Asn1Codec_unknown) codec = Dz1Asn1Codec_ber;
		if (crc == ItsIso14827CRCCheck_max) crc = ItsIso14827CRCCheck_warning;
		if (str_peer_domain == NULL) str_peer_domain = CLIENT_DOMAIN_DEFAULT;

		if ((*errp = Dz1SockAddr_setAddrStr(&dst_addr, str_addr)).code) ERR_OUT(errp);
		else if (port == 0 || port > 65535) ERR_SET_OUT(errp, EINVAL);
		else if ((*errp = Dz1SockAddr_setPort(&dst_addr, (u16_t)(port & 0xFFFF) )).code) ERR_OUT(errp);
		else if ((peer_domain = Dz1Asn1UTF8Str_newFromStr(str_peer_domain, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1UTF8Str *my_domain = NULL;
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&peer_domain);

			if ((my_domain = Dz1Asn1UTF8Str_newFromStr(SERVER_DOMAIN_DEFAULT, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&my_domain);

				if ((*errp = ItsIso14827_connectToClient(task, &dst_addr, my_domain, peer_domain, codec, crc)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&my_domain);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&peer_domain);
		}
	}
}

static void _cmdServerUsage(str_t n) { Dz1Thread_printf("Usage] %s <create|delete|initiate> <...>\n", n); }
static Dz1ShellCmdReturn _cmdServer(void *task, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	if (argc < 2) _cmdServerUsage(argv[0]);
	else if (strcmp(argv[1], "create") == 0 || strcmp(argv[1], "n") == 0)   _cmdDomain_server_create(task,   argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "delete") == 0 || strcmp(argv[1], "d") == 0)   _cmdDomain_server_delete(task,   argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "initiate") == 0 || strcmp(argv[1], "i") == 0) _cmdDomain_server_initiate(task, argv[0], argc-1, &argv[1]);
	else _cmdServerUsage(argv[0]);
	return ret;
}
// Domain : Server
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Client
static void _cmdClientCreateUsage(str_t n) { Dz1Thread_printf("Usage] %s [<mode>]\n", n); }
static void _cmdClientCreate(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc != 1 && argc != 2) _cmdClientCreateUsage(n);
	else if (tClient != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		Dz1Str mode = Dz1Text("TEST");

		if (argc == 2) mode = argv[1];

		if ((tClient = TestClientTask_new(mode, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&tClient);

			if ((*errp = Dz1Task_start(tClient, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&tClient);
		}
	}
}

static void _cmdClientDeleteUsage(str_t n) { Dz1Thread_printf("Usage] %s\n", n); }
static void _cmdClientDelete(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc != 1) _cmdClientDeleteUsage(n);
	else if (tClient == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&tClient);

		if ((*errp = Dz1Task_stop(tClient, TRUE)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&tClient);
	}
}

static void _cmdClientConnectUsage(str_t n) { Dz1Thread_printf("Usage] %s [<ip> [<port>]]\n", n); }
static void _cmdClientConnect(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc > 3) _cmdClientConnectUsage(n);
	else if (selectedClient == NULL || tClient == NULL) ERR_SET_OUT(&err, ENOSYS);
	else
	{
		Dz1SockAddr dst_addr;
		Dz1Str addr_str = selectedClient->ipStr;
		u32_t port = (u32_t)selectedClient->port & 0xFFFF;

		if (argc >= 2) addr_str = argv[1];
		if (argc >= 3)
		{
			if ((port = Dz1StrTo32(argv[2])) == 0 || port > 65535)
			{
				Dz1Thread_printf(Dz1T("port = 1 ~ 65535\n"));
				return;
			}
		}

		if ((*errp = Dz1SockAddr_setAddrByName(&dst_addr, addr_str)).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&dst_addr, (u16_t)(port & 0xFFFF) )).code) ERR_OUT(errp);
		else if (TestClient_connect(tClient, &dst_addr, selectedClient->peerDomainStr, selectedClient->userStr, selectedClient->passStr, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}

static void _cmdClientDisonnectUsage(Dz1Str n) { Dz1Thread_printf("Usage] %s [<peerDomain>]\n", n); }
static void _cmdClientDisonnect(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc > 2) _cmdClientDisonnectUsage(n);
	else if (selectedClient == NULL || tClient == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Str peerDomain = selectedClient->peerDomainStr;
		if (argc >= 2) peerDomain = argv[1];

		if (TestClient_disconnect(tClient, peerDomain, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}

static void _cmdClientSingleUsage(str_t n) { Dz1Thread_printf("Usage] %s <msgNum> [<peerDomain>]\n", n); }
static void _cmdClientSingle(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc < 2 || argc > 3) _cmdClientSingleUsage(n);
	else if (selectedClient == NULL || tClient == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Str peerDomain = selectedClient->peerDomainStr;
		u32_t req_code = Dz1StrTo32(argv[1]);
		if (argc >= 3) peerDomain = argv[2];

		if (TestClient_single(tClient, peerDomain, req_code, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}

static u32_t periodic_sub_id = (u32_t)-1;

static void _cmdClientPeriodicUsage(str_t n) { Dz1Thread_printf("Usage] %s <-1=stop | msgNum> [<peerDomain>]\n", n); }
static void _cmdClientPeriodic(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc < 2 || argc > 3) _cmdClientPeriodicUsage(n);
	else if (selectedClient == NULL || tClient == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1Str peerDomain = selectedClient->peerDomainStr;
		u32_t num = Dz1StrTo32(argv[1]);

		if (argc >= 3) peerDomain = argv[2];

		if (TestClient_periodic(tClient, peerDomain, num, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
}

static void _cmdClientFrEDUsage(str_t n) { Dz1Thread_printf("Usage] %s on | off\n", n); }
static void _cmdClientFrED(void *task, str_t parent_cmd, int argc, char *argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc != 2) _cmdClientFrEDUsage(n);
	else
	{
		bool_t disable_heartbeat = FALSE;
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1T("on")) == 0 || Dz1STRCMP(argv[1], Dz1T("o")) == 0 || Dz1STRCMP(argv[1], Dz1T("1")) == 0) disable_heartbeat = FALSE;
		else if (Dz1STRCMP(argv[1], Dz1T("off")) == 0 || Dz1STRCMP(argv[1], Dz1T("x")) == 0 || Dz1STRCMP(argv[1], Dz1T("0")) == 0) disable_heartbeat = TRUE;
		else
		{
			_cmdClientFrEDUsage(n);
			return;
		}

		if (selectedClient == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if ((*errp = ItsIso14827_controlClient(t14827, selectedClient->myDomainStr, selectedClient->peerDomainStr, selectedClient->userStr, 
													ItsIso14827ClientCtrlFlag_HeartBeatOFF, disable_heartbeat)).code) ERR_OUT(errp);
	}
}

static void _cmdclientUsage(str_t n) { Dz1Thread_printf("Usage] %s <create|delete|connect|disconnect|single> <param...>\n", n); }
static Dz1ShellCmdReturn _cmdClient(void *task, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	if (argc < 2) _cmdclientUsage(argv[0]);
	else if (strcmp(argv[1], "create") == 0		|| strcmp(argv[1], "n") == 0) _cmdClientCreate(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "delete") == 0		|| strcmp(argv[1], "d") == 0) _cmdClientDelete(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "connect") == 0	|| strcmp(argv[1], "c") == 0) _cmdClientConnect(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "disconnect") == 0	|| strcmp(argv[1], "x") == 0) _cmdClientDisonnect(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "single") == 0		|| strcmp(argv[1], "s") == 0) _cmdClientSingle(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "periodic") == 0	|| strcmp(argv[1], "p") == 0) _cmdClientPeriodic(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "fred") == 0		|| strcmp(argv[1], "f") == 0) _cmdClientFrED(task, argv[0], argc-1, &argv[1]);
	return ret;
}
// Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Session
static void _cmdSession_openUsage(str_t n) { Dz1Thread_printf("Usage] %s <port> [<initialCodec> [<initialCRCMode>]]\n", n); }
static void _cmdSession_open(void *task, str_t parent_cmd, int argc, char *argv[])
{
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc < 2 || argc > 4) _cmdSession_openUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = (u32_t)atoi(argv[1]);
		Dz1Asn1Codec codec = Dz1Asn1Codec_ber;
		ItsIso14827CRCCheck crcMode = ItsIso14827CRCCheck_explict;
		if (port == 0 || port > 65535) ERR_SET_OUT(&err, EINVAL);
		else if (argc >= 3 && (codec = Dz1Asn1CodecFromStr(argv[2])) == Dz1Asn1Codec_unknown) ERR_SET_OUT(&err, EINVAL);
		else if (argc >= 4 && (crcMode = ItsIso14827CRCCheckFromStr(argv[3])) == ItsIso14827CRCCheck_max) ERR_SET_OUT(&err, EINVAL);
		else if ((err = ItsIso14827_openPort(task, (u16_t)(port & 0xFFFF), codec, crcMode)).code) ERR_OUT(&err);
	}
}

static void _cmdSession_closeUsage(str_t n) { Dz1Thread_printf("Usage] %s <port>\n", n); }
static void _cmdSession_close(void *task, str_t parent_cmd, int argc, char *argv[])
{
	TCHAR n[64];
	Dz1SNPRINTF(n, 64, Dz1T("%s %s"), parent_cmd, argv[0]);

	if (argc != 2) _cmdSession_closeUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = (u32_t)atoi(argv[1]);
		if (port == 0 || port > 65535) ERR_SET_OUT(&err, EINVAL);
		else if ((err = ItsIso14827_closePort(task, (u16_t)(port & 0xFFFF))).code) ERR_OUT(&err);
	}
}

static void _cmdSessionUsage(str_t n) { Dz1Thread_printf("Usage] %s <open|close> <...>\n", n); }
static Dz1ShellCmdReturn _cmdSession(void *task, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	if (argc < 2) _cmdSessionUsage(argv[0]);
	else if (strcmp(argv[1], "open") == 0 || strcmp(argv[1], "o") == 0) _cmdSession_open(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "close") == 0 || strcmp(argv[1], "c") == 0) _cmdSession_close(task, argv[0], argc-1, &argv[1]);
	else _cmdSessionUsage(argv[0]);
	return ret;
}
// Session
///////////////////////////////////////////////////////////////////////////////

static void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	pthread_cleanup_push(_test_cleanup, NULL);
#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "ItsIso14827", errp)) == NULL) Dz1Error_print(errp, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "ItsIso14827", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);

		if (0) { }
		else if ((*errp = Dz1Shell_cmdReg(sh, "server", _cmdServer, task, "Server Management")).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, "client", _cmdClient, task, "Create Client")).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, "session", _cmdSession, task, "Session Management")).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
	pthread_cleanup_pop(1); // (_test_cleanup, NULL);
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("ItsIso14827Test.log.txt", "wb")) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		fflush(logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	
#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif
	// Edit Task Argument
	if ((t14827 = ItsIso14827_new(_task_exception_handler, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&t14827);
		if ((err = Dz1Task_start(t14827, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void *)t14827);
#if __WORDSIZE == 64
			Dz1Thread_printf(Dz1T("64bit version\n"));
#elif __WORDSIZE == 32
			Dz1Thread_printf(Dz1T("32bit version\n"));
#else
			Dz1Thread_printf(Dz1T("unknown architecture\n"));
#endif
			_shell_start(t14827);

			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)t14827);
		}
		pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&t14827);
	}
#ifdef _DEBUG
	printf("Press Any Key...\n");
	Dz1Thread_getch(-1, NULL);
#endif
	return err.code;
}
