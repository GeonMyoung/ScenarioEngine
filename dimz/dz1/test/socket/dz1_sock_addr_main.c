#include <stdio.h>

#ifdef CPP_BUILDER_WIN32
#pragma hdrstop
#endif

#include <dz1_cleanup.h>
#include <dz1_thread_stdio.h>
#include <dz1_sock_addr.h>

Dz1Error user_main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockAddr addr;
	//str_t str = ":1:FFFF:192.168.1.1";
	//str_t str = ":192.168.1.1";
	str_t str = "192.168.1.1";
	//str_t str = ":FFFF:C0A6:0301:0";
	
	memset(&addr, 0, sizeof(Dz1SockAddr));

	if ((err = Dz1SockAddr_setAddrStr(&addr, str)).code) { ERR_OUT(&err); }
	else if ((err = Dz1SockAddr_setPort(&addr, 4500)).code) { ERR_OUT(&err); }
	else
	{
		char buf[53];
		if (Dz1SockAddr_printable(&addr, buf, FALSE, &err) == NULL) { ERR_OUT(&err); }
		else Dz1Thread_printf("IP = %s\n", buf);
	}

	return err;
}

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1Cleanup_init();

	err = user_main();

	return err.code;
}
