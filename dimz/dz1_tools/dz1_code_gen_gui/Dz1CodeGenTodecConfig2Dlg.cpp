// ..\..\Dz1CodeGenTodecConfig2Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "dz1_code_gen_gui.h"
#include "Dz1CodeGenTodecConfig2Dlg.h"

#include "Dz1CodeGenTodecPublish.h"
// CDz1CodeGenTodecConfig2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDz1CodeGenTodecConfig2Dlg, CDialog)

CDz1CodeGenTodecConfig2Dlg::CDz1CodeGenTodecConfig2Dlg(ConstructMemberCodecLimitedInfo **ret, ConstructMemberCodecEntry *parent_entry, ObjectInfo *target_obj, CWnd* pParent /*=NULL*/)
	: CDialog(CDz1CodeGenTodecConfig2Dlg::IDD, pParent)
{
	m_ret = ret; ASSERT(m_ret != NULL);
	m_dst = (*m_ret);

	m_target_obj = target_obj; ASSERT(m_target_obj != NULL);

	m_parent_entry = parent_entry; ASSERT(m_parent_entry != NULL);
}

CDz1CodeGenTodecConfig2Dlg::~CDz1CodeGenTodecConfig2Dlg()
{
}

void CDz1CodeGenTodecConfig2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO_BYTES_OF_PRIMITIVE, m_radioBytesOfPrimitive);
	DDX_Control(pDX, IDC_SLIDER_BYTES_OF_PRIMITIVE_LEN, m_sldBytesOfPrimitiveLen);
	DDX_Control(pDX, IDC_SLIDER_BYTES_OF_PRIMITIVE_SFT, m_sldBytesOfPrimitiveSft);

	DDX_Control(pDX, IDC_RADIO_BITS_OF_PRIMITIVE, m_radioBitsOfPrimitive);
	DDX_Control(pDX, IDC_SLIDER_BITS_OF_PRIMITIVE_LEN, m_sldBitsOfPrimitiveLen);
	DDX_Control(pDX, IDC_SLIDER_BITS_OF_PRIMITIVE_SFT, m_sldBitsOfPrimitiveSft);

	DDX_Control(pDX, IDC_RADIO_ALTERNATE_FUNCTION, m_radioAlternateFunction);
	DDX_Control(pDX, IDC_EDIT_ALTERNATE_FUNCTION, m_editAlternateFunction);

	DDX_Control(pDX, IDC_RADIO_DEFAULT_METHOD, m_radioDefaultMethod);
}


BEGIN_MESSAGE_MAP(CDz1CodeGenTodecConfig2Dlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_BITS_OF_PRIMITIVE, &CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioBitsOfPrimitive)
	ON_BN_CLICKED(IDC_RADIO_BYTES_OF_PRIMITIVE, &CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioBytesOfPrimitive)
	ON_BN_CLICKED(IDC_RADIO_ALTERNATE_FUNCTION, &CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioAlternateFunction)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT_METHOD, &CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioDefaultMethod)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDz1CodeGenTodecConfig2Dlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDz1CodeGenTodecConfig2Dlg 메시지 처리기입니다.

BOOL CDz1CodeGenTodecConfig2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	s32_t prim_sz = 0;
	ObjectType type = ObjectInfo_typeOf(m_target_obj);
	if (type == ObjectType_primitive)
	{
		PrimitiveInfo *info = (PrimitiveInfo *)m_target_obj->info;
		prim_sz = _resolve_primitive_type_size(info);
		switch(prim_sz)
		{
		case 1: case 2: case 4: case 8:
			m_sldBytesOfPrimitiveLen.SetRange(1, prim_sz);
			m_sldBytesOfPrimitiveLen.SetPos(prim_sz);

			m_sldBytesOfPrimitiveSft.SetRange(0, prim_sz - 1);
			m_sldBytesOfPrimitiveSft.SetPos(0);

			m_sldBitsOfPrimitiveLen.SetRange(1, prim_sz * 8);
			m_sldBitsOfPrimitiveLen.SetPos(prim_sz * 8);

			m_sldBitsOfPrimitiveSft.SetRange(0, (prim_sz * 8) - 1);
			m_sldBitsOfPrimitiveSft.SetPos(0);

			break;
		default:
			EnableBytesOfPrimitive(FALSE);
			EnableBitsOfPrimitive(FALSE);
			break;
		}
	}
	else
	{
		EnableBytesOfPrimitive(FALSE);
		EnableBitsOfPrimitive(FALSE);
	}

	if (m_dst != NULL)
	{
		switch(m_dst->present)
		{
		case ConstructMemberCodecLimitedInfoPresent_byte_of_primitive:
			m_radioBytesOfPrimitive.SetCheck(TRUE);
			m_sldBytesOfPrimitiveLen.SetPos(m_dst->x.byte_of_primitive->byte_len);
			m_sldBytesOfPrimitiveSft.SetPos(m_dst->x.byte_of_primitive->byte_sft);
			break;
		case ConstructMemberCodecLimitedInfoPresent_bits_of_primitive:
			m_radioBitsOfPrimitive.SetCheck(TRUE);
			m_sldBitsOfPrimitiveLen.SetPos(m_dst->x.bits_of_primitive->bit_len);
			m_sldBitsOfPrimitiveSft.SetPos(m_dst->x.bits_of_primitive->bit_sft);
			break;
		case ConstructMemberCodecLimitedInfoPresent_alternate:
			m_radioAlternateFunction.SetCheck(TRUE);
			m_editAlternateFunction.SetWindowText(m_dst->x.alternate);
			break;
		case ConstructMemberCodecLimitedInfoPresent_max:
		default:
			EnableBytesOfPrimitive(FALSE);
			EnableBitsOfPrimitive(FALSE);
			EnableAlternateFunction(FALSE);
			m_radioDefaultMethod.EnableWindow(FALSE);
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDz1CodeGenTodecConfig2Dlg::EnableBitsOfPrimitive(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioBitsOfPrimitive.EnableWindow(en);
	m_sldBitsOfPrimitiveLen.EnableWindow(en);
	m_sldBitsOfPrimitiveSft.EnableWindow(en);
}

void CDz1CodeGenTodecConfig2Dlg::EnableBytesOfPrimitive(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioBytesOfPrimitive.EnableWindow(en);
	m_sldBytesOfPrimitiveLen.EnableWindow(en);
	m_sldBytesOfPrimitiveSft.EnableWindow(en);
}

void CDz1CodeGenTodecConfig2Dlg::EnableAlternateFunction(bool_t en, bool_t include_radio /* = TRUE */)
{
	if (include_radio) m_radioAlternateFunction.EnableWindow(en);
	m_editAlternateFunction.EnableWindow(en);
}

void CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioBitsOfPrimitive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioBitsOfPrimitive.GetCheck())
	{
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);

		EnableBitsOfPrimitive(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioBytesOfPrimitive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioBytesOfPrimitive.GetCheck())
	{
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);

		EnableBytesOfPrimitive(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioAlternateFunction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioAlternateFunction.GetCheck())
	{
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);

		EnableAlternateFunction(TRUE, FALSE);
	}
}

void CDz1CodeGenTodecConfig2Dlg::OnBnClickedRadioDefaultMethod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_radioDefaultMethod.GetCheck())
	{
		EnableBytesOfPrimitive(FALSE, FALSE);
		EnableBitsOfPrimitive(FALSE, FALSE);
		EnableAlternateFunction(FALSE, FALSE);
	}
}

Dz1Error CDz1CodeGenTodecConfig2Dlg::GenInfo(ConstructMemberCodecLimitedInfo **dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecLimitedInfo *temp = NULL;
	if (m_radioBytesOfPrimitive.GetCheck())
	{
		if ((temp = ConstructMemberCodecLimitedInfo_new(ConstructMemberCodecLimitedInfoPresent_byte_of_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.byte_of_primitive = CodecPrimitiveByte_new(m_parent_entry, (u32_t)m_sldBytesOfPrimitiveLen.GetPos(), (u32_t)m_sldBytesOfPrimitiveSft.GetPos(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)dst);
		}
	}
	else if (m_radioBitsOfPrimitive.GetCheck())
	{
		if ((temp = ConstructMemberCodecLimitedInfo_new(ConstructMemberCodecLimitedInfoPresent_bits_of_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.bits_of_primitive = CodecPrimitiveBits_new(m_parent_entry, (u32_t)m_sldBitsOfPrimitiveLen.GetPos(), (u32_t)m_sldBitsOfPrimitiveSft.GetPos(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)dst);
		}
	}
	else if (m_radioAlternateFunction.GetCheck())
	{
		CString str;
		m_editAlternateFunction.GetWindowText(str);
		if (str.IsEmpty()) MessageBox(_T("Alternate Function") );
		else if ((temp = ConstructMemberCodecLimitedInfo_new(ConstructMemberCodecLimitedInfoPresent_bits_of_primitive, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)&temp);
			if ((temp->x.alternate = Dz1Str_dup(str.GetBuffer(), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (ConstructMemberCodecLimitedInfo_delAndSetNull, (void *)dst);
		}
	}
	else if (m_radioDefaultMethod.GetCheck())
	{
		Dz1Error_set(errp, 0);
	}
	(*dst) = temp;
	return err;
}

void CDz1CodeGenTodecConfig2Dlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	ConstructMemberCodecLimitedInfo *temp = NULL;
	if ((*errp = GenInfo(&temp)).code) ERR_DLG_OUT(errp);
	else
	{
		ConstructMemberCodecLimitedInfo_delAndSetNull(m_ret);
		(*m_ret) = temp;
		temp = NULL;
		Dz1Error_set(errp, 0);
		OnOK();
	}
}
