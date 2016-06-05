// clock_Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "LogicSim2.h"
#include "clock_Dlg.h"
#include "afxdialogex.h"


// clock_Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(clock_Dlg, CDialogEx)

clock_Dlg::clock_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

clock_Dlg::~clock_Dlg()
{
}

void clock_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(clock_Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &clock_Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// clock_Dlg 메시지 처리기입니다.


void clock_Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void clock_Dlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItemText(IDC_EDIT1, str);
	i = _ttoi(str);

	CDialogEx::OnOK();
}


BOOL clock_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	str.Format(_T("%d"), i);
	SetDlgItemText(IDC_EDIT1, str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
