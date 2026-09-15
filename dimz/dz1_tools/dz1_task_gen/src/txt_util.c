#include "txt_util.h"

Dz1Str GetGUIDStr(Dz1Error *err)
{
	Dz1Str ret = NULL;

	char buf[40];
	DZ1_ERROR_SAFE_PTR(errp, err);

	MkGUIDStr(buf);
	if ((ret = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Get Relative Path
static ssize_t dividePath(Dz1Str inoutData, TCHAR *retList[127])
{
	ssize_t cnt = 0;

	TCHAR *dstp = inoutData;
	if (Dz1Str_isVoid(inoutData)) return -1;
	do
	{
		retList[cnt++] = dstp;
		if ((dstp = Dz1STRSTR(dstp, DIR_SEPRATOR)) != NULL) *dstp++ = 0;
	} while(dstp != NULL);

	if (cnt >= 1)
	{	// 드라이브 이름을 대문자로
		TCHAR *tp = retList[0];
		while(*tp)
		{
			if (*tp >= Dz1T('a') && *tp <= Dz1T('z')) *tp = (*tp) - Dz1T('a') + Dz1T('A');
			tp++;
		}
	}
	return cnt;
}

bool_t _get_relative_path(TCHAR *dst, size_t dst_sz, Dz1Str fromPath, Dz1Str toPath, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t fromLen = 0, toLen = 0;
	if (dst == 0 || dst_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (fromPath == NULL || (fromLen = Dz1STRLEN(fromPath)) < 2 || fromPath[1] != Dz1T(':')) ERR_SET_OUT(errp, EINVAL);	// check abs_path
	else if (toPath == NULL || (toLen = Dz1STRLEN(toPath)) < 2 || toPath[1] != Dz1T(':')) ERR_SET_OUT(errp, EINVAL);		// check abs_path
	else
	{
		ssize_t fromPathCnt = 0, toPathCnt = 0;
		TCHAR *fromPathList[127] = { NULL, }, *fromPathBuf = Dz1Str_dup(fromPath, errp);
		if (fromPathBuf == NULL) ERR_OUT(errp);
		else
		{
			TCHAR *toPathList[127] = { NULL, }, *toPathBuf = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)fromPathBuf);

			if ((toPathBuf = Dz1Str_dup(toPath, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Memory_cancel, (void *)toPathBuf);

				if		((fromPathCnt = dividePath(fromPathBuf, fromPathList)) < 0) ERR_SET_OUT(errp, EINVAL);
				else if ((toPathCnt = dividePath(toPathBuf, toPathList)) < 0) ERR_SET_OUT(errp, EINVAL);
				else if (Dz1STRCMP(fromPathList[0], toPathList[0]) != 0)
				{	// Complete Different
					Dz1STRCPY(dst, toPath);
				}
				else
				{
					TCHAR *dp = dst;

					size_t len = 0;
					ssize_t i, start_of_different;
					ssize_t cmpMax = fromPathCnt < toPathCnt ? fromPathCnt : toPathCnt;

					// find common part
					for (i = 0; i < cmpMax; i++) 
						if (Dz1STRCMP(fromPathList[i], toPathList[i]) != 0) break;
					start_of_different = i;

					// concatenate ".."
					for (i = start_of_different; errp->code == 0 && i < fromPathCnt; i++)
					{
						if (dp > dst)
						{
							if (dst_sz > 0)
							{
								*dp++ = DIR_SEP; 
								dst_sz--;
							}
							else
							{ 
								ERR_SET_OUT(errp, E2BIG);
								continue;
							}
						}

						if (dst_sz >= 2)
						{ 
							Dz1STRCPY(dp, Dz1T("..")); 
							dp += 2; 
							dst_sz -= 2;
						}
						else ERR_SET_OUT(errp, E2BIG);
					}

					// concatenate different path(s)
					for (i = start_of_different; errp->code == 0 && i < toPathCnt; i++)
					{
						if (dp > dst)
						{
							if (dst_sz > 0)
							{ 
								*dp++ = DIR_SEP;
								dst_sz--;
							}
							else
							{ 
								ERR_SET_OUT(errp, E2BIG);
								continue;
							}
						}

						if (dst_sz >= (len = Dz1STRLEN(toPathList[i])))
						{
							Dz1STRCPY(dp, toPathList[i]); 
							dp += len; 
							dst_sz -= len;
						}
						else ERR_SET_OUT(errp, E2BIG);
					}
					// Z terminate
					if (errp->code == 0 && dst_sz) { *dp++ = 0; dst_sz--; } else ERR_SET_OUT(errp, E2BIG);
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)toPathBuf);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)fromPathBuf);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Get Relative Path
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// _getDefineName
typedef enum StringParseState
{
	StringParseState_native,
	StringParseState_digit,
	StringParseState_UCase,
	StringParseState_LCase
} StringParseState;

Dz1Str _getDefineName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || dst_size <= 1 || Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else
	{
		size_t size = dst_size - 1;
		TCHAR *dp = dst, *sp = src, c;
		StringParseState state = StringParseState_native;
		while(errp->code == 0 && *sp && size > 0)
		{
			c = *sp++;
			if (c >= 'a' && c <= 'z')
			{	// low letter
				c = (c - 'a') + 'A';			// to upper case
				switch(state)
				{
				case StringParseState_digit:	// digit->LCase
					if (size > 0) { *dp++ = '_'; size--; } else { ERR_SET_OUT(errp, ENOMEM); continue; }
					state = StringParseState_native;
					break;
				case StringParseState_native:	// native->LCase
				case StringParseState_UCase:	// UCase->LCase
				case StringParseState_LCase:	// LCase->LCase
					state = StringParseState_LCase;
					break;
				}
			}
			else if (c >= 'A' && c <= 'Z')
			{	// upper case
				switch(state)
				{
				case StringParseState_digit:	// digit->UCase
				case StringParseState_LCase:	// LCase->UCase
					if (size > 0) { *dp++ = '_'; size--; } else { ERR_SET_OUT(errp, ENOMEM); continue; }
					state = StringParseState_native;
					break;
				case StringParseState_native:	// native->UCase
				case StringParseState_UCase:	// UCase->UCase
					state = StringParseState_UCase;
					break;
				}
			}
			else if (c >= '0' && c <= '9')
			{	// digits
				switch(state)
				{
				case StringParseState_native:	// native->digit
				case StringParseState_digit:	// digit->digit
				case StringParseState_UCase:	// UCase->digit
				case StringParseState_LCase:	// LCase->digit
					state = StringParseState_digit;
					break;
				}
			}
			else if (c == '_')
			{	// native
				switch(state)
				{
				case StringParseState_native:	// native->native
				case StringParseState_digit:	// digit->native
				case StringParseState_UCase:	// UCase->native
				case StringParseState_LCase:	// LCase->native
					state = StringParseState_native;
					break;
				}
			}
			else { ERR_SET_OUT(errp, EINVAL); continue; }

			if (size > 0) { *dp++ = c; size--; } else ERR_SET_OUT(errp, ENOMEM);
		}
		if (errp->code == 0 && size > 0) *dp = 0; else ERR_SET_OUT(errp, ENOMEM);
	}
	return errp->code == 0 ? dst : NULL;
}
// _getDefineName
///////////////////////////////////////////////////////////////////////////////

static ssize_t _canonicalString(TCHAR *dst, size_t dst_sz, Dz1Str src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR *dp = NULL;
	if ((dp = dst) == NULL || dst_sz == 0) ERR_SET_OUT(errp, EINVAL);
	else if (src != NULL)
	{
		TCHAR *sp = src;
		bool_t force_upper = TRUE;
		while(*sp && *sp == Dz1T('_')) sp++;				// skip underscore
		while(errp->code == 0 && *sp)
		{
			if (Dz1ISALPHA(*sp))
			{	// Alphabet
				if (force_upper)
				{
					if (dst_sz == 0) ERR_SET_OUT(errp, E2BIG);
					else
					{
						*dp++ = Dz1Letter_ucase(*sp);
						dst_sz--;
						force_upper = FALSE;
					}
				}
				else if (dst_sz == 0) ERR_SET_OUT(errp, E2BIG);
				else
				{
					*dp++ = *sp;
					dst_sz--;
				}
			}
			else if (*sp == Dz1T('_')) force_upper = TRUE; // omit '_'
			else
			{
				if (Dz1ISDIGIT(*sp)) force_upper = TRUE;
			
				if (dst_sz == 0) ERR_SET_OUT(errp, E2BIG);
				else
				{
					*dp++ = *sp;
					dst_sz--;
				}
			}
			sp++;
		}
		*dp = 0;
	}
	return errp->code == 0 ? (ssize_t)(dp - dst) : -1;
}

///////////////////////////////////////////////////////////////////////////////
// _getStructureName
Dz1Str _getStructureName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Str suffix_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t src_len = 0, suffix_len = Dz1Str_isVoid(suffix_name) ? 0 : Dz1STRLEN(suffix_name);

	if (dst == NULL || Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else if (dst_size <= ((src_len = Dz1STRLEN(src)) + suffix_len)) ERR_SET_OUT(errp, ENOMEM);
	else
	{
		TCHAR *dp = dst;
		ssize_t sz = _canonicalString(dp, dst_size, src, errp);
		if (sz < 0) ERR_OUT(errp);
		else
		{
			dp += sz;
			dst_size -= sz;
			if ((sz = _canonicalString(dp, dst_size, suffix_name, errp)) < 0) ERR_OUT(errp);
			else
			{
				dp += sz;
				dst_size -= sz;
				Dz1Error_set(errp, 0);
			}
		}
		*dp = 0;
	}
	return errp->code == 0 ? dst : NULL;
}
// _getStructureName
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// _getRuledName
Dz1Str _getRuledName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Str suffix_name, GenArgs2Naming rule, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t src_len = 0, suffix_len = Dz1Str_isVoid(suffix_name) ? 0 : Dz1STRLEN(suffix_name);

	if (suffix_len > 0 && rule == GenArgs2Naming_underscore) suffix_len++;

	if (dst == NULL || Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else if (dst_size <= (src_len = Dz1STRLEN(src)) + suffix_len) ERR_SET_OUT(errp, E2BIG);
	else
	{
		TCHAR *dp = dst;
		Dz1STRCPY(dp, src); dp += src_len; dst_size -= src_len;
		if (suffix_len > 0)
		{
			ssize_t sz = 0;
			bool_t flag = FALSE;
			TCHAR *sp = suffix_name;
			switch(rule)
			{
			case GenArgs2Naming_canonical:
				if ((sz = _canonicalString(dp, dst_size, suffix_name, errp)) < 0) ERR_OUT(errp);
				else
				{
					dp += sz;
					dst_size -= sz;
				}
				break;
			default:
			case GenArgs2Naming_underscore:
				*dp++ = Dz1T('_');									// attach single underscore
				while(*sp && *sp == Dz1T('_')) sp++;				// skip underscores
				flag = TRUE;										// previous is underscore
				while(*sp)
				{
					if (*sp == Dz1T('_'))
					{
						if (flag == FALSE) *dp++ = *sp;				// attach fresh underscore else skip
						flag = TRUE;								// previous is underscore
					}
					else
					{
						*dp++ = Dz1Letter_lcase(*sp);				// attach other letters
						flag = FALSE;								// previous is underscore
					}
					sp++;
				}
				break;
			}
		}
		*dp = 0;
	}
	return errp->code == 0 ? dst : NULL;
}
// _getRuledName
///////////////////////////////////////////////////////////////////////////////

