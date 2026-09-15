#include <dz1_base64.h>
#include "dz1_jsonTestUtil.h"

Dz1JsonNewLine test_line_mode = Dz1JsonNewLine_crlf;

void *_Dz1Json_testParse(Dz1JsonSpec *spec, Dz1Str type_name, Dz1Str text, Dz1DumpFunc dump, Dz1Error *err)
{
	void *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Json *h = NULL;
	Dz1Thread_printf("==================================================================\n");
	Dz1Thread_printf("%s Parse Test\n", type_name);
//	Dz1Thread_printf("text = %s\n", text);
	Dz1Thread_printf("==================================================================\n");
	if ((h = Dz1Json_new(DZ1_SYSTEM_CHARSET, spec, type_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		size_t st_sz = Dz1STRLEN(text) * sizeof(TCHAR);
		ssize_t sz = 0;
		u8_t *cp = (u8_t *)text;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&h);

		while(st_sz)
		{
			sz = st_sz > 64 ? 64 : (ssize_t)st_sz;
			if ((sz = Dz1Json_push_stream(h, cp, sz, errp)) < 0) ERR_OUT(errp);
			else
			{
				cp += sz; st_sz -= sz;
				if ((status = Dz1Json_parse(h, errp)) < 0) ERR_OUT(errp);
				else if (status == 0) Dz1Error_set(errp, 0);
				else if ((ret = (MyComponent *)Dz1Json_read(h, errp)) == NULL) ERR_OUT(errp);
				else 
				{
					Dz1Thread_printf("Parsed = "); dump(ret, 0);
					Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&h);
	}
	return ret;
}

Dz1Binary *_Dz1Json_testStringify(Dz1JsonSpec *spec, Dz1Str type_name, void *obj, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Json *h = NULL;
	Dz1Thread_printf("==================================================================\n");
	Dz1Thread_printf("%s Stringify Test\n", type_name);
	Dz1Thread_printf("==================================================================\n");
	if ((h = Dz1Json_new("EUCKR", spec, type_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void *)&h);
		if (Dz1Json_stringify(h, type_name, obj, test_line_mode, errp) == FALSE) ERR_OUT(errp);
		else if ((sz = Dz1Json_squeeze(h, NULL, 0, errp)) < 0) ERR_OUT(errp);
		else if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)(sz + 4), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);
			memset(ret->data, 0, ret->size);
			if (Dz1Json_squeeze(h, ret->data, sz, errp) < 0) ERR_OUT(errp);
			else 
			{
				Dz1Thread_printf("Stringify = %s", (Dz1Str)ret->data);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void *)&h);
	}
	return ret;
}

Dz1Error Dz1Json_testString(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("Dz1Str");
	Dz1Str temp = NULL;
//	Dz1Str text =	Dz1Text("{ \"abcdefghijklmnopqrstuvwxyz\" }");
	Dz1Str text =	Dz1Text("\"abcdefghijklmnopqrstuvwxyz\"");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)Dz1Str_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testStringList(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("StringList");
	StringList *temp = NULL;
	Dz1Str text =	Dz1Text("[")
					Dz1Text("\"aaa\",")
					Dz1Text("\"bbb\",")
					Dz1Text("\"ccc\",")
					Dz1Text("\"ddd\",")
					Dz1Text("\"eee\"")
					Dz1Text("]");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)StringList_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(StringList_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (StringList_delAndSetNull, (void *)&temp);
	}
	return err;
}

static Dz1Str _mk_base64_str(u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	Dz1Str temp = Dz1Codec_Base64Encode(data, sz, errp), ret = NULL;
	Dz1Str temp = Dz1Base64_enc(data, (ssize_t)sz, errp), ret = NULL;
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		size_t len = 0;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);
		if ((ret = Dz1Calloc(sizeof(TCHAR), (len = Dz1STRLEN(temp)) + 5, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TCHAR *cp = ret;
//			*cp++ = Dz1Text('{');
			*cp++ = Dz1Text('\"');
			Dz1STRCPY(cp, temp); cp += len;
			*cp++ = Dz1Text('\"');
//			*cp++ = Dz1Text('}');
			*cp = 0;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return ret;
}

Dz1Error Dz1Json_testBinary(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("Dz1Binary");
	u8_t data[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
	Dz1Str text = _mk_base64_str(data, sizeof(data), errp);
	if (text == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str temp = NULL;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
		if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)Dz1Binary_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&temp);
			if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
				Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&temp);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
	}
	return err;
}

Dz1Error Dz1Json_testReal32(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("real32_t");
	real32_t *temp = NULL;
	Dz1Str text =	Dz1Text("3.14159264\r\n");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)Dz1Real32_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1Real32_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1Real32_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testReal64(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("real64_t");
	real64_t *temp = NULL;
	Dz1Str text =	Dz1Text("3.14159264\r\n");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)Dz1Real64_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1Real64_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1Real64_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testMyStruct(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("MyStruct");
	MyStruct *temp = NULL;
	Dz1Str text =	Dz1Text("{")
					Dz1Text("	\"a\":10,")
					Dz1Text("	\"b\":20,")
					Dz1Text("	\"c\":30,")
					Dz1Text("	\"d\":40,")
					Dz1Text("	\"e\":\"ABCDEF\"")
					Dz1Text("}");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)MyStruct_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(MyStruct_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (MyStruct_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testMyUnion(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("MyUnion");
	MyUnion *temp = NULL;
	Dz1Str text = Dz1Text("{ \"e\":null }");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)MyUnion_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(MyUnion_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (MyUnion_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testMyStructList(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("MyStructList");
	MyStructList *temp = NULL;
	Dz1Str text =	Dz1Text("[")
					Dz1Text("	{ \"a\":10, \"b\":20, \"c\":30, \"d\":40, \"e\":\"ABC\" },")
					Dz1Text("	{ \"a\":11, \"b\":21, \"c\":31, \"d\":41, \"e\":\"BCD\" },")
					Dz1Text("	{ \"a\":12, \"b\":22, \"c\":32, \"d\":42, \"e\":\"CDE\" },")
					Dz1Text("	{ \"a\":13, \"b\":23, \"c\":33, \"d\":43, \"e\":null },")
					Dz1Text("	{ \"a\":14, \"b\":24, \"c\":34, \"d\":44, \"e\":\"EFG\" }")
					Dz1Text("]");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)MyStructList_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(MyStructList_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (MyStructList_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testMyUnionList(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("MyUnionList");
	MyUnionList *temp = NULL;
	Dz1Str text =	Dz1Text("[")
					Dz1Text("	{ \"a\":10 },")
					Dz1Text("	{ \"b\":21 },")
					Dz1Text("	{ \"c\":32 },")
					Dz1Text("	{ \"d\":43 },")
					Dz1Text("	{ \"e\":null }")
					Dz1Text("]");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)MyUnionList_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(MyUnionList_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (MyUnionList_delAndSetNull, (void *)&temp);
	}
	return err;
}

Dz1Error Dz1Json_testMyComponent(Dz1JsonSpec *spec)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Str type_name = Dz1Text("MyComponent");
	MyComponent *temp = NULL;
	Dz1Str text =	Dz1Text("{")
					Dz1Text("	\"a\":0xFFFF,")
					Dz1Text("	\"b\":{")
					Dz1Text("		\"a\":10,")
					Dz1Text("		\"b\":20,")
					Dz1Text("		\"c\":30,")
					Dz1Text("		\"d\":40,")
					Dz1Text("		\"e\":null")
					Dz1Text("	},")
					Dz1Text("	\"c\":{")
					Dz1Text("		\"b\":21")
					Dz1Text("	},")
					Dz1Text("	\"d\":[")
					Dz1Text("		{ \"a\":10, \"b\":20, \"c\":30, \"d\":40, \"e\":\"ABC\" },")
					Dz1Text("		{ \"a\":11, \"b\":21, \"c\":31, \"d\":41, \"e\":\"BCD\" },")
					Dz1Text("		{ \"a\":12, \"b\":22, \"c\":32, \"d\":42, \"e\":\"CDE\" },")
					Dz1Text("		{ \"a\":13, \"b\":23, \"c\":33, \"d\":43, \"e\":\"DEF\" },")
					Dz1Text("		{ \"a\":14, \"b\":24, \"c\":34, \"d\":44, \"e\":\"EFG\" }")
					Dz1Text("	],")
					Dz1Text("	\"e\":[")
					Dz1Text("		{ \"a\":10 },")
					Dz1Text("		{ \"b\":21 },")
					Dz1Text("		{ \"c\":32 },")
					Dz1Text("		{ \"d\":43 },")
					Dz1Text("		{ \"e\":\"ABCDEFG\" }")
					Dz1Text("	],")
					Dz1Text("	\"f\":3.141592764," )
					Dz1Text("	\"g\":3.141592," )
					Dz1Text("	\"h\":\"bcd\"," )
					Dz1Text("	\"i\":2100000000" )
					Dz1Text("}");
	if ((temp = _Dz1Json_testParse(spec, type_name, text, (Dz1DumpFunc)MyComponent_dump, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(MyComponent_delAndSetNull, (void *)&temp);
		if ((bin = _Dz1Json_testStringify(spec, type_name, temp, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (MyComponent_delAndSetNull, (void *)&temp);
	}
	return err;
}


