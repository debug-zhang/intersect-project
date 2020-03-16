#pragma once
#include <iostream>
using namespace std;

class Dot :public pair<double, double> {
public:
	Dot(double, double);
	Dot(const Dot&);

	double GetX();

	double GetY();

	bool equals(Dot b);
};

