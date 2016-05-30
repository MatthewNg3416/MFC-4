// OptionView.cpp : implementation file
//

#include "stdafx.h"
#include "LogicSim2.h"
#include "OptionView.h"


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
}

BEGIN_MESSAGE_MAP(OptionView, CFormView)
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
