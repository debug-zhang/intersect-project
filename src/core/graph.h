#pragma once
#include "exception.h"

class Graph {
public:
	char type = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

	virtual double GetA() = 0;

	virtual double GetB() = 0;

	virtual double GetC() = 0;

	virtual string ToString() = 0;

	virtual bool equals(string to_string) = 0;
};
