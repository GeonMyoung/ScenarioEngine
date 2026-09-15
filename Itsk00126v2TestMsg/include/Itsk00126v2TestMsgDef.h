#ifndef _DZ1_TDC_ITSK00126V2_TEST_MSG_DEF_H_
#define _DZ1_TDC_ITSK00126V2_TEST_MSG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfoData
typedef struct F2CIoTImDeviceSttusInfoData
{
	Dz1Str		iot_im_device_id;
	Dz1Str		iot_im_device_link_sttus_code;
	Dz1Str		creat_dt;
} F2CIoTImDeviceSttusInfoData;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTImDeviceSttusInfoData *F2CIoTImDeviceSttusInfoData_new(Dz1Str iot_im_device_id, 
																					 Dz1Str iot_im_device_link_sttus_code, 
																					 Dz1Str creat_dt, Dz1Error *err);
static __inline__ F2CIoTImDeviceSttusInfoData *F2CIoTImDeviceSttusInfoData_gen(Dz1Error *err) { return F2CIoTImDeviceSttusInfoData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTImDeviceSttusInfoData_copy(F2CIoTImDeviceSttusInfoData *dst, F2CIoTImDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTImDeviceSttusInfoData *F2CIoTImDeviceSttusInfoData_clone(F2CIoTImDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfoData_purge(F2CIoTImDeviceSttusInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfoData_del(F2CIoTImDeviceSttusInfoData *p);
static __inline__ void F2CIoTImDeviceSttusInfoData_delAndSetNull(void *ptr)
{
	F2CIoTImDeviceSttusInfoData **p = (F2CIoTImDeviceSttusInfoData **)ptr;
	if (p) { F2CIoTImDeviceSttusInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfoData_dump(F2CIoTImDeviceSttusInfoData *p, int tab);
// F2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfo
typedef struct F2CIoTImDeviceSttusInfo
{
	Dz1Str							 command;
	F2CIoTImDeviceSttusInfoData		*data;
} F2CIoTImDeviceSttusInfo;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTImDeviceSttusInfo *F2CIoTImDeviceSttusInfo_new(Dz1Str command, 
																			 F2CIoTImDeviceSttusInfoData *data, Dz1Error *err);
static __inline__ F2CIoTImDeviceSttusInfo *F2CIoTImDeviceSttusInfo_gen(Dz1Error *err) { return F2CIoTImDeviceSttusInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTImDeviceSttusInfo_copy(F2CIoTImDeviceSttusInfo *dst, F2CIoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTImDeviceSttusInfo *F2CIoTImDeviceSttusInfo_clone(F2CIoTImDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfo_purge(F2CIoTImDeviceSttusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfo_del(F2CIoTImDeviceSttusInfo *p);
static __inline__ void F2CIoTImDeviceSttusInfo_delAndSetNull(void *ptr)
{
	F2CIoTImDeviceSttusInfo **p = (F2CIoTImDeviceSttusInfo **)ptr;
	if (p) { F2CIoTImDeviceSttusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTImDeviceSttusInfo_dump(F2CIoTImDeviceSttusInfo *p, int tab);
// F2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceEntry
typedef struct F2CIoTDeviceEntry
{
	Dz1Str		iot_device_id;
} F2CIoTDeviceEntry;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceEntry *F2CIoTDeviceEntry_new(Dz1Str iot_device_id, Dz1Error *err);
static __inline__ F2CIoTDeviceEntry *F2CIoTDeviceEntry_gen(Dz1Error *err) { return F2CIoTDeviceEntry_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceEntry_copy(F2CIoTDeviceEntry *dst, F2CIoTDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceEntry *F2CIoTDeviceEntry_clone(F2CIoTDeviceEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceEntry_purge(F2CIoTDeviceEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceEntry_del(F2CIoTDeviceEntry *p);
static __inline__ void F2CIoTDeviceEntry_delAndSetNull(void *ptr)
{
	F2CIoTDeviceEntry **p = (F2CIoTDeviceEntry **)ptr;
	if (p) { F2CIoTDeviceEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceEntry_dump(F2CIoTDeviceEntry *p, int tab);
// F2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceList
typedef struct F2CIoTDeviceList
{
	void *storage;
	unsigned int (*count)(struct F2CIoTDeviceList *p);
	Dz1Error (*travel)(struct F2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct F2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct F2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceEntry *entry), void *ptr);
	F2CIoTDeviceEntry **(*get_array)(struct F2CIoTDeviceList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct F2CIoTDeviceList *p, F2CIoTDeviceEntry *data);
	F2CIoTDeviceEntry *(*extract)(struct F2CIoTDeviceList *p, F2CIoTDeviceEntry *ptr);
	F2CIoTDeviceEntry *(*getHead)(struct F2CIoTDeviceList *p);
} F2CIoTDeviceList;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceList *F2CIoTDeviceList_new(Dz1Error *err);
static __inline__ F2CIoTDeviceList *F2CIoTDeviceList_gen(Dz1Error *err) { return F2CIoTDeviceList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceList *F2CIoTDeviceList_clone(F2CIoTDeviceList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceList_purge(F2CIoTDeviceList *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceList_del(F2CIoTDeviceList *p);
static __inline__ void F2CIoTDeviceList_delAndSetNull(void *ptr)
{
	F2CIoTDeviceList **p = (F2CIoTDeviceList **)ptr;
	if (p != NULL) { F2CIoTDeviceList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceList_dump(F2CIoTDeviceList *p, int tab);

// F2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfoData
typedef struct F2CIoTDeviceListResponseInfoData
{
	Dz1Str				 iot_im_device_id;
	Dz1Str				 event_name;
	Dz1Str				 event_type;
	Dz1Str				 iot_device_id_qty;
	F2CIoTDeviceList	*iot_device_list;
} F2CIoTDeviceListResponseInfoData;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceListResponseInfoData *F2CIoTDeviceListResponseInfoData_new(Dz1Str iot_im_device_id, 
																							   Dz1Str event_name, 
																							   Dz1Str event_type, 
																							   Dz1Str iot_device_id_qty, 
																							   F2CIoTDeviceList *iot_device_list, Dz1Error *err);
static __inline__ F2CIoTDeviceListResponseInfoData *F2CIoTDeviceListResponseInfoData_gen(Dz1Error *err) { return F2CIoTDeviceListResponseInfoData_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceListResponseInfoData_copy(F2CIoTDeviceListResponseInfoData *dst, F2CIoTDeviceListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceListResponseInfoData *F2CIoTDeviceListResponseInfoData_clone(F2CIoTDeviceListResponseInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfoData_purge(F2CIoTDeviceListResponseInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfoData_del(F2CIoTDeviceListResponseInfoData *p);
static __inline__ void F2CIoTDeviceListResponseInfoData_delAndSetNull(void *ptr)
{
	F2CIoTDeviceListResponseInfoData **p = (F2CIoTDeviceListResponseInfoData **)ptr;
	if (p) { F2CIoTDeviceListResponseInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfoData_dump(F2CIoTDeviceListResponseInfoData *p, int tab);
// F2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfo
typedef struct F2CIoTDeviceListResponseInfo
{
	Dz1Str								 command;
	F2CIoTDeviceListResponseInfoData	*data;
} F2CIoTDeviceListResponseInfo;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceListResponseInfo *F2CIoTDeviceListResponseInfo_new(Dz1Str command, 
																					   F2CIoTDeviceListResponseInfoData *data, Dz1Error *err);
static __inline__ F2CIoTDeviceListResponseInfo *F2CIoTDeviceListResponseInfo_gen(Dz1Error *err) { return F2CIoTDeviceListResponseInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceListResponseInfo_copy(F2CIoTDeviceListResponseInfo *dst, F2CIoTDeviceListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceListResponseInfo *F2CIoTDeviceListResponseInfo_clone(F2CIoTDeviceListResponseInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfo_purge(F2CIoTDeviceListResponseInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfo_del(F2CIoTDeviceListResponseInfo *p);
static __inline__ void F2CIoTDeviceListResponseInfo_delAndSetNull(void *ptr)
{
	F2CIoTDeviceListResponseInfo **p = (F2CIoTDeviceListResponseInfo **)ptr;
	if (p) { F2CIoTDeviceListResponseInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceListResponseInfo_dump(F2CIoTDeviceListResponseInfo *p, int tab);
// F2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIotDeviceListResetInfoData
typedef struct F2CIotDeviceListResetInfoData
{
	Dz1Str				 iot_im_device_id;
	Dz1Str				 iot_device_id_qty;
	F2CIoTDeviceList	*iot_device_update_list;
	Dz1Str				 creat_dt;
} F2CIotDeviceListResetInfoData;

DZ1_CPPLINK DZ1_DLLPORT F2CIotDeviceListResetInfoData *F2CIotDeviceListResetInfoData_new(Dz1Str iot_im_device_id, 
																						 Dz1Str iot_device_id_qty, 
																						 F2CIoTDeviceList *iot_device_update_list, 
																						 Dz1Str creat_dt, Dz1Error *err);
static __inline__ F2CIotDeviceListResetInfoData *F2CIotDeviceListResetInfoData_gen(Dz1Error *err) { return F2CIotDeviceListResetInfoData_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIotDeviceListResetInfoData_copy(F2CIotDeviceListResetInfoData *dst, F2CIotDeviceListResetInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIotDeviceListResetInfoData *F2CIotDeviceListResetInfoData_clone(F2CIotDeviceListResetInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfoData_purge(F2CIotDeviceListResetInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfoData_del(F2CIotDeviceListResetInfoData *p);
static __inline__ void F2CIotDeviceListResetInfoData_delAndSetNull(void *ptr)
{
	F2CIotDeviceListResetInfoData **p = (F2CIotDeviceListResetInfoData **)ptr;
	if (p) { F2CIotDeviceListResetInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfoData_dump(F2CIotDeviceListResetInfoData *p, int tab);
// F2CIotDeviceListResetInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIotDeviceListResetInfo
typedef struct F2CIotDeviceListResetInfo
{
	Dz1Str								 command;
	F2CIotDeviceListResetInfoData		*data;
} F2CIotDeviceListResetInfo;

DZ1_CPPLINK DZ1_DLLPORT F2CIotDeviceListResetInfo *F2CIotDeviceListResetInfo_new(Dz1Str command, 
																				 F2CIotDeviceListResetInfoData *data, Dz1Error *err);
static __inline__ F2CIotDeviceListResetInfo *F2CIotDeviceListResetInfo_gen(Dz1Error *err) { return F2CIotDeviceListResetInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIotDeviceListResetInfo_copy(F2CIotDeviceListResetInfo *dst, F2CIotDeviceListResetInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIotDeviceListResetInfo *F2CIotDeviceListResetInfo_clone(F2CIotDeviceListResetInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfo_purge(F2CIotDeviceListResetInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfo_del(F2CIotDeviceListResetInfo *p);
static __inline__ void F2CIotDeviceListResetInfo_delAndSetNull(void *ptr)
{
	F2CIotDeviceListResetInfo **p = (F2CIotDeviceListResetInfo **)ptr;
	if (p) { F2CIotDeviceListResetInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIotDeviceListResetInfo_dump(F2CIotDeviceListResetInfo *p, int tab);
// F2CIotDeviceListResetInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoEntry
typedef struct F2CIoTDeviceSttusInfoEntry
{
	Dz1Str		iot_device_id;
	Dz1Str		iot_device_sttus_code;
	Dz1Str		btry_sttus_code;
	Dz1Str		link_sttus_code;
	s64_t		data_trnsmis_cont;
} F2CIoTDeviceSttusInfoEntry;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoEntry_new(Dz1Str iot_device_id, 
																				   Dz1Str iot_device_sttus_code, 
																				   Dz1Str btry_sttus_code, 
																				   Dz1Str link_sttus_code, 
																				   s64_t data_trnsmis_cont, Dz1Error *err);
static __inline__ F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoEntry_gen(Dz1Error *err) { return F2CIoTDeviceSttusInfoEntry_new(NULL, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceSttusInfoEntry_copy(F2CIoTDeviceSttusInfoEntry *dst, F2CIoTDeviceSttusInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoEntry_clone(F2CIoTDeviceSttusInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoEntry_purge(F2CIoTDeviceSttusInfoEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoEntry_del(F2CIoTDeviceSttusInfoEntry *p);
static __inline__ void F2CIoTDeviceSttusInfoEntry_delAndSetNull(void *ptr)
{
	F2CIoTDeviceSttusInfoEntry **p = (F2CIoTDeviceSttusInfoEntry **)ptr;
	if (p) { F2CIoTDeviceSttusInfoEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoEntry_dump(F2CIoTDeviceSttusInfoEntry *p, int tab);
// F2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoList
typedef struct F2CIoTDeviceSttusInfoList
{
	void *storage;
	unsigned int (*count)(struct F2CIoTDeviceSttusInfoList *p);
	Dz1Error (*travel)(struct F2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct F2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct F2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceSttusInfoEntry *entry), void *ptr);
	F2CIoTDeviceSttusInfoEntry **(*get_array)(struct F2CIoTDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct F2CIoTDeviceSttusInfoList *p, F2CIoTDeviceSttusInfoEntry *data);
	F2CIoTDeviceSttusInfoEntry *(*extract)(struct F2CIoTDeviceSttusInfoList *p, F2CIoTDeviceSttusInfoEntry *ptr);
	F2CIoTDeviceSttusInfoEntry *(*getHead)(struct F2CIoTDeviceSttusInfoList *p);
} F2CIoTDeviceSttusInfoList;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoList *F2CIoTDeviceSttusInfoList_new(Dz1Error *err);
static __inline__ F2CIoTDeviceSttusInfoList *F2CIoTDeviceSttusInfoList_gen(Dz1Error *err) { return F2CIoTDeviceSttusInfoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoList *F2CIoTDeviceSttusInfoList_clone(F2CIoTDeviceSttusInfoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoList_purge(F2CIoTDeviceSttusInfoList *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoList_del(F2CIoTDeviceSttusInfoList *p);
static __inline__ void F2CIoTDeviceSttusInfoList_delAndSetNull(void *ptr)
{
	F2CIoTDeviceSttusInfoList **p = (F2CIoTDeviceSttusInfoList **)ptr;
	if (p != NULL) { F2CIoTDeviceSttusInfoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoList_dump(F2CIoTDeviceSttusInfoList *p, int tab);

// F2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoData
typedef struct F2CIoTDeviceSttusInfoData
{
	Dz1Str							 iot_im_device_id;
	Dz1Str							 iot_device_id_qty;
	F2CIoTDeviceSttusInfoList		*iot_device_sttus_info_list;
	Dz1Str							 creat_dt;
} F2CIoTDeviceSttusInfoData;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoData *F2CIoTDeviceSttusInfoData_new(Dz1Str iot_im_device_id, 
																				 Dz1Str iot_device_id_qty, 
																				 F2CIoTDeviceSttusInfoList *iot_device_sttus_info_list, 
																				 Dz1Str creat_dt, Dz1Error *err);
static __inline__ F2CIoTDeviceSttusInfoData *F2CIoTDeviceSttusInfoData_gen(Dz1Error *err) { return F2CIoTDeviceSttusInfoData_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceSttusInfoData_copy(F2CIoTDeviceSttusInfoData *dst, F2CIoTDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfoData *F2CIoTDeviceSttusInfoData_clone(F2CIoTDeviceSttusInfoData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoData_purge(F2CIoTDeviceSttusInfoData *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoData_del(F2CIoTDeviceSttusInfoData *p);
static __inline__ void F2CIoTDeviceSttusInfoData_delAndSetNull(void *ptr)
{
	F2CIoTDeviceSttusInfoData **p = (F2CIoTDeviceSttusInfoData **)ptr;
	if (p) { F2CIoTDeviceSttusInfoData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfoData_dump(F2CIoTDeviceSttusInfoData *p, int tab);
// F2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfo
typedef struct F2CIoTDeviceSttusInfo
{
	Dz1Str							 command;
	F2CIoTDeviceSttusInfoData		*data;
} F2CIoTDeviceSttusInfo;

DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfo *F2CIoTDeviceSttusInfo_new(Dz1Str command, 
																		 F2CIoTDeviceSttusInfoData *data, Dz1Error *err);
static __inline__ F2CIoTDeviceSttusInfo *F2CIoTDeviceSttusInfo_gen(Dz1Error *err) { return F2CIoTDeviceSttusInfo_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t F2CIoTDeviceSttusInfo_copy(F2CIoTDeviceSttusInfo *dst, F2CIoTDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT F2CIoTDeviceSttusInfo *F2CIoTDeviceSttusInfo_clone(F2CIoTDeviceSttusInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfo_purge(F2CIoTDeviceSttusInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfo_del(F2CIoTDeviceSttusInfo *p);
static __inline__ void F2CIoTDeviceSttusInfo_delAndSetNull(void *ptr)
{
	F2CIoTDeviceSttusInfo **p = (F2CIoTDeviceSttusInfo **)ptr;
	if (p) { F2CIoTDeviceSttusInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void F2CIoTDeviceSttusInfo_dump(F2CIoTDeviceSttusInfo *p, int tab);
// F2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2RequestData
typedef struct Itsk00126v2RequestData
{
	Dz1Str		iot_im_device_id;
	Dz1Str		event_name;
	Dz1Str		event_type;
} Itsk00126v2RequestData;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2RequestData *Itsk00126v2RequestData_new(Dz1Str iot_im_device_id, 
																		   Dz1Str event_name, 
																		   Dz1Str event_type, Dz1Error *err);
static __inline__ Itsk00126v2RequestData *Itsk00126v2RequestData_gen(Dz1Error *err) { return Itsk00126v2RequestData_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2RequestData_copy(Itsk00126v2RequestData *dst, Itsk00126v2RequestData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2RequestData *Itsk00126v2RequestData_clone(Itsk00126v2RequestData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2RequestData_purge(Itsk00126v2RequestData *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2RequestData_del(Itsk00126v2RequestData *p);
static __inline__ void Itsk00126v2RequestData_delAndSetNull(void *ptr)
{
	Itsk00126v2RequestData **p = (Itsk00126v2RequestData **)ptr;
	if (p) { Itsk00126v2RequestData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2RequestData_dump(Itsk00126v2RequestData *p, int tab);
// Itsk00126v2RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Request
typedef struct Itsk00126v2Request
{
	Dz1Str						 command;
	Itsk00126v2RequestData		*data;
} Itsk00126v2Request;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2Request *Itsk00126v2Request_new(Dz1Str command, 
																   Itsk00126v2RequestData *data, Dz1Error *err);
static __inline__ Itsk00126v2Request *Itsk00126v2Request_gen(Dz1Error *err) { return Itsk00126v2Request_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2Request_copy(Itsk00126v2Request *dst, Itsk00126v2Request *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2Request *Itsk00126v2Request_clone(Itsk00126v2Request *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Request_purge(Itsk00126v2Request *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Request_del(Itsk00126v2Request *p);
static __inline__ void Itsk00126v2Request_delAndSetNull(void *ptr)
{
	Itsk00126v2Request **p = (Itsk00126v2Request **)ptr;
	if (p) { Itsk00126v2Request_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2Request_dump(Itsk00126v2Request *p, int tab);
// Itsk00126v2Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2EAMPresent
typedef enum Itsk00126v2EAMPresent
{
	Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info,
	Itsk00126v2EAMPresent_fc2_iot_device_list_request_info,
	Itsk00126v2EAMPresent_fc2_iot_device_list_response_info,
	Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info,
	Itsk00126v2EAMPresent_fc2_iot_device_sttus_info,
	Itsk00126v2EAMPresent_max
} Itsk00126v2EAMPresent;

DZ1_CPPLINK str_t Itsk00126v2EAMPresentStrA(Itsk00126v2EAMPresent v);
DZ1_CPPLINK Itsk00126v2EAMPresent Itsk00126v2EAMPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2EAMPresentStrW(Itsk00126v2EAMPresent v);
DZ1_CPPLINK Itsk00126v2EAMPresent Itsk00126v2EAMPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2EAMPresentStr Itsk00126v2EAMPresentStrW
#define Itsk00126v2EAMPresentFromStr Itsk00126v2EAMPresentFromStrW
#else // UNICODE
#define Itsk00126v2EAMPresentStr Itsk00126v2EAMPresentStrA
#define Itsk00126v2EAMPresentFromStr Itsk00126v2EAMPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2EAMPresentStr Itsk00126v2EAMPresentStrA
#define Itsk00126v2EAMPresentFromStr Itsk00126v2EAMPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2EAMPresent *Itsk00126v2EAMPresent_new(Itsk00126v2EAMPresent *src, Dz1Error *err);
static __inline__ Itsk00126v2EAMPresent *Itsk00126v2EAMPresent_gen(Dz1Error *err) { Itsk00126v2EAMPresent v = Itsk00126v2EAMPresent_max; return Itsk00126v2EAMPresent_new(&v, err); }
#define Itsk00126v2EAMPresent_clone             Itsk00126v2EAMPresent_new
static __inline__ void Itsk00126v2EAMPresent_del(Itsk00126v2EAMPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2EAMPresent_delAndSetNull(void *ptr)
{
	Itsk00126v2EAMPresent **p = (Itsk00126v2EAMPresent **)ptr;
	if (p != NULL) { Itsk00126v2EAMPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2EAMPresent_dump(Itsk00126v2EAMPresent *v, int tab);
// Itsk00126v2EAMPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2EAM
typedef struct Itsk00126v2EAM
{
	Itsk00126v2EAMPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		F2CIoTImDeviceSttusInfo			*f2c_iot_im_device_sttus_info;
		Itsk00126v2Request				*fc2_iot_device_list_request_info;
		F2CIoTDeviceListResponseInfo	*fc2_iot_device_list_response_info;
		F2CIoTDeviceListResponseInfo	*fc2_iot_device_list_reset_info;
		F2CIoTDeviceSttusInfo			*fc2_iot_device_sttus_info;
	} x;
} Itsk00126v2EAM;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2EAM *Itsk00126v2EAM_new(Itsk00126v2EAMPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v2EAM *Itsk00126v2EAM_gen(Dz1Error *err) { return Itsk00126v2EAM_new(Itsk00126v2EAMPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v2EAM_copy(Itsk00126v2EAM *dst, Itsk00126v2EAM *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2EAM *Itsk00126v2EAM_clone(Itsk00126v2EAM *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2EAM_purge(Itsk00126v2EAM *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2EAM_del(Itsk00126v2EAM *p);
static __inline__ void Itsk00126v2EAM_delAndSetNull(void *ptr)
{
	Itsk00126v2EAM **p = (Itsk00126v2EAM **)ptr;
	if (p != NULL) { Itsk00126v2EAM_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2EAM_dump(Itsk00126v2EAM *p, int tab);
// Itsk00126v2EAM
////////////////////////////////////////////////////////////////////////////////

#endif
