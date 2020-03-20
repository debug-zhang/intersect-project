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
	/*constructor
	params:
	returns:
	exceptions:
	*/
	Container();

	/*
	params:
	returns: the number of dots in the container
	exceptions:
	*/
	int Size();

	/*
	params:
	returns: a vector contains all graphs
	exceptions:
	*/
	vector<Graph*>* Getgraphs();

	/*
	params:
	returns: a set contains all dots
	exceptions:
	*/
	set<Dot>* GetDots();

	/*
	params:*g1(Graph), *g2(Graph)
	returns:
	exceptions: infinate_intersect_exception - if the graphs have infinate intersections(partially superpose)
	*/
	void IntersectCalculate(Graph* g1, Graph* g2);

	/*
	add a dot into the container(will ignore if two dots are superposed)
	params: d(Dot)
	returns:
	exceptions:
	*/
	void AddDot(Dot d);

	/*
	add a graph(Line, Radial or Segment) defined by ((x1, y1), (x2, y2))
	params: type(char) - which must in [L, R, S, C]
				  x1(int) - dot1's x value
				  y1(int) - dot1's y value
				  x2(int) - dot2's x value
				  y2(int) - dot2's y value
	returns:
	exceptions:
	*/
	void AddGraph(char type,int x1, int y1, int x2, int y2);
};