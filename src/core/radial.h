#pragma once
#include "line.h"

class Radial : public Line {
private:
	Dot* end_point;
	Dot* cross_point;
public:
	Radial(Dot d1, Dot d2);

	Dot* GetEndPoint();

	Dot* GetCrossPoint();

	bool equals(Graph* graph);
};

