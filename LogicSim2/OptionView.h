#pragma once
#include "afxwin.h"
#include "Gate.h"


// OptionView form view

class OptionView : public CFormView
{
	DECLARE_DYNCREATE(OptionView)

protected:
	OptionView();           // protected constructor used by dynamic creation
	virtual ~OptionView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_edit;
	Gate temp;
	afx_msg void OnCbnSelchangeCombo1();
	virtual void OnInitialUpdate();
	CComboBox m_combo;
};


