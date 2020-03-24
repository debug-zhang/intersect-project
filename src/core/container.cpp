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
vector<Graph*>* Container::GetGraphs() {
	return graphs;
}

set<pair<double,double>>* Container::GetDots() {
	set<pair<double, double>>* res = new set<pair<double, double>>;
	for (Dot d : *dots) {
		pair<double, double> pair(d.GetX(),d.GetY());
		res->insert(pair);
	}
	return res;
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
	} else if (DoubleEquals(B1 * C2 - B2 * C1, 0) && DoubleEquals(A1 * C2 - A2 * C1, 0)) {
		//if parrallel and have the same expression(might have infinate intersections)
		string type1 = typeid(*g1).name();
		string type2 = typeid(*g2).name();
		if (type1 == typeid(Line).name() || type2 == typeid(Line).name()) {
			throw infinate_intersect_exception();
		} else if (type1 == typeid(Radial).name() && type2 == typeid(Radial).name()) {
			if (B1 == 0 && B2 == 0) {
				//line is vertical
				double g1endY = ((Radial*)g1)->GetEndPoint()->GetY();
				double g1crossY = ((Radial*)g1)->GetCrossPoint()->GetY();
				double g2endY = ((Radial*)g2)->GetEndPoint()->GetY();
				double g2crossY = ((Radial*)g2)->GetCrossPoint()->GetY();
				if ((g1crossY > g1endY && g1endY > g2endY && g2endY > g2crossY) ||
					(g1crossY < g1endY && g1endY < g2endY && g2endY < g2crossY)) {
					//	<-------O  O------->
					;
				} else if ((g1crossY > g1endY && DoubleEquals(g1endY, g2endY) && g2endY > g2crossY) ||
					(g1crossY < g1endY && DoubleEquals(g1endY, g2endY) && g2endY < g2crossY)) {
					// <-------O------->
					Dot* intersect = ((Radial*)g1)->GetEndPoint();
					this->AddDot(*intersect);
				} else {
					// <-------O
					//       O------->
					throw infinate_intersect_exception();
				}
			} else {
				//line is not vertical
				double g1endX = ((Radial*)g1)->GetEndPoint()->GetX();
				double g1crossX = ((Radial*)g1)->GetCrossPoint()->GetX();
				double g2endX = ((Radial*)g2)->GetEndPoint()->GetX();
				double g2crossX = ((Radial*)g2)->GetCrossPoint()->GetX();
				if ((g1crossX > g1endX && g1endX > g2endX && g2endX > g2crossX) ||
					(g1crossX < g1endX && g1endX < g2endX && g2endX < g2crossX)) {
					//	<-------O  O------->
					;
				} else if ((g1crossX > g1endX && DoubleEquals(g1endX, g2endX) && g2endX > g2crossX) ||
					(g1crossX < g1endX && DoubleEquals(g1endX, g2endX) && g2endX < g2crossX)) {
					// <-------O------->
					Dot* intersect = ((Radial*)g1)->GetEndPoint();
					this->AddDot(*intersect);
				} else {
					// <-------O
					//       O------->
					throw infinate_intersect_exception();
				}
			}

		} else if (type1 == typeid(Radial).name() && type2 == typeid(Segment).name()) {
			if (B1 == 0 && B2 == 0) {
				//if line is vertical
				double g1endY = ((Radial*)g1)->GetEndPoint()->GetY();
				double g1crossY = ((Radial*)g1)->GetCrossPoint()->GetY();
				double g2end1Y = ((Segment*)g2)->GetEndPoint1()->GetY();
				double g2end2Y = ((Segment*)g2)->GetEndPoint2()->GetY();
				if ((g1crossY > g1endY && g1endY > g2end1Y && g1endY > g2end2Y) ||
					(g1crossY < g1endY && g1endY < g2end1Y && g1endY < g2end2Y)) {
					// <-------O O-------O
					;
				} else if ((g1crossY > g1endY && DoubleEquals(g1endY, max(g2end1Y, g2end2Y))) ||
					(g1crossY < g1endY && DoubleEquals(g1endY, min(g2end1Y, g2end2Y)))) {
					// <-------O-------O
					Dot* intersect = ((Radial*)g1)->GetEndPoint();
					this->AddDot(*intersect);
				} else {
					// <-------O
					//    O-------O
					throw infinate_intersect_exception();
				}
			} else {
				//line is not vertical
				double g1endX = ((Radial*)g1)->GetEndPoint()->GetX();
				double g1crossX = ((Radial*)g1)->GetCrossPoint()->GetX();
				double g2end1X = ((Segment*)g2)->GetEndPoint1()->GetX();
				double g2end2X = ((Segment*)g2)->GetEndPoint2()->GetX();
				if ((g1crossX > g1endX && g1endX > g2end1X && g1endX > g2end2X) ||
					(g1crossX < g1endX && g1endX < g2end1X && g1endX < g2end2X)) {
					// <-------O O-------O
					;
				} else if ((g1crossX > g1endX && DoubleEquals(g1endX, max(g2end1X, g2end2X))) ||
					(g1crossX < g1endX && DoubleEquals(g1endX, min(g2end1X, g2end2X)))) {
					// <-------O-------O
					Dot* intersect = ((Radial*)g1)->GetEndPoint();
					this->AddDot(*intersect);
				} else {
					// <-------O
					//    O-------O
					throw infinate_intersect_exception();
				}
			}
		} else if (type1 == typeid(Segment).name() && type2 == typeid(Radial).name()) {
			return this->IntersectCalculate(g2, g1);
		} else if (type1 == typeid(Segment).name() && type2 == typeid(Segment).name()) {
			if (B1 == 0 && B2 == 0) {
				//if line is vertical
				double g1end1Y = ((Segment*)g1)->GetEndPoint1()->GetY();
				double g1end2Y = ((Segment*)g1)->GetEndPoint2()->GetY();
				double g2end2Y = ((Segment*)g2)->GetEndPoint2()->GetY();
				if ((min(g1end1Y, g1end2Y) > max(g1end1Y, g2end2Y)) ||
					(max(g1end1Y, g1end2Y) < min(g1end1Y, g2end2Y))) {
					// O-------O O-------O
					;
				} else if (DoubleEquals(min(g1end1Y, g1end2Y), max(g1end1Y, g2end2Y))) {
					// O-------O-------O
					Dot* intersect = g1end1Y > g1end2Y ?
						((Segment*)g1)->GetEndPoint2() : ((Segment*)g1)->GetEndPoint1();
					this->AddDot(*intersect);
				} else if (DoubleEquals(max(g1end1Y, g1end2Y), min(g1end1Y, g2end2Y))) {
					// O-------O-------O
					Dot* intersect = g1end1Y < g1end2Y ?
						((Segment*)g1)->GetEndPoint2() : ((Segment*)g1)->GetEndPoint1();
					this->AddDot(*intersect);
				} else {
					//    O-------O
					// O-------O
					throw infinate_intersect_exception();
				}
			} else {
				//line not vertical
				double g1end1X = ((Segment*)g1)->GetEndPoint1()->GetX();
				double g1end2X = ((Segment*)g1)->GetEndPoint2()->GetX();
				double g2end2X = ((Segment*)g2)->GetEndPoint2()->GetX();
				if ((min(g1end1X, g1end2X) > max(g1end1X, g2end2X)) ||
					(max(g1end1X, g1end2X) < min(g1end1X, g2end2X))) {
					// O-------O O-------O
					;
				} else if (DoubleEquals(min(g1end1X, g1end2X), max(g1end1X, g2end2X))) {
					// O-------O-------O
					Dot* intersect = g1end1X > g1end2X ?
						((Segment*)g1)->GetEndPoint2() : ((Segment*)g1)->GetEndPoint1();
					this->AddDot(*intersect);
				} else if (DoubleEquals(max(g1end1X, g1end2X), min(g1end1X, g2end2X))) {
					// O-------O-------O
					Dot* intersect = g1end1X < g1end2X ?
						((Segment*)g1)->GetEndPoint2() : ((Segment*)g1)->GetEndPoint1();
					this->AddDot(*intersect);
				} else {
					//    O-------O
					// O-------O
					throw infinate_intersect_exception();
				}
			}
		}
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

Graph* Container::DeleteGraph(char type, int x1, int y1, int x2, int y2) {
	Graph* delete_graph = NULL;
	string graph_string = string(1, type) + " " + to_string(x1) + " " + to_string(y1) + " "
		+ to_string(x2) + " " + to_string(y2);
	
	for (int i = 0; i < graphs->size(); i++) {
		if (graphs->at(i)->equals(graph_string)) {
			delete_graph = graphs->at(i);
			graphs->erase(graphs->begin() + i);

			dots->clear();
			vector<Graph*>* new_graphs = new vector<Graph*>;
			new_graphs->swap(*graphs);
			for (Graph* graph1 : *new_graphs) {
				for (Graph* graph2 : *graphs) {
					IntersectCalculate(graph1, graph2);
				}
				graphs->push_back(graph1);
			}

			return delete_graph;
		}
	}

	throw graph_not_exist();
}
