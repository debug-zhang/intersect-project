#include "Graph.h"

void Container::add(Dot d) {
	cout << "found point " << '(' << d.first << ',' << d.second << ')' << endl;
	dots.insert(d);
}

int Container::size() {
	return dots.size();
}