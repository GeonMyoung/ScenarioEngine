#ifndef DZ1_CLOCK_INDEX_H
#define DZ1_CLOCK_INDEX_H

#include <dz1_time.h>

typedef void Dz1ClockIndex;

DZ1_CPPLINK void	*Dz1ClockIndex_new(u32_t size, Dz1Error *err);
DZ1_CPPLINK void	 Dz1ClockIndex_del(Dz1ClockIndex *pClockIndex);
DZ1_CPPLINK void	 Dz1ClockIndex_delAndSetNull(void *ppClockIndex);
DZ1_CPPLINK void	 Dz1ClockIndexA_dump(Dz1ClockIndex *pClockIndex, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK void	 Dz1ClockIndexW_dump(Dz1ClockIndex *pClockIndex, int tab);
#ifdef UNICODE
#define				 Dz1ClockIndex_dump			Dz1ClockIndexW_dump
#else // UNICODE
#define				 Dz1ClockIndex_dump			Dz1ClockIndexA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define				 Dz1ClockIndex_dump			Dz1ClockIndexA_dump
#endif // UNIX_SYSTEM

DZ1_CPPLINK Dz1Error Dz1ClockIndex_add(Dz1ClockIndex *pClockIndex, u32_t tIDX, void **user_data, Dz1DelFunc user_data_del);
DZ1_CPPLINK Dz1Error Dz1ClockIndex_addX(void *pClockIndex, u32_t tIDX, void **user_data, Dz1DelFunc user_data_del, Dz1DumpFunc user_data_dump);

DZ1_CPPLINK time_t Dz1ClockIndex_mostClosedTime(Dz1ClockIndex *pClockIndex, void **curData, Dz1Error *err);

DZ1_CPPLINK void *Dz1ClockIndex_getData(Dz1ClockIndex *pClockIndex, Dz1Error *err);

#endif

