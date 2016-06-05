#pragma once


// clock_Dlg 대화 상자입니다.

class clock_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(clock_Dlg)

public:
	clock_Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~clock_Dlg();
	CString str;
	int i;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
