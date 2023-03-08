#ifndef __MODEL__
#define __MODEL__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "point.h"
#include "triangle.h"

using namespace std;

class Model{
    public:
        vector<Point> vertices;
        vector<Triangle> triangles;
        int nVertices;
        int nTriangles;
        int nIndexes;
        GLuint vertices_buffer;
        GLuint indexes_buffer;

        Model(vector<Point> vertices, vector<Triangle> triangles);
        Model(char* path); 
        void toFile(char* path);
        void draw();
};

#endif