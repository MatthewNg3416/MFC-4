
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
#include "Save_dlg.h"

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
	ON_COMMAND(ID_FILE_SAVE, &CLogicSim2View::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CLogicSim2View::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CLogicSim2View::OnFileNew)
END_MESSAGE_MAP()

// CLogicSim2View construction/destruction
CPtrArray lines;

BOOL IsConnected(Gate& first, Gate& second, CPtrArray& lines) {
	for (int i = 0; i < lines.GetCount(); i++) {
		CList<CPoint, CPoint>* temp = (CList<CPoint, CPoint>*)lines.GetAt(i);
		for (int j = 0; j < 7; j++) {
			if (first.output[j] == temp->GetHead()) {
				for (int k = 0; k < 7; k++) {
					if (second.input[k] == temp->GetTail())
						second.input_value[k] = first.output_value[j];
						return TRUE;
				}
			}
			if (second.input[j] == temp->GetHead()) {
				for (int k = 0; k < 7; k++) {
					if (first.output[k] == temp->GetTail())
						second.input_value[j] = first.output_value[k];
						return TRUE;
				}
			}
		}
	}
	return false;
}
template <typename T>
void MoveGate(T& gate,CClientDC& dc,CPoint& start,int x, int y,bool& flag,double& pre,double& G_way,CPoint& point) 
{
	if (flag) {
		gate.c_flag = true;
		gate.Draw(dc, pre);
		gate.Draw(dc, G_way);
		flag = false;
		gate.c_flag = false;
	}
	gate.Draw(dc, G_way);
	gate.point.x += x - start.x;
	gate.point.y += y - start.y;
	start.x = x;
	start.y = y;
	gate.Draw(dc, G_way);
}

template<typename T>
void CreateGate(T& gate, CClientDC& dc,double& G_way,CPtrArray& ptrlist) 
{
	gate->Draw(dc, G_way);
	gate->way = G_way;
	gate->isbit = true;
	gate->isclock = true;
	ptrlist.Add(gate);
}

template<typename T>
void File(T& gate, CPtrArray& ptrlist,int& t_way,CString& t_label) {
	gate->way = t_way;
	gate->label = t_label;
	ptrlist.Add(gate);
}
CLogicSim2View::CLogicSim2View()
	: start(0),
	move(false)
	, current(0)
	, gate(0)
	, lineDraw(false)
	, isClicked(false)
	, lineStart(0)
	, lineEnd(0)
	, flag(false)
	, pre(-1)
{
	line.SetSize(0);
	ptrlist.SetSize(0);
	lines.SetSize(0);
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
	CClientDC dc(this);
	
	for (int i = 10; i < rect.Width(); i += 10) {

		for (int j = 10; j < rect.Height(); j += 10) {
			pDC->SetPixelV(i, j, RGB(0, 0, 0));
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
	for (int i = 0; i < ptrlist.GetCount(); i++) {
			Gate* temp = (Gate*)ptrlist.GetAt(i);
			temp->Draw(dc, temp->way);
			temp->Drawstr(dc, temp->way);
			if (!(temp->label.IsEmpty())) {
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
	Gate *gate_t;
	CRect rect;
	GetWindowRect(&rect);
	x = x * 10;
	y = y * 10;
	if (point.x < rect.Width() - 80 && point.y - 80 < rect.Height() && point.x > 60 && point.y>60) {
		if (current != -1 && move) {
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);
			if (gate == 0) {
				gate_t = new AND(CPoint(start.x, start.y), G_way);
			}
			else if (gate == 1) {
				gate_t = new OR(CPoint(start.x, start.y), G_way);
			}
			else if (gate == 2) {
				gate_t = new NOT(CPoint(start.x, start.y));
			}
			else if (gate == 3) {
				gate_t = new NAND(CPoint(start.x, start.y), G_way);
			}
			else if (gate == 4) {
				gate_t = new NOR(CPoint(start.x, start.y), G_way);
			}
			else if (gate == 5) {
				gate_t = new XOR(CPoint(start.x, start.y), G_way);
			}
			else if (gate == 6) {
				gate_t = new D_FF(CPoint(start.x, start.y));
			}
			else if (gate == 7) {
				gate_t = new JK_FF(CPoint(start.x, start.y));
			}
			else if (gate == 8) {
				gate_t = new T_FF(CPoint(start.x, start.y));
			}
			else if (gate == 9) {
				gate_t = new Bit_switch(CPoint(start.x, start.y));
			}
			else if (gate == 11) {
				gate_t = new Seven_seg(CPoint(start.x, start.y));
			}
			else if (gate == 12) {
				gate_t = new Bit_clock(CPoint(start.x, start.y));
			}
			else if (gate == 10) {
				gate_t = new Out_switch(CPoint(start.x, start.y));
			}
			if (gate != -1)
				MoveGate(*gate_t, dc, start, x, y, flag, pre, G_way, point);
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
	Gate *ptr=NULL;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CClientDC dc(this);

	for (int i = 0; i < ptrlist.GetCount(); i++) {
			ptr = (Gate*)ptrlist.GetAt(i);			
			for (int j = 0; j < 7; j++) {
				if (ptr->input[j].x - 4 < point.x&&ptr->input[j].x + 4 > point.x&&ptr->input[j].y - 4 < point.y&&ptr->input[j].y + 4 > point.y) {
					lineDraw = true;
					isClicked = true;
					lineStart = ptr->input[j];
				}
				if (ptr->output[j].x - 4 < point.x&&ptr->output[j].x + 4 > point.x&&ptr->output[j].y - 4 < point.y&&ptr->output[j].y + 4 > point.y) {
					lineDraw = true;
					isClicked = true;
					lineStart = ptr->output[j];
				}

			}
						
		if (ptr->point.x - 30 < point.x && ptr->point.x + 4 > point.x && ptr->point.y - 15 < point.y && ptr->point.y + 15 > point.y) {
			pFrame->m_option->SetDlgItemTextW(IDC_STATIC4, ptr->name);
			pFrame->m_option->temp = *ptr;
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
	x = x * 10;
	y = y * 10;
	Gate* gate_t;
	CRect rect;
	GetWindowRect(&rect);
	// TODO: Add your message handler code here and/or call default
	if (current != -1) {
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);
		if (point.x < rect.Width()-80 && point.y-80 < rect.Height() && point.x>60 && point.y>60) {
			if (gate == 0) {
				gate_t = new AND(CPoint(x, y), G_way);
			}
			else if (gate == 1) {
				gate_t = new OR(CPoint(x, y), G_way);
			}
			else if (gate == 2) {
				gate_t = new NOT(CPoint(x, y));
			}
			else if (gate == 3) {
				gate_t = new NAND(CPoint(x, y), G_way);
			}
			else if (gate == 4) {
				gate_t = new NOR(CPoint(x, y), G_way);
			}
			else if (gate == 5) {
				gate_t = new XOR(CPoint(x, y), G_way);
			}
			else if (gate == 6) {
				gate_t = new D_FF(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			else if (gate == 7) {
				gate_t = new JK_FF(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			else if (gate == 8) {
				gate_t = new T_FF(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			else if (gate == 9) {
				gate_t = new Bit_switch(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			else if (gate == 11) {
				gate_t = new Seven_seg(CPoint(x, y));
			}
			else if (gate == 12) {
				gate_t = new Bit_clock(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			else if (gate == 10) {
				gate_t = new Out_switch(CPoint(x, y));
				gate_t->Drawstr(dc, G_way);
			}
			if (gate != -1)
				CreateGate(gate_t, dc, G_way, ptrlist);
			current = -1;
			move = false;
			gate = -1;
			start.x = 0;
			start.y = 0;
			undo_num.AddTail(0);
		}
	}
	lineEnd = CPoint(x, y);
	if (lineDraw) {
		line.Add(lineStart);
		line.Add(lineEnd);
		lineDraw = false;
		m_point = new CList<CPoint, CPoint>();
		m_point->AddTail(lineStart);
		if (lineStart.x != lineEnd.x && lineStart.y != lineEnd.y) {
			m_point->AddTail(CPoint(lineEnd.x, lineStart.y));
		}
		m_point->AddTail(lineEnd);
		lines.Add(m_point);
		Invalidate(FALSE);
		undo_num.AddTail(1);
	}

	CView::OnLButtonUp(nFlags, point);
}

void CLogicSim2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint temp_p;
	CClientDC dc(this);

	for (int i = 0; i < ptrlist.GetCount(); i++) {
		Gate* temp = (Gate*)ptrlist.GetAt(i);
		temp_p = temp->point;
		if (temp_p.x - 30 < point.x&&temp_p.x + 4 > point.x&&temp_p.y - 15 < point.y&&temp_p.y + 15 > point.y) {
			if (temp->isbit) {
				if (temp->bit_flag)
					temp->bit_flag = false;
				else
					temp->bit_flag = true;
				temp->Drawstr(dc, temp->way);
			}
			else if (temp->isclock) {
				if (!temp->start_clock) {
					temp->start_clock = true;
					SetTimer(0, (1000 / temp->clock), NULL);
				}
				else {
					temp->start_clock = false;
					KillTimer(0);
				}
			}

		}
	}
	//Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

void CLogicSim2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Gate *temp;

	for (int i = 0; i < ptrlist.GetCount(); i++) {
		temp = (Gate*)ptrlist.GetAt(i);
		if (temp->point.x - 30 < point.x && temp->point.x + 4 > point.x&& temp->point.y - 15 < point.y && temp->point.y + 15 > point.y) {
			if (temp->isclock) {
				clock_Dlg dlg;
				dlg.i = temp->clock;

				int result = dlg.DoModal();
				if (result == IDOK) {
					temp->clock = dlg.i;
				}
				//Invalidate();
			}
		}
	}
	Invalidate();

	CView::OnLButtonDblClk(nFlags, point);
}

void CLogicSim2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int i;
	switch (nChar) {
	case 'C':
		if (current != -1 && move) {
			flag = true;
			pre = G_way;
			if (G_way < 3) {
				G_way++;	//게이트방향 전환
			}
			else {
				G_way = 0;
			}
		}
		break;
	case 'Z':
		if (undo_num.GetCount() == 0) {
			break;
		}
		i = undo_num.GetTail();
		redo_num.AddTail(i);
		undo_num.RemoveTail();
		if (i == 0) {
			i = ptrlist.GetCount();
			redo_ptrlist.Add(ptrlist.GetAt(i - 1));
			ptrlist.RemoveAt(i-1);
		}
		else if (i == 1) {
			i = line.GetCount();
			redo_line.Add(line.GetAt(i - 2));
			redo_line.Add(line.GetAt(i - 1));
			line.RemoveAt(i - 1);
			line.RemoveAt(i - 2);
		}
		else {
			;
		}
		Invalidate();
		break;
	case 'X':
		if (redo_num.GetCount() == 0) {
			break;
		}
		i = redo_num.GetTail();
		undo_num.AddTail(i);
		redo_num.RemoveTail();
		if (i == 0) {
			i = redo_ptrlist.GetCount();
			ptrlist.Add(redo_ptrlist.GetAt(i - 1));
			redo_ptrlist.RemoveAt(i - 1);
		}
		else if (i == 1) {
			i = redo_line.GetCount();
			line.Add(redo_line.GetAt(i - 2));
			line.Add(redo_line.GetAt(i - 1));
			redo_line.RemoveAt(i - 1);
			redo_line.RemoveAt(i - 2);
		}
		else {
			;
		}
		Invalidate();
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CLogicSim2View::OnFileNew()
{
	// TODO: Add your command handler code here

	Save_dlg dlg;

	int result = dlg.DoModal();

	if (result == IDOK) {
		OnFileSave();
		ptrlist.RemoveAll();
		line.RemoveAll();

		Invalidate();
	}
	else if (result == IDCANCEL) {
		ptrlist.RemoveAll();
		line.RemoveAll();

		Invalidate();
	}
	else {
		;
	}

}

void CLogicSim2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	for (int i = 0; i < ptrlist.GetCount(); i++) {
		Gate* temp = (Gate*)ptrlist.GetAt(i);
		if(temp->isclock){
			if (temp->bit_flag)
				temp->bit_flag = false;
			else
				temp->bit_flag = true;
			temp->Drawstr(dc, temp->way);
		}
	}
	//Invalidate();

	CView::OnTimer(nIDEvent);
}

void CLogicSim2View::OnFileSave()
{
	// TODO: Add your command handler code here

	CFileDialog dlg(FALSE, _T("logic"), NULL, OFN_HIDEREADONLY, NULL);
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();

		CFile fp;
		CFileException e;
		if (!fp.Open(strPathName, CFile::modeWrite | CFile::modeCreate, &e)) {
			e.ReportError();
			return;
		}

		CArchive ar(&fp, CArchive::store);

		int i = ptrlist.GetCount();

		ar << i;

		for (i = 0; i < ptrlist.GetCount(); i++) {
			Gate* temp = (Gate*)ptrlist.GetAt(i);
			ar << temp->name;
			ar << temp->point;
			ar << temp->way;
			ar << temp->label;
		}

		i = line.GetCount();

		ar << i;

		for (i = 0; i < line.GetCount(); i++) {
			CPoint temp = line[i];
			ar << temp;
		}
	}
}

void CLogicSim2View::OnFileOpen()
{
	// TODO: Add your command handler code here

	//CFileDialog dlg(TRUE, _T("logic"), _T(""), OFN_HIDEREADONLY, _T("(*.logic) | All Files(*.*)|*.*||"));
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);
	Gate * gate_t;
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		CFile fp;
		CFileException e;
		if (!fp.Open(strPathName, CFile::modeRead, &e)) {
			e.ReportError();
			return;
		}

		CArchive ar(&fp, CArchive::load);

		int i;
		CString t_name;
		CPoint t_point;
		int t_way;
		CString t_label;

		ptrlist.RemoveAll();

		ar >> i;

		for (int j = 0; j < i; j++) {
			ar >> t_name;
			ar >> t_point;
			ar >> t_way;
			ar >> t_label;

			if ((t_name.Compare(_T("AND"))) == 0) {
				gate_t = new AND(t_point, t_way);
			}
			else if ((t_name.Compare(_T("OR"))) == 0) {
				gate_t = new OR(t_point, t_way);
			}
			else if ((t_name.Compare(_T("NOT"))) == 0) {
				gate_t = new NOT(t_point);
			}
			else if ((t_name.Compare(_T("NAND"))) == 0) {
				gate_t = new NAND(t_point, t_way);
			}
			else if ((t_name.Compare(_T("NOR"))) == 0) {
				gate_t = new NOR(t_point, t_way);
			}
			else if ((t_name.Compare(_T("XOR"))) == 0) {
				gate_t = new XOR(t_point, t_way);
			}
			else if ((t_name.Compare(_T("D_FF"))) == 0) {
				gate_t = new D_FF(t_point);
			}
			else if ((t_name.Compare(_T("JK_FF"))) == 0) {
				gate_t = new JK_FF(t_point);
			}
			else if ((t_name.Compare(_T("T_FF"))) == 0) {
				gate_t = new T_FF(t_point);
			}
			else if ((t_name.Compare(_T("SWITCH"))) == 0) {
				gate_t = new Bit_switch(t_point);
				gate_t->isbit = true;
			}
			else if ((t_name.Compare(_T("7-SEGMENT"))) == 0) {
				gate_t = new Seven_seg(t_point);
			}
			else if ((t_name.Compare(_T("CLOCK"))) == 0) {
				gate_t = new Bit_clock(t_point);
				gate_t->isclock = true;
			}
			else if ((t_name.Compare(_T("LAMP"))) == 0) {
				gate_t = new Out_switch(t_point);
				gate_t->isbit = true;
			}
			File(gate_t, ptrlist, t_way, t_label);
		}

		ar >> i;

		line.RemoveAll();
		CPoint temp;
		for (int k = 0; k < i; k++) {
			ar >> temp;
			line.Add(temp);
		}
	}
	Invalidate();
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

	gate = 11;
	current = 1;
	move = true;
}

void CLogicSim2View::OnBitClock()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 12;
	current = 1;
	move = true;
}

void CLogicSim2View::OnOutSwitch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	gate = 10;
	current = 1;
	move = true;
}
