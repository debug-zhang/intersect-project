#ifndef LINECROSS_GRAPH_H
#define LINECROSS_GRAPH_H

#include "generic.h"

class Dot :public pair<double,double>{
public:
	Dot(double, double);

	inline double getX();

	inline double getY();

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

	inline double getA() override;

	inline double getB() override;

	inline double getC() override;
};

class Circle : public Graph {
private:
	double m, n, r;
public:
	Circle(double, double, double);

	inline double getA() override;

	inline double getB() override;

	inline double getC() override;
};

class Container {
private:
	set<Dot> dots;
public:
	void add(Dot d);

	int size();
};

void solve(Container *con, Graph* g1, Graph* g2);

#endif