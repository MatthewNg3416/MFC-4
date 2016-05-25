
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
//This is test for git-hub
struct AND {
		CPoint point;
		AND(){
			point=CPoint(0,0);
		}
		AND(CPoint &point) {
			this->point = point;
		}
		void Draw(CClientDC &dc) {
			dc.MoveTo(point.x - 30, point.y + 30);
			dc.AngleArc(point.x - 30, point.y, 30, 270, 180);
			dc.LineTo(point.x - 60, point.y - 30);
			dc.LineTo(point.x - 60, point.y + 30);
			dc.LineTo(point.x - 30, point.y + 30);
		}
	};

	struct NOT {
		CPoint point;
		NOT(CPoint &point) {
			this->point = point;
		}
		void Draw(CClientDC &dc) {
			dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
			dc.MoveTo(point.x - 10, point.y);
			dc.LineTo(point.x - 30, point.y - 10);
			dc.LineTo(point.x - 30, point.y + 10);
			dc.LineTo(point.x - 10, point.y);
		}
	};

	struct OR {
		CPoint point;
		CPoint arr[3][4];
		OR(CPoint &point) {
			this->point = point;
			
			arr[0][0].x = point.x;
			arr[0][0].y = point.y;
			arr[0][1].x = point.x - 10;
			arr[0][1].y = point.y - 10;
			arr[0][2].x = point.x - 30;
			arr[0][2].y = point.y - 20;
			arr[0][3].x = point.x - 60;
			arr[0][3].y = point.y - 30;

			arr[1][0].x = point.x;
			arr[1][0].y = point.y;
			arr[1][1].x = point.x - 10;
			arr[1][1].y = point.y + 10;
			arr[1][2].x = point.x - 30;
			arr[1][2].y = point.y + 20;
			arr[1][3].x = point.x - 60;
			arr[1][3].y = point.y + 30;

			arr[2][0].x = point.x - 60;
			arr[2][0].y = point.y - 30;
			arr[2][1].x = point.x - 40;
			arr[2][1].y = point.y - 20;
			arr[2][2].x = point.x - 40;
			arr[2][2].y = point.y + 20;
			arr[2][3].x = point.x - 60;
			arr[2][3].y = point.y + 30;
		}
		void Draw(CClientDC &dc) {
			for (int i = 0; i < 3; i++) {
				dc.PolyBezier(arr[i], 4);
			}
		}
	};
	
	struct NAND {
		AND *and;
		CPoint point;

		NAND(CPoint &point) {
			CPoint temp = point - CPoint(10, 0);
			and=new AND(temp);
			this->point = point;
		}
		void Draw(CClientDC &dc) {
			dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
			and->Draw(dc);
		}
	};

	struct NOR {
		OR *or;
		CPoint point;

		NOR(CPoint &point) {
			CPoint temp = point - CPoint(10, 0);
			or = new OR(temp);
			this->point = point;
		}
		void Draw(CClientDC &dc) {
			dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
			or->Draw(dc);
		}
	};
	
	struct XOR{
		OR * or;
		CPoint point;
		CPoint arr[4];

		XOR(CPoint &point){
			or = new OR(point);
			this->point = point;
			arr[0].x = point.x - 70;
			arr[0].y = point.y - 30;
			arr[1].x = point.x - 50;
			arr[1].y = point.y - 20;
			arr[2].x = point.x - 50;
			arr[2].y = point.y + 20;
			arr[3].x = point.x - 70;
			arr[3].y = point.y + 30;
		}
		void Draw(CClientDC &dc) {
			or ->Draw(dc);
			dc.PolyBezier(arr, 4);
		}
	};
// CLogicSim2View

IMPLEMENT_DYNCREATE(CLogicSim2View, CView)

BEGIN_MESSAGE_MAP(CLogicSim2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_GATE_AND, &CLogicSim2View::OnGateAnd)
	ON_COMMAND(ID_GATE_OR, &CLogicSim2View::OnGateOr)
	ON_COMMAND(ID_GATE_NOT, &CLogicSim2View::OnGateNot)
	ON_COMMAND(ID_GATE_NAND, &CLogicSim2View::OnGateNand)
	ON_COMMAND(ID_GATE_NOR, &CLogicSim2View::OnGateNor)
	ON_COMMAND(ID_GATE_XOR, &CLogicSim2View::OnGateXor)
END_MESSAGE_MAP()

// CLogicSim2View construction/destruction

CLogicSim2View::CLogicSim2View()
	: start(0)
	, old(0)
	, move(false)
	, current(0)
	, gate(0)
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

void CLogicSim2View::OnDraw(CDC* pDC)
{
	CLogicSim2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rect;
	GetWindowRect(&rect);
	m_point.SetSize(0);
	for (int i = 10; i < rect.Width(); i += 10) {

		for (int j = 10; j < rect.Height(); j += 10) {
			pDC->SetPixelV(i, j, RGB(0, 0, 0));
			m_point.Add(CPoint(i, j));
		}
	}
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


void CLogicSim2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	
	if (current!=-1 && move) {
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
			if (gate == 0) {
				AND and (CPoint(start.x, start.y));
				and.Draw(dc);
				and.point.x += point.x - start.x;
				and.point.y += point.y - start.y;
				start.x = point.x;
				start.y = point.y;
				and.Draw(dc);
			}
		
			else if (gate == 1) {
				OR or (CPoint(start.x, start.y));
				or .Draw(dc);
				or .point.x += point.x - start.x;
				or .point.y += point.y - start.y;
				start.x = point.x;
				start.y = point.y;
				or .Draw(dc);
			}
			else if (gate == 2) {
				NOT not (CPoint(start.x, start.y));
				not.Draw(dc);
				not.point.x += point.x - start.x;
				not.point.y += point.y - start.y;
				start.x = point.x;
				start.y = point.y;
				not.Draw(dc);
			}
			else if (gate == 3) {
				NAND nand(CPoint(start.x, start.y));
				nand.Draw(dc);
				nand.point.x += point.x - start.x;
				nand.point.y += point.y - start.y;
				start.x = point.x;
				start.y = point.y;
				nand.Draw(dc);
			}
			else if (gate == 4) {
				NOR nor(CPoint(start.x, start.y));
				nor.Draw(dc);
				nor.point.x += point.x - start.x;
				nor.point.y += point.y - start.y;
				start.x = point.x;
				start.y = point.y;
				nor.Draw(dc);
			}
			else if (gate == 5) {
			XOR xor (CPoint(start.x, start.y));
			xor.Draw(dc);
			xor.point.x += point.x - start.x;
			xor.point.y += point.y - start.y;
			start.x = point.x;
			start.y = point.y;
			xor.Draw(dc);
			}
	}

	CView::OnMouseMove(nFlags, point);
}


void CLogicSim2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}


void CLogicSim2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (current != -1) {
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);

		if (gate == 0) {
			AND and (point);
			and.Draw(dc);
		}
		else if (gate == 1) {
			OR or (point);
			or .Draw(dc);
		}
		else if (gate == 2) {
			NOT not(point);
			not.Draw(dc);
		}
		else if (gate == 3) {
				NAND nand(point);
				nand.Draw(dc);
		}
		else if (gate == 4) {
				NOR nor(point);
				nor.Draw(dc);
			}
		else if (gate == 5) {
			XOR xor (point);
			xor.Draw(dc);
			} 
		current = -1;
		move = false;
		gate = -1;
		start.x = 0;
		start.y = 0;
	}
	CView::OnLButtonUp(nFlags, point);
}


int CLogicSim2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	current = 1;
	move =true;
	gate = -1;
	return 0;
}


void CLogicSim2View::OnGateAnd()
{
	// TODO: Add your command handler code here
	gate = 0;
	current = 1;
	move = true;
}


void CLogicSim2View::OnGateOr()
{
	// TODO: Add your command handler code here
	gate = 1;
	current = 1;
	move = true;
}


void CLogicSim2View::OnGateNot()
{
	// TODO: Add your command handler code here
	gate = 2;
	current = 1;
	move = true;
}


void CLogicSim2View::OnGateNand()
{
	// TODO: Add your command handler code here
	gate = 3;
	current = 1;
	move = true;
}


void CLogicSim2View::OnGateNor()
{
	// TODO: Add your command handler code here
	gate = 4;
	current = 1;
	move = true;
}


void CLogicSim2View::OnGateXor()
{
	// TODO: Add your command handler code here
	gate = 5;
	current = 1;
	move = true;
}
