// OptionView.cpp : implementation file
//

#include "stdafx.h"
#include "LogicSim2.h"
#include "OptionView.h"
#include "MainFrm.h"

// OptionView

IMPLEMENT_DYNCREATE(OptionView, CFormView)

OptionView::OptionView()
	: CFormView(IDD_OPTIONVIEW)
{

}

OptionView::~OptionView()
{
}

void OptionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}

BEGIN_MESSAGE_MAP(OptionView, CFormView)
	ON_EN_CHANGE(IDC_EDIT1, &OptionView::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &OptionView::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// OptionView diagnostics

#ifdef _DEBUG
void OptionView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void OptionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// OptionView message handlers


void OptionView::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString str;
	m_edit.GetWindowText(str);
	temp.label = str;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	int count = pFrame->m_main->list.GetCount();
	for (int i = 0; i < count; i++) {
		if (temp.point == pFrame->m_main->list[i].point) {
			pFrame->m_main->list[i].label = temp.label;
		}
	}
}


void OptionView::OnCbnSelchangeCombo1()
{

	// TODO: Add your control notification handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	int nIndex = m_combo.GetCurSel();
	if (nIndex != CB_ERR) {
		CString str;
		m_combo.GetLBText(nIndex, str);
	}
	int count = pFrame->m_main->list.GetCount();
	for (int i = 0; i < count; i++) {
		if (temp.point == pFrame->m_main->list[i].point) {
		//	pFrame->m_main->list[i].g
		}
	}
}


void OptionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_combo.AddString(_T("µ¿"));
	m_combo.AddString(_T("¼­"));
	m_combo.AddString(_T("³²"));
	m_combo.AddString(_T("ºÏ"));
	m_combo.SetMinVisibleItems(10);
	// TODO: Add your specialized code here and/or call the base class
}
