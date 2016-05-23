
// LogicSim2View.cpp : implementation of the CLogicSim2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LogicSim2.h"
#endif

#include "LogicSim2Doc.h"
#include "LogicSim2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogicSim2View

IMPLEMENT_DYNCREATE(CLogicSim2View, CView)

BEGIN_MESSAGE_MAP(CLogicSim2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLogicSim2View construction/destruction

CLogicSim2View::CLogicSim2View()
{
	// TODO: add construction code here

}

CLogicSim2View::~CLogicSim2View()
{
}

BOOL CLogicSim2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLogicSim2View drawing

void CLogicSim2View::OnDraw(CDC* /*pDC*/)
{
	CLogicSim2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLogicSim2View printing

BOOL CLogicSim2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLogicSim2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLogicSim2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLogicSim2View diagnostics

#ifdef _DEBUG
void CLogicSim2View::AssertValid() const
{
	CView::AssertValid();
}

void CLogicSim2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogicSim2Doc* CLogicSim2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogicSim2Doc)));
	return (CLogicSim2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLogicSim2View message handlers
