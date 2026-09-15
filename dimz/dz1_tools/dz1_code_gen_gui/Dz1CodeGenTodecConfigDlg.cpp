// ..\..\Dz1CodeGenTodecConfigDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <Dz1MfcFileSelectDlg.h>

#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTodecConfigDlg.h"

#include "Dz1CodeGenTodecPublish.h"

// CDz1CodeGenTodecConfigDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTodecConfigDlg, CDialog)

CDz1CodeGenTodecConfigDlg::CDz1CodeGenTodecConfigDlg(ConstructMemberCodecInfo **ret,
													 ConstructMemberCodecEntry *parent_entry,
													 ObjectInfo *parent_obj,
													 Dz1Str instance_name, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTodecConfigDlg::IDD, pParent)
{
	m_ret = ret; ASSERT(m_ret != NULL);
	m_dst = (*m_ret);

	m_parent_entry = parent_entry;
	m_target_obj = m_parent_entry->obj;
	m_parent_obj = parent_obj;
	m_instance_name = instance_name;

	m_one_of_struct_info = NULL;
}

CDz1CodeGenTodecConfigDlg::~CDz1CodeGenTodecConfigDlg()
{
	ConstructMemberCodecLimitedInfo_delAndSetNull(&m_one_of_struct_info);
}

void CDz1CodeGenTodecConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_ONE_MEMBER_OF_STRUCTURE, m_radioOneOfStruct);
	DDX_Control(pDX, IDC_COMBO_ONE_MEMBER_OF_STRUCTURE, m_comboOneOfStruct);
	DDX_Control(pDX, IDC_EDIT_ONE_OF_STRUCTURE, m_editOneOfStruct);
	DDX_Control(pDX, IDC_BUTTON_ONE_MEMBER_OF_STRUCTURE, m_btnOneOfStruct);

	DDX_Control(pDX, IDC_RADIO_BYTES_OF_PRIMITIVE, m_radioBytesOfPrimitive);
	DDX_Control(pDX, IDC_SLIDER_BYTES_OF_PRIMITIVE_LEN, m_sldBytesOfPrimitiveLen);
	DDX_Control(pDX, IDC_SLIDER_BYTES_OF_PRIMITIVE_SFT, m_sldBytesOfPrimitiveSft);

	DDX_Control(pDX, IDC_RADIO_BITS_OF_PRIMITIVE, m_radioBitsOfPrimitive);
	DDX_Control(pDX, IDC_SLIDER_BITS_OF_PRIMITIVE_LEN, m_sldBitsOfPrimitiveLen);
	DDX_Control(pDX, IDC_SLIDER_BITS_OF_PRIMITIVE_SFT, m_sldBitsOfPrimitiveSft);

	DDX_Control(pDX, IDC_RADIO_INHIVIT_MEMBER, m_radioVoidMember);

	DDX_Control(pDX, IDC_RADIO_ALTERNATE_FUNCTION, m_radioAlternateFunction);
	DDX_Control(pDX, IDC_EDIT_ALTERNATE_FUNCTION, m_editAlternateFunction);

	DDX_Control(pDX, IDC_RADIO_DEFAULT_METHOD, m_radioDefaultMethod);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTodecConfigDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_ONE_MEMBER_OF_STRUCTURE, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioOneMemberOfStructure)
	ON_BN_CLICKED(IDC_BUTTON_ONE_MEMBER_OF_STRUCTURE, &CDz1CodeGenTodecConfigDlg::OnBnClickedButtonOneMemberOfStructure)

	ON_BN_CLICKED(IDC_RADIO_BYTES_OF_PRIMITIVE, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioSubBytesOfPrimitive)

	ON_BN_CLICKED(IDC_RADIO_BITS_OF_PRIMITIVE, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioSubBitsOfPrimitive)

	ON_BN_CLICKED(IDC_RADIO_INHIVIT_MEMBER, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioInhivitMember)

	ON_BN_CLICKED(IDC_RADIO_ALTERNATE_FUNCTION, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioUseAlternativeFunction)

	ON_BN_CLICKED(IDC_RADIO_DEFAULT_METHOD, &CDz1CodeGenTodecConfigDlg::OnBnClickedRadioDefaultMethod)

	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1CodeGenTodecConfigDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1CodeGenTodecConfigDlg 메시지 처리기입니다.

BOOL CDz1CodeGenTodecConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString title;
	title.Format(_T("%s::%s CODEC Method"), m_target_obj->name, m_instance_name);
	this->SetWindowText(title);

	// 각각의 초기화, Enable/Disable
	if (ObjectInfo_typeOf(m_parent_obj) == ObjectType_union)
		m_radioVoidMember.EnableWindow(TRUE);
	else m_radioVoidMember.EnableWindow(FALSE);

	s32_t prim_sz = 0;
	ObjectType type = ObjectInfo_typeOf(m_target_obj);
	switch(type)
	{
	case ObjectType_enumerate:				// EnumInfo
		prim_sz = 4;
		EnableOneOfStructure(FALSE);
		break;
	case ObjectType_primitive:				// PrimitiveInfo
		{
			PrimitiveInfo *info = (PrimitiveInfo *)m_target_obj->info;
			prim_sz = _resolve_primitive_type_size(info);
			EnableOneOfStructure(FALSE);
			switch(prim_sz)
			{
			case 1: case 2: case 4: case 8: break;
			default:
				EnableBitsOfPrimitive(FALSE);
				EnableBytesOfPrimitive(FALSE);
				break;
			}
		}
		break;
	default:
	case ObjectType_defined:				// DefinedInfo
	case ObjectType_bits:					// BitsInfo
	case ObjectType_func:					// FunctionInfo
	case ObjectType_constant:
	case ObjectType_declare:				// str_t				선행 정의용
	case ObjectType_reference:				// ExternInfo			헤더에서 인클루드할 경우 인클루드 순환이 발생하는 타입	
		EnableOneOfStructure(FALSE);
		EnableBitsOfPrimitive(FALSE);
		EnableBytesOfPrimitive(FALSE);
		m_radioVoidMember.EnableWindow(FALSE);
		EnableAlternateFunction(FALSE);
		m_radioDefaultMethod.EnableWindow(FALSE);
		break;
	case ObjectType_structure:				// StructureInfo
		{
		StructureInfo *st_info = (StructureInfo *)m_target_obj->info;
		CodecOneOfConstruct *oos = m_dst->x.one_of_structure;
		m_comboOneOfStruct.OnInitControl(st_info->members);
		if (oos->info != NULL)
		{
			m_one_of_struct_info = ConstructMemberCodecLimitedInfo_clone(oos->info, NULL);
			ASSERT(m_one_of_struct_info != NULL);
		}
		LoadOneOfStructMethod();

		EnableBitsOfPrimitive(FALSE);
		EnableBytesOfPrimitive(FALSE);
		}
		break;
	case ObjectType_index:					// IndexInfo
	case ObjectType_array:					// ArrayInfo
	case ObjectType_union:					// UnionInfo
	case ObjectType_extern:					// ExternInfo			외부 정의 타입
		EnableOneOfStructure(FALSE);
		EnableBitsOfPrimitive(FALSE);
		EnableBytesOfPrimitive(FALSE);
		break;
	}

	m_sldBytesOfPrimitiveLen.SetRange(1,8);
	m_sldBytesOfPrimitiveLen.SetPos(8);

	m_sldBytesOfPrimitiveSft.SetRange(0,7);
	m_sldBytesOfPrimitiveSft.SetPos(0);

	m_sldBitsOfPrimitiveLen.SetRange(1,64);
	m_sldBitsOfPrimitiveLen.SetPos(64);

	m_sldBitsOfPrimitiveSft.SetRange(0,63);
	m_sldBitsOfPrimitiveSft.SetPos(0);

	if (m_dst != NULL)
	{
		switch(m_dst->present)
		{
		case ConstructMemberCodecInfoPresent_one_of_structure:
			m_radioOneOfStruct.SetCheck(TRUE);
			{
				CodecOneOfConstruct *ooc = m_dst->x.one_of_structure;

				StructureInfo *info = (StructureInfo *)m_target_obj->info;
				StructMemberList *list = info->members;
				StructMemberEntry *node = list->find(list, ooc->instance_name);
				if (node != NULL)				
					m_comboOneOfStruct.SetCurValue(node);
			}
			break;
		case ConstructMemberCodecInfoPresent_byte_of_primitive:
			m_radioBytesOfPrimitive.SetCheck(TRUE);
			{
				CodecPrimitiveByte *bop = m_dst->x.byte_of_primitive;
				PrimitiveInfo *info = (PrimitiveInfo *)m_target_obj->info;
				switch(prim_sz)
				{
				case 1: case 2: case 4: case 8:
					m_sldBytesOfPrimitiveLen.SetRange(1, prim_sz);
					m_sldBytesOfPrimitiveLen.SetPos(bop->byte_len);
					m_sldBytesOfPrimitiveSft.SetRange(0, prim_sz - 1);
					m_sldBytesOfPrimitiveSft.SetPos(bop->byte_sft);
				default:
					break;
				}
			}
			break;
		case ConstructMemberCodecInfoPresent_bits_of_primitive:
			m_radioBitsOfPrimitive.SetCheck(TRUE);
			{
				CodecPrimitiveBits *bop = m_dst->x.bits_of_primitive;
				PrimitiveInfo *info = (PrimitiveInfo *)m_target_obj->info;
				switch(prim_sz)
				{
				case 1: case 2: case 4: case 8:
					m_sldBitsOfPrimitiveLen.SetRange(1, prim_sz * 8);
					m_sldBitsOfPrimitiveLen.SetPos(bop->bit_len);

					m_sldBitsOfPrimitiveSft.SetRange(0, (prim_sz * 8) - 1);
					m_sldBitsOfPrimitiveSft.SetPos(bop->bit_sft);
				default:
					break;
				}
			}
			break;
		case ConstructMemberCodecInfoPresent_void_member:
			m_radioVoidMember.SetCheck(TRUE);
			break;
		case ConstructMemberCodecInfoPresent_alternate:
			m_radioAlternateFunction.SetCheck(TRUE);
			m_editAlternateFunction.SetWindowText(m_dst->x.alternate);
			break;
		case ConstructMemberCodecInfoPresent_max:
		default:
			EndDialog(-1);
			break;
		}
	}
	else m_radioDefaultMethod.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTodecConfigDlg::LoadOneOfStructMethod(void)
{
	if (m_one_of_struct_info == NULL)
		m_editOneOfStruct.SetWindowText(_T("Default"));
	else
	{
		CString str;
		str.Format(_T("%s"), ConstructMemberCodecLimitedInfoPresentStr(m_one_of_struct_info->present));
		m_editOneOfStruct.SetWindowText(str);
	}
}

void CDz1CodeGenTodecConfigDlg::EnableOneOfStructure(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioOneOfStruct.EnableWindow(en);
	m_comboOneOfStruct.EnableWindow(en);
	m_btnOneOfStruct.EnableWindow(en);
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedButtonOneMemberOfStructure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDz1CodeGenTodecConfigDlg::EnableBitsOfPrimitive(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioBitsOfPrimitive.EnableWindow(en);
	m_sldBitsOfPrimitiveLen.EnableWindow(en);
	m_sldBitsOfPrimitiveSft.EnableWindow(en);
}

void CDz1CodeGenTodecConfigDlg::EnableBytesOfPrimitive(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioBytesOfPrimitive.EnableWindow(en);
	m_sldBytesOfPrimitiveLen.EnableWindow(en);
	m_sldBytesOfPrimitiveSft.EnableWindow(en);
}

void CDz1CodeGenTodecConfigDlg::EnableAlternateFunction(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioAlternateFunction.EnableWindow(en);
	m_editAlternateFunction.EnableWindow(en);
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioOneMemberOfStructure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioOneOfStruct.GetCheck())
	{
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);

		EnableOneOfStructure(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioSubBitsOfPrimitive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioBitsOfPrimitive.GetCheck())
	{
		EnableOneOfStructure(FALSE, FALSE);
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);

		EnableBitsOfPrimitive(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioSubBytesOfPrimitive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioBytesOfPrimitive.GetCheck())
	{
		EnableOneOfStructure(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);

		EnableBytesOfPrimitive(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioInhivitMember()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioVoidMember.GetCheck())
	{
		EnableOneOfStructure(FALSE, FALSE);
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);
	}
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioUseAlternativeFunction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioAlternateFunction.GetCheck())
	{
		EnableOneOfStructure(FALSE, FALSE);
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);

		EnableAlternateFunction(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedRadioDefaultMethod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioDefaultMethod.GetCheck())
	{
		EnableOneOfStructure(FALSE, FALSE);
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);
	}
}

Dz1Error CDz1CodeGenTodecConfigDlg::GenerateInfo(ConstructMemberCodecInfo **_temp)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecInfo *temp = NULL;
	if (m_radioOneOfStruct.GetCheck())
	{
		if ((temp = ConstructMemberCodecInfo_new( ConstructMemberCodecInfoPresent_one_of_structure, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			CodecOneOfConstruct *oos = NULL;
			StructMemberEntry *entry = m_comboOneOfStruct.GetCurSelValue();
			pthread_cleanup_push(ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
			if ((oos = temp->x.one_of_structure = CodecOneOfConstruct_new(m_parent_entry, entry->instance, entry->type, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((oos->info = ConstructMemberCodecLimitedInfo_clone(m_one_of_struct_info, errp)) == NULL) ERR_OUT(errp);
			else
			{
				m_one_of_struct_info = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
		}
	}
	else if (m_radioBytesOfPrimitive.GetCheck())
	{
		if ((temp = ConstructMemberCodecInfo_new( ConstructMemberCodecInfoPresent_byte_of_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.byte_of_primitive = CodecPrimitiveByte_new(m_parent_entry, (u32_t)m_sldBytesOfPrimitiveLen.GetPos(), (u32_t)m_sldBytesOfPrimitiveSft.GetPos(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
		}
	}
	else if (m_radioBitsOfPrimitive.GetCheck())
	{
		if ((temp = ConstructMemberCodecInfo_new( ConstructMemberCodecInfoPresent_bits_of_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.bits_of_primitive = CodecPrimitiveBits_new(m_parent_entry, (u32_t)m_sldBitsOfPrimitiveLen.GetPos(), (u32_t)m_sldBitsOfPrimitiveSft.GetPos(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
		}
	}
	else if (m_radioVoidMember.GetCheck())
	{
		if ((temp = ConstructMemberCodecInfo_new(ConstructMemberCodecInfoPresent_void_member, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (m_radioAlternateFunction.GetCheck())
	{
		CString str;
		m_editAlternateFunction.GetWindowText(str);
		if (str.IsEmpty()) MessageBox(_T("Alternate Function Prefix"));
		else if ((temp = ConstructMemberCodecInfo_new(ConstructMemberCodecInfoPresent_alternate, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.alternate = Dz1Str_dup(str.GetBuffer(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecInfo_delAndSetNull, (void *)&temp);
		}
	}
	else if (m_radioDefaultMethod.GetCheck())
	{
		Dz1Error_set(errp, 0);
	}
	(*_temp) = temp;
	return err;
}

void CDz1CodeGenTodecConfigDlg::OnBnClickedButtonOk()
{
	ConstructMemberCodecInfo *temp = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = GenerateInfo(&temp)).code) ERR_DLG_OUT(errp);
	else
	{
		if (m_dst != NULL) ConstructMemberCodecInfo_delAndSetNull(m_ret);
		(*m_ret) = temp;
		temp = NULL;

		OnOK();
	}
}