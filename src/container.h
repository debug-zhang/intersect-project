#pragma once
#include <set>
#include <algorithm>
#include "line.h"
#include "radial.h"
#include "segment.h"

class Container {
private:
	set<Dot> dots;
public:
	void Add(Dot d);

	int Size();
};

bool IsSameSymbol(double a, double b);

bool IsInRadialLimit(Dot* intersect, Radial* radial);

bool IsInSegmentLimit(Dot* intersect, Segment* segment);

void Solve(Container* container, Graph* g1, Graph* g2);
