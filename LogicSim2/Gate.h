#pragma once
#include "stdafx.h"
#include "math.h"
#define PI 3.14159265359


class Gate {
public:
	CPoint input[7];
	CPoint output[7];
	CPoint point;
	CString name;
	CString label=_T("");
	int way;
	bool isbit = false;
	bool bit_flag = false;
	bool isclock = false;
	int clock = 1;
	bool start_clock = false;
	bool c_flag = false;

	Gate() {
		point = CPoint(0, 0);
		for (int i = 0; i < 7; i++) {
			output[i] = (0, 0);
			input[i] = (0, 0);
		}
		name = "";
	}
	Gate(CPoint point) {
		this->point = point;
	}
public:
	virtual void Draw(CClientDC &dc, double i){}
	virtual void Drawstr(CClientDC &dc, double i){}
};

class AND : public Gate {
public:
	AND() {
		Gate::Gate();
		name = _T("AND");
	}
	AND(CPoint &point, double i) {
		this->point = point;
		name = _T("AND");
	}
	void Draw(CClientDC& dc, double i) {
		int j = i;
		i = PI / 2 * i;
		int a, b;
		a = -30; b = 30;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 0;
		dc.AngleArc(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), 30, 270 - (int)(j * 90), 180);
		a = -60; b = -30;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -60; b = 30;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 30;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -60; b = -10;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -60; b = 10;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class NOT : public Gate {
public:
	NOT() {
		Gate::Gate();
		name = _T("NOT");
	}
	NOT(CPoint &point) {
		this->point = point;
		name = _T("NOT");
	}
	void Draw(CClientDC &dc, double i) {
		i = PI / 2 * i;
		int a, b, c, d;
		a = -10; b = -5; c = 0; d = 5;
		dc.Ellipse(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		a = -10; b = 0;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = -10;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 10;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -10; b = 0;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 0;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class OR : public Gate {
	CPoint arr[3][4];
public:
	OR(CPoint &point, double i) {
		i = PI / 2 * i;
		this->point = point;
		int a, b;
		name = _T("OR");
		arr[0][0].x = point.x;
		arr[0][0].y = point.y;
		a = -10; b = -10;
		arr[0][1].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[0][1].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -30; b = -20;
		arr[0][2].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[0][2].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -60; b = -30;
		arr[0][3].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[0][3].y = point.y + (a*int(sin(i)) + b*int(cos(i)));

		arr[1][0].x = point.x;
		arr[1][0].y = point.y;
		a = -10; b = 10;
		arr[1][1].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[1][1].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -30; b = 20;
		arr[1][2].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[1][2].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -60; b = 30;
		arr[1][3].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[1][3].y = point.y + (a*int(sin(i)) + b*int(cos(i)));

		a = -60; b = -30;
		arr[2][0].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[2][0].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -40; b = -20;
		arr[2][1].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[2][1].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -40; b = 20;
		arr[2][2].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[2][2].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -60; b = 30;
		arr[2][3].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[2][3].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
	}
	void Draw(CClientDC &dc, double i) {
		for (int j = 0; j < 3; j++) {
			dc.PolyBezier(arr[j], 4);
		}
		i = PI / 2 * i;
		int a, b;
		a = -50; b = -10;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -50; b = 10;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class NAND : public Gate {
	AND *and;
public:
	NAND(CPoint &point, double i) {
		int j = i;
		i = PI / 2 * i;
		int a, b;
		a = 10; b = 0;
		CPoint temp = point - CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		and = new AND(temp,j);
		this->point = point;
		name = _T("NAND");
	}
	void Draw(CClientDC &dc, double i) {
		int j = i;
		i = PI / 2 * i;
		int a, b, c, d;
		a = -10; b = -5; c = 0; d = 5;
		dc.Ellipse(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		if(!c_flag)
			and->Draw(dc, j);
		a = -70; b = -10;
		input[0] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		a = -70; b = 10;
		input[1] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class NOR : public Gate {
	OR * or ;
public:
	NOR(CPoint &point, double i) {
		int j = i;
		i = PI / 2 * i;
		int a, b;
		a = 10; b = 0;
		CPoint temp = point - CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		or = new OR(temp, j);
		this->point = point;
		name = _T("NOR");
	}
	void Draw(CClientDC &dc, double i) {
		int j = i;
		i = PI / 2 * i;
		int a, b, c, d;
		a = -10; b = -5; c = 0; d = 5;
		dc.Ellipse(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		or ->Draw(dc,i);
		a = -60; b = -10;
		input[0] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		a = -60; b = 10;
		input[1] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class XOR : public Gate {
	OR * or ;
	CPoint arr[4];
public:
	XOR(CPoint &point, double i) {
		int a, b;
		or = new OR(point, i);
		this->point = point;
		i = PI / 2 * i;

		a = -70; b = -30;
		arr[0].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[0].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -50; b = -20;
		arr[1].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[1].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -50; b = 20;
		arr[2].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[2].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		a = -70; b = 30;
		arr[3].x = point.x + (a*int(cos(i)) - b*int(sin(i)));
		arr[3].y = point.y + (a*int(sin(i)) + b*int(cos(i)));
		name = _T("XOR");
	}
	void Draw(CClientDC &dc, double i) {
		or ->Draw(dc,i);
		dc.PolyBezier(arr, 4);
		i = PI / 2 * i;
		int a, b;
		a = -60; b = -10;
		input[0] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		a = -60; b = 10;
		input[1] = CPoint((a*int(cos(i)) - b*int(sin(i))), (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
	}
};

class D_FF : public Gate {
public:
	bool edge_stream = true;
public:
	D_FF(CPoint &point) {
		this->point = point;
		name = _T("D_FF");
	}
	void Draw(CClientDC &dc, double i) {
		i = PI / 2 * i;
		int a, b;
		a = 0; b = -20;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 50;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 40;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 30;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));

		a = -40; b = 0;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 40;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
		a = 0; b = 40;
		output[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		int str_x = 0, str_y = 0;
		if (i == 1) {
			str_x = -12;
			str_y = -2;
		}
		else if (i == 2) {
			str_x = -8;
			str_y = -15;
		}
		else if (i == 3) {
			str_x = 2;
			str_y = -12;
		}
		i = PI / 2 * i;
		int a, b;
		str.Format(_T("Q"));
		a = -15; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("Q"));
		a = -15; b = 35;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("D"));
		a = -35; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		a = -15; b = 35;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x + 10, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
	}
};

class JK_FF : public Gate {
public:
	bool edge_stream = true;
public:
	JK_FF(CPoint &point) {
		this->point = point;
		name = _T("JK_FF");
	}
	void Draw(CClientDC &dc, double i) {
		i = PI / 2 * i;
		int a, b;
		a = 0; b = -20;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 30;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 10;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));

		a = -40; b = 0;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 20;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 40;
		input[2] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
		a = 0; b = 40;
		output[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		int str_x = 0, str_y = 0;
		if (i == 1) {
			str_x = -12;
			str_y = -2;
		}
		else if (i == 2) {
			str_x = -8;
			str_y = -15;
		}
		else if (i == 3) {
			str_x = 2;
			str_y = -12;
		}
		i = PI / 2 * i;
		int a, b;
		str.Format(_T("Q"));
		a = -15; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("Q"));
		a = -15; b = 35;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("J"));
		a = -35; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("K"));
		a = -35; b = 35;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		a = -15; b = 35;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x + 10, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
	}
};

class T_FF : public Gate {
public:
	bool edge_stream = true;
public:
	T_FF(CPoint &point) {
		this->point = point;
		name = _T("T_FF");
	}
	void Draw(CClientDC &dc, double i) {
		i = PI / 2 * i;
		int a, b;
		a = 0; b = -20;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 60;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = -20;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 50;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -30; b = 40;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 30;
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));

		a = -40; b = 0;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 40;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[0] = point;
		a = 0; b = 40;
		output[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		int str_x = 0, str_y = 0;
		if (i == 1) {
			str_x = -12;
			str_y = -2;
		}
		else if (i == 2) {
			str_x = -8;
			str_y = -15;
		}
		else if (i == 3) {
			str_x = 2;
			str_y = -12;
		}
		i = PI / 2 * i;
		int a, b;
		str.Format(_T("Q"));
		a = -15; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("Q"));
		a = -15; b = 35;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		str.Format(_T("T"));
		a = -35; b = -10;
		dc.TextOut(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y, str);
		a = -15; b = 35;
		dc.MoveTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
		dc.LineTo(point.x + (a*int(cos(i)) - b*int(sin(i))) + str_x + 10, point.y + (a*int(sin(i)) + b*int(cos(i))) + str_y);
	}
};

class Bit_switch : public Gate {
public:
	//bool bit_flag = false;
public:
	Bit_switch(CPoint &point) {
		this->point = point;
		name = _T("SWITCH");
	}
	void Draw(CClientDC &dc, double i) {
		dc.Rectangle(point.x - 20, point.y - 10, point.x, point.y + 10);
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		if (bit_flag) {
			str.Format(_T("1"));
		}
		else {
			str.Format(_T("0"));
		}
		dc.TextOut(point.x - 14, point.y - 7, str);
	}
};

class Seven_seg : public Gate {
public:
	bool in[8];
public:
	Seven_seg(CPoint &point) {
		this->point = point;
		name = _T("7-SEGMENT");
	}
	void Draw(CClientDC &dc, double i) {
		i = PI / 2 * i;
		int a, b, c, d;

		a = -40; b = -10; c = 0; d = 70;
		dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));

		//CBrush black_brush = RGB(0, 0, 0);
		//dc.SelectObject(black_brush);
		if (in[0]) {
			a = -35; b = -5; c = -5; d = 5;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[1]) {
			a = -15; b = 5; c = -5; d = 25;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[2]) {
			a = -15; b = 35; c = -5; d = 55;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[3]) {
			a = -35; b = 55; c = -5; d = 65;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[4]) {
			a = -35; b = 35; c = -25; d = 55;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[5]) {
			a = -35; b = 5; c = -25; d = 25;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		if (in[6]) {
			a = -35; b = 25; c = -5; d = 35;
			dc.Rectangle(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))), point.x + (c*int(cos(i)) - d*int(sin(i))), point.y + (c*int(sin(i)) + d*int(cos(i))));
		}
		//black_brush.DeleteObject();

		a = -40; b = -10;
		input[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 0;
		input[1] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 10;
		input[2] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 20;
		input[3] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 30;
		input[4] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 40;
		input[5] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = -40; b = 50;
		input[6] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));

		a = 0; b = -10;
		output[0] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		output[1] = point;
		a = 0; b = 10;
		output[2] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 20;
		output[3] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 30;
		output[4] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 40;
		output[5] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
		a = 0; b = 50;
		output[6] = CPoint(point.x + (a*int(cos(i)) - b*int(sin(i))), point.y + (a*int(sin(i)) + b*int(cos(i))));
	}
};

class Bit_clock : public Gate {
public:
	//bool bit_flag = false;
	//int clock=1;
public:
	Bit_clock(CPoint &point) {
		this->point = point;
		name = _T("CLOCK");
	}
	void Draw(CClientDC &dc, double i) {
		dc.Rectangle(point.x - 20, point.y - 20, point.x, point.y + 20);
		dc.MoveTo(point.x - 15, point.y + 15);
		dc.LineTo(point.x - 10, point.y + 15);
		dc.LineTo(point.x - 10, point.y + 5);
		dc.LineTo(point.x - 5, point.y + 5);
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		if (bit_flag)
			str.Format(_T("1"));
		else
			str.Format(_T("0"));
		dc.TextOut(point.x - 14, point.y - 7, str);
	}
};

class Out_switch : public Gate {
public:
	//bool bit_flag = false;
public:
	Out_switch(CPoint &point) {
		this->point = point;
		name = _T("LAMP");
	}
	void Draw(CClientDC &dc, double i) {
		dc.Ellipse(point.x, point.y - 10, point.x + 20, point.y + 10);
	}
	void Drawstr(CClientDC &dc, double i) {
		CString str;
		if (bit_flag)
			str.Format(_T("1"));
		else
			str.Format(_T("0"));
		dc.TextOut(point.x + 6, point.y - 7, str);
	}
};