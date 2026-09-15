#include <dz1_thread_stdio.h>
#include "Dz1JsonStructUtil.h"
#include <Dz1Json.h>

///////////////////////////////////////////////////////////////////////////////
// TDC Support
void Dz1JsonToken_dump(Dz1JsonToken *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_tprintf(tab, Dz1T("%s(%d):"), Dz1JsonTokenTypeStr(p->t), p->t);
		if (p->v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
		else Dz1Str_dump(p->v, tab);
	}
}

void Dz1JsonVarBind_del(Dz1JsonVarBind *p)
{
	if (p == NULL) return;
	else
	{
		Dz1JsonSpecEntry *type = p->type;
		if (type != NULL && type->del != NULL && p->data != NULL)
		{
			type->del(p->data);
			p->data = NULL;
		}
		Dz1Free(p);
	}
}


void Dz1JsonOutputEntry_del(Dz1JsonOutputEntry *p)
{
	if (p == NULL) return;
	if (p->result != NULL && p->result_del != NULL)
	{
		p->result_del(p->result);
		p->result = NULL;
	}
	Dz1Free(p);
}

void Dz1JsonOutputFifo_del(Dz1JsonOutputFifo *p)
{
	if (p == NULL) return;
	if (p->head != NULL)
	{
		Dz1JsonOutputEntry *node = p->head, *next = NULL;
		while(node != NULL)
		{
			next = node->next;
			node->next = NULL;
			Dz1JsonOutputEntry_del(node);
			node = next;
		}
	}
	Dz1Free(p);
}

void Dz1JsonSpecChild_dump(Dz1JsonSpecChild *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		TCHAR buf[1024];
		Dz1SNPRINTF(buf, 1023, Dz1Text("%3d %s %s"), p->index, p->type, p->name);
		Dz1Str_dump(buf, 0);
	}
}

void Dz1JsonStack_dump(Dz1JsonStack *p, int tab)
{
	Dz1JsonVarBind *var = NULL;
	Dz1JsonSpecEntry *type = NULL;

	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->data == NULL) Dz1Thread_tprintf(tab, Dz1T("data = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("data.")); Dz1JsonStackData_dump(p->data, tab); /* using dump func */ }

	if ((var = p->dst_var) == NULL)			Dz1Thread_tprintf(tab, Dz1T("dst_var = NULL\n"));
	else if ((type = var->type) == NULL)	Dz1Thread_tprintf(tab, Dz1T("dst_var = (undef)\n"));
	else									Dz1Thread_tprintf(tab, Dz1T("dst_var = %s\n"), type->name);

	if (p->ret_var == NULL) Dz1Thread_tprintf(tab, Dz1T("ret_var = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("ret_var = ")); Dz1JsonVarBind_dump(p->ret_var, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("next = %p\n"), p->next);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
// TDC Support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1JsonOutputFifo
void Dz1JsonOutputFifo_push(Dz1JsonOutputFifo *p, Dz1JsonOutputEntry **node)
{
	if (p->head == NULL)
		p->head = p->tail = (*node);
	else
	{
		Dz1JsonOutputEntry *tail = p->tail;
		tail->next = (*node);
		p->tail = (*node);
	}
	(*node) = NULL;
}

Dz1JsonOutputEntry *Dz1JsonOutputFifo_pop(Dz1JsonOutputFifo *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonOutputEntry *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->head == NULL) Dz1Error_set(errp, ENOENT);
	else 
	{
		ret = p->head;
		if (p->head == p->tail)
			p->head = p->tail = NULL;
		else
			p->head = ret->next;
		ret->next = NULL;
	}
	return ret;
}

bool_t Dz1JsonOutputFifo_isEmpty(Dz1JsonOutputFifo *p)
{
	bool_t ret = TRUE;
	if (p != NULL && p->head != NULL) ret = FALSE;
	return ret;
}
// Dz1JsonOutputFifo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpecChilds
typedef struct JsonSpecChildsFindByIdxArg
{
	Dz1JsonSpecChild *ret;
	int idx;
} JsonSpecChildsFindByIdxArg;

static Dz1Error _Dz1JsonSpecChilds_findByIdx(void *ptr, Dz1JsonSpecChild *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	JsonSpecChildsFindByIdxArg *arg = (JsonSpecChildsFindByIdxArg *)ptr;
	if (p->index == arg->idx)
	{
		arg->ret = p;
		Dz1Error_set(errp, EEXIST);
	}
	return err;
}

Dz1JsonSpecChild *Dz1JsonSpecChilds_findByIdx(Dz1JsonSpecChilds *list, int idx)
{
	JsonSpecChildsFindByIdxArg arg = { NULL, idx };
	list->travel(list, _Dz1JsonSpecChilds_findByIdx, (void *)&arg);
	return arg.ret;
}

Dz1JsonSpecChild *Dz1JsonSpecChilds_findByName(Dz1JsonSpecChilds *list, Dz1Str name)
{
	Dz1JsonSpecChild key = { name };
	return list->find(list, &key);
}
// Dz1JsonSpecChilds
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec
Dz1JsonSpecEntry *Dz1JsonSpec_findType(Dz1JsonSpec *spec, Dz1Str type_name)
{
	Dz1JsonSpecEntry key = { type_name };
	return spec->types->find(spec->types, &key);
}
// Dz1JsonSpec
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1JsonConstruct_apply_child_data(Dz1JsonVarBind *own, Dz1JsonVarBind *child, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1JsonSpecEntry *own_spe = own->type;
	Dz1JsonSpecData *own_spd = own_spe->data;
	Dz1JsonSpecConstruct *own_cst = own_spd->x.cst;
	if (own_cst->set_child(own->data, child, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// New Line Map
static NewLineMap newLineMap[] = {
	{ Dz1JsonNewLine_continuous,	Dz1Text(""),		0 },
	{ Dz1JsonNewLine_cr,			Dz1Text("\r"),		1 },		// 0x0D
	{ Dz1JsonNewLine_lf,			Dz1Text("\n"),		1 },		// 0x0A
	{ Dz1JsonNewLine_crlf,			Dz1Text("\r\n"),	2 },		// 0x0D0A
	{ Dz1JsonNewLine_max,			NULL,				0 },
};

NewLineMap *Dz1Json_stringify_nl(Dz1JsonNewLine mode)
{
	switch(mode)
	{
	case Dz1JsonNewLine_continuous:
	case Dz1JsonNewLine_cr:
	case Dz1JsonNewLine_lf:
	case Dz1JsonNewLine_crlf:
		return &newLineMap[mode];
	case Dz1JsonNewLine_max:
	default:
		return &newLineMap[Dz1JsonNewLine_lf];
	}
}
// New Line Map
///////////////////////////////////////////////////////////////////////////////

typedef enum StringConvToHostMode
{
	StringConvToHostMode_normal,
	StringConvToHostMode_escaped,
	StringConvToHostMode_complete
} StringConvToHostMode;

str_t Dz1JsonUtilA_stringConvToHost(const str_t json_coded_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	size_t len = 0;
	if (json_coded_str == NULL || (len = strlen(json_coded_str)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (json_coded_str[0] != '\"'  || len < 2 || json_coded_str[len - 1] != '\"') ERR_SET_OUT(errp, EPERM);
	else if ((ret = Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *cp = json_coded_str, *dp = ret;
		StringConvToHostMode mode = StringConvToHostMode_normal;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		cp++;	// pass '\"'
		while(errp->code == 0 && *cp && len && mode != StringConvToHostMode_complete)
		{
			switch(mode)
			{
			default:
			case StringConvToHostMode_normal:
				switch(*cp)
				{
				case '\\': mode = StringConvToHostMode_escaped; break;
				case '\"': mode = StringConvToHostMode_complete; break;
				default: *dp++ = *cp++; len--; break;
				}
				break;
			case StringConvToHostMode_escaped:
				switch(*cp)
				{
				case 'r': *dp++ = '\r'; cp++; len--; mode = StringConvToHostMode_normal; break;
				case 'n': *dp++ = '\n'; cp++; len--; mode = StringConvToHostMode_normal; break;
				case 't': *dp++ = '\t'; cp++; len--; mode = StringConvToHostMode_normal; break;
				case 'u': 
					cp++;	// pass 'u'
					len--;
					if (len < 4)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "JSON string parse fail : offset %u\n", (u32_t)(cp - json_coded_str));
						ERR_SET_OUT(errp, EFAULT);
					}
					else
					{
						char temp[] = { '0', 'x', cp[0], cp[1], cp[2], cp[3], 0};
						u32_t v = Dz1Ato32(temp);
						*dp++ = (char)(v & 0xFF);
						cp += 4;
						len -= 4;
					}
					break;
				}
			}
		}

		if (mode != StringConvToHostMode_complete && errp->code == 0) ERR_SET_OUT(errp, EFAULT);
		else *dp = 0;
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1JsonUtilW_stringConvToHost(const wstr_t json_coded_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	size_t len = 0;
	if (json_coded_str == NULL || (len = wcslen(json_coded_str)) == 0) ERR_SET_OUT(errp, EINVAL);
	else if (json_coded_str[0] != L'\"'  || len < 2 || json_coded_str[len - 1] != L'\"') ERR_SET_OUT(errp, EPERM);
	else if ((ret = Dz1Calloc(sizeof(wchar_t), len + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t *cp = json_coded_str, *dp = ret;
		StringConvToHostMode mode = StringConvToHostMode_normal;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		cp++;	// pass '\"'
		while(errp->code == 0 && *cp && len)
		{
			switch(mode)
			{
			default:
			case StringConvToHostMode_normal:
				switch(*cp)
				{
				case L'\\': mode = StringConvToHostMode_escaped; break;
				case L'\"': mode = StringConvToHostMode_complete; break;
				default: *dp++ = *cp; break;
				}
				cp++; len--;
				break;
			case StringConvToHostMode_escaped:
				switch(*cp)
				{
				case L'r': *dp++ = L'\r'; cp++; len--; break;
				case L'n': *dp++ = L'\n'; cp++; len--; break;
				case L't': *dp++ = L'\t'; cp++; len--; break;
				case L'u': 
					cp++; len--;	// pass 'u'
					if (len < 4)
					{
						Dz1Thread_log(DZ1_THREAD_LOG_ERROR, "JSON string parse fail : offset %u\n", (u32_t)(cp - json_coded_str));
						ERR_SET_OUT(errp, EFAULT);
					}
					else
					{
						wchar_t temp[] = { L'0', L'x', cp[0], cp[1], cp[2], cp[3], 0};
						u32_t v = Dz1Wto32(temp);
						*dp++ = (wchar_t)(v & 0xFFFF);
						cp += 4;
						len -= 4;
					}
					break;
				default: *dp++ = *cp++; len--; break;
				}
				mode = StringConvToHostMode_normal; 
				break;
			}
		}

		if (mode != StringConvToHostMode_complete && errp->code == 0) ERR_SET_OUT(errp, EFAULT);
		else *dp = 0;
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

static void *_Dz1JosnUtil_parseFile(Dz1Str parse_type, Dz1Binary *bin, Dz1JsonSpec *spec, Dz1Error *errp)
{
	void *ret = NULL;
	Dz1Json *j = NULL;
	if ((j = Dz1Json_new("UTF-8", spec, parse_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&j);
		if ((sz = Dz1Json_push_stream(j, bin->data, bin->size, errp)) < 0) ERR_OUT(errp);
		else if (sz == 0) ERR_SET_OUT(errp, EPIPE);
		else if ((status = Dz1Json_parse(j, errp)) < 0) ERR_OUT(errp);
		else if (status == 0) ERR_SET_OUT(errp, EINVAL);
		else if ((ret = Dz1Json_read(j, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&j);
	}
	return ret;
}

void *Dz1JosnUtil_parseFile(Dz1Str parse_type, Dz1Str fn, Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(fn) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFile_load(fn, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = _Dz1JosnUtil_parseFile(parse_type, bin, spec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

void *Dz1JosnUtil_parseFile2(Dz1Str parse_type, Dz1Str path, Dz1Str name_ext,		  Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name_ext) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFile_load2(path, name_ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = _Dz1JosnUtil_parseFile(parse_type, bin, spec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

void *Dz1JosnUtil_parseFile3(Dz1Str parse_type, Dz1Str path, Dz1Str name, Dz1Str ext, Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name) || Dz1Str_isVoid(ext) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFile_load3(path, name, ext, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = _Dz1JosnUtil_parseFile(parse_type, bin, spec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

static Dz1Json *_Dz1JosnUtil_genJsonEmiter(Dz1Str emit_type, void *emit_ptr, Dz1JsonSpec *spec, Dz1Error *errp)
{
	Dz1Json *j = NULL;
	if ((j = Dz1Json_new("UTF-8", spec, emit_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&j);
		if (Dz1Json_stringify(j, emit_type, emit_ptr, Dz1JsonNewLine_crlf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Json_delAndSetNull, (void *)&j);
	}
	return j;
}

static bool_t _Dz1JosnUtil_emitText(Dz1Json *j, FILE *fp, Dz1Error *errp)
{
	u8_t buf[256];
	ssize_t sz = 0, written = 0;;
	while(errp->code == 0 && (sz = Dz1Json_squeeze(j, buf, sizeof(buf), errp)) > 0)
	{
		if ((written = fwrite(buf, sizeof(u8_t), (size_t)sz, fp)) != sz)
			ERR_SET_OUT(errp, EPIPE);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1JosnUtil_emitFile( Dz1Str emit_type, void *emit_ptr, Dz1Str fn, Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json *j = NULL;
	if (Dz1Str_isVoid(emit_type) || emit_ptr == NULL || Dz1Str_isVoid(fn) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((j = _Dz1JosnUtil_genJsonEmiter(emit_type, emit_ptr, spec, errp)) == NULL) ERR_OUT(errp);
	else
	{
		FILE *fp = NULL;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&j);
		if ((fp = Dz1FileStream_open(fn, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
			if (_Dz1JosnUtil_emitText(j, fp, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&j);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1JosnUtil_emitFile2(Dz1Str emit_type, void *emit_ptr, Dz1Str path, Dz1Str name_ext, Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json *j = NULL;
	if (Dz1Str_isVoid(emit_type) || emit_ptr == NULL || Dz1Str_isVoid(name_ext) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((j = _Dz1JosnUtil_genJsonEmiter(emit_type, emit_ptr, spec, errp)) == NULL) ERR_OUT(errp);
	else
	{
		FILE *fp = NULL;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&j);
		if ((fp = Dz1FileStream_open2(path, name_ext, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
			if (_Dz1JosnUtil_emitText(j, fp, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&j);
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t Dz1JosnUtil_emitFile3(Dz1Str emit_type, void *emit_ptr, Dz1Str path, Dz1Str name, Dz1Str ext, Dz1JsonSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Json *j = NULL;
	if (Dz1Str_isVoid(emit_type) || emit_ptr == NULL || Dz1Str_isVoid(name) || Dz1Str_isVoid(ext) || spec == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((j = _Dz1JosnUtil_genJsonEmiter(emit_type, emit_ptr, spec, errp)) == NULL) ERR_OUT(errp);
	else
	{
		FILE *fp = NULL;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&j);
		if ((fp = Dz1FileStream_open3(path, name, ext, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);
			if (_Dz1JosnUtil_emitText(j, fp, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&j);
	}
	return ERR_IS_SUCCESS(errp);
}

