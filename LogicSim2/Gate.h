#pragma once
#include "stdafx.h"

class Gate {
public:
	CPoint input[2];
	CPoint output[2];
	CPoint point;
	CString name;
	Gate() {
		point = CPoint(0, 0);
		input[2] = { (0,0),(0,0) };
		output[2] = { (0,0),(0,0) };
		name = "";
	}
	Gate(CPoint point) {
		this->point = point;
	}
public:
	virtual void Draw(CClientDC &dc) {}

};
class AND : public Gate {
public:
	AND() {
		Gate::Gate();
	}
	AND(CPoint &point) {
		this->point = point;
	}
	void Draw(CClientDC& dc) {
		dc.MoveTo(point.x - 30, point.y + 30);
		dc.AngleArc(point.x - 30, point.y, 30, 270, 180);
		dc.LineTo(point.x - 60, point.y - 30);
		dc.LineTo(point.x - 60, point.y + 30);
		dc.LineTo(point.x - 30, point.y + 30);
		input[0] = CPoint(point.x - 60, point.y - 10);
		input[1] = CPoint(point.x - 60, point.y + 10);
		output[0] = point;
	}
};

class NOT : public Gate {
public:
	NOT(CPoint &point) {
		this->point = point;
	}
	void Draw(CClientDC &dc) {
		dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
		dc.MoveTo(point.x - 10, point.y);
		dc.LineTo(point.x - 30, point.y - 10);
		dc.LineTo(point.x - 30, point.y + 10);
		dc.LineTo(point.x - 10, point.y);
		input[0] = CPoint(point.x - 30, point.y);
		output[0] = point;
	}
};

class OR : public Gate {
	CPoint arr[3][4];
public:
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
		input[0] = CPoint(point.x - 50, point.y - 10);
		input[1] = CPoint(point.x - 50, point.y + 10);
		output[0] = point;
	}
};

class NAND : public Gate {
	AND *and;
public:
	NAND(CPoint &point) {
		CPoint temp = point - CPoint(10, 0);
		and = new AND(temp);
		this->point = point;
	}
	void Draw(CClientDC &dc) {
		dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
		and->Draw(dc);
		input[0] = CPoint(point.x - 70, point.y - 10);
		input[1] = CPoint(point.x - 70, point.y + 10);
		output[0] = point;
	}
};

class NOR : public Gate {
	OR * or ;
public:
	NOR(CPoint &point) {
		CPoint temp = point - CPoint(10, 0);
		or = new OR(temp);
		this->point = point;
	}
	void Draw(CClientDC &dc) {
		dc.Ellipse(point.x - 10, point.y - 5, point.x, point.y + 5);
		or ->Draw(dc);
		input[0] = CPoint(point.x - 60, point.y - 10);
		input[1] = CPoint(point.x - 60, point.y + 10);
		output[0] = point;
	}
};

class XOR : public Gate {
	OR * or ;
	CPoint arr[4];
public:
	XOR(CPoint &point) {
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
		input[0] = CPoint(point.x - 60, point.y - 10);
		input[1] = CPoint(point.x - 60, point.y + 10);
		output[0] = point;
	}
};