#include "line.h"

Line::Line(Dot d1, Dot d2) {
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