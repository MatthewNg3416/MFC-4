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
}

BEGIN_MESSAGE_MAP(OptionView, CFormView)
	ON_EN_CHANGE(IDC_EDIT1, &OptionView::OnEnChangeEdit1)
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
	
	CString str = NULL;
	m_edit.GetWindowTextW(str);
	temp.label.SetString(str);
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	Gate *te;
	int count = pFrame->m_main->ptrlist.GetCount();

	for (int i = 0; i < count; i++) {
		 te= (Gate*)pFrame->m_main->ptrlist.GetAt(i);
		if (temp.point == te->point) {
			te->label.SetString(temp.label);
			}
		};
}