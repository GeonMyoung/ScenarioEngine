#ifndef DZ1_TCP_SERIAL_SERVER_CFG_UTIL_H
#define DZ1_TCP_SERIAL_SERVER_CFG_UTIL_H

#include <Dz1TcpSerialServerDef.h>

#define DZ1_TCP_SERIAL_SERVER_CFG_ENV		0x10000001
#define Dz1TcpSerialServerCfgParserEnvInitializer(cfgp)			{ (cfgp), NULL }
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerCfgParser_initEmitter(void *parser);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerCfgParser_initSyntax(void *parser);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerConfig_save(Dz1TcpSerialServerConfig *cfg, FILE *fp, int tab);

DZ1_CPPLINK Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfigFile_load(str_t path, str_t name, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1TcpSerialServerConfigFile_save(Dz1TcpSerialServerConfig *p, str_t path, str_t name);
#endif