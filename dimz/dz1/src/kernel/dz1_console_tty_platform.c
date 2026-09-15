#include "dz1_console_tty_platform.h"

Dz1ConsolePlatform *Dz1ConsolePlatform_new(void *priv, void (*priv_del)(void *priv), 
										   Dz1ThreadIOWaitF wait, 
										   Dz1ThreadIOGetChF getch, 
										   Dz1ThreadIOWriteF write, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ConsolePlatform *ret = (Dz1ConsolePlatform *)calloc(sizeof(Dz1ConsolePlatform), 1);
	if (ret == NULL) { Dz1Error_set(errp, ENOMEM); }
	else
	{
		ret->priv = priv;
		ret->priv_del = priv_del;
		ret->getch = getch;
		ret->write = write;
		ret->wait = wait;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

void Dz1ConsolePlatform_del(Dz1ConsolePlatform *p)
{
	if(!p) return;
	if (p->priv && p->priv_del) p->priv_del(p->priv);
	p->priv = NULL;
	free(p);
}

