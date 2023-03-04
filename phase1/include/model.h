#ifndef __MODEL__
#define __MODEL__

#include "point.h"
#include "triangle.h"
#include <vector>
using namespace std;

class Model{
    private:
    vector<Point> points;
    vector<Triangle> triangles;
    public:
    Model(vector<Point> points, vector<Triangle> triangles);
    vector<Point> getPoints();
    vector<Triangle> getTriangles();
};

#endif