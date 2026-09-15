#ifndef COMBO_BOX_GEN_TARGET_H
#define COMBO_BOX_GEN_TARGET_H

#include <Dz1MfcComboBoxTemplate.h>
#include <dz1_task_gen_args.h>

class CComboBoxGenTarget : public CDz1ComboCtrl<Dz1GenTarget>
{
public:
	CComboBoxGenTarget() : CDz1ComboCtrl(Dz1GenTarget_max, Dz1GenTargetStr) { }
	virtual ~CComboBoxGenTarget() { CDz1ComboCtrl::~CDz1ComboCtrl(); }

};

class CComboBoxGenTxtMode : public CDz1ComboCtrl<Dz1GenTextMode>
{
public:
	CComboBoxGenTxtMode() : CDz1ComboCtrl(Dz1GenTextMode_max, Dz1GenTextModeStr) { }
	virtual ~CComboBoxGenTxtMode() { CDz1ComboCtrl::~CDz1ComboCtrl(); }

};

/*
class CComboBoxGenWordSize : public CDz1ComboCtrl<Dz1TaskGenWordSize>
{
public:
	CComboBoxGenWordSize() : CDz1ComboCtrl(Dz1TaskGenWordSize_max, Dz1TaskGenWordSizeStr) { }
	virtual ~CComboBoxGenWordSize() { CDz1ComboCtrl::~CDz1ComboCtrl(); }

};
*/

class CComboBoxGenArgs2Naming : public CDz1ComboCtrl<GenArgs2Naming>
{
public:
	CComboBoxGenArgs2Naming() : CDz1ComboCtrl(GenArgs2Naming_max, GenArgs2NamingStr) { }
	virtual ~CComboBoxGenArgs2Naming() { CDz1ComboCtrl::~CDz1ComboCtrl(); }

};

class CComboBoxGenEndian : public CDz1ComboCtrl<Dz1TaskGenEndian>
{
public:
	CComboBoxGenEndian() : CDz1ComboCtrl(Dz1TaskGenEndian_max, Dz1TaskGenEndianStr) { }
	virtual ~CComboBoxGenEndian() { CDz1ComboCtrl::~CDz1ComboCtrl(); }
};


class CComboBoxProjectVer : public CDz1ComboCtrl<GenArgs2VisualStudioVerSupport>
{
public:
	CComboBoxProjectVer() : CDz1ComboCtrl(GenArgs2VisualStudioVerSupport_max, GenArgs2VisualStudioVerSupportStr) { }
	virtual ~CComboBoxProjectVer() { CDz1ComboCtrl::~CDz1ComboCtrl(); }
};

#endif