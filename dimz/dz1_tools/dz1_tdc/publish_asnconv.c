#include <dz1_thread_stdio.h>
#include <Dz1TdcInfoObject.h>
#include "publish_asnconv.h"

///////////////////////////////////////////////////////////////////////////////
// ASN API Header
bool_t Publish_asnConvDeclare(FILE *fp, u32_t api, PublishSpec *spec, str_t name, str_t srcName, int tab)
{
	bool_t ret = FALSE;
	Dz1Thread_printf("asnConvDeclare(%08X) : %s-%s\n", api, name, srcName);
	if (api & OBJECT_API_ASN_CONV)
	{
		fprintf(fp, "\n");
		TP(fp, tab); fprintf(fp, "%s %s %s %s_fromASN(%s *dst, %s *src);\n",
					spec->base->cpplink,
					spec->base->dllport,
					spec->error->type,
					name,
					name,
					srcName);
		// typename *typename##_newFromASN(asnname *src, Dz1Error *err)
		TP(fp, tab); fprintf(fp,
					//"%s %s DZ1_DECL_NEW_FROM_ASN(%s, %s);\n",
					"%s %s %s *%s_newFromASN(%s *src, Dz1Error *err);\n\n",
					spec->base->cpplink,
					spec->base->dllport,
					name, name, 
					srcName);
		TP(fp, tab); fprintf(fp, "%s %s %s %s_toASN(%s *dst, %s *src, ASN1WorkSpace *ws);\n",
					spec->base->cpplink,
					spec->base->dllport,
					spec->error->type,
					name,
					srcName,
					name);
		TP(fp, tab); fprintf(fp,
					//"%s %s DZ1_DECL_TO_NEW_ASN(%s, %s);\n",
				//asnname *typename##_toNewASN(typename *src, ASN1WorkSpace *ws, Dz1Error *err)
					"%s %s %s *%s_toNewASN(%s *src, ASN1WorkSpace *ws, Dz1Error *err);\n\n",
					spec->base->cpplink,
					spec->base->dllport,
					srcName,
					name,
					name);
		ret = TRUE;
	}
	return ret;
}
// ASN API Header
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Common Convert Source Print
static void EnumObject_fromASN(FILE *fp, int tab, ObjectInfo *p)
{
	//EnumInfo *info = (EnumInfo *)p->info;
	Dz1Thread_ftprintf(fp, tab, "(*dst) = (%s)(*src);\n", p->name);
}

static void EnumObject_toASN(FILE *fp, int tab, ObjectInfo *p)
{
	//EnumInfo *info = (EnumInfo *)p->info;
	Dz1Thread_ftprintf(fp, tab, "(*dst) = (%s)(*src);\n", p->srcName);
}
// Common Convert Source Print
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member prepare Optional Enumerate
static void StructMemberPointer_prepareOptionalEnum(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			if (origin->type == ObjectType_enumerate)
			{	// enum *b;
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// create from temp value    1  2     3            4  5         6
					Dz1ThreadA_ftprintf(fp, tab, "%s %s = (%s)(src->DEF_%s_%s ? src->%s : 0);\n",
										e->type->name,				// 1
										e->instance,				// 2
										e->type->name,				// 3
										p->srcName,					// 4
										e->instance,				// 5
										e->instance);				// 6
				}
				else
				{	// don't care
				}
			}
			else
			{	// int *a
			}
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
	}
}

static void StructMemberObject_prepareOptionalEnum(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (e->isPointer)
		StructMemberPointer_prepareOptionalEnum(fp, tab, p, e);
}
// Structure Member prepare Optional Enumerate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Member...
// XXX : 원래는 다른방법을 썼어야 했다.
static str_t asnPrimitiveList[] = 
{
	"INTEGER",
	"BOOLEAN",
	"REAL",
	"OCTETSTRING",
	"BITSTRING",
	"UTF8String",
	"VisibleString",
	"UniversalString",
	"OBJECTIDENTIFIER",
	NULL
};

static str_t dz1AsnPrimitiveList[] =
{
// XXX : ASN.1 type "OCTET STRING"에 대한
// XXX : DZ1대응 타입 "Dz1Asn1OctetStr"의 이름이 바뀌면
// XXX : 꼭 이곳의 이름을 변경해야 함.
	"Dz1Asn1OctetStr",
	"Dz1Asn1UTF8Str",
	"Dz1Asn1BitStr",
	"Dz1Asn1OID",
	"uint8",
	"uint16",
	"uint32",
	"uint64",
	"int8",
	"int16",
	"int32",
	"int64",
	NULL
};

static bool_t isAsnPrimitive(ObjectInfo *memberType, str_t memberSrcType)
{
	memberType = ObjectInfo_getOrigin(memberType);
	if (memberType->type == ObjectType_array) return TRUE;
	else if (memberSrcType == NULL || strlen(memberSrcType) == 0) return FALSE;
	else
	{
		str_t *i;
//		Dz1Thread_printf("@@@ memberSrcType = %s\n", memberSrcType);
//		Dz1Thread_printf("@@@ memberType ="); ObjectInfo_dump(memberType, 1);
		for (i = asnPrimitiveList; *i != NULL; i++)
			if (strcmp(memberSrcType, *i) == 0) return TRUE;
		for (i = dz1AsnPrimitiveList; *i != NULL; i++)
			if (strcmp(memberType->name, *i) == 0) return TRUE;
		return FALSE;
	}
}

static str_t _newFromASNFuncCall(char dst[1024], ObjectInfo *memberType, str_t memberSrcName, str_t instance, bool_t isUnion)
{
	str_t ret = NULL;

	str_t apiPrefix = memberType->name;
	ObjectInfo *memberOrigin = ObjectInfo_getOrigin(memberType);

	if (memberSrcName != NULL && strcmp(memberSrcName, "BOOLEAN") == 0)
	{
		memberSrcName = memberSrcName;
	}

	if (memberOrigin->type == ObjectType_primitive)
	{
		PrimitiveInfo *info = (PrimitiveInfo *)memberOrigin->info;
		apiPrefix = info->native;
	}

	if (strcmp(memberType->name, "Dz1TimeVal") == 0)
	{	//                 1 2    3         4        5 6
		sprintf(dst, "dst->%s%s = %s_newFrom%s(&src->%s%s, &err)",
			isUnion ? "x." : "",			// 1
			instance,						// 2
			apiPrefix,				// 3
			memberSrcName,					// 4
			isUnion ? "elements." : "",		// 5
			instance);						// 6
		ret = dst;
	}
	else if (strcmp(memberType->name, "Dz1Asn1Null") == 0)
	{	//                 1 2
		sprintf(dst, "dst->%s%s = Dz1Asn1Null_new(NULL, &err)",
			isUnion ? "x." : "",			// 1
			instance);						// 2
		ret = dst;
	}
	else
	{	//                 1 2    3             4      5 6
		sprintf(dst, "dst->%s%s = %s_newFromASN(%ssrc->%s%s, &err)",
			isUnion ? "x." : "",			// 1
			instance,						// 2
			apiPrefix,						// 3
			isAsnPrimitive(memberType, memberSrcName) ? "&" : "",	// 4
			isUnion ? "elements." : "",		// 5
			instance);						// 6
		ret = dst;
	}
	return ret;
}

static bool_t _optionalNewFromASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
//	if (e->srcType != NULL && strcmp(e->srcType, "NULL") == 0) { }
//	else
	{
		char buf[1024];
		_newFromASNFuncCall(buf, e->type, e->srcType, e->instance, FALSE);
		//                           1              2  3      4
		Dz1Thread_ftprintf(fp, tab, "%sif (src->DEF_%s_%s && (%s) == NULL) ERR_OUT(&err);\n",
									needElse ? "else " : "",	// 1
									p->srcName,					// 2
									e->instance,				// 3
									buf);						// 4
		needElse = TRUE;
	}
	return needElse;
}

/*
	case ObjectType_primitive:
	case ObjectType_enumerate:
	case ObjectType_structure:
	case ObjectType_union:
	case ObjectType_array:

	case ObjectType_bits:

	case ObjectType_defined:
	case ObjectType_extern:
	case ObjectType_reference:
	case ObjectType_func:
	case ObjectType_declare:
*/

static bool_t _newFromASN(FILE *fp, int tab, ObjectInfo *p, ObjectInfo *memberType, str_t memberSrcType, str_t instance, bool_t isUnion, bool_t needElse)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(memberType);
	if (memberSrcType != NULL && strcmp(memberSrcType, "NULL") == 0) { }
	else if (strcmp(origin->name, "Dz1Asn1Null") == 0) { }
	else
	{
		char buf[1024];
		_newFromASNFuncCall(buf, memberType, memberSrcType, instance, isUnion);
		//                           1      2
		Dz1Thread_ftprintf(fp, tab, "%sif ((%s) == NULL) { Dz1Thread_printf(\"%s : \"); ERR_OUT(&err); }\n",
									needElse ? "else " : "",
									buf, instance);
		needElse = TRUE;
	}
	return needElse;
}
// Member...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member from ASN
static bool_t StructMemberPointer_fromASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{	// int *a; enum *b; str *c; structure *d; union *e; array f; void *g;
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			if (origin->type == ObjectType_enumerate)
			{	// enum *b;
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// create from temp value    1              2  3           4    5       6									     7
					Dz1Thread_ftprintf(fp, tab, "%sif (src->DEF_%s_%s && (dst->%s = %s_new(&%s, &err)) == NULL) { Dz1Thread_printf(\"%s : \"); ERR_OUT(&err); }\n",
										needElse ? "else " : "",	// 1
										p->srcName,					// 2
										e->instance,				// 3
										e->instance,				// 4
										e->type->name,				// 5
										e->instance,				// 6
										e->instance);				// 7
					needElse = TRUE;
				}
				else
				{
				}
			}
			else
			{	// int *a
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// DEF_{srcName}_{instance} == 1 ? newFromASN : NULL
					needElse = _optionalNewFromASN(fp, tab, p, e, needElse);
				}
				else
				{	// newFromASN
					needElse = _newFromASN(fp, tab, p, e->type, e->srcType, e->instance, FALSE, needElse);
				}
			}
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array *f;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// DEF_{srcName}_{instance} == 1 ? newFromASN : NULL
				needElse = _optionalNewFromASN(fp, tab, p, e, needElse);
			}
			else
			{	// newFromASN
				_newFromASN(fp, tab, p, e->type, e->srcType, e->instance, FALSE, needElse);
			}
		}
		else
		{	// structure *d; union *e;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
				needElse = _optionalNewFromASN(fp, tab, p, e, needElse);
			else needElse = _newFromASN(fp, tab, p, e->type, e->srcType, e->instance, FALSE, needElse);
		}
	}
	return needElse;
}

static bool_t _fromASN(FILE *fp, int tab, ObjectInfo *p, str_t apiPrefix, str_t instance, bool_t isUnion, bool_t needElse)
{	//                           1            2                3 4         5 6
	Dz1Thread_ftprintf(fp, tab, "%sif ((err = %s_fromASN(&dst->%s%s, &src->%s%s)).code) { Dz1Thread_printf(\"%s : \"); ERR_OUT(&err); }\n",
								needElse ? "else " : "",
								apiPrefix,
								isUnion ? "x." : "",
								instance,
								isUnion ? "elements." : "",
								instance, instance);
	needElse = TRUE;
	return needElse;
}

static bool_t StructMemberNotPointer_fromASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{	// int a; enum b; str c; structure d; union e; array f; void g;
	if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b; -> fromASN;
			if (origin->type == ObjectType_enumerate)
			{	// enum b; -> assgin code will published
			}
			else
			{	// int a; -> fromASN;        1            2                3         4
				PrimitiveInfo *info = (PrimitiveInfo *)origin->info;
				needElse = _fromASN(fp, tab, p, info->native, e->instance, FALSE, needElse);
			}
		}
		else
		{	// str c; -> newFromASN;     1           2    3                   4
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
				needElse = _optionalNewFromASN(fp, tab, p, e, needElse);
			else needElse = _newFromASN(fp, tab, p, e->type, e->srcType, e->instance, FALSE, needElse);
		}
	}
	else
	{	// structure d; union e; array f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array f; -> don't care
		}
		else
		{	// structure d; union e; -> don't care
		}
	}
	return needElse;
}

static bool_t StructMemberObject_fromASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
	if (e->isPointer)
		needElse = StructMemberPointer_fromASN(fp, tab, p, e, needElse);
	else needElse = StructMemberNotPointer_fromASN(fp, tab, p, e, needElse);
	return needElse;
}
// Structure Member from ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member assign from ASN
static void StructMemberObject_assignFromASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (e->isPointer) return;
	else if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b; -> fromASN;
			if (origin->type == ObjectType_enumerate)
			{	// enum b; -> assgin code will published
				Dz1Thread_ftprintf(fp, tab, "dst->%s = (%s)src->%s;\n", e->instance, e->type->name, e->instance);
			}
			else
			{	// int a; -> fromASN
			}
		}
		else
		{	// str c; -> newFromASN
		}
	}
	else
	{	// structure d; union e; array f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array f; -> don't care
		}
		else
		{	// structure d; union e; -> don't care
		}
	}
}
// Structure Member assign from ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Object from ASN
static void StructObject_fromASN(FILE *fp, int tab, ObjectInfo *p)
{
	StructureInfo *info = (StructureInfo *)p->info;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(info->members->fifo, NULL);
	if (c)
	{
		bool_t needElse = FALSE;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		// Optional Enumerate Preparing...
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				StructMemberObject_prepareOptionalEnum(fp, tab, p, e);
		}

		// from ASN
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				needElse = StructMemberObject_fromASN(fp, tab, p, e, needElse);
		}

		if (needElse)
		{
			Dz1Thread_ftprintf(fp, tab, "else\n");
			Dz1Thread_ftprintf(fp, tab++, "{\n");
		}
		// assign from ASN
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				StructMemberObject_assignFromASN(fp, tab, p, e);
		}
		if (needElse)
		{
			Dz1Thread_ftprintf(fp, --tab, "}\n");
		}

		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Structure Object from ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member from ASN
static void UnionMemberPointer_fromASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			_newFromASN(fp, tab, p, e->type, e->srcType, e->instance, TRUE, FALSE);
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array *f; -> newFromASN
			_newFromASN(fp, tab, p, e->type, e->srcType, e->instance, TRUE, FALSE);
		}
		else
		{	// structure *d; union *e; -> newFromASN
			_newFromASN(fp, tab, p, e->type, e->srcType, e->instance, TRUE, FALSE);
		}
	}
}

static void UnionMemberNotPointer_fromASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b;
			if (origin->type == ObjectType_enumerate)
			{	// enum b; -> assign
				Dz1Thread_ftprintf(fp, tab, "dst->x.%s = (%s)src->elements.%s;\n",
					e->instance, e->type->name, e->instance);
			}
			else
			{	// int a; -> fromASN;
				PrimitiveInfo *info = (PrimitiveInfo *)origin->info;
				_fromASN(fp, tab, p, info->native, e->instance, TRUE, FALSE);
			}
		}
		else
		{	// str c; -> newFromASN;
			_newFromASN(fp, tab, p, e->type, e->srcType, e->instance, TRUE, FALSE);
		}
	}
	else
	{	// structure d; union e; array f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array f; -> don't care
		}
		else
		{	// structure d; union e; -> don't care
		}
	}
}

static void UnionMemberObject_fromASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (e->isPointer)
		UnionMemberPointer_fromASN(fp, tab, p, e);
	else UnionMemberNotPointer_fromASN(fp, tab, p, e);
}
// Union Member from ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Object from ASN
static void UnionObject_fromASN(FILE *fp, int tab, ObjectInfo *p)
{
	UnionInfo *info = (UnionInfo *)p->info;
	UnionMemberEntry *e = NULL;
	void *c = NULL;

	if ((c = Dz1FifoCursor_new(info->members->fifo, NULL)) != NULL)
	{
		//bool_t needElse = FALSE;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		Dz1Thread_ftprintf(fp, tab, "switch(src->M)\n");
		Dz1Thread_ftprintf(fp, tab++, "{\n");
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				Dz1Thread_ftprintf(fp, tab++, "case DEF_%s_%s:\n", p->srcName, e->instance);
				Dz1Thread_ftprintf(fp, tab, "dst->present = %sPresent_%s;\n", p->name, e->instance);
				UnionMemberObject_fromASN(fp, tab, p, e);
				Dz1Thread_ftprintf(fp, tab--, "break;\n");
			}
		}
		Dz1Thread_ftprintf(fp, tab++, "default:\n");
		Dz1Thread_ftprintf(fp, tab, "ERR_SET_OUT(&err, EINVAL);\n");
		Dz1Thread_ftprintf(fp, tab--, "break;\n");
		Dz1Thread_ftprintf(fp, --tab, "}\n");
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Union Object from ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member to ASN
static void _toAsnFunctionCall(char buf[1024], ObjectInfo *target, str_t instance, str_t srcType, bool_t srcIsPointer, bool_t isUnion)
{
	str_t apiPrefix = target->name;
	ObjectInfo *origin = ObjectInfo_getOrigin(target);
	if (origin->type == ObjectType_primitive)
	{
		PrimitiveInfo *info = (PrimitiveInfo *)origin->info;
		apiPrefix = info->native;
		if (srcIsPointer == FALSE) srcIsPointer = info->storage == NativeStorage_address ? TRUE : FALSE;
		//                   1              2 3   4      5 6
		sprintf(buf, "(err = %s_toASN(&dst->%s%s, %ssrc->%s%s, ws)).code",
			apiPrefix,							// 1
			isUnion ? "elements." : "",			// 2
			instance,							// 3
			srcIsPointer ? "" : "&",			// 4
			isUnion ? "x." : "",				// 5
			instance);							// 6
	}
	else if (strcmp(target->name, "Dz1TimeVal") == 0)
	{	//                   1    2        3 4   5      6 7
		sprintf(buf, "(err = %s_to%s(&dst->%s%s, %ssrc->%s%s, ws)).code",
			apiPrefix,							// 1
			srcType,							// 2
			isUnion ? "elements." : "",			// 3
			instance,							// 4
			srcIsPointer ? "" : "&",			// 5
			isUnion ? "x." : "",				// 6
			instance);							// 7
	}

	/////////////////////////////////////////////////////
	else if (strcmp(target->name, "Dz1Asn1Null") == 0)
	{	//                  1 2
		sprintf(buf, "(dst->%s%s = 1)",
			isUnion ? "elements." : "",			// 1
			instance);							// 2
	}
	/////////////////////////////////////////////////////

	else if (isAsnPrimitive(target, srcType))
	{
		sprintf(buf, "(err = %s_toASN(&dst->%s%s, %ssrc->%s%s, ws)).code",
			apiPrefix,							// 1
			isUnion ? "elements." : "",			// 2
			instance,							// 3
			srcIsPointer ? "" : "&",			// 4
			isUnion ? "x." : "",				// 5
			instance);							// 6
	}
	else
	{	//                  1 2    3           4      5 6
		sprintf(buf, "(dst->%s%s = %s_toNewASN(%ssrc->%s%s, ws, &err)) == NULL",
			isUnion ? "elements." : "",			// 1
			instance,							// 2
			apiPrefix,							// 3
			srcIsPointer ? "" : "&",			// 4
			isUnion ? "x." : "",				// 5
			instance);							// 6
	}
}

static void _optionalToASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
	char buf[1024];
	_toAsnFunctionCall(buf, e->type, e->instance, e->srcType, TRUE, FALSE);
	//                           0               1  2         3                   4  
	Dz1Thread_ftprintf(fp, tab, "%sif ((dst->DEF_%s_%s = src->%s ? 1 : 0) == 1 && %s) { Dz1Thread_printf(\"%s : \"); ERR_OUT(&err); }\n",
									needElse ? "else " : "",						// 0
									p->srcName, e->instance, e->instance,			// 1 2 3
									buf, e->instance);								// 4 5
}

static bool_t _toASN(FILE *fp, int tab, ObjectInfo *p, ObjectInfo *memberType, str_t instance, str_t srcType, bool_t isPointer, bool_t isUnion, bool_t needElse)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(memberType);
	if (srcType != NULL && strcmp(srcType, "NULL") == 0) { }
	else if (strcmp(origin->name, "Dz1Asn1Null") == 0)
	{
		origin = origin;
	}
	else
	{
		char buf[1024];
		_toAsnFunctionCall(buf, memberType, instance, srcType, isPointer, isUnion);
		Dz1Thread_ftprintf(fp, tab, "%sif (%s) { Dz1Thread_printf(\"%s : \"); ERR_OUT(&err); }\n",
							needElse ? "else " : "", buf, instance);
		needElse = TRUE;
	}
	return needElse;
}

static bool_t StructMemberPointer_toASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			if (origin->type == ObjectType_enumerate)
			{	// enum *b;
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1) dst->{instance} = *src->{instance};
				}
				else
				{	// dst->{instance} = *src->{instance};
				}
			}
			else
			{	// int *a
				//PrimitiveInfo *info = (PrimitiveInfo *)origin->info;
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// ->[else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
					_optionalToASN(fp, tab, p, e, needElse);
					needElse = TRUE;
				}
				else
				{	// ->[else ]if ((err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
					needElse = _toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, FALSE, needElse);
				}
			}
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array *f;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// ->[else ]if (src->{insrance} && (err = {memberType}_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
				_optionalToASN(fp, tab, p, e, needElse);
				needElse = TRUE;
			}
			else
			{	// ->[else ]if ((err = {memberType}_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
				needElse = _toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, FALSE, needElse);
			}
		}
		else
		{	// structure *d; union *e;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// ->[else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {memberType)_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
				_optionalToASN(fp, tab, p, e, needElse);
				needElse = TRUE;
			}
			else
			{
				needElse = _toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, FALSE, needElse);
			}
		}
	}
	return needElse;
}

static bool_t StructMemberNotPointer_toASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
	ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
	if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b;
			if (origin->type == ObjectType_enumerate)
			{	// enum b;
				// dst->{instance} = *src->{instance};
			}
			else
			{	// int a
				// ->[else ]if ((err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
				needElse = _toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, FALSE, needElse);
			}
		}
		else
		{	// str c;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// ->[else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {memberType)_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
				_optionalToASN(fp, tab, p, e, needElse);
				needElse = TRUE;
			}
			else
			{	// ->[else ]if ((err = {memberType)_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
				needElse = _toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, FALSE, needElse);
			}
		}
	}
	else
	{	// structure d; union e; array f; -> don't care
	}
	return needElse;
}

static bool_t StructMemberObject_toASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e, bool_t needElse)
{
	if (e->isPointer)
		needElse = StructMemberPointer_toASN(fp, tab, p, e, needElse);
	else needElse = StructMemberNotPointer_toASN(fp, tab, p, e, needElse);
	return needElse;
}
// Structure Member to ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Member assign to ASN
static void StructMemberPointer_assignToASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			if (origin->type == ObjectType_enumerate)
			{	// enum *b;
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// ->if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1) { dst->{instance} = *src->{instance}; }
					//                                         1  2         3                      4          5
					Dz1Thread_ftprintf(fp, tab, "if ((dst->DEF_%s_%s = src->%s ? 1 : 0) == 1) dst->%s = *src->%s;\n",
												p->srcName, e->instance, e->instance,		// 1 2 3
												e->instance, e->instance);					// 4 5
				}
				else
				{	// ->dst->{instance} = *src->{instance};
					Dz1Thread_ftprintf(fp, tab, "dst->%s = *src->%s;\n", e->instance, e->instance);
				}
			}
			else
			{	// int *a
//				if (e->isAsnOptional)
				if (StructMemberEntry_isAsnOptional(e))
				{	// [else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
				}
				else
				{	// [else ]if ((err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
				}
			}
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array *f;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// [else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {memberType}_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
			}
			else
			{	// [else ]if ((err = {memberType}_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
			}
		}
		else
		{	// structure *d; union *e;
//			if (e->isAsnOptional)
			if (StructMemberEntry_isAsnOptional(e))
			{	// [else ]if ((dst->DEF_{type}_{instance} = src->{insrance} ? 1 : 0) == 1 && (err = {memberType)_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
			}
			else
			{	// [else ]if ((err = {memberType}_toASN(&dst->{instance}, src->{instance})).code) ERR_OUT(&err);
			}
		}
	}
}

static void StructMemberNotPointer_assignToASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b;
			if (origin->type == ObjectType_enumerate)
			{	// enum b;
				// ->dst->{instance} = src->{instance};
				Dz1Thread_ftprintf(fp, tab, "dst->%s = src->%s;\n", e->instance, e->instance);
			}
			else
			{	// int a
				// [else ]if ((err = {originNative}_toASN(&dst->{instance}, src->{instance}, ws)).code) ERR_OUT(&err);
			}
		}
		else
		{	// str c; -> nop
		}
	}
	else
	{	// structure d; union e; array f; -> don't care
	}
}

static void StructMemberObject_assignToASN(FILE *fp, int tab, ObjectInfo *p, StructMemberEntry *e)
{
	if (e->isPointer) StructMemberPointer_assignToASN(fp, tab, p, e);
	else StructMemberNotPointer_assignToASN(fp, tab, p, e);
}
// Structure Member assign to ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Structure Object to ASN
static void StructObject_toASN(FILE *fp, int tab, ObjectInfo *p)
{
	StructureInfo *info = (StructureInfo *)p->info;
	StructMemberEntry *e = NULL;
	void *c = Dz1FifoCursor_new(info->members->fifo, NULL);
	if (c)
	{
		bool_t needElse = FALSE;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				needElse = StructMemberObject_toASN(fp, tab, p, e, needElse);
		}
		if (needElse)
		{
			Dz1Thread_ftprintf(fp, tab, "else\n");
			Dz1Thread_ftprintf(fp, tab++, "{\n");
		}
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (StructMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
				StructMemberObject_assignToASN(fp, tab, p, e);
		}
		if (needElse)
		{
			Dz1Thread_ftprintf(fp, --tab, "}\n");
		}
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Structure Object to ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Member to ASN
static void UnionMemberPointer_toASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int *a; enum *b; str *c; void *g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void *g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int *a; enum *b;
			_toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, TRUE, FALSE);
		}
		else
		{	// str *c; -> don't care
		}
	}
	else
	{	// structure *d; union *e; array *f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array *f; -> newFromASN
			_toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, TRUE, FALSE);
		}
		else
		{	// structure *d; union *e; -> newFromASN
			_toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, TRUE, FALSE);
		}
	}
}

static void UnionMemberNotPointer_toASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (ObjectInfo_isPrimitive(e->type))
	{	// int a; enum b; str c; void g;
		ObjectInfo *origin = ObjectInfo_getOrigin(e->type);
		if (strcmp(origin->name, VOIDTYPE_NAME) == 0)
		{	// void g; -> don't care
		}
		else if (ObjectInfo_isScalar(e->type))
		{	// int a; enum b;
			if (origin->type == ObjectType_enumerate)
			{	// enum b; -> assign
				Dz1Thread_ftprintf(fp, tab, "dst->elements.%s = src->x.%s;\n", e->instance, e->instance);
			}
			else
			{	// int a; -> fromASN;
				//PrimitiveInfo *info = (PrimitiveInfo *)origin->info;
				_toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, TRUE, FALSE);
			}
		}
		else
		{	// str c; -> newFromASN;
			_toASN(fp, tab, p, e->type, e->instance, e->srcType, e->isPointer, TRUE, FALSE);
		}
	}
	else
	{	// structure d; union e; array f;
		if (ObjectInfo_typeOf(e->type) == ObjectType_array)
		{	// array f; -> don't care
		}
		else
		{	// structure d; union e; -> don't care
		}
	}
}

static void UnionMemberObject_toASN(FILE *fp, int tab, ObjectInfo *p, UnionMemberEntry *e)
{
	if (e->isPointer)
		UnionMemberPointer_toASN(fp, tab, p, e);
	else UnionMemberNotPointer_toASN(fp, tab, p, e);
}
// Union Member to ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Union Object to ASN
static void UnionObject_toASN(FILE *fp, int tab, ObjectInfo *p)
{
	UnionInfo *info = (UnionInfo *)p->info;
	UnionMemberEntry *e = NULL;
	void *c = NULL;

	if ((c = Dz1FifoCursor_new(info->members->fifo, NULL)) != NULL)
	{
		//bool_t needElse = FALSE;
		pthread_cleanup_push(Dz1FifoCursor_del, c);

		Dz1Thread_ftprintf(fp, tab, "switch(src->present)\n");
		Dz1Thread_ftprintf(fp, tab++, "{\n");
		for (Dz1FifoCursorForward(c))
		{
			if ((e = (UnionMemberEntry *)Dz1FifoCursor_data(c)) != NULL)
			{
				Dz1Thread_ftprintf(fp, tab++, "case %sPresent_%s:\n", p->name, e->instance);
				Dz1Thread_ftprintf(fp, tab, "dst->M = DEF_%s_%s;\n", p->srcName, e->instance);
				UnionMemberObject_toASN(fp, tab, p, e);
				Dz1Thread_ftprintf(fp, tab--, "break;\n");
			}
		}
		Dz1Thread_ftprintf(fp, tab++, "default:\n");
		Dz1Thread_ftprintf(fp, tab, "ERR_SET_OUT(&err, EINVAL);\n");
		Dz1Thread_ftprintf(fp, tab--, "break;\n");
		Dz1Thread_ftprintf(fp, --tab, "}\n");
		pthread_cleanup_pop(1); // (Dz1FifoCursor_del, c);
	}
}
// Union Object to ASN
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN API Source
bool_t Publish_asnConvImple(FILE *fp, PublishSpec *spec, ObjectInfo *p, int tab)
{
	bool_t ret = FALSE;
	if (p->api & OBJECT_API_ASN_CONV)
	{
		if (p->type == ObjectType_primitive ||
			p->type == ObjectType_defined ||
			p->type == ObjectType_extern ||
			p->type == ObjectType_reference ||
			p->type == ObjectType_declare ||
			p->type == ObjectType_func) return ret;
		else if (p->type == ObjectType_array)
		{
			ArrayInfo *info = (ArrayInfo *)p->info;
			ObjectInfo *entry = info->entry;
			ObjectInfo *origin = ObjectInfo_getOrigin(entry);

			str_t entrySrcType = info->entrySrcType != NULL ? info->entrySrcType : entry->srcName;
			str_t mode = "", entryTypeStr = entry->name;

			// AVIOD_NAME_COLLISION_UTF8_STRING
			if (strcmp(entrySrcType, "UTF8String") == 0) entrySrcType = "UTF8Str";

			if (origin->type == ObjectType_primitive)
			{
				PrimitiveInfo *info = (PrimitiveInfo *)entry->info;
				mode = "S_";
				entryTypeStr = info->native;
			}
			else if (origin->type == ObjectType_enumerate)
			{
				mode = "S_";
			}

			Dz1Thread_ftprintf(fp, tab, "PSEUDO_%sLIST_FROM_ASN(%s, %s, %s)\n",
							mode, p->name, entryTypeStr, entrySrcType);
			Dz1Thread_ftprintf(fp, tab, "DZ1_NEW_LIST_FROM_ASN(%s, ASN1List)\n\n", p->name);

			Dz1Thread_ftprintf(fp, tab, "PSEUDO_ENTRY_TO_ASN(%s, %s, %s)\n",
							p->name, entryTypeStr, entrySrcType);

			Dz1Thread_ftprintf(fp, tab, "PSEUDO_LIST_TO_ASN(%s)\n", p->name);
			Dz1Thread_ftprintf(fp, tab, "DZ1_TO_NEW_ASN_LIST(%s, ASN1List)\n\n", p->name);
		}
		else
		{
			// -----------------------------------------------------------------------------
			// From ASN
			// -----------------------------------------------------------------------------
			Dz1Thread_ftprintf(fp, tab, "%s %s_fromASN(%s *dst, %s *src)\n",
						spec->error->type,
						p->name,
						p->name,
						p->srcName);
			Dz1Thread_ftprintf(fp, tab++, "{\n");
			Dz1Thread_ftprintf(fp, tab, "%s err = %s;\n",
						spec->error->type,
						spec->error->defaultVal);

			Dz1Thread_ftprintf(fp, tab, "ASN1WorkSpace ws;\n");
			Dz1Thread_ftprintf(fp, tab, "ASN1_INIT_WS_INFO(&ws);\n");
			Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\n");
			Dz1Thread_ftprintf(fp, tab, "if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);\n");
			Dz1Thread_ftprintf(fp, tab, "else\n");
			Dz1Thread_ftprintf(fp, tab++, "{\n");

			// Print Individual Convert code
			switch(p->type)
			{
			case ObjectType_enumerate:	// enum
				EnumObject_fromASN(fp, tab, p);
				break;
			case ObjectType_structure:	// struct
				StructObject_fromASN(fp, tab, p);
				break;
			case ObjectType_union:		// union
				UnionObject_fromASN(fp, tab, p);
				break;
			default:
			case ObjectType_bits:
				break;
			}

			Dz1Thread_ftprintf(fp, --tab, "}\n");
			Dz1Thread_ftprintf(fp, tab, "pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);\n");
			Dz1Thread_ftprintf(fp, tab, "return err;\n");
			Dz1Thread_ftprintf(fp, --tab, "}\n\n");
			Dz1Thread_ftprintf(fp, tab, "DZ1_NEW_FROM_ASN(%s, %s)\n\n",
						p->name,
						p->srcName);

			// -----------------------------------------------------------------------------
			// To ASN
			// -----------------------------------------------------------------------------
			Dz1Thread_ftprintf(fp, tab, "%s %s_toASN(%s *dst, %s *src, ASN1WorkSpace *ws)\n",
						spec->error->type,
						p->name,
						p->srcName,
						p->name);
			Dz1Thread_ftprintf(fp, tab++, "{\n");

			Dz1Thread_ftprintf(fp, tab, "%s err = %s;\n",
						spec->error->type,
						spec->error->defaultVal);
			Dz1Thread_ftprintf(fp, tab, "if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);\n");
			Dz1Thread_ftprintf(fp, tab, "else\n");
			Dz1Thread_ftprintf(fp, tab++, "{\n");

			// Print Individual convert code
			switch(p->type)
			{
			case ObjectType_enumerate:	// enum
				EnumObject_toASN(fp, tab, p);
				break;
			case ObjectType_structure:	// struct
				StructObject_toASN(fp, tab, p);
				break;
			case ObjectType_union:		// union
				UnionObject_toASN(fp, tab, p);
				break;
			default:
			case ObjectType_bits:
				break;
			}


			Dz1Thread_ftprintf(fp, --tab, "}\n");
			Dz1Thread_ftprintf(fp, tab, "return err;\n");
			Dz1Thread_ftprintf(fp, --tab, "}\n");
			Dz1Thread_ftprintf(fp, tab, "DZ1_TO_NEW_ASN(%s, %s)\n",
						p->name,
						p->srcName);
			ret = TRUE;
		}
	}
	return ret;
}
// ASN API Source
///////////////////////////////////////////////////////////////////////////////

