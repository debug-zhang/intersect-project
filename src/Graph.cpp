#include "Graph.h"

Dot::Dot(double a, double b) {
    x = a;
    y = b;
}

double Dot::getX() {
    return x;
}

double Dot::getY() {
    return y;
}

bool Dot::equals(Dot b) {
    return this->getX() == b.getX() && this->getY() == b.getY();
}

Line::Line(Dot d1, Dot d2) {
    a = d1.getY() - d2.getY();
    b = d2.getX() - d1.getX();
    c = -a * d1.getX() - b * d1.getY();
}

double Line::getA() {
    return a;
}

double Line::getB() {
    return b;
}

double Line::getC() {
    return c;
}

void Container::add(vector<Dot> vec) {
    for (Dot d:vec) {
        if (dots.empty()) {
            dots.push_back(d);
        } else {
            bool has = false;
            for (Dot i:dots) {
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
    for (Dot d :dots) {
        cout << "(" << d.getX() << "," << d.getY() << ")" << endl;
    }
}

vector<Dot> solve(Graph *a, Graph *b) {
    vector<Dot> res;
    //bool aIsLine = typeid(a).name() == typeid(Line).name();
    //bool bIsLine = typeid(b).name() == typeid(Line).name();
    double a1 = a->getA(), b1 = a->getB(), c1 = a->getC();
    double a2 = b->getA(), b2 = b->getB(), c2 = b->getC();
    double x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    double y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
    Dot d(x, y);
    res.push_back(d);
    return res;
}
