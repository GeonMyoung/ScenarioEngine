
// dz1_code_gen_gui.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include <dz1.h>
#include "resource.h"		// 주 기호입니다.


// CDz1CodeGenGuiApp:
// 이 클래스의 구현에 대해서는 dz1_code_gen_gui.cpp을 참조하십시오.
//

class CDz1CodeGenGuiApp : public CWinAppEx
{
public:
	CDz1CodeGenGuiApp();

// 재정의입니다.
	public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

typedef struct Dz1CodeGenControlInfo
{
	u32_t						 idStatic;
	u32_t						 idEdit;

	u32_t						 idx;
} Dz1CodeGenControlInfo;

#define Dz1CodeGenControlInfoEntry(base_name, id_index) { IDC_STATIC_##base_name##_ARG##id_index, IDC_EDIT_##base_name##_ARG##id_index, (id_index - 1) }

extern CDz1CodeGenGuiApp theApp;

#define MY_MAX_PATH			4096

DZ1_CPPLINK BOOL SelectPath(HWND owner, TCHAR *initialPAth, TCHAR path[MY_MAX_PATH], TCHAR *title);

DZ1_CPPLINK BOOL SelectFile(CWnd *parentWindow, BOOL isLoadWindow, TCHAR *initialPath,
							TCHAR *extFilter, TCHAR *defaultExt,
							TCHAR ret_path[MY_MAX_PATH], TCHAR ret_name[MY_MAX_PATH]);
