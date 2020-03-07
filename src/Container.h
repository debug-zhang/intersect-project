#ifndef LINECROSS_CONTAINER_H
#define LINECROSS_CONTAINER_H

#include "Graph.h"

class Container {
private:
	vector<Dot> dots;
public:
	void add(vector<Dot> vec);

	int size();

	void print();
};

#endif