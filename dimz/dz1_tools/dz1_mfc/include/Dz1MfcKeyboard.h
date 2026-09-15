#ifndef DZ1_MFC_KEYBOARD_H
#define DZ1_MFC_KEYBOARD_H

#include <Dz1MfcDef.h>

DZ1_CPPLINK Dz1MfcKeyboardKeyEntry	*Dz1MfcKeyboardKeyList_findPressed(Dz1MfcKeyboardKeyList *table, UINT nChar, UINT nRepCnt, UINT nFlags);
DZ1_CPPLINK Dz1MfcKeyboardKeyEntry	*Dz1MfcKeyboardKeyList_findReleased(Dz1MfcKeyboardKeyList *table, UINT nChar, UINT nRepCnt, UINT nFlags);
DZ1_CPPLINK Dz1Error				 Dz1MfcKeyboardKeyList_addKey(Dz1MfcKeyboardKeyList *table,
																  Dz1MfcKeyboardEvent ev,
																  bool_t isExtKey, u32_t code,
																  s32_t cmd, s32_t arg);

#endif