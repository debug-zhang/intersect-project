#include "pch.h"
#include "container.h"

Container::Container() {
	this->graphs = new vector<Graph*>;
	this->dots = new set<Dot>;
}

bool  Container::IsSameSymbol(double a, double b) {
	return (a >= 0 && b >= 0) || (a <= 0 && b <= 0);
}

bool  Container::IsInRadialLimit(Dot* intersect, Radial* radial) {
	Dot* end_point = radial->GetEndPoint();
	Dot* cross_point = radial->GetCrossPoint();

	return IsSameSymbol((cross_point->GetX() - end_point->GetX()), (intersect->GetX() - end_point->GetX()))
		&& IsSameSymbol((cross_point->GetY() - end_point->GetY()), (intersect->GetY() - end_point->GetY()));

}

bool  Container::IsInSegmentLimit(Dot* intersect, Segment* segment) {
	Dot* end_point1 = segment->GetEndPoint1();
	Dot* end_point2 = segment->GetEndPoint2();

	return intersect->GetX() >= min(end_point1->GetX(), end_point2->GetX())
		&& intersect->GetX() <= max(end_point1->GetX(), end_point2->GetX())
		&& intersect->GetY() >= min(end_point1->GetY(), end_point2->GetY())
		&& intersect->GetY() <= max(end_point1->GetY(), end_point2->GetY());
}


int Container::Size() {
	return (int)dots->size();
}

vector<Graph*>* Container::Getgraphs() {
	return graphs;
}

set<Dot>* Container::GetDots() {
	return dots;
}

void  Container::IntersectCalculate(Graph* g1, Graph* g2) {
	// both are line, radial or segment
	double A1 = g1->GetA(), B1 = g1->GetB(), C1 = g1->GetC();
	double A2 = g2->GetA(), B2 = g2->GetB(), C2 = g2->GetC();

	double denominator = A1 * B2 - A2 * B1;

	//if not parrallel
	if (!DoubleEquals(denominator, 0)) {
		double x = (B1 * C2 - B2 * C1) / denominator;
		double y = (A2 * C1 - A1 * C2) / denominator;
		Dot* intersect = new Dot(x, y);
		bool flag = true;

		string type1 = typeid(*g1).name();
		if (type1 == typeid(Radial).name()) {
			flag = flag & IsInRadialLimit(intersect, (Radial*)g1);
		} else if (type1 == typeid(Segment).name()) {
			flag = flag & IsInSegmentLimit(intersect, (Segment*)g1);
		}
		if (!flag) {
			return;
		}

		string type2 = typeid(*g2).name();
		if (type2 == typeid(Radial).name()) {
			flag = flag & IsInRadialLimit(intersect, (Radial*)g2);
		} else if (type2 == typeid(Segment).name()) {
			flag = flag & IsInSegmentLimit(intersect, (Segment*)g2);
		}
		if (!flag) {
			return;
		}

		this->AddDot(*intersect);
	}
}

void Container::AddDot(Dot d) {
	dots->insert(d);
}

void Container::AddGraph(char type, int x1, int y1, int x2, int y2) {
		Graph* new_graph = NULL;
		if (type == 'L') {
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Line(d1, d2);

		} else if (type == 'R') {
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Radial(d1, d2);

		} else if (type == 'S') {
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Segment(d1, d2);
		}

		if (new_graph != NULL) {
			for (Graph* graph : *graphs) {
				IntersectCalculate(new_graph, graph);
			}
			graphs->push_back(new_graph);
		}
}