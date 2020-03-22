#pragma once
#include "exception.h"

class Graph {
public:
	virtual double GetA() = 0;

	virtual double GetB() = 0;

	virtual double GetC() = 0;

	virtual bool equals(Graph* graph) = 0;
};
