#include "Graph.h"

Dot::Dot(double a, double b) {
	x = a;
	y = b;
}

double Dot::getX() {
	return x;
}

double Dot::getY() {
	return y;
}

bool Dot::equals(Dot b) {
	return this->getX() == b.getX() && this->getY() == b.getY();
}

Line::Line(Dot d1, Dot d2) {
	a = d1.getY() - d2.getY();
	b = d2.getX() - d1.getX();
	c = -a * d1.getX() - b * d1.getY();
}

Line::Line(double varX, double varY, double varC) {
	a = varX;
	b = varY;
	c = varC;
}

double Line::getA() {
	return a;
}

double Line::getB() {
	return b;
}

double Line::getC() {
	return c;
}

Circle::Circle(double varM, double varN, double varR) {
	m = varM;
	n = varN;
	r = varR;
}

double Circle::getA() {
	return m;
}

double Circle::getB() {
	return n;
}

double Circle::getC() {
	return r;
}

vector<Dot> solve(Graph* g1, Graph* g2) {
	vector<Dot> res;
	bool aIsLine = typeid(*g1).name() == typeid(Line).name();
	bool bIsLine = typeid(*g2).name() == typeid(Line).name();

	if (aIsLine && bIsLine) {
		//if both is line
		double a1 = g1->getA(), b1 = g1->getB(), c1 = g1->getC();
		double a2 = g2->getA(), b2 = g2->getB(), c2 = g2->getC();
		if ((a1 * b2 - a2 * b1) != 0) {
			//if not parrallel
			double x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
			double y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
			Dot d(x, y);
			res.push_back(d);
		}
	}
	else if (aIsLine && !bIsLine) {
		//if g1 is line and g2 is circle
		double _a = g1->getA(), _b = g1->getB(), _c = g1->getC();
		double _m = g2->getA(), _n = g2->getB(), _r = g2->getC();
		if (_b == 0) {
			//g1 is vertical line
			double x1 = -_c / _a, x2 = -_c / _a;
			double dis = pow(_r, 2) - pow(x1 - _m, 2);
			if (dis >= 0) {
				double y1 = _n + sqrt(dis);
				double y2 = _n + -sqrt(dis);
				Dot d1(x1, y1);
				Dot d2(x2, y2);
				res.push_back(d1);
				res.push_back(d2);
			}
		}
		else {
			double a = pow(_b, 2) + pow(_a, 2);
			double b = (_a * _c - _m * pow(_b, 2) + _n * _a * _b) * 2;
			double c = (pow(_m, 2) + pow(_n, 2) - pow(_r, 2)) * pow(_b, 2) + pow(_c, 2) + 2 * _n * _c * _b;
			double delta = pow(b, 2) - 4 * a * c;
			if (delta >= 0) {
				double x1 = (-b + sqrt(delta)) / (2 * a), x2 = (-b - sqrt(delta)) / (2 * a);
				double y1 = (_a * x1 + _c) / (-_b), y2 = (_a * x2 + _c) / (-_b);
				Dot d1(x1, y1);
				Dot d2(x2, y2);
				res.push_back(d1);
				res.push_back(d2);
			}
		}
	}
	else if (!aIsLine && bIsLine) {
		//if g1 is circle and g2 is line
		return solve(g2, g1);
	}
	else {
		//if both are circle
		double x1 = g1->getA(), y1 = g1->getB(), r1 = g1->getC();
		double x2 = g2->getA(), y2 = g2->getB(), r2 = g2->getC();
		double _a = 2 * (x1 - x2);
		double _b = 2 * (y1 - y2);
		double _c = pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2) - pow(r2, 2) + pow(r1, 2);
		Line* l = new Line(_a, _b, _c);
		return solve(l, g2);
	}
	return res;
}
