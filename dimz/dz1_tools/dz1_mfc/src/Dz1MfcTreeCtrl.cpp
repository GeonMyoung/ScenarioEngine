#include "stdafx.h"
#include <Dz1MfcTreeCtrl.h>

BEGIN_MESSAGE_MAP(CDz1TreeCtrl, CTreeCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// void CDz1TreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
// {
// 	if (m_get_focus_on_mose_over)
// 	{
// 		if (GetFocus() != this) SetFocus();
// 	}
// 	CTreeCtrl::OnMouseMove(nFlags, point);
// }

void CDz1TreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_get_focus_on_mose_over)
	{
		if (GetFocus() != this) SetFocus();
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

BOOL CDz1TreeCtrl::SetItemData(_In_ HTREEITEM hItem, _In_ LONG_PTR dwData)
{
	ASSERT(::IsWindow(m_hWnd)); return SetItem(hItem, TVIF_PARAM, NULL, 0, 0, 0, 0, dwData);
}

LONG_PTR CDz1TreeCtrl::GetItemData(_In_ HTREEITEM hItem) const
{
	ENSURE(::IsWindow(m_hWnd));
	ENSURE_ARG(hItem != NULL);
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_PARAM;
	VERIFY(::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item));
	return item.lParam;
}

