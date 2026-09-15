#include <dz1_parser_init.h>
#include <Dz1ParserUtil.h>
#include "dz1_todec.h"

#define TODEC_PARSE_ENV			0

typedef struct TodecParseEnv
{
	Dz1Todec						*dst;

	Dz1TodecTarget					*tgt;
	Dz1TodecTargetCodecEntry		*cdc;
	Dz1TodecTargetCodecAttrDescr	*attr;
	Dz1TodecByteDescr				*byte_sel;
	Dz1TodecRestrictDescr			*restricted;
	Dz1Str							 alter;
	Dz1TodecStreamEntry				*seq;
	Dz1TodecBunchEntry				*bch;
	Dz1Str							 postfix;
} TodecParseEnv;

static void TodecParseEnv_cleanup(void *ptr)
{
	TodecParseEnv *p = (TodecParseEnv *)ptr;

	Dz1TodecBunchEntry_delAndSetNull(&p->bch);
	Dz1TodecStreamEntry_delAndSetNull(&p->seq);
	Dz1Str_delAndSetNull(&p->alter);
	Dz1TodecRestrictDescr_delAndSetNull(&p->restricted);
	Dz1TodecByteDescr_delAndSetNull(&p->byte_sel);
	Dz1TodecTargetCodecAttrDescr_delAndSetNull(&p->attr);
	Dz1TodecTargetCodecEntry_delAndSetNull(&p->cdc);
	Dz1TodecTarget_delAndSetNull(&p->tgt);
	Dz1Todec_delAndSetNull(&p->dst);
	Dz1Str_delAndSetNull(&p->postfix);
}


static str_t __syntax_str__ =
"Main				=	message codecs for <string>=create_dst\n"
"						<liststart>\n"
"							[<Includes>]*\n"
"							[<Target>]*\n"
"						<listend><done>;\n"
"\n" // 6
"Includes			=	include <string>|<symbol>=include_add <semicolon>;\n"
"\n" // 8
"Target				=	target=target_create <symbol>=target_set_obj <liststart>\n"
"							<Codec> [<CodecMore>]*\n"
"						<listend>=target_append <semicolon>;\n"
"\n" // 12
"Codec				=	codec=codec_create <symbol>|<string>=codec_set_name <symbol>=codec_set_mode <liststart>\n"
"							[<UnionCodec>|<ArrayCodec>|<StructCodec>]+\n"
"						<listend>=codec_append;\n"
"CodecMore			=	<comma> <Codec>;\n"
"\n" // 17
"UnionCodec			=	union=union_create <lbracket> present=attr_descr_create <AttrDescr>=union_set_present <rbracket> <semicolon>\n"
"						<Sequence> [<CodecPostfix>];\n"
"StructCodec		=	<Sequence> [<CodecPostfix>];\n"
"CodecPostfix		=	<comma> <PostFix>=codec_set_postfix <semicolon>;\n"
"\n" // 22
"ArrayCodec			=	array=array_create <lbracket>\n"
"							count=attr_descr_create <AttrDescr>=array_set_count <comma>\n"
"							entry=attr_descr_create <AttrDescr>=array_set_entry [<PostFix>=array_set_postfix]\n"
"						<rbracket> <semicolon>;\n"		// array can't has "CodecPostfix"
"\n" // 27
"AttrDescr			=	<BasicMethod>|<ExtMethod>;\n"
"BasicMethod		=	omit|default=attr_descr_set_mode;\n"
"ExtMethod			=	<ByteSel>|<Alter>=attr_descr_set_data;\n"
"\n" // 31
"Sequence			=	sequence <liststart>\n"
"							[<Padding>|<Constant>|<ElemComplexDef>|<ElemSimpleDef>|<ElemConditionalDef>|<ElemOmitDef>=seq_append]+\n"
"						<listend>;\n"
"\n" // 35
///////////////////////////////////////////////////////////////////////////////
// Sequence : Padding
//	padding(nn);
"Padding			=	padding=padding_create <lbracket> <number>=padding_set_sz <rbracket> <semicolon>;\n"
// Sequence : Padding
///////////////////////////////////////////////////////////////////////////////
"\n" // 37
///////////////////////////////////////////////////////////////////////////////
// Sequence : Constant
//	constant { 0x00, 0x01, ... };
"Constant			=	constant=constant_create <liststart> <ConstantData> <listend> <semicolon>;\n"
"ConstantData		=	<number>|<letter>=constant_add_value [<ConstantDataMore>]*;\n"
"ConstantDataMore	=	<comma> <ConstantData>;\n"
// Sequence : Constant
///////////////////////////////////////////////////////////////////////////////
"\n" // 41
///////////////////////////////////////////////////////////////////////////////
// Sequence : Complex
//	complex(16 bit) {
//		padbit(						5 bit),
//		variable(memb_a,		lsb 3 bit),
//		variable(memb_b,		lsb 2 bit),
//		variable(memb_c,		lsb 1 bit),
//		variable(memb_d,		lsb 3 bit),
//		variable(memb_c >> 1,	lsb 2 bit)
//	}
"ElemComplexDef		=	complex=complex_create <liststart>\n"
"							<ElemComplexMemb>\n"
"							[<ElemComplexMombMore>]*\n"
"						<listend>=complex_set_total <semicolon>;\n"
"ElemComplexMemb	=	<BitPad>|<BitDescr>=complex_append;\n"
"ElemComplexMombMore=	<comma> <ElemComplexMemb>;\n"
"\n" // 48
// padbit(5)
"BitPad				=	padbit=padbit_create <lbracket> <number>=padbit_set_size bit <rbracket>;\n"
// databit(some_memb >> 5, lsb 3)
"BitDescr			=	databit=varbit_create <lbracket> <symbol>|<string>=varbit_set_obj [<BitShift>] <comma> <BitTake> <rbracket>;\n"
"BitShift			=	<greater> <greater> <number>=varbit_shf_cnt;\n"
"BitTake			=	lsb <number>=varbit_take_sz bit;\n"
// Complex declare Syntax
///////////////////////////////////////////////////////////////////////////////
"\n" // 53
///////////////////////////////////////////////////////////////////////////////
// Simple declare Syntax
//	simple memb_a;
//	simple nullflag(8|16|32) memb_b;
"ElemSimpleDef		=	simple=simple_create [<NullFlag>] <symbol>|<string>=simple_set_src [<ElemSimpleMethod>=simple_set_met] [<PostFix>=simple_set_postfix] <semicolon>;\n"
"NullFlag			=	nullflag <lbracket> <number>=simple_set_flag <rbracket>;\n"
// Simple declare Syntax
///////////////////////////////////////////////////////////////////////////////
"\n" // 56
///////////////////////////////////////////////////////////////////////////////
// Conditional declare Syntax
//	simple		memb_a;
//	conditional memb_b("$$->memb_a == 0");
"ElemConditionalDef	=	conditional=conditional_create <symbol>|<string>=conditional_set_src <Condition> [<ElemSimpleMethod>=conditional_set_met] [<PostFix>=conditional_set_postfix] <semicolon>;\n"
"Condition			=	<lbracket> <string>=conditional_set_cond <rbracket>;\n"
// Conditional declare Syntax
///////////////////////////////////////////////////////////////////////////////
"\n" // 59
///////////////////////////////////////////////////////////////////////////////
// Omit declare Syntax
"ElemOmitDef		=	omit=omit_create <symbol>|<string>=omit_set_src<semicolon>;\n"
// Omit declare Syntax
///////////////////////////////////////////////////////////////////////////////
"\n" // 61
///////////////////////////////////////////////////////////////////////////////
// ElemSimpleMethod
//	simple		memb_c					subbyte(1|2|4|8, 0..7);					-- ensmallize long member
//	conditional memb_d("$$->memb_c==0")	alter(mothod1 | "function prefix");		-- alternate CODEC api
//	simple								memb_e fixed(3);						-- enlarger small member
//	conditional memb_f("$$->memb_c==0")	lensz(1|2|4|8);							-- ??
//	simple		memb_g					postfix(mothod | "function_name");	-- after decode, call function as {type}_{method} or function_name
"ElemSimpleMethod	=	<ByteSel>|<Alter>|<Restricted>;\n"
"\n" // 63
"ByteSel			=	subbyte=byte_descr_create <lbracket> <number>=byte_descr_take_byte <comma> <number>=byte_descr_shf_byte <rbracket>;\n"
"\n" // 65
"Alter				=	alter <lbracket> <string>|<symbol>=set_alter_name <rbracket>;\n"
"\n" // 67
"Restricted			=	<RestrictFixed>|<RestrictSize>;\n"
"RestrictFixed		=	fixed=rstr_fixed_create <lbracket> <number>=rstr_fixed_set <rbracket>;\n"
"RestrictSize		=	lensz=rstr_dynamic_create <lbracket> <number>=rstr_dynamic_set <rbracket>;\n"
// ElemSimpleMethod
///////////////////////////////////////////////////////////////////////////////
"\n" // 71
"PostFix			=	postfix <lbracket> <symbol>|<string>=set_postfix_suffix <rbracket>;\n"
"";

///////////////////////////////////////////////////////////////////////////////
// CODEC Module
static Dz1Error create_dst(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	TodecParseEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TodecParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->dst != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{
		// emitting code here
		if ((env->dst = Dz1Todec_new(t->v, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error include_add(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1TodecInclude *incl = NULL;
	Dz1Todec *dst = NULL;
	TodecParseEnv *env = NULL;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((env = (TodecParseEnv *)node->env) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = env->dst) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((incl = dst->incl) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((*errp = Dz1TodecInclude_append(incl, t->v)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// CODEC Module
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Targets
static Dz1Error target_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTarget *tgt = Dz1TodecTarget_new(NULL, errp);
		if (tgt == NULL) ERR_OUT(errp);
		else
		{
			Dz1TodecTarget_delAndSetNull(&env->tgt);
			env->tgt = tgt;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Target Created\n");
		}
	}
	return err;
}

static Dz1Error target_set_obj(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTarget *tgt = env->tgt;
		if (tgt == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (tgt->src_name != NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			tgt->src_name = t->v;
			t->v = NULL;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Target Object = %s\n", tgt->src_name);
		}
	}
	return err;
}

static Dz1Error target_append(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1Todec *dst = env->dst;
		if (env->tgt == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = Dz1Todec_addTarget(dst, env->tgt)).code) ERR_OUT(errp);
		else
		{
			env->tgt = NULL;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Target Appended\n");
		}
	}
	return err;
}
// CODEC Targets
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single CODEC
static Dz1Error codec_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = Dz1TodecTargetCodecEntry_new(NULL, Dz1TodecTargetCodecMode_max, NULL, errp);
		if (cdc == NULL) ERR_OUT(errp);
		else
		{
			Dz1TodecTargetCodecEntry_delAndSetNull(&env->cdc);
			env->cdc = cdc;
			cdc = NULL;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Codec Created\n");
		}
	}
	return err;
}

static Dz1Error codec_set_name(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (strcmp(t->v, "default") != 0)
		{
			Dz1TodecTargetCodecEntry *cdc = env->cdc;
			if (cdc->alter_codec != NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				cdc->alter_codec = t->v;
				t->v = NULL;
				Dz1Error_set(errp, 0);
//				Dz1Thread_printf("CODEC Name=%s\n", cdc->alter_codec);
			}
		}
//		else Dz1Thread_printf("CODEC Default\n");
	}
	return err;
}

static Dz1Error codec_set_mode(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = env->cdc;
		if (strcmp(t->v, "public") == 0)
		{
			cdc->mode = Dz1TodecTargetCodecMode_public;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("CODEC Mode Public\n");
		}
		else if (strcmp(t->v, "private") == 0)
		{
			cdc->mode = Dz1TodecTargetCodecMode_private;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("CODEC Mode Private\n");
		}
		else if (strcmp(t->v, "header") == 0)
		{
			cdc->mode = Dz1TodecTargetCodecMode_header;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("CODEC Mode Public Header Only\n");
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

static Dz1Error codec_append(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTarget *tgt = NULL;
		if (env->cdc == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((tgt = env->tgt) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			Dz1TodecTargetCodecList *dst = tgt->codecs;
			if ((*errp = dst->add(dst, env->cdc)).code) ERR_OUT(errp);
			else
			{
				env->cdc = NULL;
				Dz1Error_set(errp, 0);
//				Dz1Thread_printf("Codec Appended\n");
			}
		}
	}
	return err;
}
// Single CODEC
///////////////////////////////////////////////////////////////////////////////

static Dz1Error attr_descr_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->attr != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->attr = Dz1TodecTargetCodecAttrDescr_new(Dz1TodecTargetCodecAttrDescrPresent_def, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Attribute Descriptor Created\n");
		}
	}
	return err;
}


static Dz1Error attr_descr_set_mode(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecAttrDescr *attr = NULL;
		if ((attr = env->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (strcmp(t->v, "omit") == 0)
			{
				attr->present = Dz1TodecTargetCodecAttrDescrPresent_omit;
				Dz1Error_set(errp, 0);
//				Dz1Thread_printf("Attribute Descriptor Mode : OMIT\n");
			}
			else if (strcmp(t->v, "default") == 0)
			{
				attr->present = Dz1TodecTargetCodecAttrDescrPresent_def;
				Dz1Error_set(errp, 0);
//				Dz1Thread_printf("Attribute Descriptor Mode : DEFAULT\n");
			}
			else ERR_SET_OUT(errp, EINVAL);
		}
	}
	return err;
}

static Dz1Error attr_descr_set_data(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecAttrDescr *attr = NULL;
		if ((attr = env->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (attr->x.__ptr__ != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->byte_sel != NULL)
		{
			attr->present = Dz1TodecTargetCodecAttrDescrPresent_partial_byte;
			attr->x.partial_byte = env->byte_sel;
			env->byte_sel = NULL;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Attribute Descriptor Mode : Partial Byte\n");
		}
		else if (env->alter != NULL)
		{
			attr->present = Dz1TodecTargetCodecAttrDescrPresent_alter_codec;
			attr->x.alter_codec = env->alter;
			env->alter = NULL;
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Attribute Descriptor Mode : Alternate\n");
		}
		else ERR_SET_OUT(errp, EFAULT);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Union CODEC
static Dz1Error union_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecEntry *cdc = env->cdc;
		if (cdc == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (cdc->attr != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((cdc->attr = attr = Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_un, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((attr->x.un = Dz1TodecTargetCodecAttrUnion_new(NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error union_set_present(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = NULL;
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecAttrUnion *un = NULL;
		if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((attr = cdc->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (attr->present != Dz1TodecTargetCodecAttrPresent_un) ERR_SET_OUT(errp, EFAULT);
		else if ((un = attr->x.un) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (un->pr != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->attr == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			un->pr = env->attr;
			env->attr = NULL;
		}
	}
	return err;
}
// Union CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Array CODEC
static Dz1Error array_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecEntry *cdc = env->cdc;
		if (cdc == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (cdc->attr != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((cdc->attr = attr = Dz1TodecTargetCodecAttr_new(Dz1TodecTargetCodecAttrPresent_ar, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((attr->x.ar = Dz1TodecTargetCodecAttrArray_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
//			Dz1Thread_printf("Array Created\n");
		}
	}
	return err;
}

static Dz1Error array_set_count(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = NULL;
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecAttrArray *ar = NULL;
		if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((attr = cdc->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (attr->present != Dz1TodecTargetCodecAttrPresent_ar) ERR_SET_OUT(errp, EFAULT);
		else if ((ar = attr->x.ar) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (ar->body != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->attr == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ar->cnt = env->attr;
			env->attr = NULL;
//			Dz1Thread_printf("Array Count Set\n");
		}
	}
	return err;
}

static Dz1Error array_set_entry(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = NULL;
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecAttrArray *ar = NULL;
		if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((attr = cdc->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (attr->present != Dz1TodecTargetCodecAttrPresent_ar) ERR_SET_OUT(errp, EFAULT);
		else if ((ar = attr->x.ar) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (ar->body != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->attr == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ar->body = env->attr;
			env->attr = NULL;
//			Dz1Thread_printf("Array Entry Set\n");
		}
	}
	return err;
}

static Dz1Error array_set_postfix(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = NULL;
		Dz1TodecTargetCodecAttr *attr = NULL;
		Dz1TodecTargetCodecAttrArray *ar = NULL;
		if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((attr = cdc->attr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (attr->present != Dz1TodecTargetCodecAttrPresent_ar) ERR_SET_OUT(errp, EFAULT);
		else if ((ar = attr->x.ar) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(env->postfix)) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ar->postfix = env->postfix;
			env->postfix = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Array CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Sequence
static Dz1Error seq_append(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = NULL;
		Dz1TodecStreamEntry *seq = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = cdc->seq->add(cdc->seq, env->seq)).code) ERR_OUT(errp);
		else
		{
			env->seq = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Sequence
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Single CODEC Postfix
static Dz1Error codec_set_postfix(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecTargetCodecEntry *cdc = env->cdc;
		if (Dz1Str_isVoid(cdc->postfix) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else if (Dz1Str_isVoid(env->postfix)) ERR_SET_OUT(errp, EFAULT);
		else
		{
			cdc->postfix = env->postfix;
			env->postfix = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Single CODEC Postfix
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Sequence : Padding
static Dz1Error padding_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_pad, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error padding_set_sz(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		u32_t v = 0;
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_pad) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) > 0xFFFF) ERR_SET_OUT(errp, EINVAL);
		else
		{
			seq->x.pad = (u16_t)v;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Sequence : Padding
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Sequence : Constant
static Dz1Error constant_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_value, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((seq->x.value = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error constant_add_value(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v32 = 0;
		Dz1ElasticBuf *buf = NULL;
		Dz1TodecStreamEntry *seq = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((buf = seq->x.value) == NULL) ERR_OUT(errp);
		else if ((v32 = Dz1StrTo32(t->v)) > 0xFF) ERR_SET_OUT(errp, EINVAL);
		else
		{
			u8_t v8 = (u8_t)(v32 & 0xFF);
			if ((*errp = Dz1ElasticBuf_push(buf, (u8_t *)&v8, 1)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Sequence : Constant
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Sequence : Complex
static Dz1Error complex_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		Dz1TodecTargetCodecEntry *cdc = NULL;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if (0) { }
		else if ((cdc = env->cdc) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (cdc->attr != NULL) ERR_SET_OUT(errp, EINVAL);	// complex is structure only
		else if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_bunch, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((seq->x.bunch = Dz1TodecBunchOfSource_new(0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _sum_bit_size(void *ptr, Dz1TodecBunchEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t *dst = (u32_t *)ptr;
	Dz1TodecBunchDataEntry *bits = NULL;
	Dz1TodecBitDescr *descr = NULL;
	switch(p->present)
	{
	case Dz1TodecBunchEntryPresent_pad_bits: (*dst) += p->x.pad_bits; Dz1Error_set(errp, 0); break;
	case Dz1TodecBunchEntryPresent_data_bits:
		if ((bits = p->x.data_bits) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((descr = bits->src_descr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			(*dst) += descr->bit_take; break;
			Dz1Error_set(errp, 0);
		}
	default: ERR_SET_OUT(errp, EFAULT);
	}
	return err;
}

static Dz1Error complex_set_total(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecBunchOfSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_bunch) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.bunch) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = p->seq->travel(p->seq, _sum_bit_size, &v)).code) ERR_OUT(errp);
		else if (v == 0 || Dz1TodecUnitSizeStr((Dz1TodecUnitSize)((v >> 3) & 0xFF)) == NULL) ERR_SET_OUT(errp, EINVAL);
		else
		{
			p->target_sz = (Dz1TodecUnitSize)((v >> 3) & 0xFF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error complex_append(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecBunchOfSource *bunch = NULL;
		Dz1TodecBunchEntry *bch = NULL;
		if (0) { }

		else if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_bunch) ERR_SET_OUT(errp, EFAULT);
		else if ((bunch = seq->x.bunch) == NULL) ERR_SET_OUT(errp, EFAULT);

		else if ((bch = env->bch) != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((*errp = bunch->seq->add(bunch->seq, bch)).code) ERR_OUT(errp);
		else
		{
			env->bch = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Sequence : Complex
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Complex : Bit PAD
static Dz1Error padbit_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->bch != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->bch = Dz1TodecBunchEntry_new(Dz1TodecBunchEntryPresent_pad_bits, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error padbit_set_size(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecBunchEntry *bch = NULL;
		if ((bch = env->bch) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (bch->present != Dz1TodecBunchEntryPresent_pad_bits) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) > 64) ERR_SET_OUT(errp, EINVAL);
		else
		{
			bch->x.pad_bits = (u8_t)(v & 0xFF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Complex : Bit PAD
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Complex : Member
static Dz1Error varbit_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecBunchEntry *bch = NULL;
		Dz1TodecBunchDataEntry *data = NULL;
		if (env->bch != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->bch = bch = Dz1TodecBunchEntry_new(Dz1TodecBunchEntryPresent_data_bits, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((bch->x.data_bits = data = Dz1TodecBunchDataEntry_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((data->src_descr = Dz1TodecBitDescr_new(0, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error varbit_set_obj(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecBunchEntry *bch = NULL;
		Dz1TodecBunchDataEntry *p = NULL;
		if ((bch = env->bch) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (bch->present != Dz1TodecBunchEntryPresent_data_bits) ERR_SET_OUT(errp, EFAULT);
		else if ((p = bch->x.data_bits) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			p->src_name = t->v; t->v = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error varbit_take_sz(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecBunchEntry *bch = NULL;
		Dz1TodecBunchDataEntry *data = NULL;
		Dz1TodecBitDescr *p = NULL;
		if ((bch = env->bch) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (bch->present != Dz1TodecBunchEntryPresent_data_bits) ERR_SET_OUT(errp, EFAULT);
		else if ((data = bch->x.data_bits) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((p = data->src_descr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) > 64) ERR_SET_OUT(errp, EINVAL);
		else
		{
			p->bit_take = (u8_t)(v & 0xFF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error varbit_shf_cnt(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecBunchEntry *bch = NULL;
		Dz1TodecBunchDataEntry *data = NULL;
		Dz1TodecBitDescr *p = NULL;
		if ((bch = env->bch) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (bch->present != Dz1TodecBunchEntryPresent_data_bits) ERR_SET_OUT(errp, EFAULT);
		else if ((data = bch->x.data_bits) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((p = data->src_descr) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) > 64) ERR_SET_OUT(errp, EINVAL);
		else
		{
			p->bit_trim = (u8_t)(v & 0xFF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Complex : Member
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Simple Member
static Dz1Error simple_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_single, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((seq->x.single = Dz1TodecSingleSource_new(NULL, NULL, Dz1TodecUnitSize_max, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error simple_set_src(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecSingleSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_single) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.single) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			p->src_name = t->v;
			t->v = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error simple_set_met(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecSingleSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_single) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.single) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->byte_sel != NULL)
		{
			if ((p->src_descr = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_partial_byte, env->byte_sel, errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->byte_sel = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		else if (env->alter != NULL)
		{
			Dz1TodecSingleDescr *d = NULL;
			if ((p->src_descr = d = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_alter_codec, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				d->x.alter_codec = env->alter;
				env->alter = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		else if (env->restricted != NULL)
		{
			Dz1TodecSingleDescr *d = NULL;
			if ((p->src_descr = d = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_restricted, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				d->x.restricted = env->restricted;
				env->restricted = NULL;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

static Dz1Error simple_set_postfix(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecSingleSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_single) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.single) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(env->postfix) == FALSE)
		{
			if (Dz1Str_isVoid(p->postfix) == FALSE) ERR_SET_OUT(errp, EEXIST);
			else
			{
				p->postfix = env->postfix;
				env->postfix = NULL;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

static Dz1Error simple_set_flag(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v;
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecSingleSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_single) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.single) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) != 8 && v != 16 && v != 32) ERR_SET_OUT(errp, EINVAL);
		else
		{
//			Dz1Thread_printf("@@@ Null Flag of %s is %dbit\n", p->src_name, v);
			p->nul_flag = (Dz1TodecUnitSize)(v / 8);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Simple Member
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Conditional Member
static Dz1Error conditional_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_conditional, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((seq->x.conditional = Dz1TodecConditionalSource_gen(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error conditional_set_src(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecConditionalSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_conditional) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.conditional) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			p->src_name = t->v;
			t->v = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error conditional_set_met(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecConditionalSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_conditional) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.conditional) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (env->byte_sel != NULL)
		{
			if ((p->src_descr = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_partial_byte, env->byte_sel, errp)) == NULL) ERR_OUT(errp);
			else
			{
				env->byte_sel = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		else if (env->alter != NULL)
		{
			Dz1TodecSingleDescr *d = NULL;
			if ((p->src_descr = d = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_alter_codec, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				d->x.alter_codec = env->alter;
				env->alter = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		else if (env->restricted != NULL)
		{
			Dz1TodecSingleDescr *d = NULL;
			if ((p->src_descr = d = Dz1TodecSingleDescr_new(Dz1TodecSingleDescrPresent_restricted, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				d->x.restricted = env->restricted;
				env->restricted = NULL;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

static Dz1Error conditional_set_postfix(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecConditionalSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_conditional) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.conditional) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(env->postfix) == FALSE)
		{
			if (Dz1Str_isVoid(p->postfix) == FALSE) ERR_SET_OUT(errp, EEXIST);
			else
			{
				p->postfix = env->postfix;
				env->postfix = NULL;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return err;
}

static Dz1Error conditional_set_cond(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecConditionalSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_conditional) ERR_SET_OUT(errp, EFAULT);
		else if ((p = seq->x.conditional) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(p->decider) == FALSE) ERR_SET_OUT(errp, EEXIST);
		else
		{
			p->decider = t->v; t->v = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Conditional Member
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Omit Member
static Dz1Error omit_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		if (env->seq != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->seq = seq = Dz1TodecStreamEntry_new(Dz1TodecStreamEntryPresent_omit, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error omit_set_src(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		Dz1TodecStreamEntry *seq = NULL;
		Dz1TodecConditionalSource *p = NULL;
		if ((seq = env->seq) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (seq->present != Dz1TodecStreamEntryPresent_omit) ERR_SET_OUT(errp, EFAULT);
		else if (Dz1Str_isVoid(seq->x.omit) == FALSE) ERR_SET_OUT(errp, EEXIST);
		else
		{
			seq->x.omit = t->v; t->v = NULL;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// Omit Member
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ElemSimpleMethod : subbyte
static Dz1Error byte_descr_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->byte_sel != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->byte_sel = Dz1TodecByteDescr_new(0, 0, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error byte_descr_take_byte(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecByteDescr *p = NULL;
		if ((p = env->byte_sel) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) == 0 || v > 8) ERR_SET_OUT(errp, EINVAL);
		else if (Dz1TodecUnitSizeStr((Dz1TodecUnitSize)(v & 0xF)) == NULL) ERR_SET_OUT(errp, EINVAL);
		else
		{
			p->byte_take = (Dz1TodecUnitSize)(v & 0xF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error byte_descr_shf_byte(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		u32_t v = 0;
		Dz1TodecByteDescr *p = NULL;
		if ((p = env->byte_sel) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((v = Dz1StrTo32(t->v)) > 7) ERR_SET_OUT(errp, EINVAL);
//		else if (v != 0 && Dz1TodecUnitSizeStr((Dz1TodecUnitSize)(v & 0xF)) == NULL) ERR_SET_OUT(errp, EINVAL);
		else
		{
			p->byte_trim = (u8_t)(v & 0xF);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// ElemSimpleMethod : subbyte
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ElemSimpleMethod : alter
static Dz1Error set_alter_name(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->alter != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (t->t == DZ1_PARSER_TOKEN_SYMBOL)
		{
			env->alter = t->v;
			t->v = NULL;
			Dz1Error_set(errp, 0);
		}
		else if (t->t == DZ1_PARSER_TOKEN_STRING)
		{
			char buf[1024] = "@";
			strcat(buf, t->v);
			if ((env->alter = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}
// ElemSimpleMethod : alter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ElemSimpleMethod : fixed
static Dz1Error rstr_fixed_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->restricted != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->restricted = Dz1TodecRestrictDescr_new(Dz1TodecRestrictDescrPresent_fixed, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error rstr_fixed_set(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TodecRestrictDescr *d = NULL;
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if ((d = env->restricted) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (d->present != Dz1TodecRestrictDescrPresent_fixed) ERR_SET_OUT(errp, EFAULT);
		else
		{
			d->x.fixed = Dz1StrTo32(t->v);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// ElemSimpleMethod : fixed
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ElemSimpleMethod : lensz
static Dz1Error rstr_dynamic_create(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (env->restricted != NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((env->restricted = Dz1TodecRestrictDescr_new(Dz1TodecRestrictDescrPresent_dynamic, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error rstr_dynamic_set(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		Dz1TodecRestrictDescr *d = NULL;
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if ((d = env->restricted) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (d->present != Dz1TodecRestrictDescrPresent_dynamic) ERR_SET_OUT(errp, EFAULT);
		else
		{
			u32_t v = Dz1StrTo32(t->v);
			if (Dz1TodecUnitSizeStr((Dz1TodecUnitSize)(v & 0xF)) == NULL) ERR_SET_OUT(errp, EINVAL);
			else d->x.dynamic = (Dz1TodecUnitSize)v;
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
// ElemSimpleMethod : lensz
///////////////////////////////////////////////////////////////////////////////

static Dz1Error set_postfix_suffix(Dz1ParserToken *t, void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ParserUtilEnvEntry *table = (Dz1ParserUtilEnvEntry *)ptr;
	Dz1ParserUtilEnvEntry *node = Dz1ParserUtilEnvEntry_find(table, TODEC_PARSE_ENV);
	if (node == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TodecParseEnv *env = (TodecParseEnv *)node->env;
		// emitting code here
		if (t->t == DZ1_PARSER_TOKEN_SYMBOL)
		{
			env->postfix = t->v;
			t->v = NULL;
			Dz1Error_set(errp, 0);
		}
		else if (t->t == DZ1_PARSER_TOKEN_STRING)
		{
			char buf[1024] = "@";
			strcat(buf, t->v);
			if ((env->postfix = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

#define EMITTER_ENTRY(name)			{ #name, name }
static Dz1ParserUtilEmitterInfo __emitter_table__[] =
{
	EMITTER_ENTRY(create_dst),
	EMITTER_ENTRY(include_add),

	EMITTER_ENTRY(target_create),
	EMITTER_ENTRY(target_set_obj),
	EMITTER_ENTRY(target_append),

	EMITTER_ENTRY(codec_create),
	EMITTER_ENTRY(codec_set_name),
	EMITTER_ENTRY(codec_set_mode),
	EMITTER_ENTRY(codec_append),

	EMITTER_ENTRY(codec_set_postfix),
	EMITTER_ENTRY(attr_descr_create),
	EMITTER_ENTRY(attr_descr_set_mode),
	EMITTER_ENTRY(attr_descr_set_data),

	EMITTER_ENTRY(union_create),
	EMITTER_ENTRY(union_set_present),

	EMITTER_ENTRY(array_create),
	EMITTER_ENTRY(array_set_count),
	EMITTER_ENTRY(array_set_entry),
	EMITTER_ENTRY(array_set_postfix),

	EMITTER_ENTRY(seq_append),

	EMITTER_ENTRY(padding_create),
	EMITTER_ENTRY(padding_set_sz),

	EMITTER_ENTRY(constant_create),
	EMITTER_ENTRY(constant_add_value),

	EMITTER_ENTRY(complex_create),
	EMITTER_ENTRY(complex_set_total),
	EMITTER_ENTRY(complex_append),

	EMITTER_ENTRY(padbit_create),
	EMITTER_ENTRY(padbit_set_size),

	EMITTER_ENTRY(varbit_create),
	EMITTER_ENTRY(varbit_set_obj),
	EMITTER_ENTRY(varbit_take_sz),
	EMITTER_ENTRY(varbit_shf_cnt),

	EMITTER_ENTRY(simple_create),
	EMITTER_ENTRY(simple_set_src),
	EMITTER_ENTRY(simple_set_met),
	EMITTER_ENTRY(simple_set_postfix),
	EMITTER_ENTRY(simple_set_flag),

	EMITTER_ENTRY(conditional_create),
	EMITTER_ENTRY(conditional_set_src),
	EMITTER_ENTRY(conditional_set_met),
	EMITTER_ENTRY(conditional_set_postfix),
	EMITTER_ENTRY(conditional_set_cond),

	EMITTER_ENTRY(omit_create),
	EMITTER_ENTRY(omit_set_src),

	EMITTER_ENTRY(byte_descr_create),
	EMITTER_ENTRY(byte_descr_take_byte),
	EMITTER_ENTRY(byte_descr_shf_byte),

	EMITTER_ENTRY(set_alter_name),

	EMITTER_ENTRY(rstr_fixed_create),
	EMITTER_ENTRY(rstr_fixed_set),

	EMITTER_ENTRY(rstr_dynamic_create),
	EMITTER_ENTRY(rstr_dynamic_set),

	EMITTER_ENTRY(set_postfix_suffix),
	Dz1ParserUtilEmitterInfoLast
};

static Dz1ParserHandle *Dz1TodecParser_create(Dz1Error *errp)
{
	Dz1ParserHandle *parser = Dz1Parser_new(errp);
	if (parser == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);
		if (0) { }
		else if ((*errp = Dz1ParserUtil_addEmitter(parser, __emitter_table__)).code) ERR_OUT(errp);
		else if ((*errp = Dz1ParserInit_parse(parser, __syntax_str__)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Parser_delAndSetNull, (void *)&parser);
	}
	return parser;
}

Dz1Todec *Dz1Todec_parse(str_t src_text, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Todec *ret = NULL;
	Dz1ParserHandle *parser = NULL;
	if ((parser = Dz1TodecParser_create(errp)) == NULL) ERR_OUT(errp);
	else
	{
		// Dz1ParserIPv4Env ipv4env;
		// Dz1ParserTcpListenAddrEnv listenAddrEnv;
		TodecParseEnv user_env = { NULL, };
		Dz1ParserUtilEnvEntry parse_env[] =
		{
		//	Dz1ParserIPv4Env_entry(&ipv4env),
		//	Dz1ParserTcpListenAddrEnv_entrp(&listenAddrEnv),
			{ TODEC_PARSE_ENV, &user_env },
			Dz1ParserEnvEntryLast
		};

		pthread_cleanup_push(TodecParseEnv_cleanup, (void *)&user_env);
		pthread_cleanup_push(Dz1Parser_delAndSetNull, (void *)&parser);

		if ((*errp = Dz1ParserUtilEnv_check(parse_env)).code) ERR_OUT(errp);
// 		else if ((*errp = Dz1ParserUtil_addEmitter(parser, __emitter_table__)).code) ERR_OUT(errp);
// 		else if ((*errp = Dz1ParserInit_parse(parser, __syntax_str__)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_prepare(parser, src_text)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Parser_process(parser, "Main", (void *)parse_env, 0)).code)
		{
			Dz1Thread_printf("Dz1ParserHandle_parse() : Parse Fail at %u line\n", Dz1Parser_getLineNum(parser));
			ERR_OUT(errp);
		}
		else
		{
			ret = user_env.dst;
			user_env.dst = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1Parser_delAndSetNull, (void *)&parser);
		pthread_cleanup_pop(1); // (TodecParseEnv_cleanup, (void *)&user_env);
	}
	return ret;
}

static bool_t _is_symbol_letter(char c)
{
	bool_t ret = FALSE;
	switch(c)
	{
	case '_': ret = TRUE; break;
	}
	return ret;
}

void Dz1Todec_syntax_dump(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBuf *elb = Dz1ElasticBuf_new(256, FALSE, errp);
	if (elb == NULL) Dz1Thread_printf(__syntax_str__);
	else
	{
		bool_t start_of_line = TRUE;
		u32_t col = 0, sp_len = 0;

		str_t sp = __syntax_str__;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		
		Dz1ElasticBuf_pushChrA(elb, '*', errp); col++;	// adjust start of line
		
		while (errp->code == 0 && *sp != 0)
		{
			switch(*sp)
			{
			case ';': start_of_line = TRUE;
			case '\r': sp++; break;
			case '\t': 
				sp++; 
				sp_len = 4 - (col % 4);
				if (Dz1ElasticBuf_pushStrNA(elb, "    ", sp_len, errp) == FALSE) ERR_OUT(errp); 
				else 
				{ 
					col += sp_len;
					Dz1Error_set(errp, 0); 
				} 
				break;
			case '=':
				sp++;												// skip '='
				if (start_of_line)
				{
					start_of_line = FALSE;
					if (Dz1ElasticBuf_pushChrA(elb, '=', errp) == FALSE) ERR_OUT(errp);
					else
					{
						col++;
						Dz1Error_set(errp, 0);
					}
				}
				else
				{
					while(*sp && isspace((int)*sp & 0xFF)) sp++;		// skip white space

					if (*sp && isalpha(*sp))
					{
						while(*sp && (isalnum((int)*sp & 0xFF) || _is_symbol_letter(*sp)) )
							sp++;										// skip emitter name
					}
				}
				break;
			case ' ':
				sp++;
				if (Dz1ElasticBuf_pushChrA(elb, ' ', errp) == FALSE) ERR_OUT(errp); 
				else
				{
					col++;
					while(*sp && *sp == ' ') sp++;
					Dz1Error_set(errp, 0);
				}
				break;
			case '\n': 
				sp++; 
				if (Dz1ElasticBuf_pushChrA(elb, '\n', errp) == FALSE) ERR_OUT(errp);
				else if (Dz1ElasticBuf_pushChrA(elb, '*', errp) == FALSE) ERR_OUT(errp);
				else
				{ 
					col = 1;	// adjust start of line
					Dz1Error_set(errp, 0); 
				} 
				break;
			default:
				if (Dz1ElasticBuf_pushChrA(elb, *sp++, errp) == FALSE) ERR_OUT(errp); 
				else 
				{
					col++;
					Dz1Error_set(errp, 0);
				}
				break;
			}
		}

		if (errp->code == 0)
		{
			str_t output = Dz1ElasticBuf_flattenStrAndPurgeA(elb, errp);
			if (output == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&output);
				Dz1Thread_printf(output);
				Dz1Thread_printf(Dz1T("\n"));
				pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&output);
			}
		}
		else Dz1Thread_printf(__syntax_str__);

		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
}
