
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LogicSim2.h"
#include "MainFrm.h"
#include "LogicSim2View.h"
#include "Tree.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_GATETOOLBAR, &CMainFrame::OnViewGatetoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GATETOOLBAR, &CMainFrame::OnUpdateViewGatetoolbar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_bShowToolBar(FALSE)
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	if (!m_gateToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_gateToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create 
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_gateToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_gateToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnViewGatetoolbar()
{
	// TODO: Add your command handler code here
	if (m_bShowToolBar) {
		m_bShowToolBar = FALSE;
		ShowControlBar(&m_gateToolBar, FALSE, FALSE); // 숨기기
	}
	else {
		m_bShowToolBar = TRUE;
		ShowControlBar(&m_gateToolBar, TRUE, FALSE); // 보이기
	}

}


void CMainFrame::OnUpdateViewGatetoolbar(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL visible = m_gateToolBar.IsWindowVisible();
	if (visible) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);


}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(Tree), CSize(300, 300), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CLogicSim2View), CSize(300, 300), pContext);
	SetActiveView((CView*)m_wndSplitter.GetPane(0, 1));
	return TRUE;
}
