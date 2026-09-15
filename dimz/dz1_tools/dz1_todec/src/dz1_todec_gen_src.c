#include "dz1_todec.h"

typedef struct SrcGenArg
{
	FILE				*fp;
	int					 tab;
	bool_t				 is_first;
} SrcGenArg;

static Dz1Error Dz1TodecBunchDataEntry_gen_src(FILE *fp, Dz1TodecBunchDataEntry *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecBitDescr *desc = p->src_descr;
	Dz1Thread_ftprintf(fp, tab, "variable(%s, %u, %u)", p->src_name, desc->bit_take, desc->bit_trim);
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecBunchEntry_gen_src(FILE *fp, Dz1TodecBunchEntry *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	switch(p->present)
	{
	case Dz1TodecBunchEntryPresent_data_bits:
		if ((*errp = Dz1TodecBunchDataEntry_gen_src(fp, p->x.data_bits, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TodecBunchEntryPresent_pad_bits:
		Dz1Thread_ftprintf(fp, tab, "padbit (%u)", p->x.pad_bits);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return err;
}

static Dz1Error _bunch_seq_gen_src(void *ptr, Dz1TodecBunchEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg *arg = (SrcGenArg *)ptr;

	if (arg->is_first) arg->is_first = FALSE;
	else Dz1Thread_fprintf(arg->fp, ", -- _bunch_seq_gen_src" NEW_LINE);

	if ((*errp = Dz1TodecBunchEntry_gen_src(arg->fp, p, arg->tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error Dz1TodecBunchSeq_gen_src(FILE *fp, Dz1TodecBunchSeq *list, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg arg = { fp, tab, TRUE };
	if ((*errp = list->travel(list, _bunch_seq_gen_src, (void *)&arg)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_fprintf(fp, NEW_LINE);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error Dz1TodecBunchOfSource_gen_src(FILE *fp, Dz1TodecBunchOfSource *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab,		"complex (%u)" NEW_LINE, p->target_sz);
	Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
	if ((*errp = Dz1TodecBunchSeq_gen_src(fp, p->seq, tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	Dz1Thread_ftprintf(fp, --tab,	"};" NEW_LINE);
	return err;
}

static Dz1Error Dz1TodecByteDescr_gen_src(FILE *fp, Dz1TodecByteDescr *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Thread_ftprintf(fp, tab, "subbyte (%u, %u)", p->byte_take, p->byte_trim);
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecSingleSource_gen_src(FILE *fp, Dz1TodecSingleSource *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecSingleDescr *d = NULL;
	Dz1Thread_ftprintf(fp, tab, "simple %s", p->src_name);
	if ((d = p->src_descr) != NULL)
	{
		switch(d->present)
		{
		case Dz1TodecSingleDescrPresent_partial_byte:
			if ((*errp = Dz1TodecByteDescr_gen_src(fp, d->x.partial_byte, tab)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1TodecSingleDescrPresent_alter_codec:
			Dz1Thread_ftprintf(fp, tab, "alter (%s)", d->x.alter_codec);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	Dz1Thread_fprintf(fp, ";" NEW_LINE);
	return err;
}

static Dz1Error Dz1TodecStreamEntry_gen_src(FILE *fp, Dz1TodecStreamEntry *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	switch(p->present)
	{
	case Dz1TodecStreamEntryPresent_bunch:
		if ((*errp = Dz1TodecBunchOfSource_gen_src(fp, p->x.bunch, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TodecStreamEntryPresent_single:
		if ((*errp = Dz1TodecSingleSource_gen_src(fp, p->x.single, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TodecStreamEntryPresent_pad:
		Dz1Thread_ftprintf(fp, tab, "padding (%u);", p->x.pad);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return err;
}

static Dz1Error _gen_src_stream(void *ptr, Dz1TodecStreamEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg *arg = (SrcGenArg *)ptr;
//	FILE *fp = arg->fp;
// 	if (arg->is_first) arg->is_first = FALSE;
// 	else Dz1Thread_fprintf(fp, ", -- _gen_src_stream" NEW_LINE);

	if ((*errp = Dz1TodecStreamEntry_gen_src(arg->fp, p, arg->tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecStreamList_gen_src(FILE *fp, Dz1TodecStreamList *seq, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg arg = { fp, tab, TRUE };
	Dz1Thread_ftprintf(fp, arg.tab,		"sequence" NEW_LINE);
	Dz1Thread_ftprintf(fp, arg.tab++,	"{" NEW_LINE);
	if ((*errp = seq->travel(seq, _gen_src_stream, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	Dz1Thread_ftprintf(fp, --arg.tab,	"}" NEW_LINE);
	return err;
}

static Dz1Error Dz1TodecTargetCodecEntry_gen_src(FILE *fp, Dz1TodecTargetCodecEntry *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TodecTargetCodecAttr *attr = p->attr;
	str_t name = (p->alter_codec == NULL || p->alter_codec[0] == 0) ? "default" : p->alter_codec;
	str_t mode = Dz1TodecTargetCodecModeStr(p->mode);
	Dz1Thread_ftprintf(fp, tab,		"codec %s %s" NEW_LINE, name, mode);
	Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);

	switch(attr->present)
	{
	case Dz1TodecTargetCodecAttrPresent_st:
		if ((*errp = Dz1TodecStreamList_gen_src(fp, p->seq, tab)).code) ERR_OUT(errp);
		break;
	case Dz1TodecTargetCodecAttrPresent_un:
		Dz1Thread_ftprintf(fp, tab, "union (present default);" NEW_LINE);
		if ((*errp = Dz1TodecStreamList_gen_src(fp, p->seq, tab)).code) ERR_OUT(errp);
		break;
	case Dz1TodecTargetCodecAttrPresent_ar:
		Dz1Thread_ftprintf(fp, tab, "array (count default, entry default);" NEW_LINE);
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	Dz1Thread_ftprintf(fp, --tab,	"}");

	return err;
}

static Dz1Error _gen_src_codec(void *ptr, Dz1TodecTargetCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg *arg = (SrcGenArg *)ptr;
	FILE *fp = arg->fp;
	if (arg->is_first) arg->is_first = FALSE;
	else Dz1Thread_fprintf(fp, ", -- _gen_src_codec" NEW_LINE);

	if ((*errp = Dz1TodecTargetCodecEntry_gen_src(arg->fp, p, arg->tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1TodecTargetCodecList_gen_src(FILE *fp, Dz1TodecTargetCodecList *list, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg arg = { fp, tab, TRUE };
	if ((*errp = list->travel(list, _gen_src_codec, (void *)&arg)).code) ERR_OUT(errp);
	else
	{
		Dz1Thread_fprintf(fp, NEW_LINE);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error Dz1TodecTarget_gen_src(FILE *fp, Dz1TodecTarget *p, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->codecs->count(p->codecs) > 0)
	{
		Dz1Thread_ftprintf(fp, tab,	"----------------------------------------" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,	"-- %s" NEW_LINE, p->src_name);
		Dz1Thread_ftprintf(fp, tab,	"----------------------------------------" NEW_LINE);
		Dz1Thread_ftprintf(fp, tab,	"target %s" NEW_LINE, p->src_name);
		Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
		if ((*errp = Dz1TodecTargetCodecList_gen_src(fp, p->codecs, tab)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_ftprintf(fp, --tab,	"};" NEW_LINE);
	}
	return err;
}

static Dz1Error _gen_src_target(void *ptr, Dz1TodecTarget *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg *arg = (SrcGenArg *)ptr;

 	if (arg->is_first) arg->is_first = FALSE;
 	else Dz1Thread_fprintf(arg->fp, NEW_LINE);

	if ((*errp = Dz1TodecTarget_gen_src(arg->fp, p, arg->tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error Dz1TodecTargetList_gen_src(FILE *fp, Dz1TodecTargetList *list, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SrcGenArg arg = { fp, tab, TRUE };
	if ((*errp = list->travel(list, _gen_src_target, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
//	Dz1Thread_fprintf(arg.fp, NEW_LINE);
	return err;
}

static Dz1Error Dz1TodecInclude_gen_src(FILE *fp, Dz1TodecInclude *src, int tab)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t cnt;
	Dz1TodecIncList *seq = NULL;	
	Dz1TodecIncEntry **arr = NULL;
	if ((seq = src->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((arr = seq->get_array(seq, &cnt, errp)) == NULL) ERR_OUT(errp);
	else if (cnt > 0)
	{
		u32_t i;
		Dz1TodecIncEntry *node = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++)
		{
			node = arr[i];
			Dz1Thread_ftprintf(fp, tab, "include %s;" NEW_LINE, node->name);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
		Dz1Thread_fprintf(fp, NEW_LINE);
		Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1Todec_gen_src(FILE *fp, Dz1Todec *src, Dz1MdefcModule *module)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	int tab = 0;
	char *name = strrchr(module->name, DIR_SEP_A);
	if (name == NULL) name = module->name; else name++;
	Dz1Thread_ftprintf(fp, tab,		"message codecs for \"%s.tdo\"" NEW_LINE, name);
	Dz1Thread_ftprintf(fp, tab++,	"{" NEW_LINE);
	if ((*errp = Dz1TodecInclude_gen_src(fp, src->incl, tab)).code) ERR_OUT(errp);
	else if ((*errp = Dz1TodecTargetList_gen_src(fp, src->list, tab)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	Dz1Thread_ftprintf(fp, --tab,	"}" NEW_LINE);
	return err;
}
