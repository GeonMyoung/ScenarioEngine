#ifndef _DZ1_TDC_TECHNICAL_REGULATION1_DEF_H_
#define _DZ1_TDC_TECHNICAL_REGULATION1_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateEntry
typedef struct CurrentLinkStateEntry
{
	Dz1Str		link_id;
	u16_t		speed_rate;
	u32_t		volume_rate;
	u16_t		density_rate;
	u16_t		ttime_qty;
	u16_t		delay_qty;
	u32_t		veh_q_len_qty;
	u8_t		tfdt_occupy_percent;
} CurrentLinkStateEntry;

DZ1_CPPLINK DZ1_DLLPORT CurrentLinkStateEntry *CurrentLinkStateEntry_new(Dz1Str link_id, 
																		 u16_t speed_rate, 
																		 u8_t tfdt_occupy_percent, Dz1Error *err);
static __inline__ CurrentLinkStateEntry *CurrentLinkStateEntry_gen(Dz1Error *err) { return CurrentLinkStateEntry_new(NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CurrentLinkStateEntry_copy(CurrentLinkStateEntry *dst, CurrentLinkStateEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CurrentLinkStateEntry *CurrentLinkStateEntry_clone(CurrentLinkStateEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateEntry_purge(CurrentLinkStateEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateEntry_del(CurrentLinkStateEntry *p);
static __inline__ void CurrentLinkStateEntry_delAndSetNull(void *ptr)
{
	CurrentLinkStateEntry **p = (CurrentLinkStateEntry **)ptr;
	if (p) { CurrentLinkStateEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateEntry_dump(CurrentLinkStateEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int CurrentLinkStateEntry_cmp(CurrentLinkStateEntry *a, CurrentLinkStateEntry *b); 
// CurrentLinkStateEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateList
typedef struct CurrentLinkStateList
{
	void *storage;
	unsigned int (*count)(struct CurrentLinkStateList *p);
	Dz1Error (*travel)(struct CurrentLinkStateList *p, Dz1Error (*func)(void *ptr, CurrentLinkStateEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct CurrentLinkStateList *p, Dz1Error (*func)(void *ptr, CurrentLinkStateEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct CurrentLinkStateList *p, Dz1Error (*func)(void *ptr, CurrentLinkStateEntry *entry), void *ptr);
	CurrentLinkStateEntry **(*get_array)(struct CurrentLinkStateList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct CurrentLinkStateList *p, CurrentLinkStateEntry *data);
	bool_t (*remove)(struct CurrentLinkStateList *p, CurrentLinkStateEntry *key);
	CurrentLinkStateEntry *(*extract)(struct CurrentLinkStateList *p, CurrentLinkStateEntry *key);
	CurrentLinkStateEntry *(*find)(struct CurrentLinkStateList *p, CurrentLinkStateEntry *key);
	CurrentLinkStateEntry *(*getHead)(struct CurrentLinkStateList *p);
	int (*cmp)(CurrentLinkStateEntry *a, CurrentLinkStateEntry *b);
} CurrentLinkStateList;

DZ1_CPPLINK DZ1_DLLPORT CurrentLinkStateList *CurrentLinkStateList_new(Dz1Error *err);
static __inline__ CurrentLinkStateList *CurrentLinkStateList_gen(Dz1Error *err) { return CurrentLinkStateList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT CurrentLinkStateList *CurrentLinkStateList_clone(CurrentLinkStateList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateList_purge(CurrentLinkStateList *p);
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateList_del(CurrentLinkStateList *p);
static __inline__ void CurrentLinkStateList_delAndSetNull(void *ptr)
{
	CurrentLinkStateList **p = (CurrentLinkStateList **)ptr;
	if (p != NULL) { CurrentLinkStateList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CurrentLinkStateList_dump(CurrentLinkStateList *p, int tab);

// CurrentLinkStateList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityEntry
typedef struct EventIdentityEntry
{
	Dz1Str		 node_id;
	Dz1Str		 link_id;
	u32_t		 identification_num;
	Dz1Str		 loc_jurisdiction_name;
	Dz1Str		 loc_link_id;
	Dz1Str		 loc_node_id;
	Dz1Str		 loc_roadway_name;
	u8_t		 evnt_code;
	u8_t		 special_evnt_code;
	u8_t		 planned_road_closure_code;
	u8_t		 lanes_blocked_or_closed_num;
	u8_t		*lanes_shoulder_block_code;
	Dz1Str		 start_time;
	Dz1Str		 end_time;
	u32_t		 time_duration;
} EventIdentityEntry;

DZ1_CPPLINK DZ1_DLLPORT EventIdentityEntry *EventIdentityEntry_new(Dz1Str node_id, 
																   Dz1Str link_id, 
																   Dz1Str loc_jurisdiction_name, 
																   Dz1Str loc_link_id, 
																   Dz1Str loc_node_id, 
																   Dz1Str loc_roadway_name, 
																   u8_t lanes_blocked_or_closed_num, 
																   u8_t *lanes_shoulder_block_code, 
																   Dz1Str start_time, 
																   Dz1Str end_time, 
																   u32_t time_duration, Dz1Error *err);
static __inline__ EventIdentityEntry *EventIdentityEntry_gen(Dz1Error *err) { return EventIdentityEntry_new(NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t EventIdentityEntry_copy(EventIdentityEntry *dst, EventIdentityEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT EventIdentityEntry *EventIdentityEntry_clone(EventIdentityEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityEntry_purge(EventIdentityEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityEntry_del(EventIdentityEntry *p);
static __inline__ void EventIdentityEntry_delAndSetNull(void *ptr)
{
	EventIdentityEntry **p = (EventIdentityEntry **)ptr;
	if (p) { EventIdentityEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityEntry_dump(EventIdentityEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int EventIdentityEntry_cmp(EventIdentityEntry *a, EventIdentityEntry *b); 
// EventIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityList
typedef struct EventIdentityList
{
	void *storage;
	unsigned int (*count)(struct EventIdentityList *p);
	Dz1Error (*travel)(struct EventIdentityList *p, Dz1Error (*func)(void *ptr, EventIdentityEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct EventIdentityList *p, Dz1Error (*func)(void *ptr, EventIdentityEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct EventIdentityList *p, Dz1Error (*func)(void *ptr, EventIdentityEntry *entry), void *ptr);
	EventIdentityEntry **(*get_array)(struct EventIdentityList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct EventIdentityList *p, EventIdentityEntry *data);
	bool_t (*remove)(struct EventIdentityList *p, EventIdentityEntry *key);
	EventIdentityEntry *(*extract)(struct EventIdentityList *p, EventIdentityEntry *key);
	EventIdentityEntry *(*find)(struct EventIdentityList *p, EventIdentityEntry *key);
	EventIdentityEntry *(*getHead)(struct EventIdentityList *p);
	int (*cmp)(EventIdentityEntry *a, EventIdentityEntry *b);
} EventIdentityList;

DZ1_CPPLINK DZ1_DLLPORT EventIdentityList *EventIdentityList_new(Dz1Error *err);
static __inline__ EventIdentityList *EventIdentityList_gen(Dz1Error *err) { return EventIdentityList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT EventIdentityList *EventIdentityList_clone(EventIdentityList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityList_purge(EventIdentityList *p);
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityList_del(EventIdentityList *p);
static __inline__ void EventIdentityList_delAndSetNull(void *ptr)
{
	EventIdentityList **p = (EventIdentityList **)ptr;
	if (p != NULL) { EventIdentityList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void EventIdentityList_dump(EventIdentityList *p, int tab);

// EventIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityEntry
typedef struct IncidentIdentityEntry
{
	Dz1Str		node_id;
	Dz1Str		link_id;
	u16_t		loc_offset_begin;
	u16_t		loc_offset_end;
	Dz1Str		update_time;
	u8_t		fatality_cnt;
	u8_t		injuries_cnt;
	u8_t		property_damage_code;
	Dz1Str		property_damage_desc;
} IncidentIdentityEntry;

DZ1_CPPLINK DZ1_DLLPORT IncidentIdentityEntry *IncidentIdentityEntry_new(Dz1Str node_id, 
																		 Dz1Str link_id, 
																		 Dz1Str update_time, 
																		 u8_t property_damage_code, Dz1Error *err);
static __inline__ IncidentIdentityEntry *IncidentIdentityEntry_gen(Dz1Error *err) { return IncidentIdentityEntry_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t IncidentIdentityEntry_copy(IncidentIdentityEntry *dst, IncidentIdentityEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT IncidentIdentityEntry *IncidentIdentityEntry_clone(IncidentIdentityEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityEntry_purge(IncidentIdentityEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityEntry_del(IncidentIdentityEntry *p);
static __inline__ void IncidentIdentityEntry_delAndSetNull(void *ptr)
{
	IncidentIdentityEntry **p = (IncidentIdentityEntry **)ptr;
	if (p) { IncidentIdentityEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityEntry_dump(IncidentIdentityEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int IncidentIdentityEntry_cmp(IncidentIdentityEntry *a, IncidentIdentityEntry *b); 
// IncidentIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityList
typedef struct IncidentIdentityList
{
	void *storage;
	unsigned int (*count)(struct IncidentIdentityList *p);
	Dz1Error (*travel)(struct IncidentIdentityList *p, Dz1Error (*func)(void *ptr, IncidentIdentityEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct IncidentIdentityList *p, Dz1Error (*func)(void *ptr, IncidentIdentityEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct IncidentIdentityList *p, Dz1Error (*func)(void *ptr, IncidentIdentityEntry *entry), void *ptr);
	IncidentIdentityEntry **(*get_array)(struct IncidentIdentityList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct IncidentIdentityList *p, IncidentIdentityEntry *data);
	bool_t (*remove)(struct IncidentIdentityList *p, IncidentIdentityEntry *key);
	IncidentIdentityEntry *(*extract)(struct IncidentIdentityList *p, IncidentIdentityEntry *key);
	IncidentIdentityEntry *(*find)(struct IncidentIdentityList *p, IncidentIdentityEntry *key);
	IncidentIdentityEntry *(*getHead)(struct IncidentIdentityList *p);
	int (*cmp)(IncidentIdentityEntry *a, IncidentIdentityEntry *b);
} IncidentIdentityList;

DZ1_CPPLINK DZ1_DLLPORT IncidentIdentityList *IncidentIdentityList_new(Dz1Error *err);
static __inline__ IncidentIdentityList *IncidentIdentityList_gen(Dz1Error *err) { return IncidentIdentityList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT IncidentIdentityList *IncidentIdentityList_clone(IncidentIdentityList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityList_purge(IncidentIdentityList *p);
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityList_del(IncidentIdentityList *p);
static __inline__ void IncidentIdentityList_delAndSetNull(void *ptr)
{
	IncidentIdentityList **p = (IncidentIdentityList **)ptr;
	if (p != NULL) { IncidentIdentityList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IncidentIdentityList_dump(IncidentIdentityList *p, int tab);

// IncidentIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsEntry
typedef struct IncidentConditionsEntry
{
	Dz1Str		node_id;
	Dz1Str		link_id;
	Dz1Str		contact_org_name;
	u8_t		incident_code;
	Dz1Str		other_incident_desc;
	u8_t		veh_invloved_code;
	Dz1Str		other_veh_invloved_desc;
	u8_t		status_code;
	Dz1Str		other_status_desc;
	u8_t		update_type_code;
	Dz1Str		other_update_desc;
} IncidentConditionsEntry;

DZ1_CPPLINK DZ1_DLLPORT IncidentConditionsEntry *IncidentConditionsEntry_new(Dz1Str node_id, 
																			 Dz1Str link_id, 
																			 Dz1Str contact_org_name, 
																			 u8_t incident_code, 
																			 u8_t veh_invloved_code, 
																			 u8_t status_code, 
																			 u8_t update_type_code, Dz1Error *err);
static __inline__ IncidentConditionsEntry *IncidentConditionsEntry_gen(Dz1Error *err) { return IncidentConditionsEntry_new(NULL, NULL, NULL, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t IncidentConditionsEntry_copy(IncidentConditionsEntry *dst, IncidentConditionsEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT IncidentConditionsEntry *IncidentConditionsEntry_clone(IncidentConditionsEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsEntry_purge(IncidentConditionsEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsEntry_del(IncidentConditionsEntry *p);
static __inline__ void IncidentConditionsEntry_delAndSetNull(void *ptr)
{
	IncidentConditionsEntry **p = (IncidentConditionsEntry **)ptr;
	if (p) { IncidentConditionsEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsEntry_dump(IncidentConditionsEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int IncidentConditionsEntry_cmp(IncidentConditionsEntry *a, IncidentConditionsEntry *b); 
// IncidentConditionsEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsList
typedef struct IncidentConditionsList
{
	void *storage;
	unsigned int (*count)(struct IncidentConditionsList *p);
	Dz1Error (*travel)(struct IncidentConditionsList *p, Dz1Error (*func)(void *ptr, IncidentConditionsEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct IncidentConditionsList *p, Dz1Error (*func)(void *ptr, IncidentConditionsEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct IncidentConditionsList *p, Dz1Error (*func)(void *ptr, IncidentConditionsEntry *entry), void *ptr);
	IncidentConditionsEntry **(*get_array)(struct IncidentConditionsList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct IncidentConditionsList *p, IncidentConditionsEntry *data);
	bool_t (*remove)(struct IncidentConditionsList *p, IncidentConditionsEntry *key);
	IncidentConditionsEntry *(*extract)(struct IncidentConditionsList *p, IncidentConditionsEntry *key);
	IncidentConditionsEntry *(*find)(struct IncidentConditionsList *p, IncidentConditionsEntry *key);
	IncidentConditionsEntry *(*getHead)(struct IncidentConditionsList *p);
	int (*cmp)(IncidentConditionsEntry *a, IncidentConditionsEntry *b);
} IncidentConditionsList;

DZ1_CPPLINK DZ1_DLLPORT IncidentConditionsList *IncidentConditionsList_new(Dz1Error *err);
static __inline__ IncidentConditionsList *IncidentConditionsList_gen(Dz1Error *err) { return IncidentConditionsList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT IncidentConditionsList *IncidentConditionsList_clone(IncidentConditionsList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsList_purge(IncidentConditionsList *p);
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsList_del(IncidentConditionsList *p);
static __inline__ void IncidentConditionsList_delAndSetNull(void *ptr)
{
	IncidentConditionsList **p = (IncidentConditionsList **)ptr;
	if (p != NULL) { IncidentConditionsList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void IncidentConditionsList_dump(IncidentConditionsList *p, int tab);

// IncidentConditionsList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusEntry
typedef struct RoadwaySurfaceStatusEntry
{
	Dz1Str		node_id;
	Dz1Str		link_id;
	u8_t		surface_cond_code;
	u8_t		land_blocked_or_closed_code;
	u16_t		precipitation_depth;
	u16_t		temperature_qty;
} RoadwaySurfaceStatusEntry;

DZ1_CPPLINK DZ1_DLLPORT RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusEntry_new(Dz1Str node_id, 
																				 Dz1Str link_id, 
																				 u8_t surface_cond_code, 
																				 u8_t land_blocked_or_closed_code, Dz1Error *err);
static __inline__ RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusEntry_gen(Dz1Error *err) { return RoadwaySurfaceStatusEntry_new(NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t RoadwaySurfaceStatusEntry_copy(RoadwaySurfaceStatusEntry *dst, RoadwaySurfaceStatusEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusEntry_clone(RoadwaySurfaceStatusEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusEntry_purge(RoadwaySurfaceStatusEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusEntry_del(RoadwaySurfaceStatusEntry *p);
static __inline__ void RoadwaySurfaceStatusEntry_delAndSetNull(void *ptr)
{
	RoadwaySurfaceStatusEntry **p = (RoadwaySurfaceStatusEntry **)ptr;
	if (p) { RoadwaySurfaceStatusEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusEntry_dump(RoadwaySurfaceStatusEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int RoadwaySurfaceStatusEntry_cmp(RoadwaySurfaceStatusEntry *a, RoadwaySurfaceStatusEntry *b); 
// RoadwaySurfaceStatusEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusList
typedef struct RoadwaySurfaceStatusList
{
	void *storage;
	unsigned int (*count)(struct RoadwaySurfaceStatusList *p);
	Dz1Error (*travel)(struct RoadwaySurfaceStatusList *p, Dz1Error (*func)(void *ptr, RoadwaySurfaceStatusEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct RoadwaySurfaceStatusList *p, Dz1Error (*func)(void *ptr, RoadwaySurfaceStatusEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct RoadwaySurfaceStatusList *p, Dz1Error (*func)(void *ptr, RoadwaySurfaceStatusEntry *entry), void *ptr);
	RoadwaySurfaceStatusEntry **(*get_array)(struct RoadwaySurfaceStatusList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *data);
	bool_t (*remove)(struct RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key);
	RoadwaySurfaceStatusEntry *(*extract)(struct RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key);
	RoadwaySurfaceStatusEntry *(*find)(struct RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key);
	RoadwaySurfaceStatusEntry *(*getHead)(struct RoadwaySurfaceStatusList *p);
	int (*cmp)(RoadwaySurfaceStatusEntry *a, RoadwaySurfaceStatusEntry *b);
} RoadwaySurfaceStatusList;

DZ1_CPPLINK DZ1_DLLPORT RoadwaySurfaceStatusList *RoadwaySurfaceStatusList_new(Dz1Error *err);
static __inline__ RoadwaySurfaceStatusList *RoadwaySurfaceStatusList_gen(Dz1Error *err) { return RoadwaySurfaceStatusList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT RoadwaySurfaceStatusList *RoadwaySurfaceStatusList_clone(RoadwaySurfaceStatusList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusList_purge(RoadwaySurfaceStatusList *p);
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusList_del(RoadwaySurfaceStatusList *p);
static __inline__ void RoadwaySurfaceStatusList_delAndSetNull(void *ptr)
{
	RoadwaySurfaceStatusList **p = (RoadwaySurfaceStatusList **)ptr;
	if (p != NULL) { RoadwaySurfaceStatusList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void RoadwaySurfaceStatusList_dump(RoadwaySurfaceStatusList *p, int tab);

// RoadwaySurfaceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationEntry
typedef struct WeatherInformationEntry
{
	u8_t		forecast_or_actual;
	s8_t		temperature;
	s8_t		high_temperature;
	s8_t		low_temperature;
	u8_t		special_cond;
	Dz1Str		other_cond_desc;
	u8_t		probability;
	u8_t		visibility;
	u8_t		wind_speed;
	u8_t		wind_direct_code;
	u8_t		humidity;
	u8_t		pressure;
	Dz1Str		sunrise_time;
	Dz1Str		sunset_time;
} WeatherInformationEntry;

DZ1_CPPLINK DZ1_DLLPORT WeatherInformationEntry *WeatherInformationEntry_new(u8_t forecast_or_actual, 
																			 u8_t probability, 
																			 u8_t visibility, 
																			 u8_t wind_speed, Dz1Error *err);
static __inline__ WeatherInformationEntry *WeatherInformationEntry_gen(Dz1Error *err) { return WeatherInformationEntry_new(0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t WeatherInformationEntry_copy(WeatherInformationEntry *dst, WeatherInformationEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT WeatherInformationEntry *WeatherInformationEntry_clone(WeatherInformationEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationEntry_purge(WeatherInformationEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationEntry_del(WeatherInformationEntry *p);
static __inline__ void WeatherInformationEntry_delAndSetNull(void *ptr)
{
	WeatherInformationEntry **p = (WeatherInformationEntry **)ptr;
	if (p) { WeatherInformationEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationEntry_dump(WeatherInformationEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int WeatherInformationEntry_cmp(WeatherInformationEntry *a, WeatherInformationEntry *b); 
// WeatherInformationEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationList
typedef struct WeatherInformationList
{
	void *storage;
	unsigned int (*count)(struct WeatherInformationList *p);
	Dz1Error (*travel)(struct WeatherInformationList *p, Dz1Error (*func)(void *ptr, WeatherInformationEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct WeatherInformationList *p, Dz1Error (*func)(void *ptr, WeatherInformationEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct WeatherInformationList *p, Dz1Error (*func)(void *ptr, WeatherInformationEntry *entry), void *ptr);
	WeatherInformationEntry **(*get_array)(struct WeatherInformationList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct WeatherInformationList *p, WeatherInformationEntry *data);
	bool_t (*remove)(struct WeatherInformationList *p, WeatherInformationEntry *key);
	WeatherInformationEntry *(*extract)(struct WeatherInformationList *p, WeatherInformationEntry *key);
	WeatherInformationEntry *(*find)(struct WeatherInformationList *p, WeatherInformationEntry *key);
	WeatherInformationEntry *(*getHead)(struct WeatherInformationList *p);
	int (*cmp)(WeatherInformationEntry *a, WeatherInformationEntry *b);
} WeatherInformationList;

DZ1_CPPLINK DZ1_DLLPORT WeatherInformationList *WeatherInformationList_new(Dz1Error *err);
static __inline__ WeatherInformationList *WeatherInformationList_gen(Dz1Error *err) { return WeatherInformationList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT WeatherInformationList *WeatherInformationList_clone(WeatherInformationList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationList_purge(WeatherInformationList *p);
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationList_del(WeatherInformationList *p);
static __inline__ void WeatherInformationList_delAndSetNull(void *ptr)
{
	WeatherInformationList **p = (WeatherInformationList **)ptr;
	if (p != NULL) { WeatherInformationList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void WeatherInformationList_dump(WeatherInformationList *p, int tab);

// WeatherInformationList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryEntry
typedef struct LinkRoadwayGeometryEntry
{
	Dz1Str		begin_node_id;
	s64_t		begin_node_latitude;
	u32_t		begin_node_longitude;
	Dz1Str		end_node_id;
	s64_t		end_node_latitude;
	u32_t		end_node_longitude;
	Dz1Str		jurisdiction;
	u8_t		type_code;
	Dz1Str		name;
	u32_t		length;
	u8_t		pavement_type_code;
	u16_t		restriction_height;
	u16_t		left_shoulder_width;
	u16_t		restriction_length;
	u8_t		median_type_code;
	u16_t		num_lanes;
	u8_t		num_open_lanes;
	u16_t		right_shoulder_width;
} LinkRoadwayGeometryEntry;

DZ1_CPPLINK DZ1_DLLPORT LinkRoadwayGeometryEntry *LinkRoadwayGeometryEntry_new(Dz1Str begin_node_id, 
																			   Dz1Str end_node_id, 
																			   Dz1Str jurisdiction, 
																			   u8_t type_code, 
																			   Dz1Str name, 
																			   u32_t length, 
																			   u8_t pavement_type_code, 
																			   u8_t median_type_code, 
																			   u16_t num_lanes, 
																			   u8_t num_open_lanes, Dz1Error *err);
static __inline__ LinkRoadwayGeometryEntry *LinkRoadwayGeometryEntry_gen(Dz1Error *err) { return LinkRoadwayGeometryEntry_new(NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t LinkRoadwayGeometryEntry_copy(LinkRoadwayGeometryEntry *dst, LinkRoadwayGeometryEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT LinkRoadwayGeometryEntry *LinkRoadwayGeometryEntry_clone(LinkRoadwayGeometryEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryEntry_purge(LinkRoadwayGeometryEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryEntry_del(LinkRoadwayGeometryEntry *p);
static __inline__ void LinkRoadwayGeometryEntry_delAndSetNull(void *ptr)
{
	LinkRoadwayGeometryEntry **p = (LinkRoadwayGeometryEntry **)ptr;
	if (p) { LinkRoadwayGeometryEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryEntry_dump(LinkRoadwayGeometryEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int LinkRoadwayGeometryEntry_cmp(LinkRoadwayGeometryEntry *a, LinkRoadwayGeometryEntry *b); 
// LinkRoadwayGeometryEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryList
typedef struct LinkRoadwayGeometryList
{
	void *storage;
	unsigned int (*count)(struct LinkRoadwayGeometryList *p);
	Dz1Error (*travel)(struct LinkRoadwayGeometryList *p, Dz1Error (*func)(void *ptr, LinkRoadwayGeometryEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct LinkRoadwayGeometryList *p, Dz1Error (*func)(void *ptr, LinkRoadwayGeometryEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct LinkRoadwayGeometryList *p, Dz1Error (*func)(void *ptr, LinkRoadwayGeometryEntry *entry), void *ptr);
	LinkRoadwayGeometryEntry **(*get_array)(struct LinkRoadwayGeometryList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *data);
	bool_t (*remove)(struct LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key);
	LinkRoadwayGeometryEntry *(*extract)(struct LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key);
	LinkRoadwayGeometryEntry *(*find)(struct LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key);
	LinkRoadwayGeometryEntry *(*getHead)(struct LinkRoadwayGeometryList *p);
	int (*cmp)(LinkRoadwayGeometryEntry *a, LinkRoadwayGeometryEntry *b);
} LinkRoadwayGeometryList;

DZ1_CPPLINK DZ1_DLLPORT LinkRoadwayGeometryList *LinkRoadwayGeometryList_new(Dz1Error *err);
static __inline__ LinkRoadwayGeometryList *LinkRoadwayGeometryList_gen(Dz1Error *err) { return LinkRoadwayGeometryList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT LinkRoadwayGeometryList *LinkRoadwayGeometryList_clone(LinkRoadwayGeometryList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryList_purge(LinkRoadwayGeometryList *p);
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryList_del(LinkRoadwayGeometryList *p);
static __inline__ void LinkRoadwayGeometryList_delAndSetNull(void *ptr)
{
	LinkRoadwayGeometryList **p = (LinkRoadwayGeometryList **)ptr;
	if (p != NULL) { LinkRoadwayGeometryList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void LinkRoadwayGeometryList_dump(LinkRoadwayGeometryList *p, int tab);

// LinkRoadwayGeometryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionEntry
typedef struct ProbeVehicleDetectionEntry
{
	Dz1Str		veh_id;
	u8_t		veh_class;
	Dz1Str		veh_timein;
	Dz1Str		veh_timeout;
	u16_t		veh_traveltime;
	u16_t		veh_avg_speed;
	Dz1Str		avi_id;
	s64_t		avi_latitude;
	u32_t		avi_longitude;
	Dz1Str		ref_avi_id;
	s64_t		ref_avi_latitude;
	u32_t		ref_avi_longitude;
} ProbeVehicleDetectionEntry;

DZ1_CPPLINK DZ1_DLLPORT ProbeVehicleDetectionEntry *ProbeVehicleDetectionEntry_new(Dz1Str veh_id, 
																				   u8_t veh_class, 
																				   Dz1Str veh_timein, 
																				   Dz1Str veh_timeout, 
																				   u16_t veh_traveltime, Dz1Error *err);
static __inline__ ProbeVehicleDetectionEntry *ProbeVehicleDetectionEntry_gen(Dz1Error *err) { return ProbeVehicleDetectionEntry_new(NULL, 0, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ProbeVehicleDetectionEntry_copy(ProbeVehicleDetectionEntry *dst, ProbeVehicleDetectionEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ProbeVehicleDetectionEntry *ProbeVehicleDetectionEntry_clone(ProbeVehicleDetectionEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionEntry_purge(ProbeVehicleDetectionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionEntry_del(ProbeVehicleDetectionEntry *p);
static __inline__ void ProbeVehicleDetectionEntry_delAndSetNull(void *ptr)
{
	ProbeVehicleDetectionEntry **p = (ProbeVehicleDetectionEntry **)ptr;
	if (p) { ProbeVehicleDetectionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionEntry_dump(ProbeVehicleDetectionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ProbeVehicleDetectionEntry_cmp(ProbeVehicleDetectionEntry *a, ProbeVehicleDetectionEntry *b); 
// ProbeVehicleDetectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionList
typedef struct ProbeVehicleDetectionList
{
	void *storage;
	unsigned int (*count)(struct ProbeVehicleDetectionList *p);
	Dz1Error (*travel)(struct ProbeVehicleDetectionList *p, Dz1Error (*func)(void *ptr, ProbeVehicleDetectionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ProbeVehicleDetectionList *p, Dz1Error (*func)(void *ptr, ProbeVehicleDetectionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ProbeVehicleDetectionList *p, Dz1Error (*func)(void *ptr, ProbeVehicleDetectionEntry *entry), void *ptr);
	ProbeVehicleDetectionEntry **(*get_array)(struct ProbeVehicleDetectionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *data);
	bool_t (*remove)(struct ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key);
	ProbeVehicleDetectionEntry *(*extract)(struct ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key);
	ProbeVehicleDetectionEntry *(*find)(struct ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key);
	ProbeVehicleDetectionEntry *(*getHead)(struct ProbeVehicleDetectionList *p);
	int (*cmp)(ProbeVehicleDetectionEntry *a, ProbeVehicleDetectionEntry *b);
} ProbeVehicleDetectionList;

DZ1_CPPLINK DZ1_DLLPORT ProbeVehicleDetectionList *ProbeVehicleDetectionList_new(Dz1Error *err);
static __inline__ ProbeVehicleDetectionList *ProbeVehicleDetectionList_gen(Dz1Error *err) { return ProbeVehicleDetectionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ProbeVehicleDetectionList *ProbeVehicleDetectionList_clone(ProbeVehicleDetectionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionList_purge(ProbeVehicleDetectionList *p);
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionList_del(ProbeVehicleDetectionList *p);
static __inline__ void ProbeVehicleDetectionList_delAndSetNull(void *ptr)
{
	ProbeVehicleDetectionList **p = (ProbeVehicleDetectionList **)ptr;
	if (p != NULL) { ProbeVehicleDetectionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ProbeVehicleDetectionList_dump(ProbeVehicleDetectionList *p, int tab);

// ProbeVehicleDetectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionEntry
typedef struct DetectorCollectionEntry
{
	Dz1Str		detector_id;
	Dz1Str		detector_time;
	u16_t		speed_rate;
	u8_t		volume_rate;
	u8_t		occupancy_percent;
	u32_t		veh_q_len_qty;
} DetectorCollectionEntry;

DZ1_CPPLINK DZ1_DLLPORT DetectorCollectionEntry *DetectorCollectionEntry_new(Dz1Str detector_id, 
																			 Dz1Str detector_time, 
																			 u16_t speed_rate, 
																			 u8_t occupancy_percent, Dz1Error *err);
static __inline__ DetectorCollectionEntry *DetectorCollectionEntry_gen(Dz1Error *err) { return DetectorCollectionEntry_new(NULL, NULL, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t DetectorCollectionEntry_copy(DetectorCollectionEntry *dst, DetectorCollectionEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT DetectorCollectionEntry *DetectorCollectionEntry_clone(DetectorCollectionEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionEntry_purge(DetectorCollectionEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionEntry_del(DetectorCollectionEntry *p);
static __inline__ void DetectorCollectionEntry_delAndSetNull(void *ptr)
{
	DetectorCollectionEntry **p = (DetectorCollectionEntry **)ptr;
	if (p) { DetectorCollectionEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionEntry_dump(DetectorCollectionEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int DetectorCollectionEntry_cmp(DetectorCollectionEntry *a, DetectorCollectionEntry *b); 
// DetectorCollectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionList
typedef struct DetectorCollectionList
{
	void *storage;
	unsigned int (*count)(struct DetectorCollectionList *p);
	Dz1Error (*travel)(struct DetectorCollectionList *p, Dz1Error (*func)(void *ptr, DetectorCollectionEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct DetectorCollectionList *p, Dz1Error (*func)(void *ptr, DetectorCollectionEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct DetectorCollectionList *p, Dz1Error (*func)(void *ptr, DetectorCollectionEntry *entry), void *ptr);
	DetectorCollectionEntry **(*get_array)(struct DetectorCollectionList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct DetectorCollectionList *p, DetectorCollectionEntry *data);
	bool_t (*remove)(struct DetectorCollectionList *p, DetectorCollectionEntry *key);
	DetectorCollectionEntry *(*extract)(struct DetectorCollectionList *p, DetectorCollectionEntry *key);
	DetectorCollectionEntry *(*find)(struct DetectorCollectionList *p, DetectorCollectionEntry *key);
	DetectorCollectionEntry *(*getHead)(struct DetectorCollectionList *p);
	int (*cmp)(DetectorCollectionEntry *a, DetectorCollectionEntry *b);
} DetectorCollectionList;

DZ1_CPPLINK DZ1_DLLPORT DetectorCollectionList *DetectorCollectionList_new(Dz1Error *err);
static __inline__ DetectorCollectionList *DetectorCollectionList_gen(Dz1Error *err) { return DetectorCollectionList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT DetectorCollectionList *DetectorCollectionList_clone(DetectorCollectionList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionList_purge(DetectorCollectionList *p);
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionList_del(DetectorCollectionList *p);
static __inline__ void DetectorCollectionList_delAndSetNull(void *ptr)
{
	DetectorCollectionList **p = (DetectorCollectionList **)ptr;
	if (p != NULL) { DetectorCollectionList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void DetectorCollectionList_dump(DetectorCollectionList *p, int tab);

// DetectorCollectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUEntry
typedef struct ExtentionCommPDUEntry
{
	u32_t			 idx;
	u32_t			 aid;
	time_t			 delivery_start;
	time_t			 delivery_stop;
	bool_t			 signature;
	s64_t			 payload_type;
	Dz1Binary		*payload;
} ExtentionCommPDUEntry;

DZ1_CPPLINK DZ1_DLLPORT ExtentionCommPDUEntry *ExtentionCommPDUEntry_new(u32_t idx, 
																		 u32_t aid, 
																		 time_t delivery_start, 
																		 time_t delivery_stop, 
																		 Dz1Binary *payload, Dz1Error *err);
static __inline__ ExtentionCommPDUEntry *ExtentionCommPDUEntry_gen(Dz1Error *err) { return ExtentionCommPDUEntry_new(0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ExtentionCommPDUEntry_copy(ExtentionCommPDUEntry *dst, ExtentionCommPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ExtentionCommPDUEntry *ExtentionCommPDUEntry_clone(ExtentionCommPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUEntry_purge(ExtentionCommPDUEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUEntry_del(ExtentionCommPDUEntry *p);
static __inline__ void ExtentionCommPDUEntry_delAndSetNull(void *ptr)
{
	ExtentionCommPDUEntry **p = (ExtentionCommPDUEntry **)ptr;
	if (p) { ExtentionCommPDUEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUEntry_dump(ExtentionCommPDUEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int ExtentionCommPDUEntry_cmp(ExtentionCommPDUEntry *a, ExtentionCommPDUEntry *b); 
// ExtentionCommPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUList
typedef struct ExtentionCommPDUList
{
	void *storage;
	unsigned int (*count)(struct ExtentionCommPDUList *p);
	Dz1Error (*travel)(struct ExtentionCommPDUList *p, Dz1Error (*func)(void *ptr, ExtentionCommPDUEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct ExtentionCommPDUList *p, Dz1Error (*func)(void *ptr, ExtentionCommPDUEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct ExtentionCommPDUList *p, Dz1Error (*func)(void *ptr, ExtentionCommPDUEntry *entry), void *ptr);
	ExtentionCommPDUEntry **(*get_array)(struct ExtentionCommPDUList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct ExtentionCommPDUList *p, ExtentionCommPDUEntry *data);
	bool_t (*remove)(struct ExtentionCommPDUList *p, ExtentionCommPDUEntry *key);
	ExtentionCommPDUEntry *(*extract)(struct ExtentionCommPDUList *p, ExtentionCommPDUEntry *key);
	ExtentionCommPDUEntry *(*find)(struct ExtentionCommPDUList *p, ExtentionCommPDUEntry *key);
	ExtentionCommPDUEntry *(*getHead)(struct ExtentionCommPDUList *p);
	int (*cmp)(ExtentionCommPDUEntry *a, ExtentionCommPDUEntry *b);
} ExtentionCommPDUList;

DZ1_CPPLINK DZ1_DLLPORT ExtentionCommPDUList *ExtentionCommPDUList_new(Dz1Error *err);
static __inline__ ExtentionCommPDUList *ExtentionCommPDUList_gen(Dz1Error *err) { return ExtentionCommPDUList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT ExtentionCommPDUList *ExtentionCommPDUList_clone(ExtentionCommPDUList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUList_purge(ExtentionCommPDUList *p);
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUList_del(ExtentionCommPDUList *p);
static __inline__ void ExtentionCommPDUList_delAndSetNull(void *ptr)
{
	ExtentionCommPDUList **p = (ExtentionCommPDUList **)ptr;
	if (p != NULL) { ExtentionCommPDUList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ExtentionCommPDUList_dump(ExtentionCommPDUList *p, int tab);

// ExtentionCommPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1_EamPresent
typedef enum TechnicalRegulation1_EamPresent
{
	TechnicalRegulation1_EamPresent_current_link_state,
	TechnicalRegulation1_EamPresent_event_identity,
	TechnicalRegulation1_EamPresent_incident_identity,
	TechnicalRegulation1_EamPresent_incident_conditions,
	TechnicalRegulation1_EamPresent_roadway_surface_status,
	TechnicalRegulation1_EamPresent_weather_information,
	TechnicalRegulation1_EamPresent_link_roadway_geometry,
	TechnicalRegulation1_EamPresent_probe_vehicle_detection,
	TechnicalRegulation1_EamPresent_detector_collection,
	TechnicalRegulation1_EamPresent_extention_comm_pdu,
	TechnicalRegulation1_EamPresent_max
} TechnicalRegulation1_EamPresent;

DZ1_CPPLINK str_t TechnicalRegulation1_EamPresentStrA(TechnicalRegulation1_EamPresent v);
DZ1_CPPLINK TechnicalRegulation1_EamPresent TechnicalRegulation1_EamPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TechnicalRegulation1_EamPresentStrW(TechnicalRegulation1_EamPresent v);
DZ1_CPPLINK TechnicalRegulation1_EamPresent TechnicalRegulation1_EamPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TechnicalRegulation1_EamPresentStr TechnicalRegulation1_EamPresentStrW
#define TechnicalRegulation1_EamPresentFromStr TechnicalRegulation1_EamPresentFromStrW
#else // UNICODE
#define TechnicalRegulation1_EamPresentStr TechnicalRegulation1_EamPresentStrA
#define TechnicalRegulation1_EamPresentFromStr TechnicalRegulation1_EamPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TechnicalRegulation1_EamPresentStr TechnicalRegulation1_EamPresentStrA
#define TechnicalRegulation1_EamPresentFromStr TechnicalRegulation1_EamPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1_EamPresent *TechnicalRegulation1_EamPresent_new(TechnicalRegulation1_EamPresent *src, Dz1Error *err);
static __inline__ TechnicalRegulation1_EamPresent *TechnicalRegulation1_EamPresent_gen(Dz1Error *err) { TechnicalRegulation1_EamPresent v = TechnicalRegulation1_EamPresent_max; return TechnicalRegulation1_EamPresent_new(&v, err); }
#define TechnicalRegulation1_EamPresent_clone             TechnicalRegulation1_EamPresent_new
static __inline__ void TechnicalRegulation1_EamPresent_del(TechnicalRegulation1_EamPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TechnicalRegulation1_EamPresent_delAndSetNull(void *ptr)
{
	TechnicalRegulation1_EamPresent **p = (TechnicalRegulation1_EamPresent **)ptr;
	if (p != NULL) { TechnicalRegulation1_EamPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1_EamPresent_dump(TechnicalRegulation1_EamPresent *v, int tab);
// TechnicalRegulation1_EamPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1_Eam
typedef struct TechnicalRegulation1_Eam
{
	TechnicalRegulation1_EamPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CurrentLinkStateList			*current_link_state;
		EventIdentityList				*event_identity;
		IncidentIdentityList			*incident_identity;
		IncidentConditionsList			*incident_conditions;
		RoadwaySurfaceStatusList		*roadway_surface_status;
		WeatherInformationList			*weather_information;
		LinkRoadwayGeometryList			*link_roadway_geometry;
		ProbeVehicleDetectionList		*probe_vehicle_detection;
		DetectorCollectionList			*detector_collection;
		ExtentionCommPDUList			*extention_comm_pdu;
	} x;
} TechnicalRegulation1_Eam;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1_Eam *TechnicalRegulation1_Eam_new(TechnicalRegulation1_EamPresent present, void *ptr, Dz1Error *err);
static __inline__ TechnicalRegulation1_Eam *TechnicalRegulation1_Eam_gen(Dz1Error *err) { return TechnicalRegulation1_Eam_new(TechnicalRegulation1_EamPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TechnicalRegulation1_Eam_copy(TechnicalRegulation1_Eam *dst, TechnicalRegulation1_Eam *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation1_Eam *TechnicalRegulation1_Eam_clone(TechnicalRegulation1_Eam *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1_Eam_purge(TechnicalRegulation1_Eam *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1_Eam_del(TechnicalRegulation1_Eam *p);
static __inline__ void TechnicalRegulation1_Eam_delAndSetNull(void *ptr)
{
	TechnicalRegulation1_Eam **p = (TechnicalRegulation1_Eam **)ptr;
	if (p != NULL) { TechnicalRegulation1_Eam_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation1_Eam_dump(TechnicalRegulation1_Eam *p, int tab);
// TechnicalRegulation1_Eam
////////////////////////////////////////////////////////////////////////////////

#endif
