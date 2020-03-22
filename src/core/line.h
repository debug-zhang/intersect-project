#pragma once
#include <string>
#include "dot.h"
#include "graph.h"

class Line : public Graph {
private:
	double A, B, C;
public:
	Line(Dot, Dot);

	inline double GetA() override;

	inline double GetB() override;

	inline double GetC() override;

	inline string ToString() override;

	bool equals(string to_string) override;
};

int DoubleToInt(double d);

