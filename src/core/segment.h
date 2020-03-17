#pragma once
#include "line.h"

class Segment : public Line {
private:
	Dot* end_point1;
	Dot* end_point2;
public:
	Segment(Dot d1, Dot d2) : Line(d1, d2) {
		this->end_point1 = new Dot(d1);
		this->end_point2 = new Dot(d2);
	}

	inline Dot* GetEndPoint1() {
		return end_point1;
	}

	inline Dot* GetEndPoint2() {
		return end_point2;
	}
};

