#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_DEF_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_SERVER_DEF_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_serial.h"


typedef void (*Dz1TcpSerialServerException)(void *exceptionArg, Dz1Error *reason);

typedef struct Dz1TcpSerialServerPreset
{
	u32_t             serialPort;
	Dz1SockAddr      *presetListen;
	u32_t             serialBaud;
	s32_t             bitPerByte;
	Dz1SerialParity   serialParity;
	Dz1SerialStopBit  serialStopBit;
	Dz1SerialXONXOFF  serialFlowCtrlXonXoff;
} Dz1TcpSerialServerPreset;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPreset *Dz1TcpSerialServerPreset_new(u32_t serialPort, 
																			   Dz1SockAddr *presetListen, 
																			   u32_t serialBaud, 
																			   s32_t bitPerByte, 
																			   Dz1SerialParity serialParity, 
																			   Dz1SerialStopBit serialStopBit, 
																			   Dz1SerialXONXOFF serialFlowCtrlXonXoff, Dz1Error *err);
static __inline__ Dz1TcpSerialServerPreset *Dz1TcpSerialServerPreset_gen(Dz1Error *err) { return Dz1TcpSerialServerPreset_new(0, NULL, 0, 0, Dz1SerialParity_max, Dz1SerialStopBit_max, Dz1SerialXONXOFF_max, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPreset *Dz1TcpSerialServerPreset_clone(Dz1TcpSerialServerPreset *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPreset_del(Dz1TcpSerialServerPreset *p);
static __inline__ void Dz1TcpSerialServerPreset_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerPreset **p = (Dz1TcpSerialServerPreset **)ptr;
	Dz1TcpSerialServerPreset_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPreset_dump(Dz1TcpSerialServerPreset *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialServerPreset_cmp(Dz1TcpSerialServerPreset *a, Dz1TcpSerialServerPreset *b);


typedef struct Dz1TcpSerialServerPresetList
{
	void *storage;
	Dz1Error (*add)(struct Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *data);
	void (*remove)(struct Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key);
	Dz1TcpSerialServerPreset *(*extract)(struct Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key);
	Dz1TcpSerialServerPreset **(*get_array)(struct Dz1TcpSerialServerPresetList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*travel)(struct Dz1TcpSerialServerPresetList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPreset *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TcpSerialServerPresetList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPreset *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TcpSerialServerPresetList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPreset *entry), void *ptr);
	Dz1TcpSerialServerPreset *(*find)(struct Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key);
	int (*cmp)(Dz1TcpSerialServerPreset *a, Dz1TcpSerialServerPreset *b);
	unsigned int (*count)(struct Dz1TcpSerialServerPresetList *p);
} Dz1TcpSerialServerPresetList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPresetList *Dz1TcpSerialServerPresetList_new(Dz1Error *err);
static __inline__ Dz1TcpSerialServerPresetList *Dz1TcpSerialServerPresetList_gen(Dz1Error *err) { return Dz1TcpSerialServerPresetList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerPresetList *Dz1TcpSerialServerPresetList_clone(Dz1TcpSerialServerPresetList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetList_del(Dz1TcpSerialServerPresetList *p);
static __inline__ void Dz1TcpSerialServerPresetList_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerPresetList **p = (Dz1TcpSerialServerPresetList **)ptr;
	Dz1TcpSerialServerPresetList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerPresetList_dump(Dz1TcpSerialServerPresetList *p, int tab);


typedef struct Dz1TcpSerialServerConfig
{
	Dz1SockAddr                  *emulater;
	Dz1TcpSerialServerPresetList *presets;
} Dz1TcpSerialServerConfig;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_new(Dz1SockAddr *emulater, Dz1Error *err);
static __inline__ Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_gen(Dz1Error *err) { return Dz1TcpSerialServerConfig_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_clone(Dz1TcpSerialServerConfig *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerConfig_del(Dz1TcpSerialServerConfig *p);
static __inline__ void Dz1TcpSerialServerConfig_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerConfig **p = (Dz1TcpSerialServerConfig **)ptr;
	Dz1TcpSerialServerConfig_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerConfig_dump(Dz1TcpSerialServerConfig *p, int tab);

typedef struct Dz1TcpSerialServerCfgParserEnv
{
	Dz1TcpSerialServerConfig *dst;
	Dz1TcpSerialServerPreset *preset;
} Dz1TcpSerialServerCfgParserEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialServerCfgParserEnv *Dz1TcpSerialServerCfgParserEnv_new(Dz1TcpSerialServerConfig *dst, Dz1TcpSerialServerPreset *preset, Dz1Error *err);
static __inline__ Dz1TcpSerialServerCfgParserEnv *Dz1TcpSerialServerCfgParserEnv_gen(Dz1Error *err) { return Dz1TcpSerialServerCfgParserEnv_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialServerCfgParserEnv_del(Dz1TcpSerialServerCfgParserEnv *p);
static __inline__ void Dz1TcpSerialServerCfgParserEnv_delAndSetNull(void *ptr)
{
	Dz1TcpSerialServerCfgParserEnv **p = (Dz1TcpSerialServerCfgParserEnv **)ptr;
	Dz1TcpSerialServerCfgParserEnv_del(*p); *p = NULL;
}

#endif
