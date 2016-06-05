
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
#include "Gate.h"
#include <afxtempl.h>
#include "MainFrm.h"
#include "clock_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//This is test for git-hub

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
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_CHAR()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_FLOP_D_FF, &CLogicSim2View::OnFlopDFf)
ON_COMMAND(ID_FLOP_JK_FF, &CLogicSim2View::OnFlopJkFf)
ON_COMMAND(ID_FLOP_T_FF, &CLogicSim2View::OnFlopTFf)
ON_COMMAND(ID_INOUT_SWITCH, &CLogicSim2View::OnInoutSwitch)
ON_COMMAND(ID_Seven_seg, &CLogicSim2View::OnSevenSeg)
ON_COMMAND(ID_BIT_CLOCK, &CLogicSim2View::OnBitClock)
ON_WM_TIMER()
ON_COMMAND(ID_OUT_SWITCH, &CLogicSim2View::OnOutSwitch)
ON_WM_KEYDOWN()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CLogicSim2View construction/destruction

CLogicSim2View::CLogicSim2View()
	: start(0)
	, old(0)
	, move(false)
	, current(0)
	, gate(0)
	, lineDraw(false)
	, isClicked(false)
	, lineStart(0)
	, lineEnd(0)
{
	list.SetSize(0);
	line.SetSize(0);
	ptrlist.SetSize(0);
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
	m_point.SetSize(20000);
	CClientDC dc(this);
	CString str;

	for (int i = 10; i < rect.Width(); i += 10) {

		for (int j = 10; j < rect.Height(); j += 10) {
			pDC->SetPixelV(i, j, RGB(0, 0, 0));
			m_point.Add(CPoint(i, j));
		}
	}
	if (lineDraw == true && isClicked == true) {
		CPen myPen(PS_SOLID, 2, RGB(200, 200, 200));
		pDC->SelectObject(&myPen);
		pDC->MoveTo(lineStart);
		pDC->LineTo(lineEnd.x, lineStart.y);
		pDC->MoveTo(lineEnd.x, lineStart.y);
		pDC->LineTo(lineEnd);
	}
	str.Format(_T("%d"), ptrlist.GetCount());
	pDC->TextOutW(200, 200, str);
	for (int i = 0; i < ptrlist.GetCount(); i++) {
			Gate* temp = (Gate*)ptrlist.GetAt(i);
			temp->Draw(dc, temp->way);
			temp->Drawstr(dc, temp->way);
			if (temp->label!=_T("")) {
				dc.TextOutW(temp->point.x - 30, temp->point.y - 40, temp->label);
			}
			
	}
	if (!line.IsEmpty()) {
		for (int k = 0; k + 1 < line.GetCount(); k=k+2) {
			CPen myPen(PS_SOLID, 2, RGB(200, 100, 100));
			pDC->SelectObject(&myPen);
			pDC->MoveTo(line[k]);
			pDC->LineTo(line[k + 1].x, line[k].y);
			pDC->MoveTo(line[k + 1].x, line[k].y);
			pDC->LineTo(line[k + 1]);
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
	int x = point.x / 10;
	int y = point.y / 10;

	x = x * 10;
	y = y * 10;
	if (current!=-1 && move) {
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);
			if (gate == 0) {
				AND and (CPoint(start.x, start.y));
				and.Draw(dc, G_way);
				and.point.x += x - start.x;
				and.point.y += y-start.y;
				start.x = x;
				start.y = y;
				and.Draw(dc, G_way);
			}
		
			else if (gate == 1) {
				OR or (CPoint(start.x, start.y),G_way);
				or .Draw(dc, G_way);
				or .point.x += x - start.x;
				or .point.y += y - start.y;
				start.x = x;
				start.y = y;
				or .Draw(dc, G_way);
			}
			else if (gate == 2) {
				NOT not (CPoint(start.x, start.y));
				not.Draw(dc, G_way);
				not.point.x += x - start.x;
				not.point.y += y - start.y;
				start.x = x;
				start.y = y;
				not.Draw(dc, G_way);
			}
			else if (gate == 3) {
				NAND nand(CPoint(start.x, start.y), G_way);
				nand.Draw(dc, G_way);
				nand.point.x += x - start.x;
				nand.point.y += y - start.y;
				start.x = x;
				start.y = y;
				nand.Draw(dc, G_way);
			}
			else if (gate == 4) {
				NOR nor(CPoint(start.x, start.y), G_way);
				nor.Draw(dc, G_way);
				nor.point.x += x - start.x;
				nor.point.y += y - start.y;
				start.x = x;
				start.y = y;
				nor.Draw(dc, G_way);
			}
			else if (gate == 5) {
				XOR xor (CPoint(start.x, start.y), G_way);
				xor.Draw(dc, G_way);
				xor.point.x += x - start.x;
				xor.point.y += y - start.y;
				start.x = x;
				start.y = y;
				xor.Draw(dc, G_way);
			}
			else if (gate == 6) {
				D_FF d_ff(CPoint(start.x, start.y));
				d_ff.Draw(dc, G_way);
				d_ff.point.x += x - start.x;
				d_ff.point.y += y - start.y;
				start.x = x;
				start.y = y;
				d_ff.Draw(dc, G_way);
			}
			else if (gate == 7) {
				JK_FF jk_ff(CPoint(start.x, start.y));
				jk_ff.Draw(dc, G_way);
				jk_ff.point.x += x - start.x;
				jk_ff.point.y += y - start.y;
				start.x = x;
				start.y = y;
				jk_ff.Draw(dc, G_way);
			}
			else if (gate == 8) {
				T_FF t_ff(CPoint(start.x, start.y));
				t_ff.Draw(dc, G_way);
				t_ff.point.x += x - start.x;
				t_ff.point.y += y - start.y;
				start.x = x;
				start.y = y;
				t_ff.Draw(dc, G_way);
			}
			else if (gate == 9) {
				Bit_switch bit_switch(CPoint(start.x, start.y));
				bit_switch.Draw(dc, G_way);
				bit_switch.point.x += x - start.x;
				bit_switch.point.y += y - start.y;
				start.x = x;
				start.y = y;
				bit_switch.Draw(dc, G_way);
			}
			else if (gate == 10) {
				Seven_seg seven(CPoint(start.x, start.y));
				seven.Draw(dc, G_way);
				seven.point.x += x - start.x;
				seven.point.y += y - start.y;
				start.x = x;
				start.y = y;
				seven.Draw(dc, G_way);
			}
			else if (gate == 11) {
				Bit_clock clock(CPoint(start.x, start.y));
				clock.Draw(dc, G_way);
				clock.point.x += x - start.x;
				clock.point.y += y - start.y;
				start.x = x;
				start.y = y;
				clock.Draw(dc, G_way);
			}
			else if (gate == 12) {
				Out_switch out_switch(CPoint(start.x, start.y));
				out_switch.Draw(dc, G_way);
				out_switch.point.x += x - start.x;
				out_switch.point.y += y - start.y;
				start.x = x;
				start.y = y;
				out_switch.Draw(dc, G_way);
			}
	}
	lineEnd = CPoint(x, y);
	
	if (lineDraw) {
		Invalidate();
	}
		
	CView::OnMouseMove(nFlags, point);
}


void CLogicSim2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint temp;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CClientDC dc(this);

	for (int i = 0; i < list.GetCount(); i++) {
			temp = list[i].point;
		if (temp.x - 4 < point.x&&temp.x + 4 > point.x&&temp.y - 4 < point.y&&temp.y + 4 > point.y) {
			lineDraw = true;
			isClicked = true;
			lineStart = temp;
		}
		if (temp.x - 30 < point.x&&temp.x + 4 > point.x&&temp.y - 15 < point.y&&temp.y + 15 > point.y) {
			Gate* li=(Gate*)ptrlist.GetAt(i);
			pFrame->m_option->m_edit.SetWindowTextW(list[i].label);
			pFrame->m_option->SetDlgItemTextW(IDC_STATIC4, list[i].name);
			pFrame->m_option->temp = list[i];
			li->label = list[i].label;
			Invalidate();
		}
	}
	for (int i = 0; i < line.GetCount(); i++) {
		if (point.x-3< line[i].x && point.x+3>line[i].x && point.y-3<line[i].y && point.y+3> line[i].y) {
			lineDraw = true;
			isClicked = true;
			lineStart = line[i];
		}
	}

	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDown(nFlags, point);
}


void CLogicSim2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	int x = point.x / 10;
	int y = point.y / 10;
	static int i = 0;
	static int j = 0;
	x = x * 10;
	y = y * 10;
	// TODO: Add your message handler code here and/or call default
	if (current != -1) {
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);

		if (gate == 0) {
			AND *and = new AND(CPoint(x,y));
			and->Draw(dc, G_way);
			and->way = G_way;
			list.Add(*and);
			ptrlist.Add(and);
		}
		else if (gate == 1) {
			OR* or =new OR(CPoint(x, y), G_way);
			or ->Draw(dc, G_way);
			or->way = G_way;
			list.Add(*or );
			ptrlist.Add(or);
		}
		else if (gate == 2) {
			NOT* not= new NOT(CPoint(x, y));
			not->Draw(dc, G_way);
			not->way = G_way;
			list.Add(*not);
			ptrlist.Add(not);
		}
		else if (gate == 3) {
			NAND* nand = new NAND(CPoint(x, y), G_way);
			nand->Draw(dc, G_way);
			nand->way = G_way;
			list.Add(*nand);
			ptrlist.Add(nand);
		}
		else if (gate == 4) {
			NOR* nor = new NOR(CPoint(x, y), G_way);
			nor->Draw(dc, G_way);
			nor->way = G_way;
			list.Add(*nor);
			ptrlist.Add(nor);
			}
		else if (gate == 5) {
			XOR* xor = new XOR(CPoint(x, y), G_way);
			xor->Draw(dc, G_way);
			xor->way = G_way;
			list.Add(*xor);
			ptrlist.Add(xor);
			} 
		else if (gate == 6) {
			D_FF* d_ff = new D_FF(CPoint(x, y));
			d_ff->Draw(dc, G_way);
			d_ff->Drawstr(dc, G_way);
			d_ff->way = G_way;
			list.Add(*d_ff);
			ptrlist.Add(d_ff);
		}
		else if (gate == 7) {
			JK_FF* jk_ff=new JK_FF(CPoint(x, y));
			jk_ff->Draw(dc, G_way);
			jk_ff->Drawstr(dc, G_way);
			jk_ff->way = G_way;
			list.Add(*jk_ff);
			ptrlist.Add(jk_ff);
		}
		else if (gate == 8) {
			T_FF* t_ff=new T_FF(CPoint(x, y));
			t_ff->Draw(dc, G_way);
			t_ff->Drawstr(dc, G_way);
			t_ff->way = G_way;
			list.Add(*t_ff);
			ptrlist.Add(t_ff);
		}
		else if (gate == 9) {
			Bit_switch* bit_switch = new Bit_switch(CPoint(x, y));
			bit_switch->Draw(dc, G_way);
			bit_switch->Drawstr(dc, G_way);
			bit_switch->way = G_way;
			bit_switch->isbit = true;
			list.Add(*bit_switch);
			ptrlist.Add(bit_switch);
		}
		else if (gate == 10) {
			Seven_seg* seven = new Seven_seg(CPoint(x, y));
			seven->Draw(dc, G_way);
			seven->way = G_way;
			list.Add(*seven);
			ptrlist.Add(seven);
		}
		else if (gate == 11) {
			Bit_clock* clock = new Bit_clock(CPoint(x, y));
			clock->Draw(dc, G_way);
			clock->way = G_way;
			clock->isclock = true;
			list.Add(*clock);
			ptrlist.Add(clock);
		}
		else if (gate == 12) {
			Out_switch* out_switch = new Out_switch(CPoint(x, y));
			out_switch->Draw(dc, G_way);
			out_switch->Drawstr(dc, G_way);
			out_switch->way = G_way;
			out_switch->isbit = true;
			list.Add(*out_switch);
			ptrlist.Add(out_switch);
		}
		current = -1;
		move = false;
		gate = -1;
		start.x = 0;
		start.y = 0;
	}
	lineEnd = CPoint(x, y);
	if (lineDraw) {
		line.Add(lineStart);
		line.Add(lineEnd);
		lineDraw = false;
		Invalidate(FALSE);
	}

	if (isClicked==true) {
		CPen myPen(PS_SOLID, 2, RGB(200, 100, 100));
		dc.SelectObject(&myPen);
		dc.MoveTo(lineStart);
		dc.LineTo(lineEnd.x, lineStart.y);
		dc.MoveTo(lineEnd.x, lineStart.y);
		dc.LineTo(lineEnd);
		isClicked = false;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CLogicSim2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint temp;
	CClientDC dc(this);
	for (int i = 0; i < list.GetCount(); i++) {
		temp = list[i].point;
		if (temp.x - 30 < point.x&&temp.x + 4 > point.x&&temp.y - 15 < point.y&&temp.y + 15 > point.y) {
			if (list[i].isbit) {
				if (list[i].bit_flag)
					list[i].bit_flag = false;
				else
					list[i].bit_flag = true;
				list[i].Drawstr(dc, list[i].way);
			}
			else if (list[i].isclock) {
				if (list[i].start_clock) {
					list[i].start_clock = true;
					SetTimer(0, 1000 / list[i].clock, NULL);
				}
				else {
					list[i].start_clock = false;
					KillTimer(0);
				}
			}

		}
	}
	//Invalidate();
	CView::OnRButtonDown(nFlags, point);
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



void CLogicSim2View::OnFlopDFf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 6;
	current = 1;
	move = true;
}


void CLogicSim2View::OnFlopJkFf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 7;
	current = 1;
	move = true;
}


void CLogicSim2View::OnFlopTFf()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 8;
	current = 1;
	move = true;
}


void CLogicSim2View::OnInoutSwitch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 9;
	current = 1;
	move = true;
}


void CLogicSim2View::OnSevenSeg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 10;
	current = 1;
	move = true;
}


void CLogicSim2View::OnBitClock()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 11;
	current = 1;
	move = true;
}

void CLogicSim2View::OnOutSwitch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 12;
	current = 1;
	move = true;
}

void CLogicSim2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	for (int i = 0; i < list.GetCount(); i++) {
		if(list[i].isclock){
			if (list[i].bit_flag)
				list[i].bit_flag = false;
			else
				list[i].bit_flag = true;
			list[i].Drawstr(dc, list[i].way);
		}
	}

	//Invalidate();

	CView::OnTimer(nIDEvent);
}





void CLogicSim2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nChar) {
	case 'C':
		if (current != -1 && move) {
			if (G_way < 3) {
				G_way++;	//게이트방향 전환
			}
			else {
				G_way = 0;
			}
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLogicSim2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CPoint temp;

	for (int i = 0; i < list.GetCount(); i++) {
		temp = list[i].point;
		if (temp.x - 30 < point.x&&temp.x + 4 > point.x&&temp.y - 15 < point.y&&temp.y + 15 > point.y) {
			if (list[i].isclock) {
				clock_Dlg dlg;
				dlg.i = list[i].clock;

				int result = dlg.DoModal();
				if (result == IDOK) {
					list[i].clock = dlg.i;
				}
				//Invalidate();
			}
		}
	}
	Invalidate();

	CView::OnLButtonDblClk(nFlags, point);
}
