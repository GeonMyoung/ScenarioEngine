#include "dz1_asn1_types.h"
#include "dz1_asn1_codec.h"

//Dz1Asn1TypeDescrChildPresence dz1Asn1TypeDescrChildPresence_optional = { Dz1Asn1TypeDescrChildPresencePresent_optional, { NULL } };

ssize_t Dz1Asn1_2sComplementPacking(u8_t *dst, size_t sz, s64_t v, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	u8_t *dp = dst;

	if (v == 0)
	{
		if (sz == 0) ERR_SET_OUT(errp, ENOMEM);
		else
		{
			*dp++ = 0;
			sz--;
			ret++;
		}
	}
	else 
	{
		u32_t cnt = sizeof(u64_t), i = 0;
		u64_t chk_value = v > 0 ? 0 : DZ1UINT64(0xFF80000000000000);

		while((v & DZ1UINT64(0xFF80000000000000)) == chk_value) { v <<= 8; cnt--; }
		while(errp->code == 0 && cnt)
		{
			if (sz == 0) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				*dp++ = (u8_t)((v >> 56) & 0xFF);
				sz--;
				ret++;
			}
			v <<= 8;
			cnt--;
		}
	}
	return errp->code == 0 ? ret : -1;
}

