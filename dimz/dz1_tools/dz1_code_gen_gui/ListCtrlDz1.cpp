#include "stdafx.h"
#include "ListCtrlDz1.h"

void CListCtrlDz1::CleanupControl(void)
{
	int cnt = this->GetHeaderCtrl()->GetItemCount(), i;
	this->DeleteAllItems();
	for (i = 0; i < cnt; i++) this->DeleteColumn(0);
}

void CListCtrlRefDz1::CleanupControl(void)
{
	int cnt = this->GetHeaderCtrl()->GetItemCount(), i;
	this->DeleteAllItems();
	for (i = 0; i < cnt; i++) this->DeleteColumn(0);
}
