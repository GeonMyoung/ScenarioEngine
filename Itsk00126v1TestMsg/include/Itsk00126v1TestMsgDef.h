#ifndef _DZ1_TDC_ITSK00126V1_TEST_MSG_DEF_H_
#define _DZ1_TDC_ITSK00126V1_TEST_MSG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfo
typedef struct IoTImDeviceSttusInfo
{
	Dz1Str		iot_im_device_id;
	Dz1Str		iot_im_device_link_sttus_code;
} IoTImDeviceSttusInfo;

DZ1_CPPLINK DZ1_DLLPORT IoTImDeviceSttusInfo *IoTImDeviceSttusInfo_new(Dz1Str iot_im_device_id, 
																	   Dz1Str iot_im_device_link_sttus_code, Dz1Error *err);
static __inline__ IoTImDeviceSttusInfo *IoTImDeviceSttusInfo_gen(Dz1Error *err) { return IoTImDeviceSttusInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t IoTImDeviceSttusInfo_copy(IoTImDeviceSttusInfo *dst, IoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT IoTImDeviceSttusInfo *IoTImDeviceSttusInfo_clone(IoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfo_purge(IoTImDeviceSttusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfo_del(IoTImDeviceSttusInfo *p);
static __inline__ void IoTImDeviceSttusInfo_delAndSetNull(void *ptr)
{
	IoTImDeviceSttusInfo **p = (IoTImDeviceSttusInfo **)ptr;
	if (p) { IoTImDeviceSttusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfo_dump(IoTImDeviceSttusInfo *p, int tab);
// IoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfoList
typedef struct IoTImDeviceSttusInfoList
{
	void *storage;
	unsigned int (*count)(struct IoTImDeviceSttusInfoList *p);
	Dz1Error (*travel)(struct IoTImDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, IoTImDeviceSttusInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct IoTImDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, IoTImDeviceSttusInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct IoTImDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, IoTImDeviceSttusInfo *entry), void *ptr);
	IoTImDeviceSttusInfo **(*get_array)(struct IoTImDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct IoTImDeviceSttusInfoList *p, IoTImDeviceSttusInfo *data);
	IoTImDeviceSttusInfo *(*extract)(struct IoTImDeviceSttusInfoList *p, IoTImDeviceSttusInfo *ptr);
	IoTImDeviceSttusInfo *(*getHead)(struct IoTImDeviceSttusInfoList *p);
} IoTImDeviceSttusInfoList;

DZ1_CPPLINK DZ1_DLLPORT IoTImDeviceSttusInfoList *IoTImDeviceSttusInfoList_new(Dz1Error *err);
static __inline__ IoTImDeviceSttusInfoList *IoTImDeviceSttusInfoList_gen(Dz1Error *err) { return IoTImDeviceSttusInfoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT IoTImDeviceSttusInfoList *IoTImDeviceSttusInfoList_clone(IoTImDeviceSttusInfoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfoList_purge(IoTImDeviceSttusInfoList *p);
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfoList_del(IoTImDeviceSttusInfoList *p);
static __inline__ void IoTImDeviceSttusInfoList_delAndSetNull(void *ptr)
{
	IoTImDeviceSttusInfoList **p = (IoTImDeviceSttusInfoList **)ptr;
	if (p != NULL) { IoTImDeviceSttusInfoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IoTImDeviceSttusInfoList_dump(IoTImDeviceSttusInfoList *p, int tab);

// IoTImDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfoData
typedef struct C2CIoTImDeviceSttusInfoData
{
	Dz1Str						 local_center_id;
	Dz1Str						 iot_im_device_id_qty;
	IoTImDeviceSttusInfoList	*iot_im_device_sttus_info_list;
	Dz1Str						 creat_dt;
} C2CIoTImDeviceSttusInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTImDeviceSttusInfoData *C2CIoTImDeviceSttusInfoData_new(Dz1Str local_center_id, 
																					 Dz1Str iot_im_device_id_qty, 
																					 IoTImDeviceSttusInfoList *iot_im_device_sttus_info_list, 
																					 Dz1Str creat_dt, Dz1Error *err);
static __inline__ C2CIoTImDeviceSttusInfoData *C2CIoTImDeviceSttusInfoData_gen(Dz1Error *err) { return C2CIoTImDeviceSttusInfoData_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTImDeviceSttusInfoData_copy(C2CIoTImDeviceSttusInfoData *dst, C2CIoTImDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTImDeviceSttusInfoData *C2CIoTImDeviceSttusInfoData_clone(C2CIoTImDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfoData_purge(C2CIoTImDeviceSttusInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfoData_del(C2CIoTImDeviceSttusInfoData *p);
static __inline__ void C2CIoTImDeviceSttusInfoData_delAndSetNull(void *ptr)
{
	C2CIoTImDeviceSttusInfoData **p = (C2CIoTImDeviceSttusInfoData **)ptr;
	if (p) { C2CIoTImDeviceSttusInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfoData_dump(C2CIoTImDeviceSttusInfoData *p, int tab);
// C2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfo
typedef struct C2CIoTImDeviceSttusInfo
{
	Dz1Str							 command;
	Dz1Str							 event_name;
	Dz1Str							 event_type;
	C2CIoTImDeviceSttusInfoData		*data;
} C2CIoTImDeviceSttusInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTImDeviceSttusInfo *C2CIoTImDeviceSttusInfo_new(Dz1Str command, 
																			 Dz1Str event_name, 
																			 Dz1Str event_type, 
																			 C2CIoTImDeviceSttusInfoData *data, Dz1Error *err);
static __inline__ C2CIoTImDeviceSttusInfo *C2CIoTImDeviceSttusInfo_gen(Dz1Error *err) { return C2CIoTImDeviceSttusInfo_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTImDeviceSttusInfo_copy(C2CIoTImDeviceSttusInfo *dst, C2CIoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTImDeviceSttusInfo *C2CIoTImDeviceSttusInfo_clone(C2CIoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfo_purge(C2CIoTImDeviceSttusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfo_del(C2CIoTImDeviceSttusInfo *p);
static __inline__ void C2CIoTImDeviceSttusInfo_delAndSetNull(void *ptr)
{
	C2CIoTImDeviceSttusInfo **p = (C2CIoTImDeviceSttusInfo **)ptr;
	if (p) { C2CIoTImDeviceSttusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTImDeviceSttusInfo_dump(C2CIoTImDeviceSttusInfo *p, int tab);
// C2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListRequestInfoData
typedef struct C2CIoTDeviceListRequestInfoData
{
	Dz1Str		local_center_id;
	Dz1Str		event_name;
	Dz1Str		event_type;
} C2CIoTDeviceListRequestInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListRequestInfoData *C2CIoTDeviceListRequestInfoData_new(Dz1Str local_center_id, 
																							 Dz1Str event_name, 
																							 Dz1Str event_type, Dz1Error *err);
static __inline__ C2CIoTDeviceListRequestInfoData *C2CIoTDeviceListRequestInfoData_gen(Dz1Error *err) { return C2CIoTDeviceListRequestInfoData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceListRequestInfoData_copy(C2CIoTDeviceListRequestInfoData *dst, C2CIoTDeviceListRequestInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListRequestInfoData *C2CIoTDeviceListRequestInfoData_clone(C2CIoTDeviceListRequestInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfoData_purge(C2CIoTDeviceListRequestInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfoData_del(C2CIoTDeviceListRequestInfoData *p);
static __inline__ void C2CIoTDeviceListRequestInfoData_delAndSetNull(void *ptr)
{
	C2CIoTDeviceListRequestInfoData **p = (C2CIoTDeviceListRequestInfoData **)ptr;
	if (p) { C2CIoTDeviceListRequestInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfoData_dump(C2CIoTDeviceListRequestInfoData *p, int tab);
// C2CIoTDeviceListRequestInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListRequestInfo
typedef struct C2CIoTDeviceListRequestInfo
{
	Dz1Str								 command;
	C2CIoTDeviceListRequestInfoData		*data;
} C2CIoTDeviceListRequestInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListRequestInfo *C2CIoTDeviceListRequestInfo_new(Dz1Str command, 
																					 C2CIoTDeviceListRequestInfoData *data, Dz1Error *err);
static __inline__ C2CIoTDeviceListRequestInfo *C2CIoTDeviceListRequestInfo_gen(Dz1Error *err) { return C2CIoTDeviceListRequestInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceListRequestInfo_copy(C2CIoTDeviceListRequestInfo *dst, C2CIoTDeviceListRequestInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListRequestInfo *C2CIoTDeviceListRequestInfo_clone(C2CIoTDeviceListRequestInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfo_purge(C2CIoTDeviceListRequestInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfo_del(C2CIoTDeviceListRequestInfo *p);
static __inline__ void C2CIoTDeviceListRequestInfo_delAndSetNull(void *ptr)
{
	C2CIoTDeviceListRequestInfo **p = (C2CIoTDeviceListRequestInfo **)ptr;
	if (p) { C2CIoTDeviceListRequestInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListRequestInfo_dump(C2CIoTDeviceListRequestInfo *p, int tab);
// C2CIoTDeviceListRequestInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceEntry
typedef struct C2CIoTDeviceEntry
{
	Dz1Str		iot_device_id;
} C2CIoTDeviceEntry;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceEntry *C2CIoTDeviceEntry_new(Dz1Str iot_device_id, Dz1Error *err);
static __inline__ C2CIoTDeviceEntry *C2CIoTDeviceEntry_gen(Dz1Error *err) { return C2CIoTDeviceEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceEntry_copy(C2CIoTDeviceEntry *dst, C2CIoTDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceEntry *C2CIoTDeviceEntry_clone(C2CIoTDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceEntry_purge(C2CIoTDeviceEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceEntry_del(C2CIoTDeviceEntry *p);
static __inline__ void C2CIoTDeviceEntry_delAndSetNull(void *ptr)
{
	C2CIoTDeviceEntry **p = (C2CIoTDeviceEntry **)ptr;
	if (p) { C2CIoTDeviceEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceEntry_dump(C2CIoTDeviceEntry *p, int tab);
// C2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceList
typedef struct C2CIoTDeviceList
{
	void *storage;
	unsigned int (*count)(struct C2CIoTDeviceList *p);
	Dz1Error (*travel)(struct C2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceEntry *entry), void *ptr);
	C2CIoTDeviceEntry **(*get_array)(struct C2CIoTDeviceList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CIoTDeviceList *p, C2CIoTDeviceEntry *data);
	C2CIoTDeviceEntry *(*extract)(struct C2CIoTDeviceList *p, C2CIoTDeviceEntry *ptr);
	C2CIoTDeviceEntry *(*getHead)(struct C2CIoTDeviceList *p);
} C2CIoTDeviceList;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceList *C2CIoTDeviceList_new(Dz1Error *err);
static __inline__ C2CIoTDeviceList *C2CIoTDeviceList_gen(Dz1Error *err) { return C2CIoTDeviceList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceList *C2CIoTDeviceList_clone(C2CIoTDeviceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceList_purge(C2CIoTDeviceList *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceList_del(C2CIoTDeviceList *p);
static __inline__ void C2CIoTDeviceList_delAndSetNull(void *ptr)
{
	C2CIoTDeviceList **p = (C2CIoTDeviceList **)ptr;
	if (p != NULL) { C2CIoTDeviceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceList_dump(C2CIoTDeviceList *p, int tab);

// C2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceEntry
typedef struct C2CImDeviceEntry
{
	Dz1Str				 iot_im_device_id;
	Dz1Str				 iot_device_id_qty;
	C2CIoTDeviceList	*iot_device_list;
} C2CImDeviceEntry;

DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceEntry *C2CImDeviceEntry_new(Dz1Str iot_im_device_id, 
															   Dz1Str iot_device_id_qty, 
															   C2CIoTDeviceList *iot_device_list, Dz1Error *err);
static __inline__ C2CImDeviceEntry *C2CImDeviceEntry_gen(Dz1Error *err) { return C2CImDeviceEntry_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CImDeviceEntry_copy(C2CImDeviceEntry *dst, C2CImDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceEntry *C2CImDeviceEntry_clone(C2CImDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceEntry_purge(C2CImDeviceEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceEntry_del(C2CImDeviceEntry *p);
static __inline__ void C2CImDeviceEntry_delAndSetNull(void *ptr)
{
	C2CImDeviceEntry **p = (C2CImDeviceEntry **)ptr;
	if (p) { C2CImDeviceEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceEntry_dump(C2CImDeviceEntry *p, int tab);
// C2CImDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceList
typedef struct C2CImDeviceList
{
	void *storage;
	unsigned int (*count)(struct C2CImDeviceList *p);
	Dz1Error (*travel)(struct C2CImDeviceList *p, Dz1Error (*func)(void *ptr, C2CImDeviceEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CImDeviceList *p, Dz1Error (*func)(void *ptr, C2CImDeviceEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CImDeviceList *p, Dz1Error (*func)(void *ptr, C2CImDeviceEntry *entry), void *ptr);
	C2CImDeviceEntry **(*get_array)(struct C2CImDeviceList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CImDeviceList *p, C2CImDeviceEntry *data);
	C2CImDeviceEntry *(*extract)(struct C2CImDeviceList *p, C2CImDeviceEntry *ptr);
	C2CImDeviceEntry *(*getHead)(struct C2CImDeviceList *p);
} C2CImDeviceList;

DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceList *C2CImDeviceList_new(Dz1Error *err);
static __inline__ C2CImDeviceList *C2CImDeviceList_gen(Dz1Error *err) { return C2CImDeviceList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceList *C2CImDeviceList_clone(C2CImDeviceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceList_purge(C2CImDeviceList *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceList_del(C2CImDeviceList *p);
static __inline__ void C2CImDeviceList_delAndSetNull(void *ptr)
{
	C2CImDeviceList **p = (C2CImDeviceList **)ptr;
	if (p != NULL) { C2CImDeviceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceList_dump(C2CImDeviceList *p, int tab);

// C2CImDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfoData
typedef struct C2CIoTDeviceListResponseInfoData
{
	Dz1Str				 local_center_id;
	Dz1Str				 event_name;
	Dz1Str				 event_type;
	Dz1Str				 iot_im_device_id_qty;
	C2CImDeviceList		*c2c_im_device_list;
} C2CIoTDeviceListResponseInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListResponseInfoData *C2CIoTDeviceListResponseInfoData_new(Dz1Str local_center_id, 
																							   Dz1Str event_name, 
																							   Dz1Str event_type, 
																							   Dz1Str iot_im_device_id_qty, 
																							   C2CImDeviceList *c2c_im_device_list, Dz1Error *err);
static __inline__ C2CIoTDeviceListResponseInfoData *C2CIoTDeviceListResponseInfoData_gen(Dz1Error *err) { return C2CIoTDeviceListResponseInfoData_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceListResponseInfoData_copy(C2CIoTDeviceListResponseInfoData *dst, C2CIoTDeviceListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListResponseInfoData *C2CIoTDeviceListResponseInfoData_clone(C2CIoTDeviceListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfoData_purge(C2CIoTDeviceListResponseInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfoData_del(C2CIoTDeviceListResponseInfoData *p);
static __inline__ void C2CIoTDeviceListResponseInfoData_delAndSetNull(void *ptr)
{
	C2CIoTDeviceListResponseInfoData **p = (C2CIoTDeviceListResponseInfoData **)ptr;
	if (p) { C2CIoTDeviceListResponseInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfoData_dump(C2CIoTDeviceListResponseInfoData *p, int tab);
// C2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfo
typedef struct C2CIoTDeviceListResponseInfo
{
	Dz1Str								 command;
	C2CIoTDeviceListResponseInfoData	*data;
} C2CIoTDeviceListResponseInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListResponseInfo *C2CIoTDeviceListResponseInfo_new(Dz1Str command, 
																					   C2CIoTDeviceListResponseInfoData *data, Dz1Error *err);
static __inline__ C2CIoTDeviceListResponseInfo *C2CIoTDeviceListResponseInfo_gen(Dz1Error *err) { return C2CIoTDeviceListResponseInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceListResponseInfo_copy(C2CIoTDeviceListResponseInfo *dst, C2CIoTDeviceListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceListResponseInfo *C2CIoTDeviceListResponseInfo_clone(C2CIoTDeviceListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfo_purge(C2CIoTDeviceListResponseInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfo_del(C2CIoTDeviceListResponseInfo *p);
static __inline__ void C2CIoTDeviceListResponseInfo_delAndSetNull(void *ptr)
{
	C2CIoTDeviceListResponseInfo **p = (C2CIoTDeviceListResponseInfo **)ptr;
	if (p) { C2CIoTDeviceListResponseInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceListResponseInfo_dump(C2CIoTDeviceListResponseInfo *p, int tab);
// C2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoEntry
typedef struct C2CIoTDeviceSttusInfoEntry
{
	Dz1Str		iot_device_id;
	Dz1Str		iot_device_sttus_code;
	Dz1Str		btry_sttus_code;
	Dz1Str		link_sttus_code;
	s64_t		data_trnsmis_cont;
	Dz1Str		iot_im_device_id;
} C2CIoTDeviceSttusInfoEntry;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoEntry_new(Dz1Str iot_device_id, 
																				   Dz1Str iot_device_sttus_code, 
																				   Dz1Str btry_sttus_code, 
																				   Dz1Str link_sttus_code, 
																				   s64_t data_trnsmis_cont, 
																				   Dz1Str iot_im_device_id, Dz1Error *err);
static __inline__ C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoEntry_gen(Dz1Error *err) { return C2CIoTDeviceSttusInfoEntry_new(NULL, NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceSttusInfoEntry_copy(C2CIoTDeviceSttusInfoEntry *dst, C2CIoTDeviceSttusInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoEntry_clone(C2CIoTDeviceSttusInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoEntry_purge(C2CIoTDeviceSttusInfoEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoEntry_del(C2CIoTDeviceSttusInfoEntry *p);
static __inline__ void C2CIoTDeviceSttusInfoEntry_delAndSetNull(void *ptr)
{
	C2CIoTDeviceSttusInfoEntry **p = (C2CIoTDeviceSttusInfoEntry **)ptr;
	if (p) { C2CIoTDeviceSttusInfoEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoEntry_dump(C2CIoTDeviceSttusInfoEntry *p, int tab);
// C2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoList
typedef struct C2CIoTDeviceSttusInfoList
{
	void *storage;
	unsigned int (*count)(struct C2CIoTDeviceSttusInfoList *p);
	Dz1Error (*travel)(struct C2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	C2CIoTDeviceSttusInfoEntry **(*get_array)(struct C2CIoTDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CIoTDeviceSttusInfoList *p, C2CIoTDeviceSttusInfoEntry *data);
	C2CIoTDeviceSttusInfoEntry *(*extract)(struct C2CIoTDeviceSttusInfoList *p, C2CIoTDeviceSttusInfoEntry *ptr);
	C2CIoTDeviceSttusInfoEntry *(*getHead)(struct C2CIoTDeviceSttusInfoList *p);
} C2CIoTDeviceSttusInfoList;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoList *C2CIoTDeviceSttusInfoList_new(Dz1Error *err);
static __inline__ C2CIoTDeviceSttusInfoList *C2CIoTDeviceSttusInfoList_gen(Dz1Error *err) { return C2CIoTDeviceSttusInfoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoList *C2CIoTDeviceSttusInfoList_clone(C2CIoTDeviceSttusInfoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoList_purge(C2CIoTDeviceSttusInfoList *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoList_del(C2CIoTDeviceSttusInfoList *p);
static __inline__ void C2CIoTDeviceSttusInfoList_delAndSetNull(void *ptr)
{
	C2CIoTDeviceSttusInfoList **p = (C2CIoTDeviceSttusInfoList **)ptr;
	if (p != NULL) { C2CIoTDeviceSttusInfoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoList_dump(C2CIoTDeviceSttusInfoList *p, int tab);

// C2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoData
typedef struct C2CIoTDeviceSttusInfoData
{
	Dz1Str							 local_center_id;
	Dz1Str							 iot_device_id_qty;
	C2CIoTDeviceSttusInfoList		*iot_device_sttus_info_list;
	Dz1Str							 creat_dt;
} C2CIoTDeviceSttusInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoData *C2CIoTDeviceSttusInfoData_new(Dz1Str local_center_id, 
																				 Dz1Str iot_device_id_qty, 
																				 C2CIoTDeviceSttusInfoList *iot_device_sttus_info_list, 
																				 Dz1Str creat_dt, Dz1Error *err);
static __inline__ C2CIoTDeviceSttusInfoData *C2CIoTDeviceSttusInfoData_gen(Dz1Error *err) { return C2CIoTDeviceSttusInfoData_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceSttusInfoData_copy(C2CIoTDeviceSttusInfoData *dst, C2CIoTDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfoData *C2CIoTDeviceSttusInfoData_clone(C2CIoTDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoData_purge(C2CIoTDeviceSttusInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoData_del(C2CIoTDeviceSttusInfoData *p);
static __inline__ void C2CIoTDeviceSttusInfoData_delAndSetNull(void *ptr)
{
	C2CIoTDeviceSttusInfoData **p = (C2CIoTDeviceSttusInfoData **)ptr;
	if (p) { C2CIoTDeviceSttusInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfoData_dump(C2CIoTDeviceSttusInfoData *p, int tab);
// C2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfo
typedef struct C2CIoTDeviceSttusInfo
{
	Dz1Str							 command;
	C2CIoTDeviceSttusInfoData		*data;
} C2CIoTDeviceSttusInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfo *C2CIoTDeviceSttusInfo_new(Dz1Str command, 
																		 C2CIoTDeviceSttusInfoData *data, Dz1Error *err);
static __inline__ C2CIoTDeviceSttusInfo *C2CIoTDeviceSttusInfo_gen(Dz1Error *err) { return C2CIoTDeviceSttusInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIoTDeviceSttusInfo_copy(C2CIoTDeviceSttusInfo *dst, C2CIoTDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIoTDeviceSttusInfo *C2CIoTDeviceSttusInfo_clone(C2CIoTDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfo_purge(C2CIoTDeviceSttusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfo_del(C2CIoTDeviceSttusInfo *p);
static __inline__ void C2CIoTDeviceSttusInfo_delAndSetNull(void *ptr)
{
	C2CIoTDeviceSttusInfo **p = (C2CIoTDeviceSttusInfo **)ptr;
	if (p) { C2CIoTDeviceSttusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIoTDeviceSttusInfo_dump(C2CIoTDeviceSttusInfo *p, int tab);
// C2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListRequestInfoData
typedef struct C2CSafetySignalListRequestInfoData
{
	Dz1Str		local_center_id;
	Dz1Str		event_name;
	Dz1Str		event_type;
} C2CSafetySignalListRequestInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListRequestInfoData *C2CSafetySignalListRequestInfoData_new(Dz1Str local_center_id, 
																								   Dz1Str event_name, 
																								   Dz1Str event_type, Dz1Error *err);
static __inline__ C2CSafetySignalListRequestInfoData *C2CSafetySignalListRequestInfoData_gen(Dz1Error *err) { return C2CSafetySignalListRequestInfoData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CSafetySignalListRequestInfoData_copy(C2CSafetySignalListRequestInfoData *dst, C2CSafetySignalListRequestInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListRequestInfoData *C2CSafetySignalListRequestInfoData_clone(C2CSafetySignalListRequestInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfoData_purge(C2CSafetySignalListRequestInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfoData_del(C2CSafetySignalListRequestInfoData *p);
static __inline__ void C2CSafetySignalListRequestInfoData_delAndSetNull(void *ptr)
{
	C2CSafetySignalListRequestInfoData **p = (C2CSafetySignalListRequestInfoData **)ptr;
	if (p) { C2CSafetySignalListRequestInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfoData_dump(C2CSafetySignalListRequestInfoData *p, int tab);
// C2CSafetySignalListRequestInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListRequestInfo
typedef struct C2CSafetySignalListRequestInfo
{
	Dz1Str									 command;
	C2CSafetySignalListRequestInfoData		*data;
} C2CSafetySignalListRequestInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListRequestInfo *C2CSafetySignalListRequestInfo_new(Dz1Str command, 
																						   C2CSafetySignalListRequestInfoData *data, Dz1Error *err);
static __inline__ C2CSafetySignalListRequestInfo *C2CSafetySignalListRequestInfo_gen(Dz1Error *err) { return C2CSafetySignalListRequestInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CSafetySignalListRequestInfo_copy(C2CSafetySignalListRequestInfo *dst, C2CSafetySignalListRequestInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListRequestInfo *C2CSafetySignalListRequestInfo_clone(C2CSafetySignalListRequestInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfo_purge(C2CSafetySignalListRequestInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfo_del(C2CSafetySignalListRequestInfo *p);
static __inline__ void C2CSafetySignalListRequestInfo_delAndSetNull(void *ptr)
{
	C2CSafetySignalListRequestInfo **p = (C2CSafetySignalListRequestInfo **)ptr;
	if (p) { C2CSafetySignalListRequestInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListRequestInfo_dump(C2CSafetySignalListRequestInfo *p, int tab);
// C2CSafetySignalListRequestInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfo
typedef struct C2CSafetySignalInfo
{
	Dz1Str		safety_signal_id;
	Dz1Str		administ_zone_code;
	Dz1Str		road_code;
	real64_t	lc_lat;
	real64_t	lc_lng;
	Dz1Str		safety_signal_ty_code;
	Dz1Str		safety_signal_sttus_code;
} C2CSafetySignalInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalInfo *C2CSafetySignalInfo_new(Dz1Str safety_signal_id, 
																	 Dz1Str administ_zone_code, 
																	 Dz1Str road_code, 
																	 real64_t lc_lat, 
																	 real64_t lc_lng, 
																	 Dz1Str safety_signal_ty_code, 
																	 Dz1Str safety_signal_sttus_code, Dz1Error *err);
static __inline__ C2CSafetySignalInfo *C2CSafetySignalInfo_gen(Dz1Error *err) { return C2CSafetySignalInfo_new(NULL, NULL, NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CSafetySignalInfo_copy(C2CSafetySignalInfo *dst, C2CSafetySignalInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalInfo *C2CSafetySignalInfo_clone(C2CSafetySignalInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfo_purge(C2CSafetySignalInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfo_del(C2CSafetySignalInfo *p);
static __inline__ void C2CSafetySignalInfo_delAndSetNull(void *ptr)
{
	C2CSafetySignalInfo **p = (C2CSafetySignalInfo **)ptr;
	if (p) { C2CSafetySignalInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfo_dump(C2CSafetySignalInfo *p, int tab);
// C2CSafetySignalInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfoList
typedef struct C2CSafetySignalInfoList
{
	void *storage;
	unsigned int (*count)(struct C2CSafetySignalInfoList *p);
	Dz1Error (*travel)(struct C2CSafetySignalInfoList *p, Dz1Error (*func)(void *ptr, C2CSafetySignalInfo *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CSafetySignalInfoList *p, Dz1Error (*func)(void *ptr, C2CSafetySignalInfo *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CSafetySignalInfoList *p, Dz1Error (*func)(void *ptr, C2CSafetySignalInfo *entry), void *ptr);
	C2CSafetySignalInfo **(*get_array)(struct C2CSafetySignalInfoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CSafetySignalInfoList *p, C2CSafetySignalInfo *data);
	C2CSafetySignalInfo *(*extract)(struct C2CSafetySignalInfoList *p, C2CSafetySignalInfo *ptr);
	C2CSafetySignalInfo *(*getHead)(struct C2CSafetySignalInfoList *p);
} C2CSafetySignalInfoList;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalInfoList *C2CSafetySignalInfoList_new(Dz1Error *err);
static __inline__ C2CSafetySignalInfoList *C2CSafetySignalInfoList_gen(Dz1Error *err) { return C2CSafetySignalInfoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalInfoList *C2CSafetySignalInfoList_clone(C2CSafetySignalInfoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfoList_purge(C2CSafetySignalInfoList *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfoList_del(C2CSafetySignalInfoList *p);
static __inline__ void C2CSafetySignalInfoList_delAndSetNull(void *ptr)
{
	C2CSafetySignalInfoList **p = (C2CSafetySignalInfoList **)ptr;
	if (p != NULL) { C2CSafetySignalInfoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalInfoList_dump(C2CSafetySignalInfoList *p, int tab);

// C2CSafetySignalInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignalEntry
typedef struct C2CIotDeviceListSignalEntry
{
	Dz1Str						 iot_device_id;
	Dz1Str						 safety_signal_id_qty;
	C2CSafetySignalInfoList		*c2c_safety_signal_info_list;
} C2CIotDeviceListSignalEntry;

DZ1_CPPLINK DZ1_DLLPORT C2CIotDeviceListSignalEntry *C2CIotDeviceListSignalEntry_new(Dz1Str iot_device_id, 
																					 Dz1Str safety_signal_id_qty, 
																					 C2CSafetySignalInfoList *c2c_safety_signal_info_list, Dz1Error *err);
static __inline__ C2CIotDeviceListSignalEntry *C2CIotDeviceListSignalEntry_gen(Dz1Error *err) { return C2CIotDeviceListSignalEntry_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CIotDeviceListSignalEntry_copy(C2CIotDeviceListSignalEntry *dst, C2CIotDeviceListSignalEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CIotDeviceListSignalEntry *C2CIotDeviceListSignalEntry_clone(C2CIotDeviceListSignalEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignalEntry_purge(C2CIotDeviceListSignalEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignalEntry_del(C2CIotDeviceListSignalEntry *p);
static __inline__ void C2CIotDeviceListSignalEntry_delAndSetNull(void *ptr)
{
	C2CIotDeviceListSignalEntry **p = (C2CIotDeviceListSignalEntry **)ptr;
	if (p) { C2CIotDeviceListSignalEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignalEntry_dump(C2CIotDeviceListSignalEntry *p, int tab);
// C2CIotDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignal
typedef struct C2CIotDeviceListSignal
{
	void *storage;
	unsigned int (*count)(struct C2CIotDeviceListSignal *p);
	Dz1Error (*travel)(struct C2CIotDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CIotDeviceListSignalEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CIotDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CIotDeviceListSignalEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CIotDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CIotDeviceListSignalEntry *entry), void *ptr);
	C2CIotDeviceListSignalEntry **(*get_array)(struct C2CIotDeviceListSignal *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CIotDeviceListSignal *p, C2CIotDeviceListSignalEntry *data);
	C2CIotDeviceListSignalEntry *(*extract)(struct C2CIotDeviceListSignal *p, C2CIotDeviceListSignalEntry *ptr);
	C2CIotDeviceListSignalEntry *(*getHead)(struct C2CIotDeviceListSignal *p);
} C2CIotDeviceListSignal;

DZ1_CPPLINK DZ1_DLLPORT C2CIotDeviceListSignal *C2CIotDeviceListSignal_new(Dz1Error *err);
static __inline__ C2CIotDeviceListSignal *C2CIotDeviceListSignal_gen(Dz1Error *err) { return C2CIotDeviceListSignal_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CIotDeviceListSignal *C2CIotDeviceListSignal_clone(C2CIotDeviceListSignal *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignal_purge(C2CIotDeviceListSignal *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignal_del(C2CIotDeviceListSignal *p);
static __inline__ void C2CIotDeviceListSignal_delAndSetNull(void *ptr)
{
	C2CIotDeviceListSignal **p = (C2CIotDeviceListSignal **)ptr;
	if (p != NULL) { C2CIotDeviceListSignal_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CIotDeviceListSignal_dump(C2CIotDeviceListSignal *p, int tab);

// C2CIotDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignalEntry
typedef struct C2CImDeviceListSignalEntry
{
	Dz1Str						 iot_im_device_id;
	Dz1Str						 iot_device_id_qty;
	C2CIotDeviceListSignal		*c2c_iot_device_list;
} C2CImDeviceListSignalEntry;

DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceListSignalEntry *C2CImDeviceListSignalEntry_new(Dz1Str iot_im_device_id, 
																				   Dz1Str iot_device_id_qty, 
																				   C2CIotDeviceListSignal *c2c_iot_device_list, Dz1Error *err);
static __inline__ C2CImDeviceListSignalEntry *C2CImDeviceListSignalEntry_gen(Dz1Error *err) { return C2CImDeviceListSignalEntry_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CImDeviceListSignalEntry_copy(C2CImDeviceListSignalEntry *dst, C2CImDeviceListSignalEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceListSignalEntry *C2CImDeviceListSignalEntry_clone(C2CImDeviceListSignalEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignalEntry_purge(C2CImDeviceListSignalEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignalEntry_del(C2CImDeviceListSignalEntry *p);
static __inline__ void C2CImDeviceListSignalEntry_delAndSetNull(void *ptr)
{
	C2CImDeviceListSignalEntry **p = (C2CImDeviceListSignalEntry **)ptr;
	if (p) { C2CImDeviceListSignalEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignalEntry_dump(C2CImDeviceListSignalEntry *p, int tab);
// C2CImDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignal
typedef struct C2CImDeviceListSignal
{
	void *storage;
	unsigned int (*count)(struct C2CImDeviceListSignal *p);
	Dz1Error (*travel)(struct C2CImDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CImDeviceListSignalEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct C2CImDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CImDeviceListSignalEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct C2CImDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CImDeviceListSignalEntry *entry), void *ptr);
	C2CImDeviceListSignalEntry **(*get_array)(struct C2CImDeviceListSignal *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct C2CImDeviceListSignal *p, C2CImDeviceListSignalEntry *data);
	C2CImDeviceListSignalEntry *(*extract)(struct C2CImDeviceListSignal *p, C2CImDeviceListSignalEntry *ptr);
	C2CImDeviceListSignalEntry *(*getHead)(struct C2CImDeviceListSignal *p);
} C2CImDeviceListSignal;

DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceListSignal *C2CImDeviceListSignal_new(Dz1Error *err);
static __inline__ C2CImDeviceListSignal *C2CImDeviceListSignal_gen(Dz1Error *err) { return C2CImDeviceListSignal_new(err); }
DZ1_CPPLINK DZ1_DLLPORT C2CImDeviceListSignal *C2CImDeviceListSignal_clone(C2CImDeviceListSignal *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignal_purge(C2CImDeviceListSignal *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignal_del(C2CImDeviceListSignal *p);
static __inline__ void C2CImDeviceListSignal_delAndSetNull(void *ptr)
{
	C2CImDeviceListSignal **p = (C2CImDeviceListSignal **)ptr;
	if (p != NULL) { C2CImDeviceListSignal_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CImDeviceListSignal_dump(C2CImDeviceListSignal *p, int tab);

// C2CImDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfoData
typedef struct C2CSafetySignalListResponseInfoData
{
	Dz1Str						 local_center_id;
	Dz1Str						 event_name;
	Dz1Str						 event_type;
	Dz1Str						 iot_im_device_id_qty;
	C2CImDeviceListSignal		*c2c_im_device_list;
} C2CSafetySignalListResponseInfoData;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListResponseInfoData *C2CSafetySignalListResponseInfoData_new(Dz1Str local_center_id, 
																									 Dz1Str event_name, 
																									 Dz1Str event_type, 
																									 Dz1Str iot_im_device_id_qty, 
																									 C2CImDeviceListSignal *c2c_im_device_list, Dz1Error *err);
static __inline__ C2CSafetySignalListResponseInfoData *C2CSafetySignalListResponseInfoData_gen(Dz1Error *err) { return C2CSafetySignalListResponseInfoData_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CSafetySignalListResponseInfoData_copy(C2CSafetySignalListResponseInfoData *dst, C2CSafetySignalListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListResponseInfoData *C2CSafetySignalListResponseInfoData_clone(C2CSafetySignalListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfoData_purge(C2CSafetySignalListResponseInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfoData_del(C2CSafetySignalListResponseInfoData *p);
static __inline__ void C2CSafetySignalListResponseInfoData_delAndSetNull(void *ptr)
{
	C2CSafetySignalListResponseInfoData **p = (C2CSafetySignalListResponseInfoData **)ptr;
	if (p) { C2CSafetySignalListResponseInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfoData_dump(C2CSafetySignalListResponseInfoData *p, int tab);
// C2CSafetySignalListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfo
typedef struct C2CSafetySignalListResponseInfo
{
	Dz1Str									 command;
	C2CSafetySignalListResponseInfoData		*data;
} C2CSafetySignalListResponseInfo;

DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListResponseInfo *C2CSafetySignalListResponseInfo_new(Dz1Str command, 
																							 C2CSafetySignalListResponseInfoData *data, Dz1Error *err);
static __inline__ C2CSafetySignalListResponseInfo *C2CSafetySignalListResponseInfo_gen(Dz1Error *err) { return C2CSafetySignalListResponseInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t C2CSafetySignalListResponseInfo_copy(C2CSafetySignalListResponseInfo *dst, C2CSafetySignalListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT C2CSafetySignalListResponseInfo *C2CSafetySignalListResponseInfo_clone(C2CSafetySignalListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfo_purge(C2CSafetySignalListResponseInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfo_del(C2CSafetySignalListResponseInfo *p);
static __inline__ void C2CSafetySignalListResponseInfo_delAndSetNull(void *ptr)
{
	C2CSafetySignalListResponseInfo **p = (C2CSafetySignalListResponseInfo **)ptr;
	if (p) { C2CSafetySignalListResponseInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void C2CSafetySignalListResponseInfo_dump(C2CSafetySignalListResponseInfo *p, int tab);
// C2CSafetySignalListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1RequestData
typedef struct Itsk00126v1RequestData
{
	Dz1Str		local_center_id;
	Dz1Str		event_name;
	Dz1Str		event_type;
} Itsk00126v1RequestData;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1RequestData *Itsk00126v1RequestData_new(Dz1Str local_center_id, 
																		   Dz1Str event_name, 
																		   Dz1Str event_type, Dz1Error *err);
static __inline__ Itsk00126v1RequestData *Itsk00126v1RequestData_gen(Dz1Error *err) { return Itsk00126v1RequestData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1RequestData_copy(Itsk00126v1RequestData *dst, Itsk00126v1RequestData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1RequestData *Itsk00126v1RequestData_clone(Itsk00126v1RequestData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1RequestData_purge(Itsk00126v1RequestData *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1RequestData_del(Itsk00126v1RequestData *p);
static __inline__ void Itsk00126v1RequestData_delAndSetNull(void *ptr)
{
	Itsk00126v1RequestData **p = (Itsk00126v1RequestData **)ptr;
	if (p) { Itsk00126v1RequestData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1RequestData_dump(Itsk00126v1RequestData *p, int tab);
// Itsk00126v1RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Request
typedef struct Itsk00126v1Request
{
	Dz1Str						 command;
	Itsk00126v1RequestData		*data;
} Itsk00126v1Request;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Request *Itsk00126v1Request_new(Dz1Str command, 
																   Itsk00126v1RequestData *data, Dz1Error *err);
static __inline__ Itsk00126v1Request *Itsk00126v1Request_gen(Dz1Error *err) { return Itsk00126v1Request_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1Request_copy(Itsk00126v1Request *dst, Itsk00126v1Request *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1Request *Itsk00126v1Request_clone(Itsk00126v1Request *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Request_purge(Itsk00126v1Request *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Request_del(Itsk00126v1Request *p);
static __inline__ void Itsk00126v1Request_delAndSetNull(void *ptr)
{
	Itsk00126v1Request **p = (Itsk00126v1Request **)ptr;
	if (p) { Itsk00126v1Request_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1Request_dump(Itsk00126v1Request *p, int tab);
// Itsk00126v1Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1EAMPresent
typedef enum Itsk00126v1EAMPresent
{
	Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info,
	Itsk00126v1EAMPresent_c2c_iot_device_list_request_info,
	Itsk00126v1EAMPresent_c2c_iot_device_list_response_info,
	Itsk00126v1EAMPresent_c2c_iot_device_sttus_info,
	Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info,
	Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info,
	Itsk00126v1EAMPresent_max
} Itsk00126v1EAMPresent;

DZ1_CPPLINK str_t Itsk00126v1EAMPresentStrA(Itsk00126v1EAMPresent v);
DZ1_CPPLINK Itsk00126v1EAMPresent Itsk00126v1EAMPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1EAMPresentStrW(Itsk00126v1EAMPresent v);
DZ1_CPPLINK Itsk00126v1EAMPresent Itsk00126v1EAMPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1EAMPresentStr Itsk00126v1EAMPresentStrW
#define Itsk00126v1EAMPresentFromStr Itsk00126v1EAMPresentFromStrW
#else // UNICODE
#define Itsk00126v1EAMPresentStr Itsk00126v1EAMPresentStrA
#define Itsk00126v1EAMPresentFromStr Itsk00126v1EAMPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1EAMPresentStr Itsk00126v1EAMPresentStrA
#define Itsk00126v1EAMPresentFromStr Itsk00126v1EAMPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1EAMPresent *Itsk00126v1EAMPresent_new(Itsk00126v1EAMPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1EAMPresent *Itsk00126v1EAMPresent_gen(Dz1Error *err) { Itsk00126v1EAMPresent v = Itsk00126v1EAMPresent_max; return Itsk00126v1EAMPresent_new(&v, err); }
#define Itsk00126v1EAMPresent_clone             Itsk00126v1EAMPresent_new
static __inline__ void Itsk00126v1EAMPresent_del(Itsk00126v1EAMPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1EAMPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1EAMPresent **p = (Itsk00126v1EAMPresent **)ptr;
	if (p != NULL) { Itsk00126v1EAMPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1EAMPresent_dump(Itsk00126v1EAMPresent *v, int tab);
// Itsk00126v1EAMPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1EAM
typedef struct Itsk00126v1EAM
{
	Itsk00126v1EAMPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		C2CIoTImDeviceSttusInfo				*c2c_iot_im_device_sttus_info;
		Itsk00126v1Request					*c2c_iot_device_list_request_info;
		C2CIoTDeviceListResponseInfo		*c2c_iot_device_list_response_info;
		C2CIoTDeviceSttusInfo				*c2c_iot_device_sttus_info;
		Itsk00126v1Request					*c2c_safety_signal_list_request_info;
		C2CSafetySignalListResponseInfo		*c2c_safety_signal_list_response_info;
	} x;
} Itsk00126v1EAM;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1EAM *Itsk00126v1EAM_new(Itsk00126v1EAMPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1EAM *Itsk00126v1EAM_gen(Dz1Error *err) { return Itsk00126v1EAM_new(Itsk00126v1EAMPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v1EAM_copy(Itsk00126v1EAM *dst, Itsk00126v1EAM *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1EAM *Itsk00126v1EAM_clone(Itsk00126v1EAM *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1EAM_purge(Itsk00126v1EAM *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1EAM_del(Itsk00126v1EAM *p);
static __inline__ void Itsk00126v1EAM_delAndSetNull(void *ptr)
{
	Itsk00126v1EAM **p = (Itsk00126v1EAM **)ptr;
	if (p != NULL) { Itsk00126v1EAM_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1EAM_dump(Itsk00126v1EAM *p, int tab);
// Itsk00126v1EAM
////////////////////////////////////////////////////////////////////////////////

#endif
