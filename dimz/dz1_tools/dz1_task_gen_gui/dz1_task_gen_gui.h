// dz1_task_gen_gui.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH에서 이 파일을 포함하기 전에 'stdafx.h'를 포함하십시오.
#endif

#include "resource.h"		// 주 기호

#include <dz1_error.h>
#include <dz1_str.h>
#include <Dz1MfcDefUtil.h>

// CDz1TaskGen_app:
// 이 클래스의 구현에 대해서는 dz1_task_gen_gui.cpp을 참조하십시오.
//

class CDz1TaskGen_app : public CWinApp
{
public:
	CDz1TaskGen_app();
	Dz1MfcProgInfo			*m_prog_info;
// 재정의
	public:
	virtual BOOL InitInstance();

// 구현

	DECLARE_MESSAGE_MAP()
};

extern CDz1TaskGen_app theApp;
