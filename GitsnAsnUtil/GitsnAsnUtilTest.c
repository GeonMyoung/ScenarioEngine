#include <dz1_cleanup.h>
#include <dz1_thread_log.h>
#include <dz1_shell.h>
#include <dz1_str.h>
#include <dz1_socket.h>
// #include <GitsnAsnUtil.h>
#include <dz1_asn1.h>
#include <GitsnAsnUtilSampleMsg.h>
#include <GitsnAsnUtilDefJson.h>



#ifndef UNIX_SYSTEM
#include <TCHAR.h>
#endif // UNIX_SYSTEM

static FILE* logfp = NULL;
static void _outputHook(void* ptr, unsigned char* data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void* ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }


TravelerInformation* sample_tim;
SPAT* sample_spat;
TLS* sample_tls;
TrafficLightStatusMessage* sample_tlsm;


////////////////////////////////////////////////////////////////////////////////
// cmd_json Root Command

static Dz1Asn1UTF8Str* _get_stringify_u8(Dz1JsonSpec* spec, Dz1Str struct_name, void* struct_ptr, Dz1Error* errp)
{
	Dz1Asn1UTF8Str* ret = NULL;
	Dz1Json* json = NULL;
	if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, spec, struct_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
		Dz1Str src = NULL;
		if (Dz1Json_stringify(json, struct_name, struct_ptr, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
		else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("STRINGIFIED = \n");
			Dz1Str_dump(src, 0);
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
			if ((ret = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
	}
	return ret;
}

static void cmd_enc_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_enc(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_enc_usage;
	Dz1Str n = argv[0];
	if (argc != 1) _print_usage(n);
	else
	{
		if (GitsnAsnUtil_initSample(errp) == FALSE) ERR_OUT(errp);
		else
		{


			Dz1Binary* e = TravelerInformation_get_uper_encoded(sample_tim, errp);
			if (e != NULL)
			{
				Dz1Binary_dump(e, 0);

				ASN1WorkSpace ws;

				ASN1_INIT_WS_INFO(&ws);
				pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
				TravelerInformation dec;
				memset(&dec, 0, sizeof(TravelerInformation));
				TravelerInformation_uper_decode(&ws, e, &dec, errp);
				ASN1_Print_TravelerInformation(&dec, 0);

				Gitsn_TravelerInformation deser;
				memset(&deser, 0, sizeof(Gitsn_TravelerInformation));
				if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(&dec, &deser, errp) == FALSE) ERR_OUT(errp);
				else
				{
					Gitsn_TravelerInformation_dump(&deser, 0);
					Dz1Asn1UTF8Str* str_u8 = NULL;
					Dz1JsonSpec* spec = GitsnAsnUtilDef_genJsonSpec(errp);
					if ((str_u8 = _get_stringify_u8(spec, Dz1T("Gitsn_TravelerInformation"), &deser, errp)) == NULL) ERR_OUT(errp);
					else
					{
						Dz1Asn1UTF8Str_dump(str_u8, 0);
					}
					;
				}

				pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			}
		}
	}
	return Dz1ShellCmdReturn_ok;
}


static bool_t init_MessageFrame(MessageFrame* dst, int msg_id, Dz1Binary* value, Dz1Error* errp)
{

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	memset(dst, 0, sizeof(MessageFrame));
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	if (0) {}
	else if (ASN1_SET_MessageFrame_messageId(&ws, dst, msg_id) < 0) ERR_OUT(errp);
	else if (ASN1_SET_MessageFrame_value(&ws, dst, value->data, value->size) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(errp->code); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	return ERR_IS_SUCCESS(errp);
}

static Dz1Binary* _uper_enc_messageframe(int msg_id, Dz1Binary* value, Dz1Error* errp)
{
	Dz1Binary* ret = NULL;

	if (value == NULL) ERR_OUT(errp);
	else
	{
		MessageFrame msg_frame;
		if (init_MessageFrame(&msg_frame, msg_id, value, errp) == FALSE) ERR_OUT(errp);
		else
		{
			ASN1_Print_MessageFrame(&msg_frame, 0);
			ASN1WorkSpace ws;
			ASN1_INIT_WS_INFO(&ws);
			pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			if (ASN1_PER_UNAlign_Enc_MessageFrame(&ws, &msg_frame) < 0) ERR_SET_OUT(errp, EFAULT);
			else
			{
				if (errp->code == 0)
				{
					if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, Dz1Asn1Codec_uper), errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1);
		}
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
// cmd_mf Root Command
static void cmd_mf_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_mf(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_mf_usage;
	Dz1Str n = argv[0];
	if (argc != 1) _print_usage(n);
	else
	{
		Dz1Binary* encoded_src = NULL;
		Dz1Binary* encoded_mf = NULL;

		if ((encoded_src = TrafficLightStatusMessage_get_uper_encoded(sample_tlsm, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&encoded_src);
			if ((encoded_mf = _uper_enc_messageframe(50, encoded_src, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Binary_dump(encoded_src, 0);
				Dz1Binary_dump(encoded_mf, 0);
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&encoded_mf);
				FILE* fp_tlsm = fopen("sample_mf_tlsm", "w");
				size_t sz_tlsm = encoded_mf->size;
				fwrite(encoded_mf, 1, sz_tlsm, fp_tlsm);

				// decoded
				ASN1WorkSpace ws;
				ASN1_INIT_WS_INFO(&ws);
				pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
				TrafficLightStatusMessage decoded;
				memset(&decoded, 0, sizeof(TrafficLightStatusMessage));
				if (TrafficLightStatusMessage_uper_decode(&ws, encoded_src, &decoded, errp) == FALSE) ERR_OUT(errp);
				else
				{
					ASN1_Print_TrafficLightStatusMessage(&decoded, 0);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
				// decoded
				fclose(fp_tlsm);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&encoded_mf);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&encoded_src);
		}
	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_mf Root Command
////////////////////////////////////////////////////////////////////////////////

static void cmd_json_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_json(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_json_usage;
	Dz1Str n = argv[0];
	if (argc != 1) _print_usage(n);
	else
	{
		Dz1JsonSpec* spec = NULL;

		if ((spec = GitsnAsnUtilDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{

			pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void*)&spec);

			if (GitsnAsnUtil_initSample(errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf("SAMPLE TIM = \n");
				Gitsn_TravelerInformation* tim = NULL;
				if ((tim = Gitsn_TravelerInformation_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Gitsn_TravelerInformation_delAndSetNull, (void*)&tim);
					if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(sample_tim, tim, errp) == FALSE) ERR_OUT(errp);
					else
					{
						Dz1Thread_printf("CONVERT TIM = \n");
						Gitsn_TravelerInformation_dump(tim, 0);

						Dz1Asn1UTF8Str* str_u8 = NULL;
						if ((str_u8 = _get_stringify_u8(spec, Dz1T("Gitsn_TravelerInformation"), tim, errp)) == NULL) ERR_OUT(errp);
						else
						{
							pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
							Dz1Thread_printf("STR_U8 = \n");
							Dz1Asn1UTF8Str_dump(str_u8, 0);
							pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
						}
					}
					pthread_cleanup_pop(1); //(Gitsn_TravelerInformation_delAndSetNull, (void*)&tim);
				}
			}

			pthread_cleanup_pop(1); // (Dz1JsonSpec_delAndSetNull, (void*)&spec);
		}

	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_json Root Command
////////////////////////////////////////////////////////////////////////////////



static void cmd_sample_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_sample(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_sample_usage;
	Dz1Str n = argv[0];
	if (argc != 1) _print_usage(n);
	else
	{
		Dz1JsonSpec* spec = NULL;

		if ((spec = GitsnAsnUtilDef_genJsonSpec(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void*)&spec);


			u8_t sample_spat[] = {
				0x63, 0xD0, 0xF5, 0x0E, 0x0C, 0x28, 0x71, 0x00,
				0xF8, 0x38, 0x30, 0xA1, 0xC4, 0x80, 0x02, 0x80,
				0x32, 0x00, 0xC1, 0x90, 0x3D, 0x0F, 0x50, 0x00,
				0x00, 0x00, 0x00, 0x06, 0x0E, 0x0C, 0x28, 0x71,
				0x01, 0x01, 0x87, 0xE6, 0x07, 0x26, 0x07, 0x26,
				0x07, 0x26, 0x07, 0x20, 0x60, 0x72, 0x0F, 0x04,
				0x15, 0x00, 0x78, 0x00, 0x1E, 0x0F, 0x00, 0x78,
				0x01, 0xE8, 0x1E, 0x0F, 0x00, 0x78, 0x01, 0xE8
			};
			Dz1Binary b_sample_spat = { sample_spat, 64 };

			u8_t gitsn_spat[] = {
				0x63, 0xE5, 0xA6, 0x93, 0x0E, 0x0C, 0x28, 0x71,
0x00, 0x3F, 0x38, 0x30, 0xE2, 0x88, 0x9E, 0x3F,
0x02, 0x3F, 0x32, 0x00, 0x3F, 0x3F, 0x3D, 0x0F,
0x50, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0E, 0x6B,
0x8B, 0x23, 0xF1, 0x01, 0x01, 0x87, 0xE6, 0x07,
0x26, 0x07, 0x26, 0x07, 0x26, 0x07, 0x20, 0x3F,
0x41, 0x50, 0x07, 0x3F, 0x01, 0xE7, 0x87, 0xAE,
0x07, 0x3F, 0x1E, 0x3F, 0xE7, 0x87 };
			Dz1Binary b_gitsn_spat = { gitsn_spat, 62 };

			int msg_id = 0;
			//Dz1Binary* src = GitsnAsnUtil_getValueFromMessageFrame(&b_sample_spat, &msg_id, errp);



			ASN1WorkSpace ws;
			ASN1_INIT_WS_INFO(&ws);
			pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
			SPAT asn;
			memset(&asn, 0, sizeof(SPAT));

			SPAT_uper_decode(&ws, &b_gitsn_spat, &asn, errp);
			ASN1_Print_SPAT(&asn, 0);

			pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);


		}
	}

		//	Dz1Thread_printf("SAMPLE TIM = \n");
		//	Gitsn_TravelerInformation* tim = NULL;
		//	if ((tim = Gitsn_TravelerInformation_gen(errp)) == NULL) ERR_OUT(errp);
		//	else
		//	{
		//		pthread_cleanup_push(Gitsn_TravelerInformation_delAndSetNull, (void*)&tim);
		//		if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(sample_tim, tim, errp) == FALSE) ERR_OUT(errp);
		//		else
		//		{
		//			Dz1Thread_printf("CONVERT TIM = \n");
		//			Gitsn_TravelerInformation_dump(tim, 0);

		//			Dz1Asn1UTF8Str* str_u8 = NULL;
		//			if ((str_u8 = _get_stringify_u8(spec, Dz1T("Gitsn_TravelerInformation"), tim, errp)) == NULL) ERR_OUT(errp);
		//			else
		//			{
		//				pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		//				Dz1Thread_printf("STR_U8 = \n");
		//				Dz1Asn1UTF8Str_dump(str_u8, 0);
		//				pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
		//			}
		//		}
		//		pthread_cleanup_pop(1); //(Gitsn_TravelerInformation_delAndSetNull, (void*)&tim);
		//	}
		//	pthread_cleanup_pop(1); // (Dz1JsonSpec_delAndSetNull, (void*)&spec);
		//}

	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_sample Root Command
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// cmd_inic Root Command
static void cmd_init_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s .\n"), n); }
static Dz1ShellCmdReturn cmd_init(void* ptr, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	void (*_print_usage)(Dz1Str n) = cmd_init_usage;
	Dz1Str n = argv[0];
	if (argc != 1) _print_usage(n);
	else
	{
		if (GitsnAsnUtil_initSample(errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
		}

	}
	return Dz1ShellCmdReturn_ok;
}
// cmd_inic Root Command
////////////////////////////////////////////////////////////////////////////////

static void _shell_start(void* task)
{
	void* sh = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

#ifndef UNIX_SYSTEM
	if ((sh = Dz1Shell_new(Dz1Text("win32crt"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("GitsnAsnUtil"), errp)) == NULL) ERR_OUT(errp);
#else
	if ((sh = Dz1Shell_new(Dz1Text("xterm"), DZ1_SHELL_CMD_ALL, 16, Dz1Text("root"), Dz1Text("GitsnAsnUtil"), errp)) == NULL) ERR_OUT(errp);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void*)sh);
		if (0) {}
		//else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("command_name"), command_func, task, Dz1Text("command_description") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("json"), cmd_json, task, Dz1Text("json convert test"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("enc"), cmd_enc, task, Dz1Text("enc test"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("init"), cmd_init, task, Dz1Text("init test"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("mf"), cmd_mf, task, Dz1Text("mf test"))).code) ERR_OUT(errp);
		else if ((*errp = Dz1Shell_cmdReg(sh, Dz1Text("sample"), cmd_sample, task, Dz1Text("sample test"))).code) ERR_OUT(errp);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

#ifndef UNIX_SYSTEM
int _tmain(int argc, TCHAR* argv[])
#else // UNIX_SYSTEM
int main(int argc, char* argv[])
#endif // UNIC_SYSTEM
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = Dz1FileStream_open(Dz1Text("GitsnAsnUtilTest.log.txt"), Dz1Text("wb"), NULL)) != NULL)
	{
		fwrite(DZ1_SYSTEM_CHARSET_BOM, DZ1_SYSTEM_CHARSET_BOM_SZ, 1, logfp);
		Dz1OutputHook_set(_outputHook, NULL);
	}

	if (Dz1Socket_init() == FALSE) { Dz1Thread_log(DZ1_THREAD_LOG_CRITICAL, "Win sock Initialize Fail\n"); return EFAULT; }
	else _shell_start(NULL);

	Dz1Socket_cleanup();

#ifdef _DEBUG
#ifdef UNICODE
	wprintf(L"Press Any Key...\n");
#else
	printf("Press Any Key...\n");
#endif // UNICODE
	Dz1Thread_getch(-1, NULL);
#endif // _DEBUG
	return errp->code;
}
