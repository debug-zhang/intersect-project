#include "pch.h"
#include "radial.h"

Radial::Radial(Dot d1, Dot d2) : Line(d1, d2) {
	if (d1.equals(d2)) {
		throw dot_superposition_exception();
	}
	this->end_point = new Dot(d1);
	this->cross_point = new Dot(d2);
}

Dot* Radial::GetEndPoint() {
	return end_point;
}

Dot* Radial::GetCrossPoint() {
	return cross_point;
}

bool Radial::equals(Graph* graph) {
	return this->Line::equals(graph)
		&& this->cross_point->equals(*((Radial*)graph)->cross_point)
		&& this->end_point->equals(*((Radial*)graph)->end_point);
}