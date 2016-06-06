// Save_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "LogicSim2.h"
#include "Save_dlg.h"
#include "afxdialogex.h"


// Save_dlg dialog

IMPLEMENT_DYNAMIC(Save_dlg, CDialogEx)

Save_dlg::Save_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Save_dlg::~Save_dlg()
{
}

void Save_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Save_dlg, CDialogEx)
	ON_BN_CLICKED(ID_BACK, &Save_dlg::OnClickedBack)
END_MESSAGE_MAP()


// Save_dlg message handlers


void Save_dlg::OnClickedBack()
{
	// TODO: Add your control notification handler code here
	EndDialog(NULL);
}
