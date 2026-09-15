#pragma once


// CDz1CodeGenTodecConfig2Dlg 대화 상자입니다.
#include "Dz1CodeGenTodecUtil.h"

class CDz1CodeGenTodecConfig2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CDz1CodeGenTodecConfig2Dlg)

public:
	CDz1CodeGenTodecConfig2Dlg(ConstructMemberCodecLimitedInfo **ret, ConstructMemberCodecEntry *parent_entry, ObjectInfo *target_obj, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDz1CodeGenTodecConfig2Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TODEC_CONFIG2_DLG };

private:
	CButton									 m_radioBitsOfPrimitive;
	CSliderCtrl								 m_sldBitsOfPrimitiveLen;
	CSliderCtrl								 m_sldBitsOfPrimitiveSft;
	void									 EnableBitsOfPrimitive(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioBytesOfPrimitive;
	CSliderCtrl								 m_sldBytesOfPrimitiveLen;
	CSliderCtrl								 m_sldBytesOfPrimitiveSft;
	void									 EnableBytesOfPrimitive(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioAlternateFunction;
	CEdit									 m_editAlternateFunction;
	void									 EnableAlternateFunction(bool_t en, bool_t include_radio = TRUE);

	CButton									 m_radioDefaultMethod;

	ConstructMemberCodecEntry				*m_parent_entry;
	ConstructMemberCodecLimitedInfo			**m_ret;
	ConstructMemberCodecLimitedInfo			*m_dst;

	Dz1Error								 GenInfo(ConstructMemberCodecLimitedInfo **dst);

	ObjectInfo								*m_target_obj;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioBitsOfPrimitive();
	afx_msg void OnBnClickedRadioBytesOfPrimitive();
	afx_msg void OnBnClickedRadioAlternateFunction();
	afx_msg void OnBnClickedRadioDefaultMethod();
	afx_msg void OnBnClickedButtonOk();
};
