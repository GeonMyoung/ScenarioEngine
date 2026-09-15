#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include <hae_output.h>
#include <hae_inet.h>
#include <hae_inet_rdate.h>

#define DBG_OUT(err)	HaeOut->printf(0, __FILE__ ":%d = %s(%d)\n", __LINE__, strerror((err)), (err))

#if __STDC__
#define DIFFERENCE 2208988800UL
#else
#define DIFFERENCE 2208988800
#endif

#if 0
int main(void)
{
	int err = 0;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) { err = errno; DBG_OUT(err); }
	else
	{
		time_t t;
		int recv_byte = 0;
		unsigned char _ip[4] = { 192, 168, 1, 51 };
		unsigned int ip = *(unsigned int *)_ip;
		struct sockaddr_in addr;
		memset (&addr, 0, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(37);
		addr.sin_addr.s_addr = ip;
		if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) { err = errno; DBG_OUT(err); }
		else if ((recv_byte = recv(fd, &t, sizeof(time_t), 0)) < 0) { err = errno; DBG_OUT(err); }
		else if (recv_byte == 0) { err = EPIPE; DBG_OUT(err); }
		else if (recv_byte != sizeof(time_t)) { err = EFAULT; DBG_OUT(err); }
		else
		{
			struct tm *tm_p, tm;
			t = ntohl(t) - DIFFERENCE;
			tm_p = localtime(&t);
			tm = *tm_p;
			printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		close(fd);
	}
}
#else
static void socket_cancel(void *p) { SOCKET fd = *(SOCKET *)p; closesocket(fd); }
int hae_inet_rdate(u32_t host_ordered_ip)
{
	time_t t;
	int err = 0;
	int recv_byte = 0;
	struct timeval to = { 1, 0 };
	SOCKET fd = hae_inet_getClientStreamSocket(host_ordered_ip, 37, &to, &err);
	if (fd == INVALID_SOCKET) { DBG_OUT(err); }
	else
	{
		pthread_cleanup_push((HaeGeneralDelFunc)socket_cancel, (void *)&fd);
		if ((recv_byte = recv(fd, &t, sizeof(time_t), 0)) < 0) { err = errno; DBG_OUT(err); }
		else if (recv_byte == 0) { err = EPIPE; DBG_OUT(err); }
		else if (recv_byte != sizeof(time_t)) { err = EFAULT; DBG_OUT(err); }
		else
		{
			struct timeval tNow = { t, 0 };
			tNow.tv_sec = ntohl(tNow.tv_sec) - DIFFERENCE;
			if (settimeofday(&tNow, NULL)) { err = errno; DBG_OUT(err); }
			else
			{
				struct tm *tm_p, tm;
				tm_p = localtime(&tNow.tv_sec);
				tm = *tm_p;
				HaeOut->printf(0, "hae_inet_rdate() : %04d-%02d-%02d %02d:%02d:%02d\n",
						tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			}
		}
		pthread_cleanup_pop(1); // ((HaeGeneralDelFunc)socket_cancel, (void *)&fd);
	}
	return err;
}
#endif
