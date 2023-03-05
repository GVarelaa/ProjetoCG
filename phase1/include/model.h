#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <iostream>
#include <fstream>
#include "point.h"
#include "triangle.h"

using namespace std;

class Model{
    public:
        vector<Point> vertices;
        vector<Triangle> triangles;
        int n_vertices;
        int n_triangles;
        Model(vector<Point> vertices, vector<Triangle> triangles);
        Model(char* path);
        void to_file(char* path);
};

#endif