#include "hae_output.h"

int main(void)
{
	HaeOut->printf(0, "%d, %s\n1234\n", 10, "abc");
	HaeOut->printf(1, "%d, %s\n", 20, "cde");
	HaeOut->printf(2, "%d,%s\n", 20, "cde");
	HaeOut->printf(3, "%d,%s\n", 20, "cde");
	HaeOut->printf(4, "%s\n", "end");
	return 0;
}
