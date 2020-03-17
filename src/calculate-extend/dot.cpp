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
	return DoubleEquals(first, b.first) && DoubleEquals(second, b.second);
}