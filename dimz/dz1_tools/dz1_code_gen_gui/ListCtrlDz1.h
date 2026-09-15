#ifndef LIST_CTRL_DZ1_H
#define LIST_CTRL_DZ1_H

#include <dz1_error.h>
#include "ListCtrlStyled.h"

// 컨트롤 자체가 list자료구조를 포함한 형태
class CListCtrlDz1 : public CListCtrlStyled
{
public:
	virtual BOOL InitControl() = 0;
	virtual void CleanupData() = 0;
	void CleanupControl();
};

// list자료구조는 외부에 있고 이를 참조한 형태
class CListCtrlRefDz1 : public CListCtrlStyled
{
public:
	virtual BOOL InitControl() = 0;
	virtual void CleanupData() = 0;
	void CleanupControl();
};

#endif