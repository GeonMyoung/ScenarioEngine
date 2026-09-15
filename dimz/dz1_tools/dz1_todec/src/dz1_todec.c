#include "dz1_todec.h"

Dz1Todec *Dz1Todec_new(str_t mod_name, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Todec *__internal_ret = (Dz1Todec *)Dz1Calloc(sizeof(Dz1Todec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Todec_delAndSetNull, (void *)&__internal_ret);

		if (mod_name && (__internal_ret->mod_name = Dz1StrA_clone(mod_name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->incl = Dz1TodecInclude_new(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->list = Dz1TodecTargetList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->idx = Dz1TodecTargetTable_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Todec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

typedef struct Dz1TodecIncludeAddCancelArg
{
	Dz1TodecIncIndex *idx;
	Dz1TodecIncEntry **node;
} Dz1TodecIncludeAddCancelArg;

static void Dz1TodecInclude_appendCancel(void *ptr)
{
	Dz1TodecIncludeAddCancelArg *arg = (Dz1TodecIncludeAddCancelArg *)ptr;
	Dz1TodecIncEntry *node = *arg->node;
	if (node != NULL) arg->idx->extract(arg->idx, node);
}

Dz1Error Dz1TodecInclude_append(Dz1TodecInclude *dst, str_t incld)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecIncEntry *node = NULL;
	Dz1TodecIncList *list = NULL;
	Dz1TodecIncIndex *idx = NULL;
	if (dst == NULL || incld == NULL || incld[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((list = dst->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((idx = dst->ref_idx) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((node = Dz1TodecIncEntry_new(incld, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TodecIncEntry_delAndSetNull, (void *)&node);
		if ((*errp = idx->add(idx, node)).code) ERR_OUT(errp);
		else
		{
			Dz1TodecIncludeAddCancelArg arg = { idx, &node };
			pthread_cleanup_push(Dz1TodecInclude_appendCancel, (void *)&arg);
			if ((*errp = list->add(list, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1TodecInclude_appendCancel, (void *)&arg);
		}
		pthread_cleanup_pop(1); // (Dz1TodecIncEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

////////////////////////////////////////////////////////////////////////////////
// PublishEnv API
/*
typedef struct PublishEnv
{
	Dz1MdefcModule			*module;

	str_t					*inc_arr;
	u32_t					 inc_cnt;

	FILE					*fp_src;
	FILE					*fp_hdr;

} PublishEnv;
*/

static Dz1Error _parse_inc_path(PublishEnv *dst, Dz1Str paths)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((dst->inc_path = (char **)Dz1Calloc(sizeof(char *), 64, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&dst->inc_path);
		if (paths != NULL && paths[0] != 0)
		{
			char *cp = paths, buf[2048], *dp = buf;
			while(errp->code == 0 && *cp)
			{
				if (*cp == ';')
				{	// end of string
					*dp++ = 0;
					dp = buf;

					if ((dst->inc_path[dst->inc_path_cnt++] = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				// normal letters
				else *dp++ = *cp;
				cp++;
			}

			if (errp->code == 0 )
			{
				if (dp > buf)
				{
					*dp++ = 0;
					if ((dst->inc_path[dst->inc_path_cnt++] = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&dst->inc_path);
	}
	return err;
}

PublishEnv *PublishEnv_new(str_t path, str_t name, str_t ext, Dz1TodecPubArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PublishEnv *ret = (PublishEnv *)Dz1Calloc(sizeof(PublishEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishEnv_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else if ((ret->text = Dz1TextFile_load3(path, name, ext, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _parse_inc_path(ret, arg->mod_inc_path)).code) ERR_OUT(errp);
		else if (arg->output_src && (ret->fp_src = Dz1FileStream_open3(arg->dst_path_c, TEMPORARY_FILE_NAME, "c", "w+b", errp)) == NULL) ERR_OUT(errp);
		else if (arg->output_hdr && (ret->fp_hdr = Dz1FileStream_open3(arg->dst_path_h, TEMPORARY_FILE_NAME, "h", "w+b", errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->flags = arg->flags;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (PublishEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishEnv_del(PublishEnv *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1Str_delAndSetNull(&p->text);

	if (p->inc_path != NULL)
	{
		u32_t i;
		for (i = 0; i < p->inc_path_cnt; i++)
		{
			Dz1Str_del(p->inc_path[i]);
			p->inc_path[i] = NULL;
		}
		Dz1Free(p->inc_path);
		p->inc_path = NULL;
	}
	Dz1FileStream_closeAndSetNull(&p->fp_src);
	Dz1FileStream_closeAndSetNull(&p->fp_hdr);
	Dz1Free(p);
}

// void PublishEnv_dump(PublishEnv *p, int tab)
// {
// 	if (!p) { Dz1Thread_printf("NULL\n"); return; }
// 	else
// 	{
// 		Dz1Thread_printf("{\n"); tab++;
// 		// Additional print code here
// 		Dz1Thread_tprintf(--tab, "}\n");
// 	}
// }
// PublishEnv API
////////////////////////////////////////////////////////////////////////////////


typedef struct Dz1TodecTargetTableCancelArg
{
	Dz1TodecTargetTable *list;
	Dz1TodecTarget **node;
} Dz1TodecTargetTableCancelArg;

static void Dz1TodecTargetTableCancel(void *ptr)
{
	Dz1TodecTargetTableCancelArg *arg = (Dz1TodecTargetTableCancelArg *)ptr;
	if (arg->list && arg->node && *arg->node)
		arg->list->extract(arg->list, *arg->node);
	arg->list = NULL;
	arg->node = NULL;
}

Dz1Error Dz1Todec_addTarget(Dz1Todec *dst, Dz1TodecTarget *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->idx->add(dst->idx, node)).code) ERR_OUT(errp);
	else
	{
		Dz1TodecTargetTableCancelArg arg = { dst->idx, &node };
		pthread_cleanup_push(Dz1TodecTargetTableCancel, (void *)&arg);
		if ((*errp = dst->list->add(dst->list, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1TodecTargetTableCancel, (void *)&arg);
	}
	return err;
}

TodecAnalysisData *TodecAnalysisData_gen(Dz1Todec *src, Dz1MdefcModule *module, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	StreamList *ret = Dz1Todec_analysis(src, module, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return (TodecAnalysisData *)ret;
}

void TodecAnalysisData_del(TodecAnalysisData *p)
{
	StreamList_del((StreamList *)p);
}

void TodecAnalysisData_dump(TodecAnalysisData *p, int tab)
{
	StreamList_dump((StreamList *)p, tab);
}
