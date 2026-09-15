#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_MSG_DEF_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_MSG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Reserved0
typedef struct ITSK00144_2Reserved0
{
	u8_t	reserved1;
	u8_t	reserved2;
	u8_t	reserved3;
	u8_t	reserved4;
	u8_t	reserved5;
	u8_t	reserved6;
	u8_t	reserved7;
	u8_t	reserved8;
	u8_t	reserved9;
} ITSK00144_2Reserved0;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Reserved0 *ITSK00144_2Reserved0_new(u8_t reserved1, 
																	   u8_t reserved2, 
																	   u8_t reserved3, 
																	   u8_t reserved4, 
																	   u8_t reserved5, 
																	   u8_t reserved6, 
																	   u8_t reserved7, 
																	   u8_t reserved8, 
																	   u8_t reserved9, Dz1Error *err);
static __inline__ ITSK00144_2Reserved0 *ITSK00144_2Reserved0_gen(Dz1Error *err) { return ITSK00144_2Reserved0_new(0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2Reserved0_copy(ITSK00144_2Reserved0 *dst, ITSK00144_2Reserved0 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Reserved0 *ITSK00144_2Reserved0_clone(ITSK00144_2Reserved0 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved0_purge(ITSK00144_2Reserved0 *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved0_del(ITSK00144_2Reserved0 *p);
static __inline__ void ITSK00144_2Reserved0_delAndSetNull(void *ptr)
{
	ITSK00144_2Reserved0 **p = (ITSK00144_2Reserved0 **)ptr;
	if (p) { ITSK00144_2Reserved0_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved0_dump(ITSK00144_2Reserved0 *p, int tab);
// ITSK00144_2Reserved0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Reserved18
typedef struct ITSK00144_2Reserved18
{
	u8_t	reserved1;
	u8_t	reserved2;
	u8_t	reserved3;
	u8_t	reserved4;
	u8_t	reserved5;
	u8_t	reserved6;
	u8_t	reserved7;
} ITSK00144_2Reserved18;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Reserved18 *ITSK00144_2Reserved18_new(u8_t reserved1, 
																		 u8_t reserved2, 
																		 u8_t reserved3, 
																		 u8_t reserved4, 
																		 u8_t reserved5, 
																		 u8_t reserved6, 
																		 u8_t reserved7, Dz1Error *err);
static __inline__ ITSK00144_2Reserved18 *ITSK00144_2Reserved18_gen(Dz1Error *err) { return ITSK00144_2Reserved18_new(0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2Reserved18_copy(ITSK00144_2Reserved18 *dst, ITSK00144_2Reserved18 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Reserved18 *ITSK00144_2Reserved18_clone(ITSK00144_2Reserved18 *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved18_purge(ITSK00144_2Reserved18 *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved18_del(ITSK00144_2Reserved18 *p);
static __inline__ void ITSK00144_2Reserved18_delAndSetNull(void *ptr)
{
	ITSK00144_2Reserved18 **p = (ITSK00144_2Reserved18 **)ptr;
	if (p) { ITSK00144_2Reserved18_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Reserved18_dump(ITSK00144_2Reserved18 *p, int tab);
// ITSK00144_2Reserved18
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNo
typedef struct I2XTrafficSafetyDeviceSerialNo
{
	u8_t		type;
	u32_t		id;
} I2XTrafficSafetyDeviceSerialNo;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNo_new(u8_t type, 
																						   u32_t id, Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNo_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceSerialNo_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t I2XTrafficSafetyDeviceSerialNo_copy(I2XTrafficSafetyDeviceSerialNo *dst, I2XTrafficSafetyDeviceSerialNo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNo_clone(I2XTrafficSafetyDeviceSerialNo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNo_purge(I2XTrafficSafetyDeviceSerialNo *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNo_del(I2XTrafficSafetyDeviceSerialNo *p);
static __inline__ void I2XTrafficSafetyDeviceSerialNo_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceSerialNo **p = (I2XTrafficSafetyDeviceSerialNo **)ptr;
	if (p) { I2XTrafficSafetyDeviceSerialNo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNo_dump(I2XTrafficSafetyDeviceSerialNo *p, int tab);
// I2XTrafficSafetyDeviceSerialNo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNoList
typedef struct I2XTrafficSafetyDeviceSerialNoList
{
	void *storage;
	unsigned int (*count)(struct I2XTrafficSafetyDeviceSerialNoList *p);
	Dz1Error (*travel)(struct I2XTrafficSafetyDeviceSerialNoList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceSerialNo *entry), void *ptr);
	Dz1Error (*travelForward)(struct I2XTrafficSafetyDeviceSerialNoList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceSerialNo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct I2XTrafficSafetyDeviceSerialNoList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceSerialNo *entry), void *ptr);
	I2XTrafficSafetyDeviceSerialNo **(*get_array)(struct I2XTrafficSafetyDeviceSerialNoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct I2XTrafficSafetyDeviceSerialNoList *p, I2XTrafficSafetyDeviceSerialNo *data);
	I2XTrafficSafetyDeviceSerialNo *(*extract)(struct I2XTrafficSafetyDeviceSerialNoList *p, I2XTrafficSafetyDeviceSerialNo *ptr);
	I2XTrafficSafetyDeviceSerialNo *(*getHead)(struct I2XTrafficSafetyDeviceSerialNoList *p);
} I2XTrafficSafetyDeviceSerialNoList;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceSerialNoList *I2XTrafficSafetyDeviceSerialNoList_new(Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceSerialNoList *I2XTrafficSafetyDeviceSerialNoList_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceSerialNoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceSerialNoList *I2XTrafficSafetyDeviceSerialNoList_clone(I2XTrafficSafetyDeviceSerialNoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNoList_purge(I2XTrafficSafetyDeviceSerialNoList *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNoList_del(I2XTrafficSafetyDeviceSerialNoList *p);
static __inline__ void I2XTrafficSafetyDeviceSerialNoList_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceSerialNoList **p = (I2XTrafficSafetyDeviceSerialNoList **)ptr;
	if (p != NULL) { I2XTrafficSafetyDeviceSerialNoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceSerialNoList_dump(I2XTrafficSafetyDeviceSerialNoList *p, int tab);

// I2XTrafficSafetyDeviceSerialNoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceList
typedef struct I2XTrafficSafetyDeviceList
{
	u16_t									 cnt;
	I2XTrafficSafetyDeviceSerialNoList		*id;
} I2XTrafficSafetyDeviceList;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceList *I2XTrafficSafetyDeviceList_new(u16_t cnt, 
																				   I2XTrafficSafetyDeviceSerialNoList *id, Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceList *I2XTrafficSafetyDeviceList_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceList_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t I2XTrafficSafetyDeviceList_copy(I2XTrafficSafetyDeviceList *dst, I2XTrafficSafetyDeviceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceList *I2XTrafficSafetyDeviceList_clone(I2XTrafficSafetyDeviceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceList_purge(I2XTrafficSafetyDeviceList *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceList_del(I2XTrafficSafetyDeviceList *p);
static __inline__ void I2XTrafficSafetyDeviceList_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceList **p = (I2XTrafficSafetyDeviceList **)ptr;
	if (p) { I2XTrafficSafetyDeviceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceList_dump(I2XTrafficSafetyDeviceList *p, int tab);
// I2XTrafficSafetyDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceLinkUnitStatus
typedef struct I2XTrafficSafetyDeviceLinkUnitStatus
{
	bool_t		isActive;
	bool_t		control_comm;
	bool_t		wave_comm;
	u8_t		temperature;
	u8_t		humidity;
	bool_t		isOpen;
	bool_t		isFanOn;
	bool_t		isHeaterOn;
} I2XTrafficSafetyDeviceLinkUnitStatus;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceLinkUnitStatus *I2XTrafficSafetyDeviceLinkUnitStatus_new(bool_t isActive, 
																									   bool_t control_comm, 
																									   bool_t wave_comm, 
																									   u8_t temperature, 
																									   u8_t humidity, 
																									   bool_t isOpen, 
																									   bool_t isFanOn, 
																									   bool_t isHeaterOn, Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceLinkUnitStatus *I2XTrafficSafetyDeviceLinkUnitStatus_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceLinkUnitStatus_new(0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t I2XTrafficSafetyDeviceLinkUnitStatus_copy(I2XTrafficSafetyDeviceLinkUnitStatus *dst, I2XTrafficSafetyDeviceLinkUnitStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceLinkUnitStatus *I2XTrafficSafetyDeviceLinkUnitStatus_clone(I2XTrafficSafetyDeviceLinkUnitStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceLinkUnitStatus_purge(I2XTrafficSafetyDeviceLinkUnitStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceLinkUnitStatus_del(I2XTrafficSafetyDeviceLinkUnitStatus *p);
static __inline__ void I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceLinkUnitStatus **p = (I2XTrafficSafetyDeviceLinkUnitStatus **)ptr;
	if (p) { I2XTrafficSafetyDeviceLinkUnitStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceLinkUnitStatus_dump(I2XTrafficSafetyDeviceLinkUnitStatus *p, int tab);
// I2XTrafficSafetyDeviceLinkUnitStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatus
typedef struct I2XTrafficSafetyDeviceStatus
{
	I2XTrafficSafetyDeviceSerialNo		*id;
	bool_t								 isActive;
	bool_t								 isBatteryOn;
	bool_t								 isPowered;
	bool_t								 isPowerOn;
	bool_t								 isConnected;
	u8_t								 cnt;
} I2XTrafficSafetyDeviceStatus;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatus_new(I2XTrafficSafetyDeviceSerialNo *id, 
																					   bool_t isActive, 
																					   bool_t isBatteryOn, 
																					   bool_t isPowered, 
																					   bool_t isPowerOn, 
																					   bool_t isConnected, 
																					   u8_t cnt, Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatus_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceStatus_new(NULL, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t I2XTrafficSafetyDeviceStatus_copy(I2XTrafficSafetyDeviceStatus *dst, I2XTrafficSafetyDeviceStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatus_clone(I2XTrafficSafetyDeviceStatus *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatus_purge(I2XTrafficSafetyDeviceStatus *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatus_del(I2XTrafficSafetyDeviceStatus *p);
static __inline__ void I2XTrafficSafetyDeviceStatus_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceStatus **p = (I2XTrafficSafetyDeviceStatus **)ptr;
	if (p) { I2XTrafficSafetyDeviceStatus_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatus_dump(I2XTrafficSafetyDeviceStatus *p, int tab);
// I2XTrafficSafetyDeviceStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusList
typedef struct I2XTrafficSafetyDeviceStatusList
{
	void *storage;
	unsigned int (*count)(struct I2XTrafficSafetyDeviceStatusList *p);
	Dz1Error (*travel)(struct I2XTrafficSafetyDeviceStatusList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceStatus *entry), void *ptr);
	Dz1Error (*travelForward)(struct I2XTrafficSafetyDeviceStatusList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceStatus *entry), void *ptr);
	Dz1Error (*travelBackward)(struct I2XTrafficSafetyDeviceStatusList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceStatus *entry), void *ptr);
	I2XTrafficSafetyDeviceStatus **(*get_array)(struct I2XTrafficSafetyDeviceStatusList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct I2XTrafficSafetyDeviceStatusList *p, I2XTrafficSafetyDeviceStatus *data);
	I2XTrafficSafetyDeviceStatus *(*extract)(struct I2XTrafficSafetyDeviceStatusList *p, I2XTrafficSafetyDeviceStatus *ptr);
	I2XTrafficSafetyDeviceStatus *(*getHead)(struct I2XTrafficSafetyDeviceStatusList *p);
} I2XTrafficSafetyDeviceStatusList;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatusList *I2XTrafficSafetyDeviceStatusList_new(Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceStatusList *I2XTrafficSafetyDeviceStatusList_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceStatusList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatusList *I2XTrafficSafetyDeviceStatusList_clone(I2XTrafficSafetyDeviceStatusList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusList_purge(I2XTrafficSafetyDeviceStatusList *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusList_del(I2XTrafficSafetyDeviceStatusList *p);
static __inline__ void I2XTrafficSafetyDeviceStatusList_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceStatusList **p = (I2XTrafficSafetyDeviceStatusList **)ptr;
	if (p != NULL) { I2XTrafficSafetyDeviceStatusList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusList_dump(I2XTrafficSafetyDeviceStatusList *p, int tab);

// I2XTrafficSafetyDeviceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusInfo
typedef struct I2XTrafficSafetyDeviceStatusInfo
{
	u16_t								 num;
	I2XTrafficSafetyDeviceStatusList	*status;
} I2XTrafficSafetyDeviceStatusInfo;

DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatusInfo *I2XTrafficSafetyDeviceStatusInfo_new(u16_t num, 
																							   I2XTrafficSafetyDeviceStatusList *status, Dz1Error *err);
static __inline__ I2XTrafficSafetyDeviceStatusInfo *I2XTrafficSafetyDeviceStatusInfo_gen(Dz1Error *err) { return I2XTrafficSafetyDeviceStatusInfo_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t I2XTrafficSafetyDeviceStatusInfo_copy(I2XTrafficSafetyDeviceStatusInfo *dst, I2XTrafficSafetyDeviceStatusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT I2XTrafficSafetyDeviceStatusInfo *I2XTrafficSafetyDeviceStatusInfo_clone(I2XTrafficSafetyDeviceStatusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusInfo_purge(I2XTrafficSafetyDeviceStatusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusInfo_del(I2XTrafficSafetyDeviceStatusInfo *p);
static __inline__ void I2XTrafficSafetyDeviceStatusInfo_delAndSetNull(void *ptr)
{
	I2XTrafficSafetyDeviceStatusInfo **p = (I2XTrafficSafetyDeviceStatusInfo **)ptr;
	if (p) { I2XTrafficSafetyDeviceStatusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void I2XTrafficSafetyDeviceStatusInfo_dump(I2XTrafficSafetyDeviceStatusInfo *p, int tab);
// I2XTrafficSafetyDeviceStatusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2DataPresent
typedef enum ITSK00144_2DataPresent
{
	ITSK00144_2DataPresent_req_link_unit_status = 17,
	ITSK00144_2DataPresent_rsp_link_unit_status = 18,
	ITSK00144_2DataPresent_req_status = 19,
	ITSK00144_2DataPresent_rsp_status = 20,
	ITSK00144_2DataPresent_req_list = 21,
	ITSK00144_2DataPresent_rsp_list = 22,
	ITSK00144_2DataPresent_req_update_list = 23,
	ITSK00144_2DataPresent_rsp_update_list = 24,
	ITSK00144_2DataPresent_reset = 129,
	ITSK00144_2DataPresent_hb = 153,
	ITSK00144_2DataPresent_ack = 160,
	ITSK00144_2DataPresent_nack = 161,
	ITSK00144_2DataPresent_max
} ITSK00144_2DataPresent;

DZ1_CPPLINK str_t ITSK00144_2DataPresentStrA(ITSK00144_2DataPresent v);
DZ1_CPPLINK ITSK00144_2DataPresent ITSK00144_2DataPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2DataPresentStrW(ITSK00144_2DataPresent v);
DZ1_CPPLINK ITSK00144_2DataPresent ITSK00144_2DataPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2DataPresentStr ITSK00144_2DataPresentStrW
#define ITSK00144_2DataPresentFromStr ITSK00144_2DataPresentFromStrW
#else // UNICODE
#define ITSK00144_2DataPresentStr ITSK00144_2DataPresentStrA
#define ITSK00144_2DataPresentFromStr ITSK00144_2DataPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2DataPresentStr ITSK00144_2DataPresentStrA
#define ITSK00144_2DataPresentFromStr ITSK00144_2DataPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2DataPresent *ITSK00144_2DataPresent_new(ITSK00144_2DataPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2DataPresent *ITSK00144_2DataPresent_gen(Dz1Error *err) { ITSK00144_2DataPresent v = ITSK00144_2DataPresent_max; return ITSK00144_2DataPresent_new(&v, err); }
#define ITSK00144_2DataPresent_clone             ITSK00144_2DataPresent_new
static __inline__ void ITSK00144_2DataPresent_del(ITSK00144_2DataPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2DataPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2DataPresent **p = (ITSK00144_2DataPresent **)ptr;
	if (p != NULL) { ITSK00144_2DataPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2DataPresent_dump(ITSK00144_2DataPresent *v, int tab);
// ITSK00144_2DataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Data
typedef struct ITSK00144_2Data
{
	ITSK00144_2DataPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2Reserved0					*req_link_unit_status;
		I2XTrafficSafetyDeviceLinkUnitStatus	*rsp_link_unit_status;
		ITSK00144_2Reserved0					*req_status;
		I2XTrafficSafetyDeviceStatusInfo		*rsp_status;
		ITSK00144_2Reserved0					*req_list;
		I2XTrafficSafetyDeviceList				*rsp_list;
		I2XTrafficSafetyDeviceList				*req_update_list;
		I2XTrafficSafetyDeviceList				*rsp_update_list;
		ITSK00144_2Reserved0					*reset;
		ITSK00144_2Reserved0					*hb;
		ITSK00144_2Reserved0					*ack;
		ITSK00144_2Reserved0					*nack;
	} x;
} ITSK00144_2Data;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Data *ITSK00144_2Data_new(ITSK00144_2DataPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2Data *ITSK00144_2Data_gen(Dz1Error *err) { return ITSK00144_2Data_new(ITSK00144_2DataPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ITSK00144_2Data_copy(ITSK00144_2Data *dst, ITSK00144_2Data *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2Data *ITSK00144_2Data_clone(ITSK00144_2Data *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Data_purge(ITSK00144_2Data *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Data_del(ITSK00144_2Data *p);
static __inline__ void ITSK00144_2Data_delAndSetNull(void *ptr)
{
	ITSK00144_2Data **p = (ITSK00144_2Data **)ptr;
	if (p != NULL) { ITSK00144_2Data_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2Data_dump(ITSK00144_2Data *p, int tab);
// ITSK00144_2Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrameContext
typedef struct ITSK00144_2ProtocolFrameContext
{
	I2XTrafficSafetyDeviceSerialNo		*id;
	u8_t								 seq;
	u8_t								 opcode;
	ITSK00144_2Data						*data;
} ITSK00144_2ProtocolFrameContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ProtocolFrameContext *ITSK00144_2ProtocolFrameContext_new(I2XTrafficSafetyDeviceSerialNo *id, 
																							 u8_t seq, 
																							 u8_t opcode, 
																							 ITSK00144_2Data *data, Dz1Error *err);
static __inline__ ITSK00144_2ProtocolFrameContext *ITSK00144_2ProtocolFrameContext_gen(Dz1Error *err) { return ITSK00144_2ProtocolFrameContext_new(NULL, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ProtocolFrameContext_copy(ITSK00144_2ProtocolFrameContext *dst, ITSK00144_2ProtocolFrameContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ProtocolFrameContext *ITSK00144_2ProtocolFrameContext_clone(ITSK00144_2ProtocolFrameContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrameContext_purge(ITSK00144_2ProtocolFrameContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrameContext_del(ITSK00144_2ProtocolFrameContext *p);
static __inline__ void ITSK00144_2ProtocolFrameContext_delAndSetNull(void *ptr)
{
	ITSK00144_2ProtocolFrameContext **p = (ITSK00144_2ProtocolFrameContext **)ptr;
	if (p) { ITSK00144_2ProtocolFrameContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrameContext_dump(ITSK00144_2ProtocolFrameContext *p, int tab);
// ITSK00144_2ProtocolFrameContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrame
typedef struct ITSK00144_2ProtocolFrame
{
	u16_t			 length;
	Dz1Binary		*context;
	u16_t			 crc;
} ITSK00144_2ProtocolFrame;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ProtocolFrame *ITSK00144_2ProtocolFrame_new(u16_t length, 
																			   Dz1Binary *context, 
																			   u16_t crc, Dz1Error *err);
static __inline__ ITSK00144_2ProtocolFrame *ITSK00144_2ProtocolFrame_gen(Dz1Error *err) { return ITSK00144_2ProtocolFrame_new(0, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ProtocolFrame_copy(ITSK00144_2ProtocolFrame *dst, ITSK00144_2ProtocolFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ProtocolFrame *ITSK00144_2ProtocolFrame_clone(ITSK00144_2ProtocolFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrame_purge(ITSK00144_2ProtocolFrame *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrame_del(ITSK00144_2ProtocolFrame *p);
static __inline__ void ITSK00144_2ProtocolFrame_delAndSetNull(void *ptr)
{
	ITSK00144_2ProtocolFrame **p = (ITSK00144_2ProtocolFrame **)ptr;
	if (p) { ITSK00144_2ProtocolFrame_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProtocolFrame_dump(ITSK00144_2ProtocolFrame *p, int tab);
// ITSK00144_2ProtocolFrame
////////////////////////////////////////////////////////////////////////////////

#endif
