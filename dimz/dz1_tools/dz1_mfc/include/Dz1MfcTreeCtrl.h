#ifndef DZ1_MFC_TREE_CTRL_H
#define DZ1_MFC_TREE_CTRL_H

#include <dz1_mfc.h>

#ifdef __cplusplus

class CDz1TreeCtrl : public CTreeCtrl
{
public:
	CDz1TreeCtrl() : CTreeCtrl() { m_get_focus_on_mose_over = FALSE; };
	virtual ~CDz1TreeCtrl() { CTreeCtrl::~CTreeCtrl(); }

	void SetFocusOnMouseOver(bool_t v) { m_get_focus_on_mose_over = v; }

	BOOL		 SetItemData(_In_ HTREEITEM hItem, _In_ LONG_PTR dwData);
	LONG_PTR	 GetItemData(_In_ HTREEITEM hItem) const;
private:
	bool_t m_get_focus_on_mose_over;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // __cplusplus

#endif
