// ..\..\Dz1CodeGenTdoListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "dz1_code_gen_gui.h"
#include "dz1_code_gen_tdo_list_dlg.h"
#include "dz1_code_gen_struct_util.h"

#include "Dz1CodeGenTdoColumnDlg.h"

// CDz1CodeGenTdoListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTdoListDlg, CDialog)

CDz1CodeGenTdoListDlg::CDz1CodeGenTdoListDlg(ObjectInfo *obj, Dz1CodeGenListColumnList *ret, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTdoListDlg::IDD, pParent)
{
	m_src = obj;
	ASSERT(m_src != NULL);

	m_ret = ret;
	ASSERT(m_ret != NULL);

	ArrayInfo *ai = (ArrayInfo *)m_src->info;

	m_root = ListControlGenNode_build("entry", ai->entry, NULL, NULL);

	ASSERT(m_root != NULL);
}

CDz1CodeGenTdoListDlg::~CDz1CodeGenTdoListDlg()
{
	if (m_root != NULL) ListControlGenNode_delAndSetNull(&m_root);
}

void CDz1CodeGenTdoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_SOURCES, m_treeSources);
	DDX_Control(pDX, IDC_LIST_COLUMNS, m_listColumns);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTdoListDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDz1CodeGenTdoListDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CDz1CodeGenTdoListDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTdoListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;
	str.Format("CListCtrl%s", m_src->name);
	this->SetWindowText(str);

	LoadTree();

	m_listColumns.InitControl();
	m_listColumns.Load(m_ret);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

typedef struct LoadTreeArg
{
	CTreeCtrl *dst;
	HTREEITEM parent;
} LoadTreeArg;

static Dz1Error _LoadTree(CTreeCtrl *dst, ListControlGenNode *p, HTREEITEM hParent);
static Dz1Error __LoadTree(void *ptr, ListControlGenNode *p)
{
	LoadTreeArg *arg = (LoadTreeArg *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	if ((*errp = _LoadTree(arg->dst, p, arg->parent)).code) ERR_OUT(errp);

	return err;
}

static Dz1Error _LoadTree(CTreeCtrl *dst, ListControlGenNode *p, HTREEITEM hParent)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	HTREEITEM h = dst->InsertItem(p->name, hParent, TVI_LAST);
	if (h == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->SetItemData(h, (DWORD_PTR)p);

		p->hTreeItem = h;
		LoadTreeArg arg = { dst, h };
		if ((*errp = p->childs->travel(p->childs, __LoadTree, (void *)&arg)).code) ERR_OUT(errp);
		dst->Expand(h, TVE_EXPAND);
	}
	return err;
}

BOOL CDz1CodeGenTdoListDlg::LoadTree(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _LoadTree(&m_treeSources, m_root, TVI_ROOT)).code) ERR_DLG_OUT(errp);

	return errp->code ? FALSE : TRUE;
}

Dz1Error CDz1CodeGenTdoListDlg::InsertColumn(u32_t order, ListControlGenNode *item)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1CodeGenListColumn *node = Dz1CodeGenListColumn_new(order, item->name, item->obj, item->name, Dz1CodeGenListCtrlInstanceMode_arrow, NULL, errp);
	if (node == NULL) ERR_DLG_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CodeGenListColumn_delAndSetNull, (void *)&node);
		if ((*errp = Dz1CodeGenListColumn_setParent(node, item->parent)).code) ERR_OUT(errp);
		else
		{
			CDz1CodeGenTdoColumnDlg dlg(node);
			if (dlg.DoModal() == IDOK)
			{
				if (m_listColumns.Insert(node) == TRUE)
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1CodeGenListColumn_delAndSetNull, (void *)&node);
	}
	return err;
}

void CDz1CodeGenTdoListDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HTREEITEM hItem = m_treeSources.GetSelectedItem();
	if (hItem != NULL)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		ListControlGenNode *item = (ListControlGenNode *)m_treeSources.GetItemData(hItem);

		if (item->isItem == FALSE) MessageBox(_T("해당 값은 Column으로 사용할 수 없습니다."));
		else
		{
			int nRow = m_listColumns.GetItemCount();
			if (nRow > 0)
			{	// 등록된 컬럼이 있는 경우 -> 마지막 컬럼의 Order값 다음 10단위 Order값을 얻는다
				Dz1CodeGenListColumn *last = m_listColumns.GetMyItemData(nRow - 1);
				if (last == NULL) ERR_DLG_SET_OUT(errp, EFAULT);
				else
				{
					u32_t order = ((last->order + 10) / 10) * 10;
					if ((*errp = InsertColumn(order, item)).code) ERR_DLG_OUT(errp);
				}
			}
			else if ((*errp = InsertColumn(10, item)).code) ERR_DLG_OUT(errp);
		}
	}
}
