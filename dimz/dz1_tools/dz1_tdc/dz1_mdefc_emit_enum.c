#include <dz1_thread_stdio.h>
#include <dz1_str.h>
#include <dz1_parser.h>
#include "dz1_mdefc_env.h"
#include "dz1_mdefc_emit.h"

static bool_t _is_hex_letter(char c)
{
	if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return TRUE;
	else return FALSE;
}

static bool_t isPrefixDigitStr(str_t str)
{
	bool_t include_hex = FALSE;
	if (*str == '0')
	{
		switch(*(str + 1))
		{
		case 0: break;
		case 'x': include_hex = TRUE;
		case 'b': 
		case 'o': 
			str += 2; 
			break;
		default: 
			return FALSE;
		}
	}
	else if (*str == '-' || *str == '+') str++;

	if (*str == '\0') return FALSE;
	else
	{
		bool_t pass = FALSE;
		while(*str)
		{
			pass = FALSE;
			if (include_hex && _is_hex_letter(*str)) pass = TRUE;
			else if (isdigit(*str)) pass = TRUE;

			if (pass == FALSE) return FALSE;

			str++;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Enum
static Dz1Error new_enum(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	if (p->obj) ObjectInfo_del(p->obj);

	if ((p->obj = ObjectInfo_new(ObjectType_enumerate, NULL, NULL, OBJECT_API_BASE, NULL, &err)) == NULL) ERR_OUT(&err);
	else if ((p->obj->info = EnumInfo_new(FALSE, &err)) == NULL) ERR_OUT(&err);

	return err;
}


static Dz1Error set_enum_entry_name(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	tValTake(p->enumEntry.name);

	return err;
}

static Dz1Error set_enum_entry_valStr(Dz1ParserToken *t, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;
	EnumEntry *ee = NULL;

	if (t->t == DZ1_PARSER_TOKEN_SYMBOL)
	{
		if ((ee = p->module->findEnum(p->module, t->v)) == NULL)
		{
			Dz1Thread_printf("set_enum_entry_valStr() : \"%s\" is unknown Constant or Enumeration Name\n", t->v);
			ERR_SET_OUT(errp, ESRCH);
		}
		else
		{
			tValTake(p->enumEntry.valStr);
			Dz1Error_set(errp, 0);
		}
	}
	else if (t->t == DZ1_PARSER_TOKEN_STRING)
	{
		tValTake(p->enumEntry.valStr);
		Dz1Error_set(errp, 0);
	}
	else if ((t->t & DZ1_PARSER_TOKEN_NUMBER_MASK) == DZ1_PARSER_TOKEN_NUMBER)
	{
		if (isPrefixDigitStr(t->v)== FALSE)
		{
			Dz1Thread_printf("set_enum_entry_valStr() : \"%s\" is not valid number\n", t->v);
			ERR_SET_OUT(errp, EINVAL);
		}
		else
		{
			char buf[64];
			p->enumEntry.value = (s32_t)Dz1Ato32(t->v);
			snprintf(buf, 64, "%d", p->enumEntry.value);
			if ((p->enumEntry.valStr = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else
	{
		Dz1Thread_printf("token type %08X is not handled\n", t->t);
		ERR_SET_OUT(errp, EINVAL);
	}
//	Dz1Thread_printf("enum = "); EnumEntry_dump(&p->enumEntry, 0);

	return err;
}

static Dz1Error add_enum_entry(Dz1ParserToken *t, void *param)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1MdefcParserEnv *p = (Dz1MdefcParserEnv *)param;

	EnumInfo *e = (EnumInfo *)p->obj->info;
	if ((err = e->enums->add(e->enums, p->enumEntry.name, p->enumEntry.valStr, p->enumEntry.valStr ? NULL : &p->enumEntry.value)).code) ERR_OUT(&err);
	else
	{
		if (p->enumEntry.name) { Dz1Str_del(p->enumEntry.name); p->enumEntry.name = NULL; } // modified by gm 20230602
		if (p->enumEntry.valStr) { Dz1Str_del(p->enumEntry.valStr); p->enumEntry.valStr = NULL; }; // modified by gm 20230602
		p->enumEntry.value = 0;
	}

	return err;
}
// Enum
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1MdefcEmiter_InitEnum(void *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Parser_addEmiter(p, "new_enum", new_enum)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_enum_entry_name", set_enum_entry_name)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "set_enum_entry_valStr", set_enum_entry_valStr)).code) { ERR_OUT(errp); }
	else if ((*errp = Dz1Parser_addEmiter(p, "add_enum_entry", add_enum_entry)).code) { ERR_OUT(errp); }
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
