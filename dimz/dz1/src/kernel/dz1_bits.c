#include <dz1_thread_stdio.h>
#include <dz1_malloc.h>
#include <dz1_bits.h>

static Dz1Error _Dz1Bits_set(struct Dz1Bits *p, u32_t idx)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->size_bits <= idx) ERR_SET_OUT(&err, EINVAL);
	else Dz1Bits_set(p->data, idx);
	return err;
}

static Dz1Error _Dz1Bits_clr(struct Dz1Bits *p, u32_t idx)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->size_bits <= idx) ERR_SET_OUT(&err, EINVAL);
	else Dz1Bits_clr(p->data, idx);
	return err;
}

static bool_t _Dz1Bits_isSet(struct Dz1Bits *p, u32_t idx)
{
	bool_t ret = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->size_bits <= idx) ERR_SET_OUT(&err, EINVAL);
	else
	{
//		u32_t elem = idx / DZ1_BITS_UNIT_SIZE_BIT, _idx = idx % DZ1_BITS_UNIT_SIZE_BIT;
		ret = Dz1Bits_isSet(p->data, idx);
	}
	return ret;
}

Dz1Bits *Dz1Bits_new(DZ1_BITS_UNIT *data, u32_t size_bits, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Bits *ret = (Dz1Bits *)Dz1Calloc(sizeof(Dz1Bits), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		u32_t elem_size = (size_bits / DZ1_BITS_UNIT_SIZE_BIT) + (size_bits % DZ1_BITS_UNIT_SIZE_BIT > 0 ? 1 : 0);
		pthread_cleanup_push(Dz1Bits_delAndSetNull, (void *)&ret);
		if ((ret->data = (DZ1_BITS_UNIT *)Dz1Calloc(sizeof(DZ1_BITS_UNIT), elem_size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->size_bits = size_bits;
			ret->set = _Dz1Bits_set;
			ret->clr = _Dz1Bits_clr;
			ret->isSet = _Dz1Bits_isSet;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Bits_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Bits_del(Dz1Bits *p)
{
	if (p == NULL) return;
	if (p->data) Dz1Free(p->data);
	Dz1Free(p);
}

void Dz1Bits_dump(Dz1Bits *p, int tab)
{
	if (p == NULL) return;
	else
	{
		u32_t elem_size = (p->size_bits / DZ1_BITS_UNIT_SIZE_BIT) + (p->size_bits % DZ1_BITS_UNIT_SIZE_BIT > 0 ? 1 : 0);
		Dz1Thread_tprintb(tab, p->data, elem_size, 16, FALSE);
	}
}
