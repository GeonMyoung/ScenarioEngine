#include "hae_output.h"
#include "hae_local_memory.h"
#include "hae_local_crypt.h"

#define DATA "root"

int main(void)
{
	void *data = NULL, *ddata = NULL;
	int len = 0, dlen = 0;
	HaeOut->printf(0, "Source : " DATA "\n");
	if (!hae_local_encrypt(DATA, strlen(DATA), "haeEvo2", &data, &len))
		HaeOut->printf(0, "enc error\n");
	else
	{
		HaeOut->printf(0, "Encrypted Len : %d\n", len);
		HaeOut->printb(0, data, len);
		if (!hae_local_decrypt(data, len, "haeEvo2", &ddata, &dlen))
			HaeOut->printf(0, "dec error\n");
		else
		{
			HaeOut->printf(0, "Decrypted Len : %d\n", dlen);
			HaeOut->printf(0, "Result : %s\n", ddata);
			LOCAL_FREE(ddata);
		}
		LOCAL_FREE(data);
	}
	return 0;
}
