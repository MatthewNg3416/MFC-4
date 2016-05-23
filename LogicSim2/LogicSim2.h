
// LogicSim2.h : main header file for the LogicSim2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLogicSim2App:
// See LogicSim2.cpp for the implementation of this class
//

class CLogicSim2App : public CWinApp
{
public:
	CLogicSim2App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLogicSim2App theApp;
