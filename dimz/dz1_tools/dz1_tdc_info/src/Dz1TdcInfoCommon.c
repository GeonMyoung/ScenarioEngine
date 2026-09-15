#include "Dz1TdcInfoCommon.h"

typedef struct _NameMap_A
{
	FORWARD_TYPE	 type;
	str_t			 name;
} _NameMap_A;

static _NameMap_A FORWARD_TYPE_MAP_A[] =
{
	{ FORWARD_TYPE_NONE,	"none" },
	{ FORWARD_TYPE_STRUCT,	"struct" },
	{ FORWARD_TYPE_UNION,	"union" },
	{ FORWARD_TYPE_ENUM,	"enum" },
	{ FORWARD_TYPE_IMPORT,	"imported" },
	{ FORWARD_TYPE_max,		"unknown" }
};

str_t FORWARD_TYPE_StrA(FORWARD_TYPE v)
{
	_NameMap_A *i;
	for (i = FORWARD_TYPE_MAP_A; i->type < FORWARD_TYPE_max; i++)
		if (i->type == v) break;
	return i->name;
}
#ifndef UNIX_SYSTEM
typedef struct _NameMap_W
{
	FORWARD_TYPE	 type;
	wstr_t			 name;
} _NameMap_W;

static _NameMap_W FORWARD_TYPE_MAP_W[] =
{
	{ FORWARD_TYPE_NONE,	L"none" },
	{ FORWARD_TYPE_STRUCT,	L"struct" },
	{ FORWARD_TYPE_UNION,	L"union" },
	{ FORWARD_TYPE_ENUM,	L"enum" },
	{ FORWARD_TYPE_IMPORT,	L"imported" },
	{ FORWARD_TYPE_max,		L"unknown" }
};

wstr_t FORWARD_TYPE_StrW(FORWARD_TYPE v)
{
	_NameMap_W *i;
	for (i = FORWARD_TYPE_MAP_W; i->type < FORWARD_TYPE_max; i++)
		if (i->type == v) break;
	return i->name;
}
#endif
