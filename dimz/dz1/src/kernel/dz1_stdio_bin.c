#include <dz1_malloc.h>
#include <dz1_stdio_bin.h>

ssize_t Dz1Binary_save(Dz1Binary *p, FILE *fp, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!p || !fp) DZ1_STDIO_ERR_RET(errp);
	else
	{
		ssize_t status;
		DZ1_WRITE4(fp, p->size, status, ret, errp);
		DZ1_WRITE(fp, p->data, p->size, status, ret, err);
	}
	return ret;
}

ssize_t Dz1Binary_load(Dz1Binary *p, FILE *fp, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (!p || !fp) DZ1_STDIO_ERR_RET(errp);
	else
	{
		ssize_t status;
		DZ1_READ4(fp, &p->size, status, ret, errp);
		Dz1Memory_freeAndSetNull(&p->data);
		if (p->size > 0)
		{
			if ((p->data = (u8_t *)Dz1Malloc(p->size, errp)) == NULL) DZ1_STDIO_ERR_RET(errp);
			else DZ1_READ(fp, p->data, p->size, status, ret, err);
		}
	}
	return ret;
}

