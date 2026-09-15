#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define DBG_OUT(err)			printf(__FILE__ ":%d = %s(%d)\n", __LINE__, strerror((err)), (err))

static int gr0 = 1, gr1 = 2;
static void *dumb_func(void *arg)
{
	struct timeval to;
	while(1)
	{
		pthread_testcancel();
		to.tv_sec = 0; to.tv_usec = 100000;
		select(0, NULL, NULL, NULL, &to);
		pthread_testcancel();
	}
	pthread_exit(&gr0);
	return NULL;
}

static void *killer_func(void *arg)
{
	pthread_t th = *(pthread_t *)arg;
	struct timeval to;
	to.tv_sec = 1; to.tv_usec = 0; select(0, NULL, NULL, NULL, &to);
	pthread_cancel(th);
	to.tv_sec = 1; to.tv_usec = 0; select(0, NULL, NULL, NULL, &to);
	pthread_exit(&gr1);
	return NULL;
}

int main(void)
{
	int err;
	pthread_t th0, th1;
	if ((err = pthread_create(&th0, NULL, dumb_func, NULL))) { DBG_OUT(err); }
	else if ((err = pthread_create(&th1, NULL, killer_func, (void *)&th0))) { DBG_OUT(err); }
	else
	{
		int *result0 = NULL, *result1 = NULL;
		int err0, err1;
		err0 = pthread_join(th0, (void **)&result0);
		printf("th0 = %s(%d) with %d(%p)\n", strerror(err0), err0, result0 == (int *)-1 ? -1 : *result0, result0);

		err1 = pthread_join(th1, (void **)&result1);
		printf("th1 = %s(%d) with %d(%p)\n", strerror(err1), err1, result1 == (int *)-1 ? -1 : *result1, result1);
	}
	return 0;
}
