//////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialServerDef.h"

Dz1TcpSerialServerPreset *Dz1TcpSerialServerPreset_new(u32_t serialPort, 
													   Dz1SockAddr *presetListen, 
													   u32_t serialBaud, 
													   s32_t bitPerByte, 
													   Dz1SerialParity serialParity, 
													   Dz1SerialStopBit serialStopBit, 
													   Dz1SerialXONXOFF serialFlowCtrlXonXoff, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerPreset *__internal_ret = (Dz1TcpSerialServerPreset *)Dz1Calloc(sizeof(Dz1TcpSerialServerPreset), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPreset_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->serialPort = serialPort;
		__internal_ret->presetListen = presetListen;
		__internal_ret->serialBaud = serialBaud;
		__internal_ret->bitPerByte = bitPerByte;
		__internal_ret->serialParity = serialParity;
		__internal_ret->serialStopBit = serialStopBit;
		__internal_ret->serialFlowCtrlXonXoff = serialFlowCtrlXonXoff;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPreset_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialServerPreset *Dz1TcpSerialServerPreset_clone(Dz1TcpSerialServerPreset *src, Dz1Error *err)
{
	Dz1TcpSerialServerPreset *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialServerPreset *)Dz1Calloc(sizeof(Dz1TcpSerialServerPreset), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPreset_delAndSetNull, (void *)&ret);

		if (src->presetListen && (ret->presetListen = Dz1SockAddr_clone(src->presetListen, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->serialPort = src->serialPort;
			ret->serialBaud = src->serialBaud;
			ret->bitPerByte = src->bitPerByte;
			ret->serialParity = src->serialParity;
			ret->serialStopBit = src->serialStopBit;
			ret->serialFlowCtrlXonXoff = src->serialFlowCtrlXonXoff;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPreset_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialServerPreset_del(Dz1TcpSerialServerPreset *p)
{
	if (p == NULL) return;
	if (p->presetListen) Dz1SockAddr_del(p->presetListen);
	Dz1Free(p);
}

void Dz1TcpSerialServerPreset_dump(Dz1TcpSerialServerPreset *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("serialPort = ")); Dz1u32_dump(&p->serialPort, tab);

	if (p->presetListen == NULL) Dz1Thread_tprintf(tab, Dz1T("presetListen = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("presetListen = ")); Dz1SockAddr_dump(p->presetListen, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("serialBaud = ")); Dz1u32_dump(&p->serialBaud, tab);

	Dz1Thread_tprintf(tab, Dz1T("bitPerByte = ")); Dz1s32_dump(&p->bitPerByte, tab);

	Dz1Thread_tprintf(tab, Dz1T("serialParity = %s(%d)\n"), Dz1SerialParityStr(p->serialParity), p->serialParity);

	Dz1Thread_tprintf(tab, Dz1T("serialStopBit = %s(%d)\n"), Dz1SerialStopBitStr(p->serialStopBit), p->serialStopBit);

	Dz1Thread_tprintf(tab, Dz1T("serialFlowCtrlXonXoff = %s(%d)\n"), Dz1SerialXONXOFFStr(p->serialFlowCtrlXonXoff), p->serialFlowCtrlXonXoff);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

int Dz1TcpSerialServerPreset_cmp(Dz1TcpSerialServerPreset *a, Dz1TcpSerialServerPreset *b)
{
	int ret = 0;
	if ((ret = Dz1u32_cmp(&a->serialPort, &b->serialPort)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1TcpSerialServerPresetList_add(Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1TcpSerialServerPresetList_remove(Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1TcpSerialServerPreset *Dz1TcpSerialServerPresetList_extract(Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key)
{
	return (Dz1TcpSerialServerPreset *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1TcpSerialServerPresetListMkArrArg
{
	Dz1TcpSerialServerPreset **arr;
	unsigned int idx;
} Dz1TcpSerialServerPresetListMkArrArg;

static Dz1Error _Dz1TcpSerialServerPresetList_get_array(void *ptr, Dz1TcpSerialServerPreset *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSerialServerPresetListMkArrArg *arg = (Dz1TcpSerialServerPresetListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1TcpSerialServerPreset **Dz1TcpSerialServerPresetList_get_array(Dz1TcpSerialServerPresetList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1TcpSerialServerPreset **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1TcpSerialServerPreset **)Dz1Calloc(sizeof(Dz1TcpSerialServerPreset *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1TcpSerialServerPresetListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1TcpSerialServerPresetList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1TcpSerialServerPresetList_travelForward(Dz1TcpSerialServerPresetList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPreset *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1TcpSerialServerPresetList_travelBackward(Dz1TcpSerialServerPresetList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialServerPreset *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1TcpSerialServerPreset *Dz1TcpSerialServerPresetList_find(Dz1TcpSerialServerPresetList *p, Dz1TcpSerialServerPreset *key)
{
	return (Dz1TcpSerialServerPreset *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1TcpSerialServerPresetList_count(Dz1TcpSerialServerPresetList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1TcpSerialServerPresetList *Dz1TcpSerialServerPresetList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerPresetList *ret = (Dz1TcpSerialServerPresetList *)Dz1Calloc(sizeof(Dz1TcpSerialServerPresetList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPresetList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1TcpSerialServerPreset_cmp,
				(Dz1DelFunc)Dz1TcpSerialServerPreset_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1TcpSerialServerPresetList_add;
			ret->remove = Dz1TcpSerialServerPresetList_remove;
			ret->extract = Dz1TcpSerialServerPresetList_extract;
			ret->get_array = Dz1TcpSerialServerPresetList_get_array;
			ret->travel = Dz1TcpSerialServerPresetList_travelForward;
			ret->travelForward = Dz1TcpSerialServerPresetList_travelForward;
			ret->travelBackward = Dz1TcpSerialServerPresetList_travelBackward;
			ret->find = Dz1TcpSerialServerPresetList_find;
			ret->cmp = Dz1TcpSerialServerPreset_cmp;
			ret->count = Dz1TcpSerialServerPresetList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPresetList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1TcpSerialServerPresetList_clone(void *ptr, Dz1TcpSerialServerPreset *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1TcpSerialServerPresetList *p = (Dz1TcpSerialServerPresetList *)ptr;
	Dz1TcpSerialServerPreset *cloned = Dz1TcpSerialServerPreset_clone(data, &err);
	err = Dz1AATree_insert(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1TcpSerialServerPresetList *Dz1TcpSerialServerPresetList_clone(Dz1TcpSerialServerPresetList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerPresetList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TcpSerialServerPresetList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerPresetList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1TcpSerialServerPresetList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerPresetList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialServerPresetList_del(Dz1TcpSerialServerPresetList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1TcpSerialServerPresetList_dump(void *ptr, Dz1TcpSerialServerPreset *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int *)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1TcpSerialServerPreset_dump(p, tab);
	return err;
}

void Dz1TcpSerialServerPresetList_dump(Dz1TcpSerialServerPresetList *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1TcpSerialServerPresetList_dump, (void *)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_new(Dz1SockAddr *emulater, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerConfig *__internal_ret = (Dz1TcpSerialServerConfig *)Dz1Calloc(sizeof(Dz1TcpSerialServerConfig), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->presets = Dz1TcpSerialServerPresetList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->emulater = emulater;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1TcpSerialServerConfig *Dz1TcpSerialServerConfig_clone(Dz1TcpSerialServerConfig *src, Dz1Error *err)
{
	Dz1TcpSerialServerConfig *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1TcpSerialServerConfig *)Dz1Calloc(sizeof(Dz1TcpSerialServerConfig), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);

		if (src->emulater && (ret->emulater = Dz1SockAddr_clone(src->emulater, errp)) == NULL) ERR_OUT(errp);
		else if (src->presets && (ret->presets = Dz1TcpSerialServerPresetList_clone(src->presets, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerConfig_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TcpSerialServerConfig_del(Dz1TcpSerialServerConfig *p)
{
	if (p == NULL) return;
	if (p->emulater) Dz1SockAddr_del(p->emulater);
	if (p->presets) Dz1TcpSerialServerPresetList_del(p->presets);
	Dz1Free(p);
}

void Dz1TcpSerialServerConfig_dump(Dz1TcpSerialServerConfig *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->emulater == NULL) Dz1Thread_tprintf(tab, Dz1T("emulater = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("emulater = ")); Dz1SockAddr_dump(p->emulater, tab); /* using dump func */ }

	if (p->presets == NULL) Dz1Thread_tprintf(tab, Dz1T("presets = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("presets = ")); Dz1TcpSerialServerPresetList_dump(p->presets, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

Dz1TcpSerialServerCfgParserEnv *Dz1TcpSerialServerCfgParserEnv_new(Dz1TcpSerialServerConfig *dst, Dz1TcpSerialServerPreset *preset, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TcpSerialServerCfgParserEnv *__internal_ret = (Dz1TcpSerialServerCfgParserEnv *)Dz1Calloc(sizeof(Dz1TcpSerialServerCfgParserEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1TcpSerialServerCfgParserEnv_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->dst = dst;
		__internal_ret->preset = preset;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1TcpSerialServerCfgParserEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1TcpSerialServerCfgParserEnv_del(Dz1TcpSerialServerCfgParserEnv *p)
{
	if (p == NULL) return;
	if (p->dst) Dz1TcpSerialServerConfig_del(p->dst);
	if (p->preset) Dz1TcpSerialServerPreset_del(p->preset);
	Dz1Free(p);
}

