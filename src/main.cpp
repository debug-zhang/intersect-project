#include "Graph.h"
#include "Container.h"
#include <vector>

int main() {
    int n;
    cin >> n;
    Container container;
    vector<Graph *> graphs;

    for (int i = 0; i < n; i++) {
        char type;
        int x1, y1, x2, y2;
        cin >> type >> x1 >> y1 >> x2 >> y2;
        Dot d1(x1, y1);
        Dot d2(x2, y2);
        Line *l = new Line(d1, d2);
        for (Graph *graph : graphs) {
            vector<Dot> res = solve(graph, l);
            container.add(res);
        }
        graphs.push_back(l);
    }

    container.print();
}