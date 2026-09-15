#include <hae_crc.h>

int main(void)
{
	char data[16] = "abcdefghijkl";
	unsigned long crc = hae_crc_update(0xffffffffUL, data, strlen(data));
	printf("0x%08lx\n", crc);
	return 0;
}
