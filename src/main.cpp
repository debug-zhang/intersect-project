#include <vector>
#include "container.h"
#include "IOHandler.h"

#define DEBUG 0

int main(int argc, char* argv[]) {
	IOHandler io(argc, argv, DEBUG);

	int line = io.readInt();

	Container* container = new Container;
	vector<Graph*> graphs;

	for (int i = 0; i < line; i++) {
		Graph* graph1 = NULL;
		char type = io.readChar();
		if (type == 'L') {
			int x1 = io.readInt();
			int y1 = io.readInt();
			int x2 = io.readInt();
			int y2 = io.readInt();
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Line(d1, d2);

		} else if (type == 'R') {
			int x1 = io.readInt();
			int y1 = io.readInt();
			int x2 = io.readInt();
			int y2 = io.readInt();
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Radial(d1, d2);

		} else if (type == 'S') {
			int x1 = io.readInt();
			int y1 = io.readInt();
			int x2 = io.readInt();
			int y2 = io.readInt();
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Segment(d1, d2);

		} else if (type == 'C') {
			// TO DO
		}

		if (graph1 != NULL) {
			for (Graph* graph2 : graphs) {
				Solve(container, graph1, graph2);
			}
			graphs.push_back(graph1);
		}
	}

	io.outputInt(container->Size());
	// cout << "total: " << container->Size() << endl;
	return 0;
}