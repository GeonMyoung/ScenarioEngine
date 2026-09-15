#ifndef DZ1_CODE_GEN_TODEC_HELPER_H
#define DZ1_CODE_GEN_TODEC_HELPER_H

#include <Dz1MfcListCtrlTemplate.h>
#include <Dz1MfcComboBoxTemplate.h>

#include "Dz1CodeGenTodecUtil.h"

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructObject
class CListCtrlConstructObject : public CDz1ListCtrlRO<ConstructObjectList, ConstructObjectEntry>
{
public:
	CListCtrlConstructObject() : CDz1ListCtrlRO<ConstructObjectList, ConstructObjectEntry>() { }
	~CListCtrlConstructObject() { CDz1ListCtrlRO::~CDz1ListCtrlRO(); }

	BOOL OnInitControl();
	void RefreshRow(int idx);
protected:
	virtual void	 GetFirstColumn(CString &str, ConstructObjectEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, ConstructObjectEntry *node);
};
// CListCtrlConstructObject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructCodec
class CListCtrlConstructCodec : public CDz1ListCtrlRW<ConstructCodecList, ConstructCodecEntry>
{
public:
	CListCtrlConstructCodec() : CDz1ListCtrlRW<ConstructCodecList, ConstructCodecEntry>(ConstructCodecEntry_clone, ConstructCodecEntry_del) { }
	~CListCtrlConstructCodec() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }
	BOOL OnInitControl();

protected:
	virtual void	 GetFirstColumn(CString &str, ConstructCodecEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, ConstructCodecEntry *node);
};
// CListCtrlConstructCodec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructCodec
class CListCtrlConstructMemberCodec : public CDz1ListCtrlRW<ConstructMemberCodecList, ConstructMemberCodecEntry>
{
public:
	CListCtrlConstructMemberCodec() : CDz1ListCtrlRW<ConstructMemberCodecList, ConstructMemberCodecEntry>(ConstructMemberCodecEntry_clone, ConstructMemberCodecEntry_del) { }
	~CListCtrlConstructMemberCodec() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }
	BOOL OnInitControl();
	ConstructMemberCodecEntry *FindName(Dz1Str name);
protected:
	virtual void	 GetFirstColumn(CString &str, ConstructMemberCodecEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, ConstructMemberCodecEntry *node);
};
// CListCtrlConstructMemberCodec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CComboTdcInfoStructMembers
class CComboTdcInfoStructMembers : public CDz1IndexComboCtrl<StructMemberList, StructMemberEntry>
{
protected:
	bool_t ToString(StructMemberEntry *src, CString &dst);
};

class CComboTodecLimitedMethodCtrl : public CDz1ComboCtrl<ConstructMemberCodecLimitedInfoPresent>
{
public:
	CComboTodecLimitedMethodCtrl() : CDz1ComboCtrl(ConstructMemberCodecLimitedInfoPresent_max, ConstructMemberCodecLimitedInfoPresentStr) { }
	virtual ~CComboTodecLimitedMethodCtrl() { CDz1ComboCtrl::~CDz1ComboCtrl(); }
};
// CComboTdcInfoStructMembers
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CListCtrlConstructCodecInclude
class CListCtrlConstructCodecInclude : public CDz1ListCtrlRW<ConstructCodecIncludeList, ConstructCodecIncludeEntry>
{
public:
	CListCtrlConstructCodecInclude() : CDz1ListCtrlRW<ConstructCodecIncludeList, ConstructCodecIncludeEntry>(ConstructCodecIncludeEntry_clone, ConstructCodecIncludeEntry_del) { }
	~CListCtrlConstructCodecInclude() { CDz1ListCtrlRW::~CDz1ListCtrlRW(); }
	BOOL OnInitControl();

protected:
	virtual void	 GetFirstColumn(CString &str, ConstructCodecIncludeEntry *node);
	virtual BOOL	 SetItemTexts(int nRow, ConstructCodecIncludeEntry *node);
};
// CListCtrlConstructCodecInclude
////////////////////////////////////////////////////////////////////////////////

#endif
