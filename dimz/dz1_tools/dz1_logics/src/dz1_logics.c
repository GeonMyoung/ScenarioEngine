#include "dz1_logics.h"

static bool_t _chk_relationA(Dz1LogicMatchValueType type, Dz1LogicMatchAPresent present)
{
	bool_t ret = FALSE;
	switch(type)
	{
	case Dz1LogicMatchValueType_Signed8:
	case Dz1LogicMatchValueType_Signed16:
	case Dz1LogicMatchValueType_Signed32:
	case Dz1LogicMatchValueType_Signed64:
	case Dz1LogicMatchValueType_Unsigned8:
	case Dz1LogicMatchValueType_Unsigned16:
	case Dz1LogicMatchValueType_Unsigned32:
	case Dz1LogicMatchValueType_Unsigned64:
		if (present == Dz1LogicMatchAPresent_number) ret = TRUE;
		break;
// 	case Dz1LogicMatchValueType_String:
// 		if (present == Dz1LogicMatchAPresent_text) ret = TRUE;
// 		break;
	default:
		break;
	}
	return ret;
}

#ifndef UNIX_SYSTEM // modified by gm 20230602 
static bool_t _chk_relationW(Dz1LogicMatchValueType type, Dz1LogicMatchWPresent present)
{
	bool_t ret = FALSE;
	switch(type)
	{
	case Dz1LogicMatchValueType_Signed8:
	case Dz1LogicMatchValueType_Signed16:
	case Dz1LogicMatchValueType_Signed32:
	case Dz1LogicMatchValueType_Signed64:
	case Dz1LogicMatchValueType_Unsigned8:
	case Dz1LogicMatchValueType_Unsigned16:
	case Dz1LogicMatchValueType_Unsigned32:
	case Dz1LogicMatchValueType_Unsigned64:
		if (present == Dz1LogicMatchWPresent_number) ret = TRUE;
		break;
// 	case Dz1LogicMatchValueType_String:
// 		if (present == Dz1LogicMatchWPresent_text) ret = TRUE;
// 		break;
	default:
		break;
	}
	return ret;
}
#endif // UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// Signed
static Dz1Error _match_signed_simple(s64_t v, Dz1LogicMatchNumSimple *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(match->cond)
		{
		case Dz1LogicMatchType_LessThen:
			if (v < match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_GreaterThen:
			if (v > match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_Equal:
			if (v == match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_LessEqual:
			if (v <= match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_GreaterEqual:
			if (v >= match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
		}
	}
	return err;
}

static Dz1Error _match_signed_range(s64_t v, Dz1LogicMatchNumRange *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		bool_t low_cond = FALSE, high_cond = FALSE;
		if (match->LowInclude)
			low_cond = v >= match->LowValue ? TRUE : FALSE;
		else low_cond = v > match->LowValue ? TRUE : FALSE;

		if (match->HighInclude)
			high_cond = v <= match->HighValue ? TRUE : FALSE;
		else high_cond = v < match->HighValue ? TRUE : FALSE;

		(*ret_status) = low_cond && high_cond ? TRUE: FALSE;
	}
	return err;
}

static Dz1Error _match_signed(s64_t v, Dz1LogicMatchNum *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(match->present)
		{
		case Dz1LogicMatchNumPresent_simple:
			if ((*errp = _match_signed_simple(v, match->x.simple, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchNumPresent_range:
			if ((*errp = _match_signed_range(v, match->x.range, ret_status)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}
// Signed
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Unsigned
static __inline__ Dz1Error _match_unsigned_simple(u64_t v, Dz1LogicMatchNumSimple *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(match->cond)
		{
		case Dz1LogicMatchType_LessThen:
			if ( v < (u64_t)match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_GreaterThen:
			if ( v > (u64_t)match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_Equal:
			if ( v == (u64_t)match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_LessEqual:
			if ( v <= (u64_t)match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		case Dz1LogicMatchType_GreaterEqual:
			if ( v >= (u64_t)match->value) (*ret_status) = TRUE; else (*ret_status) = FALSE;
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
		}
	}
	return err;
}

static __inline__ Dz1Error _match_unsigned_range(u64_t v, Dz1LogicMatchNumRange *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		bool_t low_cond = FALSE, high_cond = FALSE;
		if (match->LowInclude)
			low_cond = v >= (u64_t)match->LowValue ? TRUE : FALSE;
		else low_cond = v > (u64_t)match->LowValue ? TRUE : FALSE;

		if (match->HighInclude)
			high_cond = v <= (u64_t)match->HighValue ? TRUE : FALSE;
		else high_cond = v < (u64_t)match->HighValue ? TRUE : FALSE;

		(*ret_status) = low_cond && high_cond ? TRUE: FALSE;
	}
	return err;
}

static Dz1Error _match_unsigned(u64_t v, Dz1LogicMatchNum *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (match == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		switch(match->present)
		{
		case Dz1LogicMatchNumPresent_simple:
			if ((*errp = _match_signed_simple(v, match->x.simple, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchNumPresent_range:
			if ((*errp = _match_signed_range(v, match->x.range, ret_status)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}
// Signed
///////////////////////////////////////////////////////////////////////////////

Dz1Error Dz1LogicsA_express(Dz1LogicMatchValueType type, void *addr_of_value, Dz1LogicMatchA *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (addr_of_value == NULL || match == NULL || ret_status == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_chk_relationA(type, match->present) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t vs64;
		u64_t vu64;
		switch(type)
		{
		case Dz1LogicMatchValueType_Signed8:
			vs64 = (s64_t)(*(s8_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed16:
			vs64 = (s64_t)(*(s16_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed32:
			vs64 = (s64_t)(*(s32_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed64:
			vs64 = (*(s64_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned8:
			vu64 = (u64_t)(*(u8_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned16:
			vu64 = (u64_t)(*(u16_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned32:
			vu64 = (u64_t)(*(u32_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned64:
			vu64 = (*(u64_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
// 		case Dz1LogicMatchValueType_String:
// 			if ((*errp = _match_stringA((str_t)addr_of_value, match->x.text, ret_status)).code) ERR_OUT(errp);
// 			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1LogicsW_express(Dz1LogicMatchValueType type, void *addr_of_value, Dz1LogicMatchW *match, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (addr_of_value == NULL || match == NULL || ret_status == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_chk_relationW(type, match->present) == FALSE) ERR_SET_OUT(errp, EINVAL);
	else
	{
		s64_t vs64;
		u64_t vu64;
		switch(type)
		{
		case Dz1LogicMatchValueType_Signed8:
			vs64 = (s64_t)(*(s8_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed16:
			vs64 = (s64_t)(*(s16_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed32:
			vs64 = (s64_t)(*(s32_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Signed64:
			vs64 = (*(s64_t *)addr_of_value);
			if ((*errp = _match_signed(vs64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned8:
			vu64 = (u64_t)(*(u8_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned16:
			vu64 = (u64_t)(*(u16_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned32:
			vu64 = (u64_t)(*(u32_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
		case Dz1LogicMatchValueType_Unsigned64:
			vu64 = (*(u64_t *)addr_of_value);
			if ((*errp = _match_unsigned(vu64, match->x.number, ret_status)).code) ERR_OUT(errp);
			break;
// 		case Dz1LogicMatchValueType_String:
// 			if ((*errp = _match_stringW((wstr_t)addr_of_value, match->x.text, ret_status)).code) ERR_OUT(errp);
// 			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return err;
}
#endif
