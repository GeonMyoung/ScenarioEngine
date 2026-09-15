#include "dz1_todec.h"

ObjectTypeMembPublishApi *ObjectTypeMembPublishApi_find(ObjectTypeMembPublishApi *tbl, ObjectType type)
{
	ObjectTypeMembPublishApi *i;
	for (i = tbl; i->type != ObjectType_max; i++)
		if (i->type == type) return i;
	return NULL;
}

Dz1TodecUnitSize _resolve_prim_size(PrimitiveInfo *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TodecUnitSize ret = Dz1TodecUnitSize_max;
	if (info == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (strstr(info->native, "64") != NULL) ret = Dz1TodecUnitSize_Byte8;
	else if (strstr(info->native, "32") != NULL) ret = Dz1TodecUnitSize_Byte4;
	else if (strstr(info->native, "16") != NULL) ret = Dz1TodecUnitSize_Byte2;
	else if (strstr(info->native, "8") != NULL) ret = Dz1TodecUnitSize_Byte1;
//	else if (strstr(info->native, "time") != NULL) ret = Dz1TodecUnitSize_Byte4;
	else if (strstr(info->native, "Dz1IPv4") != NULL) ret = Dz1TodecUnitSize_Byte4;
	else Dz1Error_set(errp, ENOENT);
	return ret;
}

