#ifndef LINECROSS_GRAPH_H
#define LINECROSS_GRAPH_H

#include <vector>
#include "string"
#include <iostream>


using namespace std;

class Dot {
private:
    double x, y;
public:
    Dot(double, double);

    double getX();

    double getY();

    bool equals(Dot b);
};

class Graph {
public:
    virtual double getA() = 0;

    virtual double getB() = 0;

    virtual double getC() = 0;
};

class Line : public Graph {
private:
    double a, b, c;
public:
    Line(Dot d1, Dot d2);

    double getA();

    double getB();

    double getC();
};

class Container {
private:
    vector<Dot> dots;
public:
    void add(vector<Dot> vec);

    int size();

    void print();
};

vector<Dot> solve(Graph *a, Graph *b);

#endif
