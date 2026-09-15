#include "stdafx.h"
#include "dz1_mfc.h"
#include "Dz1MfcFileSelectDlg.h"

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    // 폴더지정 대화상자 출력시 기본으로 선택되어질 경로 지정
	TCHAR *path = (TCHAR *)lpData;
    switch (uMsg)
	{
        case BFFM_INITIALIZED:
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)path);
			SendMessage(hwnd, BFFM_SETEXPANDED, TRUE, (LPARAM)path);
            break;
    }
	return 0;
}

BOOL Dz1MfcPathSelectDlg(HWND owner, TCHAR *initialPath, TCHAR path[DZ1_FILE_SELECT_PATH_LEN], TCHAR *title)
{
	BOOL ret = FALSE;

	int end_pos;
	LPITEMIDLIST  pidl;
    BROWSEINFO bi;

	memset(path, 0, sizeof(TCHAR) * DZ1_FILE_SELECT_PATH_LEN);

    bi.hwndOwner = owner;
    bi.pidlRoot = NULL;

	// 선택할 디렉토리가 저장될 버퍼
    bi.pszDisplayName = NULL;
 
    // 출력될 문자열
    bi.lpszTitle = title;

    // 디렉토리 선택 옵션
    bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_NONEWFOLDERBUTTON;
 
    // 이벤트에 대한 사용자정의 함수
    bi.lpfn = BrowseCallbackProc;
 
    // 사용자정의 함수에 넘겨질 인자
    bi.lParam = (LPARAM)initialPath;

	pidl = SHBrowseForFolder(&bi);

    // 경로를 얻어온다.
    SHGetPathFromIDList(pidl, path);
    
    // 사용자가 폴더지정을 한 후 확인(OK)를 눌렀다면 해당 폴더의 경로에 대한 문자열이
    // 존재하므로 end_pos 의 값은 0 이 아니다. 취소를 눌렀다면 0 의 값을 가진다.
    if ((end_pos = (int)Dz1STRLEN(path)) > 0) ret = TRUE;
	return ret;
}

BOOL Dz1MfcPathSelectDlg2(HWND owner, TCHAR in_out_path[DZ1_FILE_SELECT_PATH_LEN], TCHAR *title)
{
	TCHAR temp[DZ1_FILE_SELECT_PATH_LEN], *init_path = temp;
	if (Dz1Str_isVoid(in_out_path) == FALSE) Dz1STRCPY(temp, in_out_path);
	else init_path = NULL;

	return Dz1MfcPathSelectDlg(owner, init_path, in_out_path, title);
}

BOOL Dz1MfcFileSelectDlg(CWnd *parentWindow,
					  BOOL open4read,
					  TCHAR *initialPath,
					  TCHAR *name_suggest,
					  TCHAR *extFilter, TCHAR *defaultExt,
					  TCHAR ret_path[DZ1_FILE_SELECT_PATH_LEN],
					  TCHAR ret_name[DZ1_FILE_SELECT_NAME_LEN])
{
	TCHAR filter[1024] = { 0, }, defExt[1024] = { 0, }, work_str[DZ1_FILE_SELECT_PATH_LEN] = { 0, };
	memset(ret_path, 0, sizeof(TCHAR) * DZ1_FILE_SELECT_PATH_LEN);
	memset(ret_name, 0, sizeof(TCHAR) * DZ1_FILE_SELECT_NAME_LEN);

	// Chart Files (*.xlc)|*.xlc|
	// Worksheet Files (*.xls)|*.xls|
	// Data Files (*.xlc;*.xls)|*.xlc;*.xls|
	// All Files (*.*)|*.*||
	if (extFilter && Dz1STRLEN(extFilter) > 0) Dz1STRCPY(filter, extFilter); // Some Name|*.ext|
	Dz1STRCAT(filter, _T("All File(*.*)|*.*||"));

	if (defaultExt && Dz1STRLEN(defaultExt) > 0) Dz1STRCPY(defExt, defaultExt);

	CFileDialog getFile(open4read, defExt, name_suggest, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, parentWindow);

	getFile.GetOFN().lpstrInitialDir	= initialPath;
// 	getFile.GetOFN().lpstrFilter		= filter;
// 	getFile.GetOFN().nFilterIndex		= 0;
	getFile.GetOFN().lpstrFile			= work_str;
	getFile.GetOFN().nMaxFile			= DZ1_FILE_SELECT_PATH_LEN;

	if (name_suggest != NULL && name_suggest[0] != 0) Dz1STRCPY(work_str, name_suggest);

	INT_PTR status = getFile.DoModal();
	if (status == IDOK)
	{
		TCHAR *srcp = work_str;
		if (Dz1STRNCMP(work_str, Dz1Text("\\\\?\\"), 4) == 0) srcp = work_str + 4;
		Dz1FileName_splitPathName(ret_path, ret_name, srcp);
		return TRUE;
	}
	else return FALSE;
}

