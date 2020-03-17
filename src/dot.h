#pragma once
#include <iostream>

#define DoubleEquals(a, b) (fabs((a) - (b)) < 1e-10)

using namespace std;

class Dot :public pair<double, double> {
public:
	Dot(double, double);
	Dot(const Dot&);

	double GetX();

	double GetY();

	bool equals(Dot b);
};

