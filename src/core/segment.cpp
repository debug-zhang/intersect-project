#include "pch.h"
#include "segment.h"

Segment::Segment(Dot d1, Dot d2) : Line(d1, d2) {
	if (d1.equals(d2)) {
		throw dot_superposition_exception();
	}
	this->end_point1 = new Dot(d1);
	this->end_point2 = new Dot(d2);
}

Dot* Segment::GetEndPoint1() {
	return end_point1;
}

Dot* Segment::GetEndPoint2() {
	return end_point2;
}