
// LogicSim2View.h : interface of the CLogicSim2View class
//

#pragma once
#include "afxtempl.h"
#include "atltypes.h"


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
	CArray<CPoint, CPoint&> m_point;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint start;
	CPoint old;
	bool move;
	int current;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int gate;
	afx_msg void OnGateAnd();
	afx_msg void OnGateOr();
	afx_msg void OnGateNot();
	afx_msg void OnGateNand();
	afx_msg void OnGateNor();
	afx_msg void OnGateXor();
};

#ifndef _DEBUG  // debug version in LogicSim2View.cpp
inline CLogicSim2Doc* CLogicSim2View::GetDocument() const
   { return reinterpret_cast<CLogicSim2Doc*>(m_pDocument); }
#endif
