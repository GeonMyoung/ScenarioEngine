
// dz1_code_gen_gui.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include <dz1_cleanup.h>
#include <dz1_malloc.h>
#include "dz1_code_gen_gui.h"
#include "dz1_code_gen_gui_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDz1CodeGenGuiApp

BEGIN_MESSAGE_MAP(CDz1CodeGenGuiApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDz1CodeGenGuiApp 생성

CDz1CodeGenGuiApp::CDz1CodeGenGuiApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CDz1CodeGenGuiApp 개체입니다.

CDz1CodeGenGuiApp theApp;


// CDz1CodeGenGuiApp 초기화
static FILE *logfp = NULL;
static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }

BOOL CDz1CodeGenGuiApp::InitInstance()
{
	Dz1Cleanup_init();
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("Dz1CodeGenGui.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CDz1CodeGenGuiDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    // 폴더지정 대화상자 출력시 기본으로 선택되어질 경로 지정
	TCHAR *path = (TCHAR *)lpData;
    switch (uMsg)
	{
        case BFFM_INITIALIZED:
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)path);
            break;
    }
	return 0;
}

BOOL SelectPath(HWND owner, TCHAR *initialPAth, TCHAR path[MY_MAX_PATH], TCHAR *title)
{
	BOOL ret = FALSE;

	int end_pos;
	LPITEMIDLIST  pidl;
    BROWSEINFO bi;

	memset(path, 0, sizeof(TCHAR) * MY_MAX_PATH);

    bi.hwndOwner = owner;
    bi.pidlRoot = NULL;

	// 선택할 디렉토리가 저장될 버퍼
    bi.pszDisplayName = NULL;
 
    // 출력될 문자열
    bi.lpszTitle = title;

    // 디렉토리 선택 옵션
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
 
    // 이벤트에 대한 사용자정의 함수
    bi.lpfn = BrowseCallbackProc;
 
    // 사용자정의 함수에 넘겨질 인자
    bi.lParam = (LPARAM)initialPAth;

	pidl = SHBrowseForFolder(&bi);

    // 경로를 얻어온다.
    SHGetPathFromIDList(pidl, path);
    
    // 사용자가 폴더지정을 한 후 확인(OK)를 눌렀다면 해당 폴더의 경로에 대한 문자열이
    // 존재하므로 end_pos 의 값은 0 이 아니다. 취소를 눌렀다면 0 의 값을 가진다.
#ifdef UNICODE
    if ((end_pos = (int)wcslen(path)) > 0) ret = TRUE;
#else
    if ((end_pos = (int)strlen(path)) > 0) ret = TRUE;
#endif
	return ret;
}

BOOL SelectFile(CWnd *parentWindow, BOOL isLoadWindow, TCHAR *initialPath,
				TCHAR *extFilter, TCHAR *defaultExt,
				TCHAR ret_path[MY_MAX_PATH], TCHAR ret_name[MY_MAX_PATH])
{
	TCHAR filter[1024], defExt[1024];

	memset(ret_path, 0, sizeof(TCHAR) * MY_MAX_PATH);
	memset(ret_name, 0, sizeof(TCHAR) * MY_MAX_PATH);

#ifdef _UNICODE
	if (extFilter && wcslen(extFilter) > 0)
		wsprintf(filter, _T("All File(*.*)|%s|*.*||"), extFilter);
	else wcscpy(filter, _T("All File(*.*)|*.*||"));

	if (defaultExt && wcslen(defaultExt) > 0)
		wcscpy(defExt, defaultExt);
	else wcscpy(defExt, "");
#else
	if (extFilter && strlen(extFilter) > 0)
		sprintf(filter, "All File(*.*)|%s|*.*||", extFilter);
	else strcpy(filter, "All File(*.*)|*.*||");

	if (defaultExt && strlen(defaultExt) > 0)
		strcpy(defExt, defaultExt);
	else strcpy(defExt, "");
#endif
	CFileDialog getFile(isLoadWindow, defExt, _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, parentWindow);
	getFile.m_ofn.lpstrInitialDir = initialPath;
	getFile.m_ofn.lpstrFile = ret_name;
	getFile.m_ofn.nMaxFile = FILENAME_MAX;

	INT_PTR status = getFile.DoModal();
	if (status == IDOK)
	{
		TCHAR *cp = NULL;
#ifdef UNICODE
		if ((cp = wcsrchr(ret_name, DIR_SEP)) != NULL)
#else
		if ((cp = strrchr(ret_name, DIR_SEP)) != NULL)
#endif
		{
			*cp++ = '\0';
#ifdef UNICODE
			wcscpy(ret_path, ret_name);
			wcscpy(ret_name, cp);
#else
			strcpy(ret_path, ret_name);
			strcpy(ret_name, cp);
#endif
		}
		return TRUE;
	}
	else return FALSE;
}

