#include "stdafx.h"
#include "dz1_mfc.h"
#include "Dz1MfcKeyboard.h"
Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyList_findPressed(Dz1MfcKeyboardKeyList *table, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	Dz1MfcKeyboardEvent ev = nFlags & 0x4000 ? Dz1MfcKeyboardEvent_Repeated : Dz1MfcKeyboardEvent_Pressed;
	bool_t is_ext_key = nFlags & 0x100 ? TRUE : FALSE;

	Dz1MfcKeyboardKeyEntry key = { ev, is_ext_key, nChar };
	return table->find(table, &key);
}

Dz1MfcKeyboardKeyEntry *Dz1MfcKeyboardKeyList_findReleased(Dz1MfcKeyboardKeyList *table, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	bool_t is_ext_key = nFlags & 0x100 ? TRUE : FALSE;
	Dz1MfcKeyboardKeyEntry key = { Dz1MfcKeyboardEvent_Released, is_ext_key, nChar };
	return table->find(table, &key);
}

Dz1Error Dz1MfcKeyboardKeyList_addKey(Dz1MfcKeyboardKeyList *dst,
									  Dz1MfcKeyboardEvent ev, bool_t isExtKey, u32_t code,
									  s32_t cmd, s32_t arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcKeyboardKeyEntry *node = Dz1MfcKeyboardKeyEntry_new(ev, isExtKey, code, cmd, arg, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcKeyboardKeyEntry_delAndSetNull, (void **)&node);
		if (0) { }
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcKeyboardKeyEntry_delAndSetNull, (void **)&node);
	}
	return err;
}

