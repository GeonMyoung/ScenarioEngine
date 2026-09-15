#include <dz1_error.h>
#include <dz1_thread_stdio.h>
#include <dz1_inet_telnet_pi.h>
#include "dz1_inet_telnet_nvt.h"

Dz1InetTelnetNVTPrinter *Dz1InetTelnetNVTPrinter_new(u32_t width, u32_t height,
													void (*dataConsume)(void *ptr, u8_t *data, size_t size),
													void (*event)(void *ptr, Dz1InetTelnetNVTPrinterEvent event),
													Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTPrinter *ret = (Dz1InetTelnetNVTPrinter *)Dz1Calloc(sizeof(Dz1InetTelnetNVTPrinter), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->width = width;
		ret->height = height;
		ret->dataConsume = dataConsume;
		ret->event = event;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1InetTelnetNVTPrinter_del(Dz1InetTelnetNVTPrinter *p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1InetTelnetNVTPrinter_dump(Dz1InetTelnetNVTPrinter *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("{ width = %u, height = %u }\n", p->width, p->height);
}

Dz1InetTelnetNVTKeyboard *Dz1InetTelnetNVTKeyboard_new(Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTKeyboard *ret = (Dz1InetTelnetNVTKeyboard *)Dz1Calloc(sizeof(Dz1InetTelnetNVTKeyboard), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
	}
	return ret;
}

void Dz1InetTelnetNVTKeyboard_del(Dz1InetTelnetNVTKeyboard *p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1InetTelnetNVTKeyboard_dump(Dz1InetTelnetNVTKeyboard *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("Omitted\n");
}

Dz1InetTelnetNVTOptValue *Dz1InetTelnetNVTOptValue_new(bool_t value, bool_t waitReply, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTOptValue *ret = (Dz1InetTelnetNVTOptValue *)Dz1Calloc(sizeof(Dz1InetTelnetNVTOptValue), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->value = value;
		ret->waitReply = waitReply;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1InetTelnetNVTOptValue *Dz1InetTelnetNVTOptValue_clone(Dz1InetTelnetNVTOptValue *src, Dz1Error *err)
{
	return Dz1InetTelnetNVTOptValue_new(src->value, src->waitReply, err);
}

void Dz1InetTelnetNVTOptValue_del(Dz1InetTelnetNVTOptValue *p)
{
	if (!p) return;
	Dz1Free(p);
}

void Dz1InetTelnetNVTOptValue_dump(Dz1InetTelnetNVTOptValue *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("{ value = %s, waitReply = %s }\n", p->value ? "TRUE" : "FALSE", p->waitReply ? "TRUE" : "FALSE" );
}

Dz1InetTelnetNVTOptEntry *Dz1InetTelnetNVTOptEntry_new(Dz1InetTelnetNVTOptValue *peer, Dz1InetTelnetNVTOptValue *local, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTOptEntry *ret = (Dz1InetTelnetNVTOptEntry *)Dz1Calloc(sizeof(Dz1InetTelnetNVTOptEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetTelnetNVTOptEntry_delAndSetNull, (void *)&ret);

		if ((ret->local = Dz1InetTelnetNVTOptValue_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->peer = Dz1InetTelnetNVTOptValue_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1InetTelnetNVTOptEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1InetTelnetNVTOptEntry *Dz1InetTelnetNVTOptEntry_clone(Dz1InetTelnetNVTOptEntry *src, Dz1Error *err)
{
	return Dz1InetTelnetNVTOptEntry_new(src->local, src->peer, err);
}

void Dz1InetTelnetNVTOptEntry_del(Dz1InetTelnetNVTOptEntry *p)
{
	if (!p) return;
	if (p->peer) Dz1InetTelnetNVTOptValue_del(p->peer);
	if (p->local) Dz1InetTelnetNVTOptValue_del(p->local);
	Dz1Free(p);
}

void Dz1InetTelnetNVTOptEntry_dump(Dz1InetTelnetNVTOptEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("{\n");
	if (p->peer) { Dz1Thread_tprintf(tab, "peer = "); Dz1InetTelnetNVTOptValue_dump(p->peer, tab); }
	if (p->local) { Dz1Thread_tprintf(tab, "local = "); Dz1InetTelnetNVTOptValue_dump(p->local, tab); }
	Dz1Thread_tprintf(tab - 1, "}\n");
}

Dz1InetTelnetNVTOpt *Dz1InetTelnetNVTOpt_new(Dz1InetTelnetOptPresent present, Dz1InetTelnetNVTOptEntry *defVal, 
											 Dz1InetTelnetNVTOptSetInform setPeerOpt, Dz1InetTelnetNVTOptRepliedInform repliedPeerOpt,
											 Dz1InetTelnetNVTOptSetInform setLocalOpt, Dz1InetTelnetNVTOptRepliedInform repliedLocalOpt,
											 Dz1InetTelnetNVTOptSubNego subNego, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTOpt *ret = (Dz1InetTelnetNVTOpt *)Dz1Calloc(sizeof(Dz1InetTelnetNVTOpt), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetTelnetNVTOpt_delAndSetNull, (void *)&ret);
		if ((ret->status = Dz1InetTelnetNVTOptEntry_clone(defVal, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->present = present;
			ret->setPeerOpt = setPeerOpt;
			ret->repliedPeerOpt = repliedPeerOpt;
			ret->setLocalOpt = setLocalOpt;
			ret->repliedLocalOpt = repliedLocalOpt;
			ret->subNego = subNego;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1InetTelnetNVTOpt_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1InetTelnetNVTOpt *Dz1InetTelnetNVTOpt_clone(Dz1InetTelnetNVTOpt *src, Dz1Error *err)
{
	return Dz1InetTelnetNVTOpt_new(src->present, src->status,
								src->setPeerOpt, src->repliedPeerOpt,
								src->setLocalOpt, src->repliedLocalOpt,
								src->subNego, err);
}

void Dz1InetTelnetNVTOpt_del(Dz1InetTelnetNVTOpt *p)
{
	if (!p) return;
	if (p->status) Dz1InetTelnetNVTOptEntry_del(p->status);
	Dz1Free(p);
}

void Dz1InetTelnetNVTOpt_dump(Dz1InetTelnetNVTOpt *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("{\n");
	Dz1Thread_tprintf(tab, "present = %s\n", Dz1InetTelnetOptPresentStr(p->present));
	if (p->status) { Dz1Thread_tprintf(tab, "status = "); Dz1InetTelnetNVTOptEntry_dump(p->status, tab + 1); }
	Dz1Thread_tprintf(tab - 1, "}\n");
}

static Dz1InetTelnetNVTOpt *Dz1InetTelnetNVTOpt_find(Dz1InetTelnetNVTControl *ctrl, Dz1InetTelnetOptPresent present)
{
	u32_t i;
	for (i = 0; i < ctrl->numOfOpts; i++)
		if (ctrl->opts[i]->present == present) return ctrl->opts[i];
	return NULL;
}

Dz1InetTelnetNVTControl *Dz1InetTelnetNVTControl_new(Dz1InetTelnetNVTOpt *opts, u32_t numOfOpts, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVTControl *ret = (Dz1InetTelnetNVTControl *)Dz1Calloc(sizeof(Dz1InetTelnetNVTControl), 1,errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetTelnetNVTControl_delAndSetNull, (void *)&ret);
		if ((ret->opts = (Dz1InetTelnetNVTOpt **)Dz1Calloc(sizeof(Dz1InetTelnetNVTOpt *), numOfOpts, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			ret->numOfOpts = numOfOpts;
			for (i = 0; errp->code == 0 && i < ret->numOfOpts; i++)
				if ((ret->opts[i] = Dz1InetTelnetNVTOpt_clone(&opts[i], errp)) == NULL) ERR_OUT(errp);
		}
		pthread_cleanup_pop(errp->code); // (Dz1InetTelnetNVTControl_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetNVTControl_del(Dz1InetTelnetNVTControl *p)
{
	if (!p) return;
	if (p->opts)
	{
		u32_t  i;
		for (i = 0; i < p->numOfOpts; i++)
			Dz1InetTelnetNVTOpt_del(p->opts[i]);
		Dz1Free(p->opts);
	}
	Dz1Free(p);
}

void Dz1InetTelnetNVTControl_dump(Dz1InetTelnetNVTControl *p, int tab)
{
	u32_t i;
	if (!p) return;
	Dz1Thread_printf("{\n");
	for (i = 0; i < p->numOfOpts; i++)
	{
		Dz1Thread_tprintf(tab, "Opt[%d] = ");
		Dz1InetTelnetNVTOpt_dump(p->opts[i], tab);
	}
	Dz1Thread_tprintf(tab - 1, "{\n");
}

Dz1InetTelnetNVT *Dz1InetTelnetNVT_new(u32_t width, u32_t height,
									void (*dataConsume)(void *ptr, u8_t *data, size_t size),
									void (*event)(void *ptr, Dz1InetTelnetNVTPrinterEvent event),
									Dz1InetTelnetNVTOpt *opts, u32_t numOfOpts,
									void *userResource, Dz1DelFunc userResourceDel,
									Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetTelnetNVT *ret = (Dz1InetTelnetNVT *)Dz1Calloc(sizeof(Dz1InetTelnetNVT), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetTelnetNVT_delAndSetNull, (void *)&ret);

		if ((ret->printer = Dz1InetTelnetNVTPrinter_new(width, height, dataConsume, event, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->keyboard = Dz1InetTelnetNVTKeyboard_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->control = Dz1InetTelnetNVTControl_new(opts, numOfOpts, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->userResource = userResource;
			ret->userResourceDel = userResourceDel;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1InetTelnetNVT_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetTelnetNVT_del(Dz1InetTelnetNVT *p)
{
	if (!p) return;
	Dz1InetTelnetNVTPrinter_del(p->printer);
	Dz1InetTelnetNVTKeyboard_del(p->keyboard);
	Dz1InetTelnetNVTControl_del(p->control);
	if (p->userResourceDel) p->userResourceDel(p->userResource);
	Dz1Free(p);
}

void Dz1InetTelnetNVT_dump(Dz1InetTelnetNVT *p, int tab)
{
	if (!p) return;
	Dz1Thread_printf("{\n");
	if (p->printer) { Dz1Thread_tprintf(tab, "printer = "); Dz1InetTelnetNVTPrinter_dump(p->printer, tab); }
	if (p->keyboard) { Dz1Thread_tprintf(tab, "keyboard = "); Dz1InetTelnetNVTKeyboard_dump(p->keyboard, tab); }
	if (p->control) { Dz1Thread_tprintf(tab, "control = "); Dz1InetTelnetNVTControl_dump(p->control, tab); }
	Dz1Thread_tprintf(tab - 1, "}\n");
}

















Dz1InetTelnetNVTPrinterEvent getPrinterEvent(u8_t *v, size_t size)
{
	switch(*v)
	{
	case Dz1InetTelnetNVTPrinterEvent_bell:
	case Dz1InetTelnetNVTPrinterEvent_ec:
	case Dz1InetTelnetNVTPrinterEvent_htab:
	case Dz1InetTelnetNVTPrinterEvent_vtab:
	case Dz1InetTelnetNVTPrinterEvent_ff:
		return (Dz1InetTelnetNVTPrinterEvent)(*v);
	case Dz1InetTelnetNVTPrinterEvent_lf:
		if (size >= 2 && *(v+1) == Dz1InetTelnetNVTPrinterEvent_cr)
			return Dz1InetTelnetNVTPrinterEvent_crlf;
		else return (Dz1InetTelnetNVTPrinterEvent)(*v);
	case Dz1InetTelnetNVTPrinterEvent_cr:
		if (size >= 2 && *(v+1) == Dz1InetTelnetNVTPrinterEvent_lf)
			return Dz1InetTelnetNVTPrinterEvent_crlf;
		else return (Dz1InetTelnetNVTPrinterEvent)(*v);
	}
	return Dz1InetTelnetNVTPrinterEvent_max;
}

static void Dz1InetTelnetNVTPrinter_recv(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTPrinter *prt, Dz1Binary *bytes)
{
	Dz1InetTelnetNVTPrinterEvent event;
	u8_t *cp = bytes->data, *dp = NULL;
	size_t size = bytes->size, _size = 0;
	while(size)
	{
		if ((event = getPrinterEvent(cp, size)) != Dz1InetTelnetNVTPrinterEvent_max)
		{
			if (_size != 0)
			{
				prt->dataConsume(env->userResource, dp, _size);
				_size = 0; dp = NULL;
			}

			prt->event(env->userResource, event);
			cp++; size--;
			if (event == Dz1InetTelnetNVTPrinterEvent_crlf) { cp++; size--; }
		}
		else
		{
			if (dp == NULL) { dp = cp; _size = 0; }
			cp++; size--; _size++;
		}
	}
	if (dp != NULL) prt->dataConsume(env->userResource, dp, _size);
}

static bool_t Dz1InetTelnetNVTOptEntry_isAgreed(Dz1InetTelnetNVTOptEntry *p)
{
	if (p->local->waitReply == FALSE && p->peer->waitReply == FALSE)
	{
		if (p->local->value == p->peer->value) return TRUE;
	}
	return FALSE;
}

static Dz1Error Dz1InetTelnetNVTControl_recvReqOrCnf(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTControl *ctrl, Dz1TcpClientSocket *s,
													 Dz1InetTelnetCmdPresent present, Dz1InetTelnetOpt *msgOpt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetNVTOpt *opt = Dz1InetTelnetNVTOpt_find(ctrl, msgOpt->present);
	if (opt == NULL)
	{
		if (present == Dz1InetTelnetCmdPresent_doOpt || present == Dz1InetTelnetCmdPresent_willOpt)
		{	// unknown Option -> send won't or don't
			Dz1InetTelnetCmdPresent replyCmdPresent = (present == Dz1InetTelnetCmdPresent_doOpt) ?
												Dz1InetTelnetCmdPresent_wontOpt : Dz1InetTelnetCmdPresent_dontOpt;
			if ((err = Dz1InetTelnetPI_sendNego(s, replyCmdPresent, msgOpt->present)).code) ERR_OUT(&err);
		}
	}
	else
	{
		bool_t value;
		switch(present)
		{
		case Dz1InetTelnetCmdPresent_doOpt:
		case Dz1InetTelnetCmdPresent_dontOpt:
			value = present == Dz1InetTelnetCmdPresent_doOpt ? TRUE : FALSE;
			if (opt->status->local->waitReply == TRUE)
			{	// Receive Reply for WILL/WON't cause setting local opt
				opt->repliedLocalOpt(env, s, value, opt->status);
				opt->status->local->value = value;
				opt->status->local->waitReply = FALSE;
				Dz1Thread_printf("Dz1InetTelnetNVTControl_recvReqOrCnf() : local %s is confirmed\n", Dz1InetTelnetOptPresentStr(msgOpt->present));
			}
			// Receive Request local opt set to...
			else if (opt->status->local->value != value && opt->setLocalOpt(env, s, value) == TRUE)
			{
				//Dz1InetTelnetCmd *cmd = NULL;
				Dz1InetTelnetCmdPresent replyCmdPresent = value == TRUE ? Dz1InetTelnetCmdPresent_willOpt :
																		  Dz1InetTelnetCmdPresent_wontOpt;
				opt->status->local->value = value;
				if ((err = Dz1InetTelnetPI_sendNego(s, replyCmdPresent, msgOpt->present)).code) ERR_OUT(&err);
				else opt->repliedLocalOpt(env, s, value, opt->status);
			}
			break;
		case Dz1InetTelnetCmdPresent_willOpt:
		case Dz1InetTelnetCmdPresent_wontOpt:
			value = present == Dz1InetTelnetCmdPresent_willOpt ? TRUE : FALSE;
			if (opt->status->peer->waitReply == TRUE)
			{	// Receive Reply for DO/DON't cause setting peer opt
				opt->repliedPeerOpt(env, s, value, opt->status);
				opt->status->peer->value = value;
				opt->status->peer->waitReply = FALSE;
				Dz1Thread_printf("Dz1InetTelnetNVTControl_recvReqOrCnf() : peer %s is confirmed\n", Dz1InetTelnetOptPresentStr(msgOpt->present));
			}
			// Receive Request peer opt set to...
			else if (opt->setPeerOpt(env, s, value) == TRUE)
			{
				//Dz1InetTelnetCmd *cmd = NULL;
				Dz1InetTelnetCmdPresent replyCmdPresent = value == TRUE ? Dz1InetTelnetCmdPresent_doOpt :
																		  Dz1InetTelnetCmdPresent_dontOpt;
				opt->status->peer->value = value;
				if ((err = Dz1InetTelnetPI_sendNego(s, replyCmdPresent, msgOpt->present)).code) ERR_OUT(&err);
				else opt->repliedLocalOpt(env, s, value, opt->status);
			}
			break;
		default:
			break;
		}
		if (Dz1InetTelnetNVTOptEntry_isAgreed(opt->status))
		{
			Dz1Thread_printf("Dz1InetTelnetNVTControl_recvReqOrCnf() : Both Agreed %s Negotiation to %s\n",
							  Dz1InetTelnetOptPresentStr(msgOpt->present), opt->status->peer->value ? "TRUE" : "FALSE");
		}
	}
	return err;
}

static Dz1Error Dz1InetTelnetNVTControl_recvSubNego(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTControl *ctrl, Dz1TcpClientSocket *s, Dz1InetTelnetOpt *subNego)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1InetTelnetNVTOpt *opt = NULL;

	if ((opt = Dz1InetTelnetNVTOpt_find(ctrl, subNego->present)) == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (opt->subNego) opt->subNego(env, s, subNego);

	return err;
}

static Dz1Error Dz1InetTelnetNVTControl_recv(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTControl *ctrl, Dz1TcpClientSocket *s, Dz1InetTelnetCmd *cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetCmdPresent present;
	Dz1Thread_printf("Dz1InetTelnetNVTControl_recv() : Received ===============================================\n");
	Dz1Thread_printf("msg = "); Dz1InetTelnetCmd_dump(cmd, 0);
	switch(cmd->present)
	{
	case Dz1InetTelnetCmdPresent_noOper:
	case Dz1InetTelnetCmdPresent_dataMark:
		// No Operation
		break;
	case Dz1InetTelnetCmdPresent_brk:
		// Peer Pressed Break Key or Attention Key
		break;
	case Dz1InetTelnetCmdPresent_interruptProcess:
		// peer want terminate current process
		break;
	case Dz1InetTelnetCmdPresent_abortOutput:
		// peer want flush current NVT Keyboard buffer
		break;
	case Dz1InetTelnetCmdPresent_areYouThere:
		// peer want evidence that local is alive - User(Human) Invoke & Peer Response
		break;
	case Dz1InetTelnetCmdPresent_eraseChar:
		// peer want erase one letter on NVT Printer
		env->printer->event(env->userResource, Dz1InetTelnetNVTPrinterEvent_ec);
		break;
	case Dz1InetTelnetCmdPresent_eraseLine:
		// peer want erase one line on NVT Printer
		env->printer->event(env->userResource, Dz1InetTelnetNVTPrinterEvent_el);
		break;
	case Dz1InetTelnetCmdPresent_goAhead:
		// peer ready to receive data -> send data in NVT Keyboard Buffer and send GA
		break;
	case Dz1InetTelnetCmdPresent_doOpt:
	case Dz1InetTelnetCmdPresent_dontOpt:
	case Dz1InetTelnetCmdPresent_willOpt:
	case Dz1InetTelnetCmdPresent_wontOpt:
		present = cmd->present;
		if ((err = Dz1InetTelnetNVTControl_recvReqOrCnf(env, ctrl, s, present, (Dz1InetTelnetOpt *)cmd->x.__ptr__)).code) ERR_OUT(&err);
		break;
	case Dz1InetTelnetCmdPresent_subNego:
		if ((err = Dz1InetTelnetNVTControl_recvSubNego(env, ctrl, s, cmd->x.subNego)).code) ERR_OUT(&err);
		break;
	default:
		break;
	}
	return err;
}

static Dz1Error Dz1InetTelnetNVTControl_optSetLocal(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTControl *ctrl, Dz1TcpClientSocket *s,
											   Dz1InetTelnetOptPresent _opt, bool_t value)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetNVTOpt *opt = Dz1InetTelnetNVTOpt_find(ctrl, _opt);
	if (opt->status->local->value != value)
	{
		Dz1InetTelnetCmdPresent cmd = value == TRUE ? Dz1InetTelnetCmdPresent_willOpt: Dz1InetTelnetCmdPresent_wontOpt;
		opt->status->local->value = value;
		if ((err = Dz1InetTelnetPI_sendNego(s, cmd, _opt)).code) ERR_OUT(&err);
		else opt->status->local->waitReply = TRUE;
	}
	return err;
}

static Dz1Error Dz1InetTelnetNVTControl_optSetPeer(Dz1InetTelnetNVT *env, Dz1InetTelnetNVTControl *ctrl, Dz1TcpClientSocket *s,
											   Dz1InetTelnetOptPresent _opt, bool_t value)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetTelnetNVTOpt *opt = Dz1InetTelnetNVTOpt_find(ctrl, _opt);
	if (opt->status->peer->value != value)
	{
		Dz1InetTelnetCmdPresent cmd = value == TRUE ? Dz1InetTelnetCmdPresent_doOpt: Dz1InetTelnetCmdPresent_dontOpt;
		opt->status->peer->value = value;
		if ((err = Dz1InetTelnetPI_sendNego(s, cmd, _opt)).code) ERR_OUT(&err);
		else opt->status->peer->waitReply = TRUE;
	}
	return err;
}

Dz1Error Dz1InetTelnetNVT_recv(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (msg->present == Dz1InetTelnetMsgPresent_bytes)
	{	// forward to printer;
		// check echo flag is true then write to NVT Keyboard
		Dz1InetTelnetNVTPrinter_recv(env, env->printer, msg->x.bytes);
	}
	else
	{
		Dz1InetTelnetCmd *cmd = msg->x.cmd;
		if ((err = Dz1InetTelnetNVTControl_recv(env, env->control, s, cmd)).code) ERR_OUT(&err);
	}
	return err;
}

Dz1Error Dz1InetTelnetNVT_optSetLocal(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOptPresent opt, bool_t value)
{
	return Dz1InetTelnetNVTControl_optSetLocal(env, env->control, s, opt, value);
}

Dz1Error Dz1InetTelnetNVT_optSetPeer(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOptPresent opt, bool_t value)
{
	return Dz1InetTelnetNVTControl_optSetPeer(env, env->control, s, opt, value);
}
	
