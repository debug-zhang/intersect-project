#include "pch.h"
#include "line.h"

Line::Line(Dot d1, Dot d2) {
	if (d1.equals(d2)) {
		throw dot_superposition_exception();
	}
	A = d1.GetY() - d2.GetY();
	B = d2.GetX() - d1.GetX();
	C = -A * d1.GetX() - B * d1.GetY();
}

inline double Line::GetA() {
	return A;
}

inline double Line::GetB() {
	return B;
}

inline double Line::GetC() {
	return C;
}

bool Line::equals(Graph* graph) {
	return DoubleEquals(this->A, ((Line*)graph)->A)
		&& DoubleEquals(this->B, ((Line*)graph)->B)
		&& DoubleEquals(this->C, ((Line*)graph)->C);
}