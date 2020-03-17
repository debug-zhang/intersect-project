#pragma once
#include <set>
#include <vector>
#include <algorithm>
#include "line.h"
#include "radial.h"
#include "segment.h"

class _declspec(dllexport) Container {
private:
	vector<Graph*>* graphs;
	set<Dot>* dots;

	bool IsSameSymbol(double a, double b);

	bool IsInRadialLimit(Dot* intersect, Radial* radial);

	bool IsInSegmentLimit(Dot* intersect, Segment* segment);
public:
	Container();

	int Size();

	vector<Graph*>* Getgraphs();

	set<Dot>* GetDots();

	void IntersectCalculate(Graph* g1, Graph* g2);

	void AddDot(Dot d);

	void AddGraph(char type,int x1, int y1, int x2, int y2);
};