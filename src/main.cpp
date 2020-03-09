#include "Graph.h"
#include "Container.h"
#include <vector>

int main() {
	int line;
	cin >> line;
	Container container;
	vector<Graph*> graphs;

	for (int i = 0; i < line; i++) {
		char type;
		cin >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			Line* l = new Line(d1, d2);
			for (Graph* graph : graphs) {
				vector<Dot> res = solve(graph, l);
				container.add(res);
			}
			graphs.push_back(l);
		} else if (type == 'C') {
			int m, n, r;
			cin >> m >> n >> r;
			Circle* c = new Circle(m, n, r);
			for (Graph* graph : graphs) {
				vector<Dot> res = solve(graph, c);
				container.add(res);
			}
			graphs.push_back(c);
		}
	}

	//container.print();
	cout << container.size() << endl;
	return 0;
}