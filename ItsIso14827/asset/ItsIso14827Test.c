#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <ItsIso14827.h>
#include <dz1_gasn_support.h>
//#include <ItsIcMsgDz1Codec.h>
#ifdef _DEBUG
#include <conio.h>
#endif

#include "generator.h"

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
	Dz1Thread_printf("ItsIso14827 : Exception Catched\n");
	ERR_OUT(reason);
}

static ItsIso14827ServerDomainCallback serverCallback =
{
	NULL,			// authenticate

	NULL,			// established
	NULL,			// disconnected
	NULL,			// echoRequest

	NULL,			// singleRequest

	NULL,			// eventPrepare
	NULL,			// eventStart
	NULL,			// eventStop

	NULL,			// periodicPrepare
	NULL,			// periodicStart
	NULL,			// periodicInvoke
	NULL,			// periodicStop

	NULL,			// healthWarning

	NULL			// param
};

static void _cmdDomain_server_createUsage(str_t n) { Dz1Thread_printf("Usage] %s server create <name> <maxClient>\n", n); }
static void _cmdDomain_server_create(void *task, str_t n, int argc, char *argv[])
{
	if (argc != 3) _cmdDomain_server_createUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t maxClient = (u32_t)atoi(argv[2]);
		Dz1Asn1UTF8Str *name = Dz1Asn1UTF8Str_newFromStr(argv[1], &err);
		if (name == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
			if ((err = ItsIso14827_createServer(task, name, maxClient, NULL, 0, &serverCallback)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		}
	}
}

static void _cmdDomain_server_deleteUsage(str_t n) { Dz1Thread_printf("Usage] %s server delete <name>\n", n); }
static void _cmdDomain_server_delete(void *task, str_t n, int argc, char *argv[])
{
	if (argc != 2) _cmdDomain_server_deleteUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1Asn1UTF8Str *name = Dz1Asn1UTF8Str_newFromStr(argv[1], &err);
		if (name == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
			ItsIso14827_deleteServer(task, name);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		}
	}
}

static void _cmdDomain_serverUsage(str_t n) { Dz1Thread_printf("Usage] %s server <create|delete|initiate> <...>\n", n); }
static void _cmdDomain_server(void *task, str_t n, int argc, char *argv[])
{
	if (argc < 2) _cmdDomain_serverUsage(n);
	else if (strcmp(argv[1], "create") == 0 || strcmp(argv[1], "c") == 0) _cmdDomain_server_create(task, n, argc-1, &argv[1]);
	else if (strcmp(argv[1], "delete") == 0 || strcmp(argv[1], "d") == 0) _cmdDomain_server_delete(task, n, argc-1, &argv[1]);
//	else if (strcmp(argv[1], "initiate") == 0 || strcmp(argv[1], "i") == 0) _cmdDomain_server_initiate(task, n, argc-1, &argv[1]);
	else _cmdDomain_serverUsage(n);
}

///////////////////////////////////////////////////////////////////////////////
// Client Command
static ItsIso14827ClientDomainCallback clientCallback =
{
	NULL,			// initiated

	NULL,			// established

	NULL			// param
};

static void _cmdDomain_client_createUsage(str_t n) { Dz1Thread_printf("Usage] %s client create <name>\n", n); }
static void _cmdDomain_client_create(void *task, str_t n, int argc, char *argv[])
{
	if (argc != 3) _cmdDomain_client_createUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
//		u32_t maxClient = (u32_t)atoi(argv[2]);
		Dz1Asn1UTF8Str *name = Dz1Asn1UTF8Str_newFromStr(argv[1], &err);
		if (name == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
			if ((err = ItsIso14827_createClient(task, name, &clientCallback)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		}
	}
}

static void _cmdDomain_client_deleteUsage(str_t n) { Dz1Thread_printf("Usage] %s client delete <name>\n", n); }
static void _cmdDomain_client_delete(void *task, str_t n, int argc, char *argv[])
{
	if (argc != 2) _cmdDomain_client_deleteUsage(n);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		Dz1Asn1UTF8Str *name = Dz1Asn1UTF8Str_newFromStr(argv[1], &err);
		if (name == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
			ItsIso14827_deleteClient(task, name);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		}
	}
}

static void _cmdDomain_clientUsage(str_t n) { Dz1Thread_printf("Usage] %s client <create|delete> <...>\n", n); }
static void _cmdDomain_client(void *task, str_t n, int argc, char *argv[])
{
	if (argc < 2) _cmdDomain_clientUsage(n);
	else if (strcmp(argv[1], "create") == 0 || strcmp(argv[1], "c") == 0) _cmdDomain_client_create(task, n, argc-1, &argv[1]);
	else if (strcmp(argv[1], "delete") == 0 || strcmp(argv[1], "d") == 0) _cmdDomain_client_delete(task, n, argc-1, &argv[1]);
//	else if (strcmp(argv[1], "connect") == 0 || strcmp(argv[1], "o") == 0) _cmdDomain_client_connect(task, n, argc-1, &argv[1]);
//	else if (strcmp(argv[1], "disconnect") == 0 || strcmp(argv[1], "x") == 0) _cmdDomain_client_disconnect(task, n, argc-1, &argv[1]);
}

///////////////////////////////////////////////////////////////////////////////
// Domain Command
static void _cmdDomainUsage(str_t n) { Dz1Thread_printf("Usage] %s <server|client|...> <...>\n", n); }
static Dz1ShellCmdReturn _cmdDomain(void *task, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	if (argc < 2) _cmdDomainUsage(argv[0]);

	else if (strcmp(argv[1], "server") == 0 || strcmp(argv[1], "s") == 0) _cmdDomain_server(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "client") == 0 || strcmp(argv[1], "c") == 0) _cmdDomain_client(task, argv[0], argc-1, &argv[1]);
	return ret;
}

static void _cmdSession_openUsage(str_t n) { Dz1Thread_printf("Usage] %s open <port> [<initialCodec> [<initialCRCMode>]]\n", n); }
static void _cmdSession_open(void *task, str_t n, int argc, char *argv[])
{
	if (argc < 2 || argc > 4) _cmdSession_openUsage(argv[0]);
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
static void _cmdSession_close(void *task, str_t n, int argc, char *argv[])
{
	if (argc != 2) _cmdSession_closeUsage(argv[0]);
	else
	{
		Dz1Error err = DZ1_ERROR_INITIALIZER;
		u32_t port = (u32_t)atoi(argv[1]);
		if (port == 0 || port > 65535) ERR_SET_OUT(&err, EINVAL);
		else if ((err = ItsIso14827_closePort(task, (u16_t)(port & 0xFFFF))).code) ERR_OUT(&err);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Session Command
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



static void _initiated(void *param, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, ItsIso14827SessionKey *key)
{
	Dz1Thread_printf("!!! Initiated\n");
}

static void _terminated(void *param, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, Iso14827Terminate reason)
{
	Dz1Thread_printf("!!! Terminated = %s(%d)\n", Iso14827TerminateStr(reason), reason);
}

static void _pubControl(void *param, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t subscriptionID, u32_t pubSerial, Iso14827PublicationMgmt cmd)
{
	Dz1Thread_printf("<< Pub Control(%u:%u) = %s(%d)\n", subscriptionID, pubSerial, Iso14827PublicationMgmtStr(cmd), cmd);
}

static void _disconnected(void *param, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user)
{
	Dz1Thread_printf("!!! Disconnected\n");
}

static Dz1Asn1UTF8Str *myDomain = NULL;
static Dz1Asn1UTF8Str *peerDomain = NULL;
static Dz1Asn1OctetStr *user = NULL;
static Dz1Asn1OctetStr *pass = NULL;

static void names_delAndSetNull(void *ptr)
{
	Dz1Asn1UTF8Str_delAndSetNull(&peerDomain);
	Dz1Asn1OctetStr_delAndSetNull(&user);
	Dz1Asn1OctetStr_delAndSetNull(&pass);
}
typedef struct ClientModeMap
{
	str_t modeName;
	str_t myDomainStr;
	str_t peerDomainStr;
	str_t ipStr;
	u16_t port;
	str_t userStr;
	str_t passStr;
	MsgGenerator *genTable;
	void (*del)(void *ptr);
	void (*dump)(void *ptr, int tab);
	ssize_t (*enc)(void *src, u8_t **dst, Dz1Asn1Codec codec, str_t *retOID, Dz1Error *err);
	ssize_t (*dec)(str_t oidStr, void **dst, u8_t *src, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
} ClientModeMap;

static ClientModeMap clientModeMap[] =
{
/*
	{ "IPES", "TEST_CLIENT", "TEST_SERVER", "192.168.0.133", 7355, "testuser", "testpass",
			ItsIcIPESGenerator, (Dz1DelFunc)ItsIcIPESMsg_del, (Dz1DumpFunc)ItsIcIPESMsg_dump,
			ItsIcIPESMsg_encode, ItsIcIPESMsg_decode },
	{ "BLES", "TEST_CLIENT", "TEST_SERVER", "192.168.0.133", 7355, "testuser", "testpass",
			ItsIcBLESGenerator, (Dz1DelFunc)ItsIcBLESMsg_del, (Dz1DumpFunc)ItsIcBLESMsg_dump,
			ItsIcBLESMsg_encode, ItsIcBLESMsg_decode },
	{ "AVI", "TEST_CLIENT", "TEST_SERVER", "192.168.0.99", 7355, "testuser", "testpass",
			ItsIcAVIGenerator, (Dz1DelFunc)ItsIcAVIMsg_del, (Dz1DumpFunc)ItsIcAVIMsg_dump,
			ItsIcAVIMsg_encode, ItsIcAVIMsg_decode },

	{ "CCTV", "TEST_CLIENT", "TEST_SERVER", "192.168.0.121", 7355, "testuser", "testpass",
			ItsIcCCTVGenerator, (Dz1DelFunc)ItsIcCCTVMsg_del, (Dz1DumpFunc)ItsIcCCTVMsg_dump,
			ItsIcCCTVMsg_encode, ItsIcCCTVMsg_decode },

	{ "VDS", "TEST_CLIENT", "TEST_SERVER", "192.168.0.99", 7355, "testuser", "testpass",
			ItsIcVDSGenerator, (Dz1DelFunc)ItsIcVDSMsg_del, (Dz1DumpFunc)ItsIcVDSMsg_dump,
			ItsIcVDSMsg_encode, ItsIcVDSMsg_decode },
*/
	{ NULL }
};

static ClientModeMap *ClientModeMap_find(str_t name)
{
	ClientModeMap *i;
	for (i = clientModeMap; i->modeName != NULL; i++)
		if (strcmp(name, i->modeName) == 0) return i;
	return NULL;
}

static ClientModeMap *selectedClient = NULL;

static void _publication(void *param, Dz1Asn1UTF8Str *domain, Dz1Asn1UTF8Str *peer, Dz1Asn1OctetStr *user, u32_t subscriptionID, u32_t pubSerial, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	void *dst = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Thread_printf("<<< Publication(%u:%u) = %s\n", subscriptionID, pubSerial, oidStr);
	Dz1Thread_tprintb(1, encodedEAM, encodedEAMSize, 16, FALSE);

	if (selectedClient && selectedClient->dec && selectedClient->dec(oidStr, (void **)&dst, encodedEAM, encodedEAMSize, Dz1Asn1Codec_ber, &err) < 0) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(selectedClient->del, (void *)dst);
		Dz1Thread_printf("Decoded = "); selectedClient->dump(dst, 0);
		pthread_cleanup_pop(1); // (selectedClient->del, (void *)dst);
	}
}

static void _cmdClientCreateUsage(str_t n) { Dz1Thread_printf("Usage] %s create <mode>\n", n); }
static void _cmdClientCreate(void *task, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc != 2) _cmdClientCreateUsage(n);
	else if (selectedClient != NULL) ERR_SET_OUT(&err, EEXIST);
	else if ((selectedClient = ClientModeMap_find(argv[1])) == NULL) ERR_SET_OUT(&err, ENOSYS);
	else
	{
		ItsIso14827ClientDomainCallback cbs = 
		{
			_initiated,
			_terminated,
			_publication,
			_pubControl,
			_disconnected
		};
		if ((myDomain= Dz1Asn1UTF8Str_newFromStr(selectedClient->myDomainStr, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&myDomain);

			if ((err = ItsIso14827_createClient(task, myDomain, &cbs)).code) ERR_OUT(&err);

			pthread_cleanup_pop(err.code); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&name);
		}
	}
}

static void _cmdClientConnectUsage(str_t n) { Dz1Thread_printf("Usage] %s [<ip> [<port>]]\n", n); }
static void _cmdClientConnect(void *task, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	TCHAR cmd[64];
	Dz1SNPRINTF(cmd, 63, Dz1Text("%s connect"), n);
	if (argc > 3) _cmdClientConnectUsage(cmd);
	else
	{
		if (selectedClient == NULL) ERR_SET_OUT(&err, ENOSYS);
		else if (myDomain == NULL) ERR_SET_OUT(&err, ENOSYS);
		else if (peerDomain != NULL) ERR_SET_OUT(&err, EEXIST);
		else
		{
			Dz1SockAddr addr;
			Dz1Asn1Codec codec_in_out = Dz1Asn1Codec_ber;
			str_t ipStr = selectedClient->ipStr;
			u16_t port = selectedClient->port;
			Iso14827RejectLogin reject = Iso14827RejectLogin_accessDenied;

			pthread_cleanup_push(names_delAndSetNull, NULL);

			if (argc >= 2) ipStr = argv[1];
			if (argc >= 3) port = (u16_t)atoi(argv[2]);

			if ((err = Dz1SockAddr_setAddrStr(&addr, ipStr)).code) ERR_OUT(&err);
			else if ((err = Dz1SockAddr_setPort(&addr, port)).code) ERR_OUT(&err);
			else if ((peerDomain = Dz1Asn1UTF8Str_newFromStr(selectedClient->peerDomainStr, &err)) == NULL) ERR_OUT(&err);
			else if ((user = Dz1Asn1OctetStr_new((u8_t *)selectedClient->userStr, (u32_t)strlen(selectedClient->userStr), &err)) == NULL) ERR_OUT(&err);
			else if ((pass = Dz1Asn1OctetStr_new((u8_t *)selectedClient->passStr, (u32_t)strlen(selectedClient->passStr), &err)) == NULL) ERR_OUT(&err);
			else if ((err = ItsIso14827_connectToServer(task, &addr, myDomain, peerDomain,
														NULL, user, pass, DZ1_ASN1_CODEC_BIT_BER,
														40, 10, 4096, &codec_in_out, ItsIso14827CRCCheck_warning, &reject)).code) ERR_OUT(&err);
			pthread_cleanup_pop(err.code); // (names_delAndSetNull, NULL);
		}
	}
}

static void _cmdClientDisonnect(void *task, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (myDomain == NULL) ERR_SET_OUT(&err, ENOSYS);
	else if (peerDomain == NULL) ERR_SET_OUT(&err, ENOSYS);
	else if ((err = ItsIso14827_disconnectFromServer(task, myDomain, peerDomain, user, Iso14827Logout_clientRequested)).code) ERR_OUT(&err);

	names_delAndSetNull(NULL);
	Dz1Asn1UTF8Str_delAndSetNull(&myDomain);
	selectedClient = NULL;
}

static void _cmdClientSingleUsage(str_t n) { Dz1Thread_printf("Usage] %s single <msgNum>\n", n); }
static void _cmdClientSingle(void *task, str_t n, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (argc < 2) _cmdClientSingleUsage(n);
	else
	{
		int num = atoi(argv[1]);
		void *msg = NULL;
		MsgGenerator *api = MsgGenerator_find(num, selectedClient->genTable);
		if (api == NULL) ERR_SET_OUT(&err, ENOSYS);
		else if ((msg = api->gen(&err)) == NULL) ERR_OUT(&err);
		else
		{
			u8_t *buf = NULL;
			str_t oidStr = NULL;
			ssize_t size = 0;
			pthread_cleanup_push(api->delAndSetNull, (void *)&msg);
			if ((size = selectedClient->enc(msg, &buf, Dz1Asn1Codec_ber, &oidStr, &err)) < 0) ERR_OUT(&err);
			else
			{
				u32_t subID = 0;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
				if ((err = ItsIso14827_singleRequest(task, ItsIso14827DomainType_client, myDomain, peerDomain, user, 1, FALSE, oidStr, buf, size, &subID)).code) ERR_OUT(&err);
				else Dz1Thread_printf("Subscription ID = %u\n", subID);
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
			}
			pthread_cleanup_pop(1); // (api->delAndSetNull, (void *)&msg);
		}
	}
}

static void _cmdclientUsage(str_t n) { Dz1Thread_printf("Usage] %s create <param...>\n", n); }
static Dz1ShellCmdReturn _cmdClient(void *task, int argc, char *argv[])
{
	Dz1ShellCmdReturn ret = Dz1ShellCmdReturn_ok;

	if (argc < 2) _cmdclientUsage(argv[0]);
	else if (strcmp(argv[1], "create") == 0 || strcmp(argv[1], "!") == 0) _cmdClientCreate(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "connect") == 0 || strcmp(argv[1], "c") == 0) _cmdClientConnect(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "disconnect") == 0 || strcmp(argv[1], "x") == 0) _cmdClientDisonnect(task, argv[0], argc-1, &argv[1]);
	else if (strcmp(argv[1], "single") == 0 || strcmp(argv[1], "s") == 0) _cmdClientSingle(task, argv[0], argc-1, &argv[1]);
	return ret;
}

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "ItsIso14827", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "ItsIso14827", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		else if ((err = Dz1Shell_cmdReg(sh, "domain", _cmdDomain, task, "Domain Management")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "session", _cmdSession, task, "Session Management")).code) ERR_OUT(&err);
		else if ((err = Dz1Shell_cmdReg(sh, "client", _cmdClient, task, "Create Client")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	void *task = NULL;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("ItsIso14827Test.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif
	// Edit Task Argument
	if ((task = ItsIso14827_new(_task_exception_handler, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&task);
		if ((err = Dz1Task_start(task, DZ1_THREAD_LOG_BASIS | DZ1_THREAD_LOG_TASK_DEBUG)).code) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Task_startCancel, (void *)task);

			_shell_start(task);

			pthread_cleanup_pop(1); // (Dz1Task_startCancel, (void *)task);
		}
		pthread_cleanup_pop(1); // (Dz1Task_delAndSetNull, (void *)&task);
	}
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return err.code;
}
