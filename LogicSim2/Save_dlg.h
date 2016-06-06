#pragma once


// Save_dlg dialog

class Save_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Save_dlg)

public:
	Save_dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Save_dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBack();
};
