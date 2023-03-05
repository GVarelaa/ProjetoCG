#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "point.h"
#include "triangle.h"

using namespace std;

class Model{
    private:
    vector<Point> vertices;
    vector<Triangle> triangles;
    int n_vertices;
    int n_triangles;

    public:
    Model(vector<Point> vertices, vector<Triangle> triangles);
    Model(char* path);
    vector<Point> getVertices();
    vector<Triangle> getTriangles();
    void to_file(char* path);
};

#endif