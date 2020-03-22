#include "pch.h"
#include "radial.h"

Radial::Radial(Dot d1, Dot d2) : Line(d1, d2) {
	if (d1.equals(d2)) {
		throw dot_superposition_exception();
	}
	this->type = 'R';
	this->end_point = new Dot(d1);
	this->cross_point = new Dot(d2);
}

Dot* Radial::GetEndPoint() {
	return end_point;
}

Dot* Radial::GetCrossPoint() {
	return cross_point;
}