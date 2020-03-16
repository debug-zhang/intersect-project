#include "dot.h"

Dot::Dot(double x, double y) {
	first = x;
	second = y;
}

Dot::Dot(const Dot& d) {
	first = d.first;
	second = d.second;
}

double Dot::GetX() {
	return first;
}

double Dot::GetY() {
	return second;
}

bool Dot::equals(Dot b) {
	return fabs(first - b.first) < 1e-10
		&& fabs(second - b.second) < 1e-10;
}