#include <dz1_fifo.h>
#include "Dz1CodeGenTodecPublish.h"
#include "Dz1CodeGenTodecArray.h"
#include "Dz1CodeGenTodecStruct.h"
#include "Dz1CodeGenTodecUnion.h"

s32_t _resolve_primitive_type_size(PrimitiveInfo *info)
{
	if (Dz1STRSTR(info->native, Dz1Text("64")) != NULL) return 8;
	else if (Dz1STRSTR(info->native, Dz1Text("32")) != NULL) return 4;
	else if (Dz1STRSTR(info->native, Dz1Text("16")) != NULL) return 2;
	else if (Dz1STRSTR(info->native, Dz1Text("8")) != NULL) return 1;
	else if (Dz1STRSTR(info->native, Dz1Text("time_t")) != NULL) return -1;
	else return 0;
}

typedef struct PublishApiMap
{
	ObjectType				 type;
	Dz1Error				 (*publish)(FILE *fp, ConstructCodecEntry *p, str_t endian);
} PublishApiMap;

static PublishApiMap *PublishApiMap_find(PublishApiMap *table, ObjectType type)
{
	PublishApiMap *i;
	for (i = table; i->type != ObjectType_max; i++)
		if (i->type == type) return i;
	return NULL;
}

static PublishApiMap publishGenMap[] =
{
	{ ObjectType_structure,	ConstructCodecEntry_struct_gen_publish },
	{ ObjectType_union,		ConstructCodecEntry_union_gen_publish },
	{ ObjectType_array,		ConstructCodecEntry_array_gen_publish }, 
	{ ObjectType_max,		NULL }
};

static PublishApiMap publishReadWriteMap[] =
{
	{ ObjectType_structure,	ConstructCodecEntry_struct_rw_publish },
	{ ObjectType_union,		ConstructCodecEntry_union_rw_publish },
	{ ObjectType_array,		ConstructCodecEntry_array_rw_publish },
	{ ObjectType_max,		NULL }
};

///////////////////////////////////////////////////////////////////////////////
// ConstructCodecEntry CODEC Source
static Dz1Error PublishApi_publish_write_src(FILE *fp, ConstructCodecEntry *p, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ObjectInfo *obj = p->parent_obj;
	ObjectType type = ObjectInfo_typeOf(obj);
	PublishApiMap *api = PublishApiMap_find(publishReadWriteMap, type);
	if (api == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((*errp = api->publish(fp, p, endian)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// ConstructCodecEntry CODEC Source
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ConstructCodecList CODEC Source
typedef struct CodecListPublishArg
{
	FILE *fp;
	str_t endian;
	bool_t first;
	bool_t has_public_api;
} CodecListPublishArg;

static Dz1Error CodecList_publish_src(void *ptr, ConstructCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg *arg = (CodecListPublishArg *)ptr;

	if (p->mode != ConstructCodecMode_static) arg->has_public_api = TRUE;

	if (p->mode == ConstructCodecMode_header) Dz1Error_set(errp, 0);
	else
	{
		if (arg->first) arg->first = FALSE;
		else Dz1Thread_fprintf(arg->fp, "" NEW_LINE);

		if ((*errp = PublishApi_publish_write_src(arg->fp, p, arg->endian)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error ConstructCodecList_publish_src(FILE *fp, ConstructCodecList *list, str_t endian, bool_t *has_public_api)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg arg = { fp, endian, TRUE, FALSE };
	if ((*errp = list->travel(list, CodecList_publish_src, (void *)&arg)).code) ERR_OUT(errp);
	else
	{
		(*has_public_api) = arg.has_public_api;
		Dz1Error_set(errp, 0);
	}
	return err;
}
// ConstructCodecList CODEC Source
///////////////////////////////////////////////////////////////////////////////

static Dz1Error CodecList_publicExist(void *ptr, ConstructCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t *ret = (bool_t *)ptr;
	if (p->mode != ConstructCodecMode_static) { (*ret) = TRUE; Dz1Error_set(errp, EEXIST); }
	return err;
}

static bool_t ConstructCodecList_publicExist(ConstructCodecList *list)
{
	bool_t ret = FALSE;
	list->travel(list, CodecList_publicExist, (void *)&ret);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// ConstructObjectEntry CODEC Source
Dz1Error ConstructObjectEntry_publish_src(FILE *fp, ConstructObjectEntry *p, str_t endian, bool_t *_has_public_api)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t _hpa = FALSE, *hpa = _has_public_api != NULL ? _has_public_api : &_hpa;
	if (p->codecs->count(p->codecs) > 0)
	{
		ObjectInfo *obj = p->obj;
		ObjectType type = ObjectInfo_typeOf(obj);
		PublishApiMap *gen_api = PublishApiMap_find(publishGenMap, type);
		if (gen_api == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ConstructCodecEntry temp = { NULL, p->obj, FALSE, NULL };
			temp.mode = ConstructCodecList_publicExist(p->codecs) ? ConstructCodecMode_public : ConstructCodecMode_static;
			Dz1Thread_fprintf(fp, "///////////////////////////////////////////////////////////////////////////////" NEW_LINE);
			Dz1Thread_fprintf(fp, "// %s CODEC" NEW_LINE, obj->name);
			if ((*errp = gen_api->publish(fp, &temp, endian)).code) ERR_OUT(errp);									// source GEN
			else if ((*errp = ConstructCodecList_publish_src(fp, p->codecs, endian, hpa)).code) ERR_OUT(errp);		// source READ/WRITE
			Dz1Thread_fprintf(fp, "// %s CODEC" NEW_LINE, obj->name);
			Dz1Thread_fprintf(fp, "///////////////////////////////////////////////////////////////////////////////" NEW_LINE NEW_LINE);
		}
	}
	return err;
}
// ConstructObjectEntry CODEC Source
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ConstructObjectList CODEC Source
// static Dz1Error ObjectList_publish(void *ptr, ConstructObjectEntry *p)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 
// 	CodecListPublishArg *arg = (CodecListPublishArg *)ptr;
// 
// 	if ((*errp = ConstructObjectEntry_publish_src(arg->fp, p, arg->endian, &arg->has_public_api)).code) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 
// 	return err;
// }

static Dz1Error ConstructObjectList_publish(FILE *fp, ConstructObjectList *list, str_t endian, Dz1MdefcModule *seq, bool_t *has_public_api)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Fifo *fifo = seq->objFifo;
	void *c = Dz1FifoCursor_new(fifo, errp);
	ObjectInfo *obj = NULL;
	for(Dz1FifoCursorForward(c))
	{
		if ((obj = Dz1FifoCursor_data(c)) != NULL)
		{
			ConstructObjectEntry key = { obj->name }, *node = list->find(list, &key);
			if (node != NULL)
			{
				if ((*errp = ConstructObjectEntry_publish_src(fp, node, endian, has_public_api)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}

// 	CodecListPublishArg arg = { fp, endian, FALSE };
// 	if ((*errp = list->travel(list, ObjectList_publish, (void *)&arg)).code) ERR_OUT(errp);
// 	else
// 	{
// 		Dz1Error_set(errp, 0);
// 		(*has_public_api) = arg.has_public_api;
// 	}
	return err;
}
// ConstructObjectList CODEC Source
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Source
Dz1Error ConstructCodec_publish_src(ConstructCodec *p, str_t path, str_t filename)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	FILE *fp = Dz1FileStream_open3(path, filename, "c", "wb", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		bool_t has_public_api = FALSE;
		pthread_cleanup_push(Dz1FileStream_cancelAndSetNull, (void *)&fp);

		Dz1Thread_fprintf(fp, "#include <dz1_malloc.h>" NEW_LINE);
		Dz1Thread_fprintf(fp, "#include \"%s.h\"" NEW_LINE, filename);
		Dz1Thread_fprintf(fp, "" NEW_LINE);
		if ((*errp = ConstructObjectList_publish(fp, p->objs, p->endian, p->module, &has_public_api)).code) ERR_OUT(errp);

		if (has_public_api == FALSE)
		{
			Dz1Thread_fprintf(fp, "" NEW_LINE);
			Dz1Thread_fprintf(fp, "extern int __avoid_empty_symbol__%s = 0;" NEW_LINE, filename);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancelAndSetNull, (void *)&fp);
	}
	return err;
}
// CODEC Source
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CODEC Header
static Dz1Error CodecList_publish_hdr(void *ptr, ConstructCodecEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg *arg = (CodecListPublishArg *)ptr;

	if (p->mode != ConstructCodecMode_static)
	{
		ObjectInfo *obj = p->parent_obj;
		str_t suffix = (p->opt_suffix != NULL && p->opt_suffix[0] != 0) ? p->opt_suffix : "";
		Dz1Thread_fprintf(arg->fp, "DZ1_CPPLINK ssize_t %s%s_write(Dz1Stream *dst, void *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);" NEW_LINE, obj->name, suffix);
		Dz1Thread_fprintf(arg->fp, "DZ1_CPPLINK ssize_t %s%s_read(void *dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);" NEW_LINE, obj->name, suffix);
	}
	return err;
}

static Dz1Error ConstructCodecList_publish_hdr(FILE *fp, ConstructCodecList *list, str_t endian)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg arg = { fp, endian, FALSE };
	if ((*errp = list->travel(list, CodecList_publish_hdr, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error ConstructObjectEntry_publish_hdr(FILE *fp, ConstructObjectEntry *p, str_t endian, bool_t *printed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->codecs->count(p->codecs) > 0)
	{
		ObjectInfo *obj = p->obj;
		bool_t has_public = ConstructCodecList_publicExist(p->codecs);

		if (has_public)
		{
			Dz1Thread_fprintf(fp, "DZ1_CPPLINK %s *%s_gen(Dz1Error *err);" NEW_LINE, obj->name, obj->name);
			if ((*errp = ConstructCodecList_publish_hdr(fp, p->codecs, endian)).code) ERR_OUT(errp);
			Dz1Thread_fprintf(fp, "" NEW_LINE);
			(*printed) = TRUE;
		}
	}
	return err;
}

static Dz1Error ConstructObjectList_publish_hdr(FILE *fp, ConstructObjectList *list, str_t endian, Dz1MdefcModule *seq, bool_t *printed)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Fifo *fifo = seq->objFifo;
	void *c = Dz1FifoCursor_new(fifo, errp);
	ObjectInfo *obj = NULL;
	for(Dz1FifoCursorForward(c))
	{
		if ((obj = Dz1FifoCursor_data(c)) != NULL)
		{
			ConstructObjectEntry key = { obj->name }, *node = list->find(list, &key);
			if (node != NULL)
			{
				if ((*errp = ConstructObjectEntry_publish_hdr(fp, node, endian, printed)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}

	return err;
}

static Dz1Error ConstructCodecIncludeEntry_publish_hdr(FILE *fp, ConstructCodecIncludeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p != NULL)
	{
		if (p->use_codate)
			Dz1Thread_fprintf(fp, "#include \"%s\"" NEW_LINE, p->filename_ext);
		else Dz1Thread_fprintf(fp, "#include <%s>" NEW_LINE, p->filename_ext);
	}
	return err;
}

static Dz1Error _IncludeList_publish_hdr(void *ptr, ConstructCodecIncludeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg *arg = (CodecListPublishArg *)ptr;
	if ((*errp = ConstructCodecIncludeEntry_publish_hdr(arg->fp, p)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error ConstructCodecIncludeList_publish_hdr(FILE *fp, ConstructCodecIncludeList *list)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CodecListPublishArg arg = { fp, NULL, TRUE, FALSE };
	if ((*errp = list->travel(list, _IncludeList_publish_hdr, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error ConstructCodec_publish_hdr(ConstructCodec *p, str_t path, str_t filename)
{
	bool_t printed = FALSE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	FILE *fp = Dz1FileStream_open3(path, filename, "h", "wb", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		Dz1MdefcModule *module = p->module;
		TCHAR module_name[1024];

		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if ((*errp = Dz1FileName_splitPathName(NULL, module_name, module->name)).code) ERR_OUT(errp);
		else
		{
			Dz1Thread_fprintf(fp, "#ifndef __HEADER_%s_" NEW_LINE, filename);
			Dz1Thread_fprintf(fp, "#define __HEADER_%s_" NEW_LINE, filename);
			Dz1Thread_fprintf(fp, "" NEW_LINE);
			Dz1Thread_fprintf(fp, "#include <dz1_io_stream.h>" NEW_LINE);
			Dz1Thread_fprintf(fp, "#include <dz1_io_stream_bin.h>" NEW_LINE NEW_LINE);
			Dz1Thread_fprintf(fp, "" NEW_LINE);
			Dz1Thread_fprintf(fp, "#include \"%s.h\"" NEW_LINE, module_name);
			Dz1Thread_fprintf(fp, "" NEW_LINE);
			if ((*errp = ConstructCodecIncludeList_publish_hdr(fp, p->includes)).code) ERR_OUT(errp);
			else
			{
				Dz1Thread_fprintf(fp, "" NEW_LINE);
				if ((*errp = ConstructObjectList_publish_hdr(fp, p->objs, p->endian, p->module, &printed)).code) ERR_OUT(errp);
				else if (printed == FALSE)
				{
					Dz1Thread_fprintf(fp, "" NEW_LINE);
					Dz1Thread_fprintf(fp, "extern int __avoid_empty_symbol__%s;" NEW_LINE, filename);
				}
				Dz1Thread_fprintf(fp, "" NEW_LINE);
				Dz1Thread_fprintf(fp, "#endif" NEW_LINE);
			}
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return err;
}
// CODEC Header
///////////////////////////////////////////////////////////////////////////////
