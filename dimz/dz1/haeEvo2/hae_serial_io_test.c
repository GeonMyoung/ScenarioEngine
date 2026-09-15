#include <hae_output.h>
#include <hae_serial_io.h>

#define DBG_OUT(err)	HaeOut->printf(0, __FILE__ ":%d = %s(%d)\n", __LINE__, strerror((err)), (err))

static int func(void *handle, void *arg)
{
	int err = 0;
	char buf[1024];
	int recv_byte = hae_serial_recv(handle, (u8_t *)buf, 1024, &err);
	if (recv_byte == 0) { err = EPIPE; DBG_OUT(err); }
	else if (recv_byte < 0) { DBG_OUT(err); }
	else
	{
		char *cp = buf;
		while(recv_byte--)
			putc(*cp, stdout);
		fflush(stdout);
	}
	return err;
}

int main(int argc, char *argv[])
{
	if (argc != 2) { HaeOut->printf(0, "%s <port_num>\n", argv[0]); }
	else
	{
		int err = 0;
		int port = atoi(argv[1]);
		int id = 0;
		void *handle = hae_serial_open(port, 9600, 8, 0, &err);
		if (handle == NULL) { DBG_OUT(err); }
		else if ((id = hae_serial_io_monitor_start(handle, func, NULL, &err)) < 0) { DBG_OUT(err); }
		else
		{
			char buf[1024];
			while(1)
			{
				if (fgets(buf, 1024, stdin) == NULL)  break;
				else
				{
					int send_byte;
					buf[1023] = '\0';
					if ((send_byte = hae_serial_send(handle, (u8_t *)buf, strlen(buf), &err)) == 0) { err = EPIPE; DBG_OUT(err); break; }
					else if (send_byte < 0) { DBG_OUT(err); break; }
					else HaeOut->printf(0, "%d byte sent\n", send_byte);
				}
			}
		}
	}
	return 0;
}
