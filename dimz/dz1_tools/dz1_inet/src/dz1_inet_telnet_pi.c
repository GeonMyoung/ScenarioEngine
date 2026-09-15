#include <dz1_error.h>
#include <dz1_str.h>
#include <dz1_thread_stdio.h>
#include <dz1_socket.h>
#include <dz1_socket_receiver.h>

#include <dz1_inet_telnet_pi.h>

#include "dz1_inet_telnet_msg.h"

#define DZ1_NVT_KEYBOARD_BREAK					243
#define DZ1_NVT_KEYBOARD_INTPROC				244
#define DZ1_NVT_KEYBOARD_ABORT_OUTPUT			245
#define DZ1_NVT_KEYBOARD_AYT					246
#define DZ1_NVT_KEYBOARD_ERASE_CHAR				247
#define DZ1_NVT_KEYBOARD_ERASE_LINE				248

#define DZ1_NVT_PRINTER_NULL					  0
#define DZ1_NVT_PRINTER_BELL					  7
#define DZ1_NVT_PRINTER_BS						  8
#define DZ1_NVT_PRINTER_HTAB					  9
#define DZ1_NVT_PRINTER_LF						 10
#define DZ1_NVT_PRINTER_VTAB					 11
#define DZ1_NVT_PRINTER_FORMFEED				 12
#define DZ1_NVT_PRINTER_CR						 13


static Dz1Error _encodeAndSend(Dz1TcpClientSocket *s, Dz1InetTelnetMsg *msg, bool_t isUrgent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t *data = NULL;
	ssize_t size = 0;
	u32_t flag = DZ1_TCP_SOCK_FLAG_COMPLETE | (isUrgent ? DZ1_TCP_SOCK_FLAG_URGENT : 0);

	Dz1Thread_printf("_encodeAndSend() : msg = "); Dz1InetTelnetMsg_dump(msg, 0);
	if ((size = Dz1InetTelnetPI_encode(&data, msg, &err)) < 0) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)data);

		if (s->send(s, data, size, flag, NULL, &err) < 0) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)data);
	}
	return err;
}

static Dz1Error _genCmdAndSend(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent cmd, bool_t isUrgent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetMsg *msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		if ((msg->x.cmd = Dz1InetTelnetCmd_new(cmd, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(s, msg, isUrgent)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
	}
	return err;
}

static Dz1Error _genNegoAndSend(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent nego, Dz1InetTelnetOptPresent opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetMsg *msg = NULL;
	if ((msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetTelnetCmd *cmd = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
		if ((cmd = msg->x.cmd = Dz1InetTelnetCmd_new(nego, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((cmd->x.__ptr__ = Dz1InetTelnetOpt_new(opt, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(s, msg, FALSE)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
	}
	return err;
}

static ssize_t _putTelnet1Byte(u8_t *dst, size_t size, u8_t src, Dz1Error *errp)
{
	bool_t useEsc = src == 0xFF ? TRUE : FALSE;
	if ((useEsc == TRUE && size < 2) || (useEsc == FALSE && size < 1)) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else if (useEsc)
	{
		if (dst != NULL) { *dst++ = 0xFF; *dst++ = 0xFF; }
		return 2;
	}
	else
	{
		if (dst != NULL) *dst++ = src;
		return 1;
	}
}
#if 0
static ssize_t _get1Byte(u8_t *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	bool_t useEsc = *src == 0xFF ? TRUE : FALSE;
	if ((useEsc == TRUE && size < 2) || (useEsc == FALSE && size < 1)) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else if (useEsc)
	{
		src++;
		*dst = *src++;
		return 2;
	}
	else
	{
		*dst = *src++;
		return 1;
	}
}
#endif
static ssize_t _putTelent2Byte(u8_t *dst, size_t size, u16_t v, Dz1Error *errp)
{
	if (size < 2) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		u8_t *cp = dst;
		ssize_t ret = 0, status;
		u8_t _v[2];
		_v[0] = (u8_t)((v & 0xFF00) >> 8);
		_v[1] = (u8_t)(v & 0xFF);
		if ((status = _putTelnet1Byte(dst, size, _v[0], errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			if (cp != NULL) cp += status;
			ret += status;
			size -= status;
		}
		if ((status = _putTelnet1Byte(dst, size, _v[1], errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			if (cp != NULL) cp += status;
			ret += status;
			size -= status;
		}
		return ret;
	}
}
#if 0
static ssize_t _get2Byte(u16_t *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	if (size < 2) { ERR_SET_OUT(errp, E2BIG); return -1; }
	else
	{
		u8_t *cp = src;
		ssize_t ret = 0, status;
		u8_t _v[2];
		if ((status = _get1Byte(&_v[0], cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			if (cp != NULL) cp += status;
			ret += status;
			size -= status;
		}
		if ((status = _get1Byte(&_v[1], cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			if (cp != NULL) cp += status;
			ret += status;
			size -= status;
		}

		*dst = (((u16_t)_v[0]) << 8) | ((u16_t)_v[1]);

		return ret;
	}
}
#endif
static ssize_t _putBytes(u8_t *dst, size_t size, u8_t *src, size_t putSize, Dz1Error *errp)
{
	ssize_t ret = 0, status;
	u8_t *srcp = src, *dstp = dst;
	while(putSize)
	{
		if ((status = _putTelnet1Byte(dstp, size, *srcp, errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			srcp++;
			putSize--;
			if (dstp != NULL) dstp += status;
			size -= status;
			ret += status;
		}
	}
	return ret;
}
#if 0
static ssize_t _getBytes(u8_t *dst, size_t getSize, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0, status;
	u8_t *dstp = dst, *srcp = src;
	while(getSize)
	{
		if ((status = _get1Byte(dstp, srcp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
		else
		{
			dstp++;
			getSize--;
			srcp += status;
			size -= status;
			ret += status;
		}
	}
	return ret;
}
#endif
typedef struct Dz1InetTelnetOptAPI
{
	Dz1InetTelnetOptCode			code;
	Dz1InetTelnetOptPresent			present;
	str_t							name;
	ssize_t							(*encode)(u8_t *dst, size_t size, Dz1InetTelnetOpt *src, Dz1Error *errp);
	ssize_t							(*decode)(Dz1InetTelnetOpt *dst, u8_t *src, size_t size, Dz1Error *errp);
} Dz1InetTelnetOptAPI;

static ssize_t ttype_enc(u8_t *dst, size_t size, Dz1InetTelnetOpt *src, Dz1Error *errp)
{
	Dz1InetTelnetOptTerminalType *ttype = src->x.terminalType;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if (dst == NULL)
	{
		if (ttype->present == Dz1InetTelnetOptTerminalTypePresent_send) return 1; /* cmd */ 
		else return (ssize_t)(1 /* cmd */ + strlen(ttype->x.is));
	}
	else
	{
		ssize_t status;
		u8_t *cp = dst;
		if (ttype->present == Dz1InetTelnetOptTerminalTypePresent_send) { *cp++ = 1; size--; }// Just Command Only
		else
		{	// IS encode
			size_t len = strlen(ttype->x.is);
			*cp++ = 0; // IS
			if ((status = _putBytes(cp, size, (u8_t *)ttype->x.is, len, errp)) < 0) { ERR_OUT(errp); return -1; }
			else { cp += status; size -= status; }
		}
		return (ssize_t)(cp - dst);
	}
}

static ssize_t ttype_dec(Dz1InetTelnetOpt *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	u8_t *cp = src;
	Dz1InetTelnetOptTerminalType *ttype = NULL;
	u8_t status = *cp++;
	size--;
	if (status == 0)
	{	// IS
		if ((ttype = dst->x.terminalType = Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_is, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((ttype->x.is = Dz1Str_ndup((char *)cp, size, errp)) == NULL) ERR_OUT(errp);
		else { cp += size; size -= size; Dz1Error_set(errp, 0); }
	}
	// SEND
	else if ((dst->x.terminalType = Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_send, NULL, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return (ssize_t)(cp - src);
}

static ssize_t winSize_enc(u8_t *dst, size_t size, Dz1InetTelnetOpt *src, Dz1Error *errp)
{
	Dz1InetTelnetOptWindowSize *ws = src->x.windowSize;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if (dst == NULL) return (ssize_t)(2 /* <Width> */ + 2); /* <Height> */
	else
	{
		ssize_t status;
		u8_t *cp = dst;
		if ((status = _putTelent2Byte(cp, size, ws->width, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }
		if ((status = _putTelent2Byte(cp, size, ws->height, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; size -= status; }
		return (ssize_t)(cp - dst);
	}
}

static ssize_t winSize_dec(Dz1InetTelnetOpt *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	u8_t *cp = src;
	Dz1InetTelnetOptTerminalType *ttype = NULL;
	u8_t status = *cp++;
	size--;
	if (status == 0)
	{	// IS
		if ((ttype = dst->x.terminalType = Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_is, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((ttype->x.is = Dz1Str_ndup((char *)cp, size, errp)) == NULL) ERR_OUT(errp);
		else { cp += size; size -= size; Dz1Error_set(errp, 0); }
	}
	// SEND
	else if ((dst->x.terminalType = Dz1InetTelnetOptTerminalType_new(Dz1InetTelnetOptTerminalTypePresent_send, NULL, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return (ssize_t)(cp - src);
}

static Dz1InetTelnetOptAPI telnet_opts[] =
{
	{ Dz1InetTelnetOptCode_binary,				Dz1InetTelnetOptPresent_binary,					"Binary Mode",								NULL },
	{ Dz1InetTelnetOptCode_echo,				Dz1InetTelnetOptPresent_echo,					"Echo",										NULL },
	{ Dz1InetTelnetOptCode_prepareReconnect,	Dz1InetTelnetOptPresent_prepareReconnect,		"Reconnect Prepare",						NULL },
	{ Dz1InetTelnetOptCode_suppressGoAhead,		Dz1InetTelnetOptPresent_suppressGoAhead,		"Suppress Go Ahead",						NULL },
	{ Dz1InetTelnetOptCode_approximateMsgSize,	Dz1InetTelnetOptPresent_approximateMsgSize,		"Approximate Message Size",					NULL },
	{ Dz1InetTelnetOptCode_status,				Dz1InetTelnetOptPresent_status,					"Give Status",								NULL },
	{ Dz1InetTelnetOptCode_timingMark,			Dz1InetTelnetOptPresent_timingMark,				"Timing Mark",								NULL },
	{ Dz1InetTelnetOptCode_rcTxAndEcho,			Dz1InetTelnetOptPresent_rcTxAndEcho,			"Remote Controlled Transmission & Echo",	NULL },
	{ Dz1InetTelnetOptCode_lineWidth,			Dz1InetTelnetOptPresent_lineWidth,				"Negotiation : Output Line Width",			NULL },
	{ Dz1InetTelnetOptCode_pageSize,			Dz1InetTelnetOptPresent_pageSize,				"Negotiation : Output Page Size",			NULL },
	{ Dz1InetTelnetOptCode_crDisposition,		Dz1InetTelnetOptPresent_crDisposition,			"Negotiation : CR Disposition",				NULL },
	{ Dz1InetTelnetOptCode_hTabStop,			Dz1InetTelnetOptPresent_hTabStop,				"Negotiation : Horizontal TAB Stop",		NULL },
	{ Dz1InetTelnetOptCode_hTabDisposition,		Dz1InetTelnetOptPresent_hTabDisposition,		"Negotiation : Horizontal TAB Disposition",	NULL },
	{ Dz1InetTelnetOptCode_formFeedDisposition,	Dz1InetTelnetOptPresent_formFeedDisposition,	"Negotiation : Form Feed Disposition",		NULL },
	{ Dz1InetTelnetOptCode_vTabStop,			Dz1InetTelnetOptPresent_vTabStop,				"Negotiation : Vertical TAB Stop",			NULL },
	{ Dz1InetTelnetOptCode_vTabDisposition,		Dz1InetTelnetOptPresent_vTabDisposition,		"Negotiation : Vertical TAB Disposition",	NULL },
	{ Dz1InetTelnetOptCode_lfDisposition,		Dz1InetTelnetOptPresent_lfDisposition,			"Negotiation : Output LF Disposition",		NULL },
	{ Dz1InetTelnetOptCode_xAscii,				Dz1InetTelnetOptPresent_xAscii,					"Extended ASCII Character Set",				NULL },
	{ Dz1InetTelnetOptCode_forceLogout,			Dz1InetTelnetOptPresent_forceLogout,			"Force Logout",								NULL },
	{ Dz1InetTelnetOptCode_byteMacro,			Dz1InetTelnetOptPresent_byteMacro,				"Byte Macro",								NULL },
	{ Dz1InetTelnetOptCode_dataEntryTerminal,	Dz1InetTelnetOptPresent_dataEntryTerminal,		"Data Entry Terminal",						NULL },
	{ Dz1InetTelnetOptCode_supdupProtocol,		Dz1InetTelnetOptPresent_supdupProtocol,			"SUPDUP Protocol",							NULL },
	{ Dz1InetTelnetOptCode_supdupOutput,		Dz1InetTelnetOptPresent_supdupOutput,			"SUPDUP Output",							NULL },
	{ Dz1InetTelnetOptCode_sendLocation,		Dz1InetTelnetOptPresent_sendLocation,			"Send Location",							NULL },
	{ Dz1InetTelnetOptCode_terminalType,		Dz1InetTelnetOptPresent_terminalType,			"Terminal Type",							ttype_enc, ttype_dec },
	{ Dz1InetTelnetOptCode_endOfRecord,			Dz1InetTelnetOptPresent_endOfRecord,			"End Of Record",							NULL },
	{ Dz1InetTelnetOptCode_tacacsUserID,		Dz1InetTelnetOptPresent_tacacsUserID,			"TACACS User Identification",				NULL },
	{ Dz1InetTelnetOptCode_OutputMarking,		Dz1InetTelnetOptPresent_OutputMarking,			"Output Marking",							NULL },
	{ Dz1InetTelnetOptCode_ttyNumber,			Dz1InetTelnetOptPresent_ttyNumber,				"Terminal Location Number",					NULL },
	{ Dz1InetTelnetOptCode_regime3270,			Dz1InetTelnetOptPresent_regime3270,				"3270 Regime",								NULL },
	{ Dz1InetTelnetOptCode_xDot3Pad,			Dz1InetTelnetOptPresent_xDot3Pad,				"X.3 PAD",									NULL },
	{ Dz1InetTelnetOptCode_windowSize,			Dz1InetTelnetOptPresent_windowSize,				"Window Size",								winSize_enc, winSize_dec },
	{ Dz1InetTelnetOptCode_terminalSpeed,		Dz1InetTelnetOptPresent_terminalSpeed,			"Terminal Speed",							NULL },
	{ Dz1InetTelnetOptCode_remoteFlowControl,	Dz1InetTelnetOptPresent_remoteFlowControl,		"Remote Flow Control",						NULL },
	{ Dz1InetTelnetOptCode_lineMode,			Dz1InetTelnetOptPresent_lineMode,				"Line Mode",								NULL },
	{ Dz1InetTelnetOptCode_xDispLoc,			Dz1InetTelnetOptPresent_xDispLoc,				"X Display Location",						NULL },
	{ Dz1InetTelnetOptCode_oldEnvs,				Dz1InetTelnetOptPresent_oldEnvs,				"Old Environment Variables",				NULL },
	{ Dz1InetTelnetOptCode_auth,				Dz1InetTelnetOptPresent_auth,					"Authenticate",								NULL },
	{ Dz1InetTelnetOptCode_encryption,			Dz1InetTelnetOptPresent_encryption,				"Encryption Option",						NULL },
	{ Dz1InetTelnetOptCode_newEnvs,				Dz1InetTelnetOptPresent_newEnvs,				"New Environment Variables",				NULL },
	{ Dz1InetTelnetOptCode_extOptList,			Dz1InetTelnetOptPresent_extOptList,				"Extended Options List",					NULL },
	{ Dz1InetTelnetOptCode_max,					Dz1InetTelnetOptPresent_max,					NULL,										NULL }
};

static Dz1InetTelnetOptAPI *Dz1InetTelnetOptAPI_findByCode(u8_t code)
{
	Dz1InetTelnetOptAPI *i;
	for (i = telnet_opts; i->name != NULL; i++)
		if (i->code == code) return i;
	return NULL;
}

static Dz1InetTelnetOptAPI *Dz1InetTelnetOptAPI_findByPresent(Dz1InetTelnetOptPresent present)
{
	Dz1InetTelnetOptAPI *i;
	for (i = telnet_opts; i->name != NULL; i++)
		if (i->present == present) return i;
	return NULL;
}

static ssize_t sub_enc(u8_t *dst, size_t size, Dz1InetTelnetCmd *src, Dz1Error *errp)
{
	u8_t *cp = dst;
	Dz1InetTelnetOpt *subNego = src->x.subNego;
	Dz1InetTelnetOptAPI *api = Dz1InetTelnetOptAPI_findByPresent(subNego->present);
	if (api == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		ssize_t status;
		if (dst == NULL)
		{
			if ((status = api->encode(NULL, size, subNego, errp)) < 0) { ERR_OUT(errp); return -1; }
			else return 1 /*type*/ + status /* context */ + 2 /* IAC SE */;
		}
		else
		{
			*cp++ = (u8_t)api->code;	// type
			if ((status = api->encode(cp, size, subNego, errp)) < 0) { ERR_OUT(errp); return -1; } else { cp += status; } // context

			*cp++ = (u8_t)Dz1InetTelnetEsc_IAC; // IAC
			*cp++ = (u8_t)Dz1InetTelnetCmdCode_endOfSubNego; // SE
		}
		return (ssize_t)(cp - dst);
	}
}

static ssize_t getContextSize(u8_t *src, size_t size)
{
	u8_t *cp = src;
	bool_t found = FALSE;
	while(size)
	{
		if (*cp == Dz1InetTelnetEsc_IAC && size >= 2 && *(cp + 1) == Dz1InetTelnetCmdCode_endOfSubNego)
		{
			found = TRUE;
			break;
		}
		else
		{
			cp++;
			size--;
		}
	}
	if (found) return (ssize_t)(cp - src); else return -1;
}

static ssize_t sub_dec(Dz1InetTelnetCmd *dst, u8_t *data, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0, status;
	u8_t *cp = data, *context = NULL;
	size_t contextSize;
	//bool_t found = FALSE;
	Dz1InetTelnetOpt *p = NULL;

	Dz1InetTelnetOptAPI *api = Dz1InetTelnetOptAPI_findByCode(*cp);
	if (api == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; } else { cp++; size--; ret++; };

	context = cp;
	if ((contextSize = getContextSize(cp, size)) < 0) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else if ((p = dst->x.subNego = Dz1InetTelnetOpt_new(api->present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else if ((status = api->decode(p, context, contextSize, errp)) < 0) { ERR_OUT(errp); return -1; }
	else
	{	// Passing <IAC> <SE>
		ret += (status + 2);
		size -= (status + 2);
	}

	return ret;
}

static ssize_t opt_enc(u8_t *dst, size_t size, Dz1InetTelnetCmd *src, Dz1Error *errp)
{
	ssize_t ret = 0;
	Dz1InetTelnetOpt *opt = (Dz1InetTelnetOpt *)src->x.__ptr__;
	Dz1InetTelnetOptAPI *api = Dz1InetTelnetOptAPI_findByPresent(opt->present);
	if (api == NULL) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		if (dst != NULL) *dst++ = api->code;
		size--;
		ret++;
	}

	return ret;
}

static ssize_t opt_dec(Dz1InetTelnetCmd *dst, u8_t *data, size_t size, Dz1Error *errp)
{
	u8_t *cp = data;
	Dz1InetTelnetOptAPI *api = Dz1InetTelnetOptAPI_findByCode(*cp++); size--;

	if (api == NULL)
	{
		ERR_SET_OUT(errp, EINVAL);
		return -1;
	}
	else if ((dst->x.__ptr__ = Dz1InetTelnetOpt_new(api->present, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else Dz1Error_set(errp, 0);

	return (ssize_t)(cp - data);
}

typedef struct Dz1InetTelnetCmdAPI
{
	u8_t					 code;
	Dz1InetTelnetCmdPresent  present;
	str_t					 name;
	ssize_t					 (*encode)(u8_t *dst, size_t size, Dz1InetTelnetCmd *src, Dz1Error *errp);
	ssize_t					 (*decode)(Dz1InetTelnetCmd *dst, u8_t *src, size_t size, Dz1Error *errp);
} Dz1InetTelnetCmdAPI;
static Dz1InetTelnetCmdAPI telnet_cmd_table[] =
{
	{ Dz1InetTelnetCmdCode_noOper,				Dz1InetTelnetCmdPresent_noOper,				"NOP",	NULL, NULL }, 	//	No Operation
	{ Dz1InetTelnetCmdCode_dataMark,			Dz1InetTelnetCmdPresent_dataMark,			"DM",	NULL, NULL }, 	//	The Data Stream Portion of a Sync
	{ Dz1InetTelnetCmdCode_brk,					Dz1InetTelnetCmdPresent_brk,				"BRK",	NULL, NULL }, 	//	NVT character BRK
	{ Dz1InetTelnetCmdCode_interruptProcess,	Dz1InetTelnetCmdPresent_interruptProcess,	"IP",	NULL, NULL }, 	//	The Function IP
	{ Dz1InetTelnetCmdCode_abortOutput,			Dz1InetTelnetCmdPresent_abortOutput,		"AO",	NULL, NULL }, 	//	The Function AO
	{ Dz1InetTelnetCmdCode_areYouThere,			Dz1InetTelnetCmdPresent_areYouThere,		"AYT",	NULL, NULL }, 	//	Th Function AYT
	{ Dz1InetTelnetCmdCode_eraseChar,			Dz1InetTelnetCmdPresent_eraseChar,			"EC",	NULL, NULL }, 	//	The Function EC
	{ Dz1InetTelnetCmdCode_eraseLine,			Dz1InetTelnetCmdPresent_eraseLine,			"EL",	NULL, NULL }, 	//	The Function EL
	{ Dz1InetTelnetCmdCode_goAhead,				Dz1InetTelnetCmdPresent_goAhead,			"GA",	NULL, NULL }, 	//	The GA Signal

	//	Indicates that what follows is sub-negotiation of the indicated option
	{ Dz1InetTelnetCmdCode_subNego,				Dz1InetTelnetCmdPresent_subNego,			"SB",	sub_enc, sub_dec},

	// End of sub negotiation
	{ Dz1InetTelnetCmdCode_endOfSubNego,		Dz1InetTelnetCmdPresent_endOfSubNego,		"SE",	NULL, NULL },

	// Indicates the desire to begin performing,
	// or confirmation that you are now performing, this indicated option
	{ Dz1InetTelnetCmdCode_willOpt,				Dz1InetTelnetCmdPresent_willOpt,			"WILL",	opt_enc, opt_dec },

	// Indicates the refusal to perform,
	// or continue performing, this indicated option
	{ Dz1InetTelnetCmdCode_wontOpt,				Dz1InetTelnetCmdPresent_wontOpt,			"WONT",	opt_enc, opt_dec },

	// Indicates the request that the other party perform,
	// or confirmation that you are excepting the other party to perform, this indicated option
	{ Dz1InetTelnetCmdCode_doOpt,				Dz1InetTelnetCmdPresent_doOpt,				"DO",	opt_enc, opt_dec },

	// Indicates the demand that the other party stop performing,
	// or confirmation that excepting the other party to perform, this indicated option
	// you are no longer excepting the other party to perform, this indicated option
	{ Dz1InetTelnetCmdCode_dontOpt,				Dz1InetTelnetCmdPresent_dontOpt,			"DONT",	opt_enc, opt_dec },

	{ Dz1InetTelnetCmdCode_max,					Dz1InetTelnetCmdPresent_max,				NULL,	NULL, NULL }
};

static Dz1InetTelnetCmdAPI *Dz1InetTelnetCmdAPI_findByCode(u8_t code)
{
	Dz1InetTelnetCmdAPI *i;
	for (i = telnet_cmd_table; i->name != NULL; i++)
		if (i->code == code) return i;
	return NULL;
}

static Dz1InetTelnetCmdAPI *Dz1InetTelnetCmdAPI_findByPresent(Dz1InetTelnetCmdPresent present)
{
	Dz1InetTelnetCmdAPI *i;
	for (i = telnet_cmd_table; i->name != NULL; i++)
		if (i->present == present) return i;
	return NULL;
}

static ssize_t _copyBytes(u8_t *dst, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	u8_t *dstp = dst;
	while(size)
	{
		if (*src != Dz1InetTelnetEsc_IAC)
		{
			if (dstp != NULL) *dstp++ = *src++;
			size--; ret++;
		}
		else if (size < 2) { ERR_SET_OUT(errp, EINVAL); return -1; }
		else
		{
			u8_t next = *(src + 1);
			if (Dz1InetTelnetCmdAPI_findByCode(next) != NULL)
			{	// it's command -> stop here
				break;
			}
			// continue parse to next
			else
			{
				src++; size--;	// pass IAC
				if (dstp != NULL) *dstp++ = *src++;
				size--; ret++;	// pass letter
			}
		}
	}
	return ret;
}

ssize_t Dz1InetTelnetPI_decode(Dz1InetTelnetMsg **_ret, u8_t *data, size_t size, Dz1Error *err)
{
	ssize_t ret = 0, status;
	Dz1Error _err, *errp = err ? err : &_err;
	u8_t *cp = data;
	Dz1InetTelnetMsg *msg = NULL;
	if (*cp == Dz1InetTelnetEsc_IAC)
	{
		Dz1InetTelnetCmdAPI *api = NULL;
		cp++; size--;	// pass IAC
		if ((api = Dz1InetTelnetCmdAPI_findByCode(*cp)) == NULL)
		{	// Second Byte is not command
			if ((status = Dz1InetTelnetPI_decode(_ret, cp, size, errp)) < 0) { ERR_OUT(errp); return -1; }
			else { ret += status; size -= status; }
		}
		// Second Byte is Command
		else if ((msg = (*_ret) = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_cmd, NULL, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		else
		{
			cp++; size--;
			pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)_ret);
			if ((msg->x.cmd = Dz1InetTelnetCmd_new(api->present, NULL, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
			else if (api->decode)
			{
				if ((status = api->decode(msg->x.cmd, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else { cp += status; size -= status; ret = (ssize_t)(cp - data); }
			}
			else ret = (ssize_t)(cp - data);
			pthread_cleanup_pop(errp->code); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)_ret);
		}
	}
	else if ((msg = (*_ret) = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_bytes, NULL, errp)) == NULL) { ERR_OUT(errp); return -1; }
	else
	{
		//u8_t *src = cp;
		ssize_t byteSize = 0;
		Dz1Binary *bytes = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)_ret);

		if ((byteSize = _copyBytes(NULL, cp, (u32_t)size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		else if ((bytes = msg->x.bytes = Dz1Binary_new(NULL, 0, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		else if ((bytes->data = (u8_t *)Dz1Malloc(byteSize, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		else if ((status = _copyBytes(bytes->data, cp, size, errp)) < 0) { ERR_OUT(errp); ret = -1; }
		{
			cp += status; size -= status;
			bytes->size = (u32_t)status;
			ret = (ssize_t)(cp - data);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)_ret);
	}
	return ret;
}

ssize_t Dz1InetTelnetPI_encode(u8_t **_ret, Dz1InetTelnetMsg *src, Dz1Error *err)
{
	ssize_t ret = 0, status;
	Dz1Error _err, *errp = err ? err : &_err;
	if (src->present == Dz1InetTelnetMsgPresent_bytes)
	{
		if (((*_ret) = (u8_t *)Dz1Memory_clone(src->x.bytes->data, src->x.bytes->size, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		else Dz1Error_set(errp, 0);
	}
	else if (src->present == Dz1InetTelnetMsgPresent_cmd)
	{
		Dz1InetTelnetCmdAPI *api = NULL;
		Dz1InetTelnetCmd *cmd = src->x.cmd;
		if ((api = Dz1InetTelnetCmdAPI_findByPresent(cmd->present)) == NULL) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
		else if (api->encode)
		{
			u8_t *data = NULL;
			// Get Size
			if ((status = api->encode(NULL, -1, cmd, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			// Allocation
			else if ((data = (*_ret) = (u8_t *)Dz1Malloc(2 + status, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
			else
			{
				u8_t *cp = data;
				pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)_ret);
				*cp++ = (u8_t)Dz1InetTelnetEsc_IAC;
				*cp++ = api->code;
				if (api->encode(cp, 2 + status, cmd, errp) < 0) { ERR_OUT(errp); ret = -1; }
				else ret = 1/*IAC*/ + 1/*!<Do|Don't|Will|Won't>*/ + status;/*Options*/
				pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)_ret);
			}
		}
		// Just 2 byte Command Packet
		else if (((*_ret) = (u8_t *)Dz1Malloc(2, errp)) == NULL) { ERR_OUT(errp); ret = -1; }
		else
		{
			u8_t *cp = (*_ret);
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)_ret);
			*cp++ = (u8_t)Dz1InetTelnetEsc_IAC;
			*cp++ = api->code;
			ret = 1 /*IAC*/ + 1;/*!<Do|Don't|Will|Won't>*/
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)_ret);
		}
	}
	else { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	return ret;
}

Dz1Error Dz1InetTelnetPI_sendCMD(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(cmd)
	{
	case Dz1InetTelnetCmdPresent_dataMark:
		if ((err = _genCmdAndSend(s, cmd, TRUE)).code) ERR_OUT(&err);
		break;
	case Dz1InetTelnetCmdPresent_noOper:
	case Dz1InetTelnetCmdPresent_brk:
	case Dz1InetTelnetCmdPresent_interruptProcess:
	case Dz1InetTelnetCmdPresent_abortOutput:
	case Dz1InetTelnetCmdPresent_areYouThere:
	case Dz1InetTelnetCmdPresent_eraseChar:
	case Dz1InetTelnetCmdPresent_eraseLine:
	case Dz1InetTelnetCmdPresent_goAhead:
		if ((err = _genCmdAndSend(s, cmd, FALSE)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

Dz1Error Dz1InetTelnetPI_sendNego(Dz1TcpClientSocket *s, Dz1InetTelnetCmdPresent nego, Dz1InetTelnetOptPresent opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(nego)
	{
	case Dz1InetTelnetCmdPresent_doOpt:
	case Dz1InetTelnetCmdPresent_dontOpt:
	case Dz1InetTelnetCmdPresent_willOpt:
	case Dz1InetTelnetCmdPresent_wontOpt:
		if ((err = _genNegoAndSend(s, nego, opt)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

Dz1Error Dz1InetTelnetPI_sendBytes(Dz1TcpClientSocket *s, u8_t *data, u32_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetMsg *msg = Dz1InetTelnetMsg_new(Dz1InetTelnetMsgPresent_bytes, NULL, &err);
	if (msg == NULL) ERR_OUT(&err);
	else
	{
		Dz1Binary *bytes = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);

		if ((bytes = msg->x.bytes = Dz1Binary_new(data, size, &err)) == NULL) ERR_OUT(&err);
		else if ((err = _encodeAndSend(s, msg, FALSE)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetTelnetMsg_del, (void *)msg);
	}
	return err;
}
