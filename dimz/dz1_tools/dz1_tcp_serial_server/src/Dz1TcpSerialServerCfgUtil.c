#include <dz1_str.h>
#include <Dz1ParserUtil.h>

#include "Dz1TcpSerialServerCfgUtil.h"

/*
	serial emulation listen addr = {
		interface = 192.168.0.1;
		tcp port = 10900;
	}
	serial preset = {
		mapping = {
			serial = 1;
			listen addr = {
				interface = 192.168.0.1;
				tcp port = 10901;
			}
			bit per byte = 8;
			parity = none;				-- even, odd
			stop bit = one;				-- oneHalf, two
			soft flow control = off;	-- off
		}
		mapping = {
			serial = 7;
			listen addr = {
				interface = 0.0.0.0;
				tcp port = 10907;
			}
			bit per byte = 8;
			parity = none;				-- even, odd
			stop bit = one;				-- oneHalf, two
			soft flow control = off;	-- off
		}
	}
*/
static str_t syntax = ""
"TcpSerialEmulationSyntax =		serial emulation <TcpListenAddr4Syntax>=_set_emulator_listen;\n"
"\n"
"TcpSerialPresetListSyntax =	serial preset <equal> <liststart>\n"
"									[<TcpPresetEntrySyntax>=_append_preset_to_list]+\n"
"								<listend>;\n"
"\n"
"TcpPresetEntrySyntax =			mapping <equal>=_new_temp_preset <liststart>\n"
"									serial <equal> <number>=_set_serial_port <semicolon>\n"
"									<TcpListenAddr4Syntax>=_set_serial_listen\n"
"									baud <equal> <number>=_set_serial_baud <semicolon>\n"
"									bit per byte <equal> <number>=_set_serial_bpb <semicolon>\n"
"									parity <equal> <symbol>=_set_serial_parity <semicolon>\n"
"									stop bit <equal> <symbol>=_set_serial_stop <semicolon>\n"
"									soft flow control <equal> <symbol>=_set_serial_flow <semicolon>\n"
"								<listend>;\n"
"\n"
"TcpSerialConfigSyntax = <TcpSerialEmulationSyntax> <TcpSerialPresetListSyntax>;\n"
"";

static Dz1Error Dz1TcpSerialServerPreset_save(Dz1TcpSerialServerPreset *src, FILE *fp, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1Thread_ftprintf(fp, tab++, "mapping = {\n");
	Dz1Thread_ftprintf(fp, tab, "serial = %u;\n", src->serialPort);
	Dz1Thread_ftprintf(fp, tab, ""); Dz1ParserUtilTcpListenAddr4_save(src->presetListen, fp, tab);
	Dz1Thread_ftprintf(fp, tab, "bit per byte = %u;\n", src->bitPerByte);
	Dz1Thread_ftprintf(fp, tab, "parity = %s; -- none | even | odd\n", Dz1SerialParityStr(src->serialParity));
	Dz1Thread_ftprintf(fp, tab, "stop bit = %s; -- one | oneHalf | two\n", Dz1SerialStopBitStr(src->serialStopBit));
	Dz1Thread_ftprintf(fp, tab, "soft flow control = %s; -- on | off\n", Dz1SerialXONXOFFStr(src->serialFlowCtrlXonXoff));
	Dz1Thread_ftprintf(fp, --tab, "}\n");
	return err;
}

static Dz1Error _Dz1TcpSerialServerPresetList_save(void *ptr, Dz1TcpSerialServerPreset *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1ListSaveArg *arg = (Dz1ListSaveArg *)ptr;
	if ((*errp = Dz1TcpSerialServerPreset_save(p, arg->fp, arg->tab)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error Dz1TcpSerialServerPresetList_save(Dz1TcpSerialServerPresetList *list, FILE *fp, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1ListSaveArg arg = { fp, tab };
	if ((*errp = list->travel(list, _Dz1TcpSerialServerPresetList_save, &arg)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1TcpSerialServerConfig_save(Dz1TcpSerialServerConfig *cfg, FILE *fp, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1Thread_ftprintf(fp, tab, "serial emulation "); Dz1ParserUtilTcpListenAddr4_save(cfg->emulater, fp, tab);
	Dz1Thread_ftprintf(fp, tab++, "serial preset = {\n");
	Dz1TcpSerialServerPresetList_save(cfg->presets, fp, tab);
	Dz1Thread_ftprintf(fp, --tab, "}\n");
	return err;
}



Dz1Error _set_emulator_listen(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	Dz1ParserUtilEnvEntry *listen4node = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerConfig *dst = env->dst;

		Dz1ParserTcpListenAddrEnv *listen4env = (Dz1ParserTcpListenAddrEnv *)listen4node->env;
		if ((dst->emulater = Dz1SockAddr_clone(&listen4env->addr, errp)) == NULL) ERR_OUT(errp);
	}
	return err;
}



Dz1Error _new_temp_preset(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset_delAndSetNull(&env->preset);
		if ((env->preset = Dz1TcpSerialServerPreset_new(0, NULL, 0, 0, -1, -1, -1, errp)) == NULL) ERR_OUT(errp);
	}
	return err;
}


Dz1Error _set_serial_port(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		if (preset == NULL) ERR_SET_OUT(errp, EFAULT);
		else preset->serialPort = (u32_t)atoi(t->v);
	}
	return err;
}


Dz1Error _set_serial_listen(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	Dz1ParserUtilEnvEntry *addrnode = Dz1ParserUtilEnvEntry_find(table, DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR);
	if (node == NULL || addrnode == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1ParserTcpListenAddrEnv *addrenv = (Dz1ParserTcpListenAddrEnv *)addrnode->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		if ((preset->presetListen = Dz1SockAddr_clone(&addrenv->addr, errp)) == NULL) ERR_OUT(errp);
	}
	return err;
}

Dz1Error _set_serial_baud(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		u32_t v = (u32_t)atoi(t->v);
		preset->serialBaud = v;
	}
	return err;
}


Dz1Error _set_serial_bpb(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		u32_t v = (u32_t)atoi(t->v);
		if (v != 7 && v != 8) ERR_SET_OUT(errp, EINVAL);
		else preset->bitPerByte = v;
	}
	return err;
}


Dz1Error _set_serial_parity(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		Dz1SerialParity v = Dz1SerialParityFromStr(t->v);
		if (v == -1) ERR_SET_OUT(errp, EINVAL);
		else preset->serialParity = v;
	}
	return err;
}


Dz1Error _set_serial_stop(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		Dz1SerialStopBit v = Dz1SerialStopBitFromStr(t->v);
		if (v == -1) ERR_SET_OUT(errp, EINVAL);
		else preset->serialStopBit = v;
	}
	return err;
}


Dz1Error _set_serial_flow(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerPreset *preset = env->preset;
		Dz1SerialXONXOFF v = Dz1SerialXONXOFFFromStr(t->v);
		if (v == -1) ERR_SET_OUT(errp, EINVAL);
		else preset->serialFlowCtrlXonXoff = v;
	}
	return err;
}



Dz1Error _append_preset_to_list(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, DZ1_TCP_SERIAL_SERVER_CFG_ENV);
	if (node == NULL ) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TcpSerialServerCfgParserEnv *env = (Dz1TcpSerialServerCfgParserEnv *)node->env;
		Dz1TcpSerialServerConfig *dst = env->dst;
		Dz1TcpSerialServerPresetList *presets = dst->presets;
		pthread_cleanup_push(Dz1TcpSerialServerPreset_delAndSetNull, (void *)&env->preset);
		if ((*errp = presets->add(presets, env->preset)).code) ERR_OUT(errp);
		else
		{
			env->preset = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerPreset_delAndSetNull, (void *)&env->preset);
	}
	return err;
}

static Dz1ParserUtilEmitterInfo emitter[] =
{
	Dz1ParserEmitterInfoEntry(_set_emulator_listen),

	Dz1ParserEmitterInfoEntry(_new_temp_preset),
	Dz1ParserEmitterInfoEntry(_set_serial_port),
	Dz1ParserEmitterInfoEntry(_set_serial_listen),
	Dz1ParserEmitterInfoEntry(_set_serial_bpb),
	Dz1ParserEmitterInfoEntry(_set_serial_baud),
	Dz1ParserEmitterInfoEntry(_set_serial_parity),
	Dz1ParserEmitterInfoEntry(_set_serial_stop),
	Dz1ParserEmitterInfoEntry(_set_serial_flow),

	Dz1ParserEmitterInfoEntry(_append_preset_to_list),
	Dz1ParserEmitterInfoEndOfEntry
};

Dz1Error Dz1TcpSerialServerCfgParser_initEmitter(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserUtil_addEmitter(parser, emitter)).code) ERR_OUT(errp);
	return err;
}

Dz1Error Dz1TcpSerialServerCfgParser_initSyntax(void *parser)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = Dz1ParserInit_parse(parser, syntax)).code) ERR_OUT(errp);
	return err;
}

Dz1TcpSerialServerConfig *_Dz1TcpSerialServerConfig_parse(str_t text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialServerConfig *ret = Dz1TcpSerialServerConfig_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		void *parser = NULL;
		pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
		if ((parser = Dz1Parser_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);
			if		((*errp = Dz1ParserUtilIPv4_emitterInit(parser)).code) ERR_OUT(errp);
			else if ((*errp = Dz1ParserUtilTcpListenAddr4_emitterInit(parser)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpSerialServerCfgParser_initEmitter(parser)).code) ERR_OUT(errp);

			else if	((*errp = Dz1ParserUtilIPv4_syntaxInit(parser)).code) ERR_OUT(errp);
			else if ((*errp = Dz1ParserUtilTcpListenAddr4_syntaxInit(parser)).code) ERR_OUT(errp);
			else if ((*errp = Dz1TcpSerialServerCfgParser_initSyntax(parser)).code) ERR_OUT(errp);
			else
			{
				Dz1ParserIPv4Env				 ipv4env;
				Dz1ParserTcpListenAddrEnv		 listen4env;
				Dz1TcpSerialServerCfgParserEnv	 tcp4serial = Dz1TcpSerialServerCfgParserEnvInitializer(ret);
				Dz1ParserUtilEnvEntry table[] =
				{
					{ DZ1_PARSER_UTIL_PARSER_IPv4, &ipv4env },
					{ DZ1_PARSER_UTIL_PARSER_TCP_LISTEN_ADDR, &listen4env },
					{ DZ1_TCP_SERIAL_SERVER_CFG_ENV, &tcp4serial },
					Dz1ParserEnvEntryLast
				};
				
				if ((*errp = Dz1Parser_prepare(parser, text)).code) ERR_OUT(errp);
				else if ((*errp = Dz1Parser_process(parser, "TcpSerialConfigSyntax", &table, 0)).code)
				{
					Dz1Thread_printf("!!! %s : Line %d\n", "Dz1TcpSerialServerConfig Parser", Dz1Parser_getLineNum(parser));
					Dz1Parser_dump(parser, 0);
					ERR_OUT(errp);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Parser_delAndSetNull, (void *)&parser);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1TcpSerialServerConfig *_Dz1TcpSerialServerConfigFile_load(str_t path, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialServerConfig *ret = NULL;

	str_t text = NULL;
	char fn[4096];
	if ((*errp = Dz1FileName_mkFullName(fn, path, name)).code) ERR_OUT(errp);
	else if ((text = Dz1TextFile_load(fn, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
		if ((ret = _Dz1TcpSerialServerConfig_parse(text, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
	}
	return ret;
}

static Dz1Error Dz1TcpSerialServerConfig_addNode(Dz1TcpSerialServerPresetList *dst, u32_t serialPort, u16_t tcpPort)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1TcpSerialServerPreset *node = Dz1TcpSerialServerPreset_new(serialPort, NULL, 115200, 8, Dz1SerialParity_none, Dz1SerialStopBit_one, Dz1SerialXONXOFF_off, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr temp;
		pthread_cleanup_push(Dz1TcpSerialServerPreset_delAndSetNull, (void *)&node);
		if ((*errp = Dz1SockAddr_setAddrStr(&temp, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&temp, tcpPort)).code) ERR_OUT(errp);
		else if ((node->presetListen = Dz1SockAddr_clone(&temp, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TcpSerialServerPreset_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_default(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1TcpSerialServerConfig *ret = Dz1TcpSerialServerConfig_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr temp;
		pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1SockAddr_setAddrStr(&temp, "0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&temp, 10900)).code) ERR_OUT(errp);
		else if ((ret->emulater = Dz1SockAddr_clone(&temp, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialServerConfig_addNode(ret->presets, 1, 10901)).code) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialServerConfig_addNode(ret->presets, 2, 10902)).code) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialServerConfig_addNode(ret->presets, 3, 10903)).code) ERR_OUT(errp);
		else if ((*errp = Dz1TcpSerialServerConfig_addNode(ret->presets, 4, 10904)).code) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
	}
	return ret;
}


Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfigFile_load(str_t path, str_t name, Dz1Error *err)
{
	Dz1TcpSerialServerConfig *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if ((ret = _Dz1TcpSerialServerConfigFile_load(path, name, errp)) == NULL)
	{
		if ((ret = Dz1TcpSerialServerConfig_default(errp)) == NULL) ERR_OUT(errp);
		else Dz1TcpSerialServerConfigFile_save(ret, path, name);
	}

	if (ret != NULL)
	{
		Dz1Thread_printf("Dz1TcpSerialServerConfig Load Result = "); Dz1TcpSerialServerConfig_dump(ret, 0);
	}
	return ret;
}

Dz1Error Dz1TcpSerialServerConfigFile_save(Dz1TcpSerialServerConfig *p, str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp= &err;

	FILE *fp = NULL;
	char fn[4096];
	if ((*errp = Dz1FileName_mkFullName(fn, path, name)).code) ERR_OUT(errp);
	else if ((fp = fopen(fn, "wb")) == NULL) ERR_OUT(errp);
	else
	{
		int tab = 0;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		Dz1TcpSerialServerConfig_save(p, fp, tab);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

