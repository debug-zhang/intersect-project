#ifndef LINECROSS_GRAPH_H
#define LINECROSS_GRAPH_H

#include "generic.h"

class Dot {
private:
	double x, y;
public:
	Dot(double, double);

	double getX();

	double getY();

	bool equals(Dot b);
};

class Graph {
public:
	virtual double getA() = 0;

	virtual double getB() = 0;

	virtual double getC() = 0;
};

class Line : public Graph {
private:
	double a, b, c;
public:
	Line(Dot d1, Dot d2);

	Line(double, double, double);

	double getA();

	double getB();

	double getC();
};

class Circle :public Graph {
private:
	double m, n, r;
public:
	Circle(double, double, double);
	double getA();
	double getB();
	double getC();
};
vector<Dot> solve(Graph* g1, Graph* g2);

#endif
