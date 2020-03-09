#include "Graph.h"

void Container::add(Dot d) {
		dots.insert(d);
}

int Container::size() {
	return dots.size();
}