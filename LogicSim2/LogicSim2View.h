
// LogicSim2View.h : interface of the CLogicSim2View class
//

#pragma once
#include "afxtempl.h"
#include "atltypes.h"
#include "Gate.h"
#include "LogicSim2Doc.h"

class CLogicSim2View : public CView
{
protected: // create from serialization only
	CLogicSim2View();
	DECLARE_DYNCREATE(CLogicSim2View)

// Attributes
public:
	 CLogicSim2Doc* GetDocument() const;

// Operations
public:
	double G_way = 0.0;	//게이트 방향을 결정하는 변수

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLogicSim2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CList<CPoint, CPoint> *m_point;
	CPoint start;
	CPoint old;
	bool move;
	int current;
	CArray<Gate, Gate> list;
	CPtrArray ptrlist;
	int gate;
	bool flag=false;
	double pre;
	CArray<CPoint, CPoint> line;
	bool lineDraw;
	bool isClicked;
	CPoint lineStart;
	CPoint lineEnd;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGateAnd();
	afx_msg void OnGateOr();
	afx_msg void OnGateNot();
	afx_msg void OnGateNand();
	afx_msg void OnGateNor();
	afx_msg void OnGateXor();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFlopDFf();
	afx_msg void OnFlopJkFf();
	afx_msg void OnFlopTFf();
	afx_msg void OnInoutSwitch();
	afx_msg void OnSevenSeg();
	afx_msg void OnBitClock();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOutSwitch();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
};

#ifndef _DEBUG  // debug version in LogicSim2View.cpp
inline CLogicSim2Doc* CLogicSim2View::GetDocument() const
   { return reinterpret_cast<CLogicSim2Doc*>(m_pDocument); }
#endif

