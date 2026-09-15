#include <dz1_thread.h>
#include <dz1_usleep.h>

#ifndef UNIX_SYSTEM
#include <winsock2.h>
#endif

void Dz1Thread_usleep(u32_t sleep_us)
{
	Dz1ThreadStatus oldStatus = Dz1Thread_getStatus();
	Dz1Thread_setStatus(Dz1ThreadStatus_sleep);
	pthread_cleanup_push((Dz1CancelFunc)Dz1Thread_setStatusCleanup, (void *)&oldStatus);
	{
#ifndef UNIX_SYSTEM
		u32_t sleep_ms = sleep_us / 1000 + ((sleep_us % 1000) >= 5000 ? 1 : 0);
		u32_t _sleep_ms;

		while(sleep_ms)
		{
			_sleep_ms = sleep_ms > 150 ? 100 : sleep_ms;

			pthread_testcancel();
			Sleep(_sleep_ms); 
			pthread_testcancel();

			sleep_ms -= _sleep_ms;
		}
#else
		u32_t _sleep_us;
		struct timeval to;
		while(sleep_us)
		{
			_sleep_us = sleep_us > 150000 ? 100000 : sleep_us;
			to.tv_sec = 0; to.tv_usec = _sleep_us;

			pthread_testcancel();
			select(0, NULL, NULL, NULL, &to);
			pthread_testcancel();

			sleep_us -= _sleep_us;
		}
#endif
	}
	pthread_cleanup_pop(1); // ((Dz1CancelFunc)Dz1Thread_setStatuscleanup, (void *)&oldStatus);
}
