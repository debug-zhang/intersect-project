#pragma once
#include "line.h"

class Radial : public Line {
private:
	Dot* end_point;
	Dot* cross_point;
public:
	Radial(Dot d1, Dot d2) : Line(d1, d2) {
		this->end_point = new Dot(d1);
		this->cross_point = new Dot(d2);
	}

	inline Dot* GetEndPoint() {
		return end_point;
	}

	inline Dot* GetCrossPoint() {
		return cross_point;
	}
};

