#pragma once
#include "Dz1CodeGenTodecHelper.h"

// CDz1CodeGenTodecConfigDlg 대화 상자입니다.

class CDz1CodeGenTodecConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTodecConfigDlg)

public:
	CDz1CodeGenTodecConfigDlg(ConstructMemberCodecInfo **ret,
							  ConstructMemberCodecEntry *parent_entry,
							  ObjectInfo *parent_obj,
							  Dz1Str instance_name, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTodecConfigDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TODEC_CONFIG_DLG };
private:
	CButton									 m_radioOneOfStruct;
	CComboTdcInfoStructMembers				 m_comboOneOfStruct;

	CEdit									 m_editOneOfStruct;
	ConstructMemberCodecLimitedInfo			*m_one_of_struct_info;
	void									 LoadOneOfStructMethod(void);

	CButton									 m_btnOneOfStruct;
	void									 EnableOneOfStructure(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioBitsOfPrimitive;
	CSliderCtrl								 m_sldBitsOfPrimitiveLen;
	CSliderCtrl								 m_sldBitsOfPrimitiveSft;
	void									 EnableBitsOfPrimitive(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioBytesOfPrimitive;
	CSliderCtrl								 m_sldBytesOfPrimitiveLen;
	CSliderCtrl								 m_sldBytesOfPrimitiveSft;
	void									 EnableBytesOfPrimitive(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioVoidMember;

	CButton									 m_radioAlternateFunction;
	CEdit									 m_editAlternateFunction;
	void									 EnableAlternateFunction(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioDefaultMethod;

	ConstructMemberCodecInfo				**m_ret;
	ConstructMemberCodecInfo				*m_dst;

	ConstructMemberCodecEntry				*m_parent_entry;
	ObjectInfo								*m_target_obj;
	ObjectInfo								*m_parent_obj;
	Dz1Str									 m_instance_name;

	Dz1Error								 GenerateInfo(ConstructMemberCodecInfo **temp);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioOneMemberOfStructure();
	afx_msg void OnBnClickedRadioSubBitsOfPrimitive();
	afx_msg void OnBnClickedRadioSubBytesOfPrimitive();
	afx_msg void OnBnClickedRadioInhivitMember();
	afx_msg void OnBnClickedRadioUseAlternativeFunction();
	afx_msg void OnBnClickedRadioDefaultMethod();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonOneMemberOfStructure();
};
