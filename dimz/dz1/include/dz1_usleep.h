#ifndef DZ1_USLEEP_H
#define DZ1_USLEEP_H

#include <dz1.h>

/*
 * Dz1Thread_usleep : sleep current thread
 *
 * @sleep_us : sleep time in micro second
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void Dz1Thread_usleep(u32_t sleep_us);

#endif
