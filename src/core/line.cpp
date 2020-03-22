#include "pch.h"
#include "line.h"

Line::Line(Dot d1, Dot d2) {
	if (d1.equals(d2)) {
		throw dot_superposition_exception();
	}

	type = 'L';
	x1 = DoubleToInt(d1.GetX());
	y1 = DoubleToInt(d1.GetY());
	x2 = DoubleToInt(d2.GetX());
	y2 = DoubleToInt(d2.GetY());

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

inline string Line::ToString() {
	return string(1, type) + " " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) + " " + to_string(y2);
}

bool Line::equals(string to_string) {
	return this->ToString() == to_string;
}

int DoubleToInt(double d) {
	if (d < 0.0) {
		return static_cast<int>(d - 0.5);
	} else {
		return static_cast<int>(d + 0.5);
	}
}