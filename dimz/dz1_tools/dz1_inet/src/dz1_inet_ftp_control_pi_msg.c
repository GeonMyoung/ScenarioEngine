////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_control_pi_msg.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPTextForm
static struct Dz1InetFtpDTPTextFormMapA
{
	str_t str;
	Dz1InetFtpDTPTextForm v;
} Dz1InetFtpDTPTextFormMapA[] =
{
	{ (char *)"nonPrint", Dz1InetFtpDTPTextForm_nonPrint },
	{ (char *)"telnet", Dz1InetFtpDTPTextForm_telnet },
	{ (char *)"asa", Dz1InetFtpDTPTextForm_asa },
	{ NULL, Dz1InetFtpDTPTextForm_max }
};

str_t Dz1InetFtpDTPTextFormStrA(Dz1InetFtpDTPTextForm v)
{
	struct Dz1InetFtpDTPTextFormMapA *i = NULL;
	for (i = Dz1InetFtpDTPTextFormMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPTextForm Dz1InetFtpDTPTextFormFromStrA(str_t str)
{
	struct Dz1InetFtpDTPTextFormMapA *i = NULL;
	for (i = Dz1InetFtpDTPTextFormMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPTextForm_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpDTPTextFormMapW
{
	wstr_t str;
	Dz1InetFtpDTPTextForm v;
} Dz1InetFtpDTPTextFormMapW[] =
{
	{ (wchar_t *)L"nonPrint", Dz1InetFtpDTPTextForm_nonPrint },
	{ (wchar_t *)L"telnet", Dz1InetFtpDTPTextForm_telnet },
	{ (wchar_t *)L"asa", Dz1InetFtpDTPTextForm_asa },
	{ NULL, Dz1InetFtpDTPTextForm_max }
};

wstr_t Dz1InetFtpDTPTextFormStrW(Dz1InetFtpDTPTextForm v)
{
	struct Dz1InetFtpDTPTextFormMapW *i = NULL;
	for (i = Dz1InetFtpDTPTextFormMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPTextForm Dz1InetFtpDTPTextFormFromStrW(wstr_t str)
{
	struct Dz1InetFtpDTPTextFormMapW *i = NULL;
	for (i = Dz1InetFtpDTPTextFormMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPTextForm_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpDTPTextForm *Dz1InetFtpDTPTextForm_new(Dz1InetFtpDTPTextForm *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPTextForm *__internal_ret = (Dz1InetFtpDTPTextForm *)Dz1Calloc(sizeof(Dz1InetFtpDTPTextForm), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpDTPTextForm
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPTypePresent
static struct Dz1InetFtpDTPTypePresentMapA
{
	str_t str;
	Dz1InetFtpDTPTypePresent v;
} Dz1InetFtpDTPTypePresentMapA[] =
{
	{ (char *)"ascii", Dz1InetFtpDTPTypePresent_ascii },
	{ (char *)"ebcdic", Dz1InetFtpDTPTypePresent_ebcdic },
	{ (char *)"image", Dz1InetFtpDTPTypePresent_image },
	{ (char *)"local", Dz1InetFtpDTPTypePresent_local },
	{ NULL, Dz1InetFtpDTPTypePresent_max }
};

str_t Dz1InetFtpDTPTypePresentStrA(Dz1InetFtpDTPTypePresent v)
{
	struct Dz1InetFtpDTPTypePresentMapA *i = NULL;
	for (i = Dz1InetFtpDTPTypePresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPTypePresent Dz1InetFtpDTPTypePresentFromStrA(str_t str)
{
	struct Dz1InetFtpDTPTypePresentMapA *i = NULL;
	for (i = Dz1InetFtpDTPTypePresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPTypePresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpDTPTypePresentMapW
{
	wstr_t str;
	Dz1InetFtpDTPTypePresent v;
} Dz1InetFtpDTPTypePresentMapW[] =
{
	{ (wchar_t *)L"ascii", Dz1InetFtpDTPTypePresent_ascii },
	{ (wchar_t *)L"ebcdic", Dz1InetFtpDTPTypePresent_ebcdic },
	{ (wchar_t *)L"image", Dz1InetFtpDTPTypePresent_image },
	{ (wchar_t *)L"local", Dz1InetFtpDTPTypePresent_local },
	{ NULL, Dz1InetFtpDTPTypePresent_max }
};

wstr_t Dz1InetFtpDTPTypePresentStrW(Dz1InetFtpDTPTypePresent v)
{
	struct Dz1InetFtpDTPTypePresentMapW *i = NULL;
	for (i = Dz1InetFtpDTPTypePresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPTypePresent Dz1InetFtpDTPTypePresentFromStrW(wstr_t str)
{
	struct Dz1InetFtpDTPTypePresentMapW *i = NULL;
	for (i = Dz1InetFtpDTPTypePresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPTypePresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpDTPTypePresent *Dz1InetFtpDTPTypePresent_new(Dz1InetFtpDTPTypePresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPTypePresent *__internal_ret = (Dz1InetFtpDTPTypePresent *)Dz1Calloc(sizeof(Dz1InetFtpDTPTypePresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetFtpDTPTypePresent_dump(Dz1InetFtpDTPTypePresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetFtpDTPTypePresentStr(*v));
}
// Dz1InetFtpDTPTypePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPType
Dz1InetFtpDTPType *Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPType *ret = (Dz1InetFtpDTPType *)Dz1Calloc(sizeof(Dz1InetFtpDTPType), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpDTPType_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetFtpDTPTypePresent_ascii:
			// _U_enum_clone
			if (ptr != NULL) ret->x.ascii = (Dz1InetFtpDTPTextForm *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpDTPTypePresent_ebcdic:
			// _U_enum_clone
			if (ptr != NULL) ret->x.ebcdic = (Dz1InetFtpDTPTextForm *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpDTPTypePresent_image:
			// _U_prim_clone
			if (ptr != NULL) ret->x.image = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpDTPTypePresent_local:
			// _U_prim_clone
			if (ptr != NULL) ret->x.local = *(u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpDTPTypePresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpDTPType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpDTPType_purge(Dz1InetFtpDTPType *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetFtpDTPTypePresent_ascii:
		Dz1InetFtpDTPTextForm_del(p->x.ascii);
		break;
	case Dz1InetFtpDTPTypePresent_ebcdic:
		Dz1InetFtpDTPTextForm_del(p->x.ebcdic);
		break;
	case Dz1InetFtpDTPTypePresent_image:
		Dz1u32_del(p->x.image);
		break;
	case Dz1InetFtpDTPTypePresent_local:
		break;
	default:
		break;
	}
}

void Dz1InetFtpDTPType_del(Dz1InetFtpDTPType *p)
{
	if (!p) return;
	Dz1InetFtpDTPType_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpDTPType_dump(Dz1InetFtpDTPType *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetFtpDTPTypePresent_ascii:
		if (p->x.ascii == NULL) Dz1Thread_printf(Dz1T("ascii = NULL\n"));
		else Dz1Thread_printf(Dz1T("ascii = %s(%d)\n"), Dz1InetFtpDTPTextFormStr(*p->x.ascii), *p->x.ascii);
		break;
	case Dz1InetFtpDTPTypePresent_ebcdic:
		if (p->x.ebcdic == NULL) Dz1Thread_printf(Dz1T("ebcdic = NULL\n"));
		else Dz1Thread_printf(Dz1T("ebcdic = %s(%d)\n"), Dz1InetFtpDTPTextFormStr(*p->x.ebcdic), *p->x.ebcdic);
		break;
	case Dz1InetFtpDTPTypePresent_image:
		Dz1Thread_printf(Dz1T("image = ")); Dz1u32_dump(p->x.image, tab); 
		break;
	case Dz1InetFtpDTPTypePresent_local:
		Dz1Thread_printf(Dz1T("local = ")); Dz1u32_dump(&p->x.local, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetFtpDTPType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPStruct
static struct Dz1InetFtpDTPStructMapA
{
	str_t str;
	Dz1InetFtpDTPStruct v;
} Dz1InetFtpDTPStructMapA[] =
{
	{ (char *)"file", Dz1InetFtpDTPStruct_file },
	{ (char *)"record", Dz1InetFtpDTPStruct_record },
	{ (char *)"page", Dz1InetFtpDTPStruct_page },
	{ NULL, Dz1InetFtpDTPStruct_max }
};

str_t Dz1InetFtpDTPStructStrA(Dz1InetFtpDTPStruct v)
{
	struct Dz1InetFtpDTPStructMapA *i = NULL;
	for (i = Dz1InetFtpDTPStructMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPStruct Dz1InetFtpDTPStructFromStrA(str_t str)
{
	struct Dz1InetFtpDTPStructMapA *i = NULL;
	for (i = Dz1InetFtpDTPStructMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPStruct_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpDTPStructMapW
{
	wstr_t str;
	Dz1InetFtpDTPStruct v;
} Dz1InetFtpDTPStructMapW[] =
{
	{ (wchar_t *)L"file", Dz1InetFtpDTPStruct_file },
	{ (wchar_t *)L"record", Dz1InetFtpDTPStruct_record },
	{ (wchar_t *)L"page", Dz1InetFtpDTPStruct_page },
	{ NULL, Dz1InetFtpDTPStruct_max }
};

wstr_t Dz1InetFtpDTPStructStrW(Dz1InetFtpDTPStruct v)
{
	struct Dz1InetFtpDTPStructMapW *i = NULL;
	for (i = Dz1InetFtpDTPStructMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPStruct Dz1InetFtpDTPStructFromStrW(wstr_t str)
{
	struct Dz1InetFtpDTPStructMapW *i = NULL;
	for (i = Dz1InetFtpDTPStructMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPStruct_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpDTPStruct *Dz1InetFtpDTPStruct_new(Dz1InetFtpDTPStruct *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPStruct *__internal_ret = (Dz1InetFtpDTPStruct *)Dz1Calloc(sizeof(Dz1InetFtpDTPStruct), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpDTPStruct
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPMode
static struct Dz1InetFtpDTPModeMapA
{
	str_t str;
	Dz1InetFtpDTPMode v;
} Dz1InetFtpDTPModeMapA[] =
{
	{ (char *)"stream", Dz1InetFtpDTPMode_stream },
	{ (char *)"block", Dz1InetFtpDTPMode_block },
	{ (char *)"compressed", Dz1InetFtpDTPMode_compressed },
	{ NULL, Dz1InetFtpDTPMode_max }
};

str_t Dz1InetFtpDTPModeStrA(Dz1InetFtpDTPMode v)
{
	struct Dz1InetFtpDTPModeMapA *i = NULL;
	for (i = Dz1InetFtpDTPModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPMode Dz1InetFtpDTPModeFromStrA(str_t str)
{
	struct Dz1InetFtpDTPModeMapA *i = NULL;
	for (i = Dz1InetFtpDTPModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpDTPModeMapW
{
	wstr_t str;
	Dz1InetFtpDTPMode v;
} Dz1InetFtpDTPModeMapW[] =
{
	{ (wchar_t *)L"stream", Dz1InetFtpDTPMode_stream },
	{ (wchar_t *)L"block", Dz1InetFtpDTPMode_block },
	{ (wchar_t *)L"compressed", Dz1InetFtpDTPMode_compressed },
	{ NULL, Dz1InetFtpDTPMode_max }
};

wstr_t Dz1InetFtpDTPModeStrW(Dz1InetFtpDTPMode v)
{
	struct Dz1InetFtpDTPModeMapW *i = NULL;
	for (i = Dz1InetFtpDTPModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpDTPMode Dz1InetFtpDTPModeFromStrW(wstr_t str)
{
	struct Dz1InetFtpDTPModeMapW *i = NULL;
	for (i = Dz1InetFtpDTPModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpDTPMode_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpDTPMode *Dz1InetFtpDTPMode_new(Dz1InetFtpDTPMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPMode *__internal_ret = (Dz1InetFtpDTPMode *)Dz1Calloc(sizeof(Dz1InetFtpDTPMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpDTPMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpAlloc
Dz1InetFtpAlloc *Dz1InetFtpAlloc_new(u32_t numOfOctet, u32_t *numOfRecord, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpAlloc *__internal_ret = (Dz1InetFtpAlloc *)Dz1Calloc(sizeof(Dz1InetFtpAlloc), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpAlloc_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->numOfOctet = numOfOctet;
		__internal_ret->numOfRecord = numOfRecord;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpAlloc_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpAlloc_purge(Dz1InetFtpAlloc *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->numOfRecord);
}

void Dz1InetFtpAlloc_del(Dz1InetFtpAlloc *p)
{
	if (p == NULL) return;
	Dz1InetFtpAlloc_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpAlloc_dump(Dz1InetFtpAlloc *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("numOfOctet = ")); Dz1u32_dump(&p->numOfOctet, tab); 
		Dz1Thread_tprintf(tab, Dz1T("numOfRecord = ")); Dz1u32_dump(p->numOfRecord, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpAlloc
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReqPresent
static struct Dz1InetFtpCPIMsgReqPresentMapA
{
	str_t str;
	Dz1InetFtpCPIMsgReqPresent v;
} Dz1InetFtpCPIMsgReqPresentMapA[] =
{
	{ (char *)"user", Dz1InetFtpCPIMsgReqPresent_user },
	{ (char *)"pass", Dz1InetFtpCPIMsgReqPresent_pass },
	{ (char *)"acct", Dz1InetFtpCPIMsgReqPresent_acct },
	{ (char *)"cwd", Dz1InetFtpCPIMsgReqPresent_cwd },
	{ (char *)"cdup", Dz1InetFtpCPIMsgReqPresent_cdup },
	{ (char *)"smnt", Dz1InetFtpCPIMsgReqPresent_smnt },
	{ (char *)"quit", Dz1InetFtpCPIMsgReqPresent_quit },
	{ (char *)"rein", Dz1InetFtpCPIMsgReqPresent_rein },
	{ (char *)"port", Dz1InetFtpCPIMsgReqPresent_port },
	{ (char *)"pasv", Dz1InetFtpCPIMsgReqPresent_pasv },
	{ (char *)"type", Dz1InetFtpCPIMsgReqPresent_type },
	{ (char *)"stru", Dz1InetFtpCPIMsgReqPresent_stru },
	{ (char *)"mode", Dz1InetFtpCPIMsgReqPresent_mode },
	{ (char *)"retr", Dz1InetFtpCPIMsgReqPresent_retr },
	{ (char *)"stor", Dz1InetFtpCPIMsgReqPresent_stor },
	{ (char *)"stou", Dz1InetFtpCPIMsgReqPresent_stou },
	{ (char *)"appe", Dz1InetFtpCPIMsgReqPresent_appe },
	{ (char *)"allo", Dz1InetFtpCPIMsgReqPresent_allo },
	{ (char *)"rest", Dz1InetFtpCPIMsgReqPresent_rest },
	{ (char *)"rnfr", Dz1InetFtpCPIMsgReqPresent_rnfr },
	{ (char *)"rnto", Dz1InetFtpCPIMsgReqPresent_rnto },
	{ (char *)"abor", Dz1InetFtpCPIMsgReqPresent_abor },
	{ (char *)"dele", Dz1InetFtpCPIMsgReqPresent_dele },
	{ (char *)"rmd", Dz1InetFtpCPIMsgReqPresent_rmd },
	{ (char *)"mkd", Dz1InetFtpCPIMsgReqPresent_mkd },
	{ (char *)"pwd", Dz1InetFtpCPIMsgReqPresent_pwd },
	{ (char *)"list", Dz1InetFtpCPIMsgReqPresent_list },
	{ (char *)"nlst", Dz1InetFtpCPIMsgReqPresent_nlst },
	{ (char *)"site", Dz1InetFtpCPIMsgReqPresent_site },
	{ (char *)"syst", Dz1InetFtpCPIMsgReqPresent_syst },
	{ (char *)"stat", Dz1InetFtpCPIMsgReqPresent_stat },
	{ (char *)"help", Dz1InetFtpCPIMsgReqPresent_help },
	{ (char *)"size", Dz1InetFtpCPIMsgReqPresent_size },
	{ (char *)"feat", Dz1InetFtpCPIMsgReqPresent_feat },
	{ NULL, Dz1InetFtpCPIMsgReqPresent_max }
};

str_t Dz1InetFtpCPIMsgReqPresentStrA(Dz1InetFtpCPIMsgReqPresent v)
{
	struct Dz1InetFtpCPIMsgReqPresentMapA *i = NULL;
	for (i = Dz1InetFtpCPIMsgReqPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCPIMsgReqPresent Dz1InetFtpCPIMsgReqPresentFromStrA(str_t str)
{
	struct Dz1InetFtpCPIMsgReqPresentMapA *i = NULL;
	for (i = Dz1InetFtpCPIMsgReqPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCPIMsgReqPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpCPIMsgReqPresentMapW
{
	wstr_t str;
	Dz1InetFtpCPIMsgReqPresent v;
} Dz1InetFtpCPIMsgReqPresentMapW[] =
{
	{ (wchar_t *)L"user", Dz1InetFtpCPIMsgReqPresent_user },
	{ (wchar_t *)L"pass", Dz1InetFtpCPIMsgReqPresent_pass },
	{ (wchar_t *)L"acct", Dz1InetFtpCPIMsgReqPresent_acct },
	{ (wchar_t *)L"cwd", Dz1InetFtpCPIMsgReqPresent_cwd },
	{ (wchar_t *)L"cdup", Dz1InetFtpCPIMsgReqPresent_cdup },
	{ (wchar_t *)L"smnt", Dz1InetFtpCPIMsgReqPresent_smnt },
	{ (wchar_t *)L"quit", Dz1InetFtpCPIMsgReqPresent_quit },
	{ (wchar_t *)L"rein", Dz1InetFtpCPIMsgReqPresent_rein },
	{ (wchar_t *)L"port", Dz1InetFtpCPIMsgReqPresent_port },
	{ (wchar_t *)L"pasv", Dz1InetFtpCPIMsgReqPresent_pasv },
	{ (wchar_t *)L"type", Dz1InetFtpCPIMsgReqPresent_type },
	{ (wchar_t *)L"stru", Dz1InetFtpCPIMsgReqPresent_stru },
	{ (wchar_t *)L"mode", Dz1InetFtpCPIMsgReqPresent_mode },
	{ (wchar_t *)L"retr", Dz1InetFtpCPIMsgReqPresent_retr },
	{ (wchar_t *)L"stor", Dz1InetFtpCPIMsgReqPresent_stor },
	{ (wchar_t *)L"stou", Dz1InetFtpCPIMsgReqPresent_stou },
	{ (wchar_t *)L"appe", Dz1InetFtpCPIMsgReqPresent_appe },
	{ (wchar_t *)L"allo", Dz1InetFtpCPIMsgReqPresent_allo },
	{ (wchar_t *)L"rest", Dz1InetFtpCPIMsgReqPresent_rest },
	{ (wchar_t *)L"rnfr", Dz1InetFtpCPIMsgReqPresent_rnfr },
	{ (wchar_t *)L"rnto", Dz1InetFtpCPIMsgReqPresent_rnto },
	{ (wchar_t *)L"abor", Dz1InetFtpCPIMsgReqPresent_abor },
	{ (wchar_t *)L"dele", Dz1InetFtpCPIMsgReqPresent_dele },
	{ (wchar_t *)L"rmd", Dz1InetFtpCPIMsgReqPresent_rmd },
	{ (wchar_t *)L"mkd", Dz1InetFtpCPIMsgReqPresent_mkd },
	{ (wchar_t *)L"pwd", Dz1InetFtpCPIMsgReqPresent_pwd },
	{ (wchar_t *)L"list", Dz1InetFtpCPIMsgReqPresent_list },
	{ (wchar_t *)L"nlst", Dz1InetFtpCPIMsgReqPresent_nlst },
	{ (wchar_t *)L"site", Dz1InetFtpCPIMsgReqPresent_site },
	{ (wchar_t *)L"syst", Dz1InetFtpCPIMsgReqPresent_syst },
	{ (wchar_t *)L"stat", Dz1InetFtpCPIMsgReqPresent_stat },
	{ (wchar_t *)L"help", Dz1InetFtpCPIMsgReqPresent_help },
	{ (wchar_t *)L"size", Dz1InetFtpCPIMsgReqPresent_size },
	{ (wchar_t *)L"feat", Dz1InetFtpCPIMsgReqPresent_feat },
	{ NULL, Dz1InetFtpCPIMsgReqPresent_max }
};

wstr_t Dz1InetFtpCPIMsgReqPresentStrW(Dz1InetFtpCPIMsgReqPresent v)
{
	struct Dz1InetFtpCPIMsgReqPresentMapW *i = NULL;
	for (i = Dz1InetFtpCPIMsgReqPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCPIMsgReqPresent Dz1InetFtpCPIMsgReqPresentFromStrW(wstr_t str)
{
	struct Dz1InetFtpCPIMsgReqPresentMapW *i = NULL;
	for (i = Dz1InetFtpCPIMsgReqPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCPIMsgReqPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpCPIMsgReqPresent *Dz1InetFtpCPIMsgReqPresent_new(Dz1InetFtpCPIMsgReqPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgReqPresent *__internal_ret = (Dz1InetFtpCPIMsgReqPresent *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsgReqPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetFtpCPIMsgReqPresent_dump(Dz1InetFtpCPIMsgReqPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetFtpCPIMsgReqPresentStr(*v));
}
// Dz1InetFtpCPIMsgReqPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReq
Dz1InetFtpCPIMsgReq *Dz1InetFtpCPIMsgReq_new(Dz1InetFtpCPIMsgReqPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgReq *ret = (Dz1InetFtpCPIMsgReq *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsgReq), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpCPIMsgReq_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetFtpCPIMsgReqPresent_user:
			// _U_prim_clone
			if (ptr && (ret->x.user = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_pass:
			// _U_prim_clone
			if (ptr && (ret->x.pass = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_acct:
			// _U_prim_clone
			if (ptr && (ret->x.acct = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_cwd:
			// _U_prim_clone
			if (ptr && (ret->x.cwd = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_cdup:
			// _U_prim_clone
			if (ptr != NULL) ret->x.cdup = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_smnt:
			// _U_prim_clone
			if (ptr && (ret->x.smnt = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_quit:
			// _U_prim_clone
			if (ptr != NULL) ret->x.quit = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_rein:
			// _U_prim_clone
			if (ptr != NULL) ret->x.rein = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_port:
			// _U_imp_clone
			if (ptr != NULL) ret->x.port = (Dz1SockAddr *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_pasv:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pasv = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_type:
			// _U_cst_clone
			if (ptr != NULL) ret->x.type = (Dz1InetFtpDTPType *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_stru:
			// _U_enum_clone
			if (ptr != NULL) ret->x.stru = *(Dz1InetFtpDTPStruct *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_mode:
			// _U_enum_clone
			if (ptr != NULL) ret->x.mode = *(Dz1InetFtpDTPMode *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_retr:
			// _U_prim_clone
			if (ptr && (ret->x.retr = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_stor:
			// _U_prim_clone
			if (ptr && (ret->x.stor = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_stou:
			// _U_prim_clone
			if (ptr != NULL) ret->x.stou = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_appe:
			// _U_prim_clone
			if (ptr && (ret->x.appe = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_allo:
			// _U_cst_clone
			if (ptr != NULL) ret->x.allo = (Dz1InetFtpAlloc *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_rest:
			// _U_prim_clone
			if (ptr && (ret->x.rest = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_rnfr:
			// _U_prim_clone
			if (ptr && (ret->x.rnfr = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_rnto:
			// _U_prim_clone
			if (ptr && (ret->x.rnto = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_abor:
			// _U_prim_clone
			if (ptr != NULL) ret->x.abor = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_dele:
			// _U_prim_clone
			if (ptr && (ret->x.dele = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_rmd:
			// _U_prim_clone
			if (ptr && (ret->x.rmd = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_mkd:
			// _U_prim_clone
			if (ptr && (ret->x.mkd = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_pwd:
			// _U_prim_clone
			if (ptr != NULL) ret->x.pwd = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_list:
			// _U_prim_clone
			if (ptr && (ret->x.list = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_nlst:
			// _U_prim_clone
			if (ptr && (ret->x.nlst = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_site:
			// _U_prim_clone
			if (ptr && (ret->x.site = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_syst:
			// _U_prim_clone
			if (ptr != NULL) ret->x.syst = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_stat:
			// _U_prim_clone
			if (ptr && (ret->x.stat = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_help:
			// _U_prim_clone
			if (ptr && (ret->x.help = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_size:
			// _U_prim_clone
			if (ptr && (ret->x.size = dz1_built_in_str_clone((str_t)ptr, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1InetFtpCPIMsgReqPresent_feat:
			// _U_prim_clone
			if (ptr != NULL) ret->x.feat = (u32_t *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgReqPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpCPIMsgReq_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpCPIMsgReq_purge(Dz1InetFtpCPIMsgReq *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetFtpCPIMsgReqPresent_user:
		dz1_built_in_str_del(p->x.user);
		break;
	case Dz1InetFtpCPIMsgReqPresent_pass:
		dz1_built_in_str_del(p->x.pass);
		break;
	case Dz1InetFtpCPIMsgReqPresent_acct:
		dz1_built_in_str_del(p->x.acct);
		break;
	case Dz1InetFtpCPIMsgReqPresent_cwd:
		dz1_built_in_str_del(p->x.cwd);
		break;
	case Dz1InetFtpCPIMsgReqPresent_cdup:
		Dz1u32_del(p->x.cdup);
		break;
	case Dz1InetFtpCPIMsgReqPresent_smnt:
		dz1_built_in_str_del(p->x.smnt);
		break;
	case Dz1InetFtpCPIMsgReqPresent_quit:
		Dz1u32_del(p->x.quit);
		break;
	case Dz1InetFtpCPIMsgReqPresent_rein:
		Dz1u32_del(p->x.rein);
		break;
	case Dz1InetFtpCPIMsgReqPresent_port:
		Dz1SockAddr_del(p->x.port);
		break;
	case Dz1InetFtpCPIMsgReqPresent_pasv:
		Dz1u32_del(p->x.pasv);
		break;
	case Dz1InetFtpCPIMsgReqPresent_type:
		Dz1InetFtpDTPType_del(p->x.type);
		break;
	case Dz1InetFtpCPIMsgReqPresent_stru:
		break;
	case Dz1InetFtpCPIMsgReqPresent_mode:
		break;
	case Dz1InetFtpCPIMsgReqPresent_retr:
		dz1_built_in_str_del(p->x.retr);
		break;
	case Dz1InetFtpCPIMsgReqPresent_stor:
		dz1_built_in_str_del(p->x.stor);
		break;
	case Dz1InetFtpCPIMsgReqPresent_stou:
		Dz1u32_del(p->x.stou);
		break;
	case Dz1InetFtpCPIMsgReqPresent_appe:
		dz1_built_in_str_del(p->x.appe);
		break;
	case Dz1InetFtpCPIMsgReqPresent_allo:
		Dz1InetFtpAlloc_del(p->x.allo);
		break;
	case Dz1InetFtpCPIMsgReqPresent_rest:
		dz1_built_in_str_del(p->x.rest);
		break;
	case Dz1InetFtpCPIMsgReqPresent_rnfr:
		dz1_built_in_str_del(p->x.rnfr);
		break;
	case Dz1InetFtpCPIMsgReqPresent_rnto:
		dz1_built_in_str_del(p->x.rnto);
		break;
	case Dz1InetFtpCPIMsgReqPresent_abor:
		Dz1u32_del(p->x.abor);
		break;
	case Dz1InetFtpCPIMsgReqPresent_dele:
		dz1_built_in_str_del(p->x.dele);
		break;
	case Dz1InetFtpCPIMsgReqPresent_rmd:
		dz1_built_in_str_del(p->x.rmd);
		break;
	case Dz1InetFtpCPIMsgReqPresent_mkd:
		dz1_built_in_str_del(p->x.mkd);
		break;
	case Dz1InetFtpCPIMsgReqPresent_pwd:
		Dz1u32_del(p->x.pwd);
		break;
	case Dz1InetFtpCPIMsgReqPresent_list:
		dz1_built_in_str_del(p->x.list);
		break;
	case Dz1InetFtpCPIMsgReqPresent_nlst:
		dz1_built_in_str_del(p->x.nlst);
		break;
	case Dz1InetFtpCPIMsgReqPresent_site:
		dz1_built_in_str_del(p->x.site);
		break;
	case Dz1InetFtpCPIMsgReqPresent_syst:
		Dz1u32_del(p->x.syst);
		break;
	case Dz1InetFtpCPIMsgReqPresent_stat:
		dz1_built_in_str_del(p->x.stat);
		break;
	case Dz1InetFtpCPIMsgReqPresent_help:
		dz1_built_in_str_del(p->x.help);
		break;
	case Dz1InetFtpCPIMsgReqPresent_size:
		dz1_built_in_str_del(p->x.size);
		break;
	case Dz1InetFtpCPIMsgReqPresent_feat:
		Dz1u32_del(p->x.feat);
		break;
	default:
		break;
	}
}

void Dz1InetFtpCPIMsgReq_del(Dz1InetFtpCPIMsgReq *p)
{
	if (!p) return;
	Dz1InetFtpCPIMsgReq_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpCPIMsgReq_dump(Dz1InetFtpCPIMsgReq *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetFtpCPIMsgReqPresent_user:
		Dz1Thread_printf(Dz1T("user = ")); dz1_built_in_str_dump(p->x.user, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_pass:
		Dz1Thread_printf(Dz1T("pass = ")); dz1_built_in_str_dump(p->x.pass, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_acct:
		Dz1Thread_printf(Dz1T("acct = ")); dz1_built_in_str_dump(p->x.acct, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_cwd:
		Dz1Thread_printf(Dz1T("cwd = ")); dz1_built_in_str_dump(p->x.cwd, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_cdup:
		Dz1Thread_printf(Dz1T("cdup = ")); Dz1u32_dump(p->x.cdup, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_smnt:
		Dz1Thread_printf(Dz1T("smnt = ")); dz1_built_in_str_dump(p->x.smnt, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_quit:
		Dz1Thread_printf(Dz1T("quit = ")); Dz1u32_dump(p->x.quit, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_rein:
		Dz1Thread_printf(Dz1T("rein = ")); Dz1u32_dump(p->x.rein, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_port:
		Dz1Thread_printf(Dz1T("port = ")); Dz1SockAddr_dump(p->x.port, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_pasv:
		Dz1Thread_printf(Dz1T("pasv = ")); Dz1u32_dump(p->x.pasv, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_type:
		Dz1Thread_printf(Dz1T("type.")); Dz1InetFtpDTPType_dump(p->x.type, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_stru:
		Dz1Thread_printf(Dz1T("stru = %s(%d)\n"), Dz1InetFtpDTPStructStr(p->x.stru), p->x.stru);
		break;
	case Dz1InetFtpCPIMsgReqPresent_mode:
		Dz1Thread_printf(Dz1T("mode = %s(%d)\n"), Dz1InetFtpDTPModeStr(p->x.mode), p->x.mode);
		break;
	case Dz1InetFtpCPIMsgReqPresent_retr:
		Dz1Thread_printf(Dz1T("retr = ")); dz1_built_in_str_dump(p->x.retr, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_stor:
		Dz1Thread_printf(Dz1T("stor = ")); dz1_built_in_str_dump(p->x.stor, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_stou:
		Dz1Thread_printf(Dz1T("stou = ")); Dz1u32_dump(p->x.stou, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_appe:
		Dz1Thread_printf(Dz1T("appe = ")); dz1_built_in_str_dump(p->x.appe, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_allo:
		Dz1Thread_printf(Dz1T("allo = ")); Dz1InetFtpAlloc_dump(p->x.allo, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_rest:
		Dz1Thread_printf(Dz1T("rest = ")); dz1_built_in_str_dump(p->x.rest, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_rnfr:
		Dz1Thread_printf(Dz1T("rnfr = ")); dz1_built_in_str_dump(p->x.rnfr, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_rnto:
		Dz1Thread_printf(Dz1T("rnto = ")); dz1_built_in_str_dump(p->x.rnto, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_abor:
		Dz1Thread_printf(Dz1T("abor = ")); Dz1u32_dump(p->x.abor, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_dele:
		Dz1Thread_printf(Dz1T("dele = ")); dz1_built_in_str_dump(p->x.dele, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_rmd:
		Dz1Thread_printf(Dz1T("rmd = ")); dz1_built_in_str_dump(p->x.rmd, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_mkd:
		Dz1Thread_printf(Dz1T("mkd = ")); dz1_built_in_str_dump(p->x.mkd, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_pwd:
		Dz1Thread_printf(Dz1T("pwd = ")); Dz1u32_dump(p->x.pwd, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_list:
		Dz1Thread_printf(Dz1T("list = ")); dz1_built_in_str_dump(p->x.list, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_nlst:
		Dz1Thread_printf(Dz1T("nlst = ")); dz1_built_in_str_dump(p->x.nlst, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_site:
		Dz1Thread_printf(Dz1T("site = ")); dz1_built_in_str_dump(p->x.site, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_syst:
		Dz1Thread_printf(Dz1T("syst = ")); Dz1u32_dump(p->x.syst, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_stat:
		Dz1Thread_printf(Dz1T("stat = ")); dz1_built_in_str_dump(p->x.stat, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_help:
		Dz1Thread_printf(Dz1T("help = ")); dz1_built_in_str_dump(p->x.help, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_size:
		Dz1Thread_printf(Dz1T("size = ")); dz1_built_in_str_dump(p->x.size, tab); 
		break;
	case Dz1InetFtpCPIMsgReqPresent_feat:
		Dz1Thread_printf(Dz1T("feat = ")); Dz1u32_dump(p->x.feat, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetFtpCPIMsgReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReplyTextList
static Dz1Error Dz1InetFtpCPIMsgReplyTextList_add(Dz1InetFtpCPIMsgReplyTextList *p, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1InetFtpCPIMsgReplyTextListMkArrArg
{
	str_t *arr;
	unsigned int idx;
} Dz1InetFtpCPIMsgReplyTextListMkArrArg;

static Dz1Error _Dz1InetFtpCPIMsgReplyTextList_get_array(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpCPIMsgReplyTextListMkArrArg *arg = (Dz1InetFtpCPIMsgReplyTextListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static str_t *Dz1InetFtpCPIMsgReplyTextList_get_array(Dz1InetFtpCPIMsgReplyTextList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	str_t *ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (str_t *)Dz1Calloc(sizeof(str_t *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1InetFtpCPIMsgReplyTextListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1InetFtpCPIMsgReplyTextList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1InetFtpCPIMsgReplyTextList_travelForward(Dz1InetFtpCPIMsgReplyTextList *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1InetFtpCPIMsgReplyTextList_travelBackward(Dz1InetFtpCPIMsgReplyTextList *p, Dz1Error (*func)(void *ptr, str_t data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static str_t Dz1InetFtpCPIMsgReplyTextList_getTail(Dz1InetFtpCPIMsgReplyTextList *p)
{
	return (str_t )Dz1Fifo_getLast(p->storage);
}

static unsigned int Dz1InetFtpCPIMsgReplyTextList_count(Dz1InetFtpCPIMsgReplyTextList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1InetFtpCPIMsgReplyTextList *Dz1InetFtpCPIMsgReplyTextList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgReplyTextList *ret = (Dz1InetFtpCPIMsgReplyTextList *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsgReplyTextList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpCPIMsgReplyTextList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)dz1_built_in_str_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1InetFtpCPIMsgReplyTextList_count;
			ret->travel = Dz1InetFtpCPIMsgReplyTextList_travelForward;
			ret->travelForward = Dz1InetFtpCPIMsgReplyTextList_travelForward;
			ret->travelBackward = Dz1InetFtpCPIMsgReplyTextList_travelBackward;
			ret->get_array = Dz1InetFtpCPIMsgReplyTextList_get_array;
			ret->add = Dz1InetFtpCPIMsgReplyTextList_add;
			ret->getTail = Dz1InetFtpCPIMsgReplyTextList_getTail;
			ret->cmp = dz1_built_in_str_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpCPIMsgReplyTextList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1InetFtpCPIMsgReplyTextList_clone(void *ptr, str_t data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpCPIMsgReplyTextList *p = (Dz1InetFtpCPIMsgReplyTextList *)ptr;
	str_t cloned = dz1_built_in_str_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1InetFtpCPIMsgReplyTextList *Dz1InetFtpCPIMsgReplyTextList_clone(Dz1InetFtpCPIMsgReplyTextList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgReplyTextList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1InetFtpCPIMsgReplyTextList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpCPIMsgReplyTextList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1InetFtpCPIMsgReplyTextList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpCPIMsgReplyTextList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpCPIMsgReplyTextList_purge(Dz1InetFtpCPIMsgReplyTextList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1InetFtpCPIMsgReplyTextList_del(Dz1InetFtpCPIMsgReplyTextList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1InetFtpCPIMsgReplyTextList_dump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); dz1_built_in_str_dump(p, tab);
	return err;
}

void Dz1InetFtpCPIMsgReplyTextList_dump(Dz1InetFtpCPIMsgReplyTextList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1InetFtpCPIMsgReplyTextList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
static Dz1Error _Dz1InetFtpCPIMsgReplyTextList_fdump(void *ptr, str_t p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1Thread_ftprintf(arg->fp, tab, Dz1T("entry = ")); dz1_built_in_str_fdump(arg->fp, p, tab);
	return err;
}

void Dz1InetFtpCPIMsgReplyTextList_fdump(FILE *fp, Dz1InetFtpCPIMsgReplyTextList *p, int tab)
{
	if (!p) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1Thread_ftprintf(fp, tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1InetFtpCPIMsgReplyTextList_fdump, (void *)&arg);
		Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpCPIMsgReplyTextList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgReply
Dz1InetFtpCPIMsgReply *Dz1InetFtpCPIMsgReply_new(u32_t code, str_t title, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgReply *__internal_ret = (Dz1InetFtpCPIMsgReply *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsgReply), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpCPIMsgReply_delAndSetNull, (void *)&__internal_ret);
		
		if (title && (__internal_ret->title = dz1_built_in_str_clone(title, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->list = Dz1InetFtpCPIMsgReplyTextList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->code = code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpCPIMsgReply_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpCPIMsgReply_purge(Dz1InetFtpCPIMsgReply *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->title);
	Dz1InetFtpCPIMsgReplyTextList_del(p->list);
}

void Dz1InetFtpCPIMsgReply_del(Dz1InetFtpCPIMsgReply *p)
{
	if (p == NULL) return;
	Dz1InetFtpCPIMsgReply_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpCPIMsgReply_dump(Dz1InetFtpCPIMsgReply *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("code = ")); Dz1u32_dump(&p->code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("title = ")); dz1_built_in_str_dump(p->title, tab); 
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1InetFtpCPIMsgReplyTextList_dump(p->list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpCPIMsgReply
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsgPresent
static struct Dz1InetFtpCPIMsgPresentMapA
{
	str_t str;
	Dz1InetFtpCPIMsgPresent v;
} Dz1InetFtpCPIMsgPresentMapA[] =
{
	{ (char *)"req", Dz1InetFtpCPIMsgPresent_req },
	{ (char *)"reply", Dz1InetFtpCPIMsgPresent_reply },
	{ NULL, Dz1InetFtpCPIMsgPresent_max }
};

str_t Dz1InetFtpCPIMsgPresentStrA(Dz1InetFtpCPIMsgPresent v)
{
	struct Dz1InetFtpCPIMsgPresentMapA *i = NULL;
	for (i = Dz1InetFtpCPIMsgPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCPIMsgPresent Dz1InetFtpCPIMsgPresentFromStrA(str_t str)
{
	struct Dz1InetFtpCPIMsgPresentMapA *i = NULL;
	for (i = Dz1InetFtpCPIMsgPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCPIMsgPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpCPIMsgPresentMapW
{
	wstr_t str;
	Dz1InetFtpCPIMsgPresent v;
} Dz1InetFtpCPIMsgPresentMapW[] =
{
	{ (wchar_t *)L"req", Dz1InetFtpCPIMsgPresent_req },
	{ (wchar_t *)L"reply", Dz1InetFtpCPIMsgPresent_reply },
	{ NULL, Dz1InetFtpCPIMsgPresent_max }
};

wstr_t Dz1InetFtpCPIMsgPresentStrW(Dz1InetFtpCPIMsgPresent v)
{
	struct Dz1InetFtpCPIMsgPresentMapW *i = NULL;
	for (i = Dz1InetFtpCPIMsgPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpCPIMsgPresent Dz1InetFtpCPIMsgPresentFromStrW(wstr_t str)
{
	struct Dz1InetFtpCPIMsgPresentMapW *i = NULL;
	for (i = Dz1InetFtpCPIMsgPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpCPIMsgPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpCPIMsgPresent *Dz1InetFtpCPIMsgPresent_new(Dz1InetFtpCPIMsgPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsgPresent *__internal_ret = (Dz1InetFtpCPIMsgPresent *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsgPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1InetFtpCPIMsgPresent_dump(Dz1InetFtpCPIMsgPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1InetFtpCPIMsgPresentStr(*v));
}
// Dz1InetFtpCPIMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpCPIMsg
Dz1InetFtpCPIMsg *Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpCPIMsg *ret = (Dz1InetFtpCPIMsg *)Dz1Calloc(sizeof(Dz1InetFtpCPIMsg), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpCPIMsg_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetFtpCPIMsgPresent_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req = (Dz1InetFtpCPIMsgReq *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgPresent_reply:
			// _U_cst_clone
			if (ptr != NULL) ret->x.reply = (Dz1InetFtpCPIMsgReply *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpCPIMsgPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpCPIMsg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpCPIMsg_purge(Dz1InetFtpCPIMsg *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetFtpCPIMsgPresent_req:
		Dz1InetFtpCPIMsgReq_del(p->x.req);
		break;
	case Dz1InetFtpCPIMsgPresent_reply:
		Dz1InetFtpCPIMsgReply_del(p->x.reply);
		break;
	default:
		break;
	}
}

void Dz1InetFtpCPIMsg_del(Dz1InetFtpCPIMsg *p)
{
	if (!p) return;
	Dz1InetFtpCPIMsg_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpCPIMsg_dump(Dz1InetFtpCPIMsg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1InetFtpCPIMsgPresent_req:
		Dz1Thread_printf(Dz1T("req.")); Dz1InetFtpCPIMsgReq_dump(p->x.req, tab); 
		break;
	case Dz1InetFtpCPIMsgPresent_reply:
		Dz1Thread_printf(Dz1T("reply = ")); Dz1InetFtpCPIMsgReply_dump(p->x.reply, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1InetFtpCPIMsg
////////////////////////////////////////////////////////////////////////////////

