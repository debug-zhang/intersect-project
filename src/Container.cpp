#include "Container.h"

void Container::add(vector<Dot> vec) {
	for (Dot d : vec) {
		if (dots.empty()) {
			dots.push_back(d);
		}
		else {
			bool has = false;
			for (Dot i : dots) {
				if (i.equals(d)) {
					has = true;
					break;
				}
			}
			if (!has) {
				dots.push_back(d);
			}
		}
	}
}


int Container::size() {
	return dots.size();
}

void Container::print() {
	for (Dot d : dots) {
		cout << "(" << d.getX() << "," << d.getY() << ")" << endl;
	}
}