#pragma once


// clock_Dlg ��ȭ �����Դϴ�.

class clock_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(clock_Dlg)

public:
	clock_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~clock_Dlg();
	CString str;
	int i;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};