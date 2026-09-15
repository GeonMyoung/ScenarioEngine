#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
#include "dz1_asn1_codecTest.h"

#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#ifdef _DEBUG
#include <conio.h>
#endif // _DEBUG
#endif // UNIX_SYSTEM

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

////////////////////////////////////////////////////////////////////////////////
// cmd_verbose Root Command
static void cmd_verbose_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <on | off>\n"), n); }
static Dz1ShellCmdReturn cmd_verbose(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2)
	{
		cmd_verbose_usage(argv[0]);
		Dz1Thread_printf(Dz1T("@@@ Verbose = %s\n"), flag_verbose ? Dz1T("ON") : Dz1T("OFF"));
	}
	else
	{
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("on")) == 0 || Dz1STRCMP(argv[1], Dz1Text("1")) == 0)
		{
			flag_verbose = TRUE;
			Dz1Thread_printf(Dz1T("@@@ Verbose = %s\n"), flag_verbose ? Dz1T("ON") : Dz1T("OFF"));
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("off")) == 0 || Dz1STRCMP(argv[1], Dz1Text("0")) == 0)
		{
			flag_verbose = FALSE;
			Dz1Thread_printf(Dz1T("@@@ Verbose = %s\n"), flag_verbose ? Dz1T("ON") : Dz1T("OFF"));
		}
		else cmd_verbose_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_verbose Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_encoder Root Command
static void cmd_encoder_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <cer | der>\n"), n); }
static Dz1ShellCmdReturn cmd_encoder(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2)
	{
		cmd_encoder_usage(argv[0]);
		Dz1Thread_printf(Dz1T("@@@ Encoder = %s\n"), Dz1Asn1BerEncoderOptStr(test_enc_opt));
	}
	else
	{
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("cer")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0)
		{
			test_enc_opt = Dz1Asn1BerEncoderOpt_cer;
			Dz1Thread_printf(Dz1T("@@@ Encoder = %s\n"), Dz1Asn1BerEncoderOptStr(test_enc_opt));
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("der")) == 0 || Dz1STRCMP(argv[1], Dz1Text("d")) == 0)
		{
			test_enc_opt = Dz1Asn1BerEncoderOpt_der;
			Dz1Thread_printf(Dz1T("@@@ Encoder = %s\n"), Dz1Asn1BerEncoderOptStr(test_enc_opt));
		}
		else cmd_encoder_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_encoder Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_decoder_usage Root Command
static void cmd_decoder_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <chunk | stream>\n"), n); }
static Dz1ShellCmdReturn cmd_decoder(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2)
	{
		cmd_decoder_usage(argv[0]);
		Dz1Thread_printf(Dz1T("@@@ Decoder = %s\n"), test_dec_opt == Dz1Asn1DecoderMode_chunk ? Dz1T("chunk") : Dz1T("stream"));
	}
	else
	{
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("chunk")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0)
		{
			test_dec_opt = Dz1Asn1DecoderMode_chunk;
			Dz1Thread_printf(Dz1T("@@@ Decoder = %s\n"), test_dec_opt == Dz1Asn1DecoderMode_chunk ? Dz1T("chunk") : Dz1T("stream"));
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("stream")) == 0 || Dz1STRCMP(argv[1], Dz1Text("s")) == 0) 
		{
			test_dec_opt = Dz1Asn1DecoderMode_stream;
			Dz1Thread_printf(Dz1T("@@@ Decoder = %s\n"), test_dec_opt == Dz1Asn1DecoderMode_chunk ? Dz1T("chunk") : Dz1T("stream"));
		}
		else cmd_decoder_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_decoder_usage Root Command
////////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK_VAR u32_t dz1Asn1EncoderFragSize;
////////////////////////////////////////////////////////////////////////////////
// cmd_frag Root Command
static void cmd_frag_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <number>\n"), n); }
static Dz1ShellCmdReturn cmd_frag(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2) 
	{
		cmd_frag_usage(argv[0]);
		Dz1Thread_printf(Dz1T("@@@ Fragment size = %u\n"), dz1Asn1EncoderFragSize);
	}
	else
	{
		u32_t num = 0;
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("status")) == 0 || Dz1STRCMP(argv[1], Dz1Text("s")) == 0)
			Dz1Thread_printf(Dz1T("@@@ Fragment size = %u\n"), dz1Asn1EncoderFragSize);
		else if ((num = Dz1StrTo32(argv[1])) > 0)
		{
			dz1Asn1EncoderFragSize = num;
			Dz1Thread_printf(Dz1T("@@@ Fragment size = %u\n"), dz1Asn1EncoderFragSize);
		}
		else cmd_encoder_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_frag Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_ber_simple Root Command
static void cmd_ber_simple_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <numeric | binary | exclusive | string | unicode | time> <params...>\n"), n); }
static Dz1ShellCmdReturn cmd_ber_simple(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2) cmd_ber_simple_usage(argv[0]);
	else
	{
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("numeric")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("n")) == 0) cmd_ber_simple_numeric(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("binary")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("b")) == 0) cmd_ber_simple_binary(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("exclusive")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("e")) == 0) cmd_ber_simple_exclusive(ptr, argv[0], argc-1, &argv[1]);
 		else if (Dz1STRCMP(argv[1], Dz1Text("string")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("s")) == 0) cmd_ber_simple_string(ptr, argv[0], argc-1, &argv[1]);
 		else if (Dz1STRCMP(argv[1], Dz1Text("unicode")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("u")) == 0) cmd_ber_simple_unicode(ptr, argv[0], argc-1, &argv[1]);
 		else if (Dz1STRCMP(argv[1], Dz1Text("time")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("t")) == 0) cmd_ber_simple_time(ptr, argv[0], argc-1, &argv[1]);
// 		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_exp_construct(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_simple_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_ber_simple Root Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_ber_construct Root Command
static void cmd_ber_construct_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <external | instance | pdv | charstr>\n"), n); }
static Dz1ShellCmdReturn cmd_ber_construct(void *ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	if (argc < 2) cmd_ber_construct_usage(argv[0]);
	else
	{
		// Command Code Here
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("external")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("e")) == 0) cmd_exp_external_native(ptr, argv[0], argc-1, &argv[1]);		// 8
		else if (Dz1STRCMP(argv[1], Dz1Text("instance")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("i")) == 0) cmd_exp_external_instance(ptr, argv[0], argc-1, &argv[1]);	// 8
		else if (Dz1STRCMP(argv[1], Dz1Text("pdv")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_exp_pdv(ptr, argv[0], argc-1, &argv[1]);				// 11
		else if (Dz1STRCMP(argv[1], Dz1Text("charstr")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_exp_charstring(ptr, argv[0], argc-1, &argv[1]);		// 29
		else cmd_ber_construct_usage(argv[0]);
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_ber_simple Root Command
////////////////////////////////////////////////////////////////////////////////

static void _shell_start(void *task)
{	void *sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("dz1_asn1"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("dz1_asn1"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
//		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("imp"), cmd_ber_imp, task, Dz1Text("BER import test") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("t"), cmd_ber_simple, task, Dz1Text("BER simple type test") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("c"), cmd_ber_construct, task, Dz1Text("BER construct type test") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("verbose"), cmd_verbose, task, Dz1Text("Verbose flag control") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("enc"), cmd_encoder, task, Dz1Text("Encoder Option control") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("dec"), cmd_decoder, task, Dz1Text("Decoder Mode control") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("frag"), cmd_frag, task, Dz1Text("Fragment size control") )).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR *argv[])
#else // UNIX_SYSTEM
int main(int argc, char *argv[])
#endif // UNIC_SYSTEM
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t thid = 0, log_lv = 0;

	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("dz1_asn1_codecTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
#ifndef UNIX_SYSTEM
#ifdef UNICODE
		u8_t bom[] = 
		{
#if	DZ1_ENDIAN == DZ1_ENDIAN_BIG
			0xFE, 0xFF
#elif	DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
			0xFF, 0xFE
#endif	// DZ1_ENDIAN
		};
		fwrite(bom, sizeof(bom), 1, logfp);
#endif // UNICODE
#endif // UNIX_SYSTEM
		Dz1OutputHook_set(_outputHook, NULL);
	}

	thid = Dz1Thread_self();
	Dz1Thread_getLogLevel(thid, &log_lv);
	Dz1Thread_setLogLevel(thid, log_lv | DZ1_THREAD_LOG_MESSAGE | DZ1_THREAD_LOG_SEQUENCE | DZ1_THREAD_LOG_CHOICE | DZ1_THREAD_LOG_INDIRECT);
	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "Win sock Initialize Fail\n"); return EFAULT; }
	else
	{
		ASN1_Print_setfunc(Dz1Thread_printf);
		dz1Asn1EncoderFragSize = 4;
		_shell_start(NULL);
	}

	Dz1Socket_cleanup();

#ifndef UNIX_SYSTEM
#ifdef _DEBUG
#ifdef UNICODE
	wprintf(L"Press Any Key...\n");
#else
	printf("Press Any Key...\n");
#endif // UNICODE
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif // _DEBUG
#endif // UNIX_SYSTEM
	return errp->code;
}
