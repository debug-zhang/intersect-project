#pragma once
#include "line.h"

class Segment : public Line {
private:
	Dot* end_point1;
	Dot* end_point2;
public:
	Segment(Dot d1, Dot d2);

	Dot* GetEndPoint1();

	Dot* GetEndPoint2();
};

